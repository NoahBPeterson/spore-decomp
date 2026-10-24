// Slice s00ce2330 -- SP tribe-planner plan table, plan-data copies, configuration lookup and the
// behaviour-tree stimulus predicates (module SPGonzago/SPTribePlanner.obj, retail build).
//
// Layouts are the retail ones recovered from the disassembly:
//   * cTribePlanData is 0x58 bytes.  Its WorkerList (fixed_vector<cCreature*,8>) lives at +0x1c and
//     the cached configuration pointer at +0x54.
//   * cTribePlanner keeps the behaviour-tree/order-manager pointer at +0x10, the plan-group array at
//     +0x14/+0x18/+0x1c and the per-plan-type re-execution times (SpVectorFloat) at +0x2c.
//   * A PlannerGroup is 0x18 bytes: plan type at +0x00 and the step vector at +0x04.
//   * cTribePlannerContext fields follow the 2008 PDB exactly (note currentFood is an int).
#include "types.h"

// Member-slot helpers for the opaque COM-style interfaces (a virtual at byte offset 4*n).
#define VSLOT(n) virtual void _v##n();
#define VSLOTS_0_3   VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
#define VSLOTS_4_7   VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
#define VSLOTS_8_11  VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11)
#define VSLOTS_12_15 VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15)
#define VSLOTS_16_19 VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19)
#define VSLOTS_0_10  VSLOTS_0_3 VSLOTS_4_7 VSLOT(8) VSLOT(9) VSLOT(10)

// ---------------------------------------------------------------------------------------------
// Opaque interfaces
// ---------------------------------------------------------------------------------------------
struct IInterface {                                     // EA::COM::IUnknown32-lookalike
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual void* AsInterface(uint32_t uType);          // +0x0c
};

struct ISerializer {                                    // EA::IO::IStream owner + record framing
    VSLOTS_0_3 VSLOT(4) VSLOT(5)
    virtual void* GetStream();                          // +0x18
    virtual void  EndRecord();                          // +0x1c
    virtual ISerializer* GetIO();                       // +0x20
};

struct IPropertyManager {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    virtual bool GetAllProperties(uint32_t uType, void* pArray);            // +0x2c
    VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17)
    virtual bool GetProperty(uint32_t uKey, uint32_t uType, void** ppOut);  // +0x48
    VSLOT(19)
};

// ---------------------------------------------------------------------------------------------
// Data types
// ---------------------------------------------------------------------------------------------
struct cTribe;
struct cTribePlanner;
struct cTribePlanData;
struct cTribePlanConfiguration;
struct PlannerGroup;

struct String16 {
    wchar_t* mpBegin;                                   // +0x00
    wchar_t* mpEnd;                                     // +0x04
    wchar_t* mpCapacity;                                // +0x08
};

extern uint32_t g_defaultUInt;              // 0x015d1164

// App::Variant-like 0x14-byte value (data, flags at +0x10, type at +0x12).
#pragma pack(push, 1)
struct Variant {
    uint32_t mData[4];
    uint16_t mFlags;
    uint16_t mType;
    void* GetStorage()
    {
        if (mFlags & 0x30) { return *(void**)mData; }
        else if (mType) return this;
        return 0;
    }
    uint32_t* GetUInt()
    {
        if (mType == 10 || mType == 0x10) { return (uint32_t*)GetStorage(); }
        return &g_defaultUInt;
    }
};
#pragma pack(pop)

// fixed_vector<cCreature*,8>: begin/end/capacity then the inline storage.
struct WorkerList {
    void** mpBegin;                                                 // +0x00
    void** mpEnd;                                                   // +0x04
    void** mpCapacityEnd;                                           // +0x08
    void*  mAlloc0;                                                 // +0x0c
    void*  mAlloc1;                                                 // +0x10
    void*  mAlloc2;                                                 // +0x14
    void*  mSlots[8];                                               // +0x18
    void assign(const WorkerList& src);                             // 0x01011cc0
    void erase(void** pFirst, void** pLast);                        // 0x00e25bd0
};

struct cTribePlanConfiguration {                        // retail, size 0x58
    float    mInitialCheckTimeDelay;                    // +0x00
    float    mCheckTime;                                // +0x04
    float    mTimeBetweenExecution;                     // +0x08
    uint32_t mFrequency;                                // +0x0c
    uint32_t mRequiredTools;                            // +0x10
    uint32_t mDesiredTools;                             // +0x14
    uint32_t mNumRequiredAdults;                        // +0x18
    uint32_t mNumDesiredAdults;                         // +0x1c
    uint32_t mMinTargetPopulation;                      // +0x20
    uint32_t mMaxTargetPopulation;                      // +0x24
    int32_t  mMinRelationshipToTarget;                  // +0x28
    int32_t  mMaxRelationshipToTarget;                  // +0x2c
    float    mFoodRate;                                 // +0x30
    int32_t  mRequiredFood;                             // +0x34
    int32_t  mDesiredFood;                              // +0x38
    uint8_t  mbExcludeChieftain;                        // +0x3c
    uint8_t  mPad3d[3];                                 // +0x3d
    uint32_t mModificationCount;                        // +0x40
    uint8_t  mDebugName[0x10];                          // +0x44 (eastl debug string)
    void*    mpPropertyList;                            // +0x54
};

