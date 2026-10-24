// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s010527f0.
//
// Space-stage tool strategies: scan events, tool activation / validity checks,
// beam and AoE tool updates, energy-repair cost adjustment.

typedef unsigned int size_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
#define nullptr 0

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

// ---------------------------------------------------------------------------
// Generic object model
// ---------------------------------------------------------------------------

// Simple reference counted object: slot 0x00 vftable head, 0x04 release,
// 0x08 secondary release, 0x0c enable, 0x10 liveness query.
class IRefCounted {
public:
    virtual void v00();
    virtual void AddRef();          // 0x04
    virtual void Release();         // 0x08
    virtual void SetEnabled(int bEnabled);  // 0x0c
    virtual bool IsAlive();         // 0x10
    virtual IRefCounted* Query(const void* pType);  // 0x14
};

class cSPTimer {
public:
    void Stop();
    uint32_t mPad00[4];
};

// Event log singleton interface.
class cSPUIEventLog {
public:
    void RemoveAllEventsOfSameType(int type);
    int PostFeedbackEvent(int type, uint32_t feedbackId, int a, int b, int c, int d);
    int GetEventInstanceID(int type, int data);
    void RestartTimer(int instanceId);
    void ModifyEventText(int instanceId, int textId);
    void ModifyData(int instanceId, int data);
    void RegisterCloseCallback(int instanceId, void* pCallback);
};

cSPUIEventLog* EventLog(int type, ...);
void KillSetiEffects();
void PlayUiSound(const char* pSound);

// ---------------------------------------------------------------------------
// Planet / inventory model
// ---------------------------------------------------------------------------

class cPlanetSpecies {
public:
    bool IsSpeciesScanned();
    void SetSpeciesAsScanned();
    bool IsColonyScanned();
    void SetColonyScanned();
    bool IsTribeScanned();
    void SetTribeAsScanned();
    float mPad24;
};

class cPlanet {
public:
    cPlanetSpecies* GetSpecies();   // 0x98
    cPlanetSpecies* GetTribe();     // 0x9c
    Vec3* GetPosition(Vec3* pOut);
    uint8_t mPad00[0x98];
};

class cPlanetModel {
public:
    Vec3* DirectionToSurfacePosition(Vec3* pOut, Vec3* pDirection);
    Vec3* MakeRandomWorldPosition(Vec3* pOut, Vec3* pDirection, float a, float b);
    uint8_t mPad00[0x20];
};

cPlanetModel* PlanetModel();
cPlanetModel* PlanetModel(Vec3* pOut);
cPlanetModel* PlanetModel(Vec3* pOut, Vec3* pDirection);
cPlanetModel* PlanetModel(Vec3* pOut, Vec3* pDirection, float a, float b);
Vec3* CreatureSurfacePoint(Vec3* pOut, cPlanetModel* pModel);
Vec3* RandomSurfacePoint(Vec3* pOut, cPlanetModel* pModel);

class cSPSpaceInventoryItem : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    Vec3* GetPosition(Vec3* pOut);       // 0x2c
    Vec3* GetDirection(Vec3* pOut);      // 0x30
};

// Player inventory: item slots plus tuning floats.
class cSPSpaceInventory {
public:
    uint8_t mPad00[0x34];
    cSPSpaceInventoryItem* mpHeldItem;   // 0x34
    uint8_t mPad38[0x4d0];
    cSPSpaceInventoryItem* mpShipItem;   // 0x508
    uint8_t mPad50c[0x34];
    float mCargoMax;                     // 0x540
    uint8_t mPad544[0x2b0];
    float mEnergyCurrent;                // 0x7f4
    float mEnergyMax;                    // 0x7f8
};

class cSPSimulatorSpaceGame {
public:
    cSPSpaceInventory* GetPlayerInventory();
    void* GetPlayerUFO();
    void* GetPlayerEmpire();
    uint8_t mPad00[0x20];
};

cSPSimulatorSpaceGame* SpaceGameGet();
cSPSimulatorSpaceGame* GetActiveSpaceGame();

