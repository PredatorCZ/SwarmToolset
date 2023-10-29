#pragma once
#include "script/core.hpp"

struct AITwoStateMatrix {
  float aiTime[2];
  Matrix aiMatrix[2];
  bool aiMoving[2];
  void ReflectorTag();
};

struct AIFourStateMatrix {
  float aiTime[4];
  Matrix aiMatrix[4];
  bool aiMoving[4];
  void ReflectorTag();
};

struct AIThreeStateMatrix {
  float aiTime[3];
  Matrix aiMatrix[3];
  bool aiMoving[3];
  void ReflectorTag();
};

struct AIFlyerTwoStateMatrix : AITwoStateMatrix {
  Vector aiVel[2];
  float fHover[2];
  Vector lastPos;
  Vector lastVel;
  float lastRoll;
  float rollState;
  Vector midpointOffset;
  void ReflectorTag();
};

struct AIEntityGenericQuicksave {
  AITwoStateMatrix aiTwoStateMatrix;
  float aiAnimTime[2];
  uint32 pAnim;
  ResourceRef pCustomAnim;
  void ReflectorTag();
};

struct AIEntityQuicksaveAnimationBlend {
  int32 animIndex;
  float dTime0;
  float dInvDTime;
  float fTAnim0;
  float fDTAnim;
  float fBlend0;
  float fDBlend;
  void ReflectorTag();
};

struct AIEntityQuicksaveAnimSet {
  AIEntityQuicksaveAnimationBlend aiAnimationBlends[8];
  void ReflectorTag();
};

struct AIEntityNonPhysicalPresenceAIEntityQuicksave {
  AIEntityQuicksaveAnimSet animSet;
  int32 bEndOfWPChain;
  float fNextVulnerability;
  int32 bNextVulnerabilityIsSet;
  ResourceRef pAggressor;
  Vector lastPos;
  Vector velocity;
  void ReflectorTag();
};

struct AIEntityQuicksave : AIEntityNonPhysicalPresenceAIEntityQuicksave {
  ResourceRef pRagDoll;
  bool bNeedToAdvanceWP;
  Vector bNeedToAdvanceWPPos;
  bool bCanSeeTarget;
  Vector lastTargetPosition;
  bool hasHealthBar;
  void ReflectorTag();
};