struct cTribePlanData {                                 // size 0x58
    uint32_t mID;                                       // +0x00
    uint32_t mState;                                    // +0x04
    uint32_t mFrequency;                                // +0x08
    float    mCheckTime;                                // +0x0c
    int32_t  mFoodRequired;                             // +0x10
    float    mFoodAccumulated;                          // +0x14
    uint8_t  mbCheck;                                   // +0x18
    uint8_t  mPad19[3];                                 // +0x19
    WorkerList mWorkers;                                // +0x1c
    cTribePlanConfiguration* mpConfiguration;           // +0x54

    cTribePlanData* FUN_00ce2880(const cTribePlanData* pSrc);
    cTribePlanData* FUN_00ce28e0(const cTribePlanData* pSrc);
    void FUN_00ce0f70();                                // 0x00ce0f70 (release workers)
    cTribePlanConfiguration* GetConfiguration();
};

struct StepVector {                                     // eastl::vector<cTribePlanData,sp_allocator>
    cTribePlanData* mpBegin;                            // +0x00
    cTribePlanData* mpEnd;                              // +0x04
    cTribePlanData* mpCapacity;                         // +0x08
    void DoDestroyValues(cTribePlanData* pFirst, cTribePlanData* pLast);   // 0x00ce0e00
};

struct PlannerGroup {                                   // size 0x18
    uint32_t mPlanType;                                 // +0x00
    StepVector mSteps;                                  // +0x04
    uint32_t mPad10[2];                                 // +0x10
};

struct SpVectorFloat {                                  // size 0x48 (begin at caller offset +0x00)
    float* mpBegin;                                     // +0x00
    float* mpEnd;                                       // +0x04
    float* mpCapacity;                                  // +0x08
    uint8_t mPad0c[0x0c];                               // +0x0c
    float  mBuffer[12];                                 // +0x18
};

struct cAgentOrder {
    int32_t  mType;                                     // +0x00
    uint8_t  mPad04[0x24];                              // +0x04
    void*    mpTarget;                                  // +0x28
    uint8_t  mPad2c[0x0d];                              // +0x2c
    Variant  mParam;                                    // +0x39
};

struct cAgentOrderManager {                             // shared by the behaviour-tree data
    cAgentOrder* FirstPending();                        // 0x00bca2c0
    void PopFront();                                    // 0x00bcaf40
};

struct cBehaviorTreeData : cAgentOrderManager {         // cTribePlanner::mpBehaviorTreeData
    void* mpBehaviorTree;                               // +0x00
    void Write(int* pSerializer);                       // 0x00bc9a80
};

struct cTribePlanner {
    void* mpVtable;                                     // +0x00
    void* mpVtableInterface;                            // +0x04
    void* mpSerializableVtable;                         // +0x08
    uint8_t mbPaused;                                   // +0x0c
    uint8_t mPad0d[3];                                  // +0x0d
    cBehaviorTreeData* mpBehaviorTreeData;              // +0x10
    PlannerGroup* mpPlansBegin;                         // +0x14
    PlannerGroup* mpPlansEnd;                           // +0x18
    PlannerGroup* mpPlansCapacity;                      // +0x1c
    uint8_t mPad20[8];                                  // +0x20
    uint8_t mPlansCompare;                              // +0x28
    uint8_t mPad29[3];                                  // +0x29
    SpVectorFloat mTimeBetweenPlanExecutionByType;      // +0x2c
    cTribe* mpTribe;                                    // +0x74
    float   mAccumulatedDeltaTime;                      // +0x78

    cTribePlanData* GetPlanData(uint32_t uOrderType, uint32_t uKey);   // 0x00ce0e60
    const wchar_t* GetStatString(int nWhich);
    unsigned char Write(int* pSerializer);
};

struct cTribePlannerContext {                           // size 0x24 (2008 PDB layout)
    cTribe* mpTribe;                                    // +0x00
    cTribePlanner* mpTribePlanner;                      // +0x04
    uint32_t mToolsMask;                                // +0x08
    uint32_t mNumAdults;                                // +0x0c
    uint32_t mMaxAdults;                                // +0x10
    int32_t  mCurrentFood;                              // +0x14 (compared as int32 in retail)
    int32_t  mAttitudeToTarget;                         // +0x18
    uint32_t mTargetPopulation;                         // +0x1c
    IInterface* mpTarget;                               // +0x20
};

struct behavior_stimulus {
    uint8_t mPad00[0x0c];
    void*   mpPointers[8];                              // +0x0c
};

struct behavior_stimuli {
    behavior_stimulus mStimuli[1];                      // fixed_vector<stimulus,1> inline storage
};

struct cPlannerTargetView {                             // view of the AsInterface result
    uint8_t mPad00[0x20c];
    float   mValue;                                     // +0x20c
};

struct PlanConfigNode {
    uint32_t mTribeId;                                  // +0x00
    cTribePlanConfiguration mConfiguration;             // +0x04 (retail embeds the config inline)
    PlanConfigNode* mpNext;                             // chain link (at +0x48 in retail buckets)
};

// ---------------------------------------------------------------------------------------------
// Externals (fixed retail addresses; calls are relocation-masked by the checker)
// ---------------------------------------------------------------------------------------------
extern wchar_t  g_emptyString16[2];         // 0x01667bac

extern uint32_t g_statInit;                 // 0x0169b3ac
extern String16 g_statString;               // 0x0169b39c

