// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00c5a580.
//
// Space mission multi-step driver: step list bookkeeping, reward scheduling,
// raid-event counters and the element copy helpers used by the mission vector.

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef int intptr_t;
#define nullptr 0

float sqrtf(float fValue);
#define __builtin_sqrtf sqrtf

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

class IRefCounted {
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
void operator_delete__(void* pMemory);

class cVarListSerializer {
public:
    cVarListSerializer(void* pOwner, const void* pFields, int nFlags);
    bool Serialize(void* pData);
    int GetFields(int nFlags);
    uint8_t mPad00[0x414];
};

// ---------------------------------------------------------------------------
// Mission object model
// ---------------------------------------------------------------------------

class cSpatialObject : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual Vec3* GetPosition();            // 0x1c
    virtual void v20();
    uint8_t mPad18[0x1c];
};

class cGameData : public cSpatialObject {
public:
    uint8_t mPad34[0x100];                  // 0x34 .. 0x134
};

class cEmpire : public IRefCounted {
public:
    uint8_t mPad14[0x28];
};

class cCivData : public IRefCounted {
public:
    Vec3* GetCities();
    uint8_t mPad14[0x28];
};

class cMissionStep : public IRefCounted {
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
    IRefCounted** mpRewardBegin;            // 0x208
    IRefCounted** mpRewardEnd;              // 0x20c
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

// Planet-targeted mission that keeps a position and a target id.
class cPlanetMission : public cSPMission {
public:
    Vec3 mPlanetPosition;                   // 0x1f0
    uint8_t mPad1fc[0x30];                  // 0x1fc
    int mTargetId;                          // 0x22c

