#include "imgui.h"
#include "script_editor.hpp"
#include "squirrel.h"

#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

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
    ImGui::Text("%lli", i);
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

void DebugHook(HSQUIRRELVM v, SQInteger /*type*/, const SQChar *sourcename,
               SQInteger line, const SQChar *funcname) {
  // printf("%s %lli %s\n",  sourcename, line, funcname);

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

void NotifyDebugState(DebugTriggerType newState) {
  debugState = newState;
  debugBreak.notify_all();
}

struct Debugger {
  std::jthread debugLoop;
  bool debugging = false;
  std::condition_variable callRequested;
  SQInteger numParams = 1;
  HSQUIRRELVM v;

  void sq_debug_call(SQInteger numParams_) {
    numParams = numParams_;
    callRequested.notify_all();
  };
};

Debugger *InitDebugger(HSQUIRRELVM v) {
  Debugger *dbg = new Debugger {
    .v = v,
  };
  dbg->debugLoop = std::jthread([dbg](std::stop_token tok) {
    std::mutex callMutex;
    std::unique_lock lk(callMutex);
    try {
      while (true) {
        dbg->callRequested.wait(lk);

        if (tok.stop_requested()) {
          return;
        }
        dbg->debugging = true;
        sq_call(dbg->v, dbg->numParams, SQFalse, SQTrue);
        dbg->debugging = false;
      }
    } catch (const InterruptedCall &) {
    }
  });

  sq_setnativedebughook(v, DebugHook);
  sq_enabledebuginfo(v, SQTrue);

  return dbg;
}

void DeleteDebugger(Debugger *&dbg) {
  NotifyDebugState(DebugTriggerType::Stop);
  dbg->debugLoop.request_stop();
  dbg->callRequested.notify_all();
  delete dbg;
  dbg = nullptr;
}

void RenderDebugger(Debugger *dbg) {
  if (ImGui::BeginTabItem("Debug")) {
    ImGui::BeginDisabled(dbg->debugging);
    if (ImGui::Button("Start")) {
      sq_pushroottable(dbg->v);
      dbg->sq_debug_call(1);
    }
    ImGui::EndDisabled();

    ImGui::SameLine();
    ImGui::BeginDisabled(!dbg->debugging);

    if (ImGui::Button("Continue")) {
      NotifyDebugState(DebugTriggerType::Continue);
    }

    ImGui::SameLine();

    if (ImGui::Button("Step Over")) {
      NotifyDebugState(DebugTriggerType::StepOver);
    }

    ImGui::SameLine();

    if (ImGui::Button("Step Into")) {
      NotifyDebugState(DebugTriggerType::StepInto);
    }

    ImGui::SameLine();

    if (ImGui::Button("Stop")) {
      NotifyDebugState(DebugTriggerType::Stop);
    }

    ImGui::EndDisabled();

    if (ImGui::CollapsingHeader("Local Variables",
                                ImGuiTreeNodeFlags_DefaultOpen) &&
        callStackNames.size()) {
      InspectCurrentFrame(dbg->v);
    }

    if (ImGui::CollapsingHeader("Call Stack", ImGuiTreeNodeFlags_DefaultOpen) &&
        callStackNames.size()) {
      ImGui::ListBox("##CallStackListBox", &callStackIndex,
                     callStackNames.data(), callStackNames.size());
    }

    ImGui::EndTabItem();
  }
}
