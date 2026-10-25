// Slice s00be5740 - cRaidBehavior (space-stage raid/city event behaviour family):
//   0x00be5740  FUN_00be5740  (1178 B)  behaviour update tick
//   0x00be5be0  FUN_00be5be0  ( 496 B)  per-mini-game-stage enter/exit handler
//   0x00be5dd0  FUN_00be5dd0  ( 713 B)  behaviour agent teardown + award pass
//   0x00be60a0  FUN_00be60a0  ( 220 B)  block-vector grow/extend helper
//
// This is the same object family as slice s00be4c00 (cRaidBeh); the offsets
// +0x2f0/+0x320/+0x340..+0x358/+0x3ec/+0x450/+0x4b4/+0x590/+0x670/+0x6e8
// line up exactly with that layout, so the same field model is reused here.
// Toolchain: cl 15.00.30729.01 (VS2008 SP1), /O2 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int    s32;
typedef unsigned long long u64;
typedef          long long s64;

#include <math.h>

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------------------
// Global objects / constants read with a direct absolute reference.
// ---------------------------------------------------------------------------
struct RandomLinearCongruential {
  u32 RandomUint32Uniform(u32 nLimit);          // 0x00a68fb0
};
extern RandomLinearCongruential gRandomGlobal;  // 0x01601760  sMathRandom

extern "C" const float gF_13ec5b4;   // 0x013ec5b4  the "update active" threshold
extern "C" const float gF_169c1b0;   // 0x0169c1b0  per-tick timer step
extern "C" const float gF_13ec4b8;   // 0x013ec4b8  normalisation epsilon (1e-8)
extern "C" const float gF_13f1160;   // 0x013f1160  camera pitch constant
extern "C" const float gF_156e15c;   // 0x0156e15c  camera distance scale
extern "C" const double gD_14688e0;  // 0x014688e0  0.35 (doubled const)

// 0x014688ac: table of sound-id pointers indexed by mini-game stage.
extern "C" u32* const gSoundByStage[12];   // 0x014688ac

// ---------------------------------------------------------------------------
// External helpers (declaration only, so the compiler emits a direct call).
// ---------------------------------------------------------------------------
struct cGameNounManager;

cGameNounManager* __cdecl NounManager();                       // 0x00b3d300
u32  __cdecl GetCurrentGameMode();                             // 0x00b5b800
u32  __cdecl FUN_00c75420();                                   // 0x00c75420
void __cdecl FUN_00c004c0_stub();                              // (declared per signature below)

struct cGameNounManager {
  void* CreateNoun(u32 type);                                  // 0x00b20c60
  void  RemoveNoun(void* n);                                   // 0x00b225d0
};

// Terrain / planet plumbing.
void* __cdecl FUN_00f67d90_ctx();                              // cTerrainEditor::GetCurrentTerrainSphere
void* __cdecl GetCameraCtl(void* a, void* b, u32 c);           // 0x00b3d280
void* __cdecl PlanetModel(void* a, void* b, void* c);          // 0x00b3d350
void* __cdecl AudioGetSystemAT();                              // 0x00a206f0
void  __cdecl Start3dSoundByName(void* id, void* ctx,
                                 float x, float y, float z);   // 0x00571f80
void  __cdecl FUN_00be53b0_dummy();

// ---------------------------------------------------------------------------
// cCombatant sub-object and cNoun base (as used by this family).
// ---------------------------------------------------------------------------
struct cSub34 {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
  virtual void v30(); virtual void v34();
  virtual void v38(void* arg);                // 0x38
};

struct cCombatant {
  u32 pad00[13];                              // 0x00 .. 0x33
  u32 GetDamageState();                       // 0x008e7f80, returns *(this+0x34)
};

