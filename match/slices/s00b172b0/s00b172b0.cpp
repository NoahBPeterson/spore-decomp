// match/slices/s00b172b0/s00b172b0.cpp
// Object file: unknown module (falls in the modmap gap, VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- /Isrc/game/include
//
// Tool-shape path for the cTribe tool-authoring code:
//   FUN_00b172b0  build the 9 OBB corners of the tool shape into the SpVector at
//                 +0x48 (resize(9) first); the shape is 15 floats at +0x00.
//   FUN_00b175e0  nearest-object search over two game-data vectors (the found
//                 objects are stored at +0xd0 / +0xd4).
//   FUN_00b17790  refresh: optional clear, rebuild-if-empty, radius (+0xcc),
//                 then nearest-object search if nothing is found yet.
//   FUN_00b17810  contact test of the shape against the nearest object.
//   FUN_00b17c10  collect every object the shape hits into the report vector.
//
// All callees are unnamed in the retail image; the stub structs only exist so the
// compiler emits a `call` at the right address/convention (chk.py links nothing).

#include "game/types.h"
#include <math.h>

// ---- globals (address in the comment) ----
extern void* g_1567e1c;   // 0x1567e1c
extern float g_145d044;   // 0x145d044  FLT_MAX
extern float g_1471064;   // 0x1471064  0.5f
extern float g_13ef54c;   // 0x13ef54c  1.1f
extern float g_167bdb4;   // 0x167bdb4
extern float g_167bdb8;   // 0x167bdb8
extern float g_167bdbc;   // 0x167bdbc

// ---- free callees ----
void* __cdecl SP_NounManager();                          // 0xb3d300
void* __cdecl SP_PlanetModel();                          // 0xb3d350
void* __cdecl FUN_00bcebc0();                            // 0xbcebc0
char  __cdecl FUN_00b16520(void* a, void* b, void* c, void* d, float* out);  // 0xb16520
char  __cdecl FUN_00b16620(void* shape, void* obj, float* out);              // 0xb16620

// ---- stub types ----
struct Vec3 { float x, y, z; };

struct NounRange { int pad; void** begin; void** end; };   // begin @+4, end @+8
struct MemberRange { int** begin; int** end; };            // begin @+0, end @+4

// SP::cGameNounManager::GetGameDataVector (0xb21340): thiscall, 5 args, ret 0x14.
struct cGameNounManager {
  char raw[8];
  NounRange* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);
};

// SP::cPlanetModel::GetRadiusAt (0xb7ef70): thiscall, 1 arg, ret 4.
struct cPlanetModel {
  char raw[0x200];
  float GetRadiusAt(void* shape);
};

// cTribe member-list accessors (0xc8e810 / 0xbd8130): thiscall, no args.
struct cTribeLike {
  char raw[0x340];
  MemberRange* GetMembers();   // returns (char*)this + 0x340
  MemberRange* GetSubList();   // returns (char*)this + 0x308
};

// SpVector<UVector3> at +0x48: resize (0x473810) / erase (0x50f740).
struct SpVectorV3 {
  Vec3* begin;
  Vec3* end;
  void  resize(int n);
  Vec3* erase(Vec3* first, Vec3* last);
};

// The shape object used by the whole slice.
struct ToolShape {
  float      f[15];              // 0x00..0x3b
  char       pad0[0x48 - 0x3c];  // 0x3c..0x47
  SpVectorV3 vec;                // 0x48
  char       pad1[0xcc - 0x50];  // 0x50..0xcb
  float      radius;             // 0xcc
  int        obj0;               // 0xd0
  int        obj1;               // 0xd4
  void FUN_00b172b0();
  void FUN_00b17790(char flag);
};

// Shape sub-object reached through the object vtable (slot 0x6c returns it).
struct SubObj {
  char     pad0[0x84];
  unsigned flags;                // 0x84
  char     pad1[0x258 - 0x88];
  float    f258;                 // 0x258
  float    f25c;                 // 0x25c
};

// Hit report filled by FUN_00b17c10: a void* vector {begin,end,cap} plus a
// float accumulator triple at +0x38, and the grow helper at 0xbab900.
struct HitReport {
  void** begin;                  // 0x00
  void** end;                    // 0x04
  void** cap;                    // 0x08
  char   pad0c[0x38 - 0x0c];
  float  acc[3];                 // 0x38
  void   PushSlot(void** slot, void** val);
};

// Contact point + type result filled by FUN_00b17810 (12-byte Vec3 copy + int).
struct HitResult { Vec3 p; int type; };

// ---- vtable-slot call helpers (emit `call [vt+off]`) ----
typedef void* (__thiscall *FnPtr)(void*);
typedef void  (__thiscall *FnVoid)(void*);
static inline FnPtr  VtP(void* o, int off) { return *(FnPtr*) (*(char**)o + off); }
static inline FnVoid VtV(void* o, int off) { return *(FnVoid*)(*(char**)o + off); }

