// s00cdfea0 -- SP tribe-planner / behavior-tree helper cluster.
//
// Retail symbols were scored from the Ghidra PDB candidates; the bodies below are written from
// the retail decompiles and disassembly with the PDB class layouts (tools/pdb_type.py) where the
// types are known.  Unknown containers are modelled by their observable leading fields.

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef int int32_t;

// ===========================================================================
// Shared types
// ===========================================================================

// EA::Variant -- 0x14 bytes: inline value or pointer, flags byte at +0x10, type word at +0x12.
struct Variant {
    union {
        int32_t  i;
        uint32_t u;
        float    f;
        void*    p;
    } mValue;               // +0x00
    uint32_t mPad04[3];     // +0x04 .. +0x0f
    uint8_t  mFlags;        // +0x10
    uint8_t  mPad11;        // +0x11
    uint16_t mType;         // +0x12
};

enum { kVariantTypeBool = 1, kVariantTypeInt = 9, kVariantTypeUInt = 10,
       kVariantTypeFloat = 13, kVariantTypeNull = 16 };

inline bool VariantIsInline(const Variant& v) { return (v.mFlags & 0x30) == 0; }

// cPropertyList: only the "get property" slot is used here (+0x24).
class cPropertyList {
public:
    virtual bool GetProperty(uint32_t uPropertyId, Variant** ppValue);   // +0x24
};

// Property ids used by the planner configuration tables.
enum {
    kPropInitialCheckTimeDelay = 0xb2176a80,
    kPropCheckTime             = 0x920a2318,
    kPropTimeBetweenExecution  = 0xcd927e7c,
    kPropFrequency             = 0x332c289d,
    kPropMinTargetPopulation   = 0xf90f8d19,
    kPropMaxTargetPopulation   = 0x6cf6d7b7,
    kPropMinRelationship       = 0x2b374411,
    kPropMaxRelationship       = 0xe32953b7,
    kPropFoodRate              = 0x1bbd28cf,
    kPropRequiredFood          = 0x8f1ec03e,
    kPropDesiredFood           = 0xdf8295c1,
    kPropExcludeChieftain      = 0x5d153ee8,
    kPropRequiredTools         = 0xe81611d7,
    kPropDesiredTools          = 0xdc57b356,
    kPropNumRequiredAdults     = 0x21c67d75,
    kPropNumDesiredAdults      = 0xbc88805a,
};

// SP::cTribePlanConfiguration (PDB size 0x58).
struct cTribePlanConfiguration {
    float    mInitialCheckTimeDelay;   // +0x00
    float    mCheckTime;               // +0x04
    float    mTimeBetweenExecution;    // +0x08
    uint32_t mFrequency;               // +0x0c
    uint32_t mRequiredTools;           // +0x10
    uint32_t mDesiredTools;            // +0x14
    uint32_t mNumRequiredAdults;       // +0x18
    uint32_t mNumDesiredAdults;        // +0x1c
    uint32_t mMinTargetPopulation;     // +0x20
    uint32_t mMaxTargetPopulation;     // +0x24
    int32_t  mMinRelationshipToTarget; // +0x28
    int32_t  mMaxRelationshipToTarget; // +0x2c
    float    mFoodRate;                // +0x30
    int32_t  mRequiredFood;            // +0x34
    int32_t  mDesiredFood;             // +0x38
    uint8_t  mbExcludeChieftain;       // +0x3c
    uint8_t  mPad3d[3];                // +0x3d
    uint32_t mModificationCount;       // +0x40
    uint32_t mDebugName[4];            // +0x44  eastl::basic_string<wchar_t> (4 words)
    void*    mpPropertyList;           // +0x54
};

// spstl::sp_fixed_vector<EA::AutoRefCount<cSPCreatureCitizen>,8> (0x34 bytes).
struct WorkerList {
    void*    mpBegin;          // +0x00
    void*    mpEnd;            // +0x04
    void*    mpCapacityEnd;    // +0x08
    uint32_t mPad0c[10];       // +0x0c inline storage
};

