#pragma once

#include "ai_entity.hpp"

struct GlowShaderController;

struct AIBug : AIEntity {
  void LoadScript() override;
  void ToNative() override;
  void FromNative() override;
  bool IsAIType(AITYPEID typeId) override;
  float GetSpottingBias(AIEntity *entity) override;

  void _49A6D0(double startTime, double endTime, float startEmissiveFactor,
               float endEmisiveFactor, float startGlowFactor,
               float endGlowFactor);

  ResourcePtr<ResourceSound> burstGib;
  ResourcePtr<ResourceSound> gibSplat;
  AudioPlayable *burstGibAudioPlayable;
  AudioPlayable *gibSplatAudioPlayable;
  AudioPlayable3DExtended *burstGibAudioPlayable3D;
  AudioPlayable3DExtended *gibSplatAudioPlayable3D;
  std::vector<GlowShaderController *> shaderControllers;
};