    bool Read(void* pData);                 // 0x00c5b210
    void UpdateFromPlanet();                // 0x00c5b280
    uint32_t GetOwnerEmpireId();            // 0x00c5b340
    void SetTarget(int nTarget);            // 0x00c5b370
    void SetPlanetPosition(int a, int b, int c);   // 0x00c5b3a0
};

class cSPRaidEvent : public cSPMission {
public:
    uint8_t mPad1f0[0x40];                  // 0x1f0
    int mTargetId;                          // 0x230
    void GenerateBomberCount();             // 0x00c5b530
    bool Init(int a, int b, int c);         // 0x00c5b600
    void Shutdown();                        // 0x00c5b660
    uint32_t CheckDistanceCondition();      // 0x00c5b6c0
    void Update();                          // 0x00c5b860
};

class cSPRaidPlunderEvent : public cSPRaidEvent {
public:
    void GeneratePirateCount();             // 0x00c5b510
    void BackgroundUpdate();                // 0x00c5b550
};

class cUFOKinestheticsTuning {
public:
    double GetGalaxyWarpMultiplier(uint a, uint b);
    uint8_t mPad00[0x11c];
    float mWarpSpeed;                       // 0x11c
};

class cSPMissionManager {
public:
    cSPMission* CreateMissionFromID(uint32_t id, uint32_t owner, cEmpire* pEmpire, void* pParent);
};

class cTerrainEditor {
public:
    void* GetCurrentTerrainSphere();
};

class cMessageServer {
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
    virtual void v24();
    virtual void v28();
    virtual void v2c(int* pTarget, const void* pMessage, int nFlags);
};

// 32-byte mission vector element (8 dwords).
struct MissionElement {
    uint32_t mField00;
    uint32_t mField04;
    uint32_t mField08;
    uint32_t mField0c;
    uint32_t mField10;
    uint32_t mField14;
    uint32_t mField18;
    uint32_t mField1c;
};

cSPMissionManager* GetMissionManager();
cTerrainEditor* NounManager();
Vec3* GetTerrainSpherePosition();
void* GetSpaceTuning();
cUFOKinestheticsTuning* GetKinestheticsTuning();
cUFOKinestheticsTuning* GetKinestheticsTuning(int a, int b);
cMessageServer* MessageServer();
void* GetUniverseContext();
void* GetActivePlanet();
int sGetNumUFOs(void* pDefinition, int keyA, int keyB);
void RemoveArtifact(int pOwner, void* pArtifact, uint16_t nCount);
void GetPropertyAsKeyArray(void* pDefinition, int key, void* pOut);
void* GetPropertyAsFloat();
void* GetMissionManagerForMission(uint32_t id);
void MissionManagerRelease(void* pMission);
void MissionStepListErase(void* pOwner);
void MissionStepListClear(void* pOwner);
void AppendMissionString(void* pString, const wchar_t* pFormat, ...);
void CreateMissionSteps(void* pOwner);
void AddStepToSchedule(uint32_t id);
void ResetStepSchedule();
bool IsPlanetValid(uint32_t planetId);
void SetPlanetHighlight(uint32_t planetId);
void ReleaseMissionList(void* pMission);
void ResizeMissionList(void* pList, int nCount);
void MissionVectorErase(void* pBegin, void* pEnd);
void ReleaseStepListContents();
void ReleaseRewardList();
void CopyStepList(cMissionMultiStep* pOwner);
void UpdateMissionDistance(cSPMission* pMission);
void SpawnRaidUFOs(void* pDefinition, int a, int b);
void ShutdownMissionStepState();
void UpdateStepUI(cSPMission* pMission);
void UpdateMissionStepState();
bool ReadMissionBase(void* pData);
void ClearMissionUI();
void RequestMissionRefresh();
cCivData* GetPlanetEmpire(uint32_t planetId);
void NotifyMissionEvent(uint32_t id);
double RoundValue(double fValue);

// ---------------------------------------------------------------------------
// 0x00c5a580  cMissionMultiStep::UpdateActiveStep
// ---------------------------------------------------------------------------
// @ 0x00c5a580
void cMissionMultiStep::UpdateActiveStep()
{
    if (!IsActive())
        return;
    int nIndex = mCurrentStepIndex;
    if (nIndex < 0)
        return;
    if (nIndex >= (int)(mpStepsEnd - mpStepsBegin))
        return;
    cMissionStep* pStep = mpStepsBegin[nIndex];
    if (pStep == nullptr)
        return;
    pStep->OnActivate();
}

// ---------------------------------------------------------------------------
// 0x00c5a610  cMissionMultiStep::CompleteStep
// ---------------------------------------------------------------------------
// @ 0x00c5a610
void cMissionMultiStep::CompleteStep()
{
    int nIndex = mCurrentStepIndex;
    cMissionStep* pStep = nullptr;
    if (nIndex >= 0 && nIndex < (int)(mpStepsEnd - mpStepsBegin))
        pStep = mpStepsBegin[nIndex];
    pStep->OnDeactivate();
}

// ---------------------------------------------------------------------------
// 0x00c5a790  cMissionMultiStep::OnAccept
// ---------------------------------------------------------------------------
// @ 0x00c5a790
void cMissionMultiStep::OnAccept()
{
    ResetStepSchedule();
    mCurrentStepIndex = -1;
    cSPMission* pFirst = nullptr;
    if (mpStepsEnd - mpStepsBegin > 0)
        pFirst = (cSPMission*)mpStepsBegin[0];
    pFirst->Accept();
    OnAccepted();
}

// ---------------------------------------------------------------------------
// 0x00c5a7d0  cMissionMultiStep::DestroyStepLists
// ---------------------------------------------------------------------------
// @ 0x00c5a7d0
void cMissionMultiStep::DestroyStepLists()
{
    ReleaseStepListContents();
    ReleaseRewardList();
    ReleaseMissionList(this);
}

// ---------------------------------------------------------------------------
// 0x00c5a990  cMissionMultiStep::Init
// ---------------------------------------------------------------------------
// @ 0x00c5a990
bool cMissionMultiStep::Init()
{
    if (!cSPMission::Init())
        return false;

    OnEnterStep();
    if (!OnValidateSteps())
        return false;
    OnResetSteps();

    int nCount = 0;
    void* pDefinition = nullptr;
    GetPropertyAsKeyArray(this, 0x6d03cf70, &pDefinition);
    int nStepCount = 0;
    AddStepToSchedule(0x6d03cf70);

    for (int i = 0; i < nStepCount; ++i) {
        uint32_t nMissionId = 0;
        uint32_t nOwner = 0;
        cSPMissionManager* pManager = GetMissionManager();
        cSPMission* pMission = pManager->CreateMissionFromID(nMissionId, nOwner,
                                                            GetOwnerEmpire(), this);
        if (pMission == nullptr) {
            ReleaseStepListContents();
            return false;
        }
        pMission->AddRef();
        if (mpRewardEnd < mpRewardBegin + 1) {
            *mpRewardEnd++ = pMission;
            pMission->AddRef();
        } else {
            ResizeMissionList(mpRewardEnd, 1);
        }
        pMission->Release();
        nCount = i + 1;
    }
    (void)nCount;

    CreateMissionSteps(this);
    mCurrentStepIndex = 0;
    return true;
}

// ---------------------------------------------------------------------------
// 0x00c5ab80  cMissionMultiStep::Shutdown
// ---------------------------------------------------------------------------
// @ 0x00c5ab80
void cMissionMultiStep::Shutdown()
{
    int nCount = (int)(mpStepsEnd - mpStepsBegin);
    for (int i = 0; i < nCount; ++i) {
        uint32_t id = 0;
        GetMissionManagerForMission(id);
        MissionManagerRelease(mpStepsBegin[i]);
    }

    IRefCounted** pSrc = mpRewardBegin;
    IRefCounted** pDst = mpRewardEnd;
    int nRewards = (int)(pSrc - pDst);
    while (pDst != pSrc) {
        if (*pDst != nullptr)
            (*pDst)->Release();
        ++pDst;
    }
    mpRewardEnd = mpRewardBegin;

    mpScheduleEnd = mpScheduleBegin;
    MissionVectorErase(mpStepsBegin, mpStepsEnd);
    mCurrentStepIndex = -1;
    ShutdownMissionStepState();
    (void)nRewards;
}

// ---------------------------------------------------------------------------
// 0x00c5ac60  cMissionMultiStep::GetUILongDescriptionSoFar
// ---------------------------------------------------------------------------
// @ 0x00c5ac60
void cMissionMultiStep::GetUILongDescriptionSoFar(void* pString)
{
    if (!IsActive())
        return;

    void** pStr = (void**)pString;
    if (pStr[0] != pStr[1]) {
        *(uint16_t*)pStr[0] = 0;
        pStr[1] = pStr[0];
    }

    if (mCurrentStepIndex >= 0) {
        for (int i = 0; i <= mCurrentStepIndex; ++i) {
            cMissionStep* pStep = mpStepsBegin[i];
            int nState = pStep->GetStepState();
            if (nState == 3 || nState == 9) {
                wchar_t* pBuffer = nullptr;
                wchar_t* pBufferEnd = nullptr;
                AppendMissionString(pString, L"%s\n\n", pBuffer);
                if (pBufferEnd - pBuffer > 2 && pBuffer != nullptr)
                    operator_delete__(pBuffer);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00c5ad40  cMissionMultiStep::cMissionMultiStep
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c5ae30  cMissionMultiStep::Write
// ---------------------------------------------------------------------------
// @ 0x00c5ae30
bool cMissionMultiStep::Write(void* pData)
{
    IOStream* pStream = ((ISerializer*)pData)->GetStream();
    uint32_t nType = 0x5626b91;
    WriteUint32(pStream->GetStream(), &nType, 1, 0);

    cVarListSerializer serializer(this, (const void*)0x01576840, 0x1a80d26);
    return serializer.Serialize(pData) != 0;
}

// ---------------------------------------------------------------------------
// 0x00c5aea0  cMissionMultiStep::Read
// ---------------------------------------------------------------------------
// @ 0x00c5aea0
bool cMissionMultiStep::Read(void* pData)
{
    IOStream* pStream = ((ISerializer*)pData)->GetStream();
    uint32_t nType = 0;
    ReadInt32(pStream->GetStream(), &nType, 1, 0);

    cVarListSerializer serializer(this, (const void*)0x01576840, 0x1a80d26);
    return serializer.Serialize(pData) != 0;
}

// ---------------------------------------------------------------------------
// 0x00c5b020  cMissionMultiStep::UpdateFromTerrainSphereA
// ---------------------------------------------------------------------------
// @ 0x00c5b020
void cMissionMultiStep::UpdateFromTerrainSphereA()
{
    UpdateMissionStepState();

    cTerrainEditor* pEditor = NounManager();
    ((IRefCounted*)pEditor->GetCurrentTerrainSphere())->v10();

    pEditor = NounManager();
    pEditor->GetCurrentTerrainSphere();
    Vec3* pPosition = GetTerrainSpherePosition();
    mpStepsBegin = *(cMissionStep***)pPosition;
    mpStepsEnd = *(cMissionStep***)((uint8_t*)pPosition + 4);
    mpStepsCap = *(cMissionStep***)((uint8_t*)pPosition + 8);

    void* pTuning = GetSpaceTuning();
    if (!((ISerializer*)pTuning)->Serialize(&mpStepsBegin))
        ClearMissionUI();
}

// ---------------------------------------------------------------------------
// 0x00c5b0b0  cMissionMultiStep::UpdateFromTerrainSphereB
// ---------------------------------------------------------------------------
// @ 0x00c5b0b0
void cMissionMultiStep::UpdateFromTerrainSphereB()
{
    ResetStepSchedule();

    cTerrainEditor* pEditor = NounManager();
    pEditor->GetCurrentTerrainSphere();
    Vec3* pPosition = GetTerrainSpherePosition();
    mpStepsBegin = *(cMissionStep***)pPosition;
    mpStepsEnd = *(cMissionStep***)((uint8_t*)pPosition + 4);
    mpStepsCap = *(cMissionStep***)((uint8_t*)pPosition + 8);

    void* pTuning = GetSpaceTuning();
    if (!((ISerializer*)pTuning)->Serialize(&mpStepsBegin))
        ClearMissionUI();
}

// ---------------------------------------------------------------------------
// 0x00c5b130  RefreshTargetPlanet
// ---------------------------------------------------------------------------
// @ 0x00c5b130
void RefreshTargetPlanet()
{
    cSPMission* pMission = nullptr;
    uint32_t nPlanet = pMission->GetTargetPlanet();
    SetPlanetHighlight(nPlanet);
    RequestMissionRefresh();
}

// ---------------------------------------------------------------------------
// 0x00c5b150  RefreshTargetPlanetConditional
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00c5b210  cPlanetMission::Read
// ---------------------------------------------------------------------------
// @ 0x00c5b210
bool cPlanetMission::Read(void* pData)
{
    bool bBase = ReadMissionBase(pData);
    cVarListSerializer serializer(this, (const void*)0x01576bc8, 0x1a80d26);
    bool bFields = serializer.Serialize(pData) != 0;
    bool bOk = bBase && bFields;

    if (((ISerializer*)pData)->GetType() < 0x210014u)
        mTargetId = *(int*)((uint8_t*)this + 0x8c);
    return bOk;
}

// ---------------------------------------------------------------------------
// 0x00c5b280  cPlanetMission::UpdateFromPlanet
// ---------------------------------------------------------------------------
// @ 0x00c5b280
void cPlanetMission::UpdateFromPlanet()
{
    UpdateMissionStepState();
    int nTarget = mTargetId;
    Vec3* pPosition;
    if (nTarget == -1) {
        cTerrainEditor* pEditor = NounManager();
        ((IRefCounted*)pEditor->GetCurrentTerrainSphere())->v10();
        pEditor = NounManager();
        pEditor->GetCurrentTerrainSphere();
        pPosition = GetTerrainSpherePosition();
    } else {
        IsPlanetValid(nTarget);
        int nEmpire = (int)(intptr_t)GetPlanetEmpire((uint32_t)nTarget);
        if (nEmpire == 0)
            return;
        pPosition = GetTerrainSpherePosition();
    }

    mPlanetPosition = *pPosition;

    void* pTuning = GetSpaceTuning();
    if (!((ISerializer*)pTuning)->Serialize(&mPlanetPosition))
        ClearMissionUI();
}

// ---------------------------------------------------------------------------
// 0x00c5b340  cPlanetMission::GetOwnerEmpireId
// ---------------------------------------------------------------------------
// @ 0x00c5b340
uint32_t cPlanetMission::GetOwnerEmpireId()
{
    uint32_t nEmpire = GetTargetPlanet();
    if (nEmpire == 0)
        return 0;
    IsPlanetValid(nEmpire);
    return (uint32_t)(intptr_t)GetPlanetEmpire(nEmpire);
}

// ---------------------------------------------------------------------------
// 0x00c5b370  cPlanetMission::SetTarget
// ---------------------------------------------------------------------------
// @ 0x00c5b370
void cPlanetMission::SetTarget(int nTarget)
{
    if (nTarget != 0)
        mTargetId = *(int*)((uint8_t*)this + 0x84);
}

// ---------------------------------------------------------------------------
// 0x00c5b3a0  cPlanetMission::SetPlanetPosition
// ---------------------------------------------------------------------------
// @ 0x00c5b3a0
void cPlanetMission::SetPlanetPosition(int a, int b, int c)
{
    *(int*)((uint8_t*)this + 0x224) = a;
    *(int*)((uint8_t*)this + 0x228) = b;
    *(int*)((uint8_t*)this + 0x22c) = c;
}

// ---------------------------------------------------------------------------
// 0x00c5b3d0  WriteMissionElementList
// ---------------------------------------------------------------------------
// @ 0x00c5b3d0
void WriteMissionElementList(ISerializer* pSerializer, MissionElement** ppElements)
{
    MissionElement* pBegin = ppElements[0];
    MissionElement* pEnd = ppElements[1];

    IOStream* pStream = pSerializer->GetStream();
    uint32_t nType = 0;
    int nCount = (int)((uint8_t*)pEnd - (uint8_t*)pBegin) >> 5;
    WriteUint32(pStream->GetStream(), &nType, 1, 0);

    for (MissionElement* pCur = pBegin; pCur != pEnd; ++pCur)
        ((IRefCounted*)pCur->mField00)->AddRef();

    nCount = 0;
    (void)nCount;
}

// ---------------------------------------------------------------------------
// 0x00c5b450  CopyMissionElementsForward
// ---------------------------------------------------------------------------
// @ 0x00c5b450
MissionElement* CopyMissionElementsForward(MissionElement* pFirst, MissionElement* pLast,
                                           MissionElement* pDest)
{
    while (pFirst != pLast) {
        *pDest = *pFirst;
        ++pFirst;
        ++pDest;
    }
    return pDest;
}

// ---------------------------------------------------------------------------
// 0x00c5b4b0  CopyMissionElementsBackward
// ---------------------------------------------------------------------------
// @ 0x00c5b4b0
MissionElement* CopyMissionElementsBackward(MissionElement* pFirst, MissionElement* pLast,
                                            MissionElement* pDest)
{
    MissionElement* pSrc = pLast;
    while (pSrc != pFirst) {
        --pSrc;
        --pDest;
        *pDest = *pSrc;
    }
    return pDest;
}

// ---------------------------------------------------------------------------
// 0x00c5b510  cSPRaidPlunderEvent::GeneratePirateCount
// ---------------------------------------------------------------------------
// @ 0x00c5b510
void cSPRaidPlunderEvent::GeneratePirateCount()
{
    sGetNumUFOs(this, 0x398db08, 0x398db09);
}

// ---------------------------------------------------------------------------
// 0x00c5b530  cSPRaidEvent::GenerateBomberCount
// ---------------------------------------------------------------------------
// @ 0x00c5b530
void cSPRaidEvent::GenerateBomberCount()
{
    sGetNumUFOs(this, 0x2fd1ef6, 0x2fd1efa);
}

// ---------------------------------------------------------------------------
// 0x00c5b550  cSPRaidPlunderEvent::BackgroundUpdate
// ---------------------------------------------------------------------------
// @ 0x00c5b550
void cSPRaidPlunderEvent::BackgroundUpdate()
{
    uint32_t nPlanet = GetTargetPlanet();
    if (IsPlanetValid(nPlanet))
        return;

    GetTargetPlanet();
    void* pWorld = GetActivePlanet();
    uint32_t nPlanetId = GetTargetPlanet();
    int pList = *(int*)((uint8_t*)(void*)nPlanetId + 0x13c);
    int nCount = (*(int*)((uint8_t*)pList + 0x138) - *(int*)((uint8_t*)pList + 0x134)) / 0x2c;
    for (int i = nCount - 1; i >= 0; --i) {
        uint8_t* pEntry = (uint8_t*)(*(int*)((uint8_t*)pList + 0x134) + i * 0x2c);
        if ((*(uint8_t*)(pEntry + 0x28) & 8) != 0 && *(uint8_t*)(pEntry + 0x12) == 4) {
            uint32_t artifact[3];
            artifact[0] = *(uint32_t*)pEntry;
            artifact[1] = 0;
            artifact[2] = 0;
            RemoveArtifact(pList, artifact, *(uint16_t*)(pEntry + 0x10));
        }
    }
    (void)pWorld;
}

// ---------------------------------------------------------------------------
// 0x00c5b600  cSPRaidEvent::Init
// ---------------------------------------------------------------------------
// @ 0x00c5b600
bool cSPRaidEvent::Init(int a, int b, int c)
{
    if (!cSPMission::Init())
        return false;

    void* pDefinition = nullptr;
    if (pDefinition != nullptr) {
        if (((ISerializer*)pDefinition)->Serialize((void*)0x39787b4) && (c & 0x10000) != 0) {
            uint8_t* pKeyArray = nullptr;
            GetPropertyAsKeyArray(nullptr, 0x39787b4, nullptr);
            (void)pKeyArray;
        }
    }
    (void)a;
    (void)b;
    return true;
}

// ---------------------------------------------------------------------------
// 0x00c5b660  cSPRaidEvent::Shutdown
// ---------------------------------------------------------------------------
// @ 0x00c5b660
void cSPRaidEvent::Shutdown()
{
    GetTargetPlanet();
    SpawnRaidUFOs(nullptr, 0, 0);
    RequestMissionRefresh();
    uint32_t nPlanet = GetTargetPlanet();
    SetPlanetHighlight(nPlanet);
    ShutdownMissionStepState();
    NotifyMissionEvent(0);

    cMessageServer* pServer = MessageServer();
    pServer->v2c(&mTargetId, (const void*)0x01622184, 0xffffd8f1);
}

// ---------------------------------------------------------------------------
// 0x00c5b6c0  cSPRaidEvent::CheckDistanceCondition
// ---------------------------------------------------------------------------
// @ 0x00c5b6c0
uint32_t cSPRaidEvent::CheckDistanceCondition()
{
    uint32_t nContext = (uint32_t)(intptr_t)GetUniverseContext();
    (void)nContext;
    void* pTuning = GetSpaceTuning();
    if (!((ISerializer*)pTuning)->Serialize(&mTargetId))
        return 0;

    cUFOKinestheticsTuning* pKinesthetics = GetKinestheticsTuning();
    float fWarpSpeed = pKinesthetics->mWarpSpeed;
    pKinesthetics = GetKinestheticsTuning(1, 4);
    double fMultiplier = pKinesthetics->GetGalaxyWarpMultiplier(1, 4);

    cCivData* pTarget = nullptr;
    uint32_t nEmpire = (uint32_t)mTargetId;
    if (nEmpire != 0)
        pTarget = GetPlanetEmpire(nEmpire);

    GetTargetPlanet();
    cCivData* pPlanet = GetPlanetEmpire(0);
    Vec3* pCitiesA = pPlanet->GetCities();
    Vec3* pCitiesB = pTarget->GetCities();

    float fDx = pCitiesB->mX - pCitiesA->mX;
    float fDy = pCitiesB->mY - pCitiesA->mY;
    float fDz = pCitiesB->mZ - pCitiesA->mZ;
    float fDistance = (float)(__builtin_sqrtf(fDx * fDx + fDy * fDy + fDz * fDz) /
                              (fMultiplier * (double)fWarpSpeed));
    if (fDistance > 10000.0f)
        fDistance = 10000.0f;

    float fBudget = (float)mTargetId;
    if (fBudget <= 10000.0f - fDistance)
        return 0;
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00c5b860  cSPRaidEvent::Update
// ---------------------------------------------------------------------------
// @ 0x00c5b860
void cSPRaidEvent::Update()
{
    float fThreshold = 10.0f;
    void* pDefinition = nullptr;
    if (pDefinition != nullptr) {
        if (((ISerializer*)pDefinition)->Serialize((void*)0x3a38abe) &&
            *(uint16_t*)((uint8_t*)pDefinition + 0x12) == 0xd) {
            float* pValue = (float*)GetPropertyAsFloat();
            fThreshold = *pValue;
        }
    }

    int nScaled = (int)(float)RoundValue((double)fThreshold * 1000.0);

    cUFOKinestheticsTuning* pKinesthetics = GetKinestheticsTuning();
    float fWarpSpeed = pKinesthetics->mWarpSpeed;
    pKinesthetics = GetKinestheticsTuning(1, 4);
    double fMultiplier = pKinesthetics->GetGalaxyWarpMultiplier(1, 4);

    cCivData* pTarget = nullptr;
    uint32_t nEmpire = (uint32_t)mTargetId;
    if (nEmpire != 0)
        pTarget = GetPlanetEmpire(nEmpire);

    GetTargetPlanet();
    cCivData* pPlanet = GetPlanetEmpire(0);
    Vec3* pCitiesA = pPlanet->GetCities();
    Vec3* pCitiesB = pTarget->GetCities();

    float fDx = pCitiesB->mX - pCitiesA->mX;
    float fDy = pCitiesB->mY - pCitiesA->mY;
    float fDz = pCitiesB->mZ - pCitiesA->mZ;
    float fDistance = (float)(__builtin_sqrtf(fDx * fDx + fDy * fDy + fDz * fDz) /
                              (fMultiplier * (double)(fWarpSpeed * (float)nScaled)));
    if (fDistance > 10000.0f)
        fDistance = 10000.0f;

    UpdateStepUI(this);
}
