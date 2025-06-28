#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <algorithm>
#include <deque>
#include <filesystem>
#include <fstream>
#include <variant>

#include "ImGuiFileDialog.h"
#include "font_awesome4/definitions.h"
#include "imgui.h"
#include "imgui_internal.h"

#include "spike/crypto/jenkinshash.hpp"
#include "spike/reflect/detail/reflector_class.hpp"
#include "spike/reflect/reflector_fwd.hpp"
#include "widgets.hpp"
#include "window.hpp"

#include "spike/master_printer.hpp"
#include "spike/reflect/reflector.hpp"
#include "spike/util/supercore.hpp"

#include "script.hpp"
#include "script/core.hpp"

std::vector<std::string> output;
std::filesystem::path ROOT_DIR;

template <class Ty> struct DTPod {
  Ty *data;
  std::string name;
};

std::string CamelCaseToSpaceCase(std::string_view data) {
  std::string retVal;
  bool lastUpperCase = false;

  for (auto i : data) {
    if (retVal.empty()) {
      retVal.push_back(std::toupper(i));
      continue;
    }

    if ((std::isupper(i) || std::isdigit(i)) && !lastUpperCase) {
      retVal.push_back(' ');
      retVal.push_back(std::tolower(i));
      lastUpperCase = true;
    } else {
      lastUpperCase = false;
      retVal.push_back(std::tolower(i));
    }
  }

  return retVal;
}

void SwitchEditResource(ResourceRef *res);

bool InputTextStd(const char *label, std::string &str) {
  return ImGui::InputText(
      label, str.data(), str.size(), ImGuiInputTextFlags_CallbackResize,
      [](ImGuiInputTextCallbackData *data) -> int {
        std::string *userData = static_cast<std::string *>(data->UserData);
        if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
          IM_ASSERT(data->Buf == userData->c_str());
          userData->resize(data->BufTextLen);
          data->Buf = (char *)userData->c_str();
        }

        return 0;
      },
      &str);
}

void Draw(DTPod<bool> &dtype) {
  if (dtype.name.size() > 0) {
    ImGui::Text("%s", dtype.name.c_str());
    ImGui::TableSetColumnIndex(1);
  }
  ImGui::PushID(dtype.name.c_str());
  ImGui::Checkbox("##editbox", dtype.data);
  ImGui::PopID();
}

struct DTScalar {
  void *data;
  std::string name;
  ImGuiDataType type;
};

void Draw(DTScalar &dtype) {
  if (dtype.name.size() > 0) {
    ImGui::Text("%s", dtype.name.c_str());
    ImGui::TableSetColumnIndex(1);
  }
  ImGui::PushID(dtype.name.c_str());
  ImGui::DragScalar("##editbox", dtype.type, dtype.data);
  ImGui::PopID();
}

void Draw(DTPod<Vector> &dtype) {
  if (dtype.name.size() > 0) {
    ImGui::Text("%s", dtype.name.c_str());
    ImGui::TableSetColumnIndex(1);
  }
  ImGui::PushID(dtype.name.c_str());
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);
  static const char *axes[3]{"X", "Y", "Z"};
  static const ImU32 colors[3]{0xff00007f, 0xff007f00, 0xff7f0000};
  ImGui::DragScalarBgN("##sample", ImGuiDataType_Float, dtype.data, 3, colors,
                       axes);
  ImGui::PopStyleVar();
  ImGui::PopID();
}

void Draw(DTPod<Angle> &dtype) {
  if (dtype.name.size() > 0) {
    ImGui::Text("%s", dtype.name.c_str());
    ImGui::TableSetColumnIndex(1);
  }
  ImGui::PushID(dtype.name.c_str());
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);
  static const char *axes[3]{"Yaw", "Pitch", "Roll"};
  static const ImU32 colors[3]{0xff007f00, 0xff7f0000, 0xff00007f};
  ImGui::DragScalarBgN("##sample", ImGuiDataType_Float, dtype.data, 3, colors,
                       axes);
  ImGui::PopStyleVar();
  ImGui::PopID();
}

void Draw(DTPod<std::string> &dtype) {
  if (dtype.name.size() > 0) {
    ImGui::Text("%s", dtype.name.c_str());
    ImGui::TableSetColumnIndex(1);
  }
  ImGui::PushID(dtype.name.c_str());
  InputTextStd("##editbox", *dtype.data);
  ImGui::PopID();
}

struct DTFilePath : DTPod<std::string> {
  FilePathType type;
};

void Draw(DTFilePath &dtype) {
  if (dtype.name.size() > 0) {
    ImGui::Text("%s", dtype.name.c_str());
    ImGui::TableSetColumnIndex(1);
  }
  ImGui::PushID(dtype.name.c_str());
  if (ImGui::Button(ICON_FA_FOLDER_OPEN)) {
    IGFD::FileDialogConfig cfg{};
    cfg.filePathName = std::string(ROOT_DIR) + *dtype.data;
    static const char *filters[]{
        ".txt", ".resources", ".dds,.tga,.jpg", ".sbm",
        ".sba", ".avi",       ".ogg,.wav",      "",
    };
    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File",
                                            filters[uint32(dtype.type)], cfg);
  }

  if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey",
                                           ImGuiWindowFlags_NoCollapse)) {
    if (ImGuiFileDialog::Instance()->IsOk()) {
      dtype.name = ImGuiFileDialog::Instance()->GetFilePathName();
    }
    ImGuiFileDialog::Instance()->Close();
  }
  ImGui::SameLine();
  InputTextStd("##editbox", *dtype.data);
  ImGui::PopID();
}

