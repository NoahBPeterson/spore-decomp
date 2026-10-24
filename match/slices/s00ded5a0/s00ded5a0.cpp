// Slice s00ded5a0: the galaxy game-entry UI state machine (layout setup, context
// menu, planet preview and the star-pick flow) plus three small mode helpers.
// Layouts follow the binary, not the 2008 PDB.
#include "types.h"

// ---------------------------------------------------------------------------
// callee stubs
// ---------------------------------------------------------------------------
struct IWindow;

struct cString {
    uint32_t mTable;
    uint32_t mKey;
    uint32_t mText;
    cString();                                                       // 0x006b5060
    cString(uint32_t nTable, uint32_t nKey, const wchar_t* pText);   // 0x006b5770
    ~cString();                                                      // 0x006b5240
    bool Load(uint32_t nTable, uint32_t nKey, const wchar_t* pText); // 0x006b54b0
    const wchar_t* GetText() const;                                  // 0x006b55c0
};

struct IWindow {
    virtual void v00();                // 0x000
    virtual void v04();                // 0x004
    virtual void* v08();               // 0x008
    virtual void* v0C(uint32_t nId);   // 0x00c
    virtual void* v10();               // 0x010
    virtual void* v14();               // 0x014
    virtual void* v18();               // 0x018
    virtual void* v1C();               // 0x01c
    virtual void* v20();               // 0x020
    virtual void* v24();               // 0x024
    virtual int32_t v28();             // 0x028
    virtual void* v2C();               // 0x02c
    virtual void* v30();               // 0x030
    virtual void* v34();               // 0x034
    virtual void* v38();               // 0x038
    virtual void* v3C();               // 0x03c
    virtual void* v40();               // 0x040
    virtual void* v44();               // 0x044
    virtual void* v48();               // 0x048
    virtual void* v4C();               // 0x04c
    virtual void* v50();               // 0x050
    virtual void* v54();               // 0x054
    virtual void* v58();               // 0x058
    virtual void* v5C();               // 0x05c
    virtual void* v60();               // 0x060
    virtual void* v64();               // 0x064
    virtual void* v68();               // 0x068
    virtual void* v6C();               // 0x06c
    virtual void* v70();               // 0x070
    virtual void* v74();               // 0x074
    virtual void* v78();               // 0x078
    virtual void v7C(bool bA, bool bB);            // 0x07c
    virtual void v80(const wchar_t* pText);        // 0x080
    virtual void* v84();               // 0x084
    virtual void* v88();               // 0x088
    virtual void* v8C();               // 0x08c
    virtual void* v90();               // 0x090
    virtual void* v94();               // 0x094
    virtual void* v98();               // 0x098
    virtual void* v9C();               // 0x09c
    virtual void* vA0();               // 0x0a0
    virtual void* vA4();               // 0x0a4
    virtual IWindow* vA8();            // 0x0a8
    virtual void* vAC();               // 0x0ac
    virtual void* vB0();               // 0x0b0
    virtual void* vB4();               // 0x0b4
    virtual void* vB8();               // 0x0b8
    virtual void* vBC();               // 0x0bc
    virtual void* vC0();               // 0x0c0
    virtual void* vC4();               // 0x0c4
    virtual void* vC8();               // 0x0c8
    virtual void* vCC();               // 0x0cc
    virtual void* vD0();               // 0x0d0
    virtual void* vD4();               // 0x0d4
    virtual void* vD8();               // 0x0d8
    virtual void* vDC();               // 0x0dc
    virtual void* vE0();               // 0x0e0
    virtual void* vE4();               // 0x0e4
    virtual void* vE8();               // 0x0e8
    virtual void* vEC();               // 0x0ec
    virtual void* vF0();               // 0x0f0
    virtual void* vF4();               // 0x0f4
    virtual void* vF8();               // 0x0f8
    virtual void* vFC();               // 0x0fc
    virtual void* v100();              // 0x100
    virtual void v104(void* pOwner);   // 0x104
};

