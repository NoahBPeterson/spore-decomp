// Slice s00dec7c0 -- SP::cGalaxyGameEntryUIStateMachine asset-selection helpers.
//
//  00dec7c0  MakeNewAsset            queue the editor with a zero key for the current asset slot
//  00dec940  LoadAsset               load the asset of the given type (event tail-call)
//  00dec990  verb-icon probe         map the browser selection to a verb icon index
//  00decad0  ShowAssetButtonsForLevel  refresh the three asset buttons of one mode panel
//  00decd10  panel highlight refresh
//  00dece10  SetupStartState
//  00decf00  small panel flag helper
//  00decf20  panel id -> callback dispatch
//  00decf70  HighlightPanelButton
//  00decfd0  ToggleAssetLock
//  00ded030  bind the creature slot to the UI comm host
//  00ded0b0  key/panel slot test
//  00ded140  ResetAssetButtons
//  00ded390  ResetThemeIcons
//  00ded410  EditExistingAsset
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// ---------------------------------------------------------------------------------------------
// Shared value types.
// ---------------------------------------------------------------------------------------------
struct Key {
    uint32_t mnA;                                               // 0x000
    uint32_t mnB;                                               // 0x004
    uint32_t mnC;                                               // 0x008
};

struct Vec3 {
    float x, y, z;
};

// ---------------------------------------------------------------------------------------------
// UI object interfaces (only the slots this slice touches are named).
// ---------------------------------------------------------------------------------------------
class cUIWindow {
public:
    virtual void w00(); virtual void w04(); virtual void w08();
    virtual cUIWindow* FindChild(uint32_t nID);                 // 0x00c
    virtual void w10();
    virtual void SetParams(int32_t nA, int32_t nB);             // 0x014
    virtual void w18();
    virtual bool HasEntry(uint32_t nID);                        // 0x01c
    virtual void w20(); virtual void w24();
    virtual void SetFlag(int32_t nA, bool bB);                  // 0x028
    virtual uint32_t GetFlags();                                // 0x02c
    virtual void w30(); virtual void w34(); virtual void w38(); virtual void w3c();
    virtual void OnCommand(int32_t nCommand);                   // 0x040
    virtual void SelectPanel(int32_t nIndex, int32_t nParam);   // 0x044
    virtual void w48();
    virtual void w4c();
    virtual void w50(); virtual void w54(); virtual void w58(); virtual void w5c();
    virtual void w60(); virtual void w64(); virtual void w68(); virtual void w6c();
    virtual void w70(); virtual void w74(); virtual void w78();
    virtual void Show(int32_t nShow, bool bEnable);             // 0x07c
    virtual void w80(); virtual void w84(); virtual void w88(); virtual void w8c();
    virtual void w90();                                         // 0x090
    virtual void w94(); virtual void w98(); virtual void w9c();
    virtual void wa0(); virtual void wa4();
    virtual cUIWindow* GetContent();                            // 0x0a8
};

class cSPUILayout {
public:
    cUIWindow* FindWindowByID(uint32_t nWindowID, int32_t nSearchChildren); // 0x008105b0
    uint8_t mPad000[0x34];
};

// The asset-panel button windows are reached through a view whose no-argument flag reader sits
// in the vtable slot that cUIWindow uses for SetFlag.
class cPanelButtonWindow {
public:
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
    virtual void w20(); virtual void w24();
    virtual uint32_t GetState();                                // 0x028
};

// 0x00831760 -- drawable image slot setter.
class Drawable_s0083_0c00 {
public:
    void SetImageIcon(int32_t nIndex, void* pImage);
};

// ---------------------------------------------------------------------------------------------
// The UI comm host (0x00b3d490 returns it).
// ---------------------------------------------------------------------------------------------
class cUICommHost {
public:
    void BindSlot(void* pKey, uint32_t nID, Vec3* pPos, uint32_t a, uint32_t b,
                  cUIWindow* pWindow);                          // 0x00ae8d00
    void Flush(uint32_t a, uint32_t b, uint32_t c, uint32_t d); // 0x00ae7e10
};

cUICommHost* __cdecl GetUiCtl();                                // 0x00b3d490

