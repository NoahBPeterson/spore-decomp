// Slice s00e5ce90 (batch bfs3, slice 19). Region 0xe5ce90-0xe5db85.
// Cell-game creature-pickup / box-distance UI helpers. Optimised:
// /O2 /MD /Gy /TP /arch:SSE /fp:fast.  Guard = 0x743b50/0xe82130.
#include "types.h"

struct cGuard19 { void* p; cGuard19(); ~cGuard19(); };

extern "C" {
  int       __cdecl FUN_00e57340(int p);
  char      __cdecl FUN_00e4ff10(char* p);
  int       __cdecl FUN_00e4fca0();
  int       __cdecl FUN_00e530e0();
  int       __cdecl FUN_00e5c9d0();
  char      __cdecl FUN_00e5cd00();
  bool      __cdecl FUN_00e5d580(int p);
  int       __cdecl FUN_00e87260(int id, void* a, int b, void* out, int n, int f);
  void      __cdecl FUN_00e53660(int a, int b);
  void      __cdecl FUN_00e539c0();
  void      __cdecl FUN_00e50450(int key);
  unsigned  __cdecl FNV1_String8(const char* s, unsigned basis, int len);
  int       __cdecl SPIDFromName(const char* s);
  void      __cdecl FUN_00e4fac0(char* state);
  void      __cdecl FUN_00e83430(int id);
  void      __cdecl FUN_00e82d10(int id);
  void      __cdecl FUN_00e82690(int id, float v);
  void      __cdecl SP_PatchSoundStart(const char* s, int b);
  void*     __cdecl FUN_0067dcd0();
  void      __cdecl FUN_00e394f0(int key, int a, int* b, int* c, int* d);
  void*     __cdecl FUN_00e4ce40(void* out);
  float     __cdecl FUN_00e52b70();
  void      __cdecl FUN_00e50020(float* a, float* b);
  float     __cdecl FUN_00e4ffe0();
  bool      __cdecl FUN_00e53280();
  void*     __cdecl FUN_00b3d400(int a);
  void*     __cdecl FUN_00b3d3f0(int a);
  void      __cdecl FUN_00e14d00(int a, int b, int c);
  void      __cdecl FUN_00e51580();
  void      __cdecl FUN_00e19350(int a, int b);
  void      __cdecl FUN_00e17df0(void* p);
  void      __cdecl FUN_00e5da10();
  // --- helpers used by the reconstructed 0xe5ce90 / 0xe5d2b0 / 0xe5d7b0 bodies ---
  void*     __cdecl FUN_00e823a0(int handle, void** out);       // 0x00e823a0 ResourceGetFromHandle
  void      __fastcall FUN_00743b50(void** p);                   // 0x00743b50 cModelWorld::VecClear
  void      __fastcall FUN_00e82130(void** p);                   // 0x00e82130 intrusive-pointer release
  void*     __cdecl FUN_00e4cc40(void* handle, void** out);      // 0x00e4cc40 thunk -> 0x00e823a0
  void      __cdecl FUN_00e628450(int a, int b, int c, void** out); // 0x00628450 CreateEffectSafe
  void      __cdecl FUN_00e4efb0(int a);                         // 0x00e4efb0 (edi = this)
  void      __cdecl FUN_00a04a90();                              // 0x00a04a90 derive
  void      __cdecl FUN_00a04ab0();                              // 0x00a04ab0 derive
  void      __cdecl FUN_00478db0(void);                          // 0x00478db0 (thiscall helper below)
  void      __cdecl FUN_00e84e40(char* msg);                     // 0x00e84e40 warning reporter
  void      __cdecl FUN_00e83430(int a);                         // 0x00e83430
  void      __cdecl FUN_00e82690(int a, float b);                // 0x00e82690
  int       __cdecl FUN_00e82620(int a, void* b);                // 0x00e82620 SP::PatchSoundStart?
  double    __cdecl FUN_01041cd0(int a, int b, int c);           // 0x01041cd0 x87 float helper (st0 result)
  float     __cdecl FUN_00e4ffe0();
  int       __cdecl FUN_009360d0();                              // 0x009360d0 RandomDouble
  int       __cdecl FUN_00e4fdb0();
}

