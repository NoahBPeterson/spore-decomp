// src/game/SPGonzago/SPMissionManager.cpp -- migrated from slice(s) s01396a80, s00fef140, s00fee3d0, s00fed430, s00fec590, s00feb120 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoSimulator.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cIPropertyManager.h"
#include "SP/cSPMission.h"
#include "SP/cSPTimer.h"
#include "SP/cVarListSerializer.h"
#include <intrin.h>
#include "SP/cEmpire.h"
#include "SP/cGameData.h"

// ---- items of slice s00feb120 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char      u8;
typedef unsigned int       u32;
typedef signed int         i32;
typedef unsigned __int64   u64;
#define MOPS(p) ((COps*)(p))
static inline void** vtbl(const void* p) { return *(void***)p; }
void* FUN_01021300();                                  // 0x01021300
void* __stdcall FUN_01002bd0(u32 key);                 // 0x01002bd0
void* __stdcall FUN_00b3d3e0();                        // 0x00b3d3e0
void  __cdecl   FUN_0093aa70(void* stream, u32* v, int n, int m); // 0x0093aa70
void  __cdecl   FUN_0093a9a0(void* stream, void* v, int n);       // 0x0093a9a0
void  __stdcall FUN_00c47b10(u32 arg);                 // 0x00c47b10
struct COps
{
    u8  FUN_00bb9c00();                    // 0x00bb9c00
    void* FUN_00bfc5f0();                  // 0x00bfc5f0
    u8  FUN_00fe4180();                    // 0x00fe4180
    u8  FUN_00c31c50();                    // 0x00c31c50
    u8  FUN_00c31bc0();                    // 0x00c31bc0
    u8  FUN_00e18c70();                    // 0x00e18c70
    u8  FUN_00feba90();                    // 0x00feba90
    u8  FUN_007c4fd0();                    // 0x007c4fd0
    u8  FUN_01044bf0(void* civ);           // 0x01044bf0
    u8  FUN_010449e0(u32 arg);             // 0x010449e0
    i32  FUN_00dd5d80(u32 a, u32 b);       // 0x00dd5d80
    void FUN_00dd6d10(u32 a, u32 b);       // 0x00dd6d10
    void FUN_00695b40(void* a, void* b, void* c); // 0x00695b40
    void FUN_00c47d80();                   // 0x00c47d80
    void FUN_00c32cd0(float* out);         // 0x00c32cd0
    void FUN_007c3d30(float* a, float* b, int c, int d); // 0x007c3d30
    void FUN_007c3c10();                   // 0x007c3c10
    void FUN_007c50b0(void* src, u8 a, u8 b); // 0x007c50b0
    void FUN_005481d0(u32* pos, u32* value);  // 0x005481d0
    void FUN_00bc3110();                   // 0x00bc3110
    void FUN_00bb1080();                   // 0x00bb1080
    void FUN_00e25bd0(void* begin, void* end); // 0x00e25bd0
    u32  FUN_00b1fdb0();                   // 0x00b1fdb0
    u32  FUN_00ba9370();                   // 0x00ba9370
    i32  FUN_00c317a0();                   // 0x00c317a0
    void* FUN_00c308d0();                  // 0x00c308d0
    void* FUN_00bef6c0();                  // 0x00bef6c0
    void* FUN_00c8b360();                  // 0x00c8b360
    float* FUN_005c65e0();                 // 0x005c65e0
    float FUN_00ffbfd0();                  // 0x00ffbfd0
    double FUN_009360d0();                 // 0x009360d0
    u64  FUN_00bc3190();                   // 0x00bc3190
};
struct cMissionRequisite
{
    u32  pad00;                 // +0x00
    i32  mMinWeaponryLevel;     // +0x04
    u32* mSpeciesIDsBegin;      // +0x08
    u32* mSpeciesIDsEnd;        // +0x0c
    u32  pad10[10];             // +0x10 .. +0x37
};
class cSPMissionManager
{
public:
    u8   pad00[0x14];                              // +0x00
    bool mDebugDraw;                               // +0x14
    u8   pad15[0x34 - 0x15];                       // +0x15
    cMissionRequisite* mNPCMissionReqBegin;        // +0x34
    cMissionRequisite* mNPCMissionReqEnd;          // +0x38
    u8   pad3c[0x48 - 0x3c];                       // +0x3c
    cMissionRequisite* mColonyMissionReqBegin;     // +0x48
    cMissionRequisite* mColonyMissionReqEnd;       // +0x4c
    u8   pad50[0x80 - 0x50];                       // +0x50
    u32* mTutorialSpeciesIDs;                      // +0x80
    u8   pad84[0xa8 - 0x84];                       // +0x84
    void** mSlots;                                 // +0xa8
    u8   padAc[0xbc - 0xac];                       // +0xac
    u32  mMissionTimer;                            // +0xbc
    void* mTrackedMission;                         // +0xc0
    void* mMostRecentMission;                      // +0xc4
    u8   mNPCMissionList[0xc];                     // +0xc8
    u8   mColonyMissionList[0xc];                  // +0xd4
    u8   padE0[0x04];                              // +0xe0
    u32  mNPCMissionTimeLimit;                     // +0xe4
    u32  mColonyMissionTimeLimit;                  // +0xe8

    void FUN_00feba50();
    void RemoveNewMissionAvailableEventLog();
    u8   Write(void* stream);
    u32  FUN_00febc70();
    u8   IsNPCMissionAvailable(void* empire, i32 index);
    u8   FUN_00febd30(i32 index);
    u32  FUN_00febdc0(u32 index);
    void FUN_00febde0(u32 index, u32 value);
    u8   FUN_00febe00(void* key);
    u8   FUN_00febe50(void* key, u32* out);
    u32  FUN_00febe90();
    void FUN_00febeb0(void* mission);
    void FUN_00febf20(void* mission);
    i32  FUN_00febf80(void* key);
    void FUN_00fec430(i32 delta);
    void FUN_00fec4e0();
};
class cVarListSerializer
{
public:
    u32 pad[0x285];

    void FUN_00692f90(void* a, void* b, u32 c);   // 0x00692f90
    u8   FUN_00692900(void* stream);              // 0x00692900
};
// ---- items of slice s00feb120 end

// ---- items of slice s00fec590 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_szSimulator[];          // 0x013f09b4 "Simulator"
extern char g_szAllocatorH[];         // 0x013ebb38 "...EASTL/allocator.h"
void*  __cdecl NounManager();                                   // 0x00b3d300
void*  __cdecl PropertyManager();                               // 0x0067de30
bool   __cdecl GetPropertyAsKey(void* pProp, uint32_t nKey, void* pOut);   // 0x006a1250
void*  __cdecl operator_new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                            const char* pFile, int32_t nLine);  // 0x00f473a0
uint32_t* __fastcall FUN_00b8d8e0(void* pArg);                  // 0x00b8d8e0
class cRefObj {
public:
    virtual void AddRef();                  // +0x00
    virtual void Release();                 // +0x04
};
struct tKey {
    uint32_t mType;             // +0x00
    uint32_t mInstance;         // +0x04
    uint32_t mGroup;            // +0x08
};
class cProperty : public cRefObj {
public:
    virtual void* v08();                    // +0x08
    virtual void* v0c();                    // +0x0c
    virtual void* v10();                    // +0x10
    virtual void* v14();                    // +0x14
    virtual void* v18();                    // +0x18
    virtual void* v1c();                    // +0x1c
    virtual void* v20();                    // +0x20
    virtual bool  v24(uint32_t nKey, void** ppOut);     // +0x24
    uint8_t  mPad04[0xe];                   // +0x04
    uint16_t mnType12;                      // +0x12
    uint32_t* GetUInt();                    // 0x0041ea00
    float*    GetFloat();                   // 0x0041ea70
};
class cIPropertyManager {
public:
    virtual void* v00();                    // +0x00
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();
    virtual void* v20();
    virtual void* v24();
    virtual void* v28();
    virtual void  v2c(uint32_t nA, uint32_t nB, void** ppOut);  // +0x2c
};
class cSPMission {
public:
    virtual void AddRef();                  // +0x00
    virtual void Release();                 // +0x04
    virtual void* v08();                    // +0x08
    virtual void* v0c();                    // +0x0c
    virtual void* v10();                    // +0x10
    virtual void* v14();                    // +0x14
    virtual void* v18();                    // +0x18
    virtual void* v1c();                    // +0x1c
    virtual void* v20();                    // +0x20
    virtual void* v24();                    // +0x24
    virtual void* v28();                    // +0x28
    virtual void* v2c();                    // +0x2c
    virtual void* v30();                    // +0x30
    virtual void* v34();                    // +0x34
    virtual void* v38();                    // +0x38
    virtual void* v3c();                    // +0x3c
    virtual void* v40();                    // +0x40
    virtual void* v44();                    // +0x44
    virtual void* v48();                    // +0x48
    virtual void* v4c();                    // +0x4c
    virtual void* v50();                    // +0x50
    virtual void* v54();                    // +0x54
    virtual void* v58();                    // +0x58
    virtual void* v5c();                    // +0x5c
    virtual void* v60();                    // +0x60
    virtual void* v64();                    // +0x64
    virtual void* v68();                    // +0x68
    virtual void* v6c();                    // +0x6c
    virtual void* v70();                    // +0x70
    virtual void* v74();                    // +0x74
    virtual bool  v78();                    // +0x78
    uint8_t  mData04[0x178];                // +0x004
    uint32_t mn17c;                         // +0x17c
    void SetMissionID(uint32_t nID);        // 0x00c470f0
    void FUN_00c47140(uint32_t nArg);       // 0x00c47140
    void FUN_00c45d30(uint32_t nArg);       // 0x00c45d30
    void FUN_00febb50(uint32_t nArg);       // 0x00febb50
    void FUN_00c47b10(uint32_t nArg);       // 0x00c47b10
    bool IsVisibleInUI();                   // 0x00c45340
    void TriggerUIUpdate();                 // 0x00c47d80
};
class cGonzagoTimer {
public:
    void Destroy();                         // 0x00b638b0
    void*    mpVtbl00;          // +0x00
    uint32_t m04;               // +0x04
    uint32_t m08;               // +0x08
    uint32_t m0c;               // +0x0c
    uint32_t m10;               // +0x10
    uint32_t m14;               // +0x14
    uint8_t  m18;               // +0x18
    uint8_t  mPad19[3];         // +0x19
    uint32_t m1c;               // +0x1c
    uint32_t m20;               // +0x20
    uint32_t m24;               // +0x24
    uint32_t m28;               // +0x28
};
class cSPTimer {
public:
    bool IsRunning();                       // 0x00feba90
};
struct tTimerValue {
    uint32_t      m00;          // +0x00
    uint32_t      m04;          // +0x04
    cGonzagoTimer mTimer;       // +0x08
    tTimerValue* CopyFrom(const tTimerValue* pSrc);     // 0x00fecb50
};
struct tTimerNode {
    tTimerNode* mpNext;         // +0x00
    tTimerNode* mpPrev;         // +0x04
    tTimerValue mValue;         // +0x08
};
class cTimerList {
public:
    tTimerNode* mpNext;         // +0x00
    tTimerNode* mpPrev;         // +0x04
    uint32_t    mUnk08;         // +0x08
    void DestroyAll();                                  // 0x00fecb20
    void FUN_00fecfc0(const tTimerValue& rValue);       // 0x00fecfc0
};
struct tRec38 {
    uint8_t   mPad00[8];        // +0x00
    void*     mpArr08;          // +0x08
    uint8_t   mPad0c[0x10];     // +0x0c
    void*     mpArr1c;          // +0x1c
    uint8_t   mPad20[0x18];     // +0x20
};
struct tRecVec {
    tRec38* mpBegin;            // +0x00
    tRec38* mpEnd;              // +0x04
    tRec38* mpCap;              // +0x08
    void FUN_00fecc40(tRec38* pBegin, tRec38* pEnd);    // 0x00fecc40
};
class tUintVec {
public:
    uint32_t* mpBegin;          // +0x00
    uint32_t* mpEnd;            // +0x04
    uint32_t* mpCap;            // +0x08
    void push_back(const uint32_t& nValue)
    {
        uint32_t* p = mpEnd;
        if (p < mpCap) {
            mpEnd = p + 1;
            if (p != 0)
                *p = nValue;
        } else {
            DoInsertValue(p, nValue);
        }
    }
    uint32_t* DoInsertValue(uint32_t* pPos, const uint32_t& nValue);  // 0x004558a0
};
struct cMapIter {
    void* mpNode;               // +0x00
    cMapIter(const cMapIter& rOther);
};
class cRbtreeUint {
public:
    uint32_t  mUnk00;           // +0x00
    void*     mpEndNode;        // +0x04 anchor node (this+0x5c+0x04)
    void*     mpEndNodeSelf;    // +0x08
    void*     mpRoot;           // +0x0c
    uint32_t  mb10;             // +0x10
    uint32_t  mn14;             // +0x14
    cMapIter Find(const uint32_t& rKey);                // 0x00e5c780
    void     Erase(const uint32_t& rKey);               // 0x00b2b5b0
    void     NukeSubtree(void* pRoot);                  // 0x009a9600
};
struct tMissionSlotVec {
    cSPMission** mpBegin;       // +0x00
    cSPMission** mpEnd;         // +0x04
    cSPMission** mpCap;         // +0x08
    uint32_t     mAlloc;        // +0x0c
    void Destroy();             // 0x00ae6970
};
class cGameNounManager {
public:
    cSPMission* CreateMissionBiosphere();           // 0x00fec0a0
    cSPMission* CreateMissionFetch();               // 0x00fec0c0
    cSPMission* CreateRaidEvent();                  // 0x00fec0e0
    cSPMission* CreateRaidPlunderEvent();           // 0x00fec100
    cSPMission* CreateMissionExplore();             // 0x00fec120
    cSPMission* CreateMissionColonize();            // 0x00fec140
    cSPMission* CreateMissionTerraform();           // 0x00fec160
    cSPMission* CreateMissionEradicate();           // 0x00fec180
    cSPMission* CreateGenericPressureEvent();       // 0x00fec1a0
    cSPMission* CreateMissionWar();                 // 0x00fec1c0
    cSPMission* CreateMissionScan();                // 0x00fec1e0
    cSPMission* CreateMissionMultiDelivery();       // 0x00fec200
    cSPMission* CreateMissionMultiStep();           // 0x00fec220
    cSPMission* CreateMissionBalance();             // 0x00fec240
    cSPMission* CreateMissionFindAliens();          // 0x00fec260
    cSPMission* CreateMissionHappinessEvent();      // 0x00fec280
    cSPMission* CreateMissionMakeAlly();            // 0x00fec2a0
    cSPMission* CreateMissionFlight101();           // 0x00fec2c0
    cSPMission* CreateMissionUseTool();             // 0x00fec2e0
    cSPMission* CreateMissionStory201();            // 0x00fec300
    cSPMission* CreateMissionTrade();               // 0x00fec320
    cSPMission* CreateMissionTradeRoute();          // 0x00fec340
    cSPMission* FUN_00fec360();                     // 0x00fec360
    cSPMission* FUN_00fec380();                     // 0x00fec380
    cSPMission* FUN_00fec3a0();                     // 0x00fec3a0
    void RemoveNoun(void* pNoun);                   // 0x00b225d0
};
class cSPMissionManager_s00fe_c590 {
public:
    void*    mpVtbl00;          // +0x000
    uint32_t mUnk04;            // +0x004
    void*    mpVtbl08;          // +0x008
    uint32_t mUnk0c;            // +0x00c
    void*    mpVtbl10;          // +0x010
    uint8_t  mb14;              // +0x014
    uint8_t  mb15;              // +0x015
    uint8_t  mb16;              // +0x016
    uint8_t  mb17;              // +0x017
    uint8_t  mb18;              // +0x018
    uint8_t  mPad19[3];         // +0x019
    void*    mpUnk1c;           // +0x01c
    tRecVec  mRecVec20;         // +0x020
    uint32_t mUnk2c;            // +0x02c
    uint32_t mUnk30;            // +0x030
    tRecVec  mRecVec34;         // +0x034
    uint32_t mUnk40;            // +0x040
    uint32_t mUnk44;            // +0x044
    tRecVec  mRecVec48;         // +0x048
    uint32_t mUnk54;            // +0x054
    uint32_t mUnk58;            // +0x058
    cRbtreeUint mFeedbackMap;   // +0x05c
    uint32_t mUnk74;            // +0x074
    cProperty* mpProp78;        // +0x078
    cProperty* mpProp7c;        // +0x07c
    uint32_t* mpArr80;          // +0x080
    uint32_t mUnk84;            // +0x084
    uint32_t mUnk88;            // +0x088
    uint32_t mUnk8c;            // +0x08c
    uint32_t mUnk90;            // +0x090
    uint32_t* mpArr94;          // +0x094
    uint32_t mUnk98;            // +0x098
    uint32_t mUnk9c;            // +0x09c
    uint32_t mUnkA0;            // +0x0a0
    uint32_t mUnkA4;            // +0x0a4
    tMissionSlotVec mSlotVec;   // +0x0a8
    uint32_t mUnkB8;            // +0x0b8
    uint32_t mnBC;              // +0x0bc
    cSPMission* mpC0;           // +0x0c0
    cSPMission* mpC4;           // +0x0c4
    cTimerList mListC8;         // +0x0c8
    cTimerList mListD4;         // +0x0d4
    uint32_t mnE0;              // +0x0e0
    uint32_t mnE4;              // +0x0e4
    uint32_t mnE8;              // +0x0e8
    uint32_t mnEC;              // +0x0ec
    tKey     mKeyF0;            // +0x0f0
    tKey     mKeyFC;            // +0x0fc
    tUintVec mVec108;           // +0x108
    uint32_t mUnk114;           // +0x114
    uint32_t mUnk118;           // +0x118
    tUintVec mVec11c;           // +0x11c
    uint32_t mUnk128;           // +0x128
    uint32_t mUnk12c;           // +0x12c
    tUintVec mVec130;           // +0x130

