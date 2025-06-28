#pragma once
#include "world_object_matrix.hpp"
#include "resource_ptr.hpp"

struct RenderState;
struct AudioPlayable;
struct AudioPlayable3DExtended;
struct ResourceObjectModel;
struct ResourceSound;
struct IncomingDamage;

struct WorldObjectModel : WorldObjectMatrix {
  virtual void SetRender(bool value);

  void LoadScript() override;
  void ToNative() override;
  void FromNative() override;
  void field_28() override;
  void field_2C() override;
  void field_30() override;
  void field_38() override;
  void ApplyDamage(IncomingDamage &dmg) override;

  const Matrix *Get() const override;
  Matrix *Get() override;

  void _95AB60();

  int32_t field_AC;
  ResourcePtr<ResourceObjectModel> resourceRef;
  RenderState *renderState;
  AABoundingBox bbox;
  ResourcePtr<ResourceSound> bulletImpact;
  ResourcePtr<ResourceSound> field_198;
  ResourcePtr<ResourceSound> field_1F4;
  AudioPlayable *bulletImpactAudioPlayable;
  AudioPlayable *field_254;
  AudioPlayable *field_258;
  AudioPlayable3DExtended *bulletImpactAudioPlayable3D;
  AudioPlayable3DExtended *field_260;
  AudioPlayable3DExtended *field_264;
  int32_t field_268;
  int32_t shaderOverrides;
  int32_t field_270;
  bool shadowAtlasCaster;
  bool shadowAtlasReceiver;
  bool field_276;
  bool field_277;
};
