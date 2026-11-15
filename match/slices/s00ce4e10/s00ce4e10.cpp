// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 4 / slice s00ce4e10.
//
// Simulator::cTribePlanner: construction/destruction, the raiding planner step and the
// eastl-vector helpers used by the planner's step tables (assignment, insert, resize).

typedef unsigned int size_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define nullptr 0

// ---------------------------------------------------------------------------------------------
// eastl / sp_vector_allocator plumbing
// ---------------------------------------------------------------------------------------------
extern const char kEastlAllocatorFile[];                       // allocator.h source path
void* operator_new(size_t nSize, const char* pName, int a, int b, const void* pFile, int nLine);
void  operator_delete_array(void* pMemory);

// 0x00ce29c0 -- copy/move a range into uninitialised storage, returns the new end.
void* FUN_00ce29c0(void** ppResult, void* pFirst, void* pLast, void* pDest, void* pOwner);
void* FUN_00ce2b30(void* pFirst, void* pLast, void* pDest);
void  FUN_00ce2c70(void* pThis, void* pFirst, void* pLast);    // eastl::vector::DoDestroyValues
void  FUN_00ce0e00(void* pFirst, void* pLast);                 // vector<PlannerGroup>::DoDestroyValues
void* FUN_00ce2cc0(void* pThis, uint32_t nCount, void* pFirst, void* pLast);
void* FUN_00ce2930(void* pFirst, void* pLast, void* pDest);
void  FUN_00ce0d90(void* pFirst, void* pLast, void* pDest);
void  FUN_00ce2ab0(void* pDest, uint32_t nCount, void* pValue, void* pOwner);
void  FUN_00ce2880(void* pValue);
void  FUN_00ce2a50(void* pFirst, void* pLast, void* pValue);
void  FUN_00ce2ba0(void* pFirst, void* pLast, void* pDest);

// ---------------------------------------------------------------------------------------------
// forward declarations of the neighbouring planner helpers
// ---------------------------------------------------------------------------------------------
struct PlannerGroup;
struct PlannerStepData;
struct PlannerGroupVector;
struct PlannerStepVector;

void* FUN_00ce4e10(void* pFirst, void* pLast, void* pDest);    // copy-construct a group range
void  FUN_00ce2c10(void* pFirst, void* pLast, void* pDest);
void* FUN_00ce4c40(void* pVector);                             // CopyPlannerVector
void  FUN_00ce4ca0(void* pFirst, void* pLast, void* pDest, void* pOwner);
void  FUN_00ce4d60(void* pDest, uint32_t nCount, void* pValue, void* pOwner);
void  FUN_00ce5a40(void* pFirst, void* pLast, void* pDest);
void  FUN_00ce5650(PlannerStepData* pEnd, PlannerStepData* pNewEnd);
void* FUN_00ce5a00(void* a, void* b, void* c);
void  FUN_00ce58a0(void* pVector);                             // vector<AutoRefCount<cStarRecord>> dtor

// ---------------------------------------------------------------------------------------------
// behaviour-tree data owned by the planner (0x670 bytes, "Simulator/cBehaviorTreeData")
// ---------------------------------------------------------------------------------------------
class cBehaviorTreeData {
public:
    uint32_t mPad00[0x19c];                         // +0x00 (0x670 bytes)
};

// 0x00bcae90 -- cAgentOrderManager::~cAgentOrderManager (thiscall: the pointer lands in ecx)
void __fastcall FUN_00bcae90(cBehaviorTreeData* pThis, void* pUnused);

// 0x00b5b6c0 -- SP::cGonzagoSimulator constructor (primary base of the planner).
class ContentValidationSummarizer {
public:
    virtual void Summarize();                       // +0x00

    uint32_t    mPad04;                             // +0x04
};

class cGonzagoSimulator : public ContentValidationSummarizer {
public:
    cGonzagoSimulator();                            // 0x00b5b6c0
    virtual void Update();                          // +0x08
};

// secondary base of the planner (EA::Trace::ITracerBase subobject, vptr at +0x08)
class ITracerBase {
public:
    virtual void TraceBegin();                      // +0x00
    virtual void TraceEnd();                        // +0x04


    uint32_t    mPad04;                             // +0x04
};

// ---------------------------------------------------------------------------------------------
// PLAN_TABLE data
// ---------------------------------------------------------------------------------------------
// SP::cTribePlanData (0x58 bytes in the eastl vector; PDB size 0x54).
struct SpSortedVector8 {                            // fixed_vector<T, 8> with inline storage
    void        Destroy();                          // 0x00ae6970 eastl vector destructor

    void*       mpBegin;
    void*       mpEnd;
    void*       mpCapacityEnd;
    void*       mPad0c0;                            // +0x0c
    void*       mPad0c1;                            // +0x10
    void*       mPad0c2;                            // +0x14
    void*       mSlot0;                             // +0x18 inline storage, 8 slots
    void*       mSlot1;                             // +0x1c
    void*       mSlot2;                             // +0x20
    void*       mSlot3;                             // +0x24
    void*       mSlot4;                             // +0x28
    void*       mSlot5;                             // +0x2c
    void*       mSlot6;                             // +0x30
    void*       mSlot7;                             // +0x34
    uint32_t    mPad38;                             // +0x38
};

