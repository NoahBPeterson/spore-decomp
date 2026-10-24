// Slice s00c368c0 - SP::cSPGameDataUFO (Simulator) methods and helpers.
// Reconstructed from annotated disassembly + Ghidra decompiles.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef          char  s8;
typedef unsigned long long u64;
typedef          long long s64;

#include <math.h>

// ---- vtable-call signature typedefs (all thiscall) -----------------------
typedef void*  (__thiscall *TFp0)(void*);
typedef void*  (__thiscall *TFpk)(void*, u32);
typedef float* (__thiscall *TFfp0)(void*);
typedef float  (__thiscall *TFf0)(void*);
typedef void   (__thiscall *TFv0)(void*);
typedef void   (__thiscall *TFv1)(void*, u32);
typedef void   (__thiscall *TFv4)(void*, u32, void*, void*, void*);
typedef void*  (__thiscall *TFmix)(void*, float, void*, void*, void*, void*);

// ---- extern data --------------------------------------------------------
extern float       g_kZero;        // 0x01485378
extern float       g_kOne;         // 0x01485720
extern float       g_kPointTwo;    // 0x0146bb60
extern float       g_kEpsilon;     // 0x0146bb74
extern u8          g_b168df34;     // 0x0168df34
extern void*       g_p158128c;     // 0x0158128c
extern u32         g_168df70;      // 0x0168df70
extern u32         g_168df6c;      // 0x0168df6c
extern u32*        g_pBucketArr;   // 0x0152d6a0
extern u32         g_nBuckets;     // 0x0152d6a4

struct PlanetGlob {
  u8    pad00[0x0c];   // +0x000
  float f0c;           // +0x00c
  float f10;           // +0x010
  u8    pad14[0x08];   // +0x014
  float f1c;           // +0x01c
  float f20;           // +0x020
};
extern PlanetGlob* g_planetGlob;   // 0x0168df68

// ---- forward callees ----------------------------------------------------
void*  __stdcall FUN_00b18460(u32 key);        // 0x00b18460
void*  __cdecl FUN_01021300();                 // 0x01021300 (GetPlayerEmpire)
void*  __cdecl MessageServer();                // 0x0067dcc0
struct SpaceGameC;
SpaceGameC* __cdecl SpaceGameGet();           // 0x01002bd0
float  __cdecl GetPropFloat(void* src, u32 key, float def);
u32    __cdecl FUN_00ac8fa0(void* src, u32 key, u32 def);
u32    __cdecl FUN_00cee370();                 // 0x00cee370
u8     __cdecl FUN_00c0c0e0();                 // 0x00c0c0e0
u8     __cdecl FUN_00c0b7c0(u32 obj);          // 0x00c0b7c0
void*  __cdecl FUN_00bc97f0(u32 a, u32 b, u32 c, u32 d);   // 0x00bc97f0
void*  __cdecl FUN_00b3d240();                 // 0x00b3d240
void   __cdecl FUN_00c36870();                 // 0x00c36870
float  __fastcall FUN_00b7e4d0(void* planet);  // 0x00b7e4d0
float  __fastcall FUN_0104be20(void* t);       // 0x0104be20
float  __fastcall FUN_0104be30(void* t);       // 0x0104be30
u8     __fastcall FUN_0104fff0(void* t);       // 0x0104fff0
void   __cdecl FUN_00cd7d10();
void   __cdecl FUN_00d3d420();
void   __cdecl FUN_00ace0f0();
void   __cdecl FUN_00b1e500();
void*  __cdecl FUN_00f473a0(u32 size, const char* name, u32 a, u32 b, u32 c, u32 d);
void   __cdecl FUN_00f47380(void* p);
bool   __cdecl WriteUint32(void* stream, const u32* v, u32 n, s32 f);
bool   __cdecl StreamWrite(void* stream, const void* data, s32 n);

