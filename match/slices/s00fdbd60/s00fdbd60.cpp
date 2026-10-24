// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00fdbd60.
//
// Space app mode: space-game bring-up/teardown, planet load transitions,
// mouse-down handling for the starmap and the planet view, and the mode
// object's constructor and destructor.

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
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

class cLocalInputState {
public:
    void OnMouseDown(int nButton, int nX, int nY, int nFlags);
    uint8_t mPad00[0x60];
};

class cSPUISpace : public IRefCounted {
public:
    void ToggleStarmapFilters(bool bShow);
};

class cSPModeStrategy : public IRefCounted {
public:
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1c();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();

    uint8_t mPad1c[0x04];               // 0x1c
    cSPUISpace* mpUISpace;              // 0x20
    uint8_t mPad24[0x08];               // 0x24
    void* mpPlanetView;                 // 0x2c
};

class cGonzagoTimer {
public:
    cGonzagoTimer();
    ~cGonzagoTimer();
    uint8_t mPad00[0x08];
};

class cGonzagoSubsystemPart {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
};

class cGonzagoSubsystem : public cGonzagoSubsystemPart {
public:
    ~cGonzagoSubsystem();
    uint8_t mPad14[0x54];               // 0x14
};

class cIModeStrategy : public IRefCounted {
public:
    uint8_t mPad14[0x04];               // 0x14
};

class cIHandler : public IRefCounted {
public:
    uint8_t mPad14[0x04];               // 0x14
};

class cAppModeSpace : public cIModeStrategy, public cGonzagoSubsystem, public cIHandler {
public:
    cAppModeSpace();
    ~cAppModeSpace();

    void InitSpaceGame();
    void EnterSpaceGame();
    void ShutdownSPG();
    void LoadNewGamePlanet();
    void TransitionFromLoadToPlanet();
    void TransitionFromEditorToPlanet();
    void TransitionToEntry();
    void PlanetOnMouseDown();
    void StopEditorPlay();
    bool OnMouseDown(int nButton, int nX, int nY, int nFlags);

    void* mpStarMap;                    // 0x68
    void* mpUniverse;                   // 0x6c
    void* mpTerrain;                    // 0x70
    void* mpPlanetKeyData;              // 0x74
    int   mnPlanetContext;              // 0x78
    void* mpGonzagoWorld;               // 0x7c
    void* mpPlanetView;                 // 0x80
    void* mpStrategy;                   // 0x84
    uint8_t mbInitialized;              // 0x88
    uint8_t mPad89[0x03];               // 0x89
    uint8_t mPad8c[0x3c];               // 0x8c
    cLocalInputState mLocalInput;       // 0xc8
    int   mnDragStartX;                 // 0x128
    int   mnDragStartY;                 // 0x12c
    int   mnDragKind;                   // 0x130
    void* mpEmpire;                     // 0x134
    void* mpPlayer;                     // 0x138
    int   mnPlayerId;                   // 0x13c
    void* mpGonzagoAsset;               // 0x140
    uint8_t mPad144[0x14];              // 0x144
    uint8_t mbSpaceGameActive;          // 0x158
    uint8_t mPad159[0x03];              // 0x159
    cSPModeStrategy* mpGameMode;        // 0x15c
    void* mpHandler;                    // 0x160
    void* mpUISpace;                    // 0x164
    int   mnOldGameMode;                // 0x168
    void* mpEditor;                     // 0x16c
    uint8_t mPad170[0x1c];              // 0x170
    uint8_t mbEditorPlaying;            // 0x18c
    uint8_t mbFlag18d;                  // 0x18d
    uint8_t mbFlag18e;                  // 0x18e
    uint8_t mbFlag18f;                  // 0x18f
    uint8_t mbFlag190;                  // 0x190
    uint8_t mbFlag191;                  // 0x191
    uint8_t mbFlag192;                  // 0x192
    uint8_t mPad193;                    // 0x193
    void* mpListHead;                   // 0x194
};

class cGameNounManager {
public:
    void* GetAvatar(void* pTarget);
};

class cSPSimulatorPlayerUFO {
public:
    void* GetStarRecordUnderMouse();
    void InitForPlanet();
};

class cSPSimulatorSpaceGame {
public:
    void* GetPlayerInventory();
};

class cPlanetModel {
public:
    uint32_t GetPlanetKey();
};

class cStarMap {
public:
    void Init();
};

class cEffectsManager {
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
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7c();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void v98();
};

class cController {
public:
    void AwardAchievement(uint32_t nAchievement);
};

