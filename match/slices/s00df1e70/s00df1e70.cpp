// SP::cGalaxyGameEntryUIStateMachine - new game flow UI helpers.
//
// The state machine drives the "new game" screens: the summary/creature
// preview, the asset browser callbacks and the random template pickers.

#include "types.h"

#define nullptr 0

// ---------------------------------------------------------------------------
// Shared value types.
// ---------------------------------------------------------------------------
struct Key {
    uint32_t mnA;                                               // 0x000
    uint32_t mnB;                                               // 0x004
    uint32_t mnC;                                               // 0x008
};

class KeyVec {
public:
    void DoInsertKey(Key* pPosition, const Key& rKey);          // 0x004e3e10
    KeyVec& operator=(const KeyVec& rOther);                    // 0x006609a0
    Key* mpBegin;                                               // 0x000
    Key* mpEnd;                                                 // 0x004
    Key* mpCap;                                                 // 0x008
};

// 36 byte functional match constraint.
struct cMatchConstraint {
    cMatchConstraint(int32_t nValue);                           // 0x00558830
    cMatchConstraint(uint32_t nKey, int32_t nEqual, int32_t nValue); // 0x00558860
    void Destroy();                                             // 0x006066f0
    uint32_t mnData[9];                                         // 0x000
};

struct cFunctionalMatch {
    cMatchConstraint maConstraints[2];                          // 0x000
};

// The object template database exposes a cdecl callback table; slot 0x34 runs
// a functional match over the template list and collects the matching keys.
struct cObjectTemplateVtbl {
    void* mpReserved[13];                                       // 0x000
    void (*mpfnFindMatches)(void* pDatabase, KeyVec* pOut, ...); // 0x034
};

struct cObjectTemplateDB {
    cObjectTemplateVtbl* mpVtbl;                                // 0x000
};

cObjectTemplateDB* ObjectTemplateDB();                          // 0x0067cb40

class cRandomLC {
public:
    uint32_t RandomUint32Uniform(uint32_t nRange);              // 0x00a68fb0
};

extern cRandomLC gRandom;                                       // 0x01601760
extern const float g_fMillisecondsPerSecond;                    // 0x013ec5b4
extern const float g_fElapsedTimeScale;                         // 0x013f5c88

class cTimerList {
public:
    void Restart();                                             // 0x00571e80
    long long GetElapsedTime();                                 // 0x0093a5e0
    void SetBoolProperty();                                     // 0x0093a2e0
    int32_t mnTimeLow;                                          // 0x000
    int32_t mnTimeHigh;                                         // 0x004
    uint8_t mPad008[0x10];                                      // 0x008
};

class cUIWindow;

class cSPUILayout {
public:
    cUIWindow* FindWindowByID(int32_t nWindowID, int32_t nSearchChildren); // 0x008105b0
    uint8_t mPad000[0x34];                                      // 0x000
};

class cUIPropertyList {
public:
    virtual void p00(); virtual void p04(); virtual void p08();
    virtual void p0c(); virtual void p10();
    virtual void SetInt(int32_t nValue);                        // 0x014
};

class cButtonDrawable {
public:
    Key mKey;                                                   // 0x000
    uint32_t mnExtra;                                           // 0x00c
};

class cUIWindow {
public:
    virtual void w00(); virtual void w04(); virtual void w08();
    virtual cUIWindow* FindChild(uint32_t nID);                 // 0x00c
    virtual void w10();
    virtual void SetParams(int32_t nA, int32_t nB);             // 0x014
    virtual void w18(); virtual void w1c(); virtual void w20(); virtual void w24();
    virtual void SetFlag(int32_t nA, int32_t nB);               // 0x028
    virtual uint32_t GetFlags();                                // 0x02c
    virtual void w30(); virtual void w34(); virtual void w38(); virtual void w3c();
    virtual void OnCommand(int32_t nCommand);                   // 0x040
    virtual void w44(); virtual void w48();
    virtual void SetSelection(Key* pKey, Key* pParam);          // 0x04c
    virtual void w50(); virtual void w54(); virtual void w58(); virtual void w5c();
    virtual void w60(); virtual void w64(); virtual void w68(); virtual void w6c();
    virtual void w70(); virtual void w74(); virtual void w78();
    virtual void Show(int32_t nShow, int32_t nEnable);          // 0x07c
    virtual void w80(); virtual void w84(); virtual void w88(); virtual void w8c();
    virtual void OnClick();                                     // 0x090
    virtual void w94(); virtual void w98(); virtual void w9c();
    virtual void wa0(); virtual void wa4();
    virtual cUIWindow* GetContent();                            // 0x0a8
    uint8_t mPad004[0x208];                                     // 0x004
    cUIPropertyList mPropertyList;                              // 0x20c
};

