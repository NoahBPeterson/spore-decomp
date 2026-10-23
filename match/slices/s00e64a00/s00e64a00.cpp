// Slice s00e64a00 (batch spcg1, slice 2) — SPGonzago/SPCellGame.obj.
// Cell-gfx teardown / per-entry sound patching plus a family of EASTL container helpers
// (vector_map erase/operator[]/insert, rbtree find/emplace, intrusive-ptr push_back).
// Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---- globals ----
extern "C" char  gspCellGame_16b3c04[];   // holds SP::cCellGame*
extern "C" char  g_16b3c08[];             // holds SP::cCellGfx*
extern "C" char  g_16b3c0c[];             // holds the UI manager*
extern "C" char  g_15fd918[];             // cDirectPropertyList*
extern "C" char  gSoundBase[];            // 0x015a8434  sound-pair table (0x18-byte stride)
extern "C" uint32_t gKeyDefaultA, gKeyDefaultB, gKeyDefaultC;   // 0x016b3dd4 /d8 /dc
extern "C" float k15a7d0c;                // 0x015a7d0c
extern "C" void* gArrA16b4178[0x40];      // 0x016b4178  layout pointer table
extern "C" unsigned char gArrB16b4278[0x40]; // 0x016b4278 visible flags

#define G   (*(char**)gspCellGame_16b3c04)
#define GG  (*(char**)g_16b3c08)
#define GUI (*(char**)g_16b3c0c)

struct cSPUILayout { void SetVisibility(bool v); };            // 0x00810590
struct PropList    { void SetBoolProperty(int key, bool v); }; // 0x006a17e0

// ---- pools / intrusive handles ----
struct Pool {
  int   Begin();            // 0x00e31100
  void* Next(int* it);      // 0x00b72230, ret 4
  void  Remove(int id);     // 0x00b72260, ret 4
};
struct Ref { void* p; void Init(); void Release(); };          // 0x00743b50 / 0x00e82130

// ---- external free callees ----
extern "C" void* __cdecl FUN_00b41ea0(void* first, void* last, void* key, unsigned char flag); // lower_bound
extern "C" void* __cdecl FUN_005701b0(void* first, void* last, void* key, unsigned char flag); // lower_bound
extern "C" void* __cdecl FUN_00e61830(void* first, void* last, void* key, unsigned char flag); // lower_bound
extern "C" void* __cdecl FUN_00e618c0(void* a, void* b, void* c); // 0x00e618c0
extern "C" void* __cdecl FUN_00e61880(void* a, void* b, void* c); // 0x00e61880
extern "C" void  __cdecl FUN_00e5c820(void* a, void* b, void* c); // 0x00e5c820
extern "C" void  __cdecl FUN_00e61930(void* a, void* b, void* c); // 0x00e61930
extern "C" int   __cdecl FUN_00e59d90(int v);                     // 0x00e59d90
extern "C" void  __cdecl FUN_00e826e0(void* p);                   // 0x00e826e0
extern "C" void* __cdecl FUN_00e82620(void* a, void* b);          // 0x00e82620 PatchSoundStart
extern "C" void  __cdecl FUN_00e82700(void* a, void* b);          // 0x00e82700
extern "C" void  __cdecl FUN_00e82500(int v);                     // 0x00e82500
extern "C" void* __cdecl FUN_0067dd40();                          // 0x0067dd40
extern "C" void* __cdecl FUN_0067dd80();                          // 0x0067dd80 SP::ModelManager
extern "C" void* __cdecl FUN_0067ddd0();                          // 0x0067ddd0 SP::EffectsManager
extern "C" void* __cdecl FUN_0067dd50();                          // 0x0067dd50
extern "C" void* __cdecl FUN_00b3d400();                          // 0x00b3d400
extern "C" void* __cdecl FUN_00b3d4d0();                          // 0x00b3d4d0 GetTriggerMgr
extern "C" void* __cdecl FUN_00b3d3f0();                          // 0x00b3d3f0
extern "C" void  __cdecl FUN_00e180d0(void* self);                // 0x00e180d0 (this=ecx)
extern "C" void  __cdecl FUN_00ad7dc0(void* self);                // 0x00ad7dc0 Sim::goStop
extern "C" void  __cdecl FUN_00ad7e40(void* self, int v);         // 0x00ad7e40 Screen::setModal
extern "C" void  __cdecl FUN_00e19010(void* self);                // 0x00e19010 cPanel
extern "C" void* __cdecl FUN_00e4ce40(Ref* out);                  // 0x00e4ce40
extern "C" void* __cdecl FUN_00e823a0(int id, Ref* out);          // 0x00e4cc40 (alias thunk)
extern "C" void* __cdecl FUN_00e5c250(void* out, int a);          // 0x00e5c250
extern "C" void  __cdecl FUN_00e58c90(void* p);                   // 0x00e58c90
extern "C" void* __cdecl operator_new(int size, const char*, int, int, const char*, int); // 0xf473a0
extern "C" void  __cdecl operator_delete(void* p);                // 0xf47380
extern "C" long  _InterlockedExchangeAdd(volatile long*, long);   // intrinsic