struct PlanetModelC {
  float GetRadiusAt(float* pos);   // 0x00b7ef70
  float GetWaterHeight();          // 0x00b7e390
};
PlanetModelC* __cdecl PlanetModel();   // 0x00b3d350

struct NounMgr;
NounMgr* __cdecl NounManager();        // 0x00b3d300

struct WStr {
  u32* mBegin;   // +0x00
  u32* mEnd;     // +0x04
  u32* mCap;     // +0x08
  void assign(u32* first, u32* last);            // 0x00423650
  void range_initialize(const wchar_t* str);     // 0x00579a90
};
WStr* __cdecl PathPick(WStr* out, WStr* prefix, WStr* suffix);   // 0x00688f00
void  __cdecl WStrFormat(WStr* out, const wchar_t* fmt, void* arg); // 0x0041e050

struct PtrVec {
  u32* mBegin;   // +0x00
  u32* mEnd;     // +0x04
  u32* mCap;     // +0x08
};

struct Loco {
  void* vtbl;              // +0x00  (ufo+0x34)
  void* Find(u32 key);                       // 0x00c41d00
  void  Set(void* p);                        // 0x00c421b0
  u8    Write(void* stream);                 // 0x00c448a0
};

struct Combat {
  void* vtbl;              // +0x00  (ufo+0x508)
  void* Find2(u32 key);                      // 0x00bfc380
  u8    Write(void* stream);                 // 0x00bfc4a0
};

struct CCombatant0 {
  void NotifyAttack(void* p);                // 0x010829f0
};

struct Timer {
  u8 data[0x3c];                             // 0x00c37b8 sized subobject
  void Restart();                            // 0x00bc3130
};

struct Sub70 {
  u8  pad00[0x70];
  u32 f70;                                   // +0x070
};

struct BehTree {
  void Write(void* stream);                  // 0x00bc9a80
};

struct EffectC {
  u8    pad00[0x0c];
  float f0c;                                 // +0x00c
  float f10;                                 // +0x010
};

struct F18Obj {
  u8    pad00[0x18];
  float f18;                                 // +0x018
};

struct Ufo {
  void*  vtbl;                 // +0x000
  u8     pad004[0x30];         // +0x004
  Loco   loco;                 // +0x034
  u32*   p38;                  // +0x038
  u8     pad03c[0x1c];         // +0x03c
  float  f58;                  // +0x058
  u32    idx5c;                // +0x05c
  u8     pad060[0x1a8];        // +0x060
  void*  p208;                 // +0x208
  u8     pad20c[0x2fc];        // +0x20c
  Combat combat;               // +0x508
  u8     pad50c[0x34];         // +0x50c
  float  f540;                 // +0x540
  u8     pad544[0x184];        // +0x544
  void*  p6c8;                 // +0x6c8
  u8     pad6cc[0x14];         // +0x6cc
  u32    u6e0;                 // +0x6e0
  u8     pad6e4[0x30];         // +0x6e4
  u32    state714;             // +0x714
  u8     pad718[0x4c];         // +0x718
  void*  p764;                 // +0x764
  u8     pad768[0x14];         // +0x768
  u8     b77c;                 // +0x77c
  u8     b77d;                 // +0x77d
  u8     b77e;                 // +0x77e
  u32    k780;                 // +0x780
  u32    k784;                 // +0x784
  u32    k788;                 // +0x788
  u8     b78c;                 // +0x78c
  u8     b78d;                 // +0x78d
  u8     pad78e[0x0a];         // +0x78e
  void*  p798;                 // +0x798
  void*  p79c;                 // +0x79c
  void*  p7a0;                 // +0x7a0
  void*  p7a4;                 // +0x7a4
  u8     pad7a8[0x08];         // +0x7a8
  void*  p7b0;                 // +0x7b0
  u8     pad7b4[0x04];         // +0x7b4
  Timer  timer;                // +0x7b8
  float  f7f4;                 // +0x7f4
  float  f7f8;                 // +0x7f8
};

