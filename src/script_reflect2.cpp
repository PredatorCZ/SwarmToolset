#include "script/tuning.hpp"

#include "spike/reflect/detail/reflector_class.hpp"
#include "spike/reflect/detail/reflector_enum.hpp"

REFLECT(BASEDCLASS(ResourcePack, TuningDataScript),
MEMBER(tdsType, "TDS_Type"));

REFLECT(CLASS(TuningDataScript_AIManagerGeneral),
MEMBER(maxDeadBodies, "MaxDeadBodies"),
MEMBER(warriorRumbleCutoffDist, "WarriorRumbleCutoffDist"),
MEMBER(warriorRumbleMaxDist, "WarriorRumbleMaxDist"),
MEMBER(warriorRumbleVolumeFactor, "WarriorRumbleVolumeFactor"));

REFLECT(CLASS(TuningDataScript_AIManagerDeadBodyRemoval),
MEMBER(ageFactor, "AgeFactor"),
MEMBER(angleFactor, "AngleFactor"),
MEMBER(bigBodyBodyFadeOutTime, "BigBodyBodyFadeOutTime"),
MEMBER(bodyFadeOutTime, "BodyFadeOutTime"),
MEMBER(maxNumberRagdolls, "MaxNumberRagdolls"),
MEMBER(onFireFactor, "OnFireFactor"),
MEMBER(rangeFactor, "RangeFactor"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_AIManager),
MEMBER(deadBodyRemoval, "DeadBodyRemoval"),
MEMBER(general, "General"));

REFLECT(CLASS(TuningDataScript_AmmoPickupAmmoBox),
MEMBER(checkRadius, "CheckRadius"),
MEMBER(checkTime, "CheckTime"),
MEMBER(pickupNumber, "PickupNumber"),
MEMBER(timePerPickup, "TimePerPickup"));

REFLECT(CLASS(TuningDataScript_AmmoPickupAmmoBundle),
MEMBER(checkRadius, "CheckRadius"),
MEMBER(checkTime, "CheckTime"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_AmmoPickup),
MEMBER(ammoBox, "AmmoBox"),
MEMBER(ammoBundle, "AmmoBundle"),);

REFLECT(CLASS(TuningDataScriptSpottingTargetBias),
MEMBER(aiHuman, "AIHuman"),
MEMBER(player, "Player"),
MEMBER(vehicle, "Vehicle"));

REFLECT(CLASS(TuningDataScriptSpotting),
MEMBER(chance, "Chance"),
MEMBER(cone, "Cone"),
MEMBER(rangeMax, "RangeMax"),
MEMBER(rangeMin, "RangeMin"));

REFLECT(CLASS(TuningDataScriptSpotting3),
MEMBER(cone, "Cone"),
MEMBER(rangeChance, "RangeChance"),
MEMBER(rangeMax, "RangeMax"),
MEMBER(rangeMin, "RangeMin"));

REFLECT(BASEDCLASS(TuningDataScriptSpotting, TuningDataScriptSpotting2),
MEMBER(torchSightModifier, "TorchSightModifier"));

REFLECT(CLASS(TuningDataScriptDamage),
MEMBER(pierceSoft, "PierceSoft"),
MEMBER(pierceHard, "PierceHard"),
MEMBER(slash, "Slash"),
MEMBER(blast, "Blast"),
MEMBER(corrosive, "Corrosive"),
MEMBER(electricity, "Electricity"),
MEMBER(heat, "Heat"),
MEMBER(psiOps, "PsiOps"),
MEMBER(punch, "Punch"));

REFLECT(CLASS(TuningDataScriptStrength),
MEMBER(bulletSoft, "BulletSoft"),
MEMBER(bulletHard, "BulletHard"),
MEMBER(slash, "Slash"),
MEMBER(blast, "Blast"),
MEMBER(corrosive, "Corrosive"),
MEMBER(electricity, "Electricity"),
MEMBER(heat, "Heat"),
MEMBER(psiOps, "PsiOps"),
MEMBER(punch, "Punch"));

REFLECT(BASEDCLASS(TuningDataScriptStrength, TuningDataScriptPlayerStrength),
MEMBER(bulletHard, "Bullet"),
MEMBER(light, "Light"),
MEMBER(sonic, "Sonic"));

REFLECT(BASEDCLASS(TuningDataScriptPlayerStrength, TuningDataScriptPlayerShield),
MEMBER(bulletHard, "Bullet"),
MEMBER(rechargeDelay, "RechargeDelay"),
MEMBER(rechargeRate, "RechargeRate"));

REFLECT(BASEDCLASS(TuningDataScriptDamage, TuningDataScriptCoreDamage),
MEMBER(coreRadius, "CoreRadius"),
MEMBER(light, "Light"),
MEMBER(sonic, "Sonic"));

REFLECT(CLASS(TuningDataScriptDamage2),
MEMBER(nonPlayerFactor, "NonPlayerFactor"));

REFLECT(CLASS(TuningDataScriptAttackForceBarge),
MEMBER(punch, "Punch"));

REFLECT(CLASS(TuningDataScript2FootImpact),
MEMBER(punchMultiplierFLeg, "PunchMultiplierFLeg"),
MEMBER(punchMultiplierRLeg, "PunchMultiplierRLeg"),
MEMBER(dustRateModifier, "DustRateModifier"));

REFLECT(BASEDCLASS(TuningDataScript2FootImpact, TuningDataScript3FootImpact),
MEMBER(punchMultiplierMLeg, "PunchMultiplierMLeg"));

REFLECT(CLASS(TuningDataScriptNavigator),
MEMBER(capsuleRadius, "CapsuleRadius"),
MEMBER(capsuleOffsetX, "CapsuleOffsetX"),
MEMBER(capsuleOffsetY, "CapsuleOffsetY"),
MEMBER(capsuleOffsetZ, "CapsuleOffsetZ"),
MEMBER(capsuleRadiusIgnore, "CapsuleRadiusIgnore"),
MEMBER(baseSizeX, "BaseSizeX"),
MEMBER(baseSizeY, "BaseSizeY"),
MEMBER(baseSizeZ, "BaseSizeZ"),
MEMBER(maxGradient, "MaxGradient"));

REFLECT(CLASS(TuningDataScriptNavigatorSpeed),
MEMBER(maxTurn, "MaxTurn"),
MEMBER(stepLength, "StepLength"),
MEMBER(stepTime, "StepTime"));

REFLECT(CLASS(TuningDataScriptNetworkStrategy),
MEMBER(deltaHealthMoveChance, "DeltaHealthMoveChance"),
MEMBER(minTimeBeforeMove, "MinTimeBeforeMove"),
MEMBER(moveWaypointChance, "MoveWaypointChance"),
MEMBER(wpDeltaHealth, "WPDeltaHealth"));

REFLECT(CLASS(TuningDataScriptBolt),
MEMBER(blastForce, "BlastForce"),
MEMBER(fallOff, "FallOff"),
MEMBER(hotSpot, "HotSpot"),
MEMBER(minDistance, "MinDistance"),
MEMBER(speed, "Speed"));

REFLECT(CLASS(TuningDataScriptAccuracy),
MEMBER(firePredictionTime, "FirePredictionTime"),
MEMBER(maxVariance, "MaxVariance"),
MEMBER(minVariance, "MinVariance"),
MEMBER(numberOfIntervals, "Number_Of_Intervals"));

REFLECT(CLASS(TuningDataScript_TankerBabyAccuracy),
MEMBER(firePredictionTime, "FirePredictionTime"),
MEMBER(maxVariance, "MaximumVariance"),
MEMBER(minVariance, "MinimumVariance"),
MEMBER(numberOfIntervals, "Num_Intervals"));

REFLECT(CLASS(TuningDataScript_CliffMiteAccuracy),
MEMBER(firePredictionTime, "FirePredictionTime"),
MEMBER(maxVariance, "Maximum_Variance"),
MEMBER(minVariance, "Minimum_Variance"),
MEMBER(numberOfIntervals, "Number_of_Intervals"));

REFLECT(CLASS(TuningDataScript_TigerShardAccuracy),
MEMBER(firePredictionTime, "FirePredictionTime"),
MEMBER(maxVariance, "MaximumVariance"),
MEMBER(minVariance, "MinimumVariance"),
MEMBER(numberOfIntervals, "Number_Of_Intervals"));

REFLECT(BASEDCLASS(TuningDataScriptDamage2, TuningDataScript_BabyPlasmaDamage),
MEMBER(thresholdForDamageToBody, "ThresholdForDamageToBody"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_BabyPlasma),
MEMBER(accuracy, "Accuracy"),
MEMBER(attackForceBarge, "AttackForceBarge"),
MEMBER(bolt, "Bolt"),
MEMBER(damage, "Damage"),
MEMBER(damageStrengthArse, "DamageStrengthArse"),
MEMBER(damageStrengthHead, "DamageStrengthHead"),
MEMBER(footImpact, "FootImpact"),
MEMBER(navigator, "Navigator"),
MEMBER(navigatorSpeedData0, "Navigator_SpeedData0"),
MEMBER(navigatorSpeedData1, "Navigator_SpeedData1"),
MEMBER(networkStrategy, "NetworkStrategy"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingAlert, "SpottingAlert"),
MEMBER(spottingIdle, "SpottingIdle"),
MEMBER(spottingTargetBias, "SpottingTargetBias"));

REFLECT(CLASS(TuningDataScriptFire),
MEMBER(resistanceThreshold, "ResistanceThreshold"));

REFLECT(BASEDCLASS(TuningDataScriptFire, TuningDataScriptFire2),
MEMBER(onFireDamageRate, "OnFireDamageRate"));