// ---- vtable accessors ----
#define VT(p) (*(void***)(p))
typedef void (__thiscall *PFN_i)(void*, int);
typedef void (__cdecl   *PFN_ci)(void*, int);
typedef void (__stdcall *PFN_si)(void*, int);
typedef void (__stdcall *PFN_sb)(void*, bool);
static inline void VCall_v(void* p, int slot) { ((void(__thiscall*)(void*))VT(p)[slot / 4])(p); }
static inline void VCall_i(void* p, int slot, int a) { ((PFN_i)VT(p)[slot / 4])(p, a); }

// ---- gfx / cell-gfx objects ----
// 0x2c-byte-element vector (sound entries) living inside cCellGfx; erase() callee-cleans.
struct Vec2c { void* mpBegin; void* mpEnd; void* mpCap; void eraseRange(void* first, void* last); };

// 0x74-byte-element vector; erase()/insertGrow() are slice functions.
struct ObjVec {
  void* mpBegin; void* mpEnd; void* mpCap;
  void* erase(void* first, void* last);          // 0x00e65180
  void  insertGrow(void* pos, void* val);        // 0x00e65200
};

// 0x74-byte element helpers (this = element pointer).
struct Obj74 {
  int f00,f04,f08,f0c,f10,f14,f18,f1c,f20,f24,f28,f2c,f30,f34,f38,f3c,f40,
      f44,f48,f4c,f50,f54,f58,f5c,f60,f64,f68,f6c,f70;
  void ctor(const void* src);      // 0x00e61750
  void assign(const void* src);    // 0x00e61000
};
struct Obj30 { char d[0x30]; void ctor0(); };   // 0x00e619a0

// object holding a vector of intrusive refs at +0x14 (refcount at +8)
struct RefPtrVec {
  void* mpBegin;
  void* mpEnd;
  void* mpCap;
  void  doInsertRef(void* pos, void** val);   // 0x00425a80
};

// object whose ref-vector lives at +0x14 (FUN_00e65970 is a member of this)
struct RefVecOwner {
  char       pad00[0x14];
  RefPtrVec  vec;
  void       push(Ref* p);                    // 0x00e65970 (thiscall, ret 4)
};

struct cCellGfx {
  void*   mpVecObjBegin;   // +0x00  (EA::AutoRefCount<...>, refcount +0x40)
  void*   mpVecObjEnd;     // +0x04
  void*   mpVecObjCap;     // +0x08
  void*   mp0c;            // +0x0c
  void*   mp10;            // +0x10
  void*   mpVecRefBegin;   // +0x14  (EA::AutoRefCount<...>, refcount +0x08)
  void*   mpVecRefEnd;     // +0x18
  void*   mpVecRefCap;     // +0x1c
  char    pad20[0x54 - 0x20];
  void*   mp54;            // +0x54  object-factory interface
  void*   mp58;            // +0x58
  void*   mSlots[0x40];    // +0x5c .. +0x15c
  void*   mp15c;           // +0x15c
  void*   mp160;           // +0x160
  void*   mp164;           // +0x164
  char    pad168[0x184 - 0x168];
  void*   mpVec2cBegin;    // +0x184
  void*   mpVec2cEnd;      // +0x188
  void*   mpVec2cCap;      // +0x18c
  char    pad190[0x161a8 - 0x190];
  void*   mp161a8;         // +0x161a8
  void*   mp161ac;         // +0x161ac
  void*   mp161b0;
  void*   mp161b4;         // +0x161b4
  void*   mp161b8;
  void*   mp161bc;         // +0x161bc
  void*   mp161c0;         // +0x161c0
  void*   mp161c4;
  void*   mp161c8;         // +0x161c8
  void*   mp161cc;         // +0x161cc
  void*   mp161d0;
  void*   mp161d4;         // +0x161d4
  void*   mp161d8;
  ObjVec  mObjVec;         // +0x161dc
  char    pad161e8[0x16208 - 0x161e8];
  void*   mp16208;         // +0x16208
  void*   mp1620c;         // +0x1620c
  void*   mp16210;         // +0x16210
  char    pad16214[0x16258 - 0x16214];
  int     m16258;          // +0x16258

