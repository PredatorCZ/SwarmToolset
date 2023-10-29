#pragma once
#include "core.hpp"
#include "enum_share.hpp"

struct AIAction : ResourcePack {
  float percentChance;
  float delayMax;
  float delayMin;
};

struct AIActionList : AIAction {
  ResourceArray actions;
};

struct AITriggerBoxActions : AIActionList {
  float delay;
};

struct AIActionTarget : AIAction {
  ResourceRef target;
};

struct AIA_Dropship_Descend : AIActionTarget {};
struct AIA_Dropship_Ascend : AIActionTarget {};
struct AIA_Dropship_Takeoff : AIActionTarget {};
struct AIA_Dropship_HoverMoveWP : AIActionTarget {};
struct AIA_Dropship_Disembark : AIActionTarget {};

struct AIA_Dropship_SetFlightSpeed : AIActionTarget {
  uint32 speed1Slow2Medium3Fast;
};

struct AIA_Dropship_Landing : AIActionTarget {
  bool flyToHover;
  bool hoverToLand;
};

struct AIA_Hopper_SetFlightSpeed : AIA_Dropship_SetFlightSpeed {};

struct AIA_Bomber_DropBomb : AIActionTarget {
  ResourceRef bomber;
  ResourceRef napalm;
};

struct AIA_Entity_AddHealthBar : AIActionTarget {};
struct AIA_Entity_RemoveHealthBar : AIActionTarget {};
struct AIA_Entity_Jump : AIAction {};

struct AIA_Entity_Kill : AIActionTarget {
  bool setOnFire;
  bool gib;
  float gibForce;
};

struct AIA_Entity_SetTarget : AIActionTarget {
  ResourceRef entity;
  bool forcedTarget;
};

struct AIA_Entity_SetStickToWaypoints : AIActionTarget {
  bool stickToWaypoints;
};

struct AIA_Entity_SetTargettable : AIActionTarget {
  bool targettable;
};

struct AIA_Entity_SetAlert : AIActionTarget {
  AIALERT alert;
};

struct AIA_Entity_SetWaypoint : AIActionTarget {
  ResourceRef waypoint;
};

struct AIA_Entity_ForcePos : AIActionTarget {
  Vector position;
};

struct AIA_Entity_SetVunerability : AIActionTarget {
  bool vunerability;
};

struct AIA_Entity_ForceAngle : AIActionTarget {
  float angle;
};

struct AIA_Entity_SetMode : AIActionTarget {
  AIMODE mode;
};

struct AIA_Entity_SetCheckGradient : AIActionTarget {
  bool checkGradient;
};

struct AIA_Entity_SetAvoidance : AIActionTarget {
  bool avoidance;
};

struct AIA_Entity_SetHealth : AIActionTarget {
  float healthPercent;
};

struct AIA_Warrior_SetZigzag : AIActionTarget {
  bool zigzag;
};

struct AIA_Warrior_SwitchOverrideAnimSet : AIActionTarget {
  ResourceRef animSet;
};

struct AIA_WarriorRoyal_SonicRoar : AIActionTarget {
  ResourceArray actions;
};

struct AIA_WarriorRoyal_SonicRoarAttack : AIActionTarget {};

struct AIA_Warrior_SetWPNarrow : AIActionTarget {
  bool narrow;
};

struct AIA_Warrior_SetMaxSpeed : AIActionTarget {
  bool allowFastRun;
};

struct AIA_Warrior_SetIgnoreRadius : AIActionTarget {
  float ignoreRadius;
  bool useDeltaY;
  float deltaY;
};

struct AIA_Human_DoSalute : AIActionTarget {};

struct AIA_Human_SetNextPointAccurate : AIActionTarget {
  bool heading;
};

struct AIA_Human_SetKneeling : AIActionTarget {
  bool kneeling;
};

struct AIA_Human_PlayAnimLoop : AIActionTarget {
  ResourceRef animation;
  ResourceRef animationSet;
  STANDARD_POSE standardPose;
  bool playImmediately;
  float maxTime;
  uint32 maxRepetitions;
  bool SetVulnerableDuring;
  bool VulnerabilityDuring;
  bool SetVulnerableAfter;
  bool VulnerabilityAfter;
};

