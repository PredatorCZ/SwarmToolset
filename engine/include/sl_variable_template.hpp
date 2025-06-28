#pragma once
#include "sl_variable.hpp"
#include <sstream>
#include <string>

namespace std {
inline const std::string &to_string(const std::string &s) { return s; }
} // namespace std

template <class Ty> struct SLVariableTemplate : SLVariable {
  virtual void SetValue(const Ty &newValue) { value = newValue; }
  virtual const Ty &GetValue() { return value; }
  virtual void SetReference(Ty *valueRef) { reference = valueRef; }
  virtual void CleanReference() { reference = nullptr; }

  std::string &DumpTypeName(std::string &outValue) override {
    return outValue = GetTypenameFromType<Ty>();
  }

  std::string &ToString(std::string &outValue) override {
    return outValue = std::to_string(value);
  }

  std::ostream &ToStream(std::ostream &str) override { return str << value; }

  bool FromString(const std::string &text, int) override {
    std::stringstream str(text);
    Ty tempValue;
    str >> tempValue;

    if (str.fail()) {
      return false;
    }

    value = tempValue;
    return true;
  }

  SLVariable *Clone() override {
    SLVariableTemplate *clone = new SLVariableTemplate();
    clone->name = name;
    clone->SetValue(value);
    clone->isLocked = isLocked;
    clone->field_26 = field_26;

    return clone;
  }

  void func_20() override {
    if (reference) {
      *reference = value;
    }
  }

  void func_24() override {
    if (reference) {
      value = *reference;
    }
  }

  Ty value = {};
  Ty *reference = nullptr;
};

template <> consteval const char *GetTypenameFromType<int32_t>() {
  return "int";
}

template <> consteval const char *GetTypenameFromType<float>() {
  return "float";
}

template <> consteval const char *GetTypenameFromType<double>() {
  return "double";
}

template <> consteval const char *GetTypenameFromType<uint32_t>() {
  return "unsigned int";
}

template <> consteval const char *GetTypenameFromType<std::string>() {
  return "string";
}