struct PlannerStepData {                            // SP::cTribePlanData
    PlannerStepData();
    void Init();

    uint32_t        mID;                            // +0x00
    uint32_t        mState;                         // +0x04
    uint32_t        mFrequency;                     // +0x08
    float           mCheckTime;                     // +0x0c
    int32_t         mFoodRequired;                  // +0x10
    float           mFoodAccumulated;               // +0x14
    uint8_t         mbCheck;                        // +0x18
    uint8_t         mPad19a;                        // +0x19
    uint8_t         mPad19b;                        // +0x1a
    uint8_t         mPad19c;                        // +0x1b
    SpSortedVector8 mWorkers;                       // +0x1c
};

void PlannerStepData::Init()
{
    mID = 0;
    mState = 0;
    mFrequency = 0;
    mCheckTime = 0.0f;
    mFoodRequired = 0;
    mFoodAccumulated = 0.0f;
    mbCheck = 0;
    mWorkers.mpBegin = (void*)&mWorkers.mSlot0;
    mWorkers.mpEnd = (void*)&mWorkers.mSlot0;
    mWorkers.mPad0c2 = 0;
    mWorkers.mPad38 = 0;
    mWorkers.mpCapacityEnd = (void*)(&mWorkers.mSlot0 + 8);
}

PlannerStepData::PlannerStepData()
{
    Init();
}

// cTribePlanData must be default-constructible when an eastl vector grows.
// ---------------------------------------------------------------------------------------------
// eastl vectors used by the planner
// ---------------------------------------------------------------------------------------------
struct PlannerGroup {                               // one (plan type, step list) pair, 0x18 bytes
    uint32_t            mPlanType;                  // +0x00
    PlannerStepData*    mpStepsBegin;               // +0x04
    PlannerStepData*    mpStepsEnd;                 // +0x08
    PlannerStepData*    mpStepsCapacity;            // +0x0c
    uint32_t            mPad10[2];                  // +0x10
};

struct PlannerGroupVector {                         // eastl::vector<PlannerGroup>
    PlannerGroup* mpBegin;                          // +0x00
    PlannerGroup* mpEnd;                            // +0x04
    PlannerGroup* mpCapacity;                       // +0x08

    void DoDestroyValues(PlannerGroup* pFirst, PlannerGroup* pEnd);   // 0x00ce2c70

    PlannerGroupVector* FUN_00ce5050(const PlannerGroupVector* pOther);              // assign
    void*               CopyFrom(const PlannerGroupVector* pSource);                 // 0x00ce4c40
    void                FUN_00ce5c40(PlannerGroup* pPos, uint32_t nCount, PlannerGroup* pValue);
    void                FUN_00ce5e90(PlannerGroup* pPos, PlannerGroup* pValue);
    void                FUN_00ce5ff0();
    PlannerGroup*       FUN_00ce6040(PlannerGroup* pPos, PlannerGroup* pValue);
};

struct PlannerStepVector {                          // eastl::vector<cTribePlanData>
    PlannerStepData* mpBegin;                       // +0x00
    PlannerStepData* mpEnd;                         // +0x04
    PlannerStepData* mpCapacity;                    // +0x08

    void FUN_00ce56a0(PlannerStepData* pEnd, const PlannerStepData* pValue);   // insert into full storage
    void FUN_00ce57e0(PlannerStepData* pPos, uint32_t nCount, const PlannerStepData* pValue);
    void FUN_00ce5a80();
    void FUN_00ce5b30(uint32_t nCount);
};

// ---------------------------------------------------------------------------------------------
// Simulator::cTribePlanner
// ---------------------------------------------------------------------------------------------
class SpVectorFloat {
public:
    void resize(int32_t nCount);                    // 0x004afc80

    float*      mpBegin;                            // +0x00
    float*      mpEnd;                              // +0x04
    float*      mpCapacity;                         // +0x08
    uint8_t     mPad0c[0x08];                       // +0x0c
    uint32_t    mUnused14;                          // +0x14
    float       mBuffer[12];                        // +0x18
};

class cTribe;

class cTribePlanner : public cGonzagoSimulator, public ITracerBase {
public:
    cTribePlanner();                                // 0x00ce55a0
    ~cTribePlanner();                               // 0x00ce4ed0

    cBehaviorTreeData*  mpBehaviorTreeData;         // +0x10
    PlannerGroup*       mpPlansBegin;               // +0x14
    PlannerGroup*       mpPlansEnd;                 // +0x18
    PlannerGroup*       mpPlansCapacity;            // +0x1c
    uint8_t             mPad20[0x0c];               // +0x20
    SpVectorFloat       mTimeBetweenPlanExecutionByType;   // +0x2c
    cTribe*             mpTribe;                    // +0x74
    float               mAccumulatedDeltaTime;      // +0x78
};