struct DTPodVectorBase : DTPod<char> {
  const VectorMethods *vecm;
  int numItems = 0;
  int selectedItem = 0;
  bool isTable = false;
};

void Draw(DTPodVectorBase &dtype,
          void (*perItem)(DTPodVectorBase &self, int index)) {
  if (dtype.name.size() > 0) {
    ImGui::Text("%s", dtype.name.c_str());
    ImGui::TableSetColumnIndex(1);
  }
  ImGui::PushID(dtype.name.c_str());
  const size_t numItems =
      dtype.vecm ? dtype.vecm->size(dtype.data) : dtype.numItems;

  if (dtype.isTable) {
    if (ImGui::BeginTable("items table", 2,
                          ImGuiTableFlags_NoSavedSettings |
                              ImGuiTableFlags_ScrollY | ImGuiTableFlags_Borders,
                          ImVec2{-100, 125})) {
      for (size_t i = 0; i < numItems; i++) {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        perItem(dtype, i);
      }

      ImGui::EndTable();
    }
  } else {
    if (ImGui::BeginListBox("##items", {-100, 0})) {
      ImGuiListClipper clipper;
      clipper.Begin(numItems, ImGui::GetTextLineHeightWithSpacing());
      clipper.IncludeItemByIndex(dtype.selectedItem);
      while (clipper.Step())
        for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
          perItem(dtype, i);
          if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
            dtype.selectedItem = i;
          }
        }

      ImGui::EndListBox();
    }
  }

  static const ImVec2 BUTTON_SIZE{18, 18};

  ImGui::SameLine();
  ImGui::BeginGroup();
  ImGui::BeginDisabled(numItems < 2 || dtype.selectedItem < 1);
  if (ImGui::Button(ICON_FA_CHEVRON_UP, BUTTON_SIZE)) {
    dtype.vecm->signal(dtype.data, VectorMethods::Swap, dtype.selectedItem,
                       dtype.selectedItem - 1);
    dtype.selectedItem--;
  }
  if (ImGui::BeginItemTooltip()) {
    ImGui::Text("Move selected item up");
    ImGui::EndTooltip();
  }
  ImGui::EndDisabled();

  ImGui::BeginDisabled(!dtype.vecm);
  if (ImGui::Button(ICON_FA_PLUS, BUTTON_SIZE)) {
    dtype.selectedItem = dtype.vecm->size(dtype.data);
    dtype.vecm->signal(dtype.data, VectorMethods::Resize,
                       dtype.selectedItem + 1, 0);
  }
  if (ImGui::BeginItemTooltip()) {
    ImGui::Text("Append new item");
    ImGui::EndTooltip();
  }
  ImGui::EndDisabled();
  ImGui::SameLine();
  ImGui::BeginDisabled(!dtype.vecm || numItems < 1 || dtype.selectedItem < 0);
  if (ImGui::Button(ICON_FA_REPLY, BUTTON_SIZE)) {
    dtype.vecm->signal(dtype.data, VectorMethods::InsertNew, dtype.selectedItem,
                       1);
    dtype.selectedItem++;
  }
  if (ImGui::BeginItemTooltip()) {
    ImGui::Text("Insert new item after currently selected");
    ImGui::EndTooltip();
  }
  ImGui::SameLine();
  if (ImGui::Button(ICON_FA_REPLY_ALL, BUTTON_SIZE)) {
    dtype.vecm->signal(dtype.data, VectorMethods::DuplicateInsert,
                       dtype.selectedItem, 1);
    dtype.selectedItem++;
  }
  if (ImGui::BeginItemTooltip()) {
    ImGui::Text("Duplicate selected item");
    ImGui::EndTooltip();
  }
  if (ImGui::Button(ICON_FA_TIMES, BUTTON_SIZE)) {
    dtype.vecm->signal(dtype.data, VectorMethods::Erase, dtype.selectedItem,
                       dtype.selectedItem + 1);
    dtype.selectedItem =
        std::min(dtype.selectedItem, int(dtype.vecm->size(dtype.data)) - 1);
  }
  if (ImGui::BeginItemTooltip()) {
    ImGui::Text("Remove selected item");
    ImGui::EndTooltip();
  }
  ImGui::EndDisabled();
  ImGui::SameLine();
  ImGui::BeginDisabled(!dtype.vecm || numItems < 1);
  if (ImGui::Button(ICON_FA_TRASH, BUTTON_SIZE)) {
    dtype.selectedItem = 0;
    dtype.vecm->signal(dtype.data, VectorMethods::Resize, dtype.selectedItem,
                       0);
  }
  if (ImGui::BeginItemTooltip()) {
    ImGui::Text("Remove all items");
    ImGui::EndTooltip();
  }
  ImGui::EndDisabled();
  ImGui::BeginDisabled(numItems < 2 || dtype.selectedItem < 0 ||
                       dtype.selectedItem == int(numItems - 1));
  if (ImGui::Button(ICON_FA_CHEVRON_DOWN, BUTTON_SIZE)) {
    dtype.vecm->signal(dtype.data, VectorMethods::Swap, dtype.selectedItem,
                       dtype.selectedItem + 1);
    dtype.selectedItem++;
  }
  if (ImGui::BeginItemTooltip()) {
    ImGui::Text("Move selected item down");
    ImGui::EndTooltip();
  }
  ImGui::EndDisabled();
  ImGui::EndGroup();
  ImGui::PopID();
}