struct cNoun {
  virtual void  v00();                        // 0x00
  virtual void  v04();                        // 0x04
  virtual void  v08();                        // 0x08
  virtual void* v0c(u32 tag);                 // 0x0c
  virtual void  v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void* v20();                        // 0x20
  virtual void  v24(); virtual void v28(); virtual void v2c(); virtual void v30();
  virtual void  v34(); virtual void v38(); virtual void v3c(); virtual void v40();
  virtual void  v44(); virtual void v48();
  virtual u32   v4c();                        // 0x4c
  virtual void  v50(); virtual void v54(void* p); virtual void v58();
  virtual void  v5c(u32 tag); virtual void v60(); virtual void v64(); virtual void v68();
  virtual void  v6c(); virtual void v70(); virtual void v74(); virtual void v78();
  virtual void  v7c(); virtual void v80(); virtual void v84(); virtual void v88();
  virtual void  v8c(); virtual void v90(); virtual void v94(); virtual void v98();
  virtual void  v9c(); virtual void va0(); virtual void va4(); virtual void va8();
  virtual void  vac(); virtual void vb0(); virtual void vb4(); virtual void vb8();
  virtual void  vbc(); virtual void vc0();    // 0xc0

  u32        pad04[12];                       // 0x04 .. 0x33
  cSub34     sub34;                           // 0x34
  u32        pad38[58];                       // 0x38 .. 0x11f
  cCombatant combat;                          // 0x120
};

// ---------------------------------------------------------------------------
// cActionCircle: agent ring.
// ---------------------------------------------------------------------------
struct cActionCircle {
  void RemoveAgent(void* agent);              // 0x00afae50
  u32  CountFreeSlots();                      // 0x00af9f60
  u8   pad00[0x50];
  void* slot;                                 // 0x50
  u8   pad54[0x10];
};

// ---------------------------------------------------------------------------
// Self object (cRaidBeh family).  Only the members this slice touches are named.
// ---------------------------------------------------------------------------
struct cCityTimer {
  u32 pad00[8];                               // 0x00 .. 0x1f
  u64 GetElapsedTime();                       // 0x00bc3190 -> eax:edx
};

struct cRaidBeh {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
  virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
  virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
  virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
  virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
  virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
  virtual void v80(); virtual void v84();
  virtual void* v88(); virtual void v8c(); virtual void v90(); virtual void v94();
  virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
  virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
  virtual void vb8(); virtual void vbc(); virtual void vc0();
  virtual void vc4(); virtual void vc8(); virtual void vcc();

  u32   pad04[10];                            // 0x04 .. 0x2b
  void* p2c;                                  // 0x2c
  u32   pad30[80];                            // 0x30 .. 0x16f
  void* p170;                                 // 0x170
  u32   pad174[95];                           // 0x174 .. 0x2ef
  u32   p2f0;                                 // 0x2f0
  u32   pad2f4[11];                           // 0x2f4 .. 0x31f
  cNoun* p320;                                // 0x320
  u32    pad324[7];                           // 0x324 .. 0x33f
  cNoun** p340;                               // 0x340
  cNoun** p344;                               // 0x344
  u32    pad348[3];                           // 0x348 .. 0x353
  void** slot354Begin;                        // 0x354
  void** slot354End;                          // 0x358
  u32    pad35c[36];                          // 0x35c .. 0x3eb
  cActionCircle circle3ec;                    // 0x3ec
  cActionCircle circle450;                    // 0x450
  cActionCircle circle4b4;                    // 0x4b4
  u8     b518;                                // 0x518
  u32    pad519[35];                          // 0x519 .. 0x5a3
  Vec3   v51c;                                // 0x51c
  u32    pad528[20];                          // 0x528 .. 0x577
  u32    p578;                                // 0x578
  u32    pad57c[5];                           // 0x57c .. 0x58f
  void*  p590;                                // 0x590
  u32    pad594[35];                          // 0x594 .. 0x61f
  u32    p620;                                // 0x620
  u32    pad624[19];                          // 0x624 .. 0x66f
  s32    mCountdown670;                       // 0x670
  u32    pad674[29];                          // 0x674 .. 0x6e7
  cCityTimer timer6e8;                        // 0x6e8
  u32    pad708[22];                          // 0x708 .. 0x75f
  u8     mFlag760;                            // 0x760
  u32    pad761[11];                          // 0x761 .. 0x78b
  u32    p78c;                                // 0x78c

