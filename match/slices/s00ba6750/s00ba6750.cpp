// match/slices/s00ba6750/s00ba6750.cpp
// Object file: SPStarManager/SPStarSearch.obj (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include
//
// Heap helpers over arrays of ref-counted pointer elements, the
// SP::cStarManager::tStarSearchCriteria constructor, star-eligibility queries
// and the star-search serializers.  Local stub structs carry the retail
// field offsets the disassembly shows.

#include "game/types.h"
#include <math.h>

// ---- unnamed retail callees (address in the comment) ----
void*    __cdecl FUN_005c65e0(void*);                  // 0x5c65e0 cCivData::GetCities
float    __cdecl FUN_010434c0(void*, void*);           // 0x10434c0 float score
int      __cdecl FUN_00b3d2a0();                       // 0xb3d2a0 SP::StarManager
void*    __cdecl FUN_00b5b800();                       // 0xb5b800 GetCurrentGameMode
void*    __cdecl FUN_01021300();                       // 0x1021300 GetPlayerEmpire
void*    __cdecl FUN_00921580(void*);                  // 0x921580 RBTreeIncrement
bool     __cdecl FUN_0093aa70(void*, const void*, int, int); // 0x93aa70 WriteUint32
unsigned char __cdecl FUN_00692e00(void*);             // 0x692e00 WriteBlob32
unsigned char __cdecl FUN_00692e50(void*);             // 0x692e50 WriteBlob16

// Game object whose __thiscall members are called with ecx = the object.
struct GameObj {
  int  AddRef();                    // 0x801920
  int  Kind();                      // 0xbb9ae0
  int  Q9c60();                     // 0xbb9c60
  int  Qa900();                     // 0xbba900
  int  Flag(int mask);              // 0xbb9af0
  void OnBan();                     // 0xbba2a0
  int  Pop(int a, int b);           // 0xbb9b00
  int  Kind2(int a);                // 0xbbaa60
  int  Match(void* arg);            // 0xbbaa80
};
int  __cdecl FUN_00bbaa60(int);                        // 0xbbaa60
int  __cdecl FUN_00bbaa80(void*, void*);               // 0xbbaa80

extern unsigned char g_1689df8;                        // 0x1689df8 re-entry guard
extern float g_13eb1bc;                                // 0x13eb1bc -1.0f
extern float g_13eb8c8;                                // 0x13eb8c8 0.3f
extern float g_13ec478;                                // 0x13ec478
extern float g_1446660;                                // 0x1446660 19.0f
extern float g_1459c40;                                // 0x1459c40 64
extern float g_140f334;                                // 0x140f334 64.0f
extern float g_13ef54c;                                // 0x13ef54c 1.1f
extern float g_1485378;                                // 0x1485378 0.0f
extern float g_156c490;                                // 0x156c490
extern float g_156c494;                                // 0x156c494
extern float g_156c498;                                // 0x156c498
extern float g_156c49c;                                // 0x156c49c
extern float g_156c638;                                // 0x156c638
extern float g_1465e88;                                // 0x1465e88 60.0f
extern float g_1465e8c;                                // 0x1465e8c 280.0f
extern float g_1465e90;                                // 0x1465e90 20.0f
extern float g_1465eb8;                                // 0x1465eb8 FLT_MAX
extern unsigned char g_1654c05;                        // 0x1654c05 game-mode tag

// A refcounted object with the vtable slots these helpers touch.
struct IRefObj {
  virtual void AddRef();        // +0x00
  virtual void Release();       // +0x04
  char pad004[0x28 - 4];
  int mScore;                   // +0x28
};

// The global math RNG lives at 0x1601760; its methods take ecx = that object.
struct Rng {
  double Next();        // 0x9360d0 RandomDoubleUniform
  unsigned NextU(unsigned n); // 0xa68fb0 RandomUint32Uniform
};

// A property record.  The value fetch (0x41ea70) is a trivial is-inlined
// one-liner in retail; written as such so MSVC folds it into the call site.
struct PropStub {
  char pad000[0x12];
  short m12;                // +0x12 type tag
  float* GetFloat();        // 0x41ea70
};

