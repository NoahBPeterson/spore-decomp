// Slice s00bf6cb0 (gold4 #128) -- the Spore tribe/terrain-editor AI host class (the same class
// seen in slice s00bf5cb0: flags at +0x89/+0x8a/+0x94, a float accumulator/timer at +0x98,
// an entity list at +0x9c/+0xa0, an embedded SP::cSPTimer at +0x1e8, a tool-page
// sp_ref_vector at +0x470, per-tool garbage-timer vectors and a player-civ pointer).
//
//   00bf6cb0  score/time limit for an "interactable object type"
//   00bf6e80  bulk copy of 0x24-stride TreeItems (with an embedded vector<TreeItem>)
//   00bf6ee0  rebuild the +0x470 tool-page vector and re-create each tool from a tool id
//   00bf6fa0  sum a per-entity float + the read-phase of every cCommunity owned by this AI
//   00bf7050  "any own entity matches the phase?" predicate
//   00bf70b0  "is there another community on the same continent?" predicate
//   00bf7150  count own entities whose player id matches
//   00bf71d0  per-frame civic-radius accumulator tick
//   00bf7230  per-frame radius shrink / horizon clamp using the current terrain sphere kind
//   00bf7390  disband stale vehicles whose community no longer owns the continent
//   00bf74a0  decide whether to fire an "embassy/comm" event (timer + random + limits)
//   00bf7730  "is the elapsed time below the score limit for this object type?"
//   00bf7760  resize a 0x20-stride element vector (pad with default-constructed timers)
//   00bf77d0  deserialise that vector (read count, then append N serialised timers)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (SSE float code, no EH frames in the original)
#include "types.h"

#include <math.h>
#pragma intrinsic(sqrt)

typedef uint32_t u32;
typedef uint8_t  u8;
typedef int32_t  i32;

#define PI(p, off) (*(int*)((char*)(p) + (off)))
#define PU(p, off) (*(u32*)((char*)(p) + (off)))
#define PB(p, off) (*(u8*)((char*)(p) + (off)))
#define PF(p, off) (*(float*)((char*)(p) + (off)))
#define PP(p, off) ((void**)((char*)(p) + (off)))
#define PS(p, off) ((char*)(p) + (off))
#define VCALL0(p, off) ((void(__thiscall*)(void*))(*(void***)(p))[(off) / 4])(p)

// ---- external helpers (named FUN_<va> so difftest resolves relocations by hex) ------------
void* FUN_00b3d300();                 // 0x00b3d300  SP::NounManager
void* FUN_00b3d2c0(u32 a);                  // 0x00b3d2c0  SP::RelationshipManager
void* FUN_00b3d350(u32 a);                  // 0x00b3d350  SP::PlanetModel
void* FUN_00b3d4a0();                       // 0x00b3d4a0  CommManager
void* FUN_00b3d390(u32* a, void* b);        // 0x00b3d390  vector<AutoRefCount<cPropertyList>>::erase
int   FUN_00b1f9d0();                       // 0x00b1f9d0  GetPlayerEmpireOrMinus1
void* FUN_00b1e500();                       // 0x00b1e500
void* FUN_00acdff0();                       // 0x00acdff0
void* FUN_00ae5ea0();                       // 0x00ae5ea0
void* FUN_00d3d420();                       // 0x00d3d420
void* FUN_00cd7d10();                       // 0x00cd7d10
void* FUN_01021260();                       // 0x1021260   SP::cSPLivingUniverse::GetActivePlanet
u32   FUN_00b5b800();                       // 0x00b5b800  SP::GetCurrentGameMode
int   FUN_00c70e00(void* self);             // 0x00c70e00  living-universe state query
void  FUN_00befd80_unused(float r, int a); // (unused free form)
struct ThTimer {                            // SP::cGonzagoTimer (0x20 bytes)
  void* FUN_00b63890();                     // 0x00b63890  ctor
  void  FUN_00b638b0();                     // 0x00b638b0  dtor
  void  FUN_00b63930(void* other);          // 0x00b63930  assign/copy
};
void  FUN_0093a780(void* stream, int a, int b, int c);  // 0x0093a780  EA::IO::ReadInt32
int   FUN_00bd8b80(void* self);             // 0x00bd8b80  entity float getter
float FUN_00bfde50(void* self, u8 phase);   // 0x00bfde50  cCommunity::ReadPhase
int   FUN_00b88590(void* self, u32 a);      // 0x00b88590  cPlanetModel::GetContinent
int   FUN_00b7e3e0(void* self, u32 a);      // 0x00b7e3e0  cPlanetModel continent-owner test
void  FUN_00caa610(void* self, int a);      // 0x00caa610  cVehicle::DisbandUnit
void  FUN_00cfe7a0(int a, int b);           // 0x00cfe7a0
void* FUN_00ce6950(void* self, u32 a, u32 b, int c);  // 0x00ce6950  cStarRecordRef::GetCommContext
void  FUN_00aeb760(void* self, void* a, void* b, u32 c, u32 d, u32 e);  // 0x00aeb760 cCommManager::ShowCommEvent
int   FUN_00ae9390();                       // 0x00ae9390  CommScreen::IsActive
u8    FUN_00ae2e20(void* self, u32 a);      // 0x00ae2e20  relationship/empire test
int   FUN_00d00a70(void* self, u32 a);         // 0x00d00a70  relationship level
u32   FUN_00bc3190(void* self, u32* hi);    // 0x00bc3190  SP::cSPTimer::GetElapsedTime
void  FUN_00bc3130(void* self);             // 0x00bc3130  SP::cSPTimer::Restart
int   FUN_00bf4170(void* self, int n, void* val);   // 0x00bf4170
void* FUN_00bf51d0(void* self, void* a, void* b);   // 0x00bf51d0
void  FUN_00bf5220(void* self, void* a, int n, void* val);  // 0x00bf5220
void  FUN_00bf5420(void* self, void* val);  // 0x00bf5420
void  FUN_00bf40d0(void* self, int n);      // 0x00bf40d0

