// Slice s00fec590: SP::cSPMissionManager - the mission factory, mission-UI
// registration/visibility helpers, the feedback-event lookups, the timer
// lists, the value/record helpers, the constructor/destructor and
// CacheProperties.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// image data referenced by this slice
// ---------------------------------------------------------------------------------------------
extern float g_k1000;                 // 0x013ec5b4 1000.0f
extern void* g_vtbl_013eb384;         // 0x013eb384 ??_7cListenerBase@@6B@
extern void* g_vtbl_01494964;         // 0x01494964 cSPMissionManager vtable (+0x00)
extern void* g_vtbl_01494940;         // 0x01494940 cSPMissionManager vtable (+0x08)
extern void* g_vtbl_01494930;         // 0x01494930 cSPMissionManager vtable (+0x10)
extern void* g_vtbl_013eb394;         // 0x013eb394 ??_7PaintSystem@@6B@
extern void* g_vtbl_013eb938;         // 0x013eb938 ??_7ITracerBase@Trace@EA@@6B@
extern void* g_vtbl_013ec458;         // 0x013ec458 ??_7ContentValidationSummarizer@@6B@
extern void* g_vtbl_01465d54;         // 0x01465d54 cGonzagoTimer vtable (+0x00)
extern void* g_vtbl_01464450;         // 0x01464450 cGonzagoTimer vtable (set later in the copy)
extern uint32_t g_missionMgrInstance; // 0x016dac64 _sInstance_cSPMissionManager_SP__2PAV12_A
extern uint32_t g_cachedUintArray[];  // 0x016dac54 mission-manager scratch uint array
extern char g_szSimulator[];          // 0x013f09b4 "Simulator"
extern char g_szAllocatorH[];         // 0x013ebb38 "...EASTL/allocator.h"

// ---------------------------------------------------------------------------------------------
// engines / free helpers
// ---------------------------------------------------------------------------------------------
void*  __cdecl NounManager();                                   // 0x00b3d300
void*  __cdecl PropertyManager();                               // 0x0067de30
bool   __cdecl GetPropertyAsKey(void* pProp, uint32_t nKey, void* pOut);   // 0x006a1250
bool   __cdecl GetPropertyAsUint32Array(void* pProp, uint32_t nKey, int32_t* pnCount, uint32_t** ppArray);  // 0x006a0840
bool   __cdecl GetPropertyAsKeyArray(void* pProp, uint32_t nKey, int32_t* pnCount, void** ppArray);         // 0x006a0ae0
bool   __cdecl WriteUint32(void* pStream, const uint32_t* pValue, uint32_t nCount, int32_t nFlag);          // 0x0093aa70
bool   __cdecl IsWorldLayoutFlagSet(uint32_t nFlag);            // 0x00685520
void   __cdecl operator_delete_array(void* pBlock);             // 0x00f47380
void*  __cdecl operator_new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                            const char* pFile, int32_t nLine);  // 0x00f473a0
uint32_t* __fastcall FUN_00b8d8e0(void* pArg);                  // 0x00b8d8e0

// ---------------------------------------------------------------------------------------------
// shared base types
// ---------------------------------------------------------------------------------------------
class cRefObj {
public:
    virtual void AddRef();                  // +0x00
    virtual void Release();                 // +0x04
};

// the property key: type/instance/group triple
struct tKey {
    uint32_t mType;             // +0x00
    uint32_t mInstance;         // +0x04
    uint32_t mGroup;            // +0x08
};

// a property value read out of the property manager
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

