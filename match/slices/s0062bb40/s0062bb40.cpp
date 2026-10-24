// SP::cSPPlayMode methods. Region 0x62bb40-0x62ca73.
// Retail layout differs from the 2008 PDB; offsets taken from the disassembly.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef void  (__thiscall *TF0)(void*);
typedef void  (__thiscall *TF1)(void*, int);
typedef void  (__thiscall *TF4)(void*, int, int, int, int);
typedef void  (__thiscall *TF5)(void*, int, int, int, int, int);

struct Vec  { void erase(void* first, void* last); };
struct VecB { void DoInsertValue(void* dst, void* src, int n); };
struct SharedLibList { unsigned char FUN_0062f6c0(); };
struct EventInfo { void ctor(unsigned char b); };
struct Dance { bool IsDancingAnim(int a, int b); };
struct Creature { void FUN_00a04a90(int a); };
struct CreatureMgr {
  void* GetCreature(int idx);
  void* GetCreatureStructure(int idx);
  int   RunSkinPaintOnEditorModel(int a, int b);
  void  DestroyAnimatedCreature(int a, int b);
};
struct PMUI { void SetUIGroupVisible(unsigned int key, int b); };

typedef void  (__thiscall *TF2u)(void*, void*, unsigned);
typedef void  (__thiscall *TF3u)(void*, void*, unsigned, unsigned);
typedef void* (__thiscall *TF0p)(void*);
typedef void* (__thiscall *TF2p)(void*, int, int);
typedef float (__thiscall *TFF5)(void*, unsigned, int, int, int, int);

// ---- Retail cSPPlayMode layout (offsets read from the disassembly; differs from the 2008 PDB) ----
struct PMParams98 {                 // 0x098: play-mode parameter block
  void*    mpObject;                // 0x098
  uint32_t pad04[9];                // 0x09c..0x0bf
};

struct EAStopwatch {                // 0x36f0: EA::Stopwatch
  uint32_t mTicks0;                 // 0x36f0
  uint32_t mTicks4;                 // 0x36f4
  uint32_t mZero8;                  // 0x36f8
  uint32_t mZeroC;                  // 0x36fc
  uint32_t mMode10;                 // 0x3700
  float    mScale14;                // 0x3704
  long long FUN_0093a3a0();         // GetElapsedTimeFloat
  void      FUN_0093a2e0();         // SetBoolProperty
};

struct PMSlot3614 {                 // object at cSPPlayMode::m3614
  uint8_t  pad000[0xac];            // 0x000..0x0ab
  void*    mAc;                     // 0x0ac  refcounted (flags at +4)
  uint8_t  pad0b0[0x2a8];           // 0x0b0..0x357
  void*    m358;                    // 0x358  object with vt[7]
  uint32_t pad35c;                  // 0x35c
  void*    mCreatureManager;        // 0x360
  uint32_t mCreatureID;             // 0x364
  void      FUN_005798f0();                       // SwitchToEditorCamera
  void      FUN_00582d70(int, int, unsigned);     // DestroyAnimatedCreature
  void*     FUN_00572400();                       // GetCurrentCamera
};

struct PMAnimData {                 // *(*cAnimatingCreature + 0x180)
  uint8_t  pad000[6];               // 0x000..0x005
  uint8_t  mFlags6;                 // 0x006
  uint8_t  pad007;                  // 0x007
  uint8_t  pad008[0x68];            // 0x008..0x06f
  float    m70;                     // 0x070
  float    m74;                     // 0x074
  float    m78;                     // 0x078
  float    m7c;                     // 0x07c
  float    m80;                     // 0x080
  float    m84;                     // 0x084
};

struct PMCreatureAnim {             // cAnimatingCreature (manager GetCreature result)
  uint8_t  pad000[0x3c];            // 0x000..0x03b
  float    m3c;                     // 0x03c
  uint8_t  pad040[0x140];           // 0x040..0x17f
  PMAnimData* m180;                 // 0x180
};

struct PMCreatureData {             // manager GetCreatureStructure result
  uint8_t  pad000[0x4c];            // 0x000..0x04b
  float    m4c;                     // 0x04c
  float    m50;                     // 0x050
};

struct PMCreature {                 // cSPPlayMode_Creature (0x50-byte allocation)
  void*    mVtbl;                   // 0x00
  int32_t  mRefCount;               // 0x04
  void*    mCreature;               // 0x08
  void*    mSlot3614;               // 0x0c
  PMCreatureData* mData;            // 0x10
  void*    mOwner;                  // 0x14
  void*    mPath;                   // 0x18
  uint32_t mId;                     // 0x1c
  float    mDistance;               // 0x20
  uint8_t  m24;                     // 0x24
  uint8_t  pad025[3];               // 0x25..0x27
  float    m28;                     // 0x28
  float    m2c;                     // 0x2c
  float    m30;                     // 0x30
  float    m34;                     // 0x34
  void*    m38;                     // 0x38
  uint8_t  pad03c[0x14];            // 0x3c..0x4f
};

