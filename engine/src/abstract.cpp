#include "abstract.hpp"
#include "abstract_manager.hpp"
#include "guid_manager.hpp"

std::string *Abstract::GetGUID() {
  if (!guid) {
    guid = new std::string();
    GUIDManager::Get()->GetGUID(this, *guid);
  }

  return guid;
}

bool Abstract::RegisterAs(const std::string &newGuid) {
  if (guid) {
    if (*guid == newGuid) {
      return true;
    }
  } else {
    guid = new std::string();
  }

  if (!GUIDManager::Get()->Add(newGuid, this)) {
    return false;
  }

  GUIDManager::Get()->Remove(this);
  *guid = newGuid;
  AbstractManager::Get()->LinkAbstract(this);

  return true;
}
