#pragma once

#include <cstdint>
#include <set>
#include <string>

struct MultiplayerNetObject;
struct SLVariableSet;
struct SLVariableAbstractRef;

struct Abstract {
  // virtual delete()
  virtual void LoadScript() = 0;
  virtual void ToNative() = 0;
  virtual void FromNative() = 0;
  virtual void SaveScript();
  virtual void func_14() {}
  virtual void func_18() {}
  virtual void func_1C() {}

  std::set<SLVariableAbstractRef *>::iterator
  AddReferee(SLVariableAbstractRef &ref);
  bool RegisterAs(const std::string &guid);
  std::string *GetGUID();

  MultiplayerNetObject *GetClientNetObject();
  MultiplayerNetObject *GetServerNetObject();

  int32_t uid;
  std::string *guid;
  SLVariableSet *variables;
  std::set<Abstract>::iterator globalRefMapIter;
  std::set<SLVariableAbstractRef *> referencedBy;
  std::set<Abstract> field_1C;
  bool doNotDelete;
  MultiplayerNetObject *clientNetObject;
  MultiplayerNetObject *serverNetObject;
};