  void    pushObj(void* p);            // 0x00e653a0
  void    doInsertObj(void* pos, void** val);  // 0x00423c40
};

// 0x2c-byte element map (key -> value), allocator flag at +0x4018.
struct KPair { int key; int val; };
struct KeyMap {
  KPair*   mpBegin;   // +0
  KPair*   mpEnd;     // +4
  char     pad08[0x4018 - 8];
  unsigned char mbFlag;   // +0x4018
  int      erase(KPair* key);          // 0x00e64fc0
  KPair*   insertAt(KPair* pos, KPair* val); // 0x00e650c0
  int*     operatorIndex(KPair* key);  // 0x00e65730
  KPair*   insertElem(KPair* pos, KPair* val); // 0x00e64480
};
struct SoundMap {
  KPair*   mpBegin;
  KPair*   mpEnd;
  char     pad08[0x16018 - 8];
  unsigned char mbFlag;   // +0x16018
  KPair*   insertAt(KPair* pos, KPair* val);  // 0x00e65120
  int*     operatorIndex(KPair* key);         // 0x00e65790
  KPair*   insertElem(KPair* pos, KPair* val); // 0x00e644e0
};
struct KeyMap4 {
  unsigned* mpBegin;
  unsigned* mpEnd;
  char      pad08[0x2018 - 8];
  unsigned char mbFlag;   // +0x2018
  unsigned* operatorIndex(unsigned* key);     // 0x00e65840
  unsigned* insertElem(unsigned* pos, unsigned* val); // 0x00e65340
};

// eastl rbtree (anchor at +4, root at +0xc)
struct RbTree {
  char   pad0[4];
  void*  mAnchor;     // +4
  void*  mp8;         // +8
  void*  mRoot;       // +0xc
  void*  find(void** out, const unsigned* key);   // 0x00e5c780
  void*  insert(const unsigned* key);             // 0x00e65030
  void*  doInsertValue(void* out, void* parent, void* val, unsigned char flag); // 0x01011280
};

struct cCellGame {
  char     pad000[0xc4];
  char     mPoolC4[4];       // +0xc4 (pool)
  char     padC8[0xe0 - 0xc8];
  KeyMap   mKeyMap;          // +0xe0
  char     pad40fc[0x5160 - (0xe0 + 0x4019)];
  int      mField5160;       // +0x5160
  char     pad5164[0x5170 - 0x5164];
  RbTree   mRb5170;          // +0x5170
  char     pad5180[0x5190 - (0x5170 + 0x10)];
  void*    mp5190;           // +0x5190
};

