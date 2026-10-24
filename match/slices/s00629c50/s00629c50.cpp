// SP::cSPPlayMode play-mode subsystem (SporeEP1_RL). Region 0x629c50-0x62abc5.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

static inline void** Vt(void* p) { return *(void***)p; }

// ---- forward declarations ---------------------------------------------------
struct cSPPlayMode;
struct cSPPlayModeUI {
  void* Construct();                // 0x634c10  (this = raw alloc -> returns ctor result)
};
struct cPlayModeTokenTranslator {
  void* Construct();                // 0x6345b0
};
struct cSPPlayMode_Creature;
struct cAnimatingCreature;
struct cPlayModePath;
struct cEditorState;

// ---- external helpers -------------------------------------------------------
void*  __cdecl csp_operator_new(uint32_t size, const char* name, int, int, int, int); // 0xf473a0
float  __cdecl FUN_009b3c10(float a, float b);          // 0x9b3c10
void*  __cdecl PropertyManager();                       // 0x67de30
void*  __cdecl ModelManager();                          // 0x67dd80
void*  __cdecl EffectsManager();                        // 0x67ddd0
bool   __cdecl GetPropertyAsKeyInstance(void* prop, int key, void* out); // 0x6a12a0
void   __stdcall FUN_00629d90(int creature, int effectId);               // 0x629d90

struct Vector3 { float x, y, z; };

void* __cdecl FUN_0062cb20(const Vector3* p, float a, int b, float c);   // 0x62cb20

// ---- effect manager (creature +0x17c, and cPlayMode_Creature server) --------
struct Mgr029 {
  void* Find(int id);            // 0x9cab60
  void  Remove(void* p);         // 0x9cb460
  void* Create(int id, int, int); // 0x9cb300
};

// an effect instance owned by Mgr029
struct cswEffect {
  uint8_t pad00[0x8c];
  void*   mpSub;                 // 0x8c
  void  FUN_009caa40(void* a, void* b, int c);  // 0x9caa40
};

struct cAnimatingCreature {
  uint8_t  pad000[0x17c];
  Mgr029*  mpEffectMgr;          // 0x17c
  void  Reset(int arg);          // 0xa04a90
};

// ---- editor baby element (cEditorState baby vector, stride 0x30) ------------
struct BabyElem {
  uint32_t id;                   // 0x00
  uint8_t  pad04[0x14];          // 0x04
  uint8_t  flag18;               // 0x18
  uint8_t  pad19[3];             // 0x19
  uint8_t  flag1c;               // 0x1c
  uint8_t  pad1d[3];             // 0x1d
  uint32_t f20;                  // 0x20
  float    f24;                  // 0x24
  float    f28;                  // 0x28
  int32_t  effectId;             // 0x2c
};

// ---- editor animated-creature data -----------------------------------------
struct cSPEditorAnimatedCreatureData {
  uint8_t  pad000[0x2c];
  Vector3  mTargetPosition;      // 0x2c
  Vector3  mActualPosition;      // 0x38
  uint32_t pad44;
  float    mActualAngle;         // 0x48
  float    mMovementSpeed;       // 0x4c
  float    mRotationSpeed;       // 0x50
  uint8_t  pad54[0x74 - 0x54];
  float    f74;                  // 0x74
  float    f78;                  // 0x78
  float    f7c;                  // 0x7c
  float    f80;                  // 0x80
  void  SetTargetPosition(Vector3& v, bool a, bool b);  // 0x59b0f0
};

// ---- a play-mode path node ("cPlayModePath") --------------------------------
struct cPlayModePath {
  uint32_t pad00[2];
  Vector3  mTargetPosition;      // 0x08
  uint8_t  pad14[0x28 - 0x14];
  uint8_t  flag28;               // 0x28
  uint8_t  pad29;
  uint8_t  flag2a;               // 0x2a
};

// ---- editor animated-creature manager --------------------------------------
struct cSPEditorAnimatedCreatureManager {
  cAnimatingCreature* GetCreature(uint32_t id);               // 0x59ca70
  cSPEditorAnimatedCreatureData* GetCreatureStructure(uint32_t id); // 0x59cac0
};