// 0x00bcb2a0 -- cAgentOrderManager-derived behaviour tree data constructor (thiscall)
cBehaviorTreeData* __fastcall FUN_00bcb2a0(cBehaviorTreeData* pThis, void* pUnused);


// ---------------------------------------------------------------------------------------------
// 0x00ce4e10 -- construct a [first,last) range of PlannerGroup into raw storage
// ---------------------------------------------------------------------------------------------
// @ 0x00ce4e10 FUN_00ce4e10
void* FUN_00ce4e10(void* pFirst, void* pLast, void* pDest)
{
    PlannerGroup* pSrc = (PlannerGroup*)pFirst;
    PlannerGroup* pOut = (PlannerGroup*)pDest;

    if (pSrc == (PlannerGroup*)pLast)
        return pDest;

    do {
        if (pOut) {
            void* pResult;
            pOut->mPlanType = pSrc->mPlanType;
            int32_t nCount = (int32_t)((char*)pSrc->mpStepsEnd - (char*)pSrc->mpStepsBegin) / 0x58;
            PlannerStepData* pNew = nullptr;
            if (nCount != 0)
                pNew = (PlannerStepData*)operator_new(nCount * 0x58, "Simulator", 0, 0,
                                                      kEastlAllocatorFile, 0xd1);
            pOut->mpStepsCapacity = (PlannerStepData*)((char*)pNew + nCount * 0x58);
            pOut->mpStepsBegin = pNew;
            pOut->mpStepsEnd = pNew;
            FUN_00ce29c0(&pResult, pSrc->mpStepsBegin, pSrc->mpStepsEnd, pNew, pLast);
            pOut->mpStepsEnd = (PlannerStepData*)pResult;
        }
        ++pSrc;
        ++pOut;
    } while (pSrc != (PlannerGroup*)pLast);

    return pOut;
}

// ---------------------------------------------------------------------------------------------
// 0x00ce4ed0 -- Simulator::cTribePlanner::~cTribePlanner
// ---------------------------------------------------------------------------------------------
// @ 0x00ce4ed0 cTribePlanner::~cTribePlanner
cTribePlanner::~cTribePlanner()
{
    if (mpBehaviorTreeData) {
        FUN_00bcae90(mpBehaviorTreeData, 0);
        operator_delete_array(mpBehaviorTreeData);
    }
    if (mpTribe) {
        ITracerBase* pTribe = (ITracerBase*)mpTribe;
        pTribe->TraceEnd();                          // vtable slot used as Release by the tribe
    }
    PlannerGroup* pTimesBegin = (PlannerGroup*)mTimeBetweenPlanExecutionByType.mpBegin;
    if (pTimesBegin) {
        if (((int32_t*)pTimesBegin)[-1] != 0)
            operator_delete_array(pTimesBegin);
    }
    PlannerGroupVector* pPlans = (PlannerGroupVector*)&mpPlansBegin;
    pPlans->DoDestroyValues(mpPlansBegin, mpPlansEnd);
    PlannerGroup* pPlansBegin = pPlans->mpBegin;
    if (pPlansBegin)
        operator_delete_array(pPlansBegin);
}

// ---------------------------------------------------------------------------------------------
// 0x00ce5050 -- eastl::vector<PlannerGroup>::operator=
// ---------------------------------------------------------------------------------------------
// @ 0x00ce5050 FUN_00ce5050
PlannerGroupVector* PlannerGroupVector::FUN_00ce5050(const PlannerGroupVector* pOther)
{
    PlannerGroupVector* pVec = this;
    if (pOther == pVec)
        return pVec;

    PlannerGroup* pSource = pOther->mpBegin;
    uint32_t nSource = (uint32_t)((char*)pOther->mpEnd - (char*)pSource) / 0x18;
    PlannerGroup* pBegin = pVec->mpBegin;
    uint32_t nCapacity = (uint32_t)((char*)pVec->mpCapacity - (char*)pBegin) / 0x18;

    if (nCapacity < nSource) {
        PlannerGroup* pNew = (PlannerGroup*)FUN_00ce2cc0(pVec, nSource, pSource, pOther->mpEnd);
        FUN_00ce0e00(pVec->mpBegin, pVec->mpEnd);
        if (pVec->mpBegin) {
            if (((int32_t*)pVec->mpBegin)[-1] != 0)
                operator_delete_array(pVec->mpBegin);
        }
        pVec->mpEnd = (PlannerGroup*)((char*)pNew + nSource * 0x18);
        pVec->mpBegin = pNew;
        pVec->mpCapacity = pVec->mpEnd;
        return pVec;
    }

    uint32_t nSize = (uint32_t)((char*)pVec->mpEnd - (char*)pBegin) / 0x18;
    if (nSize < nSource) {
        FUN_00ce2b30(pSource, (char*)pSource + nSize * 0x18, pBegin);
        PlannerGroup* pIn = (PlannerGroup*)((char*)pSource + nSize * 0x18);
        PlannerGroup* pOtherEnd = pOther->mpEnd;
        void* pResult = nullptr;
        FUN_00ce29c0(&pResult, pIn, pOtherEnd, pVec->mpEnd, pOtherEnd);
        pVec->mpEnd = (PlannerGroup*)((char*)pVec->mpBegin + nSource * 0x18);
        return pVec;
    }

    PlannerGroup* pEnd = (PlannerGroup*)FUN_00ce2b30(pSource, pOther->mpEnd, pBegin);
    FUN_00ce0e00(pEnd, pVec->mpEnd);
    pVec->mpEnd = (PlannerGroup*)((char*)pVec->mpBegin + nSource * 0x18);
    return pVec;
}

