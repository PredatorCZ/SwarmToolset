#pragma once
#include "imgui.h"
#include <filesystem>
#include <functional>
#include <set>

enum class ArrayNodeSignal {
  Close,
  Open,
  Add,
  Insert,
  Duplicate,
  Remove,
  Clean,
  MoveUp,
  MoveDown,
  Get,
};

struct ArrayNode {
  std::function<void(int)> onSignal[9]{};
  ImVec4 bgColor;
  bool openState = false;
  bool disableButtons = false;
  int selectIndex = -1;
  int numItems = 0;
  char itemBuffer[16]{};
  const char *itemName = "item";
  const char *title = "sample title";

  std::function<void(int)> &OnSignal(ArrayNodeSignal sig) {
    return onSignal[int(sig) - 1];
  }
};

struct GroupNode {
  std::function<void()> onOpen{};
  ImVec4 bgColor;
  bool openState = false;
  const char *title = "sample title";
};

void Draw(GroupNode &self);
void Draw(ArrayNode &self);

extern ImFont *HEADING_FONT24;
extern ImFont *HEADING_FONT18;

struct FolderTree {
  std::filesystem::path fullPath;
  std::string folderName;
  std::vector<std::unique_ptr<FolderTree>> children{};
  std::set<std::string> extensions;
  bool scanned = false;
  bool isFolder = true;
};

void ScanTree(FolderTree &tree);
void DrawFolderTree(FolderTree &tree, uint32_t level, uint32_t index,
                    std::filesystem::path &selectedPath);

namespace ImGui {
bool DragScalarBg(const char *label, ImGuiDataType data_type, void *p_data,
                  ImU32 bgColor, float v_speed = 1.f,
                  const void *p_min = nullptr, const void *p_max = nullptr,
                  const char *format = nullptr, ImGuiSliderFlags flags = 0);
bool DragScalarBgN(const char *label, ImGuiDataType data_type, void *p_data,
                   int components, const ImU32 *bgColors, const char **labels,
                   float v_speed = 1.f, const void *p_min = nullptr,
                   const void *p_max = nullptr, const char *format = nullptr,
                   ImGuiSliderFlags flags = 0);
} // namespace ImGui
