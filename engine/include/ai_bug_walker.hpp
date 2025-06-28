#pragma once
#include "ai_bug.hpp"

struct Walker;

struct AIBugWalker : AIBug {
  void LoadScript() override;
  void ToNative() override;
  void FromNative() override;
  bool IsAIType(AITYPEID typeId) override;

  Walker *walker;
};