// ---------------------------------------------------------------------------------------------
// Editor model (the retail layout is larger than the PDB record; offsets below are the ones the
// code of this slice touches).
// ---------------------------------------------------------------------------------------------
class cEditorModel {
public:
    uint8_t mPad000[0x4c];                                      // 0x000
    Key mKey4C;                                                 // 0x04c
    uint8_t mPad058[0x0c];                                      // 0x058
    Key mKey64;                                                 // 0x064
    Key mKey70;                                                 // 0x070
    uint8_t mPad07C[0x28];                                      // 0x07c
    int32_t mnFieldA4;                                          // 0x0a4
    int32_t mnFieldA8;                                          // 0x0a8
};

// ---------------------------------------------------------------------------------------------
// Per mode panel block (stride 0x0c0).  +0x94/+0x98/+0x9c hold the three asset images,
// +0xa0/+0xa4/+0xa8 the three asset windows (creature/vehicle/building) and
// +0xac/+0xb0/+0xb4 the currently stored key of each slot (creature/building/vehicle).
// ---------------------------------------------------------------------------------------------
class cNewGameModePanel {
public:
    uint8_t mPad000[0x10];                                      // 0x000
    int32_t mnField10;                                          // 0x010
    uint8_t mPad014[0x60];                                      // 0x014
    uint32_t* mpValuesBegin;                                    // 0x074
    uint32_t* mpValuesEnd;                                      // 0x078
    uint8_t mPad07C[0x14];                                      // 0x07c
    int32_t mnComboValue;                                       // 0x090
    void* mpImageCreature;                                      // 0x094
    void* mpImageVehicle;                                       // 0x098
    void* mpImageBuilding;                                      // 0x09c
    int32_t mnWindowIDA0;                                       // 0x0a0
    int32_t mnWindowIDA4;                                       // 0x0a4
    int32_t mnWindowIDA8;                                       // 0x0a8
    uint32_t mnCreatureKey;                                     // 0x0ac
    uint32_t mnBuildingKey;                                     // 0x0b0
    uint32_t mnVehicleKey;                                      // 0x0b4
    int32_t mnHighlightWindowID;                                // 0x0b8
    bool mbFieldBC;                                             // 0x0bc
    uint8_t mPad0BD[0x03];
};

class cUIStateList {
public:
    void Reset();                                               // 0x00e20e00
    uint8_t mPad000[0x10];
};

// ---------------------------------------------------------------------------------------------
// Globals.
// ---------------------------------------------------------------------------------------------
extern bool gbFlag16a0ee8;                                      // 0x016a0ee8
extern bool gbFlag16a0e48;                                      // 0x016a0e48
extern uint32_t gThemeIconCount;                                // 0x016a0db0
extern const uint32_t kGUI_PanelButtonIDs[6];                   // 0x0147e4d8
extern const float kRealOne;                                    // 0x01485720

class cGameModeManager {
public:
    void SetGuideState(int32_t nState);                         // 0x00de53d0
    uint8_t mPad000[0x24];                                      // 0x000
    uint32_t* mpPanelIDBegin;                                   // 0x024
    uint32_t* mpPanelIDEnd;                                     // 0x028
};

extern cGameModeManager* gpGameMode;                            // 0x016a1344

// Editor entry as stored by the editor item list (stride 0x8c).
class cEditorEntry {
public:
    uint8_t mPad000[0x84];                                      // 0x000
    uint32_t mnField84;                                         // 0x084
    uint32_t mnField88;                                         // 0x088
};

// 0x00401010 -- UI event queue singleton.
class cAssetEntryList {
public:
    PV4 PV2 PV                                         // 0x00 .. 0x18
    virtual bool Matches(uint32_t nKey);                        // 0x01c
};

class cUIEventQueue {
public:
    PV8 PV8 PV4 PV2                                    // 0x00 .. 0x54
    virtual cAssetEntryList* GetSelectedEntry(uint32_t a, uint32_t b); // 0x058
};

cUIEventQueue* __cdecl GetUIEventQueue();                       // 0x00401010

// 0x00de3d00 -- place a layout supplied image into a window.
bool __cdecl FUN_00de3d00(cSPUILayout* pLayout, uint32_t nWindowID, void* pImage);

namespace SP {

class cGalaxyGameEntryUIStateMachine {
public:
    void MakeNewAsset(uint32_t nAssetType);                     // 0x00dec7c0
    void LoadAsset(uint32_t nAssetType);                        // 0x00dec940
    void ShowAssetButtonsForLevel(int32_t nLevel);              // 0x00decad0
    void SetupStartState();                                     // 0x00dece10
    void HighlightPanelButton(uint32_t nWindowID);              // 0x00decf70
    void ToggleAssetLock(uint32_t nWindowID);                   // 0x00decfd0
    void ResetAssetButtons(bool bBuilding, bool bCreature, bool bVehicle); // 0x00ded140
    void ResetThemeIcons();                                     // 0x00ded390
    void EditExistingAsset(uint32_t nAssetType);                // 0x00ded410

