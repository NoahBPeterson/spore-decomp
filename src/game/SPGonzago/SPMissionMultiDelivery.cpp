// src/game/SPGonzago/SPMissionMultiDelivery.cpp -- migrated from slice(s) s00c59540, s00c58920, s00c57570, s00c562b0, s00c4a850 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionMultiDelivery.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_13ebb38[];
extern "C" char g_13f01bc[];
extern "C" char g_13f09b4[];
extern "C" char g_146f174[];
extern "C" char g_146f184[];
extern "C" char g_146f198[];
extern "C" char g_16919c4[];
extern "C" char g_16919c8[];
extern "C" char g_16919cc[];

#include "game/types.h"
#include "SP/cGameData.h"
#include "SP/cPlanet.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cSPMission.h"
#include "SP/cStarManager.h"
#include "SP/cVarListSerializer.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cCity.h"
#include "SP/cCivData.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPGenericPressureEvent.h"
#include "SP/cSPMissionHappinessEvent.h"
#include "SP/cTerrainSphere.h"
#include "SP/cSPMissionBase.h"
#include "SP/cPlanetModel.h"
#include "SP/cStarRecord.h"
#include <math.h>

// ---- items of slice s00c4a850 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ResourceKey {
    uint32_t mInstanceID;                                   // +0x00
    uint32_t mGroupID;                                      // +0x04
    uint32_t mTypeID;                                       // +0x08
};
template <class T>
struct cVec {
    T*       mpBegin;                                       // +0x00
    T*       mpEnd;                                         // +0x04
    T*       mpCapacity;                                    // +0x08
    void*    mpAllocator;                                   // +0x0c
    uint32_t mPad10;                                        // +0x10

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T&       operator[](uint32_t nIndex) const { return mpBegin[nIndex]; }

    void     push_back(const T& rValue)
    {
        if (mpEnd != mpCapacity) {
            T* pSlot = mpEnd;
            ++mpEnd;
            if (pSlot)
                *pSlot = rValue;
            return;
        }
        DoInsertValue(mpEnd, rValue);
    }

    void     DoInsertValue(T* pPos, const T& rValue);       // 0x00aea5d0
};
struct cPlanet {
    char     mPad000[0x13c];                                // +0x000
    void*    mpData13C;                                     // +0x13c
    char     mPad140[0x2c];                                 // +0x140
};
struct cPlanetRecord;
struct cProperty {
    void*     mpValue;                                      // +0x00
    uint32_t  mPad04;                                       // +0x04
    uint32_t  mCount;                                       // +0x08
    uint32_t  mPad0c;                                       // +0x0c
    uint16_t  mFlags;                                       // +0x10
    uint16_t  mType;                                        // +0x12

    bool*     GetBool();                                    // 0x0041e920
    int32_t*  GetInt();                                     // 0x0041e990
};
struct cPropertyList {
    virtual void        v00();                              // +0x00
    virtual void        v04();                              // +0x04
    virtual void        v08();                              // +0x08
    virtual void        v0c();                              // +0x0c
    virtual void        v10();                              // +0x10
    virtual void        v14();                              // +0x14
    virtual void        v18();                              // +0x18
    virtual void        v1c();                              // +0x1c
    virtual void        v20();                              // +0x20
    virtual bool        Find(uint32_t nKey, cProperty** ppOut);   // +0x24
    virtual cProperty*  Get(uint32_t nKey);                 // +0x28
};
struct cSPMission;
struct cSPMissionMultiDelivery;
struct cPlanetSearch;
struct cSPMission {
    // vtable +0x00 (slots used by this slice: +0x6c, +0x128, +0x16c, +0x170, +0x188)
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
    virtual void Abort();                                   // +0x06c
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
virtual void v0a4();
virtual void v0a8();
virtual void v0ac();
virtual void v0b0();
virtual void v0b4();
virtual void v0b8();
virtual void v0bc();
virtual void v0c0();
virtual void v0c4();
virtual void v0c8();
virtual void v0cc();
virtual void v0d0();
virtual void v0d4();
virtual void v0d8();
virtual void v0dc();
virtual void v0e0();
virtual void v0e4();
virtual void v0e8();
virtual void v0ec();
virtual void v0f0();
virtual void v0f4();
virtual void v0f8();
virtual void v0fc();
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
    virtual bool CheckTargetValid();                        // +0x128
virtual void v12c();
virtual void v130();
virtual void v134();
virtual void v138();
virtual void v13c();
virtual void v140();
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
    virtual void OnMissionStarted();                        // +0x16c
    virtual void OnMissionSucceeded();                      // +0x170
virtual void v174();
virtual void v178();
virtual void v17c();
virtual void v180();
    virtual void v184();
    virtual void OnPropertiesLoaded();                      // +0x188

    char           mPad004[0x12c];                          // +0x004 .. +0x12f
    uint32_t       mFlags;                                  // +0x130
    char           mPad134[0x4c];                           // +0x134 .. +0x17f
    cPropertyList* mpPropertyList;                          // +0x180
    int32_t        mField184;                               // +0x184
    int32_t        mField188;                               // +0x188
    char           mPad18c[4];                              // +0x18c
    int32_t        mField190;                               // +0x190
    cVec<ResourceKey> mKeys194;                             // +0x194
    cVec<ResourceKey> mKeys1a8;                             // +0x1a8
    cVec<ResourceKey> mKeys1bc;                             // +0x1bc
    char           mPad1d0[0x20];                           // +0x1d0 .. +0x1ef
    int32_t        mStatus;                                 // +0x1f0
    void*          mpData1f4;                               // +0x1f4
    char           mPad1f8[0xc];                            // +0x1f8 .. +0x203
    int32_t        mField204;                               // +0x204
    int32_t        mField208;                               // +0x208

    char           Init();                                  // 0x00c4ad50
    void           PickGiveOnAcceptItems();                 // 0x00c4a980
    cPlanet*       GetTargetPlanet();                       // 0x00970b30
    void           SetTargetPlanet(void* pPlanet);          // 0x00c47180
    void           SetInitialized();                        // 0x00c4a0c0
    void           TriggerUIUpdate();                       // 0x00c47d80
    int32_t        Update(void* pArg);                      // 0x00c478b0
    void*          PickPlanet(cPlanetSearch* pSearch);      // 0x00c47e20
    uint32_t       ReadTargetPlanetType();                  // 0x00c45b40
    cPlanetRecord* GetPlanetRecordFromTargetType(uint32_t nType);   // 0x00c474b0
};
struct cSPMissionMultiDelivery : cSPMission {
    void    ReturnForRewards();                             // 0x00c4b760
    int32_t Update(void* pArg);                             // 0x00c4b7a0
    bool    IsAtDeliveryTarget(void* pPlanet, ResourceKey* pKey);   // 0x00c4bb60
    bool    InitWrapper();                                  // 0x00c4baa0
    int32_t GetCountA();                                    // 0x00c4bba0
    int32_t GetCountB();                                    // 0x00c4bbc0
};
struct cPlanetSearch {                                      // pick request built by cMissionBalance::Init
    uint32_t mKind;                                         // +0x00 (0x20 / 0x38)
    char     mPad004[0x40];                                 // +0x004

    cPlanetSearch();                                        // 0x00ba7bd0
    ~cPlanetSearch();                                       // 0x00ba8220
};
void   __fastcall FUN_00c472e0(cSPMission* pThis);                      // 0x00c472e0
void   __fastcall FUN_00c471c0(cSPMission* pThis);                      // 0x00c471c0
// ---- items of slice s00c4a850 end

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
template <class T> const T& min_ref(const T& a, const T& b) { return b < a ? b : a; }
}
namespace SP {
struct cProperty_s00c5_62b0;
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
struct cProperty_s00c5_62b0 {
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
    virtual bool       GetProperty(uint32_t key, cProperty_s00c5_62b0** out);      // 0x24
    virtual cProperty_s00c5_62b0* GetPropertyRef(uint32_t key);                    // 0x28
};
}
namespace SP {
class cPropertyManager_s00c5_62b0 {
public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0c();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1c();
virtual void slot20();
virtual void slot24();
virtual void slot28();
    virtual bool GetProperty(const void* itemDefinition, uint32_t key, cProperty_s00c5_62b0** out);   // +0x2c
};
}
namespace SP {
cPropertyManager_s00c5_62b0* __cdecl PropertyManager();           // 0x0067de30
}
namespace SP {
void __cdecl GetPropertyAsText(cProperty_s00c5_62b0* pProperty, uint32_t key, WString* out);   // 0x006a1360
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
cEmpire_s00c5_62b0* __cdecl FUN_01021300();                       // 0x01021300 player empire
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
class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t range);      // 0x00a68fb0
};
}
namespace SP {
extern RandomLinearCongruential g_spRandom;            // 0x01601760
}
namespace SP {
struct IArchiveWriter : VPad<6, IEmpty> {
    virtual void* GetStream();                                     // +0x18
};
}
namespace SP {
struct IArchiver0 : VPad<6, IEmpty> {
    virtual void* GetStream();                                     // +0x18
    virtual void* EndRead();                                       // +0x1c
};
}
namespace SP {
struct IArchiver : IArchiver0 {
    virtual IArchiveWriter* GetWriter();                           // +0x20
    virtual void* ReadItem(uint32_t typeID, void* pItem, int32_t flag);   // +0x24
    virtual void* SerializeItem(uint32_t typeID, void* pItem, int32_t flag); // +0x28
    virtual void* SerializeObject(void* pObject);                  // +0x2c
};
}
namespace SP {
void __cdecl EA_ReadInt32(void* pStream, void* pOut, int32_t count, int32_t flag);       // 0x0093a780
}
namespace SP {
struct tItemInfo {                                     // 0xc-byte "requested"/"delivered" record
    AutoRefCount<cPlanet_s00c5_62b0> mpPlanet;                    // +0x00
    int32_t               mRequested;                  // +0x04
    int32_t               mDelivered;                  // +0x08
};
}
namespace SP {
struct tPickupInfo {                                   // 0x14-byte buyer-request record
    AutoRefCount<cPlanet_s00c5_62b0> mpPlanet;                    // +0x00
    uint8_t               pad004[0x0c];
    bool                  mbPickedUp;                  // +0x10
    uint8_t               pad011[3];
};
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
    uint8_t      pad080[0x0c];
    int32_t      mPoliticalID_8c;                      // +0x08c
    uint8_t      pad090[0x0c];
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
    void   FUN_00c48d40(WString* pOut);                // 0x00c48d40
    bool   FUN_00c455b0(int a, int b);                 // 0x00c455b0
    void   FUN_00c45cf0(cPlanet_s00c5_62b0* pPlanet);             // 0x00c45cf0
    bool   FUN_00c45d80(void* pStarRecord);            // 0x00c45d80
    void   FUN_00c466d0();                             // 0x00c466d0
    void   FUN_00c46b80();                             // 0x00c46b80
    void   FUN_00c48e50(uint32_t eventID);             // 0x00c48e50
    void   FUN_00c4a0c0();                             // 0x00c4a0c0
};
}
namespace SP {
class cSPMissionMultiDelivery_s00c5_62b0 : public cSPMission_s00c5_62b0 {
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
}
// ---- items of slice s00c562b0 end

// ---- items of slice s00c57570 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
class wstring {
public:
    void assign(const wchar_t* pFirst, const wchar_t* pLast); // 0x00423650
};  // namespace eastl
}
namespace SP {
class cMissionTarget {
public:
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
    virtual void NotifyContext(void* pContext);          // +0x1c
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
virtual void v0a4();
virtual void v0a8();
virtual void v0ac();
virtual void v0b0();
virtual void v0b4();
virtual void v0b8();
    virtual void NotifyAssigned();                       // +0xbc
    virtual void ReleaseTarget();                        // +0xc0
};
}
namespace SP {
struct tBuyerInfo {
    cMissionTarget* mpTarget;                            // +0x00
    int32_t         mField4;                             // +0x04
    int32_t         mField8;                             // +0x08

