#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#endif

#include "font_awesome4/definitions.h"
#include "imgui_internal.h"
#include "widgets.hpp"

ImFont *HEADING_FONT24 = nullptr;
ImFont *HEADING_FONT18 = nullptr;

void Draw(ArrayNode &self) {
  ImGui::PushStyleColor(ImGuiCol_ChildBg, self.bgColor);
  if (ImGui::BeginChild("ChildWindow", {}, ImGuiChildFlags_AutoResizeY)) {
    ImGui::PushFont(HEADING_FONT24);
    ImGui::SetNextItemOpen(self.openState);
    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 10);
    self.openState = ImGui::TreeNodeEx(self.title);
    ImGui::PopFont();

    const float indentValue = !self.openState * 10 + 40;
    ImGui::Indent(indentValue);

    ImVec4 stColor = ImGui::GetStyleColorVec4(ImGuiCol_FrameBg);
    stColor.w = 0.94f;
    ImGui::PushStyleColor(ImGuiCol_FrameBg, stColor);
    stColor = ImGui::GetStyleColorVec4(ImGuiCol_FrameBgHovered);
    stColor.w = 0.94f;
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, stColor);

    ImGui::ListBox(
        "##items", &self.selectIndex,
        [](void *userData, int index) -> const char * {
          struct ArrayNode *data = static_cast<struct ArrayNode *>(userData);
          snprintf(data->itemBuffer, sizeof(ArrayNode::itemBuffer), "%d: %s",
                   index, data->itemName);
          return data->itemBuffer;
        },
        &self, self.numItems, 5);

    ImGui::PushStyleVarX(ImGuiStyleVar_ItemSpacing, 2);
    ImGui::PushStyleVarX(ImGuiStyleVar_FramePadding, 2);
    static const ImVec2 BUTTON_SIZE{18, 18};

    ImGui::SameLine();
    ImGui::BeginDisabled(self.selectIndex < 1);
    ImGui::BeginGroup();
    if (ImGui::Button(ICON_FA_CHEVRON_UP, BUTTON_SIZE)) {
      self.OnSignal(ArrayNodeSignal::MoveUp)(self.selectIndex);
    }
    if (ImGui::BeginItemTooltip()) {
      ImGui::Text("Move selected item up");
      ImGui::EndTooltip();
    }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(self.disableButtons);

    if (ImGui::Button(ICON_FA_PLUS, BUTTON_SIZE)) {
      self.OnSignal(ArrayNodeSignal::Add)(self.selectIndex);
    }
    if (ImGui::BeginItemTooltip()) {
      ImGui::Text("Append new item");
      ImGui::EndTooltip();
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_REPLY, BUTTON_SIZE)) {
      self.OnSignal(ArrayNodeSignal::Insert)(self.selectIndex);
    }
    if (ImGui::BeginItemTooltip()) {
      ImGui::Text("Insert new item after currently selected");
      ImGui::EndTooltip();
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_REPLY_ALL, BUTTON_SIZE)) {
      self.OnSignal(ArrayNodeSignal::Duplicate)(self.selectIndex);
    }
    if (ImGui::BeginItemTooltip()) {
      ImGui::Text("Duplicate selected item");
      ImGui::EndTooltip();
    }
    if (ImGui::Button(ICON_FA_TIMES, BUTTON_SIZE)) {
      self.OnSignal(ArrayNodeSignal::Remove)(self.selectIndex);
    }
    if (ImGui::BeginItemTooltip()) {
      ImGui::Text("Remove selected item");
      ImGui::EndTooltip();
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_TRASH, BUTTON_SIZE)) {
      self.OnSignal(ArrayNodeSignal::Clean)(self.selectIndex);
    }
    if (ImGui::BeginItemTooltip()) {
      ImGui::Text("Remove all items");
      ImGui::EndTooltip();
    }

    ImGui::EndDisabled();

    ImGui::BeginDisabled(self.selectIndex < 0 ||
                         self.selectIndex == self.numItems - 1);
    if (ImGui::Button(ICON_FA_CHEVRON_DOWN, BUTTON_SIZE)) {
      self.OnSignal(ArrayNodeSignal::MoveDown)(self.selectIndex);
    }
    if (ImGui::BeginItemTooltip()) {
      ImGui::Text("Move selected item down");
      ImGui::EndTooltip();
    }
    ImGui::EndDisabled();
    ImGui::EndGroup();

    ImGui::PopStyleVar(2);

    ImGui::Indent(-indentValue);
    ImGui::PopStyleColor(2);

    if (self.openState) {
      ImGui::PushStyleColor(ImGuiCol_ChildBg,
                            ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));
      if (ImGui::BeginChild("ChildWindow2", {}, ImGuiChildFlags_AutoResizeY,
                            ImGuiWindowFlags_AlwaysUseWindowPadding)) {
        self.OnSignal(ArrayNodeSignal::Open)(self.selectIndex);
      }
      ImGui::EndChild();

      ImGui::PopStyleColor();
      ImGui::TreePop();
    }

    ImGui::PopStyleVar();
  }
  ImGui::PopStyleColor();
  ImGui::EndChild();
}