extern uint32_t g_planCfgInit;              // 0x0169b3d0
extern float    g_planCfgLoadFactor;        // 0x0169b3c0
extern float    g_planCfgGrowthFactor;      // 0x0169b3c4
extern uint32_t g_planCfgBucketCount;       // 0x0169b3b8
extern void**   g_planCfgBuckets;           // 0x0169b3b4
extern uint32_t g_planCfgBuilt;             // 0x0169b3bc
extern uint32_t g_planCfgZero;              // 0x0169b3c8
extern void*    g_planCfgEmptyBucket;       // 0x0154df28
extern char     g_planTable[1];             // 0x0169b3b0 (cTribePlanData plan table)

extern float    g_closestWaterZero[3];      // 0x0169b3d8
extern char     g_varListNameA;             // 0x01581000
extern char     g_varListNameB;             // 0x01580de0

extern "C" int  __cdecl atexit(void (__cdecl*)(void));
extern "C" void __cdecl memmove(void* pDst, const void* pSrc, unsigned nCount);
extern "C" void __cdecl operator_delete_array(void* pMemory);

void __cdecl g_statStringDtor(void);        // 0x013c4880
void __cdecl g_planCfgTableDtor(void);      // 0x013c48b0

int  __cdecl WStr_Format(void* pDest, const wchar_t* pFormat, ...);          // 0x0041e050
void __cdecl WriteUint32(void* pStream, const void* pData, int nCount, int nArg);   // 0x0093aa70
void __cdecl ReadInt32(void* pStream, void* pData, int nCount, int nArg);           // 0x0093a9e0

PlannerGroup* __cdecl LowerBound(const PlannerGroup* pFirst, const PlannerGroup* pLast,
                                 const uint32_t* pKey, uint8_t uCompare);            // 0x00612db0
void* __stdcall FUN_00af13b0(cTribe* pTribe, int nKind, int nArg);                    // 0x00af13b0
bool  __fastcall FUN_00af0c90(void* pLayoutManager);                                 // 0x00af0c90
bool  __fastcall FUN_00c8e850(void* pObject);                                        // 0x00c8e850
bool  __fastcall FUN_00c8e870(void* pObject);                                        // 0x00c8e870
bool  __fastcall FUN_00b1fbf0(cTribe* pTribe);                                       // 0x00b1fbf0
float* __fastcall GetClosestWater(cTribe* pTribe);                                   // 0x00c8fe20
float __fastcall FUN_00cee380(void* pValue);                                        // 0x00cee380
void  __fastcall GetAny(behavior_stimuli* pStimuli);                                 // 0x00d997e0
void* __cdecl PropertyManager();                                                     // 0x0067de30
int   __fastcall FUN_00ce0ed0(void* pTable, const void* pEntry);                     // 0x00ce0ed0
void  __fastcall LoadTuning(cTribePlanConfiguration* pThis);                         // 0x00ce0150
cTribePlanConfiguration* __cdecl GetTribePlanConfiguration(uint32_t uTribeId);       // 0x00ce2d20

class cVarListSerializer {
public:
    void ctor(void* pOwner, const void* pName, uint32_t uType);                     // 0x00692f90
    unsigned char Serialize(int* pSerializer);                                      // 0x00692900
private:
    uint8_t mPad[0xa14];
};

struct PtrVector {
    uint32_t* mpBegin;                                  // +0x00
    uint32_t* mpEnd;                                    // +0x04
    uint32_t* mpCapacity;                               // +0x08
    void reserve(uint32_t uCount);
    void push_back(const uint32_t& uValue);
};

// ===========================================================================
// 0x00ce2330 -- cTribePlanData plan deactivation predicate (via the pending order)
// ===========================================================================
// @ 0x00ce2330 FUN_00ce2330
bool FUN_00ce2330(cTribePlannerContext* pContext, uint32_t uArg2, uint32_t uArg3, uint32_t uArg4,
                  uint32_t uArg5, float* pOut)
{
    cAgentOrder* pOrder = pContext->mpTribePlanner->mpBehaviorTreeData->FirstPending();
    if (pOrder != 0) {
        uint32_t uPlanType = (uint32_t)pOrder->mType;
        cTribePlanData* pData =
            pContext->mpTribePlanner->GetPlanData(uPlanType, *pOrder->mParam.GetUInt());
        if (pData != 0) {
            pData->mWorkers.erase(pData->mWorkers.mpBegin, pData->mWorkers.mpEnd);
            *pOut = 0.0f;
            return true;
        }
    }
    return false;
}

// ===========================================================================
// 0x00ce23b0 -- cTribePlanner::GetStatString (lazy static wide string)
// ===========================================================================
// @ 0x00ce23b0 cTribePlanner::GetStatString
const wchar_t* cTribePlanner::GetStatString(int nWhich)
{
    if ((g_statInit & 1) == 0) {
        g_statInit |= 1;
        g_statString.mpBegin = g_emptyString16;
        g_statString.mpEnd = g_emptyString16;
        g_statString.mpCapacity = &g_emptyString16[1];
        atexit(g_statStringDtor);
    }
    if (nWhich == 2)
        WStr_Format(&g_statString, L"Tribe Planner 0x%08x", (uint32_t)mpTribe);
    return g_statString.mpBegin;
}