// SP::cTribePlanData (PDB size 0x54).
struct cTribePlanData {
    uint32_t mID;                 // +0x00
    uint32_t mState;              // +0x04
    uint32_t mFrequency;          // +0x08
    float    mCheckTime;          // +0x0c
    int32_t  mFoodRequired;       // +0x10
    float    mFoodAccumulated;    // +0x14
    uint8_t  mbCheck;             // +0x18
    uint8_t  mPad19[3];           // +0x19
    WorkerList mWorkers;          // +0x1c
    cTribePlanConfiguration* mpConfiguration;   // +0x50
};

// Plan-table entry used by the copy helper 00cdffc0 (0x44 bytes).
struct PlanEntry {
    float    mPosition[3];        // +0x00
    uint32_t mPad0c[8];           // +0x0c .. +0x2b
    uint32_t mPad2c;              // +0x2c
    float    mScale;              // +0x30
    uint32_t mPad34;              // +0x34
    uint32_t mPad38;              // +0x38
    uint8_t  mByte3c;             // +0x3c
    uint8_t  mPad3d[3];           // +0x3d
    void*    mpObject;            // +0x40  AutoRefCount payload (AddRef/Release)
};

// Generic "citizen-like" AI noun used by the planner filters.
struct cAIFlags;
struct cCitizen {
    virtual bool IsBusy();          // +0x2c
    uint32_t mPad04[0x4c];          // +0x04 .. +0x133
    uint8_t  mByte134;              // +0x134
    uint8_t  mByte135;              // +0x135
    uint8_t  mPad136[0xa16];        // +0x136 .. +0xb4b
    cAIFlags* mpAIFlags;            // +0xb4c
    uint8_t  mPadB50[0xe];          // +0xb50 .. +0xb5d
    uint8_t  mByteB5e;              // +0xb5e
};

struct cAIFlags {
    uint32_t mPad00[0x73];          // +0x00 .. +0x1cb
    uint32_t mFlags1cc;             // +0x1cc
};

// Plan table: map<unsigned int, Variant> stored as a sorted array of 24-byte pairs.
struct PlanTableEntry {
    uint32_t mKey;                  // +0x00
    void*    mpBegin;               // +0x04  cTribePlanData* array
    void*    mpEnd;                 // +0x08
    uint32_t mPad0c[3];             // +0x0c
};

struct PlanTable {
    uint32_t mPad00;                // +0x00
    uint32_t* mpEntries;            // +0x04  current entry array
    int32_t  mEntryIndex;           // +0x08  current slot index
    uint32_t mPad0c[2];             // +0x0c .. +0x13
    PlanTableEntry* mpBegin;        // +0x14
    PlanTableEntry* mpEnd;          // +0x18
    uint32_t mPad1c[3];             // +0x1c .. +0x27
    uint8_t  mByte28;               // +0x28
};

// Behavior-tree data owned by cTribePlanner.
struct cBehaviorTreeData {
    void*    mpBehaviorTree;        // +0x00
    uint32_t mMemoryBlocks;         // +0x04
    uint32_t mpFreeFunction;        // +0x08
    int32_t  mAllocatorFlags;       // +0x0c
};

struct cTribePlanner {
    cBehaviorTreeData* mpBehaviorTreeData;   // +0x00
    void*    mpAuxObject;                    // +0x04
};

struct FrameContext {
    void*    mpOwner;               // +0x00
    uint32_t mPad04;                // +0x04
    uint32_t mPad08;                // +0x08
    uint32_t mPad0c;                // +0x0c
    uint32_t mValue10;              // +0x10
    int*     mpRef;                 // +0x14
    cTribePlanner* mpPlanner;       // +0x18
};

// Order object carrying the raid-target variant (+0x4d).
struct cOrderObject {
    uint32_t mPad00[0x13];          // +0x00 .. +0x4b
    uint8_t  mPad4c;                // +0x4c
    Variant  mTargetVariant;        // +0x4d
};

// SP order record handled by the PLANNER_RAIDING leaves (fields used at +0x18/+0x1c).
struct cPlanRecord {
    uint32_t mPad00[6];             // +0x00 .. +0x17
    uint32_t mValue18;              // +0x18
    uint32_t mValue1c;              // +0x1c
};

// Timer record returned by FUN_00bcaf70.
struct cPlanTimer {
    uint32_t mPad00[0xe];           // +0x00 .. +0x37
    uint8_t  mbActive;              // +0x38
    Variant  mValue39;              // +0x39
    Variant  mValue4d;              // +0x4d
};