class cSPUILayout { public:              // sizeof == 0x18
    uint8_t mData[0x18];
    bool Init(const wchar_t* pName, int32_t nFlags, bool bAppend, uint32_t nGroup); // 0x00812160
    IWindow* FindWindowByID(uint32_t nId, bool bRecursive);                         // 0x008105b0
    void Shutdown(uint32_t nFlags);                                                 // 0x00811ad0
};

struct cSPUIPopupMenuWin2 {              // IWindow-derived popup menu
    void Reset();                                                        // 0x0081cce0
    void* AddMenuItem3(uint32_t nKey, uint32_t nFlags, uint32_t nText,
                       bool bSelect);                                    // 0x0081b6a0
    void OnMenuItemSelected(void* pA, void* pB);                         // 0x0081bef0
};

struct cSPUILayeredObject {
    void RemoveAllModels();                                              // 0x0080ea50
    void FUN_0080dda0(IWindow* pWindow, int32_t nFlags);                 // 0x0080dda0
};

struct cPlanetModelView {                // 12-byte view helper at +0x608
    uint8_t mData[0x0c];
    void FUN_00e21260(const void* pKey, const void* pText, void* pModel); // 0x00e21260
    void FUN_00e20d30(float fValue);                                      // 0x00e20d30
    void FUN_00e20e00();                                                  // 0x00e20e00
    void FUN_00e20d60(const void* pArg);                                  // 0x00e20d60
};

struct cGalaxyEditorState {              // what 0x00de4610 returns
    uint8_t mPad00[0xac];
    uint8_t mIsActive;                   // +0xac
};

struct cGalaxyEditorFlow {               // +0x628 member
    uint8_t mPad00[0x4c];
    void* mpField4C;                     // +0x4c
    void* mpField50;                     // +0x50
    uint8_t mPad54[0x10];
    void* mpField64;                     // +0x64
    uint8_t mPad68[8];
    void* mpField70;                     // +0x70
    cGalaxyEditorState* FUN_00de4610(int32_t nIndex);   // 0x00de4610
};

// menu record inside the editor's 0x70-byte item vectors
struct EditorMenuItem {
    uint32_t mField00;                   // +0x00
    uint8_t mPad04[0x14];
    uint32_t mField18;                   // +0x18
    uint8_t mPad1C[0x4c];
    int32_t mKind;                       // +0x68
    uint8_t mPad6C[4];
};

struct EditorMenuSource {                // FUN_0067cb30 result
    uint8_t mPad00[0xb4];
    EditorMenuItem* mpItemsB4;           // +0xb4
    EditorMenuItem* mpItemsB8;           // +0xb8
    uint8_t mPadBC[0x0c];
    EditorMenuItem* mpItemsC8;           // +0xc8
    EditorMenuItem* mpItemsCC;           // +0xcc
};

struct cRefMethodTable {
    uint8_t mPad00[0x170];
    void (__stdcall* mpRelease)(void* pObject, uint32_t nFlags);  // +0x170
};

struct cRefObject {                      // refcounted object (+0x40 count, +0x04 flags)
    void** mpMeta;                       // +0x00  (meta table; [0] -> method table)
    uint32_t mFlags;                     // +0x04
    uint8_t mPad08[0x38];
    int32_t mRefCount;                   // +0x40
};