REFLECT(CLASS(TuningDataScript_BlasterStrategy),
MEMBER(attackRadius, "AttackRadius"),
MEMBER(closeOnTargetChance, "CloseOnTargetChance"));
REFLECT(CLASS(TuningDataScript_BlasterAttack),
MEMBER(horizontalFiringAngle, "HorizontalFiringAngle"),
MEMBER(maxFiringRange, "MaxFiringRange"),
MEMBER(meleeAttackDist, "MeleeAttackDist"),
MEMBER(verticalFiringAngle, "VerticalFiringAngle"));
REFLECT(CLASS(TuningDataScript_BlasterAccuracy),
MEMBER(maxiumumVariance, "Maxiumum_Variance"),
MEMBER(miniumumVariance, "Miniumum_Variance"),
MEMBER(numberOfIntervals, "Number_Of_Intervals"));
REFLECT(CLASS(TuningDataScript_BlasterNavigator),
MEMBER(baseSizeX, "BaseSizeX"),
MEMBER(baseSizeY, "BaseSizeY"),
MEMBER(baseSizeZ, "BaseSizeZ"),
MEMBER(capsuleOffsetX, "CapsuleOffsetX"),
MEMBER(capsuleOffsetY, "CapsuleOffsetY"),
MEMBER(capsuleOffsetZ, "CapsuleOffsetZ"),
MEMBER(capsuleRadius, "CapsuleRadius"),
MEMBER(capsuleRadiusIgnore, "CapsuleRadiusIgnore"),
MEMBER(desiredJumpResolution, "DesiredJumpResolution"),
MEMBER(desiredResolutionX, "DesiredResolutionX"),
MEMBER(desiredResolutionZ, "DesiredResolutionZ"),
MEMBER(extraDesiredJumpResolution, "ExtraDesiredJumpResolution"),
MEMBER(extraJumpHeightMax, "ExtraJumpHeightMax"),
MEMBER(gridLengthMax, "GridLengthMax"),
MEMBER(gridLengthMin, "GridLengthMin"),
MEMBER(gridWidth, "GridWidth"),
MEMBER(jumpHeightMax, "JumpHeightMax"),
MEMBER(jumpHeightMin, "JumpHeightMin"),
MEMBER(maxGradient, "MaxGradient"));
REFLECT(CLASS(TuningDataScript_BlasterProjectile),
MEMBER(falloff, "Falloff"),
MEMBER(fireRate, "FireRate"),
MEMBER(force, "Force"),
MEMBER(hotspot, "Hotspot"));
REFLECT(CLASS(TuningDataScript_BlasterMisc),
MEMBER(facingAngle, "FacingAngle"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Blaster),
MEMBER(accuracy, "Accuracy"),
MEMBER(attack, "Attack"),
MEMBER(attackForceBarge, "AttackForceBarge"),
MEMBER(damage, "Damage"),
MEMBER(damageStrength, "DamageStrength"),
MEMBER(fire, "Fire"),
MEMBER(misc, "Misc"),
MEMBER(navigator, "Navigator"),
MEMBER(projectile, "Projectile"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingAlert, "SpottingAlert"),
MEMBER(spottingIdle, "SpottingIdle"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(strategy, "Strategy"));

REFLECT(CLASS(TuningDataScript_ChariotStrategy),
MEMBER(millingMoveChance, "MillingMoveChance"),
MEMBER(millingRadius, "MillingRadius"),
MEMBER(scurryDistance, "ScurryDistance"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Chariot),
MEMBER(damageStrengthHead, "DamageStrengthHead"),
MEMBER(damage, "Damage"),
MEMBER(fire, "Fire"),
MEMBER(navigator, "Navigator"),
MEMBER(navigatorSpeedData0, "Navigator_SpeedData0"),
MEMBER(navigatorSpeedData1, "Navigator_SpeedData1"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingAlert, "SpottingAlert"),
MEMBER(spottingIdle, "SpottingIdle"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(strategy, "Strategy"));

REFLECT(CLASS(TuningDataScript_CliffMiteSpotting),
MEMBER(alertChance, "AlertChance"),
MEMBER(alertCone, "AlertCone"),
MEMBER(alertRangeMax, "AlertRangeMax"),
MEMBER(alertRangeMin, "AlertRangeMin"),
MEMBER(idleChance, "IdleChance"),
MEMBER(idleCone, "IdleCone"),
MEMBER(idleRangeMax, "IdleRangeMax"),
MEMBER(idleRangeMin, "IdleRangeMin"),
MEMBER(torchSightModifier, "TorchSightModifier"));
REFLECT(CLASS(TuningDataScript_CliffMiteAttack),
MEMBER(farChance, "FarChance"),
MEMBER(farRange, "FarRange"),
MEMBER(maxFiringArc, "MaxFiringArc"),
MEMBER(nearChance, "NearChance"),
MEMBER(nearRange, "NearRange"));
REFLECT(CLASS(TuningDataScript_CliffMiteMissile),
MEMBER(damage, "Damage"),
MEMBER(life, "Life"),
MEMBER(minDamageFactor, "Min_Damage_Factor"),
MEMBER(speed, "Speed"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_CliffMite),
MEMBER(accuracy, "Accuracy"),
MEMBER(attack, "Attack"),
MEMBER(damage, "Damage"),
MEMBER(damageStrength, "DamageStrength"),
MEMBER(missile, "Missile"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingTargetBias, "SpottingTargetBias"));

REFLECT(CLASS(TuningDataScript_ElectricFenceFenceParameters),
MEMBER(electricityForce, "ElectricityForce"),
MEMBER(heightBottom, "HeightBottom"),
MEMBER(heightTop, "HeightTop"),
MEMBER(testDelay, "TestDelay"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_ElectricFence),
MEMBER(fenceParameters, "FenceParameters"),
MEMBER(postDamageStrength, "PostDamageStrength"));

REFLECT(CLASS(TuningDataScriptFlyingVehicles),
MEMBER(flightSpeedFast, "FlightSpeedFast"),
MEMBER(flightSpeedMedium, "FlightSpeedMedium"),
MEMBER(flightSpeedSlow, "FlightSpeedSlow"),
MEMBER(rotationRate, "RotationRate"));
REFLECT(BASEDCLASS(TuningDataScriptFlyingVehicles, TuningDataScript_FlyingVehiclesMarauderDropship),
MEMBER(playerHeading, "PlayerHeading"),
MEMBER(playerHeadingArc, "PlayerHeadingArc"),
MEMBER(playerPitch, "PlayerPitch"),
MEMBER(playerPitchArc, "PlayerPitchArc"),
MEMBER(playerPosX, "PlayerPosX"),
MEMBER(playerPosY, "PlayerPosY"),
MEMBER(playerPosZ, "PlayerPosZ"));

REFLECT(CLASS(TuningDataScript_FlyingVehiclesBomberBomb),
MEMBER(blastFalloff, "Blast_Falloff"),
MEMBER(blastForce, "Blast_Force"),
MEMBER(blastHotspot, "Blast_Hotspot"),
MEMBER(napalmLaunchNum, "Napalm_LaunchNum"),
MEMBER(naplamBlastFalloff, "Naplam_BlastFalloff"),
MEMBER(naplamBlastForce, "Naplam_BlastForce"),
MEMBER(naplamBlastHotspot, "Naplam_BlastHotspot"),
MEMBER(naplamLaunchSize, "Naplam_LaunchSize"),
MEMBER(naplamLaunchTime, "Naplam_LaunchTime"),
MEMBER(projectileLaunchSpeed, "ProjectileLaunchSpeed"));

REFLECT(CLASS(TuningDataScript_FlyingVehiclesDownDraft),
MEMBER(blastValue, "BlastValue"),
MEMBER(deltaTime, "DeltaTime"),
MEMBER(rayLength, "RayLength"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_FlyingVehicles),
MEMBER(bomber, "Bomber"),
MEMBER(bomberBomb, "BomberBomb"),
MEMBER(cargoDropship, "CargoDropship"),
MEMBER(downDraft, "DownDraft"),
MEMBER(gruntDropship, "GruntDropship"),
MEMBER(marauderDropship, "MarauderDropship"));

REFLECT(CLASS(TuningDataScript_HandGrenadeFirstPerson),
MEMBER(countdownTime, "CountdownTime"),
MEMBER(launchVelFore, "LaunchVel_Fore"),
MEMBER(launchVelUp, "LaunchVel_Up"),
MEMBER(stayPrimedTime, "StayPrimedTime"));
REFLECT(CLASS(TuningDataScript_HandGrenadeMovementData),
MEMBER(activeTime, "ActiveTime"),
MEMBER(bounceNormalLoss, "BounceNormalLoss"),
MEMBER(bounceParallelVel, "BounceParallelVel"),
MEMBER(radius, "Radius"),
MEMBER(rollingDrag, "RollingDrag"),
MEMBER(trooperCheckDelay, "TrooperCheckDelay"));
REFLECT(CLASS(TuningDataScript_HandGrenadeBlast),
MEMBER(fallOff, "FallOff"),
MEMBER(force, "Force"),
MEMBER(hotSpot, "HotSpot"));
REFLECT(CLASS(TuningDataScript_HandGrenadeSafeRadius),
MEMBER(aIHuman, "AIHuman"),
MEMBER(player, "Player"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_HandGrenade),
MEMBER(blast, "Blast"),
MEMBER(firstPerson, "FirstPerson"),
MEMBER(movementData, "MovementData"),
MEMBER(safeRadius, "SafeRadius"));

REFLECT(CLASS(TuningDataScript_HopperStrength),
MEMBER(bulletBlast, "BulletBlast"),
MEMBER(bulletBody, "BulletBody"),
MEMBER(bulletHead, "BulletHead"),
MEMBER(bulletWings, "BulletWings"),
MEMBER(heat, "Heat"));
REFLECT(CLASS(TuningDataScript_HopperFlightSpeed),
MEMBER(fast, "Fast"),
MEMBER(medium, "Medium"),
MEMBER(slow, "Slow"),
MEMBER(vFast, "VFast"),
MEMBER(vvFast, "VVFast"));
REFLECT(CLASS(TuningDataScript_HopperSpotting),
MEMBER(chance, "Chance"),
MEMBER(cone, "Cone"),
MEMBER(rangeMax, "RangeMax"),
MEMBER(rangeMin, "RangeMin"),
MEMBER(torchSightModifier, "TorchSightModifier"));
REFLECT(CLASS(TuningDataScript_HopperAttack),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_HopperAttackForce),
MEMBER(blast, "Blast"),
MEMBER(corrosive, "Corrosive"),
MEMBER(heat, "Heat"),
MEMBER(innerRadius, "InnerRadius"),
MEMBER(outerRadius, "OuterRadius"));
REFLECT(CLASS(TuningDataScript_HopperAudio),
MEMBER(screechChance, "ScreechChance"),
MEMBER(screechGibChance, "ScreechGibChance"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Hopper),
MEMBER(attack, "Attack"),
MEMBER(attackForce, "AttackForce"),
MEMBER(audio, "Audio"),
MEMBER(damage, "Damage"),
MEMBER(fire, "Fire"),
MEMBER(flightSpeed, "FlightSpeed"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(strength, "Strength"));

REFLECT(CLASS(TuningDataScript_HopperFireflyStrength),
MEMBER(blast, "Blast"),
MEMBER(bulletBody, "BulletBody"),
MEMBER(bulletHead, "BulletHead"),
MEMBER(bulletWings, "BulletWings"),
MEMBER(heat, "Heat"));
REFLECT(CLASS(TuningDataScript_HopperFireflyFlightSpeed),
MEMBER(fast, "Fast"),
MEMBER(medium, "Medium"),
MEMBER(slow, "Slow"),
MEMBER(vFast, "VFast"),
MEMBER(vvFast, "VVFast"));
REFLECT(CLASS(TuningDataScript_HopperFireflySpotting),
MEMBER(chance, "Chance"),
MEMBER(cone, "Cone"),
MEMBER(rangeMax, "RangeMax"),
MEMBER(rangeMin, "RangeMin"),
MEMBER(torchSightModifier, "TorchSightModifier"));
REFLECT(CLASS(TuningDataScript_HopperFireflyAttack),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_HopperFireflyAttackForce),
MEMBER(blast, "Blast"),
MEMBER(corrosive, "Corrosive"),
MEMBER(heat, "Heat"),
MEMBER(innerRadius, "InnerRadius"),
MEMBER(outerRadius, "OuterRadius"));
REFLECT(CLASS(TuningDataScript_HopperFireflyBolt),
MEMBER(blastForce, "BlastForce"),
MEMBER(blastHotspot, "BlastHotspot"),
MEMBER(falloff, "Falloff"),
MEMBER(speed, "Speed"));
REFLECT(CLASS(TuningDataScript_HopperFireflyAudio),
MEMBER(screechChance, "ScreechChance"),
MEMBER(screechGibChance, "ScreechGibChance"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_HopperFirefly),
MEMBER(attack, "Attack"),
MEMBER(attackForce, "AttackForce"),
MEMBER(audio, "Audio"),
MEMBER(bolt, "Bolt"),
MEMBER(damage, "Damage"),
MEMBER(fire, "Fire"),
MEMBER(flightSpeed, "FlightSpeed"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(strength, "Strength"));

REFLECT(CLASS(TuningDataScript_HopperRipplerStrength),
MEMBER(blast, "Blast"),
MEMBER(bulletBody, "BulletBody"),
MEMBER(bulletHead, "BulletHead"),
MEMBER(bulletWings, "BulletWings"),
MEMBER(heat, "Heat"));
REFLECT(CLASS(TuningDataScript_HopperRipplerFlightSpeed),
MEMBER(fast, "Fast"),
MEMBER(medium, "Medium"),
MEMBER(slow, "Slow"),
MEMBER(vFast, "VFast"),
MEMBER(vvFast, "VVFast"));
REFLECT(CLASS(TuningDataScript_HopperRipplerSpotting),
MEMBER(chance, "Chance"),
MEMBER(cone, "Cone"),
MEMBER(rangeMax, "RangeMax"),
MEMBER(rangeMin, "RangeMin"),
MEMBER(torchSightModifier, "TorchSightModifier"));
REFLECT(CLASS(TuningDataScript_HopperRipplerAttack),
MEMBER(speed, "Speed"),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_HopperRipplerAttackForce),
MEMBER(blast, "Blast"),
MEMBER(corrosive, "Corrosive"),
MEMBER(heat, "Heat"),
MEMBER(innerRadius, "InnerRadius"),
MEMBER(outerRadius, "OuterRadius"));
REFLECT(CLASS(TuningDataScript_HopperRipplerAudio),
MEMBER(screechChance, "ScreechChance"),
MEMBER(screechGibChance, "ScreechGibChance"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_HopperRippler),
MEMBER(attack, "Attack"),
MEMBER(attackForce, "AttackForce"),
MEMBER(audio, "Audio"),
MEMBER(damage, "Damage"),
MEMBER(fire, "Fire"),
MEMBER(flightSpeed, "FlightSpeed"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(strength, "Strength"));

REFLECT(CLASS(TuningDataScript_HumanSpotting),
MEMBER(minimumInterval, "MinimumInterval"),
MEMBER(movingMultiplier, "MovingMultiplier"));
REFLECT(CLASS(TuningDataScript_HumanSpottingAlert),
MEMBER(chance, "Chance"),
MEMBER(cone, "Cone"),
MEMBER(rangeMax, "RangeMax"),
MEMBER(rangeMin, "RangeMin"),
MEMBER(targetTimeout, "TargetTimeout"));
REFLECT(CLASS(TuningDataScript_HumanGrenade),
MEMBER(chance, "Chance"),
MEMBER(launchVel, "LaunchVel"),
MEMBER(maxAngle, "MaxAngle"),
MEMBER(maxRandomOffset, "MaxRandomOffset"),
MEMBER(minimumInterval, "MinimumInterval"),
//MEMBER(minimumPersonalInterval, "MinimumPersonalInterval"),
MEMBER(rangeMax, "RangeMax"),
MEMBER(rangeMin, "RangeMin"),
MEMBER(throwDelay, "ThrowDelay"));
REFLECT(CLASS(TuningDataScript_HumanPsiOps),
MEMBER(averageKillTime, "AverageKillTime"),
MEMBER(killGibForce, "KillGibForce"),
MEMBER(maxKillDistance, "MaxKillDistance"));
REFLECT(CLASS(TuningDataScript_HumanAttract),
MEMBER(celebrateChance, "CelebrateChance"),
MEMBER(fireAttractMaximumInterval, "FireAttractMaximumInterval"),
MEMBER(fireAttractMinimumInterval, "FireAttractMinimumInterval"),
MEMBER(lookPlayerChance, "LookPlayerChance"),
MEMBER(lookPlayerMaximumInterval, "LookPlayerMaximumInterval"),
MEMBER(lookPlayerMinimumInterval, "LookPlayerMinimumInterval"),
MEMBER(lookPlayerPersonalInterval, "LookPlayerPersonalInterval"),
MEMBER(noticePlayerDistance, "NoticePlayerDistance"),
MEMBER(saluteRadius, "SaluteRadius"));
REFLECT(CLASS(TuningDataScript_HumanSize),
MEMBER(sizeX, "Size_X"),
MEMBER(sizeY, "Size_Y"),
MEMBER(sizeZ, "Size_Z"));
REFLECT(CLASS(TuningDataScript_HumanNavigation),
MEMBER(baseSizeX, "BaseSizeX"),
MEMBER(baseSizeY, "BaseSizeY"),
MEMBER(baseSizeZ, "BaseSizeZ"),
MEMBER(capsuleRadius, "CapsuleRadius"),
MEMBER(maxGradient, "MaxGradient"),
MEMBER(minStaticTurnAng, "MinStaticTurnAng"));
REFLECT(CLASS(TuningDataScript_HumanDamageStrength),
//MEMBER(headShotModifier,"HeadShotModifier"),
MEMBER(strengthBlast, "StrengthBlast"),
MEMBER(strengthCorrosive, "StrengthCorrosive"),
MEMBER(strengthElectric, "StrengthElectric"),
MEMBER(strengthHeat, "StrengthHeat"),
MEMBER(strengthLight, "StrengthLight"),
MEMBER(strengthPierceHard, "StrengthPierceHard"),
MEMBER(strengthPierceSoft, "StrengthPierceSoft"),
MEMBER(strengthPunch, "StrengthPunch"),
MEMBER(strengthSlash, "StrengthSlash"),
MEMBER(strengthSonic, "StrengthSonic"));
REFLECT(CLASS(TuningDataScript_HumanBlastLaunch),
MEMBER(maxSteps, "MaxSteps"),
MEMBER(minVal, "MinVal"),
MEMBER(multiplier, "Multiplier"),
MEMBER(timeStep, "TimeStep"));
REFLECT(CLASS(TuningDataScript_HumanPunchLaunch),
MEMBER(minVal, "MinVal"));
REFLECT(CLASS(TuningDataScript_HumanSetOnFire),
MEMBER(minVal, "MinVal"));
REFLECT(CLASS(TuningDataScript_HumanGrenadesDropped),
MEMBER(maxAmount, "Max amount"),
MEMBER(minAmount, "Min amount"),
MEMBER(xzVelocity, "XZ Velocity"),
MEMBER(yVelocity, "Y Velocity"));
REFLECT(CLASS(TuningDataScript_HumanKneeling),
MEMBER(kneelChance, "KneelChance"),
MEMBER(minTime, "MinTime"),
MEMBER(standChance, "StandChance"));
REFLECT(CLASS(TuningDataScript_HumanAttractTurn),
MEMBER(chance, "Chance"),
MEMBER(maxAngle, "Max Angle"),
MEMBER(minAngle, "Min Angle"));
REFLECT(CLASS(TuningDataScript_HumanSpeechChance),
MEMBER(blindedMinInterval, "BlindedMinInterval"),
MEMBER(blindedPersonalInterval, "BlindedPersonalInterval"),
MEMBER(cCMaxHealth, "CCMaxHealth"),
MEMBER(ceaseFireDelay, "CeaseFire"),
MEMBER(ceaseFireDelay, "CeaseFireDelay"),
MEMBER(combatCrazy, "CombatCrazy"),
MEMBER(commentRange, "CommentRange"),
MEMBER(dropShipDisembard, "DropShipDisembard"),
MEMBER(dying, "Dying"),
MEMBER(fFMinInterval, "FFMinInterval"),
MEMBER(friendlyFire, "FriendlyFire"),
MEMBER(greatShotMinInterval, "GreatShotMinInterval"),
MEMBER(greatShotPersonalInterval, "GreatShotPersonalInterval"),
MEMBER(greatShotRadius, "GreatShotRadius"),
MEMBER(hopperDuck, "HopperDuck"),
MEMBER(idleComment, "IdleComment"),
MEMBER(killBig, "KillBig"),
MEMBER(killBlasterCliffmite, "KillBlasterCliffmite"),
MEMBER(killHopper, "KillHopper"),
MEMBER(killSentinelChariot, "KillSentinelChariot"),
MEMBER(killTiger, "KillTiger"),
MEMBER(killWarrior, "KillWarrior"),
MEMBER(lowHealthHealth, "LowHealth"),
MEMBER(lowHealthHealth, "LowHealthHealth"),
MEMBER(lowHealthMaxInterval, "LowHealthMaxInterval"),
MEMBER(lowHealthMinInterval, "LowHealthMinInterval"),
MEMBER(lowHealthPersonalInterval, "LowHealthPersonalInterval"),
MEMBER(manDown, "ManDown"),
MEMBER(manDownMaxInterval, "ManDownMaxInterval"),
MEMBER(manDownMinInterval, "ManDownMinInterval"),
MEMBER(manDownPersonalInterval, "ManDownPersonalInterval"),
MEMBER(manDownRadius, "ManDownRadius"),
MEMBER(minTimeSinceAttack, "MinTimeSinceAttack"),
MEMBER(minTimeSinceHurt, "MinTimeSinceHurt"),
MEMBER(openFire, "OpenFire"),
MEMBER(thankPlayerMaxHealth, "ThankPlayerMaxHealth"),
MEMBER(thankPlayerMinInterval, "ThankPlayerMinInterval"),
MEMBER(thankPlayerPersonalInterval, "ThankPlayerPersonalInterval"),
MEMBER(thankPlayerRadius, "ThankPlayerRadius"),
MEMBER(throwGrenade, "ThrowGrenade"),
MEMBER(wounded, "Wounded"));
REFLECT(CLASS(TuningDataScript_HumanTargetBias),
MEMBER(babyPlasma, "BabyPlasma"),
MEMBER(babyTanker, "BabyTanker"),
MEMBER(blaster, "Blaster"),
MEMBER(chariot, "Chariot"),
MEMBER(cliffMite, "CliffMite"),
MEMBER(fireFly, "FireFly"),
MEMBER(hopper, "Hopper"),
MEMBER(plasma, "Plasma"),
MEMBER(rhino, "Rhino"),
MEMBER(rippler, "Rippler"),
MEMBER(royal, "Royal"),
MEMBER(royalX, "RoyalX"),
MEMBER(sentinel, "Sentinel"),
MEMBER(tanker, "Tanker"),
MEMBER(tiger, "Tiger"),
MEMBER(tigerShard, "TigerShard"),
MEMBER(tigerSpit, "TigerSpit"),
MEMBER(warrior, "Warrior"));
REFLECT(CLASS(TuningDataScript_HumanSquad),
MEMBER(distanceCheckInterval, "DistanceCheckInterval"),
MEMBER(dropShipIgnoreTime, "DropShipIgnoreTime"),
MEMBER(followMaxDist, "FollowMaxDist"),
MEMBER(speed, "Speed"),
MEMBER(waitDistance, "WaitDistance"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Human),
MEMBER(attract, "Attract"),
MEMBER(attractTurn, "AttractTurn"),
MEMBER(blastLaunch, "BlastLaunch"),
//MEMBER(burstFire, "BurstFire"),
MEMBER(damageStrength, "DamageStrength"),
MEMBER(grenade, "Grenade"),
MEMBER(grenadesDropped, "GrenadesDropped"),
MEMBER(kneeling, "Kneeling"),
MEMBER(navigation, "Navigation"),
MEMBER(navigatorSpeedData0, "Navigator_Speed0"),
MEMBER(navigatorSpeedData1, "Navigator_Speed1"),
MEMBER(navigatorSpeedData2, "Navigator_Speed2"),
MEMBER(psiOps, "PsiOps"),
MEMBER(punchLaunch, "PunchLaunch"),
MEMBER(setOnFire, "SetOnFire"),
MEMBER(size, "Size"),
MEMBER(speechChance, "SpeechChance"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingAlert, "SpottingAlert"),
MEMBER(spottingIdle, "SpottingIdle"),
MEMBER(squad, "Squad"),
MEMBER(targetBias, "TargetBias"));

REFLECT(CLASS(TuningDataScript_LandMineWarning),
MEMBER(radius, "Radius"),
MEMBER(time, "Time"));
REFLECT(CLASS(TuningDataScript_LandMineInstant),
MEMBER(radius, "Radius"));
REFLECT(CLASS(TuningDataScript_LandMineBlast),
MEMBER(falloff, "Falloff"),
MEMBER(force, "Force"),
MEMBER(hotspot, "Hotspot"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_LandMine),
MEMBER(blast, "Blast"),
MEMBER(instant, "Instant"),
MEMBER(warning, "Warning"));

REFLECT(CLASS(TuningDataScript_MiscellaneousParticleEffect),
MEMBER(genericParticleEffectsPoolSize, "GenericParticleEffects_PoolSize"));
REFLECT(CLASS(TuningDataScript_MiscellaneousDecals),
MEMBER(decalDensityDrawnContext, "DecalDensity_DrawnContext"),
MEMBER(decalDensityNonDrawnContext, "DecalDensity_NonDrawnContext"),
MEMBER(decalRemovalOverlapFactor, "DecalRemoval_OverlapFactor"),
MEMBER(decalRemovalSizeFactor, "DecalRemoval_SizeFactor"),
MEMBER(temporaryDecalsCullTime, "TemporaryDecals_CullTime"),
MEMBER(temporaryDecalsMaxOverlap, "TemporaryDecals_MaxOverlap"));
REFLECT(CLASS(TuningDataScript_MiscellaneousNavigator),
MEMBER(lowLODRange, "LOW_LOD_Range"),
MEMBER(numberAngleToCheck, "NumberAngleToCheck"));
REFLECT(CLASS(TuningDataScript_MiscellaneousCollisions),
MEMBER(autoRangeFactor0, "AutoRangeFactor0"),
MEMBER(autoRangeFactor1, "AutoRangeFactor1"),
MEMBER(autoRangeFactor2, "AutoRangeFactor2"));
REFLECT(CLASS(TuningDataScript_MiscellaneousBlastCameraShake),
MEMBER(maxAngleX, "MaxAngleX"),
MEMBER(maxAngleY, "MaxAngleY"),
MEMBER(maxAngleZ, "MaxAngleZ"),
MEMBER(scale, "Scale"),
MEMBER(time, "Time"));
REFLECT(CLASS(TuningDataScript_MiscellaneousParticleEffects),
MEMBER(maxFlameSystems, "MaxFlameSystems"),
MEMBER(maxSmokeSystems, "MaxSmokeSystems"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Miscellaneous),
MEMBER(blastCameraShake, "BlastCameraShake"),
MEMBER(collisions, "Collisions"),
MEMBER(decals, "Decals"),
MEMBER(navigator, "Navigator"),
MEMBER(particleEffect, "ParticleEffect"),
MEMBER(particleEffects, "ParticleEffects"));

REFLECT(CLASS(TuningDataScript_MissileLauncherAmmo),
MEMBER(maxMissiles, "MaxMissiles"));
REFLECT(CLASS(TuningDataScript_MissileLauncherZoom),
MEMBER(zoomFactor, "ZoomFactor"));
REFLECT(CLASS(TuningDataScript_MissileLauncherShake),
MEMBER(fire1JoltAngle, "Fire1JoltAngle"),
MEMBER(fire1JoltTime, "Fire1JoltTime"),
MEMBER(fire2JoltAngle, "Fire2JoltAngle"),
MEMBER(fire2JoltTime, "Fire2JoltTime"));
REFLECT(CLASS(TuningDataScript_MissileLauncherMissileLaunch),
MEMBER(launchSpeed, "LaunchSpeed"),
MEMBER(launchingTime, "LaunchingTime"),
MEMBER(pitchingAngle, "PitchingAngle"));
REFLECT(CLASS(TuningDataScript_MissileLauncherMissileFlight),
MEMBER(flightSpeed, "FlightSpeed"),
MEMBER(guidance, "Guidance"),
MEMBER(lifeTime, "LifeTime"),
MEMBER(turnRate, "TurnRate"));
REFLECT(CLASS(TuningDataScript_MissileLauncherMissileBlast),
MEMBER(falloff, "Falloff"),
MEMBER(forceDamage, "ForceDamage"),
MEMBER(heatDamage, "HeatDamage"),
MEMBER(hotspot, "Hotspot"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_MissileLauncher),
MEMBER(ammo, "Ammo"),
MEMBER(coreDamage, "CoreDamage"),
MEMBER(missileBlast, "MissileBlast"),
MEMBER(missileFlight, "MissileFlight"),
MEMBER(missileLaunch, "MissileLaunch"),
MEMBER(shake, "Shake"),
MEMBER(zoom, "Zoom"));

REFLECT(CLASS(TuningDataScript_MoritiaMk2CarbineAmmo),
MEMBER(lowAmmo, "LowAmmo"),
MEMBER(maxNumber, "MaxNumber"));
REFLECT(CLASS(TuningDataScript_MoritiaMk2CarbinePrimary),
MEMBER(burstNumber, "BurstNumber"),
MEMBER(burstPause, "BurstPause"),
MEMBER(fireRate, "FireRate"),
MEMBER(range, "Range"),
MEMBER(spread, "Spread"),
MEMBER(spreadFirst, "SpreadFirst"),
MEMBER(strength, "Strength"));

REFLECT(CLASS(TuningDataScript_MoritiaMk2CarbineSecondary),
MEMBER(burstNumber, "BurstNumber"),
MEMBER(burstPause, "BurstPause"),
MEMBER(fireRate, "FireRate"),
MEMBER(range, "Range"),
MEMBER(spread, "Spread"),
MEMBER(spreadFirst, "SpreadFirst"),
MEMBER(strength, "Strength"));

REFLECT(CLASS(TuningDataScript_MoritiaMk2CarbineAIDrop),
MEMBER(maxBullets, "MaxBullets"),
MEMBER(minBullets, "MinBullets"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_MoritiaMk2Carbine),
MEMBER(aiDrop, "AIDrop"),
MEMBER(ammo, "Ammo"),
MEMBER(fireShake, "FireShake"),
MEMBER(fireShake2, "FireShake2"),
MEMBER(primary, "Primary"),
MEMBER(secondary, "Secondary"));

REFLECT(CLASS(TuningDataScript_MoritiaMk2GrenadeAmmo),
MEMBER(lowAmmo, "LowAmmo"),
MEMBER(maxNumber, "MaxNumber"),
MEMBER(numGrenades, "NumGrenades"));
REFLECT(CLASS(TuningDataScript_MoritiaMk2GrenadePrimary),
MEMBER(burstNumber, "BurstNumber"),
MEMBER(burstPause, "BurstPause"),
MEMBER(fireRate, "FireRate"),
MEMBER(range, "Range"),
MEMBER(spread, "Spread"),
MEMBER(spreadFirst, "SpreadFirst"),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_MoritiaMk2GrenadeGrenade),
MEMBER(launchVelY, "LaunchVelY"),
MEMBER(launchVelZ, "LaunchVelZ"));
REFLECT(CLASS(TuningDataScriptShake),
MEMBER(angleX, "AngleX"),
MEMBER(angleY, "AngleY"),
MEMBER(angleZ, "AngleZ"),
MEMBER(time, "Time"));
REFLECT(CLASS(TuningDataScriptJolt),
MEMBER(angleX, "AngleX"),
MEMBER(time, "Time"));
REFLECT(CLASS(TuningDataScript_MoritiaMk2GrenadeAIDrop),
MEMBER(maxBullets, "MaxBullets"),
MEMBER(maxGrenades, "MaxGrenades"),
MEMBER(minBullets, "MinBullets"),
MEMBER(minGrenades, "MinGrenades"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_MoritiaMk2Grenade),
MEMBER(aiDrop, "AIDrop"),
MEMBER(ammo, "Ammo"),
MEMBER(fireShake, "FireShake"),
MEMBER(grenade, "Grenade"),
MEMBER(grenadeJolt, "GrenadeJolt"),
MEMBER(primary, "Primary"));

REFLECT(CLASS(TuningDataScript_MoritiaMk2ShotgunAmmo),
MEMBER(lowAmmo, "LowAmmo"),
MEMBER(maxNumber, "MaxNumber"));
REFLECT(CLASS(TuningDataScript_MoritiaMk2ShotgunPrimary),
MEMBER(burstNumber, "BurstNumber"),
MEMBER(burstPause, "BurstPause"),
MEMBER(fireRate, "FireRate"),
MEMBER(range, "Range"),
MEMBER(spread, "Spread"),
MEMBER(spreadFirst, "SpreadFirst"),
//MEMBER(preadForPlayer, "SpreadForPlayer"),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_MoritiaMk2ShotgunSecondary),
MEMBER(numBullets, "NumBullets"),
MEMBER(range, "Range"),
MEMBER(spread, "Spread"),
MEMBER(strength, "Strength"));

REFLECT(CLASS(TuningDataScript_MoritiaMk2ShotgunAIDrop),
MEMBER(maxBullets, "MaxBullets"),
MEMBER(minBullets, "MinBullets"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_MoritiaMk2Shotgun),
MEMBER(aiDrop, "AIDrop"),
MEMBER(ammo, "Ammo"),
MEMBER(fire1Shake, "Fire1Shake"),
MEMBER(fire2Jolt, "Fire2Jolt"),
MEMBER(primary, "Primary"),
MEMBER(secondary, "Secondary"));

REFLECT(CLASS(TuningDataScript_MoritiaMk2ZoomAmmo),
MEMBER(lowAmmo, "LowAmmo"),
MEMBER(maxNumber, "MaxNumber"));
REFLECT(CLASS(TuningDataScript_MoritiaMk2ZoomPrimary),
MEMBER(burstNumber, "BurstNumber"),
MEMBER(burstPause, "BurstPause"),
MEMBER(fireRate, "FireRate"),
MEMBER(range, "Range"),
MEMBER(spread, "Spread"),
MEMBER(spreadFirst, "SpreadFirst"),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_MoritiaMk2ZoomSecondary),
MEMBER(burstNumber, "BurstNumber"),
MEMBER(burstPause, "BurstPause"),
MEMBER(fireRate, "FireRate"),
MEMBER(range, "Range"),
MEMBER(spread, "Spread"),
MEMBER(spreadFirst, "SpreadFirst"),
MEMBER(strength, "Strength"),
MEMBER(zoomFactor, "ZoomFactor"));