void FUN_00b175e0(ToolShape* t, Vec3* p);   // 0xb175e0

// ===========================================================================
// @ 0x00b172b0
// Resize the corner vector to 9 and fill the OBB corners.
//   A = f12, B = f13, t = B*A
//   s9/s10/s11 = f9*t / f10*t / f11*t
//   u = f14*A ; P/Q/R = A*f3+f0 / f1+f4*A / f2+f5*A
//   c* = P/Q/R - f6/f7/f8*u ; d* = P/Q/R + f6/f7/f8*u
// ===========================================================================
void ToolShape::FUN_00b172b0()
{
  vec.resize(9);

  float A = f[12];
  float B = f[13];
  float t0 = B * A;
  float s9  = f[9]  * t0;
  float s10 = f[10] * t0;
  float s11 = f[11] * t0;
  float u   = f[14] * A;
  float P = A * f[3] + f[0];
  float Q = f[1] + f[4] * A;
  float R = f[2] + f[5] * A;
  float c6 = P - f[6] * u, c7 = Q - f[7] * u, c8 = R - f[8] * u;
  float d6 = P + f[6] * u, d7 = Q + f[7] * u, d8 = R + f[8] * u;

  Vec3* e = vec.begin;
  e[6].x = c6 - s9;  e[6].y = c7 - s10;  e[6].z = c8 - s11;
  e[8].x = c6 + s9;  e[8].y = c7 + s10;  e[8].z = c8 + s11;
  e[0].x = d6 - s9;  e[0].y = d7 - s10;  e[0].z = d8 - s11;
  e[2].x = d6 + s9;  e[2].y = d7 + s10;  e[2].z = d8 + s11;
  e[4].x = P;        e[4].y = Q;         e[4].z = R;
  e[7].x = c6;       e[7].y = c7;        e[7].z = c8;
  e[1].x = d6;       e[1].y = d7;        e[1].z = d8;
  e[3].x = P - s9;   e[3].y = Q - s10;   e[3].z = R - s11;
  e[5].x = P + s9;   e[5].y = Q + s10;   e[5].z = R + s11;
}

// ===========================================================================
// @ 0x00b175e0
// Nearest-object search over two game-data vectors; the best objects are stored
// at +0xd4 / +0xd0.  The object position comes from vtable slot 0x2c on the
// sub-object at obj+0x120.
// ===========================================================================
void FUN_00b175e0(ToolShape* t, Vec3* p)
{
  float best1 = g_145d044;
  int res1 = 0;
  cGameNounManager* nm = (cGameNounManager*)SP_NounManager();
  NounRange* r1 = nm->GetGameDataVector((void*)0xcd7d10, (void*)0xd3d420,
                                        (void*)0xaccbb0, (void*)0xb1e500,
                                        (void*)0x18c6d19);
  for (void** it = r1->begin; it != r1->end; ++it) {
    int obj = (int)*it;
    Vec3* o = (Vec3*)VtP((char*)obj + 0x120, 0x2c)((char*)obj + 0x120);
    float dx = o->x - p->x;
    float dz = o->z - p->z;
    float dy = o->y - p->y;
    float d = dx * dx + dz * dz + dy * dy;
    if (best1 > d) { best1 = d; res1 = obj; }
  }

  float best2 = g_145d044;
  int res2 = 0;
  cGameNounManager* nm2 = (cGameNounManager*)SP_NounManager();
  NounRange* r2 = nm2->GetGameDataVector((void*)0xcd7d10, (void*)0xd3d420,
                                         (void*)0xacdff0, (void*)0xb1e500,
                                         (void*)0x18c43e8);
  if (r2->begin != r2->end) {
    for (void** it = r2->begin; it != r2->end; ++it) {
      int obj = (int)*it;
      Vec3* o = (Vec3*)VtP((char*)obj + 0x120, 0x2c)((char*)obj + 0x120);
      float dx = o->x - p->x;
      float dy = o->y - p->y;
      float dz = o->z - p->z;
      float d = dx * dx + dy * dy + dz * dz;
      if (best2 > d) { best2 = d; res2 = obj; }
    }
    t->obj1 = res2;
    t->obj0 = res1;
  } else {
    t->obj1 = 0;
    t->obj0 = res1;
  }
}

