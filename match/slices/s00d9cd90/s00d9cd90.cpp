// s00d9cd90.cpp — SP creature / tribe SWARM + SOCIAL_RESPOND behavior region
// (cSPCreatureBase helpers, memory-block drivers, heap helpers, the SWARM
// "memory block" container ops and the SOCIAL_RESPOND block lifecycle).
// Reconstructed from Ghidra decompiles + disassembly.
//
// cl rejects __thiscall on free functions, so every __thiscall / __fastcall
// entry point is declared as a member of S (methods keep the FUN_ names so
// run_all's substring match still finds them); the ignored register args of the
// original disappear.

#include <stddef.h>

// ---- imports / runtime helpers ---------------------------------------------
extern "C" void* __cdecl EastlNew(unsigned int size, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl EastlDelete(void* p);                                    // 0x00f47380

// virtual dispatch through *obj (AddRef slot0 @+0, Release slot1 @+4)
inline void AddRef(void* o) { if (o) ((void (**)(void*))(*(void***)o))[0](o); }
inline void Release(void* o) { if (o) ((void (**)(void*))(*(void***)o))[1](o); }
inline void* VFn(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }
inline void* VCall0(void* o, int off) { return ((void* (*)(void*))VFn(o, off))(o); }
inline float VCallF(void* o, int off) { return ((float (*)(void*))VFn(o, off))(o); }
inline void VCall3(void* o, int off, void* a, void* b, void* c) { ((void (*)(void*, void*, void*, void*))VFn(o, off))(o, a, b, c); }

inline void Copy8(int* d, int* s) {
  d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3];
  d[4] = s[4]; d[5] = s[5]; d[6] = s[6]; d[7] = s[7];
}

struct S {
  void  FUN_00d9cd90();                              // 0x00d9cd90 SWARM tick
  void  FUN_00d9cf70();                              // 0x00d9cf70 AddAgent
  void  FUN_00d9d100(void* creature, int target);    // 0x00d9d100
  char  FUN_00d9d1e0(void* creature);                // 0x00d9d1e0
  float FUN_00d9d420(void* creature);                // 0x00d9d420
  void  FUN_00d9d570(void* owner);                   // 0x00d9d570
  char  FUN_00d9d5b0(void* creature, int block);     // 0x00d9d5b0
  int   FUN_00d9d840(int idx);                       // 0x00d9d840
  void  FUN_00d9d890(int* first, int* last);         // 0x00d9d890
  void  FUN_00d9d8d0(int* out, int* src, int* end, int* dst); // 0x00d9d8d0
  void  FUN_00d9d9a0(void* arr, int a, int n, int i, int v,
                     float f1, float f2, float f3, float f4,
                     float f5, float f6, float f7, void* cmp);  // 0x00d9d9a0
  void  FUN_00d9da80(void* arr, void* a, int n, int i, float f1,
                     float f2, float f3);                       // 0x00d9da80
  void  FUN_00d9db30(void* src, void* end, void* dst);          // 0x00d9db30
  char  FUN_00d9dba0(void* creature);                            // 0x00d9dba0
  void  FUN_00d9dc80(void* creature, void* block);               // 0x00d9dc80
};