    tBuyerInfo* operator=(const tBuyerInfo& src);
};
}
namespace SP {
union FloatBits {
    float    f;
    uint32_t u;
};
struct Float3 {
    FloatBits x, y, z;
};
struct tItemInfo_s00c5_7570 {
    cMissionTarget* mpTarget;                            // +0x00
    Float3          mFields;                             // +0x04 (three floats through +0x0f)
    bool            mField10;                            // +0x10

    tItemInfo_s00c5_7570* operator=(const tItemInfo_s00c5_7570& src);
    tItemInfo_s00c5_7570* FUN_00c57720(const tItemInfo_s00c5_7570& src);
    tItemInfo_s00c5_7570* FUN_00c57a80(cMissionTarget* pTarget, bool flag, float f1, float f2, float f3);
};
}
namespace SP {
struct cBuyerRange {
    tBuyerInfo* mpBegin;                                 // +0x00
    tBuyerInfo* mpEnd;                                   // +0x04
};
}
namespace SP {
struct cItemRange {
    tItemInfo_s00c5_7570*  mpBegin;                                 // +0x00
    tItemInfo_s00c5_7570*  mpEnd;                                   // +0x04
};
}
namespace SP {
struct cDeliveryItemRange {
    tItemInfo* mpBegin;
    tItemInfo* mpEnd;
};
struct cPickupRange {
    tPickupInfo*  mpBegin;                                 // +0x00
    tPickupInfo*  mpEnd;                                   // +0x04
};
}
namespace SP {
bool __cdecl EA_WriteUint32(void* pStream, const void* pValue, int32_t count, int32_t flag); // 0x0093aa70
bool __cdecl EA_WriteBool8(void* pStream, const bool* pValue, int32_t count); // 0x0093a9a0
}
namespace SP {
IArchiver& __cdecl operator<<(IArchiver& archiver, const tItemInfo_s00c5_7570& item);             // 0x00c56e60
IArchiver& __cdecl operator<<(IArchiver& archiver, const tItemInfo& item); // 0x00c56e60
IArchiver& __cdecl operator<<(IArchiver& archiver, const tPickupInfo& item);                      // 0x00c56e00
inline uint32_t EA_STLSequenceCount(const cItemRange* pRange)
{
    return (uint32_t)((char*)pRange->mpEnd - (char*)pRange->mpBegin) / 12;
}
inline uint32_t EA_STLSequenceCount(const cPickupRange* pRange)
{
    return (uint32_t)((char*)pRange->mpEnd - (char*)pRange->mpBegin) / 20;
}
}
namespace SP {
class cString_s006b_47a0 {
public:
    const wchar_t* GetText();                            // 0x006b55c0
};
}
namespace SP {
class cSPMissionMultiDelivery_s00c5_7570 {
public:
    int32_t GetDynamicResponseID(int arg1, int arg2);  // 0x00c57d00 (SP::cSPMissionMultiDelivery::GetDynamicResponseID)
    int32_t OnDelivery(int arg1, void* pPlanet);  // 0x00c57ef0 (SP::cSPMissionMultiDelivery::OnDelivery)
    void  GetFetchItemName(eastl::wstring* pOut);  // 0x00c58260 (SP::cSPMissionMultiDelivery::GetFetchItemName)
    void  FUN_00c575e0();
    void  FUN_00c576d0();
    void  FUN_00c57720();
    void  FUN_00c57780();
    void  FUN_00c57810();
    void  FUN_00c57930();
    void  FUN_00c57a10();
    void  FUN_00c57a80();
    void  FUN_00c57ad0();
    bool  FUN_00c57e50(int arg1, int arg2);
    void  FUN_00c582a0(WString* out);
    void  FUN_00c58310(void* value);
    void  FUN_00c58360(void* value);
    void* FUN_00c58530(int32_t flags);
    void  FUN_00c58600();

    uint8_t             pad000[0x23c];                   // +0x000 .. +0x23b
    cString_s006b_47a0  mFetchItemName;                  // +0x23c
};
}
// ---- items of slice s00c57570 end

// ---- items of slice s00c58920 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sqrt)
typedef unsigned char      u8;
typedef unsigned int       u32;
typedef int                i32;
typedef float              f32;
typedef unsigned short     wchar_t_;
static inline float InlineSqrt(float x) { return (float)sqrt((double)x); }
template <int N, class B> struct VPad_s00c5_8920 : VPad_s00c5_8920<N - 1, B> { virtual void vpad(VPad_s00c5_8920<N, B>*) {} };
template <class B> struct VPad_s00c5_8920<0, B> : B {};
struct IEmpty_s00c5_8920 {};
extern u8 gEmptyString16[];                     // 0x01667bac
void __cdecl WFree(void* block);                // 0x00f47380  operator delete
struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
};
struct cWString {
    void* mpBegin;                      // 0x00
    void* mpEnd;                        // 0x04
    void* mpCap;                        // 0x08
    u32   mPad0c;                       // 0x0c (sizeof == 0x10 in retail)

    cWString()
        : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCap(gEmptyString16 + 2) {}

    // Release the heap buffer unless this is the shared static empty string.
    void Release()
    {
        u32 bytes = (u32)((char*)mpCap - (char*)mpBegin) & 0xfffffffeu;
        if (bytes > 2 && mpBegin != 0)
            WFree(mpBegin);
    }

    void assign(const void* first, const void* last);  // 0x00423650
};
struct IRefCounted_s00c5_8920 : VPad_s00c5_8920<47, IEmpty_s00c5_8920> {
    virtual int AddRef();               // +0xbc
    virtual int Release();              // +0xc0
};
struct SpAllocHeader {
    u32 mCount;
};
inline bool SpIsOwned(const void* p)
{
    if (p == 0)
        return false;
    return ((const SpAllocHeader*)p)[-1].mCount != 0;
}
struct cPlanetVector {
    struct cPlanet_s00c5_8920** mpBegin;           // 0x00
    struct cPlanet_s00c5_8920** mpEnd;             // 0x04
    struct cPlanet_s00c5_8920** mpCap;             // 0x08
};
struct cStarRecord {
    virtual int AddRef();               // +0x00
    virtual int Release();              // +0x04
    u8          mPad004[0x38];
    Vec3        mPosition;              // +0x3c
    u8          mPad048[0x14];
    u32         mFlags;                 // +0x5c
    cWString    mName;                  // +0x60
    u32         mField70;               // +0x70

    const Vec3& GetPosition();           // 0x005c65e0
    cWString*   GetName();               // 0x00bb9de0
    bool        TestFlag(u32 mask);      // 0x00bb9af0
    cPlanetVector* GetPlanets();         // 0x00bba790
};
struct cPlanetModel {
    u8          mPad000[0x18];
    u8          mPad018[0x16c];
    u32         mStarRecordID;           // +0x184
    cStarRecord* SortBanners();          // 0x00b8de30
};
struct cPlanet_s00c5_8920 {
    u8           mPad000[0x28];
    u32          mField28;               // +0x28
    u8           mPad02c[0x110];
    cPlanetModel* mpModel;               // +0x13c

    cWString* GetName();                 // 0x00c707e0
    i32       FUN_00b8d9b0();            // 0x00b8d9b0
};
struct tBuyerInfo_s00c5_8920 {
    IRefCounted_s00c5_8920* mpObject;              // +0x00
    u32          mField4;               // +0x04
    u32          mField8;               // +0x08
};
struct tItemInfo_s00c5_8920 {
    IRefCounted_s00c5_8920* mpObject;              // +0x00
    Vec3         mPosition;             // +0x04
    bool         mFlag;                 // +0x10
    u8           mPad011[3];

