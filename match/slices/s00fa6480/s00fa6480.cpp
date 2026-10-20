// slice s00fa6480 -- SP::cTerrainSphere lighting-region / decal / model helpers.
// Object file: SPTerrain/SPTerrainSphere.obj.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
//   0x00fa6480 SP::cTerrainSphere::AddLightingRegion
//   0x00fa6870 SP::cTerrainSphere::UpdateLightingRegions
//   0x00fa6a50 SP::cTerrainSphere::CreateDecal
//   0x00fa6c60 SP::cTerrainSphere::AddModelFootprint
//   0x00fa6ec0 SP::cTerrainSphere::ClearRelevels
//   0x00fa6f40 SP::cTerrainSphere::ReleaseBackgroundModels
//   0x00fa7010 SP::cTerrainSphere::AddModelsAndEffects
//   0x00fa7220 SP::cTerrainSphere::AddPlayerModification
//   0x00fa73c0 SP::cTerrainSphere::ClearPlayerModifications
#include "types.h"
#include <stddef.h>
#include <intrin.h>
#include <new>

// ---------------------------------------------------------------- externals
void* __cdecl EAAllocate(unsigned n, const char* name, int a, int b, int c, int d); // 0x00f473a0
void  __cdecl EADeallocate(void* p);                                                // 0x00f47380

void* __cdecl FUN_0067dda0(); // 0x0067dda0 scene/decal-id manager
void* __cdecl FUN_0067dd60(); // 0x0067dd60 SP::EffectsManager
void* __cdecl FUN_0067ddd0(); // 0x0067ddd0 effects-manager accessor
void* __cdecl FUN_0067dd80(); // 0x0067dd80 SP::ModelManager

void  __cdecl FUN_00f9f100();                       // 0x00f9f100 cTerrainSphereLightingRegion ctor
void  __cdecl FUN_00f9f950();                       // 0x00f9f950 cLightDecal ctor
void* __cdecl FUN_00f9ada0(void*, void*);           // 0x00f9ada0 direction-through-transform helper
char  __cdecl FUN_00f9abc0();                       // 0x00f9abc0 region overlap predicate
void* __cdecl FUN_00f9b2b0();                       // 0x00f9b2b0 cRelevel builder
void  __cdecl FUN_00f9b1e0();                       // 0x00f9b1e0 cRelevel copy ctor
void  __cdecl FUN_00f9f770(void*, void*, void*);    // 0x00f9f770 CopyRelevels(first,last,dest)
void  __cdecl FUN_00fa47b0();                       // 0x00fa47b0 RelevelVector::DoInsertValue
void  __cdecl FUN_00fa6a00();                       // 0x00fa6a00 relevel push_back
void  __cdecl FUN_00fa3c10();                       // 0x00fa3c10 ApplyModelFootprint
void  __cdecl FUN_00f9a7c0();                      // 0x00f9a7c0 RenderLightingRegion
void  __cdecl FUN_00f99520();                       // 0x00f99520 PinModelsToTerrain
void  __cdecl FUN_00a730c0();                       // 0x00a730c0 vector<T*>::resize
void  __cdecl FUN_00473270();                       // 0x00473270 vector reserve helper
void  __cdecl FUN_00537dc0();                       // 0x00537dc0 cSPTransformOps::Assign
void  __cdecl FUN_0041cb40();                       // 0x0041cb40 Matrix3 copy
void  __cdecl FUN_00576650();                       // 0x00576650 GetImageResource
bool* __cdecl FUN_0041e920();                       // 0x0041e920 Property::GetBool
int*  __cdecl FUN_0041e990();                       // 0x0041e990 Property::GetInt
void* __cdecl FUN_00fa28b0();                       // 0x00fa28b0 decal factory (effect,xform,scale)
void* __cdecl FUN_00fa2920();                       // 0x00fa2920 decal factory w/ belt index
void  __cdecl FUN_00fa23d0();                       // 0x00fa23d0 remove node from region
void* __cdecl FUN_00b96600();                       // 0x00b96600 vector<T*> slow push_back
void  __cdecl FUN_006ba870();                       // 0x006ba870 XForm2::Apply
void  __cdecl FUN_007c4dd0();                       // 0x007c4dd0 cViewer::Init
void  __cdecl FUN_007c3cc0();                       // 0x007c3cc0 cViewer::Clear
void  __cdecl FUN_007c3cb0();                       // 0x007c3cb0 cViewer::SetTexture
void  __cdecl FUN_007c3c20();                       // 0x007c3c20 cViewer::SetClearColor
void  __cdecl FUN_007c4a60();                       // 0x007c4a60 cViewer::SetViewport
bool  __cdecl FUN_006a0ae0(void*, uint32_t, void*, void*); // 0x006a0ae0 vector reserve wrapper
void  __cdecl FUN_00fbaf10();                       // 0x00fbaf10
void  __cdecl FUN_00fbaf50();                       // 0x00fbaf50