REFLECT(CLASS(TuningDataScript_MoritiaMk2ZoomAIDrop),
MEMBER(maxBullets, "MaxBullets"),
MEMBER(minBullets, "MinBullets"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_MoritiaMk2Zoom),
MEMBER(aiDrop, "AIDrop"),
MEMBER(ammo, "Ammo"),
MEMBER(fire1Shake, "Fire1Shake"),
MEMBER(fire2Shake, "Fire2Shake"),
MEMBER(primary, "Primary"),
MEMBER(secondary, "Secondary"));

REFLECT(CLASS(TuningDataScript_MoritiaMk4General),
MEMBER(clicksBeforeReload, "ClicksBeforeReload"));
REFLECT(CLASS(TuningDataScript_MoritiaMk4Ammo),
MEMBER(lowAmmo, "LowAmmo"));
REFLECT(CLASS(TuningDataScript_MoritiaMk4Bullets),
MEMBER(fireRate, "FireRate"),
MEMBER(maxNumber, "MaxNumber"),
MEMBER(maxReloadTime, "MaxReloadTime"),
MEMBER(minBurst, "MinBurst"),
MEMBER(minReloadTime, "MinReloadTime"),
MEMBER(range, "Range"),
MEMBER(spread, "Spread"),
MEMBER(spreadFirst, "SpreadFirst"),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_MoritiaMk4Grenades),
MEMBER(maxNumber, "MaxNumber"));
REFLECT(CLASS(TuningDataScript_MoritiaMk4Grenade),
MEMBER(blastFalloff, "BlastFalloff"),
MEMBER(blastHotspot, "BlastHotspot"),
MEMBER(blastforce, "Blastforce"),
MEMBER(drag, "Drag"),
MEMBER(launchVel, "LaunchVel"),
MEMBER(launchVelZ, "LaunchVelZ"),
MEMBER(proximityCheckLife, "ProximityCheckLife"),
MEMBER(proximityCheckRadius, "ProximityCheckRadius"),
MEMBER(proximityCheckTime, "ProximityCheckTime"));

