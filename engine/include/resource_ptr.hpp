#pragma once
#include "sl_variable_abstract_ref.hpp"

template <class Ty> struct ResourcePtr : SLVariableAbstractRef {
  Ty *object;

  ResourcePtr &operator=(Ty *newObj) {
    if (newObj != object) {
      object->DecreaseReference();
      object = newObj;
      Assign(newObj, 0);
      object->SafeLoad();
    }
  }

  bool operator==(const ResourcePtr &other) const {
    return object == other.object;
  }

  Ty *operator->() { return object; }
};
