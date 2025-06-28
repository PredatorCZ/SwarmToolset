#include "guid_manager.hpp"
#include "abstract.hpp"

void GUIDManager::Remove(Abstract *abstract) {
    auto found = items.find(*abstract->GetGUID());

    if (found != items.end()) {
        items.erase(found);
    }
}