extern "C" char* g_16b3c04;    // 0x016b3c04
extern "C" char* g_16b3c0c;    // 0x016b3c0c
extern "C" float g_16b3c88;    // 0x016b3c88
extern "C" float g_16b3c8c;    // 0x016b3c8c
extern "C" float g_16b3c90;    // 0x016b3c90
extern "C" float g_16b3c94;    // 0x016b3c94
extern "C" float g_16b3c98;    // 0x016b3c98
extern "C" float g_16b3c9c;    // 0x016b3c9c
extern "C" int   g_15a83a4;    // 0x015a83a4
extern "C" int   g_15a83a8;    // 0x015a83a8
extern "C" int   g_15a83ac;    // 0x015a83ac

static inline void** Vt(void* p) { return *(void***)p; }

// external thiscall/bound callees
struct CMgr19 {
  void* FUN_00b721d0(int id);
  void* FUN_00b72210(int handle);          // 0xb72210
  char  FUN_006ffbd0(float* p, float r);   // 0x6ffbd0
};

// @ 0x00e5d340  point-in-extended-box predicate
bool FUN_00e5d340() {
  char* e = (char*)((CMgr19*)(g_16b3c04 + 0x1c))->FUN_00b721d0(*(int*)(g_16b3c04 + 0x516c));
  if (!e) return false;
  float x = *(float*)(e + 0x4c);
  float r = *(float*)(e + 0x58);
  float d = 0.0f;
  float b = g_16b3c88;
  if (x < b || (b = g_16b3c94, b < x)) d = (x - b) * (x - b);
  float y = *(float*)(e + 0x50);
  b = g_16b3c8c;
  if (y < b || (b = g_16b3c98, b < y)) d = (y - b) * (y - b) + d;
  float z = *(float*)(e + 0x54);
  b = g_16b3c90;
  if (z < b || (b = g_16b3c9c, b < z)) d = (z - b) * (z - b) + d;
  return r * r >= d;
}

// @ 0x00e5d410
bool FUN_00e5d410(int id, float* p, float r) {
  if (id != *(int*)(g_16b3c04 + 0x40fc)) {
    char c = ((CMgr19*)0x16b3cb8)->FUN_006ffbd0(p, r);
    return (c & 0x40) == 0;
  }
  float x = p[0];
  float d = 0.0f;
  float b = g_16b3c88;
  if (x < b || (b = g_16b3c94, b < x)) d = (x - b) * (x - b);
  float y = p[1];
  b = g_16b3c8c;
  if (y < b || (b = g_16b3c98, b < y)) d = (y - b) * (y - b) + d;
  float z = p[2];
  b = g_16b3c90;
  if (z < b || (b = g_16b3c9c, b < z)) d = (z - b) * (z - b) + d;
  return r * r >= d;
}

// @ 0x00e5d580
bool FUN_00e5d580(int p) {
  if (*(int*)(p + 0xfc) != 0 && FUN_00e57340(p) == 3)
    return FUN_00e4ff10((char*)p) != 0;
  return false;
}

// @ 0x00e5daa0
void FUN_00e5daa0() {
  FUN_00e5da10();
  char* e = (char*)((CMgr19*)(g_16b3c04 + 0x1c))->FUN_00b721d0(*(int*)(g_16b3c04 + 0x411c));
  if (e != 0 && e[0x113] == 0 && e[0x112] == 0) {
    *(int*)(g_16b3c04 + 0x5158) = 5;
    FUN_00e539c0();
  }
}

// @ 0x00e5daf0
void FUN_00e5daf0() {
  g_16b3c04[0x51dc] = 0;
  FUN_00e53660(2, 1);
  g_16b3c0c[0x938] = 1;
  if (FUN_00e4fca0() == 1) {
    FUN_00e50450((int)FNV1_String8("Callout_CLG_Ending", 0x811c9dc5, 1));
    FUN_00e50450((int)FNV1_String8("Callout_CLG_TransitionButton", 0x811c9dc5, 1));
  } else if (FUN_00e4fca0() == 2) {
    FUN_00e50450(SPIDFromName("Callout_CLG_Ending"));
  }
}

// @ 0x00e5da10
void FUN_00e5da10() {
  int id = FUN_00e5c9d0();
  int key = 0;
  if (id == (int)0xa8ec6f99) key = 0x13df9c1c;
  else if (id == (int)0xcfb01b93) key = 0xf967827c;
  else if (id == (int)0x5ece4770) key = 0x7115ede5;
  int a[9];
  for (int i = 0; i < 9; ++i) a[i] = 0;
  FUN_00e394f0(key, *(int*)(g_16b3c04 + 0x5190) + 0x10, &a[6], &a[3], &a[0]);
}