// ---- extern helpers (cdecl unless noted) -----------------------------------
extern "C" void* __cdecl FUN_00b3d300(void);                       // 0x00b3d300 NounManager
extern "C" int   __cdecl FUN_00b1f9d0(void);                       // 0x00b1f9d0 GetPlayerEmpireOrMinus1
extern "C" void* __cdecl FUN_00b3d2c0(int empire);                 // 0x00b3d2c0 RelationshipManager
extern "C" int   __cdecl FUN_00d00a70(void* rel, int empire, int b); // 0x00d00a70
extern "C" void* __cdecl FUN_00cd40b0(void);                       // 0x00cd40b0 cTribeModeStrategy::Instance
extern "C" char  __cdecl FUN_00cd5550(void* self);                 // 0x00cd5550
extern "C" void* __cdecl FUN_00bfc5f0(void* nouns);                // 0x00bfc5f0 GetPlayerTribe
extern "C" void* __cdecl FUN_00c00650(void* community);            // 0x00c00650 GetLeader
extern "C" void  __cdecl FUN_00bc97f0(int a, int b, float d, void* p); // 0x00bc97f0
extern "C" void* __cdecl FUN_00b3d4d0(void);                       // 0x00b3d4d0 GetTriggerMgr
extern "C" void  __cdecl FUN_00ae0930(void* mgr, const char* trg, int a, int b, int c, int d, int e); // PostTrigger
extern "C" void* __cdecl FUN_00ad7a30(int obj);                    // 0x00ad7a30
extern "C" void  __cdecl FUN_00ae09b0(void* mgr, unsigned id, void* tgt); // PostAction
extern "C" void  __cdecl FUN_00ad7ad0(void);                       // 0x00ad7ad0 dtor
extern "C" void  __cdecl FUN_00cdab10(void* strategy);             // IncrementGoalProgress
extern "C" char  __cdecl FUN_00a75010(void* x);                    // 0x00a75010
extern "C" int   __cdecl FUN_00afa5d0(void* pos);                  // FindClosestFreeSlot
extern "C" void* __cdecl FUN_00af9ff0(void* circle, int idx);      // SlotAt
extern "C" void  __cdecl FUN_00afa030(void* slot, void* creature); // tSlot::Reserve
extern "C" void  __cdecl FUN_00c1c5c0(void* creature, int style, void* dst, void* face, float a, float b); // MoveToPoint
extern "C" void* __cdecl FUN_00c41ec0(void* x);                    // 0x00c41ec0
extern "C" void* __cdecl FUN_00449c20(void* out, float* v, float a, float b); // normalized_safe
extern "C" char  __cdecl FUN_00c42e20(void* x);                    // IsNearGoal
extern "C" void  __cdecl FUN_00c12310(void* creature, int a, int b, int c);   // InterruptAnimation
extern "C" char  __cdecl FUN_00c123f0(void* creature, int x);      // AnimationFinished
extern "C" void* __cdecl FUN_00bc96a0(void* tree, int a, int b);   // PlayIdleAnimation
extern "C" void* __cdecl FUN_00d999d0(void* h);                    // WatchMemoryBlock
extern "C" void* __cdecl FUN_00d994c0(void* h);                    // 0x00d994c0
extern "C" void* __cdecl FUN_00d99470(void* h);                    // 0x00d99470
extern "C" void  __cdecl FUN_00da6270(void* creature, int code);   // 0x00da6270
extern "C" void  __cdecl FUN_00bcaf40(void* x);                    // cAgentOrderManager::PopFront
extern "C" void  __cdecl FUN_00bc98f0(void* tree, int a, int b);   // ClearAll
extern "C" void* __cdecl FUN_00cee330(void* x);                    // 0x00cee330
extern "C" void* __cdecl FUN_00c12190(void* creature, unsigned id, int a, void* h); // PlayAnimation
extern "C" void* __cdecl FUN_00c0fa10(void* x, int y);             // 0x00c0fa10
extern "C" void* __cdecl FUN_00c0ee70(void* creature);             // GetTargetAsCreature
extern "C" void  __cdecl FUN_00bcafe0(void* x, int y);             // 0x00bcafe0
extern "C" void  __cdecl FUN_00bcb430(void* x);                    // 0x00bcb430
extern "C" char  __cdecl FUN_00ac0730(void* a, void* b);           // 0x00ac0730
extern "C" void  __cdecl FUN_00d9b950(void* arr, void* a, int n, float f1, float f2,
                                      float f3, float f4, float f5, float f6,
                                      float f7, float f8, void* cmp);  // 0x00d9b950
extern "C" void  __cdecl FUN_00d9b9b0(void* arr, void* a, int n, float f1,
                                      float f2, float f3);         // 0x00d9b9b0
extern "C" void  __cdecl FUN_00d9c020(void* block, void* creature); // CalculateGroupContribution
extern "C" void  __cdecl FUN_00c0b970(float x);                     // 0x00c0b970
extern "C" void  __cdecl FUN_00c0ba10(void* creature);              // 0x00c0ba10
extern "C" int   __cdecl FUN_00c22dc0(void* creature);              // 0x00c22dc0
extern "C" void* __cdecl FUN_00c0bbd0(void* creature);             // 0x00c0bbd0 SP::cSPCreatureBase::GetSpeciesProfile
extern "C" char  __cdecl FUN_00c232d0(void* citizen);              // 0x00c232d0 SP::cSPCreatureCitizen::IsLeader
extern "C" void  __cdecl FUN_00d9ccc0(float a, float b);            // 0x00d9ccc0

