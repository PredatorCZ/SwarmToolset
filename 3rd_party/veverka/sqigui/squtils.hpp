#pragma once
#include "imgui.h"
#include <squirrel.h>

template <size_t N> void sq_pushstring(HSQUIRRELVM v, const char (&str)[N]) {
  sq_pushstring(v, str, N - 1);
}

template <class C, size_t N> constexpr size_t sizeofa(const C (&)[N]) {
  return N;
}

inline void LoadMethods(HSQUIRRELVM v, const SQRegFunction *methods, size_t numItems) {
  for (size_t i = 0; i < numItems; i++) {
    const SQRegFunction &m = methods[i];
    /* +1 */ sq_pushstring(v, m.name, -1);
    /* +1 */ sq_newclosure(v, m.f, 0);
    /* +0 */ sq_setparamscheck(v, m.nparamscheck, m.typemask);
    /* +0 */ sq_setnativeclosurename(v, -1, m.name);
    /* -2 */ sq_newslot(v, -3, SQFalse);
  }
}

inline char SQIVEC2_TAG[] = "ImVec2";

inline const ImVec2 *GetVec2(HSQUIRRELVM v, SQInteger idx) {
  SQUserPointer self = nullptr;
  sq_getinstanceup(v, idx, &self, SQIVEC2_TAG, SQFalse);
  return static_cast<const ImVec2 *>(self);
}