struct LocoF {
  u8    pad000[0x144];
  float f144;                  // +0x144
  float f148;                  // +0x148
  float f14c;                  // +0x14c
  float f150;                  // +0x150
};

struct Vec3 {
  float x, y, z;
};

struct ParamObj {
  void*  vtbl;                 // +0x000  (vtable of the source object)
  PtrVec vec;                  // +0x004
};

struct Cand {
  u8    pad000[0xc0];          // +0x000
  void* vtbl;                  // +0x0c0
  u8    pad0c4[0x135 - 0xc4];  // +0x0c4
  u8    b135;                  // +0x135
  u8    pad136[0xb1c - 0x136]; // +0x136
  s32   b1c;                   // +0xb1c
  u8    padB20[0xb5e - 0xb20]; // +0xb20
  u8    b5e;                   // +0xb5e
};

struct GDVec {
  u32  pad00;
  u32* mBegin;                 // +0x004
  u32* mEnd;                   // +0x008
};

struct NounMgr {
  GDVec* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);
  void*  GetPlayerEmpireOrMinus1();       // 0x00b1f9d0
};

struct Empire {
  void SetUFOKey(void* key);              // 0x00c35740
};

struct Inventory {
  u8  pad00[0x76c];
  s32 f76c;                               // +0x76c
};

struct UFOsim {
  Inventory* GetPlayerInventory();        // 0x00a1ad60
};
UFOsim* __cdecl GetUFOSimulator();        // 0x00ffbe50
struct SpaceGameC {
  u8 f4c30();                             // 0x01004c30
};

struct CGameData {
  u8 Write(void* stream);                 // 0x00b18590
  void GetCastID();                       // 0x00bfcac0
};

struct CCommunity {
  void func54h(s32 id);                   // 0x00c88670
};

struct CInteractable {
  void SetEffectId(s32 id, float v);      // 0x00c3f160
};

struct Big2 {
  void* init(void* owner);                // 0x00694e60
};
struct Big28 {
  void* Init();                           // 0x0105d180
};

struct GroundContainer {
  u8     pad00[0x18];
  PtrVec list;                 // +0x018
  u8     pad24[0x08];          // +0x024
  WStr   name;                 // +0x02c
};

struct EAIter {
  u32 p0;                      // +0x00
  u32 p1;                      // +0x04
  u32 p2;                      // +0x08
  u32 p3;                      // +0x0c
};
struct EAHash {
  EAIter find(const u32& key);            // 0x00645ed0
};

struct cVarListSerializer {
  u32 mData[0xa14 / 4];                   // +0x000
  void Ctor(void* owner, void* list, u32 sig);  // 0x00692f90
  u8   Serialize(void* stream);                 // 0x00692900
};

void __stdcall WaitingList1_Insert(void* pos, void* value);   // 0x00690b80
void __stdcall FUN_00695b40(void* a, void* b, const wchar_t* c); // 0x00695b40