  // intra-slice helpers (declared, bodies live in other slices)
  u8    FUN_00c004c0(u32 which);              // 0x00c004c0
  s32   FUN_00bd8b10();                       // 0x00bd8b10
  void  FUN_00be3850();                       // 0x00be3850
  void* FUN_00bdb590(u32 a, u32 b);           // 0x00bdb590
  u8    FUN_00be3500(void* noun, u8 flag);    // 0x00be3500
  u8    FUN_00bdb930(u32 a, u32 b);           // 0x00bdb930
  s32   FUN_00bd8b80();                       // 0x00bd8b80
  s32   FUN_00bd9bb0();                       // 0x00bd9bb0
  u8    FUN_00be2070(void* noun, u32 flag);   // 0x00be2070
  void  FUN_00be53b0(u32 a, u32 b);           // 0x00be53b0
  void  FUN_00bdc1a0(u32 a, u32 b);           // 0x00bdc1a0
  void  FUN_00be41b0();                       // 0x00be41b0
  void  FUN_00bdc350();                       // 0x00bdc350
  void  FUN_00be4400();                       // 0x00be4400
  void  FUN_00be2ee0(void* end, u32 n, void* out);  // 0x00be2ee0

  // Intra-slice methods (bodies below).
  void FUN_00be5740();                              // 0x00be5740
  void FUN_00be5be0(s32 stage, u32 arg);            // 0x00be5be0
  void FUN_00be5dd0();                              // 0x00be5dd0
};

// The 0x80-byte-record vector whose dequeue/grow helper is 0x00be60a0.
struct cGonzagoTimer {
  u32 pad00[8];
  void Ctor();                                      // 0x00b63890
  void Dtor();                                      // 0x00b638b0
};

// Record element of the 0x80-byte block vector: two embedded timers and two
// owned handles.
struct CBlock {
  u32           pad00[12];                          // 0x00 .. 0x2f
  cGonzagoTimer t30;                                // 0x30
  cGonzagoTimer t50;                                // 0x50
  void*         p70;                                // 0x70
  u32           pad74;                              // 0x74
  void*         p78;                                // 0x78
  u32           pad7c;                              // 0x7c

  void CopyConstructFrom(const CBlock* src);        // 0x00bdd380
};

// IO stream chain used by the block reader: the outer stream hands out an
// inner IO object whose vtable+0x18 slot returns the EA::IO stream.
struct cIOInner {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05();
  virtual void* v06();                              // 0x18
};

struct cIOStream {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06();
  virtual void v07();                               // 0x1c
  virtual cIOInner* v08();                          // 0x20
};

// Ref-counted handle interface: Release lives at vtable+0xc0.
struct cRefCounted {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
  virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
  virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
  virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
  virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
  virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
  virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
  virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
  virtual void Release();                           // 0x30 -> vtable + 0xc0
};

// Variable-list serializer (same layout as slice s006925c0's SP class).
namespace SP {
struct cDataSerializationInfo {
  s32  mId;                                         // 0x00
  s32  mDataSize;                                   // 0x04
  bool mbSerialized;                                // 0x08
  char mPad09[3];                                   // 0x09
  void* mpBinderContext;                            // 0x0c
  void* mpSerializer;                               // 0x10
};
struct cVarListSerializer {
  cDataSerializationInfo mDataSerializationInfos[128];  // 0x00 .. 0x9ff
  s32  mSerializableVarCount;                       // 0xa00
  s32  mSerializedVarCount;                         // 0xa04
  u32  mSignature;                                  // 0xa08
  void* mpObject;                                   // 0xa0c
  void* mpSerializerList;                           // 0xa10

  cVarListSerializer(const void* obj, void* list, u32 sig);  // 0x00692f90
  void Read(void* stream);                          // 0x00693e10
};
}

struct cBlockVecOwner {
  void** mBegin;                                    // 0x00
  void** mEnd;                                      // 0x04
  void** mCapacity;                                 // 0x08
  void FUN_00be60a0(u32 index);                     // 0x00be60a0
  void FUN_00be0cd0(u32 count);                     // 0x00be0cd0
  void FUN_00be30e0(CBlock* pos, const CBlock* src);        // 0x00be30e0
  void FUN_00bda710_vec(void* first, CBlock* end);  // 0x00bda710
};

// Simulator object stored at cRaidBeh+0x590.
struct cSPSimulatorSpaceGame {
  u32  pad00[0x22];                           // 0x00 .. 0x87
  u8   b88;                                   // 0x88
  u8   pad89[1];                              // 0x89
  u8   b8a;                                   // 0x8a  (the "double interval" flag)
  u32  pad8b[0x107];                          // 0x8b .. 0x4ab
  float fTimer4ac;                            // 0x4ac
};

