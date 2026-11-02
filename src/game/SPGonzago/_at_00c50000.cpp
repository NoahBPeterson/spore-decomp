// src/game/SPGonzago/_at_00c50000.cpp -- migrated from slice(s) s00c5e260, s00c5b9c0, s00c5a580, s00c562b0, s00c54f90, s00c54110, s00c4fe60 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00c50000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "SP/cSPMission.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cCity.h"
#include "SP/cCivData.h"
#include "SP/cEmpire.h"
#include "SP/cPlanet.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPGenericPressureEvent.h"
#include "SP/cSPMissionHappinessEvent.h"
#include "SP/cTerrainSphere.h"
#include "SP/cGameData.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl FUN_01021260();                        // current active planet
extern "C" void* __cdecl FUN_01021080();                        // universe context
#pragma warning(disable : 4100)

// ---- items of slice s00c4fe60 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
extern "C" void* __cdecl FUN_01021260();                        // current active planet
extern "C" void* __cdecl FUN_01021080();                        // universe context
class Mob
{
  public:
    void* GetTargetPlanet();              // 0x00970b30 SP::cSPMission::GetTargetPlanet
    void  OnCombatantKilled(void* p);     // 0x00c4fe60
    void  OnCityDestroyed(void* p);       // 0x00c50190
    void  DestroyHerds();                 // 0x00c504a0
    void  OnPlanetDeactivate();           // 0x00c505a0
    void  OnPlanetActivate();             // 0x00c50600
    void  HandleMessage(u32 msg, void* arg);  // 0x00c4a6b0 cSPMission::HandleMessage
    int   GetTagStringBase(int tag, void* o); // 0x00c491c0 cSPMission::GetTagString
    int   GetDiseaseEffectID(int a);      // 0x00c4bd60
    void  GetText(int key, void* out);    // 0x00c487d0 SP::cSPMission::GetText
    void  TriggerUIUpdate();              // 0x00c47d80
    void  PostWarningEvent();             // 0x00c4f9d0
    void  UnkEin();                       // 0x00c4ed20
    void  UnkFfa();                       // 0x00c4fa40
    void  UnkF160();                      // 0x00c4f160
    void  UnkF320();                      // 0x00c4f320
    void  UnkFC00(void* a);               // 0x00c4fc00
    void  Unk471c0();                     // 0x00c471c0
    void  Unk472e0();                     // 0x00c472e0
    void  Unk47a10();                     // 0x00c47a10
    void  Unk48e50(int id);               // 0x00c48e50
    void  SetState(int v);                // 0x00c4eec0
    int   UnkC2b0();                      // 0x00c4c2b0
    void  BaseGetProp(void* out);          // 0x00c4bda0
    void  SerializeRecord(void* rec);     // 0x00c50ba0
    int   GetClosestDiseasedAnimalInner(void* a, void* out); // 0x00c4bdc0
    int   GetUIntField();                 // 0x008e7f80
};
// ---- items of slice s00c4fe60 end

// ---- items of slice s00c54110 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
};
struct Key  { uint32_t a, b, c; };
struct NounManager {
    void* GetDataVector(void* a, void* b, void* c, void* d, uint32_t e); // 0x00b21340
};
struct NearNoun {
    Vec3* GetPosition();                     // 0x00c6acc0
};
struct UFOPlayer {
    void* GetPlayerInventory();              // 0x00a1ad60
};
NounManager* __cdecl GetNounManager_();                // 0x00b3d300
UFOPlayer* __cdecl GetUFOSim();                        // 0x00ffbe50
// ---- items of slice s00c54110 end

// ---- items of slice s00c54f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gVtableFindAliens;
extern void* gVtableFindAliensUnk;
extern void* gVtableFindAliensExtra;
class cMissionFindAliens {
public:
    cMissionFindAliens();
    char IsActive();
    void* GetTargetPlanet();
    void* GetTargetRecord(uint32_t nType);
    void* UpdateBase(void* pParam);
    void BaseCtor();
    void* GetText(uint32_t nPropertyId, void* pParam);
    void GetUIMediumDescription(void* pParam);
    void GetUILongDescription(void* pParam);
    void* GetUIShortDescription(void* pParam);
    char Init();
    void HandleMessage(int nMessage, void* pParam);
    void Update(void* pParam);
    void SetContactGrob();
    char BindTarget();

