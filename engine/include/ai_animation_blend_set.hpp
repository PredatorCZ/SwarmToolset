#pragma once
#include "sl_variable_template.hpp"
#include <list>
#include <vector>

struct AIEntity;
struct ResourceObjectAnimation;
struct RenderState;
struct AIAnimation;
struct AudioPlayable;
struct Skeleton;

struct AnimationBlend {
  ResourceObjectAnimation *resource;
  double time;
  double time_plus_delta;
  float timeAnim;
  float timeAnim_plus_delta;
  float blend;
  float blend_plus_delta;
  bool field_28;
};

struct AIAnimationBlendSetAnimation {
  AIAnimation *animation;
  float animTime;
  float blendWeight;
};

struct AnimationBlendData {
  void _44DC00(double startTime, double endTime);
  void _44DB30(double time, bool isEnd);

  AIAnimationBlendSetAnimation *setAnimation;
  double time;
  double timeInverseLength;
  float timeAnim;
  float timeAnimLength;
  float blend;
  float blendLength;
};

struct AIAnimationBlendSet {
  void Process(RenderState *state);
  void _452A20(AIAnimation *animation, double aiTime0, double aiTime1,
               float aiAnimTime0, float aiAnimTime1, float blend0,
               float blend1);
  void _452640();
  void _4508F0(double time);
  void PushBlend(AIAnimation *animation, double aiTime0, double aiTime1,
                 float aiAnimTime0, float aiAnimTime1, float blend0,
                 float blend1);
  uint32_t NumAnimations() { return animations.size(); }
  void _450870(double time);
  void _748150();
  void CleanAudioPlayables();
  void _7481A0();
  bool _7481E0();
  void _748230(Skeleton *skel);
  void _749730(RenderState *state);
  void _748950(RenderState *state);

  std::vector<AIAnimationBlendSetAnimation *> animations;
  AIEntity *entity;
  std::list<AnimationBlendData *> animationBlends;
  std::list<AudioPlayable *> activeAudioPlayables;
  std::vector<AnimationBlend> blends;
  SLVariableTemplate<uint32_t> *AnimIndex[8];
  SLVariableTemplate<uint32_t> *m_dTime0[8];
  SLVariableTemplate<uint32_t> *m_dInvDTime[8];
  SLVariableTemplate<uint32_t> *m_fTAnim0[8];
  SLVariableTemplate<uint32_t> *m_fDTAnim[8];
  SLVariableTemplate<uint32_t> *m_fBlend0[8];
  SLVariableTemplate<uint32_t> *m_fDBlend[8];
};