    void FUN_00decd10(int32_t nLevel);                          // 0x00decd10
    void FUN_00ded030();                                        // 0x00ded030
    bool FUN_00ded0b0(Key* pKey);                               // 0x00ded0b0

    void QueueEditorLaunch(uint32_t nLaunchID, const Key& rKey); // 0x00dec770
    void ResetButtons();                                        // 0x00dec500
    void UpdateLocks();                                         // 0x00dec570
    void HandleEvent(uint32_t nEvent);                          // 0x00df3be0

    uint8_t mPad000[0x28];                                      // 0x000
    cSPUILayout mLayout;                                        // 0x028
    uint8_t mPad05C[0x1c];                                      // 0x05c
    int32_t mnRolloverCount;                                    // 0x078
    uint32_t* mpRolloverWindowIDs;                              // 0x07c
    uint8_t mPad080[0x04];                                      // 0x080
    cNewGameModePanel maModePanels[7];                          // 0x084
    uint8_t mPad5C4[0x24];                                      // 0x5c4
    int32_t mnPendingAssetAction;                               // 0x5e8
    int32_t mnField5EC;                                         // 0x5ec
    uint8_t mPad5F0[0x18];                                      // 0x5f0
    cUIStateList mStateList;                                    // 0x608
    void* mpAssetIconCreature;                                  // 0x618
    void* mpAssetIconVehicle;                                   // 0x61c
    void* mpAssetIconBuilding;                                  // 0x620
    void* mpThemeIconBlank;                                     // 0x624
    cEditorModel* mpModel;                                      // 0x628
};

} // namespace SP

using SP::cGalaxyGameEntryUIStateMachine;

// helper host used by FUN_00decf00.
class cPanelWidget {
public:
    uint8_t mPad000[0x81];
    uint8_t mbField81;                                          // 0x081
};

class cPanelHost {
public:
    void FUN_00decf00(int32_t nID);                             // 0x00decf00
    uint8_t mPad000[0x10];
    cPanelWidget* mpWidget;                                     // 0x010
};

// =============================================================================================
// @ 0x00dec7c0
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::MakeNewAsset(uint32_t nAssetType)
{
    if (mpModel == 0)
        return;

    uint32_t nLaunchID = 0;

    switch (nAssetType) {
    case 0x9596477b:
        mnPendingAssetAction = 0x54045ce;
        if (mpModel->mnFieldA8 == 0) {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            nLaunchID = 0xef18a560;
        } else if (mpModel->mnFieldA8 == 1) {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            nLaunchID = 0xe46c381e;
        } else {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            nLaunchID = 0x465c50ba;
        }
        break;

    case 0x95964778:
        mnPendingAssetAction = 0x54045e3;
        if (mpModel->mnFieldA8 == 5) {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            nLaunchID = 0x96b24187;
        } else if (mpModel->mnFieldA8 == 4) {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            nLaunchID = 0x7d433fad;
        } else {
            return;
        }
        break;

    case 0x95964775:
        mnPendingAssetAction = 0x5404617;
        mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
        nLaunchID = 0x99e92f05;
        break;

    default:
        return;
    }

    QueueEditorLaunch(nLaunchID, Key());
}

// =============================================================================================
// @ 0x00dec940
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::LoadAsset(uint32_t nAssetType)
{
    switch (nAssetType) {
    case 0x9596477a:
        HandleEvent(0x54045ce);
        break;
    case 0x95964777:
        HandleEvent(0x54045e3);
        break;
    case 0x95964774:
        HandleEvent(0x5404617);
        break;
    }
}