// ---- editor that owns the play mode ------------------------------------
struct cEditorState {
  uint8_t  pad000[0x84];
  void*    mWorld84;             // 0x84
  uint8_t  pad088[0xac - 0x88];
  void*    mObjAC;               // 0xac
  uint8_t  pad0b0[0x360 - 0xb0];
  cSPEditorAnimatedCreatureManager* mMgr;  // 0x360
  uint32_t mMomId;               // 0x364
  uint32_t pad368;
  BabyElem* mBabiesBegin;        // 0x36c
  BabyElem* mBabiesEnd;          // 0x370
  bool  RunSkinPaintOnEditorModel(int, void*);   // 0x582fe0
  void  ShowCreature();                          // 0x573390
  void  SwitchToPlayModeCamera();                // 0x574a60
  void  FUN_00572450(void* a, void* b, void* c); // 0x572450
};

// ---- sub-mode base / action -------------------------------------------------
struct cSPPlayModeSubModeBase {
  virtual void v0();
  virtual void v1(void* params);
  virtual void v2();
  virtual void v3();
  void*    mEditorBaseMode;      // 0x04
  void*    mAnim;                // 0x08
  void*    mSubModeParams;       // 0x0c
  uint32_t mField10;             // 0x10
  uint32_t mField14;             // 0x14
};

struct cSPPlayModeSubModeAction : cSPPlayModeSubModeBase {
  float SetIdleAnimation(cAnimatingCreature*, unsigned, bool, bool);  // 0x638fd0
  void  SetWalkAnimation(cAnimatingCreature*, unsigned);              // 0x6388e0
  uint8_t padAction[0x100 - 0x18];
};

// ---- animation controller ---------------------------------------------------
struct cSPPlayModeAnimation {
  virtual void  v0();
  virtual void  Init(void* ed, cSPPlayModeUI* ui);
  virtual void  v2();
  virtual float StartNewAnimation(unsigned, unsigned, bool, unsigned, void**);
  uint8_t pad[0x8c - 4];
};

// ---- a 4-byte AutoRefCount-like holder -------------------------------------
struct AutoRef4 {
  void* mpObject;                // 0x00
  void  FUN_00478db0(void* p);   // 0x478db0
};

// ============================================================================
struct cSPPlayMode {
  uint32_t pad000[3];            // 0x000
  cSPPlayModeUI* mUI;            // 0x00c
  void*    mSleepEffect;         // 0x010
  float    mIdleTime;            // 0x014
  float    mSleepAnimChangeTime; // 0x018
  uint8_t  mSleeping;            // 0x01c
  uint8_t  mSleepMode;           // 0x01d
  uint8_t  pad01e[2];            // 0x01e
  uint32_t pad020[2];            // 0x020
  float    mCrouchValue;         // 0x028
  uint32_t pad02c[4];            // 0x02c
  float    mMomTargetAngle;      // 0x03c
  uint32_t pad040[3];            // 0x040
  uint8_t  mFlag4c;              // 0x04c
  uint8_t  pad04d[0x7c - 0x4d];  // 0x04d
  cSPPlayMode_Creature** mCreaturesBegin; // 0x07c
  cSPPlayMode_Creature** mCreaturesEnd;   // 0x080
  uint32_t pad084[3];            // 0x084
  void*    mPreloadList;         // 0x090
  uint32_t pad094;               // 0x094
  void*    mPlayModeConfig;      // 0x098
  uint32_t mBits9c[2];           // 0x09c
  uint32_t mBitsA4[2];           // 0x0a4
  uint32_t mBitsAC[2];           // 0x0ac
  void*    mParamsUI;            // 0x0b4
  void*    mParamsAnim;          // 0x0b8
  void*    mParamsPlayMode;      // 0x0bc
  uint32_t pad0c0;               // 0x0c0
  uint8_t  mEnteringPlayMode;    // 0x0c4
  uint8_t  pad0c5[3];            // 0x0c5
  cSPPlayModeSubModeBase* mSubModes[4];   // 0x0c8
  cSPPlayModeSubModeAction mActionMode;   // 0x0d8
  uint32_t pad1d8[4];            // 0x1d8
  cSPPlayModeSubModeBase mSubMode1e8;     // 0x1e8
  uint32_t pad200[0x11b0 / 4 - 0x200 / 4];// 0x200
  cSPPlayModeSubModeBase mSubMode11b0;    // 0x11b0
  uint32_t pad11c8[0x3588 / 4 - 0x11c8 / 4]; // 0x11c8
  cSPPlayModeAnimation mAnimation;        // 0x3588
  cEditorState* mEditor;                  // 0x3614
  uint32_t pad3618[0x3660 / 4 - 0x3618 / 4]; // 0x3618
  AutoRef4 mRef3660;                      // 0x3660
  uint32_t m3664;                         // 0x3664
  uint32_t pad3668[0x36cc / 4 - 0x3668 / 4]; // 0x3668
  uint32_t m36cc;                         // 0x36cc
  uint8_t  mNumBabies;                    // 0x36d0
  uint8_t  pad36d1[3];                    // 0x36d1
  uint32_t m36d4;                         // 0x36d4
  uint32_t m36d8;                         // 0x36d8
  uint32_t m36dc;                         // 0x36dc
  uint32_t m36e0;                         // 0x36e0
  uint32_t m36e4;                         // 0x36e4
  uint32_t m36e8;                         // 0x36e8
  uint32_t m36ec;                         // 0x36ec
  uint8_t  pad36f0[0x370a - 0x36f0];      // 0x36f0
  uint8_t  mFlag370a;                     // 0x370a

