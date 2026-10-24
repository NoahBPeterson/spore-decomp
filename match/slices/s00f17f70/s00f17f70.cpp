// Slice s00f17f70: per-frame Update of a level-progress UI panel (0x00f17f70, 1773 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (scalar SSE compares, x87 float copies through references).
//
// The panel animates a value (mCur) towards a target (mEnd): a count-down delay, the palette
// and updater ticks, enabling/disabling child windows by state, then in state 8 starts the
// animation, and in state 3 advances it (timer, easing ratio, rect interpolation, number
// strings) and, when a new level is reached, swaps in the level image and plays the level-up.
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

typedef unsigned int uint;

// ----------------------------------------------------------------------------- UI stubs
struct IWin {
    virtual void AddRef();                           // +0x00
    virtual void Release();                          // +0x04
    PV8 PV4
    virtual float* GetRect();                        // +0x38
    PV8 PV4
    virtual void SetRect(const float* rect);         // +0x6c
    virtual void SetPosition(float x, float y);      // +0x70
    virtual void SetSize(float w, float h);          // +0x74
    PV
    virtual void SetVisible(int a, bool b);          // +0x7c
    virtual void SetText(const wchar_t* text);       // +0x80
};
struct IWinContainer {
    uint pad04[0x8c / 4];                            // +0x04
    int  mMode;                                      // +0x90
    uint pad94[(0xf0 - 0x94) / 4];                   // +0x94
    virtual void AddRef();                           // +0x00
    virtual void Release();                          // +0x04
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV2
    virtual IWin* FindChild(uint id, int recurse);   // +0xf0
};
struct Layout {
    IWin* FindWindowByID(uint id, int recurse);      // 0x008105b0
    void  SetVisibility(int visible);                // 0x00810590
    bool  IsVisible();                               // 0x00810070
};

struct IAudioSystem {
    PV8
    virtual int Query();                             // +0x20
};

struct GlobalState {
    uint pad00[0x74 / 4];
    void* mpSub74;                                   // +0x74
    uint pad78[(0xd0 - 0x78) / 4];
    int mLevel;                                      // +0xd0
};
extern GlobalState* g_16c7aa4;                       // 0x016c7aa4

struct PaletteHolder {
    void Update(uint deltaMS);                       // 0x005c28b0 (cSPPaletteCategoryUI::Update)
};
struct Updater490 {
    void Update490(uint deltaMS);                    // 0x00ae8510
    void BindSlotCreature(void* scenario, int a, float* pos, void* data, int b, IWin* win); // 0x00ae8d00
    void SetSlider(uint idA, uint idB, int a, int b); // 0x00ae7e10
    void SetSerializer();                             // 0x00c2e4e0
};
Updater490* GetUpdater490();                         // 0x00b3d490

void SetGlobalProperty(uint id, float value);                        // 0x005ca880 (cdecl)
void SetNumberString(int64_t value, wchar_t* buf, int cap);          // 0x00881ae0 (cdecl)
void SetImageFromLayout(IWin* win, Layout* layout, int id, int a);   // 0x00806a60 (cdecl)
IAudioSystem* GetSystemAT();                                         // 0x00a206f0
void KillSetiEffects(uint id, int audio);                            // 0x00435ed0 (cdecl)
int LevelFromValue(int v);                                           // 0x00eec580 (cdecl)
float LevelBaseValue();                                              // 0x00eec5b0
int FindFirstGE(int v);                                              // 0x00eec540 (cdecl)
void SpawnEffect(uint id, int a, uint* pos, uint* dir, int b, int level, uint* arr, int c);  // 0x00e39ab0 (cdecl)

struct SubA {
    uint pad00[0x18 / 4];
    PaletteHolder* mpPalette;                        // +0x18
    uint pad1c;
    void* mpField20;                                 // +0x20
    int  GetLevelData();                             // 0x00f12690
    void SetAnimWindow(IWin* win);                   // 0x00f17b00
};
struct LevelData { int GetMaxLevel(); };             // 0x005943b0
struct CtxKeys;
struct SubB {
    uint pad00[4];                                   // +0x00
    CtxKeys* mpKeys;                                 // +0x10
    int GetEffectContext();                          // 0x00f3bcb0
};

