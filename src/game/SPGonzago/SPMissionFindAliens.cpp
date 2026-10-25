// src/game/SPGonzago/SPMissionFindAliens.cpp -- migrated from slice(s) s00c54f90, s00c4dbf0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionFindAliens.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cHerd.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  __cdecl FUN_00c472e0(void* self);
extern "C" void  __cdecl FUN_00c471c0(void* self);
extern "C" void  __cdecl FUN_00c47d80(void* self);
#pragma warning(disable : 4100)

// ---- items of slice s00c4dbf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
extern "C" void  __cdecl FUN_00c472e0(void* self);
extern "C" void  __cdecl FUN_00c471c0(void* self);
extern "C" void  __cdecl FUN_00c47d80(void* self);
namespace SP {
class ThisStubs
{
  public:
    void  A();               // 0x00c48e90 cGenericPressureEvent ctor
    void  B();               // 0x00c47680 cSPMission dtor
    bool  Init();            // 0x00c4ad50
    bool  IsActive();        // 0x00c44c80
    u32   ReadTargetType();  // 0x00c45b40
    void* GetPlanetRec(int); // 0x00c474b0
    float ReadMinRange();    // 0x00c45b80
    float ReadMaxRange();    // 0x00c45bd0
    int   ReadNumJumps();    // 0x00c45c20
    int   CalcDuration();    // 0x00c45a10
    void  BaseInitA();       // 0x00c44b80
    void  BaseInitB();       // 0x00c44bd0
    void  SetSerializer();   // 0x00c2e4e0
    void  GetText(int key, void* out);   // 0x00c487d0
    void  GetUITitle(void* out);         // 0x00c48d40
    void  TriggerUIUpdate();             // 0x00c47d80
    void* PickPlanet(void* a);           // 0x00c47e20
    void* GetTargetPlanet();             // 0x00970b30
    int   Update(int a);                 // 0x00c478b0
    void  SetText(void* a);              // 0x0057cb60 eastl wstring operator=
    void  vt14c(int a);                  // mission list register
    void  vt150(int a);                  // mission list register
    void  RemoveEvent();                 // 0x00dd6d10 cSPUIEventLog::RemoveEvent
    bool  RegisterCallback();            // 0x00dd6b20 cSPUIEventLog::RegisterCallback
    void  MoveNestInit(void* a, void* b);  // 0x00c4db90
    void  PostInit();                    // 0x00c4a0c0
};
}
// ---- items of slice s00c4dbf0 end

// ---- items of slice s00c54f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int intptr_t;
#define nullptr 0
struct cMethodTable {
    void* mSlots[0x100];
};
struct cDispatchObject {
    cMethodTable* mpMethods;                    // 0x00

