#include "ai_animation_blend_set.hpp"
#include "ai_animation.hpp"
#include "ai_entity.hpp"
#include "audio_playable.hpp"
#include "audio_playable_3d_extended.hpp"
#include "ren_model.hpp"
#include "render_manager.hpp"
#include "resource_sound.hpp"
#include "skeletal_animation.hpp"
#include "skeleton.hpp"
#include "sound_manager.hpp"
#include <tnlRandom.h>

void AnimationBlendData::_44DB30(double newTime, bool isEnd) {
  const double v3 = (newTime - time) * timeInverseLength;

  if (v3 < 0.0 || v3 > 1.0) {
    if (isEnd && v3 > 1.0) {
      setAnimation->blendWeight = blendLength + blend;
      setAnimation->animTime = setAnimation->animation->duration;
    } else {
      setAnimation->blendWeight = 0.0;
    }
  } else {
    setAnimation->animTime = v3 * timeAnimLength + timeAnim;
    setAnimation->animTime =
        setAnimation->animation->duration * setAnimation->animTime;
    const float duration = setAnimation->animation->duration;
    if (setAnimation->animTime < 0.0)
      setAnimation->animTime = 0.0;
    if (duration < setAnimation->animTime)
      setAnimation->animTime = duration;
    setAnimation->blendWeight = v3 * blendLength + blend;
  }
}

void AIAnimationBlendSet::_748150() {
  float aggVal = 0;

  for (auto a : animations) {
    aggVal += a->blendWeight;
  }

  aggVal = 1.0 / aggVal;

  for (auto a : animations) {
    a->blendWeight *= aggVal;
  }
}

void AIAnimationBlendSet::_450870(double time) {
  for (size_t idx = 0; auto a : animationBlends) {
    a->_44DB30(time, ++idx == animationBlends.size());
  }
}

void AIAnimationBlendSet::_4508F0(double time) {
  _450870(time);
  _748150();
}

void AIAnimationBlendSet::_452640() {
  animations.clear();
  animationBlends.clear();

  for (auto a : activeAudioPlayables) {
    if (!a || !a->field_28()) {
      continue;
    }

    SoundManager::Get()->RemoveAudio(a);
    a->soundResource->DeleteAudioPlayable(a);
  }

  activeAudioPlayables.clear();
  blends.clear();
}

void AIAnimationBlendSet::_452A20(AIAnimation *animation, double aiTime0,
                                  double aiTime1, float aiAnimTime0,
                                  float aiAnimTime1, float blend0,
                                  float blend1) {
  aiTime0 -= 0.001;

  AnimationBlend newBlend{
      .resource = animation->resource,
      .time = aiTime0,
      .time_plus_delta = aiTime1,
      .timeAnim = aiAnimTime0,
      .timeAnim_plus_delta = aiAnimTime1,
      .blend = blend0,
      .blend_plus_delta = blend1,
      .field_28 = true,
  };

  blends.push_back(newBlend);

  AIAnimationBlendSetAnimation *nSet = new AIAnimationBlendSetAnimation();
  nSet->animation = animation;
  animations.push_back(nSet);

  AnimationBlendData *blendData = new AnimationBlendData();
  blendData->time = aiTime0;
  blendData->setAnimation = nSet;
  blendData->timeAnim = aiAnimTime0;
  blendData->blend = blend0;
  blendData->timeInverseLength = 1.0 / (aiTime1 - aiTime0);
  blendData->timeAnimLength = aiAnimTime1 - aiAnimTime0;
  blendData->blendLength = blend1 - blend0;

  if (TNL::Random::readF() <= animation->soundPropability) {
    if (animation->soundList) {

      for (auto &s : *animation->soundList) {
        AudioPlayable *audio = s->CreateAudioPlayable();

        if (!audio) {
          continue;
        }

        // bug: position is overriden when added to sound manager
        if (audio->extended3D) {
          Vector soundSource;
          if (animation->soundNode) {
            Matrix &tm = entity->renderState->matrices.at(animation->soundNode);
            const Vector &center =
                entity->renderState->renModel->bboxes.at(animation->soundNode)
                    .GetCenter();
            D3DXVec3TransformCoord(&soundSource, &center, &tm);
          } else {
            soundSource = *entity->GetPosition();
          }

          audio->extended3D->SetPosition(soundSource);
          activeAudioPlayables.push_back(audio);
        }

        audio->field_5C();
        double v30 =
            aiTime0 + animation->duration * audio->soundResource->startDelay;
        if (entity) {
          audio->entity = entity;
        }

        SoundManager::Get()->AddAudio(audio, 1033, v30, entity, 0);
      }
    }
  }

  blendData->blend = 0.0;
  blendData->blendLength = 1.0;
  double v51 = -999.0;

  for (auto &b : animationBlends) {
    double timeEnd = 1.0 / b->timeInverseLength + b->time;

    if (timeEnd > v51) {
      v51 = timeEnd;
    }
  }

  // bug?? cannot iterate when we check for empty blends
  if (v51 > 0.0 && v51 < aiTime1 && animationBlends.empty()) {
    for (auto &b : animationBlends) {
      double m_dTime0 = 1.0 / b->timeInverseLength + b->time;
      double m_fBlend0 = b->blendLength + b->blend;

      if (m_dTime0 == v51 && m_fBlend0 > 0.0) {
        float m_fTAnim0 = b->timeAnim + b->timeAnimLength;
        PushBlend(b->setAnimation->animation, m_dTime0, aiTime1, m_fTAnim0,
                  m_fTAnim0, m_fBlend0, m_fBlend0);
      }
    }
  }

  for (auto &b : animationBlends) {
    b->_44DC00(blendData->time, aiTime1);
  }

  animationBlends.push_back(blendData);
}

