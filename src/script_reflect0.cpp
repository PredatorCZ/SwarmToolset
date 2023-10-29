#include "script/ai_action.hpp"
#include "script/ai_bugs.hpp"
#include "script/ai_human.hpp"
#include "script/ai_objects.hpp"
#include "script/ai_util.hpp"
#include "script/ai_veapon.hpp"
#include "script/ai_vehicles.hpp"

#include "spike/reflect/detail/reflector_class.hpp"
#include "spike/reflect/detail/reflector_enum.hpp"

// clang-format off
REFLECT(ENUMERATION(STANDARD_POSE),
ENUM_MEMBER(STANDARD_POSE_NONE),
ENUM_MEMBER(STANDARD_POSE_OUTOFPLACE_DO_NOT_USE),
ENUM_MEMBER(STANDARD_POSE_IDLE),
ENUM_MEMBER(STANDARD_POSE_IDLE_BLIND),
ENUM_MEMBER(STANDARD_POSE_ALERT),
ENUM_MEMBER(STANDARD_POSE_ALERT_BLIND),
ENUM_MEMBER(STANDARD_POSE_ALERT_KNEELING),
ENUM_MEMBER(STANDARD_POSE_KNEELING_BLIND),
ENUM_MEMBER(STANDARD_POSE_FIRE_STOOD),
ENUM_MEMBER(STANDARD_POSE_FIRE_TURN),
ENUM_MEMBER(STANDARD_POSE_FIRE_STOOD_ATTRACT),
ENUM_MEMBER(STANDARD_POSE_FIRE_STOOD_GRENADE),
ENUM_MEMBER(STANDARD_POSE_FIRE_KNEELING),
ENUM_MEMBER(STANDARD_POSE_FIRE_KNEELING_TURN),
ENUM_MEMBER(STANDARD_POSE_FIRE_KNEELING_ATTRACT),
ENUM_MEMBER(STANDARD_POSE_FIRE_KNEELING_GRENADE),
ENUM_MEMBER(STANDARD_POSE_STATICGUN_FIRE),
ENUM_MEMBER(STANDARD_POSE_DUCK),
ENUM_MEMBER(STANDARD_POSE_HURT_STAND),
ENUM_MEMBER(STANDARD_POSE_HURT_KNEEL),
ENUM_MEMBER(STANDARD_POSE_DIE),
ENUM_MEMBER(STANDARD_POSE_DIE_FLYING),
ENUM_MEMBER(STANDARD_POSE_DROPSHIPFALL),
ENUM_MEMBER(STANDARD_POSE_ANIMLOOP)
);

REFLECT(ENUMERATION(AIMODE),
ENUM_MEMBER(AIMODE_STILL),
ENUM_MEMBER(AIMODE_MOVING),
ENUM_MEMBER(AIMODE_FIGHTING),
ENUM_MEMBER(AIMODE_IMMOBILE),
ENUM_MEMBER(AIMODE_DYING),
ENUM_MEMBER(AIMODE_RAGDOLL),
ENUM_MEMBER(AIMODE_DEAD),
ENUM_MEMBER(AIMODE_DESTROYED)
);

REFLECT(ENUMERATION(AIHUMAN),
ENUM_MEMBER(AIHUMAN_NOTYPE),
ENUM_MEMBER(AIHUMAN_PLAYER),
ENUM_MEMBER(AIHUMAN_TROOPER_GRUNT),
ENUM_MEMBER(AIHUMAN_TROOPER_MARAUDER),
ENUM_MEMBER(AIHUMAN_TROOPER_MEDIC),
ENUM_MEMBER(AIHUMAN_TROOPER_MECHANIC),
ENUM_MEMBER(AIHUMAN_TROOPER_SERGEANT),
ENUM_MEMBER(AIHUMAN_TROOPER_PSYOP),
ENUM_MEMBER(AIHUMAN_TROOPER_COMMS),
ENUM_MEMBER(AIHUMAN_PILOT),
ENUM_MEMBER(AIHUMAN_ACTOR),
ENUM_MEMBER(AIHUMAN_MULTIPLAYER__DO_NOT_USE),
ENUM_MEMBER(AIHUMAN_MAX_TYPES__DO_NOT_USE)
);

REFLECT(ENUMERATION(AIWEAPMODE),
ENUM_MEMBER(AIWEAPMODE_NOOWNER),
ENUM_MEMBER(AIWEAPMODE_PICKUP),
ENUM_MEMBER(AIWEAPMODE_INHAND),
ENUM_MEMBER(AIWEAPMODE_FIRE1),
ENUM_MEMBER(AIWEAPMODE_FIRE2),
ENUM_MEMBER(AIWEAPMODE_MODE12),
ENUM_MEMBER(AIWEAPMODE_INHAND2),
ENUM_MEMBER(AIWEAPMODE_MODE21),
ENUM_MEMBER(AIWEAPMODE_RELOAD),
ENUM_MEMBER(AIWEAPMODE_OFFSCREEN1),
ENUM_MEMBER(AIWEAPMODE_OFFSCREEN2),
ENUM_MEMBER(AIWEAPMODE_OFFSCREEN3),
ENUM_MEMBER(AIWEAPMODE_PUTONBACK),
ENUM_MEMBER(AIWEAPMODE_STOWED),
ENUM_MEMBER(AIWEAPMODE_TAKEOFFBACK),
ENUM_MEMBER(AIWEAPMODE_THROWAWAY),
ENUM_MEMBER(AIWEAPMODE_OBSTRUCTED_PUTONBACK),
ENUM_MEMBER(AIWEAPMODE_OBSTRUCTED_STOWED),
ENUM_MEMBER(AIWEAPMODE_OBSTRUCTED_TAKEOFFBACK)
);

REFLECT(ENUMERATION(BLEND),
ENUM_MEMBER(BLEND_ZERO),
ENUM_MEMBER(BLEND_ONE),
ENUM_MEMBER(BLEND_SRCCOLOR),
ENUM_MEMBER(BLEND_INVSRCCOLOR),
ENUM_MEMBER(BLEND_SRCALPHA),
ENUM_MEMBER(BLEND_INVSRCALPHA),
ENUM_MEMBER(BLEND_DESTALPHA),
ENUM_MEMBER(BLEND_INVDESTALPHA),
ENUM_MEMBER(BLEND_DESTCOLOR),
ENUM_MEMBER(BLEND_INVDESTCOLOR),
ENUM_MEMBER(BLEND_SRCALPHASAT),
ENUM_MEMBER(BLEND_BOTHSRCALPHA),
ENUM_MEMBER(BLEND_BOTHINVSRCALPHA),
ENUM_MEMBER(BLEND_BLENDFACTOR),
ENUM_MEMBER(BLEND_INVBLENDFACTOR)
);

REFLECT(ENUMERATION(AITYPEID),
ENUM_MEMBER(AITYPEID_NULL),
ENUM_MEMBER(AITYPEID_ENTITY),
ENUM_MEMBER(AITYPEID_CAMERA),
ENUM_MEMBER(AITYPEID_HUMAN),
ENUM_MEMBER(AITYPEID_PLAYER),
ENUM_MEMBER(AITYPEID_VEHICLE),
ENUM_MEMBER(AITYPEID_FLYINGVEHICLE),
ENUM_MEMBER(AITYPEID_BOMBER),
ENUM_MEMBER(AITYPEID_DROPSHIP),
ENUM_MEMBER(AITYPEID_DROPSHIPGRUNT),
ENUM_MEMBER(AITYPEID_DROPSHIPMARAUDER),
ENUM_MEMBER(AITYPEID_DROPSHIPCARGO),
ENUM_MEMBER(AITYPEID_BUG),
ENUM_MEMBER(AITYPEID_BUGWALKER),
ENUM_MEMBER(AITYPEID_BUGWARRIORBASE),
ENUM_MEMBER(AITYPEID_BUGWARRIOR),
ENUM_MEMBER(AITYPEID_BUGTIGER),
ENUM_MEMBER(AITYPEID_BUGTIGERSHARD),
ENUM_MEMBER(AITYPEID_BUGTIGERSPIT),
ENUM_MEMBER(AITYPEID_BUGROYAL),
ENUM_MEMBER(AITYPEID_BUGROYALX),
ENUM_MEMBER(AITYPEID_BUGRHINO),
ENUM_MEMBER(AITYPEID_BUGBABYTANKER),
ENUM_MEMBER(AITYPEID_BUGBABYPLASMA),
ENUM_MEMBER(AITYPEID_BUGBLASTER),
ENUM_MEMBER(AITYPEID_BUGCHARIOT),
ENUM_MEMBER(AITYPEID_BUGFLYER),
ENUM_MEMBER(AITYPEID_BUGHOPPER),
ENUM_MEMBER(AITYPEID_BUGHOPPERFIREFLY),
ENUM_MEMBER(AITYPEID_BUGHOPPERRIPPLER),
ENUM_MEMBER(AITYPEID_BUGTANKER),
ENUM_MEMBER(AITYPEID_BUGPLASMA),
ENUM_MEMBER(AITYPEID_BUGCLIFFMITE),
ENUM_MEMBER(AITYPEID_BUGSENTINEL),
ENUM_MEMBER(AITYPEID_BUGBRAIN),
ENUM_MEMBER(AITYPEID_FAKETARGET),
ENUM_MEMBER(AITYPEID_ENTITYGENERIC),
ENUM_MEMBER(AITYPEID_NONPHYSICALENTITY),
ENUM_MEMBER(AITYPEID_NUM)
);

REFLECT(ENUMERATION(AISQUADMODE),
ENUM_MEMBER(AISQUADMODE_STILL),
ENUM_MEMBER(AISQUADMODE_MOVING),
ENUM_MEMBER(AISQUADMODE_FOLLOWONPATH),
ENUM_MEMBER(AISQUADMODE_FOLLOWFREE),
ENUM_MEMBER(AISQUADMODE_MEMBERSFOLLOWPATHS),
ENUM_MEMBER(AISQUADMODE_GOTOHOTSPOTS_DONTUSE),
ENUM_MEMBER(AISQUADMODE_DISEMBARK)
);

REFLECT(ENUMERATION(AIHSM),
ENUM_MEMBER(AIHSM_NONE),
ENUM_MEMBER(AIHSM_PLAYANIM),
ENUM_MEMBER(AIHSM_PLAYANIMLOOP),
ENUM_MEMBER(AIHSM_THROWGRENADE),
ENUM_MEMBER(AIHSM_MANSTATICGUN),
ENUM_MEMBER(AIHSM_FLYING),
ENUM_MEMBER(AIHSM_DROPSHIP),
ENUM_MEMBER(AIHSM_SENTRY),
ENUM_MEMBER(AIHSM_TURN),
ENUM_MEMBER(AIHSM_LOOKPLAYER)
);

REFLECT(ENUMERATION(AIWT),
ENUM_MEMBER(AIWT_MORITIA_MK4),
ENUM_MEMBER(AIWT_MORITIA_MK2_SHOTGUN),
ENUM_MEMBER(AIWT_MORITIA_MK2_GRENADE),
ENUM_MEMBER(AIWT_HEAVY_SHOTGUN),
ENUM_MEMBER(AIWT_MORITIA_MK2_ZOOM),
ENUM_MEMBER(AIWT_MORITIA_MK2_CARBINE),
ENUM_MEMBER(AIWT_ROCKET_LAUNCHER),
ENUM_MEMBER(AIWT_RAILGUN),
ENUM_MEMBER(AIWT_MISSILE_LAUNCHER),
ENUM_MEMBER(AIWT_PSIOP_FAKE),
ENUM_MEMBER(AIWT_NUMCARRIEDWEAPS),
ENUM_MEMBER(AIWT_STATIC_SINGLE),
ENUM_MEMBER(AIWT_STATIC_DOUBLE),
ENUM_MEMBER(AIWT_STATIC_NUKE),
ENUM_MEMBER(AIWT_NONE),
ENUM_MEMBER(AIWT_NUM)
);

REFLECT(ENUMERATION(AIALERT),
ENUM_MEMBER(AIALERT_IDLE),
ENUM_MEMBER(AIALERT_ALERT),
ENUM_MEMBER(AIALERT_ATTACK),
ENUM_MEMBER(AIALERT_IGNORE)
);

REFLECT(ENUMERATION(SWITCHSTATE),
ENUM_MEMBER(SWITCHSTATE_OFF),
ENUM_MEMBER(SWITCHSTATE_SWITCHINGON),
ENUM_MEMBER(SWITCHSTATE_ON),
ENUM_MEMBER(SWITCHSTATE_SWITCHINGOFF),
ENUM_MEMBER(SWITCHSTATE_NUM)
);

REFLECT(ENUMERATION(PICKUP),
ENUM_MEMBER(PICKUP_HEALTH),
ENUM_MEMBER(PICKUP_POWERCELL),
ENUM_MEMBER(PICKUP_KEYCARD),
ENUM_MEMBER(PICKUP_MINELAYERS),
ENUM_MEMBER(PICKUP_EXPLOSIVES)
);