struct Rect4 { float x, y, z, w; };
inline float fabsf(float x) { return x < 0.0f ? -x : x; }

// eastl::min / max on references to float (b < a ? b : a)
inline const float& FMin(const float& a, const float& b) { return (b < a) ? b : a; }
inline const float& FMax(const float& a, const float& b) { return (a < b) ? b : a; }

// --------------------------------------------------------------------- messaging
struct IHandler { PV8 };
struct IServer {
    PV4
    virtual void Send(uint32_t id, int a, int b);            // +0x14
    PV2 PV
    virtual void AddHandler(IHandler* h, uint32_t id);       // +0x24
};
IServer* MessageServer();                                    // 0x0067dcc0
namespace EA { namespace Messaging {
void RemoveHandler(IServer* server, IHandler* h, uint32_t id, int prio, int flags);  // 0x00571db0
} }

// Primary and message-handler sub-objects of cSPUIProgress (handler sits at +0x04).
struct PanelPrimary { virtual void v0(); };
struct PanelHandlerBase : IHandler {
    virtual bool HandleMessage(uint msg, void* payload);     // 0x00f18970
};

// Secondary interface at +0x04 of UI panels (AddRef at +4, Release at +8).
struct IRef {
    virtual void v0();
    virtual void AddRef();                                   // +0x04
    virtual void Release();                                  // +0x08
};
struct PanelIface {
    uint pad00;                                              // +0x00
    IRef mRef;                                               // +0x04
    uint pad08[(0x90 - 8) / 4];                              // +0x08
    int  mMode;                                              // +0x90
};

// Property system (editor property list returned for a scenario).
struct Property;
struct PropertyList {
    virtual void v0();
    virtual void Release();                                  // +0x04
    PV8
    virtual Property* GetProperty(uint32_t key);             // +0x28
};
struct Property {
    union Value { int mInt; Property* mpValue; } mValue;     // +0x00
    uint pad04[3];                                           // +0x04
    uint8_t mFlags;                                          // +0x10
    uint8_t pad11;                                           // +0x11
    uint16_t mType;                                          // +0x12
};
bool GetEditorPropertyList(void* scenario, PropertyList** out);   // 0x005bf0e0
bool FUN_00eebfc0(PropertyList* list, void* key);                 // 0x00eebfc0
int  FUN_00eec570();                                              // 0x00eec570
extern Property g_15d1160;                                        // 0x015d1160

// The scenario sub-object at g_16c7aa4->mpSub74.
struct CtxKeys { uint f0, f4, f8, fC; };
struct ScenarioCtx {
    uint pad00[4];
    CtxKeys* mpKeys;                                         // +0x10
    int  GetRowCount();                                      // 0x00f3be30
    int  GetColCount(int row);                               // 0x00f3bec0
};

// Base for the animation component (UI::cScenarioPlayProgressBar).

struct IFx;

class cSPUIProgress : public PanelPrimary, public PanelHandlerBase {
public:
    uint pad08[2];                                   // +0x08
    PanelIface* mpWindow;                            // +0x10
    void* mpUnknown14;                               // +0x14
    Layout* mpLayout;                                // +0x18
    IFx* mpEffect;                                   // +0x1c
    uint pad20;                                      // +0x20
    SubA* mpSubA;                                    // +0x24
    uint pad28[(0xb8 - 0x28) / 4];
    PropertyList* mpPropList;                        // +0xb8
    float mTimer;                                    // +0xbc
    float mCur;                                      // +0xc0
    float mStart;                                    // +0xc4
    float mEnd;                                      // +0xc8
    float mNext;                                     // +0xcc
    int   mLevel;                                    // +0xd0
    int   mState;                                    // +0xd4
    uint  mDelay;                                    // +0xd8
    IWinContainer* mpWinA;                           // +0xdc
    IWinContainer* mpWinB;                           // +0xe0
    IServer* mpServer;                               // +0xe4
    IHandler* mpHandler;                             // +0xe8
    uint  mMsg;                                      // +0xec
    int   mPrio;                                     // +0xf0
    int   mFlags;                                    // +0xf4