REFLECT(CLASS(TuningDataScript_MoritiaMk4AIDrop),
MEMBER(maxGrenades, "MaxGrenades"),
MEMBER(minGrenades, "MinGrenades"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_MoritiaMk4),
MEMBER(aiDrop, "AIDrop"),
MEMBER(ammo, "Ammo"),
MEMBER(bullets, "Bullets"),
MEMBER(fireShake, "FireShake"),
MEMBER(general, "General"),
MEMBER(grenades, "Grenade"),
MEMBER(grenadeJolt, "GrenadeJolt"),
MEMBER(grenades, "Grenades"));

REFLECT(CLASS(TuningDataScript_NukeLauncherMissile),
MEMBER(climbFactor, "ClimbFactor"),
MEMBER(flightSpeed, "FlightSpeed"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_NukeLauncher),
MEMBER(missile, "Missile"));

REFLECT(CLASS(TuningDataScript_PlasmaDamageRequiredDuringFire),
MEMBER(damage, "Damage"));
REFLECT(CLASS(TuningDataScript_PlasmaBolt),
MEMBER(blastFalloff, "BlastFalloff"),
MEMBER(blastForce, "BlastForce"),
MEMBER(blastHotspot, "BlastHotspot"),
MEMBER(speed, "Speed"));
REFLECT(CLASS(TuningDataScript_PlasmaSpray),
MEMBER(sprayZScale, "SprayZScale"),
MEMBER(targetCone, "TargetCone"));
REFLECT(CLASS(TuningDataScript_PlasmaCower),
MEMBER(holdTime, "HoldTime"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Plasma),
MEMBER(bolt, "Bolt"),
MEMBER(cover, "Cower"),
MEMBER(damage, "Damage"),
MEMBER(damageRequiredDuringFire, "DamageRequiredDuringFire"),
MEMBER(damageStrengthArse, "DamageStrengthArse"),
MEMBER(damageStrengthHead, "DamageStrengthHead"),
MEMBER(footImpact, "FootImpact"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingAlert, "SpottingAlert"),
MEMBER(spottingIdle, "SpottingIdle"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(spray, "Spray"));

REFLECT(CLASS(TuningDataScript_PlayerMovement),
MEMBER(duckRate, "DuckRate"),
MEMBER(duckSpeed, "DuckSpeed"),
MEMBER(eyeHeight, "EyeHeight"),
MEMBER(heightDuck, "HeightDuck"),
MEMBER(heightStand, "HeightStand"),
MEMBER(jumpVelUp, "JumpVelUp"),
MEMBER(maxGradient, "MaxGradient"),
MEMBER(maxSlideSpeed, "MaxSlideSpeed"),
MEMBER(moveLag, "MoveLag"),
MEMBER(runSpeed, "RunSpeed"),
MEMBER(slideGradient, "SlideGradient"),
MEMBER(sphereRadius, "SphereRadius"),
MEMBER(stepHeight, "StepHeight"),
MEMBER(stepLenght, "StepLenght"),
MEMBER(turnLag, "TurnLag"),
MEMBER(turnSpeed, "TurnSpeed"));
REFLECT(CLASS(TuningDataScript_PlayerHealth),
MEMBER(regenerateRate0, "RegenerateRate0"),
MEMBER(regenerateRate1, "RegenerateRate1"));
REFLECT(CLASS(TuningDataScript_PlayerCrouch),
MEMBER(crouchAccuracy, "CrouchAccuracy"),
MEMBER(crouchBlastDamageReduction, "CrouchBlastDamageReduction"));
REFLECT(CLASS(TuningDataScript_PlayerShake),
MEMBER(shakeAmplitude, "ShakeAmplitude"),
MEMBER(shakeDuration, "ShakeDuration"));
REFLECT(CLASS(TuningDataScript_PlayerAmmoCapacity),
MEMBER(bullet, "Bullet"),
MEMBER(grenade, "Grenade"),
MEMBER(handGrenade, "HandGrenade"),
MEMBER(missile, "Missile"),
MEMBER(rocket, "Rocket"),
MEMBER(shotgun, "Shotgun"),
MEMBER(slug, "Slug"));
REFLECT(CLASS(TuningDataScript_PlayerMisc),
MEMBER(criticalHealth, "CriticalHealth"),
MEMBER(fireDamage, "FireDamage"),
MEMBER(healthPickup, "HealthPickup"),
//MEMBER(hitBoxModifier, "HitBoxModifier")
);

REFLECT(CLASS(TuningDataScript_PlayerFall),
MEMBER(damageMultiplier, "DamageMultiplier"),
MEMBER(hurtSpeed, "HurtSpeed"),
MEMBER(killPlaneHeight, "KillPlaneHeight"),
MEMBER(maxHeight, "MaxHeight"),
MEMBER(minHeight, "MinHeight"));
REFLECT(CLASS(TuningDataScript_PlayerFire),
MEMBER(checkInterval, "CheckInterval"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Player),
MEMBER(ammoCapacity, "AmmoCapacity"),
MEMBER(crouch, "Crouch"),
MEMBER(fall, "Fall"),
MEMBER(fire, "Fire"),
MEMBER(health, "Health"),
MEMBER(hitShake, "HitShake"),
MEMBER(misc, "Misc"),
MEMBER(movement, "Movement"),
MEMBER(shake, "Shake"),
MEMBER(shield, "Shield"),
MEMBER(strength, "Strength"));

REFLECT(CLASS(TuningDataScript_RagdollDrag),
MEMBER(dragFactor, "Drag Factor"));
REFLECT(CLASS(TuningDataScript_RagdollBlast),
MEMBER(blastFactor, "BlastFactor"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Ragdoll),
MEMBER(blast, "Blast"),
MEMBER(drag, "Drag"));

REFLECT(CLASS(TuningDataScript_RailgunAmmo),
MEMBER(lowAmmo, "LowAmmo"),
MEMBER(maxNumber, "MaxNumber"));
REFLECT(CLASS(TuningDataScript_RailgunBullet),
MEMBER(range, "Range"),
MEMBER(spread, "Spread"),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_RailgunShockwave),
MEMBER(falloff, "Falloff"),
MEMBER(hotSpot, "HotSpot"),
MEMBER(spacing, "Spacing"),
MEMBER(strength, "Strength"),
MEMBER(timeDelay, "TimeDelay"));
REFLECT(CLASS(TuningDataScript_RailgunZoomFactor),
MEMBER(stage1, "Stage1"),
MEMBER(stage2, "Stage2"));


REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Railgun),
MEMBER(ammo, "Ammo"),
MEMBER(bullet, "Bullet"),
MEMBER(joltUnZoomed, "JoltUnZoomed"),
MEMBER(joltZoom1, "JoltZoom1"),
MEMBER(joltZoom2, "JoltZoom2"),
MEMBER(shockwave, "Shockwave"),
MEMBER(zoomFactor, "ZoomFactor"));

REFLECT(CLASS(TuningDataScript_RocketLauncherAmmo),
MEMBER(lowAmmo, "LowAmmo"),
MEMBER(maxRockets, "MaxRockets"));
REFLECT(CLASS(TuningDataScript_RocketLauncherFiring),
MEMBER(delayMax, "DelayMax"),
MEMBER(delayMin, "DelayMin"),
MEMBER(joltAngle, "JoltAngle"),
MEMBER(joltTime, "JoltTime"),
MEMBER(speedupNum, "SpeedupNum"));
REFLECT(CLASS(TuningDataScript_RocketLauncherLockOn),
MEMBER(joltAngle, "JoltAngle"),
MEMBER(joltTime, "JoltTime"),
MEMBER(maxAngleX, "MaxAngleX"),
MEMBER(maxAngleY, "MaxAngleY"),
MEMBER(maxNumber, "MaxNumber"),
MEMBER(maxRange, "MaxRange"),
MEMBER(showAngleX, "ShowAngleX"),
MEMBER(showAngleY, "ShowAngleY"));
REFLECT(CLASS(TuningDataScript_RocketLauncherRocket),
MEMBER(lockedLifeTime, "LOCKED_LifeTime"),
MEMBER(lockedSpeed, "LOCKED_Speed"),
MEMBER(noLockLifeTime, "NOLOCK_LifeTime"),
MEMBER(noLockSpeed, "NOLOCK_Speed"),
MEMBER(turnRate, "TurnRate"),
MEMBER(weaveAngle, "WeaveAngle"),
MEMBER(weaveFrequency, "WeaveFrequency"));
REFLECT(CLASS(TuningDataScript_RocketLauncherBlast),
MEMBER(falloffRadius, "FalloffRadius"),
MEMBER(hotspotRadius, "HotspotRadius"),
MEMBER(strengthBlast, "StrengthBlast"),
MEMBER(strengthHeat, "StrengthHeat"));
REFLECT(CLASS(TuningDataScript_RocketLauncherAIDrop),
MEMBER(maxRockets, "MaxRockets"),
MEMBER(minRockets, "MinRockets"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_RocketLauncher),
MEMBER(aiDrop, "AIDrop"),
MEMBER(ammo, "Ammo"),
MEMBER(blast, "Blast"),
MEMBER(firing, "Firing"),
MEMBER(lockOn, "LockOn"),
MEMBER(rocket, "Rocket"));