// ------------------------------------------------------------------
// 0x00e64a00  SP::sDeactivateGfx
void sDeactivateGfx() {
  int it = ((Pool*)(GUI + 0x9c))->Begin();
  void* w;
  while ((w = ((Pool*)(GUI + 0x9c))->Next(&it)) != 0) {
    cSPUILayout* layout = *(cSPUILayout**)((char*)w + 0x34);
    layout->SetVisibility(false);
    for (int i = 0; i < 0x40; ++i) {
      if (gArrA16b4178[i] == layout) { gArrB16b4278[i] = 0; break; }
    }
    ((Pool*)(GUI + 0x9c))->Remove(*(int*)w);
  }

  ((PropList*)g_15fd918)->SetBoolProperty(0x387d0a8, false);

  if (*(char**)(GG + 0x184) != *(char**)(GG + 0x188)) {
    char* e = *(char**)(GG + 0x184);
    do {
      void* s28 = *(void**)(e + 0x28);
      if (s28) { FUN_00e826e0(s28); *(void**)(e + 0x28) = 0; }
      void* s24 = *(void**)(e + 0x24);
      if (s24) { FUN_00e826e0(s24); *(void**)(e + 0x24) = 0; }
      char* last = *(char**)(GG + 0x188);
      char* dst = e;
      for (char* src = e + 0x2c; src != last; src += 0x2c, dst += 0x2c) {
        *(uint32_t*)(dst + 0x00) = *(uint32_t*)(src + 0x00);
        *(uint32_t*)(dst + 0x04) = *(uint32_t*)(src + 0x04);
        *(uint32_t*)(dst + 0x08) = *(uint32_t*)(src + 0x08);
        *(uint32_t*)(dst + 0x0c) = *(uint32_t*)(src + 0x0c);
        *(uint32_t*)(dst + 0x10) = *(uint32_t*)(src + 0x10);
        *(uint32_t*)(dst + 0x14) = *(uint32_t*)(src + 0x14);
        *(uint32_t*)(dst + 0x18) = *(uint32_t*)(src + 0x18);
        *(uint32_t*)(dst + 0x1c) = *(uint32_t*)(src + 0x1c);
        *(uint32_t*)(dst + 0x20) = *(uint32_t*)(src + 0x20);
        *(uint32_t*)(dst + 0x24) = *(uint32_t*)(src + 0x24);
        *(uint32_t*)(dst + 0x28) = *(uint32_t*)(src + 0x28);
      }
      *(int*)(GG + 0x188) -= 0x2c;
    } while (e != *(char**)(GG + 0x188));
  }
  ((Vec2c*)(GG + 0x184))->eraseRange(*(void**)(GG + 0x184), *(void**)(GG + 0x188));

  FUN_00e826e0(*(void**)(GG + 0x16208));
  FUN_00e826e0(*(void**)(GG + 0x16210));
  FUN_00e826e0(*(void**)(GG + 0x1620c));

  FUN_00e180d0(FUN_00b3d400());
  FUN_00ad7dc0(FUN_00b3d4d0());
  FUN_00ad7e40(FUN_00b3d4d0(), 0);
  *(uint8_t*)(GUI + 0x936) = 0;
  (*(cSPUILayout**)(GUI + 0x90))->SetVisibility(false);
  FUN_00e19010(FUN_00b3d3f0());

  Ref r1; r1.Init();
  char* info = (char*)FUN_00e4ce40(&r1);
  Ref r2; r2.Init();
  int* list = (int*)FUN_00e823a0(*(int*)(info + 0x3c), &r2);
  int n = *list;
  for (int i = 0; i < n; ++i) {
    void** slot = (void**)(GG + 0x5c + i * 4);
    void* p = *slot;
    if (p) {
      VCall_i(p, 0xc, 1);
      p = *slot;
      if (p) { *slot = 0; VCall_v(p, 4); }
    }
  }
  VCall_v(FUN_0067dd40(), 0x30);
  VCall_i(*(void**)(GG + 0x15c), 0xc, 1);
  VCall_i(*(void**)(GG + 0x160), 0xc, 1);
  {
    void* p = *(void**)(GG + 0x160);
    if (p) { *(void**)(GG + 0x160) = 0; VCall_v(p, 4); }
  }
  VCall_i(*(void**)(GG + 0x164), 0xc, 1);
  {
    void* p = *(void**)(GG + 0x164);
    if (p) { *(void**)(GG + 0x164) = 0; VCall_v(p, 4); }
  }
  *(int*)(GG + 0x16258) = 0;
  VCall_i(FUN_0067dd80(), 0x24, 0);
  VCall_i(FUN_0067ddd0(), 0x58, 0);
  VCall_i(FUN_0067dd50(), 0x50, 0xd);
  VCall_i(FUN_0067dd50(), 0x50, 5);
  VCall_i(FUN_0067dd50(), 0x50, 2);
  VCall_i(FUN_0067dd50(), 0x50, 0x18);
  VCall_i(*(void**)(GG + 0x161c0), 0x134, 0);
  VCall_i(*(void**)(GG + 0x161a8), 0x134, 0);
  VCall_i(*(void**)(GG + 0x161cc), 0x134, 0);
  VCall_i(*(void**)(GG + 0x161b4), 0xc, 2);
  VCall_i(*(void**)(GG + 0x161bc), 0xc, 2);
  VCall_i(*(void**)(GG + 0x161ac), 0xc, 2);
  VCall_i(*(void**)(GG + 0x161c8), 0xc, 2);
  VCall_i(*(void**)(GG + 0x161d4), 0xc, 2);
  FUN_00e82500(0);
  r2.Release();
  r1.Release();
}

