// Slice s00e44200: SP::cSPUITimeline show / hide and its two companions.
//
//   0x00e44200  cSPUITimeline::Show(int show)        -- hide/show the timeline layout, its buttons,
//                                                       the per-level window, the timeline row windows
//                                                       and the effects message handler.
//   0x00e449b0  timeline message handler             -- reacts to the "timeline shown" (0x6123dbe) and
//                                                       "start timeline" (0x6256b62) messages.
//   0x00e44a30  destructive shutdown                 -- stops the timeline and releases every owned
//                                                       window / layout / key vector.  Entered with
//                                                       ecx = object + 8 (the embedded window
//                                                       subobject), see cSPUITimelineShutdown.
//
// Retail layout (differs from the 2008 dev PDB's 0x200-byte cSPUITimeline): the main CPUI layout is at
// +0x30, the window handles at +0x28..+0x60, the timeline rows at +0x364/+0x38c/+0x3b8 and the two key
// vectors at +0x450/+0x464.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct Vector4 { float x, y, z, w; };

// ------------------------------------------------------------------ UTFWin model
struct Object {
    virtual int  AddRef();                                 // +0x00
    virtual int  Release();                                // +0x04
    virtual void Delete();                                 // +0x08
};

#define IOFF(n) virtual void v##n();

struct IWindow : Object {
    IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    virtual void BeforeRelease();                          // +0x20
    virtual void Unload();                                 // +0x24
    IOFF(28) IOFF(2c) IOFF(30) IOFF(34) IOFF(38) IOFF(3c) IOFF(40)
    IOFF(44) IOFF(48) IOFF(4c) IOFF(50) IOFF(54) IOFF(58)
    virtual void SetShadeColor(uint32_t color);            // +0x5c
    virtual void SetLayoutData(const Vector4* data);       // +0x60
    IOFF(64) IOFF(68) IOFF(6c) IOFF(70) IOFF(74) IOFF(78)
    virtual void SetVisible(int visible, int recursive);   // +0x7c
    IOFF(80) IOFF(84) IOFF(88) IOFF(8c) IOFF(90) IOFF(94) IOFF(98) IOFF(9c)
    IOFF(a0) IOFF(a4) IOFF(a8) IOFF(ac) IOFF(b0) IOFF(b4) IOFF(b8) IOFF(bc)
    IOFF(c0) IOFF(c4) IOFF(c8) IOFF(cc) IOFF(d0) IOFF(d4) IOFF(d8) IOFF(dc)
    IOFF(e0) IOFF(e4) IOFF(e8) IOFF(ec) IOFF(f0) IOFF(f4) IOFF(f8) IOFF(fc)
    IOFF(100) IOFF(104)
    virtual void SetParent(void* parent);                  // +0x108
};

class cSPUILayout : public IWindow {
public:
    bool      IsVisible();                                 // 0x00810070
    void      SetVisibility(int visible);                  // 0x00810590
    IWindow*  FindWindowByID(uint32_t id, bool recursive); // 0x008105b0
    void      Shutdown(int everything);                    // 0x00811ad0
};

struct cSPPaletteItem : Object {
    void Shutdown();                                       // 0x005c6710
};

// A refcounted object with a second vtable base at +0x10 (the +0x3bc row object).
struct RefCountBase {
    virtual int AddRef();                                  // +0x00
    virtual int Release();                                 // +0x04
};
struct cTwoBaseObj {
    virtual int  AddRef();                                 // +0x00
    virtual int  Release();                                // +0x04
    virtual void Delete();                                 // +0x08
    uint32_t     mPad04[3];                                // +0x04 .. +0x0f
    RefCountBase mSecond;                                  // +0x10
};

// Animator-ish object the timeline lets go of through its first vtable slot.
struct IFlaggedRelease {
    virtual void Release(int keep);                        // +0x00
};

// The handler object EffectsManager hands back for message 0x4c4ba0a9.
struct IEffectsHandler {
    virtual void pad00();                                  // +0x00
    virtual void Release();                                // +0x04
    virtual void Delete(int unused);                       // +0x08
    virtual void SetEnabled(int enabled);                  // +0x0c
};