void AIAnimationBlendSet::PushBlend(AIAnimation *animation, double aiTime0,
                                    double aiTime1, float aiAnimTime0,
                                    float aiAnimTime1, float blend0,
                                    float blend1) {
  AnimationBlend newBlend{
      .resource = animation->resource,
      .time = aiTime0,
      .time_plus_delta = aiTime1,
      .timeAnim = aiAnimTime0,
      .timeAnim_plus_delta = aiAnimTime1,
      .blend = blend0,
      .blend_plus_delta = blend1,
      .field_28 = false,
  };

  blends.push_back(newBlend);

  AIAnimationBlendSetAnimation *nSet = new AIAnimationBlendSetAnimation();
  nSet->animation = animation;
  animations.push_back(nSet);

  AnimationBlendData *blendData = new AnimationBlendData();
  blendData->time = aiTime0;
  blendData->setAnimation = nSet;
  blendData->timeAnim = aiAnimTime0;
  blendData->blend = blend0;
  blendData->timeInverseLength = 1.0 / (aiTime1 - aiTime0);
  blendData->timeAnimLength = aiAnimTime1 - aiAnimTime0;
  blendData->blendLength = blend1 - blend0;

  animationBlends.push_back(blendData);

  if (TNL::Random::readF() <= animation->soundPropability && aiAnimTime0 == 0) {
    for (auto &s : *animation->soundList) {
      AudioPlayable *audio = s->CreateAudioPlayable();

      if (!audio) {
        continue;
      }

      // bug: position is overriden when added to sound manager
      if (audio->extended3D) {
        Vector soundSource;
        if (animation->soundNode) {
          Matrix &tm = entity->renderState->matrices.at(animation->soundNode);
          const Vector &center =
              entity->renderState->renModel->bboxes.at(animation->soundNode)
                  .GetCenter();
          D3DXVec3TransformCoord(&soundSource, &center, &tm);
        } else {
          soundSource = *entity->GetPosition();
        }

        audio->extended3D->SetPosition(soundSource);
        activeAudioPlayables.push_back(audio);
      }

      audio->field_5C();
      double v30 =
          aiTime0 + animation->duration * audio->soundResource->startDelay;
      if (entity) {
        audio->entity = entity;
      }

      SoundManager::Get()->AddAudio(audio, 1033, v30, entity, 0);
    }
  }
}

void AIAnimationBlendSet::CleanAudioPlayables() {
  for (auto a : activeAudioPlayables) {
    if (!a) {
      continue;
    }

    a->soundResource->DeleteAudioPlayable(a);
  }

  activeAudioPlayables.clear();
}

void AIAnimationBlendSet::_7481A0() {
  for (auto a : animations) {
    if (a->blendWeight > 0) {
      a->animation->skeletalAnimation->_5C34F0(a->blendWeight);
    }
  }
}

bool AIAnimationBlendSet::_7481E0() {
  if (animations.empty()) {
    return false;
  }

  const uint32_t numTracks =
      animations.front()->animation->skeletalAnimation->tracks.size();

  for (auto a : animations) {
    if (a->animation->skeletalAnimation->tracks.size() != numTracks) {
      return true;
    }
  }

  return false;
}

void AIAnimationBlendSet::_748230(Skeleton *skel) {
  for (auto a : animations) {
    if (a->blendWeight > 0 && a->animation && a->animation->skeletalAnimation) {
      a->animation->skeletalAnimation->_5C5C70(skel);
    }
  }
}

