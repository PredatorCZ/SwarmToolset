#pragma once
#include "watchable.hpp"
#include <list>

struct Watchable;

struct Watcher {
    virtual ~Watcher() = default;
    virtual void func_4();

    std::list<Watchable*> watchables; // might be set
};
