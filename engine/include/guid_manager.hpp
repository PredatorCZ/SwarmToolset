#pragma once
#include <map>
#include <string>

struct Abstract;

struct GUIDManager {
  std::map<std::string, Abstract *> items;

  // return true if guid was added, false if already exists
  bool Add(const std::string &guid, Abstract *abstract) {
    return items.emplace(guid, abstract).second;
  }

  void Remove(Abstract *abstract);

  void GetGUID(Abstract *abstract, std::string &outGuid);

  static GUIDManager *Get();
};
