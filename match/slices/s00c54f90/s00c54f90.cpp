// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00c54f90.
//
// The two multi step space missions and their helpers: the "find the aliens"
// mission with its three stage dependent UI texts, the flight 101 mission that
// tracks the infected herds and its eradicate sub mission, and the fetch
// mission target validation.

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;
typedef int int32_t;
typedef int intptr_t;
#define nullptr 0

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

struct cMethodTable {
    void* mSlots[0x100];
};

// Any retail object that dispatches through a table at offset zero.
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

// A sub mission reference: only the key query at slot 0x0c is dispatched
// virtually, every other slot is reached through cDispatchObject.
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

// The herd record resolved from a species: the three mission keys it carries.
class cHerdEntry {
public:
    uint8_t mPad000[0x504];                     // 0x000
    void* mpKeyA;                               // 0x504
    void* mpKeyB;                               // 0x508
    void* mpKeyC;                               // 0x50c
};

// A key record filled in by the property list lookup (type word at +0x06).
struct cKey {
    uint8_t mPad00[0x06];                       // 0x00
    uint16_t mnType;                            // 0x06
};

// The space object carried by a mission target: the pointing interface lives
// at offset 0x120.
class cSpaceObject {
public:
    uint8_t mPad000[0x120];                     // 0x000
    cDispatchObject mPointingInterface;         // 0x120
};

// The mission event log: the pending event count sits at 0x1b8.
class cEventLog {
public:
    void SetStoryFlag(int nA, int nB);
    void RemoveEvent();