void Draw(GroupNode &self) {
  ImGui::PushStyleColor(ImGuiCol_ChildBg, self.bgColor);
  if (ImGui::BeginChild("ChildWindow", {}, ImGuiChildFlags_AutoResizeY)) {
    ImGui::PushFont(HEADING_FONT24);
    ImGui::SetNextItemOpen(self.openState);
    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 10);
    self.openState = ImGui::TreeNodeEx(self.title);
    ImGui::PopFont();

    if (self.openState) {
      ImGui::PushStyleColor(ImGuiCol_ChildBg,
                            ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));
      if (ImGui::BeginChild("ChildWindow2", {}, ImGuiChildFlags_AutoResizeY,
                            ImGuiWindowFlags_AlwaysUseWindowPadding)) {
        self.onOpen();
      }
      ImGui::EndChild();

      ImGui::PopStyleColor();
      ImGui::TreePop();
    }

    ImGui::PopStyleVar();
  }
  ImGui::PopStyleColor();
  ImGui::EndChild();
}

namespace ImGui {
static const float DRAG_MOUSE_THRESHOLD_FACTOR =
    0.50f; // Multiplier for the default value of io.MouseDragThreshold to make
           // DragFloat/DragInt react faster to mouse drags.
bool DragScalarBg(const char *label, ImGuiDataType data_type, void *p_data,
                  ImU32 bgColor, float v_speed, const void *p_min,
                  const void *p_max, const char *format,
                  ImGuiSliderFlags flags) {
  ImGuiWindow *window = GetCurrentWindow();
  if (window->SkipItems)
    return false;

  ImGuiContext &g = *GImGui;
  const ImGuiStyle &style = g.Style;
  const ImGuiID id = window->GetID(label);
  const float w = CalcItemWidth();
  PushFont(HEADING_FONT18);
  const ImVec2 label_size = CalcTextSize(label, NULL, true);
  PopFont();
  const ImRect frame_bb(
      window->DC.CursorPos,
      window->DC.CursorPos +
          ImVec2(w, label_size.y + style.FramePadding.y * 2.0f));
  const ImRect total_bb(frame_bb.Min,
                        frame_bb.Max +
                            ImVec2(label_size.x > 0.0f
                                       ? style.ItemInnerSpacing.x + label_size.x
                                       : 0.0f,
                                   0.0f));

  const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
  ItemSize(frame_bb, style.FramePadding.y);
  if (!ItemAdd(frame_bb, id, &frame_bb,
               temp_input_allowed ? ImGuiItemFlags_Inputable : 0))
    return false;

  // Default format string when passing NULL
  if (format == NULL)
    format = DataTypeGetInfo(data_type)->PrintFmt;

  ImRect frame_bb2 = frame_bb;
  frame_bb2.Min += ImVec2(2 + label_size.x + style.ItemInnerSpacing.x, 2);
  frame_bb2.Max -= ImVec2(2, 2);

  const bool hovered = ItemHoverable(frame_bb2, id, g.LastItemData.InFlags);
  bool temp_input_is_active = temp_input_allowed && TempInputIsActive(id);
  if (!temp_input_is_active) {
    // Tabbing or CTRL-clicking on Drag turns it into an InputText
    const bool clicked = hovered && IsMouseClicked(0, ImGuiInputFlags_None, id);
    const bool double_clicked = (hovered && g.IO.MouseClickedCount[0] == 2 &&
                                 TestKeyOwner(ImGuiKey_MouseLeft, id));
    const bool make_active =
        (clicked || double_clicked || g.NavActivateId == id);
    if (make_active && (clicked || double_clicked))
      SetKeyOwner(ImGuiKey_MouseLeft, id);
    if (make_active && temp_input_allowed)
      if ((clicked && g.IO.KeyCtrl) || double_clicked ||
          (g.NavActivateId == id &&
           (g.NavActivateFlags & ImGuiActivateFlags_PreferInput)))
        temp_input_is_active = true;

    // (Optional) simple click (without moving) turns Drag into an InputText
    if (g.IO.ConfigDragClickToInputText && temp_input_allowed &&
        !temp_input_is_active)
      if (g.ActiveId == id && hovered && g.IO.MouseReleased[0] &&
          !IsMouseDragPastThreshold(0, g.IO.MouseDragThreshold *
                                           DRAG_MOUSE_THRESHOLD_FACTOR)) {
        g.NavActivateId = id;
        g.NavActivateFlags = ImGuiActivateFlags_PreferInput;
        temp_input_is_active = true;
      }

    if (make_active && !temp_input_is_active) {
      SetActiveID(id, window);
      SetFocusID(id, window);
      FocusWindow(window);
      g.ActiveIdUsingNavDirMask = (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
    }
  }

  // Draw frame base
  RenderFrame(frame_bb.Min, frame_bb.Max, bgColor, true, style.FrameRounding);
  PushFont(HEADING_FONT18);
  RenderText(ImVec2(frame_bb.Min.x + style.ItemInnerSpacing.x,
                    frame_bb.Min.y + style.FramePadding.y),
             label);
  PopFont();

  if (temp_input_is_active) {
    // Only clamp CTRL+Click input when ImGuiSliderFlags_AlwaysClamp is set
    const bool is_clamp_input = (flags & ImGuiSliderFlags_AlwaysClamp) != 0 &&
                                (p_min == NULL || p_max == NULL ||
                                 DataTypeCompare(data_type, p_min, p_max) < 0);
    return TempInputScalar(frame_bb2, id, label, data_type, p_data, format,
                           is_clamp_input ? p_min : NULL,
                           is_clamp_input ? p_max : NULL);
  }

  // Draw frame base
  const ImU32 frame_col = GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive
                                      : hovered        ? ImGuiCol_FrameBgHovered
                                                       : ImGuiCol_FrameBg);
  RenderNavHighlight(frame_bb2, id);
  RenderFrame(frame_bb2.Min, frame_bb2.Max, frame_col | 0xff000000, true,
              style.FrameRounding);

  // Drag behavior
  const bool value_changed =
      DragBehavior(id, data_type, p_data, v_speed, p_min, p_max, format, flags);
  if (value_changed)
    MarkItemEdited(id);

  // Display value using user-provided display format so user can add
  // prefix/suffix/decorations to the value.
  char value_buf[64];
  const char *value_buf_end =
      value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf),
                                       data_type, p_data, format);
  if (g.LogEnabled)
    LogSetNextTextDecoration("{", "}");
  RenderTextClipped(frame_bb2.Min, frame_bb2.Max, value_buf, value_buf_end,
                    NULL, ImVec2(0.5f, 0.5f));

  IMGUI_TEST_ENGINE_ITEM_INFO(
      id, label,
      g.LastItemData.StatusFlags |
          (temp_input_allowed ? ImGuiItemStatusFlags_Inputable : 0));
  return value_changed;
}