// ---------------------------------------------------------------- fn-ptr types
typedef void  (__thiscall *TV0)(void*);
typedef void* (__thiscall *TV0p)(void*);
typedef bool* (__thiscall *TV0bp)(void*);
typedef int*  (__thiscall *TV0ip)(void*);
typedef void  (__thiscall *TV1)(void*, void*);
typedef void  (__thiscall *TV1i)(void*, int);
typedef void  (__thiscall *TV1u)(void*, uint32_t);
typedef void* (__thiscall *TV1p)(void*, void*);
typedef char  (__thiscall *TV1c)(void*, void*);
typedef void  (__thiscall *TV2)(void*, void*, void*);
typedef void* (__thiscall *TV2p)(void*, void*, void*);
typedef char  (__thiscall *TV2c)(void*, uint32_t, void**);
typedef char  (__thiscall *TV3c)(void*, void*, int, void*);
typedef void* (__thiscall *TV3pi)(void*, void*, void*, int);
typedef void* (__thiscall *TV3pf)(void*, void*, void*, float);
typedef void* (__thiscall *TV4pf)(void*, void*, void*, float, int);
typedef void  (__thiscall *TV5pb)(void*, void*, void*, void*, void*, int);
typedef void* (__thiscall *TVo7)(void*, void*, int, int, int, int, int, int);
typedef void  (__thiscall *TV3n)(void*, uint32_t, uint32_t, const char*);
typedef void* (__thiscall *TV3ui)(void*, uint32_t, uint32_t, void*);

// ---------------------------------------------------------------- small types
struct Matrix3 { float m[9]; };
struct XForm2 {                          // SP::cSPTransform, 0x38 bytes
  uint16_t mFlags, mModCount;
  float mX, mY, mZ, mScale;
  Matrix3 mM;
};
struct Color4 { float r, g, b, a; };

class cTerrainSphere {
 public:
  void* AddLightingRegion(void* param);
  void  UpdateLightingRegions(void* param);
  void* CreateDecal(int type, void* def, void* xform, float scale);
  uint32_t AddModelFootprint(const void* xform, void* props);
  void  ClearRelevels();
  void  ReleaseBackgroundModels();
  void  AddModelsAndEffects();
  uint32_t AddPlayerModification(void* a, void* b, void* c);
  void  ClearPlayerModifications();
};

#define SELF      ((char*)this)
#define PTRV(off) (*(void**)(SELF + (off)))
#define INTV(off) (*(int*)(SELF + (off)))
#define U8V(off)  (*(uint8_t*)(SELF + (off)))

// reserve() result: {object-pointer, element-count} filled by 0x006a0ae0.
struct ReserveOut { void* mData; int mCount; };