// ===========================================================================
// @ 0x00d9cd90
void S::FUN_00d9cd90()
{
  char* self = (char*)this;
  char* cur = *(char**)(self + 100);
  char* end = *(char**)(self + 0x68);
  float local_c = 0.0f;
  *(int*)(self + 0x3c) = *(int*)0x01581314;
  *(int*)(self + 0x40) = *(int*)0x01581318;
  bool b5 = false, b6 = false, b7 = false;
  int local_8 = 0;
  if (cur != end) {
    do {
      int obj = *(int*)cur;
      int citizen = 0;
      if (obj != 0)
        citizen = ((int (__thiscall*)(void*, unsigned))VFn((void*)(obj + 0x34), 0xc))((void*)(obj + 0x34), 0x4f176642u);
      if (obj == 0 || citizen == 0) {
        local_c = *(float*)0x01581310 + local_c;
      } else {
        int kind = FUN_00c22dc0((void*)obj);
        if (kind == 4) { local_c = *(float*)0x01581308 + local_c; b5 = true; }
        else if (kind == 5) { local_c = *(float*)0x01581308 + local_c; b7 = true; }
        else if (kind == 6) { local_c = *(float*)0x01581308 + local_c; b6 = true; }
        local_c = *(float*)0x01581300 + local_c;
        int prof = (int)FUN_00c0bbd0((void*)obj);
        local_8 = *(int*)(prof + 0x62c);
        char leader = FUN_00c232d0((void*)citizen);
        if (leader != 0) {
          *(float*)(self + 0x3c) = *(float*)0x0158130c + *(float*)(self + 0x3c);
          *(float*)(self + 0x40) = *(float*)(self + 0x40) + *(float*)0x0158130c;
        }
      }
      cur += 4;
    } while (cur != end);
    if (b5) local_c = *(float*)0x015812fc + local_c;
    if (b6) local_c = *(float*)0x015812fc + local_c;
    if (b7) local_c = *(float*)0x015812fc + local_c;
  }
  float f3 = (float)*(int*)(self + 0x48);
  if (*(int*)(self + 0x48) < 0) f3 = f3 + 4294967296.0f;
  float f4 = (float)local_8;
  if (local_8 < 0) f4 = f4 + 4294967296.0f;
  FUN_00d9ccc0(f4 * *(float*)0x01581304 + local_c, f3 * *(float*)(self + 0x4c));
}

// ===========================================================================
// @ 0x00d9cf70
void S::FUN_00d9cf70()
{
  char* self = (char*)this;
  void* nouns = FUN_00b3d300();
  int empire = FUN_00b1f9d0();
  int a = ((int (__thiscall*)(void*, int))VFn(self, 0x4c))(self, empire);
  int rel = (int)FUN_00b3d2c0(a);
  int v = FUN_00d00a70((void*)rel, a, 1);
  if (v != 4) return;
  void* strat = FUN_00cd40b0();
  char c = FUN_00cd5550(strat);
  if (c != 0) return;
  void* nm = FUN_00b3d300();
  int community = (int)FUN_00bfc5f0(nm);
  if (community == 0) return;
  int leader = (int)FUN_00c00650((void*)community);
  int cit = 0;
  if (leader != 0) cit = ((int (__thiscall*)(void*, unsigned))VFn((void*)leader, 0xc))((void*)leader, 0x4f176642u);
  int vec = (int)((void* (__thiscall*)(void*))VFn((void*)community, 0x90))((void*)community);
  int i0 = *(int*)vec, i1 = *(int*)(vec + 4);
  for (int it = i0; it != i1; it += 4) FUN_00bc97f0(0x800000, 0, 10.0f, self);
  int vec2 = (int)((void* (__thiscall*)(void*))VFn(self, 0x90))(self);
  int j0 = *(int*)vec2, j1 = *(int*)(vec2 + 4);
  for (int it = j0; it != j1; it += 4) FUN_00bc97f0(0x800000, 0, 10.0f, self);
  void* tm = FUN_00b3d4d0();
  FUN_00ae0930(tm, "TRG_TotemPole_Social", 1, 1, 0, 0, 0);
  int tgt = (cit == 0) ? 0 : cit + 0xc0;
  void* t = FUN_00ad7a30(tgt);
  void* tm2 = FUN_00b3d4d0();
  FUN_00ae09b0(tm2, 0xcd5f0ca4u, t);
  FUN_00ad7ad0();
  void* s2 = FUN_00cd40b0();
  FUN_00cdab10(s2);
}