// ---------------------------------------------------------------------------------------------
// timers / timer lists
// ---------------------------------------------------------------------------------------------
class cGonzagoSimulator {
public:
    void ConstructSelf();                   // 0x00b5b6c0
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

// the value stored in a timer list node (0x34 bytes); +0x04 is never copied
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

// ---------------------------------------------------------------------------------------------
// record vectors / maps / uint vectors
// ---------------------------------------------------------------------------------------------
struct tRec38 {
    uint8_t   mPad00[8];        // +0x00
    void*     mpArr08;          // +0x08
    uint8_t   mPad0c[0x10];     // +0x0c
    void*     mpArr1c;          // +0x1c
    uint8_t   mPad20[0x18];     // +0x20
};

// the {begin,end,cap} record-vector triple; its member walks a record range
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

struct tMapNode {
    void*    mp00;              // +0x00
    void*    mp04;              // +0x04
    void*    mp08;              // +0x08
    uint32_t mn0c;              // +0x0c
    uint32_t mn10;              // +0x10
    uint32_t mn14;              // +0x14
};

// an eastl rbtree iterator: returned through a hidden return pointer
struct cMapIter {
    void* mpNode;               // +0x00
    cMapIter(const cMapIter& rOther);
};

// the eastl::rbtree<unsigned, pair<unsigned const, AutoRefCount<cFeedbackEvent>>> at +0x5c
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

// eastl::vector<AutoRefCount<cSPMission>> - the three mission slots at +0xa8
struct tMissionSlotVec {
    cSPMission** mpBegin;       // +0x00
    cSPMission** mpEnd;         // +0x04
    cSPMission** mpCap;         // +0x08
    uint32_t     mAlloc;        // +0x0c
    void Destroy();             // 0x00ae6970
};

// ---------------------------------------------------------------------------------------------
// serialisation helpers (used by the mission-list serialiser at 0x00feca80)
// ---------------------------------------------------------------------------------------------
class cOutStream {
public:
    virtual void* v00();            // +0x00
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();            // +0x18 write handle
    virtual void  v1c();            // +0x1c
    virtual cOutStream* v20();      // +0x20
};

class cVarListSerializer {
public:
    void* Construct(const void* pSrc, uint32_t nA, uint32_t nB);   // 0x00692f90
    bool  Serialize(cOutStream* pOut);                             // 0x00692900
    uint8_t mPad[0xa00];
};

struct tSerializeNode {
    tSerializeNode* mpNext;         // +0x00
    tSerializeNode* mpPrev;         // +0x04
    uint8_t         mPayload[0x40]; // +0x08
};

// ---------------------------------------------------------------------------------------------
// the noun manager the factory creates missions in
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// the mission manager itself
// ---------------------------------------------------------------------------------------------
class cSPMissionManager {
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
    cSPMissionManager* FUN_00fecc90();                                  // 0x00fecc90
    void FUN_00fece20();                                                // 0x00fece20
    void CacheProperties();                                             // 0x00fed0b0
    void FUN_00febeb0(cSPMission* pMission);                            // 0x00febeb0
};

// =============================================================================================
// the record cleanup shared by the destructor
// =============================================================================================
// @ 0x00fecc40 tRecVec::FUN_00fecc40
void tRecVec::FUN_00fecc40(tRec38* pBegin, tRec38* pEnd)
{
    while (pBegin < pEnd) {
        tRec38* p = pBegin;
        if (p->mpArr1c != 0 && *((int32_t*)p->mpArr1c - 1) != 0)
            operator_delete_array(p->mpArr1c);
        if (p->mpArr08 != 0 && *((int32_t*)p->mpArr08 - 1) != 0)
            operator_delete_array(p->mpArr08);
        ++pBegin;
    }
}

// =============================================================================================
// 0x00fec590 - build a mission from its property id and install it
// =============================================================================================
// @ 0x00fec590 SP::cSPMissionManager::CreateMissionFromID
cSPMission* cSPMissionManager::CreateMissionFromID(uint32_t nMissionID, uint32_t nArg2,
                                                   uint32_t nArg3, uint32_t nArg4)
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

// =============================================================================================
// 0x00fec8a0 / 0x00fec900 - is a live timer for this key already queued?
// =============================================================================================
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

// @ 0x00fec8a0 FUN_00fec8a0
bool cSPMissionManager::FUN_00fec8a0(void* pArg)
{
    return HasTimerForKey(&mListC8, pArg);
}

// @ 0x00fec900 FUN_00fec900
bool cSPMissionManager::FUN_00fec900(void* pArg)
{
    return HasTimerForKey(&mListD4, pArg);
}

// =============================================================================================
// 0x00fec960 - put a mission into the (three) UI mission slots
// =============================================================================================
// @ 0x00fec960 FUN_00fec960
bool cSPMissionManager::FUN_00fec960(cSPMission* pMission)
{
    cSPMission** pSlots = mSlotVec.mpBegin;
    uint32_t i = 0;

    for (;;) {
        if (pSlots[i] == pMission)
            return true;
        if (pSlots[i] == 0)
            break;
        ++i;
        if (i >= 3)
            return false;
    }

    cSPMission* pOld = pSlots[i];
    if (pMission != pOld) {
        if (pMission != 0)
            pMission->AddRef();
        pSlots[i] = pMission;
        if (pOld != 0)
            pOld->Release();
    }
    pMission->FUN_00c47b10(1);

    cSPMission* pCur = mpC0;
    if (pMission == pCur && pCur != 0) {
        if (pCur != 0) {
            mpC0 = 0;
            pCur->Release();
            pCur->TriggerUIUpdate();
        }
        if (mpC0 != 0)
            mpC0->TriggerUIUpdate();
        mnBC = 0;
    }
    return true;
}

// =============================================================================================
// 0x00feca20 - offer a newly accepted mission to the UI
// =============================================================================================
// @ 0x00feca20 FUN_00feca20
void cSPMissionManager::FUN_00feca20(cSPMission* pMission)
{
    if (pMission->mn17c == 0) {
        if (pMission->IsVisibleInUI()) {
            if (!this->FUN_00fec960(pMission))
                this->FUN_00febeb0(pMission);
        }
    }
}

// =============================================================================================
// 0x00feca80 - serialise a circular list of variable-list records
// =============================================================================================
// @ 0x00feca80 FUN_00feca80
void __cdecl FUN_00feca80(cOutStream* pOut, tSerializeNode* pList)
{
    int32_t nCount = 0;
    for (tSerializeNode* p = pList->mpNext; p != pList; p = p->mpNext)
        ++nCount;

    cOutStream* pStream = pOut->v20();
    void* pHandle = pStream->v18();
    WriteUint32(pHandle, (uint32_t*)&nCount, 1, 0);

    for (tSerializeNode* p = pList->mpNext; p != pList; p = p->mpNext) {
        cVarListSerializer ser;
        ser.Construct(&p->mPayload, 0x15b49b0, 0x1a80d26);
        ser.Serialize(pOut);
    }
    pOut->v1c();
}

// =============================================================================================
// 0x00fecb20 - destroy every node of a timer list
// =============================================================================================
// @ 0x00fecb20 FUN_00fecb20
void cTimerList::DestroyAll()
{
    for (tTimerNode* p = mpNext; p != (tTimerNode*)this; ) {
        tTimerNode* pNext = p->mpNext;
        p->mValue.mTimer.Destroy();
        operator_delete_array(p);
        p = pNext;
    }
}

// =============================================================================================
// 0x00fecb50 - copy a timer value (the +0x04 word is deliberately skipped)
// =============================================================================================
// @ 0x00fecb50 FUN_00fecb50
tTimerValue* tTimerValue::CopyFrom(const tTimerValue* pSrc)
{
    m00 = pSrc->m00;
    mTimer.mpVtbl00 = (void*)&g_vtbl_01465d54;
    mTimer.m04 = 0;
    mTimer.m08 = pSrc->mTimer.m08;
    mTimer.m0c = pSrc->mTimer.m0c;
    mTimer.m10 = pSrc->mTimer.m10;
    mTimer.m14 = pSrc->mTimer.m14;
    mTimer.m18 = pSrc->mTimer.m18;
    mTimer.m1c = pSrc->mTimer.m1c;
    mTimer.mpVtbl00 = (void*)&g_vtbl_01464450;
    mTimer.m20 = pSrc->mTimer.m20;
    mTimer.m24 = pSrc->mTimer.m24;
    mTimer.m28 = pSrc->mTimer.m28;
    return this;
}

// =============================================================================================
// 0x00fecbb0 - erase the feedback-event entry for a key, if present
// =============================================================================================
// @ 0x00fecbb0 FUN_00fecbb0
void cSPMissionManager::FUN_00fecbb0(uint32_t nKey)
{
    uint32_t key = nKey;
    cMapIter it = mFeedbackMap.Find(key);
    if (it.mpNode != (void*)&mFeedbackMap.mpEndNode)
        mFeedbackMap.Erase(key);
}

// =============================================================================================
// 0x00fecbf0 - is the current feedback-event not yet consumed?
// =============================================================================================
// @ 0x00fecbf0 FUN_00fecbf0
uint32_t cSPMissionManager::FUN_00fecbf0()
{
    if (IsWorldLayoutFlagSet(2)) {
        uint32_t nKey = 0x2ab57fac;
        cMapIter it = mFeedbackMap.Find(nKey);
        if (it.mpNode == (void*)&mFeedbackMap.mpEndNode)
            return 1;
        if (((tMapNode*)it.mpNode)->mn14 == 1)
            return 0;
        return 1;
    }
    return 0;
}

// =============================================================================================
// 0x00fecc90 - constructor (returns this in eax)
// =============================================================================================
// @ 0x00fecc90 FUN_00fecc90
cSPMissionManager* cSPMissionManager::FUN_00fecc90()
{
    ((cGonzagoSimulator*)this)->ConstructSelf();

    mpVtbl10 = (void*)&g_vtbl_013eb384;
    mb14 = 0;
    mb15 = 0;
    mb17 = 0;
    mb18 = 0;
    mpUnk1c = 0;
    mpVtbl00 = (void*)&g_vtbl_01494964;
    mpVtbl08 = (void*)&g_vtbl_01494940;
    mpVtbl10 = (void*)&g_vtbl_01494930;
    mb16 = 1;

    mRecVec20.mpBegin = 0; mRecVec20.mpEnd = 0; mRecVec20.mpCap = 0;
    mRecVec34.mpBegin = 0; mRecVec34.mpEnd = 0; mRecVec34.mpCap = 0;
    mRecVec48.mpBegin = 0; mRecVec48.mpEnd = 0; mRecVec48.mpCap = 0;

    mFeedbackMap.mpEndNodeSelf = 0;
    mFeedbackMap.mpRoot = 0;
    mFeedbackMap.mb10 = 0;
    mFeedbackMap.mpRoot = 0;
    mFeedbackMap.mb10 = 0;
    mFeedbackMap.mn14 = 0;
    mFeedbackMap.mpEndNodeSelf = (void*)&mFeedbackMap.mpEndNode;
    mFeedbackMap.mpEndNode = (void*)&mFeedbackMap.mpEndNode;

    mpProp78 = 0;
    mpProp7c = 0;
    mpArr80 = 0;
    mUnk84 = 0;
    mUnk88 = 0;
    mpArr94 = 0;
    mUnk98 = 0;
    mUnk9c = 0;
    mSlotVec.mpBegin = 0;
    mSlotVec.mpEnd = 0;
    mSlotVec.mpCap = 0;
    mnBC = 0;
    mpC0 = 0;
    mpC4 = 0;

    mListC8.mpNext = (tTimerNode*)&mListC8;
    mListC8.mpPrev = (tTimerNode*)&mListC8;
    mListD4.mpNext = (tTimerNode*)&mListD4;
    mListD4.mpPrev = (tTimerNode*)&mListD4;

    mnE0 = 0;
    mnE4 = 0;
    mnE8 = 0;
    mnEC = 0;
    mKeyF0.mType = 0; mKeyF0.mInstance = 0; mKeyF0.mGroup = 0;
    mKeyFC.mType = 0; mKeyFC.mInstance = 0; mKeyFC.mGroup = 0;
    mVec108.mpBegin = 0;
    mVec108.mpEnd = 0;
    mVec108.mpCap = 0;
    mVec11c.mpBegin = 0;
    mVec11c.mpEnd = 0;
    mVec11c.mpCap = 0;
    mVec130.mpBegin = 0;
    mVec130.mpEnd = 0;
    mVec130.mpCap = 0;

    g_missionMgrInstance = (uint32_t)this;
    return this;
}

// =============================================================================================
// 0x00fece20 - destructor
// =============================================================================================
// @ 0x00fece20 FUN_00fece20
void cSPMissionManager::FUN_00fece20()
{
    mpVtbl00 = (void*)&g_vtbl_01494964;
    mpVtbl08 = (void*)&g_vtbl_01494940;
    mpVtbl10 = (void*)&g_vtbl_01494930;
    g_missionMgrInstance = 0;

    if (mVec130.mpBegin != 0 && *((int32_t*)mVec130.mpBegin - 1) != 0)
        operator_delete_array(mVec130.mpBegin);
    if (mVec11c.mpBegin != 0 && *((int32_t*)mVec11c.mpBegin - 1) != 0)
        operator_delete_array(mVec11c.mpBegin);
    if (mVec108.mpBegin != 0 && *((int32_t*)mVec108.mpBegin - 1) != 0)
        operator_delete_array(mVec108.mpBegin);
    mListD4.DestroyAll();
    mListC8.DestroyAll();
    if (mpC4 != 0)
        mpC4->Release();
    if (mpC0 != 0)
        mpC0->Release();
    mSlotVec.Destroy();
    if (mpArr94 != 0 && *((int32_t*)mpArr94 - 1) != 0)
        operator_delete_array(mpArr94);
    if (mpArr80 != 0 && *((int32_t*)mpArr80 - 1) != 0)
        operator_delete_array(mpArr80);
    if (mpProp7c != 0)
        mpProp7c->Release();
    if (mpProp78 != 0)
        mpProp78->Release();
    mFeedbackMap.NukeSubtree(mFeedbackMap.mpRoot);
    mRecVec48.FUN_00fecc40(mRecVec48.mpBegin, mRecVec48.mpEnd);
    if (mRecVec48.mpBegin != 0 && *((int32_t*)mRecVec48.mpBegin - 1) != 0)
        operator_delete_array(mRecVec48.mpBegin);
    mRecVec34.FUN_00fecc40(mRecVec34.mpBegin, mRecVec34.mpEnd);
    if (mRecVec34.mpBegin != 0 && *((int32_t*)mRecVec34.mpBegin - 1) != 0)
        operator_delete_array(mRecVec34.mpBegin);
    mRecVec20.FUN_00fecc40(mRecVec20.mpBegin, mRecVec20.mpEnd);
    if (mRecVec20.mpBegin != 0 && *((int32_t*)mRecVec20.mpBegin - 1) != 0)
        operator_delete_array(mRecVec20.mpBegin);

    mpVtbl10 = (void*)&g_vtbl_013eb394;
    mpVtbl08 = (void*)&g_vtbl_013eb938;
    mpVtbl00 = (void*)&g_vtbl_013ec458;
}

// =============================================================================================
// 0x00fecfc0 - push a timer value onto the front of a timer list
// =============================================================================================
// @ 0x00fecfc0 FUN_00fecfc0
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

// =============================================================================================
// 0x00fed0b0 - (re)read the mission manager's configuration properties
// =============================================================================================
// @ 0x00fed0b0 SP::cSPMissionManager::CacheProperties
void cSPMissionManager::CacheProperties()
{
    cIPropertyManager* pPM = (cIPropertyManager*)PropertyManager();
    if (mpProp78 != 0) {
        cProperty* pOld = mpProp78;
        mpProp78 = 0;
        pOld->Release();
    }
    pPM->v2c(0x1254b050, 0x2ae1a8e, (void**)&mpProp78);

    cIPropertyManager* pPM2 = (cIPropertyManager*)PropertyManager();
    if (mpProp7c != 0) {
        cProperty* pOld = mpProp7c;
        mpProp7c = 0;
        pOld->Release();
    }
    pPM2->v2c(0xe8e2f4b2, 0x2ae1a8e, (void**)&mpProp7c);

    cProperty* pProp = mpProp7c;
    if (pProp != 0) {
        cProperty* pOut;
        if (pProp->v24(0x14d805b0, (void**)&pOut) && pOut->mnType12 == 0xa)
            mnE0 = *pOut->GetUInt();
    }

    float fValue = 0.0f;
    if (pProp != 0) {
        cProperty* pOut;
        if (pProp->v24(0x14d805b1, (void**)&pOut) && pOut->mnType12 == 0xd)
            fValue = *pOut->GetFloat();
    }
    mnE4 = (uint32_t)(int32_t)(fValue * g_k1000);

    if (pProp != 0) {
        cProperty* pOut;
        if (pProp->v24(0x14d805b2, (void**)&pOut) && pOut->mnType12 == 0xd)
            fValue = *pOut->GetFloat();
    }
    mnE8 = (uint32_t)(int32_t)(fValue * g_k1000);

    if (pProp != 0) {
        cProperty* pOut;
        if (pProp->v24(0x14d805b5, (void**)&pOut) && pOut->mnType12 == 0xa)
            mnEC = *pOut->GetUInt();
    }

    GetPropertyAsKey(pProp, 0x14d805b6, &mKeyF0);
    GetPropertyAsKey(pProp, 0x14d805b7, &mKeyFC);

    int32_t nCount = 0;
    uint32_t* pArray = 0;
    GetPropertyAsUint32Array(pProp, 0x14d805b4, &nCount, &pArray);
    for (int32_t i = 0; i < nCount; ++i)
        g_cachedUintArray[i] = pArray[i];

    {
        int32_t nRecCount = 0;
        void* pRecs = 0;
        GetPropertyAsKeyArray(pProp, 0x14d805b8, &nRecCount, &pRecs);
        for (int32_t i = 0; i < nRecCount; ++i)
            mVec130.push_back(((tKey*)pRecs)[i].mType);
    }
    {
        int32_t nRecCount = 0;
        void* pRecs = 0;
        GetPropertyAsKeyArray(pProp, 0x14d805b9, &nRecCount, &pRecs);
        for (int32_t i = 0; i < nRecCount; ++i)
            mVec11c.push_back(((tKey*)pRecs)[i].mType);
    }
    {
        int32_t nRecCount = 0;
        void* pRecs = 0;
        GetPropertyAsKeyArray(pProp, 0x14d805ba, &nRecCount, &pRecs);
        for (int32_t i = 0; i < nRecCount; ++i)
            mVec108.push_back(((tKey*)pRecs)[i].mType);
    }
}