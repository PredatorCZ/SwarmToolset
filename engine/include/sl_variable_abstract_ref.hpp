#pragma once
#include "sl_variable.hpp"
#include <map>
#include <set>

struct Abstract;

struct SLVariableAbstractRef : SLVariable {
  virtual void field_34();
  virtual void field_38();

  std::string &DumpTypeName(std::string &outValue) override {
    return outValue = "SLVariableAbstractRef";
  }

  std::string &ToString(std::string &outValue) override {
    return outValue = guid;
  }

  std::ostream &ToStream(std::ostream &str) override { return str << guid; }
  bool FromString(const std::string &text, int ignoreLock) override;
  SLVariable *Clone() override;
  void func_28(void *value) override { field_54 = value; }
  void *func_2C() override { return field_54; }
  // 41A5E0
  void func_30() override {
    void *value = func_2C();
    // return (*(int (__thiscall **)(int))(*(_DWORD *)value + 8))(value);
  }

  SLVariableAbstractRef() = default;
  SLVariableAbstractRef(const SLVariableAbstractRef &other);
  void SetGUIDFromReference();
  void SetReference(Abstract *abstract);
  void Assign(Abstract *abstract, int);

  int referenceState = 0;
  Abstract *reference = nullptr;
  std::string guid;
  std::set<SLVariableAbstractRef *>::iterator referenceNodeToThis;
  std::map<std::string, SLVariableAbstractRef *>::iterator
      globalReferenceNodeToThis;
  void *field_54 = nullptr;
};

template <> consteval const char *GetTypenameFromType<SLVariableAbstractRef>() {
  return "SLVariableAbstractRef";
}
