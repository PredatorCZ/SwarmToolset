#include "ai_bug_warrior_base.hpp"
#include "abstract_manager.hpp"
#include "ai_animation.hpp"
#include "ai_door.hpp"
#include "ai_group.hpp"
#include "ai_manager.hpp"
#include "ai_player.hpp"
#include "ai_waypoint.hpp"
#include "app_game.hpp"
#include "audio_playable_3d_extended.hpp"
#include "collider.hpp"
#include "dx_types.hpp"
#include "multiplayer_game.hpp"
#include "multiplayer_net_object.hpp"
#include "particle_system_warrior_bullet_hit.hpp"
#include "ragdoll.hpp"
#include "ragdoll_registry.hpp"
#include "ren_model.hpp"
#include "render_manager.hpp"
#include "render_state.hpp"
#include "resource_material.hpp"
#include "resource_object_animation.hpp"
#include "resource_object_animation_set.hpp"
#include "resource_object_model.hpp"
#include "sound_manager.hpp"
#include "surface_effects.hpp"
#include "tds.hpp"
#include "unk_registry.hpp"
#include "walker.hpp"
#include "world_object_collision.hpp"
#include <algorithm>
#include <random>
#include <tnlRandom.h>

enum ANIMSET {
  ANIMSET_StaticIdle,
  ANIMSET_StaticAlert,
  ANIMSET_StaticAttack,
  ANIMSET_StaticIgnore,
  ANIMSET_StaticTurnRight90,
  ANIMSET_StaticTurnLeft90,
  ANIMSET_RunningIdle,
  ANIMSET_RunningAlert,
  ANIMSET_RunningAttack,
  ANIMSET_RunningIgnore,
  ANIMSET_FightStepForward,
  ANIMSET_FightStepBackward,
  ANIMSET_FightStepRight,
  ANIMSET_FightStepLeft,
  ANIMSET_FightTurnRight,
  ANIMSET_FightTurnLeft,
  ANIMSET_FightStrike34,
  ANIMSET_FightStrike45,
  ANIMSET_FightStrike56,
  ANIMSET_FightStrike_Wall,
  ANIMSET_FightStrike_Wall_2,
  ANIMSET_DyingNoKick,
  ANIMSET_DyingKick,
  ANIMSET_SpecialJumpDown,
  ANIMSET_SpecialJumpUp,
  ANIMSET_SpecialJump,
  ANIMSET_SpecialOutOfGround,
  ANIMSET_BeenHit,
};

void AIBugWarriorBase::Process() {
  if (GetClientNetObject()) {
    if (AppGame::Get()->SessionTime() > aiTime[2] &&
        movementMode == AIMODE_DYING) {
      _4E7180();
    }

    AIFourStateMatrix::Process();
  } else {
    func_8();
  }
}

void AIBugWarriorBase::_4E7180() {
  // v3 = (_DWORD *)sub_41D5E0();
  // sub_668060(v3, (AIEntity *)this, GetAttacker());
  RemoveFromWorldContext_0();
  if (group) {
    group->RemoveEntity(this);
  }

  SetGroup(0, 0, 0);

  if (electrify) {
    Matrix mtx = *Get();
    auto burnModelResource = GetBurntModelResource();

    if (burnModelResource != resourceRef) {
      resourceRef->DecreaseReference();
      resourceRef.object = burnModelResource.object;
      resourceRef.Assign(burnModelResource.object, 0);
      resourceRef->SafeLoad();
    }

    renderState->SetModel(resourceRef->model);
    renderState->SetRender(true);
    animationBlendSet.Process(renderState);
    Set(mtx);
  }
  if (IsAIType(AITYPEID::BUGROYAL) || IsAIType(AITYPEID::BUGROYALX)) {
    const double sessionTime = AppGame::Get()->SessionTime();
    _49A6D0(sessionTime + 2.0, sessionTime + 6.0, 0.0, 1.0, 0.0, 1.0);
  } else {
    collision->_91DC20(2);
  }

  if (field_86C) {
    // UnkStruct0_destroy(this->data.field_86C);
    delete field_86C;
  }

  if (field_870) {
    // UnkStruct0_destroy(this->data.field_870);
    delete field_870;
  }

  field_86C = 0;
  field_870 = 0;

  if (surfaceEffects) {
    delete surfaceEffects;
    surfaceEffects = nullptr;
  }
}

float AIBugWarriorBase::GetAttackPredictionSpeed() {
  return TDSSettings::Get()->GetValue(Warrior_Attack_PredictionSpeed);
}

float AIBugWarriorBase::GetAttackStrength() {
  return TDSSettings::Get()->GetValue(Warrior_Attack_Strength);
}

float AIBugWarriorBase::GetIdleRangeMin() {
  return TDSSettings::Get()->GetValue(Warrior_Idle_RangeMin);
}

float AIBugWarriorBase::GetIdleRangeMax() {
  return TDSSettings::Get()->GetValue(Warrior_Idle_RangeMax);
}

float AIBugWarriorBase::GetIdleChance() {
  return TDSSettings::Get()->GetValue(Warrior_Idle_Chance);
}

float AIBugWarriorBase::GetIdleCone() {
  return TDSSettings::Get()->GetValue(Warrior_Idle_Cone);
}

float AIBugWarriorBase::GetAlertRangeMin() {
  return TDSSettings::Get()->GetValue(Warrior_Alert_RangeMin);
}

float AIBugWarriorBase::GetAlertRangeMax() {
  return TDSSettings::Get()->GetValue(Warrior_Alert_RangeMax);
}

float AIBugWarriorBase::GetAlertChance() {
  return TDSSettings::Get()->GetValue(Warrior_Alert_Chance);
}

float AIBugWarriorBase::GetAlertCone() {
  return TDSSettings::Get()->GetValue(Warrior_Alert_Cone);
}

ResourcePtr<ResourceObjectModel> AIBugWarriorBase::GetBurntModelResource() {
  return {};
}

bool AIBugWarriorBase::IsAIType(AITYPEID typeId) {
  switch (typeId) {
  case AITYPEID::BUGWARRIORBASE:
  case AITYPEID::BUGWALKER:
  case AITYPEID::BUG:
  case AITYPEID::ENTITY:
    return true;
  default:
    return false;
  }
}

void AIBugWarriorBase::field_48(WorldObject &obj) { _462CC0(obj, 1.0); }

void AIBugWarriorBase::CloneWarrior(AIBugWarriorBase *other) {
  Clone(other);
  other->specialMode = specialMode;
  other->waypointsNarrow = waypointsNarrow;
  other->movingZigZag = movingZigZag;
  other->allowFastRun = allowFastRun;
  other->bbox = bbox;
}

void AIBugWarriorBase::field_A0(AIAnimation *a2, int a3) {
  if (movementMode < AIMODE_DYING) {
    anim = a2;
    specialMode = AISM_PLAYANIM;
    _4ED2E0();
  }
}

