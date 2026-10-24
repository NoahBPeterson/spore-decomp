// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s0102be20.
//
// The space stage gameplay hooks around creatures and tribes: the posse
// formation used by the flocking tribe members, the release / update paths of
// a posse, the destroy and target selection paths, the mission and spice
// helpers and the comm screen shutdown.

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

struct Vec4 {
    float mX;
    float mY;
    float mZ;
    float mW;
};

// Retained object pointer array: two iterators and the allocator slot.
struct cObjectVector {
    void** mpBegin;                             // 0x00
    void** mpEnd;                               // 0x04
    void** mpCapacity;                          // 0x08
};

struct cIntVector {
    uint32_t* mpBegin;                          // 0x00
    uint32_t* mpEnd;                            // 0x04
    uint32_t* mpCapacity;                       // 0x08
};

// The creature data block shared by the posse functions.
struct cCreatureData {
    uint8_t mPad000[0x68c];                     // 0x000
    void* mpMission;                            // 0x68c
    uint8_t mPad690[0x04];                      // 0x690
    Vec3 mPosseOffset;                          // 0x694
    Vec3 mPosseAxis;                            // 0x6a0
    uint8_t mPad6ac[0x04];                      // 0x6ac
    int mnPosseIndex;                           // 0x6b0
    uint8_t mPad6b4[0x60];                      // 0x6b4
    int mnState;                                // 0x714
};

struct cMissionKey;
struct cMissionData {
    uint8_t mPad000[0x13c];                     // 0x000
    cMissionKey* mpMissionKey;                  // 0x13c
};

struct cPlanetData {
    uint8_t mPad000[0x58];                      // 0x000
    int mnPlanetType;                           // 0x058
    uint8_t mPad05c[0x2c0];                     // 0x05c
    uint8_t mPad31c[0x20];                      // 0x31c
};

struct cSpaceGameSub;
struct cSpaceGame {
    uint8_t mPad00[0x18];                       // 0x00
    cSpaceGameSub* mpSubObject;                 // 0x18
};

extern float gPosseFlockOffsets[3];
extern float gPosseRadius;
extern float gPosseAxisX;
extern float gPosseAxisY;
extern float gPosseAxisZ;
extern float gPosseScaleA;
extern float gPosseScaleB;
extern float gPosseScaleC;
extern void* gPropertyDatabase;
extern void* gColorProperties;

// The mission key container that resolves reward keys to embassy entries.
struct cMissionKey {
    void* GetRewardTable();
};

// A mission instance: the reward table lookup and the completion step.
struct cMission {
    void* Call(int nSlot) {
        return ((void* (*)(void*))((void**)*(void**)this)[nSlot >> 2])(this);
    }
};

struct cMissionStep {
    void CompleteStep(void* pPlanet, void* pLookup, uint32_t nKeyA, uint32_t nKeyB,
                      void* pMission, int nFlags);
};

struct cMissionManager {
    void* CreateMissionFromID(void* pParam3, cMissionKey* pKey, int nCount, int nFlags);
    void* FindMission(int nCount, cMissionKey* pKey);
};

struct cSpaceGamePart {
    void* ResolvePlanetPart(void* pPlanet);
};

struct cTradeRoute {
    int RemoveTradeRoute(void* pRoute);
};

struct cTradeRouteManager : cTradeRoute {
};

struct cNounManager {
    cTradeRouteManager* GetTradeRouteManager();
};

struct cTribe {
    int RemoveTradeRouteReward(uint32_t nId, int nValue);
};

struct cPlayer {
    cTribe* GetTribe();
};

struct cSpiceManager {
    void AutoAddSpiceToCargo(void* pData);
};

struct cCommScreen {
    void SetSpeakerText();
    void SetResponseCount();
};

struct cRewardReceiver {
    void Apply();
};

struct cSpaceGameSub {
    void StopStory();
    void PauseStory();
};

