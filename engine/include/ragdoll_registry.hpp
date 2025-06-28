#pragma once
#include <list>

struct RagDoll;
struct ModelDetailDynamic;

struct RagDollRegistry {
  static RagDollRegistry *Get();

  void CreateFromModelObject(ModelDetailDynamic *model);

  std::list<RagDoll *> ragdolls;
};