// A stream/output object reached through shadow vtables.
struct IStream {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
  virtual void s4(); virtual void s5(); virtual void s6();
  virtual void* GetData();      // +0x1c
  virtual void* S20();          // +0x20
  virtual void* S18();          // +0x18
};
struct IWriter {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
  virtual void s4(); virtual void s5();
  virtual void* S18();          // +0x18
};

// -------- sift-down/sift-up over an array of ref-counted pointer elements -----

// @ 0x00ba6750
void FUN_00ba6750(IRefObj** a, int lo, int hi, IRefObj* item) {
  int child = (hi - 1) >> 1;
  while (hi > lo) {
    child = (hi - 1) >> 1;
    IRefObj* parent = a[child];
    if (parent->mScore >= item->mScore) break;
    IRefObj* cur = a[hi];
    if (parent != cur) {
      if (parent) parent->AddRef();
      a[hi] = parent;
      if (cur) cur->Release();
    }
    hi = child;
  }
  IRefObj* cur = a[hi];
  if (item != cur) {
    if (item) item->AddRef();
    a[hi] = item;
    if (cur) cur->Release();
  }
  if (item) item->Release();
}

// @ 0x00ba6800
void FUN_00ba6800(void* base, int lo, int hi, int a4, int a5, int a6,
                  char (__cdecl *cmp)(void*, void*)) {
  while (lo < hi) {
    int parent = (hi - 1) >> 1;
    char* p = (char*)base + parent * 0xc;
    if (!cmp(p, &a4)) break;
    char* cur = (char*)base + hi * 0xc;
    *(int*)(cur + 0) = *(int*)(p + 0);
    *(int*)(cur + 4) = *(int*)(p + 4);
    *(int*)(cur + 8) = *(int*)(p + 8);
    hi = parent;
  }
  char* dst = (char*)base + hi * 0xc;
  *(int*)(dst + 0) = a4;
  *(int*)(dst + 4) = a5;
  *(int*)(dst + 8) = a6;
}

// --------------- SP::cStarManager::tStarSearchCriteria::tStarSearchCriteria --

struct StarSearchCriteria {
  int   m0;    // +0x00
  int   m4;    // +0x04
  int   m8;    // +0x08
  float mC;    // +0x0c
  float m10;   // +0x10
  float m14;   // +0x14
  int   m18;   // +0x18
  StarSearchCriteria();
};
StarSearchCriteria* gStarSearchCriteria; // returned in eax (in-place)

// @ 0x00ba6880
StarSearchCriteria::StarSearchCriteria() {
  m0 = 0x1fff;
  m4 = 0x3f;
  m8 = 0;
  mC = g_13eb1bc;
  m10 = g_13eb1bc;
  m14 = g_13eb1bc;
  m18 = 0;
}

// ---------------------------- star-position selection ------------------------

// @ 0x00ba68f0
void FUN_00ba68f0(float* out, int mode, int kind, float scale) {
  float* src;
  float hi;
  switch (kind) {
  case 0:
    {
      float v = (mode == 6) ? g_156c498 : (g_156c490 + g_1446660);
      float r = (float)(int)(v * g_13ec478) * g_1465e90;
      src = &g_1465e88;
      if (r >= g_1465e88) src = &r;
      hi = g_1465e8c;
    }
    break;
  case 1:
  case 2:
    if (mode == 6) { *(float*)&src = g_156c498; src = (float*)&src; }
    else { float lo = g_156c490 + scale; src = &lo; }
    hi = g_156c49c;
    break;
  case 3:
    *out = g_156c494;
    out[1] = g_156c498;
    return;
  default:
    *out = g_156c490 + scale;
    out[1] = g_156c49c;
    return;
  }
  *out = *src;
  out[1] = hi;
}

// @ 0x00ba6a40
void FUN_00ba6a40(unsigned which, unsigned* bits) {
  *bits &= 0xffffffbc;
  for (unsigned i = 0; i <= 3; ++i) {
    int bit;
    switch (i) {
    case 1:  bit = 3; break;
    case 2:  bit = 4; break;
    case 3:  bit = 5; break;
    default: bit = 2; break;
    }
    if (i == which) *bits |= 1u << bit;
    else            *bits &= ~(1u << bit);
  }
}

