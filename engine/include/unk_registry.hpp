#pragma once
#include <list>

struct UnkStruct0;
struct AIHeightMap;
struct Collider;
struct WorldObject;

struct UnkRegistry0 {
  static UnkRegistry0 *Get();

  bool _66E250(const Collider &collider);
  WorldObject *_66DAA0(const Collider &collider, WorldObject *object);

  std::list<UnkStruct0 *> field_0;
  std::list<void *> field_C;
  std::list<void *> field_18;
  std::list<AIHeightMap *> heightMaps;
};