float AIBugWarriorBase::GetSpottingBias(AIEntity *entity) {
  if (entity->IsAIType(AITYPEID::PLAYER)) {
    return TDSSettings::Get()->GetValue(Warrior_SpottingTargetBias_Player);
  } else if (entity->IsAIType(AITYPEID::HUMAN)) {
    return TDSSettings::Get()->GetValue(Warrior_SpottingTargetBias_AIHuman);
  } else if (entity->IsAIType(AITYPEID::BOMBER) ||
             entity->IsAIType(AITYPEID::DROPSHIP)) {
    return TDSSettings::Get()->GetValue(Warrior_SpottingTargetBias_Vehicle);
  } else {
    return 0.0;
  }
}

void AIBugWarriorBase::SetMovingZigZag(bool moveZigZag) {
  movingZigZag = moveZigZag;
  walker->SetMovingZigZag(moveZigZag);
}

void AIBugWarriorBase::_4ED2E0() {
  ApplyNextVulnerability();

  if (AppGame::Get()->SessionTime() > aiTime[2]) {
    if (ResourceMaterial *material = walker->Material()) {
      auto unk0 = material->field_468;

      if (unk0 > 0) {
        IncomingDamage dmg{};
        dmg.bulletHard = (aiTime[3] - aiTime[1]) * unk0;
        ApplyDamage(dmg);
      }
    }

    aiAnimTime[0] = aiAnimTime[2];
    aiAnimTime[1] = aiAnimTime[3];
    CopyUpperHalfToLower();
  }

  if (overrideAnimSet) {
    if (specialMode == AISM_PLAYANIM)
      SetStatePlayAnim();
    else
      _4E3670();
  } else {
    if (!specialMode && movementMode < AIMODE_DYING && !stickToWaypoints) {
      _4DFDF0();
      if (group->alertState > alertState) {
        SetAlertState(group->alertState);
      }

      if (group->mode > movementMode) {
        SetMovementMode(group->mode);
      }
      hitVec = {};
    }
  }

  if (!IsInActiveState()) {
    switch (specialMode) {
    case AISM_NONE:
      switch (movementMode) {
      case AIMODE_STILL:
        SetStateIdleByAlertState();
        break;
      case AIMODE_MOVING:
        SetStateMove();
        break;
      case AIMODE_FIGHTING:
        _4EAB20();
        break;
      case AIMODE_DYING:
        _4E9C60();
        break;
      case AIMODE_RAGDOLL:
        SetStateRagdoll();
        break;
      default:
        break;
      }
      break;
    case AISM_PLAYANIM:
      SetStatePlayAnim();
      break;
    case AISM_OUTOFGROUND:
      SetStateOutOfGround();
      break;
    case AISM_JUMP:
      SetStateJump();
      break;
    case AISM_BEENHIT:
      SetStateFlinch();
      break;
    default:
      break;
    }
  }

  if (field_86C) {
    const float navCapRadius = walker->GetNavigatorCapsuleRadius();
    field_86C->_470960(navCapRadius);
    field_870->_470960(navCapRadius);
    Vector &navCapOffset = walker->GetNavigatorCapsuleOffset();
    field_86C->_4709C0(navCapOffset, aiMatrix[0], aiTime[0], aiMatrix[1],
                       aiTime[1]);
    field_870->_4709C0(navCapOffset, aiMatrix[1], aiTime[1], aiMatrix[2],
                       aiTime[2]);
  }

  if (movementMode < AIMODE_DYING) {
    _462780();
    MultiplayerNetObject *netObj = GetServerNetObject();
    if (netObj) {
      netObj->setMaskBits(32);
    }
  }
}

void AIBugWarriorBase::SetStatePlayAnim() {
  const double sessionTime = AppGame::Get()->SessionTime();

  auto v9 = anim->duration * 0.25;
  if (v9 > 0.25) {
    v9 = 0.25;
  }
  auto v12 = 0.0;
  if (sessionTime > aiTime[0]) {
    v12 = v9;
  }

  const double time = sessionTime + v12;
  Matrix a4 = *Get();
  Matrix a2 = GetMatrixAtTime(time);
  Matrix v27 = (a4 + a2) * 0.5;
  // Matrix_694D60(v27);

  aiAnimTime[0] = 0.0;
  auto v5 = 1.0 / anim->duration;
  aiAnimTime[1] = v12 * (1.0 / anim->duration);
  aiAnimTime[2] = 1.0 - v5 * v9;
  aiAnimTime[3] = 1.0;

  SetMatrix(0, sessionTime, a4, true);
  SetMatrix(1, sessionTime + v12, v27, false);
  SetMatrix(2, anim->duration + sessionTime - v9, v27, false);
  SetMatrix(3, anim->duration + sessionTime, v27, false);

  if (sessionTime > aiTime[0]) {
    animationBlendSet._452A20(anim, aiTime[0], aiTime[1], aiAnimTime[0],
                              aiAnimTime[1], 1, 1);
  } else {
    animationBlendSet._452640();
  }

  animationBlendSet.PushBlend(anim, aiTime[1], aiTime[3], aiAnimTime[1],
                              aiAnimTime[3], 1.0, 1.0);

  surfaceEffects->SetDustRate(0);
  field_30();
}

void AIBugWarriorBase::_4E3670() {
  anim = static_cast<AIAnimation *>(overrideAnimSet->PickRandomAnimation());
  float v19 = TNL::Random::readF();
  v19 = v19 * 2 - 1;
  float v11 = field_F4() * v19 + 1;

  const Matrix &a4 = aiMatrix[1];

  float v12 = v11 * anim->duration;
  float v13 = aiTime[1] - aiTime[0];
  float v14 = 0.25 * v12;
  float a3 = (v13 + v14) * 0.5 + aiTime[0];
  float v25 = v12 * 0.5 + a3;

  SetMatrix(1, a3, a4, false);
  SetMatrix(2, v25, a4, false);
  SetMatrix(3, v14 + v25, a4, false);
  aiAnimTime[0] = 0.0;
  aiAnimTime[1] = 0.25;
  aiAnimTime[2] = 0.75;
  aiAnimTime[3] = 1.0;
  animationBlendSet._452640();
  animationBlendSet.PushBlend(anim, aiTime[0], aiTime[1], aiAnimTime[0],
                              aiAnimTime[1], 1.0, 0.0);
  animationBlendSet.PushBlend(anim, aiTime[0], aiTime[1], aiAnimTime[0],
                              aiAnimTime[1], 0.0, 1.0);
  animationBlendSet.PushBlend(anim, aiTime[1], aiTime[3], aiAnimTime[1],
                              aiAnimTime[3], 1.0, 1.0);
  surfaceEffects->SetDustRate(
      TDSSettings::Get()->GetValue(Warrior_FootImpact_DustRateModifier));
}