// ===========================================================================
// @ 0x00b17790
// Refresh: optionally drop the cached corners, rebuild them when empty, update
// the half-extent radius at +0xcc and re-run the nearest-object search when both
// object slots are still empty.
// ===========================================================================
void ToolShape::FUN_00b17790(char flag)
{
  if (flag)
    vec.erase(vec.begin, vec.end);
  if (vec.begin == vec.end)
    FUN_00b172b0();

  Vec3* v = vec.begin;
  double dx = (double)v[0].x - (double)v[8].x;
  double dy = (double)v[0].y - (double)v[8].y;
  double dz = (double)v[0].z - (double)v[8].z;
  double s = dx * dx;
  s = s + dz * dz;
  s = s + dy * dy;
  radius = (float)(sqrt(s) * g_1471064);

  if (obj1 == 0 && obj0 == 0)
    FUN_00b175e0(this, (Vec3*)this);
}

// ===========================================================================
// @ 0x00b17810
// Contact test of the shape against the nearest object (t->obj1): both the
// +0x48 and +0x60 corners are probed with FUN_00b16520, and finally a scaled
// position sweep.  Returns 1 with *out filled on a hit.
// ===========================================================================
char __cdecl FUN_00b17810(ToolShape* t, HitResult* out)
{
  float cfg = *(float*)((char*)FUN_00bcebc0() + 8);
  cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
  float bound = pm->GetRadiusAt(t) + cfg;

  double dx = (double)t->f[0];
  double dy = (double)t->f[1];
  double dz = (double)t->f[2];
  if (sqrt(dx * dx + dy * dy + dz * dz) >= (double)bound)
    return 0;

  if (t->vec.begin == t->vec.end)
    t->FUN_00b172b0();

  Vec3* v = t->vec.begin;
  double ax = (double)v[0].x - (double)v[8].x;
  double az = (double)v[0].z - (double)v[8].z;
  double ay = (double)v[0].y - (double)v[8].y;
  t->radius = (float)(sqrt(ax * ax + az * az + ay * ay) * 0.5f);

  if (t->obj1 == 0 && t->obj0 == 0)
    FUN_00b175e0(t, (Vec3*)t);

  if (t->obj1 == 0)
    return 0;

  int obj = t->obj1;
  Vec3* o = (Vec3*)VtP((char*)obj + 0x120, 0x2c)((char*)obj + 0x120);
  SubObj* sub = (SubObj*)VtP((void*)obj, 0x6c)((void*)obj);

  unsigned fl = sub->flags;
  if ((fl & 0x10) != 0 && (fl & 0x20) == 0)
    return 0;

  float f3 = sub->f258;
  float f2 = sub->f25c;
  void* edi = (char*)sub + 0x34;
  VtV(edi, 0x68)(edi);

  Vec3* e = t->vec.begin;
  float lax = e[6].x - o->x, lay = e[6].y - o->y, laz = e[6].z - o->z;
  float lbx = e[8].x - o->x, lby = e[8].y - o->y, lbz = e[8].z - o->z;
  double len1 = sqrt((double)lay * lay + ((double)laz * laz + (double)lax * lax));
  double len2 = sqrt((double)lbx * lbx + ((double)lby * lby + (double)lbz * lbz));

  bool hitA = ((double)f2 > len1) && ((float)len1 > f3);
  bool hitB = ((double)f2 > len2) && ((float)len2 > f3);

  if (hitA || hitB) {
    float contact[3];
    if (FUN_00b16520(edi, &e[6], &e[8], g_1567e1c, contact)) {
      if (out) { out->p = *(Vec3*)contact; out->type = 1; }
      return 1;
    }
    if (FUN_00b16520(edi, &e[8], &e[6], g_1567e1c, contact)) {
      if (out) { out->p = *(Vec3*)contact; out->type = 2; }
      return 1;
    }
    if (FUN_00b16520(edi, t, &e[7], g_1567e1c, contact)) {
      if (out) { out->p = *(Vec3*)contact; out->type = 4; }
      return 1;
    }

    float ox = o->x - t->f[0], oy = o->y - t->f[1], oz = o->z - t->f[2];
    double dist = sqrt((double)ox * ox + ((double)oy * oy + (double)oz * oz));
    if (dist < (double)f2 && (double)f3 < dist) {
      float scaled[3];
      scaled[0] = t->f[0] * g_13ef54c;
      scaled[1] = t->f[1] * g_13ef54c;
      scaled[2] = t->f[2] * g_13ef54c;
      if (FUN_00b16520(edi, scaled, t, g_1567e1c, contact)) {
        if (FUN_00b16520(edi, o, t, g_1567e1c, contact)) {
          if (out) { out->p = *(Vec3*)contact; out->type = 3; }
          return 1;
        }
      }
    }
  }

  return 0;
}