    void StartNextAnimation();                       // 0x00f17870
    bool CheckFlag(int a);                           // 0x00f135b0
    void Show(PanelIface* window);                   // 0x00f18660
    void FUN_00f17ea0();                             // 0x00f17ea0
    int  FUN_00f13b10();                             // 0x00f13b10
    void FUN_00f15890();                             // 0x00f15890

    void Update(uint deltaMS);
};

namespace UI {
// 0x0148c180 (UI::cScenarioPlayProgressBar): animates a bar between two values.
class cScenarioPlayProgressBar {
public:
    uint pad00[3];                                   // +0x00
    uint mpField0c;                                  // +0x0c
    IWinContainer* mpWindow;                         // +0x10
    IWin* mpBar;                                     // +0x14
    Rect4 mRect;                                     // +0x18 (left, top, right, bottom)
    float mCur;                                      // +0x28
    float mTarget;                                   // +0x2c
    bool mFlag30;                                    // +0x30
    bool mFlag31;                                    // +0x31
    uint8_t pad32[2];                                // +0x32
    uint pad34[8];                                   // +0x34 cSPUIAnimator
    IServer* mpServer;                               // +0x54
    IHandler* mpHandler;                             // +0x58
    uint mMsg;                                       // +0x5c
    int mPrio;                                       // +0x60
    int mFlags;                                      // +0x64

    void SetValue(float value);                      // 0x00f18a00
    void SetWindow(IWinContainer* window);           // 0x00f18a50
    void Clear();                                    // 0x00f18d60
    void Update(uint deltaMS);                       // 0x00f18dc0
};
}