class cPropertyList {
public:
    virtual void v00();
    virtual void Release();
};

class cInventory {
public:
    virtual void v00();
    virtual void v04();
    virtual bool AddItem(void* pItem);
};

void* operator_new(size_t nSize, const char* pName, int a, int b, int c, int d);
void operator_delete__(void* pMemory);
cEffectsManager* EffectsManager();
void* GonzagoModelWorld();
void ResetSpaceEffects();
void* StarMapManager();
void GetUniverseContext();
void* NounManager();
void* GetTerrainSphere();
void* GetTerrainEditor();
void* AppTimer();
void* EditorPlayState();
void SetGameMode(uint32_t nMode);
void* CreateMessage(uint32_t nKey);
void SetTimeScale(uint32_t fScaleBits);
void SetGameSpeed(uint32_t nSpeed);
void SetPause(bool bPause);
void SetPaused(bool bPaused);
void* SpaceGameGet();
void* MissionActive();
void* PreloadTuning(uint32_t nKey);
void LoadMissionTuning(uint32_t nKey);
void UnloadMissionTuning();
void RefreshSpaceUI();
void* GetPlayerInventory();
float GetMissionScore();
void SetUniverseView(int nView);
void InitializeUniverseContext(void* pContext);
void SetStarMapView(int nView);
void ResetUIState();
void ShowStarmapFilters(int nMode);
void ClearSelection(int nId);
void SelectModeSlot(int nSlot);
void ApplyNounChanges();
void* GetPlayerEmpire(void** ppEmpire);
void* LivingUniverseEmpire();
bool IsSpaceGameActive();
void GetEmpireItems(void* pEmpire, void** ppItems);
void* AchievementService();
void* AchievementUnlocked(uint32_t nKey);
void* ControllerFromKey(uint32_t nKey);
void UnlockAchievement(void* pController, uint32_t nKey);
bool ReadPropertyKey(void* pList, uint32_t nKey, void** ppOut);
bool AddInventoryItem(cInventory* pInventory, uint32_t nKey);
void ShowItemPopup(void* pItem);
void ShutdownSpaceGame();
void* GetGonzagoAsset();
void ReleaseModeStrategy();
void ResetStarMap();
void ClearSpaceUI();
void UnregisterGameHandler();
void SetCursorMode(int nMode);
void ResetGridHighlight();
void DebugDrawGrid();
void UpdateGridCells(void* pCells, int nCount, float fRadius);
void UpdateGridOverlay(float fRadius, int nCount, void* pCells);
void DrawGridRing(int a);
void* GetLocalInput();
bool HandleMouseDown(int nButton, int nX, int nY, int nFlags);
void RefreshInputState();
bool IsDraggingNoun();
bool IsStarmapDragging();
bool HandleStarmapDrag();
bool HandleStarmapClick(int nButton, int nX, int nY);
void SelectStarRecord(void* pRecord);
void* GetAvatarForRecord(void* pRecord);
void* GetPlayerController(void* pAvatar);
void AttachCamera(void* pCamera, void* pController);
bool IsCameraAttached(void* pCamera, void* pController);
void AttachSelection(void* pCamera, void* pController);
void ShowPlanetInfo();
void ShowPlanetPanel(void* pRecord);
void SetLoadedPlanet();
void InitPlanetView();
void* GetActivePlanet();
void* PlanetModel();
void* CreatePlanetView(int a, int b);
void SetPlanetViewPlanet(void* pView, int a, int b);
void SetPlanetModelView(int nView);
void EnablePlanetFeatures();
void RefreshPlanetUI();
void* CreateTransitionMessage();
void* GetMessageTarget();
void PostMessage(void* pMessage);
void RefreshModeUI();
void ResetTransitionTuning();
void ShowMissionLog();
void EnterPlanetMode();
void SetMissionState(int nKey);
void SelectSpaceUI();
void InitializePlanetContext();
void InitSelectionState();
void SetSpaceTimeScale();
void NotifySpaceLoaded();

extern uint32_t gSpaceModeSlot;
extern uint32_t gEditorModeSlot;
extern uint32_t gActivePlanetKey;
extern cAppModeSpace* gSpaceAppMode;