struct Vec3 {
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08
};

// ===========================================================================
// Externals (retail addresses)
// ===========================================================================
extern void __fastcall GetAny(void* pStimuli);                                   // 0x00d997e0
extern void* FUN_00d99420(void* pObject, int iFilter);                           // 0x00d99420
extern void FUN_00d996e0(void* pList, void* pStimuli);                           // 0x00d996e0
extern int* FUN_00bca2c0(void);                                                  // 0x00bca2c0
extern void FUN_00bcb3d0(void);                                                  // 0x00bcb3d0
extern void FUN_00bc86e0(double dTime, void* pTree, void* pArg, void* pBlocks,
                         void* pFree, int iAlign);                               // 0x00bc86e0
extern void* GameTimeManager(void);                                              // 0x00b31670
extern unsigned long long FUN_00b316c0(void);                                    // 0x00b316c0
extern int FUN_00b3d230(void);                                                   // 0x00b3d230
extern void* FUN_00bcaf70(void* pTable, int iPlanIndex, int iFlag);              // 0x00bcaf70
extern void FUN_00bcaf40(void* pNoun);                                           // 0x00bcaf40
extern void FUN_00bc97f0(int iA, uint32_t uFlags, float fRange, int iB);         // 0x00bc97f0
extern void FUN_00ce0bf0(uint32_t* pResult, const void* pSource);                // 0x00ce0bf0
extern void FUN_00ce0c50(uint32_t* pResult, uint32_t* pValue, uint32_t uFlags);  // 0x00ce0c50
extern void ForceOrdersUpdate(void* pCitizen);                        // cSPCreatureCitizen
extern void EraseRange(void* pBegin, void* pEnd);                                // eastl::vector::erase
extern void RestartTimer(void* pTimer);                                          // SP::cSPTimer::Restart
extern void AssignVariantUInt(Variant* pVariant, uint32_t uValue);               // Variant::operator=
extern void GetOrderPosition(void* pOrder, Vec3* pPosition);                     // +0x120 vtable +0x2c
extern bool GetPropertyAsUint32Array(cPropertyList* pList, uint32_t uPropertyId,
                                     uint32_t** ppArray, int* piCount);          // property helper
extern void* EventLog(uint32_t uId, uint32_t uSubId, void* pPos, int iA, int iB, int iC);
extern void PostFeedbackEvent(void* pLog, uint32_t uId, uint32_t uSubId, void* pPos,
                              int iA, int iB, int iC);
extern void* GetSystemAT(void);                                                  // EA::Audio::GetSystemAT
extern void Start3dSoundByName(uint32_t uName, int iHandle, float x, float y, float z);
extern void __cdecl operator_delete(void* pBlock);

// This slice's later helpers, used before their definitions.
PlanEntry* FUN_00cdffc0(PlanEntry* pThis, const PlanEntry* pSrc);
PlanTableEntry* FUN_00ce0e60(PlanTable* pTable, uint32_t uPlanId, uint32_t uIndex);

// ===========================================================================
// 0x00cdfea0 -- planner candidate filter
// ===========================================================================
// @ 0x00cdfea0
bool FUN_00cdfea0(cCitizen* pMember)
{
    if (!pMember)
        return false;
    if (pMember->IsBusy())
        return false;
    if (pMember->mByte135 == 0)
        return false;
    if (pMember->mByteB5e != 0)
        return false;
    if ((pMember->mpAIFlags->mFlags1cc & 0x2000000) != 0)
        return false;
    return true;
}

// ===========================================================================
// 0x00cdfef0 -- behavior-tree "set task" leaf
// ===========================================================================
// @ 0x00cdfef0
long double FUN_00cdfef0(int iNode, int iUnused1, int iUnused2, int iUnused3,
                         void* pStimuli, bool* pbOut, int iUnused5, int* pParams)
{
    if (pStimuli)
        GetAny(pStimuli);

    *pbOut = true;

    void* pObject = (void*)(*(int*)(*(int*)(iNode + 4) + 0x10) + 0x1d0);
    void* pList = FUN_00d99420(pObject, pParams[0x2d / 4]);
    FUN_00d996e0(pList, pStimuli);
    return 1.0;
}