  // --- methods (this slice) ---
  void  FUN_00629c50();                                    // 0x00629c50
  void  FUN_00629de0();                                    // 0x00629de0
  void  StopWalk(cAnimatingCreature*, unsigned);           // 0x0062a1a0
  void  SetBabyPath(unsigned, float, float, float);        // 0x0062a230
  void  Init(void* ed, uint8_t flag);                      // 0x0062a3d0
  void  FUN_0062a550();                                    // 0x0062a550
  void  WakeupCreature();                                  // 0x0062a760
  void  SetupFromConfigFile();                             // 0x0062a860
  void  BabyStartSocialCallEffect(unsigned, unsigned);     // 0x0062a990
  void  SetBabySitState(unsigned);                         // 0x0062aa90
  // --- existing nonmatching members (unchanged bodies) ---
  bool  HasActivePath(int);                                // 0x0062a360
  uint8_t OnMouseDown(void*, void*, void*, void*);         // 0x0062a7f0
  void  SetAllBabySitState();                              // 0x0062ab80
  // --- external cSPPlayMode callees ---
  void     SetAllBabySitUp();                              // 0x629220
  unsigned GetMouthPartIdx();                              // 0x628a80
  unsigned GetAnimatedBabyIndex(unsigned);                 // 0x629180
  float    FUN_00629bd0(cSPEditorAnimatedCreatureData*);   // 0x629bd0
  void     EnsurePreload();                                // 0x6289a0
};

// ---- constants/globals the original reads by absolute address ---------------
void* gTokenTranslator = 0;          // 0x15f7cf4
void* gKey15222fc = 0;               // 0x15222fc
void* gKey1522318 = 0;               // 0x1522318
float gAnglePeriod = 6.2831855f;     // 0x15f6ee4
float gPi          = 3.1415927f;     // 0x15f6de4

// ---- cSPPlayMode_Creature ---------------------------------------------------
struct cSPPlayMode_Creature {
  uint32_t pad00[2];                          // 0x00
  cAnimatingCreature* mAnimCreature;          // 0x08
  uint32_t pad0c;                             // 0x0c
  cSPEditorAnimatedCreatureData* mAnimatedCreatureData; // 0x10
  uint32_t pad14;                             // 0x14
  void*    mPath;                             // 0x18
  uint32_t mCreatureID;                       // 0x1c
  float    mCollisionRadius;                  // 0x20
  uint8_t  mCollision;                        // 0x24
  uint8_t  pad25[3];                          // 0x25
  float    mWait;                             // 0x28
  float    mSaveSpeed;                        // 0x2c
  float    mSaveRot;                          // 0x30
  float    mField34;                          // 0x34
  uint32_t pad38;                             // 0x38
  cPlayModePath** mPathListBegin;             // 0x3c
  cPlayModePath** mPathListEnd;               // 0x40
  void  ClearPathList();                      // 0x62cb90
  void  AddPathTarget(void* path, bool b);    // 0x62ce00
  bool  FUN_0062d0f0(Vector3& v, float radius, bool a, bool b); // 0x62d0f0
};