REFLECT(ENUMERATION(DOORSTATE),
ENUM_MEMBER(DOORSTATE_CLOSED),
ENUM_MEMBER(DOORSTATE_OPENING),
ENUM_MEMBER(DOORSTATE_OPENED),
ENUM_MEMBER(DOORSTATE_CLOSING),
ENUM_MEMBER(DOORSTATE_NUM)
);

REFLECT(ENUMERATION(AIMBT),
ENUM_MEMBER(AIMBT_NONE),
ENUM_MEMBER(AIMBT_PLAYERWALL),
ENUM_MEMBER(AIMBT_LADDER),
ENUM_MEMBER(AIMBT_AVOIDANCE),
ENUM_MEMBER(AIMBT_BASEWALL),
ENUM_MEMBER(AIMBT_NOGRENADE),
ENUM_MEMBER(AIBMT_BUGFLYERZONE),
ENUM_MEMBER(AIBMT_FIREPRIORITY),
ENUM_MEMBER(AIBMT_MULTIPLAYERSPAWNPOINT),
ENUM_MEMBER(AIBMT_MULTIPLAYERTEAMSPAWNPOINT_1),
ENUM_MEMBER(AIBMT_MULTIPLAYERTEAMSPAWNPOINT_2)
);

REFLECT(ENUMERATION(AISQUADFORMATION),
ENUM_MEMBER(AISQUADFORMATION_ARROWHEAD),
ENUM_MEMBER(AISQUADFORMATION_DIAMOND),
ENUM_MEMBER(AISQUADFORMATION_SINGLEFILE),
ENUM_MEMBER(AISQUADFORMATION_LINE),
ENUM_MEMBER(AISQUADFORMATION_GRUNTDROPSHIP_ON),
ENUM_MEMBER(AISQUADFORMATION_GRUNTDROPSHIP_OFF),
ENUM_MEMBER(AISQUADFORMATION_NUMTYPES__DO_NOT_USE)
);

REFLECT(ENUMERATION(AIHST),
ENUM_MEMBER(AIHST_NONE),
ENUM_MEMBER(AIHST_ANY),
ENUM_MEMBER(AIHST_TROOPERDEFEND),
ENUM_MEMBER(AIHST_TROOPERATTACK)
);

REFLECT(ENUMERATION(AIPROJ),
ENUM_MEMBER(AIPROJ_BABYPLASMABOLT),
ENUM_MEMBER(AIPROJ_BABYTANKERFIREBALL),
ENUM_MEMBER(AIPROJ_PLASMABOLT),
ENUM_MEMBER(AIPROJ_FLARE),
ENUM_MEMBER(AIPROJ_BOMB),
ENUM_MEMBER(AIPROJ_NAPALM),
ENUM_MEMBER(AIPROJ_TIGERSHARD),
ENUM_MEMBER(AIPROJ_TIGERSPIT),
ENUM_MEMBER(AIPROJ_BLASTER),
ENUM_MEMBER(AIPROJ_CLIFFMITE),
ENUM_MEMBER(AIPROJ_NUM)
);

REFLECT(ENUMERATION(AIPBSM),
ENUM_MEMBER(AIPBSM_COWER),
ENUM_MEMBER(AIPBSM_FIREPROJECTILE),
ENUM_MEMBER(AIPBSM_TRACKPLAYER)
);

REFLECT(ENUMERATION(AIFVSM),
ENUM_MEMBER(AIFVSM_NONE),
ENUM_MEMBER(AIFVSM_OLDLANDING),
ENUM_MEMBER(AIFVSM_OLDLANDED),
ENUM_MEMBER(AIFVSM_OLDTAKEOFF),
ENUM_MEMBER(AIFVSM_OLDFLYTOHOVER),
ENUM_MEMBER(AIFVSM_OLDHOVER),
ENUM_MEMBER(AIFVSM_OLDHOVERTOLAND),
ENUM_MEMBER(AIFVSM_DECEL),
ENUM_MEMBER(AIFVSM_DESCEND),
ENUM_MEMBER(AIFVSM_LOITER),
ENUM_MEMBER(AIFVSM_LOITERMOVE),
ENUM_MEMBER(AIFVSM_ASCEND),
ENUM_MEMBER(AIFVSM_ACCEL)
);

REFLECT(ENUMERATION(AIBugBabyPlasmaSpecialMode),
ENUM_MEMBER(NONE),
ENUM_MEMBER(OUTOFGROUND),
ENUM_MEMBER(MULTIWAYPOINT_NETWORK)
);

REFLECT(CLASS(CollisionFlags),
MEMBER(bullet, "COLTYPE_TERRAIN"),
MEMBER(bullet, "COLTYPE_BULLET"),
MEMBER(object, "COLTYPE_OBJECT"),
MEMBER(aiwalk, "COLTYPE_AIWALK"),
MEMBER(player, "COLTYPE_PLAYER"),
MEMBER(sight, "COLTYPE_SIGHT"),
MEMBER(bullet, "COLTYPE_EFENCE"),
MEMBER(bullet, "COLTYPE_PARTICLE"));

FWDREFLECTCLASS(ResourceRef);

REFLECT(CLASS(Matrix),
MEMBER(v[0].x, "m11"),
MEMBER(v[0].y, "m12"),
MEMBER(v[0].z, "m13"),
MEMBER(v[0].w, "m14"),
MEMBER(v[1].x, "m21"),
MEMBER(v[1].y, "m22"),
MEMBER(v[1].z, "m23"),
MEMBER(v[1].w, "m24"),
MEMBER(v[2].x, "m31"),
MEMBER(v[2].y, "m32"),
MEMBER(v[2].z, "m33"),
MEMBER(v[2].w, "m34"),
MEMBER(v[3].x, "m41"),
MEMBER(v[3].y, "m42"),
MEMBER(v[3].z, "m43"),
MEMBER(v[3].w, "m44")
);

REFLECT(BASEDCLASS(AIWorldObject, AIBugWarrior),
MEMBER(specialMode, "Special_Mode"),
MEMBER(waypointsNarrow, "Waypoints_Narrow"),
MEMBER(movingZigZag, "Moving_ZigZag"),
MEMBER(allowFastRun, "Allow_Fast_Run"),
MEMBER(cosmeticVulnerability, "Cosmetic_Vulnerability"),
MEMBER(overrideAnimSet, "Override_AnimSet"),
MEMBER(aiBugWarriorBaseQuicksave,"QUICKSAVE_AIBugWarriorBase"));

REFLECT(BASEDCLASS(AIBugWarrior, AIBugWarriorTigerSpit),
MEMBER(aiBugWarriorTigerSpitQuicksave,"QUICKSAVE_AIBugWarriorTigerSpit"));

REFLECT(BASEDCLASS(AIBugWarrior, AIBugWarriorTiger));

REFLECT(BASEDCLASS(AIWorldObject, AIBugChariot),
MEMBER(aiBugChariotQuicksave,"QUICKSAVE_AIBugChariot"));

REFLECT(BASEDCLASS(AIWorldObject, AIBugHopper),
MEMBER(aiBugFlyerBaseQuicksave,"QUICKSAVE_AIBugFlyerBase"),
MEMBER(aiBugHopperQuicksave,"QUICKSAVE_AIBugHopper"));

REFLECT(BASEDCLASS(AIWorldObject, AIBugPlasma),
MEMBER(dustSystem, "Dust_System"),
MEMBER(specialMode, "Special_Mode"),
MEMBER(aiBugPlasmaQuicksave,"QUICKSAVE_AIBugPlasma"),
MEMBER(BossMode_Target1, "BossMode_Target1"),
MEMBER(BossMode_Target2, "BossMode_Target2"));

REFLECT(BASEDCLASS(AIWorldObject, AIBugBabyPlasma),
MEMBER(specialMode, "Special_Mode"),
MEMBER(aiBugBabyPlasmaQuicksave,"QUICKSAVE_AIBugBabyPlasma"),
MEMBER(dustSystem, "Dust_System"));

REFLECT(BASEDCLASS(AIWorldObject, AIBugBlaster),
MEMBER(useExtraJump, "UseExtraJump"),
MEMBER(aiBugBlasterQuicksave,"QUICKSAVE_AIBugBlaster"));

REFLECT(BASEDCLASS(AIWorldObject, AIBugTankerBaby),
MEMBER(specialMode, "Special_Mode"),
MEMBER(aiBugTankerBabyQuicksave,"QUICKSAVE_AIBugTankerBaby"));

REFLECT(BASEDCLASS(AIBugWarrior, AIBugWarriorRoyalX),
MEMBER(leftShieldAction,"LeftShieldAction"),
MEMBER(rightShieldAction,"RightShieldAction"),
MEMBER(leftEyeAction,"LeftEyeAction"),
MEMBER(rightEyeAction,"RightEyeAction"),
MEMBER(aiBugWarriorRoyalXQuicksave,"QUICKSAVE_AIBugWarriorRoyalX"));

REFLECT(BASEDCLASS(ResourcePack, WorldObject),
MEMBER(lockedContext,"LockedContext"),
MEMBER(debugContext,"DebugContext"),
MEMBER(worldObjectQuicksave,"QUICKSAVE_WorldObject"));

REFLECT(CLASS(Angle),
MEMBER(heading, "Heading"),
MEMBER(pitch, "Pitch"),
MEMBER(roll, "Roll")
);

REFLECT(BASEDCLASS(WorldObject, WorldObjectModel),
MEMBER(resourceRef, "ResourceRef"),
MEMBER(position, "Position"),
MEMBER(angle, "Angle"),
MEMBER(render, "Render"),
MEMBER(shadowAtlasCaster, "ShadowAtlasCaster"),
MEMBER(shadowAtlasReceiver, "ShadowAtlasReceiver"),
MEMBER(shaderOverrides, "ShaderOverrides")
);

REFLECT(BASEDCLASS(WorldObjectModel, ModelDetailDynamic),
MEMBER(active, "Active"),
MEMBER(beingControlled, "BeingControlled"),
MEMBER(hasBeenControlled, "HasBeenControlled"),
MEMBER(movable, "Movable"),
MEMBER(breakoutForce, "Breakout_Force"),
MEMBER(density, "Density"),
MEMBER(flamable, "Flamable"),
MEMBER(explosive, "Explosive"),
MEMBER(modelDetailDynamicquicksave,"QUICKSAVE_ModelDetailDynamic"));

REFLECT(BASEDCLASS(ResourcePack, AIAction),
MEMBER(percentChance,"Percent_Chance"),
MEMBER(delayMin,"Delay_Min"),
MEMBER(delayMax,"Delay_Max"));

REFLECT(BASEDCLASS(AIAction, AIActionList),
MEMBER(actions,"Actions"));

REFLECT(BASEDCLASS(AIAction, AIA_Dropship_SetFlightSpeed),
MEMBER(target, "Target"),
MEMBER(speed1Slow2Medium3Fast, "Speed__1_Slow__2_Medium__3_Fast"));

REFLECT(BASEDCLASS(AIAction, AIA_Bomber_DropBomb),
MEMBER(bomber, "Bomber"),
MEMBER(target, "Target"),
MEMBER(napalm, "Napalm"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_Kill),
MEMBER(target, "Target"),
MEMBER(setOnFire, "SetOnFire"),
MEMBER(gib, "Gib"),
MEMBER(gibForce, "GibForce"));

REFLECT(BASEDCLASS(AIAction, AIA_Dropship_Descend),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_SetViewFade),
MEMBER(active, "Active"),
MEMBER(startColour, "StartColour"),
MEMBER(endColour, "EndColour"),
MEMBER(duration, "Duration"),
MEMBER(blur, "Blur"),
MEMBER(fadeBackToStart, "FadeBackToStart"),
MEMBER(holdDuration, "HoldDuration"));

REFLECT(BASEDCLASS(AIAction, AIA_SetAsViewpoint),
MEMBER(entity, "Entity"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_SetVunerability),
MEMBER(target, "Target"),
MEMBER(vunerability, "Vunerability"));

REFLECT(BASEDCLASS(AIAction, AIA_Group_ApplyActions),
MEMBER(targetGroup, "Target_Group"),
MEMBER(allMembers, "All_Members"),
MEMBER(randomMember, "Random_Member"),
MEMBER(memberId, "Member_ID"),
MEMBER(actions, "Actions"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_PlayAnimLoop),
MEMBER(target, "Target"),
MEMBER(animation, "Animation"),
MEMBER(animationSet, "AnimationSet"),
MEMBER(standardPose, "Standard_Pose"),
MEMBER(playImmediately, "PlayImmediately"),
MEMBER(maxTime, "Max_Time"),
MEMBER(maxRepetitions, "Max_Repetitions"),
MEMBER(SetVulnerableDuring, "SetVulnerableDuring"),
MEMBER(VulnerabilityDuring, "VulnerabilityDuring"),
MEMBER(SetVulnerableAfter, "SetVulnerableAfter"),
MEMBER(VulnerabilityAfter, "VulnerabilityAfter"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_ForcePos),
MEMBER(target, "Target"),
MEMBER(position, "Position"));