// thiscall helper structs (member names carry the VA so difftest maps them)
struct ThNounMgr {
  void  GetGameDataVector(void* out, void* a, void* b, void* c, void* d, u32 tag);  // 0xb21340
  void* GetPlayerCivilization();            // 0xb25fb0
  void* FUN_00f67d90();                     // 0xf67d90 GetCurrentTerrainSphere
};
struct ThSphere { int FUN_00c75420(); };    // 0xc75420 GetKind
struct ThObj { int FUN_00bf0f40(); };        // 0xbf0f40 terrain-editor mode
// per-instance element vector (stride 0x20) methods; receiver varies (this or a stream)
struct ThVec2 {
  void* FUN_00bf51d0(void* a, void* b);           // 0xbf51d0
  void  FUN_00bf5220(void* a, int n, void* val);  // 0xbf5220
  void  FUN_00bf5420(void* val);                  // 0xbf5420
  void  FUN_00bf40d0(int n);                      // 0xbf40d0
};
struct ThVehl { void* FUN_00ca71d0(); };    // 0xca71d0 pony/mode getter
struct ThVec { void* FUN_004e4410(void* src); };
void  FUN_00bf5c2170(void* self, void* a, void* b);  // 0x5c2170 sp_ref_vector::erase
struct ThToolMgr { void FUN_0104e340(void* slot); };   // 0x104e340 CreateToolFromToolID

// The AI host class (same layout as slice s00bf5cb0).
struct AI {
  char pad0[0x89];
  u8   mFlag89;                             // +0x89
  u8   mFlag8a;                             // +0x8a
  char pad8b[0x94 - 0x8b];
  u8   mFlag94;                             // +0x94
  char pad95[0x98 - 0x95];
  float mScore98;                           // +0x98
  void** mListBegin;                        // +0x9c
  void** mListEnd;                          // +0xa0
  char pada4[0xb0 - 0xa4];
  void** mVehBegin;                         // +0xb0
  void** mVehEnd;                           // +0xb4
  char padb8[0x1e8 - 0xb8];
  char mTimer1e8[0x470 - 0x1e8];            // +0x1e8 SP::cSPTimer (embedded)
  void** mToolBegin;                        // +0x470
  void** mToolEnd;                          // +0x474
  char pad478[0x4ac - 0x478];
  float mRadius4ac;                         // +0x4ac
  float mRadius4b0;                         // +0x4b0
  int   mTick4b4;                           // +0x4b4

  float FUN_00bf6cb0(int type);
  void  FUN_00bf6ee0();
  float FUN_00bf6fa0(u8 phase);
  u8    FUN_00bf7050();
  u8    FUN_00bf5720(u32 a);
  u8    FUN_00bf70b0(u32 a);
  int   FUN_00bf7150();
  void  FUN_00bf71d0();
  void  FUN_00bf7230();
  void  FUN_00bf7390();
  u32   FUN_00bf74a0();
  int   FUN_00bf7730(int type);
  void  FUN_00bf7760(u32 n);
  void  FUN_00bf77d0(void* stream);
  void  FUN_00befd80(float r);
};