    void* Call(int nSlot) {
        return ((void* (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    char CallChar(int nSlot) {
        return ((char (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    char CallChar1(int nSlot, uint32_t nArg1, void* pArg2) {
        return ((char (*)(void*, uint32_t, void*))mpMethods->mSlots[nSlot >> 2])(this, nArg1,
                                                                                 pArg2);
    }
    void* Call1(int nSlot, uint32_t nArg1) {
        return ((void* (*)(void*, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1);
    }
    void* Call2(int nSlot, uint32_t nArg1, void* pArg2) {
        return ((void* (*)(void*, uint32_t, void*))mpMethods->mSlots[nSlot >> 2])(this, nArg1,
                                                                                  pArg2);
    }
    void* Call3(int nSlot, uint32_t nArg1, uint32_t nArg2, void* pArg3) {
        return ((void* (*)(void*, uint32_t, uint32_t, void*))mpMethods->mSlots[nSlot >> 2])(
            this, nArg1, nArg2, pArg3);
    }
};
struct cKey {
    uint8_t mPad00[0x06];                       // 0x00
    uint16_t mnType;                            // 0x06
};
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
int32_t GetUniverseContext();
void* GetActivePlanet();
int32_t GetPlayerEmpire();
void* GetTargetPlanet(void* pMission);
void* NounManager();
void* GetPropertyAsKeyArray();
void AssignString(void* pDst, void* pValue);
void TriggerUIUpdate(void* pMission);
char BaseMissionInit(void* pMission);
void RemoveAliensHerd(void* pPlanet);
char CheckMissionProgress();
char CheckAliensComplete();
char CheckHerdsComplete();
char SetMissionState(void* pMission);
void HandleMissionMessage(void* pMission, int nMessage, void* pParam);
void SetMissionFlag(void* pTarget, int nValue);
void OnAcceptMission(void* pMission);
void OnRejectMission(void* pMission);
// ---- items of slice s00c54f90 end

// @ 0x00c4e230
void __fastcall FUN_00c4e230(void* ecx_this, void* edx)
{
    ((SP::ThisStubs*)ecx_this)->SetSerializer();
    if (*(int*)((char*)ecx_this + 0x1f0) == 2)
        return;
    ((SP::ThisStubs*)ecx_this)->BaseInitA();
    if (*(int*)((char*)ecx_this + 0x1f0) != 2) {
        *(int*)((char*)ecx_this + 0x1f0) = 2;
        FUN_00c47d80(ecx_this);
    }
    FUN_00c472e0(ecx_this);
    FUN_00c471c0(ecx_this);
}

// @ 0x00c552d0
void cMissionFindAliens::GetUIMediumDescription(void* pParam)
{
    if (IsActive()) {
        switch (mnFindAliensState) {
        case 0:
            GetText(0x5953ec8a, pParam);
            break;
        case 1:
            GetText(0xbe14a87a, pParam);
            break;
        case 2:
            GetText(0x81128ae1, pParam);
            break;
        }
    }
}

// @ 0x00c55330
void cMissionFindAliens::GetUILongDescription(void* pParam)
{
    if (IsActive()) {
        switch (mnFindAliensState) {
        case 0:
            GetText(0xd84d826d, pParam);
            break;
        case 1:
            GetText(0xbdc423cd, pParam);
            break;
        case 2:
            GetText(0xba93258e, pParam);
            break;
        }
    }
}

// @ 0x00c55390
void cMissionFindAliens::Update(void* pParam)
{
    int32_t nResult = (int32_t)(intptr_t)UpdateBase(pParam);
    if (nResult != 3)
        return;

    if (mnNumAliensFound != 0) {
        if (mnNumAliensFound != 1)
            return;
        int32_t nContext = GetUniverseContext();
        if (nContext != 1 && nContext != 0)
            return;

        if (!mbContactGrob) {
            if (GetActivePlanet() != nullptr && CheckMissionProgress() == 5) {
                if (CheckAliensComplete() == (char)GetPlayerEmpire())
                    return;
            }
        } else {
            if (GetActivePlanet() == nullptr)
                return;
            if (CheckAliensComplete() != (char)(intptr_t)NounManager())
                return;
        }
        if (mnNumAliensToFind != 0) {
            mnNumAliensToFind = 0;
            TriggerUIUpdate(this);
        }
        return;
    }

    int32_t nContext = GetUniverseContext();
    if (nContext != 1 && nContext != 0)
        return;

    if (!mbContactGrob) {
        if (GetActivePlanet() == nullptr)
            return;
        if (CheckMissionProgress() != 5)
            return;
        if (CheckAliensComplete() == (char)GetPlayerEmpire())
            return;
    } else {
        if (GetActivePlanet() == nullptr)
            return;
        if (CheckAliensComplete() != (char)(intptr_t)NounManager())
            return;
    }
    if (SetMissionState(this)) {
        TriggerUIUpdate(this);
    }
}

// @ 0x00c55500
void cMissionFindAliens::SetContactGrob()
{
    if (mnNumAliensFound == 2)
        return;
    ((cDispatchObject*)this)->Call(0x6c);
    if (mnNumAliensFound != 2) {
        mnNumAliensFound = 2;
        TriggerUIUpdate(this);
    }
    OnAcceptMission(this);
    OnRejectMission(this);
}

// @ 0x00c55540
char cMissionFindAliens::Init()
{
    if (!BaseMissionInit(this))
        return 0;

    cKey key;
    void* pProperties = mpProperties;
    if (pProperties != nullptr) {
        if (((cDispatchObject*)pProperties)->CallChar1(0x24, 0xf924ebff, &key) != 0 &&
            key.mnType == 9) {
            mnFindAliensState = (int32_t)(intptr_t)GetPropertyAsKeyArray();
        }
    }
    pProperties = mpProperties;
    if (pProperties != nullptr) {
        if (((cDispatchObject*)pProperties)->CallChar1(0x24, 0xf924ec00, &key) != 0 &&
            key.mnType == 1) {
            mnNumAliensFound = *(uint8_t*)(intptr_t)GetPropertyAsKeyArray();
        }
    }
    SetMissionFlag(this, 1);
    return 1;
}

// @ 0x00c555d0
void cMissionFindAliens::HandleMessage(int nMessage, void* pParam)
{
    if (nMessage == 0x43f2590 && GetActivePlanet() != nullptr && !CheckMissionProgress()) {
        if (!mbContactGrob) {
            ++mnNumAliensToFind;
            if (mnNumAliensToFind < mnNumAliensFound) {
                HandleMissionMessage(this, nMessage, pParam);
                return;
            }
        } else {
            if (!CheckHerdsComplete()) {
                HandleMissionMessage(this, nMessage, pParam);
                return;
            }
        }
        RemoveAliensHerd(GetActivePlanet());
        SetContactGrob();
    }
    HandleMissionMessage(this, nMessage, pParam);
}

// @ 0x00c55660
void* cMissionFindAliens::GetUIShortDescription(void* pParam)
{
    if (mpMissionPropList != (void*)(intptr_t)mnGiveOnAcceptMoney) {
        if (&mpMissionPropList == pParam)
            return pParam;
        AssignString(mpMissionPropList, (void*)(intptr_t)mnGiveOnAcceptMoney);
        return pParam;
    }

    uint32_t nText = 0;
    if (mnFindAliensState == 0) {
        nText = 0xb3426f5f;
    } else if (mnFindAliensState == 1) {
        nText = 0x5886769f;
    } else if (mnFindAliensState == 2) {
        nText = 0x4e1f8fa8;
    } else {
        if (pParam != &mpMissionPropList) {
            AssignString(*(void**)pParam, *((void**)pParam + 1));
        }
        return pParam;
    }
    GetText(nText, pParam);
    if (pParam != &mpMissionPropList) {
        AssignString(*(void**)pParam, *((void**)pParam + 1));
    }
    return pParam;
}