// eastl::vector<Key, sp_vector_allocator>
struct KeyVec {
    void* mpBegin;                                         // +0x00
    void* mpEnd;                                           // +0x04
    void* mpCap;                                           // +0x08
    void  DoCopy(void* first, void* last);                 // 0x0050f740
};

// ------------------------------------------------------------------ managers / singletons
struct cSPUILayoutManager {
    void SetAllWorldsVisibility(bool visible);             // 0x008106a0
    void SetLayerVisible(uint32_t id, bool visible);       // 0x00810660
};

struct IMessageServer {
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10)
    virtual void BeginModal(uint32_t id, int a, int b);    // +0x14
    virtual void SendMessage(uint32_t id, int a, int b, int c); // +0x18
};

struct cEffectsManager {
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18)
    IOFF(1c) IOFF(20) IOFF(24) IOFF(28)
    virtual bool AddMessageHandler(uint32_t id, int priority,
                                   IEffectsHandler** handlerOut); // +0x2c
};

// SP singleton at 0x0067dd50 (the object that carries the 0x16/2 notification).
struct cNotifier67dd50 {
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    IOFF(20) IOFF(24) IOFF(28) IOFF(2c) IOFF(30) IOFF(34) IOFF(38) IOFF(3c)
    IOFF(40) IOFF(44) IOFF(48) IOFF(4c) IOFF(50) IOFF(54) IOFF(58)
    virtual void SetNotificationA(uint32_t id, int value); // +0x5c
    virtual void SetNotificationB(uint32_t id, int value); // +0x60
};

struct cConfigManager {                                    // 0x0067dd30
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    IOFF(20) IOFF(24) IOFF(28) IOFF(2c)
    virtual int GetChoice(uint32_t id);                    // +0x30
};

struct cRenderTargetUser;
struct cHSM67de40 {                                        // 0x0067de40
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    virtual cRenderTargetUser* GetRenderTargets();         // +0x20
};
struct cRenderTargetUser {
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    virtual void SetCallbackTarget(void* target);          // +0x20
};

struct cWindowManager {                                    // 0x0067caa0
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    IOFF(20) IOFF(24) IOFF(28) IOFF(2c) IOFF(30) IOFF(34) IOFF(38) IOFF(3c)
    IOFF(40) IOFF(44) IOFF(48) IOFF(4c) IOFF(50) IOFF(54) IOFF(58)
    virtual void ShowWindow(int show, IWindow* window);    // +0x5c
};

struct cUIHints {
    int  SetFlag(char flag, int value);                    // 0x0067c420
};

struct IAudioSystem {                                      // EA::Audio::GetSystemAT result
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    virtual void* GetListener();                           // +0x20
};

// ------------------------------------------------------------------ callees
cSPUILayoutManager* SPUIHelpers_GetLayoutManager();        // 0x00805070
void SPUIHelpers_BeginModal(IWindow* owner, int a, int b);  // 0x008099a0
void SPUIHelpers_EndModal(IWindow* owner, int a, int b);    // 0x00809c50
void SP_KillSetiEffects(uint32_t id, void* system);        // 0x00435ed0
uint32_t SP_GetCurrentGameMode();                          // 0x00b5b800
IMessageServer* SP_MessageServer();                        // 0x0067dcc0
cEffectsManager* SP_EffectsManager();                      // 0x0067ddd0
cWindowManager* SP_WindowManager();                        // 0x0067caa0
cConfigManager* SP_ConfigManager();                        // 0x0067dd30
IAudioSystem* EA_Audio_GetSystemAT();                      // 0x00a206f0
void EA_Messaging_RemoveHandler(void* handler, void* owner, void* ids,
                                void* extra, unsigned flags); // 0x00571db0

extern "C" cNotifier67dd50* FUN_0067dd50();                // 0x0067dd50
extern "C" cHSM67de40*      FUN_0067de40();                // 0x0067de40
extern "C" cUIHints*        FUN_0067cac0();                // 0x0067cac0

