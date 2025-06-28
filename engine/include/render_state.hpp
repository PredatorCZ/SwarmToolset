#pragma once
#include "dx_types.hpp"
#include <list>
#include <map>
#include <vector>

struct RenModel;
struct RenderContext;
struct AIAnimationBlendSet;
struct RenShader;
struct RenShaderParams;
struct AABoundingBox;
struct SkeletalAnimation;

struct RenderState {
  void SetModel(RenModel *);
  void SetRender(bool shouldRender);
  void SetAnimSet(AIAnimationBlendSet *set);
  // tree_Transform_node *renModelTransformNode;
  char render;
  std::list<RenderState *>::iterator listIter;
  RenModel *renModel;
  std::vector<Matrix> matrices;
  RenderContext *renderContext;
  int currentLod;
  char field_28;
  std::list<RenderState *>::iterator contextLodNode;
  int field_30;
  int field_34;
  double field_38;
  int field_40;
  std::list<RenderState *>::iterator contextNode;
  std::map<RenShader *, RenShaderParams *> shaderParams;
  AIAnimationBlendSet *animSet;
  Vector position;
  int field_64;
  std::list<RenderState *> children;
  RenderState *parent;
  AABoundingBox *bbox;
  char field_7C;
  char field_7D;
  float field_80;
  int field_84;
  double field_88;
  int field_90;
  float field_94;
  char field_98;
  char field_99;
  char field_9A;
  char field_9B;
  char field_9C;
  std::list<SkeletalAnimation *> skeletalAnimations;
  int field_AC;
};