void AIBugWarriorBase::_4DFDF0() {
  auto SetupTarget = [&] {
    if (target) {
      const Vector &thisPosition = *GetPosition();
      const Vector &targetPosition = *target->GetPosition();
      const Vector localDistance = targetPosition - thisPosition;
      const float distance = D3DXVec3Dot(&localDistance, &localDistance);

      if (distance > 625) {
        group->SetActive(true);
        group->alertState = 2;
        group->mode = AIMODE_FIGHTING;
        group->_47D0C0(true);
      } else {
        if (alertState) {
          if (alertState == 1) {
            alertState = 2;
            field_C0(2);
            SetMovementMode(AIMODE_STILL);
          }
        } else {
          alertState = 1;
          field_C0(1);
        }
      }
    } else if (movementMode == 2) {
      SetMovementMode(AIMODE_MOVING);
    }
  };

  if (forcedTarget ||
      (field_140() && target &&
       target == AppGame::Get()->gameSession->aiManager->GetPlayerEntity(0) &&
       alertState != 3)) {
    SetupTarget();
    return;
  }

  SetTarget(nullptr, true);

  if (alertState != 3) {
    float rangeMin, rangeMax, chance, cone;

    if (alertState == 0) {
      rangeMin = GetIdleRangeMin();
      rangeMax = GetIdleRangeMax();
      chance = GetIdleChance();
      cone = GetIdleCone();
    } else {
      rangeMin = GetAlertRangeMin();
      rangeMax = GetAlertRangeMax();
      chance = GetAlertChance();
      cone = GetAlertCone();
    }

    AIEntity *spottedEntity =
        SpotEntity(rangeMin, rangeMax, chance, cone, false);
    if (spottedEntity) {
      SetTarget(spottedEntity, true);
    } else if (target && target->movementMode < AIMODE_DEAD) {
      SetTarget(target, false);
    }
    SetupTarget();
    return;
  }

  if (ignoreRadius > 0) {
    AIEntity *player =
        AppGame::Get()->gameSession->aiManager->GetPlayerEntity(0);

    if (player) {
      const Vector &thisPosition = *GetPosition();
      const Vector &targetPosition = *player->GetPosition();
      const Vector localDistance = targetPosition - thisPosition;
      const float distance = D3DXVec3Dot(&localDistance, &localDistance);

      if (distance > 0) {
        if (ignoreUseDeltaY) {
          const float v30 = targetPosition.y - thisPosition.y;

          if (-ignoreDeltaY < v30 && v30 < ignoreDeltaY) {
            SetTarget(player, true);
            SetAlertState(2);
          }
        } else {
          SetTarget(player, true);
          SetAlertState(2);
        }
      }
    }
  }
}

void AIBugWarriorBase::SetStateIdleByAlertState() {
  switch (alertState) {
  case ANIMSET_StaticIdle:
  case ANIMSET_StaticAlert:
  case ANIMSET_StaticAttack:
  case ANIMSET_StaticIgnore:
    animType = GetAnimSetResource(alertState);
    break;
  default:
    break;
  }

  anim = _4E8130(animType, 1);

  float v19 = TNL::Random::readF();
  v19 = v19 * 2 - 1;
  float v11 = field_F4() * v19 + 1;

  const Matrix &a4 = aiMatrix[1];

  float v12 = v11 * anim->duration;
  float v13 = aiTime[1] - aiTime[0];
  float v14 = 0.25 * v12;
  float a3 = (v13 + v14) * 0.5 + aiTime[0];
  float v25 = v12 * 0.5 + a3;

  SetMatrix(1, a3, a4, false);
  SetMatrix(2, v25, a4, false);
  SetMatrix(3, v14 + v25, a4, false);
  aiAnimTime[0] = 0.0;
  aiAnimTime[1] = 0.25;
  aiAnimTime[2] = 0.75;
  aiAnimTime[3] = 1.0;
  animationBlendSet._452640();
  animationBlendSet.PushBlend(anim, aiTime[0], aiTime[1], aiAnimTime[0],
                              aiAnimTime[1], 1.0, 0.0);
  animationBlendSet.PushBlend(anim, aiTime[0], aiTime[1], aiAnimTime[0],
                              aiAnimTime[1], 0.0, 1.0);
  animationBlendSet.PushBlend(anim, aiTime[1], aiTime[3], aiAnimTime[1],
                              aiAnimTime[3], 1.0, 1.0);
  surfaceEffects->SetDustRate(
      TDSSettings::Get()->GetValue(Warrior_FootImpact_DustRateModifier));
  walker->SetActiveStatus(false);
}

void AIBugWarriorBase::SetStateMove() {
  if (nextWaypoint) {
    // a3 = sub_48A500((void *)(this->data.base.walker->field_20 + 48)) * 1.5;
    float a3;
    Vector a2 = _455780(a3, waypointsNarrow == 0);
    _4E8D90(a2, movingZigZag, stickToWaypoints);
  } else {
    SetMovementMode(AIMODE_STILL);
    SetStateIdleByAlertState();
  }
}

void AIBugWarriorBase::SetStateOutOfGround() {
  animType = GetAnimSetResource(ANIMSET_SpecialOutOfGround);
  anim = static_cast<AIAnimation *>(animType->PickRandomAnimation());
  float v19 = TNL::Random::readF();
  v19 = v19 * 2 - 1;
  float v7 = field_F4() * v19 + 1;

  float v13 = v7 * anim->duration;
  double sessionTime = AppGame::Get()->SessionTime();

  SetMatrix(0, sessionTime, *Get(), false);
  SetMatrix(1, sessionTime, aiMatrix[0], false);
  SetMatrix(2, v13 * 0.75 + sessionTime, aiMatrix[0], false);
  SetMatrix(3, v13 + sessionTime, aiMatrix[0], false);
  aiAnimTime[0] = 0.0;
  aiAnimTime[1] = 0.0;
  aiAnimTime[2] = 0.75;
  aiAnimTime[3] = 1.0;

  animationBlendSet._452640();
  animationBlendSet.PushBlend(anim, aiTime[0], aiTime[3], aiAnimTime[0],
                              aiAnimTime[3], 1.0, 1.0);
  _949700();
  surfaceEffects->_4965F0(32, 4);
}

