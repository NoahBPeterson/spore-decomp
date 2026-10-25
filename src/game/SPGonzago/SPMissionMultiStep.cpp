// src/game/SPGonzago/SPMissionMultiStep.cpp -- migrated from slice(s) s00c5a580, s00c59540 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionMultiStep.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCivData.h"
#include "SP/cEmpire.h"
#include "SP/cGameData.h"
#include "SP/cSPMission.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"
#pragma warning(disable: 4100)

// ---- items of slice s00c59540 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef signed int     i32;
typedef float          f32;
static inline void** vtbl(const void* p) { return *(void***)p; }
struct CMissionOps {
    u32   FUN_00a68fb0(u32 n);                 // 0xa68fb0 RandomUint32Uniform
    void* FUN_00c451e0();                      // 0xc451e0 GetOwnerEmpire
    u32   FUN_00c31b50(int a);                 // 0xc31b50 GetRandomAlly
    void* FUN_00b8de30();                      // 0xb8de30 BioProtectorSort::operator()
    f32   FUN_00c45b80();                      // 0xc45b80 ReadMinRange
    f32   FUN_00c45bd0();                      // 0xc45bd0 ReadMaxRange
    u32   FUN_00c45c20();                      // 0xc45c20 ReadNumJumps
    void  FUN_00c58590(void* a, void* b);      // 0xc58590 vector::erase
    f32   FUN_00ffbfc0();                      // 0xffbfc0 GetMaxTravelDistance
    void* FUN_005c65e0(void* a, void* b);      // 0x5c65e0 GetCities
    void* FUN_00bb1080(void* a, void* b);      // 0xbb1080 GetStarRecords
    u32   FUN_00bb9af0(int a);                 // 0xbb9af0
    void  FUN_00bb4af0(void* a, u32 b);        // 0xbb4af0 ActivatePlanetRecordsForQuery
    void* FUN_00bb5ae0();                      // 0xbb5ae0
    i32   FUN_00b8d9b0();                      // 0xb8d9b0
    void  FUN_00c58310(void* a);               // 0xc58310
    void  FUN_00c58360(void* a);               // 0xc58360
    void* FUN_00bb59b0(void* a);               // 0xbb59b0 GetOrActivatePlanet
    void* FUN_00c58600(void* a);               // 0xc58600
    void* FUN_00c45f80();                      // 0xc45f80
    void* FUN_01046fc0(int a);                 // 0x1046fc0
    void* FUN_01045a60(u32 a, int b);          // 0x1045a60
    void  FUN_00c58b70(void* a, void* b, u32 c); // 0xc58b70
    u8    FUN_00c4ad50();                      // 0xc4ad50 SP::cSPMission::Init
    void* FUN_0041e990();                      // 0x41e990 Property::GetInt
    u32   FUN_00c58030();                      // 0xc58030 GetMaxNumItems
    u32   FUN_00c57ff0();                      // 0xc57ff0 GetMinNumItems
    u8    FUN_00c59240(u32 a, u32 b);          // 0xc59240
    u8    FUN_00c56fe0();                      // 0xc56fe0
    void  FUN_00c4a0c0();                      // 0xc4a0c0
    void  FUN_00c485e0();                      // 0xc485e0
    void  FUN_00c46b80();                      // 0xc46b80
    void  FUN_00c485d0();                      // 0xc485d0
    void  FUN_00c46ab0();                      // 0xc46ab0
    void  FUN_00c2e4e0();                      // 0xc2e4e0
    void  FUN_00c47cc0(int a);                 // 0xc47cc0 SetState
    void  FUN_00c487d0(u32 a, void* b);        // 0xc487d0 GetText
    void  FUN_00c485b0();                      // 0xc485b0 SP::cSPMission::Accept
    u8    FUN_00c45d80(u32 a);                 // 0xc45d80
};
#define MOPS(p) ((CMissionOps*)(p))
struct cMissionMultiStep {
    u8    pad0[0x1f0];
    void* mSubBegin;      // +0x1f0
    void* mSubEnd;        // +0x1f4
    u8    pad1f8[0xc];
    i32   mCurrSub;       // +0x204
    u32*  mParam;         // +0x208
    u8    pad20c[0x10];
    u8*   mRec;           // +0x21c

