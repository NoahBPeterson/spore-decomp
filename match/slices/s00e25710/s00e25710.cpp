// Slice s00e25710 (batch bfs3, slice 15). Region 0xe25710-0xe26677.
// UI::Posse / cSPUIPosseItem constructors (matched) plus EASTL vector/partition
// sorting helpers for the posse item list. Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ================= matched: object constructors =================

struct cSPUIPosseItemBase {
  char pad0[0x98];
  int  mState;            // +0x98
  char pad9c[0x14c - 0x9c];
  float f14c;             // +0x14c
  void ctor(int a, const wchar_t* name, unsigned flags);   // 0x00e255c0
};

// @ 0x00e25840
struct cSPUIPosseItemTribe : cSPUIPosseItemBase { void* ctor(int a2); };
void* cSPUIPosseItemTribe::ctor(int a2) {
  cSPUIPosseItemBase::ctor(a2, L"PosseItemTribe", 0x40464100);
  *(void**)this = (void*)0x14807b0;
  *(void**)((char*)this + 4) = (void*)0x1480798;
  *(void**)((char*)this + 0xc) = (void*)0x1480788;
  this->f14c = 1.0f;
  return this;
}

// @ 0x00e258d0
struct cSPUIPosseItemTribeBaby : cSPUIPosseItemBase { void* ctor(int a2); };
void* cSPUIPosseItemTribeBaby::ctor(int a2) {
  cSPUIPosseItemBase::ctor(a2, L"PosseItemTribeBaby", 0x40464100);
  *(void**)this = (void*)0x14808c0;
  *(void**)((char*)this + 4) = (void*)0x14808a4;
  *(void**)((char*)this + 0xc) = (void*)0x1480894;
  this->f14c = 0.0f;
  return this;
}

// @ 0x00e25950
struct cSPUIPosseItemCiv : cSPUIPosseItemBase { void* ctor(int a2); };
void* cSPUIPosseItemCiv::ctor(int a2) {
  cSPUIPosseItemBase::ctor(a2, L"PosseItemCiv", 0x40464100);
  *(void**)this = (void*)0x14809d0;
  *(void**)((char*)this + 4) = (void*)0x14809b4;
  *(void**)((char*)this + 0xc) = (void*)0x14809a4;
  return this;
}

// @ 0x00e259d0
struct cSPUIPosseItemSpace : cSPUIPosseItemBase { void* ctor(int a2); };
void* cSPUIPosseItemSpace::ctor(int a2) {
  cSPUIPosseItemBase::ctor(a2, a2 ? L"PosseItemSpace" : L"PosseItemSpaceGhostShell", 0x40464100);
  *(void**)this = (void*)0x1480ae0;
  *(void**)((char*)this + 4) = (void*)0x1480ac4;
  *(void**)((char*)this + 0xc) = (void*)0x1480ab4;
  if (a2 == 0) this->mState = 0x7fffffff;
  return this;
}

// @ 0x00e25b50
struct cSPUIPosseItemTribeGhostShell : cSPUIPosseItemBase { void* ctor(); };
void* cSPUIPosseItemTribeGhostShell::ctor() {
  cSPUIPosseItemBase::ctor(0, L"PosseItemTribeGhostShell", 0x40464100);
  *(void**)this = (void*)0x1480e10;
  *(void**)((char*)this + 4) = (void*)0x1480df4;
  *(void**)((char*)this + 0xc) = (void*)0x1480de4;
  this->mState = 0x7fffffff;
  return this;
}

struct cScenarioEditPosseItemBase {
  char pad0[0x148];
  void ctor(int a, int b);   // 0x00e25460
};

// @ 0x00e25a60
struct cSPUIPosseItem2 : cScenarioEditPosseItemBase { void* ctor(int a2, int a3); };
void* cSPUIPosseItem2::ctor(int a2, int a3) {
  cScenarioEditPosseItemBase::ctor(a2, a3);
  *(void**)this = (void*)0x1480bf0;
  *(void**)((char*)this + 4) = (void*)0x1480bd4;
  *(void**)((char*)this + 0xc) = (void*)0x1480bc4;
  return this;
}

