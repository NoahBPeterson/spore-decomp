// Slice s00df3be0 -- cGalaxyGameEntryUIStateMachine::HandleEvent (0x00df3be0, 2032 bytes).
//
// Message handler of the galaxy game-entry UI: a big switch on the event ID. Most cases play/stop an
// effect (KillSetiEffects), run one state-machine step (SetLevel, random picks, asset load/edit/new,
// panel setup) and fall to the common tail UpdateNavigationControls().
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as SetupForGame; no /EHsc).
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct WStr;

struct WStr {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08
    WStr(const wchar_t* s, const void* tag);     // 0x0041df50
    ~WStr();                                     // 0x00933960
    WStr& operator=(const WStr& o);              // 0x0057cb60
    WStr& operator=(const wchar_t* s);           // 0x005c3d90
};

struct IWindow {
    PV2 PV
    virtual IWindow* FindChild(uint32_t id);     // +0x0c
    PV4 PV2
    virtual uint32_t IsVisible();                // +0x28
    PV4 PV
    virtual int GetIndex();                      // +0x40
    PV8 PV4 PV2
    virtual void SetFlag(int flag, bool v);  // +0x7c
};

class cSPUILayout { public:
    uint32_t pad[3];
    IWindow* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
};

struct IRefObj {
    PV
    virtual void v1();   // +0x04
    PV
    virtual void v3(int arg);   // +0x0c
};

struct Zero3 {
    uint32_t x, y, z;
    Zero3() { x = 0; y = 0; z = 0; }
};

struct GGE {
    uint8_t pad00[0x24];
    uint32_t* m24;                             // +0x24 (panel id table)
    uint8_t pad28[0x170];                      // +0x28 .. +0x197
    void* m198;
    IRefObj* m19c;
    void Unk_de5d00(uint32_t id, void* cb, uint32_t v, const Zero3& zeros, int a, int b, int c);   // 0x00de5d00
    void Unk_de86d0(int a, int b);                                                              // 0x00de86d0
};
extern GGE* gpGGE;   // 0x016a1344
void Unk_dde570_on(void* p);

struct cPanelThing { void Unk_bbac80(uint32_t v, int flag); };   // 0x00bbac80

struct cGameInfo {
    uint32_t m00;            // +0x00
    uint32_t pad04[7];       // +0x04 .. +0x1f
    WStr m20;                // +0x20
    uint32_t pad2c[0x19];    // +0x2c .. +0x8f
    uint32_t m90;            // +0x90
    uint32_t pad94[5];
    uint32_t mA8;            // +0xa8
    uint32_t padac;
    uint32_t mB0;            // +0xb0
    cPanelThing* Unk_de4610();                  // 0x00de4610
    cGameInfo& operator=(const WStr& s);        // 0x0057cb60 (name copy)
};

struct IAT {
    PV8
    virtual int GetState();   // +0x20
};
IAT* GetSystemAT();           // 0x00a206f0
int GetRecorderState();       // 0x00435e90
void KillSetiEffects(uint32_t id, int state);   // 0x00435ed0
extern const uint32_t kLevelWindowIDs[];        // 0x0147e7f4

static __forceinline int ATState()
{
    IAT* p = GetSystemAT();
    return p ? p->GetState() : 0;
}

struct DeadEnd { void Fn_dde570(); };   // thiscall, no args (0x00dde570)

struct IEventSource;
struct GalaxyEvent;

struct cGalaxyGameEntryUIStateMachine {
    uint32_t pad00[2];
    uint32_t mCallback;                        // +0x08 (sub-object, passed by address)
    uint32_t pad0c[7];
    cSPUILayout mLayout;                       // +0x28
    uint32_t pad34[0xf];
    uint8_t mb70;                              // +0x70
    uint8_t pad71[3];                          // +0x71 .. +0x73
    uint32_t m74;                              // +0x74
    uint8_t pad78[0x4a8];                      // +0x78 .. +0x51f
    uint32_t m520;                             // +0x520 (passed by address)
    uint8_t pad524[0xc4];
    uint32_t mCurrentButton;                   // +0x5e8
    uint8_t pad5ec[0x3c];
    cGameInfo* mpGameInfo;                     // +0x628

