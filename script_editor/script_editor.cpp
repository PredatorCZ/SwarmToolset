#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "font_awesome4/definitions.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "script_editor.hpp"

#include "pugixml.hpp"
#include "spike/io/fileinfo.hpp"
#include "spike/master_printer.hpp"
#include "spike/util/unicode.hpp"

#include <condition_variable>
#include <fstream>
#include <list>
#include <sstream>
#include <thread>

#include "squirrel.h"

#include "sqstdaux.h"
#include "sqstdblob.h"
#include "sqstdio.h"
#include "sqstdmath.h"
#include "sqstdstring.h"
#include "sqstdsystem.h"

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

std::vector<DocumentEdit> documents;
std::map<std::string, size_t> docNameToDoc;
size_t activeDocument = 0;

DocumentEdit &Document(const char *name) {
  auto found = docNameToDoc.find(name);

  if (found == docNameToDoc.end()) {
    found = docNameToDoc.emplace(name, documents.size()).first;
    DocumentEdit &newDoc = documents.emplace_back();
    newDoc.name = found->first.c_str();
    newDoc.editor.SetLanguageDefinition(SQLangDef());
  }

  return documents.at(found->second);
}

void ActiveDocument(const char *name) {
  DocumentEdit &doc = Document(name);
  doc.active = true;
  doc.tabFlags = ImGuiTabItemFlags_SetSelected;
}

template <size_t N> void sq_pushstring(HSQUIRRELVM v, const char (&str)[N]) {
  sq_pushstring(v, str, N - 1);
}

