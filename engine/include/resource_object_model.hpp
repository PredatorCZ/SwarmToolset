#pragma once
#include "resource_object.hpp"
#include "serializable.hpp"
#include <map>
#include "resource_ptr.hpp"
#include <vector>

struct RenModel;
struct ResourceShader;
struct ResourceMaterial;
struct ResourceObjectAnimationSet;

using ClassIndex = unsigned;

struct SLColCell {};

struct ResourceObjectModel : ResourceObject, Serializable
{
  RenModel *model;
  char field_7C;
  int shadowGeneration;
  char animated;
  char field_85;
  int modelType;
  std::map<std::string, ResourcePtr<ResourceShader>> shaders;
  std::map<std::string, ResourcePtr<ResourceMaterial>> materials;
  SLVariableAbstractRef defaultPhysicalMaterial_sl;
  ResourceObject *defaultPhysicalMaterial;
  std::map<ClassIndex, ResourcePtr<ResourceObjectAnimationSet>> animationSets;
  ResourceObjectModel *baseModelAnimSets;
  ResourcePtr<ResourceObjectModel> field_110;
  char field_16C;
  int numLods;
  ResourcePtr<ResourceObject> collidableResource;
  std::vector<SLColCell> *colCells;
  std::vector<std::vector<int>> boneSlotToBoneIdPerLod;
  int *field_1E4;
};