// ======================================================================
// 0x00c368c0 - register/lookup a cGameBundleGroundContainer in the sim
// ======================================================================
// @ 0x00c368c0
u8 __fastcall FUN_00c368c0(Ufo* self, void* dummy, ParamObj* param)
{
  (void)dummy;
  u32 key = (u32)self;
  EAIter it = ((EAHash*)0x0152d69c)->find(key);
  if (it.p0 == g_pBucketArr[g_nBuckets]) {
    GroundContainer* gc;
    Big2* raw = (Big2*)FUN_00f473a0(0x74, "Simulator", 0, 0, 0, 0);
    if (raw == 0) gc = 0;
    else gc = (GroundContainer*)raw->init(self);

    WStr fmt;
    fmt.mBegin = (u32*)0x01667bac;
    fmt.mEnd = (u32*)0x01667bac;
    fmt.mCap = (u32*)0x01667bae;
    WStrFormat(&fmt, L" @ 0x%08x", self);

    WStr name;
    name.mBegin = 0;
    name.mEnd = 0;
    name.mCap = 0;
    name.range_initialize(L"cGameBundleGroundContainer");

    WStr path;
    path.mBegin = 0;
    path.mEnd = 0;
    path.mCap = 0;
    WStr* picked = PathPick(&path, &name, &fmt);
    if (picked != &gc->name) {
      gc->name.assign(picked->mBegin, picked->mEnd);
    }
    if ((((u32)path.mEnd - (u32)path.mBegin) & ~1u) > 2 && path.mBegin)
      FUN_00f47380(path.mBegin);
    if ((((u32)name.mEnd - (u32)name.mBegin) & ~1u) > 2 && name.mBegin)
      FUN_00f47380(name.mBegin);

    u32 v = (u32)param;
    if (gc->list.mEnd < gc->list.mCap) {
      *gc->list.mEnd = v;
      gc->list.mEnd++;
    } else {
      WaitingList1_Insert(gc->list.mEnd, &v);
    }

    u32 w = (u32)gc;
    if (param->vec.mEnd < param->vec.mCap) {
      *param->vec.mEnd = w;
      param->vec.mEnd++;
    } else {
      WaitingList1_Insert(param->vec.mEnd, &w);
    }

    if ((((u32)fmt.mEnd - (u32)fmt.mBegin) & ~1u) > 2 && fmt.mBegin)
      FUN_00f47380(fmt.mBegin);
  } else {
    u32* slot = (u32*)it.p0 + 1;
    u32 a = *slot;
    u32 v = (u32)a;
    if (param->vec.mEnd < param->vec.mCap) {
      *param->vec.mEnd = v;
      param->vec.mEnd++;
    } else {
      WaitingList1_Insert(param->vec.mEnd, &v);
    }
    GroundContainer* gc = (GroundContainer*)a;
    u32 w = (u32)param;
    if (gc->list.mEnd < gc->list.mCap) {
      *gc->list.mEnd = w;
      gc->list.mEnd++;
    } else {
      WaitingList1_Insert(gc->list.mEnd, &w);
    }
  }
  FUN_00695b40(self, (void*)0x01567e48, L"cGameData");
  FUN_00695b40(&self->loco, (void*)0x015816b8, L"cGameBundleContainer");
  return 1;
}