#define DBG_TOP(...)                                                           \
  { printf("%i: %lli " #__VA_ARGS__, __LINE__, sq_gettop(v)); }                \
  __VA_ARGS__;                                                                 \
  { printf(" %lli\n", sq_gettop(v)); }

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

  DBG_TOP(sq_pushroottable(v));
  DBG_TOP(sq_pushstring(v, "UI"));
  DBG_TOP(sq_newtable(v));
  DBG_TOP(sq_newslot(v, -3, SQFalse));
  DBG_TOP(sq_pop(v, 1));

  if (SQ_FAILED(sq_compile(v, readChar, &text, fileName, SQTrue))) {
    return;
  }
  DBG_TOP(sq_pushroottable(v));
  DBG_TOP(sq_call(v, 1, SQFalse, SQTrue));
  DBG_TOP(sq_pop(v, 1));

  AFileInfo finf(fileName);
  std::string fileNameFile(finf.GetFilename());

  DBG_TOP(sq_pushroottable(v));
  DBG_TOP(sq_pushroottable(v));
  DBG_TOP(sq_pushstring(v, "ST_UIS"));

  if (SQ_FAILED(sq_get(v, -2))) {
    DBG_TOP(sq_pushstring(v, "ST_UIS"));
    DBG_TOP(sq_newtable(v));
    DBG_TOP(sq_newslot(v, -3, SQFalse));
    DBG_TOP(sq_pushstring(v, "ST_UIS"));
    DBG_TOP(sq_get(v, -2));
  }

  // root, regsitry, uis table

  DBG_TOP(sq_pushstring(v, fileNameFile.c_str(), fileNameFile.size()));
  DBG_TOP(sq_pushstring(v, "UI"));
  DBG_TOP(sq_get(v, -5)); // UI to table
  DBG_TOP(sq_newslot(v, -3, SQFalse));
  DBG_TOP(sq_pop(v, 3)); // ST_UIS table and root table
}

void RenderDocuments(HSQUIRRELVM v) {
  for (auto &d : documents) {
    if (d.active && !d.opened) {
      std::string bakName = d.name;
      bakName.append(".bak");
      std::ifstream t(bakName);
      ImGuiTabItemFlags bakCase = ImGuiTabItemFlags_UnsavedDocument;
      if (t.fail()) {
        t.open(d.name);
        bakCase = 0;
      }
      if (t.good()) {
        std::string str((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
        d.editor.SetText(str);
        d.opened = true;
        d.tabFlags |= bakCase;
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
      if (!d.active && d.tabFlags == ImGuiTabItemFlags_UnsavedDocument) {
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
            d.opened = false;
          }
          ImGui::SetItemDefaultFocus();
          ImGui::SameLine();
          if (ImGui::Button("Don't Save", ImVec2(120, 0))) {
            d.tabFlags ^= ImGuiTabItemFlags_UnsavedDocument;
            ImGui::CloseCurrentPopup();
            d.opened = false;
          }
          ImGui::SameLine();
          if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
            d.active = true;
            d.tabFlags |= ImGuiTabItemFlags_SetSelected;
          }
          ImGui::EndPopup();
        }
      }

      continue;
    }

    if (d.tabFlags & ImGuiTabItemFlags_SetSelected) {
      d.tabFlags ^= ImGuiTabItemFlags_SetSelected;
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

static SQInteger _sqstd_aux_printerror(HSQUIRRELVM v) {
  SQPRINTFUNCTION pf = sq_geterrorfunc(v);
  if (pf) {
    const SQChar *sErr = 0;
    if (sq_gettop(v) >= 1) {
      if (SQ_SUCCEEDED(sq_getstring(v, 2, &sErr))) {
        pf(v, _SC("\nAN ERROR HAS OCCURRED [%s]\n"), sErr);
      } else {
        pf(v, _SC("\nAN ERROR HAS OCCURRED [unknown]\n"));
      }
      sqstd_printcallstack(v);
    }
  }
  return 0;
}

#include <filesystem>

struct FolderTree {
  std::filesystem::path fullPath;
  std::string folderName;
  std::vector<std::unique_ptr<FolderTree>> children{};
  bool scanned = false;
  bool isFolder = true;
};

void ScanTree(FolderTree &tree) {
  namespace fs = std::filesystem;
  fs::directory_iterator dirIt(tree.fullPath);
  tree.scanned = true;

  for (auto &entry : dirIt) {
    if (!entry.is_directory() && entry.path().extension() != ".nut") {
      continue;
    }
    tree.children.emplace_back(std::make_unique<FolderTree>(FolderTree{
        .fullPath = entry,
        .folderName = entry.path().filename(),
        .isFolder = entry.is_directory(),
    }));
  }
}

void DrawFolderTree(FolderTree &tree, uint32 level, uint32 index,
                    std::filesystem::path &selectedPath) {
  uint64 ptrId = index | (uint64(level) >> 32);
  ImGuiTreeNodeFlags nodeFlags = tree.isFolder ? 0 : ImGuiTreeNodeFlags_Leaf;
  const bool opened = ImGui::TreeNodeEx(
      reinterpret_cast<void *>(ptrId), nodeFlags,
      tree.isFolder ? (ICON_FA_FOLDER " %s") : (ICON_FA_FILE " %s"),
      tree.folderName.c_str());

  if (!tree.isFolder && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) &&
      ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
    selectedPath = tree.fullPath;
  }

  if (!tree.isFolder) {
    ImGui::TreePop();
    return;
  }

  if (opened && !tree.scanned && tree.isFolder) {
    ScanTree(tree);
  }

  if (opened) {
    uint32 childIndex = 0;

    for (auto &f : tree.children) {
      DrawFolderTree(*f, level + 1, childIndex++, selectedPath);
    }

    ImGui::TreePop();
  } else if (tree.scanned) {
    tree.scanned = false;
    tree.children.clear();
  }
}

void sqigui_register_ImVec2(HSQUIRRELVM v);
void sqigui_register_ImDrawList(HSQUIRRELVM v);

struct Window {
  GLFWwindow *window;
  ImGuiContext *context;
};

int InitWindow(Window &wnd, int width, int height, const char *name,
               Window *share = nullptr) {
  wnd.window = glfwCreateWindow(width, height, name, nullptr,
                                share ? share->window : nullptr);

  if (!wnd.window) {
    glfwTerminate();
    return 1;
  }

  static bool GLEW_INITED = false;

  if (!GLEW_INITED) {
    GLEW_INITED = true;
    glfwMakeContextCurrent(wnd.window);
    GLenum err = glewInit();

    if (GLEW_OK != err) {
      glfwTerminate();
      return 2;
    }
  }

  wnd.context = ImGui::CreateContext();
  ImGui::SetCurrentContext(wnd.context);
  ImGui_ImplGlfw_InitForOpenGL(wnd.window, true);
  ImGui_ImplGlfw_SetCallbacksChainForAllWindows(false);
  ImGui_ImplOpenGL3_Init();

  return 0;
}

void SwitchWindow(Window &wnd) {
  glfwMakeContextCurrent(wnd.window);
  ImGui::SetCurrentContext(wnd.context);
}

void WindowBegin(Window &wnd) {
  SwitchWindow(wnd);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void WindowEnd(Window &wnd) {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  glfwSwapBuffers(wnd.window);
}

void DestroyWindow(Window &wnd) {
  SwitchWindow(wnd);
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  glfwDestroyWindow(wnd.window);
}

int main(int, char *[]) {
  es::print::AddPrinterFunction(es::Print);

  NewIdentifierDb("script_editor/builtin.html");
  NewIdentifierDb("script_editor/stdlib.html");

  glfwSetErrorCallback(
      [](int type, const char *msg) { printerror('(' << type << ')' << msg); });

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  Window mainWnd;
  if (int status = InitWindow(mainWnd, 1000, 1000, "Script Editor"); status) {
    return status;
  }

  Window previewWnd;
  if (int status = InitWindow(previewWnd, 1280, 720, "Preview"); status) {
    return status;
  }

  // glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  // GLFWwindow *previewWnd =
  //    glfwCreateWindow(1280, 720, "Preview", nullptr, window);

  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH);

  SwitchWindow(mainWnd);
  WarmColors();
  ImGuiIO &io = ImGui::GetIO();
  io.Fonts->AddFontDefault();

  // merge in icons from Font Awesome
  static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
  ImFontConfig icons_config;
  icons_config.MergeMode = true;
  icons_config.PixelSnapH = true;
  io.Fonts->AddFontFromFileTTF("3rd_party/imgui/font_awesome4/font.ttf", 13,
                               &icons_config, icons_ranges);

  static const char *fileToEdit = "methcall.nut";
  ActiveDocument(fileToEdit);

  HSQUIRRELVM v = sq_open(1024);
  sq_setprintfunc(v, printfunc, printfunc);
  Debugger *debugger = InitDebugger(v);

  sq_pushroottable(v);

  sqstd_register_bloblib(v);
  sqstd_register_iolib(v);
  sqstd_register_systemlib(v);
  sqstd_register_mathlib(v);
  sqstd_register_stringlib(v);
  sqigui_register_ImVec2(v);
  sqigui_register_ImDrawList(v);

  sq_setcompilererrorhandler(v, CompilerError);
  sq_newclosure(v, _sqstd_aux_printerror, 0);
  sq_seterrorhandler(v);

  FolderTree rootTree{.fullPath = "scripts", .folderName = "scripts"};

  while (!glfwWindowShouldClose(mainWnd.window)) {
    WindowBegin(mainWnd);

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

    RenderDebugger(debugger);

    if (ImGui::BeginTabItem("Workspace")) {
      uint32 childIndex = 0;
      std::filesystem::path selectedPath;
      DrawFolderTree(rootTree, 0, childIndex++, selectedPath);

      if (!selectedPath.empty()) {
        ActiveDocument(selectedPath.c_str());
      }
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
    ImGui::EndChild();
    ImGui::SameLine();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::BeginChild("right space");
    ImGui::PopStyleVar();
    ImGui::BeginChild("editor space", ImVec2(0, viewport->WorkSize.y * 0.8),
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

    WindowEnd(mainWnd);
    glfwPollEvents();

    WindowBegin(previewWnd);
    viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::Begin("preview workspace", nullptr, windowFlags);

    auto sq_getsafe = [](HSQUIRRELVM v, SQInteger idx) {
      if (SQ_FAILED(sq_get(v, idx))) {
        SQPRINTFUNCTION pf = sq_geterrorfunc(v);
        sq_getlasterror(v);
        const SQChar *err = nullptr;
        sq_getstring(v, -1, &err);
        pf(v, "%s", err);
      }
    };

    [&] {
      /* 1 */ sq_pushroottable(v);
      /* 2 */ sq_pushstring(v, "ST_UIS");
      /* 2 */ if (SQ_FAILED(sq_get(v, -2))) {
        sq_pop(v, 1);
        return;
      }
      /* 3 */ sq_pushstring(v, "methcall");
      /* 3 */ if (SQ_FAILED(sq_get(v, -2))) {
        sq_pop(v, 2);
        return;
      }
      /* 4 */ sq_pushstring(v, "OnDraw");
      /* 4 */ if (SQ_FAILED(sq_get(v, -2))) {
        sq_pop(v, 3);
        return;
      }

      sq_pushstring(v, "ImDrawList");
      sq_getsafe(v, -6);
      sq_push(v, -2);
      sq_push(v, -3);
      sq_createinstance(v, -3);
      sq_setinstanceup(v, -1, ImGui::GetWindowDrawList());
      sq_call(v, 2, SQFalse, SQTrue);

      sq_pop(v, 6);
    }();

    ImGui::End();
    WindowEnd(previewWnd);
    //glfwPollEvents();
  }

  DestroyWindow(mainWnd);
  DestroyWindow(previewWnd);
  glfwTerminate();
  DeleteDebugger(debugger);
  return 0;
}
