// Slice s010743a0 -- SP::cSPUISpace::Update (0x010743a0, 2054 bytes).
// Per-frame update of the space-game UI: toggles the universe-view windows, runs the sub-updaters,
// refreshes the four UFO flag bytes from the toggle buttons, drives the rollover/travel-line code per
// universe context and plays the queued mission sounds (a deque of 32-bit ids at +0x5f4).
// Retail layout differs from the 2008 PDB, so members are accessed through a local stub with padding.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned int uint;

struct Key3 { uint a, b, c; };

// Generic UTFWin window: QueryInterface at +0x0c, GetState at +0x20, SetVisible at +0x7c.
struct IWindow {
    virtual void s00(); virtual void s04(); virtual void s08();
    virtual IWindow* QueryInterface(uint id);                      // 0x0c
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual uint GetState();                                       // 0x20
    virtual void s24(); virtual void s28(); virtual void s2c(); virtual void s30(); virtual void s34();
    virtual void s38(); virtual void s3c(); virtual void s40(); virtual void s44(); virtual void s48();
    virtual void s4c(); virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
    virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6c(); virtual void s70();
    virtual void s74(); virtual void s78();
    virtual void SetVisible(int a, bool b);                        // 0x7c
};

struct GlobalUI {
    IWindow* FindWindowByID(uint id);                              // 0x00e012b0 (ret 4)
};

struct CommMgr { bool IsActive(); };                              // 0x00ae9390
struct InputMgr {                                                 // singleton 0x00b3d3f0
    bool Query(int a);                                            // 0x00e18c70 (ret 4)
    void Set(int a, int b);                                       // 0x00e18dd0 (ret 8)
};
struct WinMgr {                                                   // singleton 0x0067caa0
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
    virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6c();
    virtual void s70(); virtual void s74(); virtual void s78(); virtual void s7c();
    virtual void s80();
    virtual int GetCapture();                                     // 0x84
};
struct ModeInfo { char pad[0x2c]; int mMode; };
static __forceinline bool ModeIs12(ModeInfo* m) { return m->mMode == 1 || m->mMode == 2; }                   // singleton 0x00b3d4d0
struct SimSlot { virtual void s00(); virtual void s04(); virtual void s08(); virtual void Enable(int a); };  // 0x0c
struct SimSettings {                                              // singleton 0x00b3d470
    char pad[0x30]; SimSlot* mSlot30; SimSlot* mSlot34; int mField38;
};
struct StarSource {                                               // singleton 0x00b3d240
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30();
    virtual IWindow* GetStarRecord();                             // 0x34
};
struct Planet {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54();
    virtual bool IsSomething();                                   // 0x58
    char pad[0x13c - 4]; struct PlanetMode* mpMode;               // +0x13c
    struct Hlp00c71* GetHelper();                                 // 0x00c71e30
};
struct PlanetMode {
    int GetKind();                                                 // 0x00b8dab0
};
struct PlanetUI { int* mp; };
struct UIHelper { int pad[0x84 / 4]; int mField84; };
struct Star {                                                     // star record
    virtual void s00(); virtual void s04(); virtual void s08();
    virtual void* QueryInterface(uint id);                        // 0x0c
};
struct UFO {                                                      // cSPSimulatorPlayerUFO
    char pad[0x14]; uint8_t mFlag[4];                             // +0x14..+0x17
    Star* GetStarRecordUnderMouse();                              // 0x00fff8e0
};
struct TerrainSphere {
    bool Check(uint id);                                           // 0x00c772c0 (ret 4)
};
struct TerrainEditor {
    TerrainSphere* GetCurrentTerrainSphere();                      // 0x00f67d90
};
struct MissionMgr { void DebugDraw(); };                          // 0x00fee8d0
struct TimeMgr { void IncPauseGate(uint id); };                   // 0x00b32220 (ret 4)
struct Animator {
    void UpdateAnim();                                             // 0x007f63b0
};
struct Obj5a8 {
    void UpdateObj();                                              // 0x00e36540
};
struct Obj61c {
    void UpdateTimer(uint a);                                      // 0x00e30990 (ret 4)
};
struct CreateDummy { char pad[0x10]; uint8_t mFlag10; };
struct UISoundHelper { bool GetFlag(); };                         // 0x00a98020 (singleton 0x01015df0)
struct UIObj1046 { void Run(); };                                 // 0x01048f00
struct SoundMgr {                                                 // singleton 0x0067caf0
    void Play(Key3 key, const void* p, int a, float f0, float f1, float f2, void* cb, int b);  // 0x0067aaf0 (ret 0x28)
};
struct Hlp00c71 { char pad[0x84]; int mField84; };