// ---------------------------------------------------------------------------
// Free helpers used by these functions.
// ---------------------------------------------------------------------------
void* __cdecl FUN_00b3d300_terrain();          // SP::NounManager chain entry
void* __cdecl FUN_00b3d350_planet(void* a, void* b, void* c);   // 0x00b3d350
void  __cdecl FUN_00b7f250(void* planet, void* basis, void* dir);  // BuildSurfaceOrientation2
void  __cdecl FUN_00b12dd0(void* cam, void* m, u32 f);          // 0x00b12dd0
void  __cdecl FUN_00b10760(void* cam, float a, float b);        // cTerrainCameraController::FUN_00b10760
void* __cdecl FUN_00b3d280_camera(void* a, void* b, u32 c);     // GetCameraCtl (0x00b3d280)
void* __cdecl FUN_00bf2100_sim(void* sim, u32 id);              // SpaceTelemetry_Add (0x00bf2100)
void  __cdecl FUN_00bddda0(void* a, u32 b, void* c, u32 d, u32 e, u32 f);  // CCity (0x00bddda0)
u32   __cdecl FUN_00c9e6d0(u32 a, u32 b);                       // 0x00c9e6d0
void* __cdecl FUN_00bf9770(void* civ, u32 a);                   // cCivilization::GetModelTypeKey
void  __cdecl FUN_00bcde70(void* a);                            // 0x00bcde70
void  __cdecl FUN_00bcde40(void* a);                            // 0x00bcde40
void  __cdecl FUN_00bcdea0(void* a);                            // 0x00bcdea0
void  __cdecl FUN_00b63890_ctor(void* t);                       // cGonzagoTimer::ctor (unused alias)
void  __cdecl FUN_00b638b0_dtor(void* t);                       // cGonzagoTimer::dtor (unused alias)
u32   __cdecl FUN_00bdd600(u32 a, u32 b, u32 c);                // 0x00bdd600
void  __cdecl FUN_00bda710(void* a, u32 b);                     // 0x00bda710
void  __cdecl EA_IO_ReadInt32(void* s, void* buf, s32 n, s32 f);// 0x0093a780
void  __cdecl FUN_00be2440(cRaidBeh* self, u32 a, u32 b);       // 0x00be2440
void  __cdecl FUN_00be2ee0_free(void* end, u32 n, void* out);   // 0x00be2ee0 (free alias)
void  __cdecl FUN_01021260_stub();                              // high-LOD getter
void  __cdecl FUN_010212a0_stub();
void  __cdecl FUN_00ff2810(u32 a, u32 b);                       // 0x00ff2810
void  __cdecl FUN_00d5aae0(void* a, void* b, void* c);          // 0x00d5aae0

