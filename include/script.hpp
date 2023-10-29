#pragma once
#include <functional>
#include <iosfwd>
#include <string_view>

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
  void Process();

private:
  friend class ScriptParserImpl;
  std::istream &stream;
  size_t bufferIter = 0;
  char curBuffer[0x1000];
  char prevChar = 0;
};
