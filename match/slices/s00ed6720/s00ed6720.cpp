// Slice s00ed6720 -- SP::cSPUIBadges panel: activation, deactivation, the
// toolbar/message dispatcher, the badge achievement auto-test and the
// scenario-node selection hook.
//
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// Every method here takes the primary panel object in ecx.  FUN_00ed6bf0 is the
// exception: it is a method of the toolbar-handler sub-object at panel+8 and
// reaches the panel through `this - 8`.  The call sites in the original use
// `mov ecx,<receiver> / push args / call`, so the methods are declared as
// member functions and invoked directly -- that reproduces the `ecx` convention
// without __thiscall on a free function (which this compiler rejects, C3865).
#include "types.h"

// ---------------------------------------------------------------- data types
struct Key12 {                       // resource key: instance/type/group
    uint32_t a, b, c;
};

extern Key12 g_15ac184;              // 0x015ac184: last badge callout key

// ---------------------------------------------------------------- UTFWin pieces
struct IWindow {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual void w4(); virtual void w5(); virtual void w6();
    virtual uint32_t GetControlID();                 // +0x1c
    virtual void w8();  virtual void w9();  virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15();
    virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
    virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27();
    virtual void w28(); virtual void w29(); virtual void w30();
    virtual void SetVisible(bool visible, bool b);   // +0x7c
};

// ---------------------------------------------------------------- external objects
struct cAudioSystem {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual int  GetState();                         // +0x20
};
cAudioSystem* __cdecl GetSystemAT();                 // 0x00a206f0

struct cMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void AddHandler(void* target, void* handler);   // +0x14
};
cMessageServer* __cdecl MessageServer();             // 0x0067dcc0

// ---------------------------------------------------------------- the sim
struct cSim {
    void   f45970();                                 // 0x00f45970
    void   f45a80();                                 // 0x00f45a80
    void   f427c0();                                 // 0x00f427c0
    void   f3bce0(int id, const void* key);          // 0x00f3bce0
    void   f40ae0(const void* key);                  // 0x00f40ae0 ScenarioNode_AppendToWorld
    void   f3e810(int id);                           // 0x00f3e810
    int    f3bf60();                                 // 0x00f3bf60
    void   f3bcc0(int n);                            // 0x00f3bcc0
    bool   f327f0();                                 // 0x00f327f0
    bool   f41270(int a);                            // 0x00f41270
    char   pad10[0x10];
    void*  f10;                                      // +0x10
};
void __fastcall sim_f3d8c0(cSim* self);              // 0x00f3d8c0

struct cGlobals {
    char  pad0[0x18];
    void* f18;                                       // +0x18
    char  pad1[0x74 - 0x1c];
    cSim* sim;                                       // +0x74
    char  pad2[0xd4 - 0x78];
    void* d4;                                        // +0xd4
};
extern cGlobals* g_16c7aa4;                          // 0x016c7aa4

// ---------------------------------------------------------------- UI helpers
// The scenario-global options object at panel+0x44 (cSPUIGlobalOptions); its
// methods are called with ecx = that object.
struct cGlobalOptions {
    void  CreateDialog();                            // 0x00e02430
    void* GetAccessFlags();                          // 0x00ff0420
    void  Enable(int a);                             // 0x00e018c0
};
// cEditorPage-like page object embedded/pointed to from Panel; its methods are
// called with ecx = the page.
struct cInventory { void ToggleExpanded(); };        // 0x005cb380
struct cMenu {
    cInventory* GetExpandedItem();                   // item at [+0x20]
    void        OnClick2();                          // 0x00e02e80
};
struct cPage {
    void         AsInterface(int a);                 // 0x00ed0260
    void         SetActive(int a);                   // 0x00ed1fe0
    void         SetActiveB(int a);                  // 0x00ee3e40
    void         Vis(int a);                         // 0x00ef8550
    void         Hook(int a);                        // 0x00ed5890
    cInventory*  GetPlayerInventory();               // 0x00a1ad60
};
struct cSPUILayout {
    bool     SetVisibility(bool visible);            // 0x00810590
    bool     IsVisible();                            // 0x00810070
    IWindow* FindWindowByID(uint32_t id, bool b);    // 0x008105b0
};

