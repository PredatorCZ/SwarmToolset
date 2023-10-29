#include "ai_base.hpp"
#include "quicksave/ai_bugs.hpp"

struct AIBugWarrior : AIWorldObject {
  std::string specialMode; // TODO string so far
  bool waypointsNarrow;
  bool movingZigZag;
  bool allowFastRun;
  bool cosmeticVulnerability;
  AIBugWarriorBaseQuicksave aiBugWarriorBaseQuicksave;
  ResourceRef overrideAnimSet;
};

struct AIBugWarriorTiger : AIBugWarrior {};

struct AIBugWarriorTigerSpit : AIBugWarrior {
  AIBugWarriorTigerSpitQuicksave aiBugWarriorTigerSpitQuicksave;
};

struct AIBugChariot : AIWorldObject {
  AIBugChariotQuicksave aiBugChariotQuicksave;
};

struct AIBugHopper : AIWorldObject {
  AIBugFlyerBaseQuicksave aiBugFlyerBaseQuicksave;
  AIBugHopperQuicksave aiBugHopperQuicksave;
};

struct AIBugPlasma : AIWorldObject {
  ResourceRef dustSystem;
  AIPBSM specialMode;
  AIBugPlasmaQuicksave aiBugPlasmaQuicksave;
  ResourceRef BossMode_Target1;
  ResourceRef BossMode_Target2;
};

struct AIBugBabyPlasma : AIWorldObject {
  AIBugBabyPlasmaSpecialMode specialMode;
  AIBugBabyPlasmaQuicksave aiBugBabyPlasmaQuicksave;
  ResourceRef dustSystem;
};

struct AIBugBlaster : AIWorldObject {
  bool useExtraJump;
  AIBugBlasterQuicksave aiBugBlasterQuicksave;
};

struct AIBugTankerBaby : AIWorldObject {
  std::string specialMode; // TODO figure out
  AIBugTankerBabyQuicksave aiBugTankerBabyQuicksave;
};

struct AIBugWarriorRoyalX : AIBugWarrior {
  ResourceArray leftShieldAction;
  ResourceArray rightShieldAction;
  ResourceArray leftEyeAction;
  ResourceArray rightEyeAction;
  AIBugWarriorRoyalXQuicksave aiBugWarriorRoyalXQuicksave;
};

enum AIFIREFLY {
  AIFIREFLY_FIRESPRAY,
  AIFIREFLY_FIREBALL,
};

struct AIBugHopperFirefly : AIWorldObject {
  AIBugFlyerBaseQuicksave aiBugFlyerBaseQuicksave;
  AIFIREFLY attackType;
  AIBugHopperFireflyQuicksave aiBugHopperFireflyQuicksave;
  ResourceRef dustSystem;
};

enum AISM {
  AISM_NONE,
  AISM_PLAYANIM,
  AISM_OUTOFGROUND,
  AISM_JUMP,
  AISM_BEENHIT,
  AISM_TANKERBUGL2,
  AISM_VEHICLELAND,
  AISM_VEHICLETAKEOFF,
  AISM_DROPSHIPFLYTOHOVER,
  AISM_DROPSHIPHOVER,
  AISM_DROPSHIPHOVERTOLAND,
  AISM_MANSTATICGUN,
};

struct AIBugRhino : AIWorldObject {
  AIBugRhinoQuicksave aiBugRhinoQuicksave;
  AISM specialMode;
  ResourceRef dustSystem;
};

struct AIBugCliffMite : AIWorldObject {
  AISM specialMode;
  AIBugCliffMiteQuicksave aiBugCliffMiteQuicksave;
};

struct AIBugHopperRippler : AIWorldObject {
  AIBugFlyerBaseQuicksave aiBugFlyerBaseQuicksave;
  AIBugHopperRipplerQuicksave aiBugHopperRipplerQuicksave;
};

struct AIBugWarriorRoyal : AIBugWarrior {
  ResourceArray leftShieldAction;
  ResourceArray rightShieldAction;
  ResourceArray leftEyeAction;
  ResourceArray rightEyeAction;
  AIBugWarriorRoyalQuicksave aiBugWarriorRoyalQuicksave;
};

struct AIBugWarriorTigerShard : AIBugWarrior {
  AIBugWarriorTigerShardQuicksave aiBugWarriorTigerShardQuicksave;
};

struct AIBugSentinel : AIWorldObject {
  ResourceArray flashActions;
  AIBugSentinelQuicksave aiBugSentinelQuicksave;
};

struct AIBugTanker : AIWorldObject {
  ResourceRef dustSystem;
  Vector initialDustPosition;
  ResourceRef l75HealthActionList;
  ResourceRef l50HealthActionList;
  ResourceRef l25HealthActionList;
  AIBugTankerQuicksave aiBugTankerQuicksave;
};