// ===========================================================================
// 0x00ce2420 -- cTribePlanner::Write (serialise version tag, var-list and plan groups)
// ===========================================================================
// @ 0x00ce2420 cTribePlanner::Write
unsigned char cTribePlanner::Write(int* pSerializer)
{
    ISerializer* pSer = (ISerializer*)pSerializer;
    uint32_t uVersion = 0x9098aeb2;
    WriteUint32(pSer->GetIO()->GetStream(), &uVersion, 1, 0);

    cVarListSerializer varList;
    varList.ctor(this, &g_varListNameA, 0x1a80d26);
    unsigned char bResult = varList.Serialize(pSerializer);

    if (mpBehaviorTreeData)
        mpBehaviorTreeData->Write(pSerializer);

    uint32_t uGroupCount = (uint32_t)(mpPlansEnd - mpPlansBegin);
    WriteUint32(pSer->GetIO()->GetStream(), &uGroupCount, 1, 0);

    PlannerGroup* pGroup = mpPlansBegin;
    PlannerGroup* pGroupEnd = mpPlansEnd;
    if (pGroup != pGroupEnd) {
        do {
            uint32_t uPlanType = pGroup->mPlanType;
            uint32_t uStepCount = (uint32_t)(pGroup->mSteps.mpEnd - pGroup->mSteps.mpBegin);
            WriteUint32(pSer->GetIO()->GetStream(), &uPlanType, 1, 0);
            WriteUint32(pSer->GetIO()->GetStream(), &uStepCount, 1, 0);
            if (uStepCount != 0) {
                cTribePlanData* pStep = pGroup->mSteps.mpBegin;
                cTribePlanData* pStepEnd = pGroup->mSteps.mpEnd;
                do {
                    cVarListSerializer stepList;
                    stepList.ctor(pStep, &g_varListNameB, 0x1a80d26);
                    stepList.Serialize(pSerializer);
                    ++pStep;
                } while (pStep != pStepEnd);
            }
            ++pGroup;
        } while (pGroup != pGroupEnd);
    }
    return bResult;
}

// ===========================================================================
// 0x00ce27a0 -- read an int32 vector from the stream
// ===========================================================================
// @ 0x00ce27a0 FUN_00ce27a0
void FUN_00ce27a0(int* pSerializer, PtrVector* pVector)
{
    ISerializer* pSer = (ISerializer*)pSerializer;
    memmove(pVector->mpBegin, pVector->mpEnd, 0);
    pVector->mpEnd = pVector->mpBegin;

    uint32_t uCount = 0;
    ReadInt32(pSer->GetIO()->GetStream(), &uCount, 1, 0);
    pVector->reserve(uCount);

    uint32_t uIndex = 0;
    uint32_t uValue;
    while (uIndex < uCount) {
        ReadInt32(pSer->GetIO()->GetStream(), &uValue, 1, 0);
        uint32_t* pEnd = pVector->mpEnd;
        if (pEnd < pVector->mpCapacity) {
            pVector->mpEnd = pEnd + 1;
            *pEnd = uValue;
        } else {
            pVector->push_back(uValue);
        }
        ++uIndex;
    }
    pSer->EndRecord();
}

// ===========================================================================
// 0x00ce2880 -- copy-construct a cTribePlanData into raw storage (writes inline workers)
// ===========================================================================
// @ 0x00ce2880 cTribePlanData::FUN_00ce2880
cTribePlanData* cTribePlanData::FUN_00ce2880(const cTribePlanData* pSrc)
{
    mID = pSrc->mID;
    mState = pSrc->mState;
    mFrequency = pSrc->mFrequency;
    mCheckTime = pSrc->mCheckTime;
    mFoodRequired = pSrc->mFoodRequired;
    mFoodAccumulated = pSrc->mFoodAccumulated;
    mbCheck = pSrc->mbCheck;

    WorkerList& w = mWorkers;
    void** pSlots = (void**)&w.mSlots[0];
    w.mpBegin = pSlots;
    w.mpEnd = pSlots;
    w.mAlloc2 = 0;
    w.mpCapacityEnd = pSlots + 8;
    w.assign(pSrc->mWorkers);
    mpConfiguration = pSrc->mpConfiguration;
    return this;
}

// ===========================================================================
// 0x00ce28e0 -- assign a cTribePlanData (keeps existing workers allocation)
// ===========================================================================
// @ 0x00ce28e0 cTribePlanData::FUN_00ce28e0
cTribePlanData* cTribePlanData::FUN_00ce28e0(const cTribePlanData* pSrc)
{
    mID = pSrc->mID;
    mState = pSrc->mState;
    mFrequency = pSrc->mFrequency;
    mCheckTime = pSrc->mCheckTime;
    mFoodRequired = pSrc->mFoodRequired;
    mFoodAccumulated = pSrc->mFoodAccumulated;
    mbCheck = pSrc->mbCheck;
    mWorkers.assign(pSrc->mWorkers);
    mpConfiguration = pSrc->mpConfiguration;
    return this;
}

// ===========================================================================
// 0x00ce2930 -- construct [first,last) cTribePlanData into raw storage
// ===========================================================================
// @ 0x00ce2930 FUN_00ce2930
cTribePlanData* FUN_00ce2930(cTribePlanData* pFirst, cTribePlanData* pLast, cTribePlanData* pDest)
{
    if (pFirst != pLast) {
        while (pFirst != pLast) {
            if (pDest != 0) {
                pDest->mID = pFirst->mID;
                pDest->mState = pFirst->mState;
                pDest->mFrequency = pFirst->mFrequency;
                pDest->mCheckTime = pFirst->mCheckTime;
                pDest->mFoodRequired = pFirst->mFoodRequired;
                pDest->mFoodAccumulated = pFirst->mFoodAccumulated;
                pDest->mbCheck = pFirst->mbCheck;
                pDest->mWorkers.mpBegin = (void**)&pDest->mWorkers.mSlots[0];
                pDest->mWorkers.mpEnd = (void**)&pDest->mWorkers.mSlots[0];
                pDest->mWorkers.mAlloc2 = 0;
                pDest->mWorkers.mpCapacityEnd = (void**)&pDest->mWorkers.mSlots[0] + 8;
                pDest->mWorkers.assign(pFirst->mWorkers);
                pDest->mpConfiguration = pFirst->mpConfiguration;
            }
            ++pFirst;
            ++pDest;
        }
        return pDest;
    }
    return pDest;
}

