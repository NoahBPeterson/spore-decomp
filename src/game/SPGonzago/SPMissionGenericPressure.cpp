// src/game/SPGonzago/SPMissionGenericPressure.cpp -- migrated from slice(s) s00c562b0, s00c54f90 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionGenericPressure.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cCity.h"
#include "SP/cCivData.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanet.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPGenericPressureEvent.h"
#include "SP/cSPMission.h"
#include "SP/cSPMissionHappinessEvent.h"
#include "SP/cTerrainSphere.h"

// ---- items of slice s00c54f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
class cSubMission {
public:
    virtual void Method00();
    virtual void Method04();
    virtual void Method08();
    virtual void* HasKey(uint32_t nKey);        // 0x0c
    uint32_t GetDiseaseEffectID();

    uint8_t mPad14[0x1dc];                      // 0x014
    int32_t mnState;                            // 0x1f0
};
struct cSubMissionVector {
    cSubMission** mpBegin;                      // 0x00
    cSubMission** mpEnd;                        // 0x04
    cSubMission** mpCapacity;                   // 0x08
};
struct cHerd {
    uint8_t mPad000[0x40];                      // 0x000
    void** mpSpeciesBegin;                      // 0x040
    void** mpSpeciesEnd;                        // 0x044
};
struct cHerdVector {
    void Clear();

    cHerd** mpBegin;                            // 0x00
    cHerd** mpEnd;                              // 0x04
    cHerd** mpCapacity;                         // 0x08
};
class cEventLog {
public:
    void SetStoryFlag(int nA, int nB);
    void RemoveEvent();

    uint8_t mPad000[0x1b8];                     // 0x000
    uint8_t mnCount;                            // 0x1b8
};
void BaseOnSubMissionComplete();  // 0x00c558f0 (defined below; used by a stub's inline body)
class cSPMissionFlight101 {
public:
    cSPMissionFlight101();
    void* Destroy(char bDelete);
    cSubMission* GetEradicateSubMission();
    cSubMission* GetHerdSubMission();
    cSubMission* GetCurrSubMission();
    void* GetTargetPlanet();
    void* UpdateBase(void* pParam);
    void BaseCtor();
    void Shutdown();
    bool Init();
    void PostLoad();
    int Update(void* pParam);
    void ValidateHerds();
    void HandleMessage(int nMessage, void* pParam);
    void GetUIMediumDescription(void* pParam);
    void GetUILongDescription(void* pParam);
    void OnReject();
    void OnAccept();
    void OnSubMissionAccept();
    void OnSubMissionComplete();
    void OnAbort();
    void DestroyObjects();
    void CollectMissionHerds();
    void SetupEradicateObjects();
    void BaseShutdown();
    char BaseInit();
    void BasePostLoad();
    void BaseOnReject();
    void BaseOnAccept();
    void BaseOnSubMissionComplete();
    void BaseDestroy();
    void* GetText(uint32_t nPropertyId, void* pParam);
    void* GetSubMissionMediumText(void* pParam);
    void* GetSubMissionLongText(void* pParam);

    void* mpVftable;                            // 0x00
    void* mpVftable2;                           // 0x04
    uint8_t mPad08[0x2c];                       // 0x08
    void* mpVftable3;                           // 0x34
    uint8_t mPad38[0x40];                       // 0x38
    int32_t mMissionId;                         // 0x078
    uint8_t mPad07c[0x20];                      // 0x07c
    void* mpEventLog;                           // 0x09c
    uint8_t mPad0a0[0xcc];                      // 0x0a0
    void* mpInfectionTarget;                    // 0x16c
    uint8_t mTextBuilder[0x14];                 // 0x170
    uint8_t mPad184[0x6c];                      // 0x184
    cSubMissionVector mSubMissions;             // 0x1f0
    uint8_t mPad1fc[0x34];                      // 0x1fc
    void* mpCurrSubMission;                     // 0x230
    cSubMission* mpEradicateMission;            // 0x234
    int32_t mnDiseaseEffectID;                  // 0x238
    bool mbHerdsInfected;                       // 0x23c
    uint8_t mPad23d[0x03];                      // 0x23d
    cHerdVector mHerds;                         // 0x240
    uint8_t mPad24c[0x18];                      // 0x24c
    int32_t mnHerdTargetKey;                    // 0x264
};
void* GetTargetPlanet(void* pMission);
void SetStoryFlag(int nA, int nB);
void* __stdcall GetObjectFromKey(void* pKey, int nMode);
// ---- items of slice s00c54f90 end