REFLECT(BASEDCLASS(AIAction, AIA_Model_SetRender),
MEMBER(target, "Target"),
MEMBER(render, "Render"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_ForceAngle),
MEMBER(target, "Target"),
MEMBER(angle, "Angle"));

REFLECT(BASEDCLASS(AIAction, AIA_Player_SetVelFactor),
MEMBER(target, "Target"),
MEMBER(speedFactorPercent, "SpeedFactor_Percent"));

REFLECT(BASEDCLASS(AIAction, AIA_QueueSpeech),
MEMBER(chatScript, "ChatScript"));

REFLECT(BASEDCLASS(AIAction, AIA_PlayAnim),
MEMBER(target, "Target"),
MEMBER(animation, "Animation"),
MEMBER(setVulnerableDuring, "SetVulnerableDuring"),
MEMBER(vulnerabilityDuring, "VulnerabilityDuring"),
MEMBER(setVulnerableAfter, "SetVulnerableAfter"),
MEMBER(vulnerabilityAfter, "VulnerabilityAfter"),
MEMBER(useCurrentAngle, "UseCurrentAngle"));

REFLECT(BASEDCLASS(AIAction, AIA_LaunchMenu),
MEMBER(menuName, "MenuName"));

REFLECT(BASEDCLASS(AIAction, AIA_PlaySound),
MEMBER(target, "Target"),
MEMBER(source, "Source"),
MEMBER(soundBone, "SoundBone"));

REFLECT(BASEDCLASS(AIAction, AIA_EnableSpeechBank),
MEMBER(enable, "Enable"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_SetWaypoint),
MEMBER(target, "Target"),
MEMBER(waypoint, "Waypoint"));

REFLECT(BASEDCLASS(AIAction, AIA_SwitchOnOff),
MEMBER(target, "Target"),
MEMBER(switchState, "Switch"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_SetMode),
MEMBER(target, "Target"),
MEMBER(mode, "Mode"));

REFLECT(BASEDCLASS(ResourcePack, AIEntityBase),
MEMBER(group,"Group"),
MEMBER(memberId, "MemberID"),
MEMBER(active,"Active"),
MEMBER(dummyEntity,"DummyEntity"),
MEMBER(alertState,"AlertState"),
MEMBER(movementMode,"MovementMode"),
MEMBER(nextWaypoint,"Next_Waypoint"),
MEMBER(prevWaypoint,"Prev_Waypoint"),
MEMBER(stickToWaypoints,"Stick_To_Waypoints"),
MEMBER(health,"Health"),
MEMBER(vunerability,"Vunerability"),
MEMBER(avoidance,"Avoidance"),
MEMBER(checkGradient, "CheckGradient"),
MEMBER(forcedTarget,"ForcedTarget"),
MEMBER(target,"Target"),
MEMBER(healthActions,"HealthActions"),
MEMBER(targettable,"Targettable"));

REFLECT(BASEDCLASS(AIEntityBase, AIEntityNonPhysicalPresenceAIEntity),
MEMBER(quicksave, "QUICKSAVE_AIEntity"));

REFLECT(BASEDCLASS(AIEntityBase, AIEntity),
MEMBER(quicksave, "QUICKSAVE_AIEntity"),
MEMBER(cosmeticVulnerability, "CosmeticVulnerability"));

REFLECT(BASEDCLASS(WorldObjectModel, AIWorldObject),
MEMBER(aiEntity, "AIEntity"),
MEMBER(modelDetailDynamicquicksave,"QUICKSAVE_ModelDetailDynamic"));

REFLECT(CLASS(AIEntityGenericAABB),
MEMBER(minX, "Min_X"),
MEMBER(minY, "Min_Y"),
MEMBER(minZ, "Min_Z"),
MEMBER(maxX, "Max_X"),
MEMBER(maxY, "Max_Y"),
MEMBER(maxZ, "Max_Z"));

REFLECT(CLASS(AiEntityGenericDamageType),
MEMBER(pierceBulletSoft, "PierceBulletSoft"),
MEMBER(pierceBulletHard, "PierceBulletHard"),
MEMBER(blast, "Blast"),
MEMBER(slash, "Slash"),
MEMBER(punch, "Punch"),
MEMBER(heat, "Heat"),
MEMBER(corrosive, "Corrosive"),
MEMBER(electricity, "Electricity"),
MEMBER(psiOps, "PsiOps"));

REFLECT(BASEDCLASS(AIWorldObject, AIFakeTarget),
MEMBER(switchedOn, "SwitchedOn"),
MEMBER(aabb, "AABB"),
MEMBER(damageType, "DamageType"));

REFLECT(BASEDCLASS(AIFakeTarget, AIEntityGeneric),
MEMBER(name, "Name"),
MEMBER(aiEntityGenericQuicksave,"QUICKSAVE_AIEntityGeneric"));

REFLECT(CLASS(AABB),
MEMBER(min, "Min"),
MEMBER(max, "Max"));

REFLECT(CLASS(Resource),
MEMBER(__guid, "__GUID"));

REFLECT(BASEDCLASS(Resource, ResourcePack),
MEMBER(package, "Package"));

REFLECT(BASEDCLASS(ResourcePack, AIEntityNonPhysicalPresence),
MEMBER(resourceRef, "ResourceRef"),
MEMBER(shaderOverrides,"ShaderOverrides"),
MEMBER(position, "Position"),
MEMBER(angle, "Angle"),
MEMBER(render, "Render"),
MEMBER(debugContext, "DebugContext"),
MEMBER(aiEntity, "AIEntity"),
MEMBER(name, "Name"));

REFLECT(CLASS(AISpawnGroupSpawning),
MEMBER(spawners,"Spawners"),
MEMBER(maxNumberActive, "Max_Number_Active"),
MEMBER(numberInWave, "Number_in_Wave"),
MEMBER(respawnDelayMin, "Respawn_Delay_Min"),
MEMBER(respawnDelayMax, "Respawn_Delay_Max"),
MEMBER(maxNumberActiveLowFPS, "Max_Number_Active_LowFPS"));

REFLECT(BASEDCLASS(WorldObject, AISpawnGroup),
MEMBER(aiGroupQuicksave,"QUICKSAVE_AIGroup"),
MEMBER(spawning, "Spawning"),
MEMBER(aabb, "AABB"),
MEMBER(startWaypoint, "StartWaypoint"),
MEMBER(aiSpawnGroupQuicksave,"QUICKSAVE_AISpawnGroup"),
MEMBER(members, "Members"),
MEMBER(groupDeathAction, "GroupDeathAction"));

REFLECT(BASEDCLASS(ResourcePack, AITriggerBox),
MEMBER(aabb, "AABB"),
MEMBER(active, "Active"),
MEMBER(checkTime, "CheckTime"),
MEMBER(lookAtRange, "LookAtRange"),
MEMBER(aiTriggerBoxQuicksave,"QUICKSAVE_AITriggerBox"),
MEMBER(triggersEntering, "Triggers_Entering"),
MEMBER(triggersExiting, "Triggers_Exiting"),
MEMBER(triggersIntersect, "Triggers_Intersect"),
MEMBER(triggersLookingAt, "Triggers_LookingAt"),
MEMBER(triggersNotIntersect, "Triggers_NotIntersect"),
MEMBER(triggersNotLookingAt, "Triggers_NotLookingAt"));

REFLECT(BASEDCLASS(ResourcePack, AIWaypoint),
MEMBER(pos, "Pos"),
MEMBER(nextWaypoint, "NextWaypoint"),
MEMBER(atTypeId, "AI_TypeID"),
MEMBER(triggers, "Triggers")
);

REFLECT(CLASS(AITriggerTriggerer),
MEMBER(triggererEntityRef, "TriggererEntity_Ref"),
MEMBER(triggererGroupRef, "TriggererGroup_Ref"),
MEMBER(triggererEntityId, "TriggererEntity_ID"),
MEMBER(triggererTypeId, "TriggererType_ID"));

REFLECT(BASEDCLASS(ResourcePack, AITrigger),
MEMBER(triggerer, "Triggerer"),
MEMBER(timesToTrigger, "TimesToTrigger"),
MEMBER(actions,"Actions")
);

REFLECT(BASEDCLASS(AISpawnerBase, AISpawner),
MEMBER(totalNumber, "Total_Number"),
MEMBER(spawnDelayMin, "Spawn_Delay_Min"),
MEMBER(spawnDelayMax, "Spawn_Delay_Max"),
MEMBER(spawnAngleRange, "Spawn_Angle"),
MEMBER(spawnAngleRange, "Spawn_Angle_Range"),
MEMBER(aabb, "AABB"),
MEMBER(nextWaypoint, "Next_Waypoint"),
MEMBER(spawnGroup, "SpawnGroup"));

REFLECT(BASEDCLASS(WorldObject, AIMarkerBox),
MEMBER(type, "Type"),
MEMBER(minX, "Min_X"),
MEMBER(minY, "Min_Y"),
MEMBER(minZ, "Min_Z"),
MEMBER(maxX, "Max_X"),
MEMBER(maxX, "Max_Y"),
MEMBER(maxX, "Max_Z"),
MEMBER(angle, "Angle"),
MEMBER(on, "On"));

REFLECT(BASEDCLASS(ResourcePack, EventAIAction),
MEMBER(eventTime, "EventTime"),
MEMBER(actionRef, "ActionRef"),
MEMBER(triggererRef, "TriggererRef"));

REFLECT(CLASS(AISquadTransients),
MEMBER(dummy, "Dummy"));

REFLECT(BASEDCLASS(WorldObject, AISquad),
MEMBER(aiGroupQuicksave,"QUICKSAVE_AIGroup"),
MEMBER(members, "Members"),
MEMBER(position, "Position"),
MEMBER(angle, "Angle"),
MEMBER(squadMode, "Squad_Mode"),
MEMBER(squadFormation, "Squad_Formation"),
MEMBER(squadFormationSpacing, "Squad_Formation_Spacing"),
MEMBER(nextWaypoint, "Next_Waypoint"),
MEMBER(prevWaypoint, "Prev_Waypoint"),
MEMBER(followEntity, "FollowEntity"),
MEMBER(groupDeathAction,"GroupDeathAction"),
MEMBER(active, "Active"),
MEMBER(membersToWaitFor, "MembersToWaitFor"),
MEMBER(searchHotspotType, "SearchHotspotType"),
MEMBER(searchHotspotRadius, "SearchHotspotRadius"),
MEMBER(transients, "Transients"),
MEMBER(aiSquadQuicksave,"QUICKSAVE_AISquad"));

REFLECT(BASEDCLASS(ResourcePack, AICounter),
MEMBER(value, "Value"));

REFLECT(BASEDCLASS(WorldObject, AIHotspot),
MEMBER(type, "Type"),
MEMBER(posX, "Pos_X"),
MEMBER(posY, "Pos_Y"),
MEMBER(posZ, "Pos_Z"),
MEMBER(angleDegrees, "AngleDegrees"),
MEMBER(kneeling, "Kneeling"),
MEMBER(on, "On"),
MEMBER(dropToGround, "DropToGround"),
MEMBER(actions, "Actions"),
MEMBER(aiHotspotQuicksave,"QUICKSAVE_AIHotspot"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIBomber),
MEMBER(aiEntity, "AIEntity"),
MEMBER(aiFlyingVehicleQuicksave, "QUICKSAVE_AIFlyingVehicle"),
MEMBER(quicksave, "QUICKSAVE_AIBomber"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIDropshipMarauder),
MEMBER(aiEntity, "AIEntity"),
MEMBER(aiFlyingVehicleQuicksave,"QUICKSAVE_AIFlyingVehicle"),
MEMBER(marauder, "Marauder"),
MEMBER(aiDropshipMarauderQuicksave,"QUICKSAVE_AIDropshipMarauder"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIDropshipGrunt),
MEMBER(aiEntity, "AIEntity"),
MEMBER(aiFlyingVehicleQuicksave,"QUICKSAVE_AIFlyingVehicle"),
MEMBER(squad, "Squad"),
MEMBER(speechResource, "Speech Resource"),
MEMBER(aiDropshipGruntQuicksave,"QUICKSAVE_AIDropshipGrunt"));

REFLECT(BASEDCLASS(AIWorldObject, AICamera),
MEMBER(movementSpeed, "Movement_Speed"),
MEMBER(rotateSpeed, "Rotate_Speed"),
MEMBER(target, "Target"),
MEMBER(followTarget, "Follow Target"),
MEMBER(cameraQuicksave,"QUICKSAVE_AICamera"));

REFLECT(BASEDCLASS(Resource, AILandMine),
MEMBER(active, "Active"),
MEMBER(posX, "PosX"),
MEMBER(posY, "PosY"),
MEMBER(posZ, "PosZ"),
MEMBER(aiLandMineQuicksave,"QUICKSAVE_AILandMine"));

