#include "TextEditor.h"
#include "pugixml.hpp"
#include <list>

struct IdentifierDesc {
  enum Command : uint8_t {
    C_TEXT,
    C_IDENTIFIER,
    C_TYPE,
    C_SAME_LINE,
    C_NO_PAD_START,
    C_NO_PAD_END,
    C_NEXT_LINE,
  };
  std::vector<const char *> chunks;
  std::vector<Command> commands;

  void Render() const {
    size_t chunkId = 0;

    for (auto c : commands) {
      switch (c) {
      case C_TEXT:
        ImGui::TextUnformatted(chunks.at(chunkId++));
        break;
      case C_IDENTIFIER:
        ImGui::TextColored(
            ImGui::ColorConvertU32ToFloat4(TextEditor::GetDarkPalette().at(
                int(TextEditor::PaletteIndex::KnownIdentifier))),
            "%s", chunks.at(chunkId++));
        break;
      case C_TYPE:
        ImGui::TextColored(ImVec4(0xee / 255.f, 0xaa / 255.f, 0xbb / 255.f, 1),
                           "%s", chunks.at(chunkId++));
        break;
      case C_SAME_LINE:
        ImGui::SameLine();
        break;
      case C_NEXT_LINE:
        ImGui::NewLine();
        break;
      default:
        break;
      }
    }
  }
};

struct IdentKey {
  std::string_view name;
  bool isFunc = true;

  bool operator<(const IdentKey &o) const {
    if (o.isFunc == isFunc) {
      return name < o.name;
    }

    return isFunc < o.isFunc;
  }
};

std::map<std::string_view, std::map<IdentKey, IdentifierDesc>> IDENTIFIERS;
std::list<pugi::xml_document> ID_HOLDER;

TextEditor::LanguageDefinition langDef{
    .mName = "Squirrel",
    .mKeywords{
        "base",       "break", "case",    "catch",    "class",    "clone",
        "continue",   "const", "default", "delete",   "else",     "enum",
        "extends",    "for",   "foreach", "function", "if",       "in",
        "local",      "null",  "resume",  "return",   "switch",   "this",
        "throw",      "try",   "typeof",  "while",    "yield",    "constructor",
        "instanceof", "true",  "false",   "static",   "__LINE__", "__FILE__",
        "rawcall",
    },
    .mCommentStart = "/*",
    .mCommentEnd = "*/",
    .mSingleLineComment = "//",
    .mTokenize = TextEditor::LanguageDefinition::CPlusPlus().mTokenize,
    .mIdentifier =
        [](const TextEditor::IndentifierAt &id) {
          IdentKey key{
              .name = id.rName,
              .isFunc = id.isFunc,
          };

          auto rootId = IDENTIFIERS.find("");
          auto found = rootId->second.find(key);

          if (id.mName == "::") {
            auto foundGroup = IDENTIFIERS.find(id.lName);

            if (foundGroup != IDENTIFIERS.end()) {
              auto foundId = foundGroup->second.find(key);

              if (foundId != foundGroup->second.end()) {
                found = foundId;
              }
            }
          }

          if (found != rootId->second.end()) {
            ImGui::BeginTooltip();
            found->second.Render();
            ImGui::EndTooltip();
          }
        },
};

TextEditor::LanguageDefinition &SQLangDef() { return langDef; }