// ------------------------------------------------------------------
// 0x00e64e10  per-entry sound patch/update
void FUN_00e64e10() {
  char* e = *(char**)(GG + 0x184);
  if (e == *(char**)(GG + 0x188)) return;
  char* pNext  = e + 0x2c;
  char* pSound = e + 0x14;
  char* pCur   = e;
  do {
    int sel = *(int*)(*(int*)(G + 0x5190) + 0x74);
    if (*(int*)(e + 0xc) != sel) {
      if (*(int*)(e + 0x10) >= sel - 5) {
        FUN_00e82700(*(void**)(e + 0x28), pSound);
      } else {
        FUN_00e826e0(*(void**)(e + 0x28));
        if (*(void**)(e + 0x28) != 0) { FUN_00e826e0(*(void**)(e + 0x28)); *(void**)(e + 0x28) = 0; }
        if (*(void**)(e + 0x24) != 0) { FUN_00e826e0(*(void**)(e + 0x24)); *(void**)(e + 0x24) = 0; }
        char* last = *(char**)(GG + 0x188);
        char* d = pCur;
        char* s = pNext;
        if (s != last) {
          do {
            *(uint32_t*)(d + 0x00) = *(uint32_t*)(s + 0x00);
            *(uint32_t*)(d + 0x04) = *(uint32_t*)(s + 0x04);
            *(uint32_t*)(d + 0x08) = *(uint32_t*)(s + 0x08);
            *(uint32_t*)(d + 0x0c) = *(uint32_t*)(s + 0x0c);
            *(uint32_t*)(d + 0x10) = *(uint32_t*)(s + 0x10);
            *(uint32_t*)(d + 0x14) = *(uint32_t*)(s + 0x14);
            *(uint32_t*)(d + 0x18) = *(uint32_t*)(s + 0x18);
            *(uint32_t*)(d + 0x1c) = *(uint32_t*)(s + 0x1c);
            *(uint32_t*)(d + 0x20) = *(uint32_t*)(s + 0x20);
            *(uint32_t*)(d + 0x24) = *(uint32_t*)(s + 0x24);
            *(uint32_t*)(d + 0x28) = *(uint32_t*)(s + 0x28);
            s += 0x2c; d += 0x2c;
          } while (s != last);
        }
        *(int*)(GG + 0x188) -= 0x2c;
      }
    } else if (*(char*)(e + 0x20) == 1) {
      int a = FUN_00e59d90(*(int*)(e + 4));
      int b = FUN_00e59d90(*(int*)(e + 8));
      int mn = b, mx = a;
      if (a < b) { mn = a; mx = b; }
      unsigned idx = (((unsigned)(mx * (mx - 1)) >> 1) + (unsigned)mn);
      void* s = FUN_00e82620(*(void**)(gSoundBase + idx * 0x18), pSound);
      FUN_00e82700(s, pSound);
      *(void**)(e + 0x24) = s;
    } else {
      int a = FUN_00e59d90(*(int*)(e + 4));
      int b = FUN_00e59d90(*(int*)(e + 8));
      int mn = b, mx = a;
      if (a < b) { mn = a; mx = b; }
      unsigned idx = (((unsigned)(mx * (mx - 1)) >> 1) + (unsigned)mn);
      void* s = FUN_00e82620(*(void**)(gSoundBase + idx * 0x18 + 8), pSound);
      FUN_00e82700(s, pSound);
      *(void**)(e + 0x28) = s;
    }
    pNext += 0x2c; pSound += 0x2c; pCur += 0x2c; e += 0x2c;
  } while (e != *(char**)(GG + 0x188));
}

// ------------------------------------------------------------------
// 0x00e64fc0  KeyMap::erase
int KeyMap::erase(KPair* key) {
  KPair* end = mpEnd;
  KPair* e = (KPair*)FUN_00b41ea0(mpBegin, end, key, mbFlag);
  // the `e + 1 == e` term is always false; kept because the original object
  // contains the compiler's redundant self-compare at this site.
  if (e == end || key->key < e->key || e + 1 == e) e = end;
  if (e == end) return 0;
  for (KPair* p = e + 1; p != end; ++p) p[-1] = p[0];
  --mpEnd;
  return 1;
}

// ------------------------------------------------------------------
// 0x00e65030  eastl rbtree::DoInsertValue wrapper (returns node+0x14)
void* RbTree::insert(const unsigned* key) {
  void** anchor = (void**)((char*)this + 4);
  void*  parent = anchor;
  void*  node = mRoot;
  while (node) {
    if (*(unsigned*)((char*)node + 0x10) < *key) node = *(void**)node;
    else { parent = node; node = *(void**)((char*)node + 4); }
  }
  if (parent != (void*)anchor && *(unsigned*)((char*)parent + 0x10) <= *key)
    return (char*)parent + 0x14;
  unsigned val[4];
  val[0] = *key; val[1] = 0; val[2] = 0; val[3] = 0;
  return (char*)doInsertValue(anchor, parent, val, 0) + 0x14;
}