// ===========================================================================
// @ 0x00d9d0e0  (__cdecl: reads its arg from the stack, plain `ret`)
char __cdecl FUN_00d9d0e0(void* p)
{
  char* e = (char*)p;
  int a = *(int*)(e + 0xb4c);
  int b = *(int*)((char*)a + 0x600);
  char c = ((char(__thiscall*)(void*))FUN_00a75010)((void*)b);
  return c == 0;
}

// ===========================================================================
// @ 0x00d9d100
void S::FUN_00d9d100(void* creature, int target)
{
  char* self = (char*)this;
  char* t = (char*)target;
  float pos[3];
  int src = *(int*)(t + 0xf4);
  pos[0] = *(float*)(src + 0x3c);
  pos[1] = *(float*)(src + 0x40);
  pos[2] = *(float*)(src + 0x44);
  int slot = FUN_00afa5d0(pos);
  *(int*)(self + 0xc) = slot;
  if (slot == -1) return;
  void* slotObj = FUN_00af9ff0((void*)(self + 0x178), slot);
  FUN_00afa030(slotObj, creature);
  float face[3];
  face[0] = *(float*)(t + 0x1c);
  face[1] = *(float*)(t + 0x20);
  face[2] = *(float*)(t + 0x24);
  unsigned nx = *(unsigned*)&face[0] ^ 0x80000000u;
  unsigned ny = *(unsigned*)&face[1] ^ 0x80000000u;
  unsigned nz = *(unsigned*)&face[2] ^ 0x80000000u;
  float nf[3];
  nf[0] = *(float*)&nx; nf[1] = *(float*)&ny; nf[2] = *(float*)&nz;
  FUN_00c1c5c0(creature, 2, (void*)((char*)slotObj + 0xc), nf, 1.0f, 2.0f);
  void* r = FUN_00c41ec0((char*)creature + 0xc0);
  *(unsigned*)((char*)r + 0x70) |= 2;
}

// ===========================================================================
// @ 0x00d9d1e0
char S::FUN_00d9d1e0(void* creature)
{
  char* self = (char*)this;
  unsigned* st = *(unsigned**)(self + 0x18);
  unsigned state = st[5];
  if (state > 3) return 1;
  switch (state) {
    case 0: {
      if (*(float*)(self + 8) != *(float*)0x0169f32c ||
          *(float*)(self + 0xc) != *(float*)0x0169f330 ||
          *(float*)(self + 0x10) != *(float*)0x0169f334) {
        char* cb = (char*)creature + 0xc0;
        float* p = (float*)VCall0(cb, 0x2c);
        float d[3];
        d[0] = *(float*)(self + 8) - p[0];
        d[1] = *(float*)(self + 0xc) - p[1];
        d[2] = *(float*)(self + 0x10) - p[2];
        char nbuf[12];
        float* n = (float*)FUN_00449c20(nbuf, d, 1.0f, 2.0f);
        float* q = (float*)VCall0(cb, 0x2c);
        FUN_00c1c5c0(creature, 2, q, n, 1.0f, 2.0f);
        st[5] = 1;
        return 1;
      }
      break;
    }
    case 1: {
      char near = FUN_00c42e20((char*)creature + 0xc0);
      if (near == 0 && (*(unsigned char*)((char*)creature + 0x330) & 1) == 0) return 1;
      break;
    }
    case 2: {
      FUN_00c12310(creature, *st, -1, 0);
      st[5] = 3;
      return 1;
    }
    case 3: {
      char fin = FUN_00c123f0(creature, 0);
      if (fin == 0) return 1;
      unsigned* ctr = st + 1;
      *ctr = *ctr - 1;
      if (*ctr == 0) return 0;
      break;
    }
    default: return 1;
  }
  st[5] = 2;
  return 1;
}