// ---------------------------------------------------------------------------
// retail services
// ---------------------------------------------------------------------------
void* NounManager();
void* GetCreatureDataVector();
void* GetPlanetDataVector();
void* GetCombatantDataVector();
void* GetCurrentGameMode();
void* BeginGameModeIteration();
void* SpaceGameGet();
void* SpaceGameGet(uint32_t nA, int nB);
void* GetPlayerTribe();
void* ResolveNoun(void* pNoun);
void* GetSpaceTradeRouteManager(void* pOwner);
void* GetMissionManager(void* pA);
void* GetPlayerHomePlanet();
void* GetActivePlanet();
void* GetPlayerEmpire();
void* GetUniverseContext();
void* GetPropertyList(uint32_t nId);
void* ObjectTemplateDB();
void* GetSpaceRelationshipTuning();
void* GetUFO();
void* GetLayout(uint32_t nId);
void* CommScreen();
void* TimerManager();
void* RandomMath();
void* MissionResultLookup(void* pA, void* pB);
char ResolveMissionKey(void* pKey);
char ResolveSpaceObject(void* pObject);
char ResolvePlanet(void* pPlanet);
char ResolveMissionManager(void* pManager);
char IsTribeOwned(void* pOwner);
char CheckMissionAllowed(void* pOwner, void* pMission);
char DoMissionsPreventHostility(void* pOwner, void* pMission);
char GetPropertyAsColorRGB(void* pProperties, uint32_t nId, void* pOut);
char TestAchievement(uint32_t nId, int nA);
int RemoveTradeRoute(void* pManager, void* pRoute);
int GetCreatureCount(void* pData);
int GetCombatantDamageState(void* pCombatant);
int GetLanguageId(void* pCreature);
int GetEmpireId(void* pCreature);
int GetLanguageOwner(int nLanguage);
int GetRelationshipValue(void* pCreature, void* pMission);
int GetMissionIndex(void* pMission);
int GetEmbassyData(void* pA, void* pB);
int IsCreatureComplete(void* pCreature);
uint32_t RandomUint32Uniform(void* pRandom, int nRange);
float fsinf(float fAngle);
float fcosf(float fAngle);
void AiRemoveCreature(int nFlags);
void ReleaseCreatureData(void* pData);
void ReleaseRef(void* pObject);
void AddRef(void* pObject);
void RemoveTradeRouteReward(void* pA, int nValue);
void AutoAddSpiceToCargo(void* pUFO, void* pData);
void GiveMissionReward(void* pA, void* pB);
void CompleteMissionStep(void* pA, void* pB, uint32_t nId, uint32_t nValue);
void AutoTestAchievement(void* pController, uint32_t nId, int nValue);
void AddAchievementScore(int nValue);
void ApplyRelationshipChange(void* pA, uint32_t nId, uint32_t nValue);
void* CreateWantedMission(void* pPlanet, void* pKey);
void* SetMissionResult(void* pA, void* pB);
void* GetSpiceManager();
void* GetRewardReceiver(uint32_t nId);
void* GetMissionStepHandler();
void* GetMissionManager();
void SetCreatureMission(void* pCreature, void* pB);
void* SelectCombatTargets(void* pA, void* pB);
void ClearActionGroup(int nSlot);
void ResetCreatureAction(void* pCreature);
void UpdateMissionState(void* pCreature);
void RemoveCreatureFromGroup(void* pCreature);
void RemoveNounFromManager(void* pManager, void* pNoun);
void SetSpeakerText(void* pText);
void SetResponseCount(uint32_t nCount);
void SetEmpireAvailable(uint32_t nValue);
void StopStory(void* pSub);
void PauseStory(void* pSub);
void ConstraintInit(void* pOut, uint32_t nA, int nB, uint32_t nC);
void ConstraintSetValue(void* pConstraint);
void VectorPushBack(void* pVector, void* pValue);
void VectorErase(void* pVector, void* pFirst, void* pLast);
void VectorDestroy(void* pVector);
void FilterApply(void* pOut, uint32_t nCount);
void FilterEvaluate(void* pA, void* pB);
void MatchApply(void* pOut, uint32_t nCount);
void MatchEvaluate(void* pA, void* pB);
void operator_delete__(void* pMemory);
char BigCatQuery(void* pA, void* pB);