    i32   SubCount() { return (i32)(((u8*)mSubEnd - (u8*)mSubBegin) >> 2); }
    void* SubAt(i32 i) { return ((void**)mSubBegin)[i]; }
    void* GetCurrSubMission();
    void  FUN_00c59dc0();
    void  FUN_00c59e20();
    void  FUN_00c59f00();
    void  FUN_00c59f60();
    void  FUN_00c59f90(u32 i, u32 v);
    u32   FUN_00c59fb0(u32 i);
    void  FUN_00c59fd0(u32 i, const void* p);
    i32   FUN_00c5a000();
    f32   FUN_00c5a050();
    void  FUN_00c5a0b0();
    u8    FUN_00c5a130();
    u8    FUN_00c5a520(u32 a);
    void  FUN_00c59eb0();
    void  FUN_00c59e70();
    void  FUN_00c5a4e0();
    void  FUN_00c5a180(u32 idx, void* out);
    void  FUN_00c5a260(void* out);
    void  FUN_00c5a280(u32 idx, void* out);
    void  FUN_00c5a390(void* out);
    void  FUN_00c5a3b0(u32 idx, void* out);
    void  FUN_00c5a4c0(void* out);
    u8    FUN_00c59b50();
    u8    FUN_00c59540(void* a, void* b);
    u8    FUN_00c59980(void* a);
};
// ---- items of slice s00c59540 end

// ---- items of slice s00c5a580 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
class IRefCounted {
public:
    virtual void AddRef();          // 0x00
    virtual void Release();         // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);   // 0x0c
    virtual void v10();
};
class cSpatialObject : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual Vec3* GetPosition();            // 0x1c
    virtual void v20();
    uint8_t mPad18[0x1c];
};
class cGameData : public cSpatialObject {
public:
    uint8_t mPad34[0x100];                  // 0x34 .. 0x134
};
class cEmpire : public IRefCounted {
public:
    uint8_t mPad14[0x28];
};
class cMissionStep : public IRefCounted {
public:
    virtual void OnActivate();              // 0x114
    virtual void OnDeactivate();            // 0x17c
    virtual int GetStepState();             // 0x60
    uint8_t mPad14[0x20];
};
class cSPMission : public cGameData {
public:
    bool IsActive();                        // 0x00
    bool Init();
    void Accept();
    uint32_t GetTargetPlanet();
    cEmpire* GetOwnerEmpire();

    uint8_t mPad134[0x0bc];                 // 0x134 .. 0x1f0
};
class cMissionMultiStep_s00c5_a580 : public cSPMission {
public:
    virtual void OnEnterStep();             // 0x16c
    virtual bool OnValidateSteps();         // 0x1a4
    virtual void OnResetSteps();            // 0x170
    virtual void OnCompleteStep();          // 0x114
    virtual void OnFailStep();              // 0x17c
    virtual void OnAccepted();              // 0x1a8

    cMissionStep** mpStepsBegin;            // 0x1f0
    cMissionStep** mpStepsEnd;              // 0x1f4
    cMissionStep** mpStepsCap;              // 0x1f8
    uint8_t mPad1fc[0x08];                  // 0x1fc
    int mCurrentStepIndex;                  // 0x204
    IRefCounted** mpRewardBegin;            // 0x208
    IRefCounted** mpRewardEnd;              // 0x20c
    uint8_t mPad210[0x0c];                  // 0x210
    uint8_t* mpScheduleBegin;               // 0x21c
    uint8_t* mpScheduleEnd;                 // 0x220
    uint8_t mPad224[0x0c];                  // 0x224
    int mTargetId;                          // 0x230

    cMissionMultiStep_s00c5_a580();
    void UpdateActiveStep();                // 0x00c5a580
    void CompleteStep();                    // 0x00c5a610
    void OnAccept();                        // 0x00c5a790
    void DestroyStepLists();                // 0x00c5a7d0
    bool Init();                            // 0x00c5a990
    void Shutdown();                        // 0x00c5ab80
    void GetUILongDescriptionSoFar(void* pString);   // 0x00c5ac60
    bool Write(void* pData);                // 0x00c5ae30
    bool Read(void* pData);                 // 0x00c5aea0
    void UpdateFromTerrainSphereA();        // 0x00c5b020
    void UpdateFromTerrainSphereB();        // 0x00c5b0b0
};
class cSPMissionManager {
public:
    cSPMission* CreateMissionFromID(uint32_t id, uint32_t owner, cEmpire* pEmpire, void* pParent);
};
cSPMissionManager* GetMissionManager();
void GetPropertyAsKeyArray(void* pDefinition, int key, void* pOut);
void* GetMissionManagerForMission(uint32_t id);
void MissionManagerRelease(void* pMission);
void CreateMissionSteps(void* pOwner);
void AddStepToSchedule(uint32_t id);
void ResetStepSchedule();
void ReleaseMissionList(void* pMission);
void ResizeMissionList(void* pList, int nCount);
void MissionVectorErase(void* pBegin, void* pEnd);
void ReleaseStepListContents();
void ReleaseRewardList();
void ShutdownMissionStepState();
// ---- items of slice s00c5a580 end

