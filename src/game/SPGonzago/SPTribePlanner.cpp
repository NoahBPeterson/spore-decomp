// src/game/SPGonzago/SPTribePlanner.cpp -- migrated from slice(s) s0135d100, s00ce4e10, s00ce3eb0, s00ce33b0, s00ce2330, s00ce1390, s00cdfea0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribePlanner.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPBehaviorTree/behavior_memory_block.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Variant.h"
#include "SP/cAgentOrder.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cPlanetModel.h"
#include "SP/cRelationshipManager.h"
#include "SP/cTribe.h"
#include "SP/cTribePlanData.h"
#include "SP/cTribePlanner.h"
#include <math.h>
#include "SP/cBehaviorTreeData.h"
#include "SP/cVarListSerializer.h"
#include "SP/cCombatant.h"
#include "SP/cGonzagoSimulator.h"
#include "SP/cSPCreatureCitizen.h"

// unnamed retail callees and globals (address in the comment)
extern int* FUN_00bca2c0(void);                                                  // 0x00bca2c0
extern void FUN_00bcb3d0(void);                                                  // 0x00bcb3d0
extern void FUN_00bc86e0(double dTime, void* pTree, void* pArg, void* pBlocks,
                         void* pFree, int iAlign);                               // 0x00bc86e0
extern void* GameTimeManager(void);                                              // 0x00b31670
extern unsigned long long FUN_00b316c0(void);                                    // 0x00b316c0
extern int FUN_00b3d230(void);                                                   // 0x00b3d230
extern void* FUN_00bcaf70(void* pTable, int iPlanIndex, int iFlag);              // 0x00bcaf70
extern void FUN_00bcaf40(void* pNoun);                                           // 0x00bcaf40
extern void ForceOrdersUpdate(void* pCitizen);                        // cSPCreatureCitizen
extern void EraseRange(void* pBegin, void* pEnd);                                // eastl::vector::erase
extern void RestartTimer(void* pTimer);                                          // SP::cSPTimer::Restart
extern void* GetSystemAT(void);                                                  // EA::Audio::GetSystemAT
extern void __cdecl operator_delete(void* pBlock);

// ---- items of slice s00cdfea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
extern void __fastcall GetAny(void* pStimuli);                                   // 0x00d997e0
extern void* FUN_00d99420(void* pObject, int iFilter);                           // 0x00d99420
extern void FUN_00d996e0(void* pList, void* pStimuli);                           // 0x00d996e0
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
class cPropertyList {
public:
    virtual bool GetProperty(uint32_t uPropertyId, Variant** ppValue);   // +0x24
};
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
struct cTribePlanConfiguration_s00cd_fea0 {
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
struct WorkerList {
    void*    mpBegin;          // +0x00
    void*    mpEnd;            // +0x04
    void*    mpCapacityEnd;    // +0x08
    uint32_t mPad0c[10];       // +0x0c inline storage
};
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
    cTribePlanConfiguration_s00cd_fea0* mpConfiguration;   // +0x50
};
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
struct cOrderObject {
    uint32_t mPad00[0x13];          // +0x00 .. +0x4b
    uint8_t  mPad4c;                // +0x4c
    Variant  mTargetVariant;        // +0x4d
};
struct cPlanRecord {
    uint32_t mPad00[6];             // +0x00 .. +0x17
    uint32_t mValue18;              // +0x18
    uint32_t mValue1c;              // +0x1c
};
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
extern void FUN_00bc97f0(int iA, uint32_t uFlags, float fRange, int iB);         // 0x00bc97f0
extern void FUN_00ce0bf0(uint32_t* pResult, const void* pSource);                // 0x00ce0bf0
extern void FUN_00ce0c50(uint32_t* pResult, uint32_t* pValue, uint32_t uFlags);  // 0x00ce0c50
extern void AssignVariantUInt(Variant* pVariant, uint32_t uValue);               // Variant::operator=
extern void GetOrderPosition(void* pOrder, Vec3* pPosition);                     // +0x120 vtable +0x2c
extern bool GetPropertyAsUint32Array(cPropertyList* pList, uint32_t uPropertyId,
                                     uint32_t** ppArray, int* piCount);          // property helper
extern void* EventLog(uint32_t uId, uint32_t uSubId, void* pPos, int iA, int iB, int iC);
extern void PostFeedbackEvent(void* pLog, uint32_t uId, uint32_t uSubId, void* pPos,
                              int iA, int iB, int iC);
extern void Start3dSoundByName(uint32_t uName, int iHandle, float x, float y, float z);
PlanEntry* FUN_00cdffc0(PlanEntry* pThis, const PlanEntry* pSrc);
PlanTableEntry* FUN_00ce0e60(PlanTable* pTable, uint32_t uPlanId, uint32_t uIndex);
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
// ---- items of slice s00cdfea0 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// ---- items of slice s00ce1390 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_defaultUInt;      // 0x015d1164
extern bool     g_bool_01581374;    // 0x01581374
extern float    g_zero;             // 0x01485378
extern float    g_two;              // 0x01470f1c
extern float    g_f_01473c70;       // 0x01473c70
extern float    g_fltMax;           // 0x01477928
#pragma pack(push, 1)
#pragma pack(pop)
#define VSLOT(n) virtual void _v##n();
#define VSLOTS_0_3   VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
#define VSLOTS_4_7   VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
#define VSLOTS_12_15 VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15)
#define VSLOTS_20_23 VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
#define VSLOTS_24_27 VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27)
#define VSLOTS_28_31 VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31)
#define VSLOTS_32_35 VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35)
#define VSLOTS_36_39 VSLOT(36) VSLOT(37) VSLOT(38) VSLOT(39)
#define VSLOTS_40_43 VSLOT(40) VSLOT(41) VSLOT(42) VSLOT(43)
#define VSLOTS_0_10  VSLOTS_0_3 VSLOTS_4_7 VSLOT(8) VSLOT(9) VSLOT(10)
#define VSLOTS_0_18  VSLOTS_0_10 VSLOT(11) VSLOTS_12_15 VSLOT(16) VSLOT(17) VSLOT(18)
#define VSLOTS_0_23  VSLOTS_0_18 VSLOT(19) VSLOTS_20_23
#define VSLOTS_0_45  VSLOTS_0_23 VSLOTS_24_27 VSLOTS_28_31 VSLOTS_32_35 VSLOTS_36_39 \
                     VSLOTS_40_43 VSLOT(44) VSLOT(45)
#define VSLOTS_0_47  VSLOTS_0_45 VSLOT(46) VSLOT(47)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Variant_s00ce_1390 {
    uint32_t mData[4];
    uint16_t mFlags;
    uint16_t mType;
    void* GetStorage() { if (mFlags & 0x30) { return *(void**)mData; } else if (mType) return this; return 0; }
    unsigned* GetUInt()
    {
        if (mType == 10 || mType == 0x10) { return (unsigned*)GetStorage(); }
        return &g_defaultUInt;
    }
    Variant_s00ce_1390& SetInt(const int* v);          // 0x00427fd0
    Variant_s00ce_1390& SetFloat(const float* v);      // 0x00428060
    Variant_s00ce_1390& SetVec3(const void* v);        // 0x006a3570
    void Destruct(bool reset);              // 0x0093db80
    ~Variant_s00ce_1390() { if (mFlags & 4) { Destruct(false); } }
};
struct IInterface {
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual void* AsInterface(uint32_t id);         // +0x0c, 0x4f396a66 = cTribe
};
struct IGetPos {
    VSLOTS_0_10
    virtual Vector3* GetPosition();                 // +0x2c
};
struct IBool11 {
    VSLOTS_0_10
    virtual bool IsBusy();                          // +0x2c
};
struct IGetId {
    VSLOTS_0_18
    virtual int GetId();                            // +0x4c
};
struct IGetRadius {
    VSLOTS_0_23
    virtual float GetRadius();                      // +0x60
};
struct ICast46 {
    VSLOTS_0_45
    virtual void* Cast(uint32_t id);                // +0xb8
};
struct IProx48 {
    VSLOTS_0_47
    virtual bool IsNear(void* pOther, float a, float b);   // +0xc0
};
struct Vector3;
struct PtrList {                                    // pair of pointers
    void** mpBegin;                                 // +0x00
    void** mpEnd;                                   // +0x04
};
struct Vec3List {
    Vector3* mpBegin;                               // +0x00
    Vector3* mpEnd;                                 // +0x04
};
struct C0Obj {
    VSLOTS_0_10
    virtual Vector3* GetPosition();                 // +0x2c
    PtrList* GetAttackables();                      // 0x00c420d0
};
struct cAgentOrder;
struct cCreature;
struct cTribe;
struct cTribePlanData_s00ce_1390;
struct cAgentOrderManager {
    cAgentOrder* FirstPending();                    // 0x00bca2c0
    char mPad[0x1cc];
    unsigned mFlags1CC;                             // +0x1cc
};
struct cAgentOrder {
    int mType;                                      // +0x00
    char mPad0[0x24];
    IInterface* mpTarget;                           // +0x28
    Vector3 mPosition;                              // +0x2c
    char mPad1[1];                                  // +0x38
    Variant_s00ce_1390 mParam;                                 // +0x39
    Variant_s00ce_1390 mOption;                                // +0x4d
};
struct WorkerList_s00ce_1390 {
    cCreature** mpBegin;                            // +0x00
    cCreature** mpEnd;                              // +0x04
};
struct cTribePlanData_s00ce_1390 {
    int mPad0;
    int mState;                                     // +0x04
    char mPad1[0x14];
    WorkerList_s00ce_1390 mWorkers;                            // +0x1c
};
struct cTribePlanner_s00ce_1390 {
    char mPad0[0x10];
    cAgentOrderManager* mpOrderManager;             // +0x10
    char mPad1[4];
    cTribePlanData_s00ce_1390* GetPlanData(int orderType, unsigned key);   // 0x00ce0e60
};
struct cTribePlannerContext {
    cTribe* mpTribe;                                // +0x00
    cTribePlanner_s00ce_1390* mpTribePlanner;                  // +0x04
    unsigned mToolsMask;                            // +0x08
    int mNumAdults;                                 // +0x0c
    int mMaxAdults;                                 // +0x10
    float mCurrentFood;                             // +0x14
    int mAttitudeToTarget;                          // +0x18
    int mTargetPopulation;                          // +0x1c
    IInterface* mpTarget;                           // +0x20
};
struct WorkerFilter {
    bool Pass(cCreature* c);                        // 0x00cdfea0
};
struct WorkerIter {
    cCreature** mCur;                               // +0x00
    cCreature** mEnd;                               // +0x04
    WorkerFilter mFilter;                           // +0x08
    WorkerIter() {}
    WorkerIter(WorkerList_s00ce_1390* w) : mCur(w->mpBegin), mEnd(w->mpEnd) {}
    WorkerIter& Init(WorkerList_s00ce_1390* w, void* p);       // 0x00ce0b20
    WorkerIter& Advance();                          // 0x00cdff70
};
struct cCreature {
    char mPad0[0xb34];
    int  mFlagB34;                                  // +0xb34
    char mPad1[0xb4c - 0xb38];
    cAgentOrderManager* mpOrderManager;             // +0xb4c
    char mPad2[0xb5e - 0xb50];
    char mFlagB5E;                                  // +0xb5e
    char mPad3[0xb80 - 0xb5f];
    float mRadiusB80;                               // +0xb80
    char mPad4[0x3c];                               // +0xb84
    char mPosC0[0x60];                              // +0xc0 embedded position object
    char mPos120[0x60];                             // +0x120 embedded position object