void __cdecl UI_CalloutMessageBox(void* where, const Key12* key);   // 0x00809db0
void* __cdecl GetUITextManager();                    // 0x00957f30
void __cdecl HelpersRemoveWindowCallback(void* p);   // 0x00807590
void __cdecl FUN_00e02430();                         // 0x00e02430
bool __cdecl FUN_00e00ac0();                         // 0x00e00ac0
void __cdecl FUN_00e02e10();                         // 0x00e02e10
void __cdecl FUN_00e21960();                         // 0x00e21960
void __cdecl FUN_00e09600();                         // 0x00e09600
void __cdecl FUN_00e097c0();                         // 0x00e097c0
int  __cdecl FUN_00ed4970();                         // 0x00ed4970 (window callback)
void* __cdecl FUN_00a1ad60(void* self);              // 0x00a1ad60 GetPlayerInventory
void __cdecl FUN_005cb380(void* p);                  // 0x005cb380 ToggleExpanded
void* __cdecl SetupTimers(void* p, int a);           // 0x008085d0
void* __cdecl FUN_00ef13b0(int a);                   // 0x00ef13b0
void __cdecl PlayUISound(uint32_t id, int state);    // 0x00435ed0
void __cdecl cUIBanningContent_Init();               // 0x00dd12f0
void __cdecl cUIBanningContent_Shutdown();           // 0x00dd14b0
void __cdecl EA_Messaging_RemoveHandler(void* a, void* b, void* c, int d, int e); // 0x00571db0
int* __cdecl XHTML_Node_Parent(void* node);          // 0x00ff0420

struct cAchievements { void AutoTest(uint32_t id, int count); };   // 0x00676e90
cAchievements* __stdcall AchievementsController(uint32_t id, int count);  // 0x00675250

// ---------------------------------------------------------------- the panel
struct Panel;

struct PanelBase {                                   // sub-object at Panel+0x10
    virtual void b0();                               // +0x00
    virtual bool DoBadgeMessage(int key, void* data, int unused);   // +0x04
    Panel* panel() { return (Panel*)((char*)this - 0x10); }
};

struct Panel {                                       // primary object (cSPUIBadges)
    void*        vtable;                             // +0x00
    void*        mGame;                              // +0x04
    char         pad8[0xc - 8];
    int          mMode0c;                            // +0x0c
    void*        mGap10;                             // +0x10
    cPage*       mPage14;                            // +0x14
    cPage*       mPage18;                            // +0x18
    cSPUILayout* mSet1c;                             // +0x1c (layout; also used as an
                                                     //       int selection sentinel)
                                                     //       and as the DoBadgeMessage
                                                     //       message-mode int
    int          mSel20;                             // +0x20
    cSPUILayout* mLayout;                            // +0x24
    cMenu*       mMenu;                              // +0x28
    void*        mGap2c;                             // +0x2c
    cPage*       mPage30;                            // +0x30
    cPage*       mPage34;                            // +0x34
    cPage*       mPage38;                            // +0x38
    cPage*       mPage3c;                            // +0x3c
    void*        mList40;                            // +0x40
    cGlobalOptions* mOptions44;                      // +0x44
    int          mState48;                           // +0x48
    Key12        mKey4c;                             // +0x4c
    int          mMode;                              // +0x58
    void*        mMsgServer;                         // +0x5c
    void*        mMsgTarget;                         // +0x60
    void*        mMsgHandler;                        // +0x64
    int          mMode68;                            // +0x68 (DoBadgeMessage msg mode)
    int          mMsgFlags;                          // +0x6c
    void*        mGap70;                             // +0x70
    char         pad74[0x84 - 0x74];
    void*        mOwned84;                           // +0x84
    char         pad88[0x94 - 0x88];
    char         mReady94;                           // +0x94