REFLECT(CLASS(AISwitchSoundEffects),
MEMBER(unlock, "Unlock"),
MEMBER(lock, "Lock"),
MEMBER(useOn, "UseOn"),
MEMBER(useOff, "UseOff"));

REFLECT(CLASS(AISwitchStateActions),
MEMBER(off, "OFF"),
MEMBER(switchingOn, "SWITCHING_ON"),
MEMBER(on, "ON"),
MEMBER(switchingOff, "SWITCHING_OFF"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AISwitch),
MEMBER(animSwitchingOn, "AnimSwitchingOn"),
MEMBER(animSwitchingOff, "AnimSwitchingOff"),
MEMBER(soundEffects, "SoundEffects"),
MEMBER(stateActions, "StateActions"),
MEMBER(autoReset, "AutoReset"),
MEMBER(numTimesUseOn, "NumTimesUseOn"),
MEMBER(numTimesUseOff, "NumTimesUseOff"),
MEMBER(switchedOn, "SwitchedOn"),
MEMBER(switchState, "SwitchState"),
MEMBER(aiSwitchQuicksave2,"QUICKSAVE_AISwitch"),
MEMBER(aiSwitchQuicksave,"QUICKSAVE"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIAmmoBundle),
MEMBER(active, "Active"),
MEMBER(ammoPickupType, "AmmoPickupType"),
MEMBER(respawnTime, "RespawnTime"),
MEMBER(aiAmmoBundleAIAmmoBundleQuicksave,"QUICKSAVE_AIAmmoBundle"),
MEMBER(aiAmmoBundleAIAmmoBundleQuicksave,"QUICKSAVE"));

REFLECT(BASEDCLASS(WorldObjectModel, AIPickupItemHealth),
MEMBER(reActivateTime, "ReActivateTime"),
MEMBER(active, "Active"),
MEMBER(timeHidden, "TimeHidden"),
MEMBER(neverHide, "NeverHide"),
MEMBER(onceOnly, "OnceOnly"),
MEMBER(pickupRadius, "PickupRadius"),
MEMBER(type, "Type"),
MEMBER(aiPickupItemHealthQuicksave,"QUICKSAVE_AIPickupItem"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIElectricFencePost),
MEMBER(on, "On"),
MEMBER(health, "Health"),
MEMBER(vulnerability, "Vulnerability"),
MEMBER(aiElectricFencePostQuicsave, "QUICKSAVE_AIElectricFencePost"),
MEMBER(quicksave, "QUICKSAVE"));

REFLECT(BASEDCLASS(WorldObject, AIElectricFence),
MEMBER(post0, "Post0"),
MEMBER(post1, "Post1"),
MEMBER(active, "Active"),
MEMBER(aiElectricFenceQuicksave,"QUICKSAVE_AIElectricFence"));

REFLECT(CLASS(AIDoorSoundEffects),
MEMBER(unlock, "Unlock"),
MEMBER(lock, "Lock"),
MEMBER(open, "Open"),
MEMBER(close, "Close"),
MEMBER(inMotionLooping, "InMotionLooping"),
MEMBER(endMotion, "EndMotion"));

REFLECT(CLASS(AIDoorStateActions),
MEMBER(closed, "CLOSED"),
MEMBER(opening, "OPENING"),
MEMBER(opened, "OPENED"),
MEMBER(closing, "CLOSING"));

REFLECT(BASEDCLASS(WorldObjectModel, AIDoor),
MEMBER(animOpening, "AnimOpening"),
MEMBER(animClosing, "AnimClosing"),
MEMBER(autoOpen, "AutoOpen"),
MEMBER(autoClose, "AutoClose"),
MEMBER(allowInterrupting, "AllowInterrupting"),
MEMBER(autoOpenRadius, "AutoOpenRadius"),
MEMBER(autoCloseRadius, "AutoCloseRadius"),
MEMBER(autoAIType, "AutoAIType"),
MEMBER(soundEffects, "SoundEffects"),
MEMBER(stateActions, "StateActions"),
MEMBER(portal0, "Portal_0"),
MEMBER(portal1, "Portal_1"),
MEMBER(switchedOn, "SwitchedOn"),
MEMBER(doorState, "DoorState"),
MEMBER(aiDoorQuicksave, "QUICKSAVE_AIDoor"),
MEMBER(quicksave, "QUICKSAVE"));

REFLECT(CLASS(AIStaticGunDoubleGunParameters),
MEMBER(range, "Range"),
MEMBER(spread, "Spread"),
MEMBER(angleRangeHeading, "AngleRangeHeading"),
MEMBER(angleRangePitch, "AngleRangePitch"));

REFLECT(CLASS(AIStaticGunDoubleAIParameters),
MEMBER(engageRange, "EngageRange"),
MEMBER(hitRate, "HitRate"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIStaticGunDouble),
MEMBER(aiWeaponQuicksave,"QUICKSAVE_AIWeapon"),
MEMBER(switchedOn, "SwitchedOn"),
MEMBER(gunParameters, "Gun_Parameters"),
MEMBER(aiParameters, "AI_Parameters"),
MEMBER(destroyed, "Destroyed"),
MEMBER(atStaticGunDoubleQuicksave, "QUICKSAVE_AIStaticGunDouble"),
MEMBER(quicksave, "QUICKSAVE"),
MEMBER(staticGunQuicksave, "QUICKSAVE_StaticGun"),
MEMBER(flash1, "Flash1"),
MEMBER(flash2, "Flash2"),
MEMBER(tracer, "Tracer"),
MEMBER(reloadAfterXMisfires, "ReloadAfterXMisfires"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIStaticNukeLauncher),
MEMBER(aiWeaponQuicksave,"QUICKSAVE_AIWeapon"),
MEMBER(viewZoom, "ViewZoom"),
MEMBER(viewOffset, "ViewOffset"),
MEMBER(switchedOn, "SwitchedOn"),
MEMBER(ammo, "Ammo"),
MEMBER(target, "Target"),
MEMBER(useActions, "UseActions"),
MEMBER(fireActions, "FireActions"),
MEMBER(impactActions, "ImpactActions"),
MEMBER(missileSpeed, "MissileSpeed"),
MEMBER(missileClimb, "MissileClimb"));

REFLECT(BASEDCLASS(WorldObject, AIProjectileLauncher),
MEMBER(active, "Active"),
MEMBER(aabb, "AABB"),
MEMBER(type, "Type"),
MEMBER(target, "Target"),
MEMBER(minTime, "Min_Time"),
MEMBER(maxTime, "Max_Time"),
MEMBER(launchAngle, "LaunchAngle"),
MEMBER(noTargetLaunchHeading, "NoTarget_LaunchHeading"),
MEMBER(noTargetLaunchDistance, "NoTarget_LaunchDistance"),
MEMBER(aiProjectileLauncherQuicksave,"QUICKSAVE_AIProjectileLauncher"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIWeaponShotgun),
MEMBER(aiWeaponQuicksave,"QUICKSAVE_AIWeapon"),
MEMBER(ammoShells, "AmmoShells"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIWeaponRailgun),
MEMBER(aiWeaponQuicksave,"QUICKSAVE_AIWeapon"),
MEMBER(ammoSlugs, "AmmoSlugs"),
MEMBER(aiWeaponRailgunQuicksave,"QUICKSAVE_AIWeaponRailgun"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIWeaponRocket),
MEMBER(aiWeaponQuicksave,"QUICKSAVE_AIWeapon"),
MEMBER(ammoRocket, "AmmoRocket"),
MEMBER(aiWeaponRocketQuicksave,"QUICKSAVE_AIWeaponRocket"));

