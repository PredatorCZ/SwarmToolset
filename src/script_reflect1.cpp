#include "script/chat.hpp"
#include "script/collidable.hpp"
#include "script/game.hpp"
#include "script/material.hpp"
#include "script/object.hpp"
#include "script/objective.hpp"
#include "script/particle.hpp"
#include "script/particle_def.hpp"
#include "script/shader.hpp"
#include "script/sound.hpp"
#include "script/world.hpp"

#include "spike/reflect/detail/reflector_class.hpp"
#include "spike/reflect/detail/reflector_enum.hpp"

template <> struct _getType<AFileInfo> : reflTypeDefault_ {
  static constexpr REFType TYPE = REFType::String;
  static constexpr uint8 SIZE = 0;
};

REFLECT(ENUMERATION(COLLIDABLE),
ENUM_MEMBER(COLLIDABLE_NONE),
ENUM_MEMBER(COLLIDABLE_BOUNDINGBOX),
ENUM_MEMBER(COLLIDABLE_BONEBOXES),
ENUM_MEMBER(COLLIDABLE_POLYGON)
);

REFLECT(ENUMERATION(UIUNLOCKABLE),
ENUM_MEMBER(UIUNLOCKABLE_TYPE_NONE),
ENUM_MEMBER(UIUNLOCKABLE_TYPE_IMAGE),
ENUM_MEMBER(UIUNLOCKABLE_TYPE_MOVIE),
ENUM_MEMBER(UIUNLOCKABLE_TYPE_LEVEL),
ENUM_MEMBER(UIUNLOCKABLE_TYPE_NUM_TYPES)
);

REFLECT(ENUMERATION(GITYPE),
ENUM_MEMBER(GITYPE_SINGLEPLAYER),
ENUM_MEMBER(GITYPE_MULTIPLAYER),
ENUM_MEMBER(GITYPE_SINGLEPLAYER_EXTRAS),
ENUM_MEMBER(GITYPE_MULTIPLAYER_EXTRAS),
ENUM_MEMBER(GITYPE_NUM_TYPES)
);

REFLECT(ENUMERATION(SubObjectivePositionType),
ENUM_MEMBER(None),
ENUM_MEMBER(WorldPosition),
ENUM_MEMBER(WorldObject)
);

REFLECT(ENUMERATION(LIGHT),
ENUM_MEMBER(LIGHT_DIRECTIONAL),
ENUM_MEMBER(LIGHT_POINT),
ENUM_MEMBER(LIGHT_SPOT)
);

REFLECT(ENUMERATION(ObjectiveState),
ENUM_MEMBER(Nostate),
ENUM_MEMBER(Preamble),
ENUM_MEMBER(Main),
ENUM_MEMBER(Success),
ENUM_MEMBER(Partialfailure),
ENUM_MEMBER(Totalfailure),
ENUM_MEMBER(Complete)
);

REFLECT(ENUMERATION(RenderTarget),
ENUM_MEMBER(SCREEN),
ENUM_MEMBER(GLOW),
ENUM_MEMBER(DISTORT)
);

REFLECT(ENUMERATION(SoundType),
ENUM_MEMBER(SpecialFX),
ENUM_MEMBER(Music),
ENUM_MEMBER(Speech)
);

REFLECT(ENUMERATION(EnvironmentalFX),
ENUM_MEMBER(None),
ENUM_MEMBER(Plain),
ENUM_MEMBER(PaddedCell),
ENUM_MEMBER(Room),
ENUM_MEMBER(Bathroom),
ENUM_MEMBER(LivingRoom),
ENUM_MEMBER(StoneRoom),
ENUM_MEMBER(Auditorium),
ENUM_MEMBER(ConcertHall),
ENUM_MEMBER(Cave),
ENUM_MEMBER(Arena),
ENUM_MEMBER(Hangar),
ENUM_MEMBER(Hallway),
ENUM_MEMBER(StoneCorridor),
ENUM_MEMBER(Alley),
ENUM_MEMBER(Forest),
ENUM_MEMBER(City),
ENUM_MEMBER(Mountains),
ENUM_MEMBER(Quarry),
ENUM_MEMBER(Generic),
ENUM_MEMBER(SewerPipe),
ENUM_MEMBER(Underwater),
ENUM_MEMBER(Drugged),
ENUM_MEMBER(Dizzy),
ENUM_MEMBER(Psychotic),
ENUM_MEMBER(Unused)
);

REFLECT(ENUMERATION(ShadowGeneration),
ENUM_MEMBER(ALL_MATERIALS_SHADOW),
ENUM_MEMBER(NO_MATERIALS_SHADOW),
ENUM_MEMBER(PER_MATERIAL_SHADOW)
);

REFLECT(ENUMERATION(ChatLinePriority),
ENUM_MEMBER(Low),
ENUM_MEMBER(Medium),
ENUM_MEMBER(High)
);

REFLECT(ENUMERATION(ModelType),
ENUM_MEMBER(Generic),
ENUM_MEMBER(Terrain),
ENUM_MEMBER(Instanced),
ENUM_MEMBER(FirstPerson)
);

REFLECT(ENUMERATION(LightInfluence),
ENUM_MEMBER(Terrain),
ENUM_MEMBER(Models),
ENUM_MEMBER(Both)
);

REFLECT(ENUMERATION(LightPriority),
ENUM_MEMBER(Lowest),
ENUM_MEMBER(Low),
ENUM_MEMBER(Normal),
ENUM_MEMBER(High),
ENUM_MEMBER(Highest)
);

FWDREFLECTCLASS(ResourceRef);
FWDREFLECTCLASS(AABB);
FWDREFLECTCLASS(CollisionFlags);

REFLECT(BASEDCLASS(ResourcePack, CompiledTerrain));

REFLECT(CLASS(ResourceSound3DParameters),
MEMBER(minDistance, "MinDistance"),
MEMBER(maxDistance, "MaxDistance"),
MEMBER(cullByDistance, "CullByDistance"));

REFLECT(BASEDCLASS(ResourcePack, ResourceSound),
MEMBER(filename, "Filename"),
MEMBER(type, "Type"),
MEMBER(streaming, "Streaming"),
MEMBER(positional3D, "Positional_3D"),
MEMBER(stereo, "Stereo"),
MEMBER(oggVorbis, "OggVorbis"),
MEMBER(limit, "Limit"),
MEMBER(priority, "Priority"),
MEMBER(default3DParameters, "Default3DParameters"),
MEMBER(semitoneShift, "SemitoneShift"),
MEMBER(random, "Random"),
MEMBER(frontEndSound, "FrontEndSound"),
MEMBER(startDelay, "StartDelay"),
MEMBER(defaultVolume, "Default Volume"));

REFLECT(BASEDCLASS(ResourcePack, ResourceSoundRandomised),
MEMBER(limit, "Limit"),
MEMBER(sounds,"Sounds")
);

REFLECT(BASEDCLASS(ResourcePack, AudioTweaks),
MEMBER(rolloff, "Rolloff"),
MEMBER(distanceFactor, "DistanceFactor"),
MEMBER(dopplerFactor, "DopplerFactor"),
MEMBER(volumeScalingNonPositional, "VolumeScaling_NonPositional"),
MEMBER(musicVolume, "MusicVolume"),
MEMBER(cullDistance, "CullDistance"),
MEMBER(prioritySoundScalingFactor, "PrioritySoundScalingFactor"));

REFLECT(BASEDCLASS(WorldObject, AmbientSoundObject),
MEMBER(playSound, "Play Sound"),
MEMBER(startImmediately, "Start Immediately"),
MEMBER(position, "Position"),
MEMBER(loopDelayLength, "Loop Delay Length"),
MEMBER(atmospheric, "Atmospheric"));

REFLECT(CLASS(ResourceObjectCollidableInfoTypes),
MEMBER(collidable0Near, "Collidable_0_Near"),
MEMBER(collidable1, "Collidable_1"),
MEMBER(collidable2, "Collidable_2"),
MEMBER(collidable3Far, "Collidable_3_Far"));

REFLECT(CLASS(ResourceObjectCollidableInfoRanges),
MEMBER(range01, "Range_0_1"),
MEMBER(range12, "Range_1_2"),
MEMBER(range23, "Range_2_3"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectCollidableInfo),
MEMBER(collidableTypes, "Collidable_Types"),
MEMBER(autoRanges, "Auto_Ranges"),
MEMBER(collidableRanges, "Collidable_Ranges"));

REFLECT(BASEDCLASS(ResourcePack, ParticleSystemGeneric),
MEMBER(particleResource, "ParticleResource"),
MEMBER(soundStartLoop, "SoundStart"),
MEMBER(soundStartLoop, "SoundStop"),
MEMBER(soundStartLoop, "SoundStartLoop"),
MEMBER(soundStopLoop, "SoundStopLoop"),
MEMBER(autoStart, "AutoStart"),
MEMBER(minOnTime, "MinOnTime"),
MEMBER(maxOnTime, "MaxOnTime"),
MEMBER(minOffTime, "MinOffTime"),
MEMBER(maxOffTime, "MaxOffTime"),
MEMBER(kickupAABB, "KickupAABB"),
MEMBER(autoDirection, "AutoDirection"),
MEMBER(particleSystemGenericQuicksave,"QUICKSAVE_ParticleSystemGeneric"));

REFLECT(BASEDCLASS(ResourcePack, ParticleSystemDustStorm),
MEMBER(particleResource, "ParticleResource"),
MEMBER(kickupAABB, "KickupAABB"),
MEMBER(active, "Active"),
MEMBER(particleSystemDustStormQuicksave,"QUICKSAVE_ParticleSystemDustStorm")
);

REFLECT(BASEDCLASS(ResourcePack, ParticleSystemDust),
MEMBER(particleResource, "ParticleResource"),
MEMBER(kickupAABB, "KickupAABB"),
MEMBER(kickupRate, "KickupRate"),
MEMBER(kickupVelocity, "KickupVelocity"),
MEMBER(kickupVariance, "KickupVariance"),
MEMBER(bStartPopulated, "bStartPopulated"),
MEMBER(autoDelete, "AutoDelete"),
MEMBER(active, "Active"),
MEMBER(timeActive, "TimeActive"),
MEMBER(startDelay, "StartDelay"),
MEMBER(particleSystemDustQuicksave,"QUICKSAVE_ParticleSystemDust"));

REFLECT(BASEDCLASS(ResourcePack, ParticleSystemNuclearBlast),
MEMBER(active, "Active"),
MEMBER(particleResourceControl, "ParticleResourceControl"),
MEMBER(particleResource1, "ParticleResource1"),
MEMBER(particleResource2, "ParticleResource2"),
MEMBER(particleResource3, "ParticleResource3"),
MEMBER(particleResource4, "ParticleResource4"),
MEMBER(particleResource5, "ParticleResource5"),
MEMBER(particleResource6, "ParticleResource6"),
MEMBER(particleResource7, "ParticleResource7"),
MEMBER(particleResource8, "ParticleResource8"),
MEMBER(particleResource9, "ParticleResource9"),
MEMBER(particleResource10, "ParticleResource10"),
MEMBER(particleSystemNuclearBlastQuicksave,"QUICKSAVE_ParticleSystemNuclearBlast"));

REFLECT(CLASS(WorldObjectContextShadowVolume),
MEMBER(useStaticVolume, "UseStaticVolume"),
MEMBER(extrusionDepth, "ExtrusionDepth"));

REFLECT(CLASS(WorldObjectContextContextSplitting),
MEMBER(allowSplitting, "AllowSplitting"),
MEMBER(maxTreeDepth, "MaxTreeDepth"));

REFLECT(BASEDCLASS(WorldObject, WorldObjectContext),
MEMBER(aabb, "AABB"),
MEMBER(flags, "Flags"),
MEMBER(shadowVolume, "ShadowVolume"),
MEMBER(terrainShadow, "TerrainShadow"),
MEMBER(contextSplitting, "ContextSplitting"),
MEMBER(inheritLights, "InheritLights"),
MEMBER(transition, "Transition"),
MEMBER(allLights, "All Lights"),
MEMBER(environmentalFX, "EnvironmentalFX"),
MEMBER(audioFXResource, "AudioFXResource"),
MEMBER(eaxVolume, "EAX Volume"));

REFLECT(CLASS(WorldObjectLightContextOverride),
MEMBER(key),
MEMBER(value));

REFLECT(BASEDCLASS(WorldObject, WorldObjectLight),
MEMBER(type, "Type"),
MEMBER(createsShadows, "CreatesShadows"),
MEMBER(ambient, "Ambient"),
MEMBER(diffuse, "Diffuse"),
MEMBER(specular, "Specular"),
MEMBER(range, "Range"),
MEMBER(angle, "Angle"),
MEMBER(aspectRatio, "AspectRatio"),
MEMBER(multiplier, "Multiplier"),
MEMBER(position, "Position"),
MEMBER(direction, "Direction"),
MEMBER(localX, "LocalX"),
MEMBER(on, "On"),
MEMBER(priority, "Priority"),
MEMBER(influence, "Influence"),
MEMBER(dynamic, "Dynamic"),
MEMBER(attenuation, "Attenuation"),
MEMBER(spotTexture, "Spot texture"),
MEMBER(spotOffset, "SpotOffset"),
MEMBER(modifiers, "Modifiers"),
MEMBER(contextOverrides, "ContextOverrides_New")
);

REFLECT(BASEDCLASS(WorldObject, WorldObjectUsableAABB),
MEMBER(aabb, "AABB"),
MEMBER(targetObject, "TargetObject"),
MEMBER(usePrompt, "UsePrompt"),
MEMBER(cannotUsePrompt, "CannotUsePrompt"),
MEMBER(activeArea, "ActiveArea"),
MEMBER(invItem, "InvItem"),
MEMBER(worldObjectUsableAABBQuicksave,"QUICKSAVE_WorldObjectUsableAABB"));