// @ 0x00e25ad0
struct cSPUIPosseItem3 : cScenarioEditPosseItemBase { void* ctor(int a2); };
void* cSPUIPosseItem3::ctor(int a2) {
  cScenarioEditPosseItemBase::ctor(0, a2);
  *(void**)this = (void*)0x1480d00;
  *(void**)((char*)this + 4) = (void*)0x1480ce4;
  *(void**)((char*)this + 0xc) = (void*)0x1480cd4;
  *(int*)((char*)this + 0x98) = 0x7fffffff;
  return this;
}

// ================= other functions in the slice =================
// The posse UI holds AutoRefCount<T> containers whose destructor calls go
// through vtable slot 1 (Release); modelled with an opaque helper.
typedef void (__thiscall *ReleaseFn)(void*);
static inline void RefRelease(void* p) {
  if (p) (*(ReleaseFn**)(*(void**)p))[1](p);
}

extern "C" {
  void* __cdecl FUN_00e23ee0(void*, void*, void*, unsigned char);
  void  __cdecl FUN_00e213f0(void*, float, unsigned);
  void  __cdecl FUN_00e24530(void*, void*, void*);
  void  __cdecl FUN_00e245c0(void*, void*);
  void  __cdecl FUN_00e25240(void*, int, int, int);
  void  __cdecl FUN_00e253c0(void*, void*, void*);
  void  __cdecl FUN_00e25460(void*, int, int);
  void  __cdecl FUN_00e25df0(void*, void*, void*, void*);
  void  __cdecl FUN_00e25f40(void*, void*, void*);
  void  __cdecl FUN_00e26410(void*, void*, int, void*);
  void  __cdecl FUN_00bbf1a0(void*, void*, void*);
  void  __cdecl FUN_00bbea40(void*, int, int, int);
  void* __cdecl FUN_00bbc7c0(void*, void*, void*, void*, void*);
  void* __cdecl FUN_00b95480(void*, void*);
  void* __cdecl FUN_00829110(void*, void*, void*, void*);
  void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);
  void  __cdecl operator_delete__(void*);
  void  __cdecl FUN_00e255c0_dlg(void*);
  void* __cdecl FUN_007f83e0(void*);
}

// @ 0x00e25710  UI::Posse::Posse -- large window constructor; raw member
// initialiser sequence (vtable stores are relocations).
struct cUIPosse15 { char pad[0x210]; void* ctor(); };
void* cUIPosse15::ctor() {
  char* s = (char*)this;
  *(void**)(s + 4) = (void*)0x13fa72c;
  *(void**)s = (void*)0x14806b8;
  *(void**)(s + 4) = (void*)0x148069c;
  char* p24 = s + 0x24;
  *(void**)(s + 8) = 0;
  *(void**)(s + 0x1c) = p24;
  *(void**)(s + 0x10) = p24;
  *(void**)(s + 0xc) = p24;
  *(void**)(s + 0x14) = p24 + 0x80;
  char* pbc = s + 0xbc;
  *(void**)(s + 0xb4) = pbc;
  *(void**)(s + 0xa8) = pbc;
  *(void**)(s + 0xa4) = pbc;
  *(void**)(s + 0xac) = pbc + 0x100;
  FUN_00e255c0_dlg(s + 0x1bc);
  *(unsigned char*)(s + 0x1d4) = 1;
  *(float*)(s + 0x1d8) = 0.0f;
  *(float*)(s + 0x1dc) = 1.0f;
  *(unsigned char*)(s + 0x1e4) = 1;
  *(unsigned char*)(s + 0x1ec) = 1;
  *(int*)(s + 0x1e0) = -1;
  *(unsigned char*)(s + 0x1e5) = 0;
  *(float*)(s + 0x1e8) = 1.0f;
  *(int*)(s + 0x1f0) = 0;
  *(int*)(s + 0x1f4) = 0;
  *(int*)(s + 0x1f8) = 0x1667bac;
  *(int*)(s + 0x1fc) = 0x1667bac;
  *(int*)(s + 0x200) = 0x1667bae;
  void* a = operator_new(0x20, (const char*)0x13f6b3c, 0, 0, 0, 0);
  *(void**)(s + 0x208) = a ? FUN_007f83e0(a) : 0;
  return this;
}

// @ 0x00e25bd0  eastl::vector<AutoRefCount<ILogReporter>>::erase(first,last)
struct cVec15 { void* f(void** First, void** Last); };
void* cVec15::f(void** First, void** Last) {
  char* s = (char*)this;
  void** end = *(void***)(s + 4);
  void** p = First; void** q = Last;
  while (q != end) { *p = *q; ++p; ++q; }
  for (void** it = Last; it != end; ++it) RefRelease(*it);
  *(void***)(s + 4) = (void**)((char*)end - ((char*)Last - (char*)First));
  return First;
}