ResourceRef *REF_TO_FILL = nullptr;
void PickClass();

void Draw(DTPod<ResourceRef> &dtype) {
  if (dtype.name.size() > 0) {
    ImGui::Text("%s", dtype.name.c_str());
    ImGui::TableSetColumnIndex(1);
  }
  ImGui::PushID(dtype.name.c_str());
  if (ImGui::Button(ICON_FA_EXTERNAL_LINK)) {
    SwitchEditResource(dtype.data);
  }
  ImGui::SameLine();
  if (ImGui::Button(ICON_FA_FOLDER_OPEN)) {
    ImGui::OpenPopup("Pick resource");
    REF_TO_FILL = dtype.data;
  }
  ImGui::SameLine();
  ImGui::BeginDisabled();
  InputTextStd("##editbox", dtype.data->asString);
  ImGui::EndDisabled();
  PickClass();
  ImGui::PopID();
}

struct DTColor {
  Color *data;
  std::string name;
  ImVec4 repr;

  static ImVec4 ColorConvertU32ToFloat4(ImU32 in) {
    float s = 1.0f / 255.0f;
    return ImVec4(((in >> IM_COL32_B_SHIFT) & 0xFF) * s,
                  ((in >> IM_COL32_G_SHIFT) & 0xFF) * s,
                  ((in >> IM_COL32_R_SHIFT) & 0xFF) * s,
                  ((in >> IM_COL32_A_SHIFT) & 0xFF) * s);
  }

  static ImU32 ColorConvertFloat4ToU32(const ImVec4 &in) {
    ImU32 out;
    out = ((ImU32)IM_F32_TO_INT8_SAT(in.x)) << IM_COL32_B_SHIFT;
    out |= ((ImU32)IM_F32_TO_INT8_SAT(in.y)) << IM_COL32_G_SHIFT;
    out |= ((ImU32)IM_F32_TO_INT8_SAT(in.z)) << IM_COL32_R_SHIFT;
    out |= ((ImU32)IM_F32_TO_INT8_SAT(in.w)) << IM_COL32_A_SHIFT;
    return out;
  }

  DTColor(Color *data_, const std::string &name_)
      : data(data_), name(name_), repr(ColorConvertU32ToFloat4(data->raw)) {}
};

void Draw(DTColor &dtype) {
  if (dtype.name.size() > 0) {
    ImGui::Text("%s", dtype.name.c_str());
    ImGui::TableSetColumnIndex(1);
  }
  ImGui::PushID(dtype.name.c_str());
  if (ImGui::ColorPicker4("##coloredit", &dtype.repr.x,
                          ImGuiColorEditFlags_PickerHueWheel)) {
    dtype.data->raw = DTColor::ColorConvertFloat4ToU32(dtype.repr);
  }
  ImGui::PopID();
}

struct GroupNodeStr : GroupNode {
  std::unique_ptr<std::string> titleName;
};

struct DTEnum {
  void *data;
  int selected = 0;
  std::string name;
  const ReflectedEnum *refl;
};

void Draw(DTEnum &dtype) {
  if (dtype.name.size() > 0) {
    ImGui::Text("%s", dtype.name.c_str());
    ImGui::TableSetColumnIndex(1);
  }
  ImGui::PushID(dtype.name.c_str());
  if (ImGui::Combo("##combo", &dtype.selected, dtype.refl->names,
                   dtype.refl->numMembers)) {
    memcpy(dtype.data, &dtype.refl->values[dtype.selected], dtype.refl->size);
  }
  ImGui::PopID();
}

using DTVectorValue =
    std::variant<DTPod<bool>, DTScalar, DTPod<Vector>, DTPod<Angle>,
                 DTPod<std::string>, DTPod<ResourceRef>, DTEnum, DTColor,
                 DTFilePath>;

struct DTVector : DTPodVectorBase {
  DTVectorValue valueTemplate;
  int stride = 0;
  std::string name;
};

void Draw(DTVector &dtype) {
  Draw(dtype, [](DTPodVectorBase &dtype_, int index) {
    DTVector &dtype = static_cast<DTVector &>(dtype_);
    char *kvData =
        static_cast<char *>(dtype.vecm ? dtype.vecm->at(dtype.data, index)
                                       : (dtype.data + dtype.stride * index));

    ImGui::PushID(index);
    ImGui::SetNextItemWidth(-1);
    std::visit(
        [kvData](auto item) {
          item.data = reinterpret_cast<decltype(item.data)>(kvData);
          Draw(item);
        },
        dtype.valueTemplate);
    ImGui::PopID();
  });
}

using DTMapKey = std::variant<DTScalar, DTPod<std::string>, DTEnum>;
using DTMapValue =
    std::variant<DTPod<bool>, DTScalar, DTPod<Vector>, DTPod<Angle>,
                 DTPod<std::string>, DTVector, DTPod<ResourceRef>, DTEnum,
                 DTColor, DTFilePath>;

struct DTMapVector : DTPodVectorBase {
  DTMapKey keyTemplate;
  DTMapValue valueTemplate;
  uint32 valueOffset;
  std::string name;
};