REFLECT(CLASS(WorldMatrix),
MEMBER(v[0].x, "_11"),
MEMBER(v[0].y, "_12"),
MEMBER(v[0].z, "_13"),
MEMBER(v[0].w, "_14"),
MEMBER(v[1].x, "_21"),
MEMBER(v[1].y, "_22"),
MEMBER(v[1].z, "_23"),
MEMBER(v[1].w, "_24"),
MEMBER(v[2].x, "_31"),
MEMBER(v[2].y, "_32"),
MEMBER(v[2].z, "_33"),
MEMBER(v[2].w, "_34"),
MEMBER(v[3].x, "_41"),
MEMBER(v[3].y, "_42"),
MEMBER(v[3].z, "_43"),
MEMBER(v[3].w, "_44")
);

REFLECT(BASEDCLASS(WorldObjectModel, ModelTerrain),
MEMBER(worldMatrix, "WorldMatrix"));

REFLECT(CLASS(WorldObjectPortalVertices),
MEMBER(v0),
MEMBER(v1),
MEMBER(v2),
MEMBER(v3));

REFLECT(BASEDCLASS(ResourcePack, WorldObjectPortal),
MEMBER(active, "Active"),
MEMBER(portalVertices, "PortalVertices"),
MEMBER(observerContextRef, "ObserverContextRef"),
MEMBER(destinationContextRef, "DestinationContextRef"),
MEMBER(propagateVisibility, "PropagateVisibility"),
MEMBER(adjoiningPortal, "AdjoiningPortal"));

REFLECT(BASEDCLASS(ModelDetailDynamic, ModelAnimated),
MEMBER(animationSpeed, "AnimationSpeed"),
MEMBER(looping, "Looping"),
MEMBER(animation, "Animation"),
MEMBER(playSound, "PlaySound"),
MEMBER(sound, "Sound"),
MEMBER(soundList, "Sound List"),
MEMBER(soundBone, "SoundBone"),
MEMBER(loopOnAnim, "LoopOnAnim"),
MEMBER(materialEffects, "MaterialEffects"),
MEMBER(modelAnimatedQuicksave,"QUICKSAVE_ModelAnimated"),
MEMBER(switchTriggers, "SwitchTriggers"),
MEMBER(quicksave,"QUICKSAVE")
);

REFLECT(CLASS(AtmosphericsWindCurrent),
MEMBER(direction, "Direction"),
MEMBER(height, "Height"),
MEMBER(turbulence, "Turbulence"),
MEMBER(changePeriod, "Change Period"),
MEMBER(maximumTurbulenceChange, "Maximum Turbulence Change"));

REFLECT(CLASS(AtmosphericsWind),
MEMBER(direction, "Direction"),
MEMBER(currentBlockSize, "Current Block Size"),
MEMBER(current01, "Current01"),
MEMBER(current02, "Current02"),
MEMBER(current03, "Current03")
);

REFLECT(CLASS(AtmosphericsSoftShadows),
MEMBER(blurIterations, "BlurIterations"),
MEMBER(centerWeight, "CenterWeight"),
MEMBER(sideWeight, "SideWeight"),
MEMBER(texelOffset, "TexelOffset"));

REFLECT(BASEDCLASS(Resource, Atmospherics),
MEMBER(RayleighColour, "Rayleigh Colour"),
MEMBER(MieColour, "Mie Colour"),
MEMBER(MieFactor, "Mie Factor"),
MEMBER(FogHalfDistance, "Fog Half Distance"),
MEMBER(FogPercentMie, "Fog Percent Mie"),
MEMBER(InScatteringModifier, "InScattering Modifier"),
MEMBER(wind, "Wind"),
MEMBER(sunLight, "SunLight"),
MEMBER(softShadows, "SoftShadows"),
MEMBER(indoorAmbient, "IndoorAmbient"),
MEMBER(indoorDiffuse, "IndoorDiffuse"),
MEMBER(indoorSpecular, "IndoorSpecular"),
MEMBER(viewingDistance, "ViewingDistance"));

REFLECT(BASEDCLASS(ModelDetailDynamic, ModelDestructable),
MEMBER(destructableObjectResource, "DestructableObjectResource"),
MEMBER(bonusAmmoPickupResource, "BonusAmmoPickupResource"),
MEMBER(bonusAmmoNum, "BonusAmmoNum"),
MEMBER(health, "Health"));

REFLECT(BASEDCLASS(Resource, LevelStats),
MEMBER(loadingImage, "LoadingImage"),
MEMBER(numObjects, "NumObjects"));

REFLECT(BASEDCLASS(Resource, GameSessionDocument),
MEMBER(authorName, "AuthorName"),
MEMBER(creationDateTime, "CreationDateTime"),
MEMBER(lastSaveDateTime, "LastSaveDateTime"));

REFLECT(CLASS(GameSessionFilesDirs),
MEMBER(levelMovie, "LevelMovie"),
MEMBER(levelBriefingImage, "LevelBriefingImage"),
MEMBER(missionSuccessImage, "MissionSuccessImage"),
MEMBER(missionFailImage, "MissionFailImage"),
MEMBER(missionCourtMarshallImage, "MissionCourtMarshallImage"),
MEMBER(interMissionImage1, "InterMissionImage1"),
MEMBER(interMissionImage2, "InterMissionImage2"),
MEMBER(missionSuccessMovie, "MissionSuccessMovie"),
MEMBER(missionFailMovie, "MissionFailMovie"),
MEMBER(missionFailCourtMarshallMovie, "MissionFailCourtMarshallMovie"));

REFLECT(CLASS(GameSessionResources),
MEMBER(briefingSpeechResourceName, "BriefingSpeechResourceName"),
MEMBER(successSpeechResourceName, "SuccessSpeechResourceName"),
MEMBER(failureSpeechResourceName, "FailureSpeechResourceName"),
MEMBER(courtMarshallSpeechResourceName, "CourtMarshallSpeechResourceName"),
MEMBER(briefingText, "BriefingText"),
MEMBER(objectivesText, "ObjectivesText"),
MEMBER(successText, "SuccessText"),
MEMBER(failureText, "FailureText"),
MEMBER(courtMarshallText, "CourtMarshallText"));

REFLECT(CLASS(GameSessionCampaign),
MEMBER(parTime, "ParTime"),
MEMBER(slBestTime, "SLBestTime"));

REFLECT(BASEDCLASS(Resource, GameSession),
MEMBER(filesDirs,"Global_Scripts_Excluded"),
MEMBER(filesDirs, "FilesDirs"),
MEMBER(resources, "Resources"),
MEMBER(campaign, "Campaign"),
MEMBER(levelAttack, "LevelAttack"));

REFLECT(BASEDCLASS(ResourcePack, UIUnlockableExtra),
MEMBER(unlockableExtraId, "UnlockableExtraID"),
MEMBER(unlockableExtraType, "UnlockableExtraType"),
MEMBER(filename, "Filename"),
MEMBER(displayString, "DisplayString"),
MEMBER(unlockingLevelID, "UnlockingLevelID"),
MEMBER(unlockableHow, "UnlockableHow"),
MEMBER(unlockValue, "UnlockValue"));

REFLECT(CLASS(GameInfoFileDirs),
MEMBER(directory, "Directory"),
MEMBER(previewImage, "PreviewImage"));

REFLECT(BASEDCLASS(ResourcePack, ChatScript),
MEMBER(lines, "Lines"),
MEMBER(actions, "Actions"));

REFLECT(BASEDCLASS(Resource, GameInfo),
MEMBER(gameInfoType, "GameInfoType"),
MEMBER(multiplayerGameType, "MULTIPLAYERGAMETYPE"),
MEMBER(id, "ID"),
MEMBER(displayString, "DisplayString"),
MEMBER(allowedInLevelAttack, "AllowedInLevelAttack"),
MEMBER(playableInDemo, "PlayableInDemo"),
MEMBER(filesDirs, "FilesDirs"));

REFLECT(CLASS(ResourceObjectModelMaterial),
MEMBER(key),
MEMBER(value));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectModel),
MEMBER(fileName, "FileName"),
MEMBER(shadowGeneration, "Shadow Generation"),
MEMBER(animated, "Animated"),
MEMBER(defaultPhysicalMaterial, "DefaultPhysicalMaterial"),
MEMBER(collidableResource, "CollidableResource"),
MEMBER(modelType, "Model Type"),
MEMBER(animationSets, "Animation Sets"),
MEMBER(boneNames, "Bone Names"),
MEMBER(debugNumComponents, "Debug_Num_Components"),
MEMBER(baseModelAnimSets, "Base_Model_AnimSets"),
MEMBER(materials, "Materials"),
MEMBER(physicalMaterials, "PhysicalMaterials")
);

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectAnimationSet),
MEMBER(animationType, "Animation Type"),
MEMBER(animations, "Animations"),
MEMBER(refModel, "Ref_Model"));

REFLECT(CLASS(ResourceObjectAnimationCompression),
MEMBER(scaleTolerance, "Scale Tolerance"),
MEMBER(rotateTolerance, "Rotate Tolerance"),
MEMBER(positionTolerance, "Position Tolerance"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectAnimation),
MEMBER(fileName, "FileName"),
MEMBER(length, "Length"),
MEMBER(soundProbability, "SoundProbability"),
MEMBER(sound, "Sound"),
MEMBER(soundList, "Sound List"),
MEMBER(soundBone, "SoundBone"),
MEMBER(animationSet, "Animation Set"),
MEMBER(boneNameExtension, "Bone Name Extension"),
MEMBER(compression, "Compression"));

REFLECT(CLASS(ResourceAmmoPickupAmount),
MEMBER(bullet, "AIAT_BULLET"),
MEMBER(grenade, "AIAT_GRENADE"),
MEMBER(shotgun, "AIAT_SHOTGUN"),
MEMBER(rocket, "AIAT_ROCKET"),
MEMBER(missile, "AIAT_MISSILE"),
MEMBER(slug, "AIAT_SLUG"),
MEMBER(handgrenade, "AIAT_HANDGRENADE"));

REFLECT(BASEDCLASS(ResourcePack, ResourceAmmoPickup),
MEMBER(model, "Model"),
MEMBER(pickupAmount, "PickupAmount"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectDropPod),
MEMBER(soundDescentResource, "SoundDescentResource"),
MEMBER(soundBurstResource, "SoundBurstResource"),
MEMBER(dataKeys, "DataKeys"),
MEMBER(podDensity, "PodDensity"),
MEMBER(blastVal, "BlastVal"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectDropPodKey),
MEMBER(keyTime, "KeyTime"),
MEMBER(shake, "Shake"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectRocketTargetNode),
MEMBER(boneName, "BoneName"),
MEMBER(nodePos, "NodePos"),
MEMBER(nodeSize, "NodeSize"),
MEMBER(testSize, "TestSize"));

REFLECT(BASEDCLASS(ResourcePack, ResourceDecal),
MEMBER(texDiffuse, "TexDiffuse"),
MEMBER(texNormal, "TexNormal"),
MEMBER(ambient, "Ambient"),
MEMBER(diffuse, "Diffuse"),
MEMBER(specular, "Specular"),
MEMBER(minU, "MinU"),
MEMBER(minV, "MinV"),
MEMBER(maxU, "MaxU"),
MEMBER(maxV, "MaxV"),
MEMBER(sizeAverage, "SizeAverage"),
MEMBER(sizeRange, "SizeRange"),
MEMBER(lifeTime, "LifeTime"),
MEMBER(fadeTime, "FadeTime"),
MEMBER(iconColour, "IconColour"));

REFLECT(CLASS(ResourceDestructableObjectDamageStrength),
MEMBER(PIERCESOFT, "DAMAGETYPE_PIERCESOFT"),
MEMBER(PIERCEHARD, "DAMAGETYPE_PIERCEHARD"),
MEMBER(SLASH, "DAMAGETYPE_SLASH"),
MEMBER(PUNCH, "DAMAGETYPE_PUNCH"),
MEMBER(BLAST, "DAMAGETYPE_BLAST"),
MEMBER(HEAT, "DAMAGETYPE_HEAT"),
MEMBER(CORROSIVE, "DAMAGETYPE_CORROSIVE"),
MEMBER(ELECTRICITY, "DAMAGETYPE_ELECTRICITY"),
MEMBER(PSIOPS, "DAMAGETYPE_PSIOPS"));

REFLECT(CLASS(ResourceDestructableObjectPiecesMovement),
MEMBER(pieceDensity, "PieceDensity"),
MEMBER(blastStrength, "BlastStrength"),
MEMBER(blastExplode, "BlastExplode"),
MEMBER(blastExplodeRadius, "BlastExplodeRadius"),
MEMBER(flamingBits, "FlamingBits"));

REFLECT(BASEDCLASS(ResourcePack, ResourceDestructableObject),
MEMBER(modelWhole, "ModelWhole"),
MEMBER(modelDead, "ModelDead"),
MEMBER(modelPieces, "ModelPieces"),
MEMBER(soundDeath, "SoundDeath"),
MEMBER(damageStrength, "DamageStrength"),
MEMBER(dynamic, "Dynamic"),
MEMBER(setOnFireAtHealthPercent, "SetOnFireAtHealthPercent"),
MEMBER(selfDamageWhenOnFire, "SelfDamageWhenOnFire"),
MEMBER(piecesMovement, "PiecesMovement"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXBabyPlasma),
MEMBER(soundBoltFire, "SoundBoltFire"),
MEMBER(soundBoltExplode, "SoundBoltExplode"),
MEMBER(scaleFactor, "ScaleFactor"),
MEMBER(materialHead, "MaterialHead"),
MEMBER(materialRear, "MaterialRear"),
MEMBER(materialBody, "MaterialBody"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXBlaster),
MEMBER(soundDeath, "SoundDeath"),
MEMBER(material, "Material"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXBomber),
MEMBER(soundGlobalEngine, "SoundGlobal_Engine"),
MEMBER(soundGlobalAscend, "SoundGlobal_Ascend"),
MEMBER(soundGlobalDescend, "SoundGlobal_Descend"),
MEMBER(soundGlobalHover, "SoundGlobal_Hover"),
MEMBER(soundGlobalFlyBy, "SoundGlobal_FlyBy"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXElectricFence),
MEMBER(soundElectricFence, "SoundElectricFence"),
MEMBER(soundElectricFencePost, "SoundElectricFencePost"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXFireball),
MEMBER(soundBoltFire, "SoundBoltFire"),
MEMBER(soundBoltExplode, "SoundBoltExplode"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXHopperFirefly),
MEMBER(soundFireSpurt, "SoundFireSpurt"),
MEMBER(material, "Material"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXHuman),
MEMBER(soundGibBounce, "SoundGibBounce"),
MEMBER(materialMPMarauder, "MaterialMPMarauder"),
MEMBER(materialMPMarauderShield, "MaterialMPMarauderShield"));