// ---------------------------------------------------------------------------
// external callees
// ---------------------------------------------------------------------------
void* __cdecl FUN_0067cb30();                                        // 0x0067cb30
void* __cdecl FUN_0080d710(void* pBox);                              // 0x0080d710
void* __fastcall FUN_0080f730(void* pBox);                           // 0x0080f730
void* __fastcall FUN_00bbaa60(void* pObject);                        // 0x00bbaa60
void* __fastcall FUN_00b8d8e0(void* pObject);                        // 0x00b8d8e0
void* __cdecl StarManager();                                         // 0x00b3d2a0
void* __cdecl FUN_00b3d360(const void* pKey);                        // 0x00b3d360
bool  __cdecl FUN_00b7d4f0(void* pHandle);                           // 0x00b7d4f0
void  __cdecl FUN_00b7d440(void* pHandle, void* pA, void* pB);       // 0x00b7d440
bool  __cdecl IsWorldLayoutFlagSet(int32_t nFlag);                   // 0x00685520
int32_t __cdecl GetRecorderState();                                  // 0x00435e90
void  __cdecl KillSetiEffects(uint32_t nId, uint32_t nState);        // 0x00435ed0
IWindow* __cdecl GetSystemAT();                                      // 0x00a206f0
struct DSub {
    int32_t GetField10(int32_t nArg);                                // 0x00830cf0
};
void* __cdecl GlobalBoundingBox();                                   // 0x0067cad0 (no-arg form)
void* __cdecl AddBoundingBoxEx(void* pOwner, int32_t nA, int32_t nB); // 0x0067cad0 (3-arg form)

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
extern uint8_t gEditorMenuSource;            // 0x016a0dd0
extern uint8_t gPlanetPreviewEnabled;        // 0x016a0dc0
extern float gPlanetPreviewBlend;            // 0x016a0d90
extern void* gAppPreferences;                // 0x015fd91c
extern uint32_t gWindowIdTable[11];          // 0x0147e4f0

// the 0x32 window ids SetLayout re-parents, in table order
#define LAYOUT_WINDOW_IDS                                                      \
    0x07d275bb, 0x07d27876, 0x05384d05, 0x05933fe0, 0x05384eec, 0x05384fbb,    \
    0x05385002, 0x053f00c7, 0x053f06e1, 0x053f06ee, 0x053f06f5, 0x053f06fc,    \
    0x053f0707, 0x0684bbe8, 0x05400fa5, 0x054045ce, 0x054045e3, 0x05404617,    \
    0x0588ab05, 0x0595e0a8, 0x05951103, 0x059434c0, 0x06451450, 0x06451451,    \
    0x059434c1, 0x059461b2, 0x059461b1, 0x059461b0, 0x05a725b4, 0x05942cd0,    \
    0x95964773, 0x95964775, 0x95964774, 0x95964779, 0x9596477b, 0x9596477a,    \
    0x95964776, 0x95964778, 0x95964777, 0x06149007, 0x06149008, 0x06149009,    \
    0x0614c680, 0x0614c681, 0x0614c682, 0x06775e1f, 0x06775e20, 0x06775e22,    \
    0x06775e23, 0x06775e21

// ---------------------------------------------------------------------------
// the state machine
// ---------------------------------------------------------------------------
struct cGalaxyGameEntryUIStateMachine {  // PDB candidate: SP::cGalaxyGameEntryUIStateMachine
    void* mpVTable;                         // +0x000
    uint8_t mPad004[0x24];                  // +0x004
    cSPUILayout mLayout;                    // +0x028
    uint8_t mPad040[0x34];                  // +0x040
    int32_t mFlowState;                     // +0x074
    uint8_t mPad078[8];                     // +0x078
    uint8_t mIsLayoutBroken;                // +0x080
    uint8_t mPad081[0x587];                 // +0x081
    cPlanetModelView mPlanetView;           // +0x608
    cSPUILayeredObject* mpLayeredObject;    // +0x614
    IWindow* mpWindow618;                   // +0x618
    IWindow* mpWindow61C;                   // +0x61c
    IWindow* mpWindow620;                   // +0x620
    IWindow* mpWindow624;                   // +0x624
    cGalaxyEditorFlow* mpEditorFlow;        // +0x628

    bool PopulateContextMenu();                                     // 0x00ded5a0
    void ShowPlanetModel();                                         // 0x00ded7d0
    void PickStarForEditorToGameFlow(uint32_t nID, int32_t nMode);  // 0x00ded920
    bool SetLayout(const wchar_t* pLayoutName);                     // 0x00dedda0
    void TearDownUI();                                              // 0x00dee2a0
};