    cAgentOrder* GiveOrder(int orderType, void* pTarget, Variant_s00ce_1390* pParam);   // 0x00c275b0
    bool AnimationFinished(uint32_t id);                                     // 0x00c123f0
    void InterruptAnimation(uint32_t id, int a, bool b);                     // 0x00c12310
    bool IsFlagB34() { return mFlagB34 == 1; }                               // 0x00c0b770
    bool HasSubFlag388() {                                                   // 0x00c0c0e0
        char* p = *(char**)((char*)this + 0xe84);
        return p && p[0x388];
    }
    bool IsNearSelf(cCreature* pOther, float a, float b) {                   // 0x00c0d560
        return ((IProx48*)this)->IsNear(pOther, a, b);
    }
};
struct cTribe {
    IGetId* AsGetId() { return (IGetId*)this; }
    float GetRadius() { return ((IGetRadius*)this)->GetRadius(); }
    Vector3* GetClosestWater();                     // 0x00c8fe20
    Vec3List* GetPoints();                          // 0x00c97020
};
struct cRelationshipManager {
    float d00a10(int a, int b, int c);              // 0x00d00a10 (ret 0xc)
    int   d00780(float f);                          // 0x00d00780 (ret 4)
};
cRelationshipManager* RelationshipManager();        // 0x00b3d2c0
struct cEventLog {
    int PostFeedbackEvent(unsigned a, unsigned b, int c, int d, int e, int f);   // 0x00dd8640
};
cEventLog* EventLog();                              // 0x00b3d3e0
struct RandomLinearCongruential {
    unsigned RandomUint32Uniform(unsigned n);       // 0x00a68fb0
};
extern RandomLinearCongruential g_random;           // 0x01601760
bool HasPendingOrder(cTribePlanData_s00ce_1390* plan, int orderType);   // 0x00ce0b60
void* FUN_00ac80d0(void* p, uint32_t type);                  // 0x00ac80d0
void* FUN_00d99500(void* p);                                 // 0x00d99500
struct CongState { int mOrderType; int mOrderId; int mPhase; float mTimer; };
struct StealState { int mOrderType; int mOrderId; float mTimer; };
struct GiftState { int mOrderType; int mOrderId; float mTimer; };
struct HuntState { int mOrderType; int mOrderId; Vector3 mTargetPos; float mTimer; };
struct GatherState { int mOrderType; int mOrderId; float mTimer; };
struct WaterState { int mOrderType; int mOrderId; float mTimer; };
// ---- items of slice s00ce1390 end

// ---- items of slice s00ce2330 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
 class cTribePlanConfiguration; 
}
extern uint32_t g_defaultUInt;              // 0x015d1164
extern float    g_closestWaterZero[3];      // 0x0169b3d8
extern "C" void __cdecl memmove(void* pDst, const void* pSrc, unsigned nCount);
extern "C" void __cdecl operator_delete_array(void* pMemory);
struct IInterface_s00ce_2330 {                                     // EA::COM::IUnknown32-lookalike
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
struct cTribePlanner_s00ce_2330;
struct cTribePlanData_s00ce_2330;
struct cTribePlanConfiguration_s00ce_2330;
struct PlannerGroup;
struct String16 {
    wchar_t* mpBegin;                                   // +0x00
    wchar_t* mpEnd;                                     // +0x04
    wchar_t* mpCapacity;                                // +0x08
};
struct Variant_s00ce_2330 {
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
struct WorkerList_s00ce_2330 {
    void** mpBegin;                                                 // +0x00
    void** mpEnd;                                                   // +0x04
    void** mpCapacityEnd;                                           // +0x08
    void*  mAlloc0;                                                 // +0x0c
    void*  mAlloc1;                                                 // +0x10
    void*  mAlloc2;                                                 // +0x14
    void*  mSlots[8];                                               // +0x18
    void assign(const WorkerList_s00ce_2330& src);                             // 0x01011cc0
    void erase(void** pFirst, void** pLast);                        // 0x00e25bd0
};
struct cTribePlanConfiguration_s00ce_2330 {                        // retail, size 0x58
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
struct cTribePlanData_s00ce_2330 {                                 // size 0x58
    uint32_t mID;                                       // +0x00
    uint32_t mState;                                    // +0x04
    uint32_t mFrequency;                                // +0x08
    float    mCheckTime;                                // +0x0c
    int32_t  mFoodRequired;                             // +0x10
    float    mFoodAccumulated;                          // +0x14
    uint8_t  mbCheck;                                   // +0x18
    uint8_t  mPad19[3];                                 // +0x19
    WorkerList_s00ce_2330 mWorkers;                                // +0x1c
    cTribePlanConfiguration_s00ce_2330* mpConfiguration;           // +0x54

    cTribePlanData_s00ce_2330* FUN_00ce2880(const cTribePlanData_s00ce_2330* pSrc);  // 0x00ce2880 (cTribePlanData::FUN_00ce2880)
    cTribePlanData_s00ce_2330* FUN_00ce28e0(const cTribePlanData_s00ce_2330* pSrc);  // 0x00ce28e0 (cTribePlanData::FUN_00ce28e0)
    void FUN_00ce0f70();                                // 0x00ce0f70 (release workers)
    cTribePlanConfiguration_s00ce_2330* GetConfiguration();  // 0x00ce2ee0 (cTribePlanData::GetConfiguration)
};
struct StepVector {                                     // eastl::vector<cTribePlanData,sp_allocator>
    cTribePlanData_s00ce_2330* mpBegin;                            // +0x00
    cTribePlanData_s00ce_2330* mpEnd;                              // +0x04
    cTribePlanData_s00ce_2330* mpCapacity;                         // +0x08
    void DoDestroyValues(cTribePlanData_s00ce_2330* pFirst, cTribePlanData_s00ce_2330* pLast);   // 0x00ce0e00
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
struct cAgentOrder_s00ce_2330 {
    int32_t  mType;                                     // +0x00
    uint8_t  mPad04[0x24];                              // +0x04
    void*    mpTarget;                                  // +0x28
    uint8_t  mPad2c[0x0d];                              // +0x2c
    Variant_s00ce_2330  mParam;                                    // +0x39
};
struct cAgentOrderManager_s00ce_2330 {                             // shared by the behaviour-tree data
    cAgentOrder_s00ce_2330* FirstPending();                        // 0x00bca2c0
    void PopFront();                                    // 0x00bcaf40
};
struct cBehaviorTreeData_s00ce_2330 : cAgentOrderManager_s00ce_2330 {         // cTribePlanner::mpBehaviorTreeData
    void* mpBehaviorTree;                               // +0x00
    void Write(int* pSerializer);                       // 0x00bc9a80
};
struct cTribePlanner_s00ce_2330 {
    void* mpVtable;                                     // +0x00
    void* mpVtableInterface;                            // +0x04
    void* mpSerializableVtable;                         // +0x08
    uint8_t mbPaused;                                   // +0x0c
    uint8_t mPad0d[3];                                  // +0x0d
    cBehaviorTreeData_s00ce_2330* mpBehaviorTreeData;              // +0x10
    PlannerGroup* mpPlansBegin;                         // +0x14
    PlannerGroup* mpPlansEnd;                           // +0x18
    PlannerGroup* mpPlansCapacity;                      // +0x1c
    uint8_t mPad20[8];                                  // +0x20
    uint8_t mPlansCompare;                              // +0x28
    uint8_t mPad29[3];                                  // +0x29
    SpVectorFloat mTimeBetweenPlanExecutionByType;      // +0x2c
    cTribe* mpTribe;                                    // +0x74
    float   mAccumulatedDeltaTime;                      // +0x78

    cTribePlanData_s00ce_2330* GetPlanData(uint32_t uOrderType, uint32_t uKey);   // 0x00ce0e60
    const wchar_t* GetStatString(int nWhich);  // 0x00ce23b0 (cTribePlanner::GetStatString)
    unsigned char Write(int* pSerializer);  // 0x00ce2420 (cTribePlanner::Write)
};
struct cTribePlannerContext_s00ce_2330 {                           // size 0x24 (2008 PDB layout)
    cTribe* mpTribe;                                    // +0x00
    cTribePlanner_s00ce_2330* mpTribePlanner;                      // +0x04
    uint32_t mToolsMask;                                // +0x08
    uint32_t mNumAdults;                                // +0x0c
    uint32_t mMaxAdults;                                // +0x10
    int32_t  mCurrentFood;                              // +0x14 (compared as int32 in retail)
    int32_t  mAttitudeToTarget;                         // +0x18
    uint32_t mTargetPopulation;                         // +0x1c
    IInterface_s00ce_2330* mpTarget;                               // +0x20
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
    cTribePlanConfiguration_s00ce_2330 mConfiguration;             // +0x04 (retail embeds the config inline)
    PlanConfigNode* mpNext;                             // chain link (at +0x48 in retail buckets)
};
void __cdecl g_statStringDtor(void);        // 0x013c4880
void __cdecl g_planCfgTableDtor(void);      // 0x013c48b0
int  __cdecl WStr_Format(void* pDest, const wchar_t* pFormat, ...);          // 0x0041e050
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
void  __fastcall LoadTuning(cTribePlanConfiguration_s00ce_2330* pThis);                         // 0x00ce0150
cTribePlanConfiguration_s00ce_2330* __cdecl GetTribePlanConfiguration_s00ce_2330(uint32_t uTribeId);       // 0x00ce2d20
struct PtrVector {
    uint32_t* mpBegin;                                  // +0x00
    uint32_t* mpEnd;                                    // +0x04
    uint32_t* mpCapacity;                               // +0x08
    void reserve(uint32_t uCount);
    void push_back(const uint32_t& uValue);
};
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
extern "C" int  __cdecl atexit(void (__cdecl*)(void));
// ---- items of slice s00ce2330 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
uint32_t FUN_00ce2f00(cTribePlannerContext_s00ce_2330* pContext, uint32_t uKey, char bIgnore);  // 0x00ce2f00 (stays in the slice: not this object's)

// ---- items of slice s00ce33b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void SP_GetDamageState();                        // 0x008e7f80 (thiscall)
extern "C" void SP_TribeIsReady();                          // 0x00c8f3a0 (thiscall int)
extern "C" void SP_GetChieftain();                          // 0x00c8fd30 (thiscall pointer)
extern "C" void* __cdecl FindFirstEligiblePlanStep(void* plan, int a, int b); // 0x00ce2f00
extern "C" void SP_GetAny();                                // 0x00d997e0 (thiscall)
extern "C" void __cdecl DeactivatePlan(void* plan, void* a, void* b, int flag); // 0x00ce3020
namespace SP {
struct PlanArgs {
    void* mpPlan;                                            // +0x00
    void* mpContext;                                         // +0x04
    uint32_t mPad08;                                         // +0x08
    void* mpAudioValue;                                      // +0x0c
};
}
namespace SP {
struct AudioSystem {
    void* mpVtable;                                          // +0x00
};
}
namespace SP {
struct cCombatant_s00ce_33b0 {
    void* mpVtable;                                          // +0x00
};
}
namespace SP {
struct cCombatantHost {
    uint32_t    mPad00[0x120 / 4];                           // +0x00 .. +0x11f
    cCombatant_s00ce_33b0  mCombatant;                                  // +0x120
};
}
namespace SP {
struct cTribe_s00ce_33b0 {
    void*    mpVtable;                                       // +0x00
    uint8_t  mPad04[0xb5a];                                  // +0x04 .. +0xb5d
    uint8_t  mFlagB5e;                                       // +0xb5e
};
}
namespace SP {
struct cStimuli {
    uint32_t mPad00[6];                                      // +0x00 .. +0x17
    int32_t  mValue18;                                       // +0x18
    void*    mpValue1c;                                      // +0x1c
};
}
// ---- items of slice s00ce33b0 end

// ---- items of slice s00ce3eb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef int intptr_t;
#define nullptr 0
struct Vec3_s00ce_3eb0 {
    float mX;
    float mY;
    float mZ;
};
class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};
class Variant_s00ce_3eb0 {
public:
    Variant_s00ce_3eb0();
    ~Variant_s00ce_3eb0();
    uint32_t mFlags;
};
class cTribePlanConfiguration_s00ce_3eb0 {
public:
    uint32_t mPriority;             // 0x00
    uint32_t mSteps;                // 0x04
    uint32_t mWorkerCount;          // 0x08
    uint32_t mPad0c[0x0c];          // 0x0c
    uint32_t mMaxWorkers;           // 0x3c
    uint32_t mStepLimit;            // 0x40
};
class cSpatialObject : public IRefCounted {
public:
    virtual void v14();
    virtual Vec3_s00ce_3eb0* GetPosition();            // 0x14
    uint8_t mPad18[0x0c];                   // 0x18
    Vec3_s00ce_3eb0 mPosition;                         // 0x24
};
class cGameData : public cSpatialObject {
public:
    virtual void v2c();
    uint8_t mPad34[0x10];
};
class cSPCreatureBase : public cGameData {
public:
    uint8_t mPad44[0xf4];                   // 0x44
    Vec3_s00ce_3eb0 mPosition;                         // 0x138
};
class cSPCreatureCitizen : public cSPCreatureBase {
public:
    bool IsLeader();
    void GiveOrder(int nOrder, int nTool, Variant_s00ce_3eb0* pParam);
    void ForceOrdersUpdate();
    Vec3_s00ce_3eb0* GetPosition();
    bool IsAvailable();
    uint32_t GetPopulation();
};
class cTribe_s00ce_3eb0 : public cGameData {
public:
    void* GetToolOfType(int nType);  // 0x00c8f6e0 (cTribe::GetToolOfType)
    cSPCreatureCitizen* GetChieftain();  // 0x00c8fd30 (cTribe::GetChieftain)
    uint32_t GetMaxPopulation();  // 0x00c8eae0 (cTribe::GetMaxPopulation)
    uint32_t GetAdultPopulation();  // 0x00c8f370 (cTribe::GetAdultPopulation)
    uint32_t GetPopulation();
    void* GetCitizenList();
    void* GetPlanGroups();