    void Rebuild(int which);                         // 0x00ed6720
    void Activate2();                                // 0x00ed6a10
    void Deactivate2();                              // 0x00ed6b00
    void BadgeAutoTest();                            // 0x00ed7060
    void SelectionChanged(int a);                    // 0x00ed7490
    void Refresh();                                  // 0x00ed5640
    void ShowCallout();                              // 0x00ed5910
    void SetMode(int key);                           // 0x00ed5330
    void Select(int a);                              // 0x00ed4c70
    void UpdateModes();                              // 0x00ed63a0
    void SyncState();                                // 0x00ed5d70
    void DropSelection();                            // 0x00ed4b70
    int  GetKey();                                   // 0x00ed4e30
};

extern void* g_BadgeMessageList[10];                 // 0x01489fa0
int  __cdecl Panel_Find(void* p);                    // 0x00ed4f50
int  __cdecl Panel_Match(uint32_t a, uint32_t b, uint32_t c);   // 0x00ed5580
int* __cdecl FUN_00ed29b0(void* begin, void* end, void* key, char c);   // 0x00ed29b0
int  __cdecl FUN_00552300(void* p);                  // 0x00552300
bool __cdecl AssetDataList(uint32_t id, int flags);  // 0x004bbe20 SetAssetData

// ===========================================================================
// 0x00ed6720 -- Panel::Rebuild(which)
// ===========================================================================
// @ 0x00ed6720
void Panel::Rebuild(int which)
{
    IWindow* w = mLayout->FindWindowByID(0x7105378, true);
    if (w)
        w->SetVisible(true, false);

    mPage30->AsInterface(0);
    mPage34->AsInterface(0);
    mPage3c->Vis(0);
    mPage38->Vis(0);
    (*(void(__thiscall**)(void*, int))(*(uint32_t**)mList40)[0x30])(mList40, 0);
    mPage14->SetActive(0);
    mPage18->SetActiveB(0);
    (*(void(__thiscall**)(void*, int))(*(uint32_t**)mMenu)[6])(mMenu, 0);

    IWindow* piVar1 = 0;
    IWindow* piVar2 = 0;
    IWindow* piVar3 = 0;
    int uVar4 = 0;

    if (which != -1) {
        cAudioSystem* at = GetSystemAT();
        if (at != 0)
            at->GetState();
        PlayUISound(0x8c35f293, 0);
    }

    if (which == 0) {
        mPage14->SetActive(1);
        mPage18->SetActiveB(1);
        (*(void(__thiscall**)(void*, int))(*(uint32_t**)mList40)[0x30])(mList40, 1);
        mPage30->AsInterface(1);
        mPage3c->Vis(1);
        mPage3c->Hook(0);

        piVar1 = mLayout->FindWindowByID(0x7104132, true);
        if (piVar1 == 0)
            piVar2 = 0;
        else {
            (*(void(__thiscall**)(void*))(*(uint32_t**)piVar1)[0])(piVar1);
            piVar2 = (IWindow*)(*(void*(__thiscall**)(void*, uint32_t))(*(uint32_t**)piVar1)[3])(piVar1, 0x8ed27e7a);
        }
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar2)[10])(piVar2, 4, 0);
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar2)[10])(piVar2, 0x20, 0);
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar2)[10])(piVar2, 1, 1);

        piVar2 = mLayout->FindWindowByID(0x7104130, true);
        if (piVar2 == 0)
            piVar3 = 0;
        else {
            (*(void(__thiscall**)(void*))(*(uint32_t**)piVar2)[0])(piVar2);
            piVar3 = (IWindow*)(*(void*(__thiscall**)(void*, uint32_t))(*(uint32_t**)piVar2)[3])(piVar2, 0x8ed27e7a);
        }
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar3)[10])(piVar3, 4, 1);
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar3)[10])(piVar3, 0x20, 1);
        uVar4 = 0;
    }
    else if (which == 1) {
        FUN_00ef13b0(1);
        mSel20 = (int)mSet1c;
        mPage3c->Hook(1);
        return;
    }
    else if (which == 2) {
        piVar1 = mLayout->FindWindowByID(0x7105378, true);
        if (piVar1 != 0)
            (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar1)[0x1f])(piVar1, 1, 1);
        (*(void(__thiscall**)(void*, int))(*(uint32_t**)mMenu)[6])(mMenu, 1);
        mPage30->AsInterface(1);
        mPage3c->Vis(1);
        mPage3c->Hook(2);

        piVar1 = mLayout->FindWindowByID(0x7104132, true);
        if (piVar1 == 0)
            piVar2 = 0;
        else {
            (*(void(__thiscall**)(void*))(*(uint32_t**)piVar1)[0])(piVar1);
            piVar2 = (IWindow*)(*(void*(__thiscall**)(void*, uint32_t))(*(uint32_t**)piVar1)[3])(piVar1, 0x8ed27e7a);
        }
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar2)[10])(piVar2, 4, 1);
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar2)[10])(piVar2, 0x20, 1);
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar2)[10])(piVar2, 1, 0);

        piVar2 = mLayout->FindWindowByID(0x7104130, true);
        if (piVar2 == 0)
            piVar3 = 0;
        else {
            (*(void(__thiscall**)(void*))(*(uint32_t**)piVar2)[0])(piVar2);
            piVar3 = (IWindow*)(*(void*(__thiscall**)(void*, uint32_t))(*(uint32_t**)piVar2)[3])(piVar2, 0x8ed27e7a);
        }
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar3)[10])(piVar3, 4, 0);
        (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar3)[10])(piVar3, 0x20, 0);
        uVar4 = 1;
    }
    else {
        return;
    }

    (*(void(__thiscall**)(void*, int, int))(*(uint32_t**)piVar3)[10])(piVar3, 1, uVar4);
    if (piVar2 != 0)
        (*(void(__thiscall**)(void*))(*(uint32_t**)piVar2)[1])(piVar2);
    if (piVar1 != 0)
        (*(void(__thiscall**)(void*))(*(uint32_t**)piVar1)[1])(piVar1);
}