// Shared push_back of a refcounted shape pointer into the report vector, then
// accumulate the contact point.  AddRef = vt[0xbc], Release = vt[0xc0].
#define PUSH_HIT(o, p_, loc) do {                            \
    void* ref_ = (p_);                                       \
    if (ref_) VtV(ref_, 0xbc)(ref_);                         \
    if ((o)->end < (o)->cap) {                               \
      void** slot_ = (o)->end;                               \
      (o)->end = slot_ + 1;                                  \
      if (slot_) { *slot_ = ref_;                            \
        if (ref_) VtV(ref_, 0xbc)(ref_); }                   \
    } else {                                                 \
      (o)->PushSlot((o)->end, &ref_);                        \
    }                                                        \
    if (ref_) VtV(ref_, 0xc0)(ref_);                         \
    (o)->acc[0] += (loc)[0];                                 \
    (o)->acc[1] += (loc)[1];                                 \
    (o)->acc[2] += (loc)[2];                                 \
  } while (0)

// ===========================================================================
// @ 0x00b17c10
// Hit collection: walk the tribe members, the tribe sub-list, the +0xd0
// object (its vtable slot 0xac result and its slot 0xbc list) and finally one
// game-data vector, testing every candidate with FUN_00b16620 and pushing the
// hits into *out.  Returns 1 when anything was collected.
// ===========================================================================
char __cdecl FUN_00b17c10(ToolShape* t, HitReport* out)
{
  float cfg = *(float*)((char*)FUN_00bcebc0() + 8);
  cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
  float bound = pm->GetRadiusAt(t) + cfg;

  double dx = (double)t->f[0];
  double dy = (double)t->f[1];
  double dz = (double)t->f[2];
  if (sqrt(dx * dx + dy * dy + dz * dz) >= (double)bound)
    goto tail;

  if (t->vec.begin == t->vec.end)
    t->FUN_00b172b0();

  {
    Vec3* v = t->vec.begin;
    double ax = (double)v[0].x - (double)v[8].x;
    double az = (double)v[0].z - (double)v[8].z;
    double ay = (double)v[0].y - (double)v[8].y;
    t->radius = (float)(sqrt(ax * ax + az * az + ay * ay) * 0.5f);
  }

  if (t->obj1 == 0 && t->obj0 == 0)
    FUN_00b175e0(t, (Vec3*)t);

  if (out) {
    out->acc[0] = g_167bdb4;
    out->acc[1] = g_167bdb8;
    out->acc[2] = g_167bdbc;
  }

  if (t->obj1 != 0) {
    cTribeLike* obj = (cTribeLike*)t->obj1;

    MemberRange* mem = obj->GetMembers();
    for (int** it = mem->begin; it != mem->end; ++it) {
      int m = (int)*it;
      void* shape = m ? (void*)((char*)m + 0x34) : 0;
      float local[3];
      if (FUN_00b16620(t, shape, local)) {
        if (!out) return 1;
        PUSH_HIT(out, shape, local);
      }
    }

    MemberRange* sub = obj->GetSubList();
    for (int** it = sub->begin; it != sub->end; ++it) {
      int e = (int)*it;
      unsigned fl = *(unsigned*)((char*)e + 0xc0);
      if ((fl & 0x10) != 0 && (fl & 0x20) == 0)
        continue;
      void* shape = (void*)((char*)e + 0x70);
      float local[3];
      if (FUN_00b16620(t, shape, local)) {
        if (!out) return 1;
        PUSH_HIT(out, shape, local);
      }
    }
  }

  if (t->obj0 != 0) {
    void* o0 = (void*)t->obj0;

    void* x = VtP(o0, 0xac)(o0);
    void* shape = x ? (void*)((char*)x + 0x34) : 0;
    {
      float local[3];
      if (FUN_00b16620(t, shape, local)) {
        if (!out) return 1;
        PUSH_HIT(out, shape, local);
      }
    }

    MemberRange* list = (MemberRange*)VtP(o0, 0xbc)(o0);
    for (int** it = list->begin; it != list->end; ++it) {
      int m = (int)*it;
      void* sh = m ? (void*)((char*)m + 0x34) : 0;
      float local[3];
      if (FUN_00b16620(t, sh, local)) {
        if (!out) return 1;
        PUSH_HIT(out, sh, local);
      }
    }
  }

  {
    cGameNounManager* nm = (cGameNounManager*)SP_NounManager();
    NounRange* r = nm->GetGameDataVector((void*)0xcd7d10, (void*)0xd3d420,
                                         (void*)0xae72d0, (void*)0xb1e500,
                                         (void*)0x18c6de8);
    for (void** it = r->begin; it != r->end; ++it) {
      int e = (int)*it;
      void* shape = e ? (void*)((char*)e + 0x34) : 0;
      float local[3];
      if (FUN_00b16620(t, shape, local)) {
        if (!out) return 1;
        PUSH_HIT(out, shape, local);
      }
    }
  }

tail:
  if (out != 0 && out->begin != out->end)
    return 1;
  return 0;
}