void AIBugWarriorBase::SetStateFlinch() {
  animType = GetAnimSetResource(ANIMSET_BeenHit);
  anim = static_cast<AIAnimation *>(animType->PickRandomAnimation());
  float v19 = TNL::Random::readF();
  v19 = v19 * 2 - 1;
  float v7 = field_F4() * v19 + 1;

  float animDuration = v7 * anim->duration;
  double sessionTime = AppGame::Get()->SessionTime();
  double time_4 = animDuration * 0.25 + sessionTime;

  const Matrix &mtx0 = *Get();
  Matrix mtx1 = GetMatrixAtTime(time_4);
  Matrix blendMatrix = (mtx0 + mtx1) * 0.5;
  // Matrix_694D60(blendMatrix);
  SetMatrix(0, sessionTime, mtx0, true);
  SetMatrix(1, time_4, blendMatrix, false);
  SetMatrix(2, animDuration * 0.75 + sessionTime, blendMatrix, false);
  SetMatrix(3, sessionTime + animDuration, blendMatrix, false);
  aiAnimTime[0] = 0.0;
  aiAnimTime[1] = 0.25;
  aiAnimTime[2] = 0.75;
  aiAnimTime[3] = 1.0;

  animationBlendSet._452A20(anim, aiTime[0], aiTime[1], aiAnimTime[0],
                            aiAnimTime[1], 0.0, 1.0);
  animationBlendSet.PushBlend(anim, aiTime[1], aiTime[3], aiAnimTime[1],
                              aiAnimTime[3], 1.0, 1.0);

  surfaceEffects->SetDustRate(
      TDSSettings::Get()->GetValue(Warrior_FootImpact_DustRateModifier));
}

void AIBugWarriorBase::SetStateJump() {
  Vector *v2 = nextWaypoint->GetPosition();
  Vector *v7 = GetPosition();
  Vector v8 = *v2 - *v7;
  float v9 = D3DXVec3Length(&v8);

  if (-0.38299999 * v9 <= v8.y) {
    if (v8.y <= 0.38299999 * v9) {
      animType = GetAnimSetResource(ANIMSET_SpecialJump);
    } else {
      animType = GetAnimSetResource(ANIMSET_SpecialJumpUp);
    }
  } else {
    animType = GetAnimSetResource(ANIMSET_SpecialJumpDown);
  }

  anim = static_cast<AIAnimation *>(animType->PickRandomAnimation());

  float v19 = TNL::Random::readF();
  v19 = v19 * 2 - 1;
  float v70 = field_F4() * v19 + 1;

  float animDuration = v70 * anim->duration;
  double sessionTime = AppGame::Get()->SessionTime();
  v70 = animDuration * 0.25;
  double v71 = v70 + sessionTime;

  const Matrix &mtx0 = *Get();
  Matrix mtx1 = GetMatrixAtTime(v71);
  Matrix blendMatrix = (mtx0 + mtx1) * 0.5;
  // Matrix_694D60(blendMatrix);

  Vector v53 = *(Vector *)&blendMatrix.m[1][0];
  Vector a3;
  Vector a2a = *v2;
  Vector v54;
  v54 = blendMatrix.m[3];
  v54 = a2a - v54;
  D3DXVec3Cross(&a3, &v54, &ExtractRow(blendMatrix, 1));

  Vector v23;
  D3DXVec3Normalize(&v23, &a3);
  InsertRow(blendMatrix, 0, v23);
  blendMatrix.m[0][3] = 0;
  blendMatrix.m[3][1] = 0;

  D3DXVec3Cross(&a3, &v53, &v23);
  InsertRow(blendMatrix, 2, a3);

  blendMatrix.m[2][3] = 0;

  Vector v58 = a2a + a3 * 0.001;
  v53 = {0, 1, 0};

  Collider collider;
  collider.field_4.collisionTypeFlags = 1;

  a3.x = v58.x - 0.0;
  a3.y = v58.y - 1.0;
  a3.z = v58.z - 0.0;

  a2a.x = v58.x + 0.0;
  a2a.y = v58.y + 1.0;
  a2a.z = v58.z + 0.0;

  collider.field_4.SetupCapsule(a2a, a3, 0, 1, 1, 1);

  if (UnkRegistry0::Get()->_66E250(collider) ||
      UnkRegistry0::Get()->_66DAA0(collider, this)) {
    v58 = collider.field_4.field_68;
    v53 = collider.field_4.field_74;
  }

  a3 = v58 - *GetPosition();
  a2a = a3;

  a3.x = a3.z * v53.y - a3.y * v53.z;
  a3.y = a2a.x * v53.z - a3.z * v53.x;
  a3.z = a2a.y * v53.x - a2a.x * v53.y;

  v54 = a3;
  D3DXVec3Normalize(&v54, &v53);

  a3.x = v53.z * v54.y - v53.y * v54.z;
  a3.y = v53.x * v54.z - v53.z * v54.x;
  a3.z = v53.y * v54.x - v53.x * v54.y;

  Matrix v78;
  InsertRow(v78, 0, v54);
  InsertRow(v78, 1, v53);
  InsertRow(v78, 2, a3);
  InsertRow(v78, 3, v58);

  a3.x = v58.x - blendMatrix.m30;
  a3.y = 0.0;
  a3.z = v58.z - blendMatrix.m32;

  const float v36 = D3DXVec3Length(&a3);
  const double v76 = v36 * 0.04 + v71;
  const double v80 = v70 + v76;

  aiAnimTime[0] = 0.0;
  aiAnimTime[1] = 0.25;
  aiAnimTime[2] = 0.75;
  aiAnimTime[3] = 1.0;
  SetMatrix(0, sessionTime, mtx0, true);
  SetMatrix(1, v71, blendMatrix, true);
  SetMatrix(2, v76, v78, true);
  SetMatrix(3, v80, v78, false);

  animationBlendSet._452A20(anim, aiTime[0], aiTime[1], aiAnimTime[0],
                            aiAnimTime[1], 1.0, 1.0);
  animationBlendSet.PushBlend(anim, aiTime[1], aiTime[2], aiAnimTime[1],
                              aiAnimTime[2], 1.0, 1.0);
  animationBlendSet.PushBlend(anim, aiTime[2], aiTime[3], aiAnimTime[2],
                              aiAnimTime[3], 1.0, 1.0);
}

void AIBugWarriorBase::func_8() {
  char v2 = true;

  if (field_82C) {
    field_82C = false;
    --dword_D2EF4C;
  }

  if (AppGame::Get()->SessionTime() <= aiTime[2]) {
    v2 = false;
  } else {
    if (movementMode == AIMODE_DYING) {
      SetMovementMode(AIMODE_DEAD);
      field_DC();
      SetActive(false);
      if (pRagDoll) {
        pRagDoll->deletable = true;
      }
      return;
    }
    specialMode = AISM_NONE;
    _4ED2E0();
  }

  if (!field_C4()) {
    switch (specialMode) {
    case AISM_NONE:
      switch (movementMode) {
      case AIMODE_STILL:
        AIFourStateMatrix::Process();
        if (v2 && alertState == 2) {
          group->alertState = 2;
          group->mode = AIMODE_FIGHTING;
          group->SetActive(true);
          group->_47D0C0(true);
        }
        return;
      case AIMODE_MOVING:
        AIFourStateMatrix::Process();
        _457A40(nullptr);
        break;
      case AIMODE_FIGHTING:
        AIFourStateMatrix::Process();
        if (fightTrack) {
          _4E28B0();
        }

        _457A40(nullptr);
        break;
      case AIMODE_IMMOBILE:
      case AIMODE_DYING:
        AIFourStateMatrix::Process();
        break;
      default:
        return;
      }
      break;
    case AISM_PLAYANIM:
    case AISM_JUMP:
      AIFourStateMatrix::Process();
      if (v2) {
        _457A40(nullptr);
      }
      break;
    case AISM_OUTOFGROUND:
    case AISM_BEENHIT:
      AIFourStateMatrix::Process();
      break;
    default:
      return;
    }
  }
}

