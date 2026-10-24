// Slice s00dc77d0 (batch hk2, slice 5). Region 0x00dc7e00-0x00dc7ea7.
// Order object Init: copies src fields, swaps the visual-effect AutoRefCount (+0x94), applies the
// effect with the order's +0x78 value, and releases the animating-creature ref at +0x9c.
#include "types.h"

struct cSrc5 {                     // param_2: object pointer at +0, uint at +0x14
  void*    mpObj;                  // +0x00 AutoRefCount<T> (raw pointer)
  uint32_t pad0[4];                // +0x04..+0x13
  uint32_t mVal;                   // +0x14
};

struct cSub5 {                     // sub-object at +0x64 (size 0x14)
  uint8_t pad[0x14];
  void SetFrom(cSrc5* src);        // 0x00ca0940 thiscall, ret 4
};

struct cMgr5 {                     // returned by FUN_00b3d290 (cdecl, no args)
  uint32_t Get();                  // 0x00ac15e0 thiscall, returns eax
};

struct cEffect5 {                  // EA::Swarm::cIVisualEffect (AutoRefCount target at +0x94)
  void Apply(uint32_t v);          // 0x00bdf6d0 thiscall, ret 4
};

struct cAnim5 {                    // SP::cAnimatingCreature (AutoRefCount target at +0x9c)
  void Release();                  // 0x00a05270 thiscall
};

void*    __cdecl FUN_00b3d290();   // 0x00b3d290 (returns a global-derived manager pointer)

struct cConvertCityOrder5 {
  uint8_t   pad0[0x64];
  cSub5     mSub64;                // +0x64
  uint32_t  m78;                   // +0x78
  uint8_t   pad1[0x90 - 0x7c];
  uint32_t  mGen90;                // +0x90
  void*     mEffect94;             // +0x94 AutoRefCount<cIVisualEffect>
  uint32_t  m98;                   // +0x98
  void*     mAnim9c;               // +0x9c AutoRefCount<cAnimatingCreature>
  uint8_t   pad2[0xac - 0xa0];
  uint8_t   mbFlagAC;              // +0xac

  void Init(cSrc5* src);           // 0x00dc7e00 thiscall, ret 4
  void FUN_00dc7dd0(cSrc5* src);   // 0x00dc7dd0 thiscall, ret 4
};

// @ 0x00dc7e00
void cConvertCityOrder5::Init(cSrc5* src) {
  mSub64.SetFrom(src);
  cMgr5* mgr = (cMgr5*)FUN_00b3d290();
  mGen90 = mgr->Get();

  void* obj = src->mpObj;
  void* nw;
  if (obj) {
    nw = ((void* (__thiscall*)(void*, uint32_t))((*(void***)obj)[3]))(obj, 0x3d5c477);
  } else {
    nw = 0;
  }
  void* old = mEffect94;
  if (nw != old) {
    if (nw) ((void (__thiscall*)(void*))((*(void***)nw)[0]))(nw);
    mEffect94 = nw;
    if (old) ((void (__thiscall*)(void*))((*(void***)old)[1]))(old);
  }
  m98 = src->mVal;
  ((cEffect5*)mEffect94)->Apply(m78);
  if (mAnim9c) {
    cAnim5* a = (cAnim5*)mAnim9c;
    mAnim9c = 0;
    a->Release();
  }
  mbFlagAC = 0;
}

// =====================================================================================
// Slice s00dc77d0 -- vehicle-tree / vehicle-ticker callbacks at 0x00DC77D0 .. 0x00DC7DD0.
// The tree and the ticker both expose a polymorphic sub-object at +0x34 (world position via
// slot 0x2c, radius via slot 0x74 as an x87 long double, path-failure notify via slot 0xec).
// =====================================================================================

extern "C" void __cdecl FUN_00f47380(void* pBuffer);        // 0x00f47380  operator delete
extern "C" void __cdecl FUN_00b5b6f0(void* pTicker);        // 0x00b5b6f0  ticker registration
extern "C" void __cdecl FUN_00b5b690(void* pTicker);        // 0x00b5b690  ticker base teardown
extern "C" long double __cdecl sqrtl(long double v);        // CRT sqrt, inlined to fsqrt

extern float  g_169fa68;      // 0x169fa68  zero vector x/y/z
extern float  g_169fa6c;      // 0x169fa6c
extern float  g_169fa70;      // 0x169fa70
extern uint8_t Vector3Equal(const float* a, const float* b);   // 0x004232c0 cdecl

