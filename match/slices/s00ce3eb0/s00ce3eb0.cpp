// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00ce3eb0.
//
// Tribe planner steps: citizen ordering helpers, the equip-workers planner
// action, and the step-vector copies used by the Gonzago simulator.

typedef unsigned int size_t;
typedef unsigned long long uint64_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned short ushort;
typedef int intptr_t;
#define nullptr 0

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};

class Variant {
public:
    Variant();
    ~Variant();
    uint32_t mFlags;
};

class cTribePlanConfiguration {
public:
    uint32_t mPriority;             // 0x00
    uint32_t mSteps;                // 0x04
    uint32_t mWorkerCount;          // 0x08
    uint32_t mPad0c[0x0c];          // 0x0c
    uint32_t mMaxWorkers;           // 0x3c
    uint32_t mStepLimit;            // 0x40
};

class cSpatialObject : public IRefCounted {
public:
    virtual void v14();
    virtual Vec3* GetPosition();            // 0x14
    uint8_t mPad18[0x0c];                   // 0x18
    Vec3 mPosition;                         // 0x24
};

class cGameData : public cSpatialObject {
public:
    virtual void v2c();
    uint8_t mPad34[0x10];
};

class cSPCreatureBase : public cGameData {
public:
    uint8_t mPad44[0xf4];                   // 0x44
    Vec3 mPosition;                         // 0x138
};

class cSPCreatureCitizen : public cSPCreatureBase {
public:
    bool IsLeader();
    void GiveOrder(int nOrder, int nTool, Variant* pParam);
    void ForceOrdersUpdate();
    Vec3* GetPosition();
    bool IsAvailable();
    uint32_t GetPopulation();
};

class cTribe : public cGameData {
public:
    void* GetToolOfType(int nType);
    cSPCreatureCitizen* GetChieftain();
    uint32_t GetMaxPopulation();
    uint32_t GetAdultPopulation();
    uint32_t GetPopulation();
    void* GetCitizenList();
    void* GetPlanGroups();

    uint8_t mPad34[0x1f0];                  // 0x34
    uint32_t mTribeId;                      // 0x224
};

class cGameNounManager {
public:
    cTribe* GetPlayerTribe();
};

// Planner step group (0x18 bytes): owner id plus a step vector.
struct PlannerStep {
    uint32_t mOwnerId;              // 0x00
    uint32_t mKind;                 // 0x04
    uint8_t mPad08[0x04];           // 0x08
    float    mTimer;                // 0x0c
    uint8_t mPad10[0x08];           // 0x10
    uint32_t mActive;               // 0x18
    uint8_t mPad1c[0x38];           // 0x1c
    cTribePlanConfiguration* mpPlan; // 0x54
};

struct PlannerGroup {
    uint32_t mOwnerId;              // 0x00
    PlannerStep* mpStepsBegin;      // 0x04
    PlannerStep* mpStepsEnd;        // 0x08
    PlannerStep* mpStepsCap;        // 0x0c
    uint32_t mPad10[0x02];          // 0x10
};

struct OrderContext {
    cTribe* mpTribe;                // 0x00
    uint32_t mPad04[0x02];          // 0x04
    uint32_t mnCount;               // 0x0c
};

struct PlannerStepArray {
    int mCounts[9];                 // 0x00
};

class cGonzagoSimulator : public IRefCounted {
public:
    void Update(float fDeltaTime, uint nFlags);

    uint8_t mPad14[0x08];           // 0x14
    cTribe* mpTribe;                // 0x1c
    float mTimer;                   // 0x20
    PlannerGroup* mpGroupBegin;     // 0x24
    PlannerGroup* mpGroupEnd;       // 0x28
};