// ------------------------------------------------------------------
// 0x00e650c0  KeyMap::insertAt
KPair* KeyMap::insertAt(KPair* pos, KPair* val) {
  KPair* end = mpEnd;
  KPair* e;
  if (pos != end && val->key < pos->key)
    e = (KPair*)FUN_00b41ea0(mpBegin, pos, val, mbFlag);
  else
    e = (KPair*)FUN_00b41ea0(pos, end, val, mbFlag);
  if (e == end || val->key < e->key) e = insertElem(e, val);
  return e;
}

// ------------------------------------------------------------------
// 0x00e65120  SoundMap::insertAt
KPair* SoundMap::insertAt(KPair* pos, KPair* val) {
  KPair* end = mpEnd;
  KPair* e;
  if (pos != end && val->key < pos->key)
    e = (KPair*)FUN_00e61830(mpBegin, pos, val, mbFlag);
  else
    e = (KPair*)FUN_00e61830(pos, end, val, mbFlag);
  if (e == end || val->key < e->key) e = insertElem(e, val);
  return e;
}

// ------------------------------------------------------------------
// 0x00e65180  ObjVec::erase (0x74-byte elements)
void* ObjVec::erase(void* first, void* last) {
  char* e = (char*)FUN_00e618c0(last, mpEnd, first);
  char* endp = (char*)mpEnd;
  if (e < endp) {
    char* p = e + 0x70;
    int n = (int)((unsigned)(endp - e - 1) / 0x74) + 1;
    do {
      void* o = *(void**)p;
      if (o) ((void(__thiscall*)(void*))VT(o)[1])(o);
      p += 0x74;
    } while (--n);
  }
  mpEnd = (char*)mpEnd - ((int)((char*)last - (char*)first) / 0x74) * 0x74;
  return first;
}

// ------------------------------------------------------------------
// 0x00e65200  ObjVec::insertGrow (0x74-byte elements)
void ObjVec::insertGrow(void* pos, void* val) {
  char* e = (char*)mpEnd;
  if (e != (char*)mpCap) {
    if (pos <= val && val < e) val = (char*)val + 0x74;
    if (e != 0) ((Obj74*)e)->ctor((char*)e - 0x74);
    FUN_00e61930(pos, (char*)mpEnd - 0x74, mpEnd);
    ((Obj74*)pos)->assign(val);
    mpEnd = (char*)mpEnd + 0x74;
    return;
  }
  int n = (int)((e - (char*)mpBegin) / 0x74);
  char* buf;
  int cap;
  if (n == 0) { cap = 1; }
  else { cap = n * 2; if (cap == 0) { buf = 0; goto alloc_done; } }
  buf = (char*)operator_new(cap * 0x74, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
alloc_done:
  char* src = (char*)mpBegin;
  char* p1 = (char*)FUN_00e61880(src, pos, buf);
  FUN_00e5c820(src, pos, buf);
  if (p1 != 0) ((Obj74*)p1)->ctor(val);
  char* endp = (char*)mpEnd;
  char* p2 = (char*)FUN_00e61880(pos, endp, p1 + 0x74);
  FUN_00e5c820(pos, endp, p1 + 0x74);
  if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0) operator_delete(mpBegin);
  mpBegin = buf;
  mpEnd = p2;
  mpCap = buf + cap * 0x74;
}

// ------------------------------------------------------------------
// 0x00e653a0  cCellGfx::pushObj (intrusive ptr, refcount at +0x40)
void cCellGfx::pushObj(void* p) {
  if (p) *(int*)((char*)p + 0x40) += 1;
  void** endp = (void**)*(void**)((char*)this + 4);
  if (endp < (void**)*(void**)((char*)this + 8)) {
    *(void**)((char*)this + 4) = endp + 1;
    if (endp) {
      *endp = p;
      if (p) *(int*)((char*)p + 0x40) += 1;
    }
  } else {
    doInsertObj(endp, &p);
  }
  if (p) {
    int n = *(int*)((char*)p + 0x40);
    if (n > 1) { *(int*)((char*)p + 0x40) = n - 1; return; }
    int x = *(int*)((char*)p + 4);
    void* c = *(void**)p;
    ((PFN_sb)VT(c)[0x170 / 4])(p, (unsigned)x >> 31);
  }
}