struct PMPath {                     // cSPCasual_Path (object at cSPPlayMode::mPath)
  void FUN_0062d8a0(float, float);
};

struct PMBGMgr {                    // cSPPlayModeBGMgr (object at cSPPlayMode::m3618)
  void FUN_0062fc90(void*, int, int, void*);
  void FUN_0062f920();
  void FUN_0062f2f0();
};

struct TC_Anim {                    // cSPPlayModeAnimation (subobject at 0x3588)
  uint8_t FUN_0062e5f0();           // IsExtraAnims
  void    FUN_0062e6c0();           // Activate
  void    FUN_0062e7a0();           // ResetCurAnimWindow
  void    FUN_0062e600();           // UpdatePageCount
};

struct TC_UI {                      // cSPPlayModeUI (object at cSPPlayMode::mUI)
  void    FUN_00635760(unsigned, int);   // SetUIGroupVisible
  uint8_t FUN_006358c0(void*, void*);    // Init
  void    FUN_00634ef0(unsigned, int);   // SetEnabled
  void    FUN_00634f50(unsigned, int);   // SetHideOut
  void    FUN_00634ec0(unsigned, int);   // SetSelected
  void    FUN_00635390(int);             // ToggleNameAndDescribe
  void    FUN_006357c0(unsigned, int);   // ToggleUIGroup
  void    FUN_00635e80();                // SetTabIndentOn
  void    FUN_00635dc0(unsigned);        // SetTabIndentOff
  void    FUN_00635f00(int);             // SetAnimButtonsEnabled
  void    FUN_00635ff0(int);             // SetExpansionAnimButtonsEnabled
  void    FUN_00634c80(int);             // UpdateButtonEffects
  void    FUN_006353e0(unsigned);        // SetTagField
  uint8_t FUN_006373e0();                // Shutdown
};

struct PMCamera {                   // cCreatureCameraBase (FUN_00572400 result)
  uint8_t  pad000[0x8c];            // 0x000..0x08b
  int32_t  mState8c;                // 0x08c
  void FUN_00626db0(float* out);    // GetCurrentCameraPosition
};

struct PMRefObj {                   // refcount wrapper (cSPPlayMode::m3660)
  void*    mObject;                 // 0x00
  int32_t  mRefCount;               // 0x04
  uint8_t  pad008[0x38];            // 0x08..0x3f
  int32_t  mCount40;                // 0x40
};

struct PMAc {                       // object at PMSlot3614::mAc
  void*    mVtbl;                   // 0x00
  unsigned mFlags4;                 // 0x04
};

struct TC_59ca70 { void* FUN_0059ca70(unsigned id); };
struct TC_59cac0 { void* FUN_0059cac0(unsigned id); };
struct TC_4558a0 { void FUN_004558a0(uint32_t* pos, const uint32_t* val); };
struct TC_5c8480 { void FUN_005c8480(void* pos, void** val); };
struct TC_62cd30 { void* FUN_0062cd30(); };
struct TC_62de70 { void* FUN_0062de70(); };
struct TC_62cef0 { void FUN_0062cef0(int a); };
struct TC_62a550 { void FUN_0062a550(); };
struct TC_62a860 { void FUN_0062a860(); };
struct TC_62b000 { void FUN_0062b000(); };
struct TC_629de0 { void FUN_00629de0(); };
struct TC_6291d0 { unsigned FUN_006291d0(int a); };
struct TC_6286a0 { unsigned FUN_006286a0(); };

extern "C" void* FUN_0067dcc0();                                       // EA::MessageServer()
extern "C" void* FUN_0067de40();
extern "C" void* FUN_00f473a0(unsigned, const char*, int, int, int, int);
extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n); // memcpy
extern "C" void** FUN_0062ffd0(void** first, void** last, void** result);
extern "C" int   __stdcall FUN_013cc2b8(void* p);                      // QueryPerformanceCounter
extern "C" float sqrtf(float);
extern const char g_013fe150[];   // 0x13fe150 "Casual/PLAYMODE"
extern const char g_013f586c[];   // 0x13f586c "Casual"
extern float gHalf1471064;        // 0x1471064 0.5f
extern float gMax3_75_13fe0c4;    // 0x13fe0c4 3.75f
extern float gTol0_05_13ec478;    // 0x13ec478 0.05f
extern float gTwo1470f1c;         // 0x1470f1c 2.0f
extern float gOne1485720;         // 0x1485720 1.0f
extern float gConst13ebc68;       // 0x13ebc68
extern float gCamX15f6d6c;        // 0x15f6d6c camera init x
extern float gCamY15f6d70;        // 0x15f6d70 camera init y
extern float gCamZ15f6d74;        // 0x15f6d74 camera init z