// @ 0x00e25c30  vector<T>::insert with reallocation
struct cVec15b { int f(void* pos, unsigned n, void* src); };
int cVec15b::f(void* pos, unsigned n, void* src) {
  char* s = (char*)this;
  char* begin = *(char**)s;
  char* end   = *(char**)(s + 4);
  unsigned cap = (unsigned)(*(char**)(s + 8) - begin) >> 2;
  if (cap < n) {
    unsigned oldN = (unsigned)(end - begin) >> 2;
    unsigned newCap = oldN * 2; if (oldN == 0) newCap = 1;
    unsigned want = oldN + n; if (want > newCap) newCap = want;
    char* nb = newCap ? (char*)operator_new(newCap * 4, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    unsigned pre = (unsigned)((char*)pos - begin);
    char* p1 = (char*)FUN_00829110(nb, begin, (void*)pre, 0);
    char* mid = p1 + pre;
    FUN_00829110(mid, pos, (void*)n, 0);
    FUN_00829110(mid + n * 4, end, (void*)((char*)end - (char*)pos), 0);
    if (begin && begin != *(char**)(s + 0x10)) operator_delete__(begin);
    *(char**)s = nb; *(char**)(s + 4) = mid; *(char**)(s + 8) = nb + newCap * 4;
    return 0;
  }
  (void)src;
  return 0;
}

// @ 0x00e25df0  partition over 4-byte AutoRefCount elements
void __cdecl FUN_00e25df0(void* first, void* last, void* end, void* pred) {
  unsigned char (*fn)(void*, void*) = (unsigned char (*)(void*, void*))pred;
  char* f = (char*)first; char* l = (char*)last;
  FUN_00bbf1a0(first, last, pred);
  for (; l < (char*)end; l += 4) {
    if (fn(*(void**)f, *(void**)l)) {
      char* a = *(char**)l;
      if (a) { void* o = *(void**)a; ((void(__thiscall*)(void*))o)(a); }
      char* fa = *(char**)f;
      RefRelease(*(void**)l);
      *(void**)l = fa;
      FUN_00bbea40(first, 0, (int)((char*)last - (char*)first) >> 2, 0);
      RefRelease(a);
    }
  }
}

// @ 0x00e25f40  make_heap / sift helper over 8-byte AutoRefCount pairs
void __cdecl FUN_00e25f40(char* begin, char* end, void* ctx) {
  int n = (int)((end - begin) >> 3);
  if (1 < n) {
    int i = ((n - 2) >> 1) + 1;
    do {
      void* a = *(void**)(begin + i * 8 - 8);
      --i;
      if (a) { void* o = *(void**)a; ((void(__thiscall*)(void*))o)(a); }
      void* b = *(void**)(begin + 4 + i * 8);
      if (b) { void* o = *(void**)b; ((void(__thiscall*)(void*))o)(b); }
      FUN_00e25240(begin, i, n, i);
    } while (i != 0);
  }
}

struct cPosseItem15 {
  char pad0[0xb4];
  int  mDistress;              // +0xb4
  char padb8[0xd0 - 0xb8];
  float mBlinkerFrequency;     // +0xd0
  char padd4[0x124 - 0xd4];
  char* mControlValuesBegin;   // +0x124
  char* mControlValuesEnd;     // +0x128
  char pad12c[0x138 - 0x12c];
  unsigned char f138;          // +0x138
  void update_control_value(unsigned key);
  void update_control_values(char force);
  bool OnTick(void* msg);
};

// @ 0x00e25fa0  cSPUIPosseItem::update_control_value(unsigned)
void cPosseItem15::update_control_value(unsigned key) {
  char* s = (char*)this;
  char* end = mControlValuesEnd;
  char* found = (char*)FUN_00e23ee0(mControlValuesBegin, end, &key, f138);
  char* match = end;
  if (found != end && *(unsigned*)found <= key && found != found + 0x10) match = found;
  if (match == end) return;
  if (key == 0x3d99184) {
    bool (*vf)(void*) = (bool (*)(void*))(*(void***)s)[0xb4 / 4];
    if (!vf(this)) return;
  }
  char* blinker = *(char**)(s + 0xd4);
  void* w = (*(void*(__thiscall**)(void*, unsigned, int))(**(void***)(blinker + 0x10)))(*(void**)(blinker + 0x10), key, 1);
  if (w) FUN_00e213f0(w, *(float*)(match + 4), *(unsigned char*)(match + 8));
  if (*(unsigned char*)(match + 8) && *(unsigned char*)(match + 9)) {
    float v = *(float*)(match + 4);
    unsigned lvl = 0;
    if (v >= 30.0f) { if (v < 60.0f) lvl = 1; } else lvl = 2;
    void* fn = (*(void***)s)[0x84 / 4];
    if (key == 0x3d99184) ((void(__thiscall*)(void*, int, unsigned))fn)(this, 1, lvl);
    else if (key == 0x3d99162) ((void(__thiscall*)(void*, int, unsigned))fn)(this, 0, lvl);
  }
  *(int*)(match + 0xc) = 0;
}

// @ 0x00e260a0  cSPUIPosseItem::update_control_values(char)
void cPosseItem15::update_control_values(char force) {
  char* p = mControlValuesBegin;
  char* end = mControlValuesEnd;
  while (p != end) {
    int key = *(int*)p;
    int tick = *(int*)(p + 0xc);
    if (force != 0 || (tick != 0 && mDistress > tick))
      update_control_value(key);
    p += 0x10;
  }
}

// @ 0x00e260f0  cSPUIPosseItem::OnTick -- full blinker sequence not reconstructed
bool cPosseItem15::OnTick(void* msg) {
  unsigned id = (*(unsigned(__thiscall**)(void*))(**(void***)msg))(msg);
  if (id != 0x3d98299) return false;
  ++mDistress;
  update_control_values(0);
  if (mBlinkerFrequency > 0.0f) {
    // TODO: fcos blink computation and blink_for_a_motive loop
    return false;
  }
  return false;
}

// @ 0x00e26410  introselect driver over 4-byte elements
void __cdecl FUN_00e26410(char* first, char* last, int depth, void* ctx) {
  while ((int)(((last - first) & 0xfffffffc)) > 0x70 && depth > 0) {
    char* pivot = (char*)FUN_00bbc7c0(first, first + (((last - first) >> 2) >> 1) * 4, last - 4, ctx, ctx);
    void* a = *(void**)pivot;
    if (a) { void* o = *(void**)a; ((void(__thiscall*)(void*))o)(a); }
    char* mid = (char*)FUN_00b95480(first, last);
    FUN_00e26410(mid, last, depth - 1, ctx);
    last = mid;
  }
  if (depth == 0) FUN_00e25df0(first, last, last, ctx);
}

// @ 0x00e264b0  partition over 8-byte elements
void* __cdecl FUN_00e264b0(char* first, char* last, char** out1, char** out2, void* pred) {
  unsigned char (*fn)(void*, void*) = (unsigned char (*)(void*, void*))pred;
  while (true) {
    while (fn(first, out1)) first += 8;
    last -= 8;
    while (fn(out1, last)) last -= 8;
    if (last <= first) break;
    FUN_00e245c0(first, last);
    first += 8;
  }
  RefRelease((void*)*out2);
  RefRelease((void*)*out1);
  return first;
}

// @ 0x00e26530  insertion pass for the 8-byte pair stable sort
void __cdecl FUN_00e26530(char* first, char* last, char* end, void* pred) {
  unsigned char (*fn)(void*, void*) = (unsigned char (*)(void*, void*))pred;
  FUN_00e25f40(first, last, pred);
  char* i = last;
  for (; i < end; i += 8) {
    if (!fn(first, i)) continue;
    char* a = *(char**)i;
    char* b = *(char**)(i + 4);
    RefRelease(a); RefRelease(b);
    char* fa = *(char**)first;
    char* fb = *(char**)(first + 4);
    if (fa != a) { RefRelease(a); *(char**)i = fa; }
    if (fb != b) { RefRelease(b); *(char**)(i + 4) = fb; }
    FUN_00e25240(first, 0, (int)((char*)last - (char*)first) >> 3, 0);
    RefRelease(b); RefRelease(a);
  }
  for (; (int)((last - first) & 0xfffffff8) > 8; last -= 8)
    FUN_00e253c0(first, last, pred);
}