// =============================================================================================
// @ 0x00dec990 -- the caller passes the editor entry in eax (non-standard convention).
// =============================================================================================
uint32_t __cdecl FUN_00dec990(cEditorEntry* pEntry)
{
    cUIEventQueue* pQueue = GetUIEventQueue();
    cAssetEntryList* pList = pQueue->GetSelectedEntry(pEntry->mnField88, pEntry->mnField84);
    if (pList == 0)
        return 1;

    if (pList->Matches(0x100f0f5a)) return 0xc;
    if (pList->Matches(0x11b79a74)) return 2;
    if (pList->Matches(0x11b79a70)) return 3;
    if (pList->Matches(0x032f92e6)) return 9;
    if (pList->Matches(0x11b79a72)) return 0xa;
    if (pList->Matches(0x11b79a71)) return 7;
    if (pList->Matches(0x11b79a78)) return 4;
    if (pList->Matches(0x11b79a75)) return 6;
    if (pList->Matches(0x11b79a76)) return 5;
    if (pList->Matches(0x11b79a77)) return 8;
    return pList->Matches(0x11b79a73) ? 11 : 1;
}

// =============================================================================================
// @ 0x00decad0
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::ShowAssetButtonsForLevel(int32_t nLevel)
{
    cNewGameModePanel* pPanel = &maModePanels[nLevel];

    cUIWindow* pWindow = mLayout.FindWindowByID(0x54045ce, 1);
    if (pWindow != 0) {
        pWindow->Show(2, pPanel->mbFieldBC);
        pWindow->Show(1, pPanel->mnCreatureKey != 0);
    }

    for (int32_t i = 0; i < mnRolloverCount; ++i) {
        cUIWindow* pRollover = mLayout.FindWindowByID(mpRolloverWindowIDs[i], 1);
        if (pRollover != 0)
            pRollover->Show(1, 0);
    }

    pWindow = mLayout.FindWindowByID(pPanel->mnWindowIDA0, 1);
    if (pWindow != 0)
        pWindow->Show(1, mpModel->mKey4C.mnA == 0);

    pWindow = mLayout.FindWindowByID(pPanel->mnWindowIDA8, 1);
    if (pWindow != 0)
        pWindow->Show(1, mpModel->mKey70.mnA == 0);

    pWindow = mLayout.FindWindowByID(pPanel->mnWindowIDA4, 1);
    if (pWindow != 0)
        pWindow->Show(1, mpModel->mKey64.mnA == 0);

    pWindow = mLayout.FindWindowByID(0x5404617, 1);
    if (pWindow != 0)
        pWindow->Show(1, pPanel->mnBuildingKey != 0);

    pWindow = mLayout.FindWindowByID(0x54045e3, 1);
    if (pWindow != 0)
        pWindow->Show(1, pPanel->mnVehicleKey != 0);

    if (pPanel->mpImageBuilding != 0)
        FUN_00de3d00(&mLayout, 0x5404617, pPanel->mpImageBuilding);

    if (pPanel->mpImageCreature != 0)
        FUN_00de3d00(&mLayout, 0x54045ce, pPanel->mpImageCreature);

    if (pPanel->mpImageVehicle != 0)
        FUN_00de3d00(&mLayout, 0x54045e3, pPanel->mpImageVehicle);

    bool bSelected = true;
    bool bNotSelected = false;
    if ((((cPanelButtonWindow*)mLayout.FindWindowByID(0x5404617, 1))->GetState() & 1) == 0) {
        bSelected = false;
        bNotSelected = true;
    }

    pWindow = mLayout.FindWindowByID(0x59434c0, 1);
    if (pWindow != 0)
        pWindow->Show(1, bSelected);

    pWindow = mLayout.FindWindowByID(0x6451450, 1);
    if (pWindow != 0)
        pWindow->Show(1, bNotSelected);

    UpdateLocks();
}

// =============================================================================================
// @ 0x00decd10
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::FUN_00decd10(int32_t nLevel)
{
    uint32_t windows[6] = {0x677345c, 0x67731fa, 0x6773513,
                           0x65fbfa0, 0x6775ebb, 0x6775ebc};
    for (uint32_t i = 0; i < 6; ++i) {
        cUIWindow* pWindow = mLayout.FindWindowByID(windows[i], 1);
        if (pWindow != 0)
            pWindow->Show(1, 0);
    }

    cUIWindow* pHighlight = mLayout.FindWindowByID(0x669f710, 1);
    cNewGameModePanel& rPanel = maModePanels[nLevel];
    if (pHighlight != 0) {
        int32_t nOtherID = rPanel.mnHighlightWindowID;
        if (nOtherID != 0) {
            cUIWindow* pOther = mLayout.FindWindowByID(nOtherID, 1);
            if (pOther == 0)
                goto done;
            pOther->Show(1, 1);
            pHighlight->Show(1, 1);
            goto done;
        }
        pHighlight->Show(1, 0);
    }
done:
    cUIWindow* pWindow;
    if (nLevel == 0)
        pWindow = mLayout.FindWindowByID(0x6775ebb, 1);
    else
        pWindow = mLayout.FindWindowByID(0x6775ebc, 1);
    if (pWindow != 0)
        pWindow->Show(1, 1);
}

