#include "script.hpp"
#include "script/core.hpp"
#include "spike/reflect/reflector.hpp"
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
      default:
        prevChar = curChar;
        curBuffer[bufferIter++] = curChar;
      }
    }
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
          newValue(PopToken());
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

      if (className.empty()) {
        return;
      }
      newClass(className);

      ProcessClassMembers();
    }
  }
};

struct ResourceHolder {
  void *data;
  const reflectorStatic *refl;

  ResourceHolder(const reflectorStatic *refl_) : refl(refl_) {
    data = malloc(refl->classSize);
    refl->methods.constructor(data);
  }

  ResourceHolder(const ResourceHolder &) = delete;
  ResourceHolder(ResourceHolder &&other) : data(other.data), refl(other.refl) {
    other.data = nullptr;
  }

  ~ResourceHolder() {
    if (data) {
      refl->methods.destructor(data);
      free(data);
    }
  }
};

std::vector<ResourceHolder> RESOURCES;

Resource* AllocClass(std::string_view className) {
  if (!className.starts_with("class_")) {
    throw std::runtime_error("class must start with class_");
  }
  className.remove_prefix(6);

  auto found = reflectorStatic::Registry().find(className);

  if (found == reflectorStatic::Registry().end()) {
    throw std::runtime_error("class not found");
  }

  auto rClass = found->second;
  auto &res = RESOURCES.emplace_back(rClass);
  return static_cast<Resource*>(res.data);
}

void ScriptParser::Process() {
  static_cast<ScriptParserImpl *>(this)->Process();
}

ResourceRef::ResourceRef(Resource *res) {}
