#pragma once

struct AudioPlayable;
struct AIEntity;

struct SoundManager {
  bool AddAudio(AudioPlayable *audioPlayable, int flags, AIEntity *entity, int rank);
  void AddAudio(AudioPlayable *audioPlayable, int flags, double startTime, AIEntity *entity, int rank);
  void RemoveAudio(AudioPlayable *audioPlayable);

  static SoundManager *Get();

  // std_tree unkTree;
  // std_tree unkList0;
  // std_tree unkList1;
  // std_tree_node_head *field_24;
  char field_28;
  int field_2C;
  // std_tree soundGroups;
};