extern uint8_t gForceTimelineMode;                         // @ 0x16acdf0

// ------------------------------------------------------------------ the timeline
struct cSPUITimeline {
    uint32_t         mVtbl;                                // +0x00
    uint32_t         mSelfWindow;                          // +0x04 head of the embedded window subobject
    uint32_t         mPad08[3];                            // +0x08 .. +0x13
    void*            mpCallbackTarget;                     // +0x14 handed to the render targets
    uint32_t         mPad18;                               // +0x18
    IFlaggedRelease* mpAnimatorA;                          // +0x1c
    cSPUILayout*     mpLayoutA;                            // +0x20
    cSPUILayout*     mpLayoutB;                            // +0x24
    IWindow*         mpWindowA;                            // +0x28
    IWindow*         mpWindowB;                            // +0x2c
    cSPUILayout*     mpLayout;                             // +0x30 the timeline layout Show() drives
    uint32_t         mPad34;                               // +0x34
    IWindow*         mpModalOwner;                         // +0x38
    IWindow*         mpCreatureWindow;                     // +0x3c
    uint32_t         mPad40;                               // +0x40
    IWindow*         mpTribeWindow;                        // +0x44
    uint32_t         mPad48;                               // +0x48
    IWindow*         mpCivWindow;                          // +0x4c
    uint32_t         mPad50[2];                            // +0x50 .. +0x57
    IWindow*         mpCreatureButton;                     // +0x58
    uint32_t         mPad5c;                               // +0x5c
    IWindow*         mpTribeButton;                        // +0x60
    uint32_t         mPad64[0x56];                         // +0x64 .. +0x1bb
    cSPPaletteItem*  mpPaletteItem;                        // +0x1bc
    Object*          mpPaletteInfo;                        // +0x1c0
    IWindow*         mpPaletteRollover;                    // +0x1c4
    IWindow*         mpEventRollover;                      // +0x1c8
    uint32_t         mPad1cc[0x28];                        // +0x1cc .. +0x26b
    bool             mbCreatureWindowShown;                // +0x26c
    bool             mbTribeWindowShown;                   // +0x26d
    uint8_t          mPad26e[0x0e];                        // +0x26e .. +0x27b
    bool             mbPanelReady;                         // +0x27c
    uint8_t          mPad27d[3];                           // +0x27d .. +0x27f
    int              mnPanelState;                         // +0x280
    int              mnShowMode;                           // +0x284
    uint32_t         mPad288[3];                           // +0x288 .. +0x293
    int              mnGameLevel;                          // +0x294
    uint32_t         mPad298[0x23];                        // +0x298 .. +0x323
    void*            mpMsgServer;                          // +0x324
    void*            mpMsgOwner;                           // +0x328
    void*            mpMsgIDs;                             // +0x32c
    IEffectsHandler* mpEffectsHandler;                     // +0x330
    unsigned         mMsgFlags;                            // +0x334
    cSPUILayout*     mpLayoutC;                            // +0x338
    cSPUILayout*     mpLayoutD;                            // +0x33c
    uint32_t         mPad340[9];                           // +0x340 .. +0x363
    IWindow*         mpRowWindows[10];                     // +0x364
    IWindow*         mpRowIcons[10];                       // +0x38c
    cTwoBaseObj*     mpRowData;                            // +0x3b4
    IWindow*         mpRowExtras[10];                      // +0x3b8
    uint32_t         mPad3e0[26];                          // +0x3e0 .. +0x447
    IFlaggedRelease* mpAnimatorB;                          // +0x448
    uint32_t         mPad44c;                              // +0x44c
    KeyVec           mCellKeys;                            // +0x450
    uint32_t         mPad45c[2];                           // +0x45c .. +0x463
    KeyVec           mCreatureKeys;                        // +0x464

    IWindow* Self() { return (IWindow*)&mSelfWindow; }     // the embedded window at +0x04