// ================================================================ 0x00fa6480
// @ 0x00fa6480
void* cTerrainSphere::AddLightingRegion(void* param) {
  char* region = (char*)EAAllocate(0x1d8, "Terrain/Sphere/cTerrainSphereLightingRegion", 0, 0, 0, 0);
  region = region ? (char*)((TV0p)FUN_00f9f100)(region) : 0;
  *(uint8_t*)(region + 0x1d4) = 1;
  *(void**)(region + 0x1d0) = this;

  void* mgr = FUN_0067dda0();
  int prev = *(int*)0x15b14ec;
  *(int*)0x15b14ec = prev + 1;
  uint32_t ids[2];
  uint32_t* pr = (uint32_t*)((TVo7)((void**)*(void***)mgr)[4])(mgr, ids, 0x80, 0x80, 0x15, 0, prev, 0);
  uint32_t id0 = pr[0];
  uint32_t id1 = pr[1];
  *(uint32_t*)(region + 0x1b0) = id0;
  *(uint32_t*)(region + 0x1b4) = id1;
  ((TV3n)((void**)*(void***)mgr)[18])(mgr, id0, id1, "TerrainDecalLightingRegion");
  if (*(uint32_t*)(region + 0x1b4) != 0xffffffffu) {
    int imgId = (int)(intptr_t)((TV3ui)((void**)*(void***)mgr)[7])(mgr, id0, id1, 0);
    ((TV1i)FUN_00576650)(region + 0x1b8, imgId);
  }

  char* viewer = region + 4;
  ((TV1u)FUN_007c4dd0)(viewer, 1);
  ((TV1u)FUN_007c3cc0)(viewer, 0);
  char* img = *(char**)(region + 0x1b8);
  if ((img[4] & 1) == 0) {
    void* o = FUN_0067dd60();
    ((TV1)((void**)*(void***)o)[13])(o, img);
  }
  ((TV1i)FUN_007c3cb0)(viewer, *(int*)img);
  Color4 col;
  col.r = 0.0f; col.g = 0.0f; col.b = 0.0f; col.a = *(float*)0x1485720;
  ((TV1)FUN_007c3c20)(viewer, &col);
  int rect[4] = {0, 0, 0x80, 0x80};
  ((TV1)FUN_007c4a60)(viewer, rect);

  char* p = (char*)((TV3pf)FUN_00fa28b0)(this, img, param, 0.0f);
  *(int*)region = *(int*)(p + 0x74);
  *(uint32_t*)(p + 0xb8) |= 2;
  float f = *(float*)(p + 0x114);
  *(int*)(p + 0x70) = 0;
  Matrix3 M;
  M.m[0] = *(float*)(p + 0x108); M.m[1] = *(float*)(p + 0x10c); M.m[2] = *(float*)(p + 0x110);
  M.m[3] = *(float*)(p + 0x118); M.m[4] = *(float*)(p + 0x11c); M.m[5] = *(float*)(p + 0x120);
  M.m[6] = *(float*)(p + 0xf8);  M.m[7] = *(float*)(p + 0xfc);  M.m[8] = *(float*)(p + 0x100);
  XForm2* x = (XForm2*)(region + 0x178);
  x->mScale *= f;
  x->mX *= f;
  x->mY *= f;
  x->mZ *= f;
  x->mFlags |= 1;
  ++x->mModCount;
  ((TV1)FUN_006ba870)(x, &M);
  x->mFlags |= 4;
  ++x->mModCount;
  x->mX = *(float*)(p + 0xec);
  x->mY = *(float*)(p + 0xf0);
  x->mZ = *(float*)(p + 0xf4);

  int n = (int)((*(char**)(SELF + 0x2f8) - *(char**)(SELF + 0x2f4)) >> 2);
  for (int i = 0; i < n; ++i) {
    char* node = *(char**)(*(char**)(SELF + 0x2f4) + i * 4);
    if (((TV1c)FUN_00f9abc0)(region, node + 4)) {
      void** e = *(void***)(region + 0x1c0);
      if (e < *(void***)(region + 0x1c4)) {
        *(void***)(region + 0x1c0) = e + 1;
        if (e) *e = node;
      } else {
        void* tmp = node;
        ((TV2)FUN_00b96600)(region + 0x1bc, e, &tmp);
      }
      *(uint8_t*)(region + 0x1d4) = 1;
    }
  }
  void** e2 = *(void***)(SELF + 0x2e4);
  if (e2 < *(void***)(SELF + 0x2e8)) {
    *(void***)(SELF + 0x2e4) = e2 + 1;
    if (e2) *e2 = region;
  } else {
    void* tmp = region;
    ((TV2)FUN_00b96600)(SELF + 0x2e0, e2, &tmp);
  }
  return *(void**)region;
}