void ParseArgs(IdentifierDesc &idesc, pugi::xml_node &c,
               bool throwEmpty = false) {
  size_t hSize = idesc.chunks.size();
  size_t cSize = idesc.commands.size();
  idesc.chunks.emplace_back("(");
  idesc.commands.emplace_back(IdentifierDesc::C_TEXT);
  idesc.commands.emplace_back(IdentifierDesc::C_SAME_LINE);
  int optlevel = 0;
  int curarg = 0;

  auto ParseChildren = [&](pugi::xml_node &p) {
    for (pugi::xml_node &pc : p.children()) {
      if (pc.name() == std::string_view("code")) {
        pugi::xml_attribute attrib = pc.attribute("class");

        if (attrib.as_string() == std::string_view("optarg")) {
          optlevel++;
          idesc.chunks.emplace_back(curarg ? " [, " : " [");
          idesc.commands.emplace_back(IdentifierDesc::C_TEXT);
          idesc.commands.emplace_back(IdentifierDesc::C_SAME_LINE);
        } else if (attrib.as_string() == std::string_view("arg")) {
          if (curarg) {
            idesc.chunks.emplace_back(", ");
            idesc.commands.emplace_back(IdentifierDesc::C_TEXT);
            idesc.commands.emplace_back(IdentifierDesc::C_SAME_LINE);
          }
        }

        if (!attrib.empty()) {
          idesc.chunks.emplace_back(pc.text().as_string());
          idesc.commands.emplace_back(IdentifierDesc::C_IDENTIFIER);
          idesc.commands.emplace_back(IdentifierDesc::C_SAME_LINE);
          curarg++;
          ParseArgs(idesc, pc, true);
        }
      }
    }
  };

  if (throwEmpty) {
    ParseChildren(c);
  } else {
    for (pugi::xml_node &p : c.children("p")) {
      ParseChildren(p);
    }
  }

  if (!curarg && throwEmpty) {
    idesc.chunks.resize(hSize);
    idesc.commands.resize(cSize);
    return;
  }

  idesc.chunks.emplace_back(")");
  idesc.commands.emplace_back(IdentifierDesc::C_TEXT);
  if (throwEmpty) {
    idesc.commands.emplace_back(IdentifierDesc::C_SAME_LINE);
  }
}

void ParseGroup(pugi::xml_node &c, std::string_view group) {
  pugi::xml_node h1 = c.child("h1");
  if (h1.empty()) {
    return;
  }
  const pugi::char_t *h1Class = h1.attribute("class").as_string();
  IdentifierDesc idesc;

  if (h1Class && *h1Class) {
    idesc.chunks.emplace_back(h1Class);
    idesc.commands.emplace_back(IdentifierDesc::C_TYPE);
    idesc.commands.emplace_back(IdentifierDesc::C_SAME_LINE);
  }

  idesc.chunks.emplace_back(h1.text().as_string());
  idesc.commands.emplace_back(IdentifierDesc::C_IDENTIFIER);

  if (!h1Class || !*h1Class) {
    idesc.commands.emplace_back(IdentifierDesc::C_NO_PAD_START);
    idesc.commands.emplace_back(IdentifierDesc::C_SAME_LINE);
    ParseArgs(idesc, c);
    idesc.commands.emplace_back(IdentifierDesc::C_NO_PAD_END);
  }

  idesc.commands.emplace_back(IdentifierDesc::C_NEXT_LINE);

  for (pugi::xml_node &p : c.children("p")) {
    for (pugi::xml_node &pc : p.children()) {
      idesc.chunks.emplace_back(pc.text().as_string());
      idesc.commands.emplace_back(pc.name() == std::string_view("code")
                                      ? IdentifierDesc::C_TYPE
                                      : IdentifierDesc::C_TEXT);
      idesc.commands.emplace_back(IdentifierDesc::C_SAME_LINE);
    }
    idesc.commands.pop_back();
  }

  IdentKey key{
      .name = h1.text().as_string(),
      .isFunc = !h1Class || !*h1Class,
  };

  IDENTIFIERS[group].emplace(key, std::move(idesc));
}

void NewIdentifierDb(const char *path) {
  pugi::xml_document &doc = ID_HOLDER.emplace_back();
  doc.load_file(path);

  for (auto &c : doc.child("body")) {
    if (c.name() == std::string_view("div")) {
      const pugi::char_t *divClass = c.attribute("class").as_string();

      if (divClass && *divClass) {
        for (auto &cc : c.children("div")) {
          ParseGroup(cc, divClass);
        }
      } else {
        ParseGroup(c, {});
      }
    }
  }
}