struct AIA_Human_SwitchWeapon : AIActionTarget {
  ResourceRef weapon;
};

enum AIHS {
  AIHS_STATIONARY,
  AIHS_WALK,
  AIHS_RUN,
};

struct AIA_Human_SetMaxSpeed : AIActionTarget {
  AIHS speed;
};

struct AIA_Human_TurnToFaceAngle : AIActionTarget {
  float angle;
  ResourceArray actions;
};

struct AIA_Human_SetPersonalAttractTurnChance : AIActionTarget {
  float turnChance;
};

struct AIA_Human_SetPersonalGrenadeChance : AIActionTarget {
  float grenadeChance;
};

struct AIA_Human_SetPersonalKneelChance : AIActionTarget {
  float kneelChance;
};

struct AIA_Human_TurnToFaceObject : AIA_WarriorRoyal_SonicRoar {
  ResourceRef object;
};

struct AIA_Human_SetSentryMode : AIActionTarget {
  bool sentryOn;
};

struct AIA_Human_Gib : AIActionTarget {
  float blastStrength;
};

struct AIA_Human_SetGunState : AIActionTarget {
  bool gunOn;
};

struct AIA_Human_GoToHotSpots : AIActionTarget {
  AIHS hotSpotType;
  float radius;
};

struct AIA_Door_LockOpen : AIActionTarget {};
struct AIA_Door_Open : AIActionTarget {};
struct AIA_Door_Close : AIActionTarget {};
struct AIA_Door_LockClosed : AIActionTarget {};

struct AIA_Lift_Up : AIActionTarget {};
struct AIA_Lift_Down : AIActionTarget {};

struct AIA_Spawner_StartSpawning : AIActionTarget {};
struct AIA_Spawner_StopSpawning : AIActionTarget {};

struct AIA_SpawnGroup_StartSpawning : AIActionTarget {};
struct AIA_SpawnGroup_StopSpawning : AIActionTarget {};

struct AIA_Light_Off : AIActionTarget {};
struct AIA_Light_On : AIActionTarget {};

struct AIA_Switch_SwitchOn : AIActionTarget {};
struct AIA_Switch_SwitchOff : AIActionTarget {};

struct AIA_SwitchOnOff : AIActionTarget {
  bool switchState;
};

struct AIA_Squad_SetWayPoint : AIActionTarget {
  ResourceRef waypoint;
};

struct AIA_Squad_SetMode : AIActionTarget {
  AISQUADMODE mode;
};

struct AIA_Squad_Detatch : AIAction {
  ResourceRef squad;
};

struct AIA_Squad_RemoveMember : AIAction {
  ResourceRef squad;
  ResourceRef member;
};

struct AIA_Squad_AddMember : AIA_Squad_RemoveMember {};

struct AIA_Squad_GoToHotSpots : AIAction {
  ResourceRef squad;
  AIHS hotSpotType;
  float radius;
};

struct AIA_Squad_SetFormation : AIActionTarget {
  AISQUADFORMATION formation;
};

struct AIA_Squad_SetFormationSpacing : AIActionTarget {
  float formationSpacing;
};

struct AIA_Squad_AttatchOnPath : AIAction {
  ResourceRef squad;
  ResourceRef entity;
};

struct AIA_Player_SetVelFactor : AIActionTarget {
  float speedFactorPercent;
};

struct AIA_Player_SwitchTorch : AIActionTarget {
  bool bSwitch;
};

struct AIA_Player_AddVelocity : AIActionTarget {
  float velX;
  float velY;
  float velZ;
};

struct AIA_Player_SetLadder : AIActionTarget {
  ResourceRef ladder;
};

struct AIA_ChatScriptStart : AIActionTarget {};
struct AIA_SetActive : AIActionTarget {};
struct AIA_DeleteGroup : AIActionTarget {};
struct AIA_LightUpdateContexts : AIActionTarget {};
struct AIA_Player_DisableWeapon : AIActionTarget {};
struct AIA_SetInactive : AIActionTarget {};
struct AIA_Delete : AIActionTarget {};
struct AIA_ClearUpDeadBodies : AIAction {};
struct AIA_MusicStop : AIAction {};

struct AIA_SetViewFade : AIAction {
  bool active;
  Color startColour;
  Color endColour;
  float duration;
  float blur;
  bool fadeBackToStart;
  float holdDuration;
};