// ---------------------------------------------------------------------------------------------
// 0x00ce5190 -- PLANNER_RAIDING_Tick
// ---------------------------------------------------------------------------------------------
void* FUN_00bca2c0();                               // cAgentOrderManager::FirstPending
void* FUN_00ce0e60(void* pTable, uint32_t uPlanId, uint32_t uIndex);
bool  FUN_00cdfea0(void* pOrder);
void  FUN_00cdff70(void* pOrder);
void  FUN_009fbc50(void* pTarget, float fX, float fY, float fZ);
void  FUN_00b3d2c0(void* pObj);
float FUN_00d00a10(void* a, void* b, uint32_t c);
int32_t FUN_00d00780(float fValue);
void  FUN_00c27db0(uint32_t uOrderType);
void* FUN_00af9f30();
int32_t FUN_00c9d110();
bool  FUN_00c0b770(void* pObject);
void  FUN_00ce0b20(void* a, void* b);

// C++ stand-ins for the engine types the tick walks over.
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

class cCombatant {
public:
    int32_t GetDamageState();                       // 0x00bca... (inlined by the caller)
    uint32_t mPad00[0x48];                          // +0x00 .. +0x11f
};

class cGameObject {
public:
    virtual Vec3* GetPosition();                    // +0x2c
    uint32_t mPad04[0x2c];                          // +0x04 .. +0xbf
    void*    mpVtblC0;                              // +0xc0 (secondary interface)
};

class cSPCreatureCitizen {
public:
    void GiveOrder(int32_t nOrder, void* pTool, void* pParam);
    uint32_t mPad00[0x16c];                         // +0x00 .. +0x5a7
    cGameObject* mpTarget;                          // +0x5a8
    uint8_t  mByteB5e;                              // +0xb5e
};

struct PlanKey {
    uint32_t mPlanId;                               // +0x00
    uint32_t mIndex;                                // +0x04
    float    mTimeout;                              // +0x08
    Vec3     mPosition;                             // +0x0c
};

class cPlanOrder {                                  // the planner's active plan object
public:
    virtual void  v00();                            // +0x00
    virtual void  v04();                            // +0x04
    virtual void* GetInterface(uint32_t uKey);      // +0x0c
    virtual void  v10();
    virtual void  v14();
    virtual void  v18();
    virtual void  v1c();
    virtual void  v20();
    virtual void  v24();
    virtual void  v28();
    virtual void  v2c();
    virtual void  v30();
    virtual void  v34();
    virtual void  v38();
    virtual void  v3c();
    virtual void  v40();
    virtual void  v44();
    virtual void  v48();
    virtual void* GetOwner(uint32_t uIndex);        // +0x4c
    virtual void  v50();
    virtual void  v54();
    virtual void  v58();
    virtual void  v5c();
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual void  v6c();
    virtual void  v70();
    virtual void  v74();
    virtual void  v78();
    virtual void  v7c();
    virtual void  v80();
    virtual void  v84();
    virtual void  v88();
    virtual void  v8c();
    virtual void* GetTarget();                      // +0x90
    virtual void  v94();
    virtual void  v98();
    virtual void  v9c();
    virtual void  va0();
    virtual void  va4();
    virtual void  va8();
    virtual void* GetGroup();                       // +0xac
    virtual void  vb0();
    virtual void  vb4();
    virtual void  vb8();
    virtual void* GetMembers();                     // +0xbc

    uint32_t mPad04[0x44];                          // +0x04 .. +0x123
    void*    mpGroup122;                            // +0x124
};

