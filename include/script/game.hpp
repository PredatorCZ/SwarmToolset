#pragma once
#include "core.hpp"

struct LevelStats : Resource {
  std::string loadingImage;
  uint32 numObjects;
};

struct GameSessionDocument : Resource {
  std::string authorName;
  time_t creationDateTime;
  time_t lastSaveDateTime;
};

struct GameSessionFilesDirs {
  std::string levelMovie;
  std::string levelBriefingImage;
  std::string missionSuccessImage;
  std::string missionFailImage;
  std::string missionCourtMarshallImage;
  std::string interMissionImage1;
  std::string interMissionImage2;
  std::string missionSuccessMovie;
  std::string missionFailMovie;
  std::string missionFailCourtMarshallMovie;
  void ReflectorTag();
};

struct GameSessionResources {
  ResourceRef briefingSpeechResourceName;
  ResourceRef successSpeechResourceName;
  ResourceRef failureSpeechResourceName;
  ResourceRef courtMarshallSpeechResourceName;
  std::string briefingText;
  std::string objectivesText;
  std::string successText;
  std::string failureText;
  std::string courtMarshallText;
  void ReflectorTag();
};

struct GameSessionCampaign {
  float parTime;
  float slBestTime;
  void ReflectorTag();
};

struct GameSession : Resource {
  std::vector<std::string> globalScriptsExcluded;
  GameSessionFilesDirs filesDirs;
  GameSessionResources resources;
  GameSessionCampaign campaign;
  GameSessionCampaign levelAttack;
};

enum UIUNLOCKABLE {
  UIUNLOCKABLE_TYPE_NONE,
  UIUNLOCKABLE_TYPE_IMAGE,
  UIUNLOCKABLE_TYPE_MOVIE,
  UIUNLOCKABLE_TYPE_LEVEL,
  UIUNLOCKABLE_TYPE_NUM_TYPES,
};

struct UIUnlockableExtra : ResourcePack {
  int32 unlockableExtraId;
  UIUNLOCKABLE unlockableExtraType;
  AFileInfo filename;
  std::string displayString;
  int32 unlockingLevelID;
  std::string unlockableHow;
  uint32 unlockValue;
};

enum GITYPE {
  GITYPE_SINGLEPLAYER,
  GITYPE_MULTIPLAYER,
  GITYPE_SINGLEPLAYER_EXTRAS,
  GITYPE_MULTIPLAYER_EXTRAS,
  GITYPE_NUM_TYPES,
};

struct GameInfoFileDirs {
  std::string directory;
  std::string previewImage;
  void ReflectorTag();
};

struct GameInfo : Resource {
  GITYPE gameInfoType;
  uint32 multiplayerGameType;
  uint32 id;
  std::string displayString;
  bool allowedInLevelAttack;
  bool playableInDemo;
  GameInfoFileDirs filesDirs;
};

struct SettingsGraphics {
  uint32 screenXRes;
  uint32 screenYRes;
  uint32 shaderQuality;
  uint32 textureQuality;
  bool shadows;
  bool softShadows;
  bool graphicsPipeline;
  bool graphicsDynamicLights;
  uint32 effectQuality;
  bool disableSM2;
  void ReflectorTag();
};
struct SettingsPerformance {
  uint32 modelDetail;
  bool adaptivePerformance;
  void ReflectorTag();
};
struct SettingsOther {
  bool glowTrail;
  bool distort;
  void ReflectorTag();
};

struct Settings : Resource {
  SettingsGraphics graphics;
  SettingsPerformance performance;
  SettingsOther other;
};