// ---------------------------------------------------------------------------
// Editor model and the per mode panel block (stride 0x0c0).
// ---------------------------------------------------------------------------
class cEditorModel {
public:
    uint8_t mPad000[0x4c];                                      // 0x000
    Key mKey4C;                                                 // 0x04c
    uint8_t mPad058[0x0c];                                      // 0x058
    Key mKey64;                                                 // 0x064
    Key mKey70;                                                 // 0x070
    uint8_t mPad07C[0x14];                                      // 0x07c
    int32_t mnField90;                                          // 0x090
    uint8_t mPad094[0x0c];                                      // 0x094
    int32_t mnFieldA0;                                          // 0x0a0
    int32_t mnFieldA4;                                          // 0x0a4
    int32_t mnFieldA8;                                          // 0x0a8
    int32_t mnFieldAC;                                          // 0x0ac
    int32_t mnFieldB0;                                          // 0x0b0
};

class cNewGameModePanel {
public:
    uint8_t mPad000[0x10];                                      // 0x000
    int32_t mnField10;                                          // 0x010
    uint8_t mPad014[0x60];                                      // 0x014
    uint32_t* mpValuesBegin;                                    // 0x074
    uint32_t* mpValuesEnd;                                      // 0x078
    uint8_t mPad07C[0x14];                                      // 0x07c
    int32_t mnComboValue;                                       // 0x090
    uint8_t mPad094[0x0c];                                      // 0x094
    int32_t mnWindowIDA0;                                       // 0x0a0
    int32_t mnWindowIDA4;                                       // 0x0a4
    int32_t mnWindowIDA8;                                       // 0x0a8
    int32_t mnFieldAC;                                          // 0x0ac
    uint8_t mPad0B0[0x10];                                      // 0x0b0
};

class cUIStateList {
public:
    void Reset();                                               // 0x00e20e00
    void Remove(int32_t nID);                                   // 0x00e21040
    uint8_t mPad000[0x14];                                      // 0x000
    int32_t mnField14;                                          // 0x014
    uint8_t mPad018[0x08];                                      // 0x018
};

// ---------------------------------------------------------------------------
// Globals and helper subsystems.
// ---------------------------------------------------------------------------
class cGameModeManager {
public:
    void SetGuideState(int32_t nState);                         // 0x00de53d0
    void LoadMode(int32_t nMode, int32_t nFlag);                // 0x00de86d0
};

extern cGameModeManager* gpGameMode;                            // 0x016a1344

class cGameUIController {
public:
    virtual void u00(); virtual void u04(); virtual void u08(); virtual void u0c();
    virtual void u10(); virtual void u14(); virtual void u18(); virtual void u1c();
    virtual void u20(); virtual void u24(); virtual void u28(); virtual void u2c();
    virtual void u30(); virtual void u34(); virtual void u38(); virtual void u3c();
    virtual void u40(); virtual void u44(); virtual void u48(); virtual void u4c();
    virtual void u50(); virtual void u54(); virtual void u58();
    virtual void SetModeObject(cEditorModel* pModel);           // 0x05c
};

extern cGameUIController* gpGameUI;                             // 0x016a1484
extern void* gsNewGameFlowLayout;                               // 0x016a0cf8

class cUIEvents {
public:
    virtual void e00(); virtual void e04(); virtual void e08(); virtual void e0c();
    virtual void e10(); virtual void e14(); virtual void e18(); virtual void e1c();
    virtual void e20(); virtual void e24(); virtual void e28(); virtual void e2c();
    virtual void e30(); virtual void e34(); virtual void e38(); virtual void e3c();
    virtual void OnCommand(uint32_t nCommand);                  // 0x040
    virtual void e44(); virtual void e48();
    virtual void OnSelect(Key* pKey, Key* pParam);              // 0x04c
};