// ===========================================================================
// 0x00cdff70 -- skip candidates that fail the planner filter
// ===========================================================================
// @ 0x00cdff70
int** __fastcall FUN_00cdff70(int*** pIter)
{
    for (;;) {
        *pIter = *pIter + 1;
        if (*pIter == pIter[1])
            return (int**)pIter;
        cCitizen* pMember = (cCitizen*)**pIter;
        if (FUN_00cdfea0(pMember))
            return (int**)pIter;
    }
}

// ===========================================================================
// 0x00cdffc0 -- copy a plan entry and take a reference on its object
// ===========================================================================
// @ 0x00cdffc0
PlanEntry* FUN_00cdffc0(PlanEntry* pThis, const PlanEntry* pSrc)
{
    pThis->mPosition[0] = pSrc->mPosition[0];
    pThis->mPosition[1] = pSrc->mPosition[1];
    pThis->mPosition[2] = pSrc->mPosition[2];
    for (int i = 0; i < 8; ++i)
        pThis->mPad0c[i] = pSrc->mPad0c[i];
    pThis->mPad2c = pSrc->mPad2c;
    pThis->mScale = pSrc->mScale;
    pThis->mPad34 = pSrc->mPad34;
    pThis->mPad38 = pSrc->mPad38;
    pThis->mByte3c = pSrc->mByte3c;
    pThis->mpObject = pSrc->mpObject;
    if (pThis->mpObject)
        (*(void (__thiscall**)(void*))pThis->mpObject) (pThis->mpObject);
    return pThis;
}

// ===========================================================================
// 0x00ce0150 -- SP::cTribePlanConfiguration::LoadTuning
// ===========================================================================
static bool ReadVariant(cPropertyList* pList, uint32_t uPropertyId, Variant** ppValue)
{
    if (!pList)
        return false;
    return pList->GetProperty(uPropertyId, ppValue);
}

static float VariantFloat(const Variant* pValue)
{
    if (pValue->mType == kVariantTypeFloat || pValue->mType == kVariantTypeNull) {
        if (VariantIsInline(*pValue))
            return pValue->mValue.f;
        return *(const float*)pValue->mValue.p;
    }
    return 0.0f;
}

static uint32_t VariantUInt(const Variant* pValue)
{
    if (pValue->mType == kVariantTypeUInt || pValue->mType == kVariantTypeNull) {
        if (VariantIsInline(*pValue))
            return pValue->mValue.u;
        return *(const uint32_t*)pValue->mValue.p;
    }
    return 0;
}

static int32_t VariantInt(const Variant* pValue)
{
    if (pValue->mType == kVariantTypeInt || pValue->mType == kVariantTypeNull) {
        if (VariantIsInline(*pValue))
            return pValue->mValue.i;
        return *(const int32_t*)pValue->mValue.p;
    }
    return 0;
}

static bool VariantBool(const Variant* pValue)
{
    if (pValue->mType == kVariantTypeBool || pValue->mType == kVariantTypeNull) {
        if (VariantIsInline(*pValue))
            return pValue->mValue.i != 0;
        return *(const uint8_t*)pValue->mValue.p != 0;
    }
    return false;
}