void* operator_new(size_t nSize, const char* pName, int a, int b, const char* pFile, int nLine);
void operator_delete__(void* pMemory);
void* GetSimulatorContext();
void* GetActiveContext();
cTribePlanConfiguration* GetTribePlanConfiguration(uint32_t tribeId);
void* GetPlanConfiguration(uint32_t tribeId, const void* pKey);
cGameNounManager* NounManager();
void* FindCreatureAt(float fX, float fY, float fZ);
void* FindToolByType(uint32_t nType);
uint32_t GameTimeFlags();
uint64_t GameTimeDelta(uint nFlags);
void GiveCityOrder(int nOrder, float fRadius);
void ClearAllOrders(void* pStimuli, uint32_t a, uint32_t b);
void* CreateOrderVariant(float* pValue, int a);
void ReleaseVariant(Variant* pVariant);
void ReleaseTrace(void* pTrace);
float GetSimulationStep(int nIndex);
float GetTribeRadius(cTribe* pTribe);
void ResetPlannerSteps(int nCount, void* pSteps);
int GetStepCount(void* pVector);
void UpdatePlannerSteps(int nCount, int* pSteps);
bool ReadPlannerCounts(void* pObject, uint32_t key, int* pCount, void** ppArray);
void AllocatePlannerEntry(int* pEntries, int a, int b);
void CopyPlannerStepRange(PlannerStep* pFirst, PlannerStep* pLast, PlannerStep* pDest);
void DestroyStepVector(PlannerGroup* pGroup);
bool CopyPlannerGroupsInternal(PlannerGroup* pFirst, PlannerGroup* pLast,
                               PlannerGroup* pDest, PlannerGroup* pOwner);
void GiveToolOrder(cSPCreatureCitizen* pCitizen, int nOrder, void* pTool, int a);
int GetToolOrderSlot(void* pTool);

