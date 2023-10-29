#include "quicksave/ai_base.hpp"
#include "world_base.hpp"
#include "enum_share.hpp"

struct AIEntityBase : ResourcePack {
  ResourceRef group;
  int32 memberId;
  bool active;
  bool dummyEntity;
  AIALERT alertState;
  AIMODE movementMode;
  ResourceRef nextWaypoint;
  ResourceRef prevWaypoint;
  bool stickToWaypoints;
  float health;
  float vunerability;
  float avoidance;
  float checkGradient;
  bool forcedTarget;
  ResourceRef target;
  ResourceArray healthActions;
  bool targettable;
};

struct AIEntityNonPhysicalPresenceAIEntity : AIEntityBase {
  AIEntityNonPhysicalPresenceAIEntityQuicksave quicksave;
};

struct AIEntity : AIEntityBase {
  AIEntityQuicksave quicksave;
  bool cosmeticVulnerability;
  void ReflectorTag();
};

struct AIWorldObject : WorldObjectModel {
  AIEntity aiEntity;
  ModelDetailDynamicQuicksave modelDetailDynamicquicksave;
};

struct AIEntityGenericAABB {
  float minX;
  float minY;
  float minZ;
  float maxX;
  float maxY;
  float maxZ;
  void ReflectorTag();
};

struct AiEntityGenericDamageType {
  int32 pierceBulletSoft;
  int32 pierceBulletHard;
  int32 blast;
  int32 slash;
  int32 punch;
  int32 heat;
  int32 corrosive;
  int32 electricity;
  int32 psiOps;
  void ReflectorTag();
};

struct AIFakeTarget : AIWorldObject {
  bool switchedOn;
  AIEntityGenericAABB aabb;
  AiEntityGenericDamageType damageType;
};

struct AIEntityGeneric : AIFakeTarget {
  std::string name;
  AIEntityGenericQuicksave aiEntityGenericQuicksave;
};
