#pragma once
#include <list>

struct Watcher;

struct Watchable {
    virtual ~Watchable() = default;
    std::list<Watcher*> watchers; // might be set
};
