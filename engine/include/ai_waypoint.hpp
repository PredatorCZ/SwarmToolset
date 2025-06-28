#pragma once
#include "world_object.hpp"
#include <list>

struct AITrigger;

struct AIWaypoint : WorldObject
{
  int field_98;
  int field_9C;
  int field_A0;
  AIWaypoint *nextWaypoint;
  int aiTypeId;
  std::list<AITrigger> triggers;
};