    tItemInfo_s00c5_8920* FUN_00c57a80(void* target, i32 flag, Vec3 position);  // 0x00c57a80
};
struct cBuyerVector {
    tBuyerInfo_s00c5_8920* mpBegin;                // 0x00
    tBuyerInfo_s00c5_8920* mpEnd;                  // 0x04
    tBuyerInfo_s00c5_8920* mpCap;                  // 0x08

    void erase(tBuyerInfo_s00c5_8920* first, tBuyerInfo_s00c5_8920* last);            // 0x00c58590
    void reserve(u32 count);                                    // 0x00c583b0
    void DoInsertValue(tBuyerInfo_s00c5_8920* end, const tBuyerInfo_s00c5_8920* value); // 0x00c58600

    void push_back(const tBuyerInfo_s00c5_8920& value)
    {
        if (mpEnd < mpCap) {
            tBuyerInfo_s00c5_8920* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot) {
                slot->mpObject = value.mpObject;
                if (slot->mpObject)
                    slot->mpObject->AddRef();
                slot->mField4 = value.mField4;
                slot->mField8 = value.mField8;
            }
        } else {
            DoInsertValue(mpEnd, &value);
        }
    }
};
struct cItemVector {
    tItemInfo_s00c5_8920* mpBegin;                 // 0x00
    tItemInfo_s00c5_8920* mpEnd;                   // 0x04
    tItemInfo_s00c5_8920* mpCap;                   // 0x08

    void erase(tItemInfo_s00c5_8920* first, tItemInfo_s00c5_8920* last);              // 0x00c58770
    void reserve(u32 count);                                    // 0x00c58470
    void DoInsertValue(tItemInfo_s00c5_8920* end, const tItemInfo_s00c5_8920* value);  // 0x00c587e0
    void Add(tItemInfo_s00c5_8920* value);                                 // 0x00c58ee0

    i32 size() const { return (i32)((u8*)mpEnd - (u8*)mpBegin) / 0x14; }

    void push_back(const tItemInfo_s00c5_8920& value)
    {
        if (mpEnd < mpCap) {
            tItemInfo_s00c5_8920* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot) {
                slot->mpObject = value.mpObject;
                if (slot->mpObject)
                    slot->mpObject->AddRef();
                slot->mPosition.x = value.mPosition.x;
                slot->mPosition.y = value.mPosition.y;
                slot->mPosition.z = value.mPosition.z;
                slot->mFlag = value.mFlag;
            }
        } else {
            DoInsertValue(mpEnd, &value);
        }
    }
};
struct cPointerVector {
    void** mpBegin;                     // 0x00
    void** mpEnd;                       // 0x04
    void** mpCap;                       // 0x08

    void DoInsertValue(void** end, void* const* value);          // 0x004558a0

    void push_back(void* const& value)
    {
        if (mpEnd < mpCap) {
            void** slot = mpEnd;
            mpEnd = slot + 1;
            if (slot)
                *slot = value;
        } else {
            DoInsertValue(mpEnd, &value);
        }
    }
};
struct cFloatVector {
    f32* mpBegin;                       // 0x00
    f32* mpEnd;                         // 0x04
    f32* mpCap;                         // 0x08

    void reserve(u32 count);                                    // 0x004e0880
    void DoInsertValue(f32* end, const f32* value);              // 0x00455660

    void push_back(const f32& value)
    {
        if (mpEnd < mpCap) {
            f32* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot)
                *slot = value;
        } else {
            DoInsertValue(mpEnd, &value);
        }
    }
};
struct IArchiveWriter_s00c5_8920 : VPad_s00c5_8920<6, IEmpty_s00c5_8920> {
    virtual void* GetStream();                                   // +0x18
};
struct IArchiver_s00c5_8920 : VPad_s00c5_8920<7, IEmpty_s00c5_8920> {
    virtual IArchiver_s00c5_8920& EndRead();                                // +0x1c
    virtual IArchiveWriter_s00c5_8920* GetWriter();                         // +0x20
    virtual void* FUN_0024();                                    // +0x24
    virtual void* SerializeItem(u32 typeID, void* item, i32 flag); // +0x28
};
bool __cdecl ReadInt32(void* pStream, void* pOut, i32 count, i32 flag);  // 0x0093a780
bool __cdecl ReadBool(void* pStream, bool* pOut);                        // 0x0093ac80
IArchiver_s00c5_8920& __cdecl operator>>(IArchiver_s00c5_8920& ar, tBuyerInfo_s00c5_8920& info);          // 0x00c56de0
struct VEffect : VPad_s00c5_8920<16, IEmpty_s00c5_8920> {
    virtual void FUN_0040(i32 id, const Vec3* values, i32 count);    // +0x40
    virtual void FUN_0044(i32 id, const f32* values, i32 count);     // +0x44
};
struct cStarMap {
    VEffect* CreateStarRecordVisual(cStarRecord* record, u32 type, u32 param); // 0x010458f0
    void     AddVisual(VEffect* visual, i32 flag);                            // 0x01044d70
    VEffect* FUN_01045120(u32 starID, VEffect* visual);                      // 0x01045120
    void     RemoveVisual(i32 handle, i32 flag);                             // 0x01045a60
};
cStarMap* __cdecl GetStarMap();                     // 0x01046fc0
struct cStarManager {
    void GetStarRecords(const Vec3& position, const struct tStarSearchCriteria& criteria,
                        struct cRefVector& out);                 // 0x00bb1080
    void ActivatePlanetRecordsForQuery(cStarRecord* record, i32 flag); // 0x00bb4af0
    void GetOrActivatePlanet(cPlanet_s00c5_8920* planet, void** out);           // 0x00bb59b0
};
cStarManager* __cdecl StarManager();                // 0x00b3d2a0
cPlanet_s00c5_8920* __cdecl GetPlayerHomePlanet();             // 0x01021370
struct cSPSimulatorPlayerUFO {
    f32 GetMaxTravelDistance();                     // 0x00ffbfc0
};
cSPSimulatorPlayerUFO* __cdecl GetUFOSimulator_s00c5_8920();   // 0x00ffbe50
struct cMissionManager {
    i32 FUN_00febf80(void* p);                      // 0x00febf80 (ret 4)
};
cMissionManager* __cdecl GetMissionManager();       // 0x00feb9f0
struct RandomLinearCongruential_s00c5_8920 {
    u32 RandomUint32Uniform(u32 range);             // 0x00a68fb0
};
RandomLinearCongruential_s00c5_8920 gRandom;                   // 0x01601760
extern Vec3 gDefaultPosition;                       // 0x016919b8
extern f32  gNegTen;                                // 0x013f561c
struct tStarSearchCriteria {
    u32   mAcceptableStarTypes;         // +0x00  0x1ff1
    u32   mAcceptableSolarTech;         // +0x04  0x3e
    u32   mMiscFilters;                 // +0x08
    f32   mMinRange;                    // +0x0c
    f32   mMaxRange;                    // +0x10
    f32   mMaxTravel;                   // +0x14
    u32   mNumJumps;                    // +0x18
};
struct cRefVector {
    cStarRecord** mpBegin;              // 0x00
    cStarRecord** mpEnd;                // 0x04
    cStarRecord** mpCap;                // 0x08

    cRefVector() : mpBegin(0), mpEnd(0), mpCap(0) {}
};
struct cSPMissionMultiDelivery_s00c5_8920 {
    u8               mPad0000[0x9c];
    cPlanet_s00c5_8920*         mpActivePlanet;    // 0x09c
    u8               mPad0a0[0x68];
    cPointerVector   mVisualVec;        // 0x108
    u8               mPad114[0xe0];
    cBuyerVector     mBuyerVec;         // 0x1f4
    u8               mPad200[8];
    cItemVector      mItemVec;          // 0x208
    u8               mPad214[8];
    i32*             mpHandleVecBegin;  // 0x21c
    i32*             mpHandleVecEnd;    // 0x220
    i32*             mpHandleVecCap;    // 0x224

    i32 GetFetchItemName(cWString* out);                    // 0x00c58260
    i32 GetItemPlanetNameList(cWString* out);               // 0x00c58920
    i32 GetNumItemsNotDeliveredToBuyer(cPlanet_s00c5_8920* p);         // 0x00c572c0
    u8  GetTagString(u32 tag, cWString* out);               // 0x00c58ad0
    void GetText(u32 textId, cWString* out);                // 0x00c487d0
    void Cleanup();                                         // 0x00c59190
    void Reset();                                           // 0x00c49f90
    bool IsInBuyerPlanetList(void* target);                 // 0x00c570e0
    bool PickItemPlanets(u32 minCount, u32 maxCount);       // 0x00c59240
    i32  CreateStarMapDestinationIndicator(cStarRecord* from, cStarRecord* to, u32 param); // 0x00c58b70
    f32  ReadMinRange();                                    // 0x00c45b80
    f32  ReadMaxRange();                                    // 0x00c45bd0
    u32  ReadNumJumps();                                    // 0x00c45c20
};
struct cSPMissionBase {
    i32 GetTagString(u32 tag, cWString* out);       // 0x00c491c0
};
void __cdecl WStr_Format(cWString* dst, const wchar_t_* fmt, ...); // 0x0041e050
void __cdecl WStr_AppendFormat(cWString* dst, const wchar_t_* fmt, ...); // 0x004e0850
extern u8           gItemSeparator[];                              // 0x0146f368
void __cdecl MemCopy(void* dst, const void* src, u32 bytes);       // 0x011e0744
// ---- items of slice s00c58920 end

// ---- items of slice s00c59540 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable: 4100)
typedef unsigned short u16;
typedef signed int     i32_s00c5_9540;