// ============================================================================
// @ 0x00629c50
void cSPPlayMode::FUN_00629c50() {
  cSPEditorAnimatedCreatureManager* mgr = mEditor->mMgr;
  cSPEditorAnimatedCreatureData* mom = mgr->GetCreatureStructure(mEditor->mMomId);
  mom->mRotationSpeed = FUN_00629bd0(mom);
  mom->mMovementSpeed = 2.5f;

  if (mNumBabies != 0) {
    for (unsigned i = 0; i < mNumBabies; ++i) {
      BabyElem* begin = mEditor->mBabiesBegin;
      unsigned n = (unsigned)(mEditor->mBabiesEnd - mEditor->mBabiesBegin);
      uint32_t id;
      if (n == 0) id = 0xffffffffu;
      else if (i < n) id = begin[i].id;
      else id = begin[0].id;

      cSPEditorAnimatedCreatureData* d = mgr->GetCreatureStructure(id);
      float v;
      if (d != 0) {
        float a = FUN_009b3c10(mMomTargetAngle - d->mActualAngle, gAnglePeriod);
        float c = fabsf(a) * 2.5f;
        float lim = gPi * 1.35f;
        v = (c <= lim) ? c : lim;
      } else {
        v = gPi;
      }
      d->mMovementSpeed = 2.5f;
      d->mRotationSpeed = v;
    }
  }
}

// @ 0x00629de0
void cSPPlayMode::FUN_00629de0() {
  char local_61 = 0;
  if (mNumBabies == 0) return;

  cSPPlayMode_Creature** begin = mCreaturesBegin;
  cSPEditorAnimatedCreatureData* d0 = begin[0]->mAnimatedCreatureData;
  Vector3 p0 = d0->mActualPosition;
  unsigned n = (unsigned)(mCreaturesEnd - mCreaturesBegin);

  for (unsigned i = 1; i < n; ++i) {
    cSPEditorAnimatedCreatureData* di = begin[i]->mAnimatedCreatureData;
    Vector3 pi = di->mActualPosition;

    float r = begin[i]->mCollisionRadius + begin[0]->mCollisionRadius;
    if (3.75f < r) r = 3.75f;

    float midX = (pi.x + p0.x) * 0.5f;
    float midY = (pi.y + p0.y) * 0.5f;
    float midZ = (pi.z + p0.z) * 0.5f;
    float dX = p0.x - pi.x;
    float dY = p0.y - pi.y;
    float dZ = p0.z - pi.z;
    float dist = sqrtf(dY * dY + (dZ * dZ + dX * dX));
    if (dist < r) {
      float s = r * 0.51f;
      float inv = 1.0f / dist;
      float nY = (dY * inv) * s;
      float nX = (inv * dX) * s;
      float nZ = (dZ * inv) * s;

      Vector3 v1 = { midX + nX, midY + nY, midZ + nZ };
      Vector3 v2 = { midX - nX, midY - nY, midZ - nZ };

      begin[0]->mCollision = 1;
      Vector3 t0 = d0->mTargetPosition;
      d0->SetTargetPosition(v1, true, true);
      d0->SetTargetPosition(t0, false, true);
      begin[0]->FUN_0062d0f0(v1, begin[0]->mCollisionRadius, false, i == 0);

      begin[i]->mCollision = 1;
      Vector3 ti = di->mTargetPosition;
      di->SetTargetPosition(v2, true, true);
      di->SetTargetPosition(ti, false, true);
      local_61 = begin[i]->FUN_0062d0f0(v2, begin[i]->mCollisionRadius, i != 0, true) ? 1 : 0;
    }
  }
  if (local_61) return;

  for (unsigned i = 0; i < n; ++i) {
    cSPPlayMode_Creature* c = mCreaturesBegin[i];
    if (c->mCollision == 0) continue;
    if (i == 0) {
      bool walking = false;
      for (unsigned j = 1; j < n; ++j) {
        cSPPlayMode_Creature* cj = mCreaturesBegin[j];
        if (cj->mPathListEnd != cj->mPathListBegin &&
            (*cj->mPathListBegin)->flag28 == 1) {
          walking = true;
          break;
        }
      }
      if (!walking) {
        c->mAnimCreature->Reset(1);
        c->mCollision = 0;
        cSPEditorAnimatedCreatureData* d = c->mAnimatedCreatureData;
        d->mMovementSpeed = c->mSaveSpeed;
        d->mRotationSpeed = c->mSaveRot;
        if (c->mPathListEnd != c->mPathListBegin) {
          d->SetTargetPosition((*c->mPathListBegin)->mTargetPosition, false, true);
        }
        mActionMode.SetWalkAnimation(c->mAnimCreature, c->mCreatureID);
      }
    } else {
      if (c->mPathListEnd == c->mPathListBegin || (*c->mPathListBegin)->flag28 != 1) {
        c->mAnimCreature->Reset(1);
        c->mCollision = 0;
      }
    }
  }
}