// ------------------------------------------------------------------
// 0x00e65410  create+retain+store a gfx object
void FUN_00e65410(int id, bool flag) {
  void* iface = *(void**)(GG + 0x54);
  void* r = (void*)((void*(__thiscall*)(void*, int, int, int))VT(iface)[0xc / 4])(iface, id, 0, 0);
  if (!r) return;
  *(int*)((char*)r + 0x40) += 1;
  ((cCellGfx*)GG)->pushObj(r);
  if (flag) {
    void* q = *(void**)(GG + 0x54);
    ((void(__thiscall*)(void*, void*))VT(q)[0x58 / 4])(q, r);
  }
  int n = *(int*)((char*)r + 0x40);
  if (n > 1) { *(int*)((char*)r + 0x40) = n - 1; return; }
  void* c = *(void**)r;
  ((PFN_sb)VT(c)[0x170 / 4])(r, (unsigned)*(int*)((char*)r + 4) >> 31);
}

// ------------------------------------------------------------------
// 0x00e65480  erase a cell-pair key from the key map
void FUN_00e65480(unsigned a, unsigned b) {
  struct P { unsigned short lo, hi; };
  P k;
  if (a < b) { k.hi = (unsigned short)a; k.lo = (unsigned short)b; }
  else       { k.hi = (unsigned short)b; k.lo = (unsigned short)a; }
  ((KeyMap*)(G + 0xe0))->erase((KPair*)&k);
}

// ------------------------------------------------------------------
// 0x00e654d0  tick + prune the cell-pair pool
void FUN_00e654d0() {
  for (int i = 10; i != 0; --i) {
    int it = ((Pool*)(G + 0xc4))->Begin();
    void* e;
    while ((e = ((Pool*)(G + 0xc4))->Next(&it)) != 0) {
      if (*(int*)((char*)e + 0x3c) == *(int*)(G + 0x5160)) {
        FUN_00e58c90(e);
      } else {
        unsigned a = *(unsigned*)((char*)e + 4);
        unsigned b = *(unsigned*)((char*)e + 8);
        ((Pool*)(G + 0xc4))->Remove(*(int*)e);
        struct Pair16 { uint16_t lo; uint16_t hi; };
        Pair16 k;
        if (a < b) { k.hi = (uint16_t)a; k.lo = (uint16_t)b; }
        else       { k.hi = (uint16_t)b; k.lo = (uint16_t)a; }
        ((KeyMap*)(G + 0xe0))->erase((KPair*)&k);
      }
    }
  }
}

// ------------------------------------------------------------------
// 0x00e655c0  SP::sGetRandomCreatureKey
int* FUN_00e655c0(unsigned key, int a) {
  char* g = G;
  RbTree* tree = (RbTree*)(g + 0x5170);
  void* out;
  unsigned* found = (unsigned*)tree->find(&out, &key);
  if (*found != (unsigned)(g + 0x5174))
    return (int*)tree->insert(&key);
  int* p = (int*)tree->insert(&key);
  int tmp[3];
  int* r = (int*)FUN_00e5c250(tmp, a);
  p[0] = r[0]; p[1] = r[1]; p[2] = r[2];
  return p;
}

// generic 12-byte triple returned by value
struct Key3 { int a, b, c; };

// ------------------------------------------------------------------
// 0x00e65640  SP::sGetCreatureKey
Key3 FUN_00e65640(int a) {
  Ref t1; t1.Init();
  int* p = (int*)FUN_00e823a0(a, &t1);
  Ref t2; t2.Init();
  char* li = (char*)FUN_00e823a0(*p, &t2);
  Key3 r;
  int n = *(int*)(li + 0x18);
  int i = 0;
  if (n > 0) {
    char* e = *(char**)(li + 0x14);
    do {
      int kind = *(int*)(e + 4);
      if (kind == 3) {
        r.a = *(int*)(e + 0x10);
        r.b = 0x3d97a8e4;
        r.c = *(int*)&k15a7d0c;
        goto release;
      } else if (kind == 4) {
        int* q = FUN_00e655c0(*p, *(int*)(e + 0xc));
        r.a = q[0]; r.b = q[1]; r.c = q[2];
        goto release;
      } else if (kind == 5) {
        char* d = *(char**)(G + 0x5190);
        r.a = *(int*)(d + 0x10);
        r.b = *(int*)(d + 0x14);
        r.c = *(int*)(d + 0x18);
        goto release;
      }
      ++i; e += 0x28;
    } while (i < n);
  }
  r.a = gKeyDefaultA;
  r.b = gKeyDefaultB;
  r.c = gKeyDefaultC;
release:
  t2.Release(); t1.Release();
  return r;
}

