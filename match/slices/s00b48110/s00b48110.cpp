// s00b48110 -- SP simulator / Havok world helpers around 0x00b48xxx.
//
// Reconstructed from the disassembly in work/match/scratch_s00b48110_cards.txt.
// MSVC 2008 SP1, /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <math.h>
#include <intrin.h>

typedef unsigned int  uint;
typedef unsigned char uchar;

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------------------
// module globals
// ---------------------------------------------------------------------------
extern uint  g_167ecc0;      // 0x0167ecc0  "useGameplayPhantom" once-guard
extern uint  g_167ecbc;      // 0x0167ecbc  cached FNV hash
extern float g_167eb8c;      // 0x0167eb8c  zero vector x
extern float g_167eb90;      // 0x0167eb90  zero vector y
extern float g_167eb94;      // 0x0167eb94  zero vector z
extern float g_146113c;      // 0x0146113c  +1e20f
extern float g_14611c0;      // 0x014611c0  -1e20f
extern float g_1461154;      // 0x01461154  squared-length epsilon
extern int   g_1569a88;      // 0x01569a88  per-tick object budget (game mode A)
extern char  g_1601760;      // 0x01601760  random LCG instance

// ---------------------------------------------------------------------------
// tracked objects: everything here only needs a handful of vtable slots
// ---------------------------------------------------------------------------
struct cGameObject {
    char  mPad00[0x75];                                          // +0x00
    uchar mFlag76;                                               // +0x76
    char  mPad77[0x50];                                          // +0x77
};

// syntax pass: calls the Update slot through the object's own vtable, exactly
// like the direct call above but emitting this-in-ecx (LOAD_OBJ, no signature
// lookup means no extra push).
struct cUpdateObjRef { char mPad[0x100]; void Update(); };
extern "C" void UpdateObjRef(void* p);

// ---------------------------------------------------------------------------
// cGameObject vtable slots (vtable at 0x00a01b20); one entry per slot in
// address order, annotated with its offset.
// ---------------------------------------------------------------------------
struct cGameVtbl {
    void (*v00)();
    void (*v04)();
    void (*v08)();
    cGameObject* (*GetSubTag)(void* pThis, uint id);               // +0x0c
    void (*v10)();
    void (*v14)();
    void (*v18)();
    void (*v1c)();
    uint (*GetId)(void* pThis);                                    // +0x20
    void (*v24)();
    void (*v28)();
    void (*v2c)();
    void (*v30)();
    void (*v34)();
    void (*v38)();
    void (*v3c)();
    void (*v40)();
    void (*v44)();
    void (*v48)();
    void (*v4c)();
    void (*v50)();
    void (*v54)();
    void (*v58)();
    void (*v5c)();
    void (*v60)();
    void (*v64)();
    void (*v68)();
    void (*v6c)();
    void (*v70)();
    void (*v74)();
    void (*v78)();
    void (*v7c)();
    void (*v80)();
    void (*v84)();
    void (*v88)();
    void (*v8c)();
    void (*v90)();
    void (*v94)();
    void (*v98)();
    void (*v9c)();
    void (*va0)();
    void (*va4)();
    void (*va8)();
    void (*vac)();
    void (*vb0)();
    void (*vb4)();
    void (*vb8)();
    void (*AddRef)(void* pThis);                                   // +0xbc
    void (*Release)(void* pThis);                                  // +0xc0
    void (*vc4)();
    void (*vc8)();
    void (*vcc)();
    void (*vd0)();
    void (*vd4)();
    void (*vd8)();
    void (*vdc)();
    void (*ve0)();
    void (*ve4)();
    void (*ve8)();
    void (*vec)();
    void (*Update)(void* pThis);                                   // +0xf0
};

inline void* vtOf(cGameObject* p) { return *(void**)p; }

inline void   vtAddRef(cGameObject* p)            { ((cGameVtbl*)vtOf(p))->AddRef(p); }
inline void   vtRelease(cGameObject* p)           { ((cGameVtbl*)vtOf(p))->Release(p); }
inline void   vtUpdate(cGameObject* p)            { ((cGameVtbl*)vtOf(p))->Update(p); }
inline cGameObject* vtGetSubTag(cGameObject* p, uint id)
                                                  { return ((cGameVtbl*)vtOf(p))->GetSubTag(p, id); }