cUIEvents* UIEventQueue();                                      // 0x00401010

class cSettings4 {
public:
    uint8_t mPad000[0x1c];                                      // 0x000
    uint8_t mbField1C;                                          // 0x01c
};

cSettings4* GetSetting4();                                      // 0x00401040

struct WString {
    uint16_t* mpBegin;                                          // 0x000
    uint16_t* mpEnd;                                            // 0x004
    uint16_t* mpCap;                                            // 0x008
};

extern uint16_t gEmptyString16[];                               // 0x01667bac

class cSpeciesProfile {
public:
    void GetUiName(WString* pName);                             // 0x004da330
    uint8_t mPad000[0x608];                                     // 0x000
    int32_t mnField608;                                         // 0x608
    int32_t mnField60C;                                         // 0x60c
};

class cSpeciesManager {
public:
    cSpeciesProfile* GetProfile(const Key& rKey);               // 0x004df550
};

cSpeciesManager* GetSetting9(Key* pKey);                        // 0x00401090

class cSomething {
public:
    void DoUpdate();                                            // 0x00b7dec0
};

cSomething* FUN_00b3d360();                                     // 0x00b3d360

class cCommHost {
public:
    void Update();                                              // 0x00ae8510
};

cCommHost* FUN_00b3d490(int32_t nID);                           // 0x00b3d490

int32_t FUN_00dee890(void* pKey);                               // 0x00dee890
void FUN_00804ed0(float* pA, float* pB);                        // 0x00804ed0
void __stdcall FUN_00dee9a0(float fA, float fB);                // 0x00dee9a0
void FUN_00de3d40(Key* pOut, KeyVec* pKeys, Key* pBaseKey);     // 0x00de3d40
void operator_delete_array(void* pMemory);                      // 0x00f47380

// ---------------------------------------------------------------------------
// The new game flow state machine.
// ---------------------------------------------------------------------------
namespace SP {

class cGalaxyGameEntryUIStateMachine {
public:
    void UpdateSummaryCreatureName();                           // 0x00df2080
    void OnAssetBrowserSelection(Key* pKey);                    // 0x00df21d0
    void DoStartNewGame(int32_t nElapsedMs);                    // 0x00df23b0
    void SelectNextState();                                     // 0x00df2550
    void SelectPreviousState();                                 // 0x00df2660
    void OnModeSelection(int32_t nModeID);                      // 0x00df2770
    void OnSummarySelection(int32_t nModeID);                   // 0x00df2920
    void PickRandomByMode(int32_t nPendingAction, uint32_t nFilterValue,
                          Key* pBaseKey);                       // 0x00df2a60
    void PickRandomCreature();                                  // 0x00df2bb0
    void PickRandomBuilding();                                  // 0x00df2d60

    void GetRandomKey(KeyVec* pKeys);                           // 0x00df1e70

    void SetCurrentState(int32_t nState);                       // 0x00df0670
    void SetLayout(void* pLayout);                              // 0x00dedda0
    void UpdateLocks();                                         // 0x00dec570
    void UpdateButtonStdDrawable(int32_t nWindowID, cButtonDrawable* pParam); // 0x00dee770
    void SetStateSummaryText(int32_t nField, uint32_t nKey, uint16_t* pText); // 0x00defd10
    void ToggleAssetLock(int32_t nWindowID);                    // 0x00decfd0
    void UpdateSpecialitySummaryText();                         // 0x00df0190
    void UpdateNavigationControls();                            // 0x00def8c0
    void FillComboBoxes();                                      // 0x00df00b0
    bool FUN_00dec4a0();                                        // 0x00dec4a0
    void FUN_00dee2a0();                                        // 0x00dee2a0
    bool FUN_00ded0b0(Key* pKey);                               // 0x00ded0b0
    void FUN_00ded030();                                        // 0x00ded030
    bool FUN_00deee80(int32_t nState);                          // 0x00deee80

