// Slice s00c562b0 -- SPGonzago/SPMission.obj: the generic "pressure" event mission (OnComplete, Init,
// Update), the happiness event (OnAccept, Update, OnComplete), the "make ally" mission constructor and
// Init, a message handler of the alliance mission, the multi-delivery mission accessors (buyer/seller
// item lists, travel cost and distance) and the serializer of one delivery item.
//
// Every mission derives from SP::cSPMission (0x1f0 bytes; the members below +0x1f0 are shared by all
// missions), each concrete mission keeps its own members from +0x1f0 on.  The message handler
// functions are entered with `this` pointing at the handler sub-object stored at mission+0x34.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

// ---------------------------------------------------------------------------------------------
// unnamed-slot filler used to reach the high retail vtable slots
// ---------------------------------------------------------------------------------------------
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
struct IEmpty {};

struct cProperty;
struct cPropertyList;
struct cStarRecordRef;
struct cPlanet;
struct cEmpire;
struct cCivData;
struct cCity;
struct cSPSimulatorSpaceGame;

// ---------------------------------------------------------------------------------------------
// eastl::basic_string<wchar_t, eastl::allocator>
// ---------------------------------------------------------------------------------------------
extern wchar_t gEmptyString16[];                       // 0x01667bac `?gEmptyString16@eastl@@3PA_WA`
void __cdecl FreeArray(void* block);                   // 0x00f47380 operator delete[]

struct WString {
    wchar_t* mpBegin;                                  // +0x00
    wchar_t* mpEnd;                                    // +0x04
    wchar_t* mpCapacity;                               // +0x08
    uint32_t mAllocatorState;                          // +0x0c (not initialised by the constructor)

    WString()
    {
        mpBegin = gEmptyString16;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    void Release()
    {
        if (((int32_t)((char*)mpCapacity - (char*)mpBegin) & ~1) > 2) {
            if (mpBegin)
                FreeArray(mpBegin);
        }
    }
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};

// ---------------------------------------------------------------------------------------------
// property bags
// ---------------------------------------------------------------------------------------------
struct cProperty {
    void*    mpData;                                   // +0x00 storage (a pointer or an inline value)
    uint8_t  pad04[4];
    int32_t  mCount;                                   // +0x08 number of stored values
    uint8_t  pad0c[4];
    uint16_t mFlags;                                   // +0x10 storage kind bits (0x30 = vector)
    uint16_t mType;                                    // +0x12 value type: 9 int, 10 uint32
    int32_t* GetInt();                                 // 0x0041e990
};

struct cPropertyList : VPad<9, IEmpty> {
    virtual bool       GetProperty(uint32_t key, cProperty** out);      // 0x24
    virtual cProperty* GetPropertyRef(uint32_t key);                    // 0x28
};

class cPropertyManager {
public:
    virtual void slot00();  virtual void slot04();  virtual void slot08();  virtual void slot0c();
    virtual void slot10();  virtual void slot14();  virtual void slot18();  virtual void slot1c();
    virtual void slot20();  virtual void slot24();  virtual void slot28();
    virtual bool GetProperty(const void* itemDefinition, uint32_t key, cProperty** out);   // +0x2c
};
cPropertyManager* __cdecl PropertyManager();           // 0x0067de30
void __cdecl GetPropertyAsText(cProperty* pProperty, uint32_t key, WString* out);   // 0x006a1360

// ---------------------------------------------------------------------------------------------
// UI event log
// ---------------------------------------------------------------------------------------------
class cSPUIEventLog {
public:
    void     RemoveEvent(uint32_t eventID, int32_t mode);                             // 0x00dd6d10
    uint32_t PostFeedbackEvent(uint32_t a, uint32_t b, int32_t c, int32_t d, int32_t e,
                               int32_t f);                                            // 0x00dd8640
    void     ModifyEventText(uint32_t eventID, const wchar_t* text);                  // 0x00dd6df0
    void     EventDoNotAddToHistory(uint32_t eventID, int32_t mode);                  // 0x00dd67d0
};
cSPUIEventLog* __cdecl EventLog();                     // 0x00b3d3e0

// ---------------------------------------------------------------------------------------------
// reference counted helpers
// ---------------------------------------------------------------------------------------------
struct IRefCounted {
    virtual void AddRef();
    virtual void Release();
};

template <class T> class AutoRefCount {
public:
    T* mpObject;                                       // +0x00

    void operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* pOld = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pOld)
                pOld->Release();
        }
    }
    T* operator->() const { return mpObject; }
};

