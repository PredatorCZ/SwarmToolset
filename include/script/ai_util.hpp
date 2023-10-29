#pragma once
#include "quicksave/ai_util.hpp"

struct AIEntityNonPhysicalPresence : ResourcePack {
  ResourceRef resourceRef;
  ResourceArray shaderOverrides;
  Vector position;
  Angle angle;
  bool render;
  std::string debugContext;
  AIEntityNonPhysicalPresenceAIEntity aiEntity;
  std::string name;
};

struct AISpawnGroupSpawning {
  ResourceArray spawners;
  int32 maxNumberActive;
  int32 numberInWave;
  int32 respawnDelayMin;
  int32 respawnDelayMax;
  int32 maxNumberActiveLowFPS;
  void ReflectorTag();
};

struct AISpawnGroup : WorldObject {
  AIGroupQuicksave aiGroupQuicksave;
  ResourceArray members;
  ResourceArray groupDeathAction;
  AISpawnGroupSpawning spawning;
  AABB aabb;
  ResourceRef startWaypoint;
  AISpawnGroupQuicksave aiSpawnGroupQuicksave;
};

struct AITriggerBox : ResourcePack {
  AABB aabb;
  bool active;
  float checkTime;
  float lookAtRange;
  ResourceArray triggersEntering;
  ResourceArray triggersExiting;
  ResourceArray triggersIntersect;
  ResourceArray triggersLookingAt;
  ResourceArray triggersNotIntersect;
  ResourceArray triggersNotLookingAt;
  AITriggerBoxQuicksave aiTriggerBoxQuicksave;
};

struct AIWaypoint : ResourcePack {
  Vector pos;
  ResourceRef nextWaypoint;
  AITYPEID atTypeId;
  ResourceArray triggers;
};

struct AITriggerTriggerer {
  ResourceRef triggererEntityRef;
  ResourceRef triggererGroupRef;
  int32 triggererEntityId;
  AITYPEID triggererTypeId;
  void ReflectorTag();
};

struct AITrigger : ResourcePack {
  AITriggerTriggerer triggerer;
  int32 timesToTrigger;
  ResourceArray actions;
};

enum AIMBT {
  AIMBT_NONE,
  AIMBT_PLAYERWALL,
  AIMBT_LADDER,
  AIMBT_AVOIDANCE,
  AIMBT_BASEWALL,
  AIMBT_NOGRENADE,
  AIBMT_BUGFLYERZONE,
  AIBMT_FIREPRIORITY,
  AIBMT_MULTIPLAYERSPAWNPOINT,
  AIBMT_MULTIPLAYERTEAMSPAWNPOINT_1,
  AIBMT_MULTIPLAYERTEAMSPAWNPOINT_2,
};

struct AIMarkerBox : WorldObject {
  AIMBT type;
  float minX;
  float minY;
  float minZ;
  float maxX;
  float maxY;
  float maxZ;
  float angle;
  bool on;
  void ReflectorTag();
};

struct EventAIAction : ResourcePack {
  float eventTime;
  ResourceRef actionRef;
  ResourceRef triggererRef;
};

enum AIHST {
  AIHST_NONE,
  AIHST_ANY,
  AIHST_TROOPERDEFEND,
  AIHST_TROOPERATTACK,
};

struct AISquadTransients {
  int32 dummy;
  void ReflectorTag();
};

struct AISquad : WorldObject {
  AIGroupQuicksave aiGroupQuicksave;
  ResourceArray members;
  ResourceArray groupDeathAction;
  Vector position;
  float angle;
  AISQUADMODE squadMode;
  AISQUADFORMATION squadFormation;
  float squadFormationSpacing;
  ResourceRef nextWaypoint;
  ResourceRef prevWaypoint;
  ResourceRef followEntity;
  bool active;
  uint32 membersToWaitFor;
  AIHST searchHotspotType;
  float searchHotspotRadius;
  AISquadTransients transients;
  AISquadQuicksave aiSquadQuicksave;
};

struct AICounter : ResourcePack {
  int32 value;
};

struct AIHotspot : WorldObject {
  AIHST type;
  float posX;
  float posY;
  float posZ;
  float angleDegrees;
  bool kneeling;
  bool on;
  bool dropToGround;
  ResourceArray actions;
  AIHotspotQuicksave aiHotspotQuicksave;
};

struct AIMultiLinkWaypoint : ResourcePack {
  Vector pos;
  ResourceRef nextWaypoint;
  AITYPEID auTypeId;
  ResourceArray triggers;
  ResourceArray linkedWaypoints;
};

struct AIHeightMap : WorldObject {
  float minX;
  float minY;
  float minZ;
  float maxX;
  float maxY;
  float maxZ;
  float nodeSize;
  CollisionFlags collisionFlags;
  ResourceRef material;
};

struct AIEntityHealthAction : ResourcePack {
  ResourceArray actions;
  float triggerPercentage;
};

struct AISpawnerBase : WorldObject {
  ResourceArray spawnEntities;
  uint32 totalNumber;
  float spawnDelayMin;
  float spawnDelayMax;
  Angle spawnAngle;
  Angle spawnAngleRange;
  AABB aabb;
  ResourceRef nextWaypoint;
};

struct AISpawner : AISpawnerBase {
  ResourceRef spawnGroup;
};

struct AISpawnerVehicle : AISpawnerBase {
  AISpawnerVehicleQuicksave aiSpawnerVehicleQuicksave;
};

struct AILiftStateActions {
  ResourceRef atBottom;
  ResourceRef goingUp;
  ResourceRef atTop;
  ResourceRef goingDown;
  void ReflectorTag();
};

struct AILiftSoundEffects {
  ResourceRef goingUpStart;
  ResourceRef goingUpLoop;
  ResourceRef goingUpStop;
  ResourceRef goingDownStart;
  ResourceRef goingDownLoop;
  ResourceRef goingDownStop;
  int32 soundEffectBoneNumber;
  void ReflectorTag();
};

enum LIFTSTATE {
  LIFTSTATE_AT_BOTTOM,
  LIFTSTATE_GOING_UP,
  LIFTSTATE_AT_TOP,
  LIFTSTATE_GOING_DOWN,
  LIFTSTATE_NUM,
};

struct AILift : WorldObjectModel {
  ResourceRef animGoingUp;
  ResourceRef animGoingDown;
  AILiftStateActions stateActions;
  bool switchedOn;
  LIFTSTATE liftState;
  AILiftSoundEffects soundEffects;
  AILiftQuicksave aiLiftQuicksave;
  AILiftQuicksave quicksave;
};

struct AISpawnerSquad : AISpawnerBase {
  ResourceArray spawnSquads;
  AISpawnerVehicleQuicksave aiSpawnerSquadQuicksave;
};

struct AITriggerBoxOLD : ResourcePack {
  AABB aabb;
  bool active;
  ResourceArray actionLists;
  ResourceArray checkEntities;
  bool cameraCheck;
  float checkTime;
  AITriggerBoxQuicksave aiTriggerBoxOLDQuicksave;
};