// @ 0x00e5d500
void FUN_00e5d500(int* out) {
  void* local = 0;
  void* mgr = FUN_0067dcd0();
  char c = (*(char(__thiscall**)(void*, int*, void**, int, int, int, int))((char*)Vt(mgr) + 0xc))
             (mgr, out, &local, 0, 0, 0, 0);
  if (c == 0) {
    out[0] = g_15a83a4;
    out[1] = g_15a83a8;
    out[2] = g_15a83ac;
  }
  if (local) (*(void(__thiscall**)(void*, int))((char*)Vt(local) + 4))(local, 0);
}

// @ 0x00e5d2b0  random size within [lo,hi] * level size
// retail returns the float in st0 (x87 TU), so model the return as double
double FUN_00e5d2b0(int handle, int level) {
  void* h;                                      // intrusive handle local [esp]
  FUN_00743b50(&h);
  char* e = (char*)FUN_00e4cc40((void*)handle, &h);
  double lo = *(float*)(e + 0x304);
  double hi = *(float*)(e + 0x308);
  double t = ((double (__thiscall*)(void*))0x009360d0)((void*)0x01601760);
  t = t * (hi - lo) + lo;
  if (hi <= t)
    t = hi;
  else if (t < lo)
    t = lo;
  double size   = *(float*)(0x01483bd0 + level * 4);
  double kScale = *(float*)0x013f6bf8;            // 0.033333335f
  // the clamp keeps the 80-bit value live; multiplying inside each arm avoids
  // a double-precision spill of the intermediate
  float result;
  if (hi <= t)
    result = (float)(hi * size * kScale);
  else if (t < lo)
    result = (float)(lo * size * kScale);
  else
    result = (float)(t * size * kScale);
  FUN_00e82130(&h);
  return (double)result;
}

// @ 0x00e5d5b0  pickup search -- partial
void FUN_00e5d5b0(float dt) {
  *(float*)(g_16b3c04 + 0x51bc) = *(float*)(g_16b3c04 + 0x51bc) - dt;
  char* target = (char*)((CMgr19*)(g_16b3c04 + 0x1c))->FUN_00b721d0(*(int*)(g_16b3c04 + 0x411c));
  if (!target) return;
  if (((CMgr19*)(g_16b3c04 + 0x1c))->FUN_00b721d0(*(int*)(g_16b3c04 + 0x51b0))) {
    *(float*)(g_16b3c04 + 0x51bc) = FUN_00e52b70();
    return;
  }
  if (!FUN_00e53280()) return;
  float a, b;
  FUN_00e50020(&a, &b);
  float cx = (g_16b3c94 + g_16b3c88) * 0.5f;
  float cy = (g_16b3c98 + g_16b3c8c) * 0.5f;
  float cz = (g_16b3c9c + g_16b3c90) * 0.5f;
  int hits[512];
  int n = FUN_00e87260(*(int*)(g_16b3c04 + 0x40fc), &cx, *(int*)&a, hits, 0x200, 0);
  for (int i = 0; i < n; ++i) {
    char* c = (char*)((CMgr19*)(g_16b3c04 + 0x1c))->FUN_00b72210(hits[i]);
    if (FUN_00e5cd00()) continue;
    float dx = *(float*)(c + 0x4c) - *(float*)(target + 0x4c);
    float dy = *(float*)(c + 0x50) - *(float*)(target + 0x50);
    float dz = *(float*)(c + 0x54) - *(float*)(target + 0x54);
    float dist = dx * dx + dy * dy + dz * dz;
    if (dist > b * b) continue;
    if (!FUN_00e5d580((int)c)) continue;
    g_16b3c04[0x51c0] = 1;
    char* s = (char*)(*(int*)(g_16b3c04 + 0x5190) + 0xb0);
    *(int*)s = 1; *(int*)(s + 4) = 0; *(int*)(s + 8) = 0; *(float*)(s + 0xc) = 0.0f;
    *(int*)(g_16b3c04 + 0x51b4) = 3;
    *(int*)(g_16b3c04 + 0x51b0) = *(int*)c;
    *(float*)(g_16b3c04 + 0x51b8) = FUN_00e4ffe0();
    return;
  }
}