    uint8_t mPad000[0x28];                                      // 0x000
    cSPUILayout mLayout;                                        // 0x028
    int32_t* mpStateListBegin;                                  // 0x05c
    int32_t* mpStateListEnd;                                    // 0x060
    uint8_t mPad064[0x0c];                                      // 0x064
    uint8_t mbField70;                                          // 0x070
    uint8_t mPad071[0x03];                                      // 0x071
    int32_t mnCurrentState;                                     // 0x074
    uint8_t mPad078[0x08];                                      // 0x078
    uint8_t mbField80;                                          // 0x080
    uint8_t mPad081[0x03];                                      // 0x081
    cNewGameModePanel maModePanels[7];                          // 0x084
    uint8_t mPad5C4[0x24];                                      // 0x5c4
    int32_t mnPendingAssetAction;                               // 0x5e8
    uint8_t mPad5EC[0x04];                                      // 0x5ec
    cTimerList mTimer;                                          // 0x5f0
    cUIStateList mStateList;                                    // 0x608
    cEditorModel* mpModel;                                      // 0x628
    uint8_t mPad62C[0x10];                                      // 0x62c
};

} // namespace SP

using SP::cGalaxyGameEntryUIStateMachine;

// ---------------------------------------------------------------------------
// The screen object that owns the state machine.
// ---------------------------------------------------------------------------
class cGalaxyGameEntryScreen {
public:
    void Update(float fDelta);                                  // 0x00df29d0
    uint8_t mPad000[0x08];                                      // 0x000
    cGalaxyGameEntryUIStateMachine* mpStateMachine;             // 0x008
    uint8_t mPad00C[0x04];                                      // 0x00c
    uint8_t mbStartRequested;                                   // 0x010
    uint8_t mPad011[0x03];                                      // 0x011
};

// ---------------------------------------------------------------------------
// 0x00df1e70 - intersect the given key vector with the templates that match
// the currently edited object.
// ---------------------------------------------------------------------------
// @ 0x00df1e70
void cGalaxyGameEntryUIStateMachine::GetRandomKey(KeyVec* pKeys)
{
    KeyVec matches;
    KeyVec filtered;

    matches.mpBegin = nullptr;
    matches.mpEnd = nullptr;
    matches.mpCap = nullptr;
    filtered.mpBegin = nullptr;
    filtered.mpEnd = nullptr;
    filtered.mpCap = nullptr;

    if (mpModel->mnFieldB0 != 0) {
        cObjectTemplateDB* pDatabase = ObjectTemplateDB();
        cMatchConstraint first(0);
        cMatchConstraint second(0x3cc89b1, 0, mpModel->mnFieldB0);

        pDatabase->mpVtbl->mpfnFindMatches(pDatabase, &matches, first, second);

        for (Key* pKey = pKeys->mpBegin; pKey != pKeys->mpEnd; ++pKey) {
            for (Key* pMatch = matches.mpBegin; pMatch != matches.mpEnd; ++pMatch) {
                if (pMatch->mnA == pKey->mnA && pMatch->mnB == pKey->mnB &&
                    pMatch->mnC == pKey->mnC) {
                    if (filtered.mpEnd < filtered.mpCap) {
                        *filtered.mpEnd = *pMatch;
                        ++filtered.mpEnd;
                    } else {
                        filtered.DoInsertKey(filtered.mpEnd, *pMatch);
                    }
                    break;
                }
            }
        }

        if (filtered.mpBegin != filtered.mpEnd)
            *pKeys = filtered;
    }

    if (matches.mpBegin != nullptr)
        operator_delete_array(matches.mpBegin);
    if (filtered.mpBegin != nullptr)
        operator_delete_array(filtered.mpBegin);
}