// @ 0x0062a1a0
void cSPPlayMode::StopWalk(cAnimatingCreature* creature, unsigned id) {
  mActionMode.SetIdleAnimation(creature, id, false, false);
  mAnimation.StartNewAnimation(id, 0x4330667, true, 0, 0);
  cEditorState* ed = mEditor;
  if (id != ed->mMomId) {
    unsigned idx = GetAnimatedBabyIndex(id);
    unsigned n = (unsigned)(ed->mBabiesEnd - ed->mBabiesBegin);
    if (idx < n) {
      ed->mBabiesBegin[idx].flag18 = 0;
    }
  }
}

// @ 0x0062a230
void cSPPlayMode::SetBabyPath(unsigned id, float x, float y, float z) {
  cSPPlayMode_Creature** begin = mCreaturesBegin;
  unsigned n = (unsigned)(mCreaturesEnd - mCreaturesBegin);
  if (n == 0) return;
  unsigned i = 0;
  while (begin[i]->mCreatureID != id) {
    ++i;
    if (n <= i) return;
  }
  if (i < n) {
    cSPPlayMode_Creature* c = begin[i];
    cSPEditorAnimatedCreatureData* data = c->mAnimatedCreatureData;
    if (((data->mActualPosition.x != x) || (data->mActualPosition.y != y)) ||
        (z != 0.0f)) {
      bool pathMatches = false;
      if (c->mPathListEnd != c->mPathListBegin) {
        cPlayModePath* p = *c->mPathListBegin;
        pathMatches = (p->mTargetPosition.x == x) && (p->mTargetPosition.y == y) &&
                      (p->mTargetPosition.z == z);
      }
      if (!pathMatches) {
        c->ClearPathList();
        cPlayModePath* t = (cPlayModePath*)FUN_0062cb20((const Vector3*)&x, 1.0f, 0, 0.5f);
        t->flag2a = 1;
        c->AddPathTarget(t, false);
      }
    }
  }
}