struct PM_L {                       // retail cSPPlayMode data layout
  uint32_t mVtbl0;                  // 0x000
  uint32_t pad004;                  // 0x004
  void*    mIHandler8;              // 0x008  IHandler subobject (MessageServer subscriber)
  void*    mUI;                     // 0x00c  cSPPlayModeUI*
  void*    m10;                     // 0x010  refcounted object released by init
  float    m14;                     // 0x014
  uint32_t pad018;                  // 0x018
  uint8_t  m1c;                     // 0x01c
  uint8_t  m1d;                     // 0x01d
  uint8_t  m1e;                     // 0x01e
  uint8_t  m1f;                     // 0x01f
  uint8_t  m20;                     // 0x020
  uint8_t  pad021[3];               // 0x021..0x023
  int32_t  m24;                     // 0x024
  float    m28;                     // 0x028
  float    m2c;                     // 0x02c
  float    m30;                     // 0x030
  float    m34;                     // 0x034
  float    m38;                     // 0x038
  uint32_t pad03c;                  // 0x03c
  float    m40[3];                  // 0x040..0x04b
  uint8_t  m4c;                     // 0x04c
  uint8_t  pad04d;                  // 0x04d
  uint8_t  m4e[3];                  // 0x04e..0x050
  uint8_t  m51;                     // 0x051
  uint16_t pad052;                  // 0x052..0x053
  float    m54;                     // 0x054  last camera position
  float    m58;                     // 0x058
  float    m5c;                     // 0x05c
  int32_t  m60;                     // 0x060  last camera state
  uint32_t* mVec64Begin;            // 0x064  pending creature-id vector
  uint32_t* mVec64End;              // 0x068
  uint32_t* mVec64Cap;              // 0x06c
  uint32_t pad070[2];               // 0x070..0x077
  void*    mPath;                   // 0x078  cSPCasual_Path* (refcounted)
  void**   mVec7cBegin;             // 0x07c  cSPPlayMode_Creature* vector
  void**   mVec7cEnd;               // 0x080
  void**   mVec7cCap;               // 0x084
  uint32_t pad088[4];               // 0x088..0x097
  PMParams98 mParams;               // 0x098
  int32_t  mc0;                     // 0x0c0
  uint8_t  mc4;                     // 0x0c4
  uint8_t  pad0c5[3];               // 0x0c5..0x0c7
  void*    mSubModes[4];            // 0x0c8..0x0d7 (index 1 = photo submode)
  uint8_t  mSubModeAction[0x110];   // 0x0d8
  uint8_t  mSubModePhoto[0xfc8];    // 0x1e8
  uint8_t  mSubModeDance[0x78];     // 0x11b0
  uint8_t  mSubModeMovie[0x2360];   // 0x1228
  uint8_t  mAnim3588[0x8c];         // 0x3588 cSPPlayModeAnimation
  void*    m3614;                   // 0x3614
  uint8_t  mBGMgr3618[0x48];        // 0x3618 cSPPlayModeBGMgr
  void*    m3660;                   // 0x3660 refcount wrapper
  uint32_t pad3664;                 // 0x3664
  float    m3668;                   // 0x3668
  uint32_t pad366c[0x16];           // 0x366c..0x36c3
  int32_t  m36c4;                   // 0x36c4
  uint32_t pad36c8;                 // 0x36c8
  int32_t  m36cc;                   // 0x36cc
  uint8_t  m36d0;                   // 0x36d0 baby counter
  uint8_t  pad36d1[3];              // 0x36d1..0x36d3
  int32_t  m36d4;                   // 0x36d4
  int32_t  m36d8[3];                // 0x36d8..0x36e3 baby ids
  uint32_t pad36e4[3];              // 0x36e4..0x36ef
  EAStopwatch mStopwatch;           // 0x36f0
  uint8_t  m3708;                   // 0x3708
  uint8_t  m3709;                   // 0x3709
  uint8_t  m370a;                   // 0x370a
};

struct PM {
  void FUN_0062bb40(int a, int b);   // @ 0x0062bb40
  void FUN_0062bec0();               // @ 0x0062bec0
  void FUN_0062bdb0();               // @ 0x0062bdb0
  void FUN_0062bf10(int a);          // @ 0x0062bf10
  void Stop();                       // @ 0x0062c340
  void Update(int a);                // @ 0x0062c550
  bool FUN_0062c7e0(int idx, int a); // @ 0x0062c7e0
  void FUN_0062c910();               // @ 0x0062c910
  void FUN_0062c990(int id);         // @ 0x0062c990
  int  GetLatestBabyID();
  void SetMomToFaceBaby(int id);
  void SetBabyIdleAnim(int id);
  bool IsEventForBaby(int id);
};

extern void* gPMGlobal;              // 0x15f7cf4
extern float gConst13fe160;          // 0x13fe160

