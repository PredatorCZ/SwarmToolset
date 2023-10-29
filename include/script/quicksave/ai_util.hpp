#pragma once
#include "script/core.hpp"
#include "script/enum_share.hpp"

struct AITriggerBoxQuicksave {
  float nextCheckTime;
  ResourceArray entitiesLast;
  void ReflectorTag();
};

struct AIGroupQuicksave {
  AIALERT desAlert;
  AIMODE desMode;
  void ReflectorTag();
};

struct AISpawnGroupQuicksave {
  uint32 memberNum;
  uint32 numInCurrWave;
  bool bSpawning;
  bool bSpawnAllowed;
  bool bSpawnedBySpot;
  void ReflectorTag();
};

struct AISquadQuicksave {
  AISQUADMODE ePrevMode;
  float fSpeed;
  ResourceArray hotSpotList;
  ResourceArray memberHotSpots;
  float dTime0;
  float dTime1;
  uint32 nNextToDisembark;
  ResourceArray pWayPointHistory;
  float dLastCheckMemberDistanceTime;
  bool bNeedToCatchup;
  bool bMembersAtTempHotspots;
  void ReflectorTag();
};

struct AIHotspotQuicksave {
  ResourceRef pOccupier;
  bool bActionsDone;
  void ReflectorTag();
};

struct AISpawnerVehicleQuicksave {
  bool bSpawning;
  void ReflectorTag();
};

struct AILiftQuicksave {
  bool getIsActive;
  float posFactor;
  bool bRequestedUp;
  bool bRequestedDown;
  void ReflectorTag();
};
