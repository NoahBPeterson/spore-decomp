// 0x00f10030 (FUN_00f10030): thiscall, one bool parameter (ret 4). Builds the on-screen HUD pieces
// of a creature/scenario-play display strategy object: the "PosseBar" UI/Posse widget (+0x60),
// the global UI layout owner (+0x5c), the social rainbow (+0x64), the scenario progress bar (+0x68),
// two screen effects (+0x140, +0x144), a card UI (+0x148) and the scenario reward UI (+0x12c); it registers
// the IWinProc subobject (+0x38) on a table of windows and the IMessageListener subobject (+0x3c) on the
// message server, then shows/hides windows from game-state flags.
//
// The bool parameter is reused as a local twice (a store into the parameter's stack slot, read back
// later by pushes as a dword; VC trusts a stack bool to be a normalized dword).
// Flags: /O2 /MD /Gy /GS- /TP (no /EHsc and no /GS cookie: neither frame exists in the original).

#include "types.h"

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define P1 virtual void CAT(pad_, __COUNTER__)();
#define P2 P1 P1
#define P4 P2 P2
#define P8 P4 P4
#define P16 P8 P8
#define P32 P16 P16

// ---- allocation helpers (cdecl) ----
void* EAAlloc(int size, int align, const char* name, void* allocator);   // 0x009512d0
void* GetEAAllocator();                                                  // 0x009512c0
void* AllocSim(size_t size, const char* name, int a, int b, int c, int d);   // 0x00f473a0

inline void* operator new(size_t size, int align, const char* name)
{
    return EAAlloc((int)size, align, name, GetEAAllocator());
}
inline void* operator new(size_t size, const char* name, int a, int b, int c, int d)
{
    return AllocSim(size, name, a, b, c, d);
}
inline void operator delete(void*, int, const char*) {}
inline void operator delete(void*, const char*, int, int, int, int) {}

struct IWinProc { virtual void wp0(); };
struct IMessageListener { virtual void ml0(); };
struct HudBase { virtual void hb0(); char padHb[0x34]; };   // +0x00 .. 0x37

// ---- windows (vtable +0x7c SetState, +0x104 AddWinProc) ----
struct Window {
    P16 P8 P4 P2 P1                       // slots 0..30
    virtual void SetState(int which, bool value);  // +0x7c
    P32 P1                                // slots 32..64
    virtual void AddWinProc(IWinProc* pProc);      // +0x104
};

struct Layout {
    Window* FindWindowByID(uint32_t id, int flag);   // 0x008105b0 (ret 8)
};

struct GlobalUI {
    GlobalUI();                                       // 0x00e03ab0
    char body[0x68 - 4];
    P2
    virtual void Load(const void* pData);             // +0x08
    Window* FindWindowByID(uint32_t id);              // 0x00e012b0 (ret 4)
    Layout* GetLayout();                              // 0x0093b6c0 (mov eax,[ecx+8])
};

struct RefObj {
    virtual int AddRef();
    virtual int Release();
};

template<typename T> inline void AssignRef(T*& slot, T* p)
{
    T* old = slot;
    if (p != old) {
        if (p) p->AddRef();
        slot = p;
        if (old) old->Release();
    }
}

struct cString {
    char pad[0x14];
    cString(uint32_t tableID, uint32_t instanceID, int flags);   // 0x006b5770 (ret 0xc)
    ~cString();                                                  // 0x006b5240
    const wchar_t* GetText();                                    // 0x006b55c0
};

struct Posse : RefObj {
    Posse();                                                     // 0x00e25710
    char body[0x20c - 4];
    P16 P8 P4 P2                                                 // slots 2..31
    virtual bool Create(const wchar_t* name, uint32_t id);       // +0x80
    P2 P1                                                        // slots 33..35
    virtual void SetRange(float a, float b, int c, int d);       // +0x90
    P8 P1                                                        // slots 37..45
    virtual void SetText(const wchar_t* text);                   // +0xb8
    P1                                                           // slot 47
    virtual void SetFlag(int v);                                 // +0xc0
};

struct Item;
struct ItemInfo { char pad[0x192]; bool bFlag; };
struct Item {
    ItemInfo* GetInfo();                                         // 0x00c04590 (mov eax,[ecx+0x1674])
};
struct ItemVec { Item** mpBegin; Item** mpEnd; };
struct NounManager {
    ItemVec* GetItemID();                                        // 0x00b1f9c0 (lea eax,[ecx+0x5c])
    struct Avatar* GetAvatar();                                  // 0x00b1fdb0 (mov eax,[ecx+0x54])
};
struct AvatarFlags { bool Get();                                 // 0x00bfc480 (mov al,[ecx+0x80])
};
struct Avatar { char pad[0x5a8]; AvatarFlags flags; };

