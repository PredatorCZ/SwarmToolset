#pragma once
#include "spike/io/fileinfo.hpp"
#include "spike/type/matrix44.hpp"
#include <string>
#include <variant>
#include <vector>

struct Color {
  uint32 raw;
  void ReflectorTag();
};

struct reflectorStatic;

struct AABB {
  Vector min;
  Vector max;
  void ReflectorTag();
};

struct Angle {
  float heading;
  float pitch;
  float roll;
  void ReflectorTag();
};

struct Matrix : es::Matrix44 {
  void ReflectorTag();
};

struct Resource {
  const reflectorStatic *refl = nullptr;
  std::string __guid;
  virtual ~Resource() = default;
  void ReflectorTag();
};

struct ResourcePack : Resource {
  std::string package;
};

struct ResourceRef {
  std::string asString;
  union {
    Resource *asLink = nullptr;
    uint64 asAddress;
  };
  void ReflectorTag();
};

using ResourceArray = std::vector<ResourceRef>;

struct CollisionFlags {
  bool terrain;
  bool bullet;
  bool object;
  bool aiwalk;
  bool player;
  bool sight;
  bool efence;
  bool particle;
  void ReflectorTag();
};