// ---- items of slice s00c562b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
}
namespace SP {
template <class B> struct VPad<0, B> : B {};
}
namespace SP {
struct IEmpty {};
}
namespace SP {
struct cProperty;
}
namespace SP {
struct cPropertyList_s00c5_62b0;
}
namespace SP {
struct cStarRecordRef;
}
namespace SP {
struct cPlanet_s00c5_62b0;
}
namespace SP {
struct cEmpire_s00c5_62b0;
}
namespace SP {
struct cCivData_s00c5_62b0;
}
namespace SP {
struct cCity_s00c5_62b0;
}
namespace SP {
struct cSPSimulatorSpaceGame;
}
namespace SP {
extern wchar_t gEmptyString16[];                       // 0x01667bac `?gEmptyString16@eastl@@3PA_WA`
}
namespace SP {
void __cdecl FreeArray(void* block);                   // 0x00f47380 operator delete[]
}
namespace SP {
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
}
namespace SP {
struct cProperty {
    void*    mpData;                                   // +0x00 storage (a pointer or an inline value)
    uint8_t  pad04[4];
    int32_t  mCount;                                   // +0x08 number of stored values
    uint8_t  pad0c[4];
    uint16_t mFlags;                                   // +0x10 storage kind bits (0x30 = vector)
    uint16_t mType;                                    // +0x12 value type: 9 int, 10 uint32
    int32_t* GetInt();                                 // 0x0041e990
};
}
namespace SP {
struct cPropertyList_s00c5_62b0 : VPad<9, IEmpty> {
    virtual bool       GetProperty(uint32_t key, cProperty** out);      // 0x24
    virtual cProperty* GetPropertyRef(uint32_t key);                    // 0x28
};
}
namespace SP {
class cSPUIEventLog {
public:
    void     RemoveEvent(uint32_t eventID, int32_t mode);                             // 0x00dd6d10
    uint32_t PostFeedbackEvent(uint32_t a, uint32_t b, int32_t c, int32_t d, int32_t e,
                               int32_t f);                                            // 0x00dd8640
    void     ModifyEventText(uint32_t eventID, const wchar_t* text);                  // 0x00dd6df0
    void     EventDoNotAddToHistory(uint32_t eventID, int32_t mode);                  // 0x00dd67d0
};
}
namespace SP {
cSPUIEventLog* __cdecl EventLog();                     // 0x00b3d3e0
}
namespace SP {
struct IRefCounted {
    virtual void AddRef();
    virtual void Release();
};
}
namespace SP {
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
}
namespace SP {
struct tCivDataList {                                  // vector of civ data records
    cCivData_s00c5_62b0** mpBegin;                                // +0x00
    cCivData_s00c5_62b0** mpEnd;                                  // +0x04
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
}
namespace SP {
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
}
namespace SP {
class cSimItem {
public:
    void FUN_00ff0370(float value);                    // 0x00ff0370
};
}
namespace SP {
struct tItemGroup {
    uint8_t    pad00[0x3c];
    cSimItem** mpObjects;                              // +0x3c
    cSimItem** mpObjectsEnd;                           // +0x40
};
}
namespace SP {
struct ICPlanetVtbl : VPad<47, IEmpty> {
    virtual void AddRef();                             // +0xbc
    virtual void Release();                            // +0xc0
};
}
namespace SP {
class cPlanet_s00c5_62b0 : public ICPlanetVtbl {
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
}
namespace SP {
struct tCityList {                                     // cCivData::GetCities result
    cCity_s00c5_62b0** mpBegin;                                   // +0x00
    cCity_s00c5_62b0** mpEnd;                                     // +0x04
    int32_t size() const { return (int32_t)(mpEnd - mpBegin); }
};
}
namespace SP {
class cCivData_s00c5_62b0 {
public:
    tCityList* GetCities();                            // 0x005c65e0
};
}
namespace SP {
class cCity_s00c5_62b0 {
public:
    uint8_t pad00[0x30];
    float   mHappiness;                                // +0x30
};
}
namespace SP {
class cEmpire_s00c5_62b0 {
public:
    uint8_t  pad000[0x84];
    uint32_t mKey;                                     // +0x84
    bool FUN_00c31bc0(void* pOther);                   // 0x00c31bc0
    void* GetShipList();                               // 0x0108db30
};
}
namespace SP {
cPlanet_s00c5_62b0* __cdecl FUN_01021260();                       // 0x01021260 active planet
}
namespace SP {
class cPlayerInventory {
public:
    uint8_t pad000[0x74c];
    bool    mbInSpace;                                 // +0x74c
};
}
namespace SP {
class cSPSimulatorSpaceGame {
public:
    cPlayerInventory* GetPlayerInventory();                        // 0x00a1ad60
    int32_t FUN_00ffc4e0(void* pOrigin, void* pDest);              // 0x00ffc4e0 travel cost
    float   FUN_00ffc490(void* pOrigin, void* pDest);              // 0x00ffc490 travel distance
};
}
namespace SP {
cSPSimulatorSpaceGame* __cdecl GetUFOSimulator();      // 0x00ffbe50
}
namespace SP {
void __cdecl FUN_00ff0370(void* pObject, float value); // 0x00ff0370
}
namespace SP {
class cScaleSource {
public:
    double FUN_00fd9410();                             // 0x00fd9410
};
}
namespace SP {
cScaleSource* __cdecl FUN_0107bcb0();                  // 0x0107bcb0
}
namespace SP {
extern uint32_t g_placeloyaltyBooster;                 // 0x01691670 `k_placeloyaltybooster`
}
namespace SP {
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
}
namespace SP {
struct IMissionVtbl0 : VPad<41, IEmpty> {
    virtual void* GetCommData(uint32_t key, int32_t mode, void* pOwner, bool flag);   // +0xa4
};
}
namespace SP {
struct IMissionVtbl1 : VPad<20, IMissionVtbl0> {
    virtual bool IsUIShortDescriptionReady();                                        // +0xf8
};
}
namespace SP {
class cSPMission_s00c5_62b0 : public IMissionVtbl1 {
public:
    void*        mpVtblSecondary;                      // +0x004
    uint8_t      pad008[0x2c];
    void*        mpHandlerVtbl;                        // +0x034
    uint8_t      pad038[0x44];
    uint32_t     mElapsedTime;                         // +0x07c milliseconds
    uint8_t      pad080[0x1c];
    cPlanet_s00c5_62b0*     mpActivePlanet;                       // +0x09c
    uint8_t      pad0a0[0x94];
    tU32Vector   mEventIDList;                         // +0x134
    uint8_t      pad140[0x0c];
    WString      mUIShortDescription;                  // +0x14c
    uint8_t      pad158[0x24];
    cPropertyList_s00c5_62b0* mpMissionPropList;                  // +0x180
    uint8_t      pad184[0x60];
    AutoRefCount<IRefCounted> mpCommTarget;            // +0x1e4
    uint8_t      pad1e8[0x08];

