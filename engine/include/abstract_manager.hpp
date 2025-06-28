#pragma once
#include <map>
#include <set>
#include <string>

struct SLVariableAbstractRef;
struct Abstract;

struct AbstractManager {
  using AbstractSet = std::set<Abstract *>;
  using RefMap = std::map<std::string, SLVariableAbstractRef *>;

  void RemoveReference(SLVariableAbstractRef *ref);
  Abstract *GetAbstractFromGUID(const std::string &guid);
  RefMap::iterator AddAbstractRef(SLVariableAbstractRef &ref);
  RefMap::iterator CopyAbstractRef(const SLVariableAbstractRef &refIn,
                                   SLVariableAbstractRef &refOut,
                                   const RefMap::iterator &iter);

  void LinkAbstract(Abstract *a2);

  AbstractSet abstracts;
  RefMap refs;
  int field_18;
  int field_1C;
  void *field_20;
  int field_24;
  int field_28;

  static AbstractManager *Get();
};