// 12-byte menu text key written inline before every AddMenuItem3 call
struct MenuTextKey {
    uint32_t mTable;
    uint32_t mKey;
    uint32_t mPage;
};

// four text ids staged for the selected star's description window
struct MenuTextIds {
    uint32_t mId0;
    uint32_t mId1;
    uint32_t mId2;
    uint32_t mId3;
};

// ---------------------------------------------------------------------------
// 0x00ded5a0 : rebuild the galaxy-entry popup menu
// ---------------------------------------------------------------------------
// @ 0x00ded5a0
bool cGalaxyGameEntryUIStateMachine::PopulateContextMenu()
{
    IWindow* pWindow = mLayout.FindWindowByID(0x0684bbe8, true);
    if (!pWindow)
        return false;
    cSPUIPopupMenuWin2* pMenu = (cSPUIPopupMenuWin2*)pWindow->v0C(0x04c058d5);
    if (!pMenu)
        return false;

    pMenu->Reset();

    cString title(0x2b7a0311, 0x5b08761, 0);

    MenuTextKey key1 = { 0xa10d844a, 0x510a95b, 0x40464100 };
    void* pFirst = pMenu->AddMenuItem3((uint32_t)&key1, 0, (uint32_t)title.GetText(), false);

    EditorMenuSource* pSource = (EditorMenuSource*)FUN_0067cb30();
    int32_t nItems = (int32_t)(pSource->mpItemsCC - pSource->mpItemsC8);
    if (nItems > 0) {
        for (int32_t i = 0; i < nItems; ++i) {
            EditorMenuItem* pItem = &pSource->mpItemsC8[i];
            MenuTextKey key;
            key.mTable = 0xa10d844a;
            key.mKey = 0x510a95b;
            key.mPage = 0x40464100;
            uint32_t nText = pItem->mKind == 2 ? pItem->mField00 : pItem->mField18;
            pMenu->AddMenuItem3((uint32_t)&key, 0, nText, false);
        }
    }

    pSource = (EditorMenuSource*)FUN_0067cb30();
    nItems = (int32_t)(pSource->mpItemsB8 - pSource->mpItemsB4);
    if (nItems > 0) {
        for (int32_t i = 0; i < nItems; ++i) {
            EditorMenuItem* pItem = &pSource->mpItemsB4[i];
            if (pItem->mKind == 7) {
                cString name;
                name.Load(0x21671745, 0x10002, L"My Creations");
                MenuTextKey key;
                key.mTable = 0xa10d844a;
                key.mKey = 0x510a95b;
                key.mPage = 0x40464100;
                pMenu->AddMenuItem3((uint32_t)&key, 0, (uint32_t)name.GetText(), false);
                name.~cString();
            } else {
                MenuTextKey key;
                key.mTable = 0xa10d844a;
                key.mKey = 0x510a95b;
                key.mPage = 0x40464100;
                pMenu->AddMenuItem3((uint32_t)&key, 0, pItem->mField18, false);
            }
        }
    }

    pMenu->OnMenuItemSelected(0, pFirst);

    void* pBox = AddBoundingBoxEx((uint8_t*)pMenu + 4, 1, 1);
    FUN_0080d710(pBox);

    title.~cString();
    return true;
}