// ---------------------------------------------------------------------------
// 0x00fdbd60  SP::cAppModeSpace::InitSpaceGame
// ---------------------------------------------------------------------------
// @ 0x00fdbd60
void cAppModeSpace::InitSpaceGame()
{
    EffectsManager()->v98();
    ResetSpaceEffects();

    Vec3 bounds;
    bounds.mX = -1500.0f;
    bounds.mY = -1500.0f;
    bounds.mZ = -500.0f;
    Vec3 other;
    other.mX = 1500.0f;
    other.mY = 1500.0f;
    other.mZ = 500.0f;
    (void)other;

    cGonzagoSubsystemPart* pWorld = (cGonzagoSubsystemPart*)GonzagoModelWorld();
    (void)pWorld;

    cStarMap* pStarMap = (cStarMap*)StarMapManager();
    pStarMap->Init();

    mpGameMode->Slot24();

    void* pUniverse = AppTimer();
    InitializeUniverseContext(pUniverse);

    void* pTerrain = GetTerrainSphere();
    void* pEditor = GetTerrainEditor();
    (void)pEditor;

    void* pState = nullptr;
    if (pState == nullptr) {
        void* pSphere = GetTerrainSphere();
        (void)pSphere;
        pState = GetTerrainEditor();
    }

    void* pTimer = AppTimer();
    if (!HandleMouseDown(0, (int)(intptr_t)pState, 0, 0)) {
        SetTimeScale(0x40000000);
        SetGameSpeed(0x40000);
    }

    mbSpaceGameActive = 1;
}

// ---------------------------------------------------------------------------
// 0x00fdbee0  SP::cAppModeSpace::EnterSpaceGame
// ---------------------------------------------------------------------------
// @ 0x00fdbee0
void cAppModeSpace::EnterSpaceGame()
{
    InitSpaceGame();
    LoadMissionTuning(0x1103192);
    UnloadMissionTuning();

    cSPSimulatorSpaceGame* pSpaceGame = (cSPSimulatorSpaceGame*)SpaceGameGet();
    void* pInventory = pSpaceGame->GetPlayerInventory();
    float fScore = GetMissionScore();
    (void)pInventory;
    (void)fScore;

    void* pMission = MissionActive();
    RefreshSpaceUI();
    (void)pMission;

    cSPUISpace* pSpaceUI = mpGameMode->mpUISpace;
    if (pSpaceUI != nullptr) {
        SetUniverseView(0);
        pSpaceUI->ToggleStarmapFilters(true);
    }
    ResetUIState();
    ClearSelection(-1);
    ClearSelection(2);
    NounManager();
    ApplyNounChanges();
}

// ---------------------------------------------------------------------------
// 0x00fdbf90  SP::AwardSpaceAchievements
// ---------------------------------------------------------------------------
// @ 0x00fdbf90
void AwardSpaceAchievements()
{
    void* pEmpire = nullptr;
    GetPlayerEmpire(&pEmpire);

    void* pUniverse = LivingUniverseEmpire();
    if (!IsSpaceGameActive()) {
        if (pEmpire != nullptr)
            ((cPropertyList*)pEmpire)->Release();
        return;
    }
    (void)pUniverse;

    void* pItems = nullptr;
    GetEmpireItems(pEmpire, &pItems);
    if (pItems != nullptr) {
        cPropertyList** ppItem = (cPropertyList**)pItems;
        while (ppItem != nullptr) {
            uint32_t nItemId = 0;
            uint32_t nItemKind = 0;
            GetTerrainSphere();
            (void)nItemId;
            (void)nItemKind;

            cPropertyList* pItem = nullptr;
            void* pPropertyManager = nullptr;
            (void)pPropertyManager;
            if (ReadPropertyKey(pItem, 0xccc6b976u, (void**)&pItem)) {
                uint32_t nKey = (uint32_t)(intptr_t)pItem;
                cController* pController = (cController*)ControllerFromKey(nKey);
                if (!AchievementUnlocked(nKey))
                    pController->AwardAchievement(nKey);

                uint32_t nItemKey = 0;
                if (ReadPropertyKey(pItem, 0x6b1e3e7bu, (void**)&nItemKey)) {
                    cSPSimulatorSpaceGame* pSpaceGame = (cSPSimulatorSpaceGame*)SpaceGameGet();
                    cInventory* pInventory = (cInventory*)pSpaceGame->GetPlayerInventory();
                    if (!pInventory->AddItem(&nItemKey))
                        ShowItemPopup(&nItemKey);
                }
            }
            if (pItem != nullptr)
                pItem->Release();
            ppItem = nullptr;
        }
        if (pItems != nullptr)
            ((cPropertyList*)pItems)->Release();
    }
    if (pEmpire != nullptr)
        ((cPropertyList*)pEmpire)->Release();
}