REFLECT(CLASS(AIBugWarriorBaseQuicksave),
MEMBER(aiFourStateMatrix, "AIFourStateMatrix"),
MEMBER(healthLegs, "m_HealthLegs"),
MEMBER(bFightStrike, "m_bFightStrike"),
MEMBER(bFightStrikeTrack, "m_bFightStrikeTrack"),
MEMBER(hitVec, "m_HitVec"),
MEMBER(animType, "m_AnimType"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(aiAnimTime, "m_AIAnimTime"),
MEMBER(bMoveWPTight, "m_bMoveWPTight"),
MEMBER(bMoveZigZag, "m_bMoveZigZag"),
MEMBER(bElectrify, "m_bElectrify"),
MEMBER(bBurntModelSwitch, "m_bBurntModelSwitch"),
MEMBER(cosmeticVulnerability, "m_cosmeticVulnerability"),
MEMBER(IgnoreRadius, "m_IgnoreRadius"),
MEMBER(IgnoreUseDeltaY, "m_IgnoreUseDeltaY"),
MEMBER(IgnoreDeltaY, "m_IgnoreDeltaY"));

REFLECT(CLASS(AIBugChariotQuicksave),
MEMBER(aiThreeStateMatrix, "AIThreeStateMatrix"),
MEMBER(animType, "m_AnimType"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(aiAnimTime, "m_AIAnimTime"),
MEMBER(millingCentre, "m_millingCentre"));

REFLECT(CLASS(AIBugFlyerBaseQuicksave),
MEMBER(aiFlyerTwoStateMatrix, "AIFlyerTwoStateMatrix"),
MEMBER(turningInFlyerZone, "m_turningInFlyerZone"),
MEMBER(forceFindPosition, "m_forceFindPosition"),
MEMBER(timeSinceLastScreech, "m_TimeSinceLastScreech"),
MEMBER(HitVec, "m_HitVec"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(animTime, "m_AnimTime"),
MEMBER(desSpeed, "m_DesSpeed"),
MEMBER(bLaden, "m_bLaden"),
MEMBER(pFlyerZone, "m_pFlyerZone"),
MEMBER(flutterAnimTime, "m_flutterAnimTime"));

REFLECT(CLASS(AIBugHopperQuicksave),
MEMBER(fightPhase, "m_FightPhase"),
MEMBER(flyOverTarget, "m_flyOverTarget"),
MEMBER(cacheAITargetPos, "m_cacheAITargetPos"),
MEMBER(bStrikeReady, "m_bStrikeReady"));

REFLECT(CLASS(AIBugPlasmaQuicksave),
MEMBER(aiTwoStateMatrix, "AITwoStateMatrix"),
MEMBER(animType, "m_AnimType"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(aiAnimTime, "m_AIAnimTime"),
MEMBER(bReqFireBolt, "m_bReqFireBolt"),
MEMBER(reqPreLaunchEffect, "m_ReqPreLaunchEffect"),
MEMBER(bBossModeVulnerable, "m_bBossModeVulnerable"),
MEMBER(compoundDamage, "m_compoundDamage"),
MEMBER(bInitialised, "m_bInitialised"),
MEMBER(cowerTimeout, "m_cowerTimeout"),
MEMBER(pbSpecialMode, "m_PBSpecialMode"),
MEMBER(cowerMode, "m_cowerMode"),
MEMBER(pSpray, "m_pSpray"),
MEMBER(pNucBlastEffect1, "m_pNucBlastEffect1"),
MEMBER(pNucBlastEffect2, "m_pNucBlastEffect2"),
MEMBER(sonicDir, "m_SonicDir"));

REFLECT(CLASS(AIBugBabyPlasmaQuicksave),
MEMBER(aiThreeStateMatrix, "AIThreeStateMatrix"),
MEMBER(animType, "m_AnimType"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(aiAnimTime, "m_AIAnimTime"),
MEMBER(bFightStrike, "m_bFightStrike"),
MEMBER(canIncreaseAccuracy, "m_LaunchedFireball"),
MEMBER(multiWPDeltaHealth, "m_PBSpecialMode"),
MEMBER(launchedFireball, "m_minMoveTime"),
MEMBER(psSpecialMode, "m_canIncreaseAccuracy"),
MEMBER(minMoveTime, "m_multiWPDeltaHealth"),
MEMBER(headElevation, "m_currentVarianceIndex"),
MEMBER(currentVarianceIndex, "m_pSpray"),
MEMBER(pSpray, "m_headElevation"),
MEMBER(pNucBlastEffect1, "m_pNucBlastEffect1"),
MEMBER(pNucBlastEffect2, "m_pNucBlastEffect2"));

REFLECT(CLASS(AIBugBlasterQuicksave),
MEMBER(aiTwoStateMatrix, "AITwoStateMatrix"),
MEMBER(animType, "m_AnimType"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(aiAnimTime, "m_AIAnimTime"),
MEMBER(projectileLaunchPos, "m_projectileLaunchPos"),
MEMBER(reqLaunchProjectile, "m_reqLaunchProjectile"),
MEMBER(nextStrikeTime, "m_nextStrikeTime"),
MEMBER(bFightStrike, "m_bFightStrike"),
MEMBER(launchToggle, "m_launchToggle"),
MEMBER(canIncreaseAccuracy, "m_canIncreaseAccuracy"),
MEMBER(bUprightMatrix, "m_bUprightMatrix"),
MEMBER(currentVarianceIndex, "m_currentVarianceIndex"));

REFLECT(CLASS(AIBugTankerBabyQuicksave),
MEMBER(aiThreeStateMatrix, "AIThreeStateMatrix"),
MEMBER(animType, "m_AnimType"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(aiAnimTime, "m_AIAnimTime"),
MEMBER(targetFirePos, "m_TargetFirePos"),
MEMBER(pSpark, "m_pSpark"),
MEMBER(sparkStarted, "m_SparkStarted"),
MEMBER(tbSpecialMode, "m_TBSpecialMode"),
MEMBER(minMoveTime, "m_minMoveTime"),
MEMBER(canIncreaseAccuracy, "m_canIncreaseAccuracy"),
MEMBER(multiWPDeltaHealth, "m_multiWPDeltaHealth"),
MEMBER(pSpray, "m_pSpray"),
MEMBER(currentVarianceIndex, "m_currentVarianceIndex"));

REFLECT(CLASS(AIBugWarriorTigerSpitQuicksave),
MEMBER(launchedFireBall, "m_LaunchedFireBall"),
MEMBER(reqLaunchSpitLong, "m_reqLaunchSpitLong"),
MEMBER(reqLaunchSpitShort, "m_reqLaunchSpitShort"),
MEMBER(spitLaunchPos, "m_SpitLaunchPos"),
MEMBER(canIncreaseAccuracy, "m_canIncreaseAccuracy"),
MEMBER(lastSightedTarget, "m_lastSightedTarget"),
MEMBER(currentVarianceIndex, "m_currentVarianceIndex"));

REFLECT(CLASS(AIBugWarriorRoyalXQuicksave),
MEMBER(finale, "m_finale"),
MEMBER(rearUpDamageHealth, "m_rearUpDamageHealth"),
MEMBER(bReqExposeBelly, "m_bReqExposeBelly"),
MEMBER(bCanFireSpray, "m_bCanFireSpray"),
MEMBER(pSpray, "m_pSpray"),
MEMBER(royalAttackType, "m_RoyalAttackType"),
MEMBER(requestRoarBlastDamageTime, "m_requestRoarBlastDamageTime"),
MEMBER(pSonicEffect, "m_pSonicEffect"));

REFLECT(CLASS(WorldObjectQuicksave),
MEMBER(pContext, "m_pContext"));

REFLECT(CLASS(ModelDetailDynamicQuicksave),
MEMBER(pRagDoll, "m_pRagDoll"),
MEMBER(pFlames, "m_pFlames"),
MEMBER(pSmoke, "m_pSmoke"),
MEMBER(flameListNum, "m_FlameListNum"),
MEMBER(smokeListNum, "m_SmokeListNum"));

REFLECT(CLASS(AITwoStateMatrix),
MEMBER(aiTime, "m_AITime"),
MEMBER(aiMatrix, "m_AIMatrix"),
MEMBER(aiMoving,"m_AIMoving"));

REFLECT(CLASS(AIFourStateMatrix),
MEMBER(aiTime, "m_AITime"),
MEMBER(aiMatrix, "m_AIMatrix"),
MEMBER(aiMoving,"m_AIMoving"));

REFLECT(CLASS(AIThreeStateMatrix),
MEMBER(aiTime, "m_AITime"),
MEMBER(aiMatrix, "m_AIMatrix"),
MEMBER(aiMoving,"m_AIMoving"));

REFLECT(BASEDCLASS(AITwoStateMatrix, AIFlyerTwoStateMatrix),
MEMBER(aiVel, "m_AIVel"),
MEMBER(fHover, "m_fHover"),
MEMBER(lastPos, "m_LastPos"),
MEMBER(lastVel, "m_LastVel"),
MEMBER(lastRoll, "m_LastRoll"),
MEMBER(rollState, "m_RollRate"),
MEMBER(midpointOffset, "m_midpointOffset"));

REFLECT(CLASS(AIEntityGenericQuicksave),
MEMBER(aiTwoStateMatrix, "AITwoStateMatrix"),
MEMBER(aiAnimTime, "m_AIAnimTime"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(pCustomAnim, "m_pCustomAnim"));

REFLECT(CLASS(AIEntityQuicksaveAnimationBlend),
MEMBER(animIndex, "AnimIndex"),
MEMBER(dTime0, "m_dTime0"),
MEMBER(dInvDTime, "m_dInvDTime"),
MEMBER(fTAnim0, "m_fTAnim0"),
MEMBER(fDTAnim, "m_fDTAnim"),
MEMBER(fBlend0, "m_fBlend0"),
MEMBER(fDBlend, "m_fDBlend"));

REFLECT(CLASS(AIEntityQuicksaveAnimSet),
MEMBER(aiAnimationBlends, "m_AIAnimationBlends"));

REFLECT(CLASS(AIEntityNonPhysicalPresenceAIEntityQuicksave),
MEMBER(animSet, "m_AnimSet"),
MEMBER(bEndOfWPChain, "m_bEndOfWPChain"),
MEMBER(fNextVulnerability, "m_fNextVulnerability"),
MEMBER(bNextVulnerabilityIsSet, "m_bNextVulnerabilityIsSet"),
MEMBER(pAggressor, "m_pAggressor"),
MEMBER(lastPos, "m_LastPos"),
MEMBER(velocity, "m_Velocity"));

REFLECT(BASEDCLASS(AIEntityNonPhysicalPresenceAIEntityQuicksave, AIEntityQuicksave),
MEMBER(pRagDoll, "m_pRagDoll"),
MEMBER(bNeedToAdvanceWP, "m_bNeedToAdvanceWP"),
MEMBER(bNeedToAdvanceWPPos, "m_bNeedToAdvanceWPPos"),
MEMBER(bCanSeeTarget, "m_bCanSeeTarget"),
MEMBER(lastTargetPosition, "m_LastTargetPosition"),
MEMBER(hasHealthBar, "HasHealthBar"));

REFLECT(CLASS(AITriggerBoxQuicksave),
MEMBER(nextCheckTime, "m_NextCheckTime"),
MEMBER(entitiesLast, "m_pEntitiesLast"));

REFLECT(CLASS(AIGroupQuicksave),
MEMBER(desAlert, "m_DesAlert"),
MEMBER(desMode, "m_DesMode"));

REFLECT(CLASS(AISpawnGroupQuicksave),
MEMBER(memberNum, "m_MemberNum"),
MEMBER(numInCurrWave, "m_NumInCurrWave"),
MEMBER(bSpawning, "m_bSpawning"),
MEMBER(bSpawnAllowed, "m_bSpawnAllowed"),
MEMBER(bSpawnedBySpot, "m_bSpawnedBySpot"));

REFLECT(CLASS(AISquadQuicksave),
MEMBER(ePrevMode, "m_ePrevMode"),
MEMBER(fSpeed, "m_fSpeed"),
MEMBER(hotSpotList, "m_HotSpotList"),
MEMBER(memberHotSpots, "m_MemberHotSpots"),
MEMBER(dTime0, "m_dTime0"),
MEMBER(dTime1, "m_dTime1"),
MEMBER(nNextToDisembark, "m_nNextToDisembark"),
MEMBER(pWayPointHistory, "m_pWayPointHistory"),
MEMBER(dLastCheckMemberDistanceTime, "m_dLastCheckMemberDistanceTime"),
MEMBER(bNeedToCatchup, "m_bNeedToCatchup"),
MEMBER(bMembersAtTempHotspots, "m_bMembersAtTempHotspots"));

REFLECT(CLASS(AIHotspotQuicksave),
MEMBER(pOccupier, "m_pOccupier"),
MEMBER(bActionsDone, "m_bActionsDone"));

REFLECT(CLASS(AICameraQuicksave),
MEMBER(targetOffset, "m_TargetOffset"));

REFLECT(CLASS(AIElectricFencePostQuicsave),
MEMBER(getIsActive, "GetIsActive"),
MEMBER(animTime, "m_AnimTime"));

REFLECT(CLASS(AIElectricFenceQuicksave),
MEMBER(checkTime, "m_CheckTime"),
MEMBER(lastT, "m_LastT"),
MEMBER(pElectricFence, "m_pElectricFence"));

REFLECT(CLASS(AIDoorQuicksave),
MEMBER(getIsActive, "GetIsActive"),
MEMBER(openFactor, "m_OpenFactor"));

REFLECT(BASEDCLASS(AIDoorQuicksave, AIDoorQuicksave2),
MEMBER(pAvoidanceBox, "m_pAvoidanceBox"),
MEMBER(posCentre, "m_PosCentre"));

REFLECT(CLASS(AILandMineQuicksave),
MEMBER(nextCheckTime, "m_NextCheckTime"),
MEMBER(lastWarnTime, "m_LastWarnTime"));

REFLECT(CLASS(AISwitchQuicksave),
MEMBER(getIsActive, "GetIsActive"),
MEMBER(posFactor, "m_PosFactor"),
MEMBER(lastSwitchTime, "m_lastSwitchTime"));

REFLECT(BASEDCLASS(AISwitchQuicksave, AISwitchQuicksave2),
MEMBER(lastSwitchTime, "m_lastSwitchTime"));

REFLECT(CLASS(AIAmmoBundleAIAmmoBundleQuicksave),
MEMBER(nextCheckTime, "m_NextCheckTime"));

REFLECT(CLASS(AIPickupItemHealthQuicksave),
MEMBER(nextPickupTime, "m_NextPickupTime"),
MEMBER(bHidden, "m_bHidden"));

REFLECT(CLASS(AIWeaponQuicksave),
MEMBER(mode, "m_Mode"),
MEMBER(desMode, "m_DesMode"),
MEMBER(pTarget, "m_pTarget"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(modeStartTime, "m_ModeStartTime"),
MEMBER(modeEndTime, "m_ModeEndTime"));

REFLECT(CLASS(StaticGunQuicksave),
MEMBER(gunHeading, "m_GunHeading"),
MEMBER(gunPitch, "m_GunPitch"),
MEMBER(viewHeading, "m_ViewHeading"),
MEMBER(viewPitch, "m_ViewPitch"),
MEMBER(modeStartTime, "m_ModeStartTime"),
MEMBER(modeEndTime, "m_ModeEndTime"),
MEMBER(desZoom, "m_DesZoom"),
MEMBER(zoom, "m_Zoom"),
MEMBER(targetingTime, "m_TargetingTime"),
MEMBER(temperature, "m_Temperature"),
MEMBER(overHeatTime, "m_OverHeatTime"),
MEMBER(bParked, "m_bParked"),
MEMBER(barrelNum, "m_BarrelNum"),
MEMBER(destroyed, "m_bDestroyed"));

REFLECT(BASEDCLASS(StaticGunQuicksave, AIStaticGunDoubleQuicksave),
MEMBER(baseMatrix, "m_BaseMatrix"),
MEMBER(gunMatrix0, "m_GunMatrix0"));

REFLECT(CLASS(AIStaticGunDoubleQuicksave2),
MEMBER(mode, "m_Mode"),
MEMBER(desMode, "m_DesMode"),
MEMBER(modeStartTime, "m_ModeStartTime"),
MEMBER(pTarget, "m_pTarget"),
MEMBER(modeEndTime, "m_ModeEndTime"),
MEMBER(pAnim, "m_pAnim"));

REFLECT(CLASS(AIProjectileLauncherQuicksave),
MEMBER(nextFireTime, "m_nextFireTime"));

REFLECT(CLASS(AIWeaponRailgunQuicksave),
MEMBER(bDesReload, "m_bDesReload"),
MEMBER(zoomStage, "m_ZoomStage"),
MEMBER(modeStartZoom, "m_ModeStartZoom"),
MEMBER(modeEndZoom, "m_ModeEndZoom"));

REFLECT(CLASS(AIWeaponRocketQuicksave),
MEMBER(burstNum, "m_BurstNum"));

REFLECT(CLASS(AIFlyingVehicleQuicksave),
MEMBER(aiFlyerTwoStateMatrix, "AIFlyerTwoStateMatrix"),
MEMBER(desSpeed, "m_DesSpeed"),
MEMBER(fvSpecialMode, "m_FVSpecialMode"),
MEMBER(nextFVSpecialMode, "m_NextFVSpecialMode"),
MEMBER(pDustRing, "m_pDustRing"));

REFLECT(CLASS(AIBomberQuicksave),
MEMBER(pConTrail[0], "m_pConTrail_1"),
MEMBER(pConTrail[1], "m_pConTrail_2"));

REFLECT(CLASS(AIDropshipMarauderQuicksave),
MEMBER(pConTrail, "m_pConTrail"),
MEMBER(bDisembarking, "m_bDisembarking"),
MEMBER(marauderPos, "m_MarauderPos"),
MEMBER(marauderAng, "m_MarauderAng"));

REFLECT(CLASS(AIDropshipGruntQuicksave),
MEMBER(pConTrail, "m_pConTrail"));

REFLECT(CLASS(AIHumanStartWeapons),
MEMBER(startWeaponSlot1, "StartWeapon_Slot_1"),
MEMBER(startWeaponSlot2, "StartWeapon_Slot_2"),
MEMBER(startWeaponSlot3, "StartWeapon_Slot_3"),
MEMBER(MORITIA_MK4, "AIWT_MORITIA_MK4"),
MEMBER(MORITIA_MK2_SHOTGUN,"AIWT_MORITIA_MK2_SHOTGUN"),
MEMBER(MORITIA_MK2_GRENADE,"AIWT_MORITIA_MK2_GRENADE"),
MEMBER(HEAVY_SHOTGUN, "AIWT_HEAVY_SHOTGUN"),
MEMBER(MORITIA_MK2_ZOOM, "AIWT_MORITIA_MK2_ZOOM"),
MEMBER(MORITIA_MK2_CARBINE,"AIWT_MORITIA_MK2_CARBINE"),
MEMBER(ROCKET_LAUNCHER,"AIWT_ROCKET_LAUNCHER"),
MEMBER(RAILGUN, "AIWT_RAILGUN"),
MEMBER(MISSILE_LAUNCHER,"AIWT_MISSILE_LAUNCHER"),
MEMBER(PSIOP_FAKE, "AIWT_PSIOP_FAKE"));

REFLECT(CLASS(AIHumanDeath),
MEMBER(gibNotLaunch, "GibNotLaunch"),
MEMBER(gibForce, "GibForce"));

REFLECT(CLASS(AIHumanQuicksave),
MEMBER(aiThreeStateMatrix, "AIThreeStateMatrix"),
MEMBER(pSwitchWeapon, "m_pSwitchWeapon"),
MEMBER(vLastAim, "m_vLastAim"),
MEMBER(mWorldEndAnim, "m_mWorldEndAnim"),
MEMBER(dLastSpottingTime, "m_dLastSpottingTime"),
MEMBER(dNextAttractTime, "m_dNextAttractTime"),
MEMBER(bJustTurned, "m_bJustTurned"),
MEMBER(bTargetDied, "m_bTargetDied"),
MEMBER(dLastPlayerLookTime, "m_dLastPlayerLookTime"),
MEMBER(vBonePos, "m_vBonePos"),
MEMBER(bThrowingGrenade, "m_bThrowingGrenade"),
MEMBER(dLastGrenadeTime, "m_dLastGrenadeTime"),
MEMBER(dLastFireTime, "m_dLastFireTime"),
MEMBER(humanSpecialMode, "m_HumanSpecialMode"),
MEMBER(nSquadMemberID, "m_nSquadMemberID"),
MEMBER(fPreviousGradient, "m_fPreviousGradient"),
MEMBER(nPreviousSpeed, "m_nPreviousSpeed"),
MEMBER(ePrevMode, "m_ePrevMode"),
MEMBER(pLoopAnim, "m_pLoopAnim"),
MEMBER(pLoopAnimSet, "m_pLoopAnimSet"),
MEMBER(dLoopAnimMaxTime, "m_dLoopAnimMaxTime"),
MEMBER(nLoopAnimReps, "m_nLoopAnimReps"),
MEMBER(nLoopAnimMaxReps, "m_nLoopAnimMaxReps"),
MEMBER(dLoopAnimTimeStart, "m_dLoopAnimTimeStart"),
MEMBER(eLoopAnimStandardPose, "m_eLoopAnimStandardPose"),
MEMBER(nSquadPathSegment, "m_nSquadPathSegment"),
MEMBER(nStuckTimer, "m_nStuckTimer"),
MEMBER(pAttachMatrixObject, "m_pAttachMatrixObject"),
MEMBER(vAttachOffset, "m_pSLVV_m_vAttachOffset"),
MEMBER(nDropShipStage, "m_nDropShipStage"),
MEMBER(nDropShipSide, "m_nDropShipSide"),
MEMBER(bKneeling, "m_bKneeling"),
MEMBER(fKneelTimer, "m_fKneelTimer"),
MEMBER(bAccuratePoints, "m_bAccuratePoints"),
MEMBER(fAccuratePointHeading, "m_fAccuratePointHeading"),
MEMBER(nAccuratePointWait, "m_nAccuratePointWait"),
MEMBER(pHotSpot, "m_pHotSpot"),
MEMBER(fBlindTime, "m_fBlindTime"),
MEMBER(pBreakIgnoreTarget, "m_pBreakIgnoreTarget"),
MEMBER(bBreakIgnore, "m_bBreakIgnore"),
MEMBER(bGunState, "m_bGunState"),
MEMBER(fPersonalGrenadeChance, "m_fPersonalGrenadeChance"),
MEMBER(fPersonalAttractTurnChance, "m_fPersonalAttractTurnChance"),
MEMBER(fPersonalKneelChance, "m_fPersonalKneelChance"),
MEMBER(bBypassSeuquencerAdvance, "m_bBypassSeuquencerAdvance"),
MEMBER(bForceToSpot, "m_bForceToSpot"),
MEMBER(pTurnToFaceObject, "m_pTurnToFaceObject"),
MEMBER(fTurnToFaceAngle, "m_fTurnToFaceAngle"),
MEMBER(pTurnToFaceActionList, "m_pTurnToFaceActionList"),
MEMBER(fBackupVulnerability, "m_fBackupVulnerability"),
MEMBER(delayedSFX_Resource, "m_DelayedSFX_Resource"),
MEMBER(delayedSFX_Rank, "m_DelayedSFX_Rank"),
MEMBER(delayedSFX_Time, "m_DelayedSFX_Time"),
MEMBER(nSaluteStage, "m_nSaluteStage"),
MEMBER(fSaluteAngle, "m_fSaluteAngle"),
MEMBER(fSalutePrevAngle, "m_fSalutePrevAngle"),
MEMBER(bWasSentry, "m_bWasSentry"),
MEMBER(eBackupAlertState, "m_eBackupAlertState"),
MEMBER(dTemporaryIgnoreTime, "m_dTemporaryIgnoreTime"),
MEMBER(nMaxSpeed, "nMaxSpeed"),
MEMBER(bShouldUsePelvisPos, "m_pSLVB_m_bShouldUsePelvisPos"));

REFLECT(CLASS(AIPlayerQuicksave),
MEMBER(viewPitch, "m_ViewPitch"),
MEMBER(weaponDesMode, "m_WeaponDesMode"),
MEMBER(velFactor, "m_VelFactor"),
MEMBER(vel, "m_Vel"),
MEMBER(floorVel, "m_FloorVel"),
MEMBER(bDropping, "m_bDropping"),
MEMBER(duckVal, "m_DuckVal"),
MEMBER(bDuckControl, "m_bDuckControl"),
MEMBER(pFloorObject, "m_pFloorObject"),
MEMBER(floorObjectBoneNum, "m_FloorObjectBoneNum"),
MEMBER(floorObjectMatrix, "m_FloorObjectMatrix"),
MEMBER(pLadder, "m_pLadder"),
MEMBER(pHandGrenade, "m_pHandGrenade"),
MEMBER(bDesHandGrenade, "m_bDesHandGrenade"),
MEMBER(shieldVal, "m_ShieldVal"),
MEMBER(shieldDamageTime, "m_ShieldDamageTime"),
MEMBER(pTorch, "m_pTorch"),
MEMBER(pDropPod, "m_pDropPod"),
MEMBER(bDisableWeapon, "m_bDisableWeapon"),
MEMBER(bEvilEyeOn, "m_bEvilEyeOn"));

REFLECT(BASEDCLASS(ResourcePack, ResourceHumanCharacter),
MEMBER(model, "Model"),
MEMBER(shaderOverrides, "ShaderOverrides"),
MEMBER(humanType, "HumanType"),
MEMBER(speechBank, "SpeechBank"));

REFLECT(BASEDCLASS(AIWorldObject, AIHuman),
MEMBER(humanType, "Human_Type"),
MEMBER(character, "Character"),
MEMBER(weaponActive, "Weapon_Active"),
MEMBER(weaponStowed1, "Weapon_Stowed1"),
MEMBER(weaponStowed2, "Weapon_Stowed2"),
MEMBER(weaponStowed3, "Weapon_Stowed3"),
MEMBER(weaponStowed4, "Weapon_Stowed4"),
MEMBER(weaponStowed5, "Weapon_Stowed5"),
MEMBER(weaponStowed6, "Weapon_Stowed6"),
MEMBER(weaponStowed7, "Weapon_Stowed7"),
MEMBER(weaponStowed8, "Weapon_Stowed8"),
MEMBER(weaponStowed9, "Weapon_Stowed9"),
MEMBER(weaponStowed10, "Weapon_Stowed10"),
MEMBER(canBreakIgnore, "CanBreakIgnore"),
MEMBER(personalGrenadeChance, "PersonalGrenadeChance"),
MEMBER(personalAttractTurnChance, "PersonalAttractTurnChance"),
MEMBER(personalKneelChance, "PersonalKneelChance"),
MEMBER(startWeapons, "StartWeapons"),
MEMBER(death, "Death"),
MEMBER(name, "Name"),
MEMBER(gunVisible, "GunVisible"),
MEMBER(dropToGround, "DropToGround"),
MEMBER(doSalute, "DoSalute"),
MEMBER(saluteRadius, "SaluteRadius"),
MEMBER(aiHumanQuicksave,"QUICKSAVE_AIHuman"));

REFLECT(CLASS(AIPlayerAmmoStowed),
MEMBER(Bullet, "Bullet"),
MEMBER(Grenade, "Grenade"),
MEMBER(Shotgun, "Shotgun"),
MEMBER(Rocket, "Rocket"),
MEMBER(Missile, "Missile"),
MEMBER(Slug, "Slug"),
MEMBER(HandGrenade, "HandGrenade"));

REFLECT(BASEDCLASS(AIHuman, AIPlayer),
MEMBER(ammoStowed, "AmmoStowed"),
MEMBER(startInDropPod, "StartInDropPod"),
MEMBER(dropPodJustEnd, "DropPodJustEnd"),
MEMBER(disableWeapon, "DisableWeapon"),
MEMBER(aiPlayerQuicksave,"QUICKSAVE_AIPlayer"),
MEMBER(collidable, "Collidable"));

REFLECT(CLASS(AIWeaponMoritiaMk2CarbineQuicksave),
MEMBER(burstNum, "m_BurstNum"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIWeaponMoritiaMk2Carbine),
MEMBER(aiWeaponQuicksave,"QUICKSAVE_AIWeapon"),
MEMBER(ammoBullet, "AmmoBullet"),
MEMBER(aiWeaponMoritiaMk2CarbineQuicksave,"QUICKSAVE_AIWeaponMoritiaMk2Carbine"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIWeaponMoritiaMk2Shotgun),
MEMBER(aiWeaponQuicksave,"QUICKSAVE_AIWeapon"),
MEMBER(ammoBullet, "AmmoBullet"),
MEMBER(aiWeaponMoritiaMk2ShotgunQuicksave,"QUICKSAVE_AIWeaponMoritiaMk2Shotgun"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIWeaponMissile),
MEMBER(aiWeaponQuicksave,"QUICKSAVE_AIWeapon"),
MEMBER(aiWeaponMissileQuicksave,"QUICKSAVE_AIWeaponMissile"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIWeaponMoritiaMk2Grenade),
MEMBER(aiWeaponQuicksave, "QUICKSAVE_AIWeapon"),
MEMBER(bulletAmmo, "BulletAmmo"),
MEMBER(grenadeAmmo, "GrenadeAmmo"),
MEMBER(aiWeaponMoritiaMk2GrenadeQuicksave, "QUICKSAVE_AIWeaponMoritiaMk2Grenade"),
MEMBER(reloadAfterXMisfires, "ReloadAfterXMisfires"),
MEMBER(mk2GrenadeQuicksave, "QUICKSAVE_Mk2Grenade"),
MEMBER(quicksave, "QUICKSAVE"));

REFLECT(CLASS(AIWeaponMoritiaMk2ZoomQuicksave),
MEMBER(burstNum, "m_BurstNum"),
MEMBER(bDesReload, "m_bDesReload"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIWeaponMoritiaMk2Zoom),
MEMBER(aiWeaponQuicksave, "QUICKSAVE_AIWeapon"),
MEMBER(ammoBullet, "AmmoBullet"),
MEMBER(aiWeaponMoritiaMk2ZoomQuicksave, "QUICKSAVE_AIWeaponMoritiaMk2Zoom"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIWeaponMoritiaMk4),
MEMBER(aiWeaponQuicksave, "QUICKSAVE_AIWeapon"),
MEMBER(ammoGrenade, "AmmoGrenade"),
MEMBER(aiWeaponMoritiaMk4Quicksave, "QUICKSAVE_AIWeaponMoritiaMk4"),
MEMBER(reloadAfterXMisfires, "ReloadAfterXMisfires"),
MEMBER(quicksave, "QUICKSAVE"),
MEMBER(mk4Quicksave, "QUICKSAVE_Mk4"));

REFLECT(BASEDCLASS(ResourcePack, AIMultiLinkWaypoint),
MEMBER(pos, "Pos"),
MEMBER(nextWaypoint, "NextWaypoint"),
MEMBER(auTypeId, "AI_TypeID"),
MEMBER(triggers, "Triggers"),
MEMBER(linkedWaypoints,"LinkedWaypoints")
);

REFLECT(BASEDCLASS(WorldObject, AIHeightMap),
MEMBER(minX, "Min_X"),
MEMBER(minY, "Min_Y"),
MEMBER(minZ, "Min_Z"),
MEMBER(maxX, "Max_X"),
MEMBER(maxX, "Max_Y"),
MEMBER(maxX, "Max_Z"),
MEMBER(nodeSize, "NodeSize"),
MEMBER(collisionFlags, "CollisionType_Flags"),
MEMBER(material, "Material"));

REFLECT(BASEDCLASS(ResourcePack, AIEntityHealthAction),
MEMBER(actions,"Actions"),
MEMBER(triggerPercentage, "TriggerPercentage"));

REFLECT(BASEDCLASS(WorldObject, AISpawnerBase),
MEMBER(spawnEntities, "SpawnEntities"),
MEMBER(totalNumber, "Total_Number"),
MEMBER(spawnDelayMin, "Spawn_Delay_Min"),
MEMBER(spawnDelayMax, "Spawn_Delay_Max"),
MEMBER(spawnAngleRange, "Spawn_Angle"),
MEMBER(spawnAngleRange, "Spawn_Angle_Range"),
MEMBER(aabb, "AABB"),
MEMBER(nextWaypoint, "Next_Waypoint"),);

REFLECT(BASEDCLASS(AISpawnerBase, AISpawnerVehicle),
MEMBER(aiSpawnerVehicleQuicksave, "QUICKSAVE_AISpawnerVehicle"));

REFLECT(CLASS(AILiftStateActions),
MEMBER(atBottom, "AT_BOTTOM"),
MEMBER(goingUp, "GOING_UP"),
MEMBER(atTop, "AT_TOP"),
MEMBER(goingDown, "GOING_DOWN"));

REFLECT(CLASS(AILiftSoundEffects),
MEMBER(goingUpStart, "GoingUp_Start"),
MEMBER(goingUpLoop, "GoingUp_Loop"),
MEMBER(goingUpStop, "GoingUp_Stop"),
MEMBER(goingDownStart, "GoingDown_Start"),
MEMBER(goingDownLoop, "GoingDown_Loop"),
MEMBER(goingDownStop, "GoingDown_Stop"),
MEMBER(soundEffectBoneNumber, "SoundEffect_BoneNumber"));

REFLECT(BASEDCLASS(WorldObjectModel, AILift),
MEMBER(animGoingUp, "AnimGoingUp"),
MEMBER(animGoingDown, "AnimGoingDown"),
MEMBER(stateActions, "StateActions"),
MEMBER(switchedOn, "SwitchedOn"),
MEMBER(liftState, "LiftState"),
MEMBER(soundEffects, "SoundEffects"),
MEMBER(aiLiftQuicksave,"QUICKSAVE_AILift"));

REFLECT(BASEDCLASS(AISpawnerBase, AISpawnerSquad),
MEMBER(spawnSquads,"SpawnSquads"),
MEMBER(aiSpawnerSquadQuicksave,"QUICKSAVE_AISpawnerSquad"));

REFLECT(BASEDCLASS(ResourcePack, AITriggerBoxOLD),
MEMBER(aabb, "AABB"),
MEMBER(active, "Active"),
MEMBER(actionLists, "ActionLists"),
MEMBER(checkEntities, "CheckEntities"),
MEMBER(cameraCheck, "CameraCheck"),
MEMBER(checkTime, "CheckTime"),
MEMBER(aiTriggerBoxOLDQuicksave,"QUICKSAVE_AITriggerBoxOLD"));

REFLECT(BASEDCLASS(AIPickupItemHealth, AIPickupItemObjective),
MEMBER(message, "Message"));

REFLECT(BASEDCLASS(WorldObjectModel, AIAmmoBox),
MEMBER(active, "Active"),
MEMBER(totalAmmo, "TotalAmmo"),
MEMBER(aiAmmoBoxQuicksave, "QUICKSAVE_AIAmmoBox"),
MEMBER(quicksave, "QUICKSAVE"));

REFLECT(BASEDCLASS(AIWorldObject, AIBugHopperFirefly),
MEMBER(aiBugFlyerBaseQuicksave,"QUICKSAVE_AIBugFlyerBase"),
MEMBER(attackType, "AttackType"),
MEMBER(aiBugHopperFireflyQuicksave,"QUICKSAVE_AIBugHopperFireFly"),
MEMBER(dustSystem, "Dust_System"));

REFLECT(BASEDCLASS(AIWorldObject, AIBugRhino),
MEMBER(aiBugRhinoQuicksave,"QUICKSAVE_AIBugRhino"),
MEMBER(specialMode, "Special_Mode"),
MEMBER(dustSystem, "Dust_System"));

REFLECT(BASEDCLASS(AIWorldObject, AIBugCliffMite),
MEMBER(specialMode, "Special_Mode"),
MEMBER(aiBugCliffMiteQuicksave,"QUICKSAVE_AIBugCliffMite"));

REFLECT(BASEDCLASS(AIWorldObject, AIBugHopperRippler),
MEMBER(aiBugFlyerBaseQuicksave,"QUICKSAVE_AIBugFlyerBase"),
MEMBER(aiBugHopperRipplerQuicksave,"QUICKSAVE_AIBugHopperRippler"));

REFLECT(BASEDCLASS(AIBugWarrior, AIBugWarriorRoyal),
MEMBER(leftShieldAction,"LeftShieldAction"),
MEMBER(rightShieldAction,"RightShieldAction"),
MEMBER(leftEyeAction,"LeftEyeAction"),
MEMBER(rightEyeAction,"RightEyeAction"),
MEMBER(aiBugWarriorRoyalQuicksave,"QUICKSAVE_AIBugWarriorRoyal"));

REFLECT(BASEDCLASS(AIBugWarrior, AIBugWarriorTigerShard),
MEMBER(aiBugWarriorTigerShardQuicksave,"QUICKSAVE_AIBugWarriorTigerShard"));

REFLECT(BASEDCLASS(AIWorldObject, AIBugSentinel),
MEMBER(flashActions,"FlashActions"),
MEMBER(aiBugSentinelQuicksave,"QUICKSAVE_AIBugSentinel"));

REFLECT(CLASS(AIBugTankerQuicksave),
MEMBER(pSpray, "m_pSpray"),
MEMBER(pSpark, "m_pSpark"),
MEMBER(stompTime, "m_StompTime"),
MEMBER(stompPos, "m_StompPos"),
MEMBER(stompStrength, "m_StompStrength"),
MEMBER(stompHotspot, "m_StompHotspot"),
MEMBER(stompFalloff, "m_StompFalloff"),
MEMBER(bBossRetract, "m_bBossRetract"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(aiTime, "m_AITime"));

REFLECT(BASEDCLASS(AIWorldObject, AIBugTanker),
MEMBER(dustSystem, "Dust_System"),
MEMBER(initialDustPosition, "InitialDustPosition"),
MEMBER(l75HealthActionList, "L2_75_Health_ActionList"),
MEMBER(l50HealthActionList, "L2_50_Health_ActionList"),
MEMBER(l25HealthActionList, "L2_25_Health_ActionList"),
MEMBER(aiBugTankerQuicksave,"QUICKSAVE_AIBugTanker"));

REFLECT(CLASS(AIWeaponMissileQuicksave),
MEMBER(ammoMissile, "m_AmmoMissile"),
MEMBER(bDesReload, "m_bDesReload"),
MEMBER(pMissile, "m_pMissile"));

REFLECT(CLASS(AIWeaponMoritiaMk2GrenadeQuicksave),
MEMBER(mode, "m_Mode"),
MEMBER(desMode, "m_DesMode"),
MEMBER(pTarget, "m_pTarget"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(modeStartTime, "m_ModeStartTime"),
MEMBER(modeEndTime, "m_ModeEndTime"));

REFLECT(CLASS(AIWeaponMoritiaMk4Quicksave),
MEMBER(ammoBullet, "m_AmmoBullet"),
MEMBER(burstNum, "m_BurstNum"),
MEMBER(lastLoadTime, "m_LastLoadTime"),
MEMBER(bNeedToVent, "m_bNeedToVent"));

REFLECT(CLASS(AIWeaponMoritiaMk4Quicksave2),
MEMBER(mode, "m_Mode"),
MEMBER(desMode, "m_DesMode"),
MEMBER(pTarget, "m_pTarget"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(modeStartTime, "m_ModeStartTime"),
MEMBER(modeEndTime, "m_ModeEndTime"));

REFLECT(CLASS(AISpawnerVehicleQuicksave),
MEMBER(bSpawning, "m_bSpawning"));

REFLECT(CLASS(AILiftQuicksave),
MEMBER(getIsActive, "GetIsActive"),
MEMBER(posFactor, "m_PosFactor"),
MEMBER(bRequestedUp, "m_bRequestedUp"),
MEMBER(bRequestedDown, "m_bRequestedDown"));

REFLECT(CLASS(AIBugHopperFireflyQuicksave),
MEMBER(reqFireBall, "m_reqFireBall"),
MEMBER(desFireTime, "m_desFireTime"),
MEMBER(pSpray, "m_pSpray"),
MEMBER(bPlayingSprayAudio, "m_bPlayingSprayAudio"),
MEMBER(sprayEndTime, "m_sprayEndTime"));

REFLECT(CLASS(AIBugRhinoQuicksave),
MEMBER(aiThreeStateMatrix, "AIThreeStateMatrix"),
MEMBER(animType, "m_AnimType"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(aiAnimTime, "m_AIAnimTime"),
MEMBER(bCharging, "m_bCharging"),
MEMBER(eRhinoAttackMode, "m_eRhinoAttackMode"),
MEMBER(chargeToPos, "m_chargeToPos"),
MEMBER(bShakeHead, "m_bShakeHead"));

REFLECT(CLASS(AIBugCliffMiteQuicksave),
MEMBER(aiTwoStateMatrix, "AITwoStateMatrix"),
MEMBER(animType, "m_AnimType"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(aiAnimTime, "m_AIAnimTime"),
MEMBER(canFire, "m_canFire"),
MEMBER(missileDamageFactor, "m_missileDamageFactor"),
MEMBER(canIncreaseAccuracy, "m_canIncreaseAccuracy"),
MEMBER(currentVarianceIndex, "m_currentVarianceIndex"));

REFLECT(CLASS(AIBugHopperRipplerQuicksave),
MEMBER(targetAcquired, "m_targetAcquired"),
MEMBER(kamikazeTargetPos, "m_kamikazeTargetPos"),
MEMBER(turningToTarget, "m_turningToTarget"));

REFLECT(CLASS(AIBugWarriorRoyalQuicksave),
MEMBER(royalAttackType, "m_RoyalAttackType"),
MEMBER(pSonicEffect, "m_pSonicEffect"),
MEMBER(vecToTarget, "m_VecToTarget"));

REFLECT(CLASS(AIBugWarriorTigerShardQuicksave),
MEMBER(reqLaunchShard, "m_reqLaunchShard"),
MEMBER(reqLaunchCone, "m_reqLaunchCone"),
MEMBER(shardLaunchPos, "m_shardLaunchPos"),
MEMBER(canIncreaseAccuracy, "m_canIncreaseAccuracy"),
MEMBER(lastSightedTarget, "m_lastSightedTarget"),
MEMBER(currentVarianceIndex, "m_currentVarianceIndex"));

REFLECT(CLASS(AIBugSentinelQuicksave),
MEMBER(aiTwoStateMatrix, "AITwoStateMatrix"),
MEMBER(animType, "m_AnimType"),
MEMBER(pAnim, "m_pAnim"),
MEMBER(aiAnimTime, "m_AIAnimTime"),
MEMBER(fightStateFightState, "m_fightState_m_eFightState"),
MEMBER(fightStateLastFightState, "m_fightState_m_elastFightState"),
MEMBER(bFlash, "m_bFlash"),
MEMBER(bRetracted, "m_bRetracted"),
MEMBER(lastFlashTime, "m_lastFlashTime"),
MEMBER(bPlayedDyingAnim, "m_bPlayedDyingAnim"));

REFLECT(BASEDCLASS(ModelDetailDynamic, AIDropshipCargo),
MEMBER(aiEntity, "AIEntity"),
MEMBER(aiFlyingVehicleQuicksave, "QUICKSAVE_AIFlyingVehicle"),
MEMBER(aiDropshipCargoQuicksave, "QUICKSAVE_AIDropshipCargo"));

REFLECT(BASEDCLASS(AIActionList, AITriggerBoxActions),
MEMBER(delay, "Delay"));

REFLECT(BASEDCLASS(AIAction, AIA_Action_SetChance),
MEMBER(target, "Target"),
MEMBER(percent, "Percent"));

REFLECT(BASEDCLASS(AIAction, AIA_AmbientSoundObject_Start),
MEMBER(ambientEffects, "Ambient Effects"));

REFLECT(BASEDCLASS(AIAction, AIA_AmbientSoundObject_Stop),
MEMBER(ambientEffects, "Ambient Effects"));

REFLECT(BASEDCLASS(AIAction, AIA_BabyPlasma_UseMultiLinkWaypoints),
MEMBER(target, "Target"),
MEMBER(useMultiLinkWaypoints, "UseMultiLinkWaypoints"));

REFLECT(BASEDCLASS(AIAction, AIA_BabyTanker_UseMultiLinkWaypoints),
MEMBER(target, "Target"),
MEMBER(useMultiLinkWaypoints, "UseMultiLinkWaypoints"));

REFLECT(BASEDCLASS(AIAction, AIA_CameraShake),
MEMBER(angle, "Angle"),
MEMBER(fadeIn, "FadeIn"),
MEMBER(fadeOut, "FadeOut"),
MEMBER(frequency, "Frequency"),
MEMBER(jolt, "Jolt"),
MEMBER(length, "Length"),
MEMBER(random, "Random"));

REFLECT(BASEDCLASS(AIAction, AIA_ChatScriptStart),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_ClearUpDeadBodies));

REFLECT(BASEDCLASS(AIAction, AIA_Counter_DecrementValue),
MEMBER(target, "Target"),
MEMBER(value, "Value"));

REFLECT(BASEDCLASS(AIAction, AIA_Counter_IncrementValue),
MEMBER(target, "Target"),
MEMBER(value, "Value"));

REFLECT(BASEDCLASS(AIAction, AIA_Counter_SetValue),
MEMBER(target, "Target"),
MEMBER(value, "Value"));

REFLECT(BASEDCLASS(AIAction, AIA_Delete),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_DeleteGroup),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Door_Close),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Door_LockClosed),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Door_LockOpen),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Door_Open),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Dropship_Ascend),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Dropship_Disembark),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Dropship_HoverMoveWP),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Dropship_Landing),
MEMBER(target, "Target"),
MEMBER(flyToHover, "FlyToHover"),
MEMBER(hoverToLand, "HoverToLand"));

REFLECT(BASEDCLASS(AIAction, AIA_Dropship_Takeoff),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_DustStorm),
MEMBER(particleResource, "ParticleResource"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_AddHealthBar),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_Jump));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_RemoveHealthBar),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_SetAlert),
MEMBER(target, "Target"),
MEMBER(alert, "Alert"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_SetAvoidance),
MEMBER(target, "Target"),
MEMBER(avoidance, "Avoidance"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_SetCheckGradient),
MEMBER(target, "Target"),
MEMBER(checkGradient, "CheckGradient"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_SetHealth),
MEMBER(target, "Target"),
MEMBERNAME(healthPercent, "HealthPercent"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_SetStickToWaypoints),
MEMBER(target, "Target"),
MEMBER(stickToWaypoints, "StickToWaypoints"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_SetTarget),
MEMBER(target, "Target"),
MEMBER(entity, "Entity"),
MEMBER(forcedTarget, "ForcedTarget"));