// @ 0x00c59d90
void* cMissionMultiStep::GetCurrSubMission()
{
    i32 idx = mCurrSub;
    u8* e = (u8*)mSubEnd;
    i32 n = (i32)(e - (u8*)mSubBegin) >> 2;
    if (idx >= 0 && idx < n) {
        return ((void**)mSubBegin)[idx];
    }
    return 0;
}

// @ 0x00c59dc0
void cMissionMultiStep::FUN_00c59dc0()
{
    i32 n = SubCount();
    for (i32 i = 0; i < n; i++) {
        void* m = SubAt(i);
        i32 s = (*(i32(__thiscall**)(void*))((char*)vtbl(m) + 0x60))(m);
        if (s != 9) {
            MOPS(m)->FUN_00c485e0();
            (*(void(__thiscall**)(void*))((char*)vtbl(m) + 0x94))(m);
        }
    }
    MOPS(this)->FUN_00c46b80();
}

// @ 0x00c59e20
void cMissionMultiStep::FUN_00c59e20()
{
    MOPS(GetCurrSubMission())->FUN_00c485d0();
    MOPS(this)->FUN_00c46ab0();
}

// @ 0x00c59e70
void cMissionMultiStep::FUN_00c59e70()
{
    void* m = GetCurrSubMission();
    (*(void(__thiscall**)(void*))((char*)vtbl(m) + 0x118))(m);
}

// @ 0x00c59eb0
void cMissionMultiStep::FUN_00c59eb0()
{
    void* m = GetCurrSubMission();
    MOPS(m)->FUN_00c485b0();
    (*(void(__thiscall**)(void*))((char*)vtbl(this) + 0x1a8))(this);
}

// @ 0x00c59f00
void cMissionMultiStep::FUN_00c59f00()
{
    MOPS(GetCurrSubMission())->FUN_00c485e0();
    if (mCurrSub == SubCount() - 1) {
        MOPS(this)->FUN_00c485e0();
    }
    (*(void(__thiscall**)(void*))((char*)vtbl(this) + 0x1ac))(this);
}

// @ 0x00c59f60
void cMissionMultiStep::FUN_00c59f60()
{
    if (mCurrSub < SubCount() - 1) {
        mCurrSub = mCurrSub + 1;
    }
}

// @ 0x00c59f90
void cMissionMultiStep::FUN_00c59f90(u32 i, u32 v)
{
    if (i < 2) {
        mParam[i] = v;
    }
}

// @ 0x00c59fb0
u32 cMissionMultiStep::FUN_00c59fb0(u32 i)
{
    if (i < 2) {
        return mParam[i];
    }
    return 0;
}

// @ 0x00c59fd0
void cMissionMultiStep::FUN_00c59fd0(u32 i, const void* p)
{
    if (i < 2) {
        u32* d = (u32*)(mRec + i * 0xc);
        const u32* s = (const u32*)p;
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
    }
}

// @ 0x00c5a000
i32 cMissionMultiStep::FUN_00c5a000()
{
    i32 n = SubCount();
    i32 sum = 0;
    for (i32 i = 0; i < n; i++) {
        void* m = SubAt(i);
        sum += (*(i32(__thiscall**)(void*))((char*)vtbl(m) + 0xec))(m);
    }
    return sum;
}

// @ 0x00c5a050
f32 cMissionMultiStep::FUN_00c5a050()
{
    i32 n = SubCount();
    f32 sum = 0.0f;
    for (i32 i = 0; i < n; i++) {
        void* m = SubAt(i);
        sum = sum + (*(f32(__thiscall**)(void*))((char*)vtbl(m) + 0xf0))(m);
    }
    return sum;
}

// @ 0x00c5a0b0
void cMissionMultiStep::FUN_00c5a0b0()
{
    MOPS(this)->FUN_00c2e4e0();
    i32 n = SubCount();
    for (i32 i = mCurrSub; i < n; i++) {
        void* m = SubAt(i);
        if (i < n - 1) {
            MOPS(m)->FUN_00c485e0();
        } else {
            i32 s = (*(i32(__thiscall**)(void*))((char*)vtbl(m) + 0x60))(m);
            if (s == 0) {
                (*(void(__thiscall**)(void*))((char*)vtbl(m) + 0x88))(m);
                MOPS(m)->FUN_00c47cc0(3);
            }
            (*(void(__thiscall**)(void*))((char*)vtbl(m) + 0x15c))(m);
        }
    }
    mCurrSub = n - 1;
}