// ---------------------------------------------------------------------------
// 0x00fdc150  SP::cAppModeSpace::ShutdownSPG
// ---------------------------------------------------------------------------
// @ 0x00fdc150
void cAppModeSpace::ShutdownSPG()
{
    if (mbSpaceGameActive == 0)
        return;

    ShutdownSpaceGame();
    mbSpaceGameActive = 0;

    void* pGonzago = mpGonzagoAsset;
    if (pGonzago != nullptr) {
        mpGonzagoAsset = nullptr;
        ((cPropertyList*)pGonzago)->Release();
    }

    ResetStarMap();
    StarMapManager();
    ResetStarMap();

    void* pHandler = mpHandler;
    if (pHandler != nullptr) {
        mpHandler = nullptr;
        ((cPropertyList*)pHandler)->Release();
    }

    if (mpGameMode != nullptr) {
        ClearSpaceUI();
        cSPModeStrategy* pMode = mpGameMode;
        if (pMode != nullptr) {
            mpGameMode = nullptr;
            pMode->Release();
        }
    }

    SetCursorMode(mnOldGameMode);
    SetCursorMode(0x609b763);
    UnregisterGameHandler();
    ResetGridHighlight();
}

// ---------------------------------------------------------------------------
// 0x00fdc240  SP::cAppModeSpace::LoadNewGamePlanet
// ---------------------------------------------------------------------------
// @ 0x00fdc240
void cAppModeSpace::LoadNewGamePlanet()
{
    InitializePlanetContext();
    void* pPlanet = GetActivePlanet();
    cPlanetModel* pModel = (cPlanetModel*)PlanetModel();

    cPropertyList* pDefinition = nullptr;
    bool bHasDefinition = ReadPropertyKey(pDefinition, 0xe38475d9u, (void**)&pDefinition);
    if (bHasDefinition) {
        void* pView = CreatePlanetView(1, 1);
        pModel = (cPlanetModel*)pView;
        SetPlanetViewPlanet(pView, 1, 1);
        SetPlanetModelView(-9);
        EnablePlanetFeatures();
        RefreshPlanetUI();
        SetPaused(false);
        (void)pModel;
        InitSelectionState();

        if (pDefinition != nullptr) {
            void* pData = nullptr;
            if (ReadPropertyKey(pDefinition, 0xa274d68bu, &pData))
                SelectStarRecord(pData);
        }
        if (pDefinition != nullptr)
            pDefinition->Release();
    } else {
        if (pDefinition != nullptr)
            pDefinition->Release();
    }
    (void)pPlanet;
}

// ---------------------------------------------------------------------------
// 0x00fdc340  SP::cAppModeSpace::UpdateSpaceGrid
// ---------------------------------------------------------------------------
// @ 0x00fdc340
void UpdateSpaceGrid(cAppModeSpace* pMode, float fRadius, const Vec3* pCenter)
{
    void* pGrid = GetTerrainSphere();
    UpdateGridCells(pGrid, 0, fRadius);

    int nCount = 0;
    void* pCells = nullptr;
    if (nCount > 0) {
        for (int i = 0; i < nCount; ++i) {
            void* pCell = ((void**)pCells)[i];
            (void)pCell;
            bool bInside = true;
            float fDx = pCenter->mX - 0.0f;
            float fDy = pCenter->mY - 0.0f;
            float fDz = pCenter->mZ - 0.0f;
            if (bInside) {
                ResetGridHighlight();
                if (fDx * fDx + fDy * fDy + fDz * fDz < fRadius * fRadius)
                    DrawGridRing(0);
            }
        }
    }

    void* pOverlay = nullptr;
    UpdateGridOverlay(fRadius, 0, pOverlay);
    int nRings = 0;
    for (int i = 0; i < nRings; ++i)
        DrawGridRing(1);
    if (pOverlay != nullptr)
        operator_delete__(pOverlay);
    (void)pMode;
}

// ---------------------------------------------------------------------------
// 0x00fdc490  SP::cAppModeSpace::StopEditorPlay
// ---------------------------------------------------------------------------
// @ 0x00fdc490
void cAppModeSpace::StopEditorPlay()
{
    if (mbEditorPlaying != 0) {
        mbEditorPlaying = 0;
        RefreshModeUI();
    }
}