// ---------------------------------------------------------------------------
// 0x00ded7d0 : rebuild the planet preview model
// ---------------------------------------------------------------------------
// @ 0x00ded7d0
void cGalaxyGameEntryUIStateMachine::ShowPlanetModel()
{
    if (!mpEditorFlow->FUN_00de4610(0)->mIsActive)
        return;

    StarManager();

    cGalaxyEditorState* pEditor = mpEditorFlow->FUN_00de4610(0);
    void* pSelection = FUN_00bbaa60(pEditor);
    float* pPosition = (float*)FUN_00b8d8e0(pSelection);

    struct { float mX, mY, mZ; } vSeed = { pPosition[0], pPosition[1], pPosition[2] };
    MenuTextIds ids = { 0, 0, 0, 0 };
    MenuTextIds ids2 = { 0, 0, 0, 0 };

    void* pKey = FUN_00b3d360(&vSeed);
    if (!FUN_00b7d4f0(pKey)) {
        mPlanetView.FUN_00e20e00();
        mPlanetView.FUN_00e20d60(&gEditorMenuSource);
        return;
    }

    void* pHandle = FUN_00b3d360(&vSeed);
    FUN_00b7d440(pHandle, &ids2, &ids);

    if (ids.mId0 != 0) {
        mpLayeredObject->RemoveAllModels();
        if (gPlanetPreviewEnabled) {
            ids.mId0 = 0xcf571b4e;
            ids.mId1 = 0xd94352ed;
            ids.mId2 = 0xcf571b4e;
            ids.mId3 = 0xd94352ed;
        }
        mPlanetView.FUN_00e21260(&ids, &ids.mId2, mpLayeredObject);
        mPlanetView.FUN_00e20d30(gPlanetPreviewBlend);
    }
    mPlanetView.FUN_00e20d60(&gEditorMenuSource);
}