// ================================================================ 0x00fa6870
// @ 0x00fa6870
void cTerrainSphere::UpdateLightingRegions(void* param) {
  int n = (int)((*(char**)(SELF + 0x2f8) - *(char**)(SELF + 0x2f4)) >> 2);
  for (int i = 0; i < n; ++i) {
    char* node = *(char**)(*(char**)(SELF + 0x2f4) + i * 4);
    if (node[0x20] == 0) continue;
    int m = (int)((*(char**)(SELF + 0x2e4) - *(char**)(SELF + 0x2e0)) >> 2);
    for (int j = 0; j < m; ++j) {
      char* r = *(char**)(*(char**)(SELF + 0x2e0) + j * 4);
      char c = ((TV1c)FUN_00f9abc0)(r, node + 4);
      int rn = (int)((*(char**)(r + 0x1c0) - *(char**)(r + 0x1bc)) >> 2);
      bool found = false;
      for (int k = 0; k < rn; ++k) {
        if (*(void**)(*(char**)(r + 0x1bc) + k * 4) == node) { found = true; break; }
      }
      if (c == 0) {
        if (found) ((TV1)FUN_00fa23d0)(r, node);
      } else if (!found) {
        void** e = *(void***)(r + 0x1c0);
        if (e < *(void***)(r + 0x1c4)) {
          *(void***)(r + 0x1c0) = e + 1;
          if (e) *e = node;
        } else {
          void* tmp = node;
          ((TV2)FUN_00b96600)(r + 0x1bc, e, &tmp);
        }
        *(uint8_t*)(r + 0x1d4) = 1;
      }
    }
    node[0x20] = 0;
  }
  int m2 = (int)((*(char**)(SELF + 0x2e4) - *(char**)(SELF + 0x2e0)) >> 2);
  for (int i = 0; i < m2; ++i) {
    char* r = *(char**)(*(char**)(SELF + 0x2e0) + i * 4);
    if (r[0x1d4]) ((TV2)FUN_00f9a7c0)(this, r, param);
  }
}

// ================================================================ 0x00fa6a50
// @ 0x00fa6a50
void* cTerrainSphere::CreateDecal(int type, void* def, void* xform, float scale) {
  if (INTV(0x2c) == 0) return 0;
  if (type == 4) {
    char* o = (char*)EAAllocate(0x74, "Terrain/Sphere/cLightDecal", 0, 0, 0, 0);
    o = o ? (char*)((TV0p)FUN_00f9f950)(o) : 0;
    *(int*)(o + 0x68) = 4;
    ((TV1p)FUN_00537dc0)(o, xform);
    *(float*)(o + 0x48) = scale;
    *(int*)(o + 0x6c) = -1;
    *(uint16_t*)(o + 0x70) = 0;
    return o;
  }
  if (type == 5) {
    char* o = (char*)EAAllocate(0x74, "Terrain/Sphere/cLightDecal", 0, 0, 0, 0);
    o = o ? (char*)((TV0p)FUN_00f9f950)(o) : 0;
    *(int*)(o + 0x68) = 5;
    ((TV1p)FUN_00537dc0)(o, xform);
    *(float*)(o + 0x48) = scale;
    void* r = AddLightingRegion(xform);
    *(int*)(o + 0x6c) = (int)(intptr_t)r;
    *(uint16_t*)(o + 0x70) = *(uint16_t*)(o + 2);
    return o;
  }
  uint32_t k0 = *(uint32_t*)def;
  uint32_t k1 = *(uint32_t*)((char*)def + 4);
  void* eff = FUN_0067dd60();
  void* res = ((TV3ui)((void**)*(void***)eff)[8])(eff, k0, k1, 0);
  if (res == 0) {
    eff = FUN_0067dd60();
    res = ((TV3ui)((void**)*(void***)eff)[8])(eff, k0, 0x40010000u, 0);
    if (res == 0) return 0;
  }
  bool bl = ((*(uint8_t*)((char*)def + 0xa) & 4) != 0) || (type == 3);
  int16_t sc = *(int16_t*)((char*)def + 0xc);
  int idx = (int)(float)sc;
  if ((float)sc < (float)idx) --idx;
  if (idx < 0) idx = 0; else if (idx >= 4) idx = 3;
  char* out;
  if (bl) out = (char*)((TV4pf)FUN_00fa2920)(this, res, xform, scale, 3 - idx);
  else    out = (char*)((TV3pf)FUN_00fa28b0)(this, res, xform, scale);
  *(int*)(out + 0x70) = type;
  uint8_t b = *(uint8_t*)((char*)def + 0xa);
  if (b & 1) *(uint32_t*)(out + 0xb8) |= 2;
  else       *(uint32_t*)(out + 0xb8) &= 0xfffffffd;
  if (!(b & 2)) *(uint32_t*)(out + 0xb8) |= 4;
  else          *(uint32_t*)(out + 0xb8) &= 0xfffffffb;
  if (type != 3) *(int*)(out + 4) += 1;
  return out + 8;
}