REFLECT(BASEDCLASS(AIAction, AIA_Entity_SetTargettable),
MEMBER(target, "Target"),
MEMBER(targettable, "Targettable"));

REFLECT(BASEDCLASS(AIAction, AIA_HUDDisplay),
MEMBER(show, "Show"));

REFLECT(BASEDCLASS(AIAction, AIA_Hopper_SetFlightSpeed),
MEMBER(target, "Target"),
MEMBER(speed1Slow2Medium3Fast, "Speed__1_Slow__2_Medium__3_Fast"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_DoSalute),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_Gib),
MEMBER(target, "Target"),
MEMBER(blastStrength, "BlastStrength"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_GoToHotSpots),
MEMBER(target, "Target"),
MEMBER(hotSpotType, "HotSpotType"),
MEMBER(radius, "Radius"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_SetGunState),
MEMBER(target, "Target"),
MEMBER(gunOn, "Gun_On"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_SetKneeling),
MEMBER(target, "Target"),
MEMBER(kneeling, "Kneeling"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_SetMaxSpeed),
MEMBER(target, "Target"),
MEMBER(speed, "Speed"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_SetNextPointAccurate),
MEMBER(target, "Target"),
MEMBER(heading, "Heading"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_SetPersonalAttractTurnChance),
MEMBER(target, "Target"),
MEMBER(turnChance, "TurnChance"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_SetPersonalGrenadeChance),
MEMBER(target, "Target"),
MEMBER(grenadeChance, "GrenadeChance"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_SetPersonalKneelChance),
MEMBER(target, "Target"),
MEMBER(kneelChance, "KneelChance"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_SetSentryMode),
MEMBER(target, "Target"),
MEMBER(sentryOn, "SentryOn"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_SwitchWeapon),
MEMBER(target, "Target"),
MEMBER(weapon, "Weapon"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_TurnToFaceAngle),
MEMBER(target, "Target"),
MEMBER(actions, "Actions"),
MEMBER(angle, "Angle"));