// @ 0x0062bb40
__declspec(noinline) void PM::FUN_0062bb40(int id, int flag) {
  PM_L* s = (PM_L*)this;
  unsigned n = (unsigned)((char*)s->mVec7cEnd - (char*)s->mVec7cBegin) >> 2;
  for (unsigned i = 0; i < n; ++i) {
    PMCreature* e = (PMCreature*)s->mVec7cBegin[i];
    if (e->mId == (unsigned)id) return;
  }
  PMSlot3614* slot = (PMSlot3614*)s->m3614;
  void* mgr = slot->mCreatureManager;
  PMCreatureAnim* cr = (PMCreatureAnim*)((TC_59ca70*)mgr)->FUN_0059ca70((unsigned)id);
  PMAnimData* anim = cr->m180;
  if ((anim->mFlags6 & 1) == 0) {
    unsigned m = (unsigned)((char*)s->mVec64End - (char*)s->mVec64Begin) >> 2;
    for (unsigned k = 0; k < m; ++k) {
      if (s->mVec64Begin[k] == (unsigned)id) return;
    }
    uint32_t* e = s->mVec64End;
    if (e < s->mVec64Cap) {
      s->mVec64End = e + 1;
      if (e != 0) *e = (unsigned)id;
      return;
    }
    ((TC_4558a0*)&s->mVec64Begin)->FUN_004558a0(e, (const uint32_t*)&id);
    return;
  }
  float dist = anim->m7c - anim->m70;
  if (dist < anim->m80 - anim->m74) dist = anim->m80 - anim->m74;
  if ((char)flag != 0) dist = cr->m3c * dist;
  dist = dist * gHalf1471064;
  if (dist > gMax3_75_13fe0c4) dist = gMax3_75_13fe0c4;
  PMCreature* np;
  void* mem = FUN_00f473a0(0x50, g_013fe150, 0, 0, 0, 0);
  if (mem == 0) np = 0;
  else np = (PMCreature*)((TC_62cd30*)mem)->FUN_0062cd30();
  PMCreature* temp = np;
  if (np != 0) ((TF0)(*(void**)((char*)np->mVtbl + 4)))(np);
  np->mId = (unsigned)id;
  np->mDistance = dist;
  np->mCreature = cr;
  np->mSlot3614 = s->m3614;
  np->mData = (PMCreatureData*)((TC_59cac0*)mgr)->FUN_0059cac0((unsigned)id);
  void* oldPath = np->mPath;
  void* newPath = s->mPath;
  if (newPath != oldPath) {
    if (newPath != 0) ((TF0)(*(void**)((char*)newPath + 4)))(newPath);
    np->mPath = newPath;
    if (oldPath != 0) ((TF0)(*(void**)((char*)oldPath + 8)))(oldPath);
  }
  np->mOwner = s;
  np->m2c = np->mData->m4c;
  np->m30 = np->mData->m50;
  void** pos = ((char)flag != 0) ? s->mVec7cEnd : s->mVec7cBegin;
  if (pos == s->mVec7cEnd && s->mVec7cEnd != s->mVec7cCap) {
    s->mVec7cEnd = pos + 1;
    if (pos != 0) {
      *pos = np;
      ((TF0)(*(void**)((char*)np->mVtbl + 4)))(np);
    }
  } else {
    ((TC_5c8480*)&s->mVec7cBegin)->FUN_005c8480(pos, (void**)&temp);
  }
  if (temp != 0) ((TF0)(*(void**)((char*)temp->mVtbl + 8)))(temp);
}

// @ 0x0062bec0
void PM::FUN_0062bec0() {
  char* s = (char*)this;
  unsigned n = (*(unsigned*)(s + 0x80) - *(unsigned*)(s + 0x7c)) >> 2;
  Vec* vec = (Vec*)(s + 0x7c);
  unsigned i = 0;
  while (i < n) {
    int* arr = *(int**)vec;
    int o = arr[i];
    if (o != 0) {
      arr[i] = 0;
      ((TF0)(*(void**)(*(char**)o + 8)))((void*)o);
    }
    ++i;
  }
  vec->erase(*(void**)vec, *(void**)((char*)vec + 4));
}

// @ 0x0062bdb0
void PM::FUN_0062bdb0() {
  char* s = (char*)this;
  unsigned n = (*(unsigned*)(s + 0x68) - *(unsigned*)(s + 0x64)) >> 2;
  if (n == 0) return;
  int ids[8];
  for (int k = 0; k < 8; ++k) ids[k] = -1;
  unsigned cnt = 0;
  void* mgr = *(void**)((char*)*(void**)(s + 0x3614) + 0x360);
  for (unsigned i = 0; i < n; ++i) {
    int id = *(int*)(*(unsigned*)(s + 0x64) + i * 4);
    char* cr = (char*)((CreatureMgr*)mgr)->GetCreature(id);
    if (cr != 0 && (*(unsigned char*)(*(char**)(cr + 0x180) + 6) & 1)) {
      FUN_0062bb40(id, id != *(int*)((char*)*(void**)(s + 0x3614) + 0x364));
      ids[cnt++] = id;
    }
  }
  for (unsigned j = 0; j < cnt; ++j) {
    int* d = *(int**)(s + 0x64);
    int* e = *(int**)(s + 0x68);
    while (d != e) {
      if (ids[j] == *d) {
        if (d + 1 < e) {
          ((VecB*)(s + 0x64))->DoInsertValue(d, d + 1, (int)e - (int)(d + 1));
        }
        *(unsigned*)(s + 0x68) -= 4;
        break;
      }
      ++d;
    }
  }
}