// singleton getters
int      __cdecl SpaceGameGet();         // 0x01002bd0 (value unused)
int      __cdecl GetUniverseContext();   // 0x01021080
Planet*  __cdecl GetActivePlanet();      // 0x01021260
CommMgr* __cdecl CommManager();          // 0x00b3d4a0
InputMgr* __cdecl GetInputMgr();         // 0x00b3d3f0
SimSettings* __cdecl GetSimSettings();   // 0x00b3d470
StarSource* __cdecl GetStarSource();     // 0x00b3d240
ModeInfo* __cdecl GetModeInfo();         // 0x00b3d4d0
WinMgr* __cdecl WindowManager();         // 0x0067caa0
UFO* __cdecl GetUFOSimulator();          // 0x00ffbe50
MissionMgr* __cdecl GetMissionManager(); // 0x00feb9f0
TimeMgr* __cdecl GameTimeManager();      // 0x00b3d380
void* __cdecl NounManager();             // 0x00b3d300
SoundMgr* __cdecl GetSoundMgr();         // 0x0067caf0
UISoundHelper* __cdecl GetUISoundHelper();   // 0x01015df0
UIObj1046* __cdecl GetUIObj1046();       // 0x01046fc0
float    __cdecl GetElapsedSeconds();    // 0x00805080
void     __cdecl AudioGuiUpdate();       // 0x00c2e4e0 (empty in retail)
void     __cdecl operator_delete_arr(void* p);   // 0x00f47380

extern uint8_t gAudioDebugA;   // 0x016e06ec
extern uint8_t gAudioDebugB;   // 0x016e06ed
extern float   gNextSoundTime; // 0x016e2230
extern const float kSoundPeriod; // 0x0149c174 (0.77f)
extern const float kNegOne;      // 0x013eb1bc (-1.0f)
extern char gSoundPtrA[];        // 0x015b9274
extern char gSoundPtrB[];        // 0x015b9278
void SoundCb();                  // 0x010701e0

namespace SP {

struct cSPUISpace {
    char pad000[0x224];
    GlobalUI* mpGlobalUI;                // +0x224
    char pad228[0x568 - 0x228];
    Animator* mpAnimator;                // +0x568
    char pad56c[0x5a8 - 0x56c];
    Obj5a8* mp5a8;                       // +0x5a8
    char pad5ac[0x5d3 - 0x5ac];
    uint8_t mFlag5d3;                    // +0x5d3
    uint8_t mFlag5d4;                    // +0x5d4
    char pad5d5[0x5f4 - 0x5d5];
    // deque<uint32_t> of queued sound ids: start iterator then finish iterator (64 entries per node)
    uint* mStartCur;                     // +0x5f4
    uint* mStartFirst;                   // +0x5f8
    uint* mStartLast;                    // +0x5fc
    uint** mStartNode;                   // +0x600
    uint* mFinishCur;                    // +0x604
    uint* mFinishFirst;                  // +0x608
    uint* mFinishLast;                   // +0x60c
    uint** mFinishNode;                  // +0x610
    char pad614[0x618 - 0x614];
    int mMode618;                        // +0x618
    Obj61c* mp61c;                       // +0x61c

    void Update(uint dt);