    uint8_t mPad34[0x1f0];                  // 0x34
    uint32_t mTribeId;                      // 0x224
};
class cGameNounManager {
public:
    cTribe_s00ce_3eb0* GetPlayerTribe();
};
struct PlannerStep {
    uint32_t mOwnerId;              // 0x00
    uint32_t mKind;                 // 0x04
    uint8_t mPad08[0x04];           // 0x08
    float    mTimer;                // 0x0c
    uint8_t mPad10[0x08];           // 0x10
    uint32_t mActive;               // 0x18
    uint8_t mPad1c[0x38];           // 0x1c
    cTribePlanConfiguration_s00ce_3eb0* mpPlan; // 0x54
};
struct PlannerGroup_s00ce_3eb0 {
    uint32_t mOwnerId;              // 0x00
    PlannerStep* mpStepsBegin;      // 0x04
    PlannerStep* mpStepsEnd;        // 0x08
    PlannerStep* mpStepsCap;        // 0x0c
    uint32_t mPad10[0x02];          // 0x10
};
struct OrderContext {
    cTribe_s00ce_3eb0* mpTribe;                // 0x00
    uint32_t mPad04[0x02];          // 0x04
    uint32_t mnCount;               // 0x0c
};
struct PlannerStepArray {
    int mCounts[9];                 // 0x00
};
class cGonzagoSimulator : public IRefCounted {
public:
    void Update(float fDeltaTime, uint nFlags);

    uint8_t mPad14[0x08];           // 0x14
    cTribe_s00ce_3eb0* mpTribe;                // 0x1c
    float mTimer;                   // 0x20
    PlannerGroup_s00ce_3eb0* mpGroupBegin;     // 0x24
    PlannerGroup_s00ce_3eb0* mpGroupEnd;       // 0x28
};
void* operator_new(size_t nSize, const char* pName, int a, int b, const char* pFile, int nLine);
void* GetSimulatorContext();
void* GetActiveContext();
cTribePlanConfiguration_s00ce_3eb0* GetTribePlanConfiguration(uint32_t tribeId);
cGameNounManager* NounManager();
void* FindToolByType(uint32_t nType);
uint32_t GameTimeFlags();
uint64_t GameTimeDelta(uint nFlags);
void GiveCityOrder(int nOrder, float fRadius);
void ClearAllOrders(void* pStimuli, uint32_t a, uint32_t b);
void ReleaseVariant(Variant_s00ce_3eb0* pVariant);
void ReleaseTrace(void* pTrace);
float GetTribeRadius(cTribe_s00ce_3eb0* pTribe);
void UpdatePlannerSteps(int nCount, int* pSteps);
bool ReadPlannerCounts(void* pObject, uint32_t key, int* pCount, void** ppArray);
void CopyPlannerStepRange(PlannerStep* pFirst, PlannerStep* pLast, PlannerStep* pDest);
void DestroyStepVector(PlannerGroup_s00ce_3eb0* pGroup);
bool CopyPlannerGroupsInternal(PlannerGroup_s00ce_3eb0* pFirst, PlannerGroup_s00ce_3eb0* pLast,
                               PlannerGroup_s00ce_3eb0* pDest, PlannerGroup_s00ce_3eb0* pOwner);
void GiveToolOrder(cSPCreatureCitizen* pCitizen, int nOrder, void* pTool, int a);
int GetToolOrderSlot(void* pTool);
// ---- items of slice s00ce3eb0 end

// ---- items of slice s00ce4e10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kEastlAllocatorFile[];                       // allocator.h source path
void* operator_new(size_t nSize, const char* pName, int a, int b, const void* pFile, int nLine);
void* FUN_00ce29c0(void** ppResult, void* pFirst, void* pLast, void* pDest, void* pOwner);
void* FUN_00ce2b30(void* pFirst, void* pLast, void* pDest);
void  FUN_00ce0e00(void* pFirst, void* pLast);                 // vector<PlannerGroup>::DoDestroyValues
void* FUN_00ce2cc0(void* pThis, uint32_t nCount, void* pFirst, void* pLast);
void* FUN_00ce2930(void* pFirst, void* pLast, void* pDest);
void  FUN_00ce0d90(void* pFirst, void* pLast, void* pDest);
void  FUN_00ce2ab0(void* pDest, uint32_t nCount, void* pValue, void* pOwner);
void  FUN_00ce2880(void* pValue);
void  FUN_00ce2a50(void* pFirst, void* pLast, void* pValue);
void  FUN_00ce2ba0(void* pFirst, void* pLast, void* pDest);
struct PlannerGroup_s00ce_4e10;
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
class cBehaviorTreeData_s00ce_4e10 {
public:
    uint32_t mPad00[0x19c];                         // +0x00 (0x670 bytes)
};
void __fastcall FUN_00bcae90(cBehaviorTreeData_s00ce_4e10* pThis, void* pUnused);
class ContentValidationSummarizer {
public:
    virtual void Summarize();                       // +0x00

    uint32_t    mPad04;                             // +0x04
};
class cGonzagoSimulator_s00ce_4e10 : public ContentValidationSummarizer {
public:
    cGonzagoSimulator_s00ce_4e10();                            // 0x00b5b6c0
    virtual void Update();                          // +0x08 0x00ce48f0
};
class ITracerBase {
public:
    virtual void TraceBegin();                      // +0x00
    virtual void TraceEnd();                        // +0x04

    uint32_t    mPad04;                             // +0x04
};
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
struct PlannerGroup_s00ce_4e10 {                               // one (plan type, step list) pair, 0x18 bytes
    uint32_t            mPlanType;                  // +0x00
    PlannerStepData*    mpStepsBegin;               // +0x04
    PlannerStepData*    mpStepsEnd;                 // +0x08
    PlannerStepData*    mpStepsCapacity;            // +0x0c
    uint32_t            mPad10[2];                  // +0x10
};
struct PlannerGroupVector {                         // eastl::vector<PlannerGroup>
    PlannerGroup_s00ce_4e10* mpBegin;                          // +0x00
    PlannerGroup_s00ce_4e10* mpEnd;                            // +0x04
    PlannerGroup_s00ce_4e10* mpCapacity;                       // +0x08

    void DoDestroyValues(PlannerGroup_s00ce_4e10* pFirst, PlannerGroup_s00ce_4e10* pEnd);   // 0x00ce2c70

    PlannerGroupVector* FUN_00ce5050(const PlannerGroupVector* pOther);              // assign
    void*               CopyFrom(const PlannerGroupVector* pSource);                 // 0x00ce4c40
    void                FUN_00ce5c40(PlannerGroup_s00ce_4e10* pPos, uint32_t nCount, PlannerGroup_s00ce_4e10* pValue);
    void                FUN_00ce5e90(PlannerGroup_s00ce_4e10* pPos, PlannerGroup_s00ce_4e10* pValue);
    void                FUN_00ce5ff0();
    PlannerGroup_s00ce_4e10*       FUN_00ce6040(PlannerGroup_s00ce_4e10* pPos, PlannerGroup_s00ce_4e10* pValue);
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
class SpVectorFloat_s00ce_4e10 {
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
class cTribePlanner_s00ce_4e10 : public cGonzagoSimulator_s00ce_4e10, public ITracerBase {
public:
    cTribePlanner_s00ce_4e10();                                // 0x00ce55a0
    ~cTribePlanner_s00ce_4e10();                               // 0x00ce4ed0