    void* mpVftable;                            // 0x00
    void* mpVftable2;                           // 0x04
    uint8_t mPad08[0x2c];                       // 0x08
    void* mpVftable3;                           // 0x34
    uint8_t mPad38[0x14c];                      // 0x38
    void* mpMissionPropList;                    // 0x184
    uint8_t mPad188[0x04];                      // 0x188
    uint32_t mnGiveOnAcceptMoney;               // 0x18c
    uint8_t mPad190[0x58];                      // 0x190
    void* mpProperties;                         // 0x1e8
    uint8_t mPad1ec[0x04];                      // 0x1ec
    int32_t mnFindAliensState;                  // 0x1f0
    int32_t mnNumAliensToFind;                  // 0x1f4
    int32_t mnNumAliensFound;                   // 0x1f8
    bool mbContactGrob;                         // 0x1fc
};
void* GetTargetPlanet(void* pMission);
// ---- items of slice s00c54f90 end

// ---- items of slice s00c562b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
void     __cdecl FUN_01041c50(const char* name, uint32_t id, int32_t flag);   // 0x01041c50
}
namespace SP {
class cTerrainSphere_s00c5_62b0 {
public:
    bool FUN_00c772c0();                               // 0x00c772c0
};
}
namespace SP {
class cGameNounManager_s00c5_62b0 {
public:
    cTerrainSphere_s00c5_62b0* GetCurrentTerrainSphere(uint32_t key);          // 0x00f67d90
};
}
namespace SP {
cGameNounManager_s00c5_62b0* __cdecl NounManager();               // 0x00b3d300
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
struct tMissionVtblSlots {
    void*   mpMain;                                    // +0x000
    void*   mpSecondary;                               // +0x004
    uint8_t pad008[0x2c];
    void*   mpHandler;                                 // +0x034
};
}
namespace SP {
class cSPMissionHappinessEvent_s00c5_62b0 : public cSPMission_s00c5_62b0 {
public:
    void OnAcceptMission();
    int32_t Update(uint32_t delta);  // 0x00c56850 (SP::cSPMissionHappinessEvent::Update)
    void OnCompleteMission();
};
}
namespace SP {
extern void* g_vtblMissionMakeAlly[];                  // 0x0146ef48
}
namespace SP {
extern void* g_vtblMissionMakeAllySecondary[];         // 0x0146dfb4
}
namespace SP {
extern void* g_vtblMissionMakeAllyHandler[];           // 0x0146ef34
}
namespace SP {
class cMissionMakeAlly : public cSPMission_s00c5_62b0 {
public:
    int32_t mAllyEmpireID;                             // +0x1f0
    bool    mbAlliancePossible;                        // +0x1f4
    uint8_t pad1f5[3];
    cMissionMakeAlly* Construct();
    bool Init();
};
}
namespace SP {
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
}
namespace SP {
class cSPMissionTradeRoute : public cSPMission_s00c5_62b0 {
public:
    int32_t mTradeState;                               // +0x1f0
    bool    mbItemsPickedUp;                           // +0x1f4
    uint8_t pad1f5[3];
    void    GetUIShortDescription(WString* pOut);
};
}
// ---- items of slice s00c562b0 end