struct IVectorItem : public IRefCounted {
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    Vec3* GetPosition(Vec3* pOut);   // 0x2c
};

void* NounManager();

// ---------------------------------------------------------------------------
// Tool strategy
// ---------------------------------------------------------------------------

class cSPToolStrategy {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual bool CanUseToolAt(int nToolId, int nTarget, int bFlag = 0);  // 0x20
    virtual bool IsValidLocation(int nTarget, Vec3* pPosition, int bFlag);  // 0x24
    virtual void v28();
    virtual void v2c();
    virtual void ShowToolEventLog(int nToolId, const void* pData, int nDataLen, int nFlags);  // 0x30
    virtual void v34();
    virtual void v38();
    virtual Vec3* GetMouseWorldPosition(Vec3* pOut);  // 0x3c
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void OnUseResult(int a, int b);  // 0x4c

    // 0x00 vftable
    cPlanet* mpPlanet;                 // 0x34
    uint8_t mPad38[0x48];
    uint8_t mbActive;                  // 0x80
    uint8_t mPad81[0x2f];
    IRefCounted* mpToolEffectA;        // 0xb0
    IRefCounted* mpToolEffectB;        // 0xb4
    uint8_t mPadB8[0x10];
    cSPTimer mTimer;                   // 0xc8
    uint8_t mPadD8[0x3c];
    cSPSpaceInventoryItem* mpTargetItem;  // 0x114
    IRefCounted* mpAreaEffect;          // 0x120
    IRefCounted* mpBeamProjectile;      // 0x124
    IRefCounted* mpEffectRef;           // 0x12c
    uint8_t mPad130[0x10];
    IRefCounted* mpActiveObject;        // 0x140
    uint8_t mPad144[0x2c];
    int mEventType;                     // 0x170

    // 0x00e14a30-style helpers replicated for this cluster.
    bool ActivateTool(int nToolId);                     // 0x00e537e0
    bool CanUseToolAtLocation(int nToolId, int nTarget);  // 0x00e53980
    void UpdatePassive();                                // 0x00e53bb0
    bool StopTool();                                     // 0x00e53650
    Vec3* FindTestTerrainLocation(Vec3* pOut, int nTarget);  // 0x00e53be0
    int SetErrorEvent(int nEventType, bool bPost);       // 0x00e527f0
};

class cSPDefaultBeamTool : public cSPToolStrategy {
public:
    bool StopTool();       // 0x00e53db0
    bool UpdateBeam();     // 0x00e53e00
};

class cSPDefaultAoETool : public cSPToolStrategy {
public:
    bool StopTool();       // 0x00e53ee0
    bool UpdateArea();     // 0x00e53f20
};

class cSPEnergyRepairToolStrategy : public cSPToolStrategy {
public:
    int AdjustCost(int nBaseCost);   // 0x00e53590
    int AdjustCostPercent(int nBaseCost);  // 0x00e535e0
};

class cSPScanToolStrategy : public cSPToolStrategy {
public:
    bool ActivateTool(int nToolId);           // 0x00e53fb0
    bool UseTool(int nToolId, int nTarget);   // 0x00e54080
    bool StopTool();                          // 0x00e53ff0
};

class cSPGetOutOfUFOToolStrategy : public cSPToolStrategy {
public:
    bool CanUseToolAtLocation(int nToolId, int nTarget);  // 0x00e540b0
    bool ActivateTool(int nToolId);                       // 0x00e540d0
};

// Free helpers used by the scan tools.
void AppendScanResult(void* pList, int* pOut);              // 0x01052880
void GetMouseRay(Vec3* pOut);                               // 0x01052f90
void ShowScanEventLog(int a, int b, int c, int pCallback, int nDuration);
int ScanSpecies(cPlanet* pPlanet);                          // 0x01053240
int ScanTribe(cPlanet* pPlanet);                            // 0x01053320
int ScanColony(cSPSimulatorSpaceGame* pGame);               // 0x010533d0
int ScanAllSpecies(cPlanet* pPlanet);                       // 0x010534c0
void AttachToolEffect(const void* pData);                   // 0x01053d50
bool IsModelValid(cPlanetModel* pModel);
void AddToolCharge(int nAmount);