// =============================================================================================
// @ 0x00dece10
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::SetupStartState()
{
    if (mLayout.FindWindowByID(0x5384881, 1) == 0)
        return;

    mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
    mLayout.FindWindowByID(0x5812792, 1)->Show(1, 0);
    mLayout.FindWindowByID(0x57f74f6, 1)->Show(1, 0);
    mLayout.FindWindowByID(0x5beb40d, 1)->Show(1, 1);
    ResetButtons();
    gpGameMode->SetGuideState(0);
    mStateList.Reset();
    mnField5EC = 0;
}

// =============================================================================================
// @ 0x00decf00
// =============================================================================================
void cPanelHost::FUN_00decf00(int32_t nID)
{
    if (mpWidget != 0)
        mpWidget->mbField81 = 1;
}

// =============================================================================================
// @ 0x00decf20
// =============================================================================================
void __stdcall FUN_00decf20(cUIWindow* pWindow, int32_t nPanelID)
{
    uint32_t nCount = (uint32_t)(gpGameMode->mpPanelIDEnd - gpGameMode->mpPanelIDBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (gpGameMode->mpPanelIDBegin[i] == (uint32_t)nPanelID) {
            pWindow->SelectPanel((int32_t)i, 0);
            return;
        }
    }
}

// =============================================================================================
// @ 0x00decf70
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::HighlightPanelButton(uint32_t nWindowID)
{
    for (uint32_t i = 0; i < 6; ++i) {
        cUIWindow* pWindow = mLayout.FindWindowByID(kGUI_PanelButtonIDs[i], 1);
        if (pWindow != 0) {
            cUIWindow* pChild = pWindow->FindChild(0x8ed27e7a);
            if (pChild != 0) {
                if (kGUI_PanelButtonIDs[i] == nWindowID)
                    pChild->SetFlag(4, 1);
                else
                    pChild->SetFlag(4, 0);
            }
        }
    }
}

// =============================================================================================
// @ 0x00decfd0
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::ToggleAssetLock(uint32_t nWindowID)
{
    cUIWindow* pWindow = mLayout.FindWindowByID(nWindowID, 1);
    cUIWindow* pChild = pWindow != 0 ? pWindow->FindChild(0x8ed27e7a) : 0;
    if ((pWindow->GetFlags() & 4) != 0)
        pChild->SetFlag(4, 0);
    else
        pChild->SetFlag(4, 1);
}

// =============================================================================================
// @ 0x00ded030
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::FUN_00ded030()
{
    if (!gbFlag16a0ee8)
        return;

    cUIWindow* pWindow = mLayout.FindWindowByID(0x657ce07, 1);
    Vec3 one = {kRealOne, kRealOne, kRealOne};
    GetUiCtl()->BindSlot(&mpModel->mKey4C, 0x4d594c50, &one, 0, 0, pWindow);
    GetUiCtl()->Flush(0, 0, 0, 0);
}

// =============================================================================================
// @ 0x00ded0b0
// =============================================================================================
bool cGalaxyGameEntryUIStateMachine::FUN_00ded0b0(Key* pKey)
{
    if (!gbFlag16a0e48)
        return true;

    cNewGameModePanel* pPanel = &maModePanels[mpModel->mnFieldA4];
    int32_t nExpected = 0;
    switch (mnPendingAssetAction) {
    case 0x54045ce:
        nExpected = (int32_t)pPanel->mnCreatureKey;
        break;
    case 0x54045e3:
        return pPanel->mnVehicleKey == pKey->mnB;
    case 0x5404617:
        return pPanel->mnBuildingKey == pKey->mnB;
    }
    return pKey->mnB == (uint32_t)nExpected;
}