// ---------------------------------------------------------------------------
// 0x0102be20  PositionPosseMembers
// ---------------------------------------------------------------------------
// @ 0x0102be20
void PositionPosseMembers()
{
    void* pManager = NounManager();
    (void)pManager;
    cObjectVector* pCreatures = (cObjectVector*)GetCreatureDataVector();

    int nCount = (int)(((uint8_t*)pCreatures->mpEnd - (uint8_t*)pCreatures->mpBegin) >> 2);
    int nPlaced = 0;
    int nIndex = 0;
    int nFlockCount = 0;
    (void)nPlaced;

    BeginGameModeIteration();
    void* pList = nullptr;
    (void)pList;
    for (int i = 0; i < nCount; ++i) {
        cCreatureData* pData = (cCreatureData*)pCreatures->mpBegin[i];
        if (pData->mnState != 3)
            continue;

        pData->mPosseOffset.mX = gPosseFlockOffsets[0];
        pData->mPosseOffset.mY = gPosseFlockOffsets[1];
        pData->mPosseOffset.mZ = gPosseFlockOffsets[2];
        pData->mnPosseIndex = nIndex;

        float fAngle = ((float)nIndex / (float)nFlockCount) * gPosseRadius * 0.5f;
        float fSin = fsinf(fAngle);
        float fCos = fcosf(fAngle);

        float fX = gPosseAxisX * fSin;
        float fY = gPosseAxisY * fSin;
        float fZ = gPosseAxisZ * fSin;

        pData->mPosseAxis.mX = ((fY * fZ - fCos * fX) * gPosseScaleB +
                               (fCos * fY + fX * fZ) * gPosseScaleC) * 2.0f +
                              (1.0f - (fX * fX + fZ * fZ) * 2.0f) * gPosseScaleA;
        pData->mPosseAxis.mY = ((fZ * fX - fCos * fY) * gPosseScaleB +
                               (fCos * fZ + fY * fX) * gPosseScaleC) * 2.0f +
                              (1.0f - (fZ * fZ + fY * fY) * 2.0f) * gPosseScaleA;
        pData->mPosseAxis.mZ = ((fCos * fX + fZ * fY) * gPosseScaleC +
                               (fX * fY - fCos * fZ) * gPosseScaleA) * 2.0f +
                              (1.0f - (fY * fY + fX * fX) * 2.0f) * gPosseScaleB;

        ++nIndex;
        nFlockCount = nIndex;
    }
}

// ---------------------------------------------------------------------------
// 0x0102c0c0  ReleaseCreaturePosse
// ---------------------------------------------------------------------------
// @ 0x0102c0c0
void ReleaseCreaturePosse(void* pNoun)
{
    if (pNoun == nullptr)
        return;
    if (ResolveSpaceObject(pNoun) == 0)
        return;

    cObjectVector* pCreatures = (cObjectVector*)GetCreatureDataVector();
    (void)pCreatures;
    cObjectVector list;
    list.mpBegin = nullptr;
    list.mpEnd = nullptr;
    list.mpCapacity = nullptr;

    int nCount = (int)(((uint8_t*)list.mpEnd - (uint8_t*)list.mpBegin) >> 2);
    for (int i = 0; i < nCount; ++i) {
        cCreatureData* pData = (cCreatureData*)(intptr_t)list.mpBegin[i];
        int nState = pData->mnState;
        if ((nState == 2 || nState == 4 || nState == 5 || nState == 0xb) &&
            IsTribeOwned(pNoun) == 0)
            ResetCreatureAction(list.mpBegin[i]);
    }
    for (void** p = list.mpBegin; p != list.mpEnd; ++p) {
        if (*p != nullptr)
            ReleaseRef(*p);
    }
    if (list.mpBegin != nullptr && ((uint32_t*)list.mpBegin)[-1] != 0)
        operator_delete__(list.mpBegin);
}

// ---------------------------------------------------------------------------
// 0x0102c1a0  UpdatePosseMembers
// ---------------------------------------------------------------------------
// @ 0x0102c1a0
void UpdatePosseMembers(void* pNest)
{
    ResolveNoun(pNest);
    if (ResolveSpaceObject(pNest) == 0)
        return;

    cIntVector* pList = (cIntVector*)GetCreatureCount(nullptr);
    int nCount = (int)(((uint8_t*)pList->mpEnd - (uint8_t*)pList->mpBegin) >> 2);
    int nLoop = nCount;
    for (int i = 0; i < nLoop; ++i) {
        void* pCreature = (void*)(intptr_t)pList->mpBegin[i];
        void* pMember = nullptr;
        ResolveNoun(pCreature);
        (void)pMember;
        if (ResolvePlanet(pMember) == 0) {
            ClearActionGroup(0);
            continue;
        }

        cObjectVector* pCreatures = (cObjectVector*)GetCreatureDataVector();
        int nCreatureCount = (int)(((uint8_t*)pCreatures->mpEnd -
                                    (uint8_t*)pCreatures->mpBegin) >> 2);
        uint32_t* pBuffer = nullptr;
        if (nCreatureCount != 0)
            pBuffer = (uint32_t*)pCreatures->mpBegin;
        cObjectVector group;
        group.mpBegin = (void**)pBuffer;
        group.mpEnd = (void**)pBuffer;

        int nGroup = (int)(((uint8_t*)group.mpEnd - (uint8_t*)group.mpBegin) >> 2);
        for (int j = 0; j < nGroup; ++j) {
            cCreatureData* pData = (cCreatureData*)(intptr_t)pBuffer[j];
            if (pData->mnState == 6 && IsTribeOwned(pMember) == 0)
                ResetCreatureAction((void*)(intptr_t)pBuffer[j]);
        }
        for (void** p = group.mpBegin; p != group.mpEnd; ++p) {
            if (*p != nullptr)
                ReleaseRef(*p);
        }
        if (pBuffer != nullptr && pBuffer[-1] != 0)
            operator_delete__(pBuffer);
        ClearActionGroup(0);
    }
}