// ===========================================================================
// 0x00ed6a10 -- Panel::Activate2()
// ===========================================================================
// @ 0x00ed6a10
void Panel::Activate2()
{
    cUIBanningContent_Init();
    FUN_00e09600();

    if (mLayout)
        mLayout->SetVisibility(true);

    int sel = mSel20;
    mReady94 = 1;
    if (sel == -1)
        sel = (int)mSet1c;
    else {
        mSel20 = -1;
        sel = mSel20;      // dead store, kept for shape
    }

    Rebuild(sel);

    mOptions44->CreateDialog();
    void* parent = mOptions44->GetAccessFlags();
    (*(void(__thiscall**)(void*, void*))(*(uint32_t**)parent)[0x41])(parent, (char*)this + 8);

    Refresh();

    void* target = (char*)this + 0x10;
    cMessageServer* server = MessageServer();
    mMsgServer  = server;
    mMsgTarget  = target;
    mMsgHandler = (void*)0x01489fa0;
    mMode68     = 10;
    mMsgFlags   = 0;

    if (server && target) {
        for (int i = 0; i < 0x28; i += 4) {
            void* h = *(void**)((char*)0x01489fa0 + i);
            (*(void(__thiscall**)(void*, void*, void*))(*(uint32_t**)server)[9])(server, target, h);
        }
    }

    void* mgr = GetUITextManager();
    void* h = (*(void*(__thiscall**)(void*, void*, int, int, int))(*(uint32_t**)mgr)[1])(
                  mgr, &FUN_00ed4970, 0x40, 0, 0);
    SetupTimers(h, 0);
}

// ===========================================================================
// 0x00ed6b00 -- Panel::Deactivate2()
// ===========================================================================
// @ 0x00ed6b00
void Panel::Deactivate2()
{
    void* mgr = GetUITextManager();
    void* h = (*(void*(__thiscall**)(void*, int(*)(), int, int, int))(*(uint32_t**)mgr)[1])(
                  mgr, FUN_00ed4970, 0, 0, 0);
    HelpersRemoveWindowCallback(h);

    if (mMsgServer) {
        void* srv = mMsgServer;
        mMsgServer = 0;
        EA_Messaging_RemoveHandler(srv, mMsgTarget, mMsgHandler, mMode68, mMsgFlags);
    }

    if (mLayout)
        mLayout->SetVisibility(false);

    mReady94 = 0;
    FUN_00e02e10();

    IWindow* w = mLayout->FindWindowByID(0x7105378, true);
    if (w)
        w->SetVisible(true, false);

    mPage30->AsInterface(0);
    mPage34->AsInterface(0);
    mPage3c->Vis(0);
    mPage38->Vis(0);
    (*(void(__thiscall**)(void*, int))(*(uint32_t**)mList40)[0x30])(mList40, 0);
    mPage14->SetActive(0);
    mPage18->SetActiveB(0);
    (*(void(__thiscall**)(void*, int))(*(uint32_t**)mMenu)[6])(mMenu, 0);
    FUN_00e21960();
    cUIBanningContent_Shutdown();
    FUN_00e097c0();
}