// ---------------------------------------------------------------------------
// 0x00df2080 - refresh the creature name and the "ready" state of the summary.
// ---------------------------------------------------------------------------
// @ 0x00df2080
void cGalaxyGameEntryUIStateMachine::UpdateSummaryCreatureName()
{
    if (mpModel == nullptr)
        return;

    int32_t nValue = 0;

    if (mpModel->mnFieldA4 == 0) {
        int32_t nKind = FUN_00dee890(&mpModel->mKey4C);
        if (nKind == 0)
            nValue = 2;
        else if (nKind == 1)
            nValue = 1;
    } else {
        Key* pKey = &mpModel->mKey4C;
        cSpeciesProfile* pProfile = GetSetting9(pKey)->GetProfile(*pKey);
        if (pProfile != nullptr) {
            WString name;
            name.mpBegin = gEmptyString16;
            name.mpEnd = gEmptyString16;
            name.mpCap = gEmptyString16 + 1;
            pProfile->GetUiName(&name);
            SetStateSummaryText(8, 0x5b08744, name.mpBegin);

            if (pProfile->mnField60C == 0)
                nValue = 1;
            else if (pProfile->mnField608 == 0)
                nValue = 2;

            uint32_t nBytes = (uint32_t)((uint8_t*)name.mpEnd - (uint8_t*)name.mpBegin);
            nBytes &= 0xfffffffeu;
            if (nBytes > 2 && name.mpBegin != nullptr)
                operator_delete_array(name.mpBegin);
        }
    }

    cUIWindow* pWindow = mLayout.FindWindowByID(0x62f1f94, 1);
    if (pWindow != nullptr)
        pWindow->Show(1, mpModel != nullptr ? 1 : 0);

    pWindow = mLayout.FindWindowByID(0x62d8b12, 1);
    if (pWindow != nullptr) {
        cUIWindow* pChild = pWindow->FindChild(0x106f146);
        if (pChild != nullptr)
            pChild->mPropertyList.SetInt(nValue);
    }
}

// ---------------------------------------------------------------------------
// 0x00df21d0 - the asset browser reported a selection; store it in the editor
// model and refresh the buttons that show it.
// ---------------------------------------------------------------------------
// @ 0x00df21d0
void cGalaxyGameEntryUIStateMachine::OnAssetBrowserSelection(Key* pKey)
{
    if (mpModel == nullptr)
        return;

    cNewGameModePanel* pPanel = &maModePanels[mpModel->mnFieldA4];
    int32_t nWindowID = 0;
    int32_t nDrawableID = 0;

    if (pKey->mnA == 0)
        return;

    if (!FUN_00ded0b0(pKey))
        return;

    if (mnPendingAssetAction == 0x54045ce) {
        mpModel->mKey4C = *pKey;

        cButtonDrawable param;
        param.mKey.mnA = pKey->mnA;
        param.mKey.mnB = 0x2f7d0004;
        param.mKey.mnC = pKey->mnC;
        UpdateButtonStdDrawable(0x65fbfa0, &param);

        nWindowID = pPanel->mnWindowIDA0;
        nDrawableID = 0x5b744bc;
        UpdateSummaryCreatureName();
        FUN_00ded030();
        UpdateLocks();
    } else if (mnPendingAssetAction == 0x54045e3) {
        mpModel->mKey64 = *pKey;

        cButtonDrawable param;
        param.mKey.mnA = 0x5cc02f6;
        param.mKey.mnB = 1;
        param.mKey.mnC = 0;

        nWindowID = pPanel->mnWindowIDA4;
        nDrawableID = 0x5b745cc;
        UpdateLocks();

        UIEventQueue()->OnCommand(0x5cc02f6);
        UIEventQueue()->OnSelect(pKey, &param.mKey);
    } else if (mnPendingAssetAction == 0x5404617) {
        mpModel->mKey70 = *pKey;

        nWindowID = pPanel->mnWindowIDA8;
        nDrawableID = 0x5b73f5b;
        UpdateLocks();
    }

    if (mnPendingAssetAction != 0 && nDrawableID != 0) {
        cButtonDrawable param;
        param.mKey.mnA = pKey->mnA;
        param.mKey.mnB = 0x2f7d0004;
        param.mKey.mnC = pKey->mnC;
        UpdateButtonStdDrawable(nDrawableID, &param);
        mnPendingAssetAction = 0;
    }

    if (nWindowID != 0) {
        cUIWindow* pWindow = mLayout.FindWindowByID(nWindowID, 1);
        pWindow->Show(1, 0);
    }

    UpdateNavigationControls();
}