// ---------------------------------------------------------------------------------------------
// planets, star records, civ data
// ---------------------------------------------------------------------------------------------
struct tCivDataList {                                  // vector of civ data records
    cCivData** mpBegin;                                // +0x00
    cCivData** mpEnd;                                  // +0x04
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

class cStarRecordRef {
public:
    uint8_t       pad000[0x15c];
    tCivDataList  mCivDataList;                        // +0x15c
    bool    FUN_00b8e040(uint32_t key);                // 0x00b8e040 loyalty booster present
    int32_t FUN_00b8de30();                            // 0x00b8de30 star record handle
    bool    FUN_00b8d970();                            // 0x00b8d970
    int32_t FUN_00b8dab0();                            // 0x00b8dab0
    void*   GetCommContext(void* pData);               // 0x00ce6950
    int32_t GetNumItemGroups();                        // 0x00c710c0
    void*   GetItemGroup(int32_t index);               // 0x00c71030
};

class cSimItem {
public:
    void FUN_00ff0370(float value);                    // 0x00ff0370
};

struct tItemGroup {
    uint8_t    pad00[0x3c];
    cSimItem** mpObjects;                              // +0x3c
    cSimItem** mpObjectsEnd;                           // +0x40
};

struct ICPlanetVtbl : VPad<47, IEmpty> {
    virtual void AddRef();                             // +0xbc
    virtual void Release();                            // +0xc0
};

class cPlanet : public ICPlanetVtbl {
public:
    uint8_t         pad004[0xd0];
    void*           mpSerializedState;                 // +0x0d4
    uint8_t         pad0d8[0x64];
    cStarRecordRef* mpStarRecord;                      // +0x13c
    uint8_t         pad140[0x78];
    uint8_t         mPendingEventCount;                // +0x1b8
    void FUN_00c71430(int32_t a, int32_t b);           // 0x00c71430
    int32_t FUN_00c710c0();                            // 0x00c710c0 item group count
    void* FUN_00c71030(int32_t index);                 // 0x00c71030 item group by index
};

struct tCityList {                                     // cCivData::GetCities result
    cCity** mpBegin;                                   // +0x00
    cCity** mpEnd;                                     // +0x04
    int32_t size() const { return (int32_t)(mpEnd - mpBegin); }
};

class cCivData {
public:
    tCityList* GetCities();                            // 0x005c65e0
};

class cCity {
public:
    uint8_t pad00[0x30];
    float   mHappiness;                                // +0x30
};

extern const float g_cityHappinessThreshold;           // 0x013eecd8 20.0f

class cEmpire {
public:
    uint8_t  pad000[0x84];
    uint32_t mKey;                                     // +0x84
    bool FUN_00c31bc0(void* pOther);                   // 0x00c31bc0
    void* GetShipList();                               // 0x0108db30
};

cEmpire* __cdecl FUN_01021300();                       // 0x01021300 player empire
cPlanet* __cdecl FUN_01021260();                       // 0x01021260 active planet

void     __cdecl FUN_01041c50(const char* name, uint32_t id, int32_t flag);   // 0x01041c50

// ---------------------------------------------------------------------------------------------
// simulator / comm
// ---------------------------------------------------------------------------------------------
class cPlayerInventory {
public:
    uint8_t pad000[0x74c];
    bool    mbInSpace;                                 // +0x74c
};

class cSPSimulatorSpaceGame {
public:
    cPlayerInventory* GetPlayerInventory();                        // 0x00a1ad60
    int32_t FUN_00ffc4e0(void* pOrigin, void* pDest);              // 0x00ffc4e0 travel cost
    float   FUN_00ffc490(void* pOrigin, void* pDest);              // 0x00ffc490 travel distance
};
cSPSimulatorSpaceGame* __cdecl GetUFOSimulator();      // 0x00ffbe50
void __cdecl FUN_00ff0370(void* pObject, float value); // 0x00ff0370

class cCommManager {
public:
    IRefCounted* FUN_00aeb3e0();                       // 0x00aeb3e0
};
cCommManager* __stdcall CommManager(uint32_t key, int32_t context, void* pCommContext);   // 0x00b3d4a0

class cTerrainSphere {
public:
    bool FUN_00c772c0();                               // 0x00c772c0
};
class cGameNounManager {
public:
    cTerrainSphere* GetCurrentTerrainSphere(uint32_t key);          // 0x00f67d90
};
cGameNounManager* __cdecl NounManager();               // 0x00b3d300

class cScaleSource {
public:
    double FUN_00fd9410();                             // 0x00fd9410
};
cScaleSource* __cdecl FUN_0107bcb0();                  // 0x0107bcb0

class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t range);      // 0x00a68fb0
};
extern RandomLinearCongruential g_spRandom;            // 0x01601760
extern uint32_t g_placeloyaltyBooster;                 // 0x01691670 `k_placeloyaltybooster`

// ---------------------------------------------------------------------------------------------
// serialization of one delivery item
// ---------------------------------------------------------------------------------------------
struct IArchiveWriter : VPad<6, IEmpty> {
    virtual void* GetStream();                                     // +0x18
};
struct IArchiver0 : VPad<6, IEmpty> {
    virtual void* GetStream();                                     // +0x18
    virtual void* EndRead();                                       // +0x1c
};
struct IArchiver : IArchiver0 {
    virtual IArchiveWriter* GetWriter();                           // +0x20
    virtual void* ReadItem(uint32_t typeID, void* pItem, int32_t flag);   // +0x24
    virtual void* SerializeItem(uint32_t typeID, void* pItem, int32_t flag); // +0x28
    virtual void* SerializeObject(void* pObject);                  // +0x2c
};

void __cdecl EA_ReadInt32(void* pStream, void* pOut, int32_t count, int32_t flag);       // 0x0093a780
bool __cdecl EA_WriteUint32(void* pStream, const uint32_t* pValue, int32_t count,
                            int32_t flag);                 // 0x0093aa70