bool DragScalarBgN(const char *label, ImGuiDataType data_type, void *p_data,
                   int components, const ImU32 *bgColors, const char **labels,
                   float v_speed, const void *p_min, const void *p_max,
                   const char *format, ImGuiSliderFlags flags) {
  ImGuiWindow *window = GetCurrentWindow();
  if (window->SkipItems)
    return false;

  ImGuiContext &g = *GImGui;
  bool value_changed = false;
  BeginGroup();
  PushID(label);
  PushMultiItemsWidths(components, CalcItemWidth());

  static const uint8_t GDataTypeSize[] = {
      sizeof(char),           sizeof(unsigned char), sizeof(short),
      sizeof(unsigned short), sizeof(int),           sizeof(unsigned int),
      sizeof(ImS64),          sizeof(ImU64),         sizeof(float),
      sizeof(double),         sizeof(bool),
  };

  uint8_t type_size = GDataTypeSize[data_type];
  for (int i = 0; i < components; i++) {
    if (i > 0)
      SameLine(0, g.Style.ItemInnerSpacing.x);
    value_changed |= DragScalarBg(labels[i], data_type, p_data, bgColors[i],
                                  v_speed, p_min, p_max, format, flags);
    PopItemWidth();
    p_data = (void *)((char *)p_data + type_size);
  }
  PopID();

  const char *label_end = FindRenderedTextEnd(label);
  if (label != label_end) {
    SameLine(0, g.Style.ItemInnerSpacing.x);
    TextEx(label, label_end);
  }

  EndGroup();
  return value_changed;
}
} // namespace ImGui

void ScanTree(FolderTree &tree) {
  namespace fs = std::filesystem;
  fs::directory_iterator dirIt(tree.fullPath);
  tree.scanned = true;

  for (auto &entry : dirIt) {
    if (!entry.is_directory() &&
        !tree.extensions.contains(entry.path().extension())) {
      continue;
    }
    tree.children.emplace_back(std::make_unique<FolderTree>(FolderTree{
        .fullPath = entry,
        .folderName = entry.path().filename(),
        .isFolder = entry.is_directory(),
    }));
  }
}

void DrawFolderTree(FolderTree &tree, uint32_t level, uint32_t index,
                    std::filesystem::path &selectedPath) {
  uint64_t ptrId = index | (uint64_t(level) >> 32);
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
    uint32_t childIndex = 0;

    for (auto &f : tree.children) {
      DrawFolderTree(*f, level + 1, childIndex++, selectedPath);
    }

    ImGui::TreePop();
  } else if (tree.scanned) {
    tree.scanned = false;
    tree.children.clear();
  }
}