    cBehaviorTreeData_s00ce_4e10*  mpBehaviorTreeData;         // +0x10
    PlannerGroup_s00ce_4e10*       mpPlansBegin;               // +0x14
    PlannerGroup_s00ce_4e10*       mpPlansEnd;                 // +0x18
    PlannerGroup_s00ce_4e10*       mpPlansCapacity;            // +0x1c
    uint8_t             mPad20[0x0c];               // +0x20
    SpVectorFloat_s00ce_4e10       mTimeBetweenPlanExecutionByType;   // +0x2c
    cTribe*             mpTribe;                    // +0x74
    float               mAccumulatedDeltaTime;      // +0x78
};
void* FUN_00bca2c0_s00ce_4e10();                               // cAgentOrderManager::FirstPending
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
struct Vec3_s00ce_4e10 {
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
    virtual Vec3_s00ce_4e10* GetPosition();                    // +0x2c
    uint32_t mPad04[0x2c];                          // +0x04 .. +0xbf
    void*    mpVtblC0;                              // +0xc0 (secondary interface)
};
class cSPCreatureCitizen_s00ce_4e10 {
public:
    void GiveOrder(int32_t nOrder, void* pTool, void* pParam);  // 0x00c275b0 (cSPCreatureCitizen::GiveOrder)
    uint32_t mPad00[0x16c];                         // +0x00 .. +0x5a7
    cGameObject* mpTarget;                          // +0x5a8
    uint8_t  mByteB5e;                              // +0xb5e
};
struct PlanKey {
    uint32_t mPlanId;                               // +0x00
    uint32_t mIndex;                                // +0x04
    float    mTimeout;                              // +0x08
    Vec3_s00ce_4e10     mPosition;                             // +0x0c
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
// ---- items of slice s00ce4e10 end

// ---- items of slice s0135d100 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void fn_00692ca0();
extern "C" void fn_00572810();
extern "C" void fn_00572840();
extern "C" void fn_00693090();
extern "C" void fn_00694f00();
extern "C" void fn_00b1fbf0();
extern "C" void fn_00675ca0();
extern "C" void fn_00c2e4e0();
extern "C" void fn_00692fb0();
extern "C" void fn_00aca730();
extern "C" void fn_00b6f860();
extern "C" void fn_00c6c390();
extern "C" void fn_00ac88f0();
extern "C" void fn_006930b0();
extern "C" void fn_00694fc0();
extern "C" void fn_00acbb80();
extern "C" void fn_00ac8750();
extern "C" void fn_00ac8780();
extern "C" void fn_00694fa0();
extern "C" void fn_0057ce00();
extern "C" void fn_00ce26c0();
extern "C" void fn_0057cde0();
extern "C" void fn_00692ff0();
extern "C" void fn_00694ee0();
typedef void (__cdecl *fp)();
struct T {
    const char* name;
    unsigned hash;
    int off;
    int p3, p4, p5;
    int z0, z1;
    fp f[7];
    T() {}
    T(const char* n, unsigned h, int o, fp f0, fp f1, fp f2, fp f3,
      fp f4, fp f5, fp f6)
        : name(n), hash(h), z0(0), z1(0) {
        f[0] = f0; f[1] = f1; f[2] = f2; f[3] = f3;
        f[4] = f4; f[5] = f5; f[6] = f6;
        off = o;
    }
};
extern T g_01580de0, g_01580e1c, g_01580e58, g_01580e94, g_01580ed0,
         g_01580f0c, g_01580f48, g_01580f84;
// ---- items of slice s0135d100 end

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

// @ 0x00cdfef0
long double FUN_00cdfef0(int iNode, int iUnused1, int iUnused2, int iUnused3, void* pStimuli, bool* pbOut, int iUnused5, int* pParams)
{
    if (pStimuli)
        GetAny(pStimuli);

    *pbOut = true;

    void* pObject = (void*)(*(int*)(*(int*)(iNode + 4) + 0x10) + 0x1d0);
    void* pList = FUN_00d99420(pObject, pParams[0x2d / 4]);
    FUN_00d996e0(pList, pStimuli);
    return 1.0;
}

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

// @ 0x00ce0150
void LoadTuning(cTribePlanConfiguration_s00cd_fea0* pThis)
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

// @ 0x00ce09b0
long double FUN_00ce09b0()
{
    cOrderObject* pOrder = (cOrderObject*)FUN_00bca2c0();
    if (!pOrder)
        return 0.0;
    return (VariantInt(&pOrder->mTargetVariant) == 3) ? 1.0 : 0.0;
}

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

// @ 0x00ce0ff0
cPlanTimer* FUN_00ce0ff0(int iUnused, PlanTable* pTable, uint32_t uKey, uint32_t uIndex, int iPlanId)
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

// @ 0x00ce1060
bool FUN_00ce1060(PlanTable* pTable, int iUnused1, int iUnused2, int iUnused3, uint32_t* pOut, cPlanRecord* pRecord)
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

// @ 0x00ce10c0
bool FUN_00ce10c0(PlanTable* pTable, int iUnused1, int iUnused2, int iUnused3, uint32_t* pOut, cPlanRecord* pRecord)
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

// @ 0x00ce1130
bool FUN_00ce1130(PlanTable* pTable, int iUnused1, int iUnused2, int iUnused3, uint32_t* pOut, cPlanRecord* pRecord)
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

// @ 0x00ce1190
bool PLANNER_RAIDING_Activate(cTribePlanner* pPlanner, int iUnused1, int iUnused2, int iUnused3, uint32_t* pOut)
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

// @ 0x00ce1390
bool PLANNER_STEAL_CONGREGATE_Activate(cTribePlannerContext* ctx, int, int, int, int, CongState* st)
{
    st->mOrderType = -1;
    st->mOrderId = -1;
    cAgentOrder* order = ctx->mpTribePlanner->mpOrderManager->FirstPending();
    if (order) {
        st->mOrderType = order->mType;
        unsigned key = *order->mParam.GetUInt();
        st->mOrderId = key;
        cTribePlanData_s00ce_1390* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, key);
        if (plan) {
            void* tgt = order->mpTarget;
            if (tgt) {
                cTribe* target = (cTribe*)((IInterface*)tgt)->AsInterface(0x4f396a66);
                if (target) {
                    plan->mState = 4;
                    int four = 4;
                    order->mOption.SetInt(&four);
                    st->mTimer = 0.0f;
                    st->mPhase = 0;
                    float radius = target->GetRadius() + g_f_01473c70;
                    WorkerIter it(&plan->mWorkers);
                    for (; it.mCur != it.mEnd; it.Advance()) {
                        if (it.mFilter.Pass(*it.mCur)) break;
                    }
                    while (it.mCur != it.mEnd) {
                        cCreature* c = *it.mCur;
                        Variant_s00ce_1390 v;
                        v.SetFloat(&radius);
                        c->GiveOrder(4, target, &v);
                        it.Advance();
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x00ce1510
bool PLANNER_STEAL_CONGREGATE_Tick(cTribePlannerContext* ctx, int, int, int, int, CongState* st, WorkerFilter* pFilter, float dt)
{
    float t = st->mTimer - dt;
    if (t > g_zero) {
        st->mTimer = t;
        return true;
    }
    st->mTimer = t;
    st->mTimer = g_two;
    if (!ctx->mpTribePlanner->mpOrderManager->FirstPending()) return true;
    cTribePlanData_s00ce_1390* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, st->mOrderId);
    switch (st->mPhase) {
    case 1: {
        WorkerIter it;
        it.Init(&plan->mWorkers, &it.mFilter);
        for (; it.mCur != it.mEnd; it.Advance()) {
            if (!(*it.mCur)->AnimationFinished(0x5dcc520)) return true;
        }
        return false;
    }
    case 0: {
        WorkerIter it;
        it.Init(&plan->mWorkers, pFilter);
        for (; it.mCur != it.mEnd; it.Advance()) {
            cAgentOrder* o = (*it.mCur)->mpOrderManager->FirstPending();
            if (o && o->mType == 4) return true;
        }
        st->mPhase = 1;
        WorkerIter it2(&plan->mWorkers);
        for (; it2.mCur != it2.mEnd; it2.Advance()) {
            if (it2.mFilter.Pass(*it2.mCur)) break;
        }
        while (it2.mCur != it2.mEnd) {
            (*it2.mCur)->InterruptAnimation(0x5dcc520, -1, false);
            it2.Advance();
        }
        return true;
    }
    }
    return true;
}

// @ 0x00ce1690
bool PLANNER_STEALING_FOOD_Activate(cTribePlannerContext* ctx, int, int, int, int, StealState* st)
{
    cTribe* pTribe = ctx->mpTribe;
    st->mOrderType = -1;
    st->mOrderId = -1;
    cAgentOrder* order = ctx->mpTribePlanner->mpOrderManager->FirstPending();
    if (order) {
        st->mOrderType = order->mType;
        unsigned key = *order->mParam.GetUInt();
        st->mOrderId = key;
        cTribePlanData_s00ce_1390* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, key);
        if (plan) {
            void* tgt = order->mpTarget;
            if (tgt) {
                cTribe* target = (cTribe*)((IInterface*)tgt)->AsInterface(0x4f396a66);
                if (target) {
                    if (g_bool_01581374) {
                        float score = RelationshipManager()->d00a10(
                            pTribe->AsGetId()->GetId(), target->AsGetId()->GetId(), 1);
                        if (RelationshipManager()->d00780(score) >= 2) return false;
                    }
                    int four = 4;
                    plan->mState = four;
                    Variant_s00ce_1390* pOpt = &order->mOption;
                    pOpt->SetInt(&four);
                    st->mTimer = 0.0f;
                    WorkerIter it(&plan->mWorkers);
                    for (; it.mCur != it.mEnd; it.Advance()) {
                        (*it.mCur)->GiveOrder(8, target, 0);
                    }
                    EventLog()->PostFeedbackEvent(0xb87901de, 0x182cd6ce, 0, 0, 1, 0);
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x00ce1810
bool PLANNER_STEALING_FOOD_Tick(cTribePlannerContext* ctx, int, int, int, int, StealState* st, WorkerFilter*, float dt)
{
    cTribe* ourTribe = ctx->mpTribe;
    cAgentOrder* order = ctx->mpTribePlanner->mpOrderManager->FirstPending();
    if (order) {
        cTribePlanData_s00ce_1390* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, st->mOrderId);
        if (plan) {
            void* tgt = order->mpTarget;
            if (tgt) {
                cTribe* target = (cTribe*)((IInterface*)tgt)->AsInterface(0x4f396a66);
                if (target) {
                    if (g_bool_01581374) {
                        float score = RelationshipManager()->d00a10(
                            ourTribe->AsGetId()->GetId(), target->AsGetId()->GetId(), 1);
                        if (RelationshipManager()->d00780(score) >= 2) return false;
                    }
                }
            }
        }
    }
    float t = st->mTimer - dt;
    if (t > g_zero) {
        st->mTimer = t;
        return true;
    }
    st->mTimer = t;
    st->mTimer = g_two;
    if (!order) return false;
    return HasPendingOrder((cTribePlanData_s00ce_1390*)0, 8);
}

// @ 0x00ce18f0
bool PLANNER_GIFTING_Activate(cTribePlannerContext* ctx, int, int, int, int, GiftState* st)
{
    st->mOrderType = -1;
    st->mOrderId = -1;
    cAgentOrder* order = ctx->mpTribePlanner->mpOrderManager->FirstPending();
    if (order) {
        st->mOrderType = order->mType;
        unsigned key = *order->mParam.GetUInt();
        st->mOrderId = key;
        cTribePlanData_s00ce_1390* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, key);
        if (plan) {
            if (order->mpTarget) {
                cTribe* target = (cTribe*)order->mpTarget->AsInterface(0x4f396a66);
                if (target) {
                    plan->mState = 4;
                    int four = 4;
                    order->mOption.SetInt(&four);
                    st->mTimer = 0.0f;
                    WorkerIter it(&plan->mWorkers);
                    for (; it.mCur != it.mEnd; it.Advance()) {
                        (*it.mCur)->GiveOrder(9, target, 0);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x00ce1a20
bool PLANNER_GIFTING_Tick(cTribePlannerContext* ctx, int, int, int, int, GiftState* st, WorkerFilter*, float dt)
{
    float t = st->mTimer - dt;
    if (t > g_zero) {
        st->mTimer = t;
        return true;
    }
    st->mTimer = t;
    st->mTimer = g_two;
    if (ctx->mpTribePlanner->mpOrderManager->FirstPending()) {
        cTribePlanData_s00ce_1390* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, st->mOrderId);
        return HasPendingOrder(plan, 9);
    }
    return false;
}

// @ 0x00ce1c90
bool PLANNER_HUNTING_Tick(cTribePlannerContext* ctx, int, int, int, int, HuntState* st, WorkerFilter*, float dt)
{
    float t = st->mTimer - dt;
    if (t > g_zero) {
        st->mTimer = t;
        return true;
    }
    st->mTimer = t;
    st->mTimer = g_two;
    if (!ctx->mpTribePlanner->mpOrderManager->FirstPending()) return false;
    cTribePlanData_s00ce_1390* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, st->mOrderId);
    if (!plan) return false;
    WorkerIter it(&plan->mWorkers);
    for (; it.mCur != it.mEnd; it.Advance()) {
        if (it.mFilter.Pass(*it.mCur)) break;
    }
    if (it.mCur == it.mEnd) return false;
    unsigned n = (unsigned)(plan->mWorkers.mpEnd - plan->mWorkers.mpBegin);
    cCreature* hunter = plan->mWorkers.mpBegin[g_random.RandomUint32Uniform(n)];
    if (((IBool11*)hunter)->IsBusy()) return true;
    if (hunter->mFlagB5E) return true;
    C0Obj* me = (C0Obj*)((char*)hunter + 0xc0);
    Vector3* myPos = me->GetPosition();
    int myId = ((IGetId*)hunter)->GetId();
    float best = g_fltMax;
    cCreature* target = 0;
    PtrList* cand = me->GetAttackables();
    for (void** p = cand->mpBegin; p != cand->mpEnd; ++p) {
        cCreature* c = (cCreature*)*p;
        if (!c) continue;
        void* iface = ((ICast46*)c)->Cast(0x17f243b);
        if (!iface) continue;
        void* obj = FUN_00ac80d0(iface, 0x18eb45e);
        if (!obj) continue;
        cCreature* other = (cCreature*)FUN_00d99500(obj);
        if (!other) continue;
        if (!other->IsFlagB34()) continue;
        if (other->HasSubFlag388()) continue;
        if (((IGetId*)other)->GetId() == myId) continue;
        Vector3* oPos = ((IGetPos*)((char*)other + 0xc0))->GetPosition();
        float dx = myPos->x - oPos->x, dy = myPos->y - oPos->y, dz = myPos->z - oPos->z;
        float d2 = dx * dx + dy * dy + dz * dz;
        if (!(best > d2)) continue;
        float d = sqrtf(d2);
        if (!hunter->IsNearSelf(other, 1.0f, d)) {
            if (!((IProx48*)hunter)->IsNear(other, 1.0f, d)) continue;
        }
        best = d2;
        target = other;
    }
    if (!target) return true;
    WorkerIter it2;
    it2.Init(&plan->mWorkers, &it2.mFilter);
    for (; it2.mCur != it2.mEnd; it2.Advance()) {
        cCreature* c = *it2.mCur;
        cAgentOrder* o = c->mpOrderManager->FirstPending();
        if (o && o->mType == 0xa) continue;
        c->GiveOrder(0xa, target, 0);
    }
    return true;
}

// @ 0x00ce20d0
bool PLANNER_GATHERING_Tick(cTribePlannerContext* ctx, int, int, int, int, GatherState* st, WorkerFilter*, float dt)
{
    float t = st->mTimer - dt;
    if (t > g_zero) {
        st->mTimer = t;
        return true;
    }
    st->mTimer = t;
    st->mTimer = g_two;
    if (ctx->mpTribePlanner->mpOrderManager->FirstPending()) {
        cTribePlanData_s00ce_1390* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, st->mOrderId);
        return HasPendingOrder(plan, 2);
    }
    return false;
}

// @ 0x00ce22c0
bool PLANNER_WATERING_Tick(cTribePlannerContext* ctx, int, int, int, int, WaterState* st, WorkerFilter*, float dt)
{
    float t = st->mTimer - dt;
    if (t > g_zero) {
        st->mTimer = t;
        return true;
    }
    st->mTimer = t;
    st->mTimer = g_two;
    if (ctx->mpTribePlanner->mpOrderManager->FirstPending()) {
        cTribePlanData_s00ce_1390* plan = ctx->mpTribePlanner->GetPlanData(st->mOrderType, st->mOrderId);
        return HasPendingOrder(plan, 1);
    }
    return false;
}

// @ 0x00ce23b0
wchar_t const * SP::cTribePlanner::GetStatString(SP::cGonzagoSimulator::eStatStringType nWhich)
{
    if ((g_statInit & 1) == 0) {
        g_statInit |= 1;
        g_statString.mpBegin = g_emptyString16;
        g_statString.mpEnd = g_emptyString16;
        g_statString.mpCapacity = &g_emptyString16[1];
        atexit(g_statStringDtor);
    }
    if (nWhich == 2)
        WStr_Format(&g_statString, L"Tribe Planner 0x%08x", (uint32_t)mpTribe.mpObject);
    return g_statString.mpBegin;
}

// @ 0x00ce27a0
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

// @ 0x00ce2880
cTribePlanData_s00ce_2330* cTribePlanData_s00ce_2330::FUN_00ce2880(const cTribePlanData_s00ce_2330* pSrc)
{
    mID = pSrc->mID;
    mState = pSrc->mState;
    mFrequency = pSrc->mFrequency;
    mCheckTime = pSrc->mCheckTime;
    mFoodRequired = pSrc->mFoodRequired;
    mFoodAccumulated = pSrc->mFoodAccumulated;
    mbCheck = pSrc->mbCheck;

    WorkerList_s00ce_2330& w = mWorkers;
    void** pSlots = (void**)&w.mSlots[0];
    w.mpBegin = pSlots;
    w.mpEnd = pSlots;
    w.mAlloc2 = 0;
    w.mpCapacityEnd = pSlots + 8;
    w.assign(pSrc->mWorkers);
    mpConfiguration = pSrc->mpConfiguration;
    return this;
}

// @ 0x00ce28e0
cTribePlanData_s00ce_2330* cTribePlanData_s00ce_2330::FUN_00ce28e0(const cTribePlanData_s00ce_2330* pSrc)
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

// @ 0x00ce2930
cTribePlanData_s00ce_2330* FUN_00ce2930(cTribePlanData_s00ce_2330* pFirst, cTribePlanData_s00ce_2330* pLast, cTribePlanData_s00ce_2330* pDest)
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

// @ 0x00ce29c0
cTribePlanData_s00ce_2330** FUN_00ce29c0(cTribePlanData_s00ce_2330** ppDest, cTribePlanData_s00ce_2330* pFirst, cTribePlanData_s00ce_2330* pLast, cTribePlanData_s00ce_2330* pDest)
{
    *ppDest = pDest;
    while (pFirst != pLast) {
        cTribePlanData_s00ce_2330* p = *ppDest;
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

// @ 0x00ce2a50
void FUN_00ce2a50(cTribePlanData_s00ce_2330* pDestFirst, cTribePlanData_s00ce_2330* pDestLast, const cTribePlanData_s00ce_2330* pSrc)
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

// @ 0x00ce2ab0
void FUN_00ce2ab0(cTribePlanData_s00ce_2330* pDest, uint32_t uCount, const cTribePlanData_s00ce_2330* pSrc)
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

// @ 0x00ce2b30
cTribePlanData_s00ce_2330* FUN_00ce2b30(const cTribePlanData_s00ce_2330* pSrcFirst, const cTribePlanData_s00ce_2330* pSrcLast, cTribePlanData_s00ce_2330* pDest)
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

// @ 0x00ce2ba0
cTribePlanData_s00ce_2330* FUN_00ce2ba0(const cTribePlanData_s00ce_2330* pSrcFirst, const cTribePlanData_s00ce_2330* pSrcLast, cTribePlanData_s00ce_2330* pDestLast)
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

// @ 0x00ce2c10
PlannerGroup* FUN_00ce2c10(PlannerGroup* pFirst, PlannerGroup* pLast, PlannerGroup* pDest)
{
    while (pFirst != pLast) {
        pFirst->mSteps.DoDestroyValues(pFirst->mSteps.mpBegin, pFirst->mSteps.mpEnd);
        cTribePlanData_s00ce_2330* pBegin = pFirst->mSteps.mpBegin;
        if (pBegin != 0 && ((int32_t*)pBegin)[-1] != 0)
            operator_delete_array(pBegin);
        ++pFirst;
        ++pDest;
    }
    return pDest;
}

// @ 0x00ce2c70
void __stdcall FUN_00ce2c70(PlannerGroup* pFirst, PlannerGroup* pLast)
{
    while (pFirst < pLast) {
        pFirst->mSteps.DoDestroyValues(pFirst->mSteps.mpBegin, pFirst->mSteps.mpEnd);
        cTribePlanData_s00ce_2330* pBegin = pFirst->mSteps.mpBegin;
        if (pBegin != 0 && ((int32_t*)pBegin)[-1] != 0)
            operator_delete_array(pBegin);
        ++pFirst;
    }
}

// @ 0x00ce2d20
namespace SP {
cTribePlanConfiguration_s00ce_2330 * GetTribePlanConfiguration(unsigned int uTribeId)
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
                cTribePlanConfiguration_s00ce_2330* pConfig =
                    (cTribePlanConfiguration_s00ce_2330*)FUN_00ce0ed0(g_planTable, &uKey);
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
}  // namespace SP

// @ 0x00ce2ee0
cTribePlanConfiguration_s00ce_2330* cTribePlanData_s00ce_2330::GetConfiguration()
{
    if (mpConfiguration == 0)
        mpConfiguration = GetTribePlanConfiguration_s00ce_2330(mID);
    return mpConfiguration;
}

// @ 0x00ce2f00
uint32_t FUN_00ce2f00(cTribePlannerContext_s00ce_2330* pContext, uint32_t uKey, char bIgnore)
{
    cTribePlanner_s00ce_2330* pPlanner = pContext->mpTribePlanner;
    PlannerGroup* pPlansEnd = pPlanner->mpPlansEnd;
    PlannerGroup* pFound = LowerBound(pPlanner->mpPlansBegin, pPlansEnd, &uKey, pPlanner->mPlansCompare);
    PlannerGroup* pGroup = pPlansEnd;
    if (pFound != pPlansEnd && pFound->mPlanType <= uKey && pFound != pFound + 1)
        pGroup = pFound;

    if (pGroup == pPlansEnd)
        return 0xffffffffu;

    cTribePlanData_s00ce_2330* pStepBegin = pGroup->mSteps.mpBegin;
    cTribePlanData_s00ce_2330* pStepEnd = pGroup->mSteps.mpEnd;
    uint32_t uCount = (uint32_t)(pStepEnd - pStepBegin);
    for (uint32_t uIndex = 0; uIndex < uCount; ++uIndex) {
        cTribePlanData_s00ce_2330* pStep = pStepBegin + uIndex;
        if (pStep->mpConfiguration == 0)
            pStep->mpConfiguration = GetTribePlanConfiguration_s00ce_2330(pStep->mID);
        cTribePlanConfiguration_s00ce_2330* pConfig = pStep->mpConfiguration;
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

// @ 0x00ce3020
void DeactivatePlan(cTribePlannerContext_s00ce_2330* pContext, uint32_t uPlanType, uint32_t uIndex, char bRelease)
{
    cTribePlanner_s00ce_2330* pPlanner = pContext->mpTribePlanner;
    cTribePlanData_s00ce_2330* pEntry = pPlanner->GetPlanData(uPlanType, uIndex);
    if (pEntry != 0) {
        if (bRelease != 0)
            pEntry->FUN_00ce0f70();
        if (pEntry->mState == 4 && uIndex < 0xc) {
            if (pEntry->mpConfiguration == 0)
                pEntry->mpConfiguration = GetTribePlanConfiguration_s00ce_2330(pEntry->mID);
            pPlanner->mTimeBetweenPlanExecutionByType.mpBegin[uIndex] =
                pEntry->mpConfiguration->mTimeBetweenExecution;
        }
        pEntry->mWorkers.erase(pEntry->mWorkers.mpBegin, pEntry->mWorkers.mpEnd);
        pEntry->mFoodAccumulated = 0.0f;
        pEntry->mFoodRequired = 0;
        pEntry->mState = 0;
    }

    cAgentOrder_s00ce_2330* pOrder = pPlanner->mpBehaviorTreeData->FirstPending();
    if (pOrder != 0 && pOrder->mType == (int)uPlanType)
        pPlanner->mpBehaviorTreeData->PopFront();
}

// @ 0x00ce30d0
float FUN_00ce30d0(cTribePlannerContext_s00ce_2330* pContext, uint32_t uArg2, uint32_t uArg3, uint32_t uArg4, behavior_stimuli* pStimuli, uint8_t* pOut)
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

// @ 0x00ce3120
float FUN_00ce3120(cTribePlannerContext_s00ce_2330* pContext, uint32_t uArg2, uint32_t uArg3, uint32_t uArg4, behavior_stimuli* pStimuli, uint8_t* pOut)
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

// @ 0x00ce3170
float FUN_00ce3170(cTribePlannerContext_s00ce_2330* pContext, uint32_t uArg2, uint32_t uArg3, uint32_t uArg4, behavior_stimuli* pStimuli, uint8_t* pOut)
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

// @ 0x00ce31e0
float FUN_00ce31e0(cTribePlannerContext_s00ce_2330* pContext, uint32_t uArg2, uint32_t uArg3, uint32_t uArg4, behavior_stimuli* pStimuli, uint8_t* pOut)
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

// @ 0x00ce3250
float FUN_00ce3250(cTribePlannerContext_s00ce_2330* pContext, uint32_t uArg2, uint32_t uArg3, uint32_t uArg4, behavior_stimuli* pStimuli, uint8_t* pOut)
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

// @ 0x00ce3300
float FUN_00ce3300(cTribePlannerContext_s00ce_2330* pContext, uint32_t uArg2, uint32_t uArg3, uint32_t uArg4, behavior_stimuli* pStimuli, uint8_t* pOut)
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

// @ 0x00ce3440
double __cdecl TryStartPlanStep(void* planRef, int a, int b, int c, SP::cStimuli* stimuli, uint8_t* outFlag)
{
    SP::cTribe_s00ce_33b0* tribe = (SP::cTribe_s00ce_33b0*)*(void**)planRef;
    SP::cCombatantHost* host = (SP::cCombatantHost*)(
        (void* (__thiscall*)(SP::cTribe_s00ce_33b0*))((void**)tribe->mpVtable)[0xac / 4])(tribe);
    int state = ((int (__thiscall*)(void*))SP_GetDamageState)(&host->mCombatant);
    if (state == 2)
        return 0.0;
    int ready = ((int (__thiscall*)(SP::cTribe_s00ce_33b0*))SP_TribeIsReady)(tribe);
    if (ready == 1) {
        SP::cTribe_s00ce_33b0* chief = (SP::cTribe_s00ce_33b0*)((void* (__thiscall*)(SP::cTribe_s00ce_33b0*))SP_GetChieftain)(tribe);
        if (!chief)
            return 0.0;
        chief = (SP::cTribe_s00ce_33b0*)((void* (__thiscall*)(SP::cTribe_s00ce_33b0*))SP_GetChieftain)(tribe);
        if (chief->mFlagB5e == 0)
            return 0.0;
    } else if (ready != 0) {
        return 0.0;
    }
    void* plan = FindFirstEligiblePlanStep(planRef, 7, 1);
    if (plan == (void*)-1)
        return 0.0;
    if (stimuli)
        ((void (__thiscall*)(SP::cStimuli*))SP_GetAny)(stimuli);
    stimuli->mpValue1c = plan;
    stimuli->mValue18 = 7;
    *outFlag = 1;
    return 1.0;
}

// @ 0x00ce3b40
void __cdecl DeactivatePlanThunk1(void* plan, int a, int b, int c, int d, SP::PlanArgs* ctx)
{
    DeactivatePlan(plan, ctx->mpPlan, ctx->mpContext, 1);
}

// @ 0x00ce3e20
void __cdecl RaidingDeactivate(void* plan, int a, int b, int c, int d, SP::PlanArgs* ctx)
{
    void* audioValue = ctx->mpAudioValue;
    SP::AudioSystem* audio = (SP::AudioSystem*)GetSystemAT();
    if (audio) {
        ((void (__thiscall*)(void*, uint32_t))((void**)audio->mpVtable)[0x38 / 4])(audio, 0x0347536b);
        ((void (__thiscall*)(void*, uint32_t, void*))((void**)audio->mpVtable)[0x40 / 4])(audio, 0x03475385, audioValue);
        ((void (__thiscall*)(void*, uint32_t, int))((void**)audio->mpVtable)[0x40 / 4])(audio, 0x034753a0, 0);
        ((void (__thiscall*)(void*))((void**)audio->mpVtable)[0x58 / 4])(audio);
    }
    DeactivatePlan(plan, ctx->mpPlan, ctx->mpContext, 1);
}

// @ 0x00ce3e90
void __cdecl DeactivatePlanThunk0(void* plan, int a, int b, int c, int d, SP::PlanArgs* ctx)
{
    DeactivatePlan(plan, ctx->mpPlan, ctx->mpContext, 0);
}

// @ 0x00ce3eb0
bool OrderNearbyCitizensToAttack(OrderContext* pContext, float fRange, float fStep)
{
    cTribe_s00ce_3eb0* pTribe = pContext->mpTribe;
    void* pWorld = GetSimulatorContext();
    if (pWorld == nullptr || pContext->mnCount == 0)
        return false;

    cTribePlanConfiguration_s00ce_3eb0* pPlan = GetTribePlanConfiguration(pTribe->mTribeId);
    if (pPlan == nullptr)
        return false;

    fRange -= fStep;
    if (fRange < 0.0f) {
        fRange = 2.0f;
        uint32_t nCount = pContext->mnCount;
        if (nCount > pPlan->mMaxWorkers)
            nCount = pPlan->mMaxWorkers;

        void* pTool = pTribe->GetToolOfType(10);
        Vec3_s00ce_3eb0* pCenter = pTribe->GetPosition();
        float fRadius = GetTribeRadius(pTribe);
        float fLimit = fRadius * fRadius;
        float fSetting = fRadius * 0.75f;

        void* pCitizens = pTribe->GetCitizenList();
        for (int pass = 0; pass < 2 && nCount != 0; ++pass) {
            cSPCreatureCitizen** pBegin = (cSPCreatureCitizen**)*(void**)pCitizens;
            cSPCreatureCitizen** pEnd = (cSPCreatureCitizen**)*((void**)pCitizens + 1);
            for (cSPCreatureCitizen** ppCitizen = pBegin; ppCitizen != pEnd; ++ppCitizen) {
                if (nCount == 0)
                    break;
                cSPCreatureCitizen* pCitizen = *ppCitizen;
                if (!pCitizen->IsAvailable())
                    continue;
                if (!pCitizen->IsLeader() && pPlan->mMaxWorkers == 0)
                    continue;
                Vec3_s00ce_3eb0* pPosition = pCitizen->GetPosition();
                float fDx = pPosition->mX - pCenter->mX;
                float fDy = pPosition->mY - pCenter->mY;
                float fDz = pPosition->mZ - pCenter->mZ;
                float fDistance = fDx * fDx + fDy * fDy + fDz * fDz;
                if (pass == 0 ? fDistance < fLimit : fDistance > fLimit) {
                    if (GetSimulatorContext() != nullptr) {
                        --nCount;
                        Variant_s00ce_3eb0 param;
                        GiveCityOrder(4, fSetting);
                        pCitizen->GiveOrder(4, 10, &param);
                        ReleaseVariant(&param);
                    }
                }
            }
        }

        if (nCount != 0 && pPlan->mMaxWorkers != 0) {
            cSPCreatureCitizen* pChieftain = pTribe->GetChieftain();
            if (pChieftain != nullptr && pChieftain->IsAvailable()) {
                Vec3_s00ce_3eb0* pPosition = pChieftain->GetPosition();
                float fDx = pPosition->mX - pCenter->mX;
                float fDy = pPosition->mY - pCenter->mY;
                float fDz = pPosition->mZ - pCenter->mZ;
                if (fDx * fDx + fDy * fDy + fDz * fDz > fLimit) {
                    Variant_s00ce_3eb0 param;
                    GiveCityOrder(4, fSetting);
                    pChieftain->GiveOrder(4, 10, &param);
                    ReleaseVariant(&param);
                } else {
                    return false;
                }
            }
        }
        (void)pTool;
    }
    return true;
}

// @ 0x00ce4380
bool PlannerEquipWorkersActivate(OrderContext* pStep, cSPCreatureCitizen* pCitizen)
{
    cTribe_s00ce_3eb0* pTribe = pStep->mpTribe;
    void* pWorld = GetSimulatorContext();
    if (pWorld == nullptr)
        return false;

    cTribePlanConfiguration_s00ce_3eb0* pPlan = GetTribePlanConfiguration(pTribe->mTribeId);
    if (pPlan == nullptr)
        return false;

    void* pGroups = pTribe->GetPlanGroups();
    DestroyStepVector((PlannerGroup_s00ce_3eb0*)pGroups);

    pCitizen->v10();

    uint32_t nWorkers = pStep->mnCount;
    if (pPlan->mMaxWorkers < nWorkers)
        nWorkers = pPlan->mMaxWorkers;
    int nAvailable = (int)nWorkers;
    UpdatePlannerSteps(nAvailable, nullptr);

    PlannerStepArray counts;
    int nCount = 0;
    void* pArray = nullptr;
    if (ReadPlannerCounts(pPlan, 0x602f317, &nCount, &pArray) && nCount > 0) {
        for (int i = 0; i < nCount; ++i) {
            int nKind = ((int*)pArray)[i * 2];
            if ((uint)(nKind - 1) < 9) {
                float fValue = (float)nAvailable * ((float*)pArray)[i * 2];
                int nSteps = (int)(fValue + 0.5f);
                if ((float)nSteps < fValue)
                    ++nSteps;
                counts.mCounts[nKind] = nSteps;
            }
        }
    }

    Vec3_s00ce_3eb0* pCenter = pTribe->GetPosition();
    float fRadius = GetTribeRadius(pTribe);
    float fLimit = fRadius * fRadius;

    void* pCitizens = pTribe->GetCitizenList();
    cSPCreatureCitizen** pBegin = (cSPCreatureCitizen**)*(void**)pCitizens;
    cSPCreatureCitizen** pEnd = (cSPCreatureCitizen**)*((void**)pCitizens + 1);
    for (cSPCreatureCitizen** ppCitizen = pBegin; ppCitizen != pEnd; ++ppCitizen) {
        if (nAvailable == 0)
            break;
        cSPCreatureCitizen* pCreature = *ppCitizen;
        if (!pCreature->IsAvailable())
            continue;
        Vec3_s00ce_3eb0* pPosition = pCreature->GetPosition();
        float fDx = pPosition->mX - pCenter->mX;
        float fDy = pPosition->mY - pCenter->mY;
        float fDz = pPosition->mZ - pCenter->mZ;
        if (fDx * fDx + fDy * fDy + fDz * fDz >= fLimit)
            continue;
        if (pCreature->IsLeader() && pPlan->mMaxWorkers != 0)
            continue;

        --nAvailable;
        pCreature->v10();
        ClearAllOrders(pCreature, 0x1d3fbffa, 0x8124080);
        pCreature->ForceOrdersUpdate();

        if (!pCreature->IsLeader()) {
            for (uint32_t nKind = 1; nKind < 9; ++nKind) {
                if (counts.mCounts[nKind] == 0)
                    continue;
                void* pTool = pTribe->GetToolOfType((int)nKind);
                if (pTool == nullptr)
                    pTool = FindToolByType(nKind);
                if (pTool == nullptr)
                    continue;
                GiveToolOrder(pCreature, 3, pTool, 0);
                int nSlot = GetToolOrderSlot(pTool);
                counts.mCounts[nSlot] = counts.mCounts[nSlot] - 1;
                break;
            }
        }
    }

    if (pPlan->mMaxWorkers != 0 && pTribe->GetPopulation() < pPlan->mStepLimit) {
        cSPCreatureCitizen* pChieftain = pTribe->GetChieftain();
        if (pChieftain != nullptr && pChieftain->IsAvailable()) {
            Vec3_s00ce_3eb0* pPosition = pChieftain->GetPosition();
            float fDx = pPosition->mX - pCenter->mX;
            float fDy = pPosition->mY - pCenter->mY;
            float fDz = pPosition->mZ - pCenter->mZ;
            if (fDx * fDx + fDy * fDy + fDz * fDz < fLimit) {
                pChieftain->v10();
                ReleaseTrace(nullptr);
                if (pChieftain != nullptr)
                    pChieftain->Release();
            }
        }
    }
    return true;
}

// @ 0x00ce4810
bool PlannerCheckWorkers(OrderContext* pContext, float fRange, float fStep)
{
    void* pWorld = GetSimulatorContext();
    if (pWorld == nullptr || pContext->mnCount == 0)
        return false;

    cTribe_s00ce_3eb0* pTribe = pContext->mpTribe;
    cTribePlanConfiguration_s00ce_3eb0* pPlan = GetTribePlanConfiguration(pTribe->mTribeId);
    if (pPlan == nullptr)
        return false;

    fRange -= fStep;
    if (fRange < 0.0f) {
        void* pGroups = pTribe->GetPlanGroups();
        PlannerGroup_s00ce_3eb0* pGroup = (PlannerGroup_s00ce_3eb0*)*(void**)pGroups;
        PlannerGroup_s00ce_3eb0* pGroupEnd = (PlannerGroup_s00ce_3eb0*)*((void**)pGroups + 1);
        while (pGroup != pGroupEnd) {
            if (GetSimulatorContext() != nullptr)
                return true;
            ++pGroup;
        }
        return false;
    }
    return true;
}

// @ 0x00ce48f0
void cGonzagoSimulator::Update(float fDeltaTime, uint nFlags)
{
    if (mpTribe == nullptr || *(uint8_t*)((uint8_t*)mpTribe + 0x556) != 0)
        return;

    int* pContext = (int*)GetSimulatorContext();
    if (pContext != nullptr) {
        if (pContext[0xb] == 1 || pContext[0xb] == 2)
            return;
    }
    if ((GameTimeFlags() & 1) != 0)
        return;

    float fDelta = (float)GameTimeDelta(nFlags) * 0.001f;
    mTimer += fDelta;
    if (mTimer < 1.0f)
        return;

    mTimer -= 1.0f;
    uint32_t nDirty = 0;
    if (GetActiveContext() != nullptr)
        nDirty |= 2;

    PlannerGroup_s00ce_3eb0* pGroup = mpGroupBegin;
    for (; pGroup != mpGroupEnd; pGroup = (PlannerGroup_s00ce_3eb0*)((uint8_t*)pGroup + 0x18)) {
        float fRemaining = pGroup->mOwnerId - 1.0f;
        pGroup->mOwnerId = (uint32_t)fRemaining;
        if (fRemaining < 0.0f) {
            PlannerStep* pStep = pGroup->mpStepsBegin;
            int nSteps = (int)(pGroup->mpStepsEnd - pStep);
            for (int i = 0; i < nSteps; ++i, ++pStep) {
                if (pStep->mKind == 4)
                    continue;
                pStep->mTimer -= 1.0f;
                pStep->mActive = (pStep->mTimer < 0.0f);
                if (pStep->mTimer < 0.0f) {
                    nDirty |= 1;
                    if (pStep->mpPlan == nullptr)
                        pStep->mpPlan = GetTribePlanConfiguration(pStep->mOwnerId);
                    pStep->mTimer = (float)pStep->mpPlan->mSteps;
                }
            }
        }
    }

    void* pCitizens = mpTribe->GetCitizenList();
    cSPCreatureCitizen** pBegin = (cSPCreatureCitizen**)*(void**)pCitizens;
    cSPCreatureCitizen** pEnd = (cSPCreatureCitizen**)*((void**)pCitizens + 1);
    for (cSPCreatureCitizen** ppCitizen = pBegin; ppCitizen != pEnd; ++ppCitizen) {
        cSPCreatureCitizen* pCitizen = *ppCitizen;
        int nDamageState = pCitizen->GetPopulation();
        if (nDamageState != 2)
            nDirty |= 1u << (nDamageState & 0x1f);
    }

    cGameNounManager* pNouns = NounManager();
    cTribe_s00ce_3eb0* pPlayerTribe = pNouns->GetPlayerTribe();
    if (pPlayerTribe != nullptr) {
        uint32_t nPlayer = pPlayerTribe->GetAdultPopulation();
        uint32_t nLocal = mpTribe->GetAdultPopulation();
        pPlayerTribe->v10();
        (void)nPlayer;
        (void)nLocal;
    }
}

// @ 0x00ce4c40
int* CopyPlannerVector(int* pOut, int* pSrc)
{
    CopyPlannerStepRange((PlannerStep*)pSrc[0], (PlannerStep*)pSrc[1], (PlannerStep*)pOut[0]);
    CopyPlannerGroupsInternal((PlannerGroup_s00ce_3eb0*)pSrc, (PlannerGroup_s00ce_3eb0*)pSrc[0],
                              (PlannerGroup_s00ce_3eb0*)pSrc[1], (PlannerGroup_s00ce_3eb0*)pOut[0]);
    pOut[1] = pSrc[1];
    return pOut;
}

// @ 0x00ce4ca0
PlannerGroup_s00ce_3eb0* CopyPlannerGroups(PlannerGroup_s00ce_3eb0* pOut, PlannerGroup_s00ce_3eb0* pFirst, PlannerGroup_s00ce_3eb0* pLast, PlannerGroup_s00ce_3eb0* pOwner)
{
    pOut->mOwnerId = (uint32_t)(intptr_t)pOwner;
    while (pFirst != pLast) {
        PlannerGroup_s00ce_3eb0* pCurrent = pOut;
        if (pCurrent->mpStepsBegin != nullptr) {
            pCurrent->mOwnerId = pFirst->mOwnerId;
            int nSteps = (int)(pFirst->mpStepsEnd - pFirst->mpStepsBegin);
            PlannerStep* pCopy = nullptr;
            if (nSteps != 0)
                pCopy = (PlannerStep*)operator_new(nSteps * 0x58, "Simulator", 0, 0,
                                                   "EASTL/allocator.h", 0xd1);
            pCurrent->mpStepsBegin = pCopy;
            pCurrent->mpStepsEnd = pCopy;
            pCurrent->mpStepsCap = pCopy + nSteps;
            CopyPlannerStepRange(pFirst->mpStepsBegin, pFirst->mpStepsEnd, pCopy);
            pCurrent->mpStepsEnd = pCopy + nSteps;
        }
        ++pOut;
        ++pFirst;
    }
    return pOut;
}

// @ 0x00ce4d60
void FillPlannerGroups(PlannerGroup_s00ce_3eb0* pDest, int nCount, PlannerGroup_s00ce_3eb0* pSrc)
{
    for (int i = 0; i < nCount; ++i) {
        pDest->mOwnerId = pSrc->mOwnerId;
        int nSteps = (int)(pSrc->mpStepsEnd - pSrc->mpStepsBegin);
        PlannerStep* pCopy = nullptr;
        if (nSteps != 0)
            pCopy = (PlannerStep*)operator_new(nSteps * 0x58, "Simulator", 0, 0,
                                               "EASTL/allocator.h", 0xd1);
        pDest->mpStepsCap = pCopy + nSteps;
        pDest->mpStepsBegin = pCopy;
        pDest->mpStepsEnd = pCopy;
        CopyPlannerStepRange(pSrc->mpStepsBegin, pSrc->mpStepsEnd, pCopy);
        pDest->mpStepsEnd = pCopy + nSteps;
        ++pDest;
        ++pSrc;
    }
}

// @ 0x00ce4e10
void* FUN_00ce4e10(void* pFirst, void* pLast, void* pDest)
{
    PlannerGroup_s00ce_4e10* pSrc = (PlannerGroup_s00ce_4e10*)pFirst;
    PlannerGroup_s00ce_4e10* pOut = (PlannerGroup_s00ce_4e10*)pDest;

    if (pSrc == (PlannerGroup_s00ce_4e10*)pLast)
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
    } while (pSrc != (PlannerGroup_s00ce_4e10*)pLast);

    return pOut;
}

// @ 0x00ce4ed0
cTribePlanner_s00ce_4e10::~cTribePlanner_s00ce_4e10()
{
    if (mpBehaviorTreeData) {
        FUN_00bcae90(mpBehaviorTreeData, 0);
        operator_delete_array(mpBehaviorTreeData);
    }
    if (mpTribe) {
        ITracerBase* pTribe = (ITracerBase*)mpTribe;
        pTribe->TraceEnd();                          // vtable slot used as Release by the tribe
    }
    PlannerGroup_s00ce_4e10* pTimesBegin = (PlannerGroup_s00ce_4e10*)mTimeBetweenPlanExecutionByType.mpBegin;
    if (pTimesBegin) {
        if (((int32_t*)pTimesBegin)[-1] != 0)
            operator_delete_array(pTimesBegin);
    }
    PlannerGroupVector* pPlans = (PlannerGroupVector*)&mpPlansBegin;
    pPlans->DoDestroyValues(mpPlansBegin, mpPlansEnd);
    PlannerGroup_s00ce_4e10* pPlansBegin = pPlans->mpBegin;
    if (pPlansBegin)
        operator_delete_array(pPlansBegin);
}

// @ 0x00ce5050
PlannerGroupVector* PlannerGroupVector::FUN_00ce5050(const PlannerGroupVector* pOther)
{
    PlannerGroupVector* pVec = this;
    if (pOther == pVec)
        return pVec;

    PlannerGroup_s00ce_4e10* pSource = pOther->mpBegin;
    uint32_t nSource = (uint32_t)((char*)pOther->mpEnd - (char*)pSource) / 0x18;
    PlannerGroup_s00ce_4e10* pBegin = pVec->mpBegin;
    uint32_t nCapacity = (uint32_t)((char*)pVec->mpCapacity - (char*)pBegin) / 0x18;

    if (nCapacity < nSource) {
        PlannerGroup_s00ce_4e10* pNew = (PlannerGroup_s00ce_4e10*)FUN_00ce2cc0(pVec, nSource, pSource, pOther->mpEnd);
        FUN_00ce0e00(pVec->mpBegin, pVec->mpEnd);
        if (pVec->mpBegin) {
            if (((int32_t*)pVec->mpBegin)[-1] != 0)
                operator_delete_array(pVec->mpBegin);
        }
        pVec->mpEnd = (PlannerGroup_s00ce_4e10*)((char*)pNew + nSource * 0x18);
        pVec->mpBegin = pNew;
        pVec->mpCapacity = pVec->mpEnd;
        return pVec;
    }

    uint32_t nSize = (uint32_t)((char*)pVec->mpEnd - (char*)pBegin) / 0x18;
    if (nSize < nSource) {
        FUN_00ce2b30(pSource, (char*)pSource + nSize * 0x18, pBegin);
        PlannerGroup_s00ce_4e10* pIn = (PlannerGroup_s00ce_4e10*)((char*)pSource + nSize * 0x18);
        PlannerGroup_s00ce_4e10* pOtherEnd = pOther->mpEnd;
        void* pResult = nullptr;
        FUN_00ce29c0(&pResult, pIn, pOtherEnd, pVec->mpEnd, pOtherEnd);
        pVec->mpEnd = (PlannerGroup_s00ce_4e10*)((char*)pVec->mpBegin + nSource * 0x18);
        return pVec;
    }

    PlannerGroup_s00ce_4e10* pEnd = (PlannerGroup_s00ce_4e10*)FUN_00ce2b30(pSource, pOther->mpEnd, pBegin);
    FUN_00ce0e00(pEnd, pVec->mpEnd);
    pVec->mpEnd = (PlannerGroup_s00ce_4e10*)((char*)pVec->mpBegin + nSource * 0x18);
    return pVec;
}

// @ 0x00ce5190
int32_t PLANNER_RAIDING_Tick(PlannerGroupVector* pPlans, uint32_t uUnused, float fTimeout, void* pTargetPos, float fDuration, void* pPlanTable, PlanKey* pKey, cSPCreatureCitizen_s00ce_4e10* pOwner)
{
    (void)pPlans;
    void* pOrder = FUN_00bca2c0_s00ce_4e10();
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
    Vec3_s00ce_4e10* pPos = pFirstMember->GetPosition();
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
                cSPCreatureCitizen_s00ce_4e10* pCitizen = (cSPCreatureCitizen_s00ce_4e10*)*ppIt;
                if (!FUN_00bca2c0_s00ce_4e10()) {
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
        cSPCreatureCitizen_s00ce_4e10* pCitizen = (cSPCreatureCitizen_s00ce_4e10*)*ppIt;
        if (!FUN_00bca2c0_s00ce_4e10()) {
            void* pTool = ((cPlanOrder*)pFound)->GetOwner(nullptr);
            pCitizen->GiveOrder(0xf, pTool, nullptr);
        }
        FUN_00cdff70(pCitizen);
    }
    return 1;
}

// @ 0x00ce57e0
void PlannerStepVector::FUN_00ce57e0(PlannerStepData* pPos, uint32_t nCount, const PlannerStepData* pValue)
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

// @ 0x00ce5a80
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

// @ 0x00ce5b30
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

// @ 0x00ce5c40
void PlannerGroupVector::FUN_00ce5c40(PlannerGroup_s00ce_4e10* pPos, uint32_t nCount, PlannerGroup_s00ce_4e10* pValue)
{
    PlannerGroupVector* pVec = this;
    if ((uint32_t)((char*)pVec->mpCapacity - (char*)pVec->mpEnd) / 0x18 >= nCount) {
        if (nCount == 0)
            return;
        PlannerGroup_s00ce_4e10 value = *pValue;
        FUN_00ce4c40(&value.mpStepsBegin);
        PlannerGroup_s00ce_4e10* pEnd = pVec->mpEnd;
        uint32_t nTail = (uint32_t)((char*)pVec->mpEnd - (char*)pPos) / 0x18;
        if (nCount < nTail) {
            FUN_00ce4ca0((char*)pEnd + nCount * -0x18, pEnd, pEnd, pEnd);
            pVec->mpEnd = (PlannerGroup_s00ce_4e10*)((char*)pVec->mpEnd + nCount * 0x18);
            FUN_00ce5a40(pPos, (char*)pEnd + nCount * -0x18, pEnd);
            PlannerGroup_s00ce_4e10* pIt = (PlannerGroup_s00ce_4e10*)((char*)pPos + nCount * 0x18);
            for (; pPos != pIt; ++pPos) {
                pPos->mPlanType = value.mPlanType;
                ((PlannerGroupVector*)&pPos->mpStepsBegin)->FUN_00ce5050(
                             (const PlannerGroupVector*)&value.mpStepsBegin);
            }
        } else {
            FUN_00ce4d60(pEnd, nCount - nTail, &value, pPos);
            pVec->mpEnd = (PlannerGroup_s00ce_4e10*)((char*)pVec->mpEnd + (nCount - nTail) * 0x18);
            FUN_00ce4ca0(pPos, pPos, pEnd, pVec->mpEnd);
            pVec->mpEnd = (PlannerGroup_s00ce_4e10*)((char*)pVec->mpEnd + nTail * 0x18);
            PlannerGroup_s00ce_4e10* pIt = (PlannerGroup_s00ce_4e10*)((char*)pPos + nTail * 0x18);
            for (; pPos != pIt; ++pPos) {
                pPos->mPlanType = value.mPlanType;
                ((PlannerGroupVector*)&pPos->mpStepsBegin)->FUN_00ce5050(
                             (const PlannerGroupVector*)&value.mpStepsBegin);
            }
        }
        FUN_00ce0e00((PlannerGroup_s00ce_4e10*)value.mpStepsBegin, (void*)value.mpStepsCapacity);
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
    PlannerGroup_s00ce_4e10* pNew = nullptr;
    if (nRequired != 0)
        pNew = (PlannerGroup_s00ce_4e10*)operator_new(nRequired * 0x18, "Simulator", 0, 0,
                                           kEastlAllocatorFile, 0xd1);
    PlannerGroup_s00ce_4e10* pOldBegin = pVec->mpBegin;
    PlannerGroup_s00ce_4e10* pOldEnd = pVec->mpEnd;
    void* pMid = FUN_00ce4e10(pOldBegin, pPos, pNew);
    FUN_00ce2c10(pOldBegin, pPos, pNew);
    void* pResult = nullptr;
    FUN_00ce4d60(pMid, nCount, (void*)pValue, pMid);
    PlannerGroup_s00ce_4e10* pAfterNew = (PlannerGroup_s00ce_4e10*)((char*)pMid + nCount * 0x18);
    void* pTail = FUN_00ce4e10(pPos, pOldEnd, pAfterNew);
    FUN_00ce2c10(pPos, pOldEnd, pAfterNew);
    if (pOldBegin)
        operator_delete_array(pOldBegin);
    (void)pResult;
    pVec->mpEnd = (PlannerGroup_s00ce_4e10*)pTail;
    pVec->mpBegin = pNew;
    pVec->mpCapacity = (PlannerGroup_s00ce_4e10*)((char*)pNew + nRequired * 0x18);
}

// @ 0x00ce5e90
void PlannerGroupVector::FUN_00ce5e90(PlannerGroup_s00ce_4e10* pPos, PlannerGroup_s00ce_4e10* pValue)
{
    PlannerGroupVector* pVec = this;
    PlannerGroup_s00ce_4e10* pEnd = pVec->mpEnd;
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
    PlannerGroup_s00ce_4e10* pNew = nullptr;
    if (nNewCapacity == 0) {
        nNewCapacity = 1;
    } else {
        nNewCapacity *= 2;
    }
    if (nNewCapacity != 0)
        pNew = (PlannerGroup_s00ce_4e10*)operator_new(nNewCapacity * 0x18, "Simulator", 0, 0,
                                           kEastlAllocatorFile, 0xd1);
    PlannerGroup_s00ce_4e10* pOldBegin = pVec->mpBegin;
    PlannerGroup_s00ce_4e10* pMid = (PlannerGroup_s00ce_4e10*)FUN_00ce4e10(pOldBegin, pPos, pNew);
    FUN_00ce2c10(pOldBegin, pPos, pNew);
    if (pMid) {
        pMid->mPlanType = pValue->mPlanType;
        ((PlannerGroupVector*)&pMid->mpStepsBegin)->CopyFrom(
            (const PlannerGroupVector*)&pValue->mpStepsBegin);
    }
    PlannerGroup_s00ce_4e10* pOldEnd = pVec->mpEnd;
    void* pTail = FUN_00ce4e10(pPos, pOldEnd, pMid + 1);
    FUN_00ce2c10(pPos, pOldEnd, pMid + 1);
    if (pVec->mpBegin)
        operator_delete_array(pVec->mpBegin);
    pVec->mpEnd = (PlannerGroup_s00ce_4e10*)pTail;
    pVec->mpBegin = pNew;
    pVec->mpCapacity = (PlannerGroup_s00ce_4e10*)((char*)pNew + nNewCapacity * 0x18);
}

// @ 0x00ce5ff0
void PlannerGroupVector::FUN_00ce5ff0()
{
    PlannerGroupVector* pVec = this;
    PlannerGroup_s00ce_4e10* pBegin = pVec->mpBegin;
    PlannerGroup_s00ce_4e10* pEnd = pVec->mpEnd;
    PlannerGroup_s00ce_4e10* pKeep = (PlannerGroup_s00ce_4e10*)FUN_00ce5a00(pEnd, pEnd, pBegin);
    pVec->DoDestroyValues(pKeep, pVec->mpEnd);
    // retail divides the tail length by the negated element size, so the end pointer
    // folds back to the start of the vector
    pVec->mpEnd = (PlannerGroup_s00ce_4e10*)((char*)pVec->mpEnd +
                                  (((char*)pEnd - (char*)pBegin) / -0x18) * 0x18);
}

// @ 0x00ce6040
PlannerGroup_s00ce_4e10* PlannerGroupVector::FUN_00ce6040(PlannerGroup_s00ce_4e10* pPos, PlannerGroup_s00ce_4e10* pValue)
{
    PlannerGroupVector* pVec = this;
    int32_t nIndex = (int32_t)(pPos - pVec->mpBegin);
    if (pPos == pVec->mpEnd && pVec->mpEnd != pVec->mpCapacity) {
        PlannerGroup_s00ce_4e10* pEnd = pVec->mpEnd;
        pVec->mpEnd = pEnd + 1;
        if (pEnd) {
            pEnd->mPlanType = pValue->mPlanType;
            ((PlannerGroupVector*)&pEnd->mpStepsBegin)->CopyFrom(
                (const PlannerGroupVector*)&pValue->mpStepsBegin);
        }
    } else {
        pVec->FUN_00ce5e90(pPos, pValue);
    }
    return (PlannerGroup_s00ce_4e10*)((char*)pVec->mpBegin + nIndex * 0x18);
}

// @ 0x0135e000
void FUN_0135e000()
{
    T t;
    t.name = "mID"; t.hash = 0x58b5360u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00572810; t.f[2]=fn_00572840; t.f[3]=fn_00693090; t.f[4]=fn_00694f00; t.f[5]=fn_00b1fbf0; t.f[6]=fn_00675ca0; t.off=0;
    g_01580de0 = t;
    t.name = "mState"; t.hash = 0x58b5361u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00572810; t.f[2]=fn_00572840; t.f[3]=fn_00693090; t.f[4]=fn_00694f00; t.f[5]=fn_00b1fbf0; t.f[6]=fn_00675ca0; t.off=0x4;
    g_01580e1c = t;
    t.name = "mFrequency"; t.hash = 0x58b5362u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00572810; t.f[2]=fn_00572840; t.f[3]=fn_00693090; t.f[4]=fn_00694f00; t.f[5]=fn_00b1fbf0; t.f[6]=fn_00675ca0; t.off=0x8;
    g_01580e58 = t;
    t.name = "mCheckTime"; t.hash = 0x58b5363u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00572810; t.f[2]=fn_00ac88f0; t.f[3]=fn_006930b0; t.f[4]=fn_00694fc0; t.f[5]=fn_00b1fbf0; t.f[6]=fn_00acbb80; t.off=0xc;
    g_01580e94 = t;
    t.name = "mFoodRequired"; t.hash = 0x58b5364u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00572810; t.f[2]=fn_00572840; t.f[3]=fn_00692ff0; t.f[4]=fn_00694ee0; t.f[5]=fn_00b1fbf0; t.f[6]=fn_0057cde0; t.off=0x10;
    g_01580ed0 = t;
    t.name = "mFoodAccumulated"; t.hash = 0x58b5365u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00572810; t.f[2]=fn_00ac88f0; t.f[3]=fn_006930b0; t.f[4]=fn_00694fc0; t.f[5]=fn_00b1fbf0; t.f[6]=fn_00acbb80; t.off=0x14;
    g_01580f0c = t;
    t.name = "mbCheck"; t.hash = 0x58b5366u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00ac8750; t.f[2]=fn_00ac8780; t.f[3]=fn_00693090; t.f[4]=fn_00694fa0; t.f[5]=fn_00b1fbf0; t.f[6]=fn_0057ce00; t.off=0x18;
    g_01580f48 = t;
    t.name = "mWorkers"; t.hash = 0x58b536fu; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00ce26c0; t.f[2]=fn_00aca730; t.f[3]=fn_00c2e4e0; t.f[4]=fn_00692fb0; t.f[5]=fn_00b6f860; t.f[6]=fn_00c6c390; t.off=0x1c;
    g_01580f84 = t;
}