// ---------- the polymorphic helper object at +0x34 -------------------------------------
class cTreeSub {
public:
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28();
  virtual float* v2c();                                  // 0x2c  world position
  virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
  virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
  virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
  virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
  virtual void v70();
  virtual long double v74();                             // 0x74  radius (x87)
  virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
  virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
  virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
  virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
  virtual void vb8(); virtual void vbc(); virtual void vc0(); virtual void vc4();
  virtual void vc8(); virtual void vcc(); virtual void vd0(); virtual void vd4();
  virtual void vd8(); virtual void vdc(); virtual void ve0(); virtual void ve4();
  virtual void ve8();
  virtual void vec();                                    // 0xec  path-failure notify
};

// ---------- star record (the entries collected for the vehicle tree) -------------------
class cStarEntry {
public:
  virtual void v00();
  virtual void v04();                                    // 0x04  Release
  virtual void v08();
  virtual void* v0c(uint32_t id);                        // 0x0c
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28();
  virtual float* v2c();                                  // 0x2c  world position
};

// eastl::vector<AutoRefCount<SP::cStarRecord>, sp_vector_allocator> (12 bytes)
struct cStarRecordVector {
  cStarEntry** mpBegin;      // +0x00
  cStarEntry** mpEnd;        // +0x04
  cStarEntry** mpCapacity;   // +0x08
  void Destroy();            // 0x00ae6970
};

// the vehicle object behind cPathState::mpObj (slot 0xb8 hands out the pilot sub-object)
class cStateObj;
class cVehicleSub {
public:
  virtual void v00(); virtual void v04(); virtual void v08();
  virtual cStateObj* v0c(uint32_t id);                   // 0x0c
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28();
  virtual char v2c();                                    // 0x2c
};

class cStateObj {
public:
  virtual void v00(); virtual void v04(); virtual void v08();
  virtual void* v0c(uint32_t id);                        // 0x0c
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28();
  virtual float* v2c();                                  // 0x2c  world position
  virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
  virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
  virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
  virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
  virtual void v70();
  virtual long double v74();                             // 0x74  radius (x87)
  virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
  virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
  virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
  virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
  virtual cVehicleSub* vb8(uint32_t id);                 // 0xb8
  virtual void vbc();
  virtual void vc0();                                    // 0xc0

  int32_t GetDamageState();                              // 0x008e7f80 thiscall
};

namespace SP {
  int32_t GetCurrentGameMode();                          // 0x00b5b800 cdecl
}

// the star-record source the tree queries (global 0x016c7aa4, collector at +0x74)
class cStarCollector {
public:
  void Collect(int32_t id, cStarRecordVector* pOut);     // 0x00f40d00 thiscall, ret 8
};

class cStarSource {
public:
  uint8_t pad00[0x74];
  cStarCollector* mp74;      // 0x74
};

extern cStarSource* g_16c7aa4;     // 0x016c7aa4

// state object hung off the tree ((*tree->GetState()) at 0x00c9f1c0)
struct cVehicleTreeState {
  uint8_t pad00[0x4b8];
  int32_t m4b8;              // 0x4b8
  uint8_t pad4bc[8];
  int32_t m4c4;              // 0x4c4
};

class cVehicleTree {
public:
  cVehicleTreeState* GetState();                         // 0x00c9f1c0
  uint8_t pad04[0x34];
  cTreeSub mSub34;                                       // 0x34
};

namespace SP { namespace VehicleTree {
  void* Idle_Activate(void* pTree);                      // 0x00dc77d0 cdecl
}}

// ---------- the path follower state ---------------------------------------------------
class cPathState {
public:
  void Assign(void* pEntry);                             // 0x00c70110
  cStateObj* mpObj;          // 0x00
  float      mF4;            // 0x04
  float      mF8;            // 0x08
  uint8_t    mFlagC;         // 0x0c
  uint8_t    pad0d[3];
  float      mPos10[3];      // 0x10
};

struct cPathSample {         // 5 floats passed by value to 0x00c9fb40
  float x, y, z, fR1, fR2;
};

class cPathTicker {
public:
  void AssignName(const char* pName);                    // 0x00ca7250 thiscall ret 4
  void FUN_00caa900();                                   // 0x00caa900 thiscall
  void FUN_00ca97a0(const float* pPos, float fA, float fB);// 0x00ca97a0 thiscall ret 0xc
  void FUN_00c9fb40(cPathSample s);                      // 0x00c9fb40 thiscall ret 0x14

  uint8_t  pad00[0x34];
  cTreeSub mSub34;                                       // 0x34
  uint8_t  pad38[0x2a4 - 0x38];
  uint8_t  mFlags2a4;                                    // 0x2a4
};

// ---------- the vehicle ticker (singleton at 0x01699ab8) ------------------------------
class cSimBase {
public:
  cSimBase();                                            // 0x00b5b6c0
};