// @ 0x00ce0150
void LoadTuning(cTribePlanConfiguration* pThis)
{
    Variant* pValue = 0;
    cPropertyList* pList = (cPropertyList*)pThis->mpPropertyList;

    pThis->mInitialCheckTimeDelay = ReadVariant(pList, kPropInitialCheckTimeDelay, &pValue)
                                    ? VariantFloat(pValue) : 0.0f;
    pThis->mCheckTime = ReadVariant(pList, kPropCheckTime, &pValue) ? VariantFloat(pValue) : 30.0f;
    pThis->mTimeBetweenExecution = ReadVariant(pList, kPropTimeBetweenExecution, &pValue)
                                   ? VariantFloat(pValue) : 0.0f;
    pThis->mFrequency = ReadVariant(pList, kPropFrequency, &pValue) ? VariantUInt(pValue) : 0xffffffffu;
    pThis->mMinTargetPopulation = ReadVariant(pList, kPropMinTargetPopulation, &pValue)
                                  ? VariantUInt(pValue) : 0;
    pThis->mMaxTargetPopulation = ReadVariant(pList, kPropMaxTargetPopulation, &pValue)
                                  ? VariantUInt(pValue) : 100;
    pThis->mMinRelationshipToTarget = ReadVariant(pList, kPropMinRelationship, &pValue)
                                      ? VariantInt(pValue) : -1;
    pThis->mMaxRelationshipToTarget = ReadVariant(pList, kPropMaxRelationship, &pValue)
                                      ? VariantInt(pValue) : -1;
    pThis->mFoodRate = ReadVariant(pList, kPropFoodRate, &pValue) ? VariantFloat(pValue) : 0.1f;
    pThis->mRequiredFood = ReadVariant(pList, kPropRequiredFood, &pValue) ? VariantInt(pValue) : 0;
    pThis->mDesiredFood = ReadVariant(pList, kPropDesiredFood, &pValue) ? VariantInt(pValue) : 0;
    pThis->mbExcludeChieftain = ReadVariant(pList, kPropExcludeChieftain, &pValue)
                                ? VariantBool(pValue) : false;

    pThis->mRequiredTools = 0;
    uint32_t* pArray = 0;
    int iCount = 0;
    if (GetPropertyAsUint32Array(pList, kPropRequiredTools, &pArray, &iCount) && iCount > 0) {
        for (int i = 0; i < iCount; ++i)
            pThis->mRequiredTools |= 1u << (pArray[i] & 0x1f);
    }

    pThis->mDesiredTools = 0;
    pArray = 0;
    iCount = 0;
    if (GetPropertyAsUint32Array(pList, kPropDesiredTools, &pArray, &iCount) && iCount > 0) {
        for (int i = 0; i < iCount; ++i)
            pThis->mDesiredTools |= 1u << (pArray[i] & 0x1f);
    }

    pThis->mNumRequiredAdults = ReadVariant(pList, kPropNumRequiredAdults, &pValue)
                                ? VariantUInt(pValue) : 1;
    pThis->mNumDesiredAdults = ReadVariant(pList, kPropNumDesiredAdults, &pValue)
                               ? VariantUInt(pValue) : 1;
}

// ===========================================================================
// 0x00ce09b0 -- "planner has a raid target" predicate
// ===========================================================================
// @ 0x00ce09b0
long double FUN_00ce09b0()
{
    cOrderObject* pOrder = (cOrderObject*)FUN_00bca2c0();
    if (!pOrder)
        return 0.0;
    return (VariantInt(&pOrder->mTargetVariant) == 3) ? 1.0 : 0.0;
}

// ===========================================================================
// 0x00ce0a20 -- SP::cTribePlanner::Shutdown
// ===========================================================================
// @ 0x00ce0a20
void Shutdown(cTribePlanner* pThis)
{
    if (pThis->mpBehaviorTreeData) {
        if (pThis->mpBehaviorTreeData->mpBehaviorTree) {
            if (FUN_00b3d230() != 0 && GameTimeManager() != 0) {
                FrameContext ctx;
                ctx.mpOwner = pThis->mpAuxObject;
                ctx.mPad04 = 0;
                ctx.mPad08 = 0;
                ctx.mPad0c = 0;
                ctx.mValue10 = 0;
                ctx.mpRef = 0;
                ctx.mpPlanner = pThis;

                GameTimeManager();
                unsigned long long uTime = FUN_00b316c0();
                double dTime = (double)(uTime & 0x7fffffffffffffffull) * 0.001;
                cBehaviorTreeData* pData = pThis->mpBehaviorTreeData;
                FUN_00bc86e0(dTime, pData->mpBehaviorTree, &ctx, (void*)pData->mMemoryBlocks,
                             (void*)pData->mpFreeFunction, pData->mAllocatorFlags);
                if (ctx.mpRef)
                    (*(void (__thiscall**)(void*))(*(int*)ctx.mpRef + 4)) (ctx.mpRef);
            }
        }
        FUN_00bcb3d0();
        pThis->mpBehaviorTreeData = 0;
    }

    if (pThis->mpAuxObject) {
        void* pObject = pThis->mpAuxObject;
        pThis->mpAuxObject = 0;
        (*(void (__thiscall**)(void*))(*(int*)pObject + 4)) (pObject);
    }
}