static inline void** vtbl(const void* p) { return *(void***)p; }
void __cdecl FUN_011e0744(void* d, void* s, u32 n);                    // 0x11e0744 memcpy
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
    i32_s00c5_9540   FUN_00b8d9b0();                      // 0xb8d9b0
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
    i32_s00c5_9540   mCurrSub;       // +0x204
    u32*  mParam;         // +0x208
    u8    pad20c[0x10];
    u8*   mRec;           // +0x21c

    i32_s00c5_9540   SubCount() { return (i32_s00c5_9540)(((u8*)mSubEnd - (u8*)mSubBegin) >> 2); }
    void* SubAt(i32_s00c5_9540 i) { return ((void**)mSubBegin)[i]; }
    void* GetCurrSubMission();
    void  FUN_00c59dc0();
    void  FUN_00c59e20();
    void  FUN_00c59f00();
    void  FUN_00c59f60();
    void  FUN_00c59f90(u32 i, u32 v);
    u32   FUN_00c59fb0(u32 i);
    void  FUN_00c59fd0(u32 i, const void* p);
    i32_s00c5_9540   FUN_00c5a000();
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

// @ 0x00c4b760
void cSPMissionMultiDelivery::ReturnForRewards()
{
    if (mStatus == 1)
        return;
    Abort();
    if (mStatus != 1) {
        mStatus = 1;
        TriggerUIUpdate();
    }
    FUN_00c472e0(this);
    FUN_00c471c0(this);
}

// @ 0x00c56b90
namespace SP {
int32_t cSPMissionMultiDelivery_s00c5_62b0::Update(uint32_t delta)
{
    int32_t result = cSPMission_s00c5_62b0::Update(delta);
    if (mDeliveryState == 0) {
        tU32Vector* pShips = (tU32Vector*)FUN_01021300()->GetShipList();
        uint32_t numShips = pShips->size();
        if (numShips > 0)
            ReturnForRewards();
    }
    return result;
}
}  // namespace SP

// @ 0x00c56d90
namespace SP {
void cSPMissionMultiDelivery_s00c5_62b0::UpdateItemName()
{
    cProperty_s00c5_62b0* pProperty = 0;
    PropertyManager()->GetProperty(mpItemDefinition, 0x37d494e, &pProperty);
    GetPropertyAsText(pProperty, 0x3068d95d, &mItemName);
}
}  // namespace SP

// @ 0x00c56de0
namespace SP {
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
}  // namespace SP