void Draw(DTMapVector &dtype) {
  Draw(dtype, [](DTPodVectorBase &dtype_, int index) {
    DTMapVector &dtype = static_cast<DTMapVector &>(dtype_);
    char *kvData = static_cast<char *>(dtype.vecm->at(dtype.data, index));

    ImGui::PushID(index);
    ImGui::PushID("key");
    ImGui::SetNextItemWidth(-1);
    std::visit(
        [kvData](auto item) {
          item.data = reinterpret_cast<decltype(item.data)>(kvData);
          Draw(item);
        },
        dtype.keyTemplate);
    ImGui::PopID();
    ImGui::TableSetColumnIndex(1);
    // ImGui::SameLine(0, 0);
    // ImGui::Text(":");
    // ImGui::SameLine(0, 0);
    ImGui::PushID("value");
    ImGui::SetNextItemWidth(-1);
    std::visit(
        [kvData = kvData + dtype.valueOffset](auto item) {
          item.data = reinterpret_cast<decltype(item.data)>(kvData);
          Draw(item);
        },
        dtype.valueTemplate);
    ImGui::PopID();
    ImGui::PopID();
  });
}

using DTVariant =
    std::variant<DTPod<bool>, DTScalar, DTPod<Vector>, DTPod<Angle>,
                 DTPod<std::string>, DTPod<ResourceRef>, DTEnum, DTColor,
                 DTMapVector, DTVector, DTFilePath>;

void Draw(std::vector<DTVariant> &dtype) {
  if (ImGui::BeginTable("editor table", 2,
                        ImGuiTableFlags_NoSavedSettings |
                            ImGuiTableFlags_SizingFixedFit)) {
    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch);
    for (auto &t : dtype) {
      ImGui::TableNextRow();
      ImGui::TableSetColumnIndex(0);
      ImGui::PushID(&t);
      std::visit([](auto &t) { Draw(t); }, t);
      ImGui::PopID();
    }
    ImGui::EndTable();
  }
}

using GroupVariant =
    std::variant<ArrayNode, GroupNodeStr, std::vector<DTVariant>>;

ImVec4 ColorFromHash(JenHash hash) {
  ImVec4 bgColor = ImGui::ColorConvertU32ToFloat4(hash.raw() | 0xff000000);

  if ((bgColor.x + bgColor.y + bgColor.z) / 3 > 0.5) {
    bgColor = ImGui::ColorConvertU32ToFloat4(~hash.raw() | 0xff000000);
  }

  return bgColor;
}

void BuildPrimitive(std::vector<DTVariant> &fields, const reflectorStatic *refl,
                    char *instance, uint32 i) {
  ReflType type = refl->types[i];
  if (type.container == REFContainer::InlineArray) {
    type.size = type.asArray.stride;
  }

  switch (type.type) {
  case REFType::Integer: {
    ImGuiDataType dt;
    switch (type.size) {
    case 1:
      dt = ImGuiDataType_S8;
      break;

    case 2:
      dt = ImGuiDataType_S16;
      break;

    case 4:
      dt = ImGuiDataType_S32;
      break;

    case 8:
      dt = ImGuiDataType_S64;
      break;
    }

    fields.emplace_back(DTScalar{instance + type.offset,
                                 CamelCaseToSpaceCase(refl->typeNames[i]), dt});
    break;
  }

  case REFType::FloatingPoint: {
    ImGuiDataType dt;
    switch (type.size) {
    case 4:
      dt = ImGuiDataType_Float;
      break;

    case 8:
      dt = ImGuiDataType_Double;
      break;
    }

    fields.emplace_back(DTScalar{instance + type.offset,
                                 CamelCaseToSpaceCase(refl->typeNames[i]), dt});
    break;
  }
  case REFType::UnsignedInteger: {
    ImGuiDataType dt;
    switch (type.size) {
    case 1:
      dt = ImGuiDataType_U8;
      break;

    case 2:
      dt = ImGuiDataType_U16;
      break;

    case 4:
      dt = ImGuiDataType_U32;
      break;

    case 8:
      dt = ImGuiDataType_U64;
      break;
    }

    fields.emplace_back(DTScalar{instance + type.offset,
                                 CamelCaseToSpaceCase(refl->typeNames[i]), dt});
    break;
  }
  case REFType::Bool:
    fields.emplace_back(
        DTPod<bool>{reinterpret_cast<bool *>(instance + type.offset),
                    CamelCaseToSpaceCase(refl->typeNames[i])});
    break;
  case REFType::Vector:
    if (type.asVector.numItems == 3 && type.asVector.stride == 4) {
      fields.emplace_back(
          DTPod<Vector>{reinterpret_cast<Vector *>(instance + type.offset),
                        CamelCaseToSpaceCase(refl->typeNames[i])});
    } else {
      printf("Unknown Vector type, implement.\n");
    }
    break;

  case REFType::Class:
    if (type.asClass.typeHash == GetReflectedClass<Angle>()->classHash) {
      fields.emplace_back(
          DTPod<Angle>{reinterpret_cast<Angle *>(instance + type.offset),
                       CamelCaseToSpaceCase(refl->typeNames[i])});
    } else if (type.asClass.typeHash ==
               GetReflectedClass<ResourceRef>()->classHash) {
      fields.emplace_back(DTPod<ResourceRef>{
          reinterpret_cast<ResourceRef *>(instance + type.offset),
          CamelCaseToSpaceCase(refl->typeNames[i])});
    } else if (type.asClass.typeHash == GetReflectedClass<Color>()->classHash) {
      fields.emplace_back(
          DTColor{reinterpret_cast<Color *>(instance + type.offset),
                  CamelCaseToSpaceCase(refl->typeNames[i])});
    }
    break;
  case REFType::String:
    if (type.asClass.typeHash == JenHash("FilePath")) {
      fields.emplace_back(DTFilePath{
          {
              reinterpret_cast<std::string *>(instance + type.offset),
              CamelCaseToSpaceCase(refl->typeNames[i]),
          },
          FilePathType(type.size)});
    } else if (type.valueNameHash != JenHash("__guid") &&
               type.valueNameHash != JenHash("package")) {
      fields.emplace_back(DTPod<std::string>{
          reinterpret_cast<std::string *>(instance + type.offset),
          CamelCaseToSpaceCase(refl->typeNames[i])});
    }
    break;

  case REFType::Enum: {
    uint64 selvalue = 0;
    memcpy(&selvalue, instance + type.offset, type.size);
    const ReflectedEnum *erefl =
        ReflectedEnum::Registry().at(type.asClass.typeHash);
    int32 selIndex = 0;

    for (; selIndex < int(erefl->numMembers); selIndex++) {
      if (erefl->values[selIndex] == selvalue) {
        break;
      }
    }

    fields.emplace_back(DTEnum{
        .data = instance + type.offset,
        .selected = selIndex,
        .name = CamelCaseToSpaceCase(refl->typeNames[i]),
        .refl = erefl,
    });
    break;
  }

  default:
    printf("Unknown type, implement.\n");
    break;
  }
}