// ===========================================================================
// 0x00ce0b20 -- initialize a plan-work iterator
// ===========================================================================
// @ 0x00ce0b20
int** FUN_00ce0b20(int** pIter, int** pSource, uint32_t uUnused)
{
    int* pBegin = *pSource;
    pIter[0] = pBegin;
    int* pEnd = pSource[1];
    pIter[1] = pEnd;
    if (pBegin != pEnd) {
        if (!FUN_00cdfea0((cCitizen*)*pBegin))
            FUN_00cdff70((int***)pIter);
    }
    return pIter;
}

// ===========================================================================
// 0x00ce0b60 -- does the worker list contain this plan id?
// ===========================================================================
// @ 0x00ce0b60
bool FUN_00ce0b60(WorkerList* pWorkers, int iPlanId)
{
    if (!pWorkers)
        return false;

    int** pIter = (int**)&pWorkers->mpBegin;
    if (pWorkers->mpBegin == pWorkers->mpEnd)
        return false;

    if (!FUN_00cdfea0((cCitizen*)*(int*)pWorkers->mpBegin))
        FUN_00cdff70((int***)&pWorkers->mpBegin);

    while (pWorkers->mpBegin != pWorkers->mpEnd) {
        int* pNoun = FUN_00bca2c0();
        if (pNoun && *pNoun == iPlanId)
            return true;
        FUN_00cdff70((int***)&pWorkers->mpBegin);
    }
    return false;
}

// ===========================================================================
// 0x00ce0d90 -- destroy a range of plan entries
// ===========================================================================
// @ 0x00ce0d90
int FUN_00ce0d90(char* pBegin, char* pEnd, char* pOut)
{
    while (pBegin != pEnd) {
        cTribePlanData* pData = (cTribePlanData*)pBegin;
        int** ppIter = (int**)&pData->mWorkers.mpBegin;
        int** ppEnd = (int**)&pData->mWorkers.mpEnd;
        for (ppIter = (int**)&pData->mWorkers.mpBegin; ppIter < ppEnd; ++ppIter) {
            if (*ppIter)
                (*(void (__thiscall**)(void*))(*(int*)*ppIter + 4)) (*ppIter);
        }
        void* pBlock = pData->mWorkers.mpBegin;
        if (pBlock && *(int*)((char*)pBlock - 4) != 0)
            operator_delete((char*)pBlock - 4);
        pBegin += 0x58;
        pOut += 0x58;
    }
    return (int)pOut;
}

// ===========================================================================
// 0x00ce0e00 -- eastl::vector<cTribePlanData>::DoDestroyValues
// ===========================================================================
// @ 0x00ce0e00
void FUN_00ce0e00(char* pBegin, char* pEnd)
{
    for (; pBegin < pEnd; pBegin += 0x58) {
        cTribePlanData* pData = (cTribePlanData*)pBegin;
        int** ppIter = (int**)&pData->mWorkers.mpBegin;
        int** ppEnd = (int**)&pData->mWorkers.mpEnd;
        for (ppIter = (int**)&pData->mWorkers.mpBegin; ppIter < ppEnd; ++ppIter) {
            if (*ppIter)
                (*(void (__thiscall**)(void*))(*(int*)*ppIter + 4)) (*ppIter);
        }
        void* pBlock = pData->mWorkers.mpBegin;
        if (pBlock && *(int*)((char*)pBlock - 4) != 0)
            operator_delete((char*)pBlock - 4);
    }
}

// ===========================================================================
// 0x00ce0e60 -- find a plan entry by id
// ===========================================================================
// @ 0x00ce0e60
PlanTableEntry* FUN_00ce0e60(PlanTable* pTable, uint32_t uPlanId, uint32_t uIndex)
{
    PlanTableEntry* pEnd = pTable->mpEnd;
    PlanTableEntry* pEntry = pTable->mpBegin;
    while (pEntry != pEnd && pEntry->mKey < uPlanId)
        ++pEntry;
    if (pEntry == pEnd || uPlanId < pEntry->mKey)
        pEntry = pEnd;
    if (pEntry != pEnd) {
        uint32_t uCount = (uint32_t)(((char*)pEntry->mpEnd - (char*)pEntry->mpBegin) / 0x58);
        if (uIndex < uCount)
            return (PlanTableEntry*)((char*)pEntry->mpBegin + uIndex * 0x58);
    }
    return 0;
}