// @ 0x00c5a130
u8 cMissionMultiStep::FUN_00c5a130()
{
    i32 n = SubCount();
    for (i32 i = 0; i < n; i++) {
        void* m = SubAt(i);
        u8 ok = (*(u8(__thiscall**)(void*))((char*)vtbl(m) + 0xf8))(m);
        if (!ok) {
            return 0;
        }
    }
    return 1;
}

// @ 0x00c5a260
void cMissionMultiStep::FUN_00c5a260(void* out)
{
    FUN_00c5a180((u32)mCurrSub, out);
}

// @ 0x00c5a280
void cMissionMultiStep::FUN_00c5a280(u32 idx, void* out)
{
    u32 tbl[15];
    tbl[5] = 0x7e677e9e; tbl[6] = 0x7e677e9d; tbl[7] = 0x7e677e9c;
    tbl[8] = 0x7e677e9b; tbl[9] = 0x7e677e9a;
    tbl[10] = 0x6119e327; tbl[0xb] = 0x6119e324; tbl[0xc] = 0x6119e325;
    tbl[0xd] = 0x6119e322; tbl[0xe] = 0x6119e323;
    tbl[0] = 0x90cd70d9; tbl[1] = 0x90cd70da; tbl[2] = 0x90cd70db;
    tbl[3] = 0x90cd70dc; tbl[4] = 0x90cd70dd;
    if (idx < 5) {
        void* m = ((void**)mSubBegin)[idx];
        if (m != 0) {
            i32 s = (*(i32(__thiscall**)(void*))((char*)vtbl(m) + 0x60))(m);
            if (s == 3) {
                u8 done = (*(u8(__thiscall**)(void*))((char*)vtbl(m) + 0xf8))(m);
                if (!done) {
                    MOPS(m)->FUN_00c487d0(tbl[idx + 5], out);
                } else {
                    MOPS(m)->FUN_00c487d0(tbl[idx + 10], out);
                }
            } else if (s == 9) {
                MOPS(m)->FUN_00c487d0(tbl[idx], out);
            }
        }
    }
}

// @ 0x00c5a390
void cMissionMultiStep::FUN_00c5a390(void* out)
{
    FUN_00c5a280((u32)mCurrSub, out);
}

// @ 0x00c5a3b0
void cMissionMultiStep::FUN_00c5a3b0(u32 idx, void* out)
{
    u32 tbl[15];
    tbl[5] = 0x9fc279b7; tbl[6] = 0x9fc279b4; tbl[7] = 0x9fc279b5;
    tbl[8] = 0x9fc279b2; tbl[9] = 0x9fc279b3;
    tbl[10] = 0x80ab3e2c; tbl[0xb] = 0x80ab3e2f; tbl[0xc] = 0x80ab3e2e;
    tbl[0xd] = 0x80ab3e29; tbl[0xe] = 0x80ab3e28;
    tbl[0] = 0x2da98672; tbl[1] = 0x2da98671; tbl[2] = 0x2da98670;
    tbl[3] = 0x2da98677; tbl[4] = 0x2da98676;
    if (idx < 5) {
        void* m = ((void**)mSubBegin)[idx];
        if (m != 0) {
            i32 s = (*(i32(__thiscall**)(void*))((char*)vtbl(m) + 0x60))(m);
            if (s == 3) {
                u8 done = (*(u8(__thiscall**)(void*))((char*)vtbl(m) + 0xf8))(m);
                if (!done) {
                    MOPS(m)->FUN_00c487d0(tbl[idx + 5], out);
                } else {
                    MOPS(m)->FUN_00c487d0(tbl[idx + 10], out);
                }
            } else if (s == 9) {
                MOPS(m)->FUN_00c487d0(tbl[idx], out);
            }
        }
    }
}

// @ 0x00c5a4c0
void cMissionMultiStep::FUN_00c5a4c0(void* out)
{
    FUN_00c5a3b0((u32)mCurrSub, out);
}

// @ 0x00c5a4e0
void cMissionMultiStep::FUN_00c5a4e0()
{
    i32 idx = mCurrSub;
    u8* e = (u8*)mSubEnd;
    i32 n = (i32)(e - (u8*)mSubBegin) >> 2;
    if (idx >= 0 && idx < n) {
        void* m = ((void**)mSubBegin)[idx];
        if (m != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(m) + 0x124))(m);
            return;
        }
    }
}

