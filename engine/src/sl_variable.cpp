#include "sl_variable.hpp"
#include <iomanip>
#include <ostream>

void SLVariable::SetName(const std::string &newName) {
  if (isLocked) {
    throw "Cannot set name of a locked variable\n";
  }

  name = newName;
}

void SLVariable::Dump(std::ostream &str, size_t indent) {
  if (!field_24) {
    return;
  }

  if (indent) {
    str << std::setfill('\t') << std::setw(indent);
  }

  str << name << ": { \"";
  ToStream(str) << "\" }\n";
}