// ===========================================================================
// 0x00be5740 - behaviour update tick.
//   * Interval/limit selection from the current terrain sphere (separate
//     constant tables for the small-object and normal cases).
//   * Two independent "active?" probes at each phase boundary.
//   * A city-telemetry pickup path and an award/random-pick path driven by the
//     two global timers.
// ===========================================================================
// @ 0x00be5740
void cRaidBeh::FUN_00be5740()
{
  cSPSimulatorSpaceGame* sim = (cSPSimulatorSpaceGame*)p590;
  if (gF_13ec5b4 <= sim->fTimer4ac)
    return;

  s32 interval;
  switch (FUN_00c75420()) {
  case 0:  interval = 0x30d40; break;        // 200000
  case 1:  interval = 0x186a0; break;        // 100000
  default: interval = 0xc350;  break;        //  50000
  }
  if (sim->b8a != 0)
    interval = interval * 2;

  if (FUN_00c004c0(0) != 0 || FUN_00c004c0(1) != 0) {
    if (FUN_00c75420() >= 1) {
      u64 elapsed = timer6e8.GetElapsedTime();
      if ((u64)(s64)interval < elapsed) {
        if (FUN_00bd8b10() > (s32)(slot354End - slot354Begin)) {
          if ((s32)(slot354End - slot354Begin) < (s32)((sim->b8a == 0) + 1)) {
            float step = gF_169c1b0;
            if (sim->fTimer4ac >= step) {
              FUN_00be3850();
              sim->fTimer4ac = sim->fTimer4ac - (float)(s32)step;
            }
          }
        }
      }
    }
  }

  if (FUN_00c004c0(0) != 0)
    return;
  if (FUN_00c004c0(1) != 0)
    return;

  if (mFlag760 == 0) {
    if (FUN_00bf2100_sim(sim, *(u32*)&p2c) > 0) {
      u32 id = *(u32*)&p2c;
      if (FUN_00bdb930(id, 0)) {
        u32 key = FUN_00c9e6d0(id, 0);
        void* modelType = FUN_00bf9770((void*)key, 0);
        u32 mode = GetCurrentGameMode();
        FUN_00bddda0((void*)id, 0, ((void**)modelType)[0],
                     (u32)((u32*)modelType)[1], ((u32*)modelType)[2],
                     mode == 0x01654c05);
        mFlag760 = 1;
        return;
      }
    }
  }

  s32 stage;
  switch (FUN_00c75420()) {
  case 0:  stage = 5; break;
  case 1:  stage = 4; break;
  default: stage = 3; break;
  }

  if (gRandomGlobal.RandomUint32Uniform((u32)(stage * 8)) != 0 ||
      FUN_00bd8b80() != 0) {
    /* fall through to the block-trim section */
  } else {
    s32 bestIndex = -1;
    s32 bestValue = 0;
    for (s32 i = 0; i < 3; i++) {
      u32 key;
      if (i == 1)      key = 0x1a56aba;
      else if (i == 2) key = 0x18ea2cc;
      else             key = 0x18eb106;
      s32 val = 0;
      if ((s32)FUN_00bdb590(key, (u32)&val) != 0 && val > bestValue) {
        bestValue = val;
        bestIndex = i;
      }
    }
    if (bestIndex != 1 && bestIndex != 2 && bestIndex != 0 && bestIndex != -1) {
      /* unreachable */
    }
    if (bestIndex != -1) {
      if (bestIndex == 1)
        FUN_00bcdea0((void*)((cNoun*)this)->v4c());
      else if (bestIndex == 2)
        FUN_00bcde40((void*)((cNoun*)this)->v4c());
      else
        FUN_00bcde70((void*)((cNoun*)this)->v4c());

      if (0.0f <= sim->fTimer4ac) {
        u32 key2, tag2;
        if (bestIndex == 1)      { key2 = 0x1a56aba; tag2 = 0x1a55e4d; }
        else if (bestIndex == 2) { key2 = 0x18ea2cc; tag2 = 0xecade42; }
        else                     { key2 = 0x18eb106; tag2 = 0xff10521; }
        FUN_00be53b0(key2, tag2);
        sim->fTimer4ac = sim->fTimer4ac - (float)(s32)gF_169c1b0;
        return;
      }
    }
  }

  if (gRandomGlobal.RandomUint32Uniform((u32)(stage * 10)) != 0)
    return;
  u64 elapsed = timer6e8.GetElapsedTime();
  if ((u64)(s64)interval >= elapsed)
    return;

  s32 count = FUN_00bd8b10() * 4;
  s32 base = FUN_00c75420();
  if (base == 1) {
    count = count * 3 / 5;
  } else if (base == 0) {
    count = count * 2 / 5;
  }
  if ((s32)(slot354End - slot354Begin) >= count)
    return;

  if (sim->b8a == 0)
    count = (FUN_00bd9bb0() + 1) / 2;
  else
    count = 1;

  if ((s32)(slot354End - slot354Begin) >= count)
    return;
  if (sim->fTimer4ac >= gF_169c1b0) {
    FUN_00be3850();
    sim->fTimer4ac = sim->fTimer4ac - (float)(s32)gF_169c1b0;
  }
}