    cSPMission* CreateMissionFromID(uint32_t nMissionID, uint32_t nArg2, uint32_t nArg3, uint32_t nArg4);  // 0x00fec590
    bool FUN_00fec8a0(void* pArg);                                      // 0x00fec8a0
    bool FUN_00fec900(void* pArg);                                      // 0x00fec900
    bool FUN_00fec960(cSPMission* pMission);                            // 0x00fec960
    void FUN_00feca20(cSPMission* pMission);                            // 0x00feca20
    void FUN_00fecbb0(uint32_t nKey);                                   // 0x00fecbb0
    uint32_t FUN_00fecbf0();                                            // 0x00fecbf0
    cSPMissionManager_s00fe_c590* FUN_00fecc90();                                  // 0x00fecc90
    void FUN_00fece20();                                                // 0x00fece20
    void CacheProperties();                                             // 0x00fed0b0
    void FUN_00febeb0(cSPMission* pMission);                            // 0x00febeb0
};
static __forceinline bool HasTimerForKey(cTimerList* pList, void* pArg)
{
    tTimerNode* pEnd = (tTimerNode*)pList;
    for (tTimerNode* p = pList->mpNext; p != pEnd; p = p->mpNext) {
        tTimerValue* pv = &p->mValue;
        if (pv != 0) {
            uint32_t* pKey = FUN_00b8d8e0(pArg);
            if (pv->mTimer.m20 == pKey[0] &&
                pv->mTimer.m24 == pKey[1] &&
                pv->mTimer.m28 == pKey[2] &&
                ((cSPTimer*)&pv->mTimer)->IsRunning())
                return false;
        }
    }
    return true;
}
// ---- items of slice s00fec590 end

// ---- items of slice s00fed430 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_fWeightScale;          // 0x01488874
extern float g_fWeightBase;           // 0x013f9428
#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct cPropertyList; struct Property;
struct cEmpire; struct cPlanetRecord; struct RefCounted;
class cGameData;
struct cSPMission_s00fe_d430;
struct cSPMissionManager_s00fe_d430;
struct Record38;
template <class T> class SPVector
{
public:
    T*     mpBegin;     // +0x00
    T*     mpEnd;       // +0x04
    T*     mpCapacity;  // +0x08
    struct Alloc
    {
        void* mpName;     // +0x0c
        void* mPool;      // +0x10
    };
    Alloc  mAlloc;      // +0x0c

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }

    // out of line in the original; body is not emitted in this TU
    void assign(const SPVector<T>* src);   // 0x0050d4e0
    void reserve(uint32_t n);              // 0x004e0880
    void DoInsertValueI(T* where, T const& v);   // 0x004558a0
    void DoInsertKey(T* where, T const& v);      // 0x004e3e10
    void DoInsertPtr(T* where, T const& v);      // 0x00aea5d0
    void DoInsertKey4(T* where, T const& v);     // 0x00b96600

    void push_back(T const& v)
    {
        if (mpEnd < mpCapacity)
        {
            T* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot)
                *slot = v;
        }
        else
        {
            DoInsertKey(mpEnd, v);
        }
    }
};
struct Property
{
    void*    mpData;      // +0x00
    uint32_t pad04;       // +0x04
    uint32_t mnCount;     // +0x08 (element count when array / external data)
    uint32_t pad0c;       // +0x0c
    uint8_t  mnFlags;     // +0x10 (0x30 = array / external data)
    uint8_t  pad11[1];
    uint16_t mnType;      // +0x12

    void* GetValuePtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
};
struct cPropertyList
{
    virtual int  AddRef();                                    // +0x00
    virtual int  Release();                                   // +0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual Property* GetProperty(uint32_t id);               // +0x28
    virtual bool GetProperty2(uint32_t id, uint32_t id2, void* out);  // +0x2c
};
cPropertyList* PropertyManager_s00fe_d430();                             // 0x0067de30
struct RefCounted
{
    virtual int  AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
};
struct AutoRefCount
{
    void* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) ((RefCounted*)mpObject)->Release(); }
    AutoRefCount& operator=(RefCounted* p)
    {
        if (p) p->AddRef();
        if (mpObject) ((RefCounted*)mpObject)->Release();
        mpObject = p;
        return *this;
    }
};
struct Key
{
    uint32_t mType;      // +0x00
    uint32_t mGroup;     // +0x04
    uint32_t mInstance;  // +0x08
};
struct cGonzagoTimer_s00fe_d430                    // 0x20 bytes
{
    int64_t mElapsedTime;               // +0x00
    int64_t mBaseTime;                  // +0x08
    uint8_t mbRunning;                  // +0x10
    uint8_t pad11[3];
    uint32_t mGetMillisecondTime;       // +0x14
    uint8_t pad18[8];                   // +0x18 (base vtable slot)

    cGonzagoTimer_s00fe_d430();                    // 0x00b63890
    ~cGonzagoTimer_s00fe_d430();                   // 0x00b638b0
    void Restart();                     // 0x00bc3130
    cGonzagoTimer_s00fe_d430& operator=(const cGonzagoTimer_s00fe_d430& o)
    {
        mElapsedTime = o.mElapsedTime;
        mBaseTime = o.mBaseTime;
        mbRunning = o.mbRunning;
        mGetMillisecondTime = o.mGetMillisecondTime;
        return *this;
    }
};
struct tRecentMission                  // 0x34 bytes
{
    uint32_t      mID;                 // +0x00
    uint32_t      pad04;
    cGonzagoTimer_s00fe_d430 mTime;               // +0x08
    Key           mKey;                // +0x28