// @ 0x00ba6ab0
int FUN_00ba6ab0(unsigned* flags) {
  unsigned f = *flags;
  int n = (f & 1) != 0;
  if ((f >> 1) & 1) n++;
  if ((f >> 2) & 1) n++;
  if ((f >> 3) & 1) n++;
  int pick = (n > 1) ? (int)((Rng*)0x1601760)->NextU((unsigned)n) : 0;
  f = *flags;
  if (f & 1) { if (pick == 0) return 0; --pick; }
  if (f & 2) { if (pick == 0) return 1; --pick; }
  if (f & 4) { if (pick == 0) return 2; --pick; }
  return (f & 8) ? 3 : 0;
}

// @ 0x00ba6b40
int FUN_00ba6b40(int* vec, int start, void* civ, float threshold) {
  int n = (vec[1] - vec[0]) >> 2;
  int w = start;
  for (int i = start; i < n; ++i) {
    void* cities = FUN_005c65e0((void*)vec[i]);
    float score = FUN_010434c0(civ, cities);
    if (score <= threshold) {
      if (w != i) {
        int* p = (int*)vec[0];
        int tmp = p[w];
        p[w] = p[i];
        p[i] = tmp;
      }
      ++w;
    }
  }
  return w;
}

// @ 0x00ba6bb0
int FUN_00ba6bb0(GameObj* param_1, void* civ, unsigned* crit, float* out) {
  int a = param_1->AddRef();
  if ((crit[0] & (1u << (a & 0x1f))) == 0) return 0;
  int b = param_1->Kind();
  if ((crit[1] & (1u << (b & 0x1f))) == 0) return 0;
  if (crit[2] & 1) {
    FUN_00b3d2a0();
    if (*(char*)((char*)param_1 + 0xac) != 0) return 0;
    if (param_1->Q9c60() != 0) return 0;
  }
  if (((crit[2] >> 1) & 1) && param_1->Qa900() == 0) return 0;
  if (((crit[2] >> 2) & 1) && param_1->Flag(0x20000) == 0) return 0;
  float fmin = (float)crit[3];
  fmin = (fmin < 0.0f) ? -1.0f : fmin * fmin;
  float fmax = (float)crit[4];
  if (fmax <= 0.0f) fmax = g_156c638 * g_13ef54c;
  void* cities = FUN_005c65e0(civ);
  float score = FUN_010434c0(param_1, cities);
  if (out) *out = score;
  if (fmin < score && score < fmax * fmax) return 1;
  return 0;
}

// @ 0x00ba6cf0
struct BannerList {
  char pad000[0xc8];
  void* mC8;   // +0xc8 vector begin (stride 0x14)
  void* mCC;   // +0xcc vector end
  char padD0[0x14c - 0xd0];
  void* m14C;  // +0x14c
};
void FUN_00ba6cf0(BannerList* self) {
  int n = (int)(((char*)self->mCC - (char*)self->mC8)) / 0x14;
  for (int i = 0; i < n; ++i) {
    char* grp = (char*)self->mC8 + i * 0x14;
    void** begin = *(void***)(grp + 0);
    int cnt = ((int)*(void***)(grp + 4) - (int)begin) >> 2;
    for (int j = 0; j < cnt; ++j) {
      ((GameObj*)begin[j])->Pop(0x10030, 0);
    }
  }
}

// @ 0x00ba6d80
int FUN_00ba6d80(BannerList* self, unsigned id) {
  if (id == 0) return *(int*)&self->m14C;
  if (id == 0xffffffff) return 0;
  void** inner = (void**)self->mC8;
  void* row = inner[(id >> 0xc) * 5];
  return *(int*)((char*)row + (id & 0xfff) * 4);
}

