#include "script.hpp"
#include "script/core.hpp"
#include "spike/crypto/jenkinshash.hpp"
#include "spike/io/fileinfo.hpp"
#include "spike/master_printer.hpp"
#include "spike/reflect/reflector.hpp"
#include "spike/reflect/reflector_fwd.hpp"
#include <algorithm>
#include <cctype>
#include <istream>

struct ScriptParserImpl : ScriptParser {
  void EnterScope() {
    while (!stream.eof()) {
      char curChar;
      stream.get(curChar);

      switch (curChar) {
      case '\n':
      case '\r':
      case ' ':
      case '\t':
        break;
      case '/':
        if (prevChar == '/') {
          SkipLine();
          break;
        }
        [[fallthrough]];
      case '[':
      case ']':
      case ':':
      case '}':
      case '"':
        throw std::runtime_error("Format error, expected {");
      case '{':
        // level++;
        return;
      }
    }
  };

  bool GetMember() {
    while (!stream.eof()) {
      char curChar;
      stream.get(curChar);

      switch (curChar) {
      case '\n':
      case '\r':
      case '\t':
        break;
      case '/':
        if (prevChar == '/') {
          SkipLine();
          break;
        } else if (prevChar == 0) {
          prevChar = curChar;
          break;
        }
        [[fallthrough]];
      case '[':
      case ']':
      case '{':
      case '"':
        throw std::runtime_error("Format error, expected [\\w:]");
      case ':':
        return false;
      case '}':
        return true;

      case ' ':
        if (!bufferIter) {
          break;
        }
        [[fallthrough]];
      default:
        prevChar = curChar;
        curBuffer[bufferIter++] = curChar;
      }
    }

    throw std::runtime_error("Format error");
  };

  void GetClass() {
    while (!stream.eof()) {
      char curChar;
      stream.get(curChar);

      switch (curChar) {
      case '\n':
      case '\r':
      case ' ':
      case '\t':
      case 0:
        break;
      case '/':
        if (prevChar == '/') {
          SkipLine();
          break;
        } else if (prevChar == 0) {
          prevChar = curChar;
          break;
        }
        [[fallthrough]];
      case '[':
      case ']':
      case '{':
      case '}':
      case '"':
        throw std::runtime_error("Format error, expected [\\w:]");
      case ':':
        return;
      default:
        prevChar = curChar;
        curBuffer[bufferIter++] = curChar;
      }
    }
  }

  std::string_view PopToken() {
    std::string_view retVal(curBuffer, bufferIter);
    bufferIter = 0;
    prevChar = 0;
    return retVal;
  }

  void SkipLine() {
    do {
      char dummy;
      stream.get(dummy);

      if (dummy == '\n') {
        break;
      }
    } while (!stream.eof());

    prevChar = 0;
    bufferIter = 0;
  }

  void ExitScope() {
    while (!stream.eof()) {
      char curChar;
      stream.get(curChar);

      switch (curChar) {
      case '\n':
      case '\r':
      case ' ':
      case '\t':
        break;
      case '/':
        if (prevChar == '/') {
          SkipLine();
          break;
        }
        [[fallthrough]];
      case '[':
      case ']':
      case ':':
      case '{':
      case '"':
        throw std::runtime_error("Format error, expected }");
      case '}':
        // level--;
        return;
      }
    }
  }

  ValueType DetermineValue() {
    while (!stream.eof()) {
      char curChar;
      stream.get(curChar);

      switch (curChar) {
      case '\n':
      case '\r':
      case ' ':
      case '\t':
        break;
      case '/':
        if (prevChar == '/') {
          SkipLine();
          break;
        }
        [[fallthrough]];
      case ']':
      case ':':
      case '{':
      case '}':
        throw std::runtime_error("Format error, expected [\"\\[\\w]");
      case '"':
        return VL_SIMPLE;
      case '[':
        return VL_ARRAY;
      default:
        prevChar = curChar;
        return VL_SUBCLASS;
      }
    }

    throw std::runtime_error("Format error");
  }

  void ProcessClassMembers() {
    auto SimpleValue = [&] {
      while (!stream.eof()) {
        char curChar;
        stream.get(curChar);

        switch (curChar) {
        case '"':
          return;
        default:
          curBuffer[bufferIter++] = curChar;
          break;
        }
      }
    };

    // ["cb", ..."cb"]
    auto ArrayValues = [&] {
      while (!stream.eof()) {
        char curChar;
        stream.get(curChar);

        switch (curChar) {
        case '\n':
        case '\r':
        case ' ':
        case '\t':
          break;
        case ']':
          if (bufferIter > 0) {
            newValue(PopToken());
          }
          return;
        case ',':
          newValue(PopToken());
          break;
        case '"':
          SimpleValue();
          break;
        default:
          /*case ':':
          case '}':
          case '{':*/
          throw std::runtime_error("Format error, expected [\"\\w]");
        }
      }
    };

    while (!stream.eof()) {
      if (GetMember()) {
        break;
      }
      EnterScope();
      auto memberName = PopToken();
      auto vType = DetermineValue();
      newMember(memberName, vType);

      switch (vType) {
      case VL_SIMPLE: {
        SimpleValue();
        newValue(PopToken());
        ExitScope();
        break;
      }
      case VL_ARRAY:
        ArrayValues();
        ExitScope();
        break;
      case VL_SUBCLASS:
        curBuffer[bufferIter++] = prevChar;
        ProcessClassMembers();
        subclassEnd();
        break;
      default:
        throw std::runtime_error("Invalid value type");
      }
    }
  }