REFLECT(BASEDCLASS(AIAction, AIA_Human_TurnToFaceObject),
MEMBER(target, "Target"),
MEMBER(actions, "Actions"),
MEMBER(object, "Object"));

REFLECT(BASEDCLASS(AIAction, AIA_Lift_Down),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Lift_Up),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_LightUpdateContexts),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Light_Off),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Light_On),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_MusicCrossfade),
MEMBER(target, "Target"),
MEMBER(fadeTime, "FadeTime"),
MEMBER(looping, "Looping"),
MEMBER(targetVolume, "TargetVolume"));

REFLECT(BASEDCLASS(AIAction, AIA_MusicFadeTo),
MEMBER(fadeTime, "FadeTime"),
MEMBER(targetVolume, "TargetVolume"));

REFLECT(BASEDCLASS(AIAction, AIA_MusicStart),
MEMBER(target, "Target"),
MEMBER(looping, "Looping"));

REFLECT(BASEDCLASS(AIAction, AIA_MusicStop));

REFLECT(BASEDCLASS(AIAction, AIA_MusicVolume),
MEMBER(targetVolume, "TargetVolume"));

REFLECT(BASEDCLASS(AIAction, AIA_ObjectiveMarker_SetPos),
MEMBER(hideMarkerWhenThere, "HideMarkerWhenThere"),
MEMBER(positionType, "PositionType"),
MEMBER(position, "Position"),
MEMBER(positionValid, "PositionValid"),
MEMBER(radius, "Radius"),
MEMBER(subObjective, "SubObjective"),
MEMBER(trackableObject, "TrackableObject"));

