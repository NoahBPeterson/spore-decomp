// src/game/SPGonzago/SPMissionHappiness.cpp -- migrated from slice(s) s00c562b0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionHappiness.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPMissionHappinessEvent.h"
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
#include "SP/cTerrainSphere.h"
#pragma warning(disable : 4100)

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
extern const float g_cityHappinessThreshold;           // 0x013eecd8 20.0f
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
class cSPMissionHappinessEvent_s00c5_62b0 : public cSPMission_s00c5_62b0 {
public:
    void OnAcceptMission();
    int32_t Update(uint32_t delta);  // 0x00c56850 (SP::cSPMissionHappinessEvent::Update)
    void OnCompleteMission();
};
}
// ---- items of slice s00c562b0 end

// @ 0x00c56850
namespace SP {
int32_t cSPMissionHappinessEvent_s00c5_62b0::Update(uint32_t delta)
{
    int32_t result = cSPMission_s00c5_62b0::Update(delta);
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
}  // namespace SP