// ------------------------------------------------------------------
// 0x00e65730  KeyMap::operator[]
int* KeyMap::operatorIndex(KPair* key) {
  KPair* end = mpEnd;
  KPair* e = (KPair*)FUN_00b41ea0(mpBegin, end, key, mbFlag);
  if (e == end || key->key < e->key) {
    KPair local;
    local.key = key->key;
    local.val = 0;
    e = (KPair*)insertAt(e, &local);
  }
  return (int*)e + 1;
}

// ------------------------------------------------------------------
// 0x00e65790  SoundMap::operator[]
int* SoundMap::operatorIndex(KPair* key) {
  KPair* end = mpEnd;
  KPair* e = (KPair*)FUN_00e61830(mpBegin, end, key, mbFlag);
  if (e == end || key->key < e->key) {
    KPair local[6];
    local[0].key = key->key;
    local[0].val = key->key;
    for (int i = 1; i < 11; ++i) ((int*)local)[i] = key->key;
    e = (KPair*)insertAt(e, local);
  }
  return (int*)e + 1;
}

// ------------------------------------------------------------------
// 0x00e65840  KeyMap4::operator[]
unsigned* KeyMap4::operatorIndex(unsigned* key) {
  unsigned* end = mpEnd;
  unsigned* e = (unsigned*)FUN_005701b0(mpBegin, end, key, mbFlag);
  if (e == end || *key < *e) {
    unsigned local[2];
    local[0] = *key;
    local[1] = 0;
    e = (unsigned*)insertElem(e, local);
  }
  return e + 1;
}

// ------------------------------------------------------------------
// 0x00e65970  intrusive-ptr push_back (refcount at +8)
void RefVecOwner::push(Ref* p) {
  if (p) _InterlockedExchangeAdd((volatile long*)((char*)p + 8), 1);
  RefPtrVec* v = (RefPtrVec*)((char*)this + 0x14);
  void** endp = (void**)v->mpEnd;
  if (endp < (void**)v->mpCap) {
    v->mpEnd = endp + 1;
    if (endp) {
      *endp = p;
      if (p) _InterlockedExchangeAdd((volatile long*)((char*)p + 8), 1);
    }
  } else {
    v->doInsertRef(endp, (void**)&p);
  }
  if (p) {
    long* c = (long*)((char*)p + 8);
    _InterlockedExchangeAdd(c, -1);
    long cur = _InterlockedExchangeAdd(c, 0);
    if (cur < 1) _InterlockedExchangeAdd(c, 1);
    else         _InterlockedExchangeAdd(c, 0);
  }
}

// ------------------------------------------------------------------
// 0x00e65a00  build a gfx object from two vcalls and append it
void FUN_00e65a00(int* param) {
  if (*param == 0) return;
  Obj74 obj;
  char* objp = (char*)&obj;
  ((Obj30*)objp)->ctor0();
  void* src = *(void**)param;
  void* old = *(void**)(objp + 0x70);
  if (src != old) {
    if (src) ((void(__thiscall*)(void*))VT(src)[0])(src);
    *(void**)(objp + 0x70) = src;
    if (old) ((void(__thiscall*)(void*))VT(old)[1])(old);
  }
  void* p = (void*)*param;
  ((void(__thiscall*)(void*, void*))VT(p)[0x1c / 4])(p, objp);
  p = (void*)*param;
  ((void(__thiscall*)(void*, void*))VT(p)[0x20 / 4])(p, objp + 0x38);
  ObjVec* vec = &((cCellGfx*)GG)->mObjVec;
  char* endp = (char*)vec->mpEnd;
  if (endp < (char*)vec->mpCap) {
    vec->mpEnd = endp + 0x74;
    if (endp) ((Obj74*)endp)->ctor(objp);
  } else {
    vec->insertGrow(endp, objp);
  }
  p = (void*)*param;
  ((void(__thiscall*)(void*, int))VT(p)[0xc / 4])(p, 0);
  p = (void*)*param;
  ((void(__thiscall*)(void*))VT(p)[4 / 4])(p);
  void* q = *(void**)(objp + 0x70);
  *param = 0;
  if (q) ((void(__thiscall*)(void*))VT(q)[1])(q);
}