inline uint   vtGetId(cGameObject* p)             { return ((cGameVtbl*)vtOf(p))->GetId(p); }

// object sampled by the steering clip helper
struct cSurfaceObj {
    char  mPad00[0x0c];
    int   mKind;                                                 // +0x0c
    Vec3* FUN_00b3da90(Vec3* pOut, int nIndex, cSurfaceObj* pOther);  // 0x00b3da90
};

// iterator produced by the world record hashtable (0x00b45b50 / 0x00645ed0)
struct cIter { void* mpNode; void* mpBucket; uchar mInserted; };

// eastl hashtable header (instances at +0x58 and +0x47c of the world)
struct cRecordMap {
    char   mPad00[4];
    void** mpBuckets;                                            // +0x04
    uint   mCount;                                               // +0x08
    void*  mpField0c;                                            // +0x0c
    void Insert(cIter* pOut, void** ppKey, bool bFlag);          // 0x00b45b50
    void find(cIter* pOut, const uint* pKey);                    // 0x00645ed0
};

struct cIceEntry { int mField0; float mValue; };                 // 8 byte entries

// The simulation service pointed at by 0x0167eae8; `this` for the functions here.
struct cSim {
    uchar  mClipFlag;                                            // +0x00
    char   mPad01[0x1f];                                         // +0x01
    int    mMode;                                                // +0x20
    char   mPad24[0x3c];                                         // +0x24
    cGameObject** mpObjBegin;                                    // +0x60
    cGameObject** mpObjEnd;                                      // +0x64
    char   mPad68[0x410];                                        // +0x68
    int    mObjIndex;                                            // +0x478
    cRecordMap mRecords;                                         // +0x47c

    void* GetMsgSource(uint id);                                 // 0x00b532f0
    void  FUN_00b5a260(cGameObject* p2, cGameObject* p3);        // 0x00b5a260
    void  Fn_00b48770(cGameObject* pObj, bool bFlag);            // 0x00b48770
    void  Fn_00b48920();                                         // 0x00b48920
    bool  Fn_00b489d0(cSurfaceObj* pA, cSurfaceObj* pB, Vec3* pNormal,
                      float fLimit, float* pOutT, Vec3* pOutVec); // 0x00b489d0
    bool  Clip(void* pBoxA, void* pBoxB, Vec3* pNormal, Vec3* pV,
               float fDistance, Vec3* pBest, uchar* pMask,
               float* pMin, float* pMax, Vec3* pNegDir, Vec3* pPosDir); // 0x00b47200
};

// object the simulation keeps in its round-robin list (distinct class so that
// its virtual Update keeps the original this-in-ecx call shape).
struct cUpdateObj {
    char  mPad00[0x76];                                          // +0x00
    uchar mFlag76;                                               // +0x76
    void  Update();                                              // vtable +0xf0
};

// The game/collision world object pointed at by 0x0167eb70.
struct cWorldObj {
    char   mPad00[0x58];                                         // +0x00
    cRecordMap mMap58;                                           // +0x58
    char   mPad68[0x10];                                         // +0x68
    cIceEntry* mpIceBegin;                                       // +0x78
    cIceEntry* mpIceEnd;                                         // +0x7c
};

extern cSim* g_sim;                                              // 0x0167eae8
extern cWorldObj* g_167eb70;                                     // 0x0167eb70

// ---------------------------------------------------------------------------
// free callees
// ---------------------------------------------------------------------------
extern void* __cdecl FUN_00b5b800();                                    // GetCurrentGameMode
extern void* __cdecl FUN_00b41ee0(void* a, void* b);
extern char  __cdecl FUN_0064f350(void* pNode, uint key, int flag);
extern uint  __cdecl FUN_00932e80(const char* s, uint seed, int c);
extern void  __cdecl FUN_00b539e0(void* p);
extern void  __cdecl FUN_00b43710(void* p);
extern void  __cdecl FUN_00b47ee0(void* p);
extern void  __cdecl FUN_00b475b0(void** pBegin, void** pEnd, void* pRandom);
extern void* __cdecl FUN_00c83c90(cGameObject** pFirst, cGameObject** pLast,
                                  cGameObject** pDst);