REFLECT(CLASS(ResourceObjectSFXHandGrenadeMouthTiming),
MEMBER(ONStart, "ON_start"),
MEMBER(ONEEnd, "ON_end"),
MEMBER(LINEStart, "LINE_start"),
MEMBER(LINEEnd, "LINE_end"),
MEMBER(FOURStart, "FOUR_start"),
MEMBER(FOUREnd, "FOUR_end"),
MEMBER(THREEStart, "THREE_start"),
MEMBER(THREEEnd, "THREE_end"),
MEMBER(TWOStart, "TWO_start"),
MEMBER(THREEEnd, "TWO_end"),
MEMBER(ONEStart, "ONE_start"),
MEMBER(ONEEnd, "ONE_end"),
MEMBER(ARMEDStart, "ARMED_start"),
MEMBER(ARMEDEnd, "ARMED_end"),
MEMBER(EMStart, "EM_start"),
MEMBER(EMEnd, "EM_end"),
MEMBER(ERStart, "ER_start"),
MEMBER(EREnd, "ER_end"),
MEMBER(GENStart, "GEN_start"),
MEMBER(GENEnd, "GEN_end"),
MEMBER(CYStart, "CY_start"),
MEMBER(CYEnd, "CY_end"),
MEMBER(SHUTStart, "SHUT_start"),
MEMBER(SHUTEnd, "SHUT_end"),
MEMBER(DOWNStart, "DOWN_start"),
MEMBER(DOWNEnd, "DOWN_end"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXHandGrenade),
MEMBER(soundInHand, "SoundInHand"),
MEMBER(soundThrown, "SoundThrown"),
MEMBER(activateTime, "ActivateTime"),
MEMBER(flashFrequency, "FlashFrequency"),
MEMBER(brightnessOff, "BrightnessOff"),
MEMBER(brightnessActivate, "BrightnessActivate"),
MEMBER(brightnessOn, "BrightnessOn"),
MEMBER(brightnessFlash0, "BrightnessFlash0"),
MEMBER(brightnessFlash1, "BrightnessFlash1"),
MEMBER(mouthTalkFrequency, "MouthTalkFrequency"),
MEMBER(mouthWaveFrequency, "MouthWaveFrequency"),
MEMBER(talkTimeDeactivate, "TalkTimeActivate"),
MEMBER(talkTimeDeactivate, "TalkTimeDeactivate"),
MEMBER(mouthTiming, "MouthTiming"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXHopper),
MEMBER(material, "Material"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXMissile),
MEMBER(soundShot, "SoundShot"),
MEMBER(soundEmpty, "SoundEmpty"),
MEMBER(soundReload, "SoundReload"),
MEMBER(soundExplode, "SoundExplode"),
MEMBER(modeSwitch1, "ModeSwitch1"),
MEMBER(modeSwitch2, "ModeSwitch2"),
MEMBER(guidanceTone, "GuidanceTone"),
MEMBER(engine, "Engine"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXMissileBomberBomb),
MEMBER(soundGlobalEngine, "SoundGlobal_Engine"),
MEMBER(soundGlobalAscend, "SoundGlobal_Ascend"),
MEMBER(soundGlobalDescend, "SoundGlobal_Descend"),
MEMBER(soundGlobalHover, "SoundGlobal_Hover"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXMoritiaMk2Carbine),
MEMBER(soundShotPrimary, "SoundShotPrimary"),
MEMBER(soundTailoffPrimary, "SoundTailoffPrimary"),
MEMBER(soundShotSecondary, "SoundShotSecondary"),
MEMBER(soundTailoffSecondary, "SoundTailoffSecondary"),
MEMBER(soundEmpty, "SoundEmpty"),
MEMBER(soundReload, "SoundReload"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXMoritiaMk2Grenade),
MEMBER(soundShotPrimary, "SoundShotPrimary"),
MEMBER(soundTailoffPrimary, "SoundTailoffPrimary"),
MEMBER(soundShotSecondary, "SoundShotSecondary"),
MEMBER(soundEmpty, "SoundEmpty"),
MEMBER(soundReload, "SoundReload"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXMoritiaMk2Shotgun),
MEMBER(soundShotPrimary, "SoundShotPrimary"),
MEMBER(soundTailoffPrimary, "SoundTailoffPrimary"),
MEMBER(soundShotSecondary, "SoundShotSecondary"),
MEMBER(soundEmpty, "SoundEmpty"),
MEMBER(soundReload, "SoundReload"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXMoritiaMk2Zoom),
MEMBER(soundShotPrimary, "SoundShotPrimary"),
MEMBER(soundTailoffPrimary, "SoundTailoffPrimary"),
MEMBER(soundShotSecondary, "SoundShotSecondary"),
MEMBER(soundTailoffSecondary, "SoundTailoffSecondary"),
MEMBER(soundEmpty, "SoundEmpty"),
MEMBER(soundReload, "SoundReload"),
MEMBER(soundZoomIn, "SoundZoomIn"),
MEMBER(soundZoomOut, "SoundZoomOut"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXPlasma),
MEMBER(soundBoltFire, "SoundBoltFire"),
MEMBER(soundBoltExplode, "SoundBoltExplode"),
MEMBER(lightColour, "LightColour"),
MEMBER(lightRange, "LightRange"),
MEMBER(materialHead, "MaterialHead"),
MEMBER(materialRear, "MaterialRear"),
MEMBER(materialBody, "MaterialBody"),
MEMBER(materialHeadCower, "MaterialHeadCower"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXMoritiaMk4),
MEMBER(soundShotPrimary, "SoundShotPrimary"),
MEMBER(soundTailoffPrimary, "SoundTailoffPrimary"),
MEMBER(soundShotSecondary, "SoundShotSecondary"),
MEMBER(soundEmpty, "SoundEmpty"),
MEMBER(soundReload, "SoundReload"),
MEMBER(soundVentShort, "SoundVent"),
MEMBER(soundVentShort, "SoundVentShort"),
MEMBER(soundGrenadeExplode, "SoundGrenadeExplode"));

REFLECT(CLASS(ResourceObjectSFXPlayerSoundEffects),
MEMBER(psfxt_INVENTORYPICKUP, "PSFXT_INVENTORYPICKUP"),
MEMBER(psfxt_HOPPERATTACK, "PSFXT_HOPPERATTACK"),
MEMBER(psfxt_WARRIORATTACK, "PSFXT_WARRIORATTACK"),
MEMBER(psfxt_TIGERATTACK, "PSFXT_TIGERATTACK"),
MEMBER(psfxt_TANKERFLAMEATTACK, "PSFXT_TANKERFLAMEATTACK"),
MEMBER(psfxt_HEALTHCRITICAL, "PSFXT_HEALTHCRITICAL"),
MEMBER(psfxt_WEAPONSWITCH, "PSFXT_WEAPONSWITCH"),
MEMBER(psfxt_FOOTFALLLADDERL, "PSFXT_FOOTFALLLADDERL"),
MEMBER(psfxt_FOOTFALLLADDERR, "PSFXT_FOOTFALLLADDERR"),
MEMBER(psfxt_JUMPTAKEOFF, "PSFXT_JUMPTAKEOFF"),
MEMBER(psfxt_JUMPLAND, "PSFXT_JUMPLAND"),
MEMBER(psfxt_HITBLAST, "PSFXT_HITBLAST"),
MEMBER(psfxt_HITBULLET, "PSFXT_HITBULLET"),
MEMBER(psfxt_SHIELDATZERO, "PSFXT_SHIELDATZERO"),
MEMBER(psfxt_SHIELDREGENSTART___NOT_USED___, "PSFXT_SHIELDREGENSTART___NOT_USED___"),
MEMBER(psfxt_SHIELDREGENERATE, "PSFXT_SHIELDREGENERATE"),
MEMBER(psfxt_SHIELDREGENEND___NOT_USED___, "PSFXT_SHIELDREGENEND___NOT_USED___"));

REFLECT(CLASS(ResourceObjectSFXPlayerHitEffectColours),
MEMBER(shield, "Shield"),
MEMBER(health, "Health"),
MEMBER(green, "Green"));

REFLECT(CLASS(ResourceObjectSFXPlayerDamageSoundEffects),
MEMBER(sfxPierceSoft, "SfxPierceSoft"),
MEMBER(sfxPierceHard, "SfxPierceHard"),
MEMBER(sfxSlash, "SfxSlash"),
MEMBER(sfxPunch, "SfxPunch"),
MEMBER(sfxBlast, "SfxBlast"),
MEMBER(sfxHeat, "SfxHeat"),
MEMBER(sfxCorrosive, "SfxCorrosive"),
MEMBER(sfxElectricity, "SfxElectricity"),
MEMBER(sfxPsiOps, "SfxPsiOps"),
MEMBER(sfxLight, "SfxLight"),
MEMBER(sfxSonic, "SfxSonic"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXPlayer),
MEMBER(soundEffects, "SoundEffects"),
MEMBER(hitEffectColours, "HitEffectColours"),
MEMBER(damageSoundEffects, "DamageSoundEffects"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXProjectileFlare),
MEMBER(soundProjectileFlare, "SoundProjectileFlare"),
MEMBER(soundProjectileFlarePop, "SoundProjectileFlarePop"),
MEMBER(lightColour, "LightColour"),
MEMBER(lightRange, "LightRange"),
MEMBER(rangePart1, "Range_Part1"),
MEMBER(rangePart2, "Range_Part2"),
MEMBER(frequency, "Frequency"),
MEMBER(randomPart2, "Random_Part2"),
MEMBER(launchSpeed, "LaunchSpeed"),
MEMBER(fallRate, "FallRate"),
MEMBER(waveMagnitude, "WaveMagnitude"),
MEMBER(range1PcentAtT, "Range1_Pcent_At_T"),
MEMBER(range1T, "Range1_T"),
MEMBER(flickerMinOn, "Flicker_min_on"),
MEMBER(flickerMaxOn, "Flicker_max_on"),
MEMBER(flickerMinOff, "Flicker_min_off"),
MEMBER(flickerMaxOff, "Flicker_max_off"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXRailGun),
MEMBER(soundShotPrimary, "SoundShotPrimary"),
MEMBER(soundEmpty, "SoundEmpty"),
MEMBER(soundReload, "SoundReload"),
MEMBER(soundZoomIn, "SoundZoomIn"),
MEMBER(soundZoomOut, "SoundZoomOut"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXRhino),
MEMBER(materialHead, "MaterialHead"),
MEMBER(materialRear, "MaterialRear"),
MEMBER(materialBody, "MaterialBody"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXHopperRippler),
MEMBER(material, "Material"),
MEMBER(lightOn, "LightOn"),
MEMBER(lightColour, "LightColour"),
MEMBER(lightRange, "LightRange"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXRocket),
MEMBER(soundShotPrimary, "SoundShotPrimary"),
MEMBER(soundShotSecondary, "SoundShotSecondary"),
MEMBER(soundEmpty, "SoundEmpty"),
MEMBER(soundReload, "SoundReload"),
MEMBER(soundExplode, "SoundExplode"),
MEMBER(soundLockOn, "SoundLockOn"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXSentinel),
MEMBER(soundDeath, "SoundDeath"),
MEMBER(material, "Material"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXShotgun),
MEMBER(soundShotPrimary, "SoundShotPrimary"),
MEMBER(soundShotSecondary, "SoundShotSecondary"),
MEMBER(soundEmpty, "SoundEmpty"),
MEMBER(soundReload, "SoundReload"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXStaticGunDouble),
MEMBER(soundShotPrimary, "SoundShotPrimary"),
MEMBER(soundTailoffPrimary, "SoundTailoffPrimary"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXTanker),
MEMBER(materialHead, "MaterialHead"),
MEMBER(materialRear, "MaterialRear"),
MEMBER(materialBody, "MaterialBody"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXTankerBaby),
MEMBER(materialHead, "MaterialHead"),
MEMBER(materialRear, "MaterialRear"),
MEMBER(materialBody, "MaterialBody"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXTigerShard),
MEMBER(materialBody, "MaterialBody"),
MEMBER(materialShields, "MaterialShields"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXTigerSpit),
MEMBER(materialBody, "MaterialBody"),
MEMBER(materialShields, "MaterialShields"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXWarrior),
MEMBER(material, "Material"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXWarriorRoyal),
MEMBER(materialShields, "MaterialShields"),
MEMBER(materialEyes, "MaterialEyes"),
MEMBER(materialRicochet, "MaterialRicochet"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSFXWarriorRoyalX),
MEMBER(materialShields, "MaterialShields"),
MEMBER(materialEyes, "MaterialEyes"),
MEMBER(materialRicochet, "MaterialRicochet"),
MEMBER(materialDeathBone, "MaterialDeathBone"));

REFLECT(CLASS(ResourceMaterialPhysicsProperties),
MEMBER(density, "Density"),
MEMBER(friction, "Friction"),
MEMBER(bounce, "Bounce"));

REFLECT(CLASS(ResourceMaterialDamageProperties),
MEMBER(heatFlammable, "HeatFlammable"),
MEMBER(blastFlammable, "BlastFlammable"));

