#pragma once
#include "enum_share.hpp"
#include "quicksave/objective.hpp"

struct ObjectiveActionAIAction : ResourcePack {
  int32 order;
  ObjectiveActionAIActionQuicksave objectiveActionAIActionQuicksave;
  ResourceArray actions;
};

struct ObjectiveActionWaitForSpeechToEnd : ResourcePack {
  int32 order;
  ObjectiveActionWaitForSpeechToEndQuicksave
      objectiveActionWaitForSpeechToEndQuicksave;
  ResourceRef entity;
  float timeoutPeriod;
};

struct ObjectiveActionKillTally : ResourcePack {
  int32 order;
  ObjectiveActionKillTallyQuicksave objectiveActionKillTallyQuicksave;
  AITYPEID type;
  int32 num;
  ResourceRef group;
  ResourceRef desiredKiller;
};

struct SubObjective : ResourcePack {
  SubObjectivePositionType positionType;
  Vector position;
  bool hideMarkerWhenThere;
  float markerRadius;
  ResourceRef trackableObject;
  ResourceArray actions;
  SubObjectiveQuicksave subObjectiveQuicksave;
};

struct ObjectiveActionStayInVicinity : ResourcePack {
  int32 order;
  ObjectiveActionStayInVicinityQuicksave objectiveActionStayInVicinityQuicksave;
  float initialiseTime;
  float timeRequired;
  float endPhaseTime;
  float resetTime;
  bool resetOnAreaLeave;
  Vector position;
  float activeArea;
  float pauseArea;
  ResourceRef activeMarkerBox;
  ResourceRef pauseMarkerBox;
  ResourceRef HUD_PROGRESS_INITIALISE_Sound;
  ResourceRef HUD_PROGRESS_MAIN_Sound;
  ResourceRef HUD_PROGRESS_PAUSED_Sound;
  ResourceRef HUD_PROGRESS_RESET_Sound;
  ResourceRef HUD_PROGRESS_FINISHED_Sound;
  ResourceRef entity;
  bool showBar;
};

struct ObjectiveAction {
  ResourceArray actions;
  void ReflectorTag();
};

struct ObjectiveTimingInfo {
  bool timed;
  float timeToComplete;
  ObjectiveState failState;
  void ReflectorTag();
};

struct ObjectiveRepeatInfo {
  float timeToRepeat;
  bool repeatInRadius;
  float repeatRadius;
  void ReflectorTag();
};

struct Objective : ResourcePack {
  int32 number;
  bool designerPhase;
  ObjectiveTimingInfo timingInfo;
  ObjectiveRepeatInfo objectiveRepeatInfo;
  std::string description;
  ResourceRef spokenObjective;
  float nextObjective;
  ObjectiveAction preamble;
  ResourceArray subObjectives;
  ObjectiveAction success;
  ObjectiveAction partialFail;
  ObjectiveAction totalFail;
  ObjectiveQuicksave objectiveQuicksave;
};

struct ObjectiveActionKeepAliveSpecific : ResourcePack {
  int32 order;
  ObjectiveActionKeepAliveSpecificQuicksave
      objectiveActionKeepAliveSpecificQuicksave;
  ResourceRef entity;
  ObjectiveState failState;
  float timeToKeepAlive;
};

struct ObjectiveActionUpdateObjectiveLocation : ResourcePack {
  int32 order;
  ObjectiveActionUpdateObjectiveLocationQuicksave
      objectiveActionUpdateObjectiveLocationQuicksave;
  bool positionValid;
  SubObjectivePositionType positionType;
  bool hideMarkerWhenThere;
  Vector position;
  float radius;
  ResourceRef trackableObject;
  ResourceRef subObjective;
};

struct ObjectiveActionWaitForObjectUse : ResourcePack {
  int32 order;
  ObjectiveActionWaitForObjectUseQuicksave quicksave;
  ResourceRef target;
};

struct ObjectiveActionWait : ResourcePack {
  int32 order;
  ObjectiveActionWaitQuicksave quicksave;
  bool showCountdown;
  float time;
};

struct ObjectiveActionUpdateGlobalObjective : ResourcePack {
  int32 order;
  ObjectiveActionUpdateGlobalObjectiveQuicksave quicksave;
  std::string description;
};

struct ObjectiveActionWaitForTrigger : ResourcePack {
  int32 order;
  ObjectiveActionWaitForTriggerQuicksave quicksave;
  float timeoutLength;
};

struct ObjectiveActionWaitTillChatScriptFinished : ResourcePack {
  int32 order;
  ObjectiveActionWaitTillChatScriptFinishedQuicksave quicksave;
  ResourceRef script;
  float timeoutPeriod;
};

struct ObjectiveActionCollectItems : ResourcePack {
  int32 order; //: { "199" }
  ObjectiveActionUpdateGlobalObjectiveQuicksave
      objectiveActionCollectItemsQuicksave;
  ResourceArray itemsToCollect;
};

struct ObjectiveActionKillSpecific : ResourcePack {
  int32 order; //: { "199" }
  ObjectiveActionUpdateGlobalObjectiveQuicksave
      objectiveActionKillSpecificQuicksave;
  ResourceRef entity;
};

struct ObjectiveActionJumpToObjective : ResourcePack {
  int32 order; //: { "199" }
  ObjectiveActionUpdateGlobalObjectiveQuicksave
      objectiveActionJumpToObjectiveQuicksave;
  uint32 objectiveNumber;           //: { "10" }
  ObjectiveState endStateToProcess; //: { "Success" }
};

struct ObjectiveActionTextMessage:ResourcePack
{
		int32 order;//: { "4" }
		ObjectiveActionUpdateGlobalObjectiveQuicksave quicksave;
		std::string string;//: { "GlobalStringTable:ARMED" }
};

struct ObjectiveActionKillTallyDestructableObjects:ResourcePack
{
		int32 order;//: { "6" }
		ObjectiveActionKillTallyDestructableObjectsQuicksave quicksave;
		uint32 countFromTrigger;//: { "1" }
		uint32 numRequired;//: { "4" }
};

struct ObjectiveActionTimedStay:ResourcePack
{
		int32 order;//: { "5" }
		ObjectiveActionUpdateGlobalObjectiveQuicksave quicksave;
		float time;//: { "20" }
		ObjectiveState failState;
		Vector position;
		float safeArea;//: { "4" }
};