// ======================================================================
// 0x00c36ae0 - periodic attractor scan (slow / fast paths)
// ======================================================================
// @ 0x00c36ae0
void __fastcall FUN_00c36ae0(Ufo* self, void* dummy, float dt)
{
  (void)dummy;
  self->f58 -= dt;
  if (self->f58 > 0.0f) return;
  self->f58 = GetPropFloat(g_p158128c, 0x5aac320eu, 1.0f);

  u32 count = FUN_00cee370();
  if (count == 0) return;

  u32 a = FUN_00ac8fa0(g_p158128c, 0xfccc22aeu, 5);
  float radius = GetPropFloat(g_p158128c, 0x1d3a528u, 50.0f);
  u32 b = FUN_00ac8fa0(g_p158128c, 0xfd23371du, 5);
  u32 limit = (b < 0x11) ? b : 16u;

  if (count <= self->idx5c) self->idx5c = 0;
  u32 n = (count <= a) ? count : a;

  for (u32 k = n; k != 0; --k) {
    u32 obj = self->p38[self->idx5c];
    bool slow = (g_b168df34 == 0);
    self->idx5c = (self->idx5c + 1) % count;
    if (slow) {
      float r2 = radius * radius;
      u32 found = 0;
      NounMgr* nm = NounManager();
      GDVec* vec = nm->GetGameDataVector((void*)&FUN_00cd7d10, (void*)&FUN_00d3d420,
                                         (void*)&FUN_00ace0f0, (void*)&FUN_00b1e500,
                                         (void*)&g_b168df34);
      for (u32* it = vec->mBegin; it != vec->mEnd; ++it) {
        if (found >= limit) break;
        Cand* cand = (Cand*)*it;
        if (cand->b135 != 0 && cand->b5e == 0 && FUN_00c0c0e0() == 0 && FUN_00c0b7c0(obj) != 0) {
          float* pa = ((TFfp0)((void**)self->loco.vtbl)[0x2c / 4])(&self->loco);
          float* pb = ((TFfp0)((void**)cand->vtbl)[0x2c / 4])(cand);
          float dx = pb[0] - pa[0];
          float dy = pb[1] - pa[1];
          float dz = pb[2] - pa[2];
          if (dx * dx + dy * dy + dz * dz < r2) {
            EffectC* e = (EffectC*)FUN_00bc97f0(0, 0x100, 0x7f7fffff, obj);
            if (e != 0) { e->f0c = 10.0f; e->f10 = 60.0f; }
            ++found;
          }
        }
      }
    } else {
      u32 buf[16];
      PtrVec vec;
      vec.mBegin = buf;
      vec.mEnd = buf;
      void** mgr = (void**)FUN_00b3d240();
      void* h = ((TFmix)((void**)self->loco.vtbl)[0x2c / 4])(&self->loco, radius, &vec,
                                                             0, (void*)&FUN_00c36870, (void*)obj);
      ((TFv1)((void**)*mgr)[0x48 / 4])(mgr, (u32)h);
      u32 c = 0;
      for (u32* it = vec.mBegin; it != vec.mEnd && c < limit; ++it, ++c) {
        EffectC* e = (EffectC*)FUN_00bc97f0(0, 0x100, 0x7f7fffff, obj);
        if (e != 0) { e->f0c = 10.0f; e->f10 = 60.0f; }
      }
      for (u32* it = vec.mBegin; it != vec.mEnd; ++it) {
        void* p = (void*)*it;
        if (p != 0) ((TFv0)(*(void***)p)[0x0c0 / 4])(p);
      }
      if (vec.mBegin != 0 && buf[-1] != 0) FUN_00f47380(vec.mBegin);
    }
  }
}

// ======================================================================
// 0x00c36e80 - cast key to game-data object
// ======================================================================
// @ 0x00c36e80
void* __fastcall FUN_00c36e80(Ufo* self, void* dummy, u32 key)
{
  (void)dummy;
  if (key != 0xb033b403u) {
    void* r = FUN_00b18460(key);
    if (r == 0) {
      r = self->loco.Find(key);
      if (r == 0) r = self->combat.Find2(key);
    }
    return r;
  }
  return self;
}

// ======================================================================
// 0x00c36ee0 - SP::cSPGameDataUFO::Write
// ======================================================================
// @ 0x00c36ee0
u8 __fastcall FUN_00c36ee0(Ufo* self, void* dummy, void* stream)
{
  (void)dummy;
  void* w = ((TFp0)((void**)stream)[0x20 / 4])(stream);
  w = ((TFp0)((void**)w)[0x18 / 4])(w);
  u32 ver = 0xb033b403u;
  WriteUint32(w, &ver, 1, 0);

  u8 ok = 0;
  if (!((CGameData*)self)->Write(stream)) goto afterChain;
  if (!self->combat.Write(stream)) goto afterChain;
  if (!self->loco.Write(stream)) goto afterChain;
  ok = 1;
afterChain:
  g_168df70 = (self->p7b0 != 0) ? ((Sub70*)self->p7b0)->f70 : 0;
  g_168df6c = (self->p764 != 0) ? ((Sub70*)self->p764)->f70 : 0;

  cVarListSerializer ser;
  ser.Ctor(self, (void*)0x01573290, 0x1a80d26u);
  if (ok) ok = ser.Serialize(stream);

  void* p = ((TFp0)((void**)stream)[0x20 / 4])(stream);
  if (self->p6c8 != 0) {
    void* ow = ((TFp0)((void**)p)[0x18 / 4])(p);
    u8 one = 1;
    StreamWrite(ow, &one, 1);
    ((BehTree*)self->p6c8)->Write(stream);
  } else {
    void* ow = ((TFp0)((void**)p)[0x18 / 4])(p);
    u8 zero = 0;
    StreamWrite(ow, &zero, 1);
  }
  return ok;
}