// ===========================================================================
// @ 0x00d9d420
float S::FUN_00d9d420(void* creature)
{
  char* self = (char*)this;
  int h = (int)FUN_00bc96a0((void*)(*(int*)(self + 0xb4c) + 8), 0x1000, 0);
  if (h == 0) return 0.0f;
  int x = (int)FUN_00d994c0(FUN_00d999d0((void*)h));
  if (x == 0) { FUN_00da6270(self, 0x15); return 0.0f; }
  int arr = *(int*)(*(int*)(self + 0xb4c) + 0x600);
  if (arr == 0) return 0.0f;
  if (*(int*)(arr + 0x1ac) != 0) return 0.0f;
  if (*(int*)(arr + 0x1b0) != 0) return 0.0f;
  float* pa = (float*)VCall0((char*)x + 0xc0, 0x2c);
  float* pb = (float*)VCall0((char*)self + 0xc0, 0x2c);
  float d0 = pa[0] - pb[0];
  float d1 = pa[1] - pb[1];
  float d2 = pa[2] - pb[2];
  float selfd = d2 * d2 + d1 * d1 + d0 * d0;
  unsigned n = *(unsigned*)(arr + 0x18);
  if (n != 0) {
    char* pc = (char*)(arr + 0x20);
    unsigned i = 0;
    do {
      if (*pc != 0) {
        int other = *(int*)(pc + 4);
        if (other != (int)self) {
          float* po = (float*)VCall0((char*)other + 0xc0, 0x2c);
          float e0 = po[0] - pb[0], e1 = po[1] - pb[1], e2 = po[2] - pb[2];
          float od = e2 * e2 + (e1 * e1 + e0 * e0);
          if (selfd > od) return 0.0f;
        }
      }
      ++i;
      pc += 0xc;
    } while (i < *(unsigned*)(arr + 0x18));
  }
  return 1.0f;
}

// ===========================================================================
// @ 0x00d9d570
void S::FUN_00d9d570(void* owner)
{
  char* self = (char*)this;
  int arr = *(int*)(*(int*)(self + 0xb4c) + 0x600);
  if (arr != 0 && *(int*)(arr + 0x1ac) == (int)self) *(int*)(arr + 0x1ac) = 0;
  int base = *(int*)(self + 0xb4c);
  int* p = *(int**)(base + 0x600);
  if (p != 0) {
    *(int*)(base + 0x600) = 0;
    ((void (*)(int*))VFn(p, 8))(p);
  }
  FUN_00bcafe0(p, *(int*)(base + 0x604));
  *(int*)(base + 0x604) = -1;
}

// ===========================================================================
// @ 0x00d9d5b0
char S::FUN_00d9d5b0(void* creature, int block)
{
  char* self = (char*)this;
  int h = (int)FUN_00bc96a0((void*)(*(int*)(self + 0xb4c) + 8), 0x1000, 0);
  if (h == 0) { FUN_00da6270(self, 0x15); return 0; }
  int x = (int)FUN_00d994c0(FUN_00d999d0((void*)h));
  if (x == 0) { FUN_00da6270(self, 0x15); return 0; }
  VCall3(self, 0x84, (void*)(x + 0x5a8), (void*)1, (void*)2);
  int arr = *(int*)(*(int*)(self + 0xb4c) + 0x600);
  *(int*)(arr + 0x1ac) = (int)self;
  unsigned n = *(unsigned*)(arr + 0x18);
  unsigned i = 0;
  if (n != 0) {
    char* pc = (char*)(arr + 0x20);
    do {
      if (*pc != 0) {
        int other = *(int*)(pc + 4);
        if (other != (int)self) {
          int oc = *(int*)((char*)other + 0xb4c);
          FUN_00bcaf40((void*)oc);
          FUN_00bc98f0((void*)(*(int*)((char*)other + 0xb4c) + 8), (int)0x1d3fbffau, (int)0x8124080u);
        }
      }
      ++i;
      pc += 0xc;
    } while (i < *(unsigned*)(arr + 0x18));
  }
  int e = (int)FUN_00cee330((char*)self + 0x34);
  if (e == 0) {
    void* res = FUN_00c12190(self, 0x2c39200u, 1, *(void**)((char*)self + 0xfc8));
    *(int*)(block + 4) = (int)res;
    *(int*)(block + 0) = 1;
    *(int*)(block + 8) = 0;
    return 1;
  }
  if (*(int*)(e + 0x12c) != 5) {
    int hh = *(int*)((char*)self + 0xfc8);
    void* q = FUN_00c0fa10((void*)(e + 0x34), 0);
    if (q != 0) hh = *(int*)q;
    void* res = FUN_00c12190(self, 0x4ffb325u, 1, (void*)hh);
    *(int*)(block + 4) = (int)res;
    *(int*)(block + 0) = 0;
    *(int*)(block + 8) = 0;
    return 1;
  }
  int tgt = (int)FUN_00c0ee70(self);
  float* pt = (float*)VCall0((char*)tgt + 0xc0, 0x2c);
  float* ps = (float*)VCall0((char*)self + 0xc0, 0x2c);
  float d[3];
  d[0] = pt[0] - ps[0];
  d[1] = pt[1] - ps[1];
  d[2] = pt[2] - ps[2];
  float inv = 1.0f / (d[2] * d[2] + (d[1] * d[1] + d[0] * d[0]) + *(float*)0x13ec4b8);
  float nf[3];
  nf[0] = inv * d[0];
  nf[1] = inv * d[1];
  nf[2] = inv * d[2];
  int tgt2 = (int)FUN_00c0ee70(self);
  float a = *(float*)VCall0((char*)tgt2 + 0xc0, 0x74);
  float b = *(float*)VCall0((char*)self + 0xc0, 0x74);
  float spd = (a + b) + *(float*)0x01485720;
  FUN_00c1c5c0(self, 2, pt, nf, spd, spd);
  *(int*)(block + 0) = 2;
  *(int*)(block + 8) = 0;
  return 1;
}