// @ 0x00c56ef0
namespace SP {
bool cSPMissionMultiDelivery_s00c5_62b0::Validate()
{
    if (!cSPMission_s00c5_62b0::Validate())
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
}  // namespace SP

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// @ 0x00c56fe0
namespace SP {
bool cSPMissionMultiDelivery_s00c5_62b0::PickFetchItem()
{
    if (!mpMissionPropList)
        return false;

    cProperty_s00c5_62b0* pProperty = mpMissionPropList->GetPropertyRef(0x781900a6);
    int32_t kind = pProperty->mFlags & 0x30;

    int32_t count;
    if (kind) {
        count = pProperty->mCount;
        if (count <= 0)
            return false;
    } else {
        if (pProperty->mType == 0)
            return false;
        count = 1;
    }

    _ReadWriteBarrier();
    tItemInfo* pItems = kind ? (tItemInfo*)pProperty->mpData
                             : (pProperty->mType ? (tItemInfo*)pProperty : 0);

    uint32_t index = g_spRandom.RandomUint32Uniform((uint32_t)count);
    mpItemDefinition = pItems[index].mpPlanet.mpObject;
    mItemCount = 0;
    mItemsDelivered = 0;
    UpdateItemName();
    return true;
}
}  // namespace SP

// @ 0x00c57070
namespace SP {
bool cSPMissionMultiDelivery_s00c5_62b0::IsItemTargetPlanet(void* pStarRecord)
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
}  // namespace SP

// @ 0x00c570e0
namespace SP {
bool cSPMissionMultiDelivery_s00c5_62b0::IsInBuyerPlanetList(void* pPlanet)
{
    int32_t count = (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12;
    for (int32_t i = 0; i < count; ++i) {
        if (mpRunnerItems[i].mpPlanet.mpObject == pPlanet)
            return true;
    }
    return false;
}
}  // namespace SP

// @ 0x00c57130
namespace SP {
tPickupInfo* cSPMissionMultiDelivery_s00c5_62b0::GetItemInfoForPlanet(void* pPlanet)
{
    for (int32_t i = 0; i < GetNumBuyerItems(); ++i) {
        if (mpBuyerItems[i].mpPlanet.mpObject == pPlanet)
            return &mpBuyerItems[i];
    }
    return 0;
}
}  // namespace SP

// @ 0x00c57180
namespace SP {
bool cSPMissionMultiDelivery_s00c5_62b0::IsItemPickedUpInPlanet()
{
    int32_t count = (int32_t)((char*)mpBuyerItemsEnd - (char*)mpBuyerItems) / 20;
    for (int32_t i = 0; i < count; ++i) {
        if (!mpBuyerItems[i].mbPickedUp)
            return false;
    }
    return true;
}
}  // namespace SP

// @ 0x00c571d0
namespace SP {
bool cSPMissionMultiDelivery_s00c5_62b0::DeliverItemsToBuyer(void* pPlanet, int32_t count, int32_t* pDelivered)
{
    int32_t numItems = (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12;
    for (int32_t i = 0; i < numItems; ++i) {
        tItemInfo* pItem = &mpRunnerItems[i];
        if ((void*)pItem->mpPlanet.mpObject == pPlanet) {
            int32_t remaining = pItem->mRequested - pItem->mDelivered;
            int32_t carried = min_ref(remaining, count);
            pItem->mDelivered += carried;
            if (pDelivered)
                *pDelivered = carried;
            if (pItem->mDelivered >= pItem->mRequested)
                return true;
        }
    }
    return false;
}
}  // namespace SP

// @ 0x00c57270
namespace SP {
bool cSPMissionMultiDelivery_s00c5_62b0::DeliveredToAllBuyers()
{
    int32_t count = (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12;
    for (int32_t i = 0; i < count; ++i) {
        if (mpRunnerItems[i].mDelivered != mpRunnerItems[i].mRequested)
            return false;
    }
    return true;
}
}  // namespace SP

// @ 0x00c572c0
namespace SP {
int32_t cSPMissionMultiDelivery_s00c5_62b0::GetNumItemsNotDeliveredToBuyer(void* pPlanet)
{
    int32_t count = (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12;
    for (int32_t i = 0; i < count; ++i) {
        if (mpRunnerItems[i].mpPlanet.mpObject == pPlanet)
            return mpRunnerItems[i].mRequested - mpRunnerItems[i].mDelivered;
    }
    return 0;
}
}  // namespace SP

// @ 0x00c57320
namespace SP {
int32_t cSPMissionMultiDelivery_s00c5_62b0::GetTotalTravelCost()
{
    int32_t total = 0;
    if (mpActivePlanet) {
        void* pOrigin = (void*)mpActivePlanet->mpStarRecord->FUN_00b8de30();
        int32_t numItems = (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12;
        for (int32_t i = 0; i < numItems; ++i) {
            cPlanet_s00c5_62b0* pPlanet = mpRunnerItems[i].mpPlanet.mpObject;
            if (pPlanet) {
                void* pDest = (void*)pPlanet->mpStarRecord->FUN_00b8de30();
                if (pDest)
                    total += GetUFOSimulator()->FUN_00ffc4e0(pOrigin, pDest) * 2;
            }
        }

        int32_t numBuyers = (int32_t)((char*)mpBuyerItemsEnd - (char*)mpBuyerItems) / 20;
        for (int32_t i = 0; i < numBuyers; ++i) {
            cPlanet_s00c5_62b0* pPlanet = mpBuyerItems[i].mpPlanet.mpObject;
            if (pPlanet) {
                void* pDest = (void*)pPlanet->mpStarRecord->FUN_00b8de30();
                if (pDest)
                    total += GetUFOSimulator()->FUN_00ffc4e0(pOrigin, pDest) * 2;
            }
        }
    }
    return total;
}
}  // namespace SP

// @ 0x00c57420
namespace SP {
float cSPMissionMultiDelivery_s00c5_62b0::GetTotalTravelDistance()
{
    float total = 0.0f;
    if (mpActivePlanet) {
        void* pOrigin = (void*)mpActivePlanet->mpStarRecord->FUN_00b8de30();
        int32_t numItems = (int32_t)((char*)mpRunnerItemsEnd - (char*)mpRunnerItems) / 12;
        for (int32_t i = 0; i < numItems; ++i) {
            cPlanet_s00c5_62b0* pPlanet = mpRunnerItems[i].mpPlanet.mpObject;
            if (pPlanet) {
                void* pDest = (void*)pPlanet->mpStarRecord->FUN_00b8de30();
                if (pDest)
                    total += GetUFOSimulator()->FUN_00ffc490(pOrigin, pDest) * 2.0f;
            }
        }

        int32_t numBuyers = (int32_t)((char*)mpBuyerItemsEnd - (char*)mpBuyerItems) / 20;
        for (int32_t i = 0; i < numBuyers; ++i) {
            cPlanet_s00c5_62b0* pPlanet = mpBuyerItems[i].mpPlanet.mpObject;
            if (pPlanet) {
                void* pDest = (void*)pPlanet->mpStarRecord->FUN_00b8de30();
                if (pDest)
                    total += GetUFOSimulator()->FUN_00ffc490(pOrigin, pDest) * 2.0f;
            }
        }
    }
    return total;
}
}  // namespace SP

// @ 0x00c57520
namespace SP {
void cSPMissionMultiDelivery_s00c5_62b0::SetItemPropertyList()
{
    FUN_00c466d0();
    cProperty_s00c5_62b0* pProperty = 0;
    PropertyManager()->GetProperty(mpItemDefinition, 0x37d494e, &pProperty);
    GetPropertyAsText(pProperty, 0x3068d95d, &mItemName);
}
}  // namespace SP

namespace SP {
inline void WriteItemSequenceCount(IArchiveWriter* writer, uint32_t count)
{
    void* stream = writer->GetStream();
    EA_WriteUint32(stream, &count, 1, 0);
}
}

// @ 0x00c57570
namespace SP {
void __cdecl WriteSTLSequence_tItemInfo(IArchiver* pArchiver, cDeliveryItemRange* pRange)
{
    uint32_t itemCount = ((char*)pRange->mpEnd - (char*)pRange->mpBegin) / (int)sizeof(tItemInfo);
    IArchiveWriter* writer = pArchiver->GetWriter();
    WriteItemSequenceCount(writer, itemCount);
    tItemInfo* p = pRange->mpBegin;
    tItemInfo* pEnd = pRange->mpEnd;
    for (; p != pEnd; ++p)
        operator<<(*pArchiver, *p);
    pArchiver->EndRead();
}
}  // namespace SP

namespace SP {
inline void WritePickupSequenceCount(IArchiveWriter* writer, uint32_t count)
{
    void* stream = writer->GetStream();
    EA_WriteUint32(stream, &count, 1, 0);
}
}

// @ 0x00c575e0
namespace SP {
void __cdecl WriteSTLSequence_tPickupInfo(IArchiver* pArchiver, cPickupRange* pRange)
{
    uint32_t itemCount = ((char*)pRange->mpEnd - (char*)pRange->mpBegin) / (int)sizeof(tPickupInfo);
    IArchiveWriter* writer = pArchiver->GetWriter();
    WritePickupSequenceCount(writer, itemCount);
    tPickupInfo* p = pRange->mpBegin;
    tPickupInfo* pEnd = pRange->mpEnd;
    for (; p != pEnd; ++p) {
        IArchiveWriter* itemWriter = pArchiver->GetWriter();
        uint8_t pickedUp = *(uint8_t*)&p->mbPickedUp;
        void* itemStream = itemWriter->GetStream();
        bool value = pickedUp != 0;
        EA_WriteBool8(itemStream, &value, 1);
        cPlanet_s00c5_62b0* planet = p->mpPlanet.mpObject;
        pArchiver->SerializeObject(planet ? (char*)planet + 0xd4 : 0);
    }
    pArchiver->EndRead();
}
}  // namespace SP

// @ 0x00c57690
namespace SP {
tItemInfo_s00c5_7570* __thiscall tItemInfo_s00c5_7570::operator=(const tItemInfo_s00c5_7570& src)
{
    mpTarget = src.mpTarget;
    if (mpTarget)
        mpTarget->NotifyAssigned();
    mFields.x.f = src.mFields.x.f;
    mFields.y.f = src.mFields.y.f;
    mFields.z.f = src.mFields.z.f;
    mField10 = src.mField10;
    return this;
}
}  // namespace SP

// @ 0x00c576d0
namespace SP {
tBuyerInfo* __thiscall tBuyerInfo::operator=(const tBuyerInfo& src)
{
    cMissionTarget* pOld = mpTarget;
    cMissionTarget* pNew = src.mpTarget;
    if (pNew != pOld) {
        if (pNew)
            pNew->NotifyAssigned();
        mpTarget = pNew;
        if (pOld)
            pOld->ReleaseTarget();
    }
    mField4 = src.mField4;
    mField8 = src.mField8;
    return this;
}
}  // namespace SP

// @ 0x00c57720
namespace SP {
tItemInfo_s00c5_7570* __thiscall tItemInfo_s00c5_7570::FUN_00c57720(const tItemInfo_s00c5_7570& src)
{
    cMissionTarget* pOld = mpTarget;
    cMissionTarget* pNew = src.mpTarget;
    if (pNew != pOld) {
        if (pNew)
            pNew->NotifyAssigned();
        mpTarget = pNew;
        if (pOld)
            pOld->ReleaseTarget();
    }
    // Retail bit-copies the three floats; a raw word copy keeps the codegen identical.
    uint32_t* pDst = (uint32_t*)&mFields.x.f;
    const uint32_t* pSrc = (const uint32_t*)&src.mFields.x.f;
    pDst[0] = pSrc[0];
    pDst[1] = pSrc[1];
    pDst[2] = pSrc[2];
    mField10 = src.mField10;
    return this;
}
}  // namespace SP

// @ 0x00c57780
namespace SP {
tBuyerInfo* __cdecl copy_forward_buyer(tBuyerInfo* pFirst, tBuyerInfo* pLast, tBuyerInfo* pDest)
{
    for (; pFirst != pLast; ++pFirst, ++pDest) {
        if (pDest) {
            pDest->mpTarget = pFirst->mpTarget;
            if (pDest->mpTarget)
                pDest->mpTarget->NotifyAssigned();
            pDest->mField4 = pFirst->mField4;
            pDest->mField8 = pFirst->mField8;
        }
    }
    return pDest;
}
}  // namespace SP

// @ 0x00c57810
namespace SP {
tItemInfo_s00c5_7570* __cdecl copy_forward_item(tItemInfo_s00c5_7570* pFirst, tItemInfo_s00c5_7570* pLast, tItemInfo_s00c5_7570* pDest)
{
    for (; pFirst != pLast; ++pFirst, ++pDest) {
        if (pDest) {
            pDest->mpTarget = pFirst->mpTarget;
            if (pDest->mpTarget)
                pDest->mpTarget->NotifyAssigned();
            Float3& destination = pDest->mFields;
            const Float3& source = pFirst->mFields;
            destination.x.f = source.x.f;
            destination.y.f = source.y.f;
            destination.z.f = source.z.f;
            pDest->mField10 = pFirst->mField10;
        }
    }
    return pDest;
}
}  // namespace SP

// @ 0x00c578c0
namespace SP {
tBuyerInfo* __cdecl copy_impl_buyer(tBuyerInfo* pFirst, tBuyerInfo* pLast, tBuyerInfo* pDest)
{
    for (; pFirst != pLast; ++pFirst, ++pDest) {
        cMissionTarget* pNew = pFirst->mpTarget;
        cMissionTarget* pOld = pDest->mpTarget;
        if (pNew != pOld) {
            if (pNew)
                pNew->NotifyAssigned();
            pDest->mpTarget = pNew;
            if (pOld)
                pOld->ReleaseTarget();
        }
        pDest->mField4 = pFirst->mField4;
        pDest->mField8 = pFirst->mField8;
    }
    return pDest;
}
}  // namespace SP

// @ 0x00c57930
namespace SP {
tBuyerInfo* __cdecl copy_backward_buyer(tBuyerInfo* pFirst, tBuyerInfo* pLast, tBuyerInfo* pDest)
{
    while (pLast != pFirst) {
        --pLast;
        --pDest;
        cMissionTarget* pNew = pLast->mpTarget;
        cMissionTarget* pOld = pDest->mpTarget;
        if (pNew != pOld) {
            if (pNew)
                pNew->NotifyAssigned();
            pDest->mpTarget = pNew;
            if (pOld)
                pOld->ReleaseTarget();
        }
        pDest->mField4 = pLast->mField4;
        pDest->mField8 = pLast->mField8;
    }
    return pDest;
}
}  // namespace SP

// @ 0x00c579a0
namespace SP {
tItemInfo_s00c5_7570* __cdecl copy_impl_item(tItemInfo_s00c5_7570* pFirst, tItemInfo_s00c5_7570* pLast, tItemInfo_s00c5_7570* pDest)
{
    for (; pFirst != pLast; ++pFirst, ++pDest) {
        cMissionTarget* pNew = pFirst->mpTarget;
        cMissionTarget* pOld = pDest->mpTarget;
        if (pNew != pOld) {
            if (pNew)
                pNew->NotifyAssigned();
            pDest->mpTarget = pNew;
            if (pOld)
                pOld->ReleaseTarget();
        }
        ((Float3*)&pDest->mFields.x.f)->x.u = ((const Float3*)&pFirst->mFields.x.f)->x.u;
        ((Float3*)&pDest->mFields.x.f)->y.u = ((const Float3*)&pFirst->mFields.x.f)->y.u;
        ((Float3*)&pDest->mFields.x.f)->z.u = ((const Float3*)&pFirst->mFields.x.f)->z.u;
        pDest->mField10 = pFirst->mField10;
    }
    return pDest;
}
}  // namespace SP

// @ 0x00c57a10
namespace SP {
tItemInfo_s00c5_7570* __cdecl copy_backward_item(tItemInfo_s00c5_7570* pFirst, tItemInfo_s00c5_7570* pLast, tItemInfo_s00c5_7570* pDest)
{
    while (pLast != pFirst) {
        --pLast;
        --pDest;
        cMissionTarget* pNew = pLast->mpTarget;
        cMissionTarget* pOld = pDest->mpTarget;
        if (pNew != pOld) {
            if (pNew)
                pNew->NotifyAssigned();
            pDest->mpTarget = pNew;
            if (pOld)
                pOld->ReleaseTarget();
        }
        ((Float3*)&pDest->mFields.x.f)->x.u = ((const Float3*)&pLast->mFields.x.f)->x.u;
        ((Float3*)&pDest->mFields.x.f)->y.u = ((const Float3*)&pLast->mFields.x.f)->y.u;
        ((Float3*)&pDest->mFields.x.f)->z.u = ((const Float3*)&pLast->mFields.x.f)->z.u;
        pDest->mField10 = pLast->mField10;
    }
    return pDest;
}
}  // namespace SP

// @ 0x00c57a80
namespace SP {
tItemInfo_s00c5_7570* __thiscall tItemInfo_s00c5_7570::FUN_00c57a80(cMissionTarget* pTarget, bool flag, float f1, float f2, float f3)
{
    mpTarget = 0;
    if (pTarget) {
        pTarget->NotifyAssigned();
        mpTarget = pTarget;
    }
    mField10 = flag;
    volatile Float3* pFields = (Float3*)&mFields.x.f;
    pFields->x.u = ((const FloatBits*)&f1)->u;
    pFields->y.u = ((const FloatBits*)&f2)->u;
    pFields->z.u = ((const FloatBits*)&f3)->u;
    return this;
}
}  // namespace SP

// @ 0x00c57ad0
namespace SP {
void __thiscall cSPMissionMultiDelivery_s00c5_7570::FUN_00c57ad0()
{
}
}  // namespace SP

// @ 0x00c57d00
namespace SP {
struct IRefBase : IEmpty {
    virtual void AddRef();                              // slot 0
    virtual void Release();                             // slot +4
};
struct IRefFound : VPad<46, IRefBase> {
    virtual void ReleaseFound();                        // slot 0xc0
};
struct IHandleManager {
    void* Get(int id);                                  // 0x00ba6dc0
    void  Find(void* key, void** out);                  // 0x00bb59b0
};
IHandleManager* __cdecl FUN_00b3d2a0();                  // 0x00b3d2a0
}
namespace SP {
struct IStateVtbl : VPad<24, IEmpty> {
    virtual int32_t FUN_60();                           // slot 0x60
};
struct IGameHelper : VPad<24, IEmpty> {
    virtual void*   FUN_60(int id);                     // slot 0x60
    virtual int32_t FUN_64(int a, void* b);             // slot 0x64
};
struct IGameHelper1 : VPad<5, IGameHelper> {
    virtual void FUN_7c(int id, void** pOut, int delivered);   // slot 0x7c
};
struct IGameManager {
    IGameHelper* GetHelper();                           // 0x00a1ad60
};
IGameManager* __cdecl FUN_01002bd0();                   // 0x01002bd0
}
namespace SP {
int32_t __thiscall cSPMissionMultiDelivery_s00c5_7570::GetDynamicResponseID(int arg1, int arg2)
{
    cSPMissionMultiDelivery_s00c5_62b0* self = (cSPMissionMultiDelivery_s00c5_62b0*)this;
    if (((IStateVtbl*)self)->FUN_60() == 3 && self->mDeliveryState == 0) {
        IRefBase* pAcquired = 0;
        IRefBase* q = (IRefBase*)FUN_00b3d2a0()->Get(arg2);
        if (q) {
            q->AddRef();
            pAcquired = q;
        }

        IRefFound* pFound = 0;
        FUN_00b3d2a0()->Find(pAcquired, (void**)&pFound);

        if (pAcquired == *(IRefBase**)((char*)self->mpActivePlanet + 0x13c) &&
            arg1 == (int)self->mPoliticalID_8c) {
            if (pFound)
                pFound->ReleaseFound();
            if (pAcquired)
                pAcquired->Release();
            return (int32_t)0xb6a7851e;
        }

        if (self->IsInBuyerPlanetList(pFound)) {
            int32_t id = FUN_01002bd0()->GetHelper()->FUN_64(5, &self->mpItemDefinition);
            if (id != -1) {
                if (pFound)
                    pFound->ReleaseFound();
                if (pAcquired)
                    pAcquired->Release();
                return (int32_t)0xfebcbe81;
            }
            if (pFound)
                pFound->ReleaseFound();
            if (pAcquired)
                pAcquired->Release();
            return (int32_t)0x2219b1c7;
        }

        if (pFound)
            pFound->ReleaseFound();
        if (pAcquired)
            pAcquired->Release();
    }
    return -1;
}
}  // namespace SP

// @ 0x00c57e50
namespace SP {
bool __thiscall cSPMissionMultiDelivery_s00c5_7570::FUN_00c57e50(int arg1, int arg2)
{
    cSPMissionMultiDelivery_s00c5_62b0* self = (cSPMissionMultiDelivery_s00c5_62b0*)this;
    if (self->FUN_00c455b0(arg1, arg2))
        return true;

    IRefBase* pAcquired = 0;
    IRefBase* q = (IRefBase*)FUN_00b3d2a0()->Get(arg2);
    if (q) {
        q->AddRef();
        pAcquired = q;
    }

    IRefFound* pFound = 0;
    FUN_00b3d2a0()->Find(pAcquired, (void**)&pFound);
    bool result = self->IsInBuyerPlanetList(pFound) && self->mDeliveryState == 0;
    if (pFound)
        pFound->ReleaseFound();
    if (pAcquired)
        pAcquired->Release();
    return result;
}
}  // namespace SP

// @ 0x00c57ef0
namespace SP {
struct IRefObj : VPad<2, IEmpty> {
    virtual void Release();                             // slot +8
};
}
namespace SP {
int32_t __thiscall cSPMissionMultiDelivery_s00c5_7570::OnDelivery(int arg1, void* pPlanet)
{
    cSPMissionMultiDelivery_s00c5_62b0* self = (cSPMissionMultiDelivery_s00c5_62b0*)this;
    if (!pPlanet)
        return -1;

    int32_t result = (int32_t)0x147a1bb6;
    int32_t id = FUN_01002bd0()->GetHelper()->FUN_64(5, &self->mpItemDefinition);
    if (id != -1) {
        void* pObj = FUN_01002bd0()->GetHelper()->FUN_60(id);
        if (pObj) {
            int32_t delivered = 0;
            bool ok = self->DeliverItemsToBuyer(pPlanet, *(int32_t*)((char*)pObj + 0x10), &delivered);
            self->TriggerUIUpdate();
            void* pItem = 0;
            ((IGameHelper1*)FUN_01002bd0()->GetHelper())->FUN_7c(id, &pItem, delivered);
            if (ok) {
                result = (int32_t)0x95ed4de1;
                if (self->DeliveredToAllBuyers() && self->mDeliveryState != 1)
                    self->ReturnForRewards();
            }
            if (pItem)
                ((IRefObj*)pItem)->Release();
        }
    }
    (void)arg1;
    return result;
}
}  // namespace SP

// @ 0x00c58070
namespace SP {
bool __cdecl FUN_00c58070(void* pContext, cBuyerRange* pRange)
{
    tBuyerInfo* pEnd = pRange->mpEnd;
    for (tBuyerInfo* p = pRange->mpBegin; p != pEnd; ++p) {
        if (p) {
            cMissionTarget* pTarget = p->mpTarget;
            if (pTarget)
                pTarget->NotifyContext(pContext);
        }
    }
    return true;
}
}  // namespace SP

// @ 0x00c580b0
namespace SP {
bool __cdecl FUN_00c580b0(void* pContext, cItemRange* pRange)
{
    tItemInfo_s00c5_7570* pEnd = pRange->mpEnd;
    for (tItemInfo_s00c5_7570* p = pRange->mpBegin; p != pEnd; ++p) {
        if (p) {
            cMissionTarget* pTarget = p->mpTarget;
            if (pTarget)
                pTarget->NotifyContext(pContext);
        }
    }
    return true;
}
}  // namespace SP

// @ 0x00c58170
namespace SP {
void __fastcall cString_ctor(void* self);   // 0x006b5060
}
namespace SP {
cSPMissionMultiDelivery_s00c5_62b0* __fastcall cMissionMultiDeliveryCtor(cSPMissionMultiDelivery_s00c5_62b0* this_, int unused)
{
    this_->ConstructBase();
    *(void**)this_ = (void*)g_146f198;
    *(void**)((char*)this_ + 0x04) = (void*)g_146f184;
    *(void**)((char*)this_ + 0x34) = (void*)g_146f174;
    this_->mDeliveryState = 0;
    this_->mpRunnerItems = 0;
    this_->mpRunnerItemsEnd = 0;
    this_->mpRunnerItemsCapacity = 0;
    this_->mpBuyerItems = 0;
    this_->mpBuyerItemsEnd = 0;
    this_->mpBuyerItemsCapacity = 0;
    *(void**)((char*)this_ + 0x21c) = 0;
    *(void**)((char*)this_ + 0x220) = 0;
    *(void**)((char*)this_ + 0x224) = 0;
    this_->mpItemDefinition = *(void**)g_16919c4;
    this_->mItemCount = *(int32_t*)g_16919c8;
    this_->mItemsDelivered = *(int32_t*)g_16919cc;
    cString_ctor((char*)this_ + 0x23c);
    (void)unused;
    return this_;
}
}  // namespace SP

// @ 0x00c58260
namespace SP {
void __thiscall cSPMissionMultiDelivery_s00c5_7570::GetFetchItemName(eastl::wstring* pOut)
{
    const wchar_t* pText = mFetchItemName.GetText();
    const wchar_t* pEnd = pText;
    while (*pEnd)
        ++pEnd;
    int32_t length = (int32_t)(pEnd - pText);
    pOut->assign(pText, pText + length);
}
}  // namespace SP

// @ 0x00c582a0
namespace SP {
void __thiscall cSPMissionMultiDelivery_s00c5_7570::FUN_00c582a0(WString* out)
{
    cSPMissionMultiDelivery_s00c5_62b0* self = (cSPMissionMultiDelivery_s00c5_62b0*)this;
    WString& description = self->mUIShortDescription;
    if (description.mpBegin == description.mpEnd &&
        self->mDeliveryState == 0 &&
        self->IsItemPickedUpInPlanet()) {
        self->GetText(0x40a0575, out);
        if (out != &description)
            description.assign(out->mpBegin, out->mpEnd);
    } else {
        self->FUN_00c48d40(out);
    }
}
}  // namespace SP

// @ 0x00c58310
namespace SP {
struct cListNode_s00c5_7570 {
    cListNode_s00c5_7570* mpNext;                       // +0x00
    cListNode_s00c5_7570* mpPrev;                       // +0x04
    void*                 mpValue;                      // +0x08
};
}
namespace SP {
void* __cdecl EAAllocate(unsigned int size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
}
namespace SP {
void __thiscall cSPMissionMultiDelivery_s00c5_7570::FUN_00c58310(void* value)
{
    cListNode_s00c5_7570* head = *(cListNode_s00c5_7570**)this;
    cListNode_s00c5_7570* node = (cListNode_s00c5_7570*)EAAllocate(0xc, (const char*)g_13f09b4, 0, 0, (const char*)g_13ebb38, 0xd1);
    if (&node->mpValue)
        node->mpValue = *(void**)value;
    node->mpNext = head;
    node->mpPrev = head->mpPrev;
    head->mpPrev->mpNext = node;
    head->mpPrev = node;
}
}  // namespace SP

// @ 0x00c58360
namespace SP {
void __thiscall cSPMissionMultiDelivery_s00c5_7570::FUN_00c58360(void* value)
{
    cListNode_s00c5_7570* head = (cListNode_s00c5_7570*)this;
    cListNode_s00c5_7570* node = (cListNode_s00c5_7570*)EAAllocate(0xc, (const char*)g_13f09b4, 0, 0, (const char*)g_13ebb38, 0xd1);
    if (&node->mpValue)
        node->mpValue = *(void**)value;
    node->mpNext = head;
    node->mpPrev = head->mpPrev;
    head->mpPrev->mpNext = node;
    head->mpPrev = node;
}
}  // namespace SP

// @ 0x00c58530
namespace SP {
void __fastcall cString_dtor_s00c5_7570(void* self);          // 0x006b5240
void __fastcall cVector_dtor_0208(void* self);                // 0x00c58130
void __fastcall cVector_dtor_01f4(void* self);                // 0x00c580f0
void __fastcall cMissionBase_dtor(void* self);                // 0x00c47680
}
namespace SP {
void* __thiscall cSPMissionMultiDelivery_s00c5_7570::FUN_00c58530(int32_t flags)
{
    cString_dtor_s00c5_7570((char*)this + 0x23c);

    int32_t* pArray = *(int32_t**)((char*)this + 0x21c);
    if (pArray != 0) {
        if (pArray[-1] != 0)
            FreeArray(pArray);
    }

    cVector_dtor_0208((char*)this + 0x208);
    cVector_dtor_01f4((char*)this + 0x1f4);
    cMissionBase_dtor(this);

    if (flags & 1)
        FreeArray(this);
    return this;
}
}  // namespace SP

// @ 0x00c58600
namespace SP {
void __thiscall cSPMissionMultiDelivery_s00c5_7570::FUN_00c58600()
{
}
}  // namespace SP

// @ 0x00c58920
i32 cSPMissionMultiDelivery_s00c5_8920::GetItemPlanetNameList(cWString* out)
{
    cWString text;
    GetText(0x4bb21f92, &text);

    i32 count = (i32)((u8*)mItemVec.mpEnd - (u8*)mItemVec.mpBegin) / 0x14;
    for (i32 i = 0, offset = 0; i < count; ++i, offset += 0x14) {
        cPlanet_s00c5_8920* planet = (cPlanet_s00c5_8920*)*(void**)((u8*)mItemVec.mpBegin + offset);

        cWString name;
        cWString sortName;

        if (planet != 0) {
            cWString* pName = planet->GetName();
            if (pName != &name)
                name.assign(pName->mpBegin, pName->mpEnd);
        }
        if (*(cPlanet_s00c5_8920**)((u8*)mItemVec.mpBegin + offset) != 0) {
            cPlanet_s00c5_8920* p = *(cPlanet_s00c5_8920**)((u8*)mItemVec.mpBegin + offset);
            cStarRecord* source = p->mpModel->SortBanners();
            if (source != 0) {
                cWString* pSortName = source->GetName();
                if (pSortName != &sortName)
                    sortName.assign(pSortName->mpBegin, pSortName->mpEnd);
            }
        }

        WStr_AppendFormat(out, (const wchar_t_*)text.mpBegin,
                          name.mpBegin, sortName.mpBegin);
        if (i != count - 1)
            WStr_AppendFormat(out, (const wchar_t_*)gItemSeparator);

        sortName.Release();
        name.Release();
    }
    text.Release();
    return 0;
}

// @ 0x00c58ad0
u8 cSPMissionMultiDelivery_s00c5_8920::GetTagString(u32 tag, cWString* out)
{
    if (tag == 0x97cc2aa3) {
        cPlanet_s00c5_8920* planet = (cPlanet_s00c5_8920*)mBuyerVec.mpBegin[0].mpObject;
        if (planet != 0) {
            cWString* name = (cWString*)planet->GetName();
            if (name != out)
                out->assign(name->mpBegin, name->mpEnd);
        }
        return 1;
    }
    if (tag == 0x659ef0ac) {
        GetFetchItemName(out);
        return 1;
    }
    if (tag == 0xaa6cdbb8) {
        GetItemPlanetNameList(out);
        return 1;
    }
    if (tag == 0x8aad4d34) {
        i32 n = GetNumItemsNotDeliveredToBuyer((cPlanet_s00c5_8920*)mBuyerVec.mpBegin[0].mpObject);
        WStr_Format(out, (const wchar_t_*)g_13f01bc, n);
        return 1;
    }
    return ((struct cSPMissionBase*)this)->GetTagString(tag, out);
}

// @ 0x00c58b70
i32 cSPMissionMultiDelivery_s00c5_8920::CreateStarMapDestinationIndicator(cStarRecord* from, cStarRecord* to, u32 param)
{
    if (from == 0 || to == 0)
        return -1;

    VEffect* visual = GetStarMap()->CreateStarRecordVisual(from, 0x166521a5u, param);
    GetStarMap()->AddVisual(visual, 0);
    mVisualVec.push_back(visual);

    Vec3 fromPos;
    {
        const Vec3& ref = from->GetPosition();
        fromPos.x = ref.x;
        fromPos.y = ref.y;
        fromPos.z = ref.z;
    }
    const Vec3& toRef = to->GetPosition();
    Vec3 delta;
    delta.x = toRef.x - fromPos.x;
    delta.y = toRef.y - fromPos.y;
    delta.z = toRef.z - fromPos.z;

    f32 distanceSq = delta.x * delta.x + (delta.y * delta.y + delta.z * delta.z);
    u32 n = 1 - (u32)(InlineSqrt(distanceSq) * gNegTen);
    u32 count = n + 1;

    cFloatVector points;
    points.reserve(count * 3 * 4);

    f32 inv = 1.0f / (f32)n;
    Vec3 step;
    step.x = delta.x * inv;
    step.y = delta.y * inv;
    step.z = delta.z * inv;

    for (u32 i = 0; i < count; ++i) {
        points.push_back(fromPos.x);
        points.push_back(fromPos.y);
        points.push_back(fromPos.z);
        fromPos.x += step.x;
        fromPos.y += step.y;
        fromPos.z += step.z;
    }

    VEffect* effect = GetStarMap()->FUN_01045120(from->mField70, visual);
    if (effect == 0) {
        if (SpIsOwned(points.mpBegin))
            WFree(points.mpBegin);
        return -1;
    }

    effect->FUN_0044(13, points.mpBegin, (i32)(count * 3));

    u32 argb = GetMissionManager()->FUN_00febf80(this);
    Vec3 rgb;
    rgb.x = (f32)((argb >> 16) & 0xff) * (1.0f / 255.0f);
    rgb.y = (f32)((argb >> 8) & 0xff) * (1.0f / 255.0f);
    rgb.z = (f32)(argb & 0xff) * (1.0f / 255.0f);
    effect->FUN_0040(5, &rgb, 1);

    if (SpIsOwned(points.mpBegin))
        WFree(points.mpBegin);
    return (i32)visual;
}

// @ 0x00c58f10
IArchiver_s00c5_8920& ReadBuyerSequence(IArchiver_s00c5_8920& ar, cBuyerVector& vec)
{
    vec.erase(vec.mpBegin, vec.mpEnd);

    u32 count = 0;
    IArchiveWriter_s00c5_8920* writer = ar.GetWriter();
    void* stream = writer->GetStream();
    ReadInt32(stream, &count, 1, 0);
    vec.reserve(count);

    for (u32 i = 0; i < count; ++i) {
        tBuyerInfo_s00c5_8920 info;
        info.mpObject = 0;
        info.mField4 = 0;
        info.mField8 = 0;
        operator>>(ar, info);
        vec.push_back(info);
        if (info.mpObject)
            info.mpObject->Release();
    }
    return ar.EndRead();
}

// @ 0x00c59010
IArchiver_s00c5_8920& ReadItemSequence(IArchiver_s00c5_8920& ar, cItemVector& vec)
{
    vec.erase(vec.mpBegin, vec.mpEnd);

    u32 count = 0;
    IArchiveWriter_s00c5_8920* writer = ar.GetWriter();
    void* stream = writer->GetStream();
    ReadInt32(stream, &count, 1, 0);
    vec.reserve(count);

    for (u32 i = 0; i < count; ++i) {
        tItemInfo_s00c5_8920 item;
        item.mpObject = 0;
        item.mPosition.x = gDefaultPosition.x;
        item.mPosition.y = gDefaultPosition.y;
        item.mPosition.z = gDefaultPosition.z;
        item.mFlag = false;

        IArchiveWriter_s00c5_8920* flagWriter = ar.GetWriter();
        ReadBool(flagWriter->GetStream(), &item.mFlag);
        if (item.mpObject) {
            IRefCounted_s00c5_8920* old = item.mpObject;
            item.mpObject = 0;
            old->Release();
        }
        ar.SerializeItem(0x3275872u, &item.mpObject, 0);
        vec.push_back(item);
        if (item.mpObject)
            item.mpObject->Release();
    }
    return ar.EndRead();
}

// @ 0x00c59190
void cSPMissionMultiDelivery_s00c5_8920::Cleanup()
{
    // Release the buyer-info and item-info vectors.
    cBuyerVector* buyerVec = &mBuyerVec;
    buyerVec->erase(buyerVec->mpBegin, buyerVec->mpEnd);
    cItemVector* itemVec = &mItemVec;
    itemVec->erase(itemVec->mpBegin, itemVec->mpEnd);

    i32 count = (i32)(mpHandleVecEnd - mpHandleVecBegin);
    for (i32 i = 0; i < count; ++i) {
        i32 handle = mpHandleVecBegin[i];
        if (handle != -1)
            GetStarMap()->RemoveVisual(handle, 0);
    }

    // Trim the handle list back to empty.
    i32* first = mpHandleVecBegin;
    i32* last = mpHandleVecEnd;
    MemCopy(first, last, (i32)((char*)last - (char*)mpHandleVecEnd));
    mpHandleVecEnd -= last - first;

    Reset();
}

// @ 0x00c59240
bool cSPMissionMultiDelivery_s00c5_8920::PickItemPlanets(u32 minCount, u32 maxCount)
{
    u32 target = minCount + gRandom.RandomUint32Uniform(maxCount - minCount);
    cStarRecord* targetStar = mpActivePlanet->mpModel->SortBanners();
    cPlanet_s00c5_8920* home = GetPlayerHomePlanet();

    cRefVector records;
    records.mpBegin = 0;
    records.mpEnd = 0;
    records.mpCap = 0;

    f32 minRange = ReadMinRange();
    f32 maxRange = ReadMaxRange();
    u32 numJumps = ReadNumJumps();

    mItemVec.erase(mItemVec.mpBegin, mItemVec.mpEnd);

    tStarSearchCriteria criteria;
    criteria.mMiscFilters = 0;
    criteria.mMinRange = 0.0f;
    criteria.mMaxRange = 0.0f;
    criteria.mMaxTravel = 0.0f;
    criteria.mNumJumps = 0;
    if (0.0f <= minRange)
        criteria.mMinRange = minRange;
    if (0.0f < maxRange)
        criteria.mMaxRange = maxRange;
    criteria.mAcceptableStarTypes = 0x1ff1;
    criteria.mAcceptableSolarTech = 0x3e;
    criteria.mMaxTravel = GetUFOSimulator_s00c5_8920()->GetMaxTravelDistance();
    criteria.mNumJumps = numJumps;

    StarManager()->GetStarRecords(targetStar->GetPosition(), criteria, records);

    i32 count = (i32)((u8*)records.mpEnd - (u8*)records.mpBegin) / 4;
    i32 index = (i32)gRandom.RandomUint32Uniform(count);

    for (i32 tries = 0; tries < count; ++tries) {
        cStarRecord* record = records.mpBegin[index];
        if (record->TestFlag(1))
            goto advance;
        if (record == targetStar)
            goto advance;

        StarManager()->ActivatePlanetRecordsForQuery(record, 0);
        {
            cPlanetVector* planets = record->GetPlanets();
            if (planets->mpBegin == planets->mpEnd)
                goto advance;
            cPlanet_s00c5_8920* planet = planets->mpBegin[0];
            if (planet == home)
                goto advance;
            if (((1 << (planet->mField28 & 0x1f)) & 0x3c) == 0)
                goto advance;
            if (planet->FUN_00b8d9b0() != 0)
                goto advance;

            void* activated = 0;
            StarManager()->GetOrActivatePlanet(planet, &activated);
            if (!IsInBuyerPlanetList(activated)) {
                tItemInfo_s00c5_8920 item;
                mItemVec.Add(item.FUN_00c57a80(activated, 0, gDefaultPosition));
                if (item.mpObject)
                    item.mpObject->Release();
                if (mItemVec.size() >= (i32)target) {
                    if (activated)
                        ((IRefCounted_s00c5_8920*)activated)->Release();
                    break;
                }
            }
            if (activated)
                ((IRefCounted_s00c5_8920*)activated)->Release();
        }
advance:
        index = (index + 1) % count;
    }

    bool complete = mItemVec.size() >= (i32)numJumps;

    for (cStarRecord** p = records.mpBegin; p < records.mpEnd; ++p) {
        cStarRecord* record = *p;
        if (record != 0)
            record->Release();
    }
    if (SpIsOwned(records.mpBegin))
        WFree(records.mpBegin);

    return complete;
}

// @ 0x00c59540
u8 cMissionMultiStep::FUN_00c59540(void* a, void* b)
{
    i32_s00c5_9540 want = (i32_s00c5_9540)b - (i32_s00c5_9540)a;
    i32_s00c5_9540 rnd  = (i32_s00c5_9540)MOPS((void*)0x1601760)->FUN_00a68fb0((u32)want);
    (void)rnd;
    void* empire = MOPS(this)->FUN_00c451e0();
    i32_s00c5_9540 ally = 0;
    if (empire != 0) {
        ally = (i32_s00c5_9540)MOPS(empire)->FUN_00c31b50(1);
    }
    void* civ = MOPS(this)->FUN_00b8de30();
    f32 home = (f32)MOPS(this)->FUN_00ffbfc0();
    (void)home;
    f32 minR = MOPS(this)->FUN_00c45b80();
    f32 maxR = MOPS(this)->FUN_00c45bd0();
    u32 jumps = MOPS(this)->FUN_00c45c20();
    // erase the existing buyer list
    MOPS(this)->FUN_00c58590(*(void**)((u8*)this + 0x1f4), *(void**)((u8*)this + 0x1f8));
    (void)civ; (void)minR; (void)maxR; (void)jumps; (void)ally;
    return 1;
}

// @ 0x00c59980
u8 cMissionMultiStep::FUN_00c59980(void* param)
{
    if (!MOPS(this)->FUN_00c45f80()) {
        return 0;
    }
    void* base = *(void**)((u8*)this + 0x9c);
    i32_s00c5_9540 seed = (i32_s00c5_9540)MOPS((void*)((u8*)base + 0x13c))->FUN_00b8de30();
    if (seed == 0) {
        return 0;
    }
    u8** vec = (u8**)((u8*)this + 0x21c);
    i32_s00c5_9540 n = (i32_s00c5_9540)(vec[1] - vec[0]) >> 2;
    for (i32_s00c5_9540 i = 0; i < n; i++) {
        i32_s00c5_9540 id = *(i32_s00c5_9540*)(vec[0] + i * 4);
        if (id != -1) {
            void* sm = MOPS((void*)id)->FUN_01046fc0(0);
            (*(void(__thiscall**)(void*))((char*)vtbl(sm) + 0x0))(sm);
        }
    }
    // collapse the record vector
    u8* src = vec[1];
    u8* dst = vec[0];
    FUN_011e0744(dst, src, (u32)(src - dst));
    vec[1] = vec[1] - (src - dst);
    (void)param;
    return 1;
}

// @ 0x00c59b50
u8 cMissionMultiStep::FUN_00c59b50()
{
    if (!MOPS(this)->FUN_00c4ad50()) {
        return 0;
    }
    u32 a = 0;
    void* prop = *(void**)((u8*)this + 0x180);
    if (prop != 0) {
        u32 tmp;
        u8 ok = (*(u8(__thiscall**)(void*, u32, u32*))((char*)vtbl(prop) + 0x24))(prop, 0x6c319752, &tmp);
        if (ok && *(u16*)(tmp + 0x12) == 9) {
            a = *(u32*)MOPS((void*)tmp)->FUN_0041e990();
        }
    }
    u32 b = 0;
    prop = *(void**)((u8*)this + 0x180);
    if (prop != 0) {
        u32 tmp;
        u8 ok = (*(u8(__thiscall**)(void*, u32, u32*))((char*)vtbl(prop) + 0x24))(prop, 0xd2fc2218, &tmp);
        if (ok && *(u16*)(tmp + 0x12) == 9) {
            b = *(u32*)MOPS((void*)tmp)->FUN_0041e990();
        }
    }
    if (!FUN_00c59540((void*)b, (void*)a)) {
        return 0;
    }
    if (!MOPS(this)->FUN_00c59240(MOPS(this)->FUN_00c57ff0(), MOPS(this)->FUN_00c58030())) {
        return 0;
    }
    if (!MOPS(this)->FUN_00c56fe0()) {
        return 0;
    }
    MOPS(this)->FUN_00c4a0c0();
    i32_s00c5_9540 nA = (i32_s00c5_9540)(*(u8**)((u8*)this + 0x20c) - *(u8**)((u8*)this + 0x208)) / 0x14;
    i32_s00c5_9540 nB = (i32_s00c5_9540)(*(u8**)((u8*)this + 0x1f8) - *(u8**)((u8*)this + 0x1f4)) / 0xc;
    if (nA > 0 && nB > 0) {
        f32 ratio = (f32)nA / (f32)nB;
        i32_s00c5_9540 per = (i32_s00c5_9540)ratio;
        i32_s00c5_9540 rem = nA - per * nB;
        for (i32_s00c5_9540 i = 0; i < nB; i++) {
            (*(u32**)((u8*)this + 0x1f4))[i * 3 + 1] = (u32)per;
            if (rem > 0) {
                (*(u32**)((u8*)this + 0x1f4))[i * 3 + 1] += (u32)rem;
                rem = 0;
            }
        }
    }
    return 1;
}