    void Show(int show);                                   // 0x00e44200
    bool HandleTimelineMessage(uint32_t msgID, void* payload); // 0x00e449b0
    void FUN_00e37910();                                   // 0x00e37910
    void FUN_00e3e7f0();                                   // 0x00e3e7f0
    void FUN_00e42100();                                   // 0x00e42100
    void FUN_00e43280();                                   // 0x00e43280
};

// The destructive shutdown (0x00e44a30) is entered with ecx = object + 8, i.e. on the embedded window
// subobject; the timeline body is 8 bytes below `this`.  Same fields as cSPUITimeline, 8 lower.
struct cSPUITimelineShutdown {
    uint32_t         mPad00;                               // +0x00 (body +0x00)
    uint32_t         mPad04;                               // +0x04 (body +0x04)
    uint32_t         mPad08[5];                            // +0x08 .. +0x1b (body +0x00 .. +0x13)
    void*            mpCallbackTarget;                     // +0x1c (body +0x14)
    uint32_t         mPad20;                               // +0x20 (body +0x18)
    IFlaggedRelease* mpAnimatorA;                          // +0x24 (body +0x1c)
    cSPUILayout*     mpLayoutA;                            // +0x28 (body +0x20)
    cSPUILayout*     mpLayoutB;                            // +0x2c (body +0x24)
    IWindow*         mpWindowA;                            // +0x30 (body +0x28)
    IWindow*         mpWindowB;                            // +0x34 (body +0x2c)
    uint32_t         mPad38[3];                            // +0x38 .. +0x43 (body +0x30 .. +0x3b)
    IWindow*         mpCreatureWindow;                     // +0x44 (body +0x3c)
    uint32_t         mPad48;                               // +0x48 (body +0x40)
    IWindow*         mpTribeWindow;                        // +0x4c (body +0x44)
    uint32_t         mPad50[0x5d];                         // +0x50 .. +0x1c3 (body +0x48 .. +0x1bb)
    cSPPaletteItem*  mpPaletteItem;                        // +0x1c4 (body +0x1bc)
    Object*          mpPaletteInfo;                        // +0x1c8 (body +0x1c0)
    IWindow*         mpPaletteRollover;                    // +0x1cc (body +0x1c4)
    IWindow*         mpEventRollover;                      // +0x1d0 (body +0x1c8)
    uint32_t         mPad1d4[0x56];                        // +0x1d4 .. +0x32b (body +0x1cc .. +0x323)
    void*            mpMsgServer;                          // +0x32c (body +0x324)
    void*            mpMsgOwner;                           // +0x330 (body +0x328)
    void*            mpMsgIDs;                             // +0x334 (body +0x32c)
    IEffectsHandler* mpEffectsHandler;                     // +0x338 (body +0x330)
    unsigned         mMsgFlags;                            // +0x33c (body +0x334)
    cSPUILayout*     mpLayoutC;                            // +0x340 (body +0x338)
    cSPUILayout*     mpLayoutD;                            // +0x344 (body +0x33c)
    uint32_t         mPad348[9];                           // +0x348 .. +0x36b (body +0x340 .. +0x363)
    IWindow*         mpRowWindows[10];                     // +0x36c (body +0x364)
    IWindow*         mpRowIcons[10];                       // +0x394 (body +0x38c)
    cTwoBaseObj*     mpRowData;                            // +0x3bc (body +0x3b4)
    IWindow*         mpRowExtras[10];                      // +0x3c0 (body +0x3b8)
    uint32_t         mPad3e8[26];                          // +0x3e8 .. +0x44f (body +0x3e0 .. +0x447)
    IFlaggedRelease* mpAnimatorB;                          // +0x450 (body +0x448)
    uint32_t         mPad454;                              // +0x454 (body +0x44c)
    KeyVec           mCellKeys;                            // +0x458 (body +0x450)
    uint32_t         mPad464[2];                           // +0x464 .. +0x46b (body +0x45c .. +0x463)
    KeyVec           mCreatureKeys;                        // +0x46c (body +0x464)