// ===========================================================================
// 0x00ed6bf0 -- PanelBase::DoBadgeMessage(key, data, unused)
// ===========================================================================
// @ 0x00ed6bf0
bool PanelBase::DoBadgeMessage(int key, void* data, int unused)
{
    Panel* p = panel();
    (void)unused;
    char* pb = (char*)data;

    if (key == 0x30c11c7) {
        int* r = (int*)Panel_Find(pb + 0x10);
        if (r == 0 || pb[0x44] != 0)
            return false;
        int id = r[2];
        void* args = pb + 0x18;
        g_16c7aa4->sim->f45970();
        if (id == -1)
            g_16c7aa4->sim->f40ae0(args);
        else
            g_16c7aa4->sim->f3bce0(id, args);
        g_16c7aa4->sim->f45a80();
        p->Refresh();
        g_16c7aa4->sim->f427c0();
        return false;
    }

    if (key == 0x462c656) {
        if (p->GetKey() != 0x7eaf739) {
            switch (p->mMode68) {
            case 1: case 3: case 4: case 6: case 7:
                p->DropSelection();
                break;
            default:
                break;
            }
        }
        return false;
    }

    if (key == 0x6202731 || key == 0x5d1536c) {
        if (FUN_00e00ac0())
            p->mOptions44->Enable(1);
        return false;
    }

    if (key == 0x65ff54a) {
        if (*(uint32_t*)(pb + 0x10) != 0x40464100)
            return false;
        uint32_t v = *(uint32_t*)(pb + 0x18);
        if (v != 0x396f69f5 && v != 0x709cbc09)
            return false;
        bool vis = false;
        if (p->mLayout != 0 && p->mLayout->IsVisible()) {
            vis = true;
            p->Deactivate2();
        }
        p->UpdateModes();
        p->SyncState();
        if (vis)
            p->Activate2();
        return false;
    }

    if (key == 0x72bdb11) {
        p->Refresh();
        return false;
    }

    if (key == 0x774e2dc) {
        int id  = *(int*)(pb + 8);
        uint32_t w0 = *(uint32_t*)(pb + 0x10);
        uint32_t w1 = *(uint32_t*)(pb + 0x18);
        uint32_t w2 = *(uint32_t*)(pb + 0x20);
        uint32_t args[3];
        g_16c7aa4->sim->f45970();
        args[0] = w0; args[1] = w1; args[2] = w2;
        if (id == -1)
            g_16c7aa4->sim->f40ae0(args);
        else
            g_16c7aa4->sim->f3bce0(id, args);
        g_16c7aa4->sim->f45a80();
        p->Refresh();
        g_16c7aa4->sim->f427c0();
        return false;
    }

    if (key == 0x7d8af04) {
        int v = (int)p->mSet1c;
        if (v == 0) {
            p->mPage14->GetPlayerInventory()->ToggleExpanded();
            return false;
        }
        if (v - 2 == 0) {
            p->mMenu->GetExpandedItem()->ToggleExpanded();
            return false;
        }
        return false;
    }

    if (key == 0x7ec5866) {
        if (*(int*)(pb + 8) != 0)
            return false;
        p->Select(1);
        if (FUN_00e00ac0())
            p->mMenu->OnClick2();
        if (p->mOwned84 != 0) {
            void* o = p->mOwned84;
            p->mOwned84 = 0;
            (*(void(__thiscall**)(void*))(*(uint32_t**)o)[1])(o);
        }
        return false;
    }

    if (key == 0x14051500) {
        int* r = (int*)*(void**)(pb + 8);
        g_16c7aa4->sim->f45970();
        if (r[2] == -1) {
            int n = g_16c7aa4->sim->f3bf60();
            g_16c7aa4->sim->f3bcc0(n - 1);
        }
        else {
            g_16c7aa4->sim->f3e810(r[2]);
        }
        g_16c7aa4->sim->f45a80();
        p->Refresh();
        g_16c7aa4->sim->f427c0();
        cAudioSystem* at = GetSystemAT();
        int state = at ? at->GetState() : 0;
        PlayUISound(0xf89e056, state);
        return false;
    }

    if (key == 0xcc0bf723) {
        if (p->mMode == 4 && data != 0) {
            int v = *(int*)data;
            if (v == 1 || v == 3) {
                p->mMode = 0;
            }
            else if (v == 2) {
                p->SetMode(0x7eaf738);
            }
        }
        return false;
    }

    if (key == 0xfd7a08d0) {
        p->Select(1);
        if (p->mMode == 3) {
            p->ShowCallout();
            return false;
        }
        void* where = (p != 0) ? (char*)p + 4 : 0;
        UI_CalloutMessageBox(where, &g_15ac184);
        p->mKey4c.a = g_15ac184.a;
        return false;
    }

    return false;
}