// @ 0x0062bf10
__declspec(noinline) void PM::FUN_0062bf10(int param) {
  PM_L* s = (PM_L*)this;
  void* msgsrv = FUN_0067dcc0();
  if (msgsrv != 0) {
    void** mvt = *(void***)msgsrv;
    void* handler = (void*)&s->mIHandler8;
    ((TF2u)mvt[0x24 / 4])(msgsrv, handler, 0x692ea61u);
    ((TF2u)mvt[0x24 / 4])(msgsrv, handler, 0x3eaed50u);
    ((TF2u)mvt[0x24 / 4])(msgsrv, handler, 0x4114116u);
    ((TF2u)mvt[0x24 / 4])(msgsrv, handler, 0x58b8059u);
    ((TF2u)mvt[0x24 / 4])(msgsrv, handler, 0x5b053b5u);
  }
  void* b = FUN_0067de40();
  void** bvt = *(void***)b;
  void* c = ((TF0p)bvt[0x20 / 4])(b);
  void** cvt = *(void***)c;
  ((TF1)cvt[0x1c / 4])(c, (int)gPMGlobal);

  ((TC_UI*)s->mUI)->FUN_006358c0(s->m3614, s);
  ((TC_UI*)s->mUI)->FUN_00635760(0x3fbfa5cu, 1);
  ((TC_UI*)s->mUI)->FUN_00635760(0x4446a98u, 1);
  ((TC_UI*)s->mUI)->FUN_00635760(0x4446ae0u, 1);
  if (((TC_Anim*)&s->mAnim3588)->FUN_0062e5f0() != 0) {
    ((TC_UI*)s->mUI)->FUN_00635760(0x4864e88u, 1);
  }

  s->m36c4 = param;
  s->m3668 = gOne1485720;
  ((TC_62a860*)s)->FUN_0062a860();

  {
    void** avt = *(void***)s->mParams.mpObject;
    unsigned r = (unsigned)((TF2p)avt[0x144 / 4])(s->mParams.mpObject, 0, s->m370a);
    ((PMBGMgr*)&s->mBGMgr3618)->FUN_0062fc90(s->mUI, s->m36c4, s->m36cc, (void*)r);
  }

  s->mSubModes[3] = (void*)&s->mSubModeMovie;
  s->mSubModes[0] = (void*)&s->mSubModeAction;
  s->mSubModes[2] = (void*)&s->mSubModeDance;
  s->mc0 = 4;
  s->mc4 = 1;
  ((TC_62a550*)s)->FUN_0062a550();
  for (unsigned i = 0; i < 4; ++i) {
    if (i == 1 || s->mSubModes[i] == 0) continue;
    void** svt = *(void***)s->mSubModes[i];
    ((TF1)svt[1])(s->mSubModes[i], (int)&s->mParams);
  }
  {
    void** pvt = *(void***)s->mSubModes[1];
    ((TF0)pvt[3])(s->mSubModes[1]);
  }
  ((TC_Anim*)&s->mAnim3588)->FUN_0062e6c0();

  if (s->m10 != 0) {
    void* p = s->m10;
    s->m10 = 0;
    ((TF0)(*(void**)((char*)*(void**)p + 4)))(p);
  }

  s->m14 = 0.0f;
  s->m1c = 0; s->m1d = 0; s->m1e = 0;
  s->m28 = 0.0f; s->m2c = 0.0f; s->m30 = 0.0f;
  s->m24 = -1;
  s->m1f = 0; s->m20 = 0;
  s->m34 = 0.0f; s->m38 = 0.0f;
  s->m36d0 = 0;
  s->m4c = 0;
  s->m36d4 = -1;

  {
    unsigned r = ((TC_6286a0*)s)->FUN_006286a0();
    void** ant = *(void***)&s->mAnim3588;
    unsigned cid = ((PMSlot3614*)s->m3614)->mCreatureID;
    ((TFF5)ant[3])(&s->mAnim3588, cid, r, 0, 1, 0);
    ((TFF5)ant[3])(&s->mAnim3588, cid, 0x4330667, 1, 0, 0);
  }

  for (int i = 0; i < 3; ++i) {
    s->m36d8[i] = 0;
    s->m40[i] = 0.0f;
  }
  s->m51 = 0;
  s->m4e[0] = 0; s->m4e[1] = 0; s->m4e[2] = 0;
  s->m54 = gCamX15f6d6c;
  s->m58 = gCamY15f6d70;
  s->m5c = gCamZ15f6d74;
  s->m60 = 0;
  s->m3708 = 1;

  if (s->mStopwatch.mMode10 == 1) {
    unsigned lo, hi;
    __asm {
      rdtsc
      mov lo, eax
      mov hi, edx
    }
    s->mStopwatch.mTicks0 = lo;
    s->mStopwatch.mTicks4 = hi;
  } else {
    long long q;
    FUN_013cc2b8(&q);
    s->mStopwatch.mTicks0 = (uint32_t)q;
    s->mStopwatch.mTicks4 = (uint32_t)(q >> 32);
  }
  s->mStopwatch.mZero8 = 0;
  s->mStopwatch.mZeroC = 0;

  ((TC_UI*)s->mUI)->FUN_00635e80();
  s->m3709 = 0;

  void* pmem = FUN_00f473a0(0x4004c, g_013f586c, 0, 0, 0, 0);
  void* newPath = 0;
  if (pmem != 0) newPath = ((TC_62de70*)pmem)->FUN_0062de70();
  void* oldPath = s->mPath;
  if (newPath != oldPath) {
    if (newPath != 0) ((TF0)(*(void**)((char*)*(void**)newPath + 4)))(newPath);
    s->mPath = newPath;
    if (oldPath != 0) ((TF0)(*(void**)((char*)*(void**)oldPath + 8)))(oldPath);
  }
  ((PMPath*)s->mPath)->FUN_0062d8a0(gConst13ebc68, gConst13ebc68);

  {
    uint32_t* b64 = s->mVec64Begin;
    uint32_t* e64 = s->mVec64End;
    FUN_011e0744(b64, e64, 0);
    s->mVec64End = (uint32_t*)((char*)s->mVec64End - ((char*)e64 - (char*)b64));
  }
  {
    void** b7c = s->mVec7cBegin;
    void** e7c = s->mVec7cEnd;
    void** res = FUN_0062ffd0(e7c, e7c, b7c);
    void** end7c = s->mVec7cEnd;
    for (void** p = res; p < end7c; ++p) {
      void* o = *p;
      if (o != 0) ((TF0)(*(void**)((char*)*(void**)o + 8)))(o);
    }
    s->mVec7cEnd = (void**)((char*)s->mVec7cEnd - ((char*)e7c - (char*)b7c));
  }
  FUN_0062bb40((int)((PMSlot3614*)s->m3614)->mCreatureID, 0);
}