// ---------------------------------------------------------------------------
// 0x00df23b0 - per frame update of the start-of-game animation.
// ---------------------------------------------------------------------------
// @ 0x00df23b0
void cGalaxyGameEntryUIStateMachine::DoStartNewGame(int32_t nElapsedMs)
{
    if (mbField70 != 0) {
        if (!FUN_00dec4a0())
            return;

        mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
        mLayout.FindWindowByID(0x5812792, 1)->Show(1, 0);
        SetCurrentState(0);
        FUN_00dee2a0();
        gpGameUI->SetModeObject(mpModel);
        mStateList.Reset();
        FUN_00b3d360()->DoUpdate();
        gpGameMode->LoadMode(0xc, 0);
        mpModel = nullptr;
        return;
    }

    float afPair[2];
    FUN_00804ed0(&afPair[0], &afPair[1]);
    FUN_00dee9a0(afPair[1], afPair[0]);

    mStateList.Remove(nElapsedMs);
    FUN_00b3d490(nElapsedMs)->Update();

    if (mnCurrentState != 0xc)
        return;

    if (mTimer.mnTimeLow == 0 && mTimer.mnTimeHigh == 0)
        mTimer.Restart();

    long long nElapsed = mTimer.GetElapsedTime();
    if ((float)(uint64_t)nElapsed * g_fElapsedTimeScale > 1.0f) {
        mTimer.SetBoolProperty();
        if (maModePanels[6].mnField10 == 0) {
            SetCurrentState(1);
            return;
        }
        SetCurrentState(mpStateListBegin[0]);
    }
}

// ---------------------------------------------------------------------------
// 0x00df2550 - advance to the next state that the current mode allows.
// ---------------------------------------------------------------------------
// @ 0x00df2550
void cGalaxyGameEntryUIStateMachine::SelectNextState()
{
    int32_t nCurrent = mnCurrentState;
    uint32_t nIndex = 0;

    if (nCurrent != 1) {
        uint32_t nCount = (uint32_t)(mpStateListEnd - mpStateListBegin);
        while (nIndex < nCount) {
            if (mpStateListBegin[nIndex] == nCurrent)
                break;
            ++nIndex;
        }
        if (nIndex == nCount)
            return;
        ++nIndex;
    }

    uint32_t nCount = (uint32_t)(mpStateListEnd - mpStateListBegin);
    if (nIndex >= nCount)
        return;

    for (;;) {
        if (nIndex >= nCount)
            return;
        if (FUN_00deee80(mpStateListBegin[nIndex]))
            break;
        ++nIndex;
    }

    SetCurrentState(mpStateListBegin[nIndex]);
    mLayout.FindWindowByID(0x5384881, 1)->OnClick();

    cUIWindow* pWindow = mLayout.FindWindowByID(0x5944089, 1);
    if (pWindow == nullptr)
        return;

    if (nIndex == nCount - 1)
        mLayout.FindWindowByID(0x5944089, 1)->Show(1, 0);
    else
        mLayout.FindWindowByID(0x5944089, 1)->Show(1, 1);
}

// ---------------------------------------------------------------------------
// 0x00df2660 - step back to the previous state that the current mode allows.
// ---------------------------------------------------------------------------
// @ 0x00df2660
void cGalaxyGameEntryUIStateMachine::SelectPreviousState()
{
    uint32_t nIndex = 0;

    if ((uint32_t)(mpStateListEnd - mpStateListBegin) != 0) {
        int32_t nCurrent = mnCurrentState;
        int32_t* pState = mpStateListBegin;
        do {
            if (*pState == nCurrent)
                break;
            ++nIndex;
            ++pState;
        } while (nIndex < (uint32_t)(mpStateListEnd - mpStateListBegin));

        if (nIndex != 0 && nCurrent != 2 && nCurrent != 3 &&
            nIndex != (uint32_t)(mpStateListEnd - mpStateListBegin)) {
            int32_t nPrevious = (int32_t)nIndex - 1;
            if (nPrevious < 0)
                return;

            for (;;) {
                if (FUN_00deee80(mpStateListBegin[nPrevious]))
                    break;
                --nPrevious;
                if (nPrevious < 0)
                    return;
            }

            SetCurrentState(mpStateListBegin[nPrevious]);
            mLayout.FindWindowByID(0x5384881, 1)->OnClick();

            if (mLayout.FindWindowByID(0x5944089, 1) == nullptr)
                return;

            mLayout.FindWindowByID(0x5944089, 1)->Show(1, 1);
            return;
        }
        return;
    }

    SetCurrentState(1);
    mLayout.FindWindowByID(0x5384881, 1)->OnClick();
}