    void UpdateGlobal();                 // 0x01065fe0
    void UpdateActiveToolCursor();       // 0x0106c930
    void UpdateTerraformingSlots();      // 0x01071d70
    void UpdateTerraformingBullseye();   // 0x01066f20
    void UpdateTravelLine(void* star);   // 0x0106cc70 (ret 4)
    void UpdatePlanetRollover(void* p);  // 0x0106ba00 (ret 4)
    void FUN_010678e0();                     // 0x010678e0
    void FUN_010679f0();                     // 0x010679f0
    void FUN_0106a970();                     // 0x0106a970
    void FUN_0106cab0();                     // 0x0106cab0
    void FUN_01072680();                     // 0x01072680
    void FUN_01069aa0();                     // 0x01069aa0
    void FUN_010691e0();                     // 0x010691e0
    void FUN_0106b630();                     // 0x0106b630
    void FUN_01065d20();                     // 0x01065d20

    __forceinline uint PopSound()
    {
        uint v = *mStartCur;
        uint* next = mStartCur + 1;
        if (next == mStartLast) {
            if (mStartFirst)
                operator_delete_arr(mStartFirst);
            ++mStartNode;
            mStartFirst = *mStartNode;
            mStartLast = mStartFirst + 0x40;
            next = mStartFirst;
        }
        mStartCur = next;
        return v;
    }
};

}  // namespace SP

// Planet-specific helpers declared after use (all thiscall members of stub classes)
extern void __cdecl ApplyToWindow(int value, IWindow* w);   // 0x00e2e6e0

static __forceinline IWindow* ToggleButton(GlobalUI* ui, uint id)
{
    IWindow* w = ui->FindWindowByID(id);
    return w ? w->QueryInterface(0x8ed27e7a) : 0;
}
static __forceinline void CopyToggle(GlobalUI* ui, uint id, int i)
{
    IWindow* q = ToggleButton(ui, id);
    uint st = q->GetState();
    GetUFOSimulator()->mFlag[i] = (uint8_t)((st >> 1) & 1);
}
static __forceinline void OrToggle(GlobalUI* ui, uint id, int i)
{
    IWindow* q = ToggleButton(ui, id);
    UFO* ufo = GetUFOSimulator();
    ufo->mFlag[i] |= (uint8_t)((q->GetState() >> 1) & 1);
}