// @ 0x00ce5190 PLANNER_RAIDING_Tick
int32_t PLANNER_RAIDING_Tick(PlannerGroupVector* pPlans, uint32_t uUnused, float fTimeout,
                             void* pTargetPos, float fDuration, void* pPlanTable,
                             PlanKey* pKey, cSPCreatureCitizen* pOwner)
{
    (void)pPlans;
    void* pOrder = FUN_00bca2c0();
    if (!pOrder)
        return 0;

    void* pPlanData = FUN_00ce0e60(pPlanTable, pKey->mPlanId, pKey->mIndex);
    if (!pPlanData)
        return 0;

    PlannerStepData* pFirst = (PlannerStepData*)((char*)pPlanData + 0x1c);
    void** ppCur = (void**)pFirst;
    void** ppEnd = (void**)((char*)pPlanData + 0x20);
    if (ppCur == ppEnd)
        return 0;

    if (!FUN_00cdfea0(*ppCur))
        FUN_00cdff70(*ppCur);
    if (ppCur == ppEnd)
        return 0;

    cGameObject* pFirstMember = (cGameObject*)*ppCur;
    Vec3* pPos = pFirstMember->GetPosition();
    FUN_009fbc50(pTargetPos, pPos->mX, pPos->mY, pPos->mZ);

    if (!pOwner || !pOwner->mpTarget)
        return 0;

    cPlanOrder* pPlan = (cPlanOrder*)pOrder;
    if (!pPlan->GetInterface(0x4f396a66))
        return 0;

    pKey->mTimeout = pKey->mTimeout - fDuration;
    if (pKey->mTimeout >= 0.0f)
        return 1;

    pKey->mTimeout = 2.0f;
    void* pCombat = pPlan->GetOwner(1);
    void* pOwnerObj = pPlan->GetOwner((uint32_t)pCombat);
    FUN_00b3d2c0(pOwnerObj);
    float fValue = FUN_00d00a10(pOwnerObj, pCombat, 1);
    FUN_00b3d2c0(*(void**)&fValue);
    if (FUN_00d00780(fValue) > 1)
        return 0;

    cCombatant* pTarget = (cCombatant*)pPlan->GetGroup();
    cCombatant* pFound = nullptr;
    void** ppMembers = (void**)pPlan->GetMembers();
    uint32_t nMembers = (uint32_t)((char*)ppMembers[1] - (char*)ppMembers[0]) / 4;
    if (nMembers != 0) {
        for (uint32_t i = 0; i < nMembers; ++i) {
            cGameObject* pMember = (cGameObject*)((void**)ppMembers)[i];
            uint8_t nType = 0;
            (void)nType;
            if (pMember) {
                int32_t nState = ((cCombatant*)((char*)pMember + 0x120))->GetDamageState();
                if (nState != 2) {
                    FUN_00c27db0(0);
                    if (FUN_00af9f30() && FUN_00c9d110() == 1)
                        pFound = (cCombatant*)((char*)pMember + 0x120);
                }
            }
        }
    }

    if (!pFound) {
        pFound = *(cCombatant**)((char*)pTarget + 0x120);
        int32_t nState = pFound ? pFound->GetDamageState() : 2;
        if (nState != 2 && pTarget) {
            for (void** ppIt = ppCur; ppIt != ppEnd; ++ppIt) {
                cSPCreatureCitizen* pCitizen = (cSPCreatureCitizen*)*ppIt;
                if (!FUN_00bca2c0()) {
                    void* pTool = pPlan->GetOwner(nullptr);
                    pCitizen->GiveOrder(0xf, pTool, nullptr);
                }
                FUN_00cdff70(pCitizen);
            }
            return 1;
        }
        return 0;
    }

    for (void** ppIt = ppCur; ppIt != ppEnd; ++ppIt) {
        cSPCreatureCitizen* pCitizen = (cSPCreatureCitizen*)*ppIt;
        if (!FUN_00bca2c0()) {
            void* pTool = ((cPlanOrder*)pFound)->GetOwner(nullptr);
            pCitizen->GiveOrder(0xf, pTool, nullptr);
        }
        FUN_00cdff70(pCitizen);
    }
    return 1;
}

// ---------------------------------------------------------------------------------------------
// 0x00ce55a0 -- Simulator::cTribePlanner::cTribePlanner
// ---------------------------------------------------------------------------------------------
// @ 0x00ce55a0 cTribePlanner::cTribePlanner
cTribePlanner::cTribePlanner()
{
    mpPlansBegin = nullptr;
    mpPlansEnd = nullptr;
    mpPlansCapacity = nullptr;

    SpVectorFloat* pTimes = &mTimeBetweenPlanExecutionByType;
    pTimes->mpBegin = pTimes->mBuffer;
    pTimes->mpEnd = pTimes->mBuffer;
    pTimes->mUnused14 = 0;
    pTimes->mpCapacity = pTimes->mBuffer + 12;
    mpTribe = nullptr;
    mAccumulatedDeltaTime = 0.0f;

    cBehaviorTreeData* pData = (cBehaviorTreeData*)operator_new(
        0x670, "Simulator/cBehaviorTreeData", 0, 0, nullptr, 0);
    if (pData != nullptr) {
        mpBehaviorTreeData = FUN_00bcb2a0(pData, nullptr);
        pTimes->resize(0xc);
        return;
    }
    mpBehaviorTreeData = nullptr;
    pTimes->resize(0xc);
}