    tRecentMission() : mID(0), mTime()
    {
        mKey.mType = 0;
        mKey.mGroup = 0;
        mKey.mInstance = 0;
    }
};
struct ListAnchor
{
    void* mpNext;      // +0x00
    void* mpPrev;      // +0x04
    void Ctor();                        // 0x00fecb20
    void Add(tRecentMission* v);        // 0x00fecfc0
};
extern Key kZeroKey;                    // 0x016dac78 (zero-initialized Key constant)
extern uint32_t kMinusOne;              // 0x014948cc (0xffffffff constant)
struct RecentNode { void* mpNext; void* mpPrev; tRecentMission mValue; };
void GameData_cd7d10();  // 0x00cd7d10
void GameData_d3d420();  // 0x00d3d420
void GameData_fed010();  // 0x00fed010
void GameData_b1e520();  // 0x00b1e500 / 0x00b1e520
typedef void (*GameDataFn)();
struct GameDataList
{
    cGameData** mpBegin;     // +0x04
    cGameData** mpEnd;       // +0x08
    cGameData** mpCapacity;  // +0x0c
    void*       mAllocator;  // +0x10
};
struct GameDataVector
{
    uint32_t mbDirty;        // +0x00
    GameDataList mData;      // +0x04
};
class cGameData
{
public:
    PV2 PV                                    // +0x00..+0x08
    virtual void* Cast(uint32_t type);        // +0x0c (0x463329e -> cSPMission)
    PV16 PV8 PV4                              // +0x10..+0x7c
    virtual void g80();                       // +0x80
};
struct cGameNounManager_s00fe_d430
{
    GameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d,
                                      uint32_t type);            // 0x00b21340
    void RemoveNoun(void* noun);                                 // 0x00b225d0
};
cGameNounManager_s00fe_d430* NounManager_s00fe_d430();               // 0x00b3d300
void*             SimTicker();                 // 0x00b3d330
struct cSimTicker
{
virtual void t00();
virtual void t04();
virtual void t08();
virtual void t0c();
virtual void t10();
virtual void t14();
virtual void t18();
virtual void t1c();
virtual void t20();
virtual void t24();
virtual void t28();
virtual void t2c();
virtual void t30();
virtual void t34();
virtual void t38();
virtual void t3c();
virtual void t40();
virtual void t44();
virtual void t48();
virtual void t4c();
    virtual void RegisterMissionManager(void* mgr);   // +0x50
};
void*             StarManager();               // 0x00b3d2a0
void*             GetPlayerEmpire();           // 0x01021300
void*             GetPlayerHomePlanet();       // 0x01021370
struct cVectorMapper { void Assign(uint32_t n); };
struct TC_PlanetRec { Key* MapToKey(); };
struct cPlanet
{
    uint32_t      pad00[0x13c / 4];   // +0x00
    TC_PlanetRec* mpRecord;           // +0x13c
};
void* GetEmpirePropList(void* empire);                  // 0x00baf700
uint32_t GetStarEmpireID(void* starManager, void* star);// 0x00885c90
struct cMissionRequisitesParser
{
    void FillList(void* out);                           // 0x00fef9f0
};
void* MakeRequisiteParser();                            // 0x00fef670
void* __stdcall MakeRequisiteParser(uint32_t id);       // 0x00fef670
void  __stdcall SetSerializer(void* parser, int zero);  // 0x00c2e4e0
struct cSerializerParser { void SetSerializer(); };     // 0x00c2e4e0 (thiscall, no args)
void  operator delete(void* p);                         // 0x00f47380 (scalar deleting dtor helper)
void* EAAllocate(int size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
void ReadInt32(void* reader, void* dst, int count, int flag);   // 0x0093a780
struct cSerialStream
{
virtual void  v00();
virtual void  v04();
virtual void  v08();
virtual void  v0c();
virtual void  v10();
virtual void  v14();
    virtual void* v18();      // +0x18
    virtual void  v1c();      // +0x1c
    virtual void* v20();      // +0x20
};
struct cVarListSerializer_s00fe_d430
{
    void* mpValue;
    void* mpStream;      // +0x04
    void* mpVtbl0;       // +0x08
    uint32_t mFlags;     // +0x0c
    uint32_t mFlags2;    // +0x10
    uint8_t  mByte;      // +0x14
    uint32_t mDword;     // +0x18
    uint32_t mDword2;    // +0x1c
    uint32_t mDword3;    // +0x20
    uint32_t mDword4;    // +0x24

    cVarListSerializer_s00fe_d430(void* value, void* stream, uint32_t id);   // 0x00692f90
    bool Serialize(void* stream);                                 // 0x00693e10
};
struct MissionStateMap
{
    uint32_t* operator[](const uint32_t& key);   // 0x00643a40
};
struct MessageBasicRC5
{
    uint32_t vftable0;    // +0x00
    volatile long mRefCount;   // +0x04
    uint32_t mData[10];   // +0x08 (mUint32[5])
    uint32_t mId;         // +0x30
    uint32_t mPad34;      // +0x34 (never written)
    uint32_t mRCFlags;    // +0x38
    void*    pad3c;       // +0x3c
};
struct MsgRCDtor { void Destroy(); };
struct cMessageServer
{
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void Send(uint32_t id, void* msg, int flag);   // +0x14
};
cMessageServer* MessageServer();                            // 0x0067dcc0
struct Record38
{
    uint32_t mWord0;      // +0x00
    uint32_t mWord1;      // +0x04
    SPVector<float> mVecA;  // +0x08 (0x14)
    SPVector<float> mVecB;  // +0x1c (0x14)
    uint32_t mWord30;     // +0x30
    uint32_t mWord34;     // +0x34
};
extern uint32_t kSerializerStream;    // 0x015b49b0
struct cSPMission_s00fe_d430
{
virtual void vf00();
virtual void vf04();
virtual void vf08();
    virtual void* Cast(uint32_t type);                       // +0x0c (0x463329e -> cSPMission)
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1c();
virtual void vf20();
virtual void vf24();
virtual void vf28();
virtual void vf2c();
virtual void vf30();
virtual void vf34();
virtual void vf38();
virtual void vf3c();
virtual void vf40();
virtual void vf44();
virtual void vf48();
virtual void vf4c();
virtual void vf50();
virtual void vf54();
virtual void vf58();
virtual void vf5c();
virtual void vf60();
virtual void vf64();
virtual void vf68();
virtual void vf6c();
virtual void vf70();
virtual void vf74();
virtual void vf78();
virtual void vf7c();
virtual void vf80();
virtual void vf84();
virtual void vf88();
virtual void vf8c();
virtual void vf90();
virtual void vf94();
virtual void vf98();
virtual void vf9c();
virtual void vfa0();
virtual void vfa4();
virtual void vfa8();
virtual void vfac();
virtual void vfb0();
virtual void vfb4();
virtual void vfb8();
virtual void vfbc();
virtual void vfc0();
virtual void vfc4();
virtual void vfc8();
virtual void vfcc();
virtual void vfd0();
virtual void vfd4();
virtual void vfd8();
virtual void vfdc();
virtual void vfe0();
virtual void vfe4();
virtual void vfe8();
virtual void vfec();
    virtual void vff0();                                     // +0xf0 (115)
    virtual bool vff4(void* a);                              // +0xf4 (116)
    virtual bool vff8();                                     // +0xf8
    virtual void vffc();
virtual void v100();
virtual void v104();
virtual void v108();
virtual void v10c();
virtual void v110();
virtual void v114();
virtual void v118();
virtual void v11c();
virtual void v120();
virtual void v124();
virtual void v128();
virtual void v12c();
virtual void v130();
virtual void v134();
virtual void v138();
virtual void v13c();
    virtual bool Query140(void* a, void* b);                 // +0x140
virtual void v144();
virtual void v148();
virtual void v14c();
virtual void v150();
virtual void v154();
virtual void v158();
virtual void v15c();
virtual void v160();
virtual void v164();
virtual void v168();
virtual void v16c();
virtual void v170();
    virtual void SetTargetPlanet(void* planet);              // +0x174

    uint32_t pad04[0x130 / 4 - 1];                           // +0x04 (vptr at +0x00)
    uint8_t  mbEventFlag;                                    // +0x130 (bit 0)
    uint8_t  pad131[3];
    char     pad134[0x17c - 0x134];
    cSPMission_s00fe_d430* mpParentMission;                             // +0x17c

    cSPMission_s00fe_d430* GetSourcePlanet();                           // 0x00c45ce0
    void*       GetOwnerEmpire();                            // 0x00c451e0
    int         GetMissionID();                              // 0x01030e10
    void*       GetTargetPlanet();                           // 0x00970b30
    bool        IsActive();                                  // 0x00c44c80
    void        SP_CacheLocalizedStrings();                     // 0x00c44f50
};
void SP_CacheLocalizedStrings();   // 0x00c44f50
struct cSPMissionManager_s00fe_d430
{
    char  pad00[0x14];
    bool  mbDebugDraw;            // +0x14
    bool  mbDebugFlag;            // +0x15
    bool  mbFlightSchoolFinished; // +0x16
    char  pad17;
    uint32_t mCheatMissionIDOverride;   // +0x18
    uint32_t mNextMissionID;            // +0x1c
    SPVector<void*> mTutorialMissionReqList;  // +0x20
    SPVector<void*> mNPCMissionReqList;       // +0x34
    SPVector<void*> mColonyMissionReqList;    // +0x48
    void*    mTutorialMissionStates;          // +0x5c (map, 0x1c)
    void*    pad60[6];                        // +0x60 .. +0x78
    cPropertyList* mpProperties;              // +0x78 (intrusive ptr)
    void*    pad7c;                           // +0x7c
    SPVector<uint32_t> mTutorialTargetPlanetKeys;  // +0x80
    SPVector<Key>      mTutorialSpeciesIDs;        // +0x94
    SPVector<AutoRefCount> mTrackedMissions;       // +0xa8
    char     padbc[0xc8 - 0xbc];
    ListAnchor mRecentColonyMissions;         // +0xc8
    void*      padc8_4;                       // +0xd0
    ListAnchor mRecentNPCMissions;            // +0xd4
    char     pade0[0x17c - 0xe0];

    // named methods
    uint32_t GetMissionWeightForColony(uint32_t key);          // 0x00fed430
    uint32_t GetMissionWeightForEmpire(void* empire, uint32_t key);  // 0x00fed640
    void*    GetMissionList();                                 // 0x00fedd50
    int      GetNumNonEventMissions(char includeEventChildren); // 0x00fedd80
    int      GetNumEventMissions();                            // 0x00feddf0
    bool     DoMissionsPreventHostility(void* a, void* b);     // 0x00fedea0
    void     SetTutorialMissionState1(uint32_t id);            // 0x00fede40
    void     SetTutorialMissionState2(uint32_t id);            // 0x00fede60
    void     SetTutorialMissionState3(uint32_t id);            // 0x00fede80
    float    FindListWeightA(uint32_t missionID);              // 0x00fedf20
    float    FindListWeightB(uint32_t missionID);              // 0x00fedfe0
    void     ForEachActiveSetTargetPlanet(void* planet);       // 0x00fee0a0
    bool     AnyActiveMatchA(void* a);                         // 0x00fee110
    bool     AnyActiveMatchB(void* a);                         // 0x00fee190
    cSPMission_s00fe_d430* FindMissionByTargetPlanet(void* planetRecord);  // 0x00fee220
    void     AddRecentMissionA(cSPMission_s00fe_d430* m, bool restart);   // 0x00fed890
    void     RemoveMissionInternal(cSPMission_s00fe_d430* m);             // 0x00febe00
    void     InitForGame();                                    // 0x00fedb50
    bool     RemoveMission(cSPMission_s00fe_d430* m);                     // 0x00fedca0
    void     PostLoad();                                       // 0x00fee310
    void     CacheProperties();                                // 0x00fed0b0
};
// ---- items of slice s00fed430 end

// ---- items of slice s00fee3d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* SpaceGameGet();                                                   // 0x01002bd0
void* RelationshipManager();                                            // 0x00b3d2c0
void* GetSpaceRelationshipTuning();                                     // 0x010407c0
void* FUN_00b3d2a0();                                                   // 0x00b3d2a0
int   FUN_00fec010(void* weights);                                      // 0x00fec010
void  operator_delete_array(void* p);                                   // 0x00f47380
struct cSPMission_s00fe_e3d0;
struct SpVecPV {
    void** mpBegin;                     // +0x00
    void** mpEnd;                       // +0x04
    void** mpCap;                       // +0x08
};
struct MissionList {
    unsigned mPad00;                    // +0x00
    SpVecPV  mItems;                    // +0x04 <-- returned list's vector
};
struct cGameNounManager_s00fe_e3d0 {
    MissionList* GetGameDataVector(unsigned a, unsigned b, unsigned c, unsigned d, int e); // 0x00b21340
    char* GetCurrentTerrainSphere();                                            // 0x00f67d90
};
struct RelMgr     { float calc(unsigned a, unsigned b, int c); };   // 0x00d00a10
struct RelTuning  { float get(); };                                 // 0x01040860
struct StarMgr    { void  PickRandomAsset(void** out, int flag); }; // 0x00bb7940
struct InsertVec  { char  FUN_00fe4180(unsigned key); };            // 0x00fe4180
struct cMissionHelper { void FUN_00c4b240(void* asset); };         // 0x00c4b240
struct TerrainSphere {
    char FUN_00c75d70(void* empire, void** out);      // 0x00c75d70
    char FUN_00c772c0(unsigned flag);                 // 0x00c772c0
};
struct cModel { char mPad00[0x13c]; void* mPlanet; };   // planet pointer at +0x13c
struct cEmpire {
    char     mPad00[0x58];                    // +0x000
    int      mArchetype;                      // +0x058
    char     mPad5c[0x84 - 0x5c];             // +0x05c
    unsigned mEmpireID;                       // +0x084
    void*  GetHomePlanet();                   // 0x00c31730
    int    GetWeaponryLevel();                // 0x00c317a0
    char   FUN_00c31bc0(cEmpire* other);      // 0x00c31bc0
};
struct cSPMission_s00fe_e3d0 {
    unsigned GetMissionID();                  // 0x01030e10
    void*    GetOwnerEmpire();                // 0x00c451e0
    cModel*  GetModel();                      // 0x00c45ce0
    void*    GetTargetPlanet();               // 0x00970b30
    char     IsActive();                      // 0x00c44c80
};
struct Req38 {
    unsigned  mMissionID;             // +0x00
    unsigned  mPad04;                 // +0x04
    unsigned* mpVec;                  // +0x08  (begin)
    unsigned* mpVecEnd;               // +0x0c
    char      mPad10[0x30 - 0x10];    // +0x10
    unsigned  mFlags30;               // +0x30
    unsigned  mFlags34;               // +0x34
};
struct MapNode {
    MapNode* mpNodeRight;             // +0x00
    MapNode* mpNodeLeft;              // +0x04
    MapNode* mpNodeParent;            // +0x08
    int      mColor;                  // +0x0c
    unsigned mKey;                    // +0x10
    unsigned mValue;                  // +0x14
};
struct MissionStateMap_s00fe_e3d0 {
    unsigned mPad00;                  // +0x00
    MapNode  mAnchor;                 // +0x04

    MapNode* findNode(const unsigned& key) const
    {
        MapNode* anchor = (MapNode*)&mAnchor;
        MapNode* lower = anchor;
        MapNode* cur = mAnchor.mpNodeParent;
        while (cur != 0) {
            if (cur->mKey >= key) {
                lower = cur;
                cur = cur->mpNodeLeft;
            } else {
                cur = cur->mpNodeRight;
            }
        }
        if (lower == anchor || key < lower->mKey) {
            lower = anchor;
        }
        return lower;
    }

    MapNode** find(MapNode** result, const unsigned* key) const;   // 0x00e5c780
};
struct SpVectorF {
    float* mpBegin;                   // +0x00
    float* mpEnd;                     // +0x04
    float* mpCap;                     // +0x08
    void   resize(int n);             // 0x004afc80
};
struct cGameData_s00fe_e3d0 {
    char        mPad00[0x70];         // +0x000
    InsertVec*  mOwner;               // +0x070
    InsertVec*  SetGameDataOwner2();  // 0x00bfc5f0
};
struct cSPMissionManager_s00fe_e3d0 {
    char  mPad00[0x14];               // +0x000
    bool  mDebugDraw;                 // +0x014
    char  mPad15[0x1c - 0x15];        // +0x015
    unsigned* mForcedMission;         // +0x01c
    Req38* mTutBegin;                 // +0x020
    Req38* mTutEnd;                   // +0x024
    char  mPad28[0x34 - 0x28];        // +0x028
    Req38* mNpcBegin;                 // +0x034
    Req38* mNpcEnd;                   // +0x038
    char  mPad3c[0x48 - 0x3c];        // +0x03c
    Req38* mColBegin;                 // +0x048
    Req38* mColEnd;                   // +0x04c
    char  mPad50[0x5c - 0x50];        // +0x050
    MissionStateMap_s00fe_e3d0 mStates;          // +0x05c
    char  mPad78[0xe0 - 0x78];        // +0x078
    unsigned mMaxMissions;            // +0x0e0
    char  mPadE4[0xec - 0xe4];        // +0x0e4
    int   mWeaponryThreshold;         // +0x0ec
    char  mPadF0[0x108 - 0xf0];       // +0x0f0
    unsigned* mVec108;                // +0x108
    unsigned* mVec10c;                // +0x10c
    char  mPad110[0x11c - 0x110];     // +0x110
    unsigned* mVec11c;                // +0x11c
    unsigned* mVec120;                // +0x120
    char  mPad124[0x130 - 0x124];     // +0x124
    unsigned* mVec130;                // +0x130
    unsigned* mVec134;                // +0x134

    unsigned    GetNumNonEventMissions(int flag);                       // 0x00fedd80
    cSPMission_s00fe_e3d0* CreateMissionFromID(unsigned id, void* planet, void* empire, int flags); // 0x00fec590
    char  FUN_00fec900(void* planet);                                   // 0x00fec900
    char  FUN_00fec8a0(void* planet);                                   // 0x00fec8a0
    char  FUN_00fecbf0();                                               // 0x00fecbf0
    char  FUN_00febd30(int index);                                      // 0x00febd30
    int   GetMissionWeightForColony(unsigned id);                       // 0x00fed430
    int   GetMissionWeightForEmpire(unsigned id, void* empire);         // 0x00fed640
    float FUN_00fedfe0(unsigned id);                                    // 0x00fedfe0
    float FUN_00fedf20(unsigned id);                                    // 0x00fedf20
    char  IsNPCMissionAvailable(void* empire, int index);               // 0x00febc90

    char  FUN_00fee3d0(void* empire, void* planet);
    cSPMission_s00fe_e3d0* GetMissionByID(int id);  // 0x00fee480 (cSPMissionManager::GetMissionByID)
    cSPMission_s00fe_e3d0* GetActiveMissionForEmpireAndPlanet(void* empire, void* planet);  // 0x00fee4f0 (cSPMissionManager::GetActiveMissionForEmpireAndPlanet)
    char  IsPlanetARaidTarget(void* planet, unsigned* out);  // 0x00fee590 (cSPMissionManager::IsPlanetARaidTarget)
    int   HasMissionConversationWithEmpireAndPlanet(void* empire, void* planet);  // 0x00fee6b0 (cSPMissionManager::HasMissionConversationWithEmpireAndPlanet)
    char  FUN_00fee730(void* empire, void* planet);
    char  FUN_00fee820();
    void  DebugDraw();  // 0x00fee8d0 (cSPMissionManager::DebugDraw)
    char  FUN_00fee930(int id);
    unsigned GetNextAvailableTutorialMission();  // 0x00feea60 (cSPMissionManager::GetNextAvailableTutorialMission)
    char  FUN_00feebb0();
    char  FUN_00feec30();
    char  FUN_00feecb0();
    unsigned FUN_00feed30(void* empire, void* planet);
};
// ---- items of slice s00fee3d0 end

// ---- items of slice s00fef140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00b3d300();                            // SP::NounManager
extern "C" void* __cdecl FUN_00b3d330();                            // SP::SimTicker
extern "C" void* __cdecl FUN_00cd7d10();
extern "C" void* __cdecl FUN_00d3d420();
extern "C" void* __cdecl FUN_00fed010();
extern "C" void* __cdecl FUN_00b1e520();
extern "C" void* __cdecl FUN_00fee2b0(void*, void*, void*);
#pragma warning(disable : 4100)
struct IEmpty {};
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
struct IRefCount {
    virtual void AddRef();                               // +0x00 (slot 0)
    virtual void Release();                              // +0x04 (slot 1)
};
struct IHTTPRequest {
    virtual void FUN_00(int);                            // +0x00 (slot 0)
};
void* __cdecl FUN_00fef670();
void  __cdecl FUN_00fef6b0();
IHTTPRequest* g_16dacb8;                                 // 0x016dacb8  HTTPRequest singleton
struct spVecF {
    float* mpBegin;                                      // +0x00
    float* mpEnd;                                        // +0x04
    u32    mCap;                                         // +0x08
    u32    mAlloc;                                       // +0x0c
    u32    mExtra;                                       // +0x10

    void* FUN_004aa350(int count, u32* alloc);           // 0x004aa350 (ret 8)  allocate
    void  FUN_0050d4e0(spVecF* src);                     // 0x0050d4e0 (ret 4)  operator=
    void  FUN_00fecc40(void* a, void* b);                // 0x00fecc40 (ret 8)
    void* FUN_00fef570(void* a, void* b);                // 0x00fef570 (ret 8)  our target
};
struct IVM00 : VPad<3, IEmpty>  { virtual void* FUN_0c(u32); };              // +0x0c
struct IVM01 : VPad<7, IVM00>   { virtual bool  FUN_2c(); };                  // +0x2c
struct IVM02 : VPad<9, IVM01>   { virtual void  FUN_54(); };                  // +0x54
struct IVM03 : VPad<2, IVM02>   { virtual int   FUN_60(); };                  // +0x60
struct IVM04 : VPad<6, IVM03>   { virtual int   FUN_7c(void*); };             // +0x7c
struct IVM05 : VPad<2, IVM04>   { virtual void  FUN_88(); };                  // +0x88
struct IVM06 : IVM05            { virtual void  FUN_8c(); };                   // +0x8c
struct IVM07 : IVM06            { virtual void  FUN_90(); };                   // +0x90
struct IVM08 : IVM07            { virtual void  FUN_94(); };                   // +0x94
struct IVM09 : IVM08            { virtual void  FUN_98(); };                   // +0x98
struct IVM10 : VPad<2, IVM09>   { virtual void* FUN_a4(void*, void*, void*, void*); }; // +0xa4
struct cSourcePlanet;
struct cSPMission_s00fe_f140 : IVM10 {
    u8  pad004[0x130 - 0x04];
    u32 mField_130;                                      // +0x130
    u8  pad134[0x17c - 0x134];
    u32 mField_17c;                                      // +0x17c

    cSourcePlanet* GetSourcePlanet();                    // 0x00c45ce0 (ret 0)
    void           SetState(int);                        // 0x00c47cc0 (ret 4)
    u32            GetMissionID();                       // 0x01030e10 (ret 0)
};
struct cSourcePlanet {
    u8  pad000[0x13c];
    u32 mField_13c;                                      // +0x13c
};
struct cGameNounManager_s00fe_f140 {
    void* GetGameDataVector(void*, void*, void*, void*, u32);  // 0x00b21340 (ret 0x14)
    void  RemoveNounsWithInterface(u32);                       // 0x00b227c0 (ret 4)
};
struct cMissionVec {                                     // vector<cSPMission*> result view
    u8            pad00[4];
    cSPMission_s00fe_f140**  mpBegin;                               // +0x04
    cSPMission_s00fe_f140**  mpEnd;                                 // +0x08
};
struct cSerializerUser {
    void SetSerializer();                                // 0x00c2e4e0
};
struct cSimTicker_s00fe_f140 : VPad<21, IEmpty> {
    virtual void FUN_54(void*);                          // +0x54 (slot 21)
};
struct cSPMissionManager_s00fe_f140 {
    u8    pad000[0x16];
    u8    mFlag_16;                                      // +0x16
    u8    pad017[0x20 - 0x17];
    spVecF mReq_20;                                      // +0x20  mTutorialMissionReqList
    spVecF mReq_34;                                      // +0x34  mNPCMissionReqList
    spVecF mReq_48;                                      // +0x48  mColonyMissionReqList
    u8    pad5c[0xc0 - 0x5c];
    void* mpField_c0;                                    // +0xc0  refcounted
    void* mpField_c4;                                    // +0xc4  refcounted

    void  CleanupArchive(void*);                         // 0x00fef140 (ret 4)
    void  OnTick(void*);                                 // 0x00fef3b0 (ret 8)
    void  ShutdownForGame();                             // 0x00fef5d0

    bool  FUN_00fee930(u32);                             // 0x00fee930 (ret 4)
    int   GetNextAvailableTutorialMission();             // 0x00feea60
    void  FUN_00fec4e0();                                // 0x00fec4e0
    void  FUN_00fec430(void*);                           // 0x00fec430 (ret 4)
    void  FUN_00fedca0(cSPMission_s00fe_f140*);                     // 0x00fedca0 (ret 4)
};
// ---- items of slice s00fef140 end

// ---- items of slice s01396a80 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0139_6a80; 
}
typedef eastl::string8_s0139_6a80 string8_s0139_6a80;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0139_6a80&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
struct Attribute
{
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = 0;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ int setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
template<typename T> bool IRead(ISerializerReadStream*, void*);
}
namespace Simulator {
template<typename T> bool IWrite(ISerializerWriteStream*, void*);
}
namespace Simulator {
template<typename T> void IReadText(const string8_s0139_6a80&, void*);
}
namespace Simulator {
template<typename T> void IWriteText(char*, void*);
}
namespace Simulator {
template<typename T> bool IValid();
}
namespace Simulator {
template<typename T> bool IToXml(void*, const char*, int);
}
namespace Simulator {
bool AV_bool();                              // 0x00b1fbf0
}
namespace Simulator {
bool TX_bool(void*, const char*, int);       // 0x0057ce00
}
namespace Simulator {
void NoopRT(const string8_s0139_6a80&, void*);          // 0x00c2e4e0
}
namespace Simulator {
void NoopWT(char*, void*);                   // 0x00692fb0
}
namespace Simulator {
struct M0; struct M1; struct M2; struct M3; struct M4;
}
namespace Simulator {
struct M5; struct M6; struct M7; struct M8;
}
namespace Simulator {
extern AttrSlot g_missionAttrs[];   // 0x015b4b90
}
namespace Simulator {
#define ADD3(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&g_missionAttrs[IDX] = a; }
}
// ---- items of slice s01396a80 end