// ===========================================================================
// @ 0x00d9d800
void __cdecl FUN_00d9d800(void* owner)
{
  char* self = (char*)owner;
  int arr = *(int*)(*(int*)(self + 0xb4c) + 0x600);
  if (arr != 0 && *(int**)(arr + 0x1ac) == (int*)self) *(int*)(arr + 0x1ac) = 0;
  ((void (__thiscall*)(void*, int, int, int))VFn(self, 0x84))(self, 0, 0, 0);
}

// ===========================================================================
// @ 0x00d9d840
int S::FUN_00d9d840(int idx)
{
  unsigned* p = *(unsigned**)this;
  p += idx * 0x84;
  bool b30 = ((((unsigned)*p) >> 0x1e) & 1) != 0;
  if (b30) return 0x3fffffff;
  do {
    p += 0x84;
    ++idx;
    bool b31 = ((((unsigned)*p) >> 0x1f) & 1) != 0;
    if (!b31) return idx;
    b30 = ((((unsigned)*p) >> 0x1e) & 1) != 0;
  } while (!b30);
  return 0x3fffffff;
}

// ===========================================================================
// @ 0x00d9d890
void S::FUN_00d9d890(int* first, int* last)
{
  for (; first < last; first += 0x84) {
    bool flag = (((unsigned)*first) >> 31) & 1;
    if (!flag) {
      void* obj = (void*)(first + 1);
      (*(void (__thiscall***)(void*, int))obj)[0](obj, 0);
    }
  }
}

// ===========================================================================
// @ 0x00d9d8d0
void S::FUN_00d9d8d0(int* out, int* src, int* end, int* dst)
{
  *out = (int)dst;
  if (src != end) {
    int* d = dst;
    while (src != end) {
      if (d != 0) {
        d[0] = src[0]; d[1] = src[1]; d[2] = src[2]; d[3] = src[3];
        d[4] = src[4]; d[5] = src[5]; d[6] = src[6]; d[7] = src[7];
      }
      src += 8;
      d += 8;
    }
    *out = (int)d;
  }
}

// ===========================================================================
// @ 0x00d9d940
struct Elem20 { int a; float f[7]; };
void __cdecl FUN_00d9d940(void* dst, unsigned n, void* src)
{
  Elem20* d = (Elem20*)dst;
  Elem20* s = (Elem20*)src;
  while (n > 0) {
    if (d != 0) {
      d->a = s->a;
      d->f[0] = s->f[0]; d->f[1] = s->f[1]; d->f[2] = s->f[2]; d->f[3] = s->f[3];
      d->f[4] = s->f[4]; d->f[5] = s->f[5]; d->f[6] = s->f[6];
    }
    --n;
    ++d;
  }
}

