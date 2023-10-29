#pragma once
#include "quicksave/ai_vehicle.hpp"

struct AIBomber : ModelDetailDynamic {
  AIEntity aiEntity;
  AIFlyingVehicleQuicksave aiFlyingVehicleQuicksave;
  AIBomberQuicksave quicksave;
};

struct AIDropshipMarauder : ModelDetailDynamic {
  AIEntity aiEntity;
  AIFlyingVehicleQuicksave aiFlyingVehicleQuicksave;
  ResourceRef marauder;
  AIDropshipMarauderQuicksave aiDropshipMarauderQuicksave;
};

struct AIDropshipGrunt : ModelDetailDynamic {
  AIEntity aiEntity;
  AIFlyingVehicleQuicksave aiFlyingVehicleQuicksave;
  ResourceRef squad;
  ResourceRef speechResource;
  AIDropshipGruntQuicksave aiDropshipGruntQuicksave;
};

struct AIDropshipCargo:ModelDetailDynamic
{
  AIEntity aiEntity;
  AIFlyingVehicleQuicksave aiFlyingVehicleQuicksave;
  AIDropshipGruntQuicksave aiDropshipCargoQuicksave;
};

