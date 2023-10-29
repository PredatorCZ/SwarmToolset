#pragma once
#include "quicksave/ai_human.hpp"

struct ResourceHumanCharacter : ResourcePack {
  ResourceRef model;
  ResourceRef shaderOverrides;
  AIHUMAN humanType;
  ResourceRef speechBank;
};

struct AIHuman : AIWorldObject {
  AIHUMAN humanType;
  ResourceRef character;
  ResourceRef weaponActive;
  ResourceRef weaponStowed1;
  ResourceRef weaponStowed2;
  ResourceRef weaponStowed3;
  ResourceRef weaponStowed4;
  ResourceRef weaponStowed5;
  ResourceRef weaponStowed6;
  ResourceRef weaponStowed7;
  ResourceRef weaponStowed8;
  ResourceRef weaponStowed9;
  ResourceRef weaponStowed10;
  bool canBreakIgnore;
  float personalGrenadeChance;
  float personalAttractTurnChance;
  float personalKneelChance;
  AIHumanStartWeapons startWeapons;
  AIHumanDeath death;
  std::string name;
  bool gunVisible;
  bool dropToGround;
  bool doSalute;
  bool saluteRadius;
  AIHumanQuicksave aiHumanQuicksave;
};

struct AIPlayerAmmoStowed {
  uint32 Bullet;
  uint32 Grenade;
  uint32 Shotgun;
  uint32 Rocket;
  uint32 Missile;
  uint32 Slug;
  uint32 HandGrenade;
  void ReflectorTag();
};

struct AIPlayer : AIHuman {
  AIPlayerAmmoStowed ammoStowed;
  bool startInDropPod;
  bool dropPodJustEnd;
  bool disableWeapon;
  AIPlayerQuicksave aiPlayerQuicksave;
  ResourceRef collidable;
};
