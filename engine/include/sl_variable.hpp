#pragma once
#include <cstdint>
#include <iosfwd>
#include <string>

template <class Ty> const char *GetTypenameFromType();

struct SLVariable {
  virtual ~SLVariable() = default;
  virtual std::string &DumpTypeName(std::string &outValue) = 0;
  virtual std::string &ToString(std::string &outValue) = 0;
  virtual std::ostream &ToStream(std::ostream &str) = 0;
  virtual void SetName(const std::string &name);
  virtual bool FromString(const std::string &value, int ignoreLock);
  virtual SLVariable *Clone() = 0;
  virtual void Dump(std::ostream &str, size_t indent);
  virtual void func_20() {}
  virtual void func_24() {}
  virtual void func_28(void*) {}
  virtual void *func_2C() { return 0; }
  virtual void func_30() {}

  std::string name;
  int32_t isLocked;
  bool field_24;
  bool field_25;
  bool field_26;
  bool field_27;
};