// @ 0x00f17f70
void cSPUIProgress::Update(uint deltaMS)
{
    if (mDelay > 0) {
        mDelay--;
        if (mDelay == 0)
            StartNextAnimation();
        return;
    }

    if (mpSubA->mpPalette)
        mpSubA->mpPalette->Update(deltaMS);
    GetUpdater490()->Update490(deltaMS);

    if (mpWinA) {
        bool active = (mState == 0 || mState == 9);
        bool levelUp = (g_16c7aa4->mLevel != 0);
        IWin* w = mpWinA->FindChild(0x7c79948, 1);
        if (w) w->SetVisible(1, active);
        w = mpWinA->FindChild(0x7c79940, 1);
        if (w) w->SetVisible(1, active);
        bool v = active && levelUp;
        w = mpWinA->FindChild(0x7c79c50, 1);
        if (w) w->SetVisible(1, v);
        w = mpWinB->FindChild(0x7c79c78, 1);
        if (w) w->SetVisible(1, active);
        v = active && CheckFlag(0);
        w = mpWinB->FindChild(0x7e20437, 1);
        if (w) w->SetVisible(1, v);
    }

    wchar_t text[0x20];

    if (mState == 8 && mpSubA->mpField20) {
        IWin* w = mpLayout->FindWindowByID(0x7c66c00, 1);
        if (w) w->SetVisible(1, false);
        if (mCur != mEnd) {
            mStart = mNext;
            float next = (float)LevelFromValue(mLevel + 1);
            mNext = next;
            float limit = next - 1.0f;
            mStart = FMin(mStart, limit);
            mTimer = LevelBaseValue();
            SetNumberString((int64_t)mNext, text, 0x20);
            w = mpLayout->FindWindowByID(0x7c7a088, 1);
            if (w) w->SetText(text);
            IWin* bar = mpLayout->FindWindowByID(0x7c7a310, 1);
            float* r = bar->GetRect();
            float rectCopy[4];
            rectCopy[0] = r[0];
            rectCopy[1] = r[1];
            rectCopy[2] = r[2];
            rectCopy[3] = r[3];
            rectCopy[1] = rectCopy[3];
            bar->SetRect(rectCopy);
            mState = 3;
        } else {
            mState = 0;
        }
    }

    if (mState != 3)
        return;

    if (!(0.0f < mTimer)) {
        mState = 0;
        return;
    }

    float one;
    float t;
    float v1;
    float q;
    float r2[4];
    float a[3];
    float dt = (float)deltaMS * 0.001f;
    one = 1.0f;
    float ratio = dt / mTimer;
    t = FMin(ratio, one);
    mTimer = mTimer - dt;
    SetGlobalProperty(0xf1472886, (mCur - mStart) / (mEnd - mStart));

    v1 = FMin(mEnd, mNext);
    IWin* ref = mpLayout->FindWindowByID(0x7c7a318, 1);
    float* ra = ref->GetRect();
    a[0] = ra[1];
    a[2] = ra[3];
    IWin* bar = mpLayout->FindWindowByID(0x7c7a310, 1);
    float* rb = bar->GetRect();
    r2[0] = rb[0];
    r2[1] = rb[1];
    r2[2] = rb[2];
    r2[3] = rb[3];
    q = 1.0f - (v1 - mStart) / (mNext - mStart);
    float zero = 0.0f;
    float p = FMax(q, zero);
    r2[1] = (((a[2] - a[0]) * p + a[0]) - r2[1]) * t + r2[1];
    bar->SetRect(r2);
    bool moved = (r2[1] != a[0]);
    IWin* w = mpLayout->FindWindowByID(0x7c7a088, 1);
    if (w) w->SetVisible(1, moved);

    float cur = (v1 - mCur) * t + mCur;
    mCur = cur;
    SetNumberString((int64_t)cur, text, 0x20);
    w = mpLayout->FindWindowByID(0x7c79fd8, 1);
    if (w) w->SetText(text);
    SetNumberString((int64_t)(mEnd - mCur), text, 0x20);
    w = mpWinA->FindChild(0x7c79d78, 1);
    if (w) w->SetText(text);

    int level = FindFirstGE((int)mCur);
    mLevel = level;
    if (level > ((LevelData*)mpSubA->GetLevelData())->GetMaxLevel()) {
        SetImageFromLayout(mpLayout->FindWindowByID(0x7eb2740, 1), mpLayout, level + 0x7f24ce0, -1);
        w = mpLayout->FindWindowByID(0x7db8991, 1);
        if (w) w->SetVisible(1, true);
        w = mpLayout->FindWindowByID(0x7c62860, 1);
        if (w) w->SetVisible(2, true);
        mState = 4;
        IAudioSystem* audio = GetSystemAT();
        KillSetiEffects(0x366f725d, audio ? audio->Query() : 0);
        if (g_16c7aa4->mLevel == 2) {
            SubB* sub = (SubB*)g_16c7aa4->mpSub74;
            uint arr[6] = {0, 0, 0, 0, 0, 0};
            uint v3[3] = {0, 0, 0};
            SpawnEffect(0xbbc2a4ef, 0, v3, &arr[3], 0, mLevel, arr, sub->GetEffectContext());
        }
    }
}

// ------------------------------------------------------------------ UI objects
struct IWindowManager {
    PV
    virtual void* GetFocus();                        // +0x04
};
IWindowManager* WindowManager();                     // 0x0067caa0
void SPUI_SetVisible_812d60(void* obj, int visible); // 0x00812d60

struct IFx {
    PV
    virtual void Release();                          // +0x04
    virtual void SetState(int state);                // +0x08
};
struct IFxSystem {
    PV2
    virtual bool Create(uint32_t id, int flags, IFx** out);  // +0x08
};
struct IEffectsManager {
    PV8 PV8 PV4 PV2 PV
    virtual IFxSystem* GetSystem();                  // +0x5c
};
IEffectsManager* EffectsManagerPtr();                // 0x0067ddd0

struct cGameTimeManager {
    void IncPauseGate(uint32_t id);                  // 0x00b32220
};
cGameTimeManager* GameTimeManager();                 // 0x00b3d380

namespace SPUIHelpers {
void BeginModal(IWin* window, int a, int b);         // 0x008099a0
}
bool cScenarioPlayProgressBar_IsReady();             // 0x00f19640

extern int g_15ad8f0;                                // 0x015ad8f0
extern int g_15ad8ec;                                // 0x015ad8ec
extern uint32_t g_13ec468;                           // 0x013ec468

struct MsgPayload {
    uint pad00[4];
    uint mKey10;                                     // +0x10
    uint pad14;                                      // +0x14
    uint mKey18;                                     // +0x18
};