// ===========================================================================
// 0x00ce29c0 -- construct [first,last) into storage, advancing *ppDest
// ===========================================================================
// @ 0x00ce29c0 FUN_00ce29c0
cTribePlanData** FUN_00ce29c0(cTribePlanData** ppDest, cTribePlanData* pFirst, cTribePlanData* pLast,
                              cTribePlanData* pDest)
{
    *ppDest = pDest;
    while (pFirst != pLast) {
        cTribePlanData* p = *ppDest;
        if (p != 0) {
            p->mID = pFirst->mID;
            p->mState = pFirst->mState;
            p->mFrequency = pFirst->mFrequency;
            p->mCheckTime = pFirst->mCheckTime;
            p->mFoodRequired = pFirst->mFoodRequired;
            p->mFoodAccumulated = pFirst->mFoodAccumulated;
            p->mbCheck = pFirst->mbCheck;
            p->mWorkers.mpBegin = (void**)&p->mWorkers.mSlots[0];
            p->mWorkers.mpEnd = (void**)&p->mWorkers.mSlots[0];
            p->mWorkers.mAlloc2 = 0;
            p->mWorkers.mpCapacityEnd = (void**)&p->mWorkers.mSlots[0] + 8;
            p->mWorkers.assign(pFirst->mWorkers);
            p->mpConfiguration = pFirst->mpConfiguration;
        }
        *ppDest = p + 1;
        ++pFirst;
    }
    return ppDest;
}

// ===========================================================================
// 0x00ce2a50 -- copy-assign [destFirst,destLast) from a single source
// ===========================================================================
// @ 0x00ce2a50 FUN_00ce2a50
void FUN_00ce2a50(cTribePlanData* pDestFirst, cTribePlanData* pDestLast, const cTribePlanData* pSrc)
{
    if (pDestFirst != pDestLast) {
        do {
            pDestFirst->mID = pSrc->mID;
            pDestFirst->mState = pSrc->mState;
            pDestFirst->mFrequency = pSrc->mFrequency;
            pDestFirst->mCheckTime = pSrc->mCheckTime;
            pDestFirst->mFoodRequired = pSrc->mFoodRequired;
            pDestFirst->mFoodAccumulated = pSrc->mFoodAccumulated;
            pDestFirst->mbCheck = pSrc->mbCheck;
            pDestFirst->mWorkers.assign(pSrc->mWorkers);
            pDestFirst->mpConfiguration = pSrc->mpConfiguration;
            ++pDestFirst;
        } while (pDestFirst != pDestLast);
    }
}

// ===========================================================================
// 0x00ce2ab0 -- construct n copies of a single cTribePlanData into raw storage
// ===========================================================================
// @ 0x00ce2ab0 FUN_00ce2ab0
void FUN_00ce2ab0(cTribePlanData* pDest, uint32_t uCount, const cTribePlanData* pSrc)
{
    if (uCount != 0) {
        do {
            if (pDest != 0) {
                pDest->mID = pSrc->mID;
                pDest->mState = pSrc->mState;
                pDest->mFrequency = pSrc->mFrequency;
                pDest->mCheckTime = pSrc->mCheckTime;
                pDest->mFoodRequired = pSrc->mFoodRequired;
                pDest->mFoodAccumulated = pSrc->mFoodAccumulated;
                pDest->mbCheck = pSrc->mbCheck;
                pDest->mWorkers.mpBegin = (void**)&pDest->mWorkers.mSlots[0];
                pDest->mWorkers.mpEnd = (void**)&pDest->mWorkers.mSlots[0];
                pDest->mWorkers.mAlloc2 = 0;
                pDest->mWorkers.mpCapacityEnd = (void**)&pDest->mWorkers.mSlots[0] + 8;
                pDest->mWorkers.assign(pSrc->mWorkers);
                pDest->mpConfiguration = pSrc->mpConfiguration;
            }
            --uCount;
            ++pDest;
        } while (uCount != 0);
    }
}

// ===========================================================================
// 0x00ce2b30 -- copy [srcFirst,srcLast) into dest, returning new dest end
// ===========================================================================
// @ 0x00ce2b30 FUN_00ce2b30
cTribePlanData* FUN_00ce2b30(const cTribePlanData* pSrcFirst, const cTribePlanData* pSrcLast,
                             cTribePlanData* pDest)
{
    while (pSrcFirst != pSrcLast) {
        pDest->mID = pSrcFirst->mID;
        pDest->mState = pSrcFirst->mState;
        pDest->mFrequency = pSrcFirst->mFrequency;
        pDest->mCheckTime = pSrcFirst->mCheckTime;
        pDest->mFoodRequired = pSrcFirst->mFoodRequired;
        pDest->mFoodAccumulated = pSrcFirst->mFoodAccumulated;
        pDest->mbCheck = pSrcFirst->mbCheck;
        pDest->mWorkers.assign(pSrcFirst->mWorkers);
        pDest->mpConfiguration = pSrcFirst->mpConfiguration;
        ++pSrcFirst;
        ++pDest;
    }
    return pDest;
}

