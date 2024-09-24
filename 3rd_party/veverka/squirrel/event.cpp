#include "sqpcheader.h"
#include <chrono>
#include <list>
#include <thread>

#include "sqstdaux.h"

template <size_t N> void sq_pushstring(HSQUIRRELVM v, const char (&str)[N]) {
  sq_pushstring(v, str, N - 1);
}

struct Event {
  virtual ~Event() = default;
  virtual void OnExecute() = 0;
};

struct ScriptedEvent;

std::list<ScriptedEvent *> events;

struct ScriptedEvent : Event {
  static inline unsigned TAG = 0;
  static inline const char ON_EXECUTE[] = "OnExecute";

  ScriptedEvent(HSQUIRRELVM v_, float delay) : v(v_) {
    printf("Creating ScriptedEvent with %f delay.\n", delay);
    endTime = std::chrono::system_clock::now() +
              std::chrono::milliseconds(int64_t(delay * 1000));
    events.emplace_back(this);
  }

  void OnExecute() override {
    sq_pushregistrytable(v);
    sq_pushstring(v, "ST_EVENTS");

    if (SQ_FAILED(sq_get(v, -2))) {
      printf("ST_EVENTS doesn't exists in registry!\n");
    }

    sq_remove(v, -2); // remove registry table
    sq_pushuserpointer(v, this);
    if (SQ_FAILED(sq_get(v, -2))) {
      printf("Event doesn't exists in ST_EVENTS!\n");
    }

    sq_remove(v, -2); // remove ST_EVENTS
    if (SQ_FAILED(sq_getbyhandle(v, -1, &onExecuteHandle))) {
        printf("Cannot find handle\n");
    }
    sq_push(v, -2);

    if (SQ_FAILED(sq_call(v, 1, SQFalse, SQFalse))) {
      printf("sq_call failed\n");
    }
    sq_settop(v, 1);
  }

  std::chrono::time_point<std::chrono::system_clock> endTime;
  HSQUIRRELVM v;
  HSQMEMBERHANDLE onExecuteHandle;

  ~ScriptedEvent() {}
};

extern "C" void PollEvents() {
  auto time = std::chrono::system_clock::now();
  for (auto event : events) {
    if (event->v && event->endTime <= time) {
      event->OnExecute();
      event->v = nullptr;
    }
  }
}

static SQInteger ScriptedEvent_constructor(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(
          v, 1, &self, (SQUserPointer)&ScriptedEvent::TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }
  if (self != nullptr) {
    return sq_throwerror(v, _SC("invalid Event object"));
  }

  HSQMEMBERHANDLE onExecuteHandle;
  sq_getclass(v, 1);
  sq_pushstring(v, "OnExecute");
  if (SQ_FAILED(sq_getmemberhandle(v, -2, &onExecuteHandle))) {
    return sq_throwerror(v, _SC("expected OnExecute"));
  }

  SQFloat fDelay = 0.f;
  if (SQ_FAILED(sq_getfloat(v, 2, &fDelay))) {
    return sq_throwerror(v, _SC("expected float"));
  }

  ScriptedEvent *rex = new ScriptedEvent(v, fDelay);
  rex->onExecuteHandle = onExecuteHandle;

  sq_pushregistrytable(v);
  sq_pushstring(v, "ST_EVENTS");

  if (SQ_FAILED(sq_get(v, -2))) {
    sq_pushstring(v, "ST_EVENTS");
    sq_newtable(v);
    if (SQ_FAILED(sq_newslot(v, -3, SQFalse))) {
      return sq_throwerror(v, _SC("Couldn't register ST_EVENTS"));
    }

    sq_pushstring(v, "ST_EVENTS");
    sq_get(v, -2);
  }

  sq_pushuserpointer(v, rex);
  sq_push(v, 1);
  if (SQ_FAILED(sq_newslot(v, -3, SQFalse))) {
    return sq_throwerror(v, _SC("Couldn't register event"));
  }
  sq_settop(v, 1);

  return 0;
}

static const SQRegFunction ScriptedEvent_methods[] = {
    {"constructor", ScriptedEvent_constructor, 0, nullptr},
};

extern "C" void sqst_register_event(HSQUIRRELVM v) {
  sq_pushstring(v, _SC("Event"), -1);
  sq_newclass(v, SQFalse);
  sq_settypetag(v, -1, (SQUserPointer)&ScriptedEvent::TAG);
  for (auto &m : ScriptedEvent_methods) {
    sq_pushstring(v, m.name, -1);
    sq_newclosure(v, m.f, 0);
    sq_setparamscheck(v, m.nparamscheck, m.typemask);
    sq_setnativeclosurename(v, -1, m.name);
    sq_newslot(v, -3, SQFalse);
  }
  sq_newslot(v, -3, SQFalse);
}
