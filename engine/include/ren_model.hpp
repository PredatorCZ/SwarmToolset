#pragma once
#include "aa_bounding_box.hpp"
#include <vector>
#include <list>
#include <set>

struct RenMesh;
struct RenModelBoneInfo;
struct Skeleton;
struct RenderState;

struct RenModel {
RenMesh *renderMesh;
  RenMesh *shadowMesh;
  RenMesh *shadowAtlasMesh;
  std::vector<Matrix> globalPose;
  std::vector<AABoundingBox> bboxes;
  std::vector<RenModelBoneInfo *> boneInfos;
  Skeleton *skeleton;
  RenMesh *mesh;
  RenMesh *field_48;
  RenMesh *field_4C;
  //std::list<RenShader::RenModelComponent> *components;
  int shadowGeneration;
  int field_58;
  int field_5C;
  int field_60;
  int field_64;
  //std::list<RenShader_RenModelComponent> shaderToComponentMap;
  std::set<RenderState*> transforms;
  std::list<RenderState*> transformList;
  std::vector<RenModel*> *lods;
  int lodIndex;
  int field_94;
  int modelType;
  std::list<RenModel*>::iterator REN_MODELS_node;
  int numRefs;
  int field_A4;
};