// ================================================================ 0x00fa6c60
// @ 0x00fa6c60
uint32_t cTerrainSphere::AddModelFootprint(const void* xform, void* props_) {
  if (!props_) return 0;
  char* props = (char*)props_;

  XForm2 lx;
  lx.mFlags = *(const uint16_t*)xform;
  lx.mModCount = *(const uint16_t*)((const char*)xform + 2);
  lx.mX = *(const float*)((const char*)xform + 4);
  lx.mY = *(const float*)((const char*)xform + 8);
  lx.mZ = *(const float*)((const char*)xform + 0xc);
  lx.mScale = *(const float*)((const char*)xform + 0x10);
  ((TV1)FUN_0041cb40)(&lx.mM, (void*)((const char*)xform + 0x14));

  void* prop = 0;
  char c = ((TV2c)((void**)*(void***)props)[9])(props, 0x589e78cu, &prop);
  if (c && *(int16_t*)((char*)prop + 0x12) == 1) {
    bool* b = ((TV0bp)FUN_0041e920)(prop);
    if (*b) {
      float* v = (float*)FUN_00f9ada0(&lx.mM, &prop);
      void* d = ((TV0p)((void**)*(void***)this)[3])(this);
      float f = *(float*)((char*)d + 0x3c) * *(float*)((char*)d + 0x38) + *(float*)((char*)d + 0x34) + *(float*)0x13eb95c;
      float vx = v[0] * f, vy = v[1] * f, vz = v[2] * f;
      lx.mFlags |= 4;
      ++lx.mModCount;
      lx.mX = vx; lx.mY = vy; lx.mZ = vz;
    }
  }

  void* prop2 = 0;
  char c2 = ((TV2c)((void**)*(void***)props)[9])(props, 0xc5ae63edu, &prop2);
  if (c2 && *(int16_t*)((char*)prop2 + 0x12) == 1) {
    bool* b2 = ((TV0bp)FUN_0041e920)(prop2);
    if (*b2) {
      char rel[0xac];
      void* r = ((TV3pi)FUN_00f9b2b0)(rel, (char*)props + 8, &lx, 1);
      ((TV1p)FUN_00fa6a00)(SELF + 0x784, r);
      char* e = *(char**)(SELF + 0x788) - 0xac;
      ((TV5pb)FUN_00fa3c10)(this, &lx, props, 0, e + 0x38, 1);
      *(uint32_t*)(e + 0xa4) &= 0xf7ffffff;
      uint32_t key = *(uint32_t*)(e + 0xa8);
      INTV(0x814) += 1;
      INTV(0x818) += 1;
      return key;
    }
  }

  char rel2[0xac];
  void* r2 = ((TV3pi)FUN_00f9b2b0)(rel2, (char*)props + 8, &lx, 0);
  char* end = *(char**)(SELF + 0x774);
  if (end < *(char**)(SELF + 0x778)) {
    *(char**)(SELF + 0x774) = end + 0xac;
    if (end) ((TV1p)FUN_00f9b1e0)(end, r2);
  } else {
    ((TV2)FUN_00fa47b0)(SELF + 0x770, end, r2);
  }
  char* e2 = *(char**)(SELF + 0x774) - 0xac;
  ((TV5pb)FUN_00fa3c10)(this, &lx, props, 0, e2 + 0x38, 1);
  uint32_t key2 = *(uint32_t*)(e2 + 0xa8);
  INTV(0x814) += 1;
  INTV(0x818) += 1;
  return key2;
}