struct AIA_SetAsViewpoint : AIAction {
  ResourceRef entity;
};

struct AIA_Group_ApplyActions : AIAction {
  ResourceRef targetGroup;
  bool allMembers;
  bool randomMember;
  int32 memberId;
  ResourceArray actions;
};

struct AIA_Model_SetRender : AIActionTarget {
  bool render;
};

struct AIA_QueueSpeech : AIAction {
  ResourceRef chatScript;
};

struct AIA_PlayAnim : AIActionTarget {
  ResourceRef animation;
  bool setVulnerableDuring;
  bool vulnerabilityDuring;
  bool setVulnerableAfter;
  bool vulnerabilityAfter;
  bool useCurrentAngle;
};

struct AIA_LaunchMenu : AIAction {
  std::string menuName;
};

struct AIA_PlaySound : AIActionTarget {
  ResourceRef source;
  bool soundBone;
};

struct AIA_EnableSpeechBank : AIAction {
  bool enable;
};

struct AIA_StampedeRumble : AIA_EnableSpeechBank {};
struct AIA_Player_EnableTorch : AIA_EnableSpeechBank {};

struct AIA_PortalOnOff : AIA_SwitchOnOff {};

struct AIA_DustStorm : AIAction {
  ResourceRef particleResource;
};

struct AIA_HUDDisplay : AIAction {
  bool show;
};

struct AIA_Script : AIAction {
  ResourceRef ifConditional;
  ResourceArray thenActions;
  ResourceArray elseActions;
};

struct AIA_Counter_SetValue : AIActionTarget {
  uint32 value;
};

struct AIA_Counter_IncrementValue : AIA_Counter_SetValue {};
struct AIA_Counter_DecrementValue : AIA_Counter_SetValue {};

struct AIA_CameraShake : AIAction {
  float length;
  Angle angle;
  Angle frequency;
  bool random;
  bool jolt;
  float fadeIn;
  float fadeOut;
};

struct AIA_MusicFadeTo : AIAction {
  float targetVolume;
  float fadeTime;
};

struct AIA_MusicStart : AIActionTarget {
  bool looping;
};

struct AIA_BabyTanker_UseMultiLinkWaypoints : AIActionTarget {
  bool useMultiLinkWaypoints;
};

struct AIA_BabyPlasma_UseMultiLinkWaypoints
    : AIA_BabyTanker_UseMultiLinkWaypoints {};

struct AIA_MusicVolume : AIAction {
  float targetVolume;
};

struct AIA_AmbientSoundObject_Stop : AIAction {
  ResourceArray ambientEffects;
};

struct AIA_AmbientSoundObject_Start : AIA_AmbientSoundObject_Stop {};

struct AIA_StaticNukeLauncher_Fire : AIAction {
  ResourceRef staticNukeLauncher;
};

struct AIA_MusicCrossfade : AIActionTarget {
  bool looping;
  float targetVolume;
  float fadeTime;
};

struct AIA_PhysicsKicker : AIActionTarget {
  Vector offset;
  float radius;
  float force;
  float damage;
  float flame;
};

struct AIA_Action_SetChance : AIActionTarget {
  float percent;
};

struct AIA_ObjectiveMarker_SetPos : AIAction {
  bool positionValid;
  SubObjectivePositionType positionType;
  bool hideMarkerWhenThere;
  Vector position;
  float radius;
  ResourceRef trackableObject;
  ResourceRef subObjective;
};

struct AIA_PlasmaBug_SetSpecialMode : AIActionTarget {
  AIPBSM specialMode;
};

struct AIA_SetPosFromObject : AIAction {
  ResourceRef objectToMove;
  ResourceRef referenceObject;
  float offsetX;
  float offsetY;
  float offsetZ;
  bool setActiveState;
  bool activeValue;
  bool setRenderState;
  bool renderValue;
};

struct AIConditional : ResourcePack {
  ResourceRef target;
};

struct AIConditionalValue : AIConditional {
  uint32 value;
};

struct AIC_Counter_Equals : AIConditionalValue {};
struct AIC_Counter_LessThan : AIConditionalValue {};
struct AIC_Counter_MoreThan : AIConditionalValue {};
struct AIC_Entity_IsAlive : AIActionTarget {};