    void UpdateNavigationControls();           // 0x00def8c0
    void SetLevel(int level);                  // 0x00df2ea0
    void Unk_df2550();                         // 0x00df2550
    void Unk_deef20(uint32_t a, void* b, int c);   // 0x00deef20
    void PickRandomAssets(int a);              // 0x00df3ab0
    void Unk_df2660();                         // 0x00df2660
    bool Unk_dec540(uint32_t a);               // 0x00dec540
    void PickRandomVehicle();                  // 0x00df2d80
    void PickRandomBuilding();                 // 0x00df2d60
    void PickRandomCreature();                 // 0x00df2bb0
    void SetCurrentState(int s);               // 0x00df0670
    void MakeRandomName();                     // 0x00defc80
    void SetStateSummaryText(int a, uint32_t b, uint32_t c);   // 0x00defd10
    void SetupPanelA(uint32_t id);             // 0x00df2920
    void SetupPanelB(uint32_t id);             // 0x00df2770
    void Init(uint32_t id);                    // 0x00df32d0
    void EditExistingAsset(uint32_t id);       // 0x00ded410
    void Unk_deede0();                         // 0x00deede0
    void MakeNewAsset(uint32_t id);            // 0x00dec7c0
    void LoadAsset(uint32_t id);               // 0x00dec940

    void HandleEvent(uint32_t id);
    void SelectTheme(uint32_t theme);                  // 0x00defdd0
    bool FUN_00def7c0(WStr* str);                       // 0x00def7c0
    bool BeginNewGameFlow(uint32_t unused, GalaxyEvent* e);   // 0x00df43d0
};

// @ 0x00df3be0
void cGalaxyGameEntryUIStateMachine::HandleEvent(uint32_t id)
{
    switch (id) {
    case 0x5a725b4:
        KillSetiEffects(0x91be3241, ATState());
        MakeRandomName();
        SetStateSummaryText(4, 0x5b08740, mpGameInfo->m00);
        UpdateNavigationControls();
        return;
    case 0x54045e3: {
        mCurrentButton = 0x54045e3;
        if (mpGameInfo->mA8 == 5) {
            mLayout.FindWindowByID(0x5384881, true)->SetFlag(1, false);
            gpGGE->Unk_de5d00(0x9c5c0628, &mCallback, mpGameInfo->mB0, Zero3(), 0, 0, 0);
        } else {
            mLayout.FindWindowByID(0x5384881, true)->SetFlag(1, false);
            gpGGE->Unk_de5d00(kLevelWindowIDs[mpGameInfo->m90], &mCallback, mpGameInfo->mB0, Zero3(), 0, 0, 0);
        }
        UpdateNavigationControls();
        return;
    }
    case 0x5384d05:
        KillSetiEffects(0xed10ce15, GetRecorderState());
        Unk_df2550();
        UpdateNavigationControls();
        return;
    case 0x53f06e1:
        KillSetiEffects(0x8e82b51c, GetRecorderState());
        SetLevel(0);
        UpdateNavigationControls();
        return;
    case 0x53f06ee:
        KillSetiEffects(0x8e82b51c, GetRecorderState());
        SetLevel(1);
        UpdateNavigationControls();
        return;
    case 0x53f06f5:
        KillSetiEffects(0x8e82b51c, GetRecorderState());
        SetLevel(2);
        UpdateNavigationControls();
        return;
    case 0x53f06fc:
        KillSetiEffects(0x8e82b51c, GetRecorderState());
        SetLevel(4);
        UpdateNavigationControls();
        return;
    case 0x53f0707:
        KillSetiEffects(0x8e82b51c, GetRecorderState());
        SetLevel(5);
        UpdateNavigationControls();
        return;
    case 0x54045ce:
        mCurrentButton = 0x54045ce;
        Unk_deef20(mpGameInfo->mA8, &m520, 0);
        UpdateNavigationControls();
        return;
    case 0x5404617: {
        mCurrentButton = 0x5404617;
        mLayout.FindWindowByID(0x5384881, true)->SetFlag(1, false);
        gpGGE->Unk_de5d00(0x695cbb72, &mCallback, mpGameInfo->mB0, Zero3(), 0, 0, 0);
        UpdateNavigationControls();
        return;
    }
    case 0x5933fe0:
        KillSetiEffects(0xed10ce15, GetRecorderState());
        Unk_df2660();
        UpdateNavigationControls();
        return;
    case 0x59434c0:
    case 0x6451450:
        KillSetiEffects(0x91be3241, GetRecorderState());
        PickRandomAssets(1);
        UpdateNavigationControls();
        return;
    case 0x59434c1:
        KillSetiEffects(0x91be3241, GetRecorderState());
        if (!Unk_dec540(0x59461b0)) {
            if (mLayout.FindWindowByID(0x54045e3, true)->IsVisible() & 1)
                PickRandomVehicle();
        }
        if (!Unk_dec540(0x59461b2)) {
            if (mLayout.FindWindowByID(0x5404617, true)->IsVisible() & 1)
                PickRandomBuilding();
        }
        UpdateNavigationControls();
        return;
    case 0x59461b0:
    case 0x59461b1:
    case 0x59461b2:
        KillSetiEffects(0xa59524f9, GetRecorderState());
        UpdateNavigationControls();
        UpdateNavigationControls();
        return;
    case 0x5951103:
        KillSetiEffects(0xddd740f9, GetRecorderState());
        mb70 = 1;
        UpdateNavigationControls();
        return;
    case 0x595e0a8: {
        IRefObj* p = gpGGE->m19c;
        if (p) {
            p->v3(1);
            p = gpGGE->m19c;
            if (p) {
                gpGGE->m19c = 0;
                p->v1();
            }
        }
        KillSetiEffects(0xb7a63c50, GetRecorderState());
        void* q = gpGGE->m198;
        if (q)
            ((DeadEnd*)q)->Fn_dde570();
        SetCurrentState(0);
        gpGGE->Unk_de86d0(2, 0);
        UpdateNavigationControls();
        return;
    }
    case 0x6149007:
    case 0x6149008:
    case 0x6149009:
        KillSetiEffects(0x216a4ce, GetRecorderState());
        SetupPanelA(id);
        UpdateNavigationControls();
        return;
    case 0x614c680:
    case 0x614c681:
    case 0x614c682:
        KillSetiEffects(0x216a4ce, GetRecorderState());
        SetupPanelB(id);
        UpdateNavigationControls();
        return;
    case 0x6451451:
        KillSetiEffects(0x91be3241, GetRecorderState());
        if (!Unk_dec540(0x59461b1)) {
            if (mLayout.FindWindowByID(0x54045ce, true)->IsVisible() & 1)
                PickRandomCreature();
        }
        UpdateNavigationControls();
        return;
    case 0x6775e1f:
    case 0x6775e20:
    case 0x6775e21:
    case 0x6775e22:
    case 0x6775e23:
        KillSetiEffects(0xed10ce15, ATState());
        Init(id);
        UpdateNavigationControls();
        return;
    case 0x7d27876:
        KillSetiEffects(0x91be3241, GetRecorderState());
        Unk_deede0();
        UpdateNavigationControls();
        return;
    case 0x95964773:
    case 0x95964776:
    case 0x95964779:
        KillSetiEffects(0xe72fd2be, GetRecorderState());
        EditExistingAsset(id);
        UpdateNavigationControls();
        return;
    case 0x95964775:
    case 0x95964778:
    case 0x9596477b:
        KillSetiEffects(0xe72fd2be, GetRecorderState());
        MakeNewAsset(id);
        UpdateNavigationControls();
        return;
    case 0x95964774:
    case 0x95964777:
    case 0x9596477a:
        KillSetiEffects(0xe72fd2be, ATState());
        LoadAsset(id);
        UpdateNavigationControls();
        return;
    default:
        break;
    }
    UpdateNavigationControls();
}