// @ 0x0062c340
void PM::Stop() {
  PM_L* s = (PM_L*)this;
  FUN_0062bec0();

  if (s->mPath != 0) {
    void* p = s->mPath;
    s->mPath = 0;
    ((TF0)(*(void**)((char*)*(void**)p + 8)))(p);
  }

  ((TC_UI*)s->mUI)->FUN_00635760(0x3fbfa5cu, 0);
  ((TC_UI*)s->mUI)->FUN_00635760(0x4446a98u, 0);
  ((TC_UI*)s->mUI)->FUN_00635760(0x4446ae0u, 0);

  ((PMBGMgr*)&s->mBGMgr3618)->FUN_0062f920();

  for (unsigned i = 0; i < 4; ++i) {
    if (i == 1 || s->mSubModes[i] == 0) continue;
    void** svt = *(void***)s->mSubModes[i];
    ((TF0)svt[2])(s->mSubModes[i]);
  }
  {
    void** pvt = *(void***)s->mSubModes[1];
    ((TF0)pvt[4])(s->mSubModes[1]);
  }

  PMSlot3614* slot = (PMSlot3614*)s->m3614;
  slot->FUN_005798f0();
  slot->FUN_00582d70(1, 0, 0);

  for (int i = 3; i != 0; --i) {
    void* o = s->m3660;
    if (o != 0) {
      void* inner = *(void**)o;
      void** ivt = *(void***)inner;
      ((TF2u)ivt[0x16c / 4])(inner, o, 0);
      void* o2 = s->m3660;
      if (o2 != 0) {
        s->m3660 = 0;
        PMRefObj* ro = (PMRefObj*)o2;
        if (ro->mCount40 > 1) {
          ro->mCount40 = ro->mCount40 - 1;
        } else {
          unsigned flag = (unsigned)ro->mRefCount >> 31 & 1;
          void* inner2 = ro->mObject;
          void** ivt2 = *(void***)inner2;
          ((TF2u)ivt2[0x170 / 4])(inner2, o2, flag);
        }
      }
    }
  }

  ((TC_62b000*)s)->FUN_0062b000();

  if (s->m10 != 0) {
    void* p = s->m10;
    ((TF1)(*(void**)((char*)*(void**)p + 0xc)))(p, 0);
    if (s->m10 != 0) {
      p = s->m10;
      s->m10 = 0;
      ((TF0)(*(void**)((char*)*(void**)p + 4)))(p);
    }
  }

  {
    void* msgsrv = FUN_0067dcc0();
    if (msgsrv != 0) {
      void** mvt = *(void***)msgsrv;
      void* handler = (void*)&s->mIHandler8;
      ((TF3u)mvt[0x2c / 4])(msgsrv, handler, 0x692ea61u, 0xffffd8f1u);
      ((TF3u)mvt[0x2c / 4])(msgsrv, handler, 0x3eaed50u, 0xffffd8f1u);
      ((TF3u)mvt[0x2c / 4])(msgsrv, handler, 0x4114116u, 0xffffd8f1u);
      ((TF3u)mvt[0x2c / 4])(msgsrv, handler, 0x58b8059u, 0xffffd8f1u);
      ((TF3u)mvt[0x2c / 4])(msgsrv, handler, 0x5b053b5u, 0xffffd8f1u);
    }
  }

  for (unsigned i = 0; i < 4; ++i) {
    if (i == 1) continue;
    s->mSubModes[i] = 0;
  }
  {
    void* pc = slot->mAc;
    if (pc != 0) ((PMAc*)pc)->mFlags4 &= 0xfffffffeu;
  }

  ((TC_UI*)s->mUI)->FUN_006353e0(1);
  if (s->mUI != 0) ((TC_UI*)s->mUI)->FUN_006373e0();

  {
    void* b = FUN_0067de40();
    void** bvt = *(void***)b;
    void* c = ((TF0p)bvt[0x20 / 4])(b);
    void** cvt = *(void***)c;
    ((TF1)cvt[0x20 / 4])(c, (int)gPMGlobal);
  }
}