// entity/vector element helper name aliases
struct Community {
  void* GetNoun();                          // 0x00bfdf80
  float ReadPhase(u8 phase);                // 0x00bfde50
};
void FUN_00aea5d0(void* a, void* b);        // 0x00aea5d0 eastl vector push_back<AutoRefCount>

// @ 0x00bf6cb0
float AI::FUN_00bf6cb0(int param_2) {
  switch (param_2) {
  case 0: case 6: case 0xb: return 4000.0f;
  case 1: case 4: case 7: return 16000.0f;
  case 2: case 5: case 8: break;
  default: return 2000.0f;
  }
  int iVar2;
  {
    void* nm = FUN_00b3d300();
    int iVar0;
    ((ThNounMgr*)nm)->GetGameDataVector(&iVar0, (void*)0xcd7d10, (void*)0xd3d420,
                                         (void*)0xacdff0, (void*)0xb1e500, 0x18c43e8);
    iVar2 = iVar0;
  }
  int local_4 = 1;
  int* piVar3 = &param_2;
  if (((PI(iVar2, 8) - PI(iVar2, 4)) >> 2) - ((PI(this, 0xa0) - PI(this, 0x9c)) >> 2) < 2) {
    piVar3 = &local_4;
  }
  return (float)*piVar3 * 12000.0f;
}

// @ 0x00bf6e80
void FUN_00bf6e80(u32* param_1, u32* param_2, u32* param_3) {
  if (param_1 != param_2) {
    u32* dst = param_1;
    do {
      dst[0] = param_3[0];
      dst[1] = param_3[1];
      dst[2] = param_3[2];
      dst[3] = param_3[3];
      dst[2] = param_3[2];
      dst[3] = param_3[3];
      ((ThVec*)((char*)dst + 0x10))->FUN_004e4410((char*)param_3 + 0x10);  // eastl::vector<TreeItem>::operator=
      dst = (u32*)((char*)dst + 0x24);
    } while (dst != param_2);
  }
}

// @ 0x00bf6ee0
void AI::FUN_00bf6ee0() {
  if (PB(this, 0x89) == 0) return;
  void** base = (void**)PS(this, 0x470);                 // sp_ref_vector@+0x470
  int n = (int)((char*)base[1] - (char*)base[0]) >> 2;
  if ((u32)n < 0xc) {
    int zero = 0;
    FUN_00bf4170(base, 0xc - n, &zero);                  // thiscall, 3 stack args
  } else {
    FUN_00bf5c2170(base, (char*)base[0] + 0x30, base[1]); // sp_ref_vector::erase
  }
  for (int off = 0; off < 0x30; off += 4) {
    void** slot = (void**)((char*)base[0] + off);
    void* old = *slot;
    if (old != 0) {
      *slot = 0;
      ((void(__thiscall*)(void*))(*(void***)old)[2])(old);   // slot 2 (+8)
    }
    u32 id = PU((void*)0x1469430, off);
    void* mgr = FUN_00b3d390(&id, slot);
    ((ThToolMgr*)mgr)->FUN_0104e340(slot);
    PB(*slot, 0x150) = 1;
  }
}

// @ 0x00bf6fa0
float AI::FUN_00bf6fa0(u8 param_2) {
  volatile float acc = 0.0f;
  for (void** p = mListBegin; p != mListEnd; ++p) {
    int r = ((int(__thiscall*)(void*))(*(void***)*p)[0x0])(*p);
    acc += (float)r;
  }
  int iv;
  {
    void* nm = FUN_00b3d300();
    ((ThNounMgr*)nm)->GetGameDataVector(&iv, (void*)0xcd7d10, (void*)0xd3d420,
                                         (void*)0xae5ea0, (void*)0xb1e500, 0x403df5c);
  }
  void** cur = *(void***)(iv + 4);
  void** end = *(void***)(iv + 8);
  while (cur != end) {
    void* comm = *cur;
    void* noun = ((Community*)comm)->GetNoun();
    if (noun == this) {
      acc += ((Community*)comm)->ReadPhase(param_2);
    }
    ++cur;
  }
  return acc;
}