// ---------------------------------------------------------------------------------------------------
// Event plumbing for the galaxy game-entry screen.
// ---------------------------------------------------------------------------------------------------
struct IEventSource {
    PV4 PV2 PV
    virtual uint32_t GetEventId();                  // +0x1c
};

struct GalaxyEvent {
    IEventSource* source;   // +0x00
    uint32_t field04;       // +0x04
    uint32_t type;          // +0x08
    uint32_t field0c;       // +0x0c
    uint32_t data;          // +0x10
};

// EA::Variant: 4 dwords of payload, then a word of flags and a word of type id.
struct Variant {
    uint32_t data[4];       // +0x00
    uint16_t flags;         // +0x10
    uint16_t type;          // +0x12
    Variant(const bool& b) : flags(0), type(0) { Store((bool*)&b); }
    void Store(bool* p);                        // 0x00422e20
    void Free(int a);                           // 0x0093db80
    ~Variant() { if (flags & 4) Free(0); }
};

struct IPrefs {
    PV4 PV
    virtual void SetProperty(uint32_t id, const Variant& v);   // +0x14
};
extern IPrefs* g_sAppPreferences;               // 0x015fd91c
void GetBoolProperty(IPrefs* p, uint32_t id, bool* out);   // 0x00407190
int GetSaveArea(uint32_t id);                              // 0x006b1f90
void SaveResource(void* prefs, int area, char flag);       // 0x006b1d50