// @ 0x00ba6dc0
int FUN_00ba6dc0(BannerList* self, unsigned id) {
  if (id == 0xffffffff) return 0;
  unsigned lo = id & 0xffffff;
  void** inner = (void**)self->mC8;
  void* row = inner[(lo >> 0xc) * 5];
  GameObj* cell = (GameObj*)(*(int*)((char*)row + (lo & 0xfff) * 4));
  return cell->Kind2((int)(id >> 0x18));
}

// @ 0x00ba6e00
int FUN_00ba6e00(BannerList* self, void* arg) {
  if (*(char*)((char*)self + 0x64) != 0) return 1;
  if (g_1689df8 != 0) return 1;
  int cnt = (int)(*(int*)((char*)self + 0xe0) - *(int*)((char*)self + 0xdc)) >> 2;
  g_1689df8 = 1;
  int all = 1;
  for (int i = 0; i < cnt; ++i) {
    void** elems = *(void***)((char*)self + 0xdc);
    if (!((GameObj*)elems[i])->Match(arg) || !all) all = 0;
    else all = 1;
  }
  g_1689df8 = 0;
  return all;
}

// @ 0x00ba6e80
int __stdcall FUN_00ba6e80(int* vec, void* civ, float threshold, int maxGroups) {
  int n = (vec[1] - vec[0]) >> 2;
  int w = FUN_00ba6b40(vec, 0, civ, threshold);
  int group = 1;
  int boundary = w;
  if (maxGroups == 0 || maxGroups > 1) {
    for (int i = 0; i < n; ++i) {
      if (i >= w) return w;
      if (i == boundary) {
        ++group;
        boundary = w;
        if (maxGroups != 0 && group > maxGroups) return w;
      }
      void* cities = FUN_005c65e0((void*)vec[i]);
      w = FUN_00ba6b40(vec, w, cities, threshold);
    }
  }
  return w;
}

// @ 0x00ba6f20
int FUN_00ba6f20(BannerList* self, int obj) {
  if (((GameObj*)obj)->AddRef() != 2) return 0;
  int* begin = *(int**)((char*)self + 0x104);
  int* end = *(int**)((char*)self + 0x108);
  int* p = begin;
  while (p != end && *p != obj) ++p;
  int idx = (int)(p - begin);
  if (((GameObj*)obj)->Flag(0x400) == 0) {
    --idx;
    if (((GameObj*)obj)->Flag(0x400) != 0) {
      while (idx >= 0 && ((GameObj*)*(begin + idx))->Flag(0x400) != 0) --idx;
    }
  }
  return *(int*)((char*)begin + (idx + 1) * 4);
}

struct StarSearchSelf {
  char pad000[0x1a0];
  void* mMgr;                // +0x1a0
  int Eligible(int kind, unsigned* prop);
};
// @ 0x00ba6fc0
int StarSearchSelf::Eligible(int kind, unsigned* prop) {
  if (kind != 5) return 1;
  if (prop != 0 && ((*prop >> 5) & 1) == 0) return 1;
  void* mgr = mMgr;
  float p = g_13eb8c8;
  if (mgr != 0) {
    int* vt = *(int**)mgr;
    void* out = 0;
    if ((*(char(__thiscall**)(void*, int, void**))(vt[9]))(mgr, 0x3e99308, &out)) {
      if (*(short*)((char*)out + 0x12) == 0xd) {
        // 0x41ea70 hands back the record's float slot (a `.prop` record's float).
        float* f = ((PropStub*)out)->GetFloat();
        p = *f;
        if (p <= g_1485378) return 1;
      }
    }
  }
  double r = ((Rng*)0x1601760)->Next();
  return (r < (double)p) ? 5 : 1;
}