int gSpaceToolFlags[8];

// ---------------------------------------------------------------------------
// 0x010527f0  cSPToolStrategy::SetErrorEvent
// ---------------------------------------------------------------------------
// @ 0x010527f0
int cSPToolStrategy::SetErrorEvent(int nEventType, bool bPost)
{
    int nResult = 0;
    if (bPost && mEventType != nEventType) {
        mEventType = nEventType;
        cSPUIEventLog* pLog = EventLog(nEventType);
        pLog->RemoveAllEventsOfSameType(nEventType);
        pLog = EventLog(nEventType, 0x131a9f54, 0, 0, 1, 0);
        nResult = pLog->PostFeedbackEvent(nEventType, 0x131a9f54, 0, 0, 1, 0);
        PlayUiSound("Ui_spg_target_error");
        KillSetiEffects();
    }
    return nResult;
}

// ---------------------------------------------------------------------------
// 0x01052880  AppendScanResult
// ---------------------------------------------------------------------------
// @ 0x01052880
void AppendScanResult(void* pList, int* pOut)
{
    if (pOut == nullptr)
        return;
    // The list drops its previous front element, then reports the new size.
    *(int*)pList = *(int*)pList;
    *pOut = *(int*)pList;
}

// ---------------------------------------------------------------------------
// 0x01052f00  cSPToolStrategy::GetPositionUnderMouse
// ---------------------------------------------------------------------------
// @ 0x01052f00
Vec3* cSPToolStrategy::GetMouseWorldPosition(Vec3* pOut)
{
    cSPSimulatorSpaceGame* pGame = GetActiveSpaceGame();
    cSPSpaceInventory* pInventory = pGame->GetPlayerInventory();
    cSPSpaceInventoryItem* pItem = nullptr;
    if (pInventory != nullptr)
        pItem = pInventory->mpHeldItem;

    IVectorItem* pRay = (IVectorItem*)NounManager();
    Vec3* pResult = pRay->GetPosition(pOut);
    pOut->mX = pResult->mX;
    pOut->mY = pResult->mY;
    pOut->mZ = pResult->mZ;
    return pOut;
}

// ---------------------------------------------------------------------------
// 0x01052f90  GetMouseRay
// ---------------------------------------------------------------------------
// @ 0x01052f90
void GetMouseRay(Vec3* pOut)
{
    IVectorItem* pRay = (IVectorItem*)NounManager();
    Vec3 local;
    Vec3* pResult = pRay->GetPosition(&local);
    pOut->mX = pResult->mX;
    pOut->mY = pResult->mY;
    pOut->mZ = pResult->mZ;
}

// ---------------------------------------------------------------------------
// 0x010531b0  SP::ShowScanEventLog
// ---------------------------------------------------------------------------
// @ 0x010531b0
void ShowScanEventLog(int pData, int a, int b, int pCallback, int nTextId)
{
    (void)a;
    (void)b;
    if (pData == 0)
        return;

    cSPUIEventLog* pLog = EventLog(0x6e000a7a, pData);
    int nEventId = pLog->GetEventInstanceID(0x6e000a7a, pData);
    if (nEventId != 0) {
        EventLog(nEventId)->RestartTimer(nEventId);
        return;
    }

    pLog = EventLog(0x6e000a7a, 0x131a9f54, 0, 0, 1, 0);
    nEventId = pLog->PostFeedbackEvent(0x6e000a7a, 0x131a9f54, 0, 0, 1, 0);
    EventLog(nEventId, nTextId)->ModifyEventText(nEventId, nTextId);
    EventLog(nEventId, pData)->ModifyData(nEventId, pData);
    if (pCallback != 0)
        EventLog(nEventId, pCallback)->RegisterCloseCallback(nEventId, (void*)pCallback);
}