void AIBugWarriorBase::field_34() {
  animType = GetAnimSetResource(ANIMSET_StaticIdle);
  anim = static_cast<AIAnimation *>(animType->PickRandomAnimation());

  if (!active) {
    return;
  }

  Matrix mtx = *Get();

  if (!_95AE20(mtx, 1.0, 2.0, mtx) && !_95B8E0(mtx, mtx, 2.0009999)) {
    _455C80(mtx, mtx);
  }

  Set(mtx);

  const double sessionTime = AppGame::Get()->SessionTime();
  mtx = *Get();
  SetMatrix(0, sessionTime, mtx, false);
  SetMatrix(1, sessionTime, mtx, false);
  SetMatrix(2, sessionTime, mtx, false);
  SetMatrix(3, anim->duration * 0.25 + sessionTime, mtx, false);
  _4ED2E0();
}

void AIBugWarriorBase::_4ED8E0(bool ignite, bool explode, float blastDamage) {
  if (movementMode < AIMODE_DYING && vulnerability > 0.0) {
    SetAttacker(nullptr);
    SetMovementMode(AIMODE_DYING);
    SetHealth(-1.0);
    if (ignite) {
      Ignite(1, 0.25, 0.25);
    }
    if (explode) {
      SetMovementMode(AIMODE_RAGDOLL);
      specialMode = AISM_NONE;
      _4ED2E0();
      const Vector &a2a = bbox.GetCenter();
      Vector a3a{0, 1, 0};
      IncomingDamage v7(a2a, a3a, a2a, 0, 1.0);
      v7.blast = blastDamage;
      pRagDoll->ApplyDamage(v7);
    } else {
      _4ED2E0();
    }
  }
}

void AIBugWarriorBase::SetActiveStatus(bool isActive) {
  AIBug::SetActiveStatus(isActive);

  if (isActive) {
    if (movementMode == AIMODE_MOVING && avoidance &&
        AbstractManager::Get()->field_18 == 2) {
      ++dword_D2EF4C;
      field_82C = 1;
      if (dword_D2EF4C > 0xA) {
        walker->SetActiveStatus(true);
      }
    }
  } else {
    if (surfaceEffects) {
      surfaceEffects->SetDustRate(0.0);
    }
  }
}

static void *MP_CLIENT_GAME;

void AIBugWarriorBase::TakeDamage(float amount) {
  if (AIEntity *attacker = GetAttacker();
      !attacker || !attacker->IsAIType(AITYPEID::PLAYER)) {
    amount *= GetDamageNonPlayerFactor();
  }

  if (!MP_CLIENT_GAME) {
    RemoveHealth(amount * vulnerability);
  }

  if (health > 0.0 || movementMode >= AIMODE_DYING) {
    if (health <= -10.0 && movementMode == AIMODE_DEAD) {
      SetMovementMode(AIMODE_DESTROYED);
    }
  } else {
    specialMode = AISM_NONE;
    field_D4();
    SetMovementMode(AIMODE_DYING);
    if (GetClientNetObject()) {
      _4E9C60();
    } else {
      _4ED2E0();
    }
  }

  if (specialMode == AISM_NONE && movementMode < AIMODE_IMMOBILE) {
    if (GetDefensePercentageChance() > TNL::Random::readF()) {
      specialMode = AISM_BEENHIT;
      if (GetClientNetObject()) {
        SetStateFlinch();
      } else {
        _4ED2E0();
      }
    }
  }
}

bool AIBugWarriorBase::DetachLimb(uint32_t boneIndex) {
  if (!pRagDoll) {
    RagDollRegistry::Get()->CreateFromModelObject(this);
  }

  if (pRagDoll->fullRagdoll) {
    return false;
  }

  pRagDoll->AddBone(boneIndex);
  density = TDSSettings::Get()->GetValue(Warrior_Ragdoll_Density);

  Vector bboxMin = bbox.min;
  Vector bboxMax = bbox.max;
  const double sessionTime = AppGame::Get()->SessionTime();
  Matrix mtx = *Get();
  animationBlendSet._4508F0(sessionTime);
  animationBlendSet.Process(renderState);
  pRagDoll->_661F80(0);
  const double nextTime = sessionTime + 0.1;
  GetMatrixAtTime(nextTime);
  Set(mtx);
  animationBlendSet._4508F0(nextTime);
  animationBlendSet.Process(renderState);
  pRagDoll->_661F80(0.1);
  bbox.min = bboxMin;
  bbox.max = bboxMax;
  bbox.shouldUpdateCenter = 1;
  _949700();
  return true;
}

void AIBugWarriorBase::_4E0160() {
  if (!surfaceEffects) {
    return;
  }

  Vector center = bbox.GetCenter();
  Vector *position = GetPosition();
  Vector localCenter = center - *position;
  Vector upAxis;
  upAxis = Get()->m[1];
  float v9 = D3DXVec3Dot(&localCenter, &upAxis);
  center = center - localCenter * v9;
  surfaceEffects->_4969E0(center);
}

void AIBugWarriorBase::_4E1AE0(WorldObjectModel *obj) {
  _462EA0(*obj);
  if (movementMode >= AIMODE_DEAD) {
    animationBlendSet._4508F0(AppGame::Get()->SessionTime());
    animationBlendSet.Process(renderState);
    field_30();
  }
  if (movementMode < AIMODE_DYING && active && vulnerability > 0.0) {
    Vector a2;
    a2 = aiMatrix[3].m[3];
    a2.y += 0.25;
    Collider collider;
    collider.field_4.SetupCapsule(a2, a2, 2, 1, 1, 1);

    if (obj->_949860(collider) &&
        collider.field_4.field_68.y > aiMatrix[3].m31) {
      AIDoor *asDoor = dynamic_cast<AIDoor *>(obj);
      if (asDoor) {
        asDoor->field_9C(0, 1, 10);
      }
    }
  }
}