// ======================================================================
// 0x00c37040 - SP::cSPGameDataUFO::CanWarp
// ======================================================================
// @ 0x00c37040
bool __fastcall FUN_00c37040(Ufo* self, void* dummy)
{
  (void)dummy;
  switch (self->state714) {
  case 0:
    if (self->f7f4 > g_kZero) {
      SpaceGameC* sg = (SpaceGameC*)SpaceGameGet();
      return sg->f4c30() == 0;
    }
    return false;
  case 3: {
    Inventory* inv = GetUFOSimulator()->GetPlayerInventory();
    if (inv == 0) return true;
    return inv->f76c >= 2;
  }
  case 8:
  case 9:
    return false;
  default:
    return true;
  }
}

// ======================================================================
// 0x00c370e0 - "is target close" test used while warping
// ======================================================================
// @ 0x00c370e0
bool __fastcall FUN_00c370e0(Ufo* self, void* dummy)
{
  (void)dummy;
  if (self->b77e != 0) {
    void* p = ((TFp0)((void**)self->loco.vtbl)[0xac / 4])(&self->loco);
    if (p != 0) {
      return ((F18Obj*)p)->f18 <= g_kEpsilon;
    }
  }
  return 0;
}

// ======================================================================
// 0x00c37130 - set flag byte + dirty marker
// ======================================================================
// @ 0x00c37130
void __fastcall FUN_00c37130(Ufo* self, void* dummy, u8 v)
{
  (void)dummy;
  if (self->b77c != v) {
    self->b77c = v;
    self->b77d = 1;
  }
}

// ======================================================================
// 0x00c37180 - SP::cSPGameDataUFO::SetDesiredModel
// ======================================================================
// @ 0x00c37180
void __fastcall FUN_00c37180(Ufo* self, void* dummy, u32* key, u8 flag)
{
  (void)dummy;
  if (self->k780 == key[0] && self->k784 == key[1] && self->k788 == key[2]) return;
  bool initial = (self->state714 == 0);
  self->k780 = key[0];
  self->k784 = key[1];
  self->k788 = key[2];
  self->b78c = flag;
  self->b78d = 1;
  if (initial) {
    Empire* e = (Empire*)FUN_01021300();
    if (e != 0) {
      e->SetUFOKey(key);
      void* ms = MessageServer();
      ((TFv4)((void**)ms)[0x18 / 4])(ms, 0x5da932eu, 0, 0, 0);
    }
  }
}

// ======================================================================
// 0x00c37230 - getter for the desired model key
// ======================================================================
// @ 0x00c37230
void __fastcall FUN_00c37230(Ufo* self, void* dummy, u32* out, u8* outFlag)
{
  (void)dummy;
  out[0] = self->k780;
  out[1] = self->k784;
  out[2] = self->k788;
  *outFlag = self->b78c;
}

// ======================================================================
// 0x00c37270 - reset the warp timer / locomotion target
// ======================================================================
// @ 0x00c37270
void __fastcall FUN_00c37270(Ufo* self, void* dummy)
{
  (void)dummy;
  void* o = FUN_00f473a0(0x1c, "Simulator", 0, 0, 0, 0);
  void* u = (o != 0) ? ((Big28*)o)->Init() : 0;
  self->loco.Set(u);
  self->timer.Restart();
}