struct Rainbow : RefObj {
    Rainbow();                                                   // 0x00e330c0
    char body[0x200 - 4];
    void Init();                                                 // 0x00e32de0
    void Setup(int v);                                           // 0x00e31a10 (this+0xc, jmp 0x810590)
};
struct ProgressBar : RefObj {
    ProgressBar();                                               // 0x00f18eb0
    char body[0x68 - 4];
    void SetWindow(Window* pWindow);                             // 0x00f18a50 (ret 4)
};
struct TimerBar { void Init(); };                                // 0x00d2bac0
struct IVisualEffect : RefObj {};
struct EffectsManager {
    P8 P2 P1                                                     // slots 0..10
    virtual void Create(uint32_t id, int flags, IVisualEffect** ppOut);   // +0x2c
};
struct MessageServer {
    P8
    virtual void AddListener(IMessageListener* pListener, uint32_t msgID);   // +0x20
};
struct CardUI : RefObj {
    CardUI();                                                    // 0x00e14810
    char body[0xf8 - 4];
    void Setup(int v);                                           // 0x00e15780 (ret 4)
    Window* FindWindowByID(uint32_t id);                         // 0x00e13390 (ret 4)
    void Refresh();                                              // 0x00e14900
};
struct RewardUI : RefObj {
    RewardUI();                                                  // 0x00f138f0
    char body[0xf8 - 4];
    void Start();                                                // 0x00f13b10
};
struct Cursor {
    void Reset(int a, int b);                                    // 0x00d2bef0 (ret 8)
    int mf0, mf4, mf8, mfC;
};
struct Range {
    void Set(int a, int b);                                      // 0x00a24480 (ret 8)
    int mf0, mf4, mf8, mfC;
};
struct HudHost {
    char pad[0xd0];
    int mValueD0;
    int pad2;
    struct Panel* mpPanelD8;
};
struct Panel { void Show(Layout* pLayout); };                    // 0x00f04d10 (ret 4)

NounManager* GetNounManager();            // 0x00b3d300
MessageServer* GetMessageServer();        // 0x0067dcc0
EffectsManager* GetEffectsManager();      // 0x0067ddd0
void VerbTray_RegisterButtons(IWinProc* pProc);   // 0x00d49b60 (cdecl)

extern Cursor gCursor_016c8050;           // 0x016c8050 (+4 = 0x016c8054, +8 = 0x016c8058, +0xc = 0x016c805c)
extern HudHost* gpHudHost_016c7aa4;       // 0x016c7aa4
extern const unsigned char kLoadData_015ad6c0[];   // 0x015ad6c0
extern const uint32_t kWinTable1_0148bdd4[7];      // 0x0148bdd4
extern const uint32_t kCardTable_0148bd98[8];      // 0x0148bd98
extern const float kRangeMax_01486ebc;             // 0x01486ebc (250.0f)

class CreatureHud : public HudBase, public IWinProc, public IMessageListener {
public:
    void Init(bool bParam);                   // @ 0x00f10030
    void AddRestrictedItem(Item* pItem);      // 0x00f0f0a0 (ret 4)
    void Func_f0e380(bool b);                 // 0x00f0e380 (ret 4)
    void Func_f0fbc0();                       // 0x00f0fbc0

    char pad40[0x5c - 0x40];
    GlobalUI* mpGlobalUI;                     // +0x5c
    Posse* mpPosse;                           // +0x60
    Rainbow* mpRainbow;                       // +0x64
    ProgressBar* mpProgressBar;               // +0x68
    char pad6c[0xb0 - 0x6c];
    TimerBar mTimerBar;                       // +0xb0
    char padb4[0x12c - 0xb4];
    RewardUI* mpRewardUI;                     // +0x12c
    char pad130[0x140 - 0x130];
    IVisualEffect* mpEffect140;               // +0x140
    IVisualEffect* mpEffect144;               // +0x144
    CardUI* mpCard;                           // +0x148
    Range mRange14c;                          // +0x14c (+0x150, +0x154, +0x158)
};