// --- layouts used by the reconstructed 0xe5ce90 body -------------------------
// object built by FUN_00e5ce90 (first argument)
struct PickupCtx {
  char           pad00[0x0c];
  void*          m_sprite;    // +0x0c  sprite / asset handle (arg 2)
  int            m_kind;      // +0x10
  void*          m_layer;     // +0x14  layer (arg 4)
  char           pad18[0x0c]; // +0x18..+0x23
  void*          m_model;     // +0x24  model produced by sMyCreateModel
  void*          m_effect;    // +0x28  intrusive effect pointer
  void*          m_slots[10]; // +0x2c  appended objects, count = m_count
  int            m_count;     // +0x54
  float          m_scale;     // +0x58
  unsigned char  m_flag5c;    // +0x5c
  char           pad5d[0x03]; // +0x5d..+0x5f
  void*          m_slot60;    // +0x60
  char           pad64[0x28]; // +0x64..+0x8b
  void*          m_slot8c;    // +0x8c
  char           pad90[0x08]; // +0x90..+0x97
  void*          m_slot98;    // +0x98
  void*          m_slot9c;    // +0x9c
  void*          m_slotA0;    // +0xa0
  void*          m_slotA4;    // +0xa4
  void*          m_slotA8;    // +0xa8
  char           padAC[0x18]; // +0xac..+0xc3
  void*          m_slotC4;    // +0xc4
};

// one 0x28-byte entry of the resource record array returned by FUN_00e4cc40
struct PickupRec {
  char  pad00[0x04];
  int   m_kind;     // +0x04  switch selector
  char  pad08[0x08];// +0x08..+0x0f
  int   m_id;       // +0x10  model / effect id
  char  pad14[0x14];// +0x14..+0x27
};

struct PickupList {
  char        pad00[0x14];
  PickupRec*  m_recs;  // +0x14
  int         m_count; // +0x18
};

// object reachable through PickupCtx::m_effect after FUN_00478db0
struct EffectObj {
  char     pad00[0x04];
  unsigned m_flags;      // +0x04
  char     pad08[0x44];  // +0x08..+0x4b
  int      m_v4[3];      // +0x4c..+0x57
};

// intrusive base shared by the objects released through ReleaseSmart
struct SmartObj {
  void**   m_vt;         // +0x00
  unsigned m_flags;      // +0x04
  char     pad08[0x38];  // +0x08..+0x3f
  int      m_refs;       // +0x40
};

// 0x00e4f000  SP::sMyCreateModel(mgr in esi, id in ecx); retried on failure
static void* CreateModel(void* mgr, int id) {
  SmartObj* o = (SmartObj*)mgr;
  void* m = ((void* (__thiscall*)(void*, int, int, int))((void**)o->m_vt)[3])(o, id, 0, 0);
  if (m == 0) {
    FUN_00e84e40((char*)0x014851f4);  // "Unable to create model"
    m = ((void* (__thiscall*)(void*, int, int, int))((void**)o->m_vt)[3])
          (o, 0xcf571b4e, 0xd94352ed, 0);
  }
  ((SmartObj*)m)->m_refs += 1;
  return m;
}

// 0x00e4efb0  create a model and stamp two post-creation flags on it
static int MakeEffectModel(void* mgr, int* scratch) {
  SmartObj* o = (SmartObj*)mgr;
  int r = ((int (__thiscall*)(void*, int*, int, void*, void*, int))((void**)o->m_vt)[0x30 / 4])
            (o, scratch, 2, (void*)0x016b3c28, (void*)0x015a7c4c, 1);
  if (r != 0) {
    ((void (__thiscall*)(void*, int, int, int))((void**)o->m_vt)[0x40 / 4])(o, r, 0, 1);
    ((void (__thiscall*)(void*, int))0x00a04ce0)((void*)r, 1);
    ((void (__thiscall*)(void*, int))0x00a04d00)((void*)r, 1);
  }
  return r;
}

// clear one intrusive-pointer field and drop a reference (vtable slot 1)
static inline void ReleaseIface(void** slot) {
  void* p = *slot;
  if (p != 0) {
    *slot = 0;
    ((void (__thiscall*)(void*))((void**)Vt(p))[1])(p);
  }
}

