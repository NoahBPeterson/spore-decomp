// src/game/SPGonzago/SPMissionFlight101.cpp -- migrated from slice(s) s00c54f90 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionFlight101.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cHerd.h"

// unnamed retail callees and globals (address in the comment)
extern void* gVtableFlight101;
extern void* gVtableFlight101Unk;
extern void* gVtableFlight101Extra;
extern void* gHerdKeyDefaults[3];

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
class cHerdEntry {
public:
    uint8_t mPad000[0x504];                     // 0x000
    void* mpKeyA;                               // 0x504
    void* mpKeyB;                               // 0x508
    void* mpKeyC;                               // 0x50c
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
class cSPMissionFetch {
public:
    char VerifyTargetPlanet(void* pTarget, void* pOut);
    char SetupHerds();
    void* GetTargetPlanet();

    uint8_t mPad000[0x16c];                     // 0x000
    void* mpSelectedHerd;                       // 0x16c
    uint8_t mHerdKeys[0x0c];                    // 0x170
    uint8_t mPad17c[0x74];                      // 0x17c
    int32_t mnState;                            // 0x1f0
    uint32_t mnTargetType;                      // 0x1f4
    uint8_t mPad1f8[0x18];                      // 0x1f8
    uint8_t mToolResource[0x0c];                // 0x210
    uint8_t mSearchA[0x34];                     // 0x21c
    uint8_t mSearchB[0x10];                     // 0x250
};
extern void* gVtableFlight101;
extern void* gVtableFlight101Unk;
extern void* gVtableFlight101Extra;
extern void* gHerdKeyDefaults[3];
class cMissionTarget {
public:
    void* SetupHerdList(uint32_t nFlagA, uint32_t nFlagB, void* pHerdKeys);
    cDispatchObject mObject;                    // 0x00
};
int32_t GetUniverseContext();
void* GetActivePlanet();
void* GetTargetPlanet(void* pMission);
void* NounManager();
void* SpaceGameGet();
void* GetMissionManager();
void* GetMissionManager(uint32_t nMissionId);
void* GetPlanetRecordFromTargetType(void* pMission, uint32_t nType);
uint32_t ReadTargetPlanetType();
void AddDiseaseEffect(void* pSpecies, uint32_t nEffect, int nValue);
void MarkSpeciesScanned(void* pSpecies);
void CollectSpecies(void* pSpecies);
void* GetHerdEntry(void* pSpecies);
char CheckHerdsComplete();
char SetMissionState(void* pMission);
void HandleMissionMessage(void* pMission, int nMessage, void* pParam);
void SetMissionFlag(void* pTarget, int nValue);
void PlayMissionEvent(uint32_t nEvent);
void AddInfectedAnimalsToHerd(void* pOwner, void* pHerd, int nCount, int nMissionId,
                              uint32_t nEffect);
uint32_t RandomUint32Uniform(int32_t nRange);
void operator_delete__(void* pMemory);
// ---- items of slice s00c54f90 end

// @ 0x00c557c0
char cMissionFindAliens::BindTarget()
{
    uint32_t nType = ReadTargetPlanetType();
    void* pRecord = GetPlanetRecordFromTargetType(this, nType);
    if (pRecord == nullptr)
        return 0;
    SetMissionFlag(pRecord, 1);
    ((cDispatchObject*)this)->Call(0x18c);
    return 1;
}

// @ 0x00c557f0
void cSPMissionFlight101::Shutdown()
{
    BaseShutdown();
    mpEradicateMission = nullptr;
}

// @ 0x00c558f0
void BaseOnSubMissionComplete()
{
    void* pInventory = ((cDispatchObject*)SpaceGameGet())->Call(0x00);
    if (pInventory != nullptr) {
        ((cDispatchObject*)pInventory)->Call(0x00);
    }
    ((cDispatchObject*)GetMissionManager())->Call1(0x00, 1);
}

// @ 0x00c55920
void cSPMissionFlight101::OnReject()
{
    BaseOnReject();
    uint32_t nMissionId = (uint32_t)mMissionId;
    ((cDispatchObject*)GetMissionManager())->Call1(0x00, nMissionId);

    void* pInventory = ((cDispatchObject*)SpaceGameGet())->Call(0x00);
    if (pInventory != nullptr) {
        ((cDispatchObject*)pInventory)->Call(0x00);
        ((cDispatchObject*)pInventory)->Call(0x00);
    }
    ((cDispatchObject*)GetMissionManager())->Call1(0x00, 1);
}

// @ 0x00c55970
void cSPMissionFlight101::OnAccept()
{
    BaseOnAccept();
    uint32_t nMissionId = (uint32_t)mMissionId;
    ((cDispatchObject*)GetMissionManager())->Call1(0x00, nMissionId);

    void* pInventory = ((cDispatchObject*)SpaceGameGet())->Call(0x00);
    if (pInventory != nullptr) {
        ((cDispatchObject*)pInventory)->Call(0x00);
        ((cDispatchObject*)pInventory)->Call(0x00);
    }
    ((cDispatchObject*)GetMissionManager())->Call1(0x00, 1);
}

// @ 0x00c559e0
cSubMission* cSPMissionFlight101::GetEradicateSubMission()
{
    int32_t nIndex = 0;
    int32_t nCount = (int32_t)(mSubMissions.mpEnd - mSubMissions.mpBegin);
    while (nIndex < nCount) {
        cSubMission* pSub = mSubMissions.mpBegin[nIndex];
        if (pSub != nullptr) {
            cSubMission* pResult = (cSubMission*)(intptr_t)pSub->HasKey(0x2f9998c);
            if (pResult != nullptr)
                return pResult;
        }
        ++nIndex;
    }
    return nullptr;
}

// @ 0x00c55a30
cSubMission* cSPMissionFlight101::GetHerdSubMission()
{
    int32_t nIndex = 0;
    int32_t nCount = (int32_t)(mSubMissions.mpEnd - mSubMissions.mpBegin);
    while (nIndex < nCount) {
        cSubMission* pSub = mSubMissions.mpBegin[nIndex];
        if (pSub != nullptr) {
            cSubMission* pResult = (cSubMission*)(intptr_t)pSub->HasKey(0x2afd27e);
            if (pResult != nullptr)
                return pResult;
        }
        ++nIndex;
    }
    return nullptr;
}

// @ 0x00c55a80
void cSPMissionFlight101::OnSubMissionAccept()
{
    cSubMission* pCurr = GetCurrSubMission();
    if (pCurr == nullptr)
        return;

    cDispatchObject* pObject = (cDispatchObject*)pCurr;
    void* pHerdKey = pCurr->HasKey(0x3470926);
    void* pEradicateKey = pCurr->HasKey(0x2afd27e);
    void* pHuntKey = pCurr->HasKey(0x2f9998c);
    void* pSpiceKey = pCurr->HasKey(0x32a12f0);

    if (pHerdKey == nullptr) {
        if (pEradicateKey != nullptr) {
            PlayMissionEvent(0x501d04fa);
            return;
        }
        if (pHuntKey != nullptr) {
            PlayMissionEvent(0xf2f1fa77);
            return;
        }
        if (pSpiceKey != nullptr) {
            PlayMissionEvent(0x3826c46f);
            mbHerdsInfected = true;
        }
        return;
    }

    PlayMissionEvent(0x50c80446);
    void* pTarget = GetTargetPlanet();
    if (GetActivePlanet() == pTarget && GetUniverseContext() == 0)
        SetupEradicateObjects();
}

// @ 0x00c55b80
char cSPMissionFetch::SetupHerds()
{
    void** pHerdKeys = (void**)mHerdKeys;
    mpSelectedHerd = nullptr;
    pHerdKeys[0] = gHerdKeyDefaults[0];
    pHerdKeys[1] = gHerdKeyDefaults[1];
    pHerdKeys[2] = gHerdKeyDefaults[2];

    cHerd* pHerdList = (cHerd*)GetTargetPlanet();
    int32_t nCount = (int32_t)(pHerdList->mpSpeciesEnd - pHerdList->mpSpeciesBegin);

    for (int32_t i = 0; i < nCount; ++i) {
        void* pSpecies = pHerdList->mpSpeciesBegin[i];
        if (SetMissionState(pSpecies))
            continue;
        mpSelectedHerd = GetHerdEntry(pSpecies);
        break;
    }

    if (mpSelectedHerd != nullptr) {
        cHerdEntry* pEntry = (cHerdEntry*)mpSelectedHerd;
        pHerdKeys[0] = pEntry->mpKeyA;
        pHerdKeys[1] = pEntry->mpKeyB;
        pHerdKeys[2] = pEntry->mpKeyC;
        return 1;
    }
    if (!CheckHerdsComplete())
        return 0;
    ((cMissionTarget*)GetTargetPlanet())->SetupHerdList(0, 0, mHerdKeys);
    return 1;
}

// @ 0x00c55ca0
void cSPMissionFlight101::ValidateHerds()
{
    if (GetUniverseContext() != 0)
        return;
    if (GetActivePlanet() != GetTargetPlanet())
        return;

    if (mHerds.mpBegin == mHerds.mpEnd)
        SetupEradicateObjects();

    int32_t nInfected = 0;
    for (cHerd** pEntry = mHerds.mpBegin; pEntry != mHerds.mpEnd; ++pEntry) {
        cHerd* pHerd = *pEntry;
        for (void** pSpecies = pHerd->mpSpeciesBegin; pSpecies != pHerd->mpSpeciesEnd;
             ++pSpecies) {
            void* pItem = *pSpecies;
            if (*(char*)((uint8_t*)pItem + 0xb62) != 0 &&
                *(char*)((uint8_t*)pItem + 0xb5e) == 0) {
                ++nInfected;
            }
        }
    }

    int32_t nExpected = (int32_t)(intptr_t)((cDispatchObject*)mpEradicateMission)->Call(0x1b0);
    if (nInfected >= nExpected)
        return;
    if (mHerds.mpBegin == mHerds.mpEnd)
        return;

    uint32_t nIndex = RandomUint32Uniform((int32_t)(mHerds.mpEnd - mHerds.mpBegin));
    cHerd* pHerd = mHerds.mpBegin[nIndex];
    uint32_t nEffect = mpEradicateMission->GetDiseaseEffectID();
    AddInfectedAnimalsToHerd(mpInfectionTarget, pHerd, 1, mMissionId, nEffect);
}

// @ 0x00c55d90
int cSPMissionFlight101::Update(void* pParam)
{
    int32_t nResult = (int32_t)(intptr_t)UpdateBase(pParam);
    if (nResult == 3 && mpCurrSubMission == nullptr)
        ((cDispatchObject*)this)->Call(0xf8);
    return nResult;
}

// @ 0x00c55de0
void cSPMissionFlight101::GetUIMediumDescription(void* pParam)
{
    cSubMission* pHerd = GetHerdSubMission();
    if (GetCurrSubMission() == pHerd) {
        if (((cDispatchObject*)pHerd)->CallChar(0xf8) == 0) {
            if (pHerd->mnState == 1) {
                GetText(0xa391d92c, pParam);
                return;
            }
            GetText(0x742ecdb3, pParam);
            return;
        }
    }
    GetSubMissionMediumText(pParam);
}

// @ 0x00c55e50
void cSPMissionFlight101::GetUILongDescription(void* pParam)
{
    cSubMission* pHerd = GetHerdSubMission();
    if (GetCurrSubMission() == pHerd) {
        if (((cDispatchObject*)pHerd)->CallChar(0xf8) == 0) {
            if (pHerd->mnState == 1) {
                GetText(0xfa62ca8f, pParam);
                return;
            }
            GetText(0x151bf3ba, pParam);
            return;
        }
    }
    GetSubMissionLongText(pParam);
}

// @ 0x00c55ec0
bool cSPMissionFlight101::Init()
{
    if (!BaseInit())
        return false;
    return (mpEradicateMission = GetEradicateSubMission()) != nullptr;
}

// @ 0x00c55ef0
void cSPMissionFlight101::PostLoad()
{
    BasePostLoad();
    mpEradicateMission = GetEradicateSubMission();
}

// @ 0x00c55f10
cSPMissionFlight101::cSPMissionFlight101()
{
    BaseCtor();
    mpCurrSubMission = nullptr;
    mpEradicateMission = nullptr;
    mnDiseaseEffectID = 0;
    mbHerdsInfected = false;
    mpVftable = &gVtableFlight101;
    mpVftable2 = &gVtableFlight101Unk;
    mpVftable3 = &gVtableFlight101Extra;
    mHerds.mpBegin = nullptr;
    mHerds.mpEnd = nullptr;
    mHerds.mpCapacity = nullptr;
}

// @ 0x00c55fc0
void* cSPMissionFlight101::Destroy(char bDelete)
{
    mpVftable = &gVtableFlight101;
    mpVftable2 = &gVtableFlight101Unk;
    mpVftable3 = &gVtableFlight101Extra;
    mHerds.Clear();
    BaseDestroy();
    if ((bDelete & 1) != 0)
        operator_delete__(this);
    return this;
}

// @ 0x00c56000
void cSPMissionFlight101::CollectMissionHerds()
{
    NounManager();
    for (cHerd** pEntry = mHerds.mpBegin; pEntry != mHerds.mpEnd; ++pEntry) {
        cHerd* pHerd = *pEntry;
        int32_t nCount = (int32_t)(pHerd->mpSpeciesEnd - pHerd->mpSpeciesBegin);
        for (int32_t i = 0; i < nCount; ++i) {
            void* pSpecies = pHerd->mpSpeciesBegin[i];
            if (pSpecies != nullptr &&
                GetPlanetRecordFromTargetType(pSpecies, 0) == (void*)mnHerdTargetKey) {
                AddDiseaseEffect(pSpecies, (uint32_t)mnDiseaseEffectID, 1);
                MarkSpeciesScanned(pSpecies);
                CollectSpecies(pSpecies);
            }
        }
    }
    mHerds.Clear();
}

// @ 0x00c560c0
void cSPMissionFlight101::HandleMessage(int nMessage, void* pParam)
{
    if (nMessage == 0x2489760) {
        if (GetActivePlanet() == GetTargetPlanet() && GetUniverseContext() == 0) {
            CollectMissionHerds();
        }
    } else if (nMessage == 0x5e37a53) {
        if (GetActivePlanet() == GetTargetPlanet() && GetUniverseContext() == 0 &&
            mHerds.mpEnd != nullptr) {
            SetupEradicateObjects();
            HandleMissionMessage(this, 0x5e37a53, pParam);
            return;
        }
    }
    HandleMissionMessage(this, nMessage, pParam);
}

// @ 0x00c56170
void cSPMissionFlight101::OnSubMissionComplete()
{
    cSubMission* pCurr = GetCurrSubMission();
    if (pCurr == nullptr)
        return;
    if (pCurr->HasKey(0x2f9998c) == nullptr)
        return;
    if (GetActivePlanet() != GetTargetPlanet())
        return;
    if (GetUniverseContext() != 0)
        return;
    CollectMissionHerds();
}