// @ 0x00f18a00
void UI::cScenarioPlayProgressBar::SetValue(float value)
{
    mTarget = FMin(FMax(value, 0.0f), 1.0f);
}

// @ 0x00f18a50
void UI::cScenarioPlayProgressBar::SetWindow(IWinContainer* window)
{
    IWinContainer* oldWindow = mpWindow;
    if (window != oldWindow) {
        if (window) window->AddRef();
        mpWindow = window;
        if (oldWindow) oldWindow->Release();
    }

    IWin* bar = mpWindow->FindChild(0x7606d98, 1);
    IWin* oldBar = mpBar;
    if (bar != oldBar) {
        if (bar) bar->AddRef();
        mpBar = bar;
        if (oldBar) oldBar->Release();
    }

    float* r = mpBar->GetRect();
    mRect.x = r[0];
    mRect.y = r[1];
    mRect.z = r[2];
    mRect.w = r[3];

    for (int i = 0; i < g_15ad8f0; i++) {
        IWin* child = mpWindow->FindChild(i + 0x7720270, 1);
        child->SetVisible(1, false);
    }
    for (int i = 0; i < g_15ad8ec; i++) {
        IWin* child = mpWindow->FindChild(i + 0x7606e61, 1);
        child->SetVisible(1, false);
    }

    ScenarioCtx* ctx = (ScenarioCtx*)g_16c7aa4->mpSub74;
    int rows = ctx->GetRowCount();
    float step = (mRect.z - mRect.x) / (float)rows;
    int childIndex = 0;
    for (int row = 0; row < rows; row++) {
        float x = (float)row * step;
        if (rows > 1 && row > 0) {
            IWin* c = mpWindow->FindChild(row + 0x7606e60, 1);
            float* cr = c->GetRect();
            c->SetPosition(x - (cr[2] - cr[0]) * 0.5f, cr[1]);
            c->SetVisible(1, true);
        }
        int cols = ctx->GetColCount(row);
        float colStep = step / (float)cols;
        for (int col = 1; col < cols; col++) {
            IWin* c = mpWindow->FindChild(childIndex + 0x7720270, 1);
            float* cr = c->GetRect();
            c->SetPosition(((float)col * colStep + x) + mRect.x - (cr[2] - cr[0]) * 0.5f, cr[1]);
            c->SetVisible(1, true);
            childIndex++;
        }
    }

    mpServer = MessageServer();
    mpHandler = (IHandler*)&pad00[1];
    mMsg = 0x148c164;
    mPrio = 1;
    mFlags = 0;
    if (mpServer && mpHandler)
        mpServer->AddHandler(mpHandler, 0xffffffff);
}

// @ 0x00f18d60
void UI::cScenarioPlayProgressBar::Clear()
{
    if (mpServer) {
        IServer* server = mpServer;
        mpServer = 0;
        EA::Messaging::RemoveHandler(server, mpHandler, mMsg, mPrio, mFlags);
    }
    if (mpWindow) {
        IWinContainer* w = mpWindow;
        mpWindow = 0;
        w->Release();
    }
    if (mpBar) {
        IWin* b = mpBar;
        mpBar = 0;
        b->Release();
    }
}

// @ 0x00f18dc0
void UI::cScenarioPlayProgressBar::Update(uint deltaMS)
{
    float d = mTarget - mCur;
    if (1.5258789e-05f < fabsf(d)) {
        float step = (float)deltaMS * 0.0005f;
        float zero = 0.0f;
        if (d > zero)
            d = FMin(FMax(d, zero), step);
        else
            d = FMin(FMax(d, -step), zero);
        mCur = mCur + d;
        mpBar->SetSize((mRect.z - mRect.x) * mCur, mRect.w - mRect.y);
    }
}