// @ 0x010743a0
void SP::cSPUISpace::Update(uint dt)
{
    SpaceGameGet();
    int ctx = GetUniverseContext();

    IWindow* wA = mpGlobalUI->FindWindowByID(0x61f54b8);
    IWindow* wB = mpGlobalUI->FindWindowByID(0x6b821a8);
    if (wA && wB) {
        bool show = false;
        if (CommManager()->IsActive() || GetInputMgr()->Query(0))
            show = true;
        wA->SetVisible(1, show);
        wB->SetVisible(1, show);
    }

    FUN_010678e0();
    FUN_010679f0();
    FUN_0106a970();
    UpdateGlobal();
    UpdateActiveToolCursor();
    FUN_0106cab0();

    IWindow* wC = mpGlobalUI->FindWindowByID(0xb2001000);
    if (wC) {
        bool vis = (mFlag5d3 || mFlag5d4) ? true : false;
        wC->SetVisible(1, vis);
    }

    mp61c->UpdateTimer(dt);
    FUN_01072680();
    mpAnimator->UpdateAnim();
    mp5a8->UpdateObj();

    if (GetUniverseContext() != 2) {
        Planet* planet = GetActivePlanet();
        if (planet) {
            PlanetMode* mode = planet->mpMode;
            IWindow* w = mpGlobalUI->FindWindowByID(0x3fea475);
            bool show;
            if (mode->GetKind() == 5 && !planet->IsSomething()) {
                ApplyToWindow(planet->GetHelper()->mField84, w);
                show = true;
            } else {
                show = false;
            }
            w->SetVisible(1, show);
        }
    }

    if (ctx == 0) {
        UpdateTerraformingSlots();
        UpdateTerraformingBullseye();
        FUN_01069aa0();
    } else if (ctx != 1) {
        mpGlobalUI->FindWindowByID(0x65680f8)->SetVisible(1, false);
    } else {
        FUN_01069aa0();
    }

    Star* star = 0;
    if (GetUniverseContext() == 2) {
        star = GetUFOSimulator()->GetStarRecordUnderMouse();
    } else {
        GetSimSettings()->mSlot30->Enable(1);
        GetSimSettings()->mField38 = 0;
        GetSimSettings()->mSlot34->Enable(1);
    }
    if (!star) {
        star = (Star*)GetStarSource()->GetStarRecord();
        GetSimSettings()->mSlot30->Enable(1);
        GetSimSettings()->mField38 = 0;
    }

    // Copy the toggle buttons' bit 1 into the four UFO flag bytes, then OR in the second set.
    CopyToggle(mpGlobalUI, 0x4cab570, 0);
    CopyToggle(mpGlobalUI, 0x4cab571, 1);
    CopyToggle(mpGlobalUI, 0x4cab56e, 2);
    CopyToggle(mpGlobalUI, 0x4cab56f, 3);
    OrToggle(mpGlobalUI, 0x5cab570, 0);
    OrToggle(mpGlobalUI, 0x5cab571, 1);
    OrToggle(mpGlobalUI, 0x5cab56e, 2);
    OrToggle(mpGlobalUI, 0x5cab56f, 3);

    switch (GetUniverseContext()) {
    case 0: {
        FUN_010691e0();
        IWindow* w = mpGlobalUI->FindWindowByID(0x2c38ab9);
        if (w)
            w->SetVisible(1, GetUISoundHelper()->GetFlag());
        break;
    }
    case 1:
        GetUIObj1046()->Run();
        UpdateTravelLine(star);
        if (star)
            UpdatePlanetRollover(star->QueryInterface(0x3275872));
        else
            UpdatePlanetRollover(0);
        break;
    case 2:
        UpdateTravelLine(star);
        GetUIObj1046()->Run();
        break;
    }

    GetMissionManager()->DebugDraw();

    if (gAudioDebugA || gAudioDebugB)
        AudioGuiUpdate();

    if (gNextSoundTime < GetElapsedSeconds())
        gNextSoundTime = GetElapsedSeconds() + kSoundPeriod;

    bool playedSpecial;
    if (CommManager()->IsActive() || GetInputMgr()->Query(0) || WindowManager()->GetCapture() != 0
        || ModeIs12(GetModeInfo()))
        playedSpecial = true;
    else
        playedSpecial = false;

    FUN_0106b630();

    if (mStartCur != mFinishCur /* queue not empty */ && !playedSpecial) {
        GameTimeManager()->IncPauseGate(0x4bf38a7);
        int n = ((mFinishNode - mStartNode) << 6) + (int)(mFinishCur - mFinishFirst) + (int)(mStartLast - mStartCur) - 0x41;
        for (; n > 0; --n) {
            uint id = PopSound();
            if (id == 0x3826c46f || id == 0xa9c3987b)
                playedSpecial = true;
            Key3 k = { id, 0xb1b104, 0x3629f036 };
            GetSoundMgr()->Play(k, 0, 0, kNegOne, kNegOne, 0.0f, (void*)SoundCb, 0);
        }
        uint id = PopSound();
        const void* p = (id == 0x3826c46f || id == 0xa9c3987b || playedSpecial) ? gSoundPtrB : gSoundPtrA;
        Key3 k = { id, 0xb1b104, 0x3629f036 };
        GetSoundMgr()->Play(k, p, 0, kNegOne, kNegOne, 0.0f, (void*)SoundCb, 0);
    }

    if (mMode618 == 4) {
        if (GetInputMgr()->Query(0)) {
            TerrainSphere* t = ((TerrainEditor*)NounManager())->GetCurrentTerrainSphere();
            if (t && !t->Check(0x65e5039)) {
                GetInputMgr()->Set(-0xc, 0);
                return;
            }
        } else {
            TerrainSphere* t = ((TerrainEditor*)NounManager())->GetCurrentTerrainSphere();
            if (!t || t->Check(0x65e5039))
                FUN_01065d20();
            else
                GetInputMgr()->Set(-0xc, 0);
        }
    }
}
