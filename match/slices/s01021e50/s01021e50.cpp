// Background simulation manager, the planet list sort helpers it uses and the
// small value helpers living next to them.

typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define nullptr 0

// ---------------------------------------------------------------------------
// Raw dispatch helper: the shipped code reaches a few interface slots that are
// far too high to spell out as virtual members, so they are called through the
// method table of the object.
// ---------------------------------------------------------------------------
struct cVTable {
    void* mpSlots[0x100];                       // 0x000
};

class cDispatchObject {
public:
    void* Call(int nSlot) {
        return ((void* (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    int32_t CallInt(int nSlot) {
        return ((int32_t (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    void CallVoid(int nSlot) {
        ((void (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    cVTable* mpTable;                           // 0x000
};

// ---------------------------------------------------------------------------
// Reference counted objects: the low two interface slots are add and release.
// ---------------------------------------------------------------------------
class cRefCounted {
public:
    virtual void AddRef();                      // slot 0x00
    virtual void Release();                     // slot 0x04
};

// EA::AutoRefCount<T>: a single pointer that keeps the object alive.
class cAutoRef {
public:
    void Assign(cRefCounted* pObject);
    cRefCounted* mpObject;                      // 0x000
};

void cAutoRef::Assign(cRefCounted* pObject)
{
    cRefCounted* pOld = mpObject;
    if (pObject == pOld)
        return;
    if (pObject != nullptr)
        pObject->AddRef();
    mpObject = pObject;
    if (pOld != nullptr)
        pOld->Release();
}

typedef int (__cdecl *cPointerCompare)(void*, void*);

// ---------------------------------------------------------------------------
// Planet list, the sorted range wrappers and the sort helpers they share.
// ---------------------------------------------------------------------------
class cPlanetList {
public:
    void Erase(void** ppFirst, void** ppLast);

    void** mpBegin;                             // 0x000
    void** mpEnd;                               // 0x004
    void** mpCapacity;                          // 0x008
};

struct cPlanetRange {
    void** mpBegin;                             // 0x000
    void** mpEnd;                               // 0x004
};

void FUN_00bab900(cPlanetList* pList, cDispatchObject** ppPlanet);

int ComparePlanetsByDistance(void* pLhs, void* pRhs);       // 0x1021110
int ComparePlanetsByRadius(void* pLhs, void* pRhs);         // 0x1021140

void SwapPlanetsByDistance(void** ppBegin, void** ppEnd, cPointerCompare pCompare);
void SwapPlanetsByRadius(void** ppBegin, void** ppEnd, cPointerCompare pCompare);

void SwapPlanetSlots(void** ppLhs, void** ppRhs);           // 0x10216a0
void** SelectMedianPlanet(void** ppFirst, void** ppMiddle, void** ppLast,
                          cPointerCompare pCompare);        // 0x1021180
void BuildPlanetHeap(int32_t nFirst, int32_t nLast, cPointerCompare pCompare);
int32_t TakePlanetSlot(int32_t nFirst, int32_t nLast, int32_t nCount,
                       int32_t nIndex, cPointerCompare pCompare);

// ---------------------------------------------------------------------------
// Small value types shared by this module.
// ---------------------------------------------------------------------------
class cObjectKey {
public:
    cObjectKey& Init(void* pFirst, void* pSecond);
    int32_t Matches(cObjectKey* pOther);

    void* mnType;                               // 0x000
    void* mpFirst;                              // 0x004
    void* mpSecond;                             // 0x008
};

class cStarVisualParams {
public:
    cStarVisualParams& CopyFrom(const cStarVisualParams& rOther);

    uint8_t mbFlag;                             // 0x000
    uint8_t mPad001[0x03];                      // 0x001
    float mafValues[25];                        // 0x004
};

struct cVector3 {
    float mfX;                                  // 0x000
    float mfY;                                  // 0x004
    float mfZ;                                  // 0x008
};

class cCivData {
public:
    cVector3* GetCities();
};

cVector3* g_pCityReferencePoint = nullptr;                  // 0x16ddb34

class cGameStateFlags {
public:
    uint8_t mPad000[0x48];                      // 0x000
    uint8_t mbFlag;                             // 0x048
};

class cGameState {
public:
    uint8_t mPad000[0x188];                     // 0x000
    cGameStateFlags* mpFlags;                   // 0x188
};

// ---------------------------------------------------------------------------
// The background simulator manager, reachable through g_pBackgroundSim.
// ---------------------------------------------------------------------------
class cVarListSerializer {
public:
    cVarListSerializer(void* pOwner, const char* pName, int32_t nFlags);
    void Serialize(void* pData);

    uint8_t mPad000[0xa14];                     // 0x000
};

class cSPBackgroundSimManager {
public:
    void Read(cVarListSerializer* pSerializer);
    void ActivatePlanet(void* pPlanetKey);
    void Destroy(int32_t nFlags);
    void UpdatePlanetTerraforming(void* pPlanet, int32_t nDelta);

    int32_t mnElapsedTime;                      // 0x000
    cDispatchObject* mpSimulator;               // 0x004
    cDispatchObject* mpStar;                    // 0x008
    cDispatchObject* mpCommObject;              // 0x00c
    int32_t mnState;                            // 0x010
    int32_t mnUnused14;                         // 0x014
    int32_t mnTimeRemaining;                    // 0x018
    cRefCounted* mpRequest;                     // 0x01c
    cPlanetList mPlanets;                       // 0x020
    uint8_t mPad02c[0x1c];                      // 0x02c
};

cSPBackgroundSimManager* g_pBackgroundSim = nullptr;        // 0x16dda8c
uint8_t g_bBackgroundSimActive = 0;                         // 0x16dda88
uint8_t g_bBackgroundSimStarted = 0;                        // 0x16dda89

class cStarManager {
public:
    void GetOrActivatePlanet(void* pPlanetKey, cDispatchObject** ppPlanet);
    cDispatchObject* GetActiveStar();
    void Tick(int32_t nDelta);
};

class cStar {
public:
    cDispatchObject* GetSolarSystem();
};

class cSolarSystem {
public:
    void Tick(int32_t nDelta);
    void SetStarCharge(float fCharge);
    cDispatchObject* GetPlanet(int32_t nIndex);
};

class cSimPlanetLowLOD {
public:
    void UpdateTerraforming(int32_t nDelta);
    void Tick(int32_t nDelta);
};

class cSPSimulatorUFO {
public:
    int32_t GetTravelCharge();
    void TravelToStarCharge(int32_t nStarIndex);
    cDispatchObject* GetPlayerInventory();
};

class cSPGameDataUFO {
public:
    void PopToDestination();
};

class cPlayerInventory {
public:
    int32_t GetStarCount();
    void SetStarCount(int32_t nStars);
};

void* StarManager();
void* GetObjectManager();
void* GetStateManager();
void* __cdecl operator_new(uint32_t nSize, const char* pName);
void FUN_00d05010(void* pObject);
void InitBackgroundSimulator(void* pStar);
void SimulateBackgroundTick(void* pStar, int32_t nDelta);
void ReleaseBackgroundSimulator(cSPBackgroundSimManager* pManager);
int32_t GetCurrentGameMode();
int32_t GetUFOContextId();
int32_t GetUniverseContextId();
void* GetUFOSimulator(int32_t nContext);
void* GetUFOSimulator();
void* GetPlayerUniverse();
int32_t GetPlayerStarCount();
void AddPlayerStars(int32_t nStars);
float g_fBackgroundTickScale = 0.001f;                      // 0x13f9428

// ---------------------------------------------------------------------------
// 0x01021e50  PartitionPlanets
// ---------------------------------------------------------------------------
// @ 0x01021e50
void** PartitionPlanets(void** ppFirst, void** ppUnused, void** ppLast,
                        cDispatchObject* pPivot, cPointerCompare pCompare)
{
    void** ppLow = ppFirst;
    for (;;) {
        while (pCompare(pPivot, *ppLow) != 0)
            ++ppLow;
        while (pCompare(pPivot, *--ppLast) != 0)
            ;
        if (ppLow >= ppLast)
            break;
        SwapPlanetSlots(ppLow, ppLast);
        ++ppLow;
    }
    if (pPivot != nullptr)
        pPivot->CallVoid(0xc0);
    return ppLow;
}

// ---------------------------------------------------------------------------
// 0x01021ed0  SortPlanetPartition
// ---------------------------------------------------------------------------
// @ 0x01021ed0
void SortPlanetPartition(void** ppFirst, void** ppLast, void** ppUnused,
                         cPointerCompare pCompare)
{
    void** ppLow = ppFirst;
    BuildPlanetHeap(0, (int32_t)(ppLast - ppFirst), pCompare);
    for (; ppLow < ppLast; ++ppLow) {
        if (pCompare(*ppFirst, *ppLow) == 0)
            continue;
        void* pValue = *ppLow;
        if (pValue != nullptr)
            ((cDispatchObject*)pValue)->CallVoid(0xbc);
        void* pOld = *ppFirst;
        if (pOld != pValue) {
            if (pOld != nullptr)
                ((cDispatchObject*)pOld)->CallVoid(0xbc);
            *ppFirst = pOld;
            if (pValue != nullptr)
                ((cDispatchObject*)pValue)->CallVoid(0xc0);
        }
        int32_t nCount = (int32_t)(ppLast - ppFirst);
        TakePlanetSlot(0, 0, nCount - 1, 0, pCompare);
        if (pValue != nullptr)
            ((cDispatchObject*)pValue)->CallVoid(0xc0);
    }
}

// ---------------------------------------------------------------------------
// 0x01021fd0  QuickSortPlanets
// ---------------------------------------------------------------------------
// @ 0x01021fd0
void QuickSortPlanets(void** ppFirst, void** ppLast, void** ppUnused,
                      int32_t nDepth, cPointerCompare pCompare)
{
    for (;;) {
        if (((uint32_t)((uint8_t*)ppLast - (uint8_t*)ppFirst) & 0xfffffffc) <= 0x70)
            break;
        if (nDepth <= 0)
            break;
        void** ppMiddle = SelectMedianPlanet(ppFirst, ppFirst + ((ppLast - ppFirst) >> 1),
                                             ppLast - 1, pCompare);
        void* pPivot = *ppMiddle;
        if (pPivot != nullptr)
            ((cDispatchObject*)pPivot)->CallVoid(0xbc);
        void** ppSplit = PartitionPlanets(ppFirst, ppLast, ppLast,
                                          (cDispatchObject*)pPivot, pCompare);
        QuickSortPlanets(ppSplit, ppLast, ppLast, nDepth - 1, pCompare);
        ppLast = ppSplit;
    }
    if (nDepth == 0)
        SortPlanetPartition(ppFirst, ppLast, ppLast, pCompare);
}

// ---------------------------------------------------------------------------
// 0x010220e0  cSPBackgroundSimManager::Read
// ---------------------------------------------------------------------------
// @ 0x010220e0
void cSPBackgroundSimManager::Read(cVarListSerializer* pSerializer)
{
    mPlanets.Erase(mPlanets.mpBegin, mPlanets.mpEnd);
    if (mpRequest != nullptr) {
        cRefCounted* pRequest = mpRequest;
        mpRequest = nullptr;
        pRequest->Release();
    }
    cVarListSerializer serializer(this, "StarManager", 0x1a80d26);
    serializer.Serialize(pSerializer);
}

// ---------------------------------------------------------------------------
// 0x01022150  cSPBackgroundSimManager::ActivatePlanet
// ---------------------------------------------------------------------------
// @ 0x01022150
void cSPBackgroundSimManager::ActivatePlanet(void* pPlanetKey)
{
    cDispatchObject* pPlanet = nullptr;
    ((cStarManager*)StarManager())->GetOrActivatePlanet(pPlanetKey, &pPlanet);

    void** ppSlot = mPlanets.mpBegin;
    while (ppSlot != mPlanets.mpEnd && *ppSlot != pPlanet)
        ++ppSlot;
    if (ppSlot == mPlanets.mpEnd) {
        if (mPlanets.mpEnd < mPlanets.mpCapacity) {
            void** ppNew = mPlanets.mpEnd;
            mPlanets.mpEnd = ppNew + 1;
            if (ppNew != nullptr)
                *ppNew = (void*)pPlanet;
        }
        else {
            FUN_00bab900(&mPlanets, &pPlanet);
        }
    }
    if (pPlanet != nullptr)
        pPlanet->CallVoid(0xbc);

    cGameState* pGame = (cGameState*)GetStateManager();
    pGame->mpFlags->mbFlag = 0;
    if (pPlanet != nullptr)
        pPlanet->CallVoid(0xc0);
}

// ---------------------------------------------------------------------------
// 0x010221f0  InitBackgroundSimulator
// ---------------------------------------------------------------------------
// @ 0x010221f0
void InitBackgroundSimulator(void* pStar)
{
    cDispatchObject* pSimulator = nullptr;
    void* pMemory = operator_new(0x100, "Simulator");
    if (pMemory != nullptr)
        pSimulator = (cDispatchObject*)pMemory;
    if (pMemory != nullptr)
        FUN_00d05010(pMemory);

    cSPBackgroundSimManager* pManager = g_pBackgroundSim;
    cDispatchObject* pOld = pManager->mpCommObject;
    if (pSimulator != pOld) {
        if (pSimulator != nullptr)
            ((cDispatchObject*)((uint8_t*)pSimulator + 8))->CallVoid(0x08);
        pManager->mpCommObject = pSimulator;
        if (pOld != nullptr)
            ((cDispatchObject*)((uint8_t*)pOld + 8))->CallVoid(0x0c);
    }
    pManager->mpCommObject->CallVoid(0x04);

    if (!g_bBackgroundSimActive) {
        if (pManager->mpStar != nullptr) {
            cDispatchObject* pOldStar = pManager->mpStar;
            pManager->mpStar = nullptr;
            pOldStar->CallVoid(0x04);
        }
        pManager->mnElapsedTime = 0x3e8;
    }

    void* pWorld = ((cStarManager*)StarManager())->GetActiveStar();
    ((cDispatchObject*)pStar)->CallVoid(0x00);
    if (pManager->mpSimulator != nullptr) {
        cDispatchObject* pOldSim = pManager->mpSimulator;
        pManager->mpSimulator = nullptr;
        pOldSim->CallVoid(0x04);
    }
    pManager->mpStar = (cDispatchObject*)pStar;
    pManager->mnState = 1;
    pManager->mPlanets.Erase(pManager->mPlanets.mpBegin, pManager->mPlanets.mpEnd);
    pManager->mnTimeRemaining = -1;
    pManager->mnUnused14 = 0;
}

// ---------------------------------------------------------------------------
// 0x01022460  ShutdownBackgroundSimulator
// ---------------------------------------------------------------------------
// @ 0x01022460
void ShutdownBackgroundSimulator()
{
    cSPBackgroundSimManager* pManager = g_pBackgroundSim;
    g_bBackgroundSimActive = 0;
    g_bBackgroundSimStarted = 0;

    if (pManager->mpSimulator != nullptr) {
        cDispatchObject* pSimulator = pManager->mpSimulator;
        pManager->mpSimulator = nullptr;
        pSimulator->CallVoid(0xc0);
    }
    if (pManager->mpStar != nullptr) {
        cDispatchObject* pStar = pManager->mpStar;
        pManager->mpStar = nullptr;
        pStar->CallVoid(0x04);
    }
    if (pManager->mpRequest != nullptr) {
        cRefCounted* pRequest = pManager->mpRequest;
        pManager->mpRequest = nullptr;
        pRequest->Release();
    }
    pManager->mPlanets.Erase(pManager->mPlanets.mpBegin, pManager->mPlanets.mpEnd);
    pManager->mnTimeRemaining = -1;

    cDispatchObject* pComm = pManager->mpCommObject;
    if (pComm != nullptr) {
        pComm->CallVoid(0x08);
        cDispatchObject* pNew = pManager->mpCommObject;
        if (pNew != nullptr) {
            pManager->mpCommObject = nullptr;
            ((cDispatchObject*)((uint8_t*)pNew + 8))->CallVoid(0x0c);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x01022510  SortPlanetsByDistance
// ---------------------------------------------------------------------------
// @ 0x01022510
void SortPlanetsByDistance(cPlanetRange* pRange)
{
    SwapPlanetsByDistance(pRange->mpBegin, pRange->mpEnd, ComparePlanetsByDistance);
}

// ---------------------------------------------------------------------------
// 0x01022530  SortPlanetsByRadius
// ---------------------------------------------------------------------------
// @ 0x01022530
void SortPlanetsByRadius(cPlanetRange* pRange)
{
    SwapPlanetsByRadius(pRange->mpBegin, pRange->mpEnd, ComparePlanetsByRadius);
}

// ---------------------------------------------------------------------------
// 0x01022550  StopBackgroundSim
// ---------------------------------------------------------------------------
// @ 0x01022550
void StopBackgroundSim()
{
    cSPBackgroundSimManager* pManager = g_pBackgroundSim;
    if (pManager->mnTimeRemaining != -1) {
        ShutdownBackgroundSimulator();
        pManager = g_pBackgroundSim;
    }
    if (pManager != nullptr) {
        pManager->Destroy(1);
        g_pBackgroundSim = nullptr;
    }
}

// ---------------------------------------------------------------------------
// 0x01022580  StartBackgroundSim
// ---------------------------------------------------------------------------
// @ 0x01022580
void StartBackgroundSim()
{
    if (g_bBackgroundSimStarted)
        return;

    cSPBackgroundSimManager* pManager = g_pBackgroundSim;
    g_bBackgroundSimStarted = 1;
    if (pManager->mpStar == nullptr)
        InitBackgroundSimulator(((cStarManager*)StarManager())->GetActiveStar());
    if (g_pBackgroundSim->mnState != 0)
        g_pBackgroundSim->mnState = 0;
}

// ---------------------------------------------------------------------------
// 0x010225d0  SimulateBackground
// ---------------------------------------------------------------------------
// @ 0x010225d0
void SimulateBackground(void* pStar, int32_t nDelta)
{
    if (pStar != nullptr && ((cDispatchObject*)pStar)->CallInt(0x00) != 0) {
        void* pPlanet = ((cDispatchObject*)pStar)->Call(0x00);
        ((cSimPlanetLowLOD*)pPlanet)->UpdateTerraforming(nDelta);
    }

    cSPBackgroundSimManager* pManager = g_pBackgroundSim;
    pManager->mnElapsedTime += nDelta;
    if (pManager->mnElapsedTime < 0x3e8)
        return;

    while (pManager->mnElapsedTime >= 0x3e8) {
        pManager->mnElapsedTime -= 0x3e8;
        cSolarSystem* pSystem = (cSolarSystem*)pManager->mpStar->Call(0x00);
        if (pSystem == nullptr)
            continue;
        int32_t nPlanets = (int32_t)(pSystem->GetPlanet(0) != nullptr);
        for (int32_t i = 0; i < nPlanets; ++i) {
            void* pPlanet = pSystem->GetPlanet(i);
            if (((cDispatchObject*)pPlanet)->CallInt(0x00) == 0)
                continue;
            void* pLowLOD = ((cDispatchObject*)pPlanet)->Call(0x00);
            ((cSimPlanetLowLOD*)pLowLOD)->Tick(0x3e8);
        }
    }

    if (pStar != nullptr)
        SimulateBackgroundTick(pStar, nDelta);
}

// ---------------------------------------------------------------------------
// 0x01022920  AdvanceBackgroundSim
// ---------------------------------------------------------------------------
// @ 0x01022920
void AdvanceBackgroundSim(int32_t nDelta)
{
    if (GetCurrentGameMode() == 0x1654c05) {
        cSPBackgroundSimManager* pManager = g_pBackgroundSim;
        SimulateBackground(pManager->mpSimulator, nDelta);
    }

    cSPBackgroundSimManager* pManager = g_pBackgroundSim;
    int32_t nState = pManager->mnState;
    if (nState != 0) {
        if (nState != 1)
            return;
    }

    cStar* pStar = (cStar*)pManager->mpStar;
    if (pStar == nullptr)
        return;
    cSolarSystem* pSystem = (cSolarSystem*)pStar->GetSolarSystem();
    if (pSystem == nullptr)
        return;

    float fCharge = (float)(uint32_t)nDelta * g_fBackgroundTickScale;
    pSystem->SetStarCharge(fCharge);
}

// ---------------------------------------------------------------------------
// 0x01022990  cObjectKey::Init
// ---------------------------------------------------------------------------
// @ 0x01022990
cObjectKey& cObjectKey::Init(void* pFirst, void* pSecond)
{
    mnType = (void*)0x1495c98;
    mpFirst = pFirst;
    mpSecond = pSecond;
    return *this;
}

// ---------------------------------------------------------------------------
// 0x010229b0  cObjectKey::Matches
// ---------------------------------------------------------------------------
// @ 0x010229b0
int32_t cObjectKey::Matches(cObjectKey* pOther)
{
    if (pOther->mnType != mpSecond)
        return 0;
    if (pOther->mpFirst != mpFirst)
        return 0;
    return 1;
}

// ---------------------------------------------------------------------------
// 0x010229d0  TravelToStar
// ---------------------------------------------------------------------------
// @ 0x010229d0
void TravelToStar(int32_t nStarIndex)
{
    if (nStarIndex == 0)
        return;
    if (GetUniverseContextId() != 2)
        return;

    cSPSimulatorUFO* pSimulator = (cSPSimulatorUFO*)GetUFOSimulator(GetUFOContextId());
    int32_t nCharge = pSimulator->GetTravelCharge();
    int32_t nStars = ((cPlayerInventory*)GetPlayerUniverse())->GetStarCount();

    ((cPlayerInventory*)GetPlayerUniverse())->SetStarCount(nCharge + nStars);
    ((cSPSimulatorUFO*)GetUFOSimulator(nStarIndex))->TravelToStarCharge(0);

    cSPGameDataUFO* pGameData = (cSPGameDataUFO*)((cSPSimulatorUFO*)GetUFOSimulator())
                                    ->GetPlayerInventory();
    pGameData->PopToDestination();
}

// ---------------------------------------------------------------------------
// 0x01022bb0  cStarVisualParams::CopyFrom
// ---------------------------------------------------------------------------
// @ 0x01022bb0
cStarVisualParams& cStarVisualParams::CopyFrom(const cStarVisualParams& rOther)
{
    mbFlag = rOther.mbFlag;
    mafValues[0] = rOther.mafValues[0];
    mafValues[1] = rOther.mafValues[1];
    mafValues[2] = rOther.mafValues[2];
    mafValues[3] = rOther.mafValues[3];
    mafValues[4] = rOther.mafValues[4];
    mafValues[5] = rOther.mafValues[5];
    mafValues[6] = rOther.mafValues[6];
    mafValues[7] = rOther.mafValues[7];
    mafValues[8] = rOther.mafValues[8];
    mafValues[9] = rOther.mafValues[9];
    mafValues[10] = rOther.mafValues[10];
    mafValues[11] = rOther.mafValues[11];
    mafValues[12] = rOther.mafValues[12];
    mafValues[13] = rOther.mafValues[13];
    mafValues[14] = rOther.mafValues[14];
    mafValues[15] = rOther.mafValues[15];
    mafValues[16] = rOther.mafValues[16];
    mafValues[17] = rOther.mafValues[17];
    mafValues[18] = rOther.mafValues[18];
    mafValues[19] = rOther.mafValues[19];
    mafValues[20] = rOther.mafValues[20];
    mafValues[21] = rOther.mafValues[21];
    mafValues[22] = rOther.mafValues[22];
    mafValues[23] = rOther.mafValues[23];
    mafValues[24] = rOther.mafValues[24];
    return *this;
}

// ---------------------------------------------------------------------------
// 0x01022cb0  SortPlanetArray
// ---------------------------------------------------------------------------
// @ 0x01022cb0
void SortPlanetArray(cAutoRef* pBegin, cAutoRef* pEnd, void* pUnused,
                     cPointerCompare pCompare)
{
    if (pBegin == pEnd)
        return;
    for (cAutoRef* pSlot = pBegin + 1; pSlot != pEnd; ++pSlot) {
        cRefCounted* pValue = pSlot->mpObject;
        if (pValue != nullptr)
            pValue->AddRef();
        cAutoRef* pScan = pSlot;
        while (pScan != pBegin && pCompare(pValue, (pScan - 1)->mpObject) != 0) {
            cRefCounted* pOld = (pScan - 1)->mpObject;
            cRefCounted* pMoved = pScan->mpObject;
            if (pOld != pMoved) {
                if (pOld != nullptr)
                    pOld->AddRef();
                pScan->mpObject = pOld;
                if (pMoved != nullptr)
                    pMoved->Release();
            }
            --pScan;
        }
        pScan->Assign(pValue);
        if (pValue != nullptr)
            pValue->Release();
    }
}

// ---------------------------------------------------------------------------
// 0x01022d80  InsertPlanetSorted
// ---------------------------------------------------------------------------
// @ 0x01022d80
void InsertPlanetSorted(cAutoRef* pBegin, cAutoRef* pEnd, cPointerCompare pCompare)
{
    if (pBegin == pEnd)
        return;
    cRefCounted* pValue = pBegin->mpObject;
    if (pValue != nullptr)
        pValue->AddRef();
    cAutoRef* pScan = pBegin;
    while (pScan != pBegin && pCompare((pScan - 1)->mpObject, pValue) != 0) {
        cRefCounted* pOld = pScan->mpObject;
        cRefCounted* pMoved = (pScan - 1)->mpObject;
        if (pMoved != pOld) {
            if (pMoved != nullptr)
                pMoved->AddRef();
            pScan->mpObject = pMoved;
            if (pOld != nullptr)
                pOld->Release();
        }
        --pScan;
    }
    pScan->Assign(pValue);
    if (pValue != nullptr)
        pValue->Release();
}

// ---------------------------------------------------------------------------
// 0x01022e50  SiftPlanetHeap
// ---------------------------------------------------------------------------
// @ 0x01022e50
void SiftPlanetHeap(cAutoRef* pBegin, cAutoRef* pEnd, int32_t nLowBound,
                    int32_t nIndex, cRefCounted* pValue, cPointerCompare pCompare)
{
    int32_t nParent = (nIndex - 1) >> 1;
    while (nIndex > nLowBound) {
        if (pCompare(pValue, pBegin[nParent].mpObject) == 0)
            break;
        pBegin[nIndex].Assign(pBegin[nParent].mpObject);
        nIndex = nParent;
        nParent = (nIndex - 1) >> 1;
    }
    pBegin[nIndex].Assign(pValue);
    if (pValue != nullptr)
        pValue->Release();
}

// ---------------------------------------------------------------------------
// 0x01022f00  CompareCityDistance
// ---------------------------------------------------------------------------
// @ 0x01022f00
int32_t CompareCityDistance(cCivData* pLhs, cCivData* pRhs)
{
    const cVector3& rOrigin = *g_pCityReferencePoint;

    const cVector3* pLhsCity = pLhs->GetCities();
    cVector3 vLhs;
    vLhs.mfX = pLhsCity->mfX - rOrigin.mfX;
    vLhs.mfY = pLhsCity->mfY - rOrigin.mfY;
    vLhs.mfZ = pLhsCity->mfZ - rOrigin.mfZ;

    const cVector3* pRhsCity = pRhs->GetCities();
    cVector3 vRhs;
    vRhs.mfX = pRhsCity->mfX - rOrigin.mfX;
    vRhs.mfY = pRhsCity->mfY - rOrigin.mfY;
    vRhs.mfZ = pRhsCity->mfZ - rOrigin.mfZ;

    float fRhsLength = vRhs.mfZ * vRhs.mfZ + vRhs.mfY * vRhs.mfY + vRhs.mfX * vRhs.mfX;
    float fLhsLength = vLhs.mfZ * vLhs.mfZ + vLhs.mfY * vLhs.mfY + vLhs.mfX * vLhs.mfX;
    return fRhsLength > fLhsLength;
}