// ---------------------------------------------------------------------------
// 0x01053240  ScanSpecies
// ---------------------------------------------------------------------------
// @ 0x01053240
int ScanSpecies(cPlanet* pPlanet)
{
    gSpaceToolFlags[10] = (int)pPlanet;
    cPlanetSpecies* pSpecies = pPlanet->GetSpecies();

    if (!pSpecies->IsSpeciesScanned()) {
        pSpecies->SetSpeciesAsScanned();
        ShowScanEventLog(pSpecies != nullptr ? 1 : 0, 0, 0, (int)pSpecies, 0);
        return 1;
    }
    ShowScanEventLog(pSpecies != nullptr ? 1 : 0, 0, 0, (int)pSpecies, 0);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x01053320  ScanTribe
// ---------------------------------------------------------------------------
// @ 0x01053320
int ScanTribe(cPlanet* pPlanet)
{
    gSpaceToolFlags[11] = (int)pPlanet;
    cPlanetSpecies* pTribe = pPlanet->GetTribe();

    if (!pTribe->IsTribeScanned()) {
        pTribe->SetTribeAsScanned();
        ShowScanEventLog(pTribe != nullptr ? 1 : 0, 0, 0, (int)pTribe, 0);
        return 1;
    }
    ShowScanEventLog(pTribe != nullptr ? 1 : 0, 0, 0, (int)pTribe, 0);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x010533d0  ScanColony
// ---------------------------------------------------------------------------
// @ 0x010533d0
int ScanColony(cSPSimulatorSpaceGame* pGame)
{
    if (pGame->mPad00[0] == 1 && pGame->mPad00[1] == 0x714)
        return 0;

    gSpaceToolFlags[12] = (int)pGame;

    Vec3 position;
    position.mX = 0.0f;
    position.mY = 0.0f;
    position.mZ = 0.0f;
    (void)position;

    cPlanetSpecies* pColony = pGame->GetPlayerUFO() != nullptr ? (cPlanetSpecies*)pGame->GetPlayerUFO() : nullptr;
    if (pColony != nullptr && !pColony->IsColonyScanned()) {
        pColony->SetColonyScanned();
        ShowScanEventLog(1, 0, 0, (int)pColony, 0);
        return 1;
    }
    ShowScanEventLog(pColony != nullptr ? 1 : 0, 0, 0, (int)pColony, 0);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x010534c0  ScanAllSpecies
// ---------------------------------------------------------------------------
// @ 0x010534c0
int ScanAllSpecies(cPlanet* pPlanet)
{
    cPlanetModel* pModel = PlanetModel();
    (void)pModel;

    gSpaceToolFlags[5] = (int)pPlanet;

    cPlanetSpecies* pSpecies = pPlanet->GetSpecies();
    if (!pSpecies->IsSpeciesScanned()) {
        pSpecies->SetSpeciesAsScanned();
        ShowScanEventLog(1, 0, 0, (int)pSpecies, 0);
        return 1;
    }
    ShowScanEventLog(pSpecies != nullptr ? 1 : 0, 0, 0, nullptr, 0);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x01053590  cSPEnergyRepairToolStrategy::AdjustCost
// ---------------------------------------------------------------------------
// @ 0x01053590
int cSPEnergyRepairToolStrategy::AdjustCost(int nBaseCost)
{
    cSPSpaceInventory* pInventory = GetActiveSpaceGame()->GetPlayerInventory();
    float fCurrent = pInventory->mEnergyCurrent;
    pInventory = GetActiveSpaceGame()->GetPlayerInventory();
    return (int)(((pInventory->mEnergyMax - fCurrent) / pInventory->mEnergyMax) * (float)nBaseCost);
}

// ---------------------------------------------------------------------------
// 0x010535e0  cSPEnergyRepairToolStrategy::AdjustCostPercent
// ---------------------------------------------------------------------------
// @ 0x010535e0
int cSPEnergyRepairToolStrategy::AdjustCostPercent(int nBaseCost)
{
    cSPSpaceInventory* pInventory = GetActiveSpaceGame()->GetPlayerInventory();
    float fCargo = pInventory->mCargoMax;
    pInventory = GetActiveSpaceGame()->GetPlayerInventory();
    float fMax = (float)(pInventory->mpShipItem != nullptr ? 1.0f : 0.0f);
    return (int)(((fMax - fCargo) / fMax) * (float)nBaseCost);
}

// ---------------------------------------------------------------------------
// 0x01053650  cSPToolStrategy::StopTool
// ---------------------------------------------------------------------------
// @ 0x01053650
bool cSPToolStrategy::StopTool()
{
    mbActive = 0;
    mTimer.Stop();
    return true;
}

// Secondary interface exposed by a cargo item holder at offset 0x0c.
class IQueryable {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual IRefCounted* Query(const void* pType);  // 0x0c
};

struct IItemHolder {
    IRefCounted* mpItem;      // 0x00
    uint32_t mPad04[2];       // 0x04
    IQueryable* mpSecondary;  // 0x0c
};

// ---------------------------------------------------------------------------
// 0x010536e0  interface_cast<cSPAnimalCargoInfo*, cSPSpaceInventoryItem, AutoRefCount>
// ---------------------------------------------------------------------------
// @ 0x010536e0
IRefCounted* CastToAnimalCargoInfo(IItemHolder* pHolder)
{
    if (pHolder->mpItem == nullptr)
        return nullptr;
    return pHolder->mpSecondary->Query((const void*)0x30fc270b);
}

// ---------------------------------------------------------------------------
// 0x01053700  interface_cast<cSPPlantCargoInfo*, cSPSpaceInventoryItem, AutoRefCount>
// ---------------------------------------------------------------------------
// @ 0x01053700
IRefCounted* CastToPlantCargoInfo(IItemHolder* pHolder)
{
    if (pHolder->mpItem == nullptr)
        return nullptr;
    return pHolder->mpSecondary->Query((const void*)0x70a2863c);
}

// ---------------------------------------------------------------------------
// 0x010537e0  cSPToolStrategy::ActivateTool
// ---------------------------------------------------------------------------
// @ 0x010537e0
bool cSPToolStrategy::ActivateTool(int nToolId)
{
    if (mpActiveObject != nullptr && !mpActiveObject->IsAlive()) {
        IRefCounted* pOld = mpActiveObject;
        mpActiveObject = nullptr;
        pOld->AddRef();
    }

    if (CanUseToolAt(nToolId, 1)) {
        (void)nToolId;
        mpEffectRef = mpEffectRef;
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x01053980  cSPToolStrategy::CanUseToolAtLocation
// ---------------------------------------------------------------------------
// @ 0x01053980
bool cSPToolStrategy::CanUseToolAtLocation(int nToolId, int nTarget)
{
    bool bResult = CanUseToolAt(nToolId, nTarget, 0);

    if (SpaceGameGet() == nullptr)
        return bResult;

    if (bResult) {
        cSPSpaceInventory* pInventory = GetActiveSpaceGame()->GetPlayerInventory();
        cSPSpaceInventoryItem* pHeld = nullptr;
        if (pInventory != nullptr)
            pHeld = pInventory->mpHeldItem;

        if (mpTargetItem == pHeld) {
            cSPSpaceInventoryItem* pItem = mpTargetItem;
            if (pItem != nullptr) {
                Vec3 dir;
                pItem->GetDirection(&dir);
                if (!IsValidLocation(nTarget, &dir, 1)) {
                    SetErrorEvent(0xfd2c5d0a, true);
                    return false;
                }
            }
        }
    }
    return bResult;
}

// ---------------------------------------------------------------------------
// 0x01053bb0  cSPToolStrategy::UpdatePassive
// ---------------------------------------------------------------------------
// @ 0x01053bb0
void cSPToolStrategy::UpdatePassive()
{
    if (mpActiveObject != nullptr && !mpActiveObject->IsAlive()) {
        IRefCounted* pOld = mpActiveObject;
        mpActiveObject = nullptr;
        pOld->AddRef();
        mEventType = mEventType;
    }
}

// ---------------------------------------------------------------------------
// 0x01053be0  cSPToolStrategy::FindTestTerrainLocation
// ---------------------------------------------------------------------------
// @ 0x01053be0
Vec3* cSPToolStrategy::FindTestTerrainLocation(Vec3* pOut, int nTarget)
{
    cSPSpaceInventory* pInventory = GetActiveSpaceGame()->GetPlayerInventory();
    pOut->mX = 0.0f;
    pOut->mY = 0.0f;
    pOut->mZ = 0.0f;

    Vec3 direction;
    if (pInventory == nullptr) {
        cPlanetModel* pModel = PlanetModel();
        if (pModel != nullptr) {
            Vec3 local;
            pModel = PlanetModel(&local);
            Vec3* pPoint = CreatureSurfacePoint(&local, pModel);
            pOut->mX = pPoint->mX;
            pOut->mY = pPoint->mY;
            pOut->mZ = pPoint->mZ;
        }
    } else {
        Vec3* pItemPos = pInventory->mpHeldItem->GetPosition(&direction);
        direction.mX = pItemPos->mX;
        direction.mY = pItemPos->mY;
        direction.mZ = pItemPos->mZ;

        cPlanetModel* pModel = PlanetModel();
        if (pModel != nullptr) {
            Vec3 local;
            pModel = PlanetModel(&local, &direction);
            Vec3* pPoint = pModel->DirectionToSurfacePosition(&local, &direction);
            pOut->mX = pPoint->mX;
            pOut->mY = pPoint->mY;
            pOut->mZ = pPoint->mZ;
        }
    }

    int i = 0;
    do {
        if (IsValidLocation(nTarget, pOut, 1))
            break;
        Vec3 local;
        cPlanetModel* pModel = PlanetModel(&local, pOut, 50.0f, 200.0f);
        Vec3* pPoint = pModel->MakeRandomWorldPosition(&local, pOut, 50.0f, 200.0f);
        pOut->mX = pPoint->mX;
        pOut->mY = pPoint->mY;
        pOut->mZ = pPoint->mZ;
        ++i;
    } while (i < 1000);

    if (i >= 1000) {
        for (i = 0; i < 1000; ++i) {
            if (IsValidLocation(nTarget, pOut, 1))
                return pOut;
            Vec3 local;
            PlanetModel(&local);
            Vec3* pPoint = CreatureSurfacePoint(&local, nullptr);
            pOut->mX = pPoint->mX;
            pOut->mY = pPoint->mY;
            pOut->mZ = pPoint->mZ;
        }
    }
    return pOut;
}

// ---------------------------------------------------------------------------
// 0x01053d50  AttachToolEffect
// ---------------------------------------------------------------------------
// @ 0x01053d50
void AttachToolEffect(const void* pData)
{
    (void)pData;
    uint8_t local40[16];
    uint8_t local30[48];
    local40[0] = 0;
    local30[0] = 0;
}

// ---------------------------------------------------------------------------
// 0x01053db0  cSPDefaultBeamTool::StopTool
// ---------------------------------------------------------------------------
// @ 0x01053db0
bool cSPDefaultBeamTool::StopTool()
{
    if (mpBeamProjectile != nullptr) {
        IRefCounted* pOld = mpBeamProjectile;
        mpBeamProjectile = nullptr;
        pOld->AddRef();
    }
    AddToolCharge(0);
    return true;
}

// ---------------------------------------------------------------------------
// 0x01053e00  cSPDefaultBeamTool::UpdateBeam
// ---------------------------------------------------------------------------
// @ 0x01053e00
bool cSPDefaultBeamTool::UpdateBeam()
{
    if (mpBeamProjectile != nullptr && mpBeamProjectile->IsAlive()) {
        IRefCounted* pOld = mpBeamProjectile;
        mpBeamProjectile = nullptr;
        pOld->AddRef();
    }
    if (mpBeamProjectile == nullptr)
        return false;

    Vec3 target;
    target.mX = 0.0f;
    target.mY = 0.0f;
    target.mZ = 0.0f;
    if (mpTargetItem != nullptr) {
        IVectorItem* pBeam = (IVectorItem*)mpTargetItem->Query((const void*)0x13f94d4);
        if (pBeam != nullptr) {
            pBeam->GetPosition(&target);
        } else {
            mpTargetItem->GetPosition(&target);
        }
    } else {
        mpTargetItem->GetPosition(&target);
    }

    IVectorItem* pProjectile = (IVectorItem*)mpBeamProjectile->Query((const void*)0x13f94d4);
    if (pProjectile != nullptr)
        pProjectile->GetPosition(&target);
    return true;
}

// ---------------------------------------------------------------------------
// 0x01053ee0  cSPDefaultAoETool::StopTool
// ---------------------------------------------------------------------------
// @ 0x01053ee0
bool cSPDefaultAoETool::StopTool()
{
    if (mpAreaEffect != nullptr) {
        IRefCounted* pOld = mpAreaEffect;
        mpAreaEffect = nullptr;
        pOld->AddRef();
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x01053f20  cSPDefaultAoETool::UpdateArea
// ---------------------------------------------------------------------------
// @ 0x01053f20
bool cSPDefaultAoETool::UpdateArea()
{
    if (mpAreaEffect == nullptr)
        return true;

    Vec3 position;
    position.mX = 0.0f;
    position.mY = 0.0f;
    position.mZ = 0.0f;

    IVectorItem* pArea = (IVectorItem*)mpAreaEffect->Query((const void*)0x13f94d4);
    if (pArea != nullptr)
        pArea->GetPosition(&position);
    else if (mpTargetItem != nullptr)
        mpTargetItem->GetPosition(&position);

    if (mpTargetItem != nullptr)
        mpTargetItem->GetDirection(&position);
    return true;
}

// ---------------------------------------------------------------------------
// 0x01053fb0  cSPScanToolStrategy::ActivateTool
// ---------------------------------------------------------------------------
// @ 0x01053fb0
bool cSPScanToolStrategy::ActivateTool(int nToolId)
{
    bool bResult = cSPToolStrategy::ActivateTool(nToolId);
    cPlanet* pPlanet = (cPlanet*)NounManager();
    if (pPlanet != nullptr) {
        cPlanetSpecies* pSpecies = pPlanet->GetSpecies();
        if (pSpecies != nullptr)
            (void)pSpecies;
    }
    return bResult;
}

// ---------------------------------------------------------------------------
// 0x01053ff0  cSPScanToolStrategy::StopTool
// ---------------------------------------------------------------------------
// @ 0x01053ff0
bool cSPScanToolStrategy::StopTool()
{
    cSPSpaceInventory* pInventory = SpaceGameGet()->GetPlayerInventory();
    (void)pInventory;

    IRefCounted* pOld = mpEffectRef;
    mpEffectRef = nullptr;
    if (pOld != nullptr)
        pOld->AddRef();

    if (mpBeamProjectile != nullptr) {
        IRefCounted* pProjectile = mpBeamProjectile;
        mpBeamProjectile = nullptr;
        pProjectile->AddRef();
    }
    AddToolCharge(0);
    return true;
}

// ---------------------------------------------------------------------------
// 0x01054080  cSPScanToolStrategy::UseTool
// ---------------------------------------------------------------------------
// @ 0x01054080
bool cSPScanToolStrategy::UseTool(int nToolId, int nTarget)
{
    if (mpEffectRef != nullptr)
        return true;
    return CanUseToolAtLocation(nToolId, nTarget);
}

// ---------------------------------------------------------------------------
// 0x010540b0  cSPGetOutOfUFOToolStrategy::CanUseToolAtLocation
// ---------------------------------------------------------------------------
// @ 0x010540b0
bool cSPGetOutOfUFOToolStrategy::CanUseToolAtLocation(int nToolId, int nTarget)
{
    return cSPToolStrategy::CanUseToolAtLocation(nToolId, nTarget);
}

// ---------------------------------------------------------------------------
// 0x010540d0  cSPGetOutOfUFOToolStrategy::ActivateTool
// ---------------------------------------------------------------------------
// @ 0x010540d0
bool cSPGetOutOfUFOToolStrategy::ActivateTool(int nToolId)
{
    if (!cSPToolStrategy::ActivateTool(nToolId))
        return false;
    ShowToolEventLog(nToolId, (const void*)0x16e1b14, 3, 0);
    return true;
}