// @ 0x0062c550
void PM::Update(int delta) {
  PM_L* s = (PM_L*)this;
  FUN_0062bdb0();
  ((TC_629de0*)s)->FUN_00629de0();

  if (s->m36d0 != 0) {
    unsigned id = ((TC_6291d0*)s)->FUN_006291d0(0);
    int idx = -1;
    for (int i = 0; i < 3; ++i) {
      if ((unsigned)s->m36d8[i] == id) { idx = i; break; }
    }
    if (idx >= 0 && s->m4e[idx] != 0) {
      PMSlot3614* slot = (PMSlot3614*)s->m3614;
      float pos[3];
      PMCamera* cam = (PMCamera*)slot->FUN_00572400();
      cam->FUN_00626db0(pos);
      float fDeltaX = pos[0] - s->m54;
      float fDeltaY = pos[1] - s->m58;
      float fDeltaZ = pos[2] - s->m5c;
      float dist;
      __asm {
        fld  dword ptr [fDeltaX]
        fmul dword ptr [fDeltaX]
        fld  dword ptr [fDeltaY]
        fmul dword ptr [fDeltaY]
        faddp st(1), st(0)
        fld  dword ptr [fDeltaZ]
        fmul dword ptr [fDeltaZ]
        faddp st(1), st(0)
        fsqrt
        fstp dword ptr [dist]
      }
      if (dist > gTol0_05_13ec478) {
        int state = ((PMCamera*)slot->FUN_00572400())->mState8c;
        if (state != 4 && state != 5) {
          if (state != 0 || (s->m60 != 4 && s->m60 != 5)) {
            s->m4e[0] = 0; s->m4e[1] = 0; s->m4e[2] = 0;
            s->m54 = pos[0];
            s->m58 = pos[1];
            s->m5c = pos[2];
          }
        }
        s->m60 = state;
      }
    }
  }

  for (unsigned i = 0; i < 4; ++i) {
    if (s->mSubModes[i] == 0) continue;
    void** svt = *(void***)s->mSubModes[i];
    ((TF1)svt[5])(s->mSubModes[i], delta);
  }

  {
    unsigned n = (unsigned)((char*)s->mVec7cEnd - (char*)s->mVec7cBegin) >> 2;
    for (unsigned i = 0; i < n; ++i) {
      ((TC_62cef0*)s->mVec7cBegin[i])->FUN_0062cef0(delta);
    }
  }

  ((PMBGMgr*)&s->mBGMgr3618)->FUN_0062f2f0();

  if (s->m3708 != 0) {
    long long t = s->mStopwatch.FUN_0093a3a0();
    if ((double)t * s->mStopwatch.mScale14 > gTwo1470f1c) {
      ((TC_UI*)s->mUI)->FUN_00634ef0(0x3e831e4u, 1);
      ((TC_UI*)s->mUI)->FUN_00634f50(0x3e831e4u, 1);
      ((TC_UI*)s->mUI)->FUN_00634ec0(0x3f43834u, 1);
      ((TC_UI*)s->mUI)->FUN_00635390(1);
      {
        void* o = ((PMSlot3614*)s->m3614)->m358;
        void** ovt = *(void***)o;
        ((TF1)ovt[0x1c / 4])(o, 0);
      }
      ((TC_UI*)s->mUI)->FUN_00634f50(0x44594d8u, 0);
      ((TC_UI*)s->mUI)->FUN_00634f50(0x445a468u, 0);
      ((TC_UI*)s->mUI)->FUN_00634ec0(0x44593d0u, 0);
      ((TC_UI*)s->mUI)->FUN_00634ec0(0x445a418u, 0);
      ((TC_UI*)s->mUI)->FUN_006357c0(0x44594d8u, 1);
      ((TC_UI*)s->mUI)->FUN_006357c0(0x445a468u, 1);
      ((TC_UI*)s->mUI)->FUN_00635e80();
      ((TC_UI*)s->mUI)->FUN_00635dc0(0x46db770u);
      ((TC_UI*)s->mUI)->FUN_00635f00(1);
      ((TC_UI*)s->mUI)->FUN_00635ff0(0);
      ((TC_Anim*)&s->mAnim3588)->FUN_0062e7a0();
      ((TC_Anim*)&s->mAnim3588)->FUN_0062e600();
      s->mStopwatch.FUN_0093a2e0();
      s->mStopwatch.mTicks0 = 0;
      s->mStopwatch.mTicks4 = 0;
      s->mStopwatch.mZero8 = 0;
      s->mStopwatch.mZeroC = 0;
      s->m3708 = 0;
    }
  }

  ((TC_UI*)s->mUI)->FUN_00634c80(delta);
}

