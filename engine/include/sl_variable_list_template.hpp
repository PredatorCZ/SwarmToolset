#pragma once
#include "sl_variable.hpp"
#include <list>

template <class Ty> struct SLVariableListTemplate : SLVariable {
  std::list<Ty *> values;
  std::string name;
};