// ---- items of slice s00c5a580 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int intptr_t;
#define nullptr 0
struct Vec3_s00c5_a580 {
    float mX;
    float mY;
    float mZ;
};
class IRefCounted_s00c5_a580 {
public:
    virtual void AddRef();          // 0x00
    virtual void Release();         // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);   // 0x0c
    virtual void v10();
};
class IOStream {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual IOStream* GetStream();          // 0x20
    virtual void GetStream2();              // 0x24
    virtual void ReadBlock(void* pDest, int nCount);
};
class ISerializer {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual bool Serialize(void* pData);
    virtual int GetFields(int nFlags);
    virtual IOStream* GetStream();          // 0x20
    virtual uint32_t GetType();             // 0x3c
};
void ReadInt32(IOStream* pStream, void* pDest, int nCount, int bFlag);
void WriteUint32(IOStream* pStream, void* pSource, int nCount, int bFlag);
class cVarListSerializer {
public:
    cVarListSerializer(void* pOwner, const void* pFields, int nFlags);
    bool Serialize(void* pData);
    int GetFields(int nFlags);
    uint8_t mPad00[0x414];
};
class cSpatialObject : public IRefCounted_s00c5_a580 {
public:
    virtual void v14();
    virtual void v18();
    virtual Vec3_s00c5_a580* GetPosition();            // 0x1c
    virtual void v20();
    uint8_t mPad18[0x1c];
};
class cGameData : public cSpatialObject {
public:
    uint8_t mPad34[0x100];                  // 0x34 .. 0x134
};
class cEmpire : public IRefCounted_s00c5_a580 {
public:
    uint8_t mPad14[0x28];
};
class cMissionStep : public IRefCounted_s00c5_a580 {
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
class cMissionMultiStep : public cSPMission {
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
    IRefCounted_s00c5_a580** mpRewardBegin;            // 0x208
    IRefCounted_s00c5_a580** mpRewardEnd;              // 0x20c
    uint8_t mPad210[0x0c];                  // 0x210
    uint8_t* mpScheduleBegin;               // 0x21c
    uint8_t* mpScheduleEnd;                 // 0x220
    uint8_t mPad224[0x0c];                  // 0x224
    int mTargetId;                          // 0x230