struct GMStub {
  void M50(int a, int b);   // 0xb5b800-dispatch: vt[3]
  void M80(int a, int b);   // empire-dispatch:    vt[4]
  static void* GetEmpire(); // 0x1021300
};
struct EmpireStub {
  void Prep();              // 0xc30c60, __thiscall
};
// @ 0x00ba7050
void GMStub::M50(int a, int b) {
  if ((void*)FUN_00b5b800() == &g_1654c05) {
    void* o = *(void**)((char*)this + 0x204);
    int* vt = *(int**)o;
    ((void(__thiscall*)(void*, int, int))vt[3])(o, a, b);
  }
}
// @ 0x00ba7080
void GMStub::M80(int a, int b) {
  EmpireStub* o = (EmpireStub*)FUN_01021300();
  o->Prep();
  void* q = *(void**)((char*)this + 0x204);
  int* vt = *(int**)q;
  ((void(__thiscall*)(void*, int, int))vt[4])(q, a, b);
}

struct Vec50Obj {
  char pad000[0x50];
  int* m50;   // +0x50
  int* m54;   // +0x54
  void Erase(int value);
};
// @ 0x00ba70d0
void Vec50Obj::Erase(int value) {
  int* p = m50;
  int* end = m54;
  while (p != end) {
    if (*p == value) {
      *p = end[-1];
      m54 -= 1;
      return;
    }
    ++p;
  }
}

// @ 0x00ba7100
void FUN_00ba7100(float* pos, int* outx, int* outy) {
  float s = 64.0f / g_156c638;
  int x = (int)(pos[0] * s) + 0x20;
  int y = (int)(pos[1] * s) + 0x20;
  int z = 0;
  int* px = (x < 0x3f) ? &x : (int*)&g_1459c40;
  if (*px <= 0) px = &z;
  *outx = *px;
  int* py = (y < 0x3f) ? &y : (int*)&g_1459c40;
  if (*py > 0) { *outy = *py; return; }
  *outy = 0;
}

// @ 0x00ba71b0
void* FUN_00ba71b0(void* civ, int* vec) {
  int* p = (int*)vec[0];
  void* best = 0;
  float bestScore = g_1465eb8;
  while (p != (int*)vec[1]) {
    void* c = (void*)*p;
    float score = FUN_010434c0(civ, FUN_005c65e0(c));
    if (score < bestScore) { best = c; bestScore = score; }
    ++p;
  }
  return best;
}

// @ 0x00ba7220
struct StarManagerCore {
  char pad000[0xc8];
  void* mC8;   // +0xc8
  void* mCC;   // +0xcc
};
void FUN_00ba7220(StarManagerCore* self, int* key) {
  char* grp = (char*)self->mC8;
  char* end = (char*)self->mCC;
  if (grp == end) return;
  do {
    int* p = *(int**)grp;
    int* e = *(int**)(grp + 4);
    if (p != e) {
      do {
        int obj = *p;
        if (*(int*)(obj + 0x74) == key[0] &&
            *(int*)(obj + 0x78) == key[1] &&
            *(int*)(obj + 0x7c) == key[2]) {
          ((GameObj*)obj)->OnBan();
        }
        ++p;
      } while (p != e);
    }
    grp += 0x14;
  } while (grp != end);
}

// @ 0x00ba72c0
void* FUN_00ba72c0(void* writer, int* vec) {
  int count = (vec[1] - vec[0]) >> 2;
  IStream* s = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
  IWriter* w = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093aa70(w, &count, 1, 0);
  for (int i = 0; i < count; ++i) {
    ((void(__thiscall*)(void*, int))(*(int**)writer)[11])(writer, ((int*)vec[0])[i]);
  }
  return writer;
}

// @ 0x00ba7320
int FUN_00ba7320(int* vec) {
  int* p = (int*)vec[0];
  int* e = (int*)vec[1];
  double total = 0.0;
  if (p == e) return (int)((int)e - (int)p) >> 2;
  for (; p != e; ++p) total += (double)*p;
  if (total <= 0.0) return (int)((int)e - (int)(int*)vec[0]) >> 2;
  double r = ((Rng*)0x1601760)->Next() * total;
  if (r < total) {
    double acc = 0.0;
    int idx = 0;
    for (int* q = (int*)vec[0]; q != (int*)vec[1]; ++q, ++idx) {
      acc += (double)*q;
      if (r < acc) return idx;
    }
  }
  return ((vec[1] - vec[0]) >> 2) - 1;
}