// @ 0x00feba10
void cSPMissionManager::RemoveNewMissionAvailableEventLog()
{
    i32 id = MOPS(FUN_00b3d3e0())->FUN_00dd5d80(0xe737105a, 0);
    if (id != 0)
    {
        MOPS(FUN_00b3d3e0())->FUN_00dd6d10(id, 0);
    }
}

// @ 0x00feba50
void cSPMissionManager::FUN_00feba50()
{
    mDebugDraw = (mDebugDraw == 0);
}

// @ 0x00febb90
u8 cSPMissionManager::Write(void* stream)
{
    void* a = (*(void* (__thiscall**)(void*))((char*)vtbl(stream) + 0x20))(stream);
    void* b = (*(void* (__thiscall**)(void*))((char*)vtbl(a) + 0x18))(a);
    u32 key = 0x2aa56c7;
    FUN_0093aa70(b, &key, 1, 0);
    cVarListSerializer ser;
    ser.FUN_00692f90((void*)((char*)this - 8), (void*)0x15b4b90, 0x1a80d26);
    return ser.FUN_00692900(stream);
}

// @ 0x00febc70
u32 cSPMissionManager::FUN_00febc70()
{
    u32 r = (u32)mMostRecentMission;
    if (r == 0)
        r = (u32)mTrackedMission;
    return r;
}

// @ 0x00febc90
u8 cSPMissionManager::IsNPCMissionAvailable(void* empire, i32 index)
{
    i32 count = (i32)(mNPCMissionReqEnd - mNPCMissionReqBegin);
    if (index >= count)
        return 0;

    cMissionRequisite* req = mNPCMissionReqBegin + index;
    i32 n = (i32)(req->mSpeciesIDsEnd - req->mSpeciesIDsBegin);
    for (i32 i = 0; i < n; i++)
    {
        u32 id = req->mSpeciesIDsBegin[i];
        void* noun = FUN_01002bd0(id);
        void* a = MOPS(noun)->FUN_00bfc5f0();
        u8 ok = MOPS(a)->FUN_00fe4180();
        if (!ok)
            return 0;
    }

    if (empire != 0)
    {
        if (empire != FUN_01021300())
        {
            i32 lvl = MOPS(empire)->FUN_00c317a0();
            if (lvl < req->mMinWeaponryLevel)
                return 0;
        }
    }
    return 1;
}

// @ 0x00febd30
u8 cSPMissionManager::FUN_00febd30(i32 index)
{
    i32 count = (i32)(mColonyMissionReqEnd - mColonyMissionReqBegin);
    if (index >= count)
        return 0;

    cMissionRequisite* req = mColonyMissionReqBegin + index;
    i32 n = (i32)(req->mSpeciesIDsEnd - req->mSpeciesIDsBegin);
    for (i32 i = 0; i < n; i++)
    {
        u32 id = req->mSpeciesIDsBegin[i];
        void* noun = FUN_01002bd0(id);
        void* a = MOPS(noun)->FUN_00bfc5f0();
        u8 ok = MOPS(a)->FUN_00fe4180();
        if (!ok)
            return 0;
    }
    return 1;
}

// @ 0x00febdc0
u32 cSPMissionManager::FUN_00febdc0(u32 index)
{
    if (index < 2)
        return mTutorialSpeciesIDs[index];
    return 0;
}

// @ 0x00febde0
void cSPMissionManager::FUN_00febde0(u32 index, u32 value)
{
    if (index < 2)
        mTutorialSpeciesIDs[index] = value;
}

// @ 0x00febe00
u8 cSPMissionManager::FUN_00febe00(void* key)
{
    u32 i = 0;
    void** slot = mSlots;
    do
    {
        if (*slot == key)
        {
            FUN_00c47b10(0);
            void* p = mSlots[i];
            if (p != 0)
            {
                mSlots[i] = 0;
                (*(void (__thiscall**)(void*))((char*)vtbl(p) + 4))(p);
            }
            return 1;
        }
        i++;
        slot++;
    } while (i < 3);
    return 0;
}

// @ 0x00febe50
u8 cSPMissionManager::FUN_00febe50(void* key, u32* out)
{
    u32 i = 0;
    void** slot = mSlots;
    do
    {
        if (*slot == key)
        {
            if (out != 0)
                *out = ((u32*)0x16dac54)[i];
            return 1;
        }
        i++;
        slot++;
    } while (i < 3);
    return 0;
}

// @ 0x00febe90
u32 cSPMissionManager::FUN_00febe90()
{
    void** slot = mSlots;
    u32 n = 0;
    if (slot[0] != 0)
        n = 1;
    if (slot[1] != 0)
        n = n + 1;
    if (slot[2] != 0)
        n = n + 1;
    return n;
}

// @ 0x00febeb0
void cSPMissionManager::FUN_00febeb0(void* mission)
{
    void* old = mTrackedMission;
    if (old != mission)
    {
        if (mission != old)
        {
            if (mission != 0)
                (*(void (__thiscall**)(void*))vtbl(mission))(mission);
            mTrackedMission = mission;
            if (old != 0)
                (*(void (__thiscall**)(void*))((char*)vtbl(old) + 4))(old);
        }
        if (old != 0)
            MOPS(old)->FUN_00c47d80();
        if (mTrackedMission != 0)
            MOPS(mTrackedMission)->FUN_00c47d80();
        mMissionTimer = 0;
    }
}