// @ 0x0062a3d0
void cSPPlayMode::Init(void* ed, uint8_t flag) {
  mEditor = (cEditorState*)ed;
  mFlag370a = flag;

  void* t = csp_operator_new(0x60, "Editor", 0, 0, 0, 0);
  if (t != 0) t = ((cPlayModeTokenTranslator*)t)->Construct();
  if (t != gTokenTranslator) {
    if (t != 0) ((void(__thiscall*)(void*))Vt(t)[1])(t);
    void* old = gTokenTranslator;
    gTokenTranslator = t;
    if (old != 0) ((void(__thiscall*)(void*))Vt(old)[2])(old);
  }

  void* ui = csp_operator_new(0x70, "Editor", 0, 0, 0, 0);
  if (ui != 0) ui = ((cSPPlayModeUI*)ui)->Construct();
  if (ui != (void*)mUI) {
    if (ui != 0) ((void(__thiscall*)(void*))Vt(ui)[0])(ui);
    cSPPlayModeUI* old = mUI;
    mUI = (cSPPlayModeUI*)ui;
    if (old != 0) ((void(__thiscall*)(void*))Vt(old)[1])(old);
  }

  m3664 = 0x3e96904;
  mSubModes[0] = 0;
  mSubModes[1] = 0;
  mSubModes[2] = 0;
  mSubModes[3] = 0;
  mFlag4c = 0;
  m36e4 = 0x44eec00;
  m36e8 = 0x44eecd8;
  m36ec = 0x44eecf0;
  m36d8 = 0;
  m36dc = 0;
  m36e0 = 0;

  void* world = mEditor->mWorld84;
  cSPPlayModeUI* uip = mUI;
  mPlayModeConfig = world;
  mParamsUI = uip;
  mParamsPlayMode = this;
  mParamsAnim = &mAnimation;
  mActionMode.mEditorBaseMode = ed;
  mSubMode1e8.mEditorBaseMode = ed;
  mSubMode11b0.mEditorBaseMode = ed;
  mAnimation.Init(ed, uip);

  mSubModes[1] = &mSubMode1e8;
  mSubMode1e8.v1(&mPlayModeConfig);

  EnsurePreload();
}

// @ 0x0062a550
void cSPPlayMode::FUN_0062a550() {
  if (mEnteringPlayMode == 0) return;

  uint32_t z0 = 0;
  uint32_t z1 = 0;

  mEditor->RunSkinPaintOnEditorModel(0, 0);
  mEditor->ShowCreature();
  mEditor->SwitchToPlayModeCamera();

  {
    void* mm = ModelManager();
    unsigned idx = ((unsigned(__thiscall*)(void*, int, int))Vt(mm)[0x28 / 4])(mm, 0x509991e6, 0);
    if (idx < 0x40) mBitsA4[idx >> 5] |= 1u << (idx & 0x1f);
  }
  {
    void* mm = ModelManager();
    unsigned idx = ((unsigned(__thiscall*)(void*, int, int))Vt(mm)[0x28 / 4])(mm, 0x509991e6, 0);
    if (idx < 0x40) mBitsAC[idx >> 5] |= 1u << (idx & 0x1f);
  }
  {
    void* mm = ModelManager();
    unsigned idx = ((unsigned(__thiscall*)(void*, int, int))Vt(mm)[0x28 / 4])(mm, 0x223e8e0, 0);
    if (idx < 0x40) mBits9c[idx >> 5] |= 1u << (idx & 0x1f);
  }
  {
    void* mm = ModelManager();
    unsigned idx = ((unsigned(__thiscall*)(void*, int, int))Vt(mm)[0x28 / 4])(mm, 0x3f57672, 0);
    if (idx < 0x40) mBitsAC[idx >> 5] |= 1u << (idx & 0x1f);
  }

  mEditor->FUN_00572450(mBits9c, mBitsAC, mBitsA4);

  if (mEditor->mObjAC != 0) {
    *(uint32_t*)((char*)mEditor->mObjAC + 4) |= 1;
  }

  uint32_t combined[2];
  combined[0] = mBitsAC[0] | mBits9c[0];
  combined[1] = mBitsAC[1] | mBits9c[1];
  uint32_t zeros[2] = { z0, z1 };

  {
    void* world = mEditor->mWorld84;
    ((void(__thiscall*)(void*, void*, void*, int))Vt(world)[0x11c / 4])(world, combined, zeros, 0);
    ((void(__thiscall*)(void*, void*, void*, int))Vt(world)[0x11c / 4])(world, mBitsA4, zeros, 1);
  }

  {
    cSPEditorAnimatedCreatureManager* mgr = mEditor->mMgr;
    mgr->GetCreature(mEditor->mMomId);
    cSPEditorAnimatedCreatureData* d = mgr->GetCreatureStructure(mEditor->mMomId);
    if (d != 0) {
      d->f74 = 0.15f;
      d->f78 = 0.0f;
      d->f7c = 0.3f;
      d->f80 = 0.5f;
    }
  }
  mEnteringPlayMode = 0;
}