// ---------------------------------------------------------------------------
// 0x0102c340  DestroyCreature
// ---------------------------------------------------------------------------
// @ 0x0102c340
void DestroyCreature(cCreatureData* pCreature, uint32_t nFlags)
{
    void* pManager = NounManager();
    cObjectVector* pCreatures = (cObjectVector*)GetCreatureDataVector();
    int nCount = (int)(((uint8_t*)pCreatures->mpEnd - (uint8_t*)pCreatures->mpBegin) >> 2);

    for (int i = 0; i < nCount; ++i) {
        cCreatureData* pData = (cCreatureData*)pCreatures->mpBegin[i];
        if (pData == nullptr)
            continue;
        if (pData->mpMission != (void*)pCreature)
            continue;
        void* pMission = pData->mpMission;
        if (pMission == nullptr)
            continue;
        pData->mpMission = nullptr;
        ReleaseRef(pMission);
    }

    if (pCreature->mPad000[0] && *(int*)((uint8_t*)pCreature + 0x714) == 3) {
        (void)0;
    }
    if (*(int*)((uint8_t*)pCreature + 0x714) == 3) {
        void* pResult = ((void* (*)(void*, uint32_t))((void**)*(void**)pCreature)[0x4c >> 2])(
            pCreature, nFlags);
        BeginGameModeIteration();
        (void)pResult;
    }

    if (GetCurrentGameMode() == (void*)0x01654c05) {
        void* pGame = SpaceGameGet();
        if (pGame != nullptr) {
            void* pSub = *(void**)((uint8_t*)pGame + 0x18);
            (void)pSub;
            void* pMinimap = nullptr;
            (void)pMinimap;
        }
    }

    (void)pManager;
    void* pSlot = *(void**)((uint8_t*)pCreature + 0x508);
    (void)pSlot;
    RemoveCreatureFromGroup(pCreature);
    RemoveNounFromManager(pManager, pCreature);
}

// ---------------------------------------------------------------------------
// 0x0102c460  PickCombatTarget
// ---------------------------------------------------------------------------
// @ 0x0102c460
cCreatureData* PickCombatTarget(cCreatureData* pCreature)
{
    void* pManager = NounManager();
    (void)pManager;
    void* pCombatants = GetCombatantDataVector();
    void* pSource = ((void* (*)(void*))((void**)*(void**)pCreature)[0x2c >> 2])(pCreature);
    (void)pSource;
    void* pResult = SelectCombatTargets(pCombatants, pSource);
    if (pResult == nullptr)
        return nullptr;

    cObjectVector list;
    list.mpBegin = nullptr;
    list.mpEnd = nullptr;
    list.mpCapacity = nullptr;
    while (list.mpBegin != list.mpEnd) {
        uint32_t nPick = RandomUint32Uniform(RandomMath(),
                                             (int)(((uint8_t*)list.mpEnd -
                                                    (uint8_t*)list.mpBegin) >> 2));
        cCreatureData* pCandidate = (cCreatureData*)list.mpBegin[nPick];
        if (GetCombatantDamageState((uint8_t*)pCandidate + 0x588) == 0) {
            if (pCandidate == nullptr) {
                UpdateMissionState(pCreature);
                return nullptr;
            }
            UpdateMissionState(pCandidate);
            return (cCreatureData*)((uint8_t*)pCandidate + 0x588);
        }
        list.mpEnd = (void**)((uint8_t*)list.mpEnd - 4);
    }
    UpdateMissionState(pCreature);
    return nullptr;
}

