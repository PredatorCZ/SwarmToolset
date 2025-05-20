#include "imgui.h"
#include "squtils.hpp"
#include <string>
#include <vector>

static char SQIDRAWLIST_TAG[] = "ImDrawList";

static SQInteger ImDrawList_constructor(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }
  if (self != nullptr) {
    return sq_throwerror(v, _SC("invalid ImDrawList object"));
  }

  sq_setinstanceup(v, 1, ImGui::GetWindowDrawList());
  return SQ_OK;
}

static SQInteger ImDrawList_AddBezierCubic(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *p1 = GetVec2(v, 2);
  const ImVec2 *p2 = GetVec2(v, 3);
  const ImVec2 *p3 = GetVec2(v, 4);
  const ImVec2 *p4 = GetVec2(v, 5);
  SQInteger color;
  sq_getinteger(v, 6, &color);
  SQFloat thickness;
  sq_getfloat(v, 7, &thickness);
  SQInteger numSegments = 0;

  if (sq_gettop(v) > 7) {
    sq_getinteger(v, 8, &numSegments);
  }

  dl->AddBezierCubic(*p1, *p2, *p3, *p4, color, thickness, numSegments);

  return 0;
}

static SQInteger ImDrawList_AddBezierQuadratic(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *p1 = GetVec2(v, 2);
  const ImVec2 *p2 = GetVec2(v, 3);
  const ImVec2 *p3 = GetVec2(v, 4);
  SQInteger color;
  sq_getinteger(v, 5, &color);
  SQFloat thickness;
  sq_getfloat(v, 6, &thickness);
  SQInteger numSegments = 0;

  if (sq_gettop(v) > 6) {
    sq_getinteger(v, 7, &numSegments);
  }

  dl->AddBezierQuadratic(*p1, *p2, *p3, color, thickness, numSegments);

  return 0;
}

static SQInteger ImDrawList_AddCircle(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *center = GetVec2(v, 2);
  SQFloat radius;
  sq_getfloat(v, 3, &radius);
  SQInteger color;
  sq_getinteger(v, 4, &color);
  SQInteger numSegments = 0;

  if (sq_gettop(v) > 4) {
    sq_getinteger(v, 5, &numSegments);
  }

  SQFloat thickness = 1;

  if (sq_gettop(v) > 5) {
    sq_getfloat(v, 6, &thickness);
  }

  dl->AddCircle(*center, radius, color, numSegments, thickness);

  return 0;
}

static SQInteger ImDrawList_AddCircleFilled(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *center = GetVec2(v, 2);
  SQFloat radius;
  sq_getfloat(v, 3, &radius);
  SQInteger color;
  sq_getinteger(v, 4, &color);
  SQInteger numSegments = 0;

  if (sq_gettop(v) > 4) {
    sq_getinteger(v, 5, &numSegments);
  }

  dl->AddCircleFilled(*center, radius, color, numSegments);

  return 0;
}

static SQInteger ImDrawList_AddConcavePolyFilled(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);

  SQInteger arrSize = sq_getsize(v, 2);
  std::vector<ImVec2> points;
  points.resize(arrSize);

  sq_pushnull(v);
  while (SQ_SUCCEEDED(sq_next(v, 2))) {
    SQInteger i;
    sq_getinteger(v, -2, &i);
    SQUserPointer valueTag;
    if (SQ_FAILED(sq_gettypetag(v, -1, &valueTag))) {
      return -1;
    }

    if (valueTag != SQIVEC2_TAG) {
      std::string exc("invalid type tag at index: ");
      exc.append(std::to_string(i));
      return sq_throwerror(v, exc.c_str());
    }

    points.at(i) = *GetVec2(v, -1);
    sq_pop(v, 2);
  }

  sq_pop(v, 1);

  arrSize = sq_getsize(v, 3);
  std::vector<ImU32> colors;
  colors.resize(arrSize);

  sq_pushnull(v);
  while (SQ_SUCCEEDED(sq_next(v, 3))) {
    SQInteger i;
    sq_getinteger(v, -2, &i);
    SQInteger col;
    sq_getinteger(v, -1, &col);

    colors.at(i) = col;
    sq_pop(v, 2);
  }

  sq_pop(v, 1);

  dl->AddConcavePolyFilled(points.data(), points.size(), colors.data(), colors.size());

  return 0;
}

static SQInteger ImDrawList_AddLine(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *p1 = GetVec2(v, 2);
  const ImVec2 *p2 = GetVec2(v, 3);
  SQInteger color0;
  sq_getinteger(v, 4, &color0);
  SQInteger color1;
  sq_getinteger(v, 5, &color1);
  SQFloat thickness = 1;
  if (sq_gettop(v) > 5) {
    sq_getfloat(v, 6, &thickness);
  }

  dl->AddLineMultiColor(*p1, *p2, color0, color1, thickness);

  return 0;
}