// ===========================================================================
// 0x00ce0ed0 -- insert-or-find a plan entry for a new order
// ===========================================================================
// @ 0x00ce0ed0
int FUN_00ce0ed0(PlanTable* pTable, const PlanEntry* pOrder)
{
    uint32_t uEntry[2] = { 0, 0 };
    FUN_00ce0bf0(uEntry, pOrder);

    uint32_t uCurrent = pTable->mpEntries[pTable->mEntryIndex];
    if (uEntry[0] != uCurrent)
        return (int)(uEntry[0] + 4);

    PlanEntry entry;
    uint32_t uValue[18];
    uValue[0] = *(const uint32_t*)pOrder;
    entry.mpObject = 0;
    FUN_00cdffc0(&entry, pOrder);
    uEntry[0] &= 0xffffff00u;
    FUN_00ce0c50(uEntry, uValue, uEntry[0]);
    int iResult = (int)(uEntry[0] + 4);
    if (entry.mpObject)
        (*(void (__thiscall**)(void*))(*(int*)entry.mpObject + 4)) (entry.mpObject);
    return iResult;
}

// ===========================================================================
// 0x00ce0f70 -- drop every worker of a plan and erase the list
// ===========================================================================
// @ 0x00ce0f70
void __fastcall FUN_00ce0f70(cTribePlanData* pData)
{
    int** ppIter = (int**)&pData->mWorkers.mpBegin;
    int** ppEnd = (int**)&pData->mWorkers.mpEnd;
    if (ppIter != ppEnd) {
        if (!FUN_00cdfea0((cCitizen*)*ppIter))
            FUN_00cdff70((int***)&pData->mWorkers.mpBegin);
        while (pData->mWorkers.mpBegin != pData->mWorkers.mpEnd) {
            cCitizen* pWorker = (cCitizen*)*(int*)pData->mWorkers.mpBegin;
            FUN_00bcaf40(pWorker);
            ForceOrdersUpdate(pWorker);
            FUN_00cdff70((int***)&pData->mWorkers.mpBegin);
        }
    }
    EraseRange(pData->mWorkers.mpBegin, pData->mWorkers.mpEnd);
}

// ===========================================================================
// 0x00ce0ff0 -- restart a plan timer record
// ===========================================================================
// @ 0x00ce0ff0
cPlanTimer* FUN_00ce0ff0(int iUnused, PlanTable* pTable, uint32_t uKey, uint32_t uIndex,
                         int iPlanId)
{
    cPlanTimer* pTimer = (cPlanTimer*)FUN_00ce0e60(pTable, uKey, uIndex);
    int iPlan = iPlanId;
    uint32_t uFrequency = pTimer->mPad00[2];
    if (uFrequency != 0xffffffffu && uFrequency != 0)
        pTimer->mPad00[2] = uFrequency - 1;

    cPlanTimer* pCreated = (cPlanTimer*)FUN_00bcaf70(pTable, iPlanId, 1);
    pCreated->mbActive = (iPlan != 0);
    RestartTimer(&pCreated->mPad00[2]);
    AssignVariantUInt(&pCreated->mValue39, uKey);
    AssignVariantUInt(&pCreated->mValue4d, uIndex);
    return pCreated;
}

// ===========================================================================
// 0x00ce1060 -- activate the "raiding" order state
// ===========================================================================
// @ 0x00ce1060
bool FUN_00ce1060(PlanTable* pTable, int iUnused1, int iUnused2, int iUnused3,
                  uint32_t* pOut, cPlanRecord* pRecord)
{
    uint32_t uId = pRecord->mValue18;
    pOut[0] = uId;
    uint32_t uState = pRecord->mValue1c;
    pOut[1] = uState;

    cTribePlanData* pData = (cTribePlanData*)FUN_00ce0e60(pTable, uId, uState);
    if (!pData)
        return false;

    EraseRange(pData->mWorkers.mpBegin, pData->mWorkers.mpEnd);
    FUN_00ce0ff0((int)pTable, pTable, pOut[0], pOut[1], (int)pTable->mpEntries[pTable->mEntryIndex]);
    return true;
}