// ---------------------------------------------------------------------------
// 0x0102c600  IsHostileToAll
// ---------------------------------------------------------------------------
// @ 0x0102c600
char IsHostileToAll(void* pPlanet)
{
    if (ResolveSpaceObject(pPlanet) == 0)
        return 0;
    int nMode = GetLanguageId(nullptr);
    if (nMode != 5 && nMode != 4)
        return 0;

    cObjectVector* pCreatures = (cObjectVector*)GetCreatureDataVector();
    void** pBegin = pCreatures->mpBegin;
    int nCount = (int)(((uint8_t*)pCreatures->mpEnd - (uint8_t*)pBegin) >> 2);
    for (int i = 0; i < nCount; ++i) {
        void* pCreature = pBegin[i];
        void* pOwner = ((void* (*)(void*))((void**)*(void**)pCreature)[0x4c >> 2])(pCreature);
        (void)pOwner;
        int nEmpire = GetLanguageOwner(0);
        int nPlayerEmpire = GetEmpireId(nullptr);
        if (nEmpire == nPlayerEmpire)
            continue;
        if ((float)((int*)pCreature)[0x1d2] < 100.0f) {
            if (0.0f < (float)((int*)pCreature)[0x88])
                goto CheckPrevention;
            if (nEmpire != 0) {
                (void)CheckMissionAllowed((void*)(intptr_t)nEmpire, (void*)(intptr_t)nPlayerEmpire);
                if (IsCreatureComplete((void*)(intptr_t)nEmpire) != 0)
                    goto CheckPrevention;
            }
        }
        continue;

CheckPrevention:
        {
            void* pMission = nullptr;
            (void)pMission;
            void* pManager = GetMissionManager(pPlanet);
            (void)pManager;
            if (DoMissionsPreventHostility(pPlanet, (void*)0x016de144) == 0)
                return 1;
            return 0;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x0102c720  GetCreatureColorProperty
// ---------------------------------------------------------------------------
// @ 0x0102c720
char GetCreatureColorProperty(void* pUnused, void* pObject, void* pOut)
{
    (void)pUnused;
    if (GetCurrentGameMode() != (void*)0x01654c05)
        return 0;
    if (pObject == nullptr)
        return 0;

    void* pType = ((void* (*)(void*))((void**)*(void**)pObject)[0x20 >> 2])(pObject);
    uint32_t nProperty = 0;
    if (pType == (void*)0x018ebadc) {
        cCreatureData* pCreature =
            (cCreatureData*)((void* (*)(void*, uint32_t))((void**)*(void**)pObject)[0xc >> 2])(
                pObject, 0xb033b403);
        if (pCreature == nullptr)
            return 0;
        if (pCreature->mnState == 0)
            return 0;
        if (pCreature->mnState == 3) {
            nProperty = 0x2587f996;
        } else {
            uint32_t nFlag = 0;
            if (GetUniverseContext() == nullptr) {
                void* pPlanet = GetActivePlanet();
                nFlag = (uint32_t)IsHostileToAll(pPlanet);
            }
            char bHostile = (char)GetEmbassyData((void*)pCreature, (void*)(intptr_t)nFlag);
            nProperty = (bHostile != 0) ? 0xc10fd3ec : 0x62872966;
        }
    } else {
        void* pPlanet = GetActivePlanet();
        char bHostile = IsHostileToAll(pPlanet);
        nProperty = (bHostile != 0) ? 0xc10fd3ec : 0x62872966;
    }

    if (gColorProperties != nullptr &&
        GetPropertyAsColorRGB(gColorProperties, nProperty, pOut) != 0)
        return 1;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x0102c7f0  ApplyFilterConstraints
// ---------------------------------------------------------------------------
// @ 0x0102c7f0
void ApplyFilterConstraints(void* pUnused, char bSecond)
{
    (void)pUnused;
    Vec3 filter;
    filter.mX = 0.0f;
    filter.mY = 0.0f;
    filter.mZ = 0.0f;

    void* pDatabase = ObjectTemplateDB();
    (void)pDatabase;
    uint8_t constraint[0x30];
    ConstraintInit(constraint, 0x2dd90af, 0, 0x476a98c7);

    if (bSecond != 0) {
        ConstraintInit(constraint, 0x3cc89b1, 0, 0x913b23be);
    }

    FilterApply(&filter, 1);
    if ((void*)0 != (void*)0)
        FilterEvaluate(nullptr, nullptr);
    if (BigCatQuery(nullptr, nullptr) != 0)
        (void)0;
    MatchApply(&filter, 1);
    MatchEvaluate(&filter, nullptr);
}

// ---------------------------------------------------------------------------
// 0x0102c980  ClearTradeRoute
// ---------------------------------------------------------------------------
// @ 0x0102c980
void ClearTradeRoute(void* pRoute)
{
    int nDelta = ((cNounManager*)NounManager())->GetTradeRouteManager()->RemoveTradeRoute(pRoute);
    if (nDelta > 0) {
        ((cPlayer*)SpaceGameGet())->GetTribe()->RemoveTradeRouteReward(0x19, -nDelta);
    }
}

// ---------------------------------------------------------------------------
// 0x0102c9e0  StartMission
// ---------------------------------------------------------------------------
// @ 0x0102c9e0
void StartMission(void* pPlanet, cMissionData* pMissionData, void* pParam3)
{
    void* pCount = ((cSpaceGamePart*)NounManager())->ResolvePlanetPart(pPlanet);

    cMissionKey* pKey = pMissionData->mpMissionKey;
    cMission* pMission;
    if (pCount != nullptr && pParam3 != nullptr) {
        pMission = (cMission*)((cMissionManager*)GetMissionManager())
                       ->CreateMissionFromID(pParam3, pKey, (int)(intptr_t)pCount, 0);
    } else {
        pMission = (cMission*)((cMissionManager*)GetMissionManager())
                       ->FindMission((int)(intptr_t)pCount, pKey);
    }

    uint32_t nKeyA;
    uint32_t nKeyB;
    if (pMission != nullptr) {
        nKeyA = (uint32_t)(intptr_t)pMission->Call(0xa4);
        nKeyB = 0x8b756f4b;
    } else {
        nKeyA = 0xc8fbf7d7;
        nKeyB = (pKey != GetPlayerHomePlanet()) ? 0x8053662e : 0x303878af;
    }

    void* pLookup = pKey->GetRewardTable();
    ((cMissionStep*)GetMissionStepHandler())
        ->CompleteStep(pPlanet, pLookup, nKeyA, nKeyB, pMission, 0);
}

// ---------------------------------------------------------------------------
// 0x0102caa0  CollectSpice
// ---------------------------------------------------------------------------
// @ 0x0102caa0
void CollectSpice(void* pPlanet, cMissionData* pData)
{
    cSpiceManager* pManager = (cSpiceManager*)GetSpiceManager();
    pManager->AutoAddSpiceToCargo(pData);
    ((cMissionStep*)GetMissionStepHandler())
        ->CompleteStep(pPlanet, pData->mpMissionKey->GetRewardTable(), 0xc8fbf7d7,
                       0x2ea8fb98, 0, 0);
}

// ---------------------------------------------------------------------------
// 0x0102cae0  GiveGift
// ---------------------------------------------------------------------------
// @ 0x0102cae0
void GiveGift(void* pPlanet, uint32_t nGiftType)
{
    int nCost;
    uint32_t nReward;
    if (nGiftType == 0) {
        void* pTuning = GetSpaceRelationshipTuning();
        nCost = *(int*)((uint8_t*)pTuning + 0x78);
        pTuning = GetSpaceRelationshipTuning();
        nReward = *(uint32_t*)((uint8_t*)pTuning + 0x84);
    } else if (nGiftType == 1) {
        void* pTuning = GetSpaceRelationshipTuning();
        nCost = *(int*)((uint8_t*)pTuning + 0x7c);
        pTuning = GetSpaceRelationshipTuning();
        nReward = *(uint32_t*)((uint8_t*)pTuning + 0x88);
    } else {
        if (nGiftType != 2)
            return;
        void* pTuning = GetSpaceRelationshipTuning();
        nCost = *(int*)((uint8_t*)pTuning + 0x80);
        pTuning = GetSpaceRelationshipTuning();
        nReward = *(uint32_t*)((uint8_t*)pTuning + 0x8c);
    }

    void* pEmpire = GetPlayerEmpire();
    if (pEmpire == nullptr)
        return;
    if (GetLanguageOwner(0) < nCost)
        return;

    (void)TestAchievement(0x77893b39, 1);
    AutoTestAchievement(nullptr, 0x77893b39, 1);
    AddAchievementScore(-nCost);
    CheckMissionAllowed(nullptr, nullptr);

    int nBefore = GetRelationshipValue(pPlanet, *(void**)((uint8_t*)pEmpire + 0x84));
    ApplyRelationshipChange(pPlanet, *(uint32_t*)((uint8_t*)pEmpire + 0x84), 0x526e51f);
    (void)nReward;
    int nAfter = GetRelationshipValue(pPlanet, *(void**)((uint8_t*)pEmpire + 0x84));
    uint32_t nResult;
    if ((float)nBefore == (float)nAfter) {
        GetActivePlanet();
        nResult = 0x661d5b89;
    } else {
        GetActivePlanet();
        nResult = 0x8efa19dc;
    }

    void* pLookup = MissionResultLookup((void*)0xc8fbf7d7, (void*)(intptr_t)nResult);
    SetMissionResult(pPlanet, pLookup);
    CompleteMissionStep(pPlanet, pLookup, 0xc8fbf7d7, nResult);
}

// ---------------------------------------------------------------------------
// 0x0102cc30  CreateNewRaid
// ---------------------------------------------------------------------------
// @ 0x0102cc30
void CreateNewRaid(void* pPlanet, cMissionData* pMission)
{
    ResolveNoun(pPlanet);
    void* pLanguage = (void*)GetLanguageOwner(0);
    uint32_t nMission = 0xffffffff;
    switch (*(uint32_t*)((uint8_t*)pLanguage + 0x58)) {
    case 0:
    case 9:
    case 0x12:
        nMission = 0x5d182075;
        break;
    case 1:
    case 10:
        nMission = 0x2b795e0d;
        break;
    case 2:
    case 0xb:
        nMission = 0x4b708009;
        break;
    case 3:
    case 0xc:
        nMission = 0xc052cccf;
        break;
    case 4:
    case 0xd:
        nMission = 0x29e235c0;
        break;
    case 5:
    case 0xe:
        nMission = 0xf46a1fc4;
        break;
    case 6:
    case 0xf:
    case 0x11:
        nMission = 0x34ca76bf;
        break;
    case 7:
    case 0x10:
        nMission = 0xb9656f6;
        break;
    default:
        break;
    }

    void* pResult = nullptr;
    if (nMission != 0) {
        void* pMissionKey = pMission->mpMissionKey;
        GetMissionManager((void*)(intptr_t)nMission);
        pResult = CreateWantedMission((void*)(intptr_t)nMission, pMissionKey);
        if (pResult != nullptr)
            ((void* (*)(void*))((void**)*(void**)pResult)[0xa4 >> 2])(pResult);
    }

    void* pLookup = MissionResultLookup(pResult == nullptr ? (void*)0xc8fbf7d7
                                                          : (void*)0xc8fbf7d7,
                                        pResult == nullptr ? (void*)0x8053662e
                                                           : (void*)0x8b756f4b);
    SetMissionResult(pPlanet, pLookup);
    CompleteMissionStep(pPlanet, pLookup, 0xc8fbf7d7,
                        pResult == nullptr ? 0x8053662e : 0x8b756f4b);
}

// ---------------------------------------------------------------------------
// 0x0102cd30  ResumeSpaceGame
// ---------------------------------------------------------------------------
// @ 0x0102cd30
void ResumeSpaceGame()
{
    cSpaceGame* pGame = (cSpaceGame*)SpaceGameGet();
    StopStory(pGame->mpSubObject);
}

// ---------------------------------------------------------------------------
// 0x0102cd40  CloseCommScreenToSpace
// ---------------------------------------------------------------------------
// @ 0x0102cd40
void CloseCommScreenToSpace()
{
    ((cCommScreen*)GetLayout(0x13fa1d4))->SetSpeakerText();
    ((cCommScreen*)GetLayout(0))->SetResponseCount();
    ((cRewardReceiver*)GetRewardReceiver(0x2710))->Apply();

    cSpaceGame* pGame = (cSpaceGame*)SpaceGameGet();
    pGame->mpSubObject->StopStory();
    pGame = (cSpaceGame*)SpaceGameGet();
    pGame->mpSubObject->PauseStory();
}