// @ 0x00febf20
void cSPMissionManager::FUN_00febf20(void* mission)
{
    void* old = mMostRecentMission;
    if (old != mission)
    {
        if (mission != old)
        {
            if (mission != 0)
                (*(void (__thiscall**)(void*))vtbl(mission))(mission);
            mMostRecentMission = mission;
            if (old != 0)
                (*(void (__thiscall**)(void*))((char*)vtbl(old) + 4))(old);
        }
        if (old != 0)
            MOPS(old)->FUN_00c47d80();
        if (mMostRecentMission != 0)
            MOPS(mMostRecentMission)->FUN_00c47d80();
    }
}

// @ 0x00febf80
i32 cSPMissionManager::FUN_00febf80(void* key)
{
    u32 i = 0;
    void** slot = mSlots;
    do
    {
        if (*slot == key)
            return (i32)((u32*)0x16dac54)[i];
        i++;
        slot++;
    } while (i < 3);
    return -1;
}

// @ 0x00febfd0
u8 FUN_00febfd0(void* self, u32* list)
{
    for (u32* p = (u32*)*list; p != list; p = (u32*)*p)
    {
        if (p + 2 != 0)
            MOPS(self)->FUN_00695b40(p + 2, (void*)0x15b49b0, (void*)0x14948dc);
    }
    return 1;
}

// @ 0x00fec010
i32 FUN_00fec010(int* v)
{
    double sum = 0.0;
    float* p = (float*)v[0];
    float* end = (float*)v[1];
    if (p != end)
    {
        do
        {
            sum += *p;
            p++;
        } while (p != end);

        if (0.0 < sum)
        {
            double r = MOPS((void*)0x1601760)->FUN_009360d0() * sum;
            if (r < sum)
            {
                double acc = 0.0;
                i32 i = 0;
                for (float* q = (float*)v[0]; q != (float*)v[1]; q++)
                {
                    acc += *q;
                    if (r < acc)
                        return i;
                    i++;
                }
            }
            return (((i32)v[1] - (i32)v[0]) >> 2) - 1;
        }
    }
    return ((i32)v[1] - (i32)v[0]) >> 2;
}

// @ 0x00fec3c0
void* FUN_00fec3c0(void* obj, u8* value)
{
    u32 one = 1;
    void* a = (*(void* (__thiscall**)(void*))((char*)vtbl(obj) + 0x20))(obj);
    void* b = (*(void* (__thiscall**)(void*))((char*)vtbl(a) + 0x18))(a);
    FUN_0093aa70(b, &one, 1, 0);

    u8 flag = (u8)(*value & 1);
    void* c = (*(void* (__thiscall**)(void*))((char*)vtbl(obj) + 0x20))(obj);
    void* d = (*(void* (__thiscall**)(void*))((char*)vtbl(c) + 0x18))(c);
    bool bv = flag != 0;
    FUN_0093a9a0(d, &bv, 1);
    return obj;
}

// @ 0x00fec430
void cSPMissionManager::FUN_00fec430(i32 delta)
{
    if (mMostRecentMission != 0)
    {
        void* p = mTrackedMission;
        if (p != 0)
        {
            if (p != 0)
            {
                mTrackedMission = 0;
                (*(void (__thiscall**)(void*))((char*)vtbl(p) + 4))(p);
                MOPS(p)->FUN_00c47d80();
            }
            if (mTrackedMission != 0)
                MOPS(mTrackedMission)->FUN_00c47d80();
            mMissionTimer = 0;
        }
    }

    void* q = mTrackedMission;
    if (q != 0)
    {
        mMissionTimer = mMissionTimer + (u32)delta;
        if (mMissionTimer >= 0x2710)
        {
            if (q != 0)
            {
                mTrackedMission = 0;
                (*(void (__thiscall**)(void*))((char*)vtbl(q) + 4))(q);
                MOPS(q)->FUN_00c47d80();
            }
            if (mTrackedMission != 0)
                MOPS(mTrackedMission)->FUN_00c47d80();
            mMissionTimer = 0;
        }
    }
}

// @ 0x00fec4e0
void cSPMissionManager::FUN_00fec4e0()
{
    u8* head = (u8*)&mNPCMissionList;
    u8* n = *(u8**)head;
    while (n != (u8*)&mNPCMissionList)
    {
        if ((u8*)n + 8 != 0)
        {
            void* timer = (u8*)n + 0x10;
            if (MOPS(timer)->FUN_00feba90())
            {
                u64 elapsed = MOPS(timer)->FUN_00bc3190();
                if (elapsed > (u64)mNPCMissionTimeLimit)
                    MOPS(timer)->FUN_00bc3110();
            }
        }
        n = *(u8**)n;
    }

    u8* n2 = *(u8**)&mColonyMissionList;
    while (n2 != (u8*)&mColonyMissionList)
    {
        if ((u8*)n2 + 8 != 0)
        {
            void* timer = (u8*)n2 + 0x10;
            if (MOPS(timer)->FUN_00feba90())
            {
                u64 elapsed = MOPS(timer)->FUN_00bc3190();
                if (elapsed > (u64)mColonyMissionTimeLimit)
                    MOPS(timer)->FUN_00bc3110();
            }
        }
        n2 = *(u8**)n2;
    }
}

// @ 0x00fec590
cSPMission* cSPMissionManager_s00fe_c590::CreateMissionFromID(uint32_t nMissionID, uint32_t nArg2, uint32_t nArg3, uint32_t nArg4)
{
    cGameNounManager* pMgr = (cGameNounManager*)NounManager();
    if (pMgr == 0)
        return 0;

    cProperty* pProp = 0;
    cIPropertyManager* pPM = (cIPropertyManager*)PropertyManager();
    if (pProp != 0) {
        cProperty* pOld = pProp;
        pProp = 0;
        pOld->Release();
    }
    pPM->v2c(nMissionID, 0x2ae1a8e, (void**)&pProp);
    if (pProp == 0)
        return 0;

    tKey key;
    key.mType = 0;
    key.mInstance = 0;
    key.mGroup = 0;
    if (!GetPropertyAsKey(pProp, 0x874b25b6, &key)) {
        if (pProp != 0)
            ((cRefObj*)pProp)->Release();
        return 0;
    }

    cSPMission* pMission = 0;
    switch ((int32_t)key.mType) {
        case (int32_t)0x9bdd8110: pMission = pMgr->CreateMissionFindAliens();      break;
        case (int32_t)0x9bd15777: pMission = pMgr->FUN_00fec3a0();                 break;
        case (int32_t)0x91531c40: pMission = pMgr->CreateMissionTradeRoute();      break;
        case (int32_t)0xa1396bc8: pMission = pMgr->CreateMissionHappinessEvent();  break;
        case (int32_t)0xa4b0a2df: pMission = pMgr->CreateRaidEvent();              break;
        case (int32_t)0xa6b569f0: pMission = pMgr->CreateMissionMultiDelivery();   break;
        case (int32_t)0xa7c92499: pMission = pMgr->CreateGenericPressureEvent();   break;
        case (int32_t)0xd65fef61: pMission = pMgr->CreateMissionTrade();           break;
        case (int32_t)0xb05a389f: pMission = pMgr->CreateMissionStory201();        break;
        case (int32_t)0xc4956aa7: pMission = pMgr->CreateRaidPlunderEvent();       break;
        case (int32_t)0xf8d26ebe: pMission = pMgr->CreateMissionMultiStep();       break;
        case (int32_t)0x008ef6a62: pMission = pMgr->CreateMissionScan();           break;
        case (int32_t)0x0138e7c32: pMission = pMgr->FUN_00fec360();                break;
        case (int32_t)0x0426613e9: pMission = pMgr->CreateMissionWar();            break;
        case (int32_t)0x02ee35d17: pMission = pMgr->FUN_00fec380();                break;
        case (int32_t)0x018b48685: pMission = pMgr->CreateMissionMakeAlly();       break;
        case (int32_t)0x0199219ff: pMission = pMgr->CreateMissionBalance();        break;
        case (int32_t)0x0228ad516: pMission = pMgr->CreateMissionExplore();        break;
        case (int32_t)0x0311cc10f: pMission = pMgr->CreateMissionBiosphere();      break;
        case (int32_t)0x03f013663: pMission = pMgr->CreateMissionFetch();          break;
        case (int32_t)0x053da5f60: pMission = pMgr->CreateMissionUseTool();        break;
        case (int32_t)0x044fe5504: pMission = pMgr->CreateMissionColonize();       break;
        case (int32_t)0x045c3d5e9: pMission = pMgr->CreateMissionEradicate();      break;
        case (int32_t)0x060462563: pMission = pMgr->CreateMissionTerraform();      break;
        case (int32_t)0x07b883cb5: pMission = pMgr->CreateMissionFlight101();      break;
    }

    if (pMission == 0) {
        if (pProp != 0)
            ((cRefObj*)pProp)->Release();
        return pMission;
    }

    pMission->SetMissionID(nMissionID);
    pMission->FUN_00c47140(nArg2);
    pMission->FUN_00c45d30(nArg3);
    pMission->FUN_00febb50(nArg4);
    if (pMission->v78() != 0) {
        if (pProp != 0)
            ((cRefObj*)pProp)->Release();
        return pMission;
    }

    pMgr->RemoveNoun(pMission);
    if (pProp != 0)
        ((cRefObj*)pProp)->Release();
    return 0;
}

// @ 0x00fec8a0
bool cSPMissionManager_s00fe_c590::FUN_00fec8a0(void* pArg)
{
    return HasTimerForKey(&mListC8, pArg);
}

// @ 0x00fec900
bool cSPMissionManager_s00fe_c590::FUN_00fec900(void* pArg)
{
    return HasTimerForKey(&mListD4, pArg);
}

// @ 0x00fecfc0
void cTimerList::FUN_00fecfc0(const tTimerValue& rValue)
{
    tTimerNode* pFirst = mpNext;
    tTimerNode* pNode = (tTimerNode*)operator_new(0x40, g_szSimulator, 0, 0, g_szAllocatorH, 0xd1);
    tTimerValue* pv = &pNode->mValue;
    if (pv != 0)
        pv->CopyFrom(&rValue);

    pNode->mpNext = pFirst;
    pNode->mpPrev = pFirst->mpPrev;
    pFirst->mpPrev->mpNext = pNode;
    pFirst->mpPrev = pNode;
}

// @ 0x00fed430
uint32_t cSPMissionManager_s00fe_d430::GetMissionWeightForColony(uint32_t key)
{
    cPropertyList*& props = *(cPropertyList**)&mpProperties;
    cPropertyList* localProps = mpProperties;
    if (localProps == 0)
    {
        cPropertyList* pm = PropertyManager_s00fe_d430();
        localProps = mpProperties;
        if (localProps)
        {
            mpProperties = 0;
            ((RefCounted*)localProps)->Release();
            props = 0;
        }
        pm->GetProperty2(0x1254b050, 0x2ae1a8e, &mpProperties);
        localProps = mpProperties;
    }

    uint32_t* keysBegin = 0; uint32_t* keysEnd = 0; uint32_t* keysCap = 0;
    Property* prop = localProps->GetProperty(0x3f3fa37);
    ((cVectorMapper*)&keysBegin)->Assign(prop->mnFlags & 0x30 ? prop->mnCount
                                                       : (uint32_t)(prop->mnType != 0));
    uint32_t* keys = (uint32_t*)prop->GetValuePtr();
    uint32_t count = prop->mnFlags & 0x30 ? prop->mnCount
                                          : (uint32_t)(prop->mnType != 0);
    if (count > 0)
    {
        uint32_t n = count;
        uint32_t* slot = keysBegin;
        uint32_t* cap = keysEnd;
        do
        {
            uint32_t v = *keys;
            if (slot < cap)
            {
                uint32_t* nxt = slot + 1;
                keysBegin = nxt;
                if (slot)
                    *slot = v;
            }
            else
            {
                ((SPVector<uint32_t>*)&keysBegin)->DoInsertKey4(slot, v);
            }
            keys += 3;
            --n;
        } while (n);
    }

    uint32_t* weightsBegin = 0; uint32_t* weightsEnd = 0; uint32_t* weightsCap = 0;
    Property* prop2 = localProps->GetProperty(0x3f3fa44);
    uint32_t wcount = prop2->mnFlags & 0x30 ? prop2->mnCount
                                            : (uint32_t)(prop2->mnType != 0);
    ((SPVector<uint32_t>*)&weightsBegin)->reserve(wcount);
    uint32_t* wsrc = (uint32_t*)prop2->GetValuePtr();
    if (wcount > 0)
    {
        uint32_t n = wcount;
        uint32_t* slot = weightsBegin;
        uint32_t* cap = weightsEnd;
        do
        {
            if (slot < cap)
            {
                uint32_t* nxt = slot + 1;
                weightsBegin = nxt;
                if (slot)
                    *slot = *wsrc;
            }
            else
            {
                ((SPVector<uint32_t>*)&weightsBegin)->DoInsertValueI(slot, *wsrc);
            }
            ++wsrc;
            --n;
        } while (n);
    }

    uint32_t* keysData = keysBegin;
    uint32_t* weightsData = weightsBegin;
    for (uint32_t i = 0; i < count; ++i)
    {
        if (keys[i] == key)
        {
            if (i == 0xffffffffu)
                break;
            uint32_t result = weightsData[i];
            if (weightsBegin && weightsBegin[-1] != 0)
                operator delete(weightsBegin);
            if (keysBegin && keysBegin[-1] != 0)
                operator delete(keysBegin);
            return result;
        }
    }

    if (weightsBegin && weightsBegin[-1] != 0)
        operator delete(weightsBegin);
    if (keysBegin && keysBegin[-1] != 0)
        operator delete(keysBegin);
    return 0;
}