Vector AIBugWarriorBase::_4E2730(float arg4) {
  if (arg4 <= 1) {
    const uint32_t bboxIndex = GetRootBoneIndex();
    const Vector &rootCenter =
        renderState->renModel->bboxes.at(bboxIndex).GetCenter();
    Vector tmPosition;
    D3DXVec3TransformCoord(&tmPosition, &rootCenter,
                           &renderState->matrices.at(bboxIndex));

    if (arg4 > 0) {
      const Matrix futureMatrix =
          GetMatrixAtTime(arg4 + AppGame::Get()->SessionTime());
      const Matrix &matrix = *Get();

      if (futureMatrix != matrix) {
        // Vector_TransformByMatrix(&tmPosition, v10, &tmPosition);
        D3DXVec3TransformCoord(&tmPosition, &tmPosition, &matrix);
      }

      return tmPosition;
    }
  }

  const Matrix futureMatrix =
      GetMatrixAtTime(arg4 + AppGame::Get()->SessionTime());
  const Vector &center = bbox.GetCenter();
  Vector tmPosition;
  D3DXVec3TransformCoord(&tmPosition, &center, &futureMatrix);
  return tmPosition;
}

void AIBugWarriorBase::_4E28B0() {
  if (!target) {
    return;
  }
  const double a4 = AppGame::Get()->SessionTime();
  const double v2 = AppGame::Get()->gameSession->gameTime.field_30;
  const double v6 = aiTime[1];

  auto DoTarget = [&]() {
    if (!target->IsAIType(AITYPEID::PLAYER)) {
      return;
    }

    if (!fightStrikeTrack) {
      return;
    }

    Matrix aiMatrix3 = aiMatrix[3];
    Vector a3 = aiMatrix3.m[1];
    Vector a2 = aiMatrix3.m[3];
    const Vector &v30 = *GetPosition();
    Vector a1 = v30 - a3;
    a2 = a1;
    D3DXVec3Cross(&a1, &a3, &a1);
    Vector v34;
    D3DXVec3Normalize(&v34, &a1);
    D3DXVec3Cross(&a1, &v34, &a3);
    a2 = a1;
    Matrix mtx;
    InsertRow(mtx, 0, v34);
    InsertRow(mtx, 1, a3);
    InsertRow(mtx, 2, a2);

    SetMatrix(1, aiTime[1], mtx, false);
    SetMatrix(2, aiTime[2], mtx, false);
    SetMatrix(3, aiTime[3], mtx, false);
  };

  if (target->IsAIType(AITYPEID::PLAYER)) {
    if (a4 <= v6 || a4 >= v2) {
      DoTarget();
      return;
    }
  } else {
    const double v7 = (v6 + aiTime[2]) * 0.5;

    if (a4 <= v7 || a4 - v2 >= v7) {
      DoTarget();
      return;
    }
  }

  if (field_FC() <= 0) {
    DoTarget();
    return;
  }

  int v9 = 0;
  Collider collider;

  while (1) {
    uint32_t v10 = field_F8(v9);
    uint32_t v12 = v10;
    if (!pRagDoll || pRagDoll->_661D50(v10)) {
      uint32_t v14 = v12;
      uint32_t v15 = v12;
      Matrix &v16 = renderState->matrices.at(v14);
      AABoundingBox &bbox = renderState->renModel->bboxes.at(v15);
      const Vector &boxCenter = bbox.GetCenter();
      Vector a1;
      D3DXVec3TransformCoord(&a1, &boxCenter, &v16);
      Vector vbox = bbox.max - bbox.min;
      const float a4 = D3DXVec3Length(&vbox);
      collider = {};
      collider.field_4.SetupCapsule(a1, a1, a4, 1, 1, 1);

      if (target->_949860(collider)) {
        break;
      }
    }

    v9++;
    if (v9 >= field_FC()) {
      DoTarget();
      return;
    }
  }

  if (target->IsAIType(AITYPEID::PLAYER)) {
    fightTrack = false;
    static_cast<AIPlayer *>(target)->_555000();
    const Matrix &v25 = *Get();

    Vector a3 = collider.field_4.field_68;
    Vector a2 = a3 - ExtractRow(v25, 2);
    Vector v43 = collider.field_4.field_74;
    collider.field_4.SetupCapsule(a2, a3, 0.0, 1.0, 1.0, 1.0);
    collider.field_4._49AD80(a3, v43);
  }

  IncomingDamage dmg(collider.field_4.field_68, collider.field_4.field_74,
                     collider.field_4.origin, this, 1);
  dmg.bulletHard = GetAttackStrength();
  target->ApplyDamage(dmg);
}

float AIBugWarriorBase::RemoveLimbHealth(uint32_t limbIndex, float amount) {
  AIEntity *attacker = GetAttacker();

  if (!attacker || attacker->IsAIType(AITYPEID::PLAYER)) {
    amount *= GetDamageNonPlayerFactor();
  }

  return limbsHealth.at(limbIndex) -= amount;
}

bool AIBugWarriorBase::_4E3910(uint32_t limbIndex) {
  auto found = limbsHealth.find(limbIndex);

  if (found == limbsHealth.end()) {
    return false;
  }

  if (pRagDoll) {
    return pRagDoll->_661D50(limbIndex);
  }

  return true;
}

static MultiplayerGame *MP_SERVER_GAME;
/*
TNL_IMPLEMENT_NETOBJECT_RPC(MultiplayerNetObject,
                            rpcAIBugWarriorBase_ApplyDamage2Server,
                            (TNL::Vector<short> a0, int a1, int a2, int a3),
                            (a0, a1, a2, a3), TNL::NetClassGroupGameMask,
                            TNL::RPCGuaranteedOrdered, TNL::RPCToGhost, 0) {}

TNL_IMPLEMENT_NETOBJECT_RPC(MultiplayerNetObject,
                            rpcAIPlayerUpdateScores2Client,
                            (int, int, int, int, int, int, int, int),
                            (a0, a1, a2, a3, a4, a5, a6, a7),
                            TNL::NetClassGroupGameMask,
                            TNL::RPCGuaranteedOrdered, TNL::RPCToGhost, 0) {}*/

