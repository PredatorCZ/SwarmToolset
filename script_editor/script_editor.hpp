#pragma once
#include "TextEditor.h"
#include "imgui.h"
#include "squirrel.h"

enum class DebugTriggerType {
  Continue,
  StepInto,
  StepOver,
  Stop,
};

struct DocumentEdit {
  TextEditor editor;
  double lastTimeTextChanged = 0;
  TextEditor::ErrorMarkers errors;
  const char *name;
  bool active = false;
  bool opened = false;
  ImGuiTabItemFlags tabFlags = 0;
};

DocumentEdit &Document(const char *name);

void NewIdentifierDb(const char *path);

TextEditor::LanguageDefinition &SQLangDef();

struct Debugger;
Debugger *InitDebugger(HSQUIRRELVM v);
void RenderDebugger(Debugger *dbg);
void DeleteDebugger(Debugger *&dbg);