REFLECT(CLASS(ResourceMaterialDamageEffect),
MEMBER(valueParticle, "ValueParticle"),
MEMBER(particles, "Particles"),
MEMBER(valueDecal, "ValueDecal"),
MEMBER(decals, "Decals"),
MEMBER(valueSound, "ValueSound"),
MEMBER(sounds, "Sounds")
);

REFLECT(CLASS(ResourceMaterialDamageEffects),
MEMBER(pierceSoft, "Pierce_Soft"),
MEMBER(pierceHard, "Pierce_Hard"),
MEMBER(slash, "Slash"),
MEMBER(punch, "Punch"),
MEMBER(blast, "Blast"),
MEMBER(heat, "Heat"),
MEMBER(corrosive, "Corrosive"),
MEMBER(electricity, "Electricity"),
MEMBER(psiOps, "PsiOps"),
MEMBER(light, "Light"),
MEMBER(notSet,"DAMAGETYPENAME_NOTSET"));

REFLECT(CLASS(ResourceMaterialDamagingRates),
MEMBER(pierceSoft, "DAMAGETYPE_PIERCESOFT"),
MEMBER(pierceHard, "DAMAGETYPE_PIERCEHARD"),
MEMBER(slash, "DAMAGETYPE_SLASH"),
MEMBER(punch, "DAMAGETYPE_PUNCH"),
MEMBER(blast, "DAMAGETYPE_BLAST"),
MEMBER(heat, "DAMAGETYPE_HEAT"),
MEMBER(corrosive, "DAMAGETYPE_CORROSIVE"),
MEMBER(electricity, "DAMAGETYPE_ELECTRICITY"),
MEMBER(psiOps, "DAMAGETYPE_PSIOPS"),
MEMBER(light, "DAMAGETYPE_LIGHT"));

REFLECT(BASEDCLASS(ResourcePack, ResourceMaterial),
MEMBER(materialName, "MaterialName"),
MEMBER(collisionFlags, "CollisionType_Flags"),
MEMBER(physicsProperties, "PhysicsProperties"),
MEMBER(damageProperties, "DamageProperties"),
MEMBER(damageEffects, "DamageEffects"),
MEMBER(damagingRates, "DamagingRates"),
MEMBER(dustParticleResource, "DustParticleResource"),
MEMBER(physicsProperties, "PlayerFootstepResource"),
MEMBER(materialName,"HumanFootstepResource"),
MEMBER(materialName,"WarriorBaseFootstepResource"),
MEMBER(dustRingParticleResouce, "DustRingParticleResource"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleTypeSimple),
MEMBER(texture, "Texture"),
MEMBER(emissive, "Emissive"),
MEMBER(srcBlend, "SrcBlend"),
MEMBER(destBlend, "DestBlend"),
MEMBER(ambient, "AmbientColour"),
MEMBER(diffuse, "DiffuseColour"));

REFLECT(CLASS(ResourceParticleExplosionFlame),
MEMBER(startColour,"Flame_Start_Colour"),
MEMBER(endColour,"Flame_End_Colour"),
MEMBER(minU,"Flame_Min_U"),
MEMBER(maxU,"Flame_Max_U"),
MEMBER(minV,"Flame_Min_V"),
MEMBER(maxV,"Flame_Max_V"),
MEMBER(startSize,"Flame_Start_Size"),
MEMBER(endSize,"Flame_End_Size"),
MEMBER(life,"Flame_Life")
);

REFLECT(CLASS(ResourceParticleExplosionSmoke),
MEMBER(minU, "Smoke_Min_U"),
MEMBER(maxU, "Smoke_Max_U"),
MEMBER(minV, "Smoke_Min_V"),
MEMBER(maxV, "Smoke_Max_V"),
MEMBER(startSize, "Smoke_Start_Size"),
MEMBER(endSize, "Smoke_End_Size"),
MEMBER(life, "Smoke_Life")
);

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleExplosion),
MEMBER(flameParticleType, "Flame_ParticleType"),
MEMBER(smokeParticleType, "Smoke_ParticleType"),
MEMBER(soundEffect, "SoundEffect"),
MEMBER(flame, "Flame"),
MEMBER(smoke, "Smoke"),
MEMBER(dontDrawProcessDist, "DontDrawProcessDist"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleAnimatedOABB),
MEMBER(particleType, "ParticleType"),
MEMBER(minU, "Min_U"),
MEMBER(minV, "Min_V"),
MEMBER(maxU, "Max_U"),
MEMBER(maxV, "Max_V"),
MEMBER(startColour, "StartColour"),
MEMBER(endColour, "EndColour"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(rate, "Rate"),
MEMBER(random, "Random"),
MEMBER(life, "Life"),
MEMBER(gravity, "Gravity"),
MEMBER(drag, "Drag"),
MEMBER(fireDamageFactor, "FireDamageFactor"),
MEMBER(dontDrawProcessDist, "DontDrawProcessDist"));

REFLECT(CLASS(ResourceParticleBlastCloudDebris),
MEMBER(particleType, "ParticleType"),
MEMBER(colour, "Colour"),
MEMBER(minU, "Min_U"),
MEMBER(maxU, "Max_U"),
MEMBER(minV, "Min_V"),
MEMBER(maxV, "Max_V"),
MEMBER(size, "Size"));

REFLECT(BASEDCLASS(ResourceParticleBlastCloudDebris, ResourceParticleBlastCloudData),
MEMBER(num, "Num"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleBlastCloud),
MEMBER(debris, "Debris"),
MEMBER(fingers, "Fingers"),
MEMBER(cloud,"Cloud")
);

REFLECT(CLASS(TexCoord),
MEMBER(minU, "Min_u"),
MEMBER(maxU, "Max_u"),
MEMBER(minV, "Min_v"),
MEMBER(maxV, "Max_v"));