// ===========================================================================
// 0x00ce2ba0 -- copy [srcFirst,srcLast) backwards, returning new dest begin
// ===========================================================================
// @ 0x00ce2ba0 FUN_00ce2ba0
cTribePlanData* FUN_00ce2ba0(const cTribePlanData* pSrcFirst, const cTribePlanData* pSrcLast,
                             cTribePlanData* pDestLast)
{
    while (pSrcLast != pSrcFirst) {
        --pSrcLast;
        --pDestLast;
        pDestLast->mID = pSrcLast->mID;
        pDestLast->mState = pSrcLast->mState;
        pDestLast->mFrequency = pSrcLast->mFrequency;
        pDestLast->mCheckTime = pSrcLast->mCheckTime;
        pDestLast->mFoodRequired = pSrcLast->mFoodRequired;
        pDestLast->mFoodAccumulated = pSrcLast->mFoodAccumulated;
        pDestLast->mbCheck = pSrcLast->mbCheck;
        pDestLast->mWorkers.assign(pSrcLast->mWorkers);
        pDestLast->mpConfiguration = pSrcLast->mpConfiguration;
    }
    return pDestLast;
}

// ===========================================================================
// 0x00ce2c10 -- destroy a [first,last) range of PlannerGroup
// ===========================================================================
// @ 0x00ce2c10 FUN_00ce2c10
PlannerGroup* FUN_00ce2c10(PlannerGroup* pFirst, PlannerGroup* pLast, PlannerGroup* pDest)
{
    while (pFirst != pLast) {
        pFirst->mSteps.DoDestroyValues(pFirst->mSteps.mpBegin, pFirst->mSteps.mpEnd);
        cTribePlanData* pBegin = pFirst->mSteps.mpBegin;
        if (pBegin != 0 && ((int32_t*)pBegin)[-1] != 0)
            operator_delete_array(pBegin);
        ++pFirst;
        ++pDest;
    }
    return pDest;
}

// ===========================================================================
// 0x00ce2c70 -- destroy a [first,last) range of PlannerGroup (in place)
// ===========================================================================
// @ 0x00ce2c70 FUN_00ce2c70
void __stdcall FUN_00ce2c70(PlannerGroup* pFirst, PlannerGroup* pLast)
{
    while (pFirst < pLast) {
        pFirst->mSteps.DoDestroyValues(pFirst->mSteps.mpBegin, pFirst->mSteps.mpEnd);
        cTribePlanData* pBegin = pFirst->mSteps.mpBegin;
        if (pBegin != 0 && ((int32_t*)pBegin)[-1] != 0)
            operator_delete_array(pBegin);
        ++pFirst;
    }
}

// ===========================================================================
// 0x00ce2d20 -- GetTribePlanConfiguration (lazy hash table, built from properties)
// ===========================================================================
// @ 0x00ce2d20 SP::GetTribePlanConfiguration
cTribePlanConfiguration* GetTribePlanConfiguration(uint32_t uTribeId)
{
    if ((g_planCfgInit & 1) == 0) {
        g_planCfgInit |= 1;
        g_planCfgLoadFactor = 1.0f;
        g_planCfgGrowthFactor = 2.0f;
        g_planCfgBucketCount = 1;
        g_planCfgBuckets = (void**)&g_planCfgEmptyBucket;
        g_planCfgBuilt = 0;
        g_planCfgZero = 0;
        atexit(g_planCfgTableDtor);
    }

    if (g_planCfgBuilt == 0) {
        uint32_t* pArrayBegin = 0;
        uint32_t* pArrayEnd = 0;
        IPropertyManager* pm = (IPropertyManager*)PropertyManager();
        pm->GetAllProperties(0x72d02c25, &pArrayBegin);

        void* pValue = 0;
        uint32_t* pCur = pArrayBegin;
        while (pCur != pArrayEnd) {
            uint32_t uKey = *pCur;
            if (pValue != 0) {
                void* pOld = pValue;
                pValue = 0;
                (*(void (__thiscall**)(void*))(*(int*)pOld + 4))(pOld);
            }
            if (pm->GetProperty(uKey, 0x72d02c25, &pValue)) {
                cTribePlanConfiguration* pConfig =
                    (cTribePlanConfiguration*)FUN_00ce0ed0(g_planTable, &uKey);
                void* pOldList = pConfig->mpPropertyList;
                if (pValue != pOldList) {
                    if (pValue != 0)
                        (*(void (__thiscall**)(void*))*(int*)pValue)(pValue);
                    pConfig->mpPropertyList = pValue;
                    if (pOldList != 0)
                        (*(void (__thiscall**)(void*))(*(int*)pOldList + 4))(pOldList);
                }
                LoadTuning(pConfig);
            }
            ++pCur;
        }
        if (pValue != 0)
            (*(void (__thiscall**)(void*))(*(int*)pValue + 4))(pValue);
        if (pArrayBegin != 0 && ((int32_t*)pArrayBegin)[-1] != 0)
            operator_delete_array(pArrayBegin);
    }

    PlanConfigNode* pNode = (PlanConfigNode*)g_planCfgBuckets[uTribeId % g_planCfgBucketCount];
    PlanConfigNode* pSentinel = (PlanConfigNode*)g_planCfgBuckets[g_planCfgBucketCount];
    PlanConfigNode* pFound = pNode;
    while (pFound != 0) {
        if (uTribeId == pFound->mTribeId)
            break;
        pFound = pFound->mpNext;
    }
    if (pFound == 0)
        pFound = pSentinel;
    if (pFound != pSentinel)
        return &pFound->mConfiguration;
    return 0;
}