void Build(std::vector<GroupVariant> &groups, const reflectorStatic *refl,
           char *instance) {
  if (refl->baseClass.raw()) {
    const reflectorStatic *base =
        reflectorStatic::Registry().at(refl->baseClass);
    Build(groups, base, instance);
  }

  auto Fields = [&groups]() -> auto & {
    if (groups.empty() ||
        !std::get_if<std::vector<DTVariant>>(&groups.back())) {
      groups.emplace_back(std::vector<DTVariant>{});
    }

    return std::get<std::vector<DTVariant>>(groups.back());
  };

  auto AppendToCurGroup = [&Fields](DTVariant var) {
    Fields().emplace_back(std::move(var));
  };

  for (uint32 i = 0; i < refl->nTypes; i++) {
    const ReflType &type = refl->types[i];

    if (type.container == REFContainer::ContainerVector ||
        type.container == REFContainer::InlineArray) {
      const bool isArray = type.container == REFContainer::InlineArray;
      const VectorMethods *vecm = isArray ? nullptr : &refl->vectorMethods[i];

      std::vector<DTVariant> temps;
      BuildPrimitive(temps, refl, nullptr, i);

      DTVectorValue valueTemplate;

      bool isValuePod =
          temps.size() &&
          std::visit(
              [&valueTemplate](auto &item) {
                using TypeName = std::decay_t<decltype(item)>;
                if constexpr (std::is_same_v<TypeName, DTPod<bool>> ||
                              std::is_same_v<TypeName, DTPod<std::string>> ||
                              std::is_same_v<TypeName, DTFilePath> ||
                              std::is_same_v<TypeName, DTScalar> ||
                              std::is_same_v<TypeName, DTPod<Vector>> ||
                              std::is_same_v<TypeName, DTPod<Angle>> ||
                              std::is_same_v<TypeName, DTPod<ResourceRef>> ||
                              std::is_same_v<TypeName, DTEnum> ||
                              std::is_same_v<TypeName, DTColor>) {
                  item.name.clear();
                  valueTemplate = item;
                  return true;
                }

                return false;
              },
              temps.front());

      if (isValuePod) {
        DTVector vector{
            {
                {instance + type.offset,
                 CamelCaseToSpaceCase(refl->typeNames[i])},
                vecm,
                type.asArray.numItems,
                0,
            },
            valueTemplate,
            type.asArray.stride,
            CamelCaseToSpaceCase(refl->typeNames[i]),
        };

        AppendToCurGroup(vector);
        continue;
      }

      if (type.type == REFType::Class) {
        int numItems =
            isArray ? type.asArray.numItems
                    : int(refl->vectorMethods[i].size(instance + type.offset));

        ArrayNode node{.bgColor = ColorFromHash(type.valueNameHash),
                       .openState = true,
                       .disableButtons = isArray,
                       .selectIndex = -1 + (numItems > 0),
                       .numItems = numItems,
                       .title = refl->typeNames[i]};

        std::shared_ptr<std::vector<std::vector<GroupVariant>>> subclassFields =
            std::make_shared<std::vector<std::vector<GroupVariant>>>();

        for (int f = 0; f < numItems; f++) {
          Build(subclassFields->emplace_back(),
                reflectorStatic::Registry().at(
                    isArray ? type.asArray.asClass.typeHash
                            : type.asClass.typeHash),
                isArray ? (instance + type.offset) + type.asArray.stride * f
                        : static_cast<char *>(refl->vectorMethods[i].at(
                              instance + type.offset, f)));
        }

        node.OnSignal(ArrayNodeSignal::Open) = [=](int index) {
          if (index < 0) {
            return; // TODO show disabled members
          }
          for (auto &i : subclassFields->at(index)) {
            ImGui::PushID(&i);
            std::visit([](auto &t) { Draw(t); }, i);
            ImGui::PopID();
          }
        };

        groups.emplace_back(node);
        continue;
      }
    } else if (type.container == REFContainer::ContainerVectorMap &&
               type.type == REFType::Class) {
      const reflectorStatic *kvRefl =
          reflectorStatic::Registry().at(type.asClass.typeHash);
      assert(kvRefl->types[1].valueNameHash == JenHash("value"));

      uint32 valueOffset = kvRefl->types[1].offset;

      std::vector<DTVariant> temps;
      BuildPrimitive(temps, kvRefl, nullptr, 0);
      DTMapKey keyTemplate;
      std::visit(
          [&keyTemplate](auto &item) {
            using TypeName = std::decay_t<decltype(item)>;
            if constexpr (std::is_same_v<TypeName, DTScalar> ||
                          std::is_same_v<TypeName, DTPod<std::string>> ||
                          std::is_same_v<TypeName, DTFilePath> ||
                          std::is_same_v<TypeName, DTEnum>) {
              item.name.clear();
              keyTemplate = item;
            }
          },
          temps.front());

      temps.clear();
      BuildPrimitive(temps, kvRefl, nullptr, 1);
      DTMapValue valueTemplate;

      bool isValuePod = std::visit(
          [&valueTemplate](auto &item) {
            using TypeName = std::decay_t<decltype(item)>;
            if constexpr (std::is_same_v<TypeName, DTPod<bool>> ||
                          std::is_same_v<TypeName, DTPod<std::string>> ||
                          std::is_same_v<TypeName, DTFilePath> ||
                          std::is_same_v<TypeName, DTScalar> ||
                          std::is_same_v<TypeName, DTPod<Vector>> ||
                          std::is_same_v<TypeName, DTPod<Angle>> ||
                          std::is_same_v<TypeName, DTPod<ResourceRef>> ||
                          std::is_same_v<TypeName, DTEnum> ||
                          std::is_same_v<TypeName, DTColor>) {
              item.name.clear();
              valueTemplate = item;
              return true;
            }

            return false;
          },
          temps.front());

      if (isValuePod) {
        DTMapVector mapVector{
            {
                {instance + type.offset,
                 CamelCaseToSpaceCase(refl->typeNames[i])},
                &refl->vectorMethods[i],
                0,
                0,
                true,
            },
            keyTemplate,
            valueTemplate,
            valueOffset,
            CamelCaseToSpaceCase(refl->typeNames[i]),
        };

        AppendToCurGroup(mapVector);
        continue;
      }

      // following code seems not to trigger
      assert(false);
      ArrayNode node{
          .bgColor = ColorFromHash(type.valueNameHash),
          .openState = true,
          .numItems = int(refl->vectorMethods[i].size(instance + type.offset)),
          .title = refl->typeNames[i]};

      node.OnSignal(ArrayNodeSignal::Open) = [=](int index) {
        if (index < 0) {
          return; // TODO show disabled members
        }
        /*for (auto &i : subclassFields->at(index)) {
          ImGui::PushID(&i);
          std::visit([](auto &t) { Draw(t); }, i);
          ImGui::PopID();
        }*/
      };

      groups.emplace_back(node);
      continue;
    }

    if (type.container != REFContainer::None) {
      printf("Unknown container type, implement.\n");
      continue;
    }

    switch (type.type) {
    case REFType::Class:
      if (type.asClass.typeHash == GetReflectedClass<Angle>()->classHash) {
      } else if (type.asClass.typeHash ==
                 GetReflectedClass<ResourceRef>()->classHash) {
      } else if (type.asClass.typeHash ==
                 GetReflectedClass<Color>()->classHash) {
      } else {
        std::shared_ptr<std::vector<GroupVariant>> vars =
            std::make_shared<std::vector<GroupVariant>>();
        std::unique_ptr<std::string> strPtr = std::make_unique<std::string>(
            CamelCaseToSpaceCase(refl->typeNames[i]));
        GroupNodeStr gnode{
            {
                [=] {
                  for (auto &i : *vars) {
                    ImGui::PushID(&i);
                    std::visit([](auto &t) { Draw(t); }, i);
                    ImGui::PopID();
                  }
                },
                ColorFromHash(type.valueNameHash),
                true,
                strPtr->c_str(),
            },
            std::move(strPtr),
        };

        groups.emplace_back(std::move(gnode));

        Build(*vars, reflectorStatic::Registry().at(type.asClass.typeHash),
              instance + type.offset);
        break;
      }
      [[fallthrough]];

    default:
      BuildPrimitive(Fields(), refl, instance, i);
      break;
    }
  }
}