// =============================================================================================
// @ 0x00ded140
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::ResetAssetButtons(bool bBuilding, bool bCreature,
                                                       bool bVehicle)
{
    if (mpModel == 0)
        return;

    cNewGameModePanel* pPanel = &maModePanels[mpModel->mnFieldA4];

    if (bCreature) {
        cUIWindow* pWindow = mLayout.FindWindowByID(0x5b744bc, 1);
        cUIWindow* pContent = pWindow->GetContent();
        cUIWindow* pChild = pContent != 0 ? pContent->FindChild(0x103c1908) : 0;
        pChild->SetParams(0, (int32_t)mpAssetIconCreature);
        mLayout.FindWindowByID(pPanel->mnWindowIDA0, 1)->Show(1, 1);
        mLayout.FindWindowByID(0x5b69a71, 1)->Show(1, 0);
        pWindow = mLayout.FindWindowByID(0x59461b1, 1);
        bool bLocked = false;
        if (pWindow != 0)
            bLocked = ((pWindow->GetFlags() >> 2) & 1) != 0;
        if (bLocked)
            ToggleAssetLock(0x59461b1);
    }

    if (bBuilding) {
        cUIWindow* pWindow = mLayout.FindWindowByID(0x5b73f5b, 1);
        cUIWindow* pContent = pWindow->GetContent();
        cUIWindow* pChild = pContent != 0 ? pContent->FindChild(0x103c1908) : 0;
        pChild->SetParams(0, (int32_t)mpAssetIconBuilding);
        mLayout.FindWindowByID(pPanel->mnWindowIDA8, 1)->Show(1, 1);
        mLayout.FindWindowByID(0x5b69a72, 1)->Show(1, 0);
        pWindow = mLayout.FindWindowByID(0x59461b2, 1);
        bool bLocked = false;
        if (pWindow != 0)
            bLocked = ((pWindow->GetFlags() >> 2) & 1) != 0;
        if (bLocked)
            ToggleAssetLock(0x59461b2);
    }

    if (bVehicle) {
        cUIWindow* pWindow = mLayout.FindWindowByID(0x5b745cc, 1);
        cUIWindow* pContent = pWindow->GetContent();
        cUIWindow* pChild = pContent != 0 ? pContent->FindChild(0x103c1908) : 0;
        pChild->SetParams(0, (int32_t)mpAssetIconVehicle);
        mLayout.FindWindowByID(pPanel->mnWindowIDA4, 1)->Show(1, 1);
        mLayout.FindWindowByID(0x5b69a70, 1)->Show(1, 0);
        pWindow = mLayout.FindWindowByID(0x59461b0, 1);
        bool bLocked = false;
        if (pWindow != 0)
            bLocked = ((pWindow->GetFlags() >> 2) & 1) != 0;
        if (bLocked)
            ToggleAssetLock(0x59461b0);
    }
}

// =============================================================================================
// @ 0x00ded390
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::ResetThemeIcons()
{
    for (uint32_t i = 0; i < gThemeIconCount; ++i) {
        cUIWindow* pWindow = mLayout.FindWindowByID(0x57f74f6 + i, 1);
        if (pWindow != 0) {
            cUIWindow* pContent = pWindow->GetContent();
            cUIWindow* pChild = pContent != 0 ? pContent->FindChild(0x53eb526) : 0;
            ((Drawable_s0083_0c00*)pChild)->SetImageIcon(0, mpThemeIconBlank);
            pWindow->w90();
        }
    }
}

// =============================================================================================
// @ 0x00ded410
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::EditExistingAsset(uint32_t nAssetType)
{
    if (mpModel == 0)
        return;

    switch (nAssetType) {
    case 0x95964779:
        if (mpModel->mKey4C.mnA == 0)
            return;
        mnPendingAssetAction = 0x54045ce;
        mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
        if (mpModel->mnFieldA8 == 0)
            QueueEditorLaunch(0xef18a560, mpModel->mKey4C);
        else if (mpModel->mnFieldA8 == 1)
            QueueEditorLaunch(0xe46c381e, mpModel->mKey4C);
        else
            QueueEditorLaunch(0x465c50ba, mpModel->mKey4C);
        break;

    case 0x95964776:
        if (mpModel->mKey64.mnA == 0)
            return;
        mnPendingAssetAction = 0x54045e3;
        if (mpModel->mnFieldA8 == 5) {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            QueueEditorLaunch(0x96b24187, mpModel->mKey64);
        } else if (mpModel->mnFieldA8 == 4) {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            QueueEditorLaunch(0x7d433fad, mpModel->mKey64);
        }
        break;

    case 0x95964773:
        if (mpModel->mKey70.mnA == 0)
            return;
        mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
        mnPendingAssetAction = 0x5404617;
        QueueEditorLaunch(0x99e92f05, mpModel->mKey70);
        break;
    }
}