// @ 0x00ba73b0
void FUN_00ba73b0(void* writer, int* vec) {
  int count = (vec[1] - vec[0]) / 0x14;
  IStream* s = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
  IWriter* w = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093aa70(w, &count, 1, 0);
  char* p = (char*)vec[0];
  char* e = (char*)vec[1];
  for (; p != e; p += 0x14) FUN_00ba72c0(writer, (int*)p);
  ((void(__thiscall*)(void*))(*(int**)writer)[7])(writer);
}

// @ 0x00ba7450
char FUN_00ba7450(int arg, char* node) {
  char* e = node + 4;
  for (char* n = *(char**)(node + 8); n != e; n = (char*)FUN_00921580(n)) {
    void* o = *(void**)(n + 0x14);
    if (o) ((void(__thiscall*)(void*, int))(*(int**)o)[7])(o, arg);
  }
  return 1;
}

// @ 0x00ba7490
void FUN_00ba7490(void* writer, int* vec) {
  int count = (vec[1] - vec[0]) >> 4;
  IStream* s = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
  IWriter* w = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093aa70(w, &count, 1, 0);
  char* p = (char*)vec[0];
  char* e = (char*)vec[1];
  for (; p != e; p += 0x10) {
    IStream* s2 = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
    IWriter* w2 = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s2)[6])(s2);
    FUN_00692e00(((void*(__thiscall*)(void*, char*))(*(int**)w2)[6])(w2, p));
  }
  ((void(__thiscall*)(void*))(*(int**)writer)[7])(writer);
}

// @ 0x00ba7510
void FUN_00ba7510(void* writer, int* vec) {
  int count = (vec[1] - vec[0]) >> 4;
  IStream* s = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
  IWriter* w = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093aa70(w, &count, 1, 0);
  char* p = (char*)vec[0];
  char* e = (char*)vec[1];
  for (; p != e; p += 0x10) {
    IStream* s2 = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
    IWriter* w2 = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s2)[6])(s2);
    FUN_00692e50(((void*(__thiscall*)(void*, char*))(*(int**)w2)[6])(w2, p));
  }
  ((void(__thiscall*)(void*))(*(int**)writer)[7])(writer);
}

// @ 0x00ba7590
void FUN_00ba7590(void* writer, char* node) {
  int first = *(int*)(node + 0x14);
  IStream* s = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
  IWriter* w = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093aa70(w, &first, 1, 0);
  char* e = node + 4;
  for (char* n = *(char**)(node + 8); n != e; n = (char*)FUN_00921580(n)) {
    IStream* s2 = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
    IWriter* w2 = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s2)[6])(s2);
    int v = *(int*)(n + 0x10);
    FUN_0093aa70(w2, &v, 1, 0);
    ((void(__thiscall*)(void*))(*(int**)writer)[7])(writer);
    IStream* s3 = (IStream*)((void*(__thiscall*)(void*))(*(int**)writer)[8])(writer);
    IWriter* w3 = (IWriter*)((void*(__thiscall*)(void*))(*(int**)s3)[6])(s3);
    int v2 = *(int*)(n + 0x14);
    FUN_0093aa70(w3, &v2, 1, 0);
    ((void(__thiscall*)(void*))(*(int**)writer)[7])(writer);
  }
  ((void(__thiscall*)(void*))(*(int**)writer)[7])(writer);
}

// @ 0x00ba7660
void FUN_00ba7660(IRefObj** first, IRefObj** last) {
  if (first == last) return;
  for (IRefObj** cur = first + 1; cur != last; ++cur) {
    IRefObj* item = *cur;
    if (item) item->AddRef();
    IRefObj** hole = cur;
    while (hole != first) {
      IRefObj* prev = *(hole - 1);
      if (item->mScore >= prev->mScore) break;
      IRefObj* old = *hole;
      if (prev != old) {
        if (prev) prev->AddRef();
        *hole = prev;
        if (old) old->Release();
      }
      --hole;
    }
    IRefObj* old = *hole;
    if (item != old) {
      if (item) item->AddRef();
      *hole = item;
      if (old) old->Release();
    }
    if (item) item->Release();
  }
}