// ===========================================================================
// 0x00be5be0 - per-mini-game-stage enter/exit handler.
//   param2 selects the stage; 2/5/8 run a stage-specific pre-build hook and
//   then rebuild the camera framing, the other values just forward to the
//   generic noun handler.  A nonzero stage table slot then starts its 3D sound.
// ===========================================================================
// @ 0x00be5be0
void cRaidBeh::FUN_00be5be0(s32 stage, u32 arg)
{
  switch (stage) {
  case 0: case 1: case 3: case 4: case 6: case 7: case 9: case 10: case 11:
    FUN_00bdc1a0((u32)stage, arg);
    /* falls through */
  default:
    if (stage != 2 && stage != 5 && stage != 8)
      goto sound;
    break;
  case 2:
    FUN_00be41b0();
    break;
  case 5:
    FUN_00bdc350();
    break;
  case 8:
    FUN_00be4400();
    break;
  }

  {
    cNoun* builder = p320;
    cSub34* sub = (cSub34*)((u8*)builder + 0x34);
    void* (__thiscall* getter)(cSub34*) =
        *(void* (__thiscall**)(cSub34*))(((u8*)*(void**)sub) + 0x2c);
    float* p = (float*)getter(sub);

    Vec3 dir;
    dir.x = p[0] - v51c.x;
    dir.y = p[1] - v51c.y;
    dir.z = p[2] - v51c.z;

    float inv = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z +
                              gF_13ec4b8);
    Vec3 unit;
    unit.x = dir.x * inv;
    unit.y = dir.y * inv;
    unit.z = dir.z * inv;

    void* basis[4];
    void* planet = FUN_00b3d350_planet(&unit, &v51c, &dir);
    FUN_00b7f250(planet, basis, &unit);

    FUN_00b12dd0(FUN_00b3d280_camera(&v51c, basis, 1), basis, 1);

    float pitch = gF_156e15c * (float)gD_14688e0;
    FUN_00b10760(FUN_00b3d280_camera(0, 0, 0), pitch, gF_13f1160);
  }

sound:
  if (gSoundByStage[stage] != 0) {
    cNoun* builder = p320;
    cSub34* sub = (cSub34*)((u8*)builder + 0x34);
    void* (__thiscall* getter)(cSub34*) =
        *(void* (__thiscall**)(cSub34*))(((u8*)*(void**)sub) + 0x2c);
    float* p = (float*)getter(sub);

    u32 ctx = 0;
    void* at = AudioGetSystemAT();
    if (at != 0)
      ctx = (u32)((cNoun*)at)->v0c(0);
    Start3dSoundByName((void*)gSoundByStage[stage], (void*)ctx, p[0], p[1], p[2]);
  }
}

// ===========================================================================
// 0x00be5dd0 - behaviour agent teardown + award pass.
//   Walks the +0x354 agent vector (counting live ones), awards score for each,
//   prunes the +0x340 raid-participant vector, then repeatedly drops the
//   countdown at +0x670 while handing out an award and regenerating the
//   "best target" binding.
// ===========================================================================
// @ 0x00be5dd0
void cRaidBeh::FUN_00be5dd0()
{
  s32 live = 0;
  while (slot354Begin != slot354End) {
    cNoun* n = (cNoun*)*slot354Begin;
    if (n != 0) {
      if (n->combat.GetDamageState() != 2)
        live++;
      FUN_00be2070(n, 0);
      continue;
    }
    /* empty slot: drop it */
    break;
  }

  for (s32 i = 0; i < live; i++) {
    if (i < FUN_00bd8b10())
      FUN_00be3850();
  }

  s32 count = (s32)(p344 - p340);
  for (s32 i = 0; i < count; i++) {
    cNoun* n = p340[i];
    if (n == p320)
      continue;
    if (n->v0c(0x436f315) != 0)
      continue;
    circle3ec.RemoveAgent(p340[i]);
  }

  for (s32 i = 0; i < count; i++) {
    cNoun* n = p340[i];
    if (n == p320)
      continue;
    if (n->v0c(0x436f315) != 0)
      continue;
    u32 key = (u32)n->v20();
    void* x = FUN_00bdb590(key, 0);
    if (x != 0)
      ((cSub34*)((u8*)n + 0x34))->v38((u8*)x + 0xc);
    FUN_00be3500(n, 0);
  }

  u8 awarded = 0;
  while (mCountdown670 > 0) {
    s32 bestIndex = -1;
    s32 bestValue = 0;
    for (s32 i = 0; i < 3; i++) {
      u32 key;
      if (i == 1)      key = 0x1a56aba;
      else if (i == 2) key = 0x18ea2cc;
      else             key = 0x18eb106;
      s32 val = 0;
      if ((s32)FUN_00bdb590(key, (u32)&val) != 0 && val > bestValue) {
        bestValue = val;
        bestIndex = i;
      }
    }
    if (bestIndex != -1) {
      u32 key2, tag2;
      if (bestIndex == 1)      { key2 = 0x1a56aba; tag2 = 0x1a55e4d; }
      else if (bestIndex == 2) { key2 = 0x18ea2cc; tag2 = 0xecade42; }
      else                     { key2 = 0x18eb106; tag2 = 0xff10521; }
      FUN_00be53b0(key2, tag2);
      awarded = 1;
    }
    mCountdown670--;
  }

  FUN_00be2440(this, 0, 0);

  if (awarded && GetCurrentGameMode() == 0x01654c05 && p2f0 != 0) {
    FUN_010212a0_stub();
    FUN_00ff2810(p2f0, 0);
  }
}

