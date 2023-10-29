#pragma once
#include "script/core.hpp"

struct ObjectiveActionAIActionQuicksave {
  bool complete;
  bool triggered;
  void ReflectorTag();
};

struct ObjectiveActionWaitForSpeechToEndQuicksave {
  bool complete;
  bool triggered;
  float timeLeft;
  void ReflectorTag();
};

struct ObjectiveActionKillTallyQuicksave {
  bool complete;
  bool triggered;
  int32 currentCount;
  void ReflectorTag();
};

struct SubObjectiveQuicksave {
  ResourceRef itrAction;
  bool bDeRegistedPositionWithHUD;
  void ReflectorTag();
};

struct ObjectiveActionStayInVicinityQuicksave {
  bool complete;
  bool triggered;
  ResourceRef currentState;
  float currentPhaseTime;
  float continueTime;
  void ReflectorTag();
};

enum class ObjectiveState {
  Nostate,
  Preamble,
  Main,
  Success,
  Partialfailure,
  Totalfailure,
  Complete,
};

struct ObjectiveQuicksave {
  ObjectiveState pState;
  float timeLeft;
  bool itrOA;
  bool bTriggered;
  void ReflectorTag();
};

struct ObjectiveActionKeepAliveSpecificQuicksave {
  bool complete;
  bool triggered;
  float timeLeft;
  void ReflectorTag();
};

struct ObjectiveActionUpdateObjectiveLocationQuicksave {
  bool complete;
  bool triggered;
  void ReflectorTag();
};

struct ObjectiveActionWaitForObjectUseQuicksave {
  bool complete;
  bool triggered;
  void ReflectorTag();
};

struct ObjectiveActionWaitQuicksave {
  bool complete;
  bool triggered;
  float startTime;
  void ReflectorTag();
};

struct ObjectiveActionUpdateGlobalObjectiveQuicksave {
  bool complete;
  bool triggered;
  void ReflectorTag();
};

struct ObjectiveActionWaitForTriggerQuicksave {
  bool complete;
  bool triggered;
  float timeLeft;
  bool getIsActive;
  void ReflectorTag();
};

struct ObjectiveActionWaitTillChatScriptFinishedQuicksave {
  bool complete;
  bool triggered;
  float timeLeft;
  void ReflectorTag();
};

struct ObjectiveActionKillTallyDestructableObjectsQuicksave {
  bool complete;
  bool triggered;
  uint32 numBeforeTriggered;
  void ReflectorTag();
};