// ================================================================ 0x00fa6ec0
// @ 0x00fa6ec0
void cTerrainSphere::ClearRelevels() {
  char* b0 = *(char**)(SELF + 0x770);
  char* e0 = *(char**)(SELF + 0x774);
  FUN_00f9f770(e0, e0, b0);
  int d0 = (int)(e0 - b0);
  INTV(0x774) -= (d0 / 0xac) * 0xac;
  _ReadWriteBarrier();

  char* b1 = *(char**)(SELF + 0x784);
  char* e1 = *(char**)(SELF + 0x788);
  FUN_00f9f770(e1, e1, b1);
  int d1 = (int)(e1 - b1);
  INTV(0x788) -= (d1 / 0xac) * 0xac;
  _ReadWriteBarrier();

  INTV(0x814) += 1;
}

// ================================================================ 0x00fa6f40
// @ 0x00fa6f40
void cTerrainSphere::ReleaseBackgroundModels() {
  ReserveOut ro = {0, 0};
  void* mgr = 0;
  char ok = FUN_006a0ae0(PTRV(0x28), 0x3abb0afu, &ro, &mgr);
  if (!ok) return;
  void* eff = FUN_0067ddd0();
  mgr = ((TV1p)((void**)*(void***)eff)[21])(eff, (void*)0x3fbae24);
  ((TV1i)FUN_00a730c0)(SELF + 0x7ec, ro.mCount);
  for (int i = 0, off = 0; i < ro.mCount; ++i, off += 0xc) {
    char** slot = (char**)(*(char**)(SELF + 0x7ec) + i * 4);
    char* e = *slot;
    if (e) {
      *slot = 0;
      ((TV0)((void**)*(void***)e)[1])(e);
    }
    char r = ((TV3c)((void**)*(void***)mgr)[2])(mgr, *(char**)((char*)ro.mData + off), 0, slot);
    if (r) {
      char* e2 = *(char**)(*(char**)(SELF + 0x7ec) + i * 4);
      ((TV1)((void**)*(void***)e2)[2])(e2, 0);
    }
  }
}

// ================================================================ 0x00fa7010
// @ 0x00fa7010
void cTerrainSphere::AddModelsAndEffects() {
  if (U8V(0x76c)) return;
  ReleaseBackgroundModels();

  ReserveOut ro = {0, 0};
  void* mgr = 0;
  char ok = FUN_006a0ae0(PTRV(0x28), 0x40539d4u, &ro, &mgr);
  if (ok) {
    void* eff = FUN_0067ddd0();
    mgr = ((TV1p)((void**)*(void***)eff)[21])(eff, (void*)0x3fbae24);
    ((TV1i)FUN_00a730c0)(SELF + 0x800, ro.mCount);
    for (int i = 0, off = 0; i < ro.mCount; ++i, off += 0xc) {
      char** slot = (char**)(*(char**)(SELF + 0x800) + i * 4);
      char* e = *slot;
      if (e) {
        *slot = 0;
        ((TV0)((void**)*(void***)e)[1])(e);
      }
      char r = ((TV3c)((void**)*(void***)mgr)[2])(mgr, *(char**)((char*)ro.mData + off), 0, slot);
      if (r) {
        char* e2 = *(char**)(*(char**)(SELF + 0x800) + i * 4);
        ((TV1)((void**)*(void***)e2)[2])(e2, 0);
      }
    }
  }

  if (INTV(0x7ac) == 0) {
    U8V(0x76c) = 1;
    return;
  }
  void* mm = FUN_0067dd80();
  mm = ((TV1p)((void**)*(void***)mm)[7])(mm, (void*)0x3fbae24);
  char* vec = SELF + 0x7d8;
  if (*(void**)(vec) == *(void**)(vec + 4)) ((TV1i)FUN_00473270)(vec, INTV(0x7ac));
  for (int i = 0; i < INTV(0x7ac); ++i) {
    char* model = *(char**)(SELF + 0x7b0) + i * 0xc;
    char** slot = (char**)(*(char**)(SELF + 0x7d8) + i * 4);
    char* nv = (char*)((TV3c)((void**)*(void***)mm)[3])(mm, *(void**)model, 0, *(void**)(model + 8));
    char* old = *slot;
    if (nv != old) {
      if (nv) *(int*)(nv + 0x40) += 1;
      *slot = nv;
      if (old) {
        int rc = *(int*)(old + 0x40);
        if (rc < 2) {
          ((TV1u)((void**)*(void***)old)[92])(old, (uint32_t)(*(uint32_t*)(old + 4) >> 31));
        } else {
          *(int*)(old + 0x40) = rc - 1;
        }
      }
    }
    char* cur = *(char**)(*(char**)(SELF + 0x7d8) + i * 4);
    if (cur) {
      ((TV1p)FUN_00537dc0)(cur + 8, *(char**)(SELF + 0x7c4) + i * 0x38);
      *(uint32_t*)(cur + 4) |= 0x20;
    }
  }
  ((TV0)FUN_00f99520)(this);
  U8V(0x76c) = 1;
}