struct IWinTextEdit {
    PV8 PV8 PV4 PV
    virtual const wchar_t* GetText();                          // +0x54
    PV2
    virtual void SetText(const wchar_t* text, int len);        // +0x60
};
IWinTextEdit* InterfaceCastTextEdit(IWindow* w);   // 0x005febd0

extern uint32_t g_uiEventMask[];                   // 0x016a1848

// Wrapper whose +0x08 field points at the game-entry state machine; it forwards UI messages to it.
struct cGalaxyGameEntryUIHost {
    uint8_t pad00[8];
    cGalaxyGameEntryUIStateMachine* mpState;              // +0x08
    void Unk_e00670(uint32_t id, uint32_t arg);           // 0x00e00670
    void HandleUIEvent(uint32_t id, uint32_t arg);        // 0x00df46d0
};

// @ 0x00df43d0
bool cGalaxyGameEntryUIStateMachine::BeginNewGameFlow(uint32_t unused, GalaxyEvent* e)
{
    if (e->type == 0x685a2b9) {
        KillSetiEffects(0xb0cc7e7, ATState());
        return false;
    }
    if (e->type == 0x287259f6) {
        uint32_t id = e->source->GetEventId();
        if (id == 0x53f0707) {
            IPrefs* prefs = g_sAppPreferences;
            bool isSet = false;
            GetBoolProperty(prefs, 0x80eaa93, &isSet);
            if (!isSet) {
                IWindow* w = mLayout.FindWindowByID(0x809b720, true);
                if (w)
                    w->SetFlag(1, false);
                isSet = true;
                {
                    Variant v(isSet);
                    prefs->SetProperty(0x80eaa93, v);
                }
                SaveResource(prefs, GetSaveArea(0x11ac192), 0);
            }
        }
        HandleEvent(id);
        return false;
    }
    if (e->type == 0x4f5527e8) {
        uint32_t id = e->source->GetEventId();
        if (id == 0x588ab05) {
            IWindow* w = mLayout.FindWindowByID(id, true);
            if (w) {
                IWindow* child = w->FindChild(0x2f5528d9);
                if (child) {
                    uint32_t& panel = gpGGE->m24[child->GetIndex()];
                    mpGameInfo->Unk_de4610()->Unk_bbac80(panel, 1);
                }
            }
        }
        return false;
    }
    if (e->type == 0x9b1552d8) {
        KillSetiEffects(0x1ac6d1af, ATState());
        uint32_t id = e->source->GetEventId();
        if (id == 0x5400fa5) {
            IWinTextEdit* te = InterfaceCastTextEdit(mLayout.FindWindowByID(id, true));
            bool tag;
            WStr text(te->GetText(), &tag);   // 2nd ctor argument is an unused tag
            if (FUN_00def7c0(&text))
                te->SetText(text.mpBegin, 0);
            if (mpGameInfo) {
                *mpGameInfo = text;
                SetStateSummaryText(4, 0x5b08740, mpGameInfo->m00);
            }
            UpdateNavigationControls();
            return false;
        }
        if (id == 0x7d275bb) {
            IWinTextEdit* te = InterfaceCastTextEdit(mLayout.FindWindowByID(id, true));
            mpGameInfo->m20 = te->GetText();
            UpdateNavigationControls();
            return false;
        }
        return false;
    }
    if (e->type == 0x4cab02d) {
        KillSetiEffects(0xddd740f9, GetRecorderState());
        SelectTheme(e->data);
        return false;
    }
    return false;
}

// @ 0x00df46d0
void cGalaxyGameEntryUIHost::HandleUIEvent(uint32_t id, uint32_t arg)
{
    if (mpState->mb70 == 0 &&
        ((g_uiEventMask[id >> 5] >> (id & 31)) & 1) == 0 &&
        (Unk_e00670(id, arg), id == 0x1b) &&
        mpState->m74 != 0) {
        cGalaxyGameEntryUIStateMachine* ui = mpState;
        IRefObj* p = gpGGE->m19c;
        if (p) {
            p->v3(1);
            p = gpGGE->m19c;
            if (p) {
                gpGGE->m19c = 0;
                p->v1();
            }
        }
        KillSetiEffects(0xb7a63c50, GetRecorderState());
        void* q = gpGGE->m198;
        if (q)
            ((DeadEnd*)q)->Fn_dde570();
        ui->SetCurrentState(0);
        gpGGE->Unk_de86d0(2, 0);
        ui->UpdateNavigationControls();
    }
}