    __forceinline cSPUITimeline* Body() { return (cSPUITimeline*)((char*)this - 8); }
    __forceinline void* SelfOrNull() {
        cSPUITimeline* b = Body();
        return b ? (void*)b->Self() : (void*)0;
    }

    void Destroy();                                        // 0x00e44a30
};

// ------------------------------------------------------------------ window helpers
// The level windows 0x15503770..0x15503774 are hidden before the current level's one is shown; each
// test looks the window up twice, exactly as the original does.
static __forceinline void HideLevelWindow(cSPUILayout* layout, uint32_t id)
{
    if (layout->FindWindowByID(id, 1))
        layout->FindWindowByID(id, 1)->SetVisible(1, 0);
}

static __forceinline void ShowWindowByID(cSPUILayout* layout, uint32_t id, int visible)
{
    layout->FindWindowByID(id, 1)->SetVisible(1, visible);
}

static __forceinline void ClearWindowRect(cSPUILayout* layout, uint32_t id)
{
    IWindow* hidden = layout->FindWindowByID(id, 1);
    hidden->SetVisible(1, 0);
    IWindow* cleared = layout->FindWindowByID(id, 1);
    Vector4 empty = { 0.0f, 0.0f, 0.0f, 0.0f };
    cleared->SetLayoutData(&empty);
}

static __forceinline void TintWindow(cSPUILayout* layout, uint32_t id)
{
    layout->FindWindowByID(id, 1)->SetShadeColor(0xff4b4b4b);
}