struct cGroupOrderVector {   // eastl::vector<AutoRefCount<cVehicleGroupOrder>>
  void* mpBegin;             // +0x00
  void* mpEnd;               // +0x04
  void* mpCapacity;          // +0x08
  void Destroy();            // 0x00ae6970
};

struct cSpatialVector {      // eastl::vector<AutoRefCount<cSpatialObject>>
  void* mpBegin;             // +0x00
  void* mpEnd;               // +0x04
  void* mpCapacity;          // +0x08
  void Destroy();            // 0x00ad92d0
};

class cVehicleTicker : public cSimBase {
public:
  cVehicleTicker();                                      // 0x00dc7d70
  void Destroy();                                        // 0x00dc7cc0

  void* volatile mpVt00;     // 0x00
  uint32_t pad04;            // 0x04
  void* volatile mpVt08;     // 0x08
  uint32_t pad0c;            // 0x0c
  cGroupOrderVector mGroupOrders;   // 0x10
  uint8_t pad1c[8];          // 0x1c
  cSpatialVector mVoxSoundIds;      // 0x24
  uint8_t pad30[8];          // 0x30
  cSpatialVector m38;        // 0x38
};

extern cVehicleTicker* g_1699ab8;    // 0x01699ab8

// @ 0x00dc77d0
void* SP::VehicleTree::Idle_Activate(void* pTree) {
  cVehicleTree* pThis = (cVehicleTree*)pTree;
  int32_t id = pThis->GetState()->m4c4;
  if (id == -1)
    return 0;

  cStarRecordVector vec;
  vec.mpBegin = 0;
  vec.mpEnd = 0;
  vec.mpCapacity = 0;
  g_16c7aa4->mp74->Collect(id, &vec);
  if (vec.mpBegin == vec.mpEnd) {
    vec.Destroy();
    return 0;
  }

  float* pRef = pThis->mSub34.v2c();
  float fRefX = pRef[0];
  float fRefY = pRef[1];
  float fRefZ = pRef[2];
  int32_t nCount = (int32_t)(vec.mpEnd - vec.mpBegin);
  cStarEntry* pBest = 0;
  float fBest = 3.402823466e+38F;
  for (int32_t i = 0; i < nCount; ++i) {
    cStarEntry* pEntry = vec.mpBegin[i];
    if (pEntry != 0) {
      cStarEntry* pObj = (cStarEntry*)pEntry->v0c(0x1186577);
      if (pObj != 0) {
        float* pPos = pObj->v2c();
        float fDist = (pPos[1] - fRefY) * (pPos[1] - fRefY)
                    + (pPos[2] - fRefZ) * (pPos[2] - fRefZ)
                    + (pPos[0] - fRefX) * (pPos[0] - fRefX);
        if (fDist < fBest) {
          fBest = fDist;
          pBest = pObj;
        }
      }
    }
  }
  for (cStarEntry** pp = vec.mpBegin; pp < vec.mpEnd; ++pp) {
    if (*pp != 0)
      (*pp)->v04();
  }
  if (vec.mpBegin != 0 && ((int32_t*)vec.mpBegin)[-1] != 0)
    FUN_00f47380(vec.mpBegin);
  return pBest;
}

// @ 0x00dc7940
long double FUN_00dc7940(cVehicleTree* pTree) {
  if (pTree->GetState()->m4b8 == 5) {
    if (SP::VehicleTree::Idle_Activate(pTree) != 0)
      return 1.0;
  }
  return 0.0;
}