// ---------------------------------------------------------------------------
// 0x00ce3eb0  OrderNearbyCitizensToAttack
// ---------------------------------------------------------------------------
// @ 0x00ce3eb0
bool OrderNearbyCitizensToAttack(OrderContext* pContext, float fRange, float fStep)
{
    cTribe* pTribe = pContext->mpTribe;
    void* pWorld = GetSimulatorContext();
    if (pWorld == nullptr || pContext->mnCount == 0)
        return false;

    cTribePlanConfiguration* pPlan = GetTribePlanConfiguration(pTribe->mTribeId);
    if (pPlan == nullptr)
        return false;

    fRange -= fStep;
    if (fRange < 0.0f) {
        fRange = 2.0f;
        uint32_t nCount = pContext->mnCount;
        if (nCount > pPlan->mMaxWorkers)
            nCount = pPlan->mMaxWorkers;

        void* pTool = pTribe->GetToolOfType(10);
        Vec3* pCenter = pTribe->GetPosition();
        float fRadius = GetTribeRadius(pTribe);
        float fLimit = fRadius * fRadius;
        float fSetting = fRadius * 0.75f;

        void* pCitizens = pTribe->GetCitizenList();
        for (int pass = 0; pass < 2 && nCount != 0; ++pass) {
            cSPCreatureCitizen** pBegin = (cSPCreatureCitizen**)*(void**)pCitizens;
            cSPCreatureCitizen** pEnd = (cSPCreatureCitizen**)*((void**)pCitizens + 1);
            for (cSPCreatureCitizen** ppCitizen = pBegin; ppCitizen != pEnd; ++ppCitizen) {
                if (nCount == 0)
                    break;
                cSPCreatureCitizen* pCitizen = *ppCitizen;
                if (!pCitizen->IsAvailable())
                    continue;
                if (!pCitizen->IsLeader() && pPlan->mMaxWorkers == 0)
                    continue;
                Vec3* pPosition = pCitizen->GetPosition();
                float fDx = pPosition->mX - pCenter->mX;
                float fDy = pPosition->mY - pCenter->mY;
                float fDz = pPosition->mZ - pCenter->mZ;
                float fDistance = fDx * fDx + fDy * fDy + fDz * fDz;
                if (pass == 0 ? fDistance < fLimit : fDistance > fLimit) {
                    if (GetSimulatorContext() != nullptr) {
                        --nCount;
                        Variant param;
                        GiveCityOrder(4, fSetting);
                        pCitizen->GiveOrder(4, 10, &param);
                        ReleaseVariant(&param);
                    }
                }
            }
        }

        if (nCount != 0 && pPlan->mMaxWorkers != 0) {
            cSPCreatureCitizen* pChieftain = pTribe->GetChieftain();
            if (pChieftain != nullptr && pChieftain->IsAvailable()) {
                Vec3* pPosition = pChieftain->GetPosition();
                float fDx = pPosition->mX - pCenter->mX;
                float fDy = pPosition->mY - pCenter->mY;
                float fDz = pPosition->mZ - pCenter->mZ;
                if (fDx * fDx + fDy * fDy + fDz * fDz > fLimit) {
                    Variant param;
                    GiveCityOrder(4, fSetting);
                    pChieftain->GiveOrder(4, 10, &param);
                    ReleaseVariant(&param);
                } else {
                    return false;
                }
            }
        }
        (void)pTool;
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00ce4380  SP::PLANNER_EQUIP_WORKERS_Activate
// ---------------------------------------------------------------------------
// @ 0x00ce4380
bool PlannerEquipWorkersActivate(OrderContext* pStep, cSPCreatureCitizen* pCitizen)
{
    cTribe* pTribe = pStep->mpTribe;
    void* pWorld = GetSimulatorContext();
    if (pWorld == nullptr)
        return false;

    cTribePlanConfiguration* pPlan = GetTribePlanConfiguration(pTribe->mTribeId);
    if (pPlan == nullptr)
        return false;

    void* pGroups = pTribe->GetPlanGroups();
    DestroyStepVector((PlannerGroup*)pGroups);

    pCitizen->v10();

    uint32_t nWorkers = pStep->mnCount;
    if (pPlan->mMaxWorkers < nWorkers)
        nWorkers = pPlan->mMaxWorkers;
    int nAvailable = (int)nWorkers;
    UpdatePlannerSteps(nAvailable, nullptr);

    PlannerStepArray counts;
    int nCount = 0;
    void* pArray = nullptr;
    if (ReadPlannerCounts(pPlan, 0x602f317, &nCount, &pArray) && nCount > 0) {
        for (int i = 0; i < nCount; ++i) {
            int nKind = ((int*)pArray)[i * 2];
            if ((uint)(nKind - 1) < 9) {
                float fValue = (float)nAvailable * ((float*)pArray)[i * 2];
                int nSteps = (int)(fValue + 0.5f);
                if ((float)nSteps < fValue)
                    ++nSteps;
                counts.mCounts[nKind] = nSteps;
            }
        }
    }

    Vec3* pCenter = pTribe->GetPosition();
    float fRadius = GetTribeRadius(pTribe);
    float fLimit = fRadius * fRadius;

    void* pCitizens = pTribe->GetCitizenList();
    cSPCreatureCitizen** pBegin = (cSPCreatureCitizen**)*(void**)pCitizens;
    cSPCreatureCitizen** pEnd = (cSPCreatureCitizen**)*((void**)pCitizens + 1);
    for (cSPCreatureCitizen** ppCitizen = pBegin; ppCitizen != pEnd; ++ppCitizen) {
        if (nAvailable == 0)
            break;
        cSPCreatureCitizen* pCreature = *ppCitizen;
        if (!pCreature->IsAvailable())
            continue;
        Vec3* pPosition = pCreature->GetPosition();
        float fDx = pPosition->mX - pCenter->mX;
        float fDy = pPosition->mY - pCenter->mY;
        float fDz = pPosition->mZ - pCenter->mZ;
        if (fDx * fDx + fDy * fDy + fDz * fDz >= fLimit)
            continue;
        if (pCreature->IsLeader() && pPlan->mMaxWorkers != 0)
            continue;

        --nAvailable;
        pCreature->v10();
        ClearAllOrders(pCreature, 0x1d3fbffa, 0x8124080);
        pCreature->ForceOrdersUpdate();

        if (!pCreature->IsLeader()) {
            for (uint32_t nKind = 1; nKind < 9; ++nKind) {
                if (counts.mCounts[nKind] == 0)
                    continue;
                void* pTool = pTribe->GetToolOfType((int)nKind);
                if (pTool == nullptr)
                    pTool = FindToolByType(nKind);
                if (pTool == nullptr)
                    continue;
                GiveToolOrder(pCreature, 3, pTool, 0);
                int nSlot = GetToolOrderSlot(pTool);
                counts.mCounts[nSlot] = counts.mCounts[nSlot] - 1;
                break;
            }
        }
    }

    if (pPlan->mMaxWorkers != 0 && pTribe->GetPopulation() < pPlan->mStepLimit) {
        cSPCreatureCitizen* pChieftain = pTribe->GetChieftain();
        if (pChieftain != nullptr && pChieftain->IsAvailable()) {
            Vec3* pPosition = pChieftain->GetPosition();
            float fDx = pPosition->mX - pCenter->mX;
            float fDy = pPosition->mY - pCenter->mY;
            float fDz = pPosition->mZ - pCenter->mZ;
            if (fDx * fDx + fDy * fDy + fDz * fDz < fLimit) {
                pChieftain->v10();
                ReleaseTrace(nullptr);
                if (pChieftain != nullptr)
                    pChieftain->Release();
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00ce4810  PlannerCheckWorkers
// ---------------------------------------------------------------------------
// @ 0x00ce4810
bool PlannerCheckWorkers(OrderContext* pContext, float fRange, float fStep)
{
    void* pWorld = GetSimulatorContext();
    if (pWorld == nullptr || pContext->mnCount == 0)
        return false;

    cTribe* pTribe = pContext->mpTribe;
    cTribePlanConfiguration* pPlan = GetTribePlanConfiguration(pTribe->mTribeId);
    if (pPlan == nullptr)
        return false;

    fRange -= fStep;
    if (fRange < 0.0f) {
        void* pGroups = pTribe->GetPlanGroups();
        PlannerGroup* pGroup = (PlannerGroup*)*(void**)pGroups;
        PlannerGroup* pGroupEnd = (PlannerGroup*)*((void**)pGroups + 1);
        while (pGroup != pGroupEnd) {
            if (GetSimulatorContext() != nullptr)
                return true;
            ++pGroup;
        }
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00ce48f0  Simulator::cGonzagoSimulator::Update
// ---------------------------------------------------------------------------
// @ 0x00ce48f0
void cGonzagoSimulator::Update(float fDeltaTime, uint nFlags)
{
    if (mpTribe == nullptr || *(uint8_t*)((uint8_t*)mpTribe + 0x556) != 0)
        return;

    int* pContext = (int*)GetSimulatorContext();
    if (pContext != nullptr) {
        if (pContext[0xb] == 1 || pContext[0xb] == 2)
            return;
    }
    if ((GameTimeFlags() & 1) != 0)
        return;

    float fDelta = (float)GameTimeDelta(nFlags) * 0.001f;
    mTimer += fDelta;
    if (mTimer < 1.0f)
        return;

    mTimer -= 1.0f;
    uint32_t nDirty = 0;
    if (GetActiveContext() != nullptr)
        nDirty |= 2;

    PlannerGroup* pGroup = mpGroupBegin;
    for (; pGroup != mpGroupEnd; pGroup = (PlannerGroup*)((uint8_t*)pGroup + 0x18)) {
        float fRemaining = pGroup->mOwnerId - 1.0f;
        pGroup->mOwnerId = (uint32_t)fRemaining;
        if (fRemaining < 0.0f) {
            PlannerStep* pStep = pGroup->mpStepsBegin;
            int nSteps = (int)(pGroup->mpStepsEnd - pStep);
            for (int i = 0; i < nSteps; ++i, ++pStep) {
                if (pStep->mKind == 4)
                    continue;
                pStep->mTimer -= 1.0f;
                pStep->mActive = (pStep->mTimer < 0.0f);
                if (pStep->mTimer < 0.0f) {
                    nDirty |= 1;
                    if (pStep->mpPlan == nullptr)
                        pStep->mpPlan = GetTribePlanConfiguration(pStep->mOwnerId);
                    pStep->mTimer = (float)pStep->mpPlan->mSteps;
                }
            }
        }
    }

    void* pCitizens = mpTribe->GetCitizenList();
    cSPCreatureCitizen** pBegin = (cSPCreatureCitizen**)*(void**)pCitizens;
    cSPCreatureCitizen** pEnd = (cSPCreatureCitizen**)*((void**)pCitizens + 1);
    for (cSPCreatureCitizen** ppCitizen = pBegin; ppCitizen != pEnd; ++ppCitizen) {
        cSPCreatureCitizen* pCitizen = *ppCitizen;
        int nDamageState = pCitizen->GetPopulation();
        if (nDamageState != 2)
            nDirty |= 1u << (nDamageState & 0x1f);
    }

    cGameNounManager* pNouns = NounManager();
    cTribe* pPlayerTribe = pNouns->GetPlayerTribe();
    if (pPlayerTribe != nullptr) {
        uint32_t nPlayer = pPlayerTribe->GetAdultPopulation();
        uint32_t nLocal = mpTribe->GetAdultPopulation();
        pPlayerTribe->v10();
        (void)nPlayer;
        (void)nLocal;
    }
}

// ---------------------------------------------------------------------------
// 0x00ce4c40  CopyPlannerVector
// ---------------------------------------------------------------------------
// @ 0x00ce4c40
int* CopyPlannerVector(int* pOut, int* pSrc)
{
    CopyPlannerStepRange((PlannerStep*)pSrc[0], (PlannerStep*)pSrc[1], (PlannerStep*)pOut[0]);
    CopyPlannerGroupsInternal((PlannerGroup*)pSrc, (PlannerGroup*)pSrc[0],
                              (PlannerGroup*)pSrc[1], (PlannerGroup*)pOut[0]);
    pOut[1] = pSrc[1];
    return pOut;
}

// ---------------------------------------------------------------------------
// 0x00ce4ca0  CopyPlannerGroups
// ---------------------------------------------------------------------------
// @ 0x00ce4ca0
PlannerGroup* CopyPlannerGroups(PlannerGroup* pOut, PlannerGroup* pFirst,
                                PlannerGroup* pLast, PlannerGroup* pOwner)
{
    pOut->mOwnerId = (uint32_t)(intptr_t)pOwner;
    while (pFirst != pLast) {
        PlannerGroup* pCurrent = pOut;
        if (pCurrent->mpStepsBegin != nullptr) {
            pCurrent->mOwnerId = pFirst->mOwnerId;
            int nSteps = (int)(pFirst->mpStepsEnd - pFirst->mpStepsBegin);
            PlannerStep* pCopy = nullptr;
            if (nSteps != 0)
                pCopy = (PlannerStep*)operator_new(nSteps * 0x58, "Simulator", 0, 0,
                                                   "EASTL/allocator.h", 0xd1);
            pCurrent->mpStepsBegin = pCopy;
            pCurrent->mpStepsEnd = pCopy;
            pCurrent->mpStepsCap = pCopy + nSteps;
            CopyPlannerStepRange(pFirst->mpStepsBegin, pFirst->mpStepsEnd, pCopy);
            pCurrent->mpStepsEnd = pCopy + nSteps;
        }
        ++pOut;
        ++pFirst;
    }
    return pOut;
}

// ---------------------------------------------------------------------------
// 0x00ce4d60  FillPlannerGroups
// ---------------------------------------------------------------------------
// @ 0x00ce4d60
void FillPlannerGroups(PlannerGroup* pDest, int nCount, PlannerGroup* pSrc)
{
    for (int i = 0; i < nCount; ++i) {
        pDest->mOwnerId = pSrc->mOwnerId;
        int nSteps = (int)(pSrc->mpStepsEnd - pSrc->mpStepsBegin);
        PlannerStep* pCopy = nullptr;
        if (nSteps != 0)
            pCopy = (PlannerStep*)operator_new(nSteps * 0x58, "Simulator", 0, 0,
                                               "EASTL/allocator.h", 0xd1);
        pDest->mpStepsCap = pCopy + nSteps;
        pDest->mpStepsBegin = pCopy;
        pDest->mpStepsEnd = pCopy;
        CopyPlannerStepRange(pSrc->mpStepsBegin, pSrc->mpStepsEnd, pCopy);
        pDest->mpStepsEnd = pCopy + nSteps;
        ++pDest;
        ++pSrc;
    }
}