void AIAnimationBlendSet::Process(RenderState *state) {
  if (animations.empty()) {
    return;
  }

  auto anim = animations.front()->animation;

  if (anim->field_24) {
    if (anim->field_24 == 1) {
      _748950(state);
    }
  } else if (!anim->field_28) {
    _749730(state);
  }
}

void AIAnimationBlendSet::_749730(RenderState *state) {
  std::vector<std::vector<Matrix3x4> *> framesPerAnim;
  float v31 = 0;

  for (auto a : animations) {
    if (!a->animation) {
      continue;
    }

    if (a->animation->frames.size() > 0) {
      const uint32_t frame = a->animation->GetFrame(a->animTime);
      framesPerAnim.emplace_back(a->animation->frames.at(frame));
    } else {
      framesPerAnim.emplace_back(nullptr);
      v31 += a->blendWeight;
    }
  }

  for (int index = -1; auto &m : state->matrices) {
    if (index < 0) [[unlikely]] {
      index++;
      continue;
    }

    m = {}; // bug? _m44 is not 1

    for (size_t animIndex = 0; auto a : animations) {
      float v17 = a->blendWeight;

      if (v17 == 0) {
        continue;
      }

      auto boneTransforms = framesPerAnim.at(animIndex);

      if (!boneTransforms) {
        continue;
      }

      if (v31 != 0.0) {
        v17 += v31;
        v31 = 0.0;
      }

      const Matrix3x4 &trackMatrix = boneTransforms->at(index);
      Matrix trackMatrix4x4;
      InsertRow(trackMatrix4x4, 0, trackMatrix.m[0]);
      InsertRow(trackMatrix4x4, 1, trackMatrix.m[1]);
      InsertRow(trackMatrix4x4, 1, trackMatrix.m[2]);
      InsertRow(trackMatrix4x4, 3, trackMatrix.m[3]);

      m += trackMatrix4x4 * v17;
    }

    D3DXMatrixMultiply(&m, &m, &state->matrices.front());
  }
}

void AIAnimationBlendSet::_748950(RenderState *state) {
  if (animations.size() == 1) {
    animations.front()->animation->skeletalAnimation->InterpolateToRenderState(
        state, animations.front()->animTime);
    return;
  }

  uint32_t v5 = 0;

  if (state->currentLod) {
    int v6 = state->currentLod - 1;

    if (v6) {
      v5 = 1;

      if (v6 == 1) {
        v5 = 2;
      }
    }
  }

  if (state->field_90 >= RenderManager::Get()->field_20) {
    if (v5 == 0) {
      goto LABEL_32;
    }
  } else {
    v5 = 1;
  }

  if (animations.size() > v5) {
    if (v5 == 1) {
      double v10 = 0;
      AIAnimationBlendSetAnimation *skAnim = nullptr;

      for (auto a : animations) {
        if (v10 < a->blendWeight) {
          v10 = a->blendWeight;
          skAnim = a;
        }
      }

      skAnim->animation->skeletalAnimation->InterpolateToRenderState(
          state, skAnim->animTime);
      return;
    }

    float v12 = 0.0;
    float v29 = 0.0;
    AIAnimationBlendSetAnimation *anim0 = animations.front();
    AIAnimationBlendSetAnimation *anim1 = animations.front();

    for (auto a : animations) {
      if (a->blendWeight > v29) {
        v29 = a->blendWeight;
        anim1 = a;
      } else {
        v29 = v12;
        anim1 = anim0;
        v12 = a->blendWeight;
        anim0 = a;
      }
    }

    for (auto a : animations) {
      if (anim0 != a && anim1 != a) {
        a->blendWeight = 0;
      }
    }

    float v25 = 1.0 / (v29 + v12);
    anim0->blendWeight = v25 * v12;
    anim1->blendWeight = v25 * v29;
  }

LABEL_32:
  _748230(state->renModel->skeleton);
  const bool v24 = _7481E0();
  if (v24) {
    _7481A0();
  }

  bool unk = true;

  for (auto a : animations) {
    if (a->blendWeight > 0) {
      if (v24) {
        a->animation->skeletalAnimation->_5C50D0(state, a->animTime,
                                                 a->blendWeight, unk);
      } else {
        a->animation->skeletalAnimation->_5C4FC0(state, a->animTime,
                                                 a->blendWeight, unk);
      }
      unk = false;
    }
  }

  state->renModel->skeleton->SetTransforms(state->matrices.front(),
                                           state->matrices);
}