// ---------------------------------------------------------------------------
// 0x00df2770 - one of the three mode buttons was pressed.
// ---------------------------------------------------------------------------
// @ 0x00df2770
void cGalaxyGameEntryUIStateMachine::OnModeSelection(int32_t nModeID)
{
    int32_t nOldValue = mpModel->mnField90;
    int32_t anModeIDs[6] = {0x614c680, 0x614c681, 0x614c682, 0, 2, 1};

    for (int32_t i = 0; i < 3; ++i) {
        int32_t nID = anModeIDs[i];
        cUIWindow* pWindow = mLayout.FindWindowByID(nID, 1);
        if (pWindow == nullptr)
            continue;

        cUIWindow* pButton = pWindow->FindChild(0x8ed27e7a);
        if (pButton == nullptr)
            continue;

        if (nID == nModeID) {
            mpModel->mnField90 = anModeIDs[i + 3];
            pButton->SetFlag(4, 1);
        } else {
            pButton->SetFlag(4, 0);
        }
    }

    if (mpModel != nullptr && mpModel->mnFieldA4 != 6 &&
        nOldValue != mpModel->mnField90) {
        mpModel->mKey64.mnA = 0;
        mpModel->mKey64.mnB = 0;
        mpModel->mKey64.mnC = 0;

        cUIWindow* pWindow = mLayout.FindWindowByID(0x5b745cc, 1);
        cUIWindow* pControl = pWindow->GetContent();
        if (pControl != nullptr)
            pControl = pControl->FindChild(0x103c1908);
        pControl->SetParams(0, mStateList.mnField14);

        cNewGameModePanel* pPanel = &maModePanels[mpModel->mnFieldA4];
        mLayout.FindWindowByID(pPanel->mnWindowIDA4, 1)->Show(1, 1);
        mLayout.FindWindowByID(0x5b69a70, 1)->Show(1, 0);

        pWindow = mLayout.FindWindowByID(0x59461b0, 1);
        if (pWindow != nullptr && ((pWindow->GetFlags() >> 2) & 1) != 0)
            ToggleAssetLock(0x59461b0);
    }

    UpdateSpecialitySummaryText();
}

// ---------------------------------------------------------------------------
// 0x00df2920 - one of the three summary buttons was pressed.
// ---------------------------------------------------------------------------
// @ 0x00df2920
void cGalaxyGameEntryUIStateMachine::OnSummarySelection(int32_t nModeID)
{
    uint32_t nOffset = 0;
    int32_t anModeIDs[6] = {0x6149007, 0x6149008, 0x6149009, 0, 1, 2};

    for (; nOffset < 3 * sizeof(int32_t); nOffset += sizeof(int32_t)) {
        int32_t nID = *(const int32_t*)((const uint8_t*)anModeIDs + nOffset);
        cUIWindow* pWindow = mLayout.FindWindowByID(nID, 1);
        if (pWindow == nullptr)
            continue;

        cUIWindow* pButton = pWindow->FindChild(0x8ed27e7a);
        if (pButton == nullptr)
            continue;

        if (nID == nModeID) {
            mpModel->mnFieldA0 =
                *(const int32_t*)((const uint8_t*)anModeIDs + nOffset + 3 * sizeof(int32_t));
            pButton->SetFlag(4, 1);
        } else {
            pButton->SetFlag(4, 0);
        }
    }

    FillComboBoxes();
}