REFLECT(CLASS(TexCoord2),
MEMBER(minU, "Min_U"),
MEMBER(maxU, "Max_U"),
MEMBER(minV, "Min_V"),
MEMBER(maxV, "Max_V"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleDust),
MEMBER(particleType, "ParticleType"),
MEMBER(renderTarget, "Render_Target"),
MEMBER(colour, "Colour"),
MEMBER(texCoord, "TexCoord"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(lifeTime, "LifeTime"),
MEMBER(gravity, "Gravity"),
MEMBER(drag, "Drag"),
MEMBER(wind, "Wind"),
MEMBER(diffusion, "Diffusion"),
MEMBER(lodFactor, "LODFactor"),
MEMBER(dontDrawProcessDist, "DontDrawProcessDist"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleDustEx),
MEMBER(particleType, "ParticleType"),
MEMBER(renderTarget, "Render_Target"),
MEMBER(colour, "Colour"),
MEMBER(texCoord, "TexCoord"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(lifeTime, "LifeTime"),
MEMBER(gravity, "Gravity"),
MEMBER(gravityAlongNormal, "GravityAlongNormal"),
MEMBER(drag, "Drag"),
MEMBER(diffusion, "Diffusion"),
MEMBER(endDiffusion, "EndDiffusion"),
MEMBER(kickupRate, "Kickup Rate"),
MEMBER(kickupVelocity, "Kickup Velocity"),
MEMBER(kickupVariance, "Kickup Variance"),
MEMBER(moving, "Moving"),
MEMBER(notMovingLife, "NotMovingLife"),
MEMBER(startPopulatedPcent, "StartPopulatedPcent"),
MEMBER(lockToBoneTime, "LockToBoneTime"),
MEMBER(force1, "Force 1"),
MEMBER(force2, "Force 2"),
MEMBER(force3, "Force 3"),
MEMBER(force4, "Force 4"));

REFLECT(CLASS(ResourceParticleDustRingParticle),
MEMBER(particleType, "ParticleType"),
MEMBER(minU, "MinU"),
MEMBER(minV, "MinV"),
MEMBER(maxU, "MaxU"),
MEMBER(maxV, "MaxV"),
MEMBER(colour, "Colour"),
MEMBER(size, "Size"),
MEMBER(life, "Life"));

REFLECT(CLASS(ResourceParticleDustRingLaunch),
MEMBER(rate, "Rate"),
MEMBER(velUp, "VelUp"),
MEMBER(velOut, "VelOut"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleDustRing),
MEMBER(particle, "Particles"),
MEMBER(launch, "Launch"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleElectricFence),
MEMBER(particleType, "ParticleType"),
MEMBER(renderTarget, "Render_Target"),
MEMBER(texCoord, "TexCoord"),
MEMBER(length, "Length"),
MEMBER(size, "Size"),
MEMBER(speed, "Speed"),
MEMBER(sparksPerSec, "SparksPerSec"),
MEMBER(startRandomizer, "StartRandomizer"),
MEMBER(endRandomizer, "EndRandomizer"),
MEMBER(arcsPerSpark, "ArcsPerSpark"),
MEMBER(sectionsPerArc, "SectionsPerArc"),
MEMBER(sectionsVariance, "SectionsVariance"),
MEMBER(arcLife, "ArcLife"),
MEMBER(textureAlignAtPostPcent, "TextureAlignAtPostPcent"),
MEMBER(textureAlignAtEndPcent, "TextureAlignAtEndPcent"),
MEMBER(uvRandomSpeed, "UVRandomSpeed"),
MEMBER(posRandomSpeed, "PosRandomSpeed"),
MEMBER(lightRangePost, "LightRangePost"),
MEMBER(lightRangeEffect, "LightRangeEffect"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleSmokeTrail),
MEMBER(particleType, "ParticleType"),
MEMBER(renderTarget, "Render_Target"),
MEMBER(texCoord, "TexCoord"),
MEMBER(startColour, "StartColour"),
MEMBER(endColour, "EndColour"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(rate, "Rate"),
MEMBER(life, "Life"),
MEMBER(drag, "Drag"),
MEMBER(gravity, "Gravity"),
MEMBER(random, "Random"),
MEMBER(constantRotation, "ConstantRotation"),
MEMBER(randomRotation, "RandomRotation"),
MEMBER(fadeUpTime, "FadeUpTime"));

REFLECT(CLASS(ResourceParticleGenericTextureInfo),
MEMBER(minU, "Min_u"),
MEMBER(minV, "Min_v"),
MEMBER(maxU, "Max_u"),
MEMBER(maxV, "Max_v"),
MEMBER(randomFlipX, "RandomFlipX"),
MEMBER(randomFlipY, "RandomFlipY"),
MEMBER(colorStart, "Colour_Start"),
MEMBER(colorEnd, "Colour_End"));

REFLECT(CLASS(ResourceParticleGenericLaunchInfo),
MEMBER(launchNum, "LaunchNum"),
MEMBER(sizeStart, "Size_Start"),
MEMBER(sizeEnd, "Size_End"),
MEMBER(velNormalMin, "VelNormal_Min"),
MEMBER(velNormalMax, "VelNormal_Max"),
MEMBER(velSpreadMin, "VelSpread_Min"),
MEMBER(velSpreadMax, "VelSpread_Max"));

REFLECT(CLASS(ResourceParticleGenericMovementInfo),
MEMBER(gravity, "Gravity"),
MEMBER(drag, "Drag"),
MEMBER(lifeMin, "Life_Min"),
MEMBER(lifeMax, "Life_Max"));

REFLECT(CLASS(ResourceParticleGenericScalingInfo),
MEMBER(scaleNumber, "ScaleNumber"),
MEMBER(scaleSize, "ScaleSize"),
MEMBER(scaleLife, "ScaleLife"),
MEMBER(scaleVel, "ScaleVel"));

REFLECT(CLASS(ResourceParticleGenericTrailInfo),
MEMBER(active, "Active"),
MEMBER(particle2DActive, "Particle_2D_Active"),
MEMBER(numBounces, "NumBounces"),
MEMBER(lenScale, "LenScale"),
MEMBER(widScale, "WidScale"),
MEMBER(velScale, "VelScale"),
MEMBER(sizeTimeScale, "SizeTimeScale"),
MEMBER(trailColourStart, "TrailColour_Start"),
MEMBER(trailColourEnd, "TrailColour_End"),
MEMBER(trailMin_u, "TrailMin_u"),
MEMBER(trailMin_v, "TrailMin_v"),
MEMBER(trailMax_u, "TrailMax_u"),
MEMBER(trailMax_v, "TrailMax_v"),
MEMBER(trailRandomFlipX, "TrailRandomFlipX"),
MEMBER(trailRandomFlipY, "TrailRandomFlipY"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleGeneric),
MEMBER(particleType, "ParticleType"),
MEMBER(trailParticleType, "TrailParticleType"),
MEMBER(renderTarget, "Render_Target"),
MEMBER(effectLifeTime, "EffectLifeTime"),
MEMBER(startDelay, "StartDelay"),
MEMBER(textureInfo, "TextureInfo"),
MEMBER(launchInfo, "LaunchInfo"),
MEMBER(movementInfo, "MovementInfo"),
MEMBER(scalingInfo, "ScalingInfo"),
MEMBER(trailInfo, "TrailInfo"),
MEMBER(decalChance, "DecalChance"),
MEMBER(resourceDecals, "ResourceDecals"),
MEMBER(dontDrawProcessDist, "DontDrawProcessDist"));

REFLECT(CLASS(ResourceParticleFireflySprayLiquid),
MEMBER(particleType, "ParticleType"),
MEMBER(minU, "Min_U"),
MEMBER(maxU, "Max_U"),
MEMBER(minV, "Min_V"),
MEMBER(maxV, "Max_V"),
MEMBER(launchRate, "LaunchRate"),
MEMBER(launchVel, "LaunchVel"),
MEMBER(launchRand, "LaunchRand"),
MEMBER(life, "Life"),
MEMBER(gravity, "Gravity"),
MEMBER(drag, "Drag"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(startColour, "StartColour"),
MEMBER(endColour, "EndColour"));

REFLECT(CLASS(ResourceParticleFireflySprayFlame),
MEMBER(particleType, "ParticleType"),
MEMBER(minU, "Min_U"),
MEMBER(maxU, "Max_U"),
MEMBER(minV, "Min_V"),
MEMBER(maxV, "Max_V"),
MEMBER(launchRate, "LaunchRate"),
MEMBER(life, "Life"),
MEMBER(gravity, "Gravity"),
MEMBER(drag, "Drag"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(startColour, "StartColour"),
MEMBER(endColour, "EndColour"));

REFLECT(CLASS(ResourceParticleFireflySprayFloor),
MEMBER(timeFactor, "TimeFactor"),
MEMBER(spread, "Spread"));

REFLECT(CLASS(ResourceParticleFireflySprayDamage),
MEMBER(damageDelay, "DamageDelay"),
MEMBER(strengthBlast, "StrengthBlast"),
MEMBER(strengthHeat, "StrengthHeat"),
MEMBER(strengthCorrosive, "StrengthCorrosive"),
MEMBER(hotspot, "Hotspot"),
MEMBER(falloff, "Falloff"));

REFLECT(CLASS(ResourceParticleFireflySprayDistortion),
MEMBER(distortionOn, "DistortionOn"),
MEMBER(distortionStartColour, "DistortionStartColour"),
MEMBER(distortionLifeScale, "DistortionLifeScale"),
MEMBER(distortionSizeScale,"m_DistortionSizeScale"),
MEMBER(distortionKickupPcent,"m_DistortionKickupPcent"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleFireflySpray),
MEMBER(liquid, "Liquid"),
MEMBER(flame, "Flame"),
MEMBER(floor, "Floor"),
MEMBER(damage, "Damage"),
MEMBER(distortion, "Distortion"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleNuclearBlastControl),
MEMBER(autoPopulateTime, "AutoPopulateTime"),
MEMBER(fadeupStartTime, "FadeupStartTime"),
MEMBER(fadeupEndTime, "FadeupEndTime"),
MEMBER(slowStartTime, "SlowStartTime"),
MEMBER(slowEndTime, "SlowEndTime"),
MEMBER(slowMinScale, "SlowMinScale"),
MEMBER(kickupAABB, "KickupAABB"));

REFLECT(CLASS(ResourceParticleNuclearBlastAttack),
MEMBER(color, "A_Colour"),
MEMBER(size, "A_Size"),
MEMBER(pos0to1, "A_0to1_pos"));

REFLECT(CLASS(ResourceParticleNuclearBlastDecay),
MEMBER(color, "D_Colour"),
MEMBER(size, "D_Size"),
MEMBER(pos0to1, "D_0to1_pos"));

REFLECT(CLASS(ResourceParticleNuclearBlastSustain),
MEMBER(color, "S_Colour"),
MEMBER(size, "S_Size"),
MEMBER(pos0to1, "S_0to1_pos"));

REFLECT(CLASS(ResourceParticleNuclearBlastRelease),
MEMBER(color, "R_Colour"),
MEMBER(size, "R_Size"),
MEMBER(pos0to1, "R_0to1_pos"));

REFLECT(CLASS(ResourceParticleNuclearBlastFinal),
MEMBER(color, "F_Colour"),
MEMBER(size, "F_Size"),
MEMBER(pos0to1, "F_0to1_pos"));

REFLECT(CLASS(ResourceParticleNuclearBlastKickupTypeDustEx),
MEMBER(active, "Active"));

REFLECT(CLASS(ResourceParticleNuclearBlastKickupTypesGeneric),
MEMBER(active, "Active"),
MEMBER(applyBoneMatToNormal, "ApplyBoneMatToNormal"),
MEMBER(normal, "Normal"),
MEMBER(velNormMin, "VelNorm_Min"),
MEMBER(velNormMax, "VelNorm_Max"),
MEMBER(velSpreadMin, "VelSpread_Min"),
MEMBER(velSpeadMax, "VelSpead_Max"));

REFLECT(CLASS(ResourceParticleNuclearBlastKickupTypes),
MEMBER(dustEx, "DustEx"),
MEMBER(generic, "Generic"));

REFLECT(CLASS(ResourceParticleNuclearBlastForce),
MEMBER(startTime, "Start Time"),
MEMBER(endTime, "End Time"),
MEMBER(startVel, "Start Vel"),
MEMBER(endVel, "End Vel"),
MEMBER(withDir, "With Dir"),
MEMBER(againstDir, "Against Dir"),
MEMBER(dirX, "dir x"),
MEMBER(dirY, "dir y"),
MEMBER(dirZ, "dir z"));

REFLECT(CLASS(ResourceParticleNuclearBlastRotation),
MEMBER(rotStartSpeed, "RotStartSpeed"),
MEMBER(rotFinalSpeed, "RotFinalSpeed"),
MEMBER(rotFinalTime, "RotFinalTime"));

REFLECT(CLASS(ResourceParticleNuclearBlastAnimation),
MEMBER(on, "On"),
MEMBER(numWid, "NumWid"),
MEMBER(numHgt, "NumHgt"),
MEMBER(time, "Time"));

REFLECT(CLASS(ResourceParticleNuclearBlastDamage),
MEMBER(delay, "Delay"),
MEMBER(strengthSonic, "StrengthSonic"),
MEMBER(blastHotspot, "BlastHotspot"),
MEMBER(blastFalloff, "BlastFalloff"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleNuclearBlast),
MEMBER(particleType, "ParticleType"),
MEMBER(active, "Active"),
MEMBER(renTargetScreen, "RenTarget screen"),
MEMBER(renTargetDistort, "RenTarget distort"),
MEMBER(renTargetBlur, "RenTarget blur"),
MEMBER(renTargetGlow, "RenTarget glow"),
MEMBER(startDelay, "StartDelay"),
MEMBER(populateThisPhase, "PopulateThisPhase"),
MEMBER(fadeupThisPhase, "FadeupThisPhase"),
MEMBER(kickupAABBOffset, "KickupAABB_Offset"),
MEMBER(kickupAABBOffsetInc, "KickupAABB_OffsetInc"),
MEMBER(texCoord, "TexCoord"),
MEMBER(lifeTime, "LifeTime"),
MEMBER(processType, "ProcessType"),
MEMBER(attack, "Attack"),
MEMBER(decay, "Decay"),
MEMBER(sustain, "Sustain"),
MEMBER(release, "Release"),
MEMBER(final, "Final"),
MEMBER(gravity, "Gravity"),
MEMBER(gravityAlongNormal, "GravityAlongNormal"),
MEMBER(drag, "Drag"),
MEMBER(diffusion, "Diffusion"),
MEMBER(endDiffusion, "EndDiffusion"),
MEMBER(kickupTypes, "KickupTypes"),
MEMBER(kickupRate, "Kickup Rate"),
MEMBER(kickupVelocity, "Kickup Velocity"),
MEMBER(kickupVelScale, "Kickup VelScale"),
MEMBER(kickupVariance, "Kickup Variance"),
MEMBER(moving, "Moving"),
MEMBER(notMovingLife, "NotMovingLife"),
MEMBER(lockToBoneTime, "LockToBoneTime"),
MEMBER(force1, "Force 1"),
MEMBER(force2, "Force 2"),
MEMBER(force3, "Force 3"),
MEMBER(force4, "Force 4"),
MEMBER(rotation, "Rotation"),
MEMBER(animation, "Animation"),
MEMBER(damage, "Damage"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleNapalm),
MEMBER(flameParticleType, "Flame_ParticleType"),
MEMBER(smokeParticleType, "Smoke_ParticleType"),
MEMBER(flame, "Flame"),
MEMBER(smoke, "Smoke"));

REFLECT(CLASS(ResourceParticlePlasmaSplashLaunch),
MEMBER(number, "Number"),
MEMBER(velUp, "VelUp"),
MEMBER(velOut, "VelOut"),
MEMBER(gravity, "Gravity"));

REFLECT(CLASS(ResourceParticlePlasmaSplashParticles),
MEMBER(particleType, "ParticleType"),
MEMBER(minU, "MinU"),
MEMBER(minV, "MinV"),
MEMBER(maxU, "MaxU"),
MEMBER(maxV, "MaxV"),
MEMBER(startColour, "StartColour"),
MEMBER(endColour, "EndColour"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(minLife, "MinLife"),
MEMBER(maxLife, "MaxLife"));

REFLECT(CLASS(ResourceParticlePlasmaSplashLight),
MEMBER(startColour, "StartColour"),
MEMBER(endColour, "EndColour"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(life, "Life"));

REFLECT(CLASS(ResourceParticlePlasmaSplashCollision),
MEMBER(maxMapSize, "MaxMapSize"),
MEMBER(minMapSize, "MinMapSize"),
MEMBER(maxLODRange, "MaxLODRange"));

REFLECT(CLASS(ResourceParticlePlasmaSplashFlash),
MEMBER(particleType, "ParticleType"),
MEMBER(minU, "MinU"),
MEMBER(minV, "MinV"),
MEMBER(maxU, "MaxU"),
MEMBER(maxV, "MaxV"),
MEMBER(startColour, "StartColour"),
MEMBER(endColour, "EndColour"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(life, "Life"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticlePlasmaSplash),
MEMBER(launch, "Launch"),
MEMBER(particles, "Particles"),
MEMBER(light, "Light"),
MEMBER(collision, "Collision"),
MEMBER(flash, "Flash"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleTracerFire),
MEMBER(particleType, "ParticleType"),
MEMBER(texCoord, "TexCoord"),
MEMBER(length, "Length"),
MEMBER(size, "Size"),
MEMBER(speed, "Speed"),
MEMBER(numPerSecond, "NumPerSecond"),
MEMBER(colour, "Colour"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleMoritiaMuzzleFlash),
MEMBER(particleType, "ParticleType"),
MEMBER(texCoord, "TexCoord"),
MEMBER(time, "Time"),
MEMBER(lightRange, "LightRange"),
MEMBER(lightAmbient, "LightAmbient"),
MEMBER(lightDiffuse, "LightDiffuse"),
MEMBER(lightSpecular, "LightSpecular"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleMoritiaMk4HitFlash),
MEMBER(particleType, "ParticleType"),
MEMBER(flashTexCoord, "FlashTexCoord"),
MEMBER(sprayTexCoord, "SprayTexCoord"));

REFLECT(CLASS(ResourceParticleMoritiaMk4VentCloudData),
MEMBER(rate, "Rate"),
MEMBER(life, "Life"),
MEMBER(changeCloudSize, "ChangeCloudSize"),
MEMBER(size, "Size"),
MEMBER(velX, "Velx"),
MEMBER(velY, "Vely"),
MEMBER(velZ, "Velz"),
MEMBER(random, "Random"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleMoritiaMk4Vent),
MEMBER(particleType, "ParticleType"),
MEMBER(renderTarget, "Render_Target"),
MEMBER(drawVentGraphic, "DrawVentGraphic"),
MEMBER(colour, "Colour"),
MEMBER(texCoord, "TexCoord"),
MEMBER(time, "Time"),
MEMBER(size, "Size"),
MEMBER(random, "Random"),
MEMBER(cloudTexCoord, "CloudTexCoord"),
MEMBER(cloudData, "CloudData"));

REFLECT(CLASS(ResourceParticleSimple3DLight),
MEMBER(on, "On"),
MEMBER(multiplier, "Multiplier"),
MEMBER(range, "Range"),
MEMBER(colour, "Colour"),
MEMBER(ambientColour, "AmbientColour"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleSimple3D),
MEMBER(particleType, "ParticleType"),
MEMBER(renderTarget, "Render_Target"),
MEMBER(lineWidScale, "LineWidScale"),
MEMBER(lineLenScale, "LineLenScale"),
MEMBER(uvRandomSpeed, "UVRandomSpeed"),
MEMBER(fadeUsingArc, "FadeUsingArc"),
MEMBER(quadRotZAngInc, "QuadRotZAngInc"),
MEMBER(alignToScreen, "AlignToScreen"),
MEMBER(alignToScreenAtPos, "AlignToScreenAtPos"),
MEMBER(oneMatrixForAllQuads, "OneMatrixForAllQuads"),
MEMBER(colour, "Colour"),
MEMBER(texCoord, "TexCoord"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(lifeTime, "LifeTime"),
MEMBER(gravity, "Gravity"),
MEMBER(drag, "Drag"),
MEMBER(wind, "Wind"),
MEMBER(diffusion, "Diffusion"),
MEMBER(lodFactor, "LODFactor"),
MEMBER(light, "Light"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleSystemDescriptor),
MEMBER(resourceObjectModel, "ResourceObjectModel"),
MEMBER(resourceParticleSystem, "ResourceParticleSystem"),
MEMBER(soundFireLoop, "SoundFireLoop"),
MEMBER(soundFireStart, "SoundFireStart"),
MEMBER(soundFireEnd, "SoundFireEnd"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleWarriorBulletHit),
MEMBER(particleType, "ParticleType"),
MEMBER(shellPieceTexCoord, "Shell_Piece_TexCoord"),
MEMBER(bloodBlobTexCoord, "Blood_Blob_TexCoord"),
MEMBER(bloodSprayTexCoord, "Blood_Spray_TexCoord"));

REFLECT(CLASS(ResourceParticleTankerSprayLiquid),
MEMBER(particleType, "ParticleType"),
MEMBER(minU, "Min_U"),
MEMBER(maxU, "Max_U"),
MEMBER(minV, "Min_V"),
MEMBER(maxV, "Max_V"),
MEMBER(launchRate, "LaunchRate"),
MEMBER(launchVel, "LaunchVel"),
MEMBER(launchRand, "LaunchRand"),
MEMBER(life, "Life"),
MEMBER(gravity, "Gravity"),
MEMBER(drag, "Drag"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(startColour, "StartColour"),
MEMBER(endColour, "EndColour"));

REFLECT(CLASS(ResourceParticleTankerSprayFlame),
MEMBER(particleType, "ParticleType"),
MEMBER(minU, "Min_U"),
MEMBER(maxU, "Max_U"),
MEMBER(minV, "Min_V"),
MEMBER(maxV, "Max_V"),
MEMBER(launchRate, "LaunchRate"),
MEMBER(life, "Life"),
MEMBER(gravity, "Gravity"),
MEMBER(drag, "Drag"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(startColour, "StartColour"),
MEMBER(endColour, "EndColour"));

REFLECT(CLASS(ResourceParticleTankerSprayFloor),
MEMBER(timeFactor, "TimeFactor"),
MEMBER(spread, "Spread"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleTankerSpray),
MEMBER(liquid, "Liquid"),
MEMBER(flame, "Flame"),
MEMBER(Floor, "Floor"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleMuzzleFlash),
MEMBER(particleType, "ParticleType"),
MEMBER(texCoord, "TexCoord"),
MEMBER(time, "Time"),
MEMBER(lightRange, "LightRange"),
MEMBER(lightAmbient, "LightAmbient"),
MEMBER(lightDiffuse, "LightDiffuse"),
MEMBER(lightSpecular, "LightSpecular"),
MEMBER(petalFwdScale, "PetalFwdScale"),
MEMBER(petalFwdScaleVariance, "PetalFwdScaleVariance"),
MEMBER(muzzleFlash1Hgt, "MuzzleFlash1Hgt"),
MEMBER(muzzleFlash1Len, "MuzzleFlash1Len"),
MEMBER(muzzleFlash2Hgt, "MuzzleFlash2Hgt"),
MEMBER(muzzleFlash2Len, "MuzzleFlash2Len"),
MEMBER(muzzleFlash1Variance, "MuzzleFlash1Variance"),
MEMBER(muzzleFlash2Variance, "MuzzleFlash2Variance"),
MEMBER(typeAZAdjust1, "TypeAZAdjust1"),
MEMBER(typeAZAdjust2, "TypeAZAdjust2"),
MEMBER(typeBZAdjust1, "TypeBZAdjust1"),
MEMBER(typeBZAdjust2, "TypeBZAdjust2"),
MEMBER(size, "Size"),
MEMBER(numAnims, "NumAnims"),
MEMBER(startAnimIfDelayed, "StartAnimIfDelayed"),
MEMBER(startAnimDelayTime, "StartAnimDelayTime"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleConTrail),
MEMBER(particleType, "ParticleType"),
MEMBER(texCoord, "TexCoord"),
MEMBER(startColour, "StartColour"),
MEMBER(endColour, "EndColour"),
MEMBER(rate, "Rate"),
MEMBER(life, "Life"),
MEMBER(startWidth, "StartWidth"),
MEMBER(endWidth, "EndWidth"),
MEMBER(gravity, "Gravity"),
MEMBER(random, "Random"),
MEMBER(minVisibleSpeed, "MinVisibleSpeed"),
MEMBER(maxVisibleSpeed, "MaxVisibleSpeed"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleLights),
MEMBER(particleType, "ParticleType"),
MEMBER(texCoord, "TexCoord"),
MEMBER(time, "Time"),
MEMBER(lightRange, "LightRange"),
MEMBER(lightAmbient, "LightAmbient"),
MEMBER(lightDiffuse, "LightDiffuse"),
MEMBER(lightSpecular, "LightSpecular"),
MEMBER(petalFwdScale, "PetalFwdScale"),
MEMBER(petalFwdScaleVariance, "PetalFwdScaleVariance"),
MEMBER(muzzleFlash1Hgt, "MuzzleFlash1Hgt"),
MEMBER(muzzleFlash1Len, "MuzzleFlash1Len"),
MEMBER(muzzleFlash2Hgt, "MuzzleFlash2Hgt"),
MEMBER(muzzleFlash2Len, "MuzzleFlash2Len"),
MEMBER(muzzleFlash1Variance, "MuzzleFlash1Variance"),
MEMBER(muzzleFlash2Variance, "MuzzleFlash2Variance"),
MEMBER(typeAZAdjust1, "TypeAZAdjust1"),
MEMBER(typeAZAdjust2, "TypeAZAdjust2"),
MEMBER(typeBZAdjust1, "TypeBZAdjust1"),
MEMBER(typeBZAdjust2, "TypeBZAdjust2"),
MEMBER(size, "Size"),
MEMBER(numAnims, "NumAnims"),
MEMBER(startAnimIfDelayed, "StartAnimIfDelayed"),
MEMBER(startAnimDelayTime, "StartAnimDelayTime"),
MEMBER(numSpokes, "NumSpokes"),
MEMBER(startAngle, "StartAngle"),
MEMBER(spokeLen, "SpokeLen"),
MEMBER(spokeWidBase, "SpokeWidBase"),
MEMBER(spokeWidEnd, "SpokeWidEnd"),
MEMBER(spokeColour, "SpokeColour"));

REFLECT(CLASS(ResourceParticleBulletHitDebrisTextureInfo),
MEMBER(minU, "Min_u"),
MEMBER(minV, "Min_v"),
MEMBER(maxU, "Max_u"),
MEMBER(maxV, "Max_v"),
MEMBER(colorStart, "Colour_Start"),
MEMBER(colorEnd, "Colour_End"));

REFLECT(CLASS(ResourceParticleBulletHitDebrisLaunchInfo),
MEMBER(launchNum, "LaunchNum"),
MEMBER(size_Start, "Size_Start"),
MEMBER(sizeEnd, "Size_End"),
MEMBER(minLife, "Min_Life"),
MEMBER(maxLife, "Max_Life"),
MEMBER(launchVel, "Launch_Vel"),
MEMBER(velVariance, "Vel_Variance"),
MEMBER(gravity, "Gravity"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleBulletHitDebris),
MEMBER(particleType, "ParticleType"),
MEMBER(textureInfo, "TextureInfo"),
MEMBER(launchInfo, "LaunchInfo"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleBulletHitDust),
MEMBER(particleType, "ParticleType"),
MEMBER(texCoord, "TexCoord"),);

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleBlood),
MEMBER(particleType, "ParticleType"),
MEMBER(bloodBlobTexCoord, "Blood_Blob_TexCoord"),
MEMBER(bloodSprayTexCoord, "Blood_Spray_TexCoord"));

REFLECT(CLASS(ResourceParticleFlareParticle),
MEMBER(particleType, "Flare_ParticleType"),
MEMBER(Min_U, "Flare_Min_U"),
MEMBER(Max_U, "Flare_Max_U"),
MEMBER(Min_V, "Flare_Min_V"),
MEMBER(Max_V, "Flare_Max_V"),
MEMBER(Size0, "Flare_Size0"),
MEMBER(Size1, "Flare_Size1"),
MEMBER(Life, "Flare_Life"),
MEMBER(Rate, "Flare_Rate"));

REFLECT(CLASS(ResourceParticleFlareLight),
MEMBER(lightPos, "LightPos"),
MEMBER(lightRangeMin, "LightRangeMin"),
MEMBER(lightRangeMax, "LightRangeMax"),
MEMBER(lightMultiplier, "LightMultiplier"),
MEMBER(lightShadow, "LightShadow"),
MEMBER(lightAmbient, "LightAmbient"),
MEMBER(lightDiffuse, "LightDiffuse"),
MEMBER(lightSpecular, "LightSpecular"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleFlare),
MEMBER(flare, "Flare"),
MEMBER(smoke, "Smoke"),
MEMBER(burnTime0, "BurnTime0"),
MEMBER(burnTime1, "BurnTime1"),
MEMBER(burnTime2, "BurnTime2"),
MEMBER(burnTime3, "BurnTime3"),
MEMBER(light, "Light"));

REFLECT(CLASS(ResourceParticleBloodSpurtParticle),
MEMBER(colour, "Colour"),
MEMBER(launchNum, "LaunchNum"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(life, "Life"),
MEMBER(launchVel, "LaunchVel"),
MEMBER(random, "Random"),
MEMBER(gravity, "Gravity"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleBloodSpurt),
MEMBER(particleType, "ParticleType"),
MEMBER(textureInfo, "TextureInfo"),
MEMBER(spurt, "Spurt"),
MEMBER(spray, "Spray"));

REFLECT(BASEDCLASS(ResourcePack, ResourceShaderBumpTexBlend2),
MEMBER(diffuseTexture1, "Diffuse Texture 1"),
MEMBER(diffuseTexture2, "Diffuse Texture 2"),
MEMBER(normalMapTexture, "Normal map texture"),
MEMBER(ambient, "Ambient"),
MEMBER(diffuse, "Diffuse"),
MEMBER(specular, "Specular"),
MEMBER(Texture1Scale, "Texture 1 Scale"),
MEMBER(Texture2Scale, "Texture 2 Scale"),
MEMBER(Texture3Scale, "Texture 3 Scale"),
MEMBER(applyNormalTo1stTextureOnly, "Apply normal to 1st texture only"));

REFLECT(BASEDCLASS(ResourcePack, ResourceShaderOverlay),
MEMBER(diffuseTexture, "Diffuse texture"),
MEMBER(normalMapTexture, "Normal map texture"),
MEMBER(ambient, "Ambient"),
MEMBER(diffuse, "Diffuse"),
MEMBER(specular, "Specular"),
MEMBER(vertexAlpha, "Vertex Alpha"),
MEMBER(diffuseUScale, "DiffuseUScale"),
MEMBER(diffuseVScale, "DiffuseVScale"),
MEMBER(normalUScale, "NormalUScale"),
MEMBER(normalVScale, "NormalVScale"),
MEMBER(diffuseUOffset, "DiffuseUOffset"),
MEMBER(diffuseVOffset, "DiffuseVOffset"),
MEMBER(normalUOffset, "NormalUOffset"),
MEMBER(normalVOffset, "NormalVOffset"),
MEMBER(textureVelocity, "TextureVelocity"),
MEMBER(depthBias, "DepthBias"),
MEMBER(blended, "Blended"));

REFLECT(BASEDCLASS(ResourcePack, ShaderParamsBumpSpec),
MEMBER(shader, "Shader"),
MEMBER(getDefaults, "Get defaults"),
MEMBER(ambient, "Ambient"),
MEMBER(diffuse, "Diffuse"),
MEMBER(specular, "Specular"),
MEMBER(diffuseUScale, "DiffuseUScale"),
MEMBER(diffuseVScale, "DiffuseVScale"),
MEMBER(normalUScale, "NormalUScale"),
MEMBER(normalVScale, "NormalVScale"),
MEMBER(diffuseUOffset, "DiffuseUOffset"),
MEMBER(diffuseVOffset, "DiffuseVOffset"),
MEMBER(normalUOffset, "NormalUOffset"),
MEMBER(normalVOffset, "NormalVOffset"));

REFLECT(BASEDCLASS(ResourcePack, ResourceShaderAnisotropic),
MEMBER(diffuseTexture, "Diffuse texture"),
MEMBER(normalMapTexture, "Normal map texture"),
MEMBER(anisotropicMapTexture, "Anisotropic map texture"),
MEMBER(ambient, "Ambient"),
MEMBER(diffuse, "Diffuse"),
MEMBER(specular, "Specular"),
MEMBER(diffuseUScale, "DiffuseUScale"),
MEMBER(diffuseVScale, "DiffuseVScale"),
MEMBER(normalUScale, "NormalUScale"),
MEMBER(normalVScale, "NormalVScale"),
MEMBER(alphaTested, "AlphaTested"),
MEMBER(doubleFaced, "DoubleFaced"),
MEMBER(ignoreMipmaps, "IgnoreMipmaps"),
MEMBER(blended, "Blended"));

REFLECT(BASEDCLASS(ResourcePack, ResourceShaderUnlit),
MEMBER(diffuseTexture, "Diffuse texture"),
MEMBER(ambient, "Ambient"),
MEMBER(diffuse, "Diffuse"),
MEMBER(alphaBlended, "Alpha Blended"),
MEMBER(alphaTested, "Alpha Tested"),
MEMBER(vertexAlpha, "Vertex Alpha"),
MEMBER(generateShadows, "Generate Shadows"),
MEMBER(srcBlend, "SrcBlend"),
MEMBER(destBlend, "DestBlend"),
MEMBER(pulseFrequency, "PulseFrequency"),
MEMBER(textureVelocity, "TextureVelocity"),
MEMBER(fogFactor, "FogFactor"),
MEMBER(fogOutFactor, "FogOutFactor"),
MEMBER(blended, "Blended"));

REFLECT(BASEDCLASS(ResourcePack, ResourceShaderPhong),
MEMBER(diffuseTexture, "Diffuse texture"),
MEMBER(normalMapTexture, "Normal map texture"),
MEMBER(ambient, "Ambient"),
MEMBER(diffuse, "Diffuse"),
MEMBER(specular, "Specular"),
MEMBER(alphaBlended, "Alpha Blended"),
MEMBER(alphaTested, "Alpha Tested"),
MEMBER(generateShadows, "Generate Shadows"),
MEMBER(diffuseUScale, "DiffuseUScale"),
MEMBER(diffuseVScale, "DiffuseVScale"),
MEMBER(normalUScale, "NormalUScale"),
MEMBER(normalVScale, "NormalVScale"),
MEMBER(diffuseUOffset, "DiffuseUOffset"),
MEMBER(diffuseVOffset, "DiffuseVOffset"),
MEMBER(normalUOffset, "NormalUOffset"),
MEMBER(normalVOffset, "NormalVOffset"),
MEMBER(doubleFaced, "DoubleFaced"),
MEMBER(ignoreMipmaps, "IgnoreMipmaps"),
MEMBER(blended, "Blended"));

REFLECT(BASEDCLASS(ResourcePack, ResourceShaderGlow),
MEMBER(glowTexture, "Glow texture"),
MEMBER(glowUScale, "GlowUScale"),
MEMBER(glowVScale, "GlowVScale"),
MEMBER(emissiveFactor, "EmissiveFactor"),
MEMBER(glowFactor, "GlowFactor"),
MEMBER(textureVelocity, "TextureVelocity"),
MEMBER(fogFactor, "FogFactor"),
MEMBER(blended, "Blended"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionAIAction),
MEMBER(order, "Order"),
MEMBER(objectiveActionAIActionQuicksave,"QUICKSAVE"),
MEMBER(actions,"Actions")
);

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionWaitForSpeechToEnd),
MEMBER(order, "Order"),
MEMBER(objectiveActionWaitForSpeechToEndQuicksave,"QUICKSAVE"),
MEMBER(entity, "Entity"),
MEMBER(timeoutPeriod, "TimeoutPeriod"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionKillTally),
MEMBER(order, "Order"),
MEMBER(objectiveActionKillTallyQuicksave,"QUICKSAVE"),
MEMBER(type, "Type"),
MEMBER(num, "Num"),
MEMBER(group, "Group"),
MEMBER(desiredKiller, "DesiredKiller"));

REFLECT(BASEDCLASS(ResourcePack, SubObjective),
MEMBER(positionType, "PositionType"),
MEMBER(position, "Position"),
MEMBER(hideMarkerWhenThere, "HideMarkerWhenThere"),
MEMBER(markerRadius, "MarkerRadius"),
MEMBER(trackableObject, "TrackableObject"),
MEMBER(markerRadius, "Actions"),
MEMBER(subObjectiveQuicksave,"QUICKSAVE_SubObjective"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionStayInVicinity),
MEMBER(order, "Order"),
MEMBER(objectiveActionStayInVicinityQuicksave,"QUICKSAVE"),
MEMBER(initialiseTime, "InitialiseTime"),
MEMBER(timeRequired, "TimeRequired"),
MEMBER(endPhaseTime, "EndPhaseTime"),
MEMBER(resetTime, "ResetTime"),
MEMBER(resetOnAreaLeave, "ResetOnAreaLeave"),
MEMBER(position, "Position"),
MEMBER(activeArea, "ActiveArea"),
MEMBER(pauseArea, "PauseArea"),
MEMBER(activeMarkerBox, "ActiveMarkerBox"),
MEMBER(pauseMarkerBox, "PauseMarkerBox"),
MEMBER(HUD_PROGRESS_INITIALISE_Sound, "HUD_PROGRESS_INITIALISE_Sound"),
MEMBER(HUD_PROGRESS_MAIN_Sound, "HUD_PROGRESS_MAIN_Sound"),
MEMBER(HUD_PROGRESS_PAUSED_Sound, "HUD_PROGRESS_PAUSED_Sound"),
MEMBER(HUD_PROGRESS_RESET_Sound, "HUD_PROGRESS_RESET_Sound"),
MEMBER(HUD_PROGRESS_FINISHED_Sound, "HUD_PROGRESS_FINISHED_Sound"),
MEMBER(entity, "Entity"),
MEMBER(showBar, "ShowBar"));

REFLECT(CLASS(ObjectiveTimingInfo),
MEMBER(timed, "Timed"),
MEMBER(timeToComplete, "TimeToComplete"),
MEMBER(failState, "FailState"));

REFLECT(CLASS(ObjectiveRepeatInfo),
MEMBER(timeToRepeat,"TimeToRepeat"),
MEMBER(repeatInRadius, "RepeatInRadius"),
MEMBER(repeatRadius, "RepeatRadius"));

REFLECT(CLASS(ObjectiveAction),
MEMBER(actions, "Actions"));

REFLECT(BASEDCLASS(ResourcePack, Objective),
MEMBER(number, "Number"),
MEMBER(designerPhase, "Designer Phase"),
MEMBER(timingInfo, "TimingInfo"),
MEMBER(objectiveRepeatInfo, "ObjectiveRepeatInfo"),
MEMBER(description, "Description"),
MEMBER(spokenObjective, "SpokenObjective"),
MEMBER(nextObjective, "NextObjective"),
MEMBER(preamble, "Preamble"),
MEMBER(subObjectives, "SubObjectives"),
MEMBER(success, "Success"),
MEMBER(partialFail, "PartialFail"),
MEMBER(totalFail, "TotalFail"),
MEMBER(objectiveQuicksave,"QUICKSAVE_Objective"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionKeepAliveSpecific),
MEMBER(order,"Order"),
MEMBER(objectiveActionKeepAliveSpecificQuicksave, "QUICKSAVE"),
MEMBER(entity, "Entity"),
MEMBER(failState, "FailState"),
MEMBER(timeToKeepAlive, "TimeToKeepAlive"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionUpdateObjectiveLocation),
MEMBER(order, "Order"),
MEMBER(objectiveActionUpdateObjectiveLocationQuicksave,"QUICKSAVE"),
MEMBER(positionValid, "PositionValid"),
MEMBER(positionType, "PositionType"),
MEMBER(hideMarkerWhenThere, "HideMarkerWhenThere"),
MEMBER(position, "Position"),
MEMBER(radius, "Radius"),
MEMBER(trackableObject, "TrackableObject"),
MEMBER(subObjective, "SubObjective"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionWaitForObjectUse),
MEMBER(order, "Order"),
MEMBER(quicksave, "QUICKSAVE"),
MEMBER(target, "Target"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionWait),
MEMBER(order, "Order"),
MEMBER(quicksave, "QUICKSAVE"),
MEMBER(showCountdown, "ShowCountdown"),
MEMBER(time, "Time"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionUpdateGlobalObjective),
MEMBER(order, "Order"),
MEMBER(quicksave, "QUICKSAVE"),
MEMBER(description, "Description"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionWaitForTrigger),
MEMBER(order, "Order"),
MEMBER(quicksave, "QUICKSAVE"),
MEMBER(timeoutLength, "TimeoutLength"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionWaitTillChatScriptFinished),
MEMBER(order, "Order"),
MEMBER(quicksave, "QUICKSAVE"),
MEMBER(script, "Script"),
MEMBER(timeoutPeriod, "TimeoutPeriod"));

REFLECT(BASEDCLASS(ResourcePack, ChatLine),
MEMBER(string, "String"),
MEMBER(sound, "Sound"),
MEMBER(aiEntity, "AIEntity"),
MEMBER(delay, "Delay"),
MEMBER(priority, "Priority"),
MEMBER(order, "Order"),
MEMBER(subtitled, "Subtitled"),
MEMBER(speechType, "SpeechType"));

REFLECT(BASEDCLASS(ResourcePack, ResourceSpeechType),
MEMBER(speechType, "SpeechType"),
MEMBER(chance, "Chance"),
MEMBER(speech, "Speech")
);

REFLECT(BASEDCLASS(ResourcePack, ResourceStringTable),
MEMBER(filename, "Filename"));

REFLECT(CLASS(ParticleSystemGenericQuicksave),
MEMBER(getIsActive, "GetIsActive"),
MEMBER(kickupRate, "m_KickupRate"),
MEMBER(nextOffTime, "m_NextOffTime"),
MEMBER(nextOnTime, "m_NextOnTime"),
MEMBER(initialAutoStart, "m_InitialAutoStart"));

REFLECT(CLASS(ParticleSystemDustStormQuicksave),
MEMBER(lastResourceGuid, "m_LastResourceGuid"),
MEMBER(lastPosition, "m_LastPosition"),
MEMBER(first, "m_First"),
MEMBER(bAutoDelete, "m_bAutoDelete"),
MEMBER(timeActive, "m_TimeActive"),
MEMBER(startTime, "m_StartTime"),
MEMBER(lastT, "m_LastT"),
MEMBER(interpolatingAtmosphere, "m_InterpolatingAtmosphere"),
MEMBER(interpolatingDuration, "m_InterpolatingDuration"),
MEMBER(interpolatingStartTime, "m_InterpolatingStartTime"),
MEMBER(interpolatingEndTime, "m_InterpolatingEndTime"),
MEMBER(currentColour, "m_CurrentColour"),
MEMBER(oldRayleighColour, "m_OldRayleighColour"),
MEMBER(oldRayleighDensity, "m_OldRayleighDensity"),
MEMBER(oldMieColour, "m_OldMieColour"),
MEMBER(oldMieFactor, "m_OldMieFactor"),
MEMBER(oldMieDensity, "m_OldMieDensity"),
MEMBER(oldInScatteringModifier, "m_OldInScatteringModifier"),
MEMBER(oldRainLaunchNum, "m_OldRainLaunchNum"),
MEMBER(savedOrigAtmosphereVals, "m_SavedOrigAtmosphereVals"),
MEMBER(origRayleighColour, "m_OrigRayleighColour"),
MEMBER(origRayleighDensity, "m_OrigRayleighDensity"),
MEMBER(origMieColour, "m_OrigMieColour"),
MEMBER(origMieFactor, "m_OrigMieFactor"),
MEMBER(origMieDensity, "m_OrigMieDensity"),
MEMBER(origInScatteringModifier, "m_OrigInScatteringModifier"),
MEMBER(particleEffectOn, "m_ParticleEffectOn"),
MEMBER(particleRainEffectOn, "m_ParticleRainEffectOn"),
MEMBER(interpolatingRainLaunchNum, "m_InterpolatingRainLaunchNum"),
MEMBER(noProcess, "ms_NoProcess"),
MEMBER(noGetParticles, "ms_NoGetParticles"),
MEMBER(forceWindDir, "ms_forceWindDir"),
MEMBER(showDebug, "ms_showDebug"),
MEMBER(reflectRadius, "ms_ReflectRadius"),
MEMBER(flipThruWindDir, "ms_flipThruWindDir"),
MEMBER(flipThruFwdDir, "ms_flipThruFwdDir"),
MEMBER(ignoreWind, "ms_ignoreWind"),
MEMBER(onlyGetInReflectRadius, "ms_onlyGetInReflectRadius"),
MEMBER(UOORPorig, "ms_UOORP_orig"),
MEMBER(isStormActive, "ms_IsStormActive"),
MEMBER(changeAtmosphereStart, "ms_ChangeAtmosphereStart"));

REFLECT(CLASS(ParticleSystemDustQuicksave),
MEMBER(startTime, "m_StartTime"),
MEMBER(lastT, "m_LastT"));

REFLECT(CLASS(ParticleSystemNuclearBlastQuicksave),
MEMBER(rpParticleResourceControl, "m_rpParticleResourceControl"),
MEMBER(rpParticleResource1, "m_rpParticleResource1"),
MEMBER(rpParticleResource2, "m_rpParticleResource2"),
MEMBER(rpParticleResource3, "m_rpParticleResource3"),
MEMBER(rpParticleResource4, "m_rpParticleResource4"),
MEMBER(rpParticleResource5, "m_rpParticleResource5"),
MEMBER(rpParticleResource6, "m_rpParticleResource6"),
MEMBER(rpParticleResource7, "m_rpParticleResource7"),
MEMBER(rpParticleResource8, "m_rpParticleResource8"),
MEMBER(rpParticleResource9, "m_rpParticleResource9"),
MEMBER(rpParticleResource10, "m_rpParticleResource10"),
MEMBER(posLocal, "m_PosLocal"),
MEMBER(usePosInsteadOfKickupCenter, "m_usePosInsteadOfKickupCenter"),
MEMBER(timeIntoEffect, "m_TimeIntoEffect"),
MEMBER(bActive, "m_bActive"),
MEMBER(bUseKillPlane, "m_bUseKillPlane"),
MEMBER(killPlaneNormal, "m_killPlaneNormal"),
MEMBER(collisionPos, "m_collisionPos"));

REFLECT(CLASS(WorldObjectUsableAABBQuicksave),
MEMBER(canBeUsed, "CanBeUsed"));

REFLECT(CLASS(ModelAnimatedQuicksave),
MEMBER(fAnimationTime, "m_fAnimationTime"));

REFLECT(CLASS(ModelAnimatedQuicksave2),
MEMBER(getIsActive, "GetIsActive"),
MEMBER(fAnimationTime, "m_fAnimationTime"));

REFLECT(CLASS(ObjectiveActionAIActionQuicksave),
MEMBER(complete, "Complete"),
MEMBER(triggered, "Triggered"));

REFLECT(CLASS(ObjectiveActionWaitForSpeechToEndQuicksave),
MEMBER(complete, "Complete"),
MEMBER(triggered, "Triggered"),
MEMBER(timeLeft, "TimeLeft"));

REFLECT(CLASS(ObjectiveActionKillTallyQuicksave),
MEMBER(complete, "Complete"),
MEMBER(triggered, "Triggered"),
MEMBER(currentCount, "CurrentCount"));

REFLECT(CLASS(SubObjectiveQuicksave),
MEMBER(itrAction, "m_itrAction"),
MEMBER(bDeRegistedPositionWithHUD, "m_bDeRegistedPositionWithHUD"));

REFLECT(CLASS(ObjectiveActionStayInVicinityQuicksave),
MEMBER(complete, "Complete"),
MEMBER(triggered, "Triggered"),
MEMBER(currentState, "CurrentState"),
MEMBER(currentPhaseTime, "CurrentPhaseTime"),
MEMBER(continueTime, "ContinueTime"));

REFLECT(CLASS(ObjectiveQuicksave),
MEMBER(pState, "m_pState"),
MEMBER(timeLeft, "m_TimeLeft"),
MEMBER(itrOA, "m_itrOA"),
MEMBER(bTriggered, "m_bTriggered"));

REFLECT(CLASS(ObjectiveActionKeepAliveSpecificQuicksave),
MEMBER(complete, "Complete"),
MEMBER(triggered, "Triggered"),
MEMBER(timeLeft, "TimeLeft"));

REFLECT(CLASS(ObjectiveActionUpdateObjectiveLocationQuicksave),
MEMBER(complete, "Complete"),
MEMBER(triggered, "Triggered"));

REFLECT(CLASS(ObjectiveActionWaitForObjectUseQuicksave),
MEMBER(complete, "Complete"),
MEMBER(triggered, "Triggered"));

REFLECT(CLASS(ObjectiveActionWaitQuicksave),
MEMBER(complete, "Complete"),
MEMBER(triggered, "Triggered"),
MEMBER(startTime, "StartTime"));

REFLECT(CLASS(ObjectiveActionUpdateGlobalObjectiveQuicksave),
MEMBER(complete, "Complete"),
MEMBER(triggered, "Triggered"));

REFLECT(CLASS(ObjectiveActionWaitForTriggerQuicksave),
MEMBER(complete, "Complete"),
MEMBER(triggered, "Triggered"),
MEMBER(timeLeft, "TimeLeft"),
MEMBER(getIsActive, "GetIsActive"));

REFLECT(CLASS(ObjectiveActionWaitTillChatScriptFinishedQuicksave),
MEMBER(complete, "Complete"),
MEMBER(triggered, "Triggered"),
MEMBER(timeLeft, "TimeLeft"));

REFLECT(BASEDCLASS(WorldObject, WorldObjectDecal),
MEMBER(resource, "Resource"),
MEMBER(permanent, "Permanent"),
MEMBER(centre, "Centre"),
MEMBER(normal, "Normal"),
MEMBER(radius, "Radius"));

REFLECT(CLASS(LightModifierAnimateQuicksave),
MEMBER(originalPosition, "m_OriginalPosition"),
MEMBER(originalDirection, "m_OriginalDirection"),
MEMBER(originalLocalX, "m_OriginalLocalX"));

REFLECT(BASEDCLASS(ResourcePack, LightModifierAnimate),
MEMBER(active, "Active"),
MEMBER(modelObject, "ModelObject"),
MEMBER(boneName, "BoneName"),
MEMBER(affectPosition, "AffectPosition"),
MEMBER(affectOrientation, "AffectOrientation"),
MEMBER(lightModifierAnimateQuicksave,"QUICKSAVE_LightModifierAnimate"));

REFLECT(BASEDCLASS(ResourcePack, LightModifierFlicker),
MEMBER(active, "Active"),
MEMBER(intensity1, "Intensity1"),
MEMBER(intensity2, "Intensity2"),
MEMBER(duration1, "Duration1"),
MEMBER(duration2, "Duration2"),
MEMBER(transitionPeriod, "TransitionPeriod"),
MEMBER(randomize, "Randomize"),
MEMBER(durationJitter, "DurationJitter"),
MEMBER(intensityJitter, "IntensityJitter"),
MEMBER(lightModifierFlickerQuicksave,"QUICKSAVE_LightModifierFlicker"));

REFLECT(BASEDCLASS(ResourcePack, ContextModifier),
MEMBER(active, "Active"),
MEMBER(context, "Context"),
MEMBER(targetValue, "TargetValue"),
MEMBER(transitionPeriod, "TransitionPeriod"),
MEMBER(contextModifierQuicksave,"QUICKSAVE_ContextModifier"));

REFLECT(BASEDCLASS(Resource, WorldObjectContainer),
MEMBER(groupMembers, "GroupMembers"));

REFLECT(BASEDCLASS(ResourcePack, LightModifierSetColor),
MEMBER(active, "Active"),
MEMBER(ambient, "Ambient"),
MEMBER(diffuse, "Diffuse"),
MEMBER(specular, "Specular"),
MEMBER(transitionPeriod, "TransitionPeriod"),
MEMBER(lightModifierSetColorQuicksave,"QUICKSAVE_LightModifierSetColor"));

REFLECT(BASEDCLASS(ResourcePack, ResourceShaderTintDistort),
MEMBER(tintTexture, "Tint texture"),
MEMBER(distortTexture, "Distort texture"),
MEMBER(ambient, "Ambient"),
MEMBER(textureVelocity, "TextureVelocity"),
MEMBER(blended, "Blended"));

REFLECT(BASEDCLASS(ResourcePack, ResourceShaderTexBlend3),
MEMBER(diffuseTexture1, "Diffuse Texture 1"),
MEMBER(diffuseTexture2, "Diffuse Texture 2"),
MEMBER(diffuseTexture3, "Diffuse Texture 3"),
MEMBER(ambient, "Ambient"),
MEMBER(diffuse, "Diffuse"),
MEMBER(specular, "Specular"),
MEMBER(texture1Scale, "Texture 1 Scale"),
MEMBER(texture2Scale, "Texture 2 Scale"),
MEMBER(texture3Scale, "Texture 3 Scale"));

REFLECT(BASEDCLASS(ResourcePack, ParticleSystemAnimatedOABB),
MEMBER(particleResource, "ParticleResource"),
MEMBER(targetModel, "TargetModel"),
MEMBER(rateFactor, "RateFactor"),
MEMBER(lifeTime, "LifeTime"),
MEMBER(active, "Active"),
MEMBER(particleSystemAnimatedOABBQuicksave,"QUICKSAVE_ParticleSystemAnimatedOABB"));

REFLECT(BASEDCLASS(ResourcePack, ParticleSystemExplosion),
MEMBER(particleSystemExplosionQuicksave,"QUICKSAVE_ParticleSystemAnimated"),
MEMBER(explosionParticleResource, "ExplosionParticleResource"),
MEMBER(position, "Position"),
MEMBER(size, "Size"),
MEMBER(damageRadius, "DamageRadius"),
MEMBER(damageValue, "DamageValue"),
MEMBER(lightOn, "LightOn"));

REFLECT(BASEDCLASS(ParticleSystemDust, ParticleSystemTerrainDust),
MEMBER(numNodes, "NumNodes"),
MEMBER(desNodeSize, "DesNodeSize"),
MEMBER(kickupArea, "KickupArea"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionCollectItems),
MEMBER(order, "Order"),
MEMBER(objectiveActionCollectItemsQuicksave,"QUICKSAVE"),
MEMBER(itemsToCollect, "ItemsToCollect")
);

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionKillSpecific),
MEMBER(order, "Order"),
MEMBER(objectiveActionKillSpecificQuicksave,"QUICKSAVE"),
MEMBER(entity, "Entity"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionJumpToObjective),
MEMBER(order, "Order"),
MEMBER(objectiveActionJumpToObjectiveQuicksave,"QUICKSAVE"),
MEMBER(objectiveNumber, "ObjectiveNumber"),
MEMBER(endStateToProcess, "EndStateToProcess"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionTextMessage),
MEMBER(order, "Order"),
MEMBER(quicksave, "QUICKSAVE"),
MEMBER(string, "String"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionKillTallyDestructableObjects),
MEMBER(order, "Order"),
MEMBER(quicksave, "QUICKSAVE"),
MEMBER(countFromTrigger, "CountFromTrigger"),
MEMBER(numRequired, "NumRequired"));

REFLECT(BASEDCLASS(ResourcePack, ObjectiveActionTimedStay),
MEMBER(order, "Order"),
MEMBER(quicksave, "QUICKSAVE"),
MEMBER(time, "Time"),
MEMBER(failState, "FailState"),
MEMBER(position, "Position"),
MEMBER(safeArea, "SafeArea"));

REFLECT(CLASS(SettingsGraphics),
MEMBER(screenXRes),
MEMBER(screenYRes),
MEMBER(shaderQuality),
MEMBER(textureQuality),
MEMBER(shadows),
MEMBER(softShadows),
MEMBER(graphicsPipeline),
MEMBER(graphicsDynamicLights),
MEMBER(effectQuality),
MEMBER(disableSM2));

REFLECT(CLASS(SettingsPerformance),
MEMBER(modelDetail),
MEMBER(adaptivePerformance));

REFLECT(CLASS(SettingsOther),
MEMBER(glowTrail),
MEMBER(distort));

REFLECT(BASEDCLASS(Resource, Settings),
MEMBER(graphics),
MEMBER(performance),
MEMBER(other));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectSpeechDropship),
MEMBER(LandingChance, "LandingChance"),
MEMBER(TakingOffChance, "TakingOffChance"),
MEMBER(DroppingOffSquadChance, "DroppingOffSquadChance"),
MEMBER(speechLanding,"SpeechLanding"),
MEMBER(speechTakingOff,"SpeechTakingOff"),
MEMBER(speechDroppingOffSquad,"SpeechDroppingOffSquad")
);

REFLECT(CLASS(LightModifierFlickerQuicksave),
MEMBER(originalAmbient, "m_OriginalAmbient"),
MEMBER(originalDiffuse, "m_OriginalDiffuse"),
MEMBER(originalSpecular, "m_OriginalSpecular"),
MEMBER(startTime, "m_StartTime"),
MEMBER(effectiveIntensity, "m_EffectiveIntensity"),
MEMBER(effectiveDuration, "m_EffectiveDuration"),
MEMBER(activeStage, "m_ActiveStage"));

REFLECT(CLASS(ContextModifierQuicksave),
MEMBER(startValue, "m_StartValue"),
MEMBER(startTime, "m_StartTime"));

REFLECT(CLASS(LightModifierSetColorQuicksave),
MEMBER(originalAmbient, "m_OriginalAmbient"),
MEMBER(originalDiffuse, "m_OriginalDiffuse"),
MEMBER(originalSpecular, "m_OriginalSpecular"),
MEMBER(startTime, "m_StartTime"));

REFLECT(CLASS(ParticleSystemAnimatedOABBQuicksave),
MEMBER(launchBoxMin, "m_LaunchBox_MIN"),
MEMBER(launchBoxMax, "m_LaunchBox_MAX"),
MEMBER(fDamageTime, "m_fDamageTime"),
MEMBER(eType, "m_eType"),
MEMBER(bModelRefValid, "m_bModelRefValid"),
MEMBER(scaleRate, "m_ScaleRate"),
MEMBER(scaleSize, "m_ScaleSize"));

REFLECT(CLASS(ParticleSystemExplosionQuicksave),
MEMBER(getIsActive, "GetIsActive"),
MEMBER(rpParticleResource, "m_rpParticleResource"),
MEMBER(startTime, "m_StartTime"),
MEMBER(endTime, "m_EndTime"),
MEMBER(pos, "m_Pos"),
MEMBER(size, "m_Size"),
MEMBER(bFlipX, "m_bFlipX"),
MEMBER(bFlipY, "m_bFlipY"));

REFLECT(CLASS(ObjectiveActionKillTallyDestructableObjectsQuicksave),
MEMBER(complete, "Complete"),
MEMBER(triggered, "Triggered"),
MEMBER(numBeforeTriggered, "NumBeforeTriggered"));

REFLECT(BASEDCLASS(ResourcePack, AIConversation),
MEMBER(humans,"Humans"),
MEMBER(chatLines,"ChatLines"),
MEMBER(active, "Active"),
MEMBER(delayMin, "DelayMin"),
MEMBER(delayMax, "DelayMax"));

REFLECT(BASEDCLASS(ResourcePack, ResourceObjectRocketTargetInfo),
MEMBER(nodes, "Nodes"));

REFLECT(BASEDCLASS(ResourceObjectSFXBlaster, ResourceObjectSFXCliffMite));
REFLECT(BASEDCLASS(ResourceObjectSFXBlaster, ResourceObjectSFXChariot));

REFLECT(BASEDCLASS(ResourceObjectSFXBomber, ResourceObjectSFXDropshipGrunt));
REFLECT(BASEDCLASS(ResourceObjectSFXBomber, ResourceObjectSFXDropshipCargo));
REFLECT(BASEDCLASS(ResourceObjectSFXBomber, ResourceObjectSFXDropshipMarauder));

REFLECT(CLASS(ResourceParticleDustStormRain),
MEMBER(rainActive, "RainActive"),
MEMBER(rainVel, "RainVel"),
MEMBER(rainKickupSize, "RainKickupSize"),
MEMBER(launchNum, "LaunchNum"),
MEMBER(rainLife, "RainLife"),
MEMBER(launchYOffset, "LaunchYOffset"),
MEMBER(lenScale, "LenScale"),
MEMBER(widScale, "WidScale"),
MEMBER(velScale, "VelScale"),
MEMBER(colourStart, "ColourStart"),
MEMBER(colourEnd, "ColourEnd"),
MEMBER(rainMinU, "RainMin_U"),
MEMBER(rainMinV, "RainMin_V"),
MEMBER(rainMaxU, "RainMax_U"),
MEMBER(rainMaxV, "RainMax_V"));

REFLECT(BASEDCLASS(ResourcePack, ResourceParticleDustStorm),
MEMBER(particleType, "ParticleType"),
MEMBER(colour, "Colour"),
MEMBER(texCoord, "TexCoord"),
MEMBER(startSize, "StartSize"),
MEMBER(endSize, "EndSize"),
MEMBER(lifeTime, "LifeTime"),
MEMBER(gravity, "Gravity"),
MEMBER(drag, "Drag"),
MEMBER(wind, "Wind"),
MEMBER(kickupRate, "KickupRate"),
MEMBER(kickupVariance, "KickupVariance"),
MEMBER(kickupVelocity, "KickupVelocity"),
MEMBER(diffusion, "Diffusion"),
MEMBER(grapFromAtmosphere, "Grap from Atmosphere"),
MEMBER(rayLeighColour, "RayLeigh Colour"),
MEMBER(mieColour, "Mie Colour"),
MEMBER(mieFactor, "Mie Factor"),
MEMBER(fogHalfDistance, "Fog Half Distance"),
MEMBER(fogPercentMie, "Fog Percent Mie"),
MEMBER(inScatteringModifier, "InScattering Modifier"),
MEMBER(changeTime, "Change Time"),
MEMBER(useAtmosphereSettings, "Use Atmosphere Settings"),
MEMBER(aroundCamera, "AroundCamera"),
MEMBER(rainData, "Rain Data"));

REFLECT(BASEDCLASS(ResourcePack, ResourceSpeechBankGrunt),
MEMBER(speechSets, "SpeechSets"));

REFLECT(BASEDCLASS(ResourcePack, ResourceSpeechBankLeader),
MEMBER(speechSets, "SpeechSets"));

REFLECT(BASEDCLASS(ResourcePack, ResourceSpeechBankPsiOps),
MEMBER(speechSets, "SpeechSets"));

REFLECT(BASEDCLASS(ResourcePack, ResourceSpeechBankMechanic),
MEMBER(speechSets, "SpeechSets"));
