#pragma once
#include "core.hpp"

enum class ChatLinePriority {
  Low,
  Medium,
  High,
};

struct ChatLine : ResourcePack {
  std::string string;
  ResourceRef sound;
  ResourceRef aiEntity;
  float delay;
  ChatLinePriority priority;
  bool order;
  bool subtitled;
  ResourceRef speechType;
};

struct ResourceSpeechType : ResourcePack {
  std::string speechType; // TODO string so far
  float chance;
  ResourceArray speech;
};

struct ResourceSpeechBankGrunt : ResourcePack {
  ResourceArray speechSets;
};

struct ResourceSpeechBankLeader : ResourceSpeechBankGrunt {};
struct ResourceSpeechBankPsiOps : ResourceSpeechBankGrunt {};
struct ResourceSpeechBankMechanic : ResourceSpeechBankGrunt {};

struct ResourceStringTable : ResourcePack {
  AFileInfo filename;
};

struct ChatScript : ResourcePack {
  ResourceArray lines;
  ResourceArray actions;
};

struct ResourceObjectSpeechDropship : ResourcePack {
  float LandingChance;
  float TakingOffChance;
  float DroppingOffSquadChance;
  ResourceArray speechLanding;
  ResourceArray speechTakingOff;
  ResourceArray speechDroppingOffSquad;
};

struct AIConversation : ResourcePack {
  ResourceArray humans;
  ResourceArray chatLines;
  bool active;
  float delayMin;
  float delayMax;
};
