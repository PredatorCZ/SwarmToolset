#pragma once
#include <functional>
#include <iosfwd>
#include <string_view>
#include <memory>
#include "settings.hpp"

enum ValueType {
  VL_SIMPLE,   // in ""
  VL_ARRAY,    // in []
  VL_SUBCLASS, // non whitespace
};

struct ScriptParser {
  ScriptParser(std::istream &str) : stream(str) {}
  std::function<void(std::string_view)> newClass;
  std::function<void(std::string_view, ValueType)> newMember;
  std::function<void(std::string_view)> newValue;
  std::function<void()> subclassEnd;
  void SW_EXTERN Process();

private:
  friend class ScriptParserImpl;
  std::istream &stream;
  size_t bufferIter = 0;
  char curBuffer[0x1000];
  char prevChar = 0;
};

struct Resource;

std::unique_ptr<Resource> SW_EXTERN AllocClass(std::string_view className);