// ---------------------------------------------------------------------------------------------
// delivery item lists
// ---------------------------------------------------------------------------------------------
struct tItemInfo {                                     // 0xc-byte "requested"/"delivered" record
    AutoRefCount<cPlanet> mpPlanet;                    // +0x00
    int32_t               mRequested;                  // +0x04
    int32_t               mDelivered;                  // +0x08
};

struct tPickupInfo {                                   // 0x14-byte buyer-request record
    AutoRefCount<cPlanet> mpPlanet;                    // +0x00
    uint8_t               pad004[0x0c];
    bool                  mbPickedUp;                  // +0x10
    uint8_t               pad011[3];
};

struct tU32Vector {
    uint32_t* mpBegin;                                 // +0x00
    uint32_t* mpEnd;                                   // +0x04
    uint32_t* mpCapacity;                              // +0x08
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    static void FUN_004558a0(uint32_t* pEnd, const uint32_t* pValue);    // 0x004558a0
    void push_back(uint32_t value)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* pSlot = mpEnd;
            mpEnd = pSlot + 1;
            if (pSlot)
                *pSlot = value;
        } else {
            FUN_004558a0(mpEnd, &value);
        }
    }
};

// ---------------------------------------------------------------------------------------------
// cSPMission (0x1f0 bytes; the members from +0x1f0 on belong to the concrete missions)
// ---------------------------------------------------------------------------------------------
struct IMissionVtbl0 : VPad<41, IEmpty> {
    virtual void* GetCommData(uint32_t key, int32_t mode, void* pOwner, bool flag);   // +0xa4
};
struct IMissionVtbl1 : VPad<20, IMissionVtbl0> {
    virtual bool IsUIShortDescriptionReady();                                        // +0xf8
};

class cSPMission : public IMissionVtbl1 {
public:
    void*        mpVtblSecondary;                      // +0x004
    uint8_t      pad008[0x2c];
    void*        mpHandlerVtbl;                        // +0x034
    uint8_t      pad038[0x44];
    uint32_t     mElapsedTime;                         // +0x07c milliseconds
    uint8_t      pad080[0x1c];
    cPlanet*     mpActivePlanet;                       // +0x09c
    uint8_t      pad0a0[0x94];
    tU32Vector   mEventIDList;                         // +0x134
    uint8_t      pad140[0x0c];
    WString      mUIShortDescription;                  // +0x14c
    uint8_t      pad158[0x24];
    cPropertyList* mpMissionPropList;                  // +0x180
    uint8_t      pad184[0x60];
    AutoRefCount<IRefCounted> mpCommTarget;            // +0x1e4
    uint8_t      pad1e8[0x08];

    void   ConstructBase();                            // 0x00c48e90
    bool   Init();                                     // 0x00c4ad50
    void   Accept();                                   // 0x00c485b0
    void   OnAccept();                                 // 0x00c47a10
    bool   Validate();                                 // 0x00c484e0
    int32_t Update(uint32_t delta);                    // 0x00c478b0
    cPlanet* GetTargetPlanet();                        // 0x00970b30
    cEmpire* GetOwnerEmpire();                         // 0x00c451e0
    void   SetState(int32_t state);                    // 0x00c47cc0
    void   TriggerUIUpdate();                          // 0x00c47d80
    void   HandleMessage(uint32_t message, void* data);  // 0x00c4a6b0
    void   GetText(uint32_t textID, WString* pOut);    // 0x00c487d0
    void   FUN_00c45cf0(cPlanet* pPlanet);             // 0x00c45cf0
    bool   FUN_00c45d80(void* pStarRecord);            // 0x00c45d80
    void   FUN_00c466d0();                             // 0x00c466d0
    void   FUN_00c46b80();                             // 0x00c46b80
    void   FUN_00c48e50(uint32_t eventID);             // 0x00c48e50
    void   FUN_00c4a0c0();                             // 0x00c4a0c0
};

struct tMissionVtblSlots {
    void*   mpMain;                                    // +0x000
    void*   mpSecondary;                               // +0x004
    uint8_t pad008[0x2c];
    void*   mpHandler;                                 // +0x034
};

// ---------------------------------------------------------------------------------------------
// cSPGenericPressureEvent -- "keep the planet happy for N seconds"
// ---------------------------------------------------------------------------------------------
class cSPGenericPressureEvent : public cSPMission {
public:
    int32_t mPressureTarget;                           // +0x1f0 required seconds, -1 = finished
    int32_t mEventID;                                  // +0x1f4
    void OnComplete();
    bool Init();
    int32_t Update(uint32_t delta);
};

// ---------------------------------------------------------------------------------------------
// cSPMissionHappinessEvent -- "get the planet happiness above the threshold"
// ---------------------------------------------------------------------------------------------
class cSPMissionHappinessEvent : public cSPMission {
public:
    void OnAcceptMission();
    int32_t Update(uint32_t delta);
    void OnCompleteMission();
};

// ---------------------------------------------------------------------------------------------
// cMissionMakeAlly -- the mission installed by the first-alliance event
// ---------------------------------------------------------------------------------------------
extern void* g_vtblMissionMakeAlly[];                  // 0x0146ef48
extern void* g_vtblMissionMakeAllySecondary[];         // 0x0146dfb4
extern void* g_vtblMissionMakeAllyHandler[];           // 0x0146ef34