  void Process() {
    while (!stream.eof()) {
      GetClass();
      EnterScope();
      auto className = PopToken();

      if (className.empty() || className == "class_InstanceObjectBuilder") {
        return;
      }
      newClass(className);

      ProcessClassMembers();
    }
  }
};

std::unique_ptr<Resource> AllocClass(std::string_view className) {
  if (!className.starts_with("class_")) {
    throw std::runtime_error("class must start with class_");
  }
  className.remove_prefix(6);

  auto found = reflectorStatic::Registry().find(className);

  if (found == reflectorStatic::Registry().end()) {
    throw std::runtime_error("class not found");
  }

  auto rClass = found->second;
  void *data = malloc(rClass->classSize);
  if (!rClass->methods.constructor) {
    throw std::runtime_error("class " + std::string(className) +
                             " not constructible");
  }
  rClass->methods.constructor(data);
  Resource *resData = static_cast<Resource *>(data);
  resData->refl = rClass;

  return std::unique_ptr<Resource>(resData);
}

void ScriptParser::Process() {
  static_cast<ScriptParserImpl *>(this)->Process();
}

struct ReflectedInstanceFriend : ReflectedInstance {
  using ReflectedInstance::rfStatic;
};

class ReflectorMemberFriend : public ReflectorMember {
public:
  using ReflectorMember::ReflectorMember;
  using ReflectorMember::operator=;
  operator const ReflType &() const {
    return ReflectedInstanceFriend{data}.rfStatic->types[id];
  }
};

void LoadScript(std::istream &str,
                std::vector<std::unique_ptr<Resource>> &resources) {
  std::vector<ReflectorPureWrap> classStack;
  ReflectorMemberFriend member{{}, 0};
  int curMapItem = -1;
  int curArrayItem = -1;
  int index = -1;

  auto NewClass = [&](std::string_view name) {
    Resource *res = resources.emplace_back(AllocClass(name)).get();
    classStack.clear();
    classStack.emplace_back(ReflectedInstance{res->refl, res});
  };

  auto NewMember = [&](std::string_view name, ValueType type) {
    if (classStack.empty()) {
      return;
    }

    if (name.size() > 3 && name.back() == '_' &&
        name.at(name.size() - 3) == '_') {
      index = name.at(name.size() - 2) - '0';
      name.remove_suffix(3);
    }

    ReflectorPureWrap &lastClass = classStack.back();

    if (curMapItem > -1) {
      lastClass = member.ReflectedSubClass(curMapItem++);
      // there isn't map of subclasses so far
      lastClass["key"] = name;
      return;
    }

    member = lastClass[name];

    if (!member) {
      if (type == VL_SUBCLASS) {
        classStack.emplace_back(ReflectedInstance{nullptr, nullptr});
      }
      return;
    }

    if (type == VL_SUBCLASS) {
      ReflType type = member;
      curMapItem = (type.container == REFContainer::ContainerVectorMap) - 1;
      classStack.emplace_back(
          member.ReflectedSubClass(std::max(0, int(index))));
      return;
    }

    curArrayItem = (type == VL_ARRAY) - 1;

    if (!member) {
      PrintError("Member: ", name,
                 " not found in class: ", lastClass.ClassName());
      return;
    }
  };

  auto SetValue = [&](ReflectorMemberFriend member, std::string_view name) {
    if (!member) {
      return;
    }
    if (member.IsReflectedSubClass()) {
      ReflectorPureWrap subClass(
          member.ReflectedSubClass(std::max(curArrayItem, 0)));

      if (subClass.data) {
        if (subClass.ClassName() == "ResourceRef") {
          member = subClass["asString"];
        } else if (subClass.ClassName() == "Color") {
          member = subClass["raw"];
        }
      }
    }

    if (ReflType type = member; type.type == REFType::Bool) {
      int isTrue = name.front() == '1';
      if (!isTrue && name.front() != '0') {
        ReflectorPureWrap &lastClass = classStack.back();
        ReflectedInstanceFriend inst{lastClass.data};
        PrintWarning("Expected boolean for", lastClass.ClassName(),
                     "::", inst.rfStatic->typeNames[type.index],
                     " got: ", name);
        if (curArrayItem > -1) {
          curArrayItem++;
        }
        return;
      }
      member.ReflectValue(isTrue, curArrayItem);
      if (curArrayItem > -1) {
        curArrayItem++;
      }
      return;
    } else if (type.type == REFType::String &&
               type.asClass.typeHash == JenHash("FilePath")) {
      std::string nPath(name);
      std::transform(nPath.begin(), nPath.end(), nPath.begin(),
                     [](char i) { return std::tolower(i); });
      AFileInfo finf(nPath);
      member.ReflectValue(finf.GetFullPath(), std::max(index, curArrayItem));
    } else {
      member.ReflectValue(name, std::max(index, curArrayItem));
    }

    if (curArrayItem > -1) {
      curArrayItem++;
    }
  };

  auto NewValue = [&](std::string_view name) {
    if (curMapItem > -1) {
      ReflectorPureWrap lastClass = classStack.back();
      auto sub = lastClass["value"];
      SetValue(reinterpret_cast<ReflectorMemberFriend &>(sub), name);
      return;
    }

    SetValue(member, name);
  };

  ScriptParserImpl parser{str};
  parser.newClass = NewClass;
  parser.newMember = NewMember;
  parser.newValue = NewValue;
  parser.subclassEnd = [&] {
    if (classStack.empty()) {
      throw std::logic_error("wtf?");
    }
    classStack.pop_back();
    curMapItem = -1;
  };

  parser.Process();
}