// ===========================================================================
// 0x00ce10c0 -- deactivate the "raiding" order state
// ===========================================================================
// @ 0x00ce10c0
bool FUN_00ce10c0(PlanTable* pTable, int iUnused1, int iUnused2, int iUnused3,
                  uint32_t* pOut, cPlanRecord* pRecord)
{
    uint32_t uId = pRecord->mValue18;
    pOut[0] = uId;
    uint32_t uState = pRecord->mValue1c;
    pOut[1] = uState;
    pOut[2] = 0;

    cTribePlanData* pData = (cTribePlanData*)FUN_00ce0e60(pTable, uId, uState);
    if (!pData)
        return false;

    FUN_00ce0ff0((int)pTable, pTable, uId, uState, 4);
    EraseRange(pData->mWorkers.mpBegin, pData->mWorkers.mpEnd);
    return true;
}

// ===========================================================================
// 0x00ce1130 -- cancel the "raiding" order state
// ===========================================================================
// @ 0x00ce1130
bool FUN_00ce1130(PlanTable* pTable, int iUnused1, int iUnused2, int iUnused3,
                  uint32_t* pOut, cPlanRecord* pRecord)
{
    uint32_t uId = pRecord->mValue18;
    pOut[0] = uId;
    uint32_t uState = pRecord->mValue1c;
    pOut[1] = uState;
    pOut[2] = 0;

    cTribePlanData* pData = (cTribePlanData*)FUN_00ce0e60(pTable, uId, uState);
    if (!pData)
        return false;

    FUN_00ce0ff0((int)pTable, pTable, uId, uState, 4);
    return true;
}

// ===========================================================================
// 0x00ce1190 -- SP::PLANNER_RAIDING_Activate
// ===========================================================================
// @ 0x00ce1190
bool PLANNER_RAIDING_Activate(cTribePlanner* pPlanner, int iUnused1, int iUnused2, int iUnused3,
                              uint32_t* pOut)
{
    pOut[0] = 0xffffffffu;
    pOut[1] = 0xffffffffu;

    cOrderObject* pOrder = (cOrderObject*)FUN_00bca2c0();
    if (!pOrder)
        return false;

    uint32_t uPlanId = *(uint32_t*)pOrder;
    pOut[0] = uPlanId;
    uint32_t uTargetId = (uint32_t)VariantInt(&pOrder->mTargetVariant);
    pOut[1] = uTargetId;

    PlanTable* pTable = (PlanTable*)pPlanner->mpAuxObject;
    cTribePlanData* pData = (cTribePlanData*)FUN_00ce0e60(pTable, uPlanId, uTargetId);
    if (!pData)
        return false;

    if (pData->mState != 4) {
        int** ppIter = (int**)&pData->mWorkers.mpBegin;
        int** ppEnd = (int**)&pData->mWorkers.mpEnd;
        if (ppIter != ppEnd) {
            if (!FUN_00cdfea0((cCitizen*)*ppIter))
                FUN_00cdff70((int***)&pData->mWorkers.mpBegin);
            while (pData->mWorkers.mpBegin != pData->mWorkers.mpEnd) {
                FUN_00bc97f0(0, 0x1000000, 0x43960000, ((int*)pOrder)[10]);
                FUN_00cdff70((int***)&pData->mWorkers.mpBegin);
            }
        }
    }

    pData->mState = 4;
    AssignVariantUInt(&pOrder->mTargetVariant, 4);
    pOut[2] = 0;

    Vec3 position;
    GetOrderPosition(pPlanner->mpAuxObject, &position);

    void* pLog = EventLog(0x166b09f6, 0x182cd6ce, &position, 0, 1, 0);
    PostFeedbackEvent(pLog, 0x166b09f6, 0x182cd6ce, &position, 0, 1, 0);

    void* pSystem = GetSystemAT();
    int iHandle = pSystem ? (*(int (__thiscall**)(void*))(*(int*)pSystem + 0x20)) (pSystem) : 0;
    Start3dSoundByName(0x3fb22e3b, iHandle, position.x, position.y, position.z);

    pSystem = GetSystemAT();
    iHandle = pSystem ? (*(int (__thiscall**)(void*))(*(int*)pSystem + 0x20)) (pSystem) : 0;
    pOut[3] = (uint32_t)iHandle;
    Start3dSoundByName(0x0ad1a17u, iHandle, position.x, position.y, position.z);
    return true;
}