// ---------------------------------------------------------------------------------------------
// 0x00ce57e0 -- eastl::vector<cTribePlanData>::DoInsertValues
// ---------------------------------------------------------------------------------------------
// @ 0x00ce57e0 FUN_00ce57e0
void PlannerStepVector::FUN_00ce57e0(PlannerStepData* pPos, uint32_t nCount,
                                     const PlannerStepData* pValue)
{
    PlannerStepVector* pVec = this;
    if ((uint32_t)((char*)pVec->mpCapacity - (char*)pVec->mpEnd) / 0x58 >= nCount) {
        if (nCount == 0)
            return;
        FUN_00ce2880((void*)pValue);
        PlannerStepData* pEnd = pVec->mpEnd;
        uint32_t nTail = (uint32_t)((char*)pVec->mpEnd - (char*)pPos) / 0x58;
        if (nTail <= nCount) {
            FUN_00ce2ab0(pEnd, nCount - nTail, (void*)pValue, pPos);
            pVec->mpEnd = (PlannerStepData*)((char*)pVec->mpEnd + (nCount - nTail) * 0x58);
            void* pResult = nullptr;
            FUN_00ce29c0(&pResult, pPos, pEnd, pVec->mpEnd, pPos);
            pVec->mpEnd = (PlannerStepData*)((char*)pVec->mpEnd + nTail * 0x58);
            FUN_00ce2a50(pPos, pEnd, (void*)pValue);
            return;
        }
        PlannerStepData* pMoveStart = (PlannerStepData*)((char*)pEnd + nCount * -0x58);
        void* pResult = nullptr;
        FUN_00ce29c0(&pResult, pMoveStart, pEnd, pEnd, pEnd);
        pVec->mpEnd = (PlannerStepData*)((char*)pVec->mpEnd + nCount * 0x58);
        FUN_00ce2ba0(pPos, pMoveStart, pEnd);
        FUN_00ce2a50(pPos, (char*)pPos + nCount * 0x58, (void*)pValue);
        return;
    }

    uint32_t nSize = (uint32_t)((char*)pVec->mpEnd - (char*)pVec->mpBegin) / 0x58;
    uint32_t nNewCapacity = nSize * 2;
    if (nSize == 0)
        nNewCapacity = 1;
    uint32_t nRequired = nSize + nCount;
    if (nRequired < nNewCapacity)
        nRequired = nNewCapacity;
    PlannerStepData* pNew = nullptr;
    if (nRequired != 0)
        pNew = (PlannerStepData*)operator_new(nRequired * 0x58, "Simulator", 0, 0,
                                              kEastlAllocatorFile, 0xd1);
    PlannerStepData* pOldBegin = pVec->mpBegin;
    PlannerStepData* pOldEnd = pVec->mpEnd;
    void* pMid = FUN_00ce2930(pOldBegin, pPos, pNew);
    FUN_00ce0d90(pOldBegin, pPos, pNew);
    void* pTest = nullptr;
    FUN_00ce2ab0(pMid, nCount, (void*)pValue, pMid);
    PlannerStepData* pAfterNew = (PlannerStepData*)((char*)pMid + nCount * 0x58);
    void* pTail = FUN_00ce2930(pPos, pOldEnd, pAfterNew);
    FUN_00ce0d90(pPos, pOldEnd, pAfterNew);
    if (pOldBegin) {
        if (((int32_t*)pOldBegin)[-1] != 0)
            operator_delete_array(pOldBegin);
    }
    (void)pTest;
    pVec->mpEnd = (PlannerStepData*)pTail;
    pVec->mpBegin = pNew;
    pVec->mpCapacity = (PlannerStepData*)((char*)pNew + nRequired * 0x58);
}

// ---------------------------------------------------------------------------------------------
// 0x00ce5a80 -- eastl::vector<cTribePlanData>::push_back() (default-constructed element)
// ---------------------------------------------------------------------------------------------
// @ 0x00ce5a80 FUN_00ce5a80
void PlannerStepVector::FUN_00ce5a80()
{
    PlannerStepVector* pVec = this;
    if (pVec->mpEnd < pVec->mpCapacity) {
        PlannerStepData* pNew = pVec->mpEnd;
        pVec->mpEnd = pNew + 1;
        if (pNew)
            pNew->Init();
        return;
    }
    PlannerStepData value;
    pVec->FUN_00ce56a0(pVec->mpEnd, &value);
    value.mWorkers.Destroy();
}

// ---------------------------------------------------------------------------------------------
// 0x00ce5b30 -- eastl::vector<cTribePlanData>::resize(n)
// ---------------------------------------------------------------------------------------------
// @ 0x00ce5b30 FUN_00ce5b30
void PlannerStepVector::FUN_00ce5b30(uint32_t nCount)
{
    PlannerStepVector* pVec = this;
    PlannerStepData* pEnd = pVec->mpEnd;
    PlannerStepData* pBegin = pVec->mpBegin;
    uint32_t nSize = (uint32_t)((char*)pEnd - (char*)pBegin) / 0x58;
    if (nSize < nCount) {
        PlannerStepData value;
        pVec->FUN_00ce57e0(pEnd, nCount - nSize, &value);
        value.mWorkers.Destroy();
        return;
    }
    FUN_00ce5650((PlannerStepData*)((char*)pBegin + nCount * 0x58), pEnd);
}