// ======================================================================
// 0x00c372c0 - x87 compare of f540 vs 0.2 * virtual float
// ======================================================================
// @ 0x00c372c0
s32 __fastcall FUN_00c372c0(Ufo* self, void* dummy)
{
  (void)dummy;
  float v = self->f540;
  float r = ((TFf0)((void**)self->combat.vtbl)[0x58 / 4])(&self->combat);
  if (v <= r * 0.2f) return 1;
  return 0;
}

// ======================================================================
// 0x00c37300 - SSE compare of f7f4 vs 0.2 * f7f8
// ======================================================================
// @ 0x00c37300
s32 __fastcall FUN_00c37300(Ufo* self, void* dummy)
{
  (void)dummy;
  if (self->f7f8 * 0.2f >= self->f7f4) return 1;
  return 0;
}

// ======================================================================
// 0x00c37330 - is the object's empire the player's empire?
// ======================================================================
// @ 0x00c37330
bool __fastcall FUN_00c37330(Loco* loco, void* dummy)
{
  (void)dummy;
  Ufo* self = (Ufo*)((char*)loco - 0x34);
  void* emp = NounManager()->GetPlayerEmpireOrMinus1();
  void* v = ((TFp0)((void**)self->vtbl)[0x4c / 4])(self);
  return v == emp;
}

// ======================================================================
// 0x00c37550 - alt float getter A
// ======================================================================
// @ 0x00c37550
float __fastcall FUN_00c37550(LocoF* self, void* dummy, s32 which)
{
  (void)dummy;
  if (which == 0) return self->f144;
  return self->f14c;
}

// ======================================================================
// 0x00c37570 - alt float getter B
// ======================================================================
// @ 0x00c37570
float __fastcall FUN_00c37570(LocoF* self, void* dummy, s32 which)
{
  (void)dummy;
  if (which == 0) return self->f148;
  return self->f150;
}

// ======================================================================
// 0x00c375d0 - interpolate altitude between surface and water plane
// ======================================================================
// @ 0x00c375d0
float __cdecl FUN_00c375d0(float* pos)
{
  float radius = PlanetModel()->GetRadiusAt(pos);
  float water = PlanetModel()->GetWaterHeight();
  float base = (water > radius) ? water : radius;
  float h = FUN_00b7e4d0(PlanetModel());
  PlanetGlob* pg = g_planetGlob;
  float t = (sqrtf(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]) - (pg->f0c + base)) /
            ((pg->f10 + h) - (pg->f0c + base));
  float r = (1.0f - t) * base + t * h;
  return (r > base) ? r : base;
}

// ======================================================================
// 0x00c376b0 - planet ceiling + water offset
// ======================================================================
// @ 0x00c376b0
float __cdecl FUN_00c376b0()
{
  float top = g_planetGlob->f10;
  return FUN_00b7e4d0(PlanetModel()) + top;
}

// ======================================================================
// 0x00c37740 - pick the nearest trigger band for a target object
// ======================================================================
// @ 0x00c37740
void* __fastcall FUN_00c37740(Ufo* self, void* dummy, ParamObj* param)
{
  (void)dummy;
  if (param == 0) return 0;
  void* a = ((TFpk)((void**)param->vtbl)[0x5c / 4])(param, 0xb033b403u);
  void* b = ((TFpk)((void**)param->vtbl)[0x5c / 4])(param, 0x137e8e0u);
  if (a == 0 && (b == 0 || ((Cand*)b)->b1c != 2)) return 0;

  void* t = ((TFp0)((void**)param->vtbl)[0x08 / 4])(param);
  float* p1 = ((TFfp0)((void**)self->loco.vtbl)[0x2c / 4])(&self->loco);
  float* p2 = ((TFfp0)((void**)t)[0x2c / 4])(t);
  float dx = p2[0] - p1[0];
  float dy = p2[1] - p1[1];
  float dz = p2[2] - p1[2];
  float d = sqrtf(dx * dx + dy * dy + dz * dz);

  if (self->p798 != 0) {
    float lo = FUN_0104be20(self->p798);
    if (lo <= d) {
      float hi = FUN_0104be30(self->p798);
      if (d <= hi) return self->p798;
    }
  }
  if (self->p79c != 0) {
    float lo = FUN_0104be20(self->p79c);
    if (lo <= d) {
      float hi = FUN_0104be30(self->p79c);
      if (d <= hi) return self->p79c;
    }
  }
  if (self->p7a0 != 0) {
    float lo = FUN_0104be20(self->p7a0);
    if (lo <= d) {
      float hi = FUN_0104be30(self->p7a0);
      if (d <= hi) return self->p7a0;
    }
  }
  return 0;
}