// @ 0x00f10030
void CreatureHud::Init(bool bParam)
{
    mpPosse = new(4, "UI/Posse") Posse();
    if (!mpPosse->Create(L"PosseBar", 0x40464100)) {
        mpPosse = 0;
    } else {
        cString text(0xefdb68ec, 0x760b242, 0);
        mpPosse->SetText(text.GetText());
        mpPosse->SetRange(0.0f, kRangeMax_01486ebc, 0, 0);
        mpPosse->SetFlag(0);
        ItemVec* pItems = GetNounManager()->GetItemID();
        Item** it = pItems->mpBegin;
        Item** itEnd = pItems->mpEnd;
        for (; it != itEnd; ++it) {
            Item* pItem = *it;
            if (!pItem->GetInfo() || !pItem->GetInfo()->bFlag)
                AddRestrictedItem(pItem);
        }
    }
    mpGlobalUI = new("Simulator", 0, 0, 0, 0) GlobalUI();
    mpGlobalUI->Load(kLoadData_015ad6c0);
    for (uint32_t i = 0; i < 7; ++i) {
        Window* w = mpGlobalUI->FindWindowByID(kWinTable1_0148bdd4[i]);
        if (w) w->AddWinProc((IWinProc*)this);
    }
    Window* w;
    w = mpGlobalUI->FindWindowByID(0x7104132);
    if (w) w->AddWinProc((IWinProc*)this);
    w = mpGlobalUI->FindWindowByID(0x7104130);
    if (w) w->AddWinProc((IWinProc*)this);
    IWinProc* pWinProc = (IWinProc*)this;
    VerbTray_RegisterButtons(pWinProc);
    IMessageListener* pListener = (IMessageListener*)this;
    GetMessageServer()->AddListener(pListener, 0x14051500);
    gCursor_016c8050.Reset(gCursor_016c8050.mf4, gCursor_016c8050.mf8);
    gCursor_016c8050.mfC = 0;
    Func_f0e380(bParam);

    AssignRef(mpRainbow, new(4, "cUISocialRainbow") Rainbow());
    mpRainbow->Init();
    mpRainbow->Setup(0);

    AssignRef(mpProgressBar, new("UI/cScenarioPlayProgressBar", 0, 0, 0, 0) ProgressBar());
    ProgressBar* pBar = mpProgressBar;
    pBar->SetWindow(mpGlobalUI->GetLayout()->FindWindowByID(0x760c730, 1));
    mTimerBar.Init();
    w = mpGlobalUI->FindWindowByID(0x7e1aea8);
    if (w) w->SetState(1, 0);

    EffectsManager* pEffects = GetEffectsManager();
    if (mpEffect140) {
        IVisualEffect* pOld = mpEffect140;
        mpEffect140 = 0;
        pOld->Release();
    }
    pEffects->Create(0x36099acf, 0, &mpEffect140);
    pEffects = GetEffectsManager();
    if (mpEffect144) {
        IVisualEffect* pOld = mpEffect144;
        mpEffect144 = 0;
        pOld->Release();
    }
    pEffects->Create(0xaaa2ac3c, 0, &mpEffect144);

    Range* pRange = &mRange14c;
    pRange->Set(pRange->mf4, pRange->mf8);
    pRange->mfC = 0;

    AssignRef(mpCard, new("UI", 0, 0, 0, 0) CardUI());
    mpCard->Setup(0);
    for (uint32_t i = 0; i < 8; ++i) {
        Window* c = mpCard->FindWindowByID(kCardTable_0148bd98[i]);
        if (c) c->AddWinProc(pWinProc);
    }
    bParam = gpHudHost_016c7aa4->mValueD0 == 0;
    Window* c = mpCard->FindWindowByID(0x72830b2);
    if (c) {
        c->SetState(1, bParam);
        if (bParam && gpHudHost_016c7aa4->mValueD0 == 0)
            mpCard->Refresh();
    }
    w = mpGlobalUI->FindWindowByID(0x7e1f090);
    if (w) w->SetState(2, bParam);
    w = mpGlobalUI->FindWindowByID(0x7e85fd3);
    if (w) w->SetState(1, !bParam);
    Func_f0fbc0();
    w = mpGlobalUI->FindWindowByID(0x74b5ee0);
    if (w) w->SetState(1, bParam);
    if (bParam) {
        Panel* pPanel = gpHudHost_016c7aa4->mpPanelD8;
        pPanel->Show(mpGlobalUI->GetLayout());
    }

    AssignRef(mpRewardUI, new("Simulator/cScenarioRewardUI", 0, 0, 0, 0) RewardUI());
    mpRewardUI->Start();

    Avatar* pAvatar = GetNounManager()->GetAvatar();
    if (pAvatar) {
        bParam = pAvatar->flags.Get();
        w = mpGlobalUI->FindWindowByID(0xb698347a);
        if (w) w->SetState(1, bParam);
        w = mpGlobalUI->FindWindowByID(0x18ac46e);
        if (w) w->SetState(1, !bParam);
        w = mpGlobalUI->FindWindowByID(0x7d8ee20);
        if (w) w->SetState(1, !bParam);
        w = mpGlobalUI->FindWindowByID(0x4d039a8);
        if (w) w->SetState(1, !bParam);
        w = mpGlobalUI->FindWindowByID(0x685a85e);
        if (w) w->SetState(2, !bParam);
    }
}