// ---------------------------------------------------------------------------------------------
// 0x00ce5c40 -- eastl::vector<PlannerGroup>::insert(pos, count, value)
// ---------------------------------------------------------------------------------------------
// @ 0x00ce5c40 FUN_00ce5c40
void PlannerGroupVector::FUN_00ce5c40(PlannerGroup* pPos, uint32_t nCount,
                                      PlannerGroup* pValue)
{
    PlannerGroupVector* pVec = this;
    if ((uint32_t)((char*)pVec->mpCapacity - (char*)pVec->mpEnd) / 0x18 >= nCount) {
        if (nCount == 0)
            return;
        PlannerGroup value = *pValue;
        FUN_00ce4c40(&value.mpStepsBegin);
        PlannerGroup* pEnd = pVec->mpEnd;
        uint32_t nTail = (uint32_t)((char*)pVec->mpEnd - (char*)pPos) / 0x18;
        if (nCount < nTail) {
            FUN_00ce4ca0((char*)pEnd + nCount * -0x18, pEnd, pEnd, pEnd);
            pVec->mpEnd = (PlannerGroup*)((char*)pVec->mpEnd + nCount * 0x18);
            FUN_00ce5a40(pPos, (char*)pEnd + nCount * -0x18, pEnd);
            PlannerGroup* pIt = (PlannerGroup*)((char*)pPos + nCount * 0x18);
            for (; pPos != pIt; ++pPos) {
                pPos->mPlanType = value.mPlanType;
                ((PlannerGroupVector*)&pPos->mpStepsBegin)->FUN_00ce5050(
                             (const PlannerGroupVector*)&value.mpStepsBegin);
            }
        } else {
            FUN_00ce4d60(pEnd, nCount - nTail, &value, pPos);
            pVec->mpEnd = (PlannerGroup*)((char*)pVec->mpEnd + (nCount - nTail) * 0x18);
            FUN_00ce4ca0(pPos, pPos, pEnd, pVec->mpEnd);
            pVec->mpEnd = (PlannerGroup*)((char*)pVec->mpEnd + nTail * 0x18);
            PlannerGroup* pIt = (PlannerGroup*)((char*)pPos + nTail * 0x18);
            for (; pPos != pIt; ++pPos) {
                pPos->mPlanType = value.mPlanType;
                ((PlannerGroupVector*)&pPos->mpStepsBegin)->FUN_00ce5050(
                             (const PlannerGroupVector*)&value.mpStepsBegin);
            }
        }
        FUN_00ce0e00((PlannerGroup*)value.mpStepsBegin, (void*)value.mpStepsCapacity);
        if (value.mpStepsBegin) {
            if (((int32_t*)value.mpStepsBegin)[-1] != 0)
                operator_delete_array(value.mpStepsBegin);
        }
        return;
    }

    uint32_t nSize = (uint32_t)((char*)pVec->mpEnd - (char*)pVec->mpBegin) / 0x18;
    uint32_t nNewCapacity = nSize * 2;
    if (nSize == 0)
        nNewCapacity = 1;
    uint32_t nRequired = nSize + nCount;
    if (nRequired < nNewCapacity)
        nRequired = nNewCapacity;
    PlannerGroup* pNew = nullptr;
    if (nRequired != 0)
        pNew = (PlannerGroup*)operator_new(nRequired * 0x18, "Simulator", 0, 0,
                                           kEastlAllocatorFile, 0xd1);
    PlannerGroup* pOldBegin = pVec->mpBegin;
    PlannerGroup* pOldEnd = pVec->mpEnd;
    void* pMid = FUN_00ce4e10(pOldBegin, pPos, pNew);
    FUN_00ce2c10(pOldBegin, pPos, pNew);
    void* pResult = nullptr;
    FUN_00ce4d60(pMid, nCount, (void*)pValue, pMid);
    PlannerGroup* pAfterNew = (PlannerGroup*)((char*)pMid + nCount * 0x18);
    void* pTail = FUN_00ce4e10(pPos, pOldEnd, pAfterNew);
    FUN_00ce2c10(pPos, pOldEnd, pAfterNew);
    if (pOldBegin)
        operator_delete_array(pOldBegin);
    (void)pResult;
    pVec->mpEnd = (PlannerGroup*)pTail;
    pVec->mpBegin = pNew;
    pVec->mpCapacity = (PlannerGroup*)((char*)pNew + nRequired * 0x18);
}