// release PickupCtx::m_effect via SmartObj::m_refs, falling back to vtable+0x170
static void ReleaseSmart(PickupCtx* self) {
  SmartObj* p = (SmartObj*)self->m_effect;
  if (p == 0)
    return;
  self->m_effect = 0;
  if (p->m_refs > 1) {
    p->m_refs -= 1;
  } else {
    int flag = (int)(p->m_flags >> 31);
    ((void (__thiscall*)(void*, int))((void**)p->m_vt)[0x170 / 4])(p, flag);
  }
}

// @ 0x00e5d7b0  mission slot tick
void FUN_00e5d7b0(int slot, int arg4) {
  (void)arg4;
  char* game = g_16b3c04;
  int*  st   = *(int**)(game + 0x5190);       // per-slot state block

  if (*(char*)((char*)st + 0x69) == 0) {
    *(float*)(game + 0x51d0) = *(float*)0x014763b0;
    *(float*)(game + 0x51cc) = *(float*)0x01483f64;
    void* h = 0;                              // intrusive handle local (arg slot reuse)
    FUN_00743b50(&h);
    char* res = (char*)FUN_00e4ce40(&h);
    int   v   = *(int*)(res + 0xdc);
    FUN_00e82130(&h);
    if (v == 1) {
      FUN_00e53660(2, 1);
      g_16b3c0c[0x938] = 1;
      FUN_00e50450((int)FNV1_String8("Callout_CLG_Mate", 0x811c9dc5, 1));
    }
  }

  st = *(int**)(game + 0x5190);
  if (*(int*)((char*)st + 0x90) != 1) {
    *(int*)((char*)st + 0x90) = 1;
    *(int*)((char*)st + 0x94) = 0;
    *(int*)((char*)st + 0x98) = 0;
    *(int*)((char*)st + 0x9c) = 0;
  }

  st = *(int**)(game + 0x5190);
  if (*(int*)((char*)st + 0x90) == 1) {
    int* counter = (int*)((char*)st + 0x94);
    if (*counter != 6) {
      int n = *counter + 1;
      *counter = n;
      int clamped = (n > 6) ? 6 : *counter;
      *counter = clamped;
      if (clamped == 6) {
        FUN_00e82690(0xc1fa4704, 1.0f);
        FUN_00e82620((int)0x014853c0, 0);      // "ui_mission_complete"
        *(int*)((char*)st + 0x90) = 3;
        *(float*)((char*)st + 0x9c) = *(float*)0x01486110;
      }
    }
  }

  st = *(int**)(game + 0x5190);
  *(char*)((char*)st + 0x69) = 1;
  st = *(int**)(game + 0x5190);
  *(char*)((char*)st + 0x68) = 1;
  st = *(int**)(game + 0x5190);
  *(int*)((char*)st + 0x34 + slot * 4) = 2;

  int key = 0;
  for (int i = 0; i < 0xc; ++i) {
    if (*(int*)(0x01483e98 + i * 8) == slot) {
      key = *(int*)(0x01483e9c + i * 8);
      break;
    }
  }

  FUN_00e83430(key);
  void* card = ((void* (__cdecl*)())FUN_00b3d400)();
  ((void (__thiscall*)(void*, int, int, int))FUN_00e14d00)
      (card, 0, 0x00b1b104, *(int*)0x0150d6d8);
  FUN_00e51580();
  if (FUN_00e530e0() < 1)
    FUN_00e82d10((int)0x83932384);

  FUN_00e4fac0((char*)(*(int*)(game + 0x5190) + 0x34));
  void* panel = ((void* (__cdecl*)())FUN_00b3d3f0)();
  ((void (__thiscall*)(void*, int, int))FUN_00e19350)(panel, -0xf, key);

  void* refresh = ((void* (__cdecl*)())FUN_00b3d400)();
  if (refresh != 0)
    ((void (__thiscall*)(void*))FUN_00e17df0)(refresh);
}