// @ 0x00c5a520
u8 cMissionMultiStep::FUN_00c5a520(u32 a)
{
    u8 r = MOPS(this)->FUN_00c45d80(a);
    if (r) {
        return 1;
    }
    for (i32 i = 0; i <= mCurrSub; i++) {
        void* m = ((void**)mSubBegin)[i];
        if (m != 0) {
            u8 ok = (*(u8(__thiscall**)(void*, u32))((char*)vtbl(m) + 0xf4))(m, a);
            if (ok) {
                return 1;
            }
        }
    }
    return 0;
}

// @ 0x00c5a580
void cMissionMultiStep_s00c5_a580::UpdateActiveStep()
{
    if (!IsActive())
        return;
    int nIndex = mCurrentStepIndex;
    if (nIndex < 0)
        return;
    if (nIndex >= (int)(mpStepsEnd - mpStepsBegin))
        return;
    cMissionStep* pStep = mpStepsBegin[nIndex];
    if (pStep == nullptr)
        return;
    pStep->OnActivate();
}

// @ 0x00c5a610
void cMissionMultiStep_s00c5_a580::CompleteStep()
{
    int nIndex = mCurrentStepIndex;
    cMissionStep* pStep = nullptr;
    if (nIndex >= 0 && nIndex < (int)(mpStepsEnd - mpStepsBegin))
        pStep = mpStepsBegin[nIndex];
    pStep->OnDeactivate();
}

// @ 0x00c5a790
void cMissionMultiStep_s00c5_a580::OnAccept()
{
    ResetStepSchedule();
    mCurrentStepIndex = -1;
    cSPMission* pFirst = nullptr;
    if (mpStepsEnd - mpStepsBegin > 0)
        pFirst = (cSPMission*)mpStepsBegin[0];
    pFirst->Accept();
    OnAccepted();
}

// @ 0x00c5a7d0
void cMissionMultiStep_s00c5_a580::DestroyStepLists()
{
    ReleaseStepListContents();
    ReleaseRewardList();
    ReleaseMissionList(this);
}

// @ 0x00c5a990
bool cMissionMultiStep_s00c5_a580::Init()
{
    if (!cSPMission::Init())
        return false;

    OnEnterStep();
    if (!OnValidateSteps())
        return false;
    OnResetSteps();

    int nCount = 0;
    void* pDefinition = nullptr;
    GetPropertyAsKeyArray(this, 0x6d03cf70, &pDefinition);
    int nStepCount = 0;
    AddStepToSchedule(0x6d03cf70);

    for (int i = 0; i < nStepCount; ++i) {
        uint32_t nMissionId = 0;
        uint32_t nOwner = 0;
        cSPMissionManager* pManager = GetMissionManager();
        cSPMission* pMission = pManager->CreateMissionFromID(nMissionId, nOwner,
                                                            GetOwnerEmpire(), this);
        if (pMission == nullptr) {
            ReleaseStepListContents();
            return false;
        }
        pMission->AddRef();
        if (mpRewardEnd < mpRewardBegin + 1) {
            *mpRewardEnd++ = pMission;
            pMission->AddRef();
        } else {
            ResizeMissionList(mpRewardEnd, 1);
        }
        pMission->Release();
        nCount = i + 1;
    }
    (void)nCount;

    CreateMissionSteps(this);
    mCurrentStepIndex = 0;
    return true;
}

// @ 0x00c5ab80
void cMissionMultiStep_s00c5_a580::Shutdown()
{
    int nCount = (int)(mpStepsEnd - mpStepsBegin);
    for (int i = 0; i < nCount; ++i) {
        uint32_t id = 0;
        GetMissionManagerForMission(id);
        MissionManagerRelease(mpStepsBegin[i]);
    }

    IRefCounted** pSrc = mpRewardBegin;
    IRefCounted** pDst = mpRewardEnd;
    int nRewards = (int)(pSrc - pDst);
    while (pDst != pSrc) {
        if (*pDst != nullptr)
            (*pDst)->Release();
        ++pDst;
    }
    mpRewardEnd = mpRewardBegin;

    mpScheduleEnd = mpScheduleBegin;
    MissionVectorErase(mpStepsBegin, mpStepsEnd);
    mCurrentStepIndex = -1;
    ShutdownMissionStepState();
    (void)nRewards;
}