extern void  __cdecl FUN_00b47600(void* pWhere, void* pValue);

static const int& Min(const int& a, const int& b) { return a < b ? a : b; }

static int SampleCount(int k)
{
    int n;
    if (k < 0)
        n = 0;
    else if (k <= 1)
        n = 1;
    else if (k == 2)
        n = 3;
    else
        n = 0;
    return n;
}

// ---------------------------------------------------------------------------
// 0x00b48770 -- (de)register one object with the phantom/collision world
// ---------------------------------------------------------------------------
// @ 0x00b48770
void cSim::Fn_00b48770(cGameObject* pObj, bool bFlag)
{
    cGameObject* pRec;

    if (pObj) {
        pRec = vtGetSubTag(pObj, 0x0116dd1b);
        if (pRec) {
            cGameObject** pEnd = mpObjEnd;
            cGameObject** p = mpObjBegin;
            while (p != pEnd && *p != pRec)
                ++p;
            if (p == pEnd)
                return;
        }
    } else {
        pRec = 0;
    }

    if ((g_167ecc0 & 1) == 0) {
        g_167ecc0 |= 1;
        g_167ecbc = FUN_00932e80("useGameplayPhantom", 0x811c9dc5u, 1);
    }

    uint  id    = vtGetId(pObj);
    void* key   = GetMsgSource(id);
    void* pNode = FUN_00b41ee0(pObj, key);
    if (!pNode)
        return;
    if (!FUN_0064f350(pNode, 0xcf3b981du, 1) &&
        !FUN_0064f350(pNode, g_167ecbc, 0))
        return;

    cGameObject* pStored = vtGetSubTag(pObj, 0x01186577);
    if (!pStored)
        return;

    if (!pRec) {
        vtAddRef(pStored);
        cIter it;
        bool  bInserted = false;
        mRecords.Insert(&it, (void**)&pStored, bInserted);
        if (pStored)
            vtRelease(pStored);
    }

    if (mMode == 0) {
        if (bFlag)
            FUN_00b5a260(pStored, pRec);
        else
            FUN_00b539e0(pStored);
    } else if (mMode == 1) {
        cIter it;
        uint  mapKey = (uint)pStored;
        g_167eb70->mMap58.find(&it, &mapKey);
        if (it.mpNode != g_167eb70->mMap58.mpBuckets[g_167eb70->mMap58.mCount]) {
            FUN_00b43710(pStored);
            FUN_00b47ee0(pStored);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00b48920 -- advance the round-robin object update cursor
// ---------------------------------------------------------------------------
// @ 0x00b48920
void cSim::Fn_00b48920()
{
    int  nAmount = (FUN_00b5b800() == (void*)0x01654c10) ? g_1569a88 : 10;
    int  nCur    = mObjIndex;
    int  nTarget = nCur + nAmount;
    int  nCount  = (int)(mpObjEnd - mpObjBegin);
    int  nLimit  = Min(nTarget, nCount);

    while (mObjIndex < nLimit) {
        cUpdateObj* p = (cUpdateObj*)mpObjBegin[mObjIndex];
        if (p->mFlag76)
            p->Update();
        ++mObjIndex;
    }

    int nFinal = (int)(mpObjEnd - mpObjBegin);
    if (nLimit == nFinal) {
        _ReadWriteBarrier();
        mObjIndex = 0;
        FUN_00b475b0((void**)mpObjBegin, (void**)mpObjEnd, &g_1601760);
    }
}

// ---------------------------------------------------------------------------
// 0x00b489d0 -- sampled slab clip between two surface objects
// ---------------------------------------------------------------------------
// @ 0x00b489d0
bool cSim::Fn_00b489d0(cSurfaceObj* pA, cSurfaceObj* pB, Vec3* pNormal,
                         float fLimit, float* pOutT, Vec3* pOutVec)
{
    int  kindA = pA->mKind;
    int  kindB = pB->mKind;

    Vec3 vBest;
    vBest.x = g_146113c;
    vBest.y = g_146113c;
    vBest.z = g_146113c;
    bool bMask = true;

    int nA1 = SampleCount(kindA);
    int nB1 = SampleCount(kindB);
    int nA2 = SampleCount(kindA);
    int nB2 = SampleCount(kindB);

    *pOutT = fLimit;
    float fMin = g_14611c0;
    float fMax = g_146113c;
    Vec3  vNeg;
    vNeg.x = g_167eb8c;
    vNeg.y = g_167eb90;
    vNeg.z = g_167eb94;
    Vec3  vPos;
    vPos.x = g_167eb8c;
    vPos.y = g_167eb90;
    vPos.z = g_167eb94;
    Vec3  vDir;
    Vec3  vSampleA;
    Vec3  vSampleB;

    for (int i = 0; i < nA1; ++i) {
        pA->FUN_00b3da90(&vDir, i, pB);
        if (!Clip(pA, pB, pNormal, &vDir, 1.0f, &vBest, (uchar*)&bMask,
                  &fMin, &fMax, &vNeg, &vPos))
            return false;
    }

    for (int i = 0; i < nB1; ++i) {
        pB->FUN_00b3da90(&vDir, i, pB);
        if (!Clip(pA, pB, pNormal, &vDir, 1.0f, &vBest, (uchar*)&bMask,
                  &fMin, &fMax, &vNeg, &vPos))
            return false;
    }

    for (int i = 0; i < nA2; ++i) {
        for (int j = 0; j < nB2; ++j) {
            Vec3* pvA = pB->FUN_00b3da90(&vSampleA, j, pA);
            Vec3* pvB = pA->FUN_00b3da90(&vSampleB, i, pB);
            vDir.x = pvA->z * pvB->y - pvA->y * pvB->z;
            vDir.z = pvB->x * pvA->y - pvA->x * pvB->y;
            vDir.y = pvA->x * pvB->z - pvB->x * pvA->z;
            float len2 = vDir.z * vDir.z + vDir.y * vDir.y + vDir.x * vDir.x;
            if (len2 >= g_1461154) {
                if (!Clip(pA, pB, pNormal, &vDir, len2, &vBest, (uchar*)&bMask,
                          &fMin, &fMax, &vNeg, &vPos))
                    return false;
            }
        }
    }

    if (fMin > fLimit || fMax < 0.0f)
        return false;

    if (mClipFlag) {
        if (fMin > 0.0f) {
            *pOutT = fMin;
            *pOutVec = vNeg;
        } else {
            if (!bMask)
                return false;
            *pOutT = 0.0f;
            *pOutVec = vBest;
        }
    } else {
        if (fabsf(fMax) < fabsf(fMin)) {
            *pOutT = fMax;
            *pOutVec = vPos;
        } else {
            *pOutT = fMin;
            *pOutVec = vNeg;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00b48e00 -- SteerVec::push_back (default 0x2c-byte node, field +4 = 1)
// ---------------------------------------------------------------------------
struct SteerNode {
    char mPad00[4];
    int  mField04;                                               // +0x04
    char mPad08[0x24];                                           // +0x08
};

struct SteerVec {
    SteerNode* mpBegin;                                          // +0x00
    SteerNode* mpEnd;                                            // +0x04
    SteerNode* mpCap;                                            // +0x08
    void push_back();                                            // 0x00b48e00
    void DoInsertValue(SteerNode* pWhere, SteerNode* pValue);    // 0x00b47600
};

// @ 0x00b48e00
void SteerVec::push_back()
{
    if (mpEnd < mpCap) {
        SteerNode* p = mpEnd;
        mpEnd = p + 1;
        if (p)
            p->mField04 = 1;
    } else {
        SteerNode tmp;
        tmp.mField04 = 1;
        DoInsertValue(mpEnd, &tmp);
    }
}

// ---------------------------------------------------------------------------
// 0x00b48e40 -- eastl::vector<AutoRefCount<cSpatialObject>>::erase(first,last)
// ---------------------------------------------------------------------------
struct cSpatialVec {
    cGameObject** mpBegin;                                       // +0x00
    cGameObject** mpEnd;                                         // +0x04
    cGameObject** mpCap;                                         // +0x08
    void erase(cGameObject** pFirst, cGameObject** pLast);       // 0x00b48e40
};

// @ 0x00b48e40
void cSpatialVec::erase(cGameObject** pFirst, cGameObject** pLast)
{
    cGameObject** pLastArg = pLast;
    cGameObject** p = (cGameObject**)FUN_00c83c90(pLastArg, mpEnd, pFirst);
    cGameObject** pEnd = mpEnd;
    for (; p < pEnd; ++p) {
        if (*p)
            vtRelease(*p);
    }
    mpEnd -= (pLastArg - pFirst);
}

// ---------------------------------------------------------------------------
// 0x00b48ea0 -- decay the world ice layer entries by dt, dropping dead ones
// ---------------------------------------------------------------------------
// @ 0x00b48ea0
void __cdecl FUN_00b48ea0(float dt)
{
    cIceEntry* it = g_167eb70->mpIceBegin;
    cIceEntry* p  = it + 1;
    if (it != g_167eb70->mpIceEnd) {
        do {
            _ReadWriteBarrier();
            it->mValue -= dt;
            if (it->mValue <= 0.0f) {
                cIceEntry* pEnd = g_167eb70->mpIceEnd;
                cIceEntry* s = p;
                while (s != pEnd) {
                    s[-1] = *s;
                    ++s;
                }
                --g_167eb70->mpIceEnd;
            } else {
                ++it;
                ++p;
            }
        } while (it != g_167eb70->mpIceEnd);
    }
}

// ===========================================================================
// 0x00b48110 -- Steering::Update
//
// Recomputes the steering velocity written at state+0x00. While the object is
// not grounded (byte +0x77) it forwards its own velocity and aligns its
// orientation to the surface; otherwise it consumes the current locomotion
// request: walk toward the next waypoint projected on the planet surface,
// brake / re-request when the waypoint is reached and hand the result to the
// aim-slope follower (0x00b46df0) which returns the fraction of the requested
// speed actually applied.
// ===========================================================================
#pragma intrinsic(sqrt)

extern const float g_1488874;    // 0x01488874  0.1f
extern const float g_13eb8a0;    // 0x013eb8a0  0.25f
extern const float g_13f7344;    // 0x013f7344  0.95f
extern const float g_1470f1c;    // 0x01470f1c  2.0f
extern const float g_1471064;    // 0x01471064  0.5f

extern void __cdecl operator_delete__(void* p);                  // 0x00f47380

struct Quat { float x, y, z, w; };

struct Waypoint { float f[15]; };                                 // 0x3c bytes

// locomotion request (0x74 bytes): waypoint vector plus goal data
struct cLocomotionRequest {
    Waypoint* mpBegin;                                           // +0x00
    Waypoint* mpEnd;                                             // +0x04
    char      mPad08[0x14 - 0x08];                               // +0x08
    Vec3      mDst;                                              // +0x14 (head of the 0x3c-byte
                                                                 //       current waypoint)
    float     mGoalStopDistance;                                 // +0x20
    char      mPad24[0x50 - 0x24];                               // +0x24
    Vec3      mField50;                                          // +0x50 reference direction
    int       mType;                                             // +0x5c (0 none, 1/3 follow, 2 hold)
    float     mAcceptableStopDistance;                           // +0x60
    float     mField64;                                          // +0x64 alignment threshold
    float     mPrevDistance;                                     // +0x68
    float     mElapsed;                                          // +0x6c
    int       mField70;                                          // +0x70

    cLocomotionRequest();                                        // 0x00ac9850
    cLocomotionRequest(const cLocomotionRequest& o);             // 0x00b46d90 (ret 4)
    void EraseWaypoint(const Waypoint* pWhere);                  // 0x00b47520 (ret 4)
    ~cLocomotionRequest()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};

// locomotive driven by the steering step
class cSteerLoco {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual const Vec3* GetPosition();                           // +0x2c
    virtual Quat* GetOrientation();                              // +0x30
    virtual void v0d(); virtual void v0e();                      // +0x34 +0x38
    virtual void SetOrientation(const Quat* pQ);                 // +0x3c
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16();  // +0x40 .. +0x58
    virtual const Vec3* GetDirection(Vec3* pOut);                // +0x5c
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d();                      // +0x60 .. +0xb4
    virtual void FnB8(const void* pArg);                         // +0xb8
    virtual void v2f(); virtual void v30();                      // +0xbc +0xc0
    virtual void SetDesiredSpeed(float fSpeed, int nFlag);       // +0xc4
    virtual float GetDesiredSpeed();                             // +0xc8
    virtual void v33();                                          // +0xcc
    virtual float FnD0();                                        // +0xd0
    virtual void v35(); virtual void v36();                      // +0xd4 +0xd8
    virtual void SetRequest(const cLocomotionRequest& r);        // +0xdc

    char  mPad04[0x77 - 0x04];                                   // +0x04
    uchar mFlag77;                                               // +0x77
    char  mPad78[0x1e8 - 0x78];                                  // +0x78
    float mTurnRate;                                             // +0x1e8

    Vec3* GetVelocity();                                         // 0x00d20610
    void  GetSteerDirection(Vec3* pOut);                         // 0x00c44080
    cLocomotionRequest* GetRequest();                            // 0x00c41ec0
};

// steering state written by Update
struct cSteerState {
    Vec3        mVelocity;                                       // +0x00
    char        mPad0c[0x10 - 0x0c];                             // +0x0c
    float       mDt;                                             // +0x10
    cSteerLoco* mpObject;                                        // +0x14
};

struct cPlanetModel {
    Quat* BuildSurfaceOrientation2(Quat* pOut, const Vec3* pPos, const Vec3* pUp);  // 0x00b7f250 ret 0xc
    Vec3* DirectionToSurfacePosition(Vec3* pOut, const Vec3* pDir);                 // 0x00b815a0 ret 8
};

extern cPlanetModel* __cdecl PlanetModel();                      // 0x00b3d350
extern Vec3* __cdecl NormalizedSafe(Vec3* pOut, const Vec3* pIn);// 0x00449c20
extern Quat __cdecl Slerp(const Quat& a, const Quat& b, float t); // 0x005b2500
extern float __stdcall Fn_00b46df0(cSteerLoco* pObj, const Vec3* pTarget, float dt, float fSpeed, float fTurn);  // 0x00b46df0

struct Steering {
    void Update(cSteerState* pState);                            // 0x00b48110 (ret 4)
};

// @ 0x00b48110
void Steering::Update(cSteerState* pState)
{
    pState->mpObject->FnD0();
    pState->mpObject->GetVelocity();
    pState->mpObject->FnB8((const void*)0x0137e8e0);

    Vec3 vDir;
    pState->mpObject->GetSteerDirection(&vDir);
    float fLen = (float)sqrt(vDir.x * vDir.x + vDir.y * vDir.y + vDir.z * vDir.z);
    if (g_1461154 <= fLen) {
        float fInv = 1.0f / fLen;
        vDir.x = fInv * vDir.x;
        vDir.y = vDir.y * fInv;
        vDir.z = vDir.z * fInv;
    } else {
        Vec3 vTmp;
        const Vec3* pv = pState->mpObject->GetDirection(&vTmp);
        vDir.x = pv->x * g_1488874;
        vDir.y = pv->y * g_1488874;
        vDir.z = pv->z * g_1488874;
    }

    const Vec3* pp = pState->mpObject->GetPosition();
    Vec3 vPos;
    vPos.x = pp->x;
    vPos.y = pp->y;
    vPos.z = pp->z;
    Vec3 vUp;
    pState->mpObject->GetDirection(&vUp);
    float fSpeed = pState->mpObject->GetDesiredSpeed();
    float fTurn  = pState->mpObject->mTurnRate;
    cLocomotionRequest* pReq = pState->mpObject->GetRequest();
    cPlanetModel* pPlanet = PlanetModel();

    int   nType = pReq->mType;
    float fDist;
    if (nType == 0) {
        fDist = 0.0f;
    } else {
        float dz = vPos.z - pReq->mDst.z;
        float dy = vPos.y - pReq->mDst.y;
        float dx = vPos.x - pReq->mDst.x;
        fDist = (float)sqrt(dz * dz + dy * dy + dx * dx);
    }

    if (pState->mpObject->mFlag77 == 0) {
        const Vec3* pv = pState->mpObject->GetVelocity();
        pState->mVelocity = *pv;
        const Vec3* pPos = pState->mpObject->GetPosition();
        Vec3 vGround;
        pState->mpObject->GetDirection(&vGround);
        Quat q;
        pPlanet->BuildSurfaceOrientation2(&q, pPos, &vGround);
        q = Slerp(*pState->mpObject->GetOrientation(), q, pState->mDt);
        pState->mpObject->SetOrientation(&q);
        return;
    }

    float fGoalStop = pReq->mGoalStopDistance;
    bool  notHold3  = nType != 3;
    bool  bStop     = false;
    if (nType == 0) {
        fSpeed = 0.0f;
    } else if (nType != 2) {
        bool bProgressed;
        if (fDist < pReq->mPrevDistance) {
            bProgressed = false;
        } else {
            float fElapsed = pState->mDt + pReq->mElapsed;
            pReq->mElapsed = fElapsed;
            bProgressed = true;
            if (g_13eb8a0 < fElapsed) {
                Vec3 vSurf;
                Vec3* pv = pPlanet->DirectionToSurfacePosition(&vSurf, &pReq->mDst);
                pReq->mDst = *pv;
            }
        }
        if (fGoalStop > fDist) {
            bStop = true;
        } else if (pState->mDt * fSpeed < fDist) {
            if (bProgressed && fDist < pReq->mAcceptableStopDistance)
                bStop = true;
        } else {
            fSpeed = (fDist / pState->mDt) * g_13f7344;
        }
        pReq->mPrevDistance = fDist;
        if (bStop) {
            if (pReq->mpBegin == pReq->mpEnd) {
                fSpeed = 0.0f;
            } else {
                pReq->mElapsed = 0.0f;
                Waypoint* pFirst = pReq->mpBegin;
                *(Waypoint*)&pReq->mDst = *pFirst;
                pReq->EraseWaypoint(pFirst);
                bStop = false;
            }
        }
    }

    if (nType != 0 && fDist < (fSpeed / fTurn) * g_1470f1c) {
        Vec3 vDelta;
        vDelta.x = pReq->mDst.x - vPos.x;
        vDelta.y = pReq->mDst.y - vPos.y;
        vDelta.z = pReq->mDst.z - vPos.z;
        Vec3 vNorm;
        const Vec3* pn = NormalizedSafe(&vNorm, &vDelta);
        float fDot = pn->y * vUp.y + pn->z * vUp.z + pn->x * vUp.x;
        if (fDot < g_1471064) {
            float fCap = (fDist * fTurn) * g_1471064;
            const float* pf = &fCap;
            if (fSpeed <= fCap)
                pf = &fSpeed;
            fSpeed = *pf;
        }
    }

    Vec3 vTarget;
    vTarget.x = vPos.x + vDir.x;
    vTarget.y = vPos.y + vDir.y;
    vTarget.z = vPos.z + vDir.z;
    float fAmount = Fn_00b46df0(pState->mpObject, &vTarget, pState->mDt, fSpeed, fTurn);
    if (fAmount > 0.0f) {
        pState->mVelocity.x = vDir.x * fSpeed;
        pState->mVelocity.y = vDir.y * fSpeed;
        pState->mVelocity.z = vDir.z * fSpeed;
    } else {
        pState->mVelocity.x = 0.0f;
        pState->mVelocity.y = 0.0f;
        pState->mVelocity.z = 0.0f;
    }

    if (!notHold3) {
        Vec3 vTmp;
        const Vec3* pv = pState->mpObject->GetDirection(&vTmp);
        float fAlign = pv->z * pReq->mField50.z
                     + pv->y * pReq->mField50.y
                     + pv->x * pReq->mField50.x;
        notHold3 = true;
        if (!(fAlign > pReq->mField64))
            notHold3 = false;
    }

    if (bStop) {
        if (notHold3) {
            {
                cLocomotionRequest goal;
                pState->mpObject->SetRequest(goal);
            }
            pState->mpObject->SetDesiredSpeed(0.0f, 1);
            pState->mVelocity.x = 0.0f;
            pState->mVelocity.y = 0.0f;
            pState->mVelocity.z = 0.0f;
        } else {
            {
                cLocomotionRequest goal(*pState->mpObject->GetRequest());
                goal.mDst = vPos;
                pState->mpObject->SetRequest(goal);
            }
        }
    }
}
