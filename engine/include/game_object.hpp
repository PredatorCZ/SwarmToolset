#pragma once

#include "abstract.hpp"
#include <list>

struct PackageRef;

struct GameObject : Abstract {
  void LoadScript() override;
  void ToNative() override;
  void FromNative() override;

  PackageRef *packageRef;
  std::list<GameObject>::iterator sessionIter;
  bool inSession;
  int32_t field_44;
};