// ================================================================== 0x00e44200
// @ 0x00e44200
void cSPUITimeline::Show(int show)
{
    if (!show && !mpLayout->IsVisible())
        return;

    if (show != mpLayout->IsVisible()) {
        cSPUILayoutManager* mgr = SPUIHelpers_GetLayoutManager();
        if (show) {
            mgr->SetAllWorldsVisibility(false);
            mgr->SetLayerVisible(0x8c509d6c, true);
            mgr->SetLayerVisible(0x5b598f6, true);
            mgr->SetLayerVisible(0x5b598f7, true);
        } else {
            mgr->SetLayerVisible(0x8c509d6c, false);
            mgr->SetLayerVisible(0x5b598f6, false);
            mgr->SetLayerVisible(0x5b598f7, false);
            mgr->SetAllWorldsVisibility(true);
        }
    }
    mpLayout->SetVisibility(show);

    if (show) {
        IAudioSystem* audio = EA_Audio_GetSystemAT();
        SP_KillSetiEffects(0x6d093bee, audio ? audio->GetListener() : 0);
        SPUIHelpers_BeginModal(mpModalOwner, 0, 0);
        SP_MessageServer()->BeginModal(0x4a07018, 0, 0);
        mbPanelReady = false;
        mnPanelState = 0;
    } else {
        SPUIHelpers_EndModal(mpModalOwner, 0, 0);
        if (mbCreatureWindowShown) {
            SP_WindowManager()->ShowWindow(1, mpCreatureWindow);
            mbCreatureWindowShown = false;
        }
        if (mbTribeWindowShown) {
            SP_WindowManager()->ShowWindow(1, mpTribeWindow);
            mbTribeWindowShown = false;
        }
    }

    FUN_0067cac0()->SetFlag(show == 0, 1);

    if (mpCreatureButton)
        mpCreatureButton->SetVisible(1, show);
    if (mpTribeButton)
        mpTribeButton->SetVisible(1, show);

    if (IWindow* w = mpLayout->FindWindowByID(0x4486ae8, 1))
        w->SetVisible(1, show);
    if (IWindow* w = mpLayout->FindWindowByID(0x4486b30, 1))
        w->SetVisible(1, show);
    if (IWindow* w = mpLayout->FindWindowByID(0x54e53d9d, 1))
        w->SetVisible(1, show);
    if (IWindow* w = mpLayout->FindWindowByID(0xf54a5ddc, 1))
        w->SetVisible(1, show);
    if (IWindow* w = mpLayout->FindWindowByID(0x61388da, 1))
        w->SetVisible(1, show);
    if (IWindow* w = mpLayout->FindWindowByID(0x61388db, 1))
        w->SetVisible(1, show);
    if (IWindow* w = mpLayout->FindWindowByID(0x694d94c, 1))
        w->SetVisible(1, show);
    if (IWindow* w = mpLayout->FindWindowByID(0x694d94b, 1))
        w->SetVisible(1, show);

    if (show) {
        int level;
        switch (SP_GetCurrentGameMode()) {
        case 0x1654c00: level = 0; break;
        case 0x1654c01: level = 1; break;
        case 0x1654c02: level = 2; break;
        case 0x1654c04: level = 3; break;
        case 0x1654c05: level = 4; break;
        case 0x1654c10: level = 5; break;
        default:        level = show; break;
        }

        HideLevelWindow(mpLayout, 0x15503770);
        HideLevelWindow(mpLayout, 0x15503771);
        HideLevelWindow(mpLayout, 0x15503772);
        HideLevelWindow(mpLayout, 0x15503773);
        HideLevelWindow(mpLayout, 0x15503774);

        if (mpLayout->FindWindowByID(0x15503770 + level, 1)) {
            int shown;
            switch (SP_GetCurrentGameMode()) {
            case 0x1654c00: shown = 0; break;
            case 0x1654c01: shown = 1; break;
            case 0x1654c02: shown = 2; break;
            case 0x1654c04: shown = 3; break;
            case 0x1654c05: shown = 4; break;
            case 0x1654c10: shown = 5; break;
            default:        shown = show; break;
            }
            ShowWindowByID(mpLayout, 0x15503770 + shown, 1);
        }

        if (cEffectsManager* effects = SP_EffectsManager()) {
            if (IEffectsHandler* old = mpEffectsHandler) {
                mpEffectsHandler = 0;
                old->Release();
            }
            if (effects->AddMessageHandler(0x4c4ba0a9, 0, &mpEffectsHandler))
                mpEffectsHandler->Delete(0);
        }

        SP_MessageServer()->SendMessage(0x6123dbe, 0, 0, 0);

        ClearWindowRect(mpLayout, 0x74ed2970);
        ClearWindowRect(mpLayout, 0x74ed2971);
        ClearWindowRect(mpLayout, 0x74ed2972);
        ClearWindowRect(mpLayout, 0x74ed2973);
        ClearWindowRect(mpLayout, 0x74ed2974);

        TintWindow(mpLayout, 0x60be2e0);
        TintWindow(mpLayout, 0x60be2e1);
        TintWindow(mpLayout, 0x60be2e2);
        TintWindow(mpLayout, 0x60be2e3);
        TintWindow(mpLayout, 0x60be2e4);

        FUN_00e42100();
        FUN_00e3e7f0();
        FUN_00e37910();
    } else {
        if (IEffectsHandler* old = mpEffectsHandler) {
            old->SetEnabled(0);
            if (IEffectsHandler* released = mpEffectsHandler) {
                mpEffectsHandler = 0;
                released->Release();
            }
        }
        FUN_0067dd50()->SetNotificationB(0x16, 2);
        FUN_00e43280();
        FUN_00e37910();
    }
}

// ================================================================== 0x00e449b0
// @ 0x00e449b0
bool cSPUITimeline::HandleTimelineMessage(uint32_t msgID, void* payload)
{
    if (msgID != 0x6123dbe) {
        if (msgID == 0x6256b62 && payload != 0) {
            int* data = (int*)payload;
            int kind = data[2];
            mnGameLevel = data[4];
            if (gForceTimelineMode || kind == 1)
                mnShowMode = SP_ConfigManager()->GetChoice(0x4ea96cb) ? 1 : 2;
            Show(1);
            return true;
        }
    } else {
        FUN_0067dd50()->SetNotificationA(0x16, 2);
    }
    return true;
}