void AIBugWarriorBase::ApplyDamage(IncomingDamage &dmg) {
  if (!active && health > 0.0) {
    return;
  }

  SetAttacker(dmg.entity);
  MultiplayerNetObject *clientNetObject = GetClientNetObject();
  MultiplayerNetObject *serverNetObject = GetServerNetObject();

  if (!clientNetObject && !serverNetObject) {
    field_C8(dmg, -1);
    return;
  }

  if (!dmg.entity || dmg.entity->field_429) {
    return;
  }

  MultiplayerNetObject *dmgEntityNetObject = dmg.entity->GetClientNetObject();

  if (!clientNetObject) {
    if (!serverNetObject) {
      field_C8(dmg, -1);
      return;
    }

    dmgEntityNetObject = dmg.entity->GetServerNetObject();
  }

  TNL::Vector<int16_t> vec;

  auto PushVec = [&](const Vector &inVec) {
    vec.push_back(inVec.x * 64);
    vec.push_back(inVec.y * 64);
    vec.push_back(inVec.z * 64);
  };

  PushVec(dmg.field_2C);
  PushVec(dmg.field_38);
  PushVec(dmg.field_44);
  vec.push_back(dmg.bulletSoft);
  vec.push_back(dmg.bulletHard);
  vec.push_back(dmg.slash);
  vec.push_back(dmg.punch);
  vec.push_back(dmg.blast);
  vec.push_back(dmg.heat);
  vec.push_back(dmg.corrosive);
  vec.push_back(dmg.electricity);
  vec.push_back(dmg.psiops);
  vec.push_back(dmg.flash);
  vec.push_back(dmg.sonic);
  vec.push_back(dmg.field_5C);

  const uint32_t boneIndex = collision->GetBoneIndex();

  if (clientNetObject) {
    clientNetObject->rpcAIBugWarriorBase_ApplyDamage2Server(
        vec, boneIndex, renderState->currentLod, dmgEntityNetObject->field_168);
  } else {
    field_C8(dmg, boneIndex);

    if (dmgEntityNetObject && movementMode == AIMODE_DEAD &&
        movementMode < AIMODE_DYING) {
      MultiplayerGamePlayer *ply =
          MP_SERVER_GAME->_698930(dmgEntityNetObject->field_168);
      if (ply) {
        serverNetObject->rpcAIPlayerUpdateScores2Client(
            ply->index, ply->field_108, ply->field_10C, ++ply->field_110, 0, 0,
            0, 0);
      }
    }

    _4E3910(boneIndex);

    serverNetObject->rpcAIBugWarriorBase_ApplyDamage2Client(
        vec, health, boneIndex, renderState->currentLod,
        dmgEntityNetObject->field_168);
  }
}

void AIBugWarriorBase::SetLimbHealth(uint32_t limbIndex, float health) {
  limbsHealth[limbIndex] = health;
}

void AIBugWarriorBase::SetStateDieElectrify() {
  SetHealth(-1.0);
  SetMovementMode(AIMODE_DYING);
  animType = GetAnimSetResource(ANIMSET_StaticAttack);
  anim = static_cast<AIAnimation *>(animType->PickRandomAnimation());

  double stage0BeginTime = AppGame::Get()->SessionTime();
  double stage1BeginTime = anim->duration * 0.25 + stage0BeginTime;
  double stage2BeginTime = anim->duration * 0.75 + stage0BeginTime;

  AIAnimation *nextAnim = static_cast<AIAnimation *>(
      GetAnimSetResource(ANIMSET_DyingNoKick)->PickRandomAnimation());
  double stage3BeginTime =
      (0.25 * nextAnim->duration + anim->duration * 0.25) * 0.5 +
      stage2BeginTime;
  double stage4BeginTime = nextAnim->duration * 0.75 + stage3BeginTime;

  const Matrix &mtx = *Get();

  SetMatrix(0, stage0BeginTime, mtx, false);
  SetMatrix(1, stage1BeginTime, mtx, false);
  SetMatrix(2, stage4BeginTime, mtx, false);
  SetMatrix(3, stage4BeginTime, mtx, false);
  aiAnimTime[0] = 0.0;
  aiAnimTime[1] = 0.25;
  aiAnimTime[2] = 0.75;
  aiAnimTime[3] = 1.0;

  animationBlendSet._452A20(anim, stage0BeginTime, stage1BeginTime,
                            aiAnimTime[0], aiAnimTime[1], 1.0, 1.0);
  animationBlendSet.PushBlend(anim, stage1BeginTime, stage2BeginTime,
                              aiAnimTime[1], aiAnimTime[2], 1.0, 1.0);
  animationBlendSet.PushBlend(anim, stage2BeginTime, stage3BeginTime,
                              aiAnimTime[2], aiAnimTime[3], 1.0, 0.0);
  animationBlendSet.PushBlend(nextAnim, stage2BeginTime, stage3BeginTime, 0.0,
                              0.25, 0.0, 1.0);
  animationBlendSet.PushBlend(nextAnim, stage3BeginTime, stage4BeginTime, 0.25,
                              1.0, 1.0, 1.0);
  animationBlendSet.PushBlend(nextAnim, stage4BeginTime, stage4BeginTime + 1.0,
                              1.0, 1.0, 1.0, 1.0);

  uint32_t v13 = collision->_91DDB0();
  if (v13 & 0x80) {
    collision->_91DC20(v13 ^ 0x80);
  }
  burntModelSwitch = true;
  Ignite(1, 0.0, 0.050000001);
  _4E7180();
}

void AIBugWarriorBase::TakeLimbDamage(float amount) {
  AIEntity *attacker = GetAttacker();

  if (!attacker || !attacker->IsAIType(AITYPEID::PLAYER)) {
    amount *= GetDamageNonPlayerFactor();
  }

  healthLegs -= amount * vulnerability;
  if (specialMode == AISM_NONE && movementMode < AIMODE_IMMOBILE &&
      (TNL::Random::readI() & 3) == 0) {
    specialMode = AISM_BEENHIT;
    if (GetClientNetObject())
      SetStateFlinch();
    else
      _4ED2E0();
  }
}

void AIBugWarriorBase::field_30() {
  if (pRagDoll && pRagDoll->fullRagdoll) {
    return;
  }

  ++INFO_WARRIORBUGBASE_TOTAL;
  bool v3 = true;
  if (AppGame::Get()->field_3F8 == 1 && movementMode != AIMODE_DYING) {
    int v5 = renderState->field_90;
    if (v5 >= 5) {
      if (RenderManager::Get()->field_20 != v5)
        v3 = false;
    } else {
      renderState->field_90 = v5 + 1;
    }
  }

  if ((movementMode < AIMODE_DEAD || AbstractManager::Get()->field_18 != 2) &&
      v3) {
    if (!isDummyEntity) {
      if (animationBlendSet.NumAnimations()) {
        animationBlendSet._4508F0(AppGame::Get()->SessionTime());
        renderState->SetAnimSet(&animationBlendSet);
        ++INFO_WARRIORBUGBASE;
      } else {
        renderState->SetAnimSet(nullptr);
        GetAnimSetResource(ANIMSET_StaticIdle)
            ->animations.front()
            ->SampleToRenState(renderState, 0);
      }
    }
  } else {
    renderState->SetAnimSet(nullptr);
  }

  int v8 = GetRootBoneIndex();
  Vector a1 = renderState->renModel->bboxes.at(v8).GetCenter();
  D3DXVec3TransformCoord(&a1, &a1, &renderState->matrices.at(v8));
  Vector v11 = field_EC();

  bbox.min = a1 - v11;
  bbox.max = a1 + v11;
  bbox.shouldUpdateCenter = true;

  _4E0160();
  _95AB60();
}