// @ 0x00fed640
uint32_t cSPMissionManager_s00fe_d430::GetMissionWeightForEmpire(void* empire, uint32_t key)
{
    cPropertyList*& props = *(cPropertyList**)&mpProperties;
    cPropertyList* localProps = mpProperties;
    if (localProps == 0)
    {
        cPropertyList* pm = PropertyManager_s00fe_d430();
        localProps = mpProperties;
        if (localProps)
        {
            mpProperties = 0;
            ((RefCounted*)localProps)->Release();
            props = 0;
        }
        pm->GetProperty2(0x1254b050, 0x2ae1a8e, &mpProperties);
        localProps = mpProperties;
    }

    uint32_t* keysBegin = 0; uint32_t* keysEnd = 0; uint32_t* keysCap = 0;
    Property* prop = localProps->GetProperty(0x3f3fa37);
    uint32_t count = prop->mnFlags & 0x30 ? prop->mnCount
                                          : (uint32_t)(prop->mnType != 0);
    ((SPVector<uint32_t>*)&keysBegin)->reserve(count);
    uint32_t* keys = (uint32_t*)prop->GetValuePtr();
    if (count > 0)
    {
        uint32_t n = count;
        uint32_t* slot = keysBegin;
        uint32_t* cap = keysEnd;
        do
        {
            uint32_t v = *keys;
            if (slot < cap)
            {
                uint32_t* nxt = slot + 1;
                keysBegin = nxt;
                if (slot)
                    *slot = v;
            }
            else
            {
                ((SPVector<uint32_t>*)&keysBegin)->DoInsertKey4(slot, v);
            }
            keys += 3;
            --n;
        } while (n);
    }

    uint32_t propID = 0x5760d54;
    uint32_t* ep = (uint32_t*)empire;
    if (ep[0x84 / 4] != GetStarEmpireID(StarManager(), 0))
    {
        if (ep[0x5c / 4] != ep[0x60 / 4])
            propID = 0x5760d66;
        else if (ep[0x70 / 4] != ep[0x74 / 4])
            propID = 0x5760d6d;
    }

    cPropertyList* empireProps = (cPropertyList*)GetEmpirePropList(empire);

    uint32_t* weightsBegin = 0; uint32_t* weightsEnd = 0; uint32_t* weightsCap = 0;
    if (propID != 0 && empireProps != 0)
    {
        Property* prop2 = empireProps->GetProperty(propID);
        uint32_t wcount = prop2->mnFlags & 0x30 ? prop2->mnCount
                                                : (uint32_t)(prop2->mnType != 0);
        ((SPVector<uint32_t>*)&weightsBegin)->reserve(wcount);
        uint32_t* wsrc = (uint32_t*)prop2->GetValuePtr();
        if (wcount > 0)
        {
            uint32_t n = wcount;
            uint32_t* slot = weightsBegin;
            uint32_t* cap = weightsEnd;
            do
            {
                if (slot < cap)
                {
                    uint32_t* nxt = slot + 1;
                    weightsBegin = nxt;
                    if (slot)
                        *slot = *wsrc;
                }
                else
                {
                    ((SPVector<uint32_t>*)&weightsBegin)->DoInsertValueI(slot, *wsrc);
                }
                ++wsrc;
                --n;
            } while (n);
        }

        uint32_t* keysData = keysBegin;
        uint32_t* weightsData = weightsBegin;
        for (uint32_t i = 0; i < count; ++i)
        {
            if (keys[i] == key)
            {
                if (i == 0xffffffffu)
                    break;
                uint32_t result = weightsData[i];
                if (weightsBegin && weightsBegin[-1] != 0)
                    operator delete(weightsBegin);
                if (keysBegin && keysBegin[-1] != 0)
                    operator delete(keysBegin);
                return result;
            }
        }
    }

    if (weightsBegin && weightsBegin[-1] != 0)
        operator delete(weightsBegin);
    if (keysBegin && keysBegin[-1] != 0)
        operator delete(keysBegin);
    return 0;
}

// @ 0x00fed890
void cSPMissionManager_s00fe_d430::AddRecentMissionA(cSPMission_s00fe_d430* mission, bool restart)
{
    if (!mission->GetOwnerEmpire())
        return;
    if (!mission->GetSourcePlanet())
        return;

    if (((cPlanet*)mission->GetSourcePlanet())->mpRecord == (TC_PlanetRec*)GetPlayerHomePlanet())
        return;

    tRecentMission entry;
    entry.mID = mission->GetMissionID();

    Key* key = ((cPlanet*)mission->GetSourcePlanet())->mpRecord->MapToKey();
    entry.mKey.mType = key->mType;
    entry.mKey.mGroup = key->mGroup;
    entry.mKey.mInstance = key->mInstance;

    if (restart)
        entry.mTime.Restart();

    if (mission->GetOwnerEmpire() == GetPlayerEmpire())
        mRecentNPCMissions.Add(&entry);
    else
        mRecentColonyMissions.Add(&entry);

    // trim the NPC list to 10 entries (from the tail)
    while (true)
    {
        RecentNode* node = (RecentNode*)mRecentNPCMissions.mpNext;
        uint32_t n = 0;
        if (node == (RecentNode*)&mRecentNPCMissions)
            break;
        do { node = (RecentNode*)node->mpNext; ++n; } while (node != (RecentNode*)&mRecentNPCMissions);
        if (n <= 10)
            break;
        RecentNode* victim = (RecentNode*)mRecentNPCMissions.mpPrev;
        *(void**)victim->mpPrev = victim->mpNext;
        *(void**)((char*)victim->mpNext + 4) = victim->mpPrev;
        victim->mValue.mTime.~cGonzagoTimer_s00fe_d430();
        operator delete(victim);
    }

    // trim the colony list to 10 entries (from the tail)
    while (true)
    {
        RecentNode* node = (RecentNode*)mRecentColonyMissions.mpNext;
        uint32_t n = 0;
        if (node == (RecentNode*)&mRecentColonyMissions)
            break;
        do { node = (RecentNode*)node->mpNext; ++n; } while (node != (RecentNode*)&mRecentColonyMissions);
        if (n <= 10)
            break;
        RecentNode* victim = (RecentNode*)mRecentColonyMissions.mpPrev;
        *(void**)victim->mpPrev = victim->mpNext;
        *(void**)((char*)victim->mpNext + 4) = victim->mpPrev;
        victim->mValue.mTime.~cGonzagoTimer_s00fe_d430();
        operator delete(victim);
    }
}

// @ 0x00feda00
void RecentListRead(void* stream, ListAnchor* anchor)
{
    anchor->Ctor();
    anchor->mpNext = anchor;
    anchor->mpPrev = anchor;

    uint32_t count = 0;
    cSerialStream* s = (cSerialStream*)stream;
    cSerialStream* strm = (cSerialStream*)s->v20();
    void* reader = strm->v18();
    ReadInt32(reader, &count, 1, 0);

    for (uint32_t i = 0; i < count; ++i)
    {
        tRecentMission value;

        cVarListSerializer_s00fe_d430 ser(&value, &kSerializerStream, 0x1a80d26);
        ser.Serialize(stream);

        RecentNode* node = (RecentNode*)EAAllocate(
            0x40, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        if (node)
        {
            node->mValue = value;
            node->mpNext = anchor;
            node->mpPrev = anchor->mpPrev;
            *(void**)anchor->mpPrev = node;
            anchor->mpPrev = node;
        }
        value.mTime.~cGonzagoTimer_s00fe_d430();
    }

    s->v1c();
}

// @ 0x00fedb50
void cSPMissionManager_s00fe_d430::InitForGame()
{
    ((cSimTicker*)SimTicker())->RegisterMissionManager(this);

    CacheProperties();

    ((cSerializerParser*)MakeRequisiteParser())->SetSerializer();
    ((cMissionRequisitesParser*)MakeRequisiteParser(0x6b5005e))->FillList(&mTutorialMissionReqList);
    ((cMissionRequisitesParser*)MakeRequisiteParser(0x994d1f83))->FillList(&mNPCMissionReqList);
    ((cMissionRequisitesParser*)MakeRequisiteParser(0xa07f6fd6))->FillList(&mColonyMissionReqList);

    SP_CacheLocalizedStrings();

    mbFlightSchoolFinished = true;

    SPVector<uint32_t>& planetKeys = mTutorialTargetPlanetKeys;
    for (int i = 2; i != 0; --i)
    {
        uint32_t* slot = planetKeys.mpEnd;
        if (slot < planetKeys.mpCapacity)
        {
            planetKeys.mpEnd = slot + 1;
            if (slot)
                *slot = 0xffffffffu;
        }
        else
        {
            planetKeys.DoInsertValueI(slot, kMinusOne);
        }
    }
    SPVector<Key>& speciesIDs = mTutorialSpeciesIDs;
    for (int i = 2; i != 0; --i)
    {
        Key* slot = speciesIDs.mpEnd;
        if (slot < speciesIDs.mpCapacity)
        {
            speciesIDs.mpEnd = slot + 1;
            if (slot)
                *slot = kZeroKey;
        }
        else
        {
            speciesIDs.DoInsertKey(slot, kZeroKey);
        }
    }
    SPVector<AutoRefCount>& tracked = mTrackedMissions;
    for (int i = 3; i != 0; --i)
    {
        AutoRefCount zero;
        AutoRefCount* slot = tracked.mpEnd;
        if (slot < tracked.mpCapacity)
        {
            tracked.mpEnd = slot + 1;
            if (slot)
                slot->mpObject = 0;
        }
        else
        {
            tracked.DoInsertPtr(slot, zero);
        }
    }
}

// @ 0x00fedca0
bool cSPMissionManager_s00fe_d430::RemoveMission(cSPMission_s00fe_d430* mission)
{
    if (mission->mpParentMission == 0)
        AddRecentMissionA(mission, true);

    RemoveMissionInternal(mission);

    if (mission->mpParentMission == 0)
    {
        MessageBasicRC5 msg;
        msg.mId = 0x38cf2ff;
        msg.vftable0 = 0x13eb90c;
        _InterlockedExchange((volatile long*)&msg.mRefCount, 0);
        msg.vftable0 = 0x13eb844;
        msg.mRCFlags = 0;
        *(void**)&msg.mData = mission;
        cMessageServer* server = MessageServer();
        server->Send(msg.mId, &msg, 0);
        ((MsgRCDtor*)&msg)->Destroy();
    }

    cGameNounManager_s00fe_d430* nouns = NounManager_s00fe_d430();
    if (nouns)
    {
        nouns->RemoveNoun(mission);
        return true;
    }
    return false;
}

// @ 0x00fedd50
void* cSPMissionManager_s00fe_d430::GetMissionList()
{
    cGameNounManager_s00fe_d430* nouns = NounManager_s00fe_d430();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    return (char*)vec + 4;
}

// @ 0x00fedd80
int cSPMissionManager_s00fe_d430::GetNumNonEventMissions(char includeEventChildren)
{
    int n = 0;
    cGameNounManager_s00fe_d430* nouns = NounManager_s00fe_d430();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    cGameData** it = list.mpBegin;
    cGameData** end = list.mpEnd;
    for (; it != end; ++it)
    {
        cSPMission_s00fe_d430* m = (cSPMission_s00fe_d430*)*it;
        if (!m)
            continue;
        if ((m->mbEventFlag & 1) != 0)
            continue;
        if (m->mpParentMission != 0 && !includeEventChildren)
            continue;
        ++n;
    }
    return n;
}

// @ 0x00feddf0
int cSPMissionManager_s00fe_d430::GetNumEventMissions()
{
    int n = 0;
    cGameNounManager_s00fe_d430* nouns = NounManager_s00fe_d430();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    cGameData** it = list.mpBegin;
    cGameData** end = list.mpEnd;
    for (; it != end; ++it)
    {
        cSPMission_s00fe_d430* m = (cSPMission_s00fe_d430*)*it;
        if (m && (m->mbEventFlag & 1) != 0)
            ++n;
    }
    return n;
}

// @ 0x00fede40
void cSPMissionManager_s00fe_d430::SetTutorialMissionState1(uint32_t id)
{
    MissionStateMap* states = (MissionStateMap*)(char*)&mTutorialMissionStates;
    uint32_t key = id;
    *states->operator[](key) = 1;
}

// @ 0x00fede60
void cSPMissionManager_s00fe_d430::SetTutorialMissionState2(uint32_t id)
{
    MissionStateMap* states = (MissionStateMap*)(char*)&mTutorialMissionStates;
    uint32_t key = id;
    *states->operator[](key) = 2;
}

// @ 0x00fede80
void cSPMissionManager_s00fe_d430::SetTutorialMissionState3(uint32_t id)
{
    MissionStateMap* states = (MissionStateMap*)(char*)&mTutorialMissionStates;
    uint32_t key = id;
    *states->operator[](key) = 3;
}

// @ 0x00fedea0
bool cSPMissionManager_s00fe_d430::DoMissionsPreventHostility(void* a, void* b)
{
    cGameNounManager_s00fe_d430* nouns = NounManager_s00fe_d430();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    int count = (int)(list.mpEnd - list.mpBegin);
    for (int i = 0; i < count; ++i)
    {
        cSPMission_s00fe_d430* m = (cSPMission_s00fe_d430*)list.mpBegin[i];
        if (m->Query140(a, b))
            return true;
    }
    return false;
}

// @ 0x00fedf20
float cSPMissionManager_s00fe_d430::FindListWeightA(uint32_t missionID)
{
    RecentNode* node = (RecentNode*)mRecentColonyMissions.mpNext;
    RecentNode* end = (RecentNode*)&mRecentColonyMissions;
    uint32_t index = 0;
    while (node != end)
    {
        tRecentMission* rec = &node->mValue;
        if (rec && rec->mID == missionID)
            return (float)(int)index * g_fWeightScale + g_fWeightBase;
        node = (RecentNode*)node->mpNext;
        ++index;
    }

    cGameNounManager_s00fe_d430* nouns = NounManager_s00fe_d430();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cSPMission_s00fe_d430* m = (cSPMission_s00fe_d430*)*it;
        if (m->IsActive() && m->GetMissionID() == missionID)
            return g_fWeightBase;
    }
    return 1.0f;
}