REFLECT(BASEDCLASS(AIAction, AIA_PhysicsKicker),
MEMBER(target, "Target"),
MEMBER(damage, "Damage"),
MEMBER(flame, "Flame"),
MEMBER(force, "Force"),
MEMBER(offset, "Offset"),
MEMBER(radius, "Radius"),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_PlasmaBug_SetSpecialMode),
MEMBER(target, "Target"),
MEMBER(specialMode, "SpecialMode"));

REFLECT(BASEDCLASS(AIAction, AIA_Player_AddVelocity),
MEMBER(target, "Target"),
MEMBER(velX, "Vel_X"),
MEMBER(velY, "Vel_Y"),
MEMBER(velZ, "Vel_Z"));

REFLECT(BASEDCLASS(AIAction, AIA_Player_DisableWeapon),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Player_EnableTorch),
MEMBER(enable, "Enable"),);

REFLECT(BASEDCLASS(AIAction, AIA_Player_SetLadder),
MEMBER(target, "Target"),
MEMBER(ladder, "Ladder"));

REFLECT(BASEDCLASS(AIAction, AIA_Player_SwitchTorch),
MEMBER(target, "Target"),
MEMBER(bSwitch, "Switch"));

REFLECT(BASEDCLASS(AIAction, AIA_PortalOnOff),
MEMBER(target, "Target"),
MEMBER(switchState, "Switch"),);

REFLECT(BASEDCLASS(AIAction, AIA_Script),
MEMBER(elseActions, "ELSE_Actions"),
MEMBER(ifConditional, "IF_Conditional"),
MEMBER(thenActions, "THEN_Actions"));

REFLECT(BASEDCLASS(AIAction, AIA_SetActive),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_SetInactive),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_SetPosFromObject),
MEMBER(activeValue, "ActiveValue"),
MEMBER(objectToMove, "Object_To_Move"),
MEMBER(offsetX, "Offset_x"),
MEMBER(offsetY, "Offset_y"),
MEMBER(offsetZ, "Offset_z"),
MEMBER(referenceObject, "Reference_Object"),
MEMBER(renderValue, "RenderValue"),
MEMBER(setActiveState, "SetActiveState"),
MEMBER(setRenderState, "SetRenderState"));

REFLECT(BASEDCLASS(AIAction, AIA_SpawnGroup_StartSpawning),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_SpawnGroup_StopSpawning),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Spawner_StartSpawning),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Spawner_StopSpawning),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Squad_AddMember),
MEMBER(squad, "Squad"),
MEMBER(member, "Member"));

REFLECT(BASEDCLASS(AIAction, AIA_Squad_AttatchOnPath),
MEMBER(squad, "Squad"),
MEMBER(entity, "Entity"));

REFLECT(BASEDCLASS(AIAction, AIA_Squad_Detatch),
MEMBER(squad, "Squad"));

REFLECT(BASEDCLASS(AIAction, AIA_Squad_GoToHotSpots),
MEMBER(squad, "Squad"),
MEMBER(hotSpotType, "HotSpotType"),
MEMBER(radius, "Radius"));

REFLECT(BASEDCLASS(AIAction, AIA_Squad_RemoveMember),
MEMBER(squad, "Squad"),
MEMBER(member, "Member"));

REFLECT(BASEDCLASS(AIAction, AIA_Squad_SetFormation),
MEMBER(target, "Target"),
MEMBER(formation, "Formation"));

REFLECT(BASEDCLASS(AIAction, AIA_Squad_SetFormationSpacing),
MEMBER(target, "Target"),
MEMBER(formationSpacing, "Formation_Spacing"));

REFLECT(BASEDCLASS(AIAction, AIA_Squad_SetMode),
MEMBER(target, "Target"),
MEMBER(mode, "Mode"));

REFLECT(BASEDCLASS(AIAction, AIA_Squad_SetWayPoint),
MEMBER(target, "Target"),
MEMBER(waypoint, "Waypoint"));

REFLECT(BASEDCLASS(AIAction, AIA_StampedeRumble),
MEMBER(enable, "Enable"));

REFLECT(BASEDCLASS(AIAction, AIA_StaticNukeLauncher_Fire),
MEMBER(staticNukeLauncher, "StaticNukeLauncher"));

REFLECT(BASEDCLASS(AIAction, AIA_Switch_SwitchOff),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Switch_SwitchOn),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_WarriorRoyal_SonicRoar),
MEMBER(target, "Target"),
MEMBER(actions, "Actions"));

REFLECT(BASEDCLASS(AIAction, AIA_WarriorRoyal_SonicRoarAttack),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(AIAction, AIA_Warrior_SetIgnoreRadius),
MEMBER(target, "Target"),
MEMBER(deltaY, "DeltaY"),
MEMBER(ignoreRadius, "IgnoreRadius"),
MEMBER(useDeltaY, "UseDeltaY"));

REFLECT(BASEDCLASS(AIAction, AIA_Warrior_SetMaxSpeed),
MEMBER(target, "Target"),
MEMBER(allowFastRun, "AllowFastRun"));

REFLECT(BASEDCLASS(AIAction, AIA_Warrior_SetWPNarrow),
MEMBER(target, "Target"),
MEMBER(narrow, "Narrow"));

REFLECT(BASEDCLASS(AIAction, AIA_Warrior_SetZigzag),
MEMBER(target, "Target"),
MEMBER(zigzag, "Zigzag"));

REFLECT(BASEDCLASS(AIAction, AIA_Warrior_SwitchOverrideAnimSet),
MEMBER(target, "Target"),
MEMBER(animSet, "AnimSet"));

REFLECT(BASEDCLASS(ResourcePack, AIC_Counter_Equals),
MEMBER(target, "Target"),
MEMBER(value, "Value"));

REFLECT(BASEDCLASS(ResourcePack, AIC_Counter_LessThan),
MEMBER(target, "Target"),
MEMBER(value, "Value"));

REFLECT(BASEDCLASS(ResourcePack, AIC_Counter_MoreThan),
MEMBER(target, "Target"),
MEMBER(value, "Value"));

REFLECT(BASEDCLASS(AIAction, AIC_Entity_IsAlive),
MEMBER(target, "Target"));