// ---------------------------------------------------------------------------
// 0x00ded920 : star picked in the editor -> game flow
// ---------------------------------------------------------------------------
// @ 0x00ded920
void cGalaxyGameEntryUIStateMachine::PickStarForEditorToGameFlow(uint32_t nID, int32_t nMode)
{
    if (!mpEditorFlow)
        return;

    MenuTextIds ids = { 0, 0, 0, 0x2b7a0311 };
    bool bWorldFlag = IsWorldLayoutFlagSet(2);

    if (!bWorldFlag || nMode != 0) {
        if (nMode != 1)
            return;

        uint32_t nWindowId = 0;
        if (nID < 0x54045cf) {
            switch (nID) {
            case 0x53f06e1: nWindowId = 0x5b218d0; break;
            case 0x53f06ee: nWindowId = 0x5b218c8; break;
            case 0x53f06f5: nWindowId = 0x5adf8e1; break;
            case 0x53f06fc: nWindowId = 0x5adf8e0; break;
            case 0x53f0707: nWindowId = 0x5b218d8; break;
            default: break;
            }
        } else if (nID > 0x54045cf) {
            switch (nID) {
            case 0x54045e4: nWindowId = 0x5b69a70; break;
            case 0x5404618: nWindowId = 0x5b69a72; break;
            default: break;
            }
        }

        if (nWindowId != 0) {
            IWindow* pPage = mLayout.FindWindowByID(nWindowId, true);
            if (pPage)
                pPage->v7C(true, false);
        }
        IWindow* pDescription = mLayout.FindWindowByID(0x5b82168, true);
        if (pDescription)
            pDescription->v7C(true, true);
        return;
    }

    uint32_t nSelectedWindow = 0;

    if (nID < 0x54045cf) {
        if (nID != 0x54045ce) {
            switch (nID) {
            case 0x53f06e1:
                nSelectedWindow = 0x5b218d0;
                ids.mId0 = 0x5b08708;
                ids.mId1 = 0x5b08708;
                ids.mId2 = 0x668e2b7;
                break;
            case 0x53f06ee:
                nSelectedWindow = 0x5b218c8;
                ids.mId0 = 0x5b08709;
                ids.mId1 = 0x65f8fbc;
                ids.mId2 = 0x668e2b8;
                break;
            case 0x53f06f5:
                nSelectedWindow = 0x5adf8e1;
                ids.mId0 = 0x5b08710;
                ids.mId1 = 0x65f8fc5;
                ids.mId2 = 0x668e2b9;
                break;
            case 0x53f06fc:
                nSelectedWindow = 0x5adf8e0;
                ids.mId0 = 0x5b08711;
                ids.mId1 = 0x65f8fd0;
                ids.mId2 = 0x668e2ba;
                break;
            case 0x53f0707:
                nSelectedWindow = 0x5b218d8;
                ids.mId1 = 0x65f8fdb;
                if (IsWorldLayoutFlagSet(2)) {
                    ids.mId0 = 0x7a7b627;
                    ids.mId3 = 0x3dade1bb;
                } else {
                    ids.mId0 = 0x5b08712;
                }
                ids.mId2 = 0x668e2bb;
                break;
            default:
                break;
            }
        } else {
            if (mpEditorFlow->mpField4C) {
                IWindow* pPage = mLayout.FindWindowByID(0x5b69a71, true);
                if (pPage)
                    pPage->v7C(true, true);
            }
            KillSetiEffects(0xd607a5a7, GetRecorderState());
        }
    } else if (nID > 0x5951103) {
        if (nID >= 0x6775e1f && nID <= 0x6775e23)
            KillSetiEffects(0xd607a5a7, GetRecorderState());
    } else if (nID != 0x5951103) {
        if (nID == 0x54045e3) {
            if (mpEditorFlow->mpField64) {
                IWindow* pPage = mLayout.FindWindowByID(0x5b69a70, true);
                if (pPage)
                    pPage->v7C(true, true);
            }
            KillSetiEffects(0xd607a5a7, GetRecorderState());
        } else if (nID == 0x5404617) {
            if (mpEditorFlow->mpField70) {
                IWindow* pPage = mLayout.FindWindowByID(0x5b69a72, true);
                if (pPage)
                    pPage->v7C(true, true);
            }
            KillSetiEffects(0xd607a5a7, GetRecorderState());
        }
    } else if (mFlowState == 0xb) {
        KillSetiEffects(0xd607a5a7, GetRecorderState());
    }

    IWindow* pDescription = mLayout.FindWindowByID(0x5b82168, true);
    if (nSelectedWindow == 0) {
        if (pDescription)
            pDescription->v7C(true, true);
        return;
    }

    IWindow* pAudio = GetSystemAT();
    uint32_t nAudioState = 0;
    if (pAudio)
        nAudioState = (uint32_t)pAudio->v20();
    KillSetiEffects(0xd607a5a7, nAudioState);
    if (pDescription)
        pDescription->v7C(true, false);

    bool bToggled = false;
    IWindow* pSource = mLayout.FindWindowByID(nID, true);
    if (pSource)
        bToggled = ((uint32_t)pSource->v28() >> 1) & 1;

    IWindow* pPage = mLayout.FindWindowByID(nSelectedWindow, true);
    if (pPage)
        pPage->v7C(true, true);

    IWindow* pText = mLayout.FindWindowByID(ids.mId1, true);
    if (pText) {
        uint32_t nTable = bToggled ? ids.mId3 : 0x2b7a0311;
        uint32_t nKey = bToggled ? ids.mId0 : ids.mId2;
        cString text(nTable, nKey, 0);
        pText->v80(text.GetText());
        text.~cString();
    }
}