// ---------------------------------------------------------------------------
// 0x00fdc4b0  UnlinkListNode
// ---------------------------------------------------------------------------
// @ 0x00fdc4b0
int* UnlinkListNode(int* pOut, int** ppNode)
{
    int* pNode = *ppNode;
    int* pNext = *(int**)((uint8_t*)pNode + 4);
    *(int*)pNext[1] = *pNext;
    *(int*)(*pNext + 4) = pNext[1];
    operator_delete__(pNext);
    *pOut = (int)(intptr_t)pNode;
    return pOut;
}

// ---------------------------------------------------------------------------
// 0x00fdc520  SP::cAppModeSpace::OnMouseDown
// ---------------------------------------------------------------------------
// @ 0x00fdc520
bool cAppModeSpace::OnMouseDown(int nButton, int nX, int nY, int nFlags)
{
    mLocalInput.OnMouseDown(nButton, nX, nY, nFlags);
    bool bHandled = HandleMouseDown(nButton, nX, nY, nFlags);
    RefreshInputState();

    if (IsDraggingNoun())
        return bHandled;

    if (mpGameMode != nullptr && mpGameMode->mpPlanetView != nullptr) {
        if (IsStarmapDragging())
            return bHandled;
    }

    void* pContext = GetActivePlanet();
    if (pContext == nullptr) {
        StopEditorPlay();
        return bHandled;
    }

    if (nButton == 1000) {
        if (mnPlanetContext == 2) {
            cSPSimulatorPlayerUFO* pUFO = (cSPSimulatorPlayerUFO*)SpaceGameGet();
            void* pRecord = pUFO->GetStarRecordUnderMouse();
            if (pRecord != nullptr) {
                cGameNounManager* pNouns = (cGameNounManager*)NounManager();
                void* pAvatar = pNouns->GetAvatar(pRecord);
                SetPaused(false);
                void* pController = GetPlayerController(pAvatar);
                void* pCamera = *(void**)pAvatar;
                AttachCamera(pCamera, pController);
                (void)pCamera;
                if (IsCameraAttached(pCamera, pController)) {
                    AttachSelection(pCamera, pController);
                    return false;
                }
            }
            void* pOther = MissionActive();
            if (pRecord != nullptr && pOther != pRecord) {
                SelectStarRecord(pRecord);
                ShowPlanetPanel(pRecord);
                return true;
            }
        }
    } else if (nButton == 0x3e9 || nButton == 0x3eau) {
        mnDragStartX = nX;
        mnDragStartY = nY;
        SetGameMode(0);
        SelectModeSlot(0);
        SetGameMode(gSpaceModeSlot);
        SelectSpaceUI();
        SetGameMode(gEditorModeSlot);
        EnterPlanetMode();
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00fdc710  SP::cAppModeSpace::TransitionFromLoadToPlanet
// ---------------------------------------------------------------------------
// @ 0x00fdc710
void cAppModeSpace::TransitionFromLoadToPlanet()
{
    InitSpaceGame();
    void* pPlanet = GetActivePlanet();
    InitializePlanetContext();

    cPlanetModel* pModel = (cPlanetModel*)PlanetModel();
    if (pModel != nullptr) {
        uint32_t nKey = pModel->GetPlanetKey();
        (void)nKey;
        SetLoadedPlanet();
    }
    (void)pPlanet;

    SetPlanetModelView(0);
    RefreshPlanetUI();
    InitPlanetView();

    cSPSimulatorPlayerUFO* pUFO = (cSPSimulatorPlayerUFO*)SpaceGameGet();
    pUFO->InitForPlanet();

    void* pMessage = CreateTransitionMessage();
    PostMessage(pMessage);
    RefreshModeUI();
    ResetTransitionTuning();

    ResetUIState();
    ClearSelection(-1);
    NounManager();
    ApplyNounChanges();
}

// ---------------------------------------------------------------------------
// 0x00fdc800  SP::cAppModeSpace::TransitionFromEditorToPlanet
// ---------------------------------------------------------------------------
// @ 0x00fdc800
void cAppModeSpace::TransitionFromEditorToPlanet()
{
    InitSelectionState();
    void* pContext = GetActivePlanet();
    if (pContext == nullptr) {
        InitializePlanetContext();

        cPlanetModel* pModel = (cPlanetModel*)PlanetModel();
        if (pModel == nullptr) {
            void* pView = CreatePlanetView(1, 1);
            SetPlanetViewPlanet(pView, 1, 0);
        } else {
            uint32_t nKey = pModel->GetPlanetKey();
            (void)nKey;
            SetLoadedPlanet();
        }

        SetPlanetModelView(0);
        RefreshPlanetUI();
        InitPlanetView();

        void* pMessage = CreateTransitionMessage();
        PostMessage(pMessage);
        RefreshModeUI();
        ResetTransitionTuning();

        ResetUIState();
        ClearSelection(-1);
        NounManager();
        ApplyNounChanges();

        uint32_t nSlot = gSpaceModeSlot;
        void* pGameMode = mpGameMode->mpPlanetView;
        if (*(int*)((uint8_t*)pGameMode + 0x204) == 1)
            nSlot = 0xebb801;
        else
            nSlot = 0x1103193;
        (void)nSlot;
        SetGameSpeed(0xebb801);
        UnloadMissionTuning();
    } else {
        SetPaused(false);
        UnloadMissionTuning();
        SetUniverseView(0);

        if (mnPlanetContext == 1) {
            ShowMissionLog();
            return;
        }
        if (mnPlanetContext == 2) {
            mpGameMode->mpUISpace->ToggleStarmapFilters(true);
            StarMapManager();
            return;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00fdc980  SP::cAppModeSpace::TransitionToEntry
// ---------------------------------------------------------------------------
// @ 0x00fdc980
void cAppModeSpace::TransitionToEntry()
{
    if (mpGameMode != nullptr) {
        ShutdownSpaceGame();
        PlanetModel();
        RefreshPlanetUI();
        ShutdownSPG();
    }

    cEffectsManager* pEffects = EffectsManager();
    pEffects->v54();
    void* pEntry = nullptr;
    if (pEntry != nullptr) {
        (void)pEntry;
        cPropertyList* pList = (cPropertyList*)pEntry;
        (void)pList;
        operator_delete__(pEntry);
    }
}

// ---------------------------------------------------------------------------
// 0x00fdc9e0  SP::cAppModeSpace::PlanetOnMouseDown
// ---------------------------------------------------------------------------
// @ 0x00fdc9e0
void cAppModeSpace::PlanetOnMouseDown()
{
    ShutdownSpaceGame();
    PlanetModel();
    RefreshPlanetUI();
    ShutdownSPG();
}

// ---------------------------------------------------------------------------
// 0x00fdca00  SP::cAppModeSpace::cAppModeSpace
// ---------------------------------------------------------------------------
// @ 0x00fdca00
cAppModeSpace::cAppModeSpace()
{
    mpStarMap = nullptr;
    mpUniverse = nullptr;
    mpTerrain = nullptr;
    mpPlanetKeyData = nullptr;
    mnPlanetContext = 0;
    mpGonzagoWorld = nullptr;
    mpPlanetView = nullptr;
    mpStrategy = nullptr;
    mbInitialized = 0;
    mnDragStartX = 0;
    mnDragStartY = 0;
    mnDragKind = 0;
    mpEmpire = nullptr;
    mpPlayer = nullptr;
    mnPlayerId = 0;
    mpGonzagoAsset = nullptr;
    mbSpaceGameActive = 0;
    mpGameMode = nullptr;
    mpHandler = nullptr;
    mpUISpace = nullptr;
    mnOldGameMode = 0;
    mpEditor = nullptr;
    mbEditorPlaying = 0;
    mbFlag18d = 0;
    mbFlag18e = 0;
    mbFlag18f = 0;
    mbFlag190 = 0;
    mbFlag191 = 0;
    mbFlag192 = 0;
    mpListHead = nullptr;

    mpListHead = this;
    gSpaceAppMode = this;
}

// ---------------------------------------------------------------------------
// 0x00fdcba0  SP::cAppModeSpace::~cAppModeSpace
// ---------------------------------------------------------------------------
// @ 0x00fdcba0
cAppModeSpace::~cAppModeSpace()
{
    gSpaceAppMode = nullptr;

    if (mpGameMode != nullptr) {
        ReleaseModeStrategy();
        mpGameMode->Release();
    }

    void* pNode = mpListHead;
    while (pNode != mpListHead) {
        void* pNext = *(void**)pNode;
        operator_delete__(pNode);
        pNode = pNext;
    }

    if (mpUISpace != nullptr)
        ((cPropertyList*)mpUISpace)->Release();

    if (mpHandler != nullptr)
        ((cPropertyList*)mpHandler)->Release();

    if (mpGameMode != nullptr)
        ((cPropertyList*)mpGameMode)->Release();

    if (mpGonzagoAsset != nullptr)
        ((cPropertyList*)mpGonzagoAsset)->Release();

    if (mpEmpire != nullptr)
        ((cPropertyList*)mpEmpire)->Release();
}