// @ 0x0062a760
void cSPPlayMode::WakeupCreature() {
  if (mSleeping != 0) {
    void* e = mSleepEffect;
    if (e != 0) {
      ((void(__thiscall*)(void*, int))Vt(e)[3])(e, 0);
      e = mSleepEffect;
      if (e != 0) {
        mSleepEffect = 0;
        ((void(__thiscall*)(void*))Vt(e)[1])(e);
      }
    }
  }
  uint8_t mode = mSleepMode;
  mIdleTime = 0.0f;
  mSleepAnimChangeTime = 0.0f;
  mSleeping = 0;
  if (mode >= 2) {
    if (mode == 3) {
      mAnimation.StartNewAnimation(mEditor->mMomId, 0x4079859, false, 1, 0);
    }
    mSleepMode = 0;
    mCrouchValue = 0.0f;
    SetAllBabySitUp();
  }
}

// @ 0x0062a860
void cSPPlayMode::SetupFromConfigFile() {
  if (mPreloadList != 0) {
    void* p = mPreloadList;
    mPreloadList = 0;
    ((void(__thiscall*)(void*))Vt(p)[1])(p);
  }
  void* pm = PropertyManager();
  if (mPreloadList != 0) {
    void* p = mPreloadList;
    mPreloadList = 0;
    ((void(__thiscall*)(void*))Vt(p)[1])(p);
  }
  ((void(__thiscall*)(void*, int, void*, void**))Vt(pm)[0x2c / 4])(
      pm, 0x38f796ad, gKey15222fc, &mPreloadList);

  void* key1 = 0;
  if (GetPropertyAsKeyInstance(mPreloadList, 0x3e2fee2, &key1)) {
    void* o = mPlayModeConfig;
    void* r = ((void*(__thiscall*)(void*, int))Vt(o)[0x144 / 4])(o, 0);
    ((void(__thiscall*)(void*, void*))Vt(r)[0x30 / 4])(r, key1);
  }

  m36cc = 0;
  GetPropertyAsKeyInstance(mPreloadList, 0x3feb3cf, &m36cc);
  void* key3 = 0;
  if (GetPropertyAsKeyInstance(mPreloadList, 0x3e96904, &key3)) {
    void* world = mEditor->mWorld84;
    void* r = ((void*(__thiscall*)(void*, void*, void*, int))Vt(world)[0x0c / 4])(
        world, key3, gKey1522318, 0);
    mRef3660.FUN_00478db0(r);
    if (mRef3660.mpObject != 0) {
      void* mm = ModelManager();
      unsigned idx = ((unsigned(__thiscall*)(void*, int, int))Vt(mm)[0x28 / 4])(mm, 0x3e97417, 0);
      if (idx < 0x40) {
        uint32_t* bits = (uint32_t*)((char*)mRef3660.mpObject + 0x44);
        bits[idx >> 5] |= 1u << (idx & 0x1f);
      }
    }
  }
}

// @ 0x0062a990
void cSPPlayMode::BabyStartSocialCallEffect(unsigned babyIndex, unsigned creatureId) {
  BabyElem* begin = mEditor->mBabiesBegin;
  uint32_t mouthIdx = GetMouthPartIdx();
  if (mouthIdx == 0xffffffffu) return;
  cAnimatingCreature* creature = mEditor->mMgr->GetCreature(creatureId);
  unsigned off = babyIndex;   // element index
  if (begin[off].effectId != -1) {
    FUN_00629d90((int)creature, begin[off].effectId);
    begin[off].effectId = -1;
  }
  void* local = 0;
  void* em = EffectsManager();
  if (local != 0) {
    local = 0;
    ((void(__thiscall*)(void*))Vt(local)[1])(local);
  }
  if (((bool(__thiscall*)(void*, int, int, void**))Vt(em)[0x2c / 4])(
          em, 0xe1b24ddb, 0, &local)) {
    ((void(__thiscall*)(void*, int))Vt(local)[2])(local, 0);
    cswEffect* eff = (cswEffect*)creature->mpEffectMgr->Create(0xe1b24ddb, 0, 0);
    if (eff != 0) {
      eff->FUN_009caa40(local, (void*)mouthIdx, 0);
      begin[off].effectId = 0xe1b24ddb;
    }
  }
  if (local != 0) {
    ((void(__thiscall*)(void*))Vt(local)[1])(local);
  }
}