// @ 0x00f18660
void cSPUIProgress::Show(PanelIface* window)
{
    void* focus = WindowManager()->GetFocus();
    void* focusBase = focus ? (void*)((uint32_t*)focus - 1) : 0;
    SPUI_SetVisible_812d60(focusBase, 1);

    if (!mpEffect) {
        IFxSystem* fx = EffectsManagerPtr()->GetSystem();
        if (mpEffect) {
            IFx* old = mpEffect;
            mpEffect = 0;
            old->Release();
        }
        if (fx->Create(0x4c4ba0a9, 0, &mpEffect)) {
            mpEffect->SetState(0);
        }
    }

    GameTimeManager()->IncPauseGate(0x4bf38a7);
    IWin* modal = mpLayout->FindWindowByID(0xffffffff, 1);
    SPUIHelpers::BeginModal(modal, 0, 0);
    mpLayout->SetVisibility(1);
    mState = 1;

    if (window != mpWindow) {
        PanelIface* old = mpWindow;
        if (window) window->mRef.AddRef();
        mpWindow = window;
        if (old) old->mRef.Release();
    }

    if (mpServer) {
        IServer* old = mpServer;
        mpServer = 0;
        EA::Messaging::RemoveHandler(old, mpHandler, mMsg, mPrio, mFlags);
    }
    mpServer = MessageServer();
    mpHandler = (IHandler*)static_cast<PanelHandlerBase*>(this);
    mMsg = 0x148803c;
    mPrio = 1;
    mFlags = 0;
    if (mpServer && mpHandler)
        mpServer->AddHandler(mpHandler, 0x7cc7f30);

    bool stateFive = (mpWindow->mMode == 5);
    SubB* sub = (SubB*)g_16c7aa4->mpSub74;
    void* scenario = (void*)sub->GetEffectContext();
    CtxKeys* keys = sub->mpKeys;

    if (cScenarioPlayProgressBar_IsReady()) {
        if (mpPropList) {
            PropertyList* old = mpPropList;
            mpPropList = 0;
            old->Release();
        }
        if (GetEditorPropertyList(scenario, &mpPropList)) {
            Property* prop = mpPropList->GetProperty(0x5888ef41);
            int value;
            if (prop->mType == 9 || prop->mType == 0x10) {
                if (prop->mFlags & 0x30)
                    value = prop->mValue.mpValue->mValue.mInt;
                else
                    value = prop->mValue.mInt;
            } else {
                value = g_15d1160.mValue.mInt;
            }
            if (!FUN_00eebfc0(mpPropList, &keys->f8) && value != FUN_00eec570()) {
                IWin* anim = mpLayout->FindWindowByID(0x7c79cc8, 1);
                mpSubA->SetAnimWindow(anim);
                IWin* slot = mpLayout->FindWindowByID(0x7c79f90, 1);
                float pos[3] = {1.0f, 1.0f, 1.0f};
                GetUpdater490()->BindSlotCreature(scenario, 0, pos, &g_13ec468, 0, slot);
                uint id1 = 0x058c965a + (stateFive ? -44 : 0);
                uint id2 = 0x07d88234 + (stateFive ? -643 : 0);
                GetUpdater490()->SetSlider(id2, id1, 0, 1);
                GetUpdater490()->SetSerializer();
            } else {
                if (mpPropList) {
                    PropertyList* old = mpPropList;
                    mpPropList = 0;
                    old->Release();
                }
            }
        }
    }

    FUN_00f15890();
    MessageServer()->Send(0x7e36032, mpWindow->mMode == 5, 0);
}

static inline cSPUIProgress* PanelOwner(PanelHandlerBase* h)
{
    return (cSPUIProgress*)((char*)h - 4);
}
// @ 0x00f18970
bool PanelHandlerBase::HandleMessage(uint msg, void* payload)
{    if (msg != 0x65ff54a)
        return false;
    MsgPayload* p = (MsgPayload*)payload;
    if (p->mKey10 != 0x40464100)
        return false;
    if (p->mKey18 != 0x3098258b)
        return false;

    Layout* layout = PanelOwner(this)->mpLayout;
    bool visible;
    if (!layout)
        visible = false;
    else
        visible = layout->IsVisible();

    PanelIface* window = PanelOwner(this)->mpWindow;
    cSPUIProgress* self = PanelOwner(this);
    if (window) window->mRef.AddRef();
    if (visible) self->StartNextAnimation();
    self->FUN_00f17ea0();
    self->FUN_00f13b10();
    if (visible) self->Show(window);
    if (window) window->mRef.Release();
    return false;
}