struct EditResource {
  std::unique_ptr<Resource> resource;
  std::vector<GroupVariant> groups{};

  void Build() {
    const reflectorStatic *refl = resource->refl;
    char *instance = reinterpret_cast<char *>(resource.get());
    ::Build(groups, refl, instance);
  }
};

struct DataClass {
  std::vector<EditResource> resources;
  std::string name;
  bool active = false;
  bool opened = false;
  ImGuiTabItemFlags tabFlags = 0;
};

void LoadScript(std::istream &str,
                std::vector<std::unique_ptr<Resource>> &resources);

void LoadClasses(std::map<std::string, DataClass> &packs,
                 const std::string &path) {
  std::ifstream str(path);
  std::vector<std::unique_ptr<Resource>> resources;
  LoadScript(str, resources);

  for (auto &ref : resources) {
    EditResource res{.resource = std::move(ref)};
    res.Build();
    ReflectorPureWrap wrap({res.resource->refl, res.resource.get()});
    auto member = wrap["package"];

    if (member) {
      packs[member].resources.emplace_back(std::move(res));
    }
  }
}

struct ResourceHistory {
  EditResource *curEditResource;
  const Resource *clickedNodeId;
};

std::deque<ResourceHistory> RESOURCE_HISTORY;
int HISTORY_INDEX = -1;
EditResource *curEditResource = nullptr;
const Resource *clickedNodeId = nullptr;

