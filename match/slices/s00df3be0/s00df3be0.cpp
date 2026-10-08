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

struct IWindow {
    PV8 PV2
    virtual uint32_t IsVisible();                // +0x28
    PV8 PV8 PV4
    virtual void SetFlag(int flag, bool v);  // +0x7c
};

struct cSPUILayout {
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
    uint8_t pad00[0x198];
    void* m198;
    IRefObj* m19c;
    void Unk_de5d00(uint32_t id, void* cb, uint32_t v, const Zero3& zeros, int a, int b, int c);   // 0x00de5d00
    void Unk_de86d0(int a, int b);                                                              // 0x00de86d0
};
extern GGE* gpGGE;   // 0x016a1344
void Unk_dde570_on(void* p);

struct cGameInfo {
    uint32_t m00;            // +0x00
    uint32_t pad04[0x23];
    uint32_t m90;            // +0x90
    uint32_t pad94[5];
    uint32_t mA8;            // +0xa8
    uint32_t padac;
    uint32_t mB0;            // +0xb0
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

struct cGalaxyGameEntryUIStateMachine {
    uint32_t pad00[2];
    uint32_t mCallback;                        // +0x08 (sub-object, passed by address)
    uint32_t pad0c[7];
    cSPUILayout mLayout;                       // +0x28
    uint32_t pad34[0xf];
    uint8_t mb70;                              // +0x70
    uint8_t pad71[0x4af];
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