// ===========================================================================
// 0x00be60a0 - block-vector grow/extend helper.
//   `this` is a vector of 0x80-byte CBlock records (begin/end at +0/+4).  If
//   the requested index is in range, copy-grow via the high-water helpers;
//   otherwise default-construct records through FUN_00be2ee0 and release the
//   two handle slots those records own.
// ===========================================================================
// @ 0x00be60a0
void cBlockVecOwner::FUN_00be60a0(u32 index)
{
  void** begin = mBegin;
  void** end   = mEnd;

  if ((u32)(((u8*)end - (u8*)begin) >> 7) < index) {
    CBlock tmp;
    tmp.t30.Ctor();
    tmp.t50.Ctor();
    tmp.p70 = 0;
    tmp.p78 = 0;
    FUN_00be2ee0_free(end, index - (u32)(((u8*)end - (u8*)begin) >> 7), &tmp);
    if (tmp.p78 != 0)
      (*(void (**)(void*))((*(u8**)tmp.p78) + 0xc0))(tmp.p78);
    if (tmp.p70 != 0)
      (*(void (**)(void*))((*(u8**)tmp.p70) + 0xc0))(tmp.p70);
    tmp.t50.Dtor();
    tmp.t30.Dtor();
    return;
  }

  u32 dst = (u32)begin + index * 0x80;
  u32 first = FUN_00bdd600((u32)end, (u32)end, dst);
  FUN_00bda710((void*)first, (u32)end);
  mEnd = (void**)((u32)end + ((s32)((u32)end - dst) >> 7) * -0x80);
}

// ===========================================================================
// 0x00be6180 - block-vector load.
//   Clears the 0x80-byte-record vector, reads a record count from the stream,
//   sizes the vector, then for each record default-constructs a CBlock (two
//   embedded timers + two owned handles), reads it through a
//   cVarListSerializer and appends it, releasing the temporary's handles and
//   destroying its timers afterwards.  The stream is closed at the end.
// ===========================================================================
// @ 0x00be6180
void __cdecl FUN_00be6180(cIOStream* stream, cBlockVecOwner* vec)
{
  CBlock* begin = (CBlock*)vec->mBegin;
  CBlock* end   = (CBlock*)vec->mEnd;

  u32 first = FUN_00bdd600((u32)end, (u32)end, (u32)begin);
  vec->FUN_00bda710_vec((void*)first, (CBlock*)vec->mEnd);
  vec->mEnd = (void**)((u32)vec->mEnd + ((s32)((u32)end - (u32)begin) >> 7) * -0x80);

  u32 count = 0;
  void* io = stream->v08()->v06();
  EA_IO_ReadInt32(io, &count, 1, 0);
  vec->FUN_00be0cd0(count);

  for (u32 i = 0; i < count; i++) {
    CBlock tmp;
    tmp.t30.Ctor();
    tmp.t50.Ctor();
    tmp.p70 = 0;
    tmp.p78 = 0;

    SP::cVarListSerializer ser(&tmp, (void*)0x156e448, 0x1a80d26);
    ser.Read(stream);

    CBlock* e = (CBlock*)vec->mEnd;
    if (e < (CBlock*)vec->mCapacity) {
      vec->mEnd = (void**)(e + 1);
      if (e != 0)
        e->CopyConstructFrom(&tmp);
    } else {
      vec->FUN_00be30e0(e, &tmp);
    }

    if (tmp.p78 != 0)
      ((cRefCounted*)tmp.p78)->Release();
    if (tmp.p70 != 0)
      ((cRefCounted*)tmp.p70)->Release();
    tmp.t50.Dtor();
    tmp.t30.Dtor();
  }

  stream->v07();
}