class cMissionMakeAlly : public cSPMission {
public:
    int32_t mAllyEmpireID;                             // +0x1f0
    bool    mbAlliancePossible;                        // +0x1f4
    uint8_t pad1f5[3];
    cMissionMakeAlly* Construct();
    bool Init();
};

// message handler sub-object stored at mission+0x34 of the alliance mission
class cMsgHandler {
public:
    virtual void* slot00();                            // +0x00
    virtual void  HandleMessage(uint32_t message, void* data);   // +0x04
    virtual void  slot08();                            // +0x08
    virtual void  slot0c();                            // +0x0c
    uint8_t pad004[0x1bc];
    bool    mbAlliancePossible;                        // +0x1c0 (mission+0x1f4)
    // cSPMission::HandleMessage (0x00c4a6b0) invoked with this sub-object as `this`
    void    HandleMessageSuper(uint32_t message, void* data);
};

// ---------------------------------------------------------------------------------------------
// cSPMissionTradeRoute -- "carry the items" mission UI text
// ---------------------------------------------------------------------------------------------
class cSPMissionTradeRoute : public cSPMission {
public:
    int32_t mTradeState;                               // +0x1f0
    bool    mbItemsPickedUp;                           // +0x1f4
    uint8_t pad1f5[3];
    void    GetUIShortDescription(WString* pOut);
};

// ---------------------------------------------------------------------------------------------
// cSPMissionMultiDelivery -- "carry the items from planet A to buyer B"
// ---------------------------------------------------------------------------------------------
class cSPMissionMultiDelivery : public cSPMission {
public:
    int32_t      mDeliveryState;                       // +0x1f0 0 while the items are being fetched
    tItemInfo*   mpRunnerItems;                        // +0x1f4
    tItemInfo*   mpRunnerItemsEnd;                     // +0x1f8
    tItemInfo*   mpRunnerItemsCapacity;                // +0x1fc
    uint8_t      pad200[0x08];
    tPickupInfo* mpBuyerItems;                         // +0x208
    tPickupInfo* mpBuyerItemsEnd;                      // +0x20c
    tPickupInfo* mpBuyerItemsCapacity;                 // +0x210
    uint8_t      pad214[0x1c];
    void*        mpItemDefinition;                     // +0x230
    int32_t      mItemCount;                           // +0x234
    int32_t      mItemsDelivered;                      // +0x238
    WString      mItemName;                            // +0x23c