REFLECT(CLASS(TuningDataScript_ShotgunAmmo),
MEMBER(lowAmmo, "LowAmmo"),
MEMBER(maxShells, "MaxShells"));
REFLECT(CLASS(TuningDataScript_ShotgunPrimary),
MEMBER(blastAngle, "BlastAngle"),
MEMBER(blastRange, "BlastRange"),
MEMBER(blastStrength, "BlastStrength"),
MEMBER(numberRayTests, "NumberRayTests"),
MEMBER(numberShells, "NumberShells"),
MEMBER(rayTestRange, "RayTestRange"),
MEMBER(rayTestSpread, "RayTestSpread"),
MEMBER(rayTestStrength, "RayTestStrength"));
REFLECT(CLASS(TuningDataScript_ShotgunPrimaryJolt),
MEMBER(angle, "Angle"),
MEMBER(time, "Time"));
REFLECT(CLASS(TuningDataScript_ShotgunSecondary),
MEMBER(blastAngle, "BlastAngle"),
MEMBER(blastRange, "BlastRange"),
MEMBER(blastStrength, "BlastStrength"),
MEMBER(numberRayTests, "NumberRayTests"),
MEMBER(numberShells, "NumberShells"),
MEMBER(rayTestRange, "RayTestRange"),
MEMBER(rayTestSpread, "RayTestSpread"),
MEMBER(rayTestStrength, "RayTestStrength"));
REFLECT(CLASS(TuningDataScript_ShotgunSecondaryJolt),
MEMBER(angle, "Angle"),
MEMBER(time, "Time"));
REFLECT(CLASS(TuningDataScript_ShotgunAIDrop),
MEMBER(maxShells, "MaxShells"),
MEMBER(minShells, "MinShells"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Shotgun),
MEMBER(aiDrop, "AIDrop"),
MEMBER(ammo, "Ammo"),
MEMBER(primary, "Primary"),
MEMBER(primaryJolt, "PrimaryJolt"),
MEMBER(secondary, "Secondary"),
MEMBER(secondaryJolt, "SecondaryJolt"));

REFLECT(CLASS(TuningDataScript_StaticGunDoubleGeneral),
MEMBER(bulletStrength, "BulletStrength"),
MEMBER(fireRate, "FireRate"),
MEMBER(zoomFactor, "ZoomFactor"),
MEMBER(zoomRate, "ZoomRate"));
REFLECT(CLASS(TuningDataScript_StaticGunDoubleRotation),
MEMBER(gunLag, "GunLag"),
MEMBER(rateHeading, "RateHeading"),
MEMBER(ratePitch, "RatePitch"));
REFLECT(CLASS(TuningDataScript_StaticGunDoubleTemerature),
MEMBER(coolingRate, "CoolingRate"),
MEMBER(firingDelta, "FiringDelta"),
MEMBER(overheatTime, "OverheatTime"));

REFLECT(CLASS(TuningDataScript_StaticGunDoubleAIParameters),
MEMBER(rateHeading, "RateHeading"),
MEMBER(ratePitch, "RatePitch"),
MEMBER(reTargetTime, "ReTargetTime"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_StaticGunDouble),
MEMBER(aiParameters, "AIParameters"),
MEMBER(fireShake, "FireShake"),
MEMBER(general, "General"),
MEMBER(rotation, "Rotation"),
MEMBER(temerature, "Temerature"));

REFLECT(CLASS(TuningDataScript_TankerBullet),
MEMBER(head, "Head"),
MEMBER(rest, "Rest"));
REFLECT(CLASS(TuningDataScript_TankerBlast),
MEMBER(head, "Head"),
MEMBER(rest, "Rest"));
REFLECT(CLASS(TuningDataScript_TankerSpotting),
MEMBER(chance, "Chance"),
MEMBER(cone, "Cone"),
MEMBER(rangeMax, "RangeMax"),
MEMBER(rangeMin, "RangeMin"),
MEMBER(torchSightModifier, "TorchSightModifier"));
REFLECT(CLASS(TuningDataScript_TankerStomp),
MEMBER(strength, "Strength"),
MEMBER(falloff, "Falloff"),
MEMBER(hotspot, "Hotspot"));
REFLECT(CLASS(TuningDataScript_TankerFire),
MEMBER(damageDelay, "DamageDelay"),
MEMBER(falloff, "Falloff"),
MEMBER(hotspot, "Hotspot"),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_TankerHealth),
MEMBER(valRetract, "ValRetract"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Tanker),
MEMBER(blast, "Blast"),
MEMBER(bullet, "Bullet"),
MEMBER(damage, "Damage"),
MEMBER(fire, "Fire"),
//MEMBER(footImpact, "FootImpact"),
MEMBER(health, "Health"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(stomp, "Stomp"));