// ---------------------------------------------------------------------------
// 0x00df29d0 - per frame update of the screen that owns the state machine.
// ---------------------------------------------------------------------------
// @ 0x00df29d0
void cGalaxyGameEntryScreen::Update(float fDelta)
{
    if (mpStateMachine != nullptr && mpStateMachine->mbField80 != 0)
        mpStateMachine->SetLayout(gsNewGameFlowLayout);

    if (mbStartRequested) {
        if (GetSetting4()->mbField1C == 0) {
            mbStartRequested = 0;
            gpGameMode->SetGuideState(0);
            gpGameMode->SetGuideState(1);
        }
    }

    long long nMilliseconds = (long long)(fDelta * g_fMillisecondsPerSecond);
    mpStateMachine->DoStartNewGame((int32_t)nMilliseconds);
}

// ---------------------------------------------------------------------------
// 0x00df2a60 - pick a random template for the given filter and report it as an
// asset browser selection.
// ---------------------------------------------------------------------------
// @ 0x00df2a60
void cGalaxyGameEntryUIStateMachine::PickRandomByMode(int32_t nPendingAction,
                                                      uint32_t nFilterValue,
                                                      Key* pBaseKey)
{
    KeyVec keys;
    keys.mpBegin = nullptr;
    keys.mpEnd = nullptr;
    keys.mpCap = nullptr;

    cObjectTemplateDB* pDatabase = ObjectTemplateDB();
    cMatchConstraint first(0);
    cMatchConstraint second(0x2dc9d1e, 0, (int32_t)nFilterValue);

    pDatabase->mpVtbl->mpfnFindMatches(pDatabase, &keys, first, second);

    GetRandomKey(&keys);

    if (keys.mpBegin != keys.mpEnd) {
        Key key;
        FUN_00de3d40(&key, &keys, pBaseKey);
        if (key.mnA != 0) {
            mnPendingAssetAction = nPendingAction;
            OnAssetBrowserSelection(&key);
        }
    }

    if (keys.mpBegin != nullptr)
        operator_delete_array(keys.mpBegin);
}

// ---------------------------------------------------------------------------
// 0x00df2bb0 - pick a random creature for the current mode.
// ---------------------------------------------------------------------------
// @ 0x00df2bb0
void cGalaxyGameEntryUIStateMachine::PickRandomCreature()
{
    cNewGameModePanel* pPanel = &maModePanels[mpModel->mnFieldA4];

    if (pPanel->mpValuesBegin != pPanel->mpValuesEnd) {
        uint32_t nCount = (uint32_t)(pPanel->mpValuesEnd - pPanel->mpValuesBegin);
        uint32_t nIndex = gRandom.RandomUint32Uniform(nCount);

        Key key;
        key.mnA = pPanel->mpValuesBegin[nIndex];
        key.mnB = 0;
        key.mnC = (uint32_t)pPanel->mnFieldAC;
        mnPendingAssetAction = 0x54045ce;
        OnAssetBrowserSelection(&key);
        return;
    }

    if (pPanel->mnComboValue == 0)
        return;

    KeyVec keys;
    keys.mpBegin = nullptr;
    keys.mpEnd = nullptr;
    keys.mpCap = nullptr;

    cObjectTemplateDB* pDatabase = ObjectTemplateDB();
    cMatchConstraint first(0);
    cMatchConstraint second(0x54a32960, 0, 1);
    cMatchConstraint third(0x52def3f, 0, pPanel->mnComboValue);

    pDatabase->mpVtbl->mpfnFindMatches(pDatabase, &keys, first, second, third);

    GetRandomKey(&keys);

    if (keys.mpBegin != keys.mpEnd) {
        Key key;
        FUN_00de3d40(&key, &keys, &mpModel->mKey4C);
        if (key.mnA != 0) {
            mnPendingAssetAction = 0x54045ce;
            OnAssetBrowserSelection(&key);
        }
    }

    if (keys.mpBegin != nullptr)
        operator_delete_array(keys.mpBegin);
}

// ---------------------------------------------------------------------------
// 0x00df2d60 - pick a random building for the current mode.
// ---------------------------------------------------------------------------
// @ 0x00df2d60
void cGalaxyGameEntryUIStateMachine::PickRandomBuilding()
{
    PickRandomByMode(0x5404617, 0x99e92f05, &mpModel->mKey70);
}
