// slice s00fa47b0 -- SP::cTerrainSphere relevel / decal-node / teardown helpers.
// Object file: SPTerrain/SPTerrainSphere.obj.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
//   0x00fa47b0 SP::RelevelVector::DoInsertValue   (vector<cRelevel>::DoInsertValue)
//   0x00fa48d0 SP::cTerrainSphere::Shutdown
//   0x00fa4e90 SP::cTerrainSphere::UpdateDecalNode
//   0x00fa4fc0 SP::cTerrainSphere::DestroyDecalNode
//   0x00fa5040 SP::cTerrainSphere::RemoveRelevel
//   0x00fa5440 SP::cTerrainSphere::ReleaseManaged
//   0x00fa5490 SP::cTerrainSphere::FlushManaged
//   0x00fa5580 SP::cTerrainSphere::EraseRelevel
#include "types.h"
#include <stddef.h>
#include <intrin.h>
#include <new>

struct cRelevel;

// ---------------------------------------------------------------- externals
void*     __cdecl EAAllocate(unsigned n, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void      __cdecl EADeallocate(void* p);                                                               // 0x00f47380 (operator delete)

cRelevel* __cdecl RelevelUninitCopy(const cRelevel* first, const cRelevel* last, cRelevel* dest);      // 0x00f9f730
cRelevel* __cdecl RelevelCopyBackward(const cRelevel* first, const cRelevel* last, cRelevel* dest);    // 0x00f9f8b0
cRelevel* __cdecl CopyRelevels(cRelevel* first, cRelevel* last, cRelevel* dest);                       // 0x00f9f770
void      __cdecl FUN_00f9f620(void* dest, const void* src);                                           // 0x00f9f620 cRelevel::operator=

// cdecl-declared externals that are actually __thiscall; invoked through a matching fn-ptr type.
void FUN_007c3ba0(void*);                                     // 0x007c3ba0
void FUN_007c4000(void*);                                     // 0x007c4000
int  FUN_00692400(void*, int);                                // 0x00692400 SP::cJob::Cancel
int  FUN_00690120(void*);                                     // 0x00690120 SP::cJob::GetStatus
void FUN_00f92b90(void*);                                     // 0x00f92b90
void FUN_00fc7950(void*);                                     // 0x00fc7950
void FUN_00fb3e20(void*);                                     // 0x00fb3e20
void FUN_00fb4340(void*);                                     // 0x00fb4340
void FUN_00fbe4f0(void*);                                     // 0x00fbe4f0
void FUN_00fbd650(void*);                                     // 0x00fbd650
void FUN_00fadac0(void*);                                     // 0x00fadac0
void FUN_00fa4660(void*, void*);                              // 0x00fa4660
void FUN_00fa44d0(void*, void*);                              // 0x00fa44d0
void FUN_00fa29b0(void*, uint32_t);                           // 0x00fa29b0 cTerrainSphere::RemoveDecal
void FUN_00faeec0(void*);                                     // 0x00faeec0
void FUN_00c2e4e0(void*);                                     // 0x00c2e4e0
void FUN_00fc6d10(void*);                                     // 0x00fc6d10
void* FUN_00f67d90(void*);                                     // 0x00f67d90 cTerrainEditor::GetCurrentTerrainSphere
void FUN_00f67a60(void*, int);                                // 0x00f67a60
void FUN_00fae800(void*);                                     // 0x00fae800
void FUN_00facfc0(void*);                                     // 0x00facfc0
int  FUN_00fad140(void*, int, void*);                         // 0x00fad140 cTerrainSphereDecal::GetBBoxForFace
void FUN_004558a0(void*, uint32_t*, const uint32_t*);         // 0x004558a0 SP::SimpleVector<uint>::DoInsertValue
void FUN_00533500(void*, void*, void*);                       // 0x00533500 vector<T*> deallocate
void FUN_005f3680(void*, void*, void*);                       // 0x005f3680 vector<AutoRefCount<cMWModel>>::DoDestroyValues
int  FUN_00fa45c0(const void*, const void*, float);           // 0x00fa45c0
void FUN_00f9a680(void*, int, void*);                         // 0x00f9a680
void FUN_00f9a760(void*, int, float);                         // 0x00f9a760
void FUN_00f9a6f0(void*, int, void*);                         // 0x00f9a6f0

void*     __cdecl FUN_0067dd50();                             // 0x0067dd50
void*     __cdecl FUN_0067dda0();                             // 0x0067dda0
void*     __cdecl FUN_0067ddd0();                             // 0x0067ddd0 SP::EffectsManager
void*     __cdecl FUN_0067dcc0();                             // 0x0067dcc0 SP::MessageServer
void*     __cdecl FUN_00f48a70();                             // 0x00f48a70 SP::TerrainEditor
void*     __cdecl FUN_00f48aa0();                             // 0x00f48aa0 SP::GetActiveTerrainSphere
void      __cdecl FUN_00f48af0(void*);                        // 0x00f48af0
void*     __cdecl FUN_00f9ae80(void*, void*, void*);          // 0x00f9ae80
void*     __cdecl FUN_005f4e10(void*, void*, void*);          // 0x005f4e10 eastl::copy_impl do_copy
void      __cdecl FUN_00f672b0(void*);                        // 0x00f672b0
void      __cdecl FUN_011e0744(void*, void*, void*);          // 0x011e0744 (vector free thunk)

// ---------------------------------------------------------------- fn-ptr types
typedef void (__thiscall *TC0)(void*);
typedef void* (__thiscall *TC0p)(void*);
typedef int  (__thiscall *TC0i)(void*);
typedef int  (__thiscall *TC1i)(void*, int);
typedef void (__thiscall *TC1u)(void*, uint32_t);
typedef void (__thiscall *TC1p)(void*, void*);
typedef void (__thiscall *TC2u)(void*, uint32_t, uint32_t);
typedef void (__thiscall *TC2pp)(void*, void*, void*);
typedef void (__thiscall *TC2ppc)(void*, uint32_t*, const uint32_t*);
typedef int  (__thiscall *TC2ip)(void*, int, void*);
typedef void (__thiscall *TC3)(void*, void*, uint32_t, int);
typedef int  (__thiscall *TC3f)(void*, const void*, const void*, float);

#define VT0(obj, idx)          ((TC0)(*(void***)(obj))[idx])(obj)
#define VT0i(obj, idx)         ((TC0i)(*(void***)(obj))[idx])(obj)
#define VT1i(obj, idx, a)      ((TC1i)(*(void***)(obj))[idx])(obj, a)
#define VT2u(obj, idx, a, b)   ((TC2u)(*(void***)(obj))[idx])(obj, a, b)
#define VT3(obj, idx, a, b, c) ((TC3)(*(void***)(obj))[idx])(obj, a, b, c)

// Inlined intrusive AutoRefCount release (refcount lives at object+8).
#define ATOMREL8(p)                                                                                  \
  do {                                                                                               \
    volatile long* _r = (volatile long*)((char*)(p) + 8);                                            \
    _InterlockedExchangeAdd(_r, -1);                                                                 \
    long _v = _InterlockedExchangeAdd(_r, 0);                                                        \
    if (_v < 1) _InterlockedExchangeAdd(_r, 1); else _InterlockedExchangeAdd(_r, 0);                 \
  } while (0)

// ---------------------------------------------------------------- relevel element / vector
struct Vector3 { float x, y, z; };
struct Rect    { float l, t, r, b; };
struct Key     { uint32_t instance, type, group; };
struct Matrix3I { Vector3 row0, row1, row2; };
struct cSPTransform {
  uint16_t mFlags, mModCount;
  float mTx, mTy, mTz, mScale;
  Matrix3I mRot;
};
struct cRelevel {
  cSPTransform mTransform;   // +0x00
  Rect mBounds[6];           // +0x38
  Key  mKey;                 // +0x98
  uint32_t mFlagsAndBits;    // +0xa4
  uint32_t mExtra;           // +0xa8
  cRelevel(const cRelevel&) throw();
  cRelevel& operator=(const cRelevel&) throw();
};

struct SPAllocator {
  const char* mpName;
  uint32_t mExtra;
  void* allocate(size_t n) {
    return EAAllocate(n, "Simulator", 0, 0,
                      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                      0xd1);
  }
  void deallocate(void* p) {
    if (p && ((int*)p)[-1] != 0) EADeallocate(p);
  }
};

struct RelevelVector {
  cRelevel* mpBegin;
  cRelevel* mpEnd;
  cRelevel* mpCapacity;
  SPAllocator mAllocator;
  typedef size_t size_type;
  cRelevel* DoAllocate(size_type n) { return n ? (cRelevel*)mAllocator.allocate(n * sizeof(cRelevel)) : 0; }
  void DoFree(cRelevel* p, size_type) { mAllocator.deallocate(p); }
  void DoInsertValue(cRelevel* position, const cRelevel& value);
};

// ================================================================ 0x00fa47b0
// @ 0x00fa47b0
void RelevelVector::DoInsertValue(cRelevel* position, const cRelevel& value) {
  if (mpEnd != mpCapacity) {
    const cRelevel* pValue = &value;
    if ((pValue >= position) && (pValue < mpEnd)) ++pValue;
    ::new ((void*)mpEnd) cRelevel(*(mpEnd - 1));
    RelevelCopyBackward(position, mpEnd - 1, mpEnd);
    *position = *pValue;
    ++mpEnd;
  } else {
    const size_type nPosSize = size_type(position - mpBegin);
    const size_type nPrevSize = size_type(mpEnd - mpBegin);
    const size_type nNewSize = nPrevSize ? (2 * nPrevSize) : 1;
    cRelevel* const pNewData = DoAllocate(nNewSize);
    cRelevel* pNewEnd = RelevelUninitCopy(mpBegin, position, pNewData);
    ::new (pNewEnd) cRelevel(value);
    pNewEnd = RelevelUninitCopy(position, mpEnd, ++pNewEnd);
    DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
    mpBegin = pNewData;
    mpEnd = pNewEnd;
    mpCapacity = pNewData + nNewSize;
  }
}

// ---------------------------------------------------------------- the terrain sphere
class cTerrainSphere {
 public:
  void Shutdown();
  void UpdateDecalNode(void* node);
  void DestroyDecalNode(void* node);
  bool RemoveRelevel(uint32_t key, unsigned char removeDecals);
  void ReleaseManaged();
  void FlushManaged();
  bool EraseRelevel(uint32_t key);
};

#define PTR(off)   (*(void**)((char*)this + (off)))
#define INTV(off)  (*(int*)((char*)this + (off)))
#define BYTEV(off) (*(unsigned char*)((char*)this + (off)))

// ================================================================ 0x00fa48d0
// @ 0x00fa48d0
void cTerrainSphere::Shutdown() {
  if (PTR(0x8e4)) {
    ((TC0)FUN_007c3ba0)(PTR(0x8e4));
    if (PTR(0x8e4)) {
      void* v = PTR(0x8e4);
      ((TC0)FUN_007c4000)(v);
      EADeallocate(v);
    }
    PTR(0x8e4) = 0;
  }
  if (PTR(0x81c)) {
    ((TC1i)FUN_00692400)(PTR(0x81c), 1);
    if (PTR(0x81c)) {
      void* v = PTR(0x81c);
      PTR(0x81c) = 0;
      ((TC0i)FUN_00690120)(v);
    }
    BYTEV(0x370) = 0;
  }
  if (PTR(0x8a0)) {
    void* p = PTR(0x8a0);
    if (p) { PTR(0x8a0) = 0; VT0(p, 1); }
    if (PTR(0x8a4) != (void*)-1) {
      void* s = FUN_0067dd50();
      ((TC1u)(*(void***)s)[31])(s, (uint32_t)(uintptr_t)PTR(0x8a4));
    }
    PTR(0x8a4) = (void*)-1;
  }
  if (PTR(0x89c) != (void*)-1) {
    void* s = FUN_0067dda0();
    ((TC2u)(*(void***)s)[5])(s, (uint32_t)(uintptr_t)PTR(0x898), (uint32_t)(uintptr_t)PTR(0x89c));
  }
  PTR(0x89c) = (void*)-1;
  PTR(0x898) = (void*)-1;
  if (PTR(0x894)) {
    ((TC1i)FUN_00692400)(PTR(0x894), 1);
    if (PTR(0x894)) {
      void* v = PTR(0x894);
      PTR(0x894) = 0;
      ((TC0i)FUN_00690120)(v);
    }
  }
  {
    void* eff = FUN_0067ddd0();
    int r = ((TC1i)(*(void***)eff)[9])(eff, -1);
    if (r == (int)(uintptr_t)PTR(0x924)) VT0(this, 41);
  }
  VT0(PTR(0x924), 1);
  VT0(PTR(0x924), 3);
  PTR(0x924) = 0;
  {
    void* te = FUN_00f48a70();
    if (((TC0p)FUN_00f67d90)(te) == this) {
      void* te2 = FUN_00f48a70();
      ((TC1i)FUN_00f67a60)(te2, 0);
    }
  }
  if (FUN_00f48aa0() == this) FUN_00f48af0(0);
  VT0(this, 43);
  if (PTR(0x210)) {
    ((TC0)FUN_00fc7950)(PTR(0x210));
    if (PTR(0x210)) {
      void* p = PTR(0x210);
      PTR(0x210) = 0;
      VT0((char*)p + 8, 3);
    }
  }
  if (PTR(0x2c)) {
    ((TC0)FUN_00f92b90)(PTR(0x2c));
    if (PTR(0x2c)) {
      void* p = PTR(0x2c);
      PTR(0x2c) = 0;
      int* rc = (int*)((char*)p + 4);
      if (--*rc == 0) { *rc = 1; VT1i(p, 0, 1); }
    }
  }
  {
    void** a = (void**)((char*)this + 0x118);
    void** b = (void**)((char*)this + 0x130);
    void** c = (void**)((char*)this + 0x148);
    void** d = (void**)((char*)this + 0x160);
    void** e = (void**)((char*)this + 0x178);
    for (int i = 0; i < 6; ++i) {
      if (a[i]) {
        ((TC0)FUN_00fb3e20)(a[i]);
        if (a[i]) { ((TC0)FUN_00fb4340)(a[i]); EADeallocate(a[i]); }
        a[i] = 0;
      }
      if (b[i]) {
        ((TC0)FUN_00fb3e20)(b[i]);
        if (b[i]) { ((TC0)FUN_00fb4340)(b[i]); EADeallocate(b[i]); }
        b[i] = 0;
      }
      if (c[i]) { void* p = c[i]; c[i] = 0; ATOMREL8(p); }
      if (d[i]) { void* p = d[i]; d[i] = 0; ATOMREL8(p); }
      if (e[i]) { void* p = e[i]; e[i] = 0; ATOMREL8(p); }
    }
  }
  if (PTR(0x20c)) {
    ((TC0)FUN_00fbe4f0)(PTR(0x20c));
    if (PTR(0x20c)) { void* p = PTR(0x20c); ((TC0)FUN_00fbd650)(p); EADeallocate(p); }
    PTR(0x20c) = 0;
  }
  for (int f = 0; f < 4; ++f) {
    char* lst = (char*)this + 0x218 + f * 0x14;
    void** lb = *(void***)lst;
    int n = (int)((*(char**)(lst + 4) - (char*)lb) >> 2);
    for (int j = 0; j < n; ++j) {
      void* p = lb[j];
      if (!p) continue;
      ((TC0)FUN_00fadac0)(p);
      int* rc = (int*)((char*)p + 4);
      if (--*rc == 0) { *rc = 1; VT1i(p, 0, 1); }
      lb[j] = 0;
    }
    FUN_011e0744(lb, *(void**)(lst + 4), 0);
    *(char**)(lst + 4) = (char*)*(char**)(lst + 4) - n * 4;
    char* fl = (char*)this + 0x268 + f * 0x14;
    void* fb = *(void**)fl;
    void* fe = *(void**)(fl + 4);
    FUN_011e0744(fb, fe, 0);
    *(char**)(fl + 4) = (char*)fe - ((char*)fe - (char*)fb);
  }
  {
    void* ms = FUN_0067dcc0();
    VT3(ms, 11, (char*)this + 8, 0x87d5f9bf, 0xffffd8f1);
    VT3(ms, 11, (char*)this + 8, 0x03d5bf9a, 0xffffd8f1);
    VT3(ms, 11, (char*)this + 8, 0x044edd9a, 0xffffd8f1);
    VT3(ms, 11, (char*)this + 8, 0x044edd9c, 0xffffd8f1);
  }
  {
    void* begin = PTR(0x8b0);
    void* end = PTR(0x8b4);
    void* r = FUN_00f9ae80(end, end, begin);
    for (char* p = (char*)r; p < (char*)PTR(0x8b4); p += 8) {
      void* q = *(void**)p;
      if (q) VT0(q, 1);
    }
    long len = (char*)end - (char*)begin;
    PTR(0x8b4) = (char*)end - (len >> 3) * 8;
  }
  {
    void* begin = PTR(0x8c4);
    void* end = PTR(0x8c8);
    void* r = FUN_00f9ae80(end, end, begin);
    for (char* p = (char*)r; p < (char*)PTR(0x8c8); p += 8) {
      void* q = *(void**)p;
      if (q) VT0(q, 1);
    }
    long len = (char*)end - (char*)begin;
    PTR(0x8c8) = (char*)end - (len >> 3) * 8;
  }
  if (PTR(0x308)) { void* p = PTR(0x308); PTR(0x308) = 0; ATOMREL8(p); }
  while (PTR(0x2f4) != PTR(0x2f8)) {
    ((TC1p)FUN_00fa4660)(this, **(void***)PTR(0x2f4));
  }
  while (PTR(0x2e0) != PTR(0x2e4)) {
    ((TC1p)FUN_00fa44d0)(this, **(void***)PTR(0x2e0));
  }
  ((TC1p)(*(void***)this)[36])(this, FUN_0067dd50());
  FUN_00f672b0(PTR(0x928));
  PTR(0x928) = 0;
  ((TC0)FUN_00faeec0)(PTR(0xa4c));
  if (PTR(0xa4c)) { void* q = PTR(0xa4c); ((TC0)FUN_00c2e4e0)(q); EADeallocate(q); }
  PTR(0xa4c) = 0;
}

// ================================================================ 0x00fa4e90
// @ 0x00fa4e90
void cTerrainSphere::UpdateDecalNode(void* node) {
  char* e = (char*)node;
  if (*(int*)(e + 0x68) == 4) {
    int handle = *(int*)(e + 0x6c);
    if (handle == -1) {
      Vector3 v;
      v.x = *(float*)(e + 4);
      v.y = *(float*)(e + 8);
      v.z = *(float*)(e + 0xc);
      int h = ((TC3f)FUN_00fa45c0)(this, &v, e + 0x38, *(float*)(e + 0x10));
      *(int*)(e + 0x6c) = h;
      *(uint16_t*)(e + 0x70) = *(uint16_t*)(e + 2);
      return;
    }
    if (*(uint16_t*)(e + 0x70) != *(uint16_t*)(e + 2)) {
      Vector3 v;
      v.x = *(float*)(e + 4);
      v.y = *(float*)(e + 8);
      v.z = *(float*)(e + 0xc);
      ((TC2ip)FUN_00f9a680)(this, handle, &v);
      ((void(__thiscall*)(void*, int, float))FUN_00f9a760)(this, handle, *(float*)(e + 0x10));
    }
    ((TC2ip)FUN_00f9a6f0)(this, handle, e + 0x38);
    *(uint16_t*)(e + 0x70) = *(uint16_t*)(e + 2);
    return;
  }
  if (*(int*)(e + 0x68) == 5) return;
  char* b = e - 8;
  if (*(int*)(b + 0x7c) == 0) return;
  if (*(int*)(b + 0x70) == 9) {
    void* q = *(void**)(b + 0x128);
    if ((*(unsigned char*)((char*)q + 4) & 1) == 0) return;
  }
  if ((*(uint32_t*)(b + 0xb8) >> 3) & 1) return;
  ((TC0)FUN_00fae800)(b);
  if ((*(uint32_t*)(b + 0xb8) >> 4) & 1) return;
  ((TC0)FUN_00facfc0)(b);
}

// ================================================================ 0x00fa4fc0
// @ 0x00fa4fc0
void cTerrainSphere::DestroyDecalNode(void* node) {
  char* n = (char*)node;
  int type = *(int*)(n + 0x68);
  if (type == 4) {
    ((TC1p)FUN_00fa4660)(this, *(void**)(n + 0x6c));
    EADeallocate(n);
    return;
  }
  if (type == 5) {
    ((TC1p)FUN_00fa44d0)(this, *(void**)(n + 0x6c));
    EADeallocate(n);
    return;
  }
  char* b = n - 8;
  int rc = *(int*)(b + 4);
  rc += -1;
  *(int*)(b + 4) = rc;
  if (rc == 0) {
    *(int*)(b + 4) = 1;
    void** vt = *(void***)b;
    ((TC1i)vt[0])(b, 1);
  }
  if (*(int*)(b + 0x7c) != 0) {
    ((TC1u)FUN_00fa29b0)(this, *(uint32_t*)(b + 0x74));
  }
}

// ================================================================ 0x00fa5040
// @ 0x00fa5040
bool cTerrainSphere::RemoveRelevel(uint32_t key, unsigned char removeDecals) {
  cRelevel* rb = (cRelevel*)PTR(0x784);
  int count = (int)((cRelevel*)PTR(0x788) - rb);
  int idx = -1;
  if (count != 0) {
    unsigned i = 0;
    cRelevel* p = rb;
    do {
      if (*(uint32_t*)((char*)p + 0xa8) == key) { idx = (int)i; break; }
      p = (cRelevel*)((char*)p + 0xac);
      ++i;
    } while (i < (unsigned)count);
  }
  if (idx != -1) {
    if (removeDecals) {
      for (int f = 0; f < 4; ++f) {
        void** lb = *(void***)((char*)this + 0x218 + f * 0x14);
        int n = (int)((*(char**)((char*)this + 0x218 + f * 0x14 + 4) - (char*)lb) >> 2);
        for (int j = n - 1; j >= 0; --j) {
          void* d = lb[j];
          if (!d) continue;
          if (((*(uint32_t*)((char*)d + 0xb8) >> 3) & 1) == 0) continue;
          for (int face = 0; face < 6; ++face) {
            float box[4];
            if (!((TC2ip)FUN_00fad140)(d, face, box)) continue;
            float* r = (float*)((char*)this + 0x784 + idx * 0xac + face * 0x10 + 0x38);
            if (box[2] > r[0] && r[2] > box[0] && box[3] > r[1] && r[3] > box[1]) {
              ((TC1u)FUN_00fa29b0)(this, (uint32_t)((f << 24) | j));
              break;
            }
          }
        }
      }
    }
    cRelevel* bend = (cRelevel*)PTR(0x788);
    cRelevel* pc = (cRelevel*)((char*)rb + idx * 0xac);
    cRelevel* pn = (cRelevel*)((char*)pc + 0xac);
    if (pn < bend) {
      while (pn != bend) {
        FUN_00f9f620((char*)pn - 0xac, pn);
        pn = (cRelevel*)((char*)pn + 0xac);
      }
    }
    INTV(0x788) -= 0xac;
    return true;
  }
  cRelevel* wb = (cRelevel*)PTR(0x770);
  int wcount = (int)((cRelevel*)PTR(0x774) - wb);
  int widx = -1;
  if (wcount != 0) {
    unsigned i = 0;
    cRelevel* p = wb;
    do {
      if (*(uint32_t*)((char*)p + 0xa8) == key) { widx = (int)i; break; }
      p = (cRelevel*)((char*)p + 0xac);
      ++i;
    } while (i < (unsigned)wcount);
  }
  if (widx == -1) return false;
  if (removeDecals) {
    for (int f = 0; f < 4; ++f) {
      void** lb = *(void***)((char*)this + 0x218 + f * 0x14);
      int n = (int)((*(char**)((char*)this + 0x218 + f * 0x14 + 4) - (char*)lb) >> 2);
      for (int j = n - 1; j >= 0; --j) {
        void* d = lb[j];
        if (!d) continue;
        if (((*(uint32_t*)((char*)d + 0xb8) >> 3) & 1) == 0) continue;
        for (int face = 0; face < 6; ++face) {
          float box[4];
          if (!((TC2ip)FUN_00fad140)(d, face, box)) continue;
          float* r = (float*)((char*)this + 0x770 + widx * 0xac + face * 0x10 + 0x38);
          if (box[2] > r[0] && r[2] > box[0] && box[3] > r[1] && r[3] > box[1]) {
            uint32_t packed = (uint32_t)((f << 24) | j);
            int ff = (int)(packed >> 24);
            uint32_t jj = packed & 0xffffff;
            void** dl = *(void***)((char*)this + 0x218 + ff * 0x14);
            int dn = (int)((*(char**)((char*)this + 0x218 + ff * 0x14 + 4) - (char*)dl) >> 2);
            if (jj < (uint32_t)dn) {
              void* dd = dl[jj];
              if (dd) {
                ((TC0)FUN_00fadac0)(dd);
                int* rc = (int*)((char*)dd + 4);
                if (--*rc == 0) { *rc = 1; ((TC1i)(*(void***)dd)[0])(dd, 1); }
                dl[jj] = 0;
                char* fl = (char*)this + 0x268 + ff * 0x14;
                uint32_t* fe = *(uint32_t**)(fl + 4);
                if (fe < *(uint32_t**)(fl + 8)) {
                  *(uint32_t**)(fl + 4) = fe + 1;
                  if (fe) *fe = jj;
                } else {
                  uint32_t local = jj;
                  ((TC2ppc)FUN_004558a0)(fl, fe, &local);
                }
              }
            }
            break;
          }
        }
      }
    }
  }
  cRelevel* wend = (cRelevel*)PTR(0x774);
  cRelevel* wc = (cRelevel*)((char*)wb + widx * 0xac);
  cRelevel* wn = (cRelevel*)((char*)wc + 0xac);
  if (wn < wend) {
    while (wn != wend) {
      FUN_00f9f620((char*)wn - 0xac, wn);
      wn = (cRelevel*)((char*)wn + 0xac);
    }
  }
  INTV(0x774) -= 0xac;
  return true;
}

// ================================================================ 0x00fa5440
// @ 0x00fa5440
void cTerrainSphere::ReleaseManaged() {
  void** base = (void**)((char*)this + 0x7ec);
  int n = (int)((*(char**)((char*)this + 0x7f0) - (char*)base[0]) >> 2);
  for (int i = 0; i < n; ++i) {
    void* p = ((void**)base[0])[i];
    if (p) ((TC1i)(*(void***)p)[3])(p, 1);
  }
  ((TC2pp)FUN_00533500)(base, base[0], base[1]);
}

// ================================================================ 0x00fa5490
// @ 0x00fa5490
void cTerrainSphere::FlushManaged() {
  if (PTR(0x210) && *(unsigned char*)((char*)PTR(0x210) + 0xac)) {
    ((TC0)FUN_00fc6d10)(PTR(0x210));
  }
  if (!BYTEV(0x76c)) return;
  ReleaseManaged();
  {
    void** v = (void**)((char*)this + 0x800);
    int n = (int)((*(char**)((char*)this + 0x804) - (char*)v[0]) >> 2);
    for (int i = 0; i < n; ++i) {
      void* p = ((void**)v[0])[i];
      if (p) ((TC1i)(*(void***)p)[3])(p, 1);
    }
    ((TC2pp)FUN_00533500)(v, v[0], v[1]);
  }
  {
    void** v = (void**)((char*)this + 0x7d8);
    int n = (int)((*(char**)((char*)this + 0x7dc) - (char*)v[0]) >> 2);
    for (int i = 0; i < n; ++i) {
      void* p = ((void**)v[0])[i];
      if (p) ((TC1i)(*(void***)p)[91])(p, 0);
    }
    void* res = FUN_005f4e10(v[1], v[1], v[0]);
    ((TC2pp)FUN_005f3680)(v, res, v[1]);
    int cnt = (int)(((char*)v[1] - (char*)v[0]) >> 2);
    v[1] = (char*)v[1] - cnt * 4;
  }
  BYTEV(0x76c) = 0;
}

// ================================================================ 0x00fa5580
// @ 0x00fa5580
bool cTerrainSphere::EraseRelevel(uint32_t key) {
  int count = (int)((cRelevel*)PTR(0x79c) - (cRelevel*)PTR(0x798));
  for (int i = 0; i < count; ++i) {
    if (((cRelevel*)PTR(0x798))[i].mExtra == key) {
      cRelevel* cur = (cRelevel*)PTR(0x798) + i;
      if (cur + 1 < (cRelevel*)PTR(0x79c)) CopyRelevels(cur + 1, (cRelevel*)PTR(0x79c), cur);
      INTV(0x79c) -= 0xac;
      return true;
    }
  }
  return false;
}
