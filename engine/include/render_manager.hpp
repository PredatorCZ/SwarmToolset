#pragma once
#include <list>

struct RenderContext;
struct RenLight;

struct RenderManager {
  static RenderManager *Get();

  std::list<RenderContext *> contexts;
  std::list<RenLight *> lights;
  int field_18;
  int field_1C;
  int field_20;
  char field_24;
  char field_25;
  int field_28;
  int field_2C;
  int field_30;
  int field_34;
  int field_38;
  int field_3C;
};