// ---------------------------------------------------------------------------------------------
// 0x00ce5e90 -- eastl::vector<PlannerGroup>::insert(pos, value)
// ---------------------------------------------------------------------------------------------
// @ 0x00ce5e90 FUN_00ce5e90
void PlannerGroupVector::FUN_00ce5e90(PlannerGroup* pPos, PlannerGroup* pValue)
{
    PlannerGroupVector* pVec = this;
    PlannerGroup* pEnd = pVec->mpEnd;
    if (pEnd != pVec->mpCapacity) {
        if (pPos <= pValue && pValue < pEnd)
            ++pValue;
        if (pEnd) {
            pEnd->mPlanType = pEnd[-1].mPlanType;
            ((PlannerGroupVector*)&pEnd->mpStepsBegin)->CopyFrom(
                (const PlannerGroupVector*)&pEnd[-1].mpStepsBegin);
        }
        FUN_00ce5a40(pPos, pVec->mpEnd - 1, pVec->mpEnd);
        pPos->mPlanType = pValue->mPlanType;
        ((PlannerGroupVector*)&pPos->mpStepsBegin)->FUN_00ce5050(
                     (const PlannerGroupVector*)&pValue->mpStepsBegin);
        pVec->mpEnd = pVec->mpEnd + 1;
        return;
    }

    uint32_t nNewCapacity = (uint32_t)((char*)pEnd - (char*)pVec->mpBegin) / 0x18;
    PlannerGroup* pNew = nullptr;
    if (nNewCapacity == 0) {
        nNewCapacity = 1;
    } else {
        nNewCapacity *= 2;
    }
    if (nNewCapacity != 0)
        pNew = (PlannerGroup*)operator_new(nNewCapacity * 0x18, "Simulator", 0, 0,
                                           kEastlAllocatorFile, 0xd1);
    PlannerGroup* pOldBegin = pVec->mpBegin;
    PlannerGroup* pMid = (PlannerGroup*)FUN_00ce4e10(pOldBegin, pPos, pNew);
    FUN_00ce2c10(pOldBegin, pPos, pNew);
    if (pMid) {
        pMid->mPlanType = pValue->mPlanType;
        ((PlannerGroupVector*)&pMid->mpStepsBegin)->CopyFrom(
            (const PlannerGroupVector*)&pValue->mpStepsBegin);
    }
    PlannerGroup* pOldEnd = pVec->mpEnd;
    void* pTail = FUN_00ce4e10(pPos, pOldEnd, pMid + 1);
    FUN_00ce2c10(pPos, pOldEnd, pMid + 1);
    if (pVec->mpBegin)
        operator_delete_array(pVec->mpBegin);
    pVec->mpEnd = (PlannerGroup*)pTail;
    pVec->mpBegin = pNew;
    pVec->mpCapacity = (PlannerGroup*)((char*)pNew + nNewCapacity * 0x18);
}

// ---------------------------------------------------------------------------------------------
// 0x00ce5ff0 -- eastl::vector<PlannerGroup>: destroy the tail of the storage
// ---------------------------------------------------------------------------------------------
// @ 0x00ce5ff0 FUN_00ce5ff0
void PlannerGroupVector::FUN_00ce5ff0()
{
    PlannerGroupVector* pVec = this;
    PlannerGroup* pBegin = pVec->mpBegin;
    PlannerGroup* pEnd = pVec->mpEnd;
    PlannerGroup* pKeep = (PlannerGroup*)FUN_00ce5a00(pEnd, pEnd, pBegin);
    pVec->DoDestroyValues(pKeep, pVec->mpEnd);
    // retail divides the tail length by the negated element size, so the end pointer
    // folds back to the start of the vector
    pVec->mpEnd = (PlannerGroup*)((char*)pVec->mpEnd +
                                  (((char*)pEnd - (char*)pBegin) / -0x18) * 0x18);
}

// ---------------------------------------------------------------------------------------------
// 0x00ce6040 -- eastl::vector<PlannerGroup>::insert(end, value)
// ---------------------------------------------------------------------------------------------
// @ 0x00ce6040 FUN_00ce6040
PlannerGroup* PlannerGroupVector::FUN_00ce6040(PlannerGroup* pPos, PlannerGroup* pValue)
{
    PlannerGroupVector* pVec = this;
    int32_t nIndex = (int32_t)(pPos - pVec->mpBegin);
    if (pPos == pVec->mpEnd && pVec->mpEnd != pVec->mpCapacity) {
        PlannerGroup* pEnd = pVec->mpEnd;
        pVec->mpEnd = pEnd + 1;
        if (pEnd) {
            pEnd->mPlanType = pValue->mPlanType;
            ((PlannerGroupVector*)&pEnd->mpStepsBegin)->CopyFrom(
                (const PlannerGroupVector*)&pValue->mpStepsBegin);
        }
    } else {
        pVec->FUN_00ce5e90(pPos, pValue);
    }
    return (PlannerGroup*)((char*)pVec->mpBegin + nIndex * 0x18);
}

// eastl vector destructor for the step-value temporaries (0x00ae6970).
void FUN_00ce58a0(void* pVector)
{
    PlannerStepVector* pVec = (PlannerStepVector*)pVector;
    if (pVec->mpBegin)
        operator_delete_array(pVec->mpBegin);
}