// ===========================================================================
// @ 0x00d9d9a0
void S::FUN_00d9d9a0(void* arr, int a, int n, int i, int v,
                    float f1, float f2, float f3, float f4,
                    float f5, float f6, float f7, void* cmp)
{
  char* base = (char*)arr;
  (void)a; (void)v;
  for (;;) {
    int child = i * 2 + 2;
    if (n <= child) break;
    char* c = base + child * 0x20;
    char ok = ((char (*)(void*, void*))cmp)(c, c - 0x20);
    if (ok != 0) child = i * 2 + 1;
    Copy8((int*)(base + i * 0x20), (int*)(base + child * 0x20));
    i = child;
  }
  if (i == n - 1) {
    Copy8((int*)(base + i * 0x20), (int*)(base + (n - 1) * 0x20));
    i = n - 1;
  }
  FUN_00d9b950(arr, (void*)a, i, f1, f2, f3, f4, f5, f6, f7, *(float*)&v, cmp);
}

// ===========================================================================
// @ 0x00d9da80
void S::FUN_00d9da80(void* arr, void* a, int n, int i, float f1, float f2, float f3)
{
  int* base = (int*)arr;
  (void)a;
  for (;;) {
    int child = i * 2 + 2;
    if (n <= child) break;
    int r = base[child];
    void* c1 = r == 0 ? 0 : (void*)(r + 0xc0);
    int l = base[child - 1];
    void* c0 = l == 0 ? 0 : (void*)(l + 0xc0);
    char ok = FUN_00ac0730(c0, c1);
    if (ok != 0) child = i * 2 + 1;
    base[i] = base[child];
    i = child;
  }
  if (i == n - 1) {
    base[i] = base[n - 1];
    i = n - 1;
  }
  FUN_00d9b9b0(arr, a, i, f1, f2, f3);
}

// ===========================================================================
// @ 0x00d9db30
void S::FUN_00d9db30(void* src, void* end, void* dst)
{
  int* s = (int*)src;
  int* e = (int*)end;
  int* d = (int*)dst;
  if (s != e) {
    while (s != e) {
      if (d != 0) {
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3];
        d[4] = s[4]; d[5] = s[5]; d[6] = s[6]; d[7] = s[7];
      }
      s += 8; d += 8;
    }
  }
}

// ===========================================================================
// @ 0x00d9dba0
char S::FUN_00d9dba0(void* creature)
{
  char* self = (char*)this;
  char* blk = (char*)creature;
  if (blk != 0) *(int*)(blk + 4) = 0;
  *(int*)(blk + 8) = 0;
  *(int*)(blk + 0xc) = -1;
  *(float*)(blk + 0x18) = *(float*)0x01485720;
  int h = (int)FUN_00bc96a0((void*)(*(int*)(self + 0xb4c) + 8), 0x10000, 0);
  if (h == 0) return 0;
  void* nw = FUN_00d99470(FUN_00d999d0((void*)h));
  int old = *(int*)(blk + 4);
  if ((int)nw != old) {
    if (nw != 0) ((void (*)(void*))VFn(nw, 0))(nw);
    *(int*)(blk + 4) = (int)nw;
    if (old != 0) ((void (*)(int))VFn((void*)old, 4))((int)old);
  }
  int cur = *(int*)(blk + 4);
  if (cur == 0) return 0;
  VCall3(self, 0x84, (void*)(cur + 0x5a8), (void*)1, (void*)2);
  FUN_00d9c020(blk, self);
  *(int*)(blk + 0) = 0;
  FUN_00bc98f0((void*)(*(int*)(self + 0xb4c) + 8), 0x10000, 0);
  FUN_00c0b970(0.0f);
  *(unsigned*)(self + 0xb58) |= 0x20;
  return 1;
}

// ===========================================================================
// @ 0x00d9dc80
void S::FUN_00d9dc80(void* creature, void* block)
{
  char* self = (char*)this;
  char* blk = (char*)block;
  if (((*(unsigned*)(self + 0xb58) >> 9) & 1) == 0) VCall3(self, 0x84, 0, 0, 0);
  FUN_00bc98f0((void*)(*(int*)(self + 0xb4c) + 8), 0x10000000, 0);
  FUN_00c0ba10(self);
  *(unsigned*)(self + 0xb58) &= 0xffffffdfu;
  if (blk != 0) {
    int* q = *(int**)(blk + 4);
    if (q != 0) {
      ((void (*)(int*))((void**)q[0])[1])(q);
    }
  }
}