    int32_t GetNumRunnerItems() { return (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12; }
    int32_t GetNumBuyerItems() { return (int32_t)((char*)mpBuyerItemsEnd - (char*)mpBuyerItems) / 20; }

    void  UpdateItemName();                            // 0x00c56d90
    bool  PickFetchItem();                             // 0x00c56fe0
    bool  IsItemTargetPlanet(void* pStarRecord);       // 0x00c57070
    bool  IsInBuyerPlanetList(void* pPlanet);          // 0x00c570e0
    tPickupInfo* GetItemInfoForPlanet(void* pPlanet);  // 0x00c57130
    bool  IsItemPickedUpInPlanet();                    // 0x00c57180
    bool  DeliverItemsToBuyer(void* pPlanet, int32_t count, int32_t* pDelivered);   // 0x00c571d0
    bool  DeliveredToAllBuyers();                      // 0x00c57270
    int32_t GetNumItemsNotDeliveredToBuyer(void* pPlanet);   // 0x00c572c0
    int32_t GetTotalTravelCost();                      // 0x00c57320
    float GetTotalTravelDistance();                    // 0x00c57420
    void  SetItemPropertyList();                       // 0x00c57520
    int32_t Update(uint32_t delta);                    // 0x00c56b90
    bool  Validate();                                  // 0x00c56ef0
    void  ReturnForRewards();                          // 0x00c4b760
};

// =============================================================================================
// 0x00c562b0 -- cSPGenericPressureEvent::OnComplete
// =============================================================================================
// @ 0x00c562b0 cSPGenericPressureEvent::OnComplete
void cSPGenericPressureEvent::OnComplete()
{
    EventLog()->RemoveEvent(mEventID, 1);
    mEventID = 0;

    WString text;
    GetText(0xa4742587, &text);

    uint32_t eventID = EventLog()->PostFeedbackEvent(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
    EventLog()->ModifyEventText(eventID, text.mpBegin);
    EventLog()->EventDoNotAddToHistory(eventID, 1);
    text.Release();
}

// =============================================================================================
// 0x00c56360 -- cSPGenericPressureEvent::Init
// =============================================================================================
// @ 0x00c56360 cSPGenericPressureEvent::Init
bool cSPGenericPressureEvent::Init()
{
    if (mpMissionPropList) {
        cProperty* pProperty;
        if (mpMissionPropList->GetProperty(0x319296b, &pProperty) && pProperty->mType == 9)
            mPressureTarget = *pProperty->GetInt();
    }

    bool ok = cSPMission::Init();
    Accept();
    FUN_00c45cf0(mpActivePlanet);

    WString text;
    GetText(0xf5e91374, &text);
    mEventID = EventLog()->PostFeedbackEvent(0x5e40fcb9, 0x131a9f54, 0, 0, 1, 0);
    EventLog()->ModifyEventText(mEventID, text.mpBegin);
    mEventIDList.push_back((uint32_t)mEventID);

    mpActivePlanet->FUN_00c71430(3, 1);
    mpActivePlanet->mPendingEventCount++;
    text.Release();
    return ok;
}

// =============================================================================================
// 0x00c56490 -- cSPGenericPressureEvent::Update
// =============================================================================================
// @ 0x00c56490 cSPGenericPressureEvent::Update
int32_t cSPGenericPressureEvent::Update(uint32_t delta)
{
    int32_t result = cSPMission::Update(delta);
    if (result == 3) {
        int32_t required = mPressureTarget;
        if (mpActivePlanet->mpStarRecord->FUN_00b8e040(g_placeloyaltyBooster)) {
            double scale = FUN_0107bcb0()->FUN_00fd9410();
            required = (int32_t)(int64_t)((double)(uint32_t)required * scale);
        }

        if (mPressureTarget >= 0 && mElapsedTime / 1000 > (uint32_t)required) {
            EventLog()->RemoveEvent(mEventID, 1);
            mEventID = 0;

            WString text;
            GetText(0x40951cd1, &text);
            uint32_t eventID = EventLog()->PostFeedbackEvent(0x5e40fcb9, 0x131a9f54, 0, 0, 1, 0);
            EventLog()->ModifyEventText(eventID, text.mpBegin);
            FUN_00c48e50(eventID);
            mEventID = (int32_t)eventID;

            int32_t numGroups = mpActivePlanet->FUN_00c710c0();
            for (int32_t i = 0; i < numGroups; ++i) {
                tItemGroup* pGroup = (tItemGroup*)mpActivePlanet->FUN_00c71030(i);
                int32_t numObjects = (int32_t)(pGroup->mpObjectsEnd - pGroup->mpObjects);
                for (int32_t j = 0; j < numObjects; ++j)
                    pGroup->mpObjects[j]->FUN_00ff0370(0.0f);
            }
            mPressureTarget = -1;
            text.Release();
        }
    }

    cPlanet* pPlanet = mpActivePlanet;
    if (pPlanet == FUN_01021260() && GetUFOSimulator()->GetPlayerInventory()->mbInSpace)
        return 5;
    return 3;
}

// =============================================================================================
// 0x00c56760 -- cSPMissionHappinessEvent::OnAccept
// =============================================================================================
// @ 0x00c56760 cSPMissionHappinessEvent::OnAcceptMission
void cSPMissionHappinessEvent::OnAcceptMission()
{
    cSPMission::OnAccept();
    cPlanet* pTargetPlanet = GetTargetPlanet();
    pTargetPlanet->mPendingEventCount++;

    cEmpire* pOwnerEmpire = GetOwnerEmpire();
    cEmpire* pPlayerEmpire = FUN_01021300();
    if (!pOwnerEmpire)
        return;
    if (pOwnerEmpire != pPlayerEmpire && !pOwnerEmpire->FUN_00c31bc0(pPlayerEmpire))
        return;

    cStarRecordRef* pStarRecord = GetTargetPlanet()->mpStarRecord;
    cStarRecordRef* pContextRecord = GetTargetPlanet()->mpStarRecord;
    uint32_t empireKey = pOwnerEmpire->mKey;
    void* pCommData = GetCommData(0x8b756f4b, 2, this, pOwnerEmpire == pPlayerEmpire);
    cCommManager* pCommManager = CommManager(empireKey, pContextRecord->FUN_00b8de30(),
                                             pStarRecord->GetCommContext(pCommData));
    mpCommTarget = pCommManager->FUN_00aeb3e0();
}

// =============================================================================================
// 0x00c56850 -- cSPMissionHappinessEvent::Update
// =============================================================================================
// @ 0x00c56850 cSPMissionHappinessEvent::Update
int32_t cSPMissionHappinessEvent::Update(uint32_t delta)
{
    int32_t result = cSPMission::Update(delta);
    if (result == 3) {
        cStarRecordRef* pStarRecord = GetTargetPlanet()->mpStarRecord;
        tCivDataList* pCivList = &pStarRecord->mCivDataList;
        if (pCivList->size() > 0) {
            tCityList* pCities = pCivList->mpBegin[0]->GetCities();
            for (int32_t i = 0; i < pCities->size(); ++i) {
                if (pCities->mpBegin[i]->mHappiness <= g_cityHappinessThreshold)
                    return 3;
            }
        }
        result = 5;
    }
    return result;
}

// =============================================================================================
// 0x00c568d0 -- cSPMissionHappinessEvent::OnComplete
// =============================================================================================
// @ 0x00c568d0 cSPMissionHappinessEvent::OnCompleteMission
void cSPMissionHappinessEvent::OnCompleteMission()
{
    WString text;
    GetText(0x25594ea8, &text);
    uint32_t eventID = EventLog()->PostFeedbackEvent(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
    EventLog()->ModifyEventText(eventID, text.mpBegin);

    cPlanet* pPlanet = GetTargetPlanet();
    pPlanet->mPendingEventCount--;

    FUN_00c46b80();
    text.Release();
}

// =============================================================================================
// 0x00c56970 -- cMissionMakeAlly::cMissionMakeAlly
// =============================================================================================
// @ 0x00c56970 cMissionMakeAlly::Construct
cMissionMakeAlly* cMissionMakeAlly::Construct()
{
    ConstructBase();
    mAllyEmpireID = 0;
    mbAlliancePossible = false;
    tMissionVtblSlots* vptrs = (tMissionVtblSlots*)this;
    vptrs->mpMain = &g_vtblMissionMakeAlly;
    vptrs->mpSecondary = &g_vtblMissionMakeAllySecondary;
    vptrs->mpHandler = &g_vtblMissionMakeAllyHandler;
    return this;
}

// =============================================================================================
// 0x00c56ac0 -- cMissionMakeAlly::Init
// =============================================================================================
// @ 0x00c56ac0 cMissionMakeAlly::Init
bool cMissionMakeAlly::Init()
{
    if (!cSPMission::Init())
        return false;
    FUN_00c4a0c0();
    return true;
}

// =============================================================================================
// 0x00c56b20 -- alliance mission message handler (this == mission+0x34)
// =============================================================================================
// @ 0x00c56b20 cMsgHandler::HandleMessage
void cMsgHandler::HandleMessage(uint32_t message, void* data)
{
    // the handler is a secondary base sub-object of the mission, stored at mission+0x34
    if (message == 0x5fa2448) {
        mbAlliancePossible = true;
        cTerrainSphere* pSphere = NounManager()->GetCurrentTerrainSphere(0x5fa31f4);
        if (!pSphere->FUN_00c772c0())
            FUN_01041c50("SPG_FirstAlliancePossible", 0x5fa31f4, 1);
        cSPMission* pMission = (cSPMission*)((char*)this - 0x34);
        pMission->TriggerUIUpdate();
    }
    HandleMessageSuper(message, data);
}

// =============================================================================================
// 0x00c56b90 -- cSPMissionMultiDelivery::Update
// =============================================================================================
// @ 0x00c56b90 cSPMissionMultiDelivery::Update
int32_t cSPMissionMultiDelivery::Update(uint32_t delta)
{
    int32_t result = cSPMission::Update(delta);
    if (mDeliveryState == 0) {
        tU32Vector* pShips = (tU32Vector*)FUN_01021300()->GetShipList();
        uint32_t numShips = pShips->size();
        if (numShips > 0)
            ReturnForRewards();
    }
    return result;
}

// =============================================================================================
// 0x00c56bd0 -- cSPMissionTradeRoute::GetUIShortDescription
// =============================================================================================
// @ 0x00c56bd0 cSPMissionTradeRoute::GetUIShortDescription
void cSPMissionTradeRoute::GetUIShortDescription(WString* pOut)
{
    uint32_t textID;
    if (mUIShortDescription.mpBegin == mUIShortDescription.mpEnd) {
        if (IsUIShortDescriptionReady())
            textID = 0x4e1f8fa8;
        else if (mbItemsPickedUp)
            textID = 0xf046cb6d;
        else
            textID = 0xaad9c0b3;
        GetText(textID, pOut);
        if (pOut != &mUIShortDescription)
            mUIShortDescription.assign(pOut->mpBegin, pOut->mpEnd);
    } else if (pOut != &mUIShortDescription) {
        pOut->assign(mUIShortDescription.mpBegin, mUIShortDescription.mpEnd);
    }
}

// =============================================================================================
// 0x00c56d90 -- cSPMissionMultiDelivery::UpdateItemName
// =============================================================================================
// @ 0x00c56d90 cSPMissionMultiDelivery::UpdateItemName
void cSPMissionMultiDelivery::UpdateItemName()
{
    cProperty* pProperty = 0;
    PropertyManager()->GetProperty(mpItemDefinition, 0x37d494e, &pProperty);
    GetPropertyAsText(pProperty, 0x3068d95d, &mItemName);
}

// =============================================================================================
// 0x00c56de0 -- operator>> (read one delivery item)
// =============================================================================================
// @ 0x00c56de0 operator>>
IArchiver& operator>>(IArchiver& archiver, tItemInfo& item)
{
    void* pStream = archiver.GetWriter()->GetStream();
    EA_ReadInt32(pStream, &item.mRequested, 1, 0);
    pStream = archiver.GetWriter()->GetStream();
    EA_ReadInt32(pStream, &item.mDelivered, 1, 0);
    item.mpPlanet = 0;
    archiver.SerializeItem(0x3275872, &item, 0);
    return archiver;
}

// =============================================================================================
// 0x00c56e60 -- operator<< (write one delivery item)
// =============================================================================================
// @ 0x00c56e60 operator<<
IArchiver& operator<<(IArchiver& archiver, const tItemInfo& item)
{
    void* pStream = archiver.GetWriter()->GetStream();
    uint32_t value = (uint32_t)item.mRequested;
    EA_WriteUint32(pStream, &value, 1, 0);
    pStream = archiver.GetWriter()->GetStream();
    value = (uint32_t)item.mDelivered;
    EA_WriteUint32(pStream, &value, 1, 0);
    archiver.SerializeObject(item.mpPlanet.mpObject ? &item.mpPlanet.mpObject->mpSerializedState : 0);
    return archiver;
}

// =============================================================================================
// 0x00c56ef0 -- cSPMissionMultiDelivery::Validate
// =============================================================================================
// @ 0x00c56ef0 cSPMissionMultiDelivery::Validate
bool cSPMissionMultiDelivery::Validate()
{
    if (!cSPMission::Validate())
        return false;

    int32_t numBuyers = (int32_t)((char*)mpBuyerItemsEnd - (char*)mpBuyerItems) / 20;
    for (int32_t i = 0; i < numBuyers; ++i) {
        if (mpBuyerItems[i].mpPlanet->mpStarRecord->FUN_00b8d970()) {
            SetState(1);
            return false;
        }
    }

    int32_t numItems = (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12;
    for (int32_t i = 0; i < numItems; ++i) {
        cStarRecordRef* pStarRecord = mpRunnerItems[i].mpPlanet->mpStarRecord;
        if (pStarRecord->FUN_00b8d970() || pStarRecord->FUN_00b8dab0() != 5) {
            SetState(1);
            return false;
        }
    }
    return true;
}

// =============================================================================================
// 0x00c56fe0 -- cSPMissionMultiDelivery::PickFetchItem
// =============================================================================================
// @ 0x00c56fe0 cSPMissionMultiDelivery::PickFetchItem
bool cSPMissionMultiDelivery::PickFetchItem()
{
    if (!mpMissionPropList)
        return false;

    cProperty* pProperty = mpMissionPropList->GetPropertyRef(0x781900a6);
    uint16_t kind = pProperty->mFlags & 0x30;
    if (kind == 0 && pProperty->mType == 0)
        return false;

    int32_t count;
    tItemInfo* pItems;
    if (kind) {
        count = pProperty->mCount;
        if (count <= 0)
            return false;
        pItems = (tItemInfo*)pProperty->mpData;
    } else {
        count = 1;
        pItems = pProperty->mType ? (tItemInfo*)pProperty : 0;
    }

    uint32_t index = g_spRandom.RandomUint32Uniform((uint32_t)count);
    mpItemDefinition = pItems[index].mpPlanet.mpObject;
    mItemCount = 0;
    mItemsDelivered = 0;
    UpdateItemName();
    return true;
}

// =============================================================================================
// 0x00c57070 -- cSPMissionMultiDelivery item/target check
// =============================================================================================
// @ 0x00c57070 cSPMissionMultiDelivery::IsItemTargetPlanet
bool cSPMissionMultiDelivery::IsItemTargetPlanet(void* pStarRecord)
{
    if (FUN_00c45d80(pStarRecord))
        return true;
    for (tItemInfo* p = mpRunnerItems; p != mpRunnerItemsEnd; ++p) {
        if (p->mpPlanet->mpStarRecord == pStarRecord)
            return true;
    }
    for (tPickupInfo* p = mpBuyerItems; p != mpBuyerItemsEnd; ++p) {
        if (p->mpPlanet->mpStarRecord == pStarRecord)
            return true;
    }
    return false;
}

// =============================================================================================
// 0x00c570e0 -- cSPMissionMultiDelivery::IsInBuyerPlanetList
// =============================================================================================
// @ 0x00c570e0 cSPMissionMultiDelivery::IsInBuyerPlanetList
bool cSPMissionMultiDelivery::IsInBuyerPlanetList(void* pPlanet)
{
    int32_t count = (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12;
    for (int32_t i = 0; i < count; ++i) {
        if (mpRunnerItems[i].mpPlanet.mpObject == pPlanet)
            return true;
    }
    return false;
}

// =============================================================================================
// 0x00c57130 -- cSPMissionMultiDelivery::GetItemInfoForPlanet
// =============================================================================================
// @ 0x00c57130 cSPMissionMultiDelivery::GetItemInfoForPlanet
tPickupInfo* cSPMissionMultiDelivery::GetItemInfoForPlanet(void* pPlanet)
{
    for (int32_t i = 0; i < GetNumBuyerItems(); ++i) {
        if (mpBuyerItems[i].mpPlanet.mpObject == pPlanet)
            return &mpBuyerItems[i];
    }
    return 0;
}

// =============================================================================================
// 0x00c57180 -- cSPMissionMultiDelivery::IsItemPickedUpInPlanet
// =============================================================================================
// @ 0x00c57180 cSPMissionMultiDelivery::IsItemPickedUpInPlanet
bool cSPMissionMultiDelivery::IsItemPickedUpInPlanet()
{
    int32_t count = (int32_t)((char*)mpBuyerItemsEnd - (char*)mpBuyerItems) / 20;
    for (int32_t i = 0; i < count; ++i) {
        if (!mpBuyerItems[i].mbPickedUp)
            return false;
    }
    return true;
}

// =============================================================================================
// 0x00c571d0 -- cSPMissionMultiDelivery::DeliverItemsToBuyer
// =============================================================================================
// @ 0x00c571d0 cSPMissionMultiDelivery::DeliverItemsToBuyer
bool cSPMissionMultiDelivery::DeliverItemsToBuyer(void* pPlanet, int32_t count, int32_t* pDelivered)
{
    int32_t numItems = (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12;
    for (int32_t i = 0; i < numItems; ++i) {
        tItemInfo* pItem = &mpRunnerItems[i];
        if ((void*)pItem->mpPlanet.mpObject == pPlanet) {
            int32_t remaining = pItem->mRequested - pItem->mDelivered;
            int32_t carried = count < remaining ? count : remaining;
            pItem->mDelivered += carried;
            if (pDelivered)
                *pDelivered = carried;
            if (pItem->mDelivered >= pItem->mRequested)
                return true;
        }
    }
    return false;
}

// =============================================================================================
// 0x00c57270 -- cSPMissionMultiDelivery::DeliveredToAllBuyers
// =============================================================================================
// @ 0x00c57270 cSPMissionMultiDelivery::DeliveredToAllBuyers
bool cSPMissionMultiDelivery::DeliveredToAllBuyers()
{
    int32_t count = (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12;
    for (int32_t i = 0; i < count; ++i) {
        if (mpRunnerItems[i].mDelivered != mpRunnerItems[i].mRequested)
            return false;
    }
    return true;
}

// =============================================================================================
// 0x00c572c0 -- cSPMissionMultiDelivery::GetNumItemsNotDeliveredToBuyer
// =============================================================================================
// @ 0x00c572c0 cSPMissionMultiDelivery::GetNumItemsNotDeliveredToBuyer
int32_t cSPMissionMultiDelivery::GetNumItemsNotDeliveredToBuyer(void* pPlanet)
{
    int32_t count = (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12;
    for (int32_t i = 0; i < count; ++i) {
        if (mpRunnerItems[i].mpPlanet.mpObject == pPlanet)
            return mpRunnerItems[i].mRequested - mpRunnerItems[i].mDelivered;
    }
    return 0;
}

// =============================================================================================
// 0x00c57320 -- cSPMissionMultiDelivery::GetTotalTravelCost
// =============================================================================================
// @ 0x00c57320 cSPMissionMultiDelivery::GetTotalTravelCost
int32_t cSPMissionMultiDelivery::GetTotalTravelCost()
{
    int32_t total = 0;
    if (mpActivePlanet) {
        void* pOrigin = (void*)mpActivePlanet->mpStarRecord->FUN_00b8de30();
        int32_t numItems = (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12;
        for (int32_t i = 0; i < numItems; ++i) {
            cPlanet* pPlanet = mpRunnerItems[i].mpPlanet.mpObject;
            if (pPlanet) {
                void* pDest = (void*)pPlanet->mpStarRecord->FUN_00b8de30();
                if (pDest)
                    total += GetUFOSimulator()->FUN_00ffc4e0(pOrigin, pDest) * 2;
            }
        }

        int32_t numBuyers = (int32_t)((char*)mpBuyerItemsEnd - (char*)mpBuyerItems) / 20;
        for (int32_t i = 0; i < numBuyers; ++i) {
            cPlanet* pPlanet = mpBuyerItems[i].mpPlanet.mpObject;
            if (pPlanet) {
                void* pDest = (void*)pPlanet->mpStarRecord->FUN_00b8de30();
                if (pDest)
                    total += GetUFOSimulator()->FUN_00ffc4e0(pOrigin, pDest) * 2;
            }
        }
    }
    return total;
}

// =============================================================================================
// 0x00c57420 -- cSPMissionMultiDelivery::GetTotalTravelDistance
// =============================================================================================
// @ 0x00c57420 cSPMissionMultiDelivery::GetTotalTravelDistance
float cSPMissionMultiDelivery::GetTotalTravelDistance()
{
    float total = 0.0f;
    if (mpActivePlanet) {
        void* pOrigin = (void*)mpActivePlanet->mpStarRecord->FUN_00b8de30();
        int32_t numItems = (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12;
        for (int32_t i = 0; i < numItems; ++i) {
            cPlanet* pPlanet = mpRunnerItems[i].mpPlanet.mpObject;
            if (pPlanet) {
                void* pDest = (void*)pPlanet->mpStarRecord->FUN_00b8de30();
                if (pDest)
                    total += GetUFOSimulator()->FUN_00ffc490(pOrigin, pDest) * 2.0f;
            }
        }

        int32_t numBuyers = (int32_t)((char*)mpBuyerItemsEnd - (char*)mpBuyerItems) / 20;
        for (int32_t i = 0; i < numBuyers; ++i) {
            cPlanet* pPlanet = mpBuyerItems[i].mpPlanet.mpObject;
            if (pPlanet) {
                void* pDest = (void*)pPlanet->mpStarRecord->FUN_00b8de30();
                if (pDest)
                    total += GetUFOSimulator()->FUN_00ffc490(pOrigin, pDest) * 2.0f;
            }
        }
    }
    return total;
}

// =============================================================================================
// 0x00c57520 -- cSPMissionMultiDelivery::SetItemPropertyList
// =============================================================================================
// @ 0x00c57520 cSPMissionMultiDelivery::SetItemPropertyList
void cSPMissionMultiDelivery::SetItemPropertyList()
{
    FUN_00c466d0();
    cProperty* pProperty = 0;
    PropertyManager()->GetProperty(mpItemDefinition, 0x37d494e, &pProperty);
    GetPropertyAsText(pProperty, 0x3068d95d, &mItemName);
}

}  // namespace SP