    void   ConstructBase();                            // 0x00c48e90
    bool   Init();                                     // 0x00c4ad50
    void   Accept();                                   // 0x00c485b0
    void   OnAccept();                                 // 0x00c47a10
    bool   Validate();                                 // 0x00c484e0
    int32_t Update(uint32_t delta);                    // 0x00c478b0
    cPlanet_s00c5_62b0* GetTargetPlanet();                        // 0x00970b30
    cEmpire_s00c5_62b0* GetOwnerEmpire();                         // 0x00c451e0
    void   SetState(int32_t state);                    // 0x00c47cc0
    void   TriggerUIUpdate();                          // 0x00c47d80
    void   HandleMessage(uint32_t message, void* data);  // 0x00c4a6b0
    void   GetText(uint32_t textID, WString* pOut);    // 0x00c487d0
    void   FUN_00c45cf0(cPlanet_s00c5_62b0* pPlanet);             // 0x00c45cf0
    bool   FUN_00c45d80(void* pStarRecord);            // 0x00c45d80
    void   FUN_00c466d0();                             // 0x00c466d0
    void   FUN_00c46b80();                             // 0x00c46b80
    void   FUN_00c48e50(uint32_t eventID);             // 0x00c48e50
    void   FUN_00c4a0c0();                             // 0x00c4a0c0
};
}
namespace SP {
class cSPGenericPressureEvent_s00c5_62b0 : public cSPMission_s00c5_62b0 {
public:
    int32_t mPressureTarget;                           // +0x1f0 required seconds, -1 = finished
    int32_t mEventID;                                  // +0x1f4
    void OnComplete();  // 0x00c562b0 (SP::cSPGenericPressureEvent::OnComplete)
    bool Init();  // 0x00c56360 (SP::cSPGenericPressureEvent::Init)
    int32_t Update(uint32_t delta);  // 0x00c56490 (SP::cSPGenericPressureEvent::Update)
};
}
// ---- items of slice s00c562b0 end

// @ 0x00c56260
void cSPMissionFlight101::OnAbort()
{
    if (mpEventLog != nullptr) {
        ((cEventLog*)mpEventLog)->SetStoryFlag(3, 0);
        --((cEventLog*)mpEventLog)->mnCount;
    }
    if (mSubMissions.mpEnd != nullptr)
        ((cEventLog*)GetObjectFromKey(mSubMissions.mpEnd, 1))->RemoveEvent();
    DestroyObjects();
}

// @ 0x00c562b0
namespace SP {
void cSPGenericPressureEvent_s00c5_62b0::OnComplete()
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
}  // namespace SP

// @ 0x00c56360
namespace SP {
bool cSPGenericPressureEvent_s00c5_62b0::Init()
{
    if (mpMissionPropList) {
        cProperty* pProperty;
        if (mpMissionPropList->GetProperty(0x319296b, &pProperty) && pProperty->mType == 9)
            mPressureTarget = *pProperty->GetInt();
    }

    bool ok = cSPMission_s00c5_62b0::Init();
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
}  // namespace SP

// @ 0x00c56490
namespace SP {
int32_t cSPGenericPressureEvent_s00c5_62b0::Update(uint32_t delta)
{
    int32_t result = cSPMission_s00c5_62b0::Update(delta);
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

    cPlanet_s00c5_62b0* pPlanet = mpActivePlanet;
    if (pPlanet == FUN_01021260() && GetUFOSimulator()->GetPlayerInventory()->mbInSpace)
        return 5;
    return 3;
}
}  // namespace SP