// ======================================================================
// 0x00c37890 - is the target inside the selected trigger band?
// ======================================================================
// @ 0x00c37890
u8 __fastcall FUN_00c37890(Ufo* self, void* dummy, ParamObj* param, s32 which)
{
  (void)dummy;
  void* t;
  if (which == 1) t = self->p798;
  else if (which == 2) t = self->p79c;
  else if (which == 3) t = self->p7a0;
  else return 0;
  if (t == 0) return 0;
  if (FUN_0104fff0(t) == 0) return 0;
  if (param == 0) return 0;

  void* a = ((TFpk)((void**)param->vtbl)[0x5c / 4])(param, 0xb033b403u);
  void* b = ((TFpk)((void**)param->vtbl)[0x5c / 4])(param, 0x137e8e0u);
  if (a != 0 || (b != 0 && ((Cand*)b)->b1c == 2)) {
    void* o = ((TFp0)((void**)param->vtbl)[0x08 / 4])(param);
    float* p1 = ((TFfp0)((void**)self->loco.vtbl)[0x2c / 4])(&self->loco);
    float* p2 = ((TFfp0)((void**)o)[0x2c / 4])(o);
    float dx = p2[0] - p1[0];
    float dy = p2[1] - p1[1];
    float dz = p2[2] - p1[2];
    float d = sqrtf(dx * dx + dy * dy + dz * dz);
    if (FUN_0104be20(t) <= d && d <= FUN_0104be30(t)) return 1;
  }
  return 0;
}

// ======================================================================
// 0x00c379a0 - SP::cSPGameDataUFO::NotifyAttack
// ======================================================================
// @ 0x00c379a0
void __fastcall FUN_00c379a0(Ufo* self, void* dummy, ParamObj* param)
{
  (void)dummy;
  ((CCombatant0*)self)->NotifyAttack(param);
  if (param == 0) return;
  void* p = ((TFpk)((void**)param->vtbl)[0x5c / 4])(param, 0xb033b403u);
  if (p == 0) return;
  void* old = self->p208;
  if (p == old) return;
  ((TFv0)(*(void***)p)[0x00 / 4])(p);
  self->p208 = p;
  if (old != 0) ((TFv0)(*(void***)old)[0x04 / 4])(old);
}

// ======================================================================
// 0x00c37a00 - clear the cached cast id
// ======================================================================
// @ 0x00c37a00
void __fastcall FUN_00c37a00(Ufo* self, void* dummy)
{
  (void)dummy;
  ((CGameData*)self)->GetCastID();
  void* p = self->p208;
  if (p != 0) {
    self->p208 = 0;
    ((TFv0)(*(void***)p)[0x04 / 4])(p);
  }
}

// ======================================================================
// 0x00c37a30 - community interaction effect scale
// ======================================================================
// @ 0x00c37a30
void __fastcall FUN_00c37a30(Ufo* self, void* dummy, s32 effectId)
{
  (void)dummy;
  ((CCommunity*)self)->func54h(effectId);
  CInteractable* p = (CInteractable*)self->p7a4;
  if (p == 0) return;
  float m;
  if (self->u6e0 != 3) m = g_planetGlob->f1c;
  else m = g_planetGlob->f20;
  float r = ((TFf0)((void**)self->vtbl)[0x34 / 4])(self);
  p->SetEffectId(effectId, r * m);
}