void PushHistory() {
  HISTORY_INDEX++;
  RESOURCE_HISTORY.resize(HISTORY_INDEX);
  RESOURCE_HISTORY.push_back({curEditResource, clickedNodeId});
}

void GoBack() {
  HISTORY_INDEX = std::max(0, HISTORY_INDEX - 1);
  if (HISTORY_INDEX >= int(RESOURCE_HISTORY.size())) {
    return;
  }
  curEditResource = RESOURCE_HISTORY.at(HISTORY_INDEX).curEditResource;
  clickedNodeId = RESOURCE_HISTORY.at(HISTORY_INDEX).clickedNodeId;
}

void GoForward() {
  HISTORY_INDEX = std::min(int(RESOURCE_HISTORY.size()) - 1, HISTORY_INDEX + 1);
  if (HISTORY_INDEX < 0) {
    return;
  }
  curEditResource = RESOURCE_HISTORY.at(HISTORY_INDEX).curEditResource;
  clickedNodeId = RESOURCE_HISTORY.at(HISTORY_INDEX).clickedNodeId;
}

std::string workingDir;
std::map<std::string, std::map<std::string, DataClass>> collection;

void SwitchEditResource(ResourceRef *res) {
  for (auto &[_, dclass] : collection.at(workingDir)) {
    for (auto &r : dclass.resources) {
      if (res->asLink ? r.resource.get() == res->asLink
                      : r.resource->__guid == res->asString) {
        curEditResource = &r;
        clickedNodeId = r.resource.get();
        PushHistory();
        return;
      }
    }
  }

  for (auto &[_, dclass] : collection.at("globals")) {
    for (auto &r : dclass.resources) {
      if (res->asLink ? r.resource.get() == res->asLink
                      : r.resource->__guid == res->asString) {
        curEditResource = &r;
        clickedNodeId = r.resource.get();
        PushHistory();
        return;
      }
    }
  }
}

void PickClass() {
  static Resource *selectedResource = nullptr;

  if (ImGui::BeginPopupModal("Pick resource")) {
    static std::string filter;
    InputTextStd("Filter", filter);
    bool doubleClicked = false;

    if (ImGui::BeginListBox("##pickclass", {-1, -30})) {
      for (auto &[pack, dcls] : collection.at(workingDir)) {
        for (auto &r : dcls.resources) {
          auto found =
              std::search(r.resource->__guid.begin(), r.resource->__guid.end(),
                          filter.begin(), filter.end(), [](char c0, char c1) {
                            return std::tolower(c0) == std::tolower(c1);
                          });

          if (filter.empty() || found != r.resource->__guid.end()) {
            if (ImGui::Selectable(r.resource->__guid.c_str(),
                                  r.resource.get() == selectedResource)) {
              selectedResource = r.resource.get();
            }

            doubleClicked |=
                ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) &&
                ImGui::IsItemClicked(ImGuiMouseButton_Left);

            ImGui::SameLine();
            ImGui::TextDisabled("(%s)", r.resource->refl->className);
          }
        }
      }

      for (auto &[pack, dcls] : collection.at("globals")) {
        for (auto &r : dcls.resources) {
          auto found =
              std::search(r.resource->__guid.begin(), r.resource->__guid.end(),
                          filter.begin(), filter.end(), [](char c0, char c1) {
                            return std::tolower(c0) == std::tolower(c1);
                          });

          if (filter.empty() || found != r.resource->__guid.end()) {
            if (ImGui::Selectable(r.resource->__guid.c_str(),
                                  r.resource.get() == selectedResource)) {
              selectedResource = r.resource.get();
            }

            doubleClicked |=
                ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) &&
                ImGui::IsItemClicked(ImGuiMouseButton_Left);

            ImGui::SameLine();
            ImGui::TextDisabled("(%s)", r.resource->refl->className);
          }
        }
      }

      ImGui::EndListBox();
    }

    ImGui::Spacing();
    ImGui::BeginDisabled(!selectedResource);
    if (doubleClicked || ImGui::Button("DONE", {80, 0})) {
      REF_TO_FILL->asString = selectedResource->__guid;
      REF_TO_FILL->asLink = selectedResource;
      REF_TO_FILL = nullptr;
      selectedResource = nullptr;
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndDisabled();
    ImGui::SameLine();
    if (ImGui::Button("CANCEL", {80, 0})) {
      REF_TO_FILL = nullptr;
      selectedResource = nullptr;
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }
}