// @ 0x0062c7e0
bool PM::FUN_0062c7e0(int idx, int a) {
  char* s = (char*)this;
  if (*(unsigned char*)(s + 0x36d0) >= 3) return false;
  void* mgr = *(void**)(s + 0x3614);
  if (!((CreatureMgr*)mgr)->RunSkinPaintOnEditorModel(1, a)) return false;
  ++*(unsigned char*)(s + 0x36d0);
  int id = GetLatestBabyID();
  if (id == -1) return true;
  char* cstr = (char*)((CreatureMgr*)*(void**)((char*)mgr + 0x360))->GetCreatureStructure(id);
  *(float*)(cstr + 0x74) = gConst13fe160;
  *(float*)(cstr + 0x78) = 0.0f;
  unsigned char b = ((SharedLibList*)(s + 0x3618))->FUN_0062f6c0();
  ((EventInfo*)cstr)->ctor(b);
  ((Creature*)((CreatureMgr*)*(void**)((char*)mgr + 0x360))->GetCreature(id))->FUN_00a04a90(1);
  SetMomToFaceBaby(id);
  *(unsigned char*)(s + 0x1f) = 1;
  *(int*)(s + idx * 4 + 0x36d8) = id;
  FUN_0062bb40(id, 1);
  char* puVar2 = (char*)*(void**)((char*)mgr + 0x360);
  void* cr2 = ((CreatureMgr*)puVar2)->GetCreature(*(int*)(puVar2 + 0x364));
  int local = 0;
  ((TF4)(*(void**)(*(char**)cr2 + 0x58)))(cr2, (int)&local, 0, 0, 0);
  if (((Dance*)(s + 0x11b0))->IsDancingAnim(local, 0)) SetBabyIdleAnim(id);
  return true;
}

// @ 0x0062c910
void PM::FUN_0062c910() {
  char* s = (char*)this;
  void* p = *(void**)(s + 0x94);
  if (p != 0) {
    *(void**)(s + 0x94) = 0;
    ((TF0)(*(void**)(*(char**)p + 4)))(p);
  }
  if (*(void**)(s + 0xc8) != 0) Stop();
  void* q = *(void**)(s + 0xcc);
  ((TF0)(*(void**)(*(char**)q + 8)))(q);
  {
    char* vt = *(char**)(s + 0x3588);
    ((TF0)(*(void**)(vt + 8)))(s + 0x3588);
  }
  *(void**)(s + 0xcc) = 0;
  void* g = *(void**)&gPMGlobal;
  if (g != 0) {
    *(void**)&gPMGlobal = 0;
    ((TF0)(*(void**)(*(char**)g + 8)))(g);
  }
  void* h = *(void**)(s + 0xc);
  if (h != 0) {
    *(void**)(s + 0xc) = 0;
    ((TF0)(*(void**)(*(char**)h + 4)))(h);
  }
}

// @ 0x0062c990
void PM::FUN_0062c990(int id) {
  char* s = (char*)this;
  if (id >= 0) {
    if (*(void**)(s + id * 4 + 0x36d8) == 0) {
      FUN_0062c7e0(id, 0);
      return;
    }
    IsEventForBaby(id);
    return;
  }
  void* mgr = *(void**)(s + 0x3614);
  if (*(unsigned char*)(s + 0x36d0) == 0) {
    ((CreatureMgr*)mgr)->RunSkinPaintOnEditorModel(1, 0);
    ((PMUI*)*(void**)(s + 0xc))->SetUIGroupVisible(0x4066678u, 1);
    ((PMUI*)*(void**)(s + 0xc))->SetUIGroupVisible(0x40666b8u, 1);
    *(unsigned char*)(s + 0x36d0) = 1;
    int bid = GetLatestBabyID();
    if (bid == -1) return;
    SetMomToFaceBaby(bid);
    *(unsigned char*)(s + 0x1f) = 1;
    return;
  }
  ((CreatureMgr*)mgr)->DestroyAnimatedCreature(1, 0);
  ((PMUI*)*(void**)(s + 0xc))->SetUIGroupVisible(0x4066678u, 0);
  ((PMUI*)*(void**)(s + 0xc))->SetUIGroupVisible(0x40666b8u, 0);
  void* edx = *(void**)(s + 0x3614);
  int off = *(int*)((char*)edx + 0x364);
  char* vt = *(char**)(s + 0x3588);
  *(unsigned char*)(s + 0x36d0) = 0;
  ((TF5)(*(void**)(vt + 0xc)))(s + 0x3588, off, 0x4373694, 0, 1, 0);
}
