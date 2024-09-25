#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "TextEditor.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "spike/master_printer.hpp"
#include "spike/util/unicode.hpp"

#include <condition_variable>
#include <fstream>
#include <sstream>
#include <thread>

#include "squirrel.h"

#include "sqstdaux.h"
#include "sqstdblob.h"
#include "sqstdio.h"
#include "sqstdmath.h"
#include "sqstdstring.h"
#include "sqstdsystem.h"

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
};

void WarmColors() {
  ImVec4 *colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 0.95f, 1.f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
  colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.29f, 0.29f, 0.29f, 0.54f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.53f, 0.53f, 0.53f, 0.40f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.64f, 0.64f, 0.64f, 0.67f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.17f, 0.15f, 0.12f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 1.00f, 0.02f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.49f, 0.58f, 0.69f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.62f, 0.67f, 0.73f, 1.00f);
  colors[ImGuiCol_Button] = ImVec4(0.70f, 0.70f, 0.70f, 0.40f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.29f, 0.40f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(1.00f, 0.99f, 0.92f, 0.31f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  colors[ImGuiCol_Tab] = ImVec4(0.43f, 0.40f, 0.31f, 0.86f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.33f, 0.18f, 0.80f);
  colors[ImGuiCol_TabActive] = ImVec4(0.66f, 0.63f, 0.19f, 1.00f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.36f, 0.12f, 1.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
  colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
  colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
  colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
  colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

std::vector<std::string> output;

void printfunc(HSQUIRRELVM SQ_UNUSED_ARG(v), const SQChar *s, ...) {
  va_list vl;
  char buffer[0x1000]{};
  va_start(vl, s);
  vsprintf(buffer, s, vl);
  va_end(vl);
  output.emplace_back(buffer);
}

struct CallInfo {
  SQStackInfos info;
  std::string name;
};

std::vector<CallInfo> callStack;
std::vector<const char *> callStackNames;
std::string_view brokeSource;
std::string_view brokeFunction;
std::condition_variable debugBreak;
std::mutex callMutex;
enum class DebugTriggerType {
  Continue,
  StepInto,
  StepOver,
  Stop,
};

DebugTriggerType debugState;
int callStackIndex = 0;

std::vector<CallInfo> CreateCallStack(HSQUIRRELVM v) {
  SQInteger level = 0;
  std::vector<CallInfo> retVal;

  while (SQ_SUCCEEDED(sq_stackinfos(v, level++, &retVal.emplace_back().info))) {
    CallInfo &curInfo = retVal.back();
    curInfo.name = std::string(curInfo.info.funcname) + ':' +
                   std::to_string(curInfo.info.line);
  }

  return retVal;
}

void PrintVariable(HSQUIRRELVM v, const SQChar *name, bool isKey = false) {
  SQObjectType objType = sq_gettype(v, -1);

  bool nodeIsOpen = false;

  if (!isKey) {
    switch (objType) {
    case OT_TABLE:
    case OT_ARRAY:
      nodeIsOpen = ImGui::TreeNode("##treeNode");
      ImGui::SameLine();
      break;
    default:
      break;
    }
  }

  const ImVec4 typeColor(0xee / 255.f, 0xaa / 255.f, 0xbb / 255.f, 1);

  if (name) {
    ImGui::TextColored(typeColor, "%s: ", name);
    ImGui::SameLine();
  } else if (isKey) {
    ImGui::PushStyleColor(ImGuiCol_Text, typeColor);
    ImGui::Text("[");
    ImGui::SameLine(0, 0);
  }

  switch (objType) {
  case OT_NULL:
    ImGui::Text("null");
    break;
  case OT_INTEGER: {
    SQInteger i;
    sq_getinteger(v, -1, &i);
    ImGui::Text("%i", i);
    break;
  }
  case OT_FLOAT: {
    SQFloat f;
    sq_getfloat(v, -1, &f);
    ImGui::Text("%f", f);
    break;
  }
  case OT_USERPOINTER: {
    SQUserPointer p;
    sq_getuserpointer(v, -1, &p);
    ImGui::Text("%p", p);
    break;
  }
  case OT_STRING: {
    const SQChar *s;
    sq_getstring(v, -1, &s);
    ImGui::Text("%s", s);
    break;
  }
  case OT_TABLE:
    if (isKey) {
      ImGui::Text("<table>");
    } else {
      ImGui::Text("{...}");
    }

    if (nodeIsOpen) {
      sq_pushnull(v);
      while (SQ_SUCCEEDED(sq_next(v, -2))) {
        sq_push(v, -2);
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        PrintVariable(v, nullptr, true);
        ImGui::SameLine();
        PrintVariable(v, nullptr);
        sq_pop(v, 1);
      }

      sq_pop(v, 1);
      ImGui::TreePop();
    }
    break;
  case OT_ARRAY:
    if (isKey) {
      ImGui::Text("<array>");
    } else {
      ImGui::Text("{...}");
    }
    if (nodeIsOpen) {
      sq_pushnull(v);
      while (SQ_SUCCEEDED(sq_next(v, -2))) {
        sq_push(v, -2);
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        PrintVariable(v, nullptr, true);
        ImGui::SameLine();
        PrintVariable(v, nullptr);
        sq_pop(v, 1);
      }

      sq_pop(v, 1);
      ImGui::TreePop();
    }
    break;
  case OT_CLOSURE: {
    const SQChar *s;
    sq_getclosurename(v, -1);
    sq_getstring(v, -1, &s);
    sq_pop(v, 1);
    ImGui::Text("<function: %s>", s);
    break;
  }
  case OT_NATIVECLOSURE: {
    const SQChar *s;
    sq_getclosurename(v, -1);
    sq_getstring(v, -1, &s);
    sq_pop(v, 1);
    ImGui::Text("<native function: %s>", s);
    break;
  } break;
  case OT_GENERATOR:
    ImGui::Text("<generator>");
    break;
  case OT_USERDATA:
    ImGui::Text("<userdata>");
    break;
  case OT_THREAD:
    ImGui::Text("<thread>");
    break;
  case OT_CLASS: {
    const SQChar *s;
    sq_getclassname(v, &s);
    ImGui::Text("<class: %s>", s);
    break;
  }
  case OT_INSTANCE:
    ImGui::Text("<instance>");
    break;
  case OT_WEAKREF:
    ImGui::Text("<weakref>");
    break;
  case OT_BOOL: {
    SQBool bval;
    sq_getbool(v, -1, &bval);
    ImGui::Text("%s", bval ? "true" : "false");
  } break;
  default:
    assert(0);
    break;
  }
  sq_pop(v, 1);
  if (isKey) {
    ImGui::SameLine(0, 0);
    ImGui::Text("]: ");
    ImGui::PopStyleColor();
  }
}

void InspectCurrentFrame(HSQUIRRELVM v) {
  const SQChar *name;
  SQUnsignedInteger seq = 0;

  if (!ImGui::BeginTable("varaibles table", 1, ImGuiTableFlags_RowBg)) {
    return;
  }

  while ((name = sq_getlocal(v, callStackIndex, seq++))) {
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::PushID(seq);
    PrintVariable(v, name);
    ImGui::PopID();
  }

  ImGui::EndTable();
}

struct InterruptedCall : std::exception {};

struct DocumentEdit {
  TextEditor editor;
  double lastTimeTextChanged = 0;
  TextEditor::ErrorMarkers errors;
  const char *name;
  bool active = false;
  bool opened = false;
  ImGuiTabItemFlags tabFlags = 0;
};

std::vector<DocumentEdit> documents;
std::map<std::string, size_t> docNameToDoc;
size_t activeDocument = 0;

DocumentEdit &Document(const char *name) {
  auto found = docNameToDoc.find(name);

  if (found == docNameToDoc.end()) {
    found = docNameToDoc.emplace(name, documents.size()).first;
    DocumentEdit &newDoc = documents.emplace_back();
    newDoc.name = found->first.c_str();
    newDoc.editor.SetLanguageDefinition(langDef);
  }

  return documents.at(found->second);
}

void DebugHook(HSQUIRRELVM v, SQInteger /*type*/, const SQChar *sourcename,
               SQInteger line, const SQChar *funcname) {
  // printf("%c %s %lli %s\n", (char)type, sourcename, line, funcname);

  if (Document(sourcename).editor.GetBreakpoints().contains(line) ||
      debugState == DebugTriggerType::StepInto ||
      (debugState == DebugTriggerType::StepOver && brokeFunction == funcname)) {
    brokeSource = sourcename;
    brokeFunction = funcname;
    Document(sourcename).editor.SetCurrentBreakPoint(line);
    callStack = CreateCallStack(v);

    for (auto &s : callStack) {
      callStackNames.emplace_back(s.name.c_str());
    }

    std::unique_lock lk(callMutex);
    debugBreak.wait(lk);
    Document(sourcename).editor.SetCurrentBreakPoint(-1);
    callStackNames.clear();

    if (debugState == DebugTriggerType::Stop) {
      throw InterruptedCall{};
    }
  }
}

void sq_compile(HSQUIRRELVM v, std::stringstream text, const char *fileName) {
  auto readChar = [](SQUserPointer iobuf) -> SQInteger {
    std::stringstream *str = static_cast<std::stringstream *>(iobuf);
    static const SQInteger utf8_lengths[16] = {
        1, 1, 1, 1, 1, 1, 1, 1, /* 0000 to 0111 : 1 byte (plain ASCII) */
        0, 0, 0, 0,             /* 1000 to 1011 : not valid */
        2, 2,                   /* 1100, 1101 : 2 bytes */
        3,                      /* 1110 : 3 bytes */
        4                       /* 1111 :4 bytes */
    };
    static const unsigned char byte_masks[5] = {0, 0, 0x1f, 0x0f, 0x07};
    unsigned char inchar;
    SQInteger c = 0;
    if (str->read(reinterpret_cast<char *>(&inchar), 1); str->eof()) {
      return 0;
    }
    c = inchar;
    //
    if (c >= 0x80) {
      SQInteger tmp;
      SQInteger codelen = utf8_lengths[c >> 4];
      if (codelen == 0) {
        return 0;
      }
      //"invalid UTF-8 stream";
      tmp = c & byte_masks[codelen];
      for (SQInteger n = 0; n < codelen - 1; n++) {
        tmp <<= 6;
        if (str->read(reinterpret_cast<char *>(&inchar), 1); str->eof()) {
          return 0;
        }
        tmp |= inchar & 0x3F;
      }
      c = tmp;
    }
    return c;
  };

  sq_compile(v, readChar, &text, fileName, SQTrue);
}

void RenderDocuments(HSQUIRRELVM v) {
  for (auto &d : documents) {
    if (d.active && !d.opened) {
      std::string bakName = d.name;
      bakName.append(".bak");
      std::ifstream t(bakName);
      if (t.fail()) {
        t.open(d.name);
      }
      if (t.good()) {
        std::string str((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
        d.editor.SetText(str);
        d.opened = true;
      }
    }

    auto Save = [&] {
      std::string newName1 = d.name;
      newName1.append(".old1");
      std::string newName2 = d.name;
      newName2.append(".old2");
      remove(newName2.c_str());
      rename(newName1.c_str(), newName2.c_str());
      rename(d.name, newName1.c_str());
      std::ofstream str(d.name);

      if (str.good()) {
        std::string text = d.editor.GetText();
        str << text;

        std::string bakName = d.name;
        bakName.append(".bak");
        remove(bakName.c_str());
      }

      d.tabFlags ^= ImGuiTabItemFlags_UnsavedDocument;
    };

    if (!ImGui::BeginTabItem(d.name, &d.active, d.tabFlags)) {
      if (d.tabFlags & ImGuiTabItemFlags_UnsavedDocument) {
        ImGui::OpenPopup("Unsaved document");
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing,
                                ImVec2(0.5f, 0.5f));
        if (ImGui::BeginPopupModal("Unsaved document", NULL,
                                   ImGuiWindowFlags_AlwaysAutoResize)) {
          ImGui::Text("Document %s hasn't been saved", d.name);
          ImGui::Separator();

          if (ImGui::Button("Save", ImVec2(120, 0))) {
            Save();
            ImGui::CloseCurrentPopup();
          }
          ImGui::SetItemDefaultFocus();
          ImGui::SameLine();
          if (ImGui::Button("Don't Save", ImVec2(120, 0))) {
            d.tabFlags ^= ImGuiTabItemFlags_UnsavedDocument;
            ImGui::CloseCurrentPopup();
          }
          ImGui::SameLine();
          if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
            d.active = true;
          }
          ImGui::EndPopup();
        }
      }

      continue;
    }

    if (d.lastTimeTextChanged + 1 <= ImGui::GetTime()) {
      std::string text = d.editor.GetText();
      std::string bakName = d.name;
      bakName.append(".bak");
      std::ofstream str(bakName);
      if (str.good()) {
        str << text;
      }
      sq_compile(v, std::stringstream(std::move(text)), d.name);
      d.lastTimeTextChanged = std::numeric_limits<double>().infinity();
      auto newErrors = std::move(d.errors);
      d.editor.SetErrorMarkers(newErrors);
    }
    d.editor.Render(d.name);
    if (d.editor.IsTextChanged()) {
      d.lastTimeTextChanged = ImGui::GetTime();
      d.tabFlags = ImGuiTabItemFlags_UnsavedDocument;
    }

    ImGuiIO &io = ImGui::GetIO();
    bool ctrl = io.ConfigMacOSXBehaviors ? io.KeySuper : io.KeyCtrl;
    if ((d.tabFlags & ImGuiTabItemFlags_UnsavedDocument) && ctrl &&
        ImGui::IsKeyPressed(ImGuiKey_S)) {
      Save();
    }
    ImGui::EndTabItem();
  }
}

void CompilerError(HSQUIRRELVM, const SQChar *sErr, const SQChar *sSource,
                   SQInteger line, SQInteger /*column*/) {
  Document(sSource).errors[line].append(sErr).push_back('\n');
}

int main(int, char *argv[]) {
  es::print::AddPrinterFunction(es::Print);

  glfwSetErrorCallback(
      [](int type, const char *msg) { printerror('(' << type << ')' << msg); });

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  int width = 1800;
  int height = 1020;

  GLFWwindow *window =
      glfwCreateWindow(width, height, "Script Editor", nullptr, nullptr);

  if (!window) {
    glfwTerminate();
    return 1;
  }

  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  GLFWwindow *previewWnd =
      glfwCreateWindow(width, height, "Preview", nullptr, window);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH);

  glfwMakeContextCurrent(window);

  GLenum err = glewInit();

  if (GLEW_OK != err) {
    glfwTerminate();
    return 2;
  }

  ImGuiContext *mainCtx = ImGui::CreateContext();
  WarmColors();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();
  ImGuiContext *previewCtx = ImGui::CreateContext();
  ImGui::SetCurrentContext(previewCtx);
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();

  static const char *fileToEdit = "methcall.nut";
  Document(fileToEdit).active = true;

  HSQUIRRELVM v = sq_open(1024);
  sq_setprintfunc(v, printfunc, printfunc);
  sq_setnativedebughook(v, DebugHook);
  sq_enabledebuginfo(v, SQTrue);

  sq_pushroottable(v);

  sqstd_register_bloblib(v);
  sqstd_register_iolib(v);
  sqstd_register_systemlib(v);
  sqstd_register_mathlib(v);
  sqstd_register_stringlib(v);

  sq_setcompilererrorhandler(v, CompilerError);

  std::condition_variable callRequested;
  SQInteger numParams = 1;
  bool debugging = false;

  std::jthread debugLoop([&](std::stop_token tok) {
    std::mutex callMutex;
    std::unique_lock lk(callMutex);
    while (true) {
      callRequested.wait(lk);

      if (tok.stop_requested()) {
        return;
      }
      debugging = true;
      sq_call(v, numParams, SQFalse, SQTrue);
      debugging = false;
    }
  });

  auto sq_debug_call = [&](SQInteger numParams_) {
    numParams = numParams_;
    callRequested.notify_all();
  };

  while (!glfwWindowShouldClose(window)) {
    glfwMakeContextCurrent(window);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::SetCurrentContext(mainCtx);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
    ImGui::Begin("main workspace", nullptr, windowFlags);
    ImGui::BeginChild("left space", ImVec2(200, 0),
                      ImGuiChildFlags_ResizeX | ImGuiChildFlags_Border);
    ImGui::BeginTabBar("left tabspace");

    if (ImGui::BeginTabItem("Debug")) {
      ImGui::BeginDisabled(debugging);
      if (ImGui::Button("Start")) {
        sq_pushroottable(v);
        sq_debug_call(1);
      }
      ImGui::EndDisabled();

      ImGui::SameLine();
      ImGui::BeginDisabled(!debugging);

      if (ImGui::Button("Continue")) {
        debugState = DebugTriggerType::Continue;
        debugBreak.notify_all();
      }

      ImGui::SameLine();

      if (ImGui::Button("Step Over")) {
        debugState = DebugTriggerType::StepOver;
        debugBreak.notify_all();
      }

      ImGui::SameLine();

      if (ImGui::Button("Step Into")) {
        debugState = DebugTriggerType::StepInto;
        debugBreak.notify_all();
      }

      ImGui::SameLine();

      if (ImGui::Button("Stop")) {
        debugState = DebugTriggerType::Stop;
        debugBreak.notify_all();
      }

      ImGui::EndDisabled();

      if (ImGui::CollapsingHeader("Local Variables",
                                  ImGuiTreeNodeFlags_DefaultOpen) &&
          callStackNames.size()) {
        InspectCurrentFrame(v);
      }

      if (ImGui::CollapsingHeader("Call Stack",
                                  ImGuiTreeNodeFlags_DefaultOpen) &&
          callStackNames.size()) {
        ImGui::ListBox("##CallStackListBox", &callStackIndex,
                       callStackNames.data(), callStackNames.size());
      }

      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Workspace")) {
      ImGui::Button("Samole button");
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
    ImGui::EndChild();
    ImGui::SameLine();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::BeginChild("right space");
    ImGui::PopStyleVar();
    ImGui::BeginChild("editor space", ImVec2(0, height * 0.8),
                      ImGuiChildFlags_ResizeY | ImGuiChildFlags_Border);
    ImGui::BeginTabBar("right tabspace");
    RenderDocuments(v);
    ImGui::EndTabBar();
    ImGui::EndChild();

    ImGui::BeginChild("output", ImVec2(0, 0), ImGuiChildFlags_Border);

    if (ImGui::BeginTable("output table", 1)) {
      for (auto &o : output) {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TextUnformatted(o.data(), o.data() + o.size());
      }
      ImGui::EndTable();
    }

    ImGui::EndChild();
    ImGui::EndChild();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();

    glfwMakeContextCurrent(previewWnd);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::SetCurrentContext(previewCtx);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Button("Press me");

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(previewWnd);
  }

  ImGui::SetCurrentContext(mainCtx);
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::SetCurrentContext(previewCtx);
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext(mainCtx);
  ImGui::DestroyContext(previewCtx);

  glfwDestroyWindow(window);
  glfwDestroyWindow(previewWnd);
  glfwTerminate();
  debugLoop.request_stop();
  callRequested.notify_all();
  return 0;
}