// @ 0x00bf7050
u8 AI::FUN_00bf7050() {
  int n = (PI(this, 0xa0) - PI(this, 0x9c)) >> 2;
  for (int i = 0; i < n; ++i) {
    void* obj = *(void**)(PI(this, 0x9c) + i * 4);
    int local_c[3];
    int uVar2 = ((int(__thiscall*)(void*, void*))(*(void***)obj)[0x5c / 4])(obj, local_c);
    if (FUN_00bf5720(uVar2)) return 1;
  }
  return 0;
}

// @ 0x00bf70b0
u8 AI::FUN_00bf70b0(u32 param_2) {
  int iv;
  {
    void* nm = FUN_00b3d300();
    ((ThNounMgr*)nm)->GetGameDataVector(&iv, (void*)0xcd7d10, (void*)0xd3d420,
                                         (void*)0xae5ea0, (void*)0xb1e500, 0x403df5c);
  }
  void** cur = *(void***)(iv + 4);
  void** end = *(void***)(iv + 8);
  void* pm = FUN_00b3d350(param_2);
  int cont = FUN_00b88590(pm, param_2);
  while (cur != end) {
    void* c = *cur;
    void* noun = ((Community*)c)->GetNoun();
    if (noun != this) {
      u32 uVar5 = ((int(__thiscall*)(void*))(*(void***)PS(c, 0x34))[0x2c / 4])(PS(c, 0x34));
      void* pm2 = FUN_00b3d350(uVar5);
      if ((int)FUN_00b88590(pm2, uVar5) == cont) return 1;
    }
    ++cur;
  }
  return 0;
}

// @ 0x00bf7150
int AI::FUN_00bf7150() {
  int local_4 = 0;
  int iv;
  {
    void* nm = FUN_00b3d300();
    ((ThNounMgr*)nm)->GetGameDataVector(&iv, (void*)0xcd7d10, (void*)0xd3d420,
                                         (void*)0xae5ea0, (void*)0xb1e500, 0x403df5c);
  }
  void** cur = *(void***)(iv + 4);
  void** end = *(void***)(iv + 8);
  if (cur != end) {
    do {
      void* e = *cur;
      int a = ((int(__thiscall*)(void*))(*(void***)e)[0x4c / 4])(e);
      int b = ((int(__thiscall*)(void*))(*(void***)this)[0x4c / 4])(this);
      if (a == b) ++local_4;
      ++cur;
    } while (cur != end);
    return local_4;
  }
  return 0;
}

// @ 0x00bf71d0
void AI::FUN_00bf71d0() {
  u32 gm = FUN_00b5b800();
  if (gm == 0x1654c05) {
    void* planet = FUN_01021260();
    int iVar2 = FUN_00c70e00(planet);
    if (iVar2 == 5) return;
  }
  mTick4b4 += 1;
  if (mTick4b4 >= 6) {
    mTick4b4 -= 6;
    float f = FUN_00bf6fa0(1);
    FUN_00befd80(f * 0.1f);
  }
}

// @ 0x00bf7230
void AI::FUN_00bf7230() {
  float fVar6 = mScore98;
  if (fVar6 > 0.0f) {
    float fVar4 = 1.0f;
    if (PB(this, 0x94) == 0 && PB(this, 0x8a) == 0) {
      if (mRadius4ac <= 2000.0f) {
        int iVar3 = ((ThObj*)this)->FUN_00bf0f40();
        if (iVar3 == 1 || FUN_00bf7050() == 0) fVar4 = 0.8f;
        else fVar4 = 0.6f;
      } else {
        fVar4 = 0.0f;
      }
    }
    float fVar5 = fVar4 * fVar6 + mRadius4ac;
    float fv4 = (fVar6 - fVar4 * fVar6) + mRadius4b0;
    fVar6 = mScore98 - fVar6;
    mRadius4ac = fVar5;
    mRadius4b0 = fv4;
    mScore98 = fVar6;
    if (PB(this, 0x89) == 0 && fVar6 < 0.0f) {
      mScore98 = (fVar5 + fVar6) + fv4;
      mRadius4ac = 0.0f;
      mRadius4b0 = 0.0f;
    }
    mFlag94 = 0;
  }
  {
    void* nm = FUN_00b3d300();
    void* sp = ((ThNounMgr*)nm)->FUN_00f67d90();
    int kind = ((ThSphere*)sp)->FUN_00c75420();
    float lim;
    if (kind == 1) lim = 9000.0f;
    else if (kind == 2) lim = 27000.0f;
    else lim = 3000.0f;
    if (mRadius4ac > lim) mRadius4ac = lim;
    if (mRadius4b0 > lim) mRadius4b0 = lim;
  }
}