// @ 0x00fedfe0
float cSPMissionManager_s00fe_d430::FindListWeightB(uint32_t missionID)
{
    RecentNode* node = (RecentNode*)mRecentNPCMissions.mpNext;
    RecentNode* end = (RecentNode*)&mRecentNPCMissions;
    uint32_t index = 0;
    while (node != end)
    {
        tRecentMission* rec = &node->mValue;
        if (rec && rec->mID == missionID)
            return (float)(int)index * g_fWeightScale + g_fWeightBase;
        node = (RecentNode*)node->mpNext;
        ++index;
    }

    cGameNounManager_s00fe_d430* nouns = NounManager_s00fe_d430();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cSPMission_s00fe_d430* m = (cSPMission_s00fe_d430*)*it;
        if (m->IsActive() && m->GetMissionID() == missionID)
            return g_fWeightBase;
    }
    return 1.0f;
}

// @ 0x00fee0a0
void cSPMissionManager_s00fe_d430::ForEachActiveSetTargetPlanet(void* planet)
{
    cGameNounManager_s00fe_d430* nouns = NounManager_s00fe_d430();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cSPMission_s00fe_d430* m = (cSPMission_s00fe_d430*)*it;
        if (m && m->IsActive())
            m->SetTargetPlanet(planet);
    }
}

// @ 0x00fee110
bool cSPMissionManager_s00fe_d430::AnyActiveMatchA(void* a)
{
    cGameNounManager_s00fe_d430* nouns = NounManager_s00fe_d430();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cSPMission_s00fe_d430* m = (cSPMission_s00fe_d430*)*it;
        if (m && m->IsActive() && m->vff4(a))
            return true;
    }
    return false;
}

// @ 0x00fee190
bool cSPMissionManager_s00fe_d430::AnyActiveMatchB(void* a)
{
    cGameNounManager_s00fe_d430* nouns = NounManager_s00fe_d430();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cSPMission_s00fe_d430* m = (cSPMission_s00fe_d430*)*it;
        if (m && m->IsActive() && (m->mbEventFlag & 1) != 0 && m->vff4(a))
            return true;
    }
    return false;
}

// @ 0x00fee220
cSPMission_s00fe_d430* cSPMissionManager_s00fe_d430::FindMissionByTargetPlanet(void* planetRecord)
{
    cGameNounManager_s00fe_d430* nouns = NounManager_s00fe_d430();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cGameData* obj = *it;
        if (!obj)
            continue;
        cSPMission_s00fe_d430* m = (cSPMission_s00fe_d430*)obj->Cast(0x463329e);
        if (!m)
            continue;
        void* target = m->GetTargetPlanet();
        if (!target)
            continue;
        if (!mbDebugFlag && ((cPlanet*)target)->mpRecord != (TC_PlanetRec*)planetRecord)
            continue;
        return m;
    }
    return 0;
}

// @ 0x00fee2b0
Record38* CopyRecords(Record38* first, Record38* last, Record38* dest)
{
    if (first == last)
        goto done;
    for (; first != last; first += 1, dest += 1)
    {
        dest->mWord0 = first->mWord0;
        dest->mWord1 = first->mWord1;
        dest->mVecA.assign(&first->mVecA);
        dest->mVecB.assign(&first->mVecB);
        dest->mWord30 = first->mWord30;
        dest->mWord34 = first->mWord34;
    }
done:
    return dest;
}

// @ 0x00fee310
void cSPMissionManager_s00fe_d430::PostLoad()
{
    ((cSimTicker*)SimTicker())->RegisterMissionManager(this);

    CacheProperties();

    ((cSerializerParser*)MakeRequisiteParser())->SetSerializer();
    ((cMissionRequisitesParser*)MakeRequisiteParser(0x6b5005e))->FillList(&mTutorialMissionReqList);
    ((cMissionRequisitesParser*)MakeRequisiteParser(0x994d1f83))->FillList(&mNPCMissionReqList);
    ((cMissionRequisitesParser*)MakeRequisiteParser(0xa07f6fd6))->FillList(&mColonyMissionReqList);

    SP_CacheLocalizedStrings();

    cGameNounManager_s00fe_d430* nouns = NounManager_s00fe_d430();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cGameData* obj = *it;
        if (obj)
            obj->g80();
    }
}

// @ 0x00fee3d0
char cSPMissionManager_s00fe_e3d0::FUN_00fee3d0(void* empire, void* planet)
{
    cEmpire* player = (cEmpire*)FUN_01021300();
    void* home = player->GetHomePlanet();
    unsigned count = GetNumNonEventMissions(0);
    if (empire == player) {
        if (planet == home) {
            return 1;
        }
        if (count < mMaxMissions && FUN_00fec900(planet)) {
            return 1;
        }
    } else if (count < mMaxMissions && FUN_00fec8a0(planet)) {
        unsigned playerID = ((cEmpire*)FUN_01021300())->mEmpireID;
        unsigned empireID = ((cEmpire*)empire)->mEmpireID;
        RelMgr* rel = (RelMgr*)RelationshipManager();
        float damage = rel->calc(empireID, playerID, 0);
        float tuning = ((RelTuning*)GetSpaceRelationshipTuning())->get();
        if (tuning > damage) {
            return 0;
        }
        return 1;
    }
    return 0;
}

// @ 0x00fee480
cSPMission_s00fe_e3d0* cSPMissionManager_s00fe_e3d0::GetMissionByID(int id)
{
    cGameNounManager_s00fe_e3d0* nm = (cGameNounManager_s00fe_e3d0*)NounManager();
    MissionList* list = nm->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00fed010, 0x00b1e520, 0x2aa5ada);
    SpVecPV& v = list->mItems;
    void** p = v.mpBegin;
    void** end = v.mpEnd;
    for (; p != end; ++p) {
        cSPMission_s00fe_e3d0* m = (cSPMission_s00fe_e3d0*)*p;
        if (m != 0 && m->GetMissionID() == (unsigned)id) {
            return m;
        }
        }
    return 0;
}

// @ 0x00fee4f0
cSPMission_s00fe_e3d0* cSPMissionManager_s00fe_e3d0::GetActiveMissionForEmpireAndPlanet(void* empire, void* planet)
{
    cGameNounManager_s00fe_e3d0* nm = (cGameNounManager_s00fe_e3d0*)NounManager();
    MissionList* list = nm->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00fed010, 0x00b1e520, 0x2aa5ada);
    SpVecPV& v = list->mItems;
    void** p = v.mpBegin;
    void** end = v.mpEnd;
    for (; p != end; ++p) {
        cSPMission_s00fe_e3d0* m = (cSPMission_s00fe_e3d0*)*p;
        if (m != 0 && m->GetOwnerEmpire() == empire
            && (planet == 0 || m->GetModel()->mPlanet == planet)) {
            switch (((int (__thiscall*)(void*))((*(void***)m))[0x60 / 4])(m)) {
            case 3:
            case 5:
                return m;
            }
        }
        }
    return 0;
}

// @ 0x00fee590
char cSPMissionManager_s00fe_e3d0::IsPlanetARaidTarget(void* planet, unsigned* out)
{
    cGameNounManager_s00fe_e3d0* nm = (cGameNounManager_s00fe_e3d0*)NounManager();
    MissionList* list = nm->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00fed010, 0x00b1e520, 0x2aa5ada);
    SpVecPV& v = list->mItems;
    void** p = v.mpBegin;
    void** end = v.mpEnd;
    for (; p != end; ++p) {
        cSPMission_s00fe_e3d0* m = (cSPMission_s00fe_e3d0*)*p;
        if (m != 0
            && m->GetTargetPlanet() != 0
            && ((cModel*)m->GetTargetPlanet())->mPlanet == planet
            && ((int (__thiscall*)(void*))((*(void***)m))[0x60 / 4])(m) == 3
            && (m->GetMissionID() == 0xa4b0a2df
                || m->GetMissionID() == 0xbbae6b99
                || m->GetMissionID() == 0xc4956aa7
                || m->GetMissionID() == 0xd646c543
                || m->GetMissionID() == 0x25089345
                || m->GetMissionID() == 0x56afe39d)) {
            if (m->GetOwnerEmpire() != 0) {
                *out = ((cEmpire*)m->GetOwnerEmpire())->mEmpireID;
                return 1;
            }
            *out = 0xffffffff;
            return 1;
        }
        }
    return 0;
}

// @ 0x00fee6b0
int cSPMissionManager_s00fe_e3d0::HasMissionConversationWithEmpireAndPlanet(void* empire, void* planet)
{
    cGameNounManager_s00fe_e3d0* nm = (cGameNounManager_s00fe_e3d0*)NounManager();
    MissionList* list = nm->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00fed010, 0x00b1e520, 0x2aa5ada);
    SpVecPV& v = list->mItems;
    void** p = v.mpBegin;
    void** end = v.mpEnd;
    for (; p != end; ++p) {
        cSPMission_s00fe_e3d0* m = (cSPMission_s00fe_e3d0*)*p;
        if (m != 0 && ((char (__thiscall*)(void*, void*, void*))((*(void***)m))[0x134 / 4])(m, empire, planet)) {
            return 1;
        }
        }
    return 0;
}

// @ 0x00fee730
char cSPMissionManager_s00fe_e3d0::FUN_00fee730(void* empire, void* planet)
{
    if (GetActiveMissionForEmpireAndPlanet(empire, planet) != 0) {
        return 0;
    }
    cEmpire* player = (cEmpire*)FUN_01021300();
    if (!player->FUN_00c31bc0((cEmpire*)empire)) {
        return 0;
    }
    if (((cEmpire*)empire)->GetWeaponryLevel() < mWeaponryThreshold - 1) {
        return 0;
    }
    int theirs = ((cEmpire*)empire)->mArchetype;
    switch (player->mArchetype) {
    case 9:
        if (theirs == 0 || theirs == 9 || theirs == 0x12) return 0;
        break;
    case 10:
        if (theirs == 1 || theirs == 0x0a) return 0;
        break;
    case 11:
        if (theirs == 2 || theirs == 0x0b) return 0;
        break;
    case 12:
        if (theirs == 3 || theirs == 0x0c) return 0;
        break;
    case 13:
        if (theirs == 4 || theirs == 0x0d) return 0;
        break;
    case 14:
        if (theirs == 5 || theirs == 0x0e) return 0;
        break;
    case 15:
        if (theirs == 6 || theirs == 0x0f || theirs == 0x11) return 0;
        break;
    case 16:
        if (theirs == 7 || theirs == 0x10) return 0;
        break;
    }
    return 1;
}

// @ 0x00fee820
char cSPMissionManager_s00fe_e3d0::FUN_00fee820()
{
    cGameNounManager_s00fe_e3d0* nm = (cGameNounManager_s00fe_e3d0*)NounManager();
    MissionList* list = nm->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00fed010, 0x00b1e520, 0x2aa5ada);
    SpVecPV& v = list->mItems;
    void** p = v.mpBegin;
    void** end = v.mpEnd;
    for (; p != end; ++p) {
        cSPMission_s00fe_e3d0* m = (cSPMission_s00fe_e3d0*)*p;
        unsigned id = m->GetMissionID();
        if (m != 0 && m->IsActive()
            && (id == 0x29e235c0
                || id == 0x34ca76bf
                || id == 0x0b9656f6
                || id == 0x4b708009
                || id == 0xc052cccf
                || id == 0x2b795e0d
                || id == 0x5d182075
                || id == 0xf46a1fc4)) {
            return 1;
        }
        }
    return 0;
}

// @ 0x00fee8d0
void cSPMissionManager_s00fe_e3d0::DebugDraw()
{
    if (!mDebugDraw) {
        return;
    }
    cGameNounManager_s00fe_e3d0* nm = (cGameNounManager_s00fe_e3d0*)NounManager();
    MissionList* list = nm->GetGameDataVector(
        0x00cd7d10, 0x00d3d420, 0x00fed010, 0x00b1e520, 0x2aa5ada);
    SpVecPV& v = list->mItems;
    void** p = v.mpBegin;
    void** end = v.mpEnd;
    for (; p != end; ++p) {
        cSPMission_s00fe_e3d0* m = (cSPMission_s00fe_e3d0*)*p;
        if (m != 0) {
            ((void (__thiscall*)(void*))((*(void***)m))[0x114 / 4])(m);
        }
        }
}

// @ 0x00fee930
char cSPMissionManager_s00fe_e3d0::FUN_00fee930(int id)
{
    MapNode* slot;
    MapNode* node = *mStates.find(&slot, (const unsigned*)&id);
    if (node != &mStates.mAnchor) {
        if (node->mValue == 2 || node->mValue == 3) {
            return 1;
        }
    }
    char ok;
    switch (id) {
    case -0x1c0a6b1f: {                       // 0xe3f594e1
        cSPMission_s00fe_e3d0* m = GetMissionByID(id);
        if (m != 0 && m->IsActive()) {
            return 0;
        }
        TerrainSphere* ts = (TerrainSphere*)((cGameNounManager_s00fe_e3d0*)NounManager())->GetCurrentTerrainSphere();
        ok = ts->FUN_00c772c0(0x4ac8010);
        break;
    }
    case -0x6951388c: {                       // 0x96aec774
        cSPMission_s00fe_e3d0* m = GetMissionByID(id);
        if (m != 0 && m->IsActive()) {
            return 0;
        }
        ok = ((cGameData_s00fe_e3d0*)SpaceGameGet())->SetGameDataOwner2()->FUN_00fe4180(0x3ae13c90);
        break;
    }
    case -0x69513889: {                       // 0x96aec777
        cSPMission_s00fe_e3d0* m = GetMissionByID(id);
        if (m != 0 && m->IsActive()) {
            return 0;
        }
        ok = ((cGameData_s00fe_e3d0*)SpaceGameGet())->SetGameDataOwner2()->FUN_00fe4180(0x3ae13c93);
        break;
    }
    case 0x62613a1d: {
        cSPMission_s00fe_e3d0* m = GetMissionByID(id);
        if (m != 0 && m->IsActive()) {
            return 0;
        }
        ok = ((cGameData_s00fe_e3d0*)SpaceGameGet())->SetGameDataOwner2()->FUN_00fe4180(0x372e73ee);
        break;
    }
    default:
        return 0;
    }
    if (ok) {
        return 1;
    }
    return 0;
}

