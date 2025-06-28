#pragma once
#include "sl_variable_list_template.hpp"
#include "sl_variable_template.hpp"
#include "watcher.hpp"
#include <list>
#include <vector>

struct AIEntity;
struct AIUsable;
struct SLVariableSet;
struct SLVariableAbstractRef;
struct AIPlayer;

struct AIManager : Watcher {
  AIPlayer *GetPlayer(int playerIndex);
  AIEntity *GetPlayerEntity(int playerIndex);

  std::vector<AIPlayer *> players;
  std::list<AIUsable *> usables;
  std::list<AIEntity *> entities;
  int field_38;
  float field_3C;
  float warriorRumbleVolumeFactor;
  float rumbleVolMultStTime;
  float rumbleVolMultEndTime;
  float rumbleVolMultStVol;
  float field_50;
  SLVariableSet *sl_quicksave;
  SLVariableListTemplate<SLVariableAbstractRef> *sl_deadBodyList;
  SLVariableTemplate<float> *sl_rumbleVolMultStTime;
  SLVariableTemplate<float> *sl_rumbleVolMultEndTime;
  SLVariableTemplate<float> *sl_rumbleVolMultStVol;
  int field_68;
};