// ---------------------------------------------------------------------------
// 0x00dedda0 : build the galaxy-entry layout
// ---------------------------------------------------------------------------
// @ 0x00dedda0
bool cGalaxyGameEntryUIStateMachine::SetLayout(const wchar_t* pLayoutName)
{
    mLayout.Shutdown(1);
    if (!pLayoutName)
        return false;

    bool bInit = mLayout.Init(pLayoutName, 1, true, 0x5b598fa);
    mIsLayoutBroken = bInit ? 0 : 1;

    const uint32_t nWindowIds[0x32] = { LAYOUT_WINDOW_IDS };
    for (int32_t i = 0; i < 0x32; ++i) {
        IWindow* pWindow = mLayout.FindWindowByID(nWindowIds[i], true);
        if (pWindow)
            pWindow->v104(this);
    }

    IWindow* pPreview = mLayout.FindWindowByID(0x5812792, true);
    if (pPreview)
        pPreview->v7C(true, false);

    cSPUILayeredObject* pLayer =
        (cSPUILayeredObject*)FUN_0080f730(GlobalBoundingBox());
    if (pLayer != mpLayeredObject) {
        if (pLayer)
            ((IWindow*)pLayer)->v04();
        cSPUILayeredObject* pOld = mpLayeredObject;
        mpLayeredObject = pLayer;
        if (pOld)
            ((IWindow*)pOld)->v08();
    }

    pPreview = mLayout.FindWindowByID(0x5812792, true);
    if (pPreview)
        mpLayeredObject->FUN_0080dda0(pPreview, 1);

    PopulateContextMenu();

    IWindow* pRoot = mLayout.FindWindowByID(0x5b744bc, true);
    if (pRoot) {
        IWindow* pA = pRoot->vA8();
        IWindow* pB = 0;
        if (pA)
            pB = (IWindow*)pA->v0C(0x103c1908);
        IWindow* pNew = 0;
        if (pB)
            pNew = (IWindow*)pB->v10();
        if (pNew != mpWindow618) {
            if (pNew)
                pNew->v00();
            IWindow* pOld = mpWindow618;
            mpWindow618 = pNew;
            if (pOld)
                pOld->v04();
        }
    }

    pRoot = mLayout.FindWindowByID(0x5b73f5b, true);
    if (pRoot) {
        IWindow* pA = pRoot->vA8();
        IWindow* pB = 0;
        if (pA)
            pB = (IWindow*)pA->v0C(0x103c1908);
        IWindow* pNew = 0;
        if (pB)
            pNew = (IWindow*)pB->v10();
        if (pNew != mpWindow620) {
            if (pNew)
                pNew->v00();
            IWindow* pOld = mpWindow620;
            mpWindow620 = pNew;
            if (pOld)
                pOld->v04();
        }
    }

    pRoot = mLayout.FindWindowByID(0x5b745cc, true);
    if (pRoot) {
        IWindow* pA = pRoot->vA8();
        IWindow* pB = 0;
        if (pA)
            pB = (IWindow*)pA->v0C(0x103c1908);
        IWindow* pNew = 0;
        if (pB)
            pNew = (IWindow*)pB->v10();
        if (pNew != mpWindow61C) {
            if (pNew)
                pNew->v00();
            IWindow* pOld = mpWindow61C;
            mpWindow61C = pNew;
            if (pOld)
                pOld->v04();
        }
    }

    pRoot = mLayout.FindWindowByID(0x57f74f6, true);
    if (pRoot) {
        IWindow* pA = pRoot->vA8();
        IWindow* pB = 0;
        if (pA)
            pB = (IWindow*)pA->v0C(0x53eb526);
        int32_t nNew = 0;
        if (pB)
            nNew = ((DSub*)pB)->GetField10(0);
        if ((IWindow*)nNew != mpWindow624) {
            if (nNew)
                ((IWindow*)nNew)->v00();
            IWindow* pOld = mpWindow624;
            mpWindow624 = (IWindow*)nNew;
            if (pOld)
                pOld->v04();
        }
    }

    for (int32_t i = 0; i < 0x0b; ++i) {
        IWindow* pWindow = mLayout.FindWindowByID(gWindowIdTable[i], true);
        if (pWindow)
            pWindow->v7C(true, false);
    }

    return bInit;
}

// ---------------------------------------------------------------------------
// 0x00dee2a0 : release the owned windows and shut the layout down
// ---------------------------------------------------------------------------
// @ 0x00dee2a0
void cGalaxyGameEntryUIStateMachine::TearDownUI()
{
    if (IWindow* pWindow = mpWindow618) {
        mpWindow618 = 0;
        pWindow->v04();
    }
    if (IWindow* pWindow = mpWindow61C) {
        mpWindow61C = 0;
        pWindow->v04();
    }
    if (IWindow* pWindow = mpWindow620) {
        mpWindow620 = 0;
        pWindow->v04();
    }
    if (IWindow* pWindow = mpWindow624) {
        mpWindow624 = 0;
        pWindow->v04();
    }

    mIsLayoutBroken = 1;
    mLayout.Shutdown(1);
}