// @ 0x00feea60
unsigned cSPMissionManager_s00fe_e3d0::GetNextAvailableTutorialMission()
{
    unsigned flag = 0;
    char* ts = ((cGameNounManager_s00fe_e3d0*)NounManager())->GetCurrentTerrainSphere();
    if (ts != 0 && ((TerrainSphere*)ts)->FUN_00c772c0(0x4ac8010)) {
        flag = 1;
    }
    Req38* begin = mTutBegin;
    int count = (int)(mTutEnd - begin);
    if (count <= 0) {
        return 0xffffffff;
    }
    int offset = 0;
    for (int i = 0; i < count; i++, offset += 0x38) {
        Req38* req = (Req38*)((char*)begin + offset);
        unsigned key = req->mMissionID;
        MapNode* node = mStates.findNode(key);
        if (node != &mStates.mAnchor && node->mValue == 1) {
            continue;
        }
        if (FUN_00fee930((int)key)) {
            continue;
        }
        int n = (int)(req->mpVecEnd - req->mpVec);
        bool allIn = true;
        for (int j = 0; j < n; j++) {
            if (!((cGameData_s00fe_e3d0*)SpaceGameGet())->SetGameDataOwner2()->FUN_00fe4180(req->mpVec[j])) {
                allIn = false;
                break;
            }
        }
        if (req->mFlags30 == (req->mFlags30 & flag) && (req->mFlags34 & flag) == 0) {
            if (!allIn) {
                return 0xffffffff;
            }
            return req->mMissionID;
        }
    }
    return 0xffffffff;
}

// @ 0x00feebb0
char cSPMissionManager_s00fe_e3d0::FUN_00feebb0()
{
    int count = (int)(mVec134 - mVec130);
    for (int i = 0; i < count; i++) {
        unsigned key = mVec130[i];
        MapNode* node = mStates.findNode(key);
        if (node != &mStates.mAnchor && node->mValue == 1) {
            continue;
        }
        if (!FUN_00fee930((int)key)) {
            return 1;
        }
    }
    return 0;
}

// @ 0x00feec30
char cSPMissionManager_s00fe_e3d0::FUN_00feec30()
{
    int count = (int)(mVec120 - mVec11c);
    for (int i = 0; i < count; i++) {
        unsigned key = mVec11c[i];
        MapNode* node = mStates.findNode(key);
        if (node != &mStates.mAnchor && node->mValue == 1) {
            continue;
        }
        if (!FUN_00fee930((int)key)) {
            return 1;
        }
    }
    return 0;
}

// @ 0x00feecb0
char cSPMissionManager_s00fe_e3d0::FUN_00feecb0()
{
    int count = (int)(mVec10c - mVec108);
    for (int i = 0; i < count; i++) {
        unsigned key = mVec108[i];
        MapNode* node = mStates.findNode(key);
        if (node != &mStates.mAnchor && node->mValue == 1) {
            continue;
        }
        if (!FUN_00fee930((int)key)) {
            return 1;
        }
    }
    return 0;
}

// @ 0x00feed30
unsigned cSPMissionManager_s00fe_e3d0::FUN_00feed30(void* empire, void* planet)
{
    if (!FUN_00fee3d0(empire, planet)) {
        return 0;
    }
    cEmpire* player = (cEmpire*)FUN_01021300();
    void* home = player->GetHomePlanet();
    unsigned result = 0;
    SpVectorF weights;

    if (empire == player) {
        if (planet == home) {
            unsigned id = GetNextAvailableTutorialMission();
            if (mForcedMission != 0) {
                id = (unsigned)mForcedMission;
            }
            result = (unsigned)CreateMissionFromID(id, planet, empire, 0);
            mForcedMission = 0;
            return result;
        }
        int count = (int)(mColEnd - mColBegin);
        weights.mpBegin = 0;
        weights.mpEnd = 0;
        weights.mpCap = 0;
        weights.resize(count);
        for (int i = 0; i < count; i++) {
            Req38* req = &mColBegin[i];
            float value = 0.0f;
            if (FUN_00febd30(i)) {
                int w = GetMissionWeightForColony(req->mMissionID);
                float wf = (float)w;
                value = FUN_00fedfe0(req->mMissionID) * wf;
            }
            weights.mpBegin[i] = value;
        }
        bool done = false;
        do {
            int idx = FUN_00fec010(&weights);
            if (idx < 0 || idx >= count) {
                break;
            }
            unsigned id = mColBegin[idx].mMissionID;
            if (mForcedMission != 0) {
                id = (unsigned)mForcedMission;
            }
            result = (unsigned)CreateMissionFromID(id, planet, empire, 0);
            if (result == 0) {
                for (int i = 0; i < count; i++) {
                    if (mColBegin[i].mMissionID == id) {
                        weights.mpBegin[i] = 0.0f;
                    }
                }
            } else {
                done = true;
            }
            mForcedMission = 0;
        } while (!done);
    } else {
        if (FUN_00fecbf0()) {
            unsigned key = 0x2ab57fac;
            MapNode* slot;
            MapNode* node = *mStates.find(&slot, &key);
            if (node == &mStates.mAnchor || (node->mValue != 2 && node->mValue != 3)) {
                result = (unsigned)CreateMissionFromID(0x2ab57fac, planet, empire, 0);
                if (result != 0) {
                    goto cleanup;
                }
            }
            char* ts = ((cGameNounManager_s00fe_e3d0*)NounManager())->GetCurrentTerrainSphere();
            void* out = 0;
            if (((TerrainSphere*)ts)->FUN_00c75d70(empire, &out)) {
                result = (unsigned)CreateMissionFromID((unsigned)out, planet, empire, 0);
                if (result != 0) {
                    goto cleanup;
                }
            }
        }
        int count = (int)(mNpcEnd - mNpcBegin);
        weights.mpBegin = 0;
        weights.mpEnd = 0;
        weights.mpCap = 0;
        weights.resize(count);
        for (int i = 0; i < count; i++) {
            Req38* req = &mNpcBegin[i];
            float value = 0.0f;
            if (IsNPCMissionAvailable(empire, i)) {
                int w = GetMissionWeightForEmpire(req->mMissionID, empire);
                float wf = (float)w;
                value = FUN_00fedf20(req->mMissionID) * wf;
            }
            weights.mpBegin[i] = value;
        }
        bool done = false;
        do {
            int idx = FUN_00fec010(&weights);
            if (idx < 0 || idx >= count) {
                break;
            }
            unsigned id = mNpcBegin[idx].mMissionID;
            if (mForcedMission != 0) {
                id = (unsigned)mForcedMission;
            }
            if (id == 0x9bd15777) {
                if (FUN_00fecbf0()) {
                    void* asset = 0;
                    StarMgr* star = (StarMgr*)FUN_00b3d2a0();
                    star->PickRandomAsset(&asset, 1);
                    if (asset != 0) {
                        result = (unsigned)CreateMissionFromID(0x831e4599, planet, empire, 0);
                        if (result != 0) {
                            ((cMissionHelper*)result)->FUN_00c4b240(asset);
                        }
                    }
                }
            } else {
                result = (unsigned)CreateMissionFromID(id, planet, empire, 0);
            }
            if (result != 0) {
                done = true;
            } else {
                for (int i = 0; i < count; i++) {
                    if (mNpcBegin[i].mMissionID == id) {
                        weights.mpBegin[i] = 0.0f;
                    }
                }
            }
            mForcedMission = 0;
        } while (!done);
    }
cleanup:
    if (weights.mpBegin != 0 && ((unsigned*)weights.mpBegin)[-1] != 0) {
        operator_delete_array(weights.mpBegin);
    }
    return result;
}

// @ 0x00fef3b0
void cSPMissionManager_s00fe_f140::OnTick(void* param2)
{
    cGameNounManager_s00fe_f140* nm = (cGameNounManager_s00fe_f140*)FUN_00b3d300();
    cMissionVec* v = (cMissionVec*)nm->GetGameDataVector(
        FUN_00cd7d10, FUN_00d3d420, FUN_00fed010, FUN_00b1e520, 0x2aa5ada);
    cSPMission_s00fe_f140** hi = v->mpEnd;
    for (cSPMission_s00fe_f140** it = v->mpBegin; it != hi; ++it) {
        cSPMission_s00fe_f140* m = *it;
        if (m == 0)
            continue;
        if (m->FUN_2c())
            continue;
        if (m->FUN_60() == 10)
            continue;
        int prev = m->FUN_60();
        do {
            switch (m->FUN_60()) {
            case 1:
                FUN_00fedca0(m);
                break;
            case 2:
                m->FUN_88();
                m->SetState(3);
                break;
            case 3: {
                int r = m->FUN_7c(param2);
                if (r != 3)
                    m->SetState(r);
            } break;
            case 4:
                break;
            case 5:
                m->FUN_94();
                if (m->mField_17c != 0)
                    m->SetState(9);
                else
                    m->SetState(1);
                break;
            case 6:
                m->FUN_98();
                m->SetState(1);
                break;
            case 7:
                m->FUN_90();
                m->SetState(1);
                break;
            case 8:
                m->FUN_8c();
                m->SetState(1);
                break;
            }
        } while (prev != m->FUN_60());
    }
    CleanupArchive(param2);
    FUN_00fec4e0();
    FUN_00fec430(param2);
}

// @ 0x00fef570
void* spVecF::FUN_00fef570(void* a, void* b)
{
    void* mid = FUN_00fee2b0(b, mpEnd, a);
    FUN_00fecc40(mid, mpEnd);
    int count = (int)((char*)b - (char*)a) / -0x38;
    mpEnd = (float*)((char*)mpEnd + count * 0x38);
    return a;
}

// @ 0x00fef5d0
void cSPMissionManager_s00fe_f140::ShutdownForGame()
{
    cSimTicker_s00fe_f140* t = (cSimTicker_s00fe_f140*)FUN_00b3d330();
    t->FUN_54(this);
    ((cSerializerUser*)FUN_00fef670())->SetSerializer();
    FUN_00fef6b0();
    mReq_20.FUN_00fef570(mReq_20.mpBegin, mReq_20.mpEnd);
    mReq_34.FUN_00fef570(mReq_34.mpBegin, mReq_34.mpEnd);
    mReq_48.FUN_00fef570(mReq_48.mpBegin, mReq_48.mpEnd);
    ((cGameNounManager_s00fe_f140*)FUN_00b3d300())->RemoveNounsWithInterface(0x2aa5ada);
    if (mpField_c0 != 0) {
        void* p = mpField_c0;
        mpField_c0 = 0;
        ((IRefCount*)p)->Release();
    }
    if (mpField_c4 != 0) {
        void* p = mpField_c4;
        mpField_c4 = 0;
        ((IRefCount*)p)->Release();
    }
}

// @ 0x00fef670
void* FUN_00fef670()
{
    if (g_16dacb8 == 0) {
        void* p = operator_new(4, "Simulator", 0, 0, 0, 0);
        if (p != 0) {
            *(u32*)p = 0x13fb19c;                        // vtbl_UTFInternet::HTTPRequest
            g_16dacb8 = (IHTTPRequest*)p;
            return p;
        }
        g_16dacb8 = 0;
    }
    return g_16dacb8;
}

// @ 0x00fef6b0
void FUN_00fef6b0()
{
    if (g_16dacb8 != 0)
        g_16dacb8->FUN_00(1);
    g_16dacb8 = 0;
}

// @ 0x01396a80
namespace Simulator {
void InitE229()
{
    ADD3(0, "mbFirstCommunication",       0x361c377, 0x16, IRead<M0>, IWrite<M0>, IReadText<M0>, IWriteText<M0>, AV_bool, TX_bool)
    ADD3(1, "mbFlightSchoolFinished",     0x56cfe7c, 0x17, IRead<M1>, IWrite<M1>, IReadText<M1>, IWriteText<M1>, AV_bool, TX_bool)
    ADD3(2, "mbMission201Finished",       0x6410400, 0x18, IRead<M2>, IWrite<M2>, IReadText<M2>, IWriteText<M2>, AV_bool, TX_bool)
    ADD3(3, "mTutorialTargetPlanetKeys",  0x361c389, 0x80, IRead<M3>, IWrite<M3>, NoopRT, NoopWT, IValid<M3>, IToXml<M3>)
    ADD3(4, "mTutorialSpeciesIDs",        0x361d38d, 0x94, IRead<M4>, IWrite<M4>, NoopRT, NoopWT, IValid<M4>, IToXml<M4>)
    ADD3(5, "mRecentNPCMissions",         0x1361c38a, 0xc8, IRead<M5>, IWrite<M5>, NoopRT, NoopWT, IValid<M5>, IToXml<M5>)
    ADD3(6, "mRecentColonyMissions",      0x1361c38b, 0xd4, IRead<M6>, IWrite<M6>, NoopRT, NoopWT, IValid<M6>, IToXml<M6>)
    ADD3(7, "mTrackedMissions",           0x361c38c, 0xa8, IRead<M7>, IWrite<M7>, NoopRT, NoopWT, IValid<M7>, IToXml<M7>)
    ADD3(8, "mTutorialMissionStates",     0x361c38d, 0x5c, IRead<M8>, IWrite<M8>, NoopRT, NoopWT, IValid<M8>, IToXml<M8>)
}
}  // namespace Simulator