// @ 0x00e5ce90  creature/box pickup builder
void FUN_00e5ce90(int* rawSelf, int spriteHandle, int variant, int* layer, char owner,
                  int arg6, int eventKind, int arg8) {
  PickupCtx* self = (PickupCtx*)rawSelf;

  self->m_sprite = (void*)spriteHandle;
  self->m_count  = 0;

  // drop the seven cached intrusive pointers, in the retail order
  ReleaseIface(&self->m_slotA8);
  ReleaseIface(&self->m_slotA0);
  ReleaseIface(&self->m_slotA4);
  ReleaseIface(&self->m_slot98);
  ReleaseIface(&self->m_slot9c);
  ReleaseIface(&self->m_slot8c);
  ReleaseIface(&self->m_slot60);

  self->m_flag5c = 1;
  self->m_kind   = 0;
  self->m_layer  = (void*)layer;
  self->m_slotC4 = 0;

  double d = FUN_01041cd0(0, 0, 0x3f800000);
  if (d < 0.0) d = 0.0;
  if (d > 1.0) d = 1.0;
  self->m_scale = (float)d;

  char* gfx = *(char**)0x016b3c08;
  void* mgr;    // gfx+0x161c0 / +0x161cc : model manager handed to sMyCreateModel (esi)
  void* fx;     // gfx+0x161bc / +0x161c8 : first argument of CreateEffectSafe
  void* other;  // gfx+0x161c4 / +0x161d0 : object handed to FUN_00e4efb0 (edi)
  if (variant == 1) {
    mgr   = *(void**)(gfx + 0x161c0);
    fx    = *(void**)(gfx + 0x161bc);
    other = *(void**)(gfx + 0x161c4);
  } else {
    mgr   = *(void**)(gfx + 0x161cc);
    fx    = *(void**)(gfx + 0x161c8);
    other = *(void**)(gfx + 0x161d0);
  }

  if (arg6 == 0) {
    ReleaseSmart(self);
    self->m_model = 0;
  } else if (eventKind == 0x3d97a8e4) {
    int scratch = 0;
    int* o = (int*)MakeEffectModel(other, &scratch);
    self->m_model = (void*)o;
    if (o != 0) {
      ((void (__thiscall*)(void*, int))FUN_00a04a90)(o, 0);
      ((void (__thiscall*)(void*, int))FUN_00a04ab0)(o, 0);
      ((void (__thiscall*)(void*, int, int))((void**)Vt(o))[1])(o, 0, 0);
    }
    ReleaseSmart(self);
  } else if (eventKind == 0x476a98c7) {
    void* fac = *(void**)(gfx + 0x161cc);
    int* eff = (int*)((void* (__thiscall*)(void*, int, int, int))((void**)Vt(fac))[3])
                     (fac, arg6, arg8, 0);
    ((void (__thiscall*)(void*, int*))FUN_00478db0)(&self->m_effect, eff);
    EffectObj* e = (EffectObj*)self->m_effect;
    e->m_flags |= 4;
    e->m_v4[0] = *(int*)0x015a7bbc;
    e->m_v4[1] = *(int*)0x015a7bc0;
    e->m_v4[2] = *(int*)0x015a7bc4;
  }

  void* h = 0;                                  // intrusive resource handle local
  FUN_00743b50(&h);
  PickupList* list = (PickupList*)FUN_00e4cc40(layer, &h);

  for (int i = 0; i < list->m_count; ++i) {
    PickupRec* rec = list->m_recs + i;
    switch (rec->m_kind) {
    case 0:
      if (self->m_model == 0)
        self->m_slots[self->m_count++] = CreateModel(mgr, rec->m_id);
      else
        self->m_count++;
      break;

    case 1: {
      void* out = 0;
      FUN_00e628450((int)fx, rec->m_id, 0, &out);
      ((void (__thiscall*)(void*, int))((void**)Vt(out))[2])(out, owner == 0 ? 1 : 0);
      self->m_slots[self->m_count++] = out;
      break;
    }

    case 3:
      if (self->m_model == 0) {
        int scratch = 0;
        int* o = (int*)MakeEffectModel(other, &scratch);
        if (o != 0) {
          ((void (__thiscall*)(void*, int))FUN_00a04a90)(o, 0);
          ((void (__thiscall*)(void*, int))FUN_00a04ab0)(o, 0);
          ((void (__thiscall*)(void*, int, int))((void**)Vt(o))[1])(o, 0, 0);
          self->m_slots[self->m_count++] = o;
        }
      } else {
        self->m_slots[self->m_count++] = 0;
      }
      break;

    case 4:
    case 5:
    case 6:
      self->m_slots[self->m_count++] = 0;
      break;

    default:
      break;
    }
  }

  FUN_00e82130(&h);
}