// @ 0x0062aa90
void cSPPlayMode::SetBabySitState(unsigned index) {
  cEditorState* ed = mEditor;
  BabyElem* begin = ed->mBabiesBegin;
  unsigned n = (unsigned)(ed->mBabiesEnd - ed->mBabiesBegin);
  uint32_t id;
  if (n == 0) id = 0xffffffffu;
  else if (index < n) id = begin[index].id;
  else id = begin[0].id;

  if (begin[index].effectId != -1) {
    cAnimatingCreature* creature = ed->mMgr->GetCreature(id);
    int h = begin[index].effectId;
    if (h != -1) {
      cswEffect* eff = (cswEffect*)creature->mpEffectMgr->Find(h);
      if (eff != 0) {
        if (eff->mpSub != 0) ((void(__thiscall*)(void*, int))Vt(eff->mpSub)[3])(eff->mpSub, 1);
        creature->mpEffectMgr->Remove(eff);
      }
    }
    begin[index].effectId = -1;
  }
  begin[index].f24 = 0.0f;
  begin[index].f28 = 0.0f;
  begin[index].flag1c = 0;
}

// ============================================================================
// @ 0x00629d90
void __stdcall FUN_00629d90(int arg1, int arg2) {
  if (arg2 == -1) return;
  void* v = (*(Mgr029**)(arg1 + 0x17c))->Find(arg2);
  if (v == 0) return;
  if (*(void**)((char*)v + 0x8c)) {
    void* o = *(void**)((char*)v + 0x8c);
    ((void(__thiscall*)(void*, int))Vt(o)[3])(o, 1);
  }
  (*(Mgr029**)(arg1 + 0x17c))->Remove(v);
}

// @ 0x0062ab80
void cSPPlayMode::SetAllBabySitState() {
  cEditorState* ed = mEditor;
  int n = (int)(ed->mBabiesEnd - ed->mBabiesBegin);
  for (int i = 0; i < n; ++i) SetBabySitState((unsigned)i);
}

// @ 0x0062a360
bool cSPPlayMode::HasActivePath(int creatureID) {
  cSPPlayMode_Creature** begin = mCreaturesBegin;
  unsigned n = (unsigned)(mCreaturesEnd - mCreaturesBegin);
  if (n == 0) return false;
  unsigned i = 0;
  while (begin[i]->mCreatureID != (uint32_t)creatureID) {
    ++i;
    if (i >= n) return false;
  }
  if (i < n) {
    cSPPlayMode_Creature* c = begin[i];
    if (c->mField34 > 0.0f) return true;
    cSPPlayMode_Creature* c0 = begin[0];
    if (c0->mCollision != 0 && c->mCollision != 0) return true;
  }
  return false;
}

// @ 0x0062a7f0
uint8_t cSPPlayMode::OnMouseDown(void* a, void* b, void* c, void* d) {
  cSPPlayMode* m = this;
  WakeupCreature();
  *(uint8_t*)((char*)m + 0x1f) = 0;
  *(uint8_t*)((char*)m + 0x20) = 0;
  *(uint32_t*)((char*)m + 0x34) = 0;
  *(uint32_t*)((char*)m + 0x38) = 0;
  uint8_t r = 0;
  int* p = (int*)((char*)m + 0xc8);
  for (int i = 4; i != 0; --i, ++p) {
    if (*p != 0) {
      uint8_t x = ((uint8_t(__thiscall*)(void*, void*, void*, void*, void*))Vt((void*)*p)[6])
                      ((void*)*p, a, b, c, d);
      r = (uint8_t)(r | x);
    }
  }
  return r;
}