int main(int, char *argv[]) {
  es::print::AddPrinterFunction(es::Print);
  ROOT_DIR = argv[1];

  glfwSetErrorCallback(
      [](int type, const char *msg) { printerror('(' << type << ')' << msg); });

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

  Window mainWnd;
  if (int status = InitWindow(mainWnd, 1300, 1000, "Data Editor"); status) {
    return status;
  }

  SwitchWindow(mainWnd);
  WarmColors();
  ImGuiIO &io = ImGui::GetIO();
  HEADING_FONT24 = io.Fonts->AddFontFromFileTTF("data_editor/moderniz.otf", 24);
  HEADING_FONT18 = io.Fonts->AddFontFromFileTTF("data_editor/moderniz.otf", 18);
  io.FontDefault = io.Fonts->AddFontDefault();

  // merge in icons from Font Awesome
  static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
  ImFontConfig icons_config;
  icons_config.MergeMode = true;
  icons_config.PixelSnapH = true;
  io.Fonts->AddFontFromFileTTF("3rd_party/imgui/font_awesome4/font.ttf", 13,
                               &icons_config, icons_ranges);

  namespace fs = std::filesystem;
  fs::path stPath(ROOT_DIR / "st");
  fs::directory_iterator dirIt(stPath);

  for (auto &entry : dirIt) {
    if (entry.is_directory()) {
      collection[entry.path().filename()];
    }
  }

  std::vector<std::jthread> scanners;
  std::set<std::string> scanned;

  scanners.emplace_back([&stPath] {
    for (auto &e : fs::directory_iterator{stPath / "globals" / "scripts"}) {
      LoadClasses(collection["globals"], e.path());
    }
  });
  std::string filter;

  while (!glfwWindowShouldClose(mainWnd.window)) {
    if (io.MouseReleased[3]) {
      GoBack();
    } else if (io.MouseReleased[4]) {
      GoForward();
    }
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
                      ImGuiChildFlags_ResizeX | ImGuiChildFlags_Border,
                      ImGuiWindowFlags_NoScrollWithMouse |
                          ImGuiWindowFlags_NoScrollbar);

    ImGui::BeginChild("header buttons", {-1, 20});
    ImGui::BeginDisabled(HISTORY_INDEX < 1);
    if (ImGui::Button(ICON_FA_ARROW_LEFT)) {
      GoBack();
    }
    ImGui::EndDisabled();
    ImGui::SameLine();
    ImGui::BeginDisabled((HISTORY_INDEX + 1) >= int(RESOURCE_HISTORY.size()));
    if (ImGui::Button(ICON_FA_ARROW_RIGHT)) {
      GoForward();
    }
    ImGui::EndDisabled();
    ImGui::SameLine();
    ImGui::SetNextItemWidth(-20);
    InputTextStd(ICON_FA_SEARCH, filter);
    ImGui::EndChild();
    // FOLDER SELECTOR BEGIN
    ImGui::BeginChild("folder selector");
    for (auto &[name, packs] : collection) {
      if (ImGui::TreeNodeEx(name.c_str(), 0, ICON_FA_FOLDER " %s",
                            name.c_str())) {
        if (packs.empty() && !scanned.contains(name)) {
          scanned.emplace(name);
          scanners.emplace_back([&packs, dirIter = fs::directory_iterator{
                                             stPath / name / "scripts"}] {
            for (auto &e : dirIter) {
              LoadClasses(packs, e.path());
            }
          });
        }

        for (auto &[packName, data] : packs) {
          if (ImGui::TreeNodeEx(packName.c_str(), 0, ICON_FA_DROPBOX " %s",
                                packName.c_str())) {
            for (auto &i : data.resources) {
              ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf |
                                         ((clickedNodeId == i.resource.get()) *
                                          ImGuiTreeNodeFlags_Selected);
              auto found = std::search(
                  i.resource->__guid.begin(), i.resource->__guid.end(),
                  filter.begin(), filter.end(), [](char c0, char c1) {
                    return std::tolower(c0) == std::tolower(c1);
                  });

              if (filter.empty() || found != i.resource->__guid.end()) {
                if (ImGui::TreeNodeEx(i.resource->__guid.c_str(), flags,
                                      ICON_FA_CUBE " %s",
                                      i.resource->__guid.c_str())) {
                  if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                    curEditResource = &i;
                    workingDir = name;
                    clickedNodeId = i.resource.get();
                    PushHistory();
                  }
                  ImGui::TreePop();
                }

                ImGui::SameLine();
                ImGui::TextDisabled("(%s)", i.resource->refl->className);
              }
            }

            ImGui::TreePop();
          }
        }
        ImGui::TreePop();
      }
    }
    ImGui::EndChild();
    // FOLDER SELECTOR END
    ImGui::EndChild();
    ImGui::SameLine();

    // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::BeginChild("right space");
    ImGui::BeginChild(
        "editor space", {}, ImGuiChildFlags_ResizeY | ImGuiChildFlags_Border,
        ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
    // ImGui::PopStyleVar();
    // ImGui::BeginTabBar("right tabspace");
    ImGui::BeginChild("editor space", {});
    if (curEditResource) {
      ImGui::PushFont(HEADING_FONT24);
      ImGui::SetNextItemWidth(-1);
      InputTextStd("##guid", curEditResource->resource->__guid);
      ImGui::PopFont();
      ImGui::Separator();
      for (auto &i : curEditResource->groups) {
        ImGui::PushID(&i);
        std::visit([](auto &t) { Draw(t); }, i);
        ImGui::PopID();
      }
    }
    ImGui::EndChild();
    // ImGui::EndTabBar();
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
  }

  DestroyWindow(mainWnd);
  glfwTerminate();
  return 0;
}