REFLECT(CLASS(TuningDataScript_TankerBabyAttack),
MEMBER(blastFalloff, "BlastFalloff"),
MEMBER(blastForce, "BlastForce"),
MEMBER(blastHotSpot, "BlastHotSpot"),
MEMBER(boltSpeed, "BoltSpeed"),
MEMBER(fireBurstRange, "FireBurstRange"),
MEMBER(forceBarge, "ForceBarge"));
REFLECT(CLASS(TuningDataScript_TankerBabyDamageStrength),
MEMBER(threshold));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_TankerBaby),
MEMBER(accuracy, "Accuracy"),
MEMBER(attack, "Attack"),
MEMBER(damage, "Damage"),
MEMBER(damageStrengthHead, "DamageStrength"),
MEMBER(damageStrengthHead, "DamageStrengthHead"),
MEMBER(footImpact, "FootImpact"),
MEMBER(navigator, "Navigator"),
MEMBER(navigatorSpeedData0, "Navigator_SpeedData0"),
MEMBER(navigatorSpeedData1, "Navigator_SpeedData1"),
MEMBER(networkStrategy, "NetworkStrategy"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingAlert, "SpottingAlert"),
MEMBER(spottingIdle, "SpottingIdle"),
MEMBER(spottingTargetBias, "SpottingTargetBias"));

REFLECT(CLASS(TuningDataScript_TigerDefence),
MEMBER(percentageChance, "PercentageChance"));
REFLECT(CLASS(TuningDataScript_TigerAttack),
MEMBER(predictionSpeed, "PredictionSpeed"),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_TigerStrength),
MEMBER(blast, "Blast"),
MEMBER(bulletHead, "BulletHead"),
MEMBER(bulletLegs, "BulletLegs"),
MEMBER(bulletNerve, "BulletNerve"),
MEMBER(cosmeticShieldsPierce, "CosmeticShieldsPierce"),
MEMBER(heat, "Heat"),
MEMBER(sonic, "Sonic"));
REFLECT(CLASS(TuningDataScript_TigerHealth),
MEMBER(cosmeticShields, "CosmeticShields"));
REFLECT(CLASS(TuningDataScript_TigerStrategy),
MEMBER(evasionChance, "EvasionChance"),
MEMBER(evasionDist, "EvasionDist"));
REFLECT(CLASS(TuningDataScript_TigerDeath),
MEMBER(bodyMovementFactor, "BodyMovementFactor"),
MEMBER(deltaHealthForGib, "DeltaHealthForGib"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Tiger),
MEMBER(alert, "Alert"),
MEMBER(attack, "Attack"),
MEMBER(damage, "Damage"),
MEMBER(death, "Death"),
MEMBER(defence, "Defence"),
MEMBER(fire, "Fire"),
MEMBER(health, "Health"),
MEMBER(idle, "Idle"),
MEMBER(navigator, "Navigator"),
MEMBER(navigatorSpeedData0, "Navigator_SpeedData0"),
MEMBER(navigatorSpeedData1, "Navigator_SpeedData1"),
MEMBER(navigatorSpeedData2, "Navigator_SpeedData2"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(strategy, "Strategy"),
MEMBER(strength, "Strength"));

REFLECT(CLASS(TuningDataScript_TigerShardDefence),
MEMBER(percentageChance, "PercentageChance"));
REFLECT(CLASS(TuningDataScript_TigerShardAttack),
MEMBER(predictionSpeed, "PredictionSpeed"),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_TigerShardStrength),
MEMBER(blast, "Blast"),
MEMBER(bulletHead, "BulletHead"),
MEMBER(bulletLegs, "BulletLegs"),
MEMBER(bulletNerve, "BulletNerve"),
MEMBER(heat, "Heat"),
MEMBER(sonic, "Sonic"));
REFLECT(CLASS(TuningDataScript_TigerShardWeapon),
MEMBER(coneAngle, "ConeAngle"),
MEMBER(coneNumShards, "ConeNumShards"),
MEMBER(coneSpreadX, "ConeSpreadX"),
MEMBER(coneSpreadY, "ConeSpreadY"),
MEMBER(coneSpreadZ, "ConeSpreadZ"),
MEMBER(damage, "Damage"),
MEMBER(fireAngle, "FireAngle"),
MEMBER(innerRange, "InnerRange"),
MEMBER(meleeRange, "MeleeRange"),
MEMBER(outerRange, "OuterRange"));
REFLECT(CLASS(TuningDataScript_TigerShardStrategy),
MEMBER(berserkHealth, "BerserkHealth"),
MEMBER(evasionChance, "EvasionChance"),
MEMBER(evasionDistance, "EvasionDistance"),
MEMBER(idealDist, "IdealDist"),
MEMBER(meleeAttackDist, "MeleeAttackDist"),
MEMBER(shortFireChance, "ShortFireChance"),
MEMBER(shortFireDist, "ShortFireDist"));
REFLECT(CLASS(TuningDataScript_TigerShardBolt),
MEMBER(life, "Life"),
MEMBER(speed, "Speed"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_TigerShard),
MEMBER(accuracy, "Accuracy"),
MEMBER(alert, "Alert"),
MEMBER(attack, "Attack"),
MEMBER(bolt, "Bolt"),
MEMBER(damage, "Damage"),
MEMBER(defence, "Defence"),
MEMBER(fire, "Fire"),
MEMBER(idle, "Idle"),
MEMBER(navigator, "Navigator"),
MEMBER(navigatorSpeedData0, "Navigator_SpeedData0"),
MEMBER(navigatorSpeedData1, "Navigator_SpeedData1"),
MEMBER(navigatorSpeedData2, "Navigator_SpeedData2"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(strategy, "Strategy"),
MEMBER(strength, "Strength"),
MEMBER(weapon, "Weapon"));

REFLECT(CLASS(TuningDataScript_TigerSpitDefence),
MEMBER(percentageChance, "PercentageChance"));
REFLECT(CLASS(TuningDataScript_TigerSpitAttack),
MEMBER(predictionSpeed, "PredictionSpeed"),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_TigerSpitStrength),
MEMBER(blast, "Blast"),
MEMBER(bulletHead, "BulletHead"),
MEMBER(bulletLegs, "BulletLegs"),
MEMBER(bulletNerve, "BulletNerve"),
MEMBER(heat, "Heat"),
MEMBER(sonic, "Sonic"));
REFLECT(CLASS(TuningDataScript_TigerSpitWeapon),
MEMBER(innerRange, "InnerRange"),
MEMBER(meleeRange, "MeleeRange"),
MEMBER(outerRange, "OuterRange"),
MEMBER(spitAngle, "SpitAngle"));
REFLECT(CLASS(TuningDataScript_TigerSpitStrategy),
MEMBER(berserkHealth, "BerserkHealth"),
MEMBER(evasionChance, "EvasionChance"),
MEMBER(evasionDistance, "EvasionDistance"),
MEMBER(idealDist, "IdealDist"),
MEMBER(meleeAttackDist, "MeleeAttackDist"),
MEMBER(shotSpitChance, "ShotSpitChance"),
MEMBER(shotSpitDist, "ShotSpitDist"));
REFLECT(CLASS(TuningDataScript_TigerSpitAccuracy),
MEMBER(maximumVariance, "MaximumVariance"),
MEMBER(minimumVariance, "MinimumVariance"),
MEMBER(number_Of_Intervals, "Number_Of_Intervals"),
MEMBER(spitPredictionTime, "SpitPredictionTime"));
REFLECT(CLASS(TuningDataScript_TigerSpitBolt),
MEMBER(blastFalloff, "BlastFalloff"),
MEMBER(blastForce, "BlastForce"),
MEMBER(blastHotspot, "BlastHotspot"),
MEMBER(speed, "Speed"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_TigerSpit),
MEMBER(accuracy, "Accuracy"),
MEMBER(alert, "Alert"),
MEMBER(attack, "Attack"),
MEMBER(bolt, "Bolt"),
MEMBER(damage, "Damage"),
MEMBER(defence, "Defence"),
MEMBER(fire, "Fire"),
MEMBER(idle, "Idle"),
MEMBER(navigator, "Navigator"),
MEMBER(navigatorSpeedData0, "Navigator_SpeedData0"),
MEMBER(navigatorSpeedData1, "Navigator_SpeedData1"),
MEMBER(navigatorSpeedData2, "Navigator_SpeedData2"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(strategy, "Strategy"),
MEMBER(strength, "Strength"),
MEMBER(weapon, "Weapon"));

REFLECT(CLASS(TuningDataScript_WarriorDefence),
MEMBER(percentageChance, "PercentageChance"));
REFLECT(CLASS(TuningDataScript_WarriorRagdoll),
MEMBER(density, "Density"));
REFLECT(CLASS(TuningDataScript_WarriorAttack),
MEMBER(predictionSpeed, "PredictionSpeed"),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_WarriorStrength),
MEMBER(blast, "Blast"),
MEMBER(bulletHeadHard, "BulletHeadHard"),
MEMBER(bulletHeadSoft, "BulletHeadSoft"),
MEMBER(bulletLegsHard, "BulletLegsHard"),
MEMBER(bulletLegsSoft, "BulletLegsSoft"),
MEMBER(bulletNerveHard, "BulletNerveHard"),
MEMBER(bulletNerveSoft, "BulletNerveSoft"),
MEMBER(corrosive, "Corrosive"),
MEMBER(cosmeticShields, "CosmeticShields"),
MEMBER(electricity, "Electricity"),
MEMBER(heat, "Heat"),
MEMBER(psiOps, "PsiOps"),
MEMBER(punch, "Punch"),
MEMBER(slash, "Slash"),
MEMBER(sonic, "Sonic"));
REFLECT(CLASS(TuningDataScript_WarriorHealth),
MEMBER(cosmeticShields, "CosmeticShields"));
REFLECT(CLASS(TuningDataScript_WarriorDeath),
MEMBER(bodyMovementFactor, "BodyMovementFactor"),
MEMBER(deltaHealthForGib, "DeltaHealthForGib"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Warrior),
MEMBER(alert, "Alert"),
MEMBER(attack, "Attack"),
MEMBER(damage, "Damage"),
MEMBER(death, "Death"),
MEMBER(defence, "Defence"),
MEMBER(fire, "Fire"),
//MEMBER(footImpact, "FootImpact"),
MEMBER(health, "Health"),
MEMBER(idle, "Idle"),
MEMBER(navigator, "Navigator"),
MEMBER(navigatorSpeedData0, "Navigator_SpeedData0"),
MEMBER(navigatorSpeedData1, "Navigator_SpeedData1"),
MEMBER(navigatorSpeedData2, "Navigator_SpeedData2"),
MEMBER(ragdoll, "Ragdoll"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(strength, "Strength"));

REFLECT(CLASS(TuningDataScript_WarriorRoyalDefence),
MEMBER(percentageChance, "PercentageChance"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalRagdoll),
MEMBER(density, "Density"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalAttack),
MEMBER(predictionSpeed, "PredictionSpeed"),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalLegPunches),
MEMBER(colSphereRadius, "ColSphereRadius"),
MEMBER(impactPunchForce, "ImpactPunchForce"),
MEMBER(minLegVelocity, "MinLegVelocity"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalFootImpact),
MEMBER(punchMultiplier, "PunchMultiplier"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalStrength),
MEMBER(blast, "Blast"),
MEMBER(corrosive, "Corrosive"),
MEMBER(electricity, "Electricity"),
MEMBER(eyePierceHard, "EyePierceHard"),
MEMBER(eyePierceSoft, "EyePierceSoft"),
MEMBER(eyeShieldPierceHard, "EyeShieldPierceHard"),
MEMBER(eyeShieldPierceSoft, "EyeShieldPierceSoft"),
MEMBER(heat, "Heat"),
MEMBER(psiOps, "PsiOps"),
MEMBER(punch, "Punch"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalHealth),
MEMBER(cosmeticShields, "CosmeticShields"),
MEMBER(eyeLeft, "EyeLeft"),
MEMBER(eyeRight, "EyeRight"),
MEMBER(eyeShieldLeft, "EyeSheildLeft"),
MEMBER(eyeShieldRight, "EyeSheildRight"),
MEMBER(mandibleShields, "MandibleShields"));