void AIBugWarriorBase::_4EEA70() {
  collision->_91E6B0(0, 2, 0.60000002);
  collision->_91E6B0(1, 2, 0.60000002);
  collision->_91E6B0(2, 2, 0.60000002);
  collision->_91E6B0(3, 2, 0.60000002);
  collision->_91E1B0();
  collision->_91DC20(2);

  if (movementMode > AIMODE_DYING) {
    if (AbstractManager::Get()->field_18 == 5) {
      if (!pRagDoll || !pRagDoll->fullRagdoll) {
        animationBlendSet._4508F0(AppGame::Get()->SessionTime());
        animationBlendSet.Process(renderState);
        _949700();
      }
      renderState->SetAnimSet(nullptr);
    }
  } else {
    collision->_91DC20(150);

    if (!surfaceEffects) {
      surfaceEffects = new SurfaceEffects(this);
      surfaceEffects->_496D20({2.5, 0, 2.5}, {0, 1, 0}, 1);
    }
  }
}

AIAnimation *AIBugWarriorBase::_4E8130(ResourceObjectAnimationSet *animSet,
                                       bool unk) {
  if (unk && renderState->currentLod <= 1) {
    Matrix mtx = *Get();
    Matrix v68 = aiMatrix[3];
    Vector v55 = ExtractRow(aiMatrix[3], 1) * 1.625 * GetHullSizeFactor();
    v55 += ExtractRow(aiMatrix[3], 3);
    Set(v68);
    uint32_t v12 = GetRootBoneIndex();
    Vector rootBboxCenter = renderState->renModel->bboxes.at(v12).GetCenter();

    Collider collider;
    collider.field_4.collisionTypeFlags = 8;
    std::default_random_engine re;
    std::vector<ResourcePtr<ResourceObjectAnimation>> shuffledAnimations(
        animSet->animations);
    std::shuffle(shuffledAnimations.begin(), shuffledAnimations.end(), re);

    AIAnimation *v53 = nullptr;
    AIAnimation *v56 = nullptr;
    float v54 = 1000;

    while (!v53) {
      auto &animRes = shuffledAnimations.back();
      const float animHalfTime =
          shuffledAnimations.back()->animation.duration * 0.5;
      shuffledAnimations.pop_back();
      animRes->SampleToRenState(renderState, animHalfTime);
      Vector tmAtAnimHalfTime;
      D3DXVec3TransformCoord(&tmAtAnimHalfTime, &rootBboxCenter,
                             &renderState->matrices.at(v12));

      Vector hullBottomPoint = tmAtAnimHalfTime - v55;
      float v48 = D3DXVec3Length(&hullBottomPoint);

      if (GetHullSizeFactor() >= v48) {
        v53 = &animRes->animation;
        break;
      }

      Vector v72 = hullBottomPoint * 2;
      float v22 = GetHullSizeFactor();
      Vector v70 = v72 * v22;
      float v24 = 1 / v48;

      tmAtAnimHalfTime = tmAtAnimHalfTime + v24 * v70;

      collider.field_4.SetupCapsule(v55, tmAtAnimHalfTime, 0, 1, 1, 1);
      if (UnkRegistry0::Get()->_66DAA0(collider, this)) {
        if (v48 < v54) {
          v54 = v48;
          v56 = &animRes->animation;
        }
        continue;
      }

      Vector v52 = tmAtAnimHalfTime;
      Vector v57 = tmAtAnimHalfTime - ExtractRow(v68, 3);
      float v27 = D3DXVec3Dot(&v57, &ExtractRow(v68, 1));
      v52 = tmAtAnimHalfTime - v27 * ExtractRow(v68, 1);
      Vector v73 = ExtractRow(v68, 1) * GetHullSizeFactor();
      Vector segmentP1 = v52 - v73;
      v52 += ExtractRow(v68, 1) * GetHullSizeFactor();

      collider.field_4.SetupCapsule(v52, segmentP1, 0, 1, 1, 1);

      if (UnkRegistry0::Get()->_66DAA0(collider, this)) {
        v53 = &animRes->animation;
        break;
      } else {
        if (v48 < v54) {
          v54 = v48;
          v56 = &animRes->animation;
        }
      }
    }

    Set(mtx);

    return v53 ? v53 : v56;
  } else {
    return anim;
  }
}
void AIBugWarriorBase::_4E8D90(const Vector &a2, bool moveZigZag,
                               bool stickToWaypoints) {}
void AIBugWarriorBase::_4E9C60() {}

void AIBugWarriorBase::_4EAB20() {}

void AIBugWarriorBase::SetStateRagdoll() {
  if (pRagDoll && pRagDoll->fullRagdoll) {
    return;
  }

  auto deadResource = GetDeadModelResource();

  if (deadResource.object != resourceRef.object) {
    resourceRef->DecreaseReference();
    resourceRef.object = deadResource.object;
    resourceRef.Assign(deadResource.object, 0);
    resourceRef->SafeLoad();
  }

  renderState->SetModel(resourceRef->model);
  renderState->SetRender(true);
  density = TDSSettings::Get()->GetValue(Warrior_Ragdoll_Density);
  Vector bboxMax = bbox.max;
  Vector bboxMin = bbox.min;

  double sessionTime = AppGame::Get()->SessionTime();
  animationBlendSet._4508F0(sessionTime);
  animationBlendSet.Process(renderState);
  sessionTime += 0.1;

  Matrix nextMatrix = GetMatrixAtTime(sessionTime);

  if (pRagDoll) {
    RagDoll::Bones ragdollBones;
    pRagDoll->_6666B0(ragdollBones);
    Set(nextMatrix);
    animationBlendSet._4508F0(sessionTime);
    animationBlendSet.Process(renderState);
    pRagDoll->_661FB0(ragdollBones, 0.1);
  } else {
    RagDollRegistry::Get()->CreateFromModelObject(this);
    Set(nextMatrix);
    animationBlendSet._4508F0(sessionTime);
    animationBlendSet.Process(renderState);
    pRagDoll->_663EB0(0.1);
  }

  bbox.max = bboxMax;
  bbox.min = bboxMin;
  bbox.shouldUpdateCenter = true;

  _949700();
  _4E7180();
  SetActive(false);

  Vector boundsVolumeMin = bboxMin * 0.75 + bbox.max * 0.25;
  Vector boundsVolumeMax = bboxMin * 0.25 + bbox.max * 0.75;
  Vector boundsArea = boundsVolumeMax - boundsVolumeMin;

  for (int i = 0; i < 16; i++) {
    Vector v48{TNL::Random::readF(), TNL::Random::readF(),
               TNL::Random::readF()};
    v48 = boundsVolumeMin + boundsArea * v48;
    Vector v49{TNL::Random::readF(), TNL::Random::readF(),
               TNL::Random::readF()};
    v49 = (Vector(0.5, 0.5, 0.5) - v49) * 8;

    (new ParticleSystemWarriorBulletHit())->_743540(v48, v49, 4);
  }

  if (burstGibAudioPlayable3D) {
    burstGibAudioPlayable3D->AddSource(GetPosition());
  }

  SoundManager::Get()->_5CD780(burstGibAudioPlayable, 9, 0, 0);
}
