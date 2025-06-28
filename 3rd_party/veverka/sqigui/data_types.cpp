#include "squtils.hpp"
#include <cstdio>

static SQInteger ImVec2_destructor(SQUserPointer p,
                                   SQInteger SQ_UNUSED_ARG(size)) {
  delete (ImVec2 *)p;
  return 1;
}

static SQInteger ImVec2_constructor(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIVEC2_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }
  if (self != nullptr) {
    return sq_throwerror(v, _SC("invalid ImVec2 object"));
  }

  ImVec2 *rex = new ImVec2();
  const SQInteger numOps = sq_gettop(v);

  if (numOps > 1) {
    sq_getfloat(v, 2, &rex->x);
    if (numOps > 2) {
      sq_getfloat(v, 3, &rex->y);
    } else {
      rex->y = rex->x;
    }
  }

  sq_setinstanceup(v, 1, rex);
  sq_setreleasehook(v, 1, ImVec2_destructor);
  return SQ_OK;
}

static SQInteger ImVec2_tostring(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIVEC2_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImVec2 *vec = static_cast<ImVec2 *>(self);

  char buffer[0x40]{};
  snprintf(buffer, sizeof(buffer), "[ %g, %g ]", vec->x, vec->y);
  sq_pushstring(v, buffer);
  return 1;
}

template <void (*fn)(float &, float)>
static SQInteger ImVec2_op(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIVEC2_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  sq_clone(v, 1);
  sq_getinstanceup(v, -1, &self, SQIVEC2_TAG, SQFalse);
  ImVec2 *vec = static_cast<ImVec2 *>(self);

  const SQObjectType fstType = sq_gettype(v, 2);

  if (fstType & SQObjectType::OT_INTEGER) {
    SQFloat flt;
    sq_getfloat(v, 2, &flt);
    fn(vec->x, flt);
    fn(vec->y, flt);
  } else {
    if (SQ_FAILED(sq_getinstanceup(v, 2, &self, SQIVEC2_TAG, SQFalse))) {
      return sq_throwerror(v, _SC("invalid type tag"));
    }

    ImVec2 *oVec = static_cast<ImVec2 *>(self);
    fn(vec->x, oVec->x);
    fn(vec->y, oVec->y);
  }

  return 1;
}

static SQInteger ImVec2_cloned(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 2, &self, SQIVEC2_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImVec2 *vec = new ImVec2(*static_cast<ImVec2 *>(self));
  sq_setinstanceup(v, 1, vec);
  sq_setreleasehook(v, 1, ImVec2_destructor);
  return 0;
}

static SQInteger ImVec2_unm(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIVEC2_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  sq_clone(v, 1);
  sq_getinstanceup(v, -1, &self, SQIVEC2_TAG, SQFalse);
  ImVec2 *vec = static_cast<ImVec2 *>(self);

  vec->x *= -1;
  vec->y *= -1;

  return 1;
}

void op_add(float &a, float b) { a += b; }
void op_sub(float &a, float b) { a -= b; }
void op_mul(float &a, float b) { a *= b; }
void op_div(float &a, float b) { a /= b; }

static const SQRegFunction ImVec2_methods[] = {
    {"constructor", ImVec2_constructor, 0, "xnn"},
    {"_tostring", ImVec2_tostring, 1, "x"},
    {"_cloned", ImVec2_cloned, 2, "xx"},
    {"_add", ImVec2_op<op_add>, 2, "xx|n"},
    {"_sub", ImVec2_op<op_sub>, 2, "xx|n"},
    {"_mul", ImVec2_op<op_mul>, 2, "xx|n"},
    {"_div", ImVec2_op<op_div>, 2, "xx|n"},
    {"_unm", ImVec2_unm, 1, "x"},
};

void sqigui_register_ImVec2(HSQUIRRELVM v) {
  /* +1 */ sq_pushstring(v, _SC(SQIVEC2_TAG));
  /* +1 */ sq_newclass(v, SQFalse);
  /* +0 */ sq_settypetag(v, -1, SQIVEC2_TAG);

  LoadMethods(v, ImVec2_methods, sizeofa(ImVec2_methods));

  /* -2 */ sq_newslot(v, -3, SQFalse);
}