// ===========================================================================
// 0x00ce2ee0 -- cTribePlanData::GetConfiguration (lazy cached pointer)
// ===========================================================================
// @ 0x00ce2ee0 cTribePlanData::GetConfiguration
cTribePlanConfiguration* cTribePlanData::GetConfiguration()
{
    if (mpConfiguration == 0)
        mpConfiguration = GetTribePlanConfiguration(mID);
    return mpConfiguration;
}

// ===========================================================================
// 0x00ce2f00 -- find the first eligible plan step of a plan type
// ===========================================================================
// @ 0x00ce2f00 FUN_00ce2f00
uint32_t FUN_00ce2f00(cTribePlannerContext* pContext, uint32_t uKey, char bIgnore)
{
    cTribePlanner* pPlanner = pContext->mpTribePlanner;
    PlannerGroup* pPlansEnd = pPlanner->mpPlansEnd;
    PlannerGroup* pFound = LowerBound(pPlanner->mpPlansBegin, pPlansEnd, &uKey, pPlanner->mPlansCompare);
    PlannerGroup* pGroup = pPlansEnd;
    if (pFound != pPlansEnd && pFound->mPlanType <= uKey && pFound != pFound + 1)
        pGroup = pFound;

    if (pGroup == pPlansEnd)
        return 0xffffffffu;

    cTribePlanData* pStepBegin = pGroup->mSteps.mpBegin;
    cTribePlanData* pStepEnd = pGroup->mSteps.mpEnd;
    uint32_t uCount = (uint32_t)(pStepEnd - pStepBegin);
    for (uint32_t uIndex = 0; uIndex < uCount; ++uIndex) {
        cTribePlanData* pStep = pStepBegin + uIndex;
        if (pStep->mpConfiguration == 0)
            pStep->mpConfiguration = GetTribePlanConfiguration(pStep->mID);
        cTribePlanConfiguration* pConfig = pStep->mpConfiguration;
        if ((pStep->mFrequency == 0xffffffffu || pStep->mFrequency != 0)
            && pStep->mbCheck != 0
            && ((pConfig->mMinRelationshipToTarget == -1 && pConfig->mMaxRelationshipToTarget == -1)
                || (pConfig->mMinRelationshipToTarget <= pContext->mAttitudeToTarget
                    && pContext->mAttitudeToTarget <= pConfig->mMaxRelationshipToTarget))
            && (((pConfig->mNumRequiredAdults <= pContext->mNumAdults
                  || pContext->mMaxAdults < pConfig->mNumRequiredAdults)
                 && pConfig->mRequiredFood <= pContext->mCurrentFood
                 && (pContext->mToolsMask & pConfig->mRequiredTools) == pConfig->mRequiredTools
                 && pConfig->mMinTargetPopulation <= pContext->mTargetPopulation
                 && pContext->mTargetPopulation <= pConfig->mMaxTargetPopulation)
                || bIgnore == 0))
            return uIndex;
    }
    return 0xffffffffu;
}

// ===========================================================================
// 0x00ce3020 -- DeactivatePlan
// ===========================================================================
// @ 0x00ce3020 SP::DeactivatePlan
void DeactivatePlan(cTribePlannerContext* pContext, uint32_t uPlanType, uint32_t uIndex, char bRelease)
{
    cTribePlanner* pPlanner = pContext->mpTribePlanner;
    cTribePlanData* pEntry = pPlanner->GetPlanData(uPlanType, uIndex);
    if (pEntry != 0) {
        if (bRelease != 0)
            pEntry->FUN_00ce0f70();
        if (pEntry->mState == 4 && uIndex < 0xc) {
            if (pEntry->mpConfiguration == 0)
                pEntry->mpConfiguration = GetTribePlanConfiguration(pEntry->mID);
            pPlanner->mTimeBetweenPlanExecutionByType.mpBegin[uIndex] =
                pEntry->mpConfiguration->mTimeBetweenExecution;
        }
        pEntry->mWorkers.erase(pEntry->mWorkers.mpBegin, pEntry->mWorkers.mpEnd);
        pEntry->mFoodAccumulated = 0.0f;
        pEntry->mFoodRequired = 0;
        pEntry->mState = 0;
    }

    cAgentOrder* pOrder = pPlanner->mpBehaviorTreeData->FirstPending();
    if (pOrder != 0 && pOrder->mType == (int)uPlanType)
        pPlanner->mpBehaviorTreeData->PopFront();
}

// ===========================================================================
// 0x00ce30d0 -- stimulus predicate (plan type 1)
// ===========================================================================
// @ 0x00ce30d0 FUN_00ce30d0
float FUN_00ce30d0(cTribePlannerContext* pContext, uint32_t uArg2, uint32_t uArg3, uint32_t uArg4,
                   behavior_stimuli* pStimuli, uint8_t* pOut)
{
    uint32_t uStep = FUN_00ce2f00(pContext, 1, 0);
    if (uStep != 0xffffffffu) {
        if (pStimuli != 0)
            GetAny(pStimuli);
        pStimuli->mStimuli[0].mpPointers[4] = (void*)uStep;
        pStimuli->mStimuli[0].mpPointers[3] = (void*)1;
        *pOut = 1;
        return 1.0f;
    }
    return 0.0f;
}