    cMissionMultiStep();
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
class cTerrainEditor {
public:
    void* GetCurrentTerrainSphere();
};
cTerrainEditor* NounManager_s00c5_a580();
Vec3_s00c5_a580* GetTerrainSpherePosition();
void* GetSpaceTuning();
void* GetUniverseContext();
void* GetActivePlanet();
void CreateMissionSteps(void* pOwner);
void ResetStepSchedule();
void SetPlanetHighlight(uint32_t planetId);
void UpdateMissionStepState();
void ClearMissionUI();
void RequestMissionRefresh();
void NotifyMissionEvent(uint32_t id);
// ---- items of slice s00c5a580 end

// ---- items of slice s00c5b9c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" extern float g_elemPosX;      // 0x01691fc8
extern "C" extern float g_elemPosY;      // 0x01691fcc
extern "C" extern float g_elemPosZ;      // 0x01691fd0
typedef unsigned short     u16;
typedef unsigned char      u8;
struct Vec3_s00c5_b9c0 {
  float x, y, z;
  Vec3_s00c5_b9c0& operator=(const Vec3_s00c5_b9c0& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct cMsgServerVt {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
  virtual void Notify(void* sub, void* tag);         // vtable slot 0x20
};
void* __cdecl MessageServer();                       // 0x0067dcc0
struct SPVecU32 {
  u32* begin; u32* end; u32* cap;
  void DoInsertValue(u32* pos, const u32* val);      // 0x004558a0
};
struct cSPMission_s00c5_b9c0 {
  u32   vtbl000;                   // 0x000
  u32   vtbl004;                   // 0x004
  u32   pad008[11];                // 0x008
  u32   vtbl034;                   // 0x034
  u32   pad038[23];                // 0x038
  u32   targetEmpireID;            // 0x094
  u32   pad098[39];                // 0x098
  SPVecU32 ev134;                  // 0x134
  u32   pad140[16];                // 0x140
  void* p180;                      // 0x180
  u32   pad184[24];                // 0x184
  void* p1e4;                      // 0x1e4
  u32   pad1e8[2];                 // 0x1e8

  void  InitGeneric();             // 0x00c48e90
  void  Destroy();                 // 0x00c47680
  void* GetTargetPlanet();         // 0x00970b30
  u32   GetMissionID();            // 0x01030e10
  void  GetText(u32 tag, void* out);            // 0x00c487d0
  u8    GetTagString(u32 tag, void* out);       // 0x00c491c0
  void  OnAcceptBase();                         // 0x00c47a10
  void  HandlerComplete();                      // 0x00c46b80
  void  HandlerFail();                          // 0x00c469f0
};
struct cRaidPlunderEvent : cSPMission_s00c5_b9c0 {
  u32   f1f0, f1f4, f1f8;
  u8    b1fc; u8 pad1fd[3];
  u32   f200, f204, f208;
  float f20c, f210;
  u32   f214, f218, f21c;
};
struct cRaidEvent : cSPMission_s00c5_b9c0 {
  void* p1f0;
  u32   f1f4, f1f8, f1fc, f200, f204, f208;
  float f20c, f210;
  u8    b214, b215;
  u16   pad216;
  u32   f218;
  u8    b21c, b21d, b21e; u8 pad21f;
  u32   f220;
  Vec3_s00c5_b9c0  v224;
  u32   f230;
  u8    b234; u8 pad235[3];
  u32   f238, f23c, f240;
};
// ---- items of slice s00c5b9c0 end

// ---- items of slice s00c5e260 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vtbl { void* p[64]; };
typedef char  (__thiscall* FnC0)(void*);
typedef void  (__thiscall* FnVoid)(void*);
struct PlanetFilter {
  int  mField0;           // +0x00
  int  mPad04[0x11];      // +0x04 .. +0x47
  void FUN_00ba7bd0();    // 0x00ba7bd0 (constructor)
  void FUN_00ba8220();    // 0x00ba8220 (destructor)
};
struct TargetObj {
  void FUN_00c74690();    // 0x00c74690
};
struct Mission {
  Vtbl*   mpVtable;       // +0x000
  void*   mpField04;      // +0x004
  uint8_t mPad008[0x2c];  // +0x008 .. +0x033
  void*   mpField34;      // +0x034
  uint8_t mPad038[0x40];  // +0x038 .. +0x077
  int     mField078;      // +0x078
  uint8_t mPad07C[0xb4];  // +0x07c .. +0x12f
  uint32_t mField130;     // +0x130
  uint8_t mPad134[0x3c];  // +0x134 .. +0x16f
  uint8_t mField170[0x10];// +0x170 .. +0x17f
  void*   mpField180;     // +0x180
  uint8_t mPad184[0x6c];  // +0x184 .. +0x1ef
  int     mField1f0;      // +0x1f0
  void*   mpField1f4;     // +0x1f4
  int     mField1f8;      // +0x1f8
  int     mField1fc;      // +0x1fc

  // base helpers (addresses from the shipped binary)
  void  TriggerUIUpdate();        // 0x00c47d80
  void* GetTargetPlanet();        // 0x00970b30
  void  FUN_00c44b80();           // 0x00c44b80
  void  FUN_00c44bd0();           // 0x00c44bd0
  void  FUN_00c49f90();           // 0x00c49f90
  void  FUN_00c472e0();           // 0x00c472e0
  void  FUN_00c471c0();           // 0x00c471c0
  int   FUN_00c44cb0();           // 0x00c44cb0
  bool  IsActive();               // 0x00c44c80
  void  GetText(int id, int arg); // 0x00c487d0
  void  SetSerializer();          // 0x00c2e4e0
  bool  Init();                   // 0x00c4ad50
  int   ReadTargetPlanetType();   // 0x00c45b40
  void* GetPlanetRecordFromTargetType(int t); // 0x00c474b0
  void  FUN_00c47180(void* p);    // 0x00c47180
  int   ReadTargetAnimalSpeciesType(void* p); // 0x00c45b60
  void* GetAnimalSpeciesFromType(int t);      // 0x00c47610
  void* GetTargetPlanet(void* p, int a, int b); // 0x00970b30 (3-arg)
  void* PickPlanet(void* filter); // 0x00c47e20
  int   FUN_00c45b40();           // 0x00c45b40 (alias: ReadTargetPlanetType)
  void  FUN_00c4a0c0();           // 0x00c4a0c0
  char  FUN_00c5ea60();           // 0x00c5ea60 (see body)

  void  FUN_00c5ed90(int v);      // 0x00c5ed90
  void  FUN_00c5edb0();           // 0x00c5edb0
  void  FUN_00c5ee40();           // 0x00c5ee40
  void  FUN_00c5eed0(int arg);    // 0x00c5eed0
  void  FUN_00c5efb0(int arg);    // 0x00c5efb0
  int   FUN_00c5f090();           // 0x00c5f090
  int   FUN_00c5f0f0(int a, int b);// 0x00c5f0f0
  int   FUN_00c5f150();           // 0x00c5f150
  void  FUN_00c5f250();           // 0x00c5f250
  void  FUN_00c5f280();           // 0x00c5f280
  void  FUN_00c5f2c0();           // 0x00c5f2c0
  void  FUN_00c5f360();           // 0x00c5f360
  int   FUN_00c5f3d0();           // 0x00c5f3d0
  int   FUN_00c5f4e0(int id);     // 0x00c5f4e0
};
struct MissionScan : Mission {
  MissionScan();                  // 0x00c5e740
};
void __fastcall MissionBaseCtor(void* self);
// ---- items of slice s00c5e260 end

// @ 0x00c50940
void __fastcall FUN_00c50940(void* ecx_this, void* edx)
{
    (void)edx;
    Mob* self = (Mob*)ecx_this;
    self->Unk47a10();
    void* tp = self->GetTargetPlanet();
    void* ap = FUN_01021260();
    if (ap == tp) {
        if (FUN_01021080() == 0)
            self->OnPlanetActivate();
    }
}

// @ 0x00c54e50
bool FindNearestNoun(void* out, Key* pKey)
{
    void* v = GetNounManager_()->GetDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                           (void*)0x00accc30, (void*)0x00b1e500, 0x1be418e);
    float best = *(float*)0x0146e760;                // FLT_MAX
    int count = (*(int*)((char*)v + 8) - *(int*)((char*)v + 4)) >> 2;
    void* inv = GetUFOSim()->GetPlayerInventory();
    const float* invPos = (const float*)((char*)inv + 0x718);
    for (int i = 0; i < count; ++i) {
        NearNoun* noun = *(NearNoun**)(*(int*)((char*)v + 4) + i * 4);
        Key* k = (Key*)(*(int*)((char*)noun + 0xa4) + 0x504);
        if (k->a != pKey->a || k->b != pKey->b || k->c != pKey->c)
            continue;
        float* p = (float*)noun->GetPosition();
        float dy = p[1] - invPos[1];
        float dx = p[0] - invPos[0];
        float dz = p[2] - invPos[2];
        float d2 = dz * dz + dy * dy + dx * dx;
        if (best > d2) {
            best = d2;
            NearNoun* noun2 = *(NearNoun**)(*(int*)((char*)v + 4) + i * 4);
            float* p2 = (float*)noun2->GetPosition();
            *(Vec3*)out = *(Vec3*)p2;
        }
    }
    return best != *(float*)0x0146e760;
}

// @ 0x00c55130
cMissionFindAliens::cMissionFindAliens()
{
    BaseCtor();
    mnFindAliensState = 0;
    mnNumAliensToFind = 0;
    mnNumAliensFound = 0;
    mbContactGrob = false;
    mpVftable = &gVtableFindAliens;
    mpVftable2 = &gVtableFindAliensUnk;
    mpVftable3 = &gVtableFindAliensExtra;
}

// @ 0x00c568d0
namespace SP {
void cSPMissionHappinessEvent_s00c5_62b0::OnCompleteMission()
{
    WString text;
    GetText(0x25594ea8, &text);
    uint32_t eventID = EventLog()->PostFeedbackEvent(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
    EventLog()->ModifyEventText(eventID, text.mpBegin);

    cPlanet_s00c5_62b0* pPlanet = GetTargetPlanet();
    pPlanet->mPendingEventCount--;

    FUN_00c46b80();
    text.Release();
}
}  // namespace SP

// @ 0x00c56970
namespace SP {
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
}  // namespace SP

// @ 0x00c56ac0
namespace SP {
bool cMissionMakeAlly::Init()
{
    if (!cSPMission_s00c5_62b0::Init())
        return false;
    FUN_00c4a0c0();
    return true;
}
}  // namespace SP

// @ 0x00c56b20
namespace SP {
void cMsgHandler::HandleMessage(uint32_t message, void* data)
{
    // the handler is a secondary base sub-object of the mission, stored at mission+0x34
    if (message == 0x5fa2448) {
        mbAlliancePossible = true;
        cTerrainSphere_s00c5_62b0* pSphere = NounManager()->GetCurrentTerrainSphere(0x5fa31f4);
        if (!pSphere->FUN_00c772c0())
            FUN_01041c50("SPG_FirstAlliancePossible", 0x5fa31f4, 1);
        cSPMission_s00c5_62b0* pMission = (cSPMission_s00c5_62b0*)((char*)this - 0x34);
        pMission->TriggerUIUpdate();
    }
    HandleMessageSuper(message, data);
}
}  // namespace SP

// @ 0x00c56bd0
namespace SP {
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
}  // namespace SP

// @ 0x00c5ad40
cMissionMultiStep::cMissionMultiStep()
{
    mpStepsBegin = nullptr;
    mpStepsEnd = nullptr;
    mpStepsCap = nullptr;
    mCurrentStepIndex = -1;
    mpRewardBegin = nullptr;
    mpRewardEnd = nullptr;
    mpScheduleBegin = nullptr;
    mpScheduleEnd = nullptr;
    mTargetId = 0;
    CreateMissionSteps(nullptr);
    ResetStepSchedule();
}

// @ 0x00c5ae30
bool cMissionMultiStep::Write(void* pData)
{
    IOStream* pStream = ((ISerializer*)pData)->GetStream();
    uint32_t nType = 0x5626b91;
    WriteUint32(pStream->GetStream(), &nType, 1, 0);

    cVarListSerializer serializer(this, (const void*)0x01576840, 0x1a80d26);
    return serializer.Serialize(pData) != 0;
}

// @ 0x00c5aea0
bool cMissionMultiStep::Read(void* pData)
{
    IOStream* pStream = ((ISerializer*)pData)->GetStream();
    uint32_t nType = 0;
    ReadInt32(pStream->GetStream(), &nType, 1, 0);

    cVarListSerializer serializer(this, (const void*)0x01576840, 0x1a80d26);
    return serializer.Serialize(pData) != 0;
}

// @ 0x00c5b020
void cMissionMultiStep::UpdateFromTerrainSphereA()
{
    UpdateMissionStepState();

    cTerrainEditor* pEditor = NounManager_s00c5_a580();
    ((IRefCounted_s00c5_a580*)pEditor->GetCurrentTerrainSphere())->v10();

    pEditor = NounManager_s00c5_a580();
    pEditor->GetCurrentTerrainSphere();
    Vec3_s00c5_a580* pPosition = GetTerrainSpherePosition();
    mpStepsBegin = *(cMissionStep***)pPosition;
    mpStepsEnd = *(cMissionStep***)((uint8_t*)pPosition + 4);
    mpStepsCap = *(cMissionStep***)((uint8_t*)pPosition + 8);

    void* pTuning = GetSpaceTuning();
    if (!((ISerializer*)pTuning)->Serialize(&mpStepsBegin))
        ClearMissionUI();
}

// @ 0x00c5b0b0
void cMissionMultiStep::UpdateFromTerrainSphereB()
{
    ResetStepSchedule();

    cTerrainEditor* pEditor = NounManager_s00c5_a580();
    pEditor->GetCurrentTerrainSphere();
    Vec3_s00c5_a580* pPosition = GetTerrainSpherePosition();
    mpStepsBegin = *(cMissionStep***)pPosition;
    mpStepsEnd = *(cMissionStep***)((uint8_t*)pPosition + 4);
    mpStepsCap = *(cMissionStep***)((uint8_t*)pPosition + 8);

    void* pTuning = GetSpaceTuning();
    if (!((ISerializer*)pTuning)->Serialize(&mpStepsBegin))
        ClearMissionUI();
}

// @ 0x00c5b130
void RefreshTargetPlanet()
{
    cSPMission* pMission = nullptr;
    uint32_t nPlanet = pMission->GetTargetPlanet();
    SetPlanetHighlight(nPlanet);
    RequestMissionRefresh();
}

// @ 0x00c5b150
void RefreshTargetPlanetConditional(cSPMission* pMission)
{
    uint32_t nPlanet = pMission->GetTargetPlanet();
    SetPlanetHighlight(nPlanet);

    if (GetUniverseContext() == nullptr) {
        if (pMission->GetTargetPlanet() == (uint32_t)(intptr_t)GetActivePlanet()) {
            RequestMissionRefresh();
            return;
        }
    }
    NotifyMissionEvent(0);
}

// @ 0x00c5bc30
cRaidPlunderEvent* __fastcall FUN_00c5bc30(cRaidPlunderEvent* self, void* dummy)
{
  (void)dummy;
  self->InitGeneric();
  self->vtbl000 = 0x0146f6b0;
  self->vtbl004 = 0x0146f6a0;
  self->vtbl034 = 0x0146f690;
  self->f1f0 = 0;
  self->f1f4 = 0;
  self->f1f8 = 0;
  self->b1fc = 0;
  self->f200 = 0;
  self->f204 = 0;
  self->f208 = 0;
  self->f20c = 0.0f;
  self->f210 = 0.0f;
  self->f214 = 0;
  self->f218 = 0;
  self->f21c = 0;
  return self;
}

// @ 0x00c5bd40
cRaidEvent* __fastcall FUN_00c5bd40(cRaidEvent* self, void* dummy)
{
  (void)dummy;
  self->InitGeneric();
  self->vtbl000 = 0x0146f898;
  self->vtbl004 = 0x0146f888;
  self->vtbl034 = 0x0146f878;
  self->p1f0 = 0;
  self->f1f4 = 0;
  self->f1f8 = 0;
  self->f1fc = 0;
  self->f200 = 0;
  self->f204 = 0;
  self->f208 = 0;
  self->f20c = 0.0f;
  self->f210 = 0.0f;
  self->b214 = 0;
  self->f218 = 0;
  self->b21c = 0;
  self->b21d = 0;
  self->f220 = 0;
  {
    void* sub = &self->vtbl034;
    self->b215 = self->b21e = 1;
    self->v224.x = g_elemPosX;
    self->v224.y = g_elemPosY;
    self->v224.z = g_elemPosZ;
    self->f230 = 0xffffffff;
    self->b234 = 0;
    self->f238 = 0;
    self->f23c = 0;
    self->f240 = 0;
    ((cMsgServerVt*)MessageServer())->Notify(sub, (void*)0x01622184);
  }
  return self;
}

// @ 0x00c5e740
MissionScan::MissionScan()
{
  MissionBaseCtor(this);
  mpVtable  = (Vtbl*)0x146fc00;
  mpField04 = (void*)0x146dfb4;
  mpField34 = (void*)0x146fbf0;
  mField1f0 = 0;
  mpField1f4 = (void*)*(int*)0x16925c0;
  mField1f8 = *(int*)0x16925c4;
  mField1fc = *(int*)0x16925c8;
}

// @ 0x00c5ea60
char Mission::FUN_00c5ea60()
{
  if (!Init())
    return 0;

  int t = FUN_00c45b40();
  void* rec = GetPlanetRecordFromTargetType(t);
  if (rec != 0)
    FUN_00c47180(rec);

  uint32_t raw = *(volatile uint32_t*)&mField130;
  raw >>= 3;
  if ((raw & 1) != 0 && (uint32_t)mField078 == 0x89238409u) {
    void* p = (void*)((char*)this + 0x170);
    int species = ReadTargetAnimalSpeciesType(p);
    GetAnimalSpeciesFromType(species);
    void* obj = GetTargetPlanet(p, 0, 0);
    ((TargetObj*)obj)->FUN_00c74690();
  }

  if (GetTargetPlanet() == 0) {
    PlanetFilter filter;
    filter.FUN_00ba7bd0();
    filter.mField0 = 0x38;
    void* picked = PickPlanet(&filter);
    if (picked == 0) {
      filter.FUN_00ba8220();
      return 0;
    }
    FUN_00c47180(picked);
    filter.FUN_00ba8220();
  }

  if (((FnC0)mpVtable->p[0x128 / 4])(this) == '\0')
    return 0;
  FUN_00c4a0c0();
  ((FnVoid)mpVtable->p[0x170 / 4])(this);
  return 1;
}