// ================================================================== 0x00e44a30
// @ 0x00e44a30
void cSPUITimelineShutdown::Destroy()
{
    Body()->Show(0);

    cSPUITimeline* body = Body();
    void* callback = body ? (void*)&mpCallbackTarget : (void*)0;
    cRenderTargetUser* targets = FUN_0067de40()->GetRenderTargets();
    targets->SetCallbackTarget(callback);

    if (IFlaggedRelease* animator = mpAnimatorA) {
        animator->Release(1);
        mpAnimatorA = 0;
    }

    mCellKeys.DoCopy(mCellKeys.mpBegin, mCellKeys.mpEnd);
    mCreatureKeys.DoCopy(mCreatureKeys.mpBegin, mCreatureKeys.mpEnd);

    if (IFlaggedRelease* animator = mpAnimatorB) {
        animator->Release(1);
        mpAnimatorB = 0;
    }

    if (mpTribeWindow)
        mpTribeWindow->SetParent(body ? body->Self() : 0);
    if (mpWindowB)
        mpWindowB->SetParent(body ? body->Self() : 0);
    if (mpCreatureWindow)
        mpCreatureWindow->SetParent(body ? body->Self() : 0);
    if (mpWindowA)
        mpWindowA->SetParent(body ? body->Self() : 0);

    if (mpPaletteItem) {
        mpPaletteItem->Shutdown();
        if (cSPPaletteItem* item = mpPaletteItem) {
            mpPaletteItem = 0;
            item->Delete();
        }
    }
    if (Object* info = mpPaletteInfo) {
        mpPaletteInfo = 0;
        info->Delete();
    }
    if (IWindow* rollover = mpPaletteRollover) {
        rollover->Unload();
        if (IWindow* released = mpPaletteRollover) {
            mpPaletteRollover = 0;
            released->Release();
        }
    }
    if (IWindow* rollover = mpEventRollover) {
        rollover->Unload();
        if (IWindow* released = mpEventRollover) {
            mpEventRollover = 0;
            released->Release();
        }
    }
    if (cTwoBaseObj* rowData = mpRowData) {
        rowData->Delete();
        if (cTwoBaseObj* released = mpRowData) {
            mpRowData = 0;
            released->mSecond.Release();
        }
    }

    for (int i = 0; i < 10; ++i) {
        if (mpRowWindows[i]) {
            if (IWindow* window = mpRowWindows[i]) {
                mpRowWindows[i] = 0;
                window->Release();
            }
        }
        if (mpRowIcons[i]) {
            if (IWindow* icon = mpRowIcons[i]) {
                mpRowIcons[i] = 0;
                icon->Release();
            }
        }
        if (IWindow* extra = mpRowExtras[i]) {
            extra->BeforeRelease();
            if (IWindow* released = mpRowExtras[i]) {
                mpRowExtras[i] = 0;
                released->Release();
            }
        }
    }

    if (cSPUILayout* layout = mpLayoutB) {
        layout->Shutdown(1);
        if (cSPUILayout* released = mpLayoutB) {
            mpLayoutB = 0;
            released->Delete();
        }
    }
    if (cSPUILayout* layout = mpLayoutA) {
        layout->Shutdown(1);
        if (cSPUILayout* released = mpLayoutA) {
            mpLayoutA = 0;
            released->Delete();
        }
    }
    if (cSPUILayout* layout = mpLayoutC) {
        layout->Shutdown(1);
        if (cSPUILayout* released = mpLayoutC) {
            mpLayoutC = 0;
            released->Delete();
        }
    }
    if (cSPUILayout* layout = mpLayoutD) {
        layout->Shutdown(1);
        if (cSPUILayout* released = mpLayoutD) {
            mpLayoutD = 0;
            released->Delete();
        }
    }

    if (mpMsgServer) {
        void* server = mpMsgServer;
        mpMsgServer = 0;
        EA_Messaging_RemoveHandler(server, mpMsgOwner, mpMsgIDs, mpEffectsHandler,
                                   mMsgFlags);
    }
}