// ---------------------------------------------------------------------------
// 0x00dee320 : construct the global notify-attack listener
// ---------------------------------------------------------------------------
struct cNotifyAttackListener {
    void* mpVTable;                      // +0x00 (0x0147e618)
    uint32_t mField04;                   // +0x04
    uint32_t mField08;                   // +0x08
    uint32_t mField0C;                   // +0x0c
    uint8_t mField10;                    // +0x10
    uint8_t mPad11[3];                   // +0x11
    uint32_t mField14;                   // +0x14
    cNotifyAttackListener();             // 0x00dee320
};

extern cNotifyAttackListener* gNotifyListener;   // 0x016a1570
void __fastcall FUN_00e00630(cNotifyAttackListener* pThis);   // 0x00e00630

// @ 0x00dee320
cNotifyAttackListener::cNotifyAttackListener()
{
    FUN_00e00630(this);
    *(void* volatile*)&mpVTable = (void*)0x147e618;
    *(uint32_t volatile*)&mField14 = 0;
    *(uint32_t volatile*)&mField08 = 0;
    *(cNotifyAttackListener* volatile*)&gNotifyListener = this;
    *(uint32_t volatile*)&mField0C = 0;
    *(uint8_t volatile*)&mField10 = 0;
}

// ---------------------------------------------------------------------------
// 0x00dee360 : refresh the "notify attack" toggle from the preferences
// ---------------------------------------------------------------------------
struct cProperty {
    uint8_t mPad00[0x12];
    uint16_t mType;                      // +0x12
    uint8_t* GetBool();                  // 0x0041e920
};

struct cPropertyList {
    virtual bool v00(); virtual bool v04(); virtual bool v08(); virtual bool v0C();
    virtual bool v10(); virtual bool v14(); virtual bool v18(); virtual bool v1C();
    virtual bool v20();
    virtual bool FindProperty(uint32_t nId, cProperty** ppOut);  // 0x24
};

struct cGalaxyGameEntryMode {
    cRefObject* mpObject00;                             // +0x00
    cRefObject* mpObject04;                             // +0x04
    cGalaxyGameEntryUIStateMachine* mpStateMachine;     // +0x08
    void RefreshNotifyAttackToggle();                   // 0x00dee360
    void ReleaseOwned();                                // 0x00dee3d0
};

// @ 0x00dee360
void cGalaxyGameEntryMode::RefreshNotifyAttackToggle()
{
    char cValue = 0;
    cPropertyList* pPreferences = (cPropertyList*)gAppPreferences;
    if (pPreferences) {
        cProperty* pProperty;
        if (pPreferences->FindProperty(0x80eaa93, &pProperty) && pProperty->mType == 1)
            cValue = *pProperty->GetBool();
    }

    IWindow* pCheck = mpStateMachine->mLayout.FindWindowByID(0x809b720, true);
    if (pCheck)
        pCheck->v7C(true, cValue == 0);
}

// ---------------------------------------------------------------------------
// 0x00dee3d0 : release the refcounted objects the mode holds
// ---------------------------------------------------------------------------
static void ReleaseRef(cRefObject* pObject)
{
    if (!pObject)
        return;
    uint32_t nFlags = pObject->mFlags >> 31;
    if (pObject->mRefCount > 1) {
        --pObject->mRefCount;
        return;
    }
    cRefMethodTable* pTable = *(cRefMethodTable**)pObject->mpMeta;
    pTable->mpRelease(pObject, nFlags & 1);
}

// @ 0x00dee3d0
void cGalaxyGameEntryMode::ReleaseOwned()
{
    IWindow* pStateMachine = (IWindow*)mpStateMachine;
    if (pStateMachine)
        pStateMachine->v08();
    ReleaseRef(mpObject04);
    ReleaseRef(mpObject00);
}