// ===========================================================================
// 0x00ed7060 -- Panel::BadgeAutoTest()
// ===========================================================================
// @ 0x00ed7060
void Panel::BadgeAutoTest()
{
    cAchievements* c;
    c = AchievementsController(0x48cdfa34, 1); c->AutoTest(0x48cdfa34, 1);
    c = AchievementsController(0xabc8af1a, 1); c->AutoTest(0xabc8af1a, 1);
    c = AchievementsController(0xec310ad9, 1); c->AutoTest(0xec310ad9, 1);

    uint32_t* pi = *(uint32_t**)((char*)g_16c7aa4->sim + 0x10);
    if (pi != 0)
        (*(void(__thiscall**)(uint32_t*))(*(uint32_t**)pi)[0])(pi);

    int local_24 = 0;    // count of 0x2b978c46
    int local_c  = 0;    // count of 0x9ea3031a
    int local_1c = 0;    // count of 0x372e2c04
    int local_14 = 0;    // count of 0xccc35c46
    int local_10 = 0;    // count of 0x65672ade
    int local_28 = 0;    // count of 0x24682294
    int local_20 = 0;    // count of 0x2399be55
    bool bVar5 = true;
    bool bVar6 = true;
    bool bVar7 = true;

    uint32_t* puVar10;
    if (pi[0x2c24 / 4] < 0x3fffffff)
        puVar10 = (uint32_t*)(pi[0x2c24 / 4] * 0x238 + pi[0x2c10 / 4]);
    else
        puVar10 = (uint32_t*)pi[0x2c14 / 4];
    uint32_t* puVar2 = (uint32_t*)pi[0x2c14 / 4];

    if (puVar2 != puVar10) {
        int* iVar13  = (int*)pi[0x2bf4 / 4];
        int* piVar14 = (int*)pi[0x2bf8 / 4];
        do {
            int* piVar11 = (int*)FUN_00ed29b0(iVar13, piVar14, puVar10 + 1,
                                              (char)pi[0x2c08 / 4]);
            if (piVar11 != piVar14 && *piVar11 <= (int)puVar10[1] &&
                piVar11 != piVar11 + 0x9fa) {
                int iVar12 = piVar11[8];
                int iVar3  = piVar11[3];
                if (iVar3 == 0x2399be55) {
                    local_20++;
                }
                else if (iVar3 == 0x24682294) {
                    local_28++;
                }
                else if (iVar3 == 0x2b978c46) {
                    local_24++;
                    if (iVar12 == (int)0x9ea3031a)
                        local_c++;
                    else if (iVar12 == 0x372e2c04)
                        local_1c++;
                    else if (iVar12 == (int)0xccc35c46)
                        local_14++;
                    else if (iVar12 == 0x65672ade)
                        local_10++;
                }
            }
            do {
                uint32_t uVar4 = *puVar10;
                puVar10 += 0x8e;
                if ((uVar4 >> 0x1e & 1) != 0) break;
            } while ((int)*puVar10 < 0);
        } while (puVar2 != puVar10);
    }

    {
        int iVar13 = pi[0x2bf4 / 4];
        if (iVar13 != (int)pi[0x2bf8 / 4]) {
            int* piVar14 = (int*)(iVar13 + 0xc);
            do {
                if (AssetDataList(*piVar14, 0)) {
                    if (bVar5 && FUN_00552300(piVar14 - 1) != 0)
                        bVar5 = false;
                    if (bVar6 && Panel_Match(piVar14[-1], *piVar14, piVar14[1]) == 0)
                        bVar6 = false;
                }
                {
                    int iVar12 = piVar14[0x1b];
                    if (iVar12 != piVar14[0x1c]) {
                        do {
                            if ((*piVar14 == 0x2b978c46 || *piVar14 == 0x24682294) &&
                                (!bVar7 || *(int*)(iVar12 + 0x4ac) != 1))
                                bVar7 = false;
                            iVar12 += 0x4e0;
                        } while (iVar12 != piVar14[0x1c]);
                    }
                }
                iVar13 += 0x27e8;
                piVar14 += 0x9fa;
            } while (iVar13 != (int)pi[0x2bf8 / 4]);
        }
    }

    if (local_24 == 0) {
        c = AchievementsController(0xe55af32f, 1); c->AutoTest(0xe55af32f, 1);
    }
    if (0 < local_c)  { c = AchievementsController(0x62d8b529, local_c);  c->AutoTest(0x62d8b529, local_c); }
    if (0 < local_1c) { c = AchievementsController(0xeec38869, local_1c); c->AutoTest(0xeec38869, local_1c); }
    if (0 < local_14) { c = AchievementsController(0xaeda120e, local_14); c->AutoTest(0xaeda120e, local_14); }
    if (0 < local_10) { c = AchievementsController(0x5191a2e3, local_10); c->AutoTest(0x5191a2e3, local_10); }
    if (0 < local_1c && 0 < local_14 && 0 < local_10) {
        c = AchievementsController(0xa9d241a5, 1); c->AutoTest(0xa9d241a5, 1);
    }
    if (0 < local_28) { c = AchievementsController(0x60aec253, local_28); c->AutoTest(0x60aec253, local_28); }
    if (0 < local_20) { c = AchievementsController(0x836a79ce, local_20); c->AutoTest(0x836a79ce, local_20); }
    if (bVar5 && (0 < local_20 || 0 < local_28 || 0 < local_24)) {
        c = AchievementsController(0x280d4a31, 1); c->AutoTest(0x280d4a31, 1);
    }
    if (bVar6 && (0 < local_20 || 0 < local_28 || 0 < local_24)) {
        c = AchievementsController(0x5c324dc2, 1); c->AutoTest(0x5c324dc2, 1);
    }
    if (99 < local_20 + local_28 + local_24) {
        c = AchievementsController(0x88b15773, 1); c->AutoTest(0x88b15773, 1);
    }
    if (bVar7 && (0 < local_28 || 0 < local_24)) {
        c = AchievementsController(0x3b23cfa9, 1); c->AutoTest(0x3b23cfa9, 1);
    }
    if (g_16c7aa4->sim->f327f0()) {
        c = AchievementsController(0xe5e6d992, 1); c->AutoTest(0xe5e6d992, 1);
    }

    if (pi != 0)
        (*(void(__thiscall**)(uint32_t*))(*(uint32_t**)pi)[1])(pi);
}

// ===========================================================================
// 0x00ed7490 -- Panel::SelectionChanged(a)
// ===========================================================================
// @ 0x00ed7490
void Panel::SelectionChanged(int a)
{
    (void)a;
    if (g_16c7aa4->sim->f41270(0)) {
        if (*(int*)((char*)g_16c7aa4->sim->f10 + 8) == 0)
            BadgeAutoTest();
        Select(0);
        sim_f3d8c0(g_16c7aa4->sim);
    }
    else {
        mMode = 0;
    }
}
