#pragma once
#include "abstract.hpp"
#include "resource_ptr.hpp"
#include <list>

using LARGE_INTEGER = uint64_t;

struct WorldObjectContext;
struct LevelStats;
struct ColCells;
struct WorldObjectContext;
struct AIManager;
struct AudioListenerDirectSound3D;
struct AIPlayer;
struct GameObject;
struct Processable;
struct Viewport;
struct OverlayText;
struct ResourceStringTable;

struct GameTime {
  int field_4;
  LARGE_INTEGER gameTick;
  double field_10;
  double field_18;
  double sessionTime;
  double lastTickSessionTime;
  double field_30;
  double gameSpeed;
  double field_40;
  double field_48;
  char field_50;
  char field_51;
  int field_54;
  double field_58;
};

struct GameSession : Abstract {
  WorldObjectContext *field_38;
  LevelStats *levelStats;
  GameTime gameTime;
  ColCells *colCells;
  int field_A4;
  WorldObjectContext *worldObjectContext;
  AIManager *aiManager;
  AudioListenerDirectSound3D *listener;
  AIPlayer *field_B4;
  std::list<GameObject *> gameObjects;
  std::list<Processable *> processables[3];
  std::list<void *> field_E8;
  Viewport *viewport;
  char isLoading;
  int field_FC;
  OverlayText *overlayText;
  int infoOverlayFlags;
  std::string levelName;
  int field_124;
  char field_128;
  int field_12C;
  int field_130;
  int field_134;
  char field_138;
  char field_139;
  std::list<void *> globalScriptsExcluded;
  std::string levelMovie;
  std::string levelBriefingImage;
  std::string missionSuccessImage;
  std::string missionFailImage;
  std::string missionCourtMarshallImage;
  std::string interMissionImage1;
  std::string interMissionImage2;
  std::string briefingSpeechResourceName;
  std::string successSpeechResourceName;
  std::string failureSpeechResourceName;
  std::string courtMarshallSpeechResourceName;
  std::string missionSuccessMovie;
  std::string missionFailMovie;
  std::string missionCourtMarshallMovie;
  ResourcePtr<ResourceStringTable> briefingText;
  ResourcePtr<ResourceStringTable> objectivesText;
  ResourcePtr<ResourceStringTable> successText;
  ResourcePtr<ResourceStringTable> failureText;
  ResourcePtr<ResourceStringTable> courtMarshallText;
  float campaignParTime;
  float campaignSLBestTime;
  float levelAttackParTime;
  float levelAttackSLBestTime;
  char field_4C0;
  char field_4C1;
  float field_4C4;
};