// @ 0x00bf7390
void AI::FUN_00bf7390() {
  void** p = mVehBegin;
  void** e = mVehEnd;
  if (p == e) return;
  do {
    void* veh = *p;
    if (veh != 0) {
      if (((u8(__thiscall*)(void*))(*(void***)veh)[0x2c / 4])(veh) == 0) {
        int a = ((int(__thiscall*)(void*))(*(void***)veh)[0x4c / 4])(veh);
        int b = ((int(__thiscall*)(void*))(*(void***)this)[0x4c / 4])(this);
        if (a == b && PI(veh, 0xb1c) == 0) {
          void* sp = ((ThVehl*)veh)->FUN_00ca71d0();
          if (PI(sp, 0x10) != 7) {
            void* sub = PS(veh, 0x34);
            u32 u = ((int(__thiscall*)(void*))(*(void***)sub)[0x2c / 4])(sub);
            void* pm = FUN_00b3d350(u);
            if (FUN_00b7e3e0(pm, u) == 0) {
              u32 u2 = ((int(__thiscall*)(void*))(*(void***)sub)[0x2c / 4])(sub);
              void* pm2 = FUN_00b3d350(u2);
              int cont = FUN_00b88590(pm2, u2);
              void* pm3 = FUN_00b3d350(0);
              if (PB((void*)((char*)0 + cont + PI(pm3, 0x64)), 0) != 0) {
                u32 u3 = ((int(__thiscall*)(void*))(*(void***)sub)[0x2c / 4])(sub);
                if (FUN_00bf5720(u3) == 0) {
                  u32 u4 = ((int(__thiscall*)(void*))(*(void***)sub)[0x2c / 4])(sub);
                  if (FUN_00bf70b0(u4) == 0) {
                    FUN_00caa610(veh, 1);
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
    ++p;
  } while (p != e);
}

// @ 0x00bf74a0
u32 AI::FUN_00bf74a0() {
  u32 n = (PU(this, 0xa0) - PU(this, 0x9c)) & 0xfffffffc;
  if ((int)n <= 4) return n;
  void* obj = *(void**)PS(this, 0x9c);
  if (obj == 0) return (u32)(uintptr_t)obj;
  if (PB(this, 0x8a) != 0) return (u32)(uintptr_t)obj;
  void* nm = FUN_00b3d300();
  void* civ = ((ThNounMgr*)nm)->GetPlayerCivilization();
  if (civ == 0) return 0;
  if (PB(civ, 0x8d) == 0) return (u32)(uintptr_t)civ;
  void* nm2 = FUN_00b3d300();
  int emp = FUN_00b1f9d0();
  u32 id = ((u32(__thiscall*)(void*, int))(*(void***)this)[0x4c / 4])(this, emp);
  void* rm = FUN_00b3d2c0(id);
  u8 r = (u8)FUN_00ae2e20(rm, id);
  if (r != 0) return (u32)r;
  {
    void* nm3 = FUN_00b3d300();
    int emp2 = FUN_00b1f9d0();
    u32 id2 = ((u32(__thiscall*)(void*, int))(*(void***)this)[0x4c / 4])(this, emp2);
    void* rm2 = FUN_00b3d2c0(id2);
    int k = FUN_00d00a70(rm2, id2);
    if (k == 4) return 4;
  }
  u32 fv1 = (u32)(i32)PF(civ, 0x98);              // cvttss2si ecx,[ebp+0x98]
  int cnt1 = (PI(civ, 0xa0) - PI(civ, 0x9c)) >> 2;
  int cnt2 = (PI(this, 0xa0) - PI(this, 0x9c)) >> 2;
  u32 r1 = ((u32(__thiscall*)(void*, int))(*(void***)0x1601760)[0])((void*)0x1601760, 5);
  u32 r2 = ((u32(__thiscall*)(void*, int))(*(void***)0x1601760)[0])((void*)0x1601760, 5);
  float fv2 = PF(civ, 0x98);
  int n1 = FUN_00bf7150();
  int half = n1 / 2;
  int n2 = FUN_00bf7150();
  int d10 = (int)fv2 / 10 - 200;
  int lim = (n2 + half + (int)r2 + (int)r1 + cnt2 + cnt1) * 200 + d10;
  int t18 = (int)fv1;
  if (lim < t18) t18 = lim;
  int round = t18 / 100 * 100;                      // MSVC emits imul 0x51eb851f; sar 5
  if (round < 100) return (u32)t18 * 0x51eb851f;    // low 32 bits, as the original returns eax
  {
    u32 hiw;
    u32 el = FUN_00bc3190(PS(this, 0x1e8), &hiw);
    if (hiw == 0 && el <= 0x11170) return el;
  }
  void* cm = FUN_00b3d4a0();
  if (FUN_00ae9390() != 0) { FUN_00bc3130(PS(this, 0x1e8)); return 0; }
  int span = 1;
  int mode = ((ThObj*)civ)->FUN_00bf0f40();
  if (mode == 0) span = 0x10;
  else if (mode == 1) span = 8;
  else if (mode == 2) span = 0xc;
  {
    void* nm4 = FUN_00b3d300();
    void* sp = ((ThNounMgr*)nm4)->FUN_00f67d90();
    int kind = ((ThSphere*)sp)->FUN_00c75420();
    if (kind == 0) { span = span * 2; span = span * 2; }
    else if (kind == 1) span = span * 3;
    else if (kind == 2) { span = span * 2; }
  }
  u32 roll = ((u32(__thiscall*)(void*, int))(*(void***)0x1601760)[0])((void*)0x1601760, span);
  if (roll == 0) {
    void* cm2 = FUN_00b3d4a0();
    int gm = *(int*)0x169d3c8;
    FUN_00cfe7a0(0, round);
    void* planet = FUN_01021260();
    void* ctx = FUN_00ce6950(*(void**)PS(planet, 0x13c), 0xdbf385bf, 0x6eeceef0, 0);
    FUN_00aeb760(cm2, ctx, ctx, 0xdbf385bf, 0x6eeceef0, 0);
  }
  FUN_00bc3130(PS(this, 0x1e8));
  return 0;
}

// @ 0x00bf7730
int AI::FUN_00bf7730(int param_2) {
  float fVar1 = FUN_00bf6cb0(param_2);
  if (fVar1 <= mScore98) return 1;
  return 0;
}

// @ 0x00bf7760
void AI::FUN_00bf7760(u32 param_2) {
  void** vec = (void**)this;
  void* begin = vec[0];
  void* end = vec[1];
  int count = (int)((char*)end - (char*)begin) >> 5;
  if ((u32)count < param_2) {
    struct Timer20 { u32 w[8]; } local_20;      // 0x20-byte cGonzagoTimer (no /GS cookie)
    ((ThTimer*)&local_20)->FUN_00b63890();
    ((ThVec2*)this)->FUN_00bf5220(end, param_2 - count, &local_20);
    ((ThTimer*)&local_20)->FUN_00b638b0();
    return;
  }
  ((ThVec2*)this)->FUN_00bf51d0((char*)begin + param_2 * 0x20, end);
}

// @ 0x00bf77d0
void AI::FUN_00bf77d0(void* param_2) {
  ((ThVec2*)this)->FUN_00bf51d0(*(void**)param_2, *((void**)param_2 + 1));
  u32 count = 0;
  void* p0 = (void*)((int(__thiscall*)(void*))(*(void***)param_2)[0x20 / 4])(param_2);
  void* out = (void*)((int(__thiscall*)(void*))(*(void***)p0)[0x18 / 4])(p0);
  FUN_0093a780(out, (int)&count, 1, 0);
  ((ThVec2*)this)->FUN_00bf40d0((int)count);
  u32 i = 0;
  if (count != 0) {
    do {
      struct Timer20 { u32 w[8]; } t;              // 0x20-byte cGonzagoTimer (no /GS cookie)
      ((ThTimer*)&t)->FUN_00b63890();
      ((ThTimer*)&t)->FUN_00b63930(param_2);
      void** base = (void**)PS(this, 0);
      void* dst = base[1];
      if (dst < base[2]) {
        base[1] = (char*)dst + 0x20;
        if (dst != 0) {
          u32* d = (u32*)dst;
          d[0] = 0x1465d54;
          d[1] = 0;
          d[2] = PU(&t, 0);
          d[3] = PU(&t, 4);
          d[4] = PU(&t, 8);
          d[5] = PU(&t, 0xc);
          PB(d, 0x18) = PB(&t, 0x18);
          d[7] = PU(&t, 0x1c);
          d[0] = 0x1464450;
        }
      } else {
        ((ThVec2*)this)->FUN_00bf5420(&t);
      }
      ((ThTimer*)&t)->FUN_00b638b0();
      ++i;
    } while (i < count);
  }
  ((void(__thiscall*)(void*))(*(void***)param_2)[0x1c / 4])(param_2);
}