// ================================================================ 0x00fa7220
// @ 0x00fa7220
uint32_t cTerrainSphere::AddPlayerModification(void* a, void* b, void* c) {
  char* local = 0;
  void* eff = FUN_0067ddd0();
  void* mgr = ((TV1p)((void**)*(void***)eff)[21])(eff, (void*)0x3fbae24);
  if (local) {
    char* p = local;
    local = 0;
    ((TV0)((void**)*(void***)p)[1])(p);
  }
  char ok = ((TV3c)((void**)*(void***)mgr)[2])(mgr, b, (int)(intptr_t)c, &local);
  if (!ok) {
    if (local) { char* p = local; ((TV0)((void**)*(void***)p)[1])(p); }
    return 0;
  }
  ((TV1)((void**)*(void***)local)[6])(local, a);
  ((TV1i)((void**)*(void***)local)[2])(local, 0);

  int n = 0x32;
  void* sp = *(void**)0x15fd918;
  if (sp) {
    void* prop = 0;
    if (((TV2c)((void**)*(void***)sp)[9])(sp, 0x3a8b697u, &prop) &&
        *(int16_t*)((char*)prop + 0x12) == 9) {
      n = *((TV0ip)FUN_0041e990)(prop);
    }
  }

  char* b7 = *(char**)(SELF + 0x798);
  char* e7 = *(char**)(SELF + 0x79c);
  int cnt = (int)(e7 - b7) / 0xac;
  if (cnt == n) {
    if (b7 + 0xac < e7) FUN_00f9f770(b7 + 0xac, e7, b7);
    INTV(0x79c) -= 0xac;
  }

  char src[0x38] = {0};
  char rel[0xac];
  void* r = ((TV3pi)FUN_00f9b2b0)(rel, src, a, 0);
  char* end = *(char**)(SELF + 0x79c);
  if (end < *(char**)(SELF + 0x7a0)) {
    *(char**)(SELF + 0x79c) = end + 0xac;
    if (end) ((TV1p)FUN_00f9b1e0)(end, r);
  } else {
    ((TV2)FUN_00fa47b0)(SELF + 0x798, end, r);
  }
  uint32_t key = *(uint32_t*)(*(char**)(SELF + 0x79c) - 4);
  INTV(0x814) += 1;
  INTV(0x818) += 1;
  if (local) { char* p = local; ((TV0)((void**)*(void***)p)[1])(p); }
  return key;
}

// ================================================================ 0x00fa73c0
// @ 0x00fa73c0
void cTerrainSphere::ClearPlayerModifications() {
  char* b = *(char**)(SELF + 0x798);
  char* e = *(char**)(SELF + 0x79c);
  FUN_00f9f770(e, e, b);
  int d = (int)(e - b);
  INTV(0x79c) -= (d / 0xac) * 0xac;
  _ReadWriteBarrier();

  ((TV1u)((void**)*(void***)PTRV(0x28))[6])(PTRV(0x28), 0x536250cu);
  ((TV1u)((void**)*(void***)PTRV(0x28))[6])(PTRV(0x28), 0x536250du);
  ((TV1u)((void**)*(void***)PTRV(0x28))[6])(PTRV(0x28), 0x3a23f9au);

  ((TV1i)FUN_00fbaf10)(PTRV(0x20c), 0);
  ((TV1i)FUN_00fbaf50)(PTRV(0x20c), 0);
  INTV(0x814) += 1;
}