    uint8_t mPad000[0x1b8];                     // 0x000
    uint8_t mnCount;                            // 0x1b8
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

// The fetch mission view: the herd selection state and the search buffers.
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

extern void* gVtableFindAliens;
extern void* gVtableFindAliensUnk;
extern void* gVtableFindAliensExtra;
extern void* gVtableFlight101;
extern void* gVtableFlight101Unk;
extern void* gVtableFlight101Extra;
extern void* gResourceNone;
extern void* gHerdKeyDefaults[3];

// The mission search list owned by the noun manager.
struct cSearchVector {
    void* mpBegin;                              // 0x00
    void* mpEnd;                                // 0x04
    void* mpCapacity;                           // 0x08
};

class cNounManager {
public:
    cSearchVector* GetAlienSearchList();
    cSearchVector* GetHerdSearchList();
};

// The planet target reached through the planet lookup.
class cMissionTarget {
public:
    void* SetupHerdList(uint32_t nFlagA, uint32_t nFlagB, void* pHerdKeys);
    cDispatchObject mObject;                    // 0x00
};

// ---------------------------------------------------------------------------
// retail services
// ---------------------------------------------------------------------------
int32_t GetUniverseContext();
void* GetActivePlanet();
int32_t GetPlayerEmpire();
void* GetTargetPlanet(void* pMission);
void* NounManager();
void* SpaceGameGet();
void* GetMissionManager();
void* GetMissionManager(uint32_t nMissionId);
void* GetPropertyAsKeyArray();
void* GetPlanetRecordFromTargetType(void* pMission, uint32_t nType);
uint32_t ReadTargetPlanetType();
char CompareResourceHandle(const void* pHandle, const void* pValue);
void* FindAliensSubMission(void* pSearch, void* pTarget);
void* FindHerdSubMission(void* pSearch, void* pTarget);
void* ProcessAliensSubMission(void* pSearch, void* pOut);
void* ProcessToolSubMission(void* pTool, void* pOut);
void AssignRefCount(void* pDst, void* pValue);
void* GetMissionText(uint8_t* pBuffer, uint32_t nValue);
void* GetStringKey(void* pString);
void ShowDialogue(void* pKey);
void AssignString(void* pDst, void* pValue);
void AddDiseaseEffect(void* pSpecies, uint32_t nEffect, int nValue);
void MarkSpeciesScanned(void* pSpecies);
void CollectSpecies(void* pSpecies);
void RemoveHerd(void* pHerd);
void SetStoryFlag(int nA, int nB);
void DestroyMissionObjects(void* pMission);
void TriggerUIUpdate(void* pMission);
void BaseMissionInitFindAliens(void* pMission);
void BaseMissionInitFlight101(void* pMission);
char BaseMissionInit(void* pMission);
void* GetHerdEntry(void* pSpecies);
void RemoveAliensHerd(void* pPlanet);
char CheckMissionProgress();
char CheckAliensComplete();
char CheckHerdsComplete();
char SetMissionState(void* pMission);
void HandleMissionMessage(void* pMission, int nMessage, void* pParam);
void SetMissionFlag(void* pTarget, int nValue);
void OnAcceptMission(void* pMission);
void OnRejectMission(void* pMission);
void IncrementMissionCounter(void* pMission, int nValue);
char UnlockMissionState();
void* UpdateMission(void* pMission, void* pParam);
void PlayMissionEvent(uint32_t nEvent);
void AddInfectedAnimalsToHerd(void* pOwner, void* pHerd, int nCount, int nMissionId,
                              uint32_t nEffect);
void* __stdcall GetObjectFromKey(void* pKey, int nMode);
void RemoveHerdsFromInventory(void* pInventory);
void ClearHerdVector(void* pVector);
uint32_t RandomUint32Uniform(int32_t nRange);
void RemoveEventLogEntry(void* pLog);
void operator_delete__(void* pMemory);

// ---------------------------------------------------------------------------
// 0x00c54f90  cSPMissionFetch::VerifyTargetPlanet
// ---------------------------------------------------------------------------
// @ 0x00c54f90
char cSPMissionFetch::VerifyTargetPlanet(void* pTarget, void* pOut)
{
    if (GetUniverseContext() != 0)
        return 0;

    void* pTargetPlanet = GetTargetPlanet();
    if (GetActivePlanet() != pTargetPlanet)
        return 0;

    if (mnState != 0)
        return 0;

    uint32_t nType = mnTargetType;
    if ((int32_t)nType >= 0x3e994b2c) {
        if (nType == 0x69412983) {
            cSearchVector* pSearch = ((cNounManager*)NounManager())->GetHerdSearchList();
            if (pSearch->mpBegin == pSearch->mpEnd)
                return 0;
            void* pFound = FindHerdSubMission(pSearch, pTarget);
            AssignRefCount(&pFound, pFound);
            if (pTarget == nullptr)
                return 0;
            void* pPosition = ((cSpaceObject*)pTarget)->mPointingInterface.Call(0x2c);
            *(Vec3*)pOut = *(Vec3*)pPosition;
            ((cDispatchObject*)pTarget)->Call(0x04);
            return 1;
        }
        if (nType != 0x736c417f)
            return 0;
        if (CompareResourceHandle(mToolResource, gResourceNone))
            return (char)(intptr_t)ProcessToolSubMission(mSearchB, pOut);
        return (char)(intptr_t)ProcessAliensSubMission(mSearchA, pOut);
    }

    if (nType == 0x3e994b2b) {
        cSearchVector* pSearch = ((cNounManager*)NounManager())->GetHerdSearchList();
        if (pSearch->mpBegin == pSearch->mpEnd)
            return 0;
        void* pFound = FindHerdSubMission(pSearch, pTarget);
        AssignRefCount(&pFound, pFound);
        if (pTarget == nullptr)
            return 0;
        void* pPosition = ((cSpaceObject*)pTarget)->mPointingInterface.Call(0x2c);
        *(Vec3*)pOut = *(Vec3*)pPosition;
        ((cDispatchObject*)pTarget)->Call(0x04);
        return 1;
    }
    if (nType == 0xfb3b1635) {
        cSearchVector* pSearch = ((cNounManager*)NounManager())->GetAlienSearchList();
        if (pSearch->mpBegin == pSearch->mpEnd)
            return 0;
        void* pFound = FindAliensSubMission(pSearch, pTarget);
        AssignRefCount(&pFound, pFound);
        if (pTarget == nullptr)
            return 0;
        void* pPosition = ((cSpaceObject*)pTarget)->mPointingInterface.Call(0x2c);
        *(Vec3*)pOut = *(Vec3*)pPosition;
        ((cDispatchObject*)pTarget)->Call(0x04);
        return 1;
    }
    if (nType == 0x6d5c48c)
        return (char)(intptr_t)ProcessToolSubMission(mSearchB, pOut);
    if (nType == 0x2dc69129)
        return (char)(intptr_t)ProcessAliensSubMission(mSearchA, pOut);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c55130  cMissionFindAliens::cMissionFindAliens
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c552d0  cMissionFindAliens::GetUIMediumDescription
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55330  cMissionFindAliens::GetUILongDescription
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55390  cMissionFindAliens::Update
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55500  cMissionFindAliens::SetContactGrob
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55540  cMissionFindAliens::Init
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c555d0  cMissionFindAliens::HandleMessage
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55660  cMissionFindAliens::GetUIShortDescription
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c557c0  cMissionFindAliens::BindTarget
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c557f0  cSPMissionFlight101::Shutdown
// ---------------------------------------------------------------------------
// @ 0x00c557f0
void cSPMissionFlight101::Shutdown()
{
    BaseShutdown();
    mpEradicateMission = nullptr;
}

// ---------------------------------------------------------------------------
// 0x00c55810  cSPMissionFlight101::SetupEradicateObjects
// ---------------------------------------------------------------------------
// @ 0x00c55810
void cSPMissionFlight101::SetupEradicateObjects()
{
    cSubMission* pSub = mpEradicateMission;
    if (pSub == nullptr)
        return;

    uint32_t nEffect = pSub->GetDiseaseEffectID();
    mnDiseaseEffectID = (int32_t)nEffect;

    cDispatchObject* pObject = (cDispatchObject*)pSub;
    void* pA = pObject->Call3(0x1b8, (uint32_t)mMissionId, nEffect, &mHerds);
    void* pB = pObject->Call1(0x1b4, (uint32_t)(intptr_t)pA);
    void* pC = pObject->Call1(0x1b0, (uint32_t)(intptr_t)pB);
    void* pText = GetMissionText(mTextBuilder, (uint32_t)(intptr_t)pC);
    void* pKey = GetStringKey(pText);
    ShowDialogue(pKey);
}

// ---------------------------------------------------------------------------
// 0x00c558f0  BaseOnSubMissionComplete
// ---------------------------------------------------------------------------
// @ 0x00c558f0
void BaseOnSubMissionComplete()
{
    void* pInventory = ((cDispatchObject*)SpaceGameGet())->Call(0x00);
    if (pInventory != nullptr) {
        ((cDispatchObject*)pInventory)->Call(0x00);
    }
    ((cDispatchObject*)GetMissionManager())->Call1(0x00, 1);
}

// ---------------------------------------------------------------------------
// 0x00c55920  cSPMissionFlight101::OnReject
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55970  cSPMissionFlight101::OnAccept
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c559e0  cSPMissionFlight101::GetEradicateSubMission
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55a30  cSPMissionFlight101::GetHerdSubMission
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55a80  cSPMissionFlight101::OnSubMissionAccept
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55b80  cSPMissionFetch::SetupHerds
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55ca0  cSPMissionFlight101::ValidateHerds
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55d90  cSPMissionFlight101::Update
// ---------------------------------------------------------------------------
// @ 0x00c55d90
int cSPMissionFlight101::Update(void* pParam)
{
    int32_t nResult = (int32_t)(intptr_t)UpdateBase(pParam);
    if (nResult == 3 && mpCurrSubMission == nullptr)
        ((cDispatchObject*)this)->Call(0xf8);
    return nResult;
}

// ---------------------------------------------------------------------------
// 0x00c55de0  cSPMissionFlight101::GetUIMediumDescription
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55e50  cSPMissionFlight101::GetUILongDescription
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55ec0  cSPMissionFlight101::Init
// ---------------------------------------------------------------------------
// @ 0x00c55ec0
bool cSPMissionFlight101::Init()
{
    if (!BaseInit())
        return false;
    return (mpEradicateMission = GetEradicateSubMission()) != nullptr;
}

// ---------------------------------------------------------------------------
// 0x00c55ef0  cSPMissionFlight101::PostLoad
// ---------------------------------------------------------------------------
// @ 0x00c55ef0
void cSPMissionFlight101::PostLoad()
{
    BasePostLoad();
    mpEradicateMission = GetEradicateSubMission();
}

// ---------------------------------------------------------------------------
// 0x00c55f10  cSPMissionFlight101::cSPMissionFlight101
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c55fc0  cSPMissionFlight101::Destroy
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c56000  cSPMissionFlight101::CollectMissionHerds
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c560c0  cSPMissionFlight101::HandleMessage
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c56170  cSPMissionFlight101::OnSubMissionComplete
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c56260  cSPMissionFlight101::OnAbort
// ---------------------------------------------------------------------------
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