REFLECT(CLASS(TuningDataScript_WarriorRoyalDamageThreshold),
MEMBER(threshold, "Threshold"));

REFLECT(CLASS(TuningDataScript_WarriorRoyalStrategy),
MEMBER(facingTargetAngle, "FacingTargetAngle"),
MEMBER(outOfDistanceAttackRoarChance, "OutOfDistanceAttackRoarChance"),
MEMBER(outOfDistanceAttackRoarRange, "OutOfDistanceAttackRoarRange"),
MEMBER(randomRoarChance, "RandomRoarChance"),
MEMBER(randomRoarMinDistance, "RandomRoarMinDistance"));

REFLECT(CLASS(TuningDataScript_WarriorRoyalMisc),
MEMBER(eyeRadius, "EyeRadius"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_WarriorRoyal),
MEMBER(attack, "Attack"),
MEMBER(damage, "Damage"),
MEMBER(damageThreshold, "DamageThreshold"),
MEMBER(defence, "Defence"),
MEMBER(fire, "Fire"),
MEMBER(footImpact, "FootImpact"),
MEMBER(health, "Health"),
MEMBER(legPunches, "LegPunches"),
MEMBER(misc, "Misc"),
MEMBER(navigator, "Navigator"),
MEMBER(navigatorSpeedData0, "Navigator_SpeedData0"),
MEMBER(navigatorSpeedData1, "Navigator_SpeedData1"),
MEMBER(navigatorSpeedData2, "Navigator_SpeedData2"),
MEMBER(ragdoll, "Ragdoll"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingAlert, "SpottingAlert"),
MEMBER(spottingIdle, "SpottingIdle"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(strategy, "Strategy"),
MEMBER(strength, "Strength"));

REFLECT(CLASS(TuningDataScript_WarriorRoyalXDefence),
MEMBER(percentageChance, "PercentageChance"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalXRagdoll),
MEMBER(density, "Density"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalXAttack),
MEMBER(predictionSpeed, "PredictionSpeed"),
MEMBER(strength, "Strength"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalXLegPunches),
MEMBER(colSphereRadius, "ColSphereRadius"),
MEMBER(impactPunchForce, "ImpactPunchForce"),
MEMBER(minLegVelocity, "MinLegVelocity"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalXFootImpact),
MEMBER(punchMultiplier, "PunchMultiplier"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalXStrength),
MEMBER(annoyedRearUpHard, "AnnoyedRearUpHard"),
MEMBER(annoyedRearUpSoft, "AnnoyedRearUpSoft"),
MEMBER(blast, "Blast"),
MEMBER(corrosive, "Corrosive"),
MEMBER(electricity, "Electricity"),
MEMBER(eyePierceSoft, "EyePierceSoft"),
MEMBER(eyeShieldPierceHard, "EyeShieldPierceHard"),
MEMBER(eyeShieldPierceSoft, "EyeShieldPierceSoft"),
MEMBER(eyepierceHard, "EyepierceHard"),
MEMBER(heat, "Heat"),
MEMBER(psiOps, "PsiOps"),
MEMBER(punch, "Punch"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalXDamageThreshold),
MEMBER(threshold, "Threshold"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalXHealth),
MEMBER(cosmeticShields, "CosmeticShields"),
MEMBER(eyeLeft, "EyeLeft"),
MEMBER(eyeRight, "EyeRight"),
MEMBER(eyeShieldLeft, "EyeSheildLeft"),
MEMBER(eyeShieldRight, "EyeSheildRight"),
MEMBER(mandibleShields, "MandibleShields"),
MEMBER(rearUpDamageTrigger, "RearUpDamageTrigger"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalXStrategy),
MEMBER(blastDelayTime, "BlastDelayTime"),
MEMBER(jetFireChance, "JetFireChance"),
MEMBER(sonicRadialRoarChance, "SonicRadialRoarChance"),
MEMBER(sonicRadialRoarDistance, "SonicRadialRoarDistance"),
MEMBER(sonicRoarChance, "SonicRoarChance"),
MEMBER(sonicRoarDistance, "SonicRoarDistance"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalXDamage),
MEMBER(nonPlayerFactor, "NonPlayerFactor"),
MEMBER(sonicBlastIntensity, "SonicBlastIntensity"));
REFLECT(CLASS(TuningDataScript_WarriorRoyalXMisc),
MEMBER(eyeRadius, "EyeRadius"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_WarriorRoyalX),
MEMBER(attack, "Attack"),
MEMBER(damage, "Damage"),
MEMBER(damageThreshold, "DamageThreshold"),
MEMBER(Defence, "Defence"),
MEMBER(fire, "Fire"),
MEMBER(footImpact, "FootImpact"),
MEMBER(health, "Health"),
MEMBER(legPunches, "LegPunches"),
MEMBER(misc, "Misc"),
MEMBER(navigator, "Navigator"),
MEMBER(navigatorSpeedData0, "Navigator_SpeedData0"),
MEMBER(navigatorSpeedData1, "Navigator_SpeedData1"),
MEMBER(navigatorSpeedData2, "Navigator_SpeedData2"),
MEMBER(Ragdoll, "Ragdoll"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingAlert, "SpottingAlert"),
MEMBER(spottingIdle, "SpottingIdle"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(strategy, "Strategy"),
MEMBER(strength, "Strength"));

REFLECT(CLASS(TuningDataScript_RhinoDamageStrengthThreshold),
MEMBER(threshold, "Threshold"));
REFLECT(CLASS(TuningDataScript_RhinoAttack),
MEMBER(attackStill, "AttackStill"),
MEMBER(chargeForceFront, "ChargeForceFront"),
MEMBER(chargeForceTop, "ChargeForceTop"));
REFLECT(CLASS(TuningDataScript_RhinoStrategy),
MEMBER(chargeHeadDipDistance, "ChargeHeadDipDistance"),
MEMBER(chargePastDistance, "ChargePastDistance"),
MEMBER(slideDistance, "SlideDistance"),
MEMBER(slideHoldTime, "SlideHoldTime"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Rhino),
MEMBER(attack, "Attack"),
MEMBER(damage, "Damage"),
MEMBER(damageStrengthHead, "DamageStrengthHead"),
MEMBER(damageStrengthRear, "DamageStrengthRear"),
MEMBER(damageStrengthThreshold, "DamageStrengthThreshold"),
MEMBER(footImpact, "FootImpact"),
MEMBER(navigator, "Navigator"),
MEMBER(navigatorSpeedData0, "Navigator_SpeedData0"),
MEMBER(navigatorSpeedData1, "Navigator_SpeedData1"),
MEMBER(navigatorSpeedData2, "Navigator_SpeedData2"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingAlert, "SpottingAlert"),
MEMBER(spottingIdle, "SpottingIdle"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(strategy, "Strategy"));

REFLECT(CLASS(TuningDataScript_SentinelAttack),
MEMBER(flashCutoffMax, "FlashCutoffMax"),
MEMBER(flashFalloffMin, "FlashFalloffMin"),
MEMBER(flashIntensity, "FlashIntensity"),
MEMBER(zapDistance, "ZapDistance"));

REFLECT(BASEDCLASS(TuningDataScript, TuningDataScript_Sentinel),
MEMBER(attack, "Attack"),
MEMBER(damage, "Damage"),
MEMBER(fire, "Fire"),
MEMBER(spotting, "Spotting"),
MEMBER(spottingAlert, "SpottingAlert"),
MEMBER(spottingIdle, "SpottingIdle"),
MEMBER(spottingTargetBias, "SpottingTargetBias"),
MEMBER(strength, "Strength"));