static SQInteger ImDrawList_AddRect(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *p1 = GetVec2(v, 2);
  const ImVec2 *p2 = GetVec2(v, 3);
  SQInteger color0;
  sq_getinteger(v, 4, &color0);
  SQInteger color1;
  sq_getinteger(v, 5, &color1);
  SQInteger color2;
  sq_getinteger(v, 6, &color2);
  SQInteger color3;
  sq_getinteger(v, 7, &color3);
  SQFloat rounding = 0;
  if (sq_gettop(v) > 7) {
    sq_getfloat(v, 8, &rounding);
  }
  SQInteger flags = 0;
  if (sq_gettop(v) > 8) {
    sq_getinteger(v, 9, &flags);
  }
  SQFloat thickness = 1;
  if (sq_gettop(v) > 9) {
    sq_getfloat(v, 10, &thickness);
  }

  dl->AddRectMultiColor(*p1, *p2, color0, color1, color2, color3, rounding, flags, thickness);

  return 0;
}

static SQInteger ImDrawList_AddRectFilled(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *p1 = GetVec2(v, 2);
  const ImVec2 *p2 = GetVec2(v, 3);
  SQInteger color0;
  sq_getinteger(v, 4, &color0);
  SQInteger color1;
  sq_getinteger(v, 5, &color1);
  SQInteger color2;
  sq_getinteger(v, 6, &color2);
  SQInteger color3;
  sq_getinteger(v, 7, &color3);

  dl->AddRectFilledMultiColor(*p1, *p2, color0, color1, color2, color3);

  return 0;
}

static SQInteger ImDrawList_PathClear(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  dl->PathClear();

  return 0;
}

static SQInteger ImDrawList_PathLineTo(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *pos = GetVec2(v, 2);

  if (sq_gettop(v) > 2) {
      SQInteger color;
      sq_getinteger(v, 3, &color);
      dl->PathLineTo(*pos, color);
      return 0;
  }

  dl->PathLineTo(*pos);

  return 0;
}

static SQInteger ImDrawList_PathLineToMergeDuplicate(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *pos = GetVec2(v, 2);
  SQInteger color;
  sq_getinteger(v, 3, &color);
  dl->PathLineToMergeDuplicate(*pos, color);

  return 0;
}

static SQInteger ImDrawList_PathFillConvex(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  dl->PathFillConvex();

  return 0;
}

static SQInteger ImDrawList_PathFillConcave(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  dl->PathFillConcave();

  return 0;
}

static SQInteger ImDrawList_PathStroke(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  SQInteger flags = 0;
  if (sq_gettop(v) > 1) {
    sq_getinteger(v, 2, &flags);
  }

  SQFloat thickness = 1;
  if (sq_gettop(v) > 2) {
    sq_getfloat(v, 3, &thickness);
  }

  dl->PathStroke(flags, thickness);

  return 0;
}

static SQInteger ImDrawList_PathArcTo(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *center = GetVec2(v, 2);
  SQFloat radius;
  sq_getfloat(v, 3, &radius);
  SQFloat amin;
  sq_getfloat(v, 4, &amin);
  SQFloat amax;
  sq_getfloat(v, 5, &amax);

  SQInteger numSegments = 0;
  if (sq_gettop(v) > 5) {
    sq_getinteger(v, 6, &numSegments);
  }


  dl->PathArcTo(*center, radius, amin, amax, numSegments);

  return 0;
}

static SQInteger ImDrawList_PathEllipticalArcTo(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *center = GetVec2(v, 2);
  const ImVec2 *radius = GetVec2(v, 3);
  SQFloat rot;
  sq_getfloat(v, 4, &rot);
  SQFloat amin;
  sq_getfloat(v, 5, &amin);
  SQFloat amax;
  sq_getfloat(v, 6, &amax);

  SQInteger numSegments = 0;
  if (sq_gettop(v) > 6) {
    sq_getinteger(v, 7, &numSegments);
  }

  dl->PathEllipticalArcTo(*center, *radius, rot, amin, amax, numSegments);

  return 0;
}

static SQInteger ImDrawList_PathArcToFast(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *center = GetVec2(v, 2);
  SQFloat radius;
  sq_getfloat(v, 3, &radius);
  SQFloat amin;
  sq_getfloat(v, 4, &amin);
  SQFloat amax;
  sq_getfloat(v, 5, &amax);

  dl->PathArcToFast(*center, radius, amin, amax);

  return 0;
}

static SQInteger ImDrawList_PathRect(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *p1 = GetVec2(v, 2);
  const ImVec2 *p2 = GetVec2(v, 3);
  SQInteger color0;
  sq_getinteger(v, 4, &color0);
  SQInteger color1;
  sq_getinteger(v, 5, &color1);
  SQInteger color2;
  sq_getinteger(v, 6, &color2);
  SQInteger color3;
  sq_getinteger(v, 7, &color3);

  SQFloat rounding = 0;
  if (sq_gettop(v) > 7) {
    sq_getfloat(v, 8, &rounding);
  }

  SQInteger flags = 0;
  if (sq_gettop(v) > 8) {
    sq_getinteger(v, 9, &flags);
  }

  dl->PathRect(*p1, *p2, color0, color1, color2, color3, rounding, flags);

  return 0;
}