// ===========================================================================
// 0x00ce3120 -- stimulus predicate (plan type 2)
// ===========================================================================
// @ 0x00ce3120 FUN_00ce3120
float FUN_00ce3120(cTribePlannerContext* pContext, uint32_t uArg2, uint32_t uArg3, uint32_t uArg4,
                   behavior_stimuli* pStimuli, uint8_t* pOut)
{
    uint32_t uStep = FUN_00ce2f00(pContext, 2, 0);
    if (uStep != 0xffffffffu) {
        if (pStimuli != 0)
            GetAny(pStimuli);
        pStimuli->mStimuli[0].mpPointers[4] = (void*)uStep;
        pStimuli->mStimuli[0].mpPointers[3] = (void*)2;
        *pOut = 1;
        return 1.0f;
    }
    return 0.0f;
}

// ===========================================================================
// 0x00ce3170 -- stimulus predicate (plan type 3, requires a buildable layout)
// ===========================================================================
// @ 0x00ce3170 FUN_00ce3170
float FUN_00ce3170(cTribePlannerContext* pContext, uint32_t uArg2, uint32_t uArg3, uint32_t uArg4,
                   behavior_stimuli* pStimuli, uint8_t* pOut)
{
    cTribe* pTribe = pContext->mpTribe;
    if (FUN_00c8e870(pTribe)) {
        if (FUN_00af0c90(FUN_00af13b0(pTribe, 3, 0))) {
            uint32_t uStep = FUN_00ce2f00(pContext, 3, 0);
            if (uStep != 0xffffffffu) {
                if (pStimuli != 0)
                    GetAny(pStimuli);
                pStimuli->mStimuli[0].mpPointers[4] = (void*)uStep;
                pStimuli->mStimuli[0].mpPointers[3] = (void*)3;
                *pOut = 1;
                return 1.0f;
            }
        }
    }
    return 0.0f;
}

// ===========================================================================
// 0x00ce31e0 -- stimulus predicate (plan type 4, requires a buildable layout)
// ===========================================================================
// @ 0x00ce31e0 FUN_00ce31e0
float FUN_00ce31e0(cTribePlannerContext* pContext, uint32_t uArg2, uint32_t uArg3, uint32_t uArg4,
                   behavior_stimuli* pStimuli, uint8_t* pOut)
{
    cTribe* pTribe = pContext->mpTribe;
    if (FUN_00c8e850(pTribe)) {
        if (FUN_00af0c90(FUN_00af13b0(pTribe, 4, 0))) {
            uint32_t uStep = FUN_00ce2f00(pContext, 4, 0);
            if (uStep != 0xffffffffu) {
                if (pStimuli != 0)
                    GetAny(pStimuli);
                pStimuli->mStimuli[0].mpPointers[4] = (void*)uStep;
                pStimuli->mStimuli[0].mpPointers[3] = (void*)4;
                *pOut = 1;
                return 1.0f;
            }
        }
    }
    return 0.0f;
}

// ===========================================================================
// 0x00ce3250 -- stimulus predicate (plan type 5, requires water away from zero)
// ===========================================================================
// @ 0x00ce3250 FUN_00ce3250
float FUN_00ce3250(cTribePlannerContext* pContext, uint32_t uArg2, uint32_t uArg3, uint32_t uArg4,
                   behavior_stimuli* pStimuli, uint8_t* pOut)
{
    cTribe* pTribe = pContext->mpTribe;
    if (FUN_00b1fbf0(pTribe)) {
        float* pWater = GetClosestWater(pTribe);
        if (pWater[0] != g_closestWaterZero[0] || pWater[1] != g_closestWaterZero[1]
            || pWater[2] != g_closestWaterZero[2]) {
            if (FUN_00af0c90(FUN_00af13b0(pTribe, 5, 0))) {
                uint32_t uStep = FUN_00ce2f00(pContext, 5, 0);
                if (uStep != 0xffffffffu) {
                    if (pStimuli != 0)
                        GetAny(pStimuli);
                    pStimuli->mStimuli[0].mpPointers[4] = (void*)uStep;
                    pStimuli->mStimuli[0].mpPointers[3] = (void*)5;
                    *pOut = 1;
                    return 1.0f;
                }
            }
        }
    }
    return 0.0f;
}

// ===========================================================================
// 0x00ce3300 -- stimulus predicate (plan type 10, target eligibility)
// ===========================================================================
// @ 0x00ce3300 FUN_00ce3300
float FUN_00ce3300(cTribePlannerContext* pContext, uint32_t uArg2, uint32_t uArg3, uint32_t uArg4,
                   behavior_stimuli* pStimuli, uint8_t* pOut)
{
    cTribe* pTribe = pContext->mpTribe;
    if (pContext->mpTarget != 0) {
        void* pTarget = pContext->mpTarget->AsInterface(0x4f396a66);
        if (pTarget != 0) {
            if (FUN_00cee380(&((cPlannerTargetView*)pTarget)->mValue) > 0.0f) {
                if ((FUN_00c8e850(pTarget) && FUN_00c8e850(pTribe))
                    || (FUN_00c8e870(pTarget) && FUN_00c8e870(pTribe))) {
                    uint32_t uStep = FUN_00ce2f00(pContext, 10, 0);
                    if (uStep != 0xffffffffu) {
                        if (pStimuli != 0)
                            GetAny(pStimuli);
                        pStimuli->mStimuli[0].mpPointers[4] = (void*)uStep;
                        pStimuli->mStimuli[0].mpPointers[3] = (void*)10;
                        *pOut = 1;
                        return 1.0f;
                    }
                }
            }
        }
    }
    return 0.0f;
}