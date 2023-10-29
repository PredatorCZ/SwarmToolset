#pragma once
#include <vector>
#include <string>
#include "spike/io/fileinfo.hpp"
#include "spike/type/matrix44.hpp"

using Color = UCVector4;

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
  std::string __guid;
  virtual ~Resource() = default;
  void ReflectorTag();
};

struct ResourcePack : Resource {
  std::string package;
};

struct ResourceRef {
  Resource *ref;
  ResourceRef(Resource *res);
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