static SQInteger ImDrawList_PushColorArea(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *p1 = GetVec2(v, 2);
  const ImVec2 *p2 = GetVec2(v, 3);
  SQInteger color0;
  sq_getinteger(v, 4, &color0);
  SQInteger color1;
  sq_getinteger(v, 5, &color1);
  SQInteger color2;
  sq_getinteger(v, 6, &color2);
  SQInteger color3;
  sq_getinteger(v, 7, &color3);

  dl->PushColor(*p1, *p2, color0, color1, color2, color3);

  return 0;
}

static SQInteger ImDrawList_PushColor(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  SQInteger color;
  sq_getinteger(v, 2, &color);

  dl->PushColor(color);

  return 0;
}

static SQInteger ImDrawList_PopColor(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);

  dl->PopColor();

  return 0;
}

static SQInteger ImDrawList_PathBezierCubicCurveTo(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *p1 = GetVec2(v, 2);
  const ImVec2 *p2 = GetVec2(v, 3);
  const ImVec2 *p3 = GetVec2(v, 4);

  SQInteger numSegments = 0;
  if (sq_gettop(v) > 4) {
    sq_getinteger(v, 5, &numSegments);
  }

  dl->PathBezierCubicCurveTo(*p1, *p2, *p3, numSegments);

  return 0;
}

static SQInteger ImDrawList_PathBezierQuadraticCurveTo(HSQUIRRELVM v) {
  SQUserPointer self = nullptr;
  if (SQ_FAILED(sq_getinstanceup(v, 1, &self, SQIDRAWLIST_TAG, SQFalse))) {
    return sq_throwerror(v, _SC("invalid type tag"));
  }

  ImDrawList *dl = static_cast<ImDrawList *>(self);
  const ImVec2 *p1 = GetVec2(v, 2);
  const ImVec2 *p2 = GetVec2(v, 3);

  SQInteger numSegments = 0;
  if (sq_gettop(v) > 3) {
    sq_getinteger(v, 4, &numSegments);
  }

  dl->PathBezierQuadraticCurveTo(*p1, *p2, numSegments);

  return 0;
}

static const SQRegFunction ImDrawList_methods[] = {
    {"constructor", ImDrawList_constructor, 1, "x"},
    {"AddBezierCubic", ImDrawList_AddBezierCubic, -6, "xxxxxini"},
    {"AddBezierQuadratic", ImDrawList_AddBezierQuadratic, -5, "xxxxini"},
    {"AddCircle", ImDrawList_AddCircle, -4, "xxniin"},
    {"AddCircleFilled", ImDrawList_AddCircleFilled, -4, "xxnii"},
    {"AddConcavePolyFilled", ImDrawList_AddConcavePolyFilled, 3, "xaa"},
    {"AddLine", ImDrawList_AddLine, -4, "xxxiin"},
    {"AddRect", ImDrawList_AddRect, -7, "xxxiiiinin"},
    {"AddRectFilled", ImDrawList_AddRectFilled, 7, "xxxiiii"},
    {"PathClear", ImDrawList_PathClear, 1, "x"},
    {"PathLineTo", ImDrawList_PathLineTo, -2, "xxi"},
    {"PathLineToMergeDuplicate", ImDrawList_PathLineToMergeDuplicate, 3, "xxi"},
    {"PathFillConvex", ImDrawList_PathFillConvex, 1, "x"},
    {"PathFillConcave", ImDrawList_PathFillConcave, 1, "x"},
    {"PathStroke", ImDrawList_PathStroke, -1, "xin"},
    {"PathArcTo", ImDrawList_PathArcTo, -5, "xxnnni"},
    {"PathArcToFast", ImDrawList_PathArcToFast, 5, "xxnnn"},
    {"PathEllipticalArcTo", ImDrawList_PathEllipticalArcTo, -6, "xxxnnni"},
    {"PathBezierCubicCurveTo", ImDrawList_PathBezierCubicCurveTo, -4, "xxxxi"},
    {"PathBezierQuadraticCurveTo", ImDrawList_PathBezierQuadraticCurveTo, -3, "xxxi"},
    {"PathRect", ImDrawList_PathRect, -7, "xxxiiiini"},
    {"PushColorArea", ImDrawList_PushColorArea, 7, "xxxiiii"},
    {"PopColorArea", ImDrawList_PopColor, 1, "x"},
    {"PushColor", ImDrawList_PushColor, 2, "xi"},
    {"PopColor", ImDrawList_PopColor, 1, "x"},
};

void sqigui_register_ImDrawList(HSQUIRRELVM v) {
  /* +1 */ sq_pushstring(v, _SC(SQIDRAWLIST_TAG));
  /* +1 */ sq_newclass(v, SQFalse);
  /* +0 */ sq_settypetag(v, -1, SQIDRAWLIST_TAG);

  LoadMethods(v, ImDrawList_methods, sizeofa(ImDrawList_methods));

  /* -2 */ sq_newslot(v, -3, SQFalse);
}