// @ 0x00dc7970
bool FUN_00dc7970(cPathTicker* pTicker, int32_t, int32_t, int32_t, int32_t,
                  cPathState* pState, int32_t, float fDelta) {
  SP::GetCurrentGameMode();
  if ((pTicker->mFlags2a4 & 8) != 0) {
    pTicker->AssignName("(22) Vehicle Movement Tracking : path failure");
    pTicker->FUN_00caa900();
    return false;
  }

  pState->mF4 += fDelta;
  pState->mF8 += fDelta;
  if (pState->mpObj != 0) {
    cVehicleSub* pObj = pState->mpObj->vb8(0x17f243b);
    if (pObj->v2c()) {
      cStateObj* pOld = pState->mpObj;
      if (pOld != 0) {
        pState->mpObj = 0;
        pOld->vc0();
      }
    } else {
      cStateObj* pCombatant = pObj->v0c(0x13f94d4);
      if (pCombatant != 0 && pCombatant->GetDamageState() == 2) {
        cStateObj* pOld = pState->mpObj;
        if (pOld != 0) {
          pState->mpObj = 0;
          pOld->vc0();
        }
        pTicker->mSub34.vec();
        pState->mFlagC = 1;
      }
    }
  }

  if (pState->mF4 > 2.0f) {
    cStarEntry* pEntry = (cStarEntry*)SP::VehicleTree::Idle_Activate(pTicker);
    if (pEntry != 0 && pEntry != (cStarEntry*)pState->mpObj) {
      if (pState->mpObj == 0) {
        pState->Assign(pEntry);
      } else {
        float* pTreePos = pTicker->mSub34.v2c();
        float* pPos = pEntry->v2c();
        float fDX = pPos[0] - pTreePos[0];
        float fDY = pPos[1] - pTreePos[1];
        float fDZ = pPos[2] - pTreePos[2];
        float fDist = fDX * fDX + fDY * fDY + fDZ * fDZ;
        if (sqrtl(fDist) < 32.0f)
          pState->Assign(pEntry);
      }
    }
    pState->mF4 = 0.0f;
  }

  if (pState->mpObj != 0 && pState->mF8 > 1.0f) {
    float* pObjPos = pState->mpObj->v2c();
    float fOwn = (float)pState->mpObj->v74();
    float fSum = (float)(pTicker->mSub34.v74() + fOwn);
    float* pTreePos = pTicker->mSub34.v2c();
    float fX = pObjPos[0];
    float fY = pObjPos[1];
    float fZ = pObjPos[2];
    float fDX = fX - pTreePos[0];
    float fDY = fY - pTreePos[1];
    float fDZ = fZ - pTreePos[2];
    float fDist = fDX * fDX + fDY * fDY + fDZ * fDZ;
    if (sqrtl(fDist) - fSum < 4.0f) {
      if (pState->mFlagC == 0) {
        pTicker->mSub34.vec();
        pState->mFlagC = 1;
      }
    } else if (Vector3Equal(&pState->mPos10[0], &g_169fa68)) {
      pState->mPos10[0] = fX;
      pState->mPos10[1] = fY;
      pState->mPos10[2] = fZ;
      pTicker->FUN_00ca97a0(pObjPos, fSum + 4.0f, 0.0f);
      cPathSample sample;
      sample.x = fX;
      sample.y = fY;
      sample.z = fZ;
      sample.fR1 = fSum;
      sample.fR2 = fSum + 8.0f;
      pTicker->FUN_00c9fb40(sample);
      pState->mFlagC = 0;
    } else {
      float fDZ2 = fZ - pState->mPos10[2];
      float fDY2 = fY - pState->mPos10[1];
      float fDX2 = fX - pState->mPos10[0];
      float fDist2 = fDZ2 * fDZ2 + fDY2 * fDY2 + fDX2 * fDX2;
      if (fDist2 > 256.0f) {
        pState->mPos10[0] = g_169fa68;
        pState->mPos10[1] = g_169fa6c;
        pState->mPos10[2] = g_169fa70;
      }
    }
    pState->mF8 = 0.0f;
  }
  return true;
}

// @ 0x00dc7cc0
void cVehicleTicker::Destroy() {
  cSpatialVector* pVec38 = &m38;
  mpVt00 = (void*)0x0147c4d8;
  mpVt08 = (void*)0x0147c4b4;
  pVec38->Destroy();
  if (mVoxSoundIds.mpBegin != 0 && ((int32_t*)mVoxSoundIds.mpBegin)[-1] != 0)
    FUN_00f47380(mVoxSoundIds.mpBegin);
  mGroupOrders.Destroy();
  mpVt00 = (void*)0x0147c468;
  mpVt08 = (void*)0x0147c444;
  FUN_00b5b690(this);
  if (g_1699ab8 == this)
    g_1699ab8 = 0;
  mpVt00 = (void*)0x013ec458;
  mpVt08 = (void*)0x013eb938;
}

// @ 0x00dc7d70
cVehicleTicker::cVehicleTicker() {
  mpVt00 = (void*)0x0147c468;
  mpVt08 = (void*)0x0147c444;
  g_1699ab8 = this;
  FUN_00b5b6f0(this);
  mpVt00 = (void*)0x0147c4d8;
  mpVt08 = (void*)0x0147c4b4;
  mGroupOrders.mpBegin = 0;
  mGroupOrders.mpEnd = 0;
  mGroupOrders.mpCapacity = 0;
  mVoxSoundIds.mpBegin = 0;
  mVoxSoundIds.mpEnd = 0;
  mVoxSoundIds.mpCapacity = 0;
  m38.mpBegin = 0;
  m38.mpEnd = 0;
  m38.mpCapacity = 0;
}

// @ 0x00dc7dd0
void cConvertCityOrder5::FUN_00dc7dd0(cSrc5* src) {
  mSub64.SetFrom(src);
  cMgr5* mgr = (cMgr5*)FUN_00b3d290();
  mGen90 = mgr->Get();
}
