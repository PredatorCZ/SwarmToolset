#pragma once
#include "audio_playable.hpp"

struct AudioPlayable3DExtended : AudioPlayable {
  virtual void SetPosition(const Vector &position) = 0;

  int field_A8;
  int field_AC;
  char field_B0;
  int field_B4;
  int field_B8;
  int field_BC;
  int field_C0;
  int field_C4;
  int field_C8;
  int field_CC;
  int field_D0;
  int field_D4;
  int field_D8;
  int field_DC;
  int field_E0;
  int field_E4;
  int field_E8;
  int field_EC;
  int field_F0;
  int field_F4;
  char field_F8;
  char field_F9;
  int field_FC;
  int field_100;
  int field_104;
  int field_108;
  int field_10C;
};
