// Slice s00b60110 -- App ArgScript command constructors/executors, the
// simulator setup command, and a couple of App mode key/cheat hooks.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// external helpers / globals
extern "C" void  operator_delete__(void* p);                                           // 0x00f47380
extern "C" void* operator_new(int size, const char* tag, int a, int b, int c, int d);  // 0x00f473a0

extern "C" int      FUN_01021080();   // 0x01021080 SP::cSPLivingUniverse::GetUniverseContext
extern "C" uint32_t FUN_00b5b800();   // 0x00b5b800 SP::GetCurrentGameMode
extern "C" void*    FUN_0067dd50();   // 0x0067dd50
extern "C" void*    FUN_0067ddb0();   // 0x0067ddb0
extern "C" void*    FUN_0067caa0();   // 0x0067caa0 SP::WindowManager
extern "C" void*    FUN_0067dd10();   // 0x0067dd10 SP::App
extern "C" void*    FUN_0067ddd0();   // 0x0067ddd0 EffectsManagerPtr
extern "C" void*    FUN_0067de40();   // 0x0067de40
extern "C" void*    FUN_00b3d300();   // 0x00b3d300 SP::NounManager
extern "C" void*    FUN_01021260();   // 0x01021260 GetActivePlanet
extern "C" void*    FUN_00b3d350();   // 0x00b3d350 SP::PlanetModel
extern "C" void*    FUN_01021300();   // 0x01021300 GetPlayerEmpire
extern "C" void*    FUN_0102f810();   // 0x0102f810 economy tuning singleton
extern "C" void*    FUN_01002bd0();   // 0x01002bd0 SP::SpaceGameGet
extern "C" void*    FUN_00cd40b0();   // 0x00cd40b0 SP::cTribeModeStrategy::Instance
extern "C" void*    FUN_00cf74c0();   // 0x00cf74c0 SP::cCivModeStrategy::Get

extern char        g_emptyString[];   // 0x01667bac eastl::gEmptyString16
extern const char  g_143d498[];       // 0x0143d498 "no"
extern const char  g_143d49c[];       // 0x0143d49c "yes"
extern const float g_0145c12c;        // 0x0145c12c 2000.0f

struct PlayerStateGlobal {
    char  pad00[0x18];
    void* m18;                        // +0x18
};
extern PlayerStateGlobal* g_p016c7aa4;   // 0x016c7aa4

// ---------------------------------------------------------------------------
// ArgScript command infrastructure.
namespace EA {
namespace ArgScript {

struct cArguments;
struct cIParser;

// 0xc8-byte argument spec; the parsed option bits land in mFlags (+0x70).
struct cArgumentSpec {
    char     mHead[0x6c];
    bool     mRespectHelp;   // +0x6c
    char     mPad6d[3];
    uint32_t mFlags;         // +0x70
    char     mTail[0xc8 - 0x74];

    // Kept POD so owners can run construction exactly where the original did
    // (after the command vtbl store) instead of in a mem-initializer list.
    void ctor(bool respectHelp);                      // 0x0083a9f0
    void dtor();                                      // 0x00405050
    void Parse(cArguments* args, cIParser* parser);   // 0x0083b9d0
    int  ConstructSpec(const char* desc, ...);        // 0x0083bcd0
};

// 0x10-byte command base (vptr/parser/refcount).
struct cCommandBase {
    void**    vtbl;      // +0x00
    cIParser* mParser;   // +0x04
    int       mRefCount; // +0x08
    int       mPad0c;    // +0x0c

    cCommandBase();             // 0x0083c800
    ~cCommandBase();            // 0x0083c750
};

void Output(cIParser* parser, const char* fmt, ...);  // 0x00841000

}  // namespace ArgScript
}  // namespace EA

// ---------------------------------------------------------------------------
// small helpers / shared object layouts
struct EString8 {
    char* begin;   // +0x00
    char* end;     // +0x04
    char* cap;     // +0x08
};

struct WString16 {
    wchar_t* begin;   // +0x00
    wchar_t* end;     // +0x04
    wchar_t* cap;     // +0x08
};

// eastl::fixed_string<wchar_t,16,1>
struct FixedWString16 {
    wchar_t* begin;       // +0x00
    wchar_t* end;         // +0x04
    wchar_t* cap;         // +0x08
    void*    mAllocator;  // +0x0c
    wchar_t* poolBegin;   // +0x10 (points at mBuffer when no overflow)
    wchar_t  mBuffer[16]; // +0x14

    FixedWString16(const wchar_t* src);   // 0x006962a0
};

namespace EA {
WString16* ConvertToString16(WString16* out, const char* src, int len);  // 0x0093c5a0
EString8*  ConvertToString8(EString8* out, const WString16* src);        // 0x0093c570
}  // namespace EA

extern const char* g_sEnglishTable[];   // 0x01569d50 (stride 2 pointers)
extern const char* g_sEnUsTable[];      // 0x01569e18 (stride 2 pointers)

// ref-counted effect object used by the style filter command
struct IEffect {
    virtual void v00();          // +0x00
    virtual void v04();          // +0x04 release
    virtual void v08(int arg);   // +0x08
    virtual void v0c(int arg);   // +0x0c
    virtual char v10();          // +0x10
};

struct AutoEffect {
    IEffect* mPtr;   // +0x00
};

struct IEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(uint32_t name, int zero, void* effect);   // +0x2c
};

// ---------------------------------------------------------------------------
// typed entry points used by the app-mode handlers (all direct thiscalls)
struct PauseFrame {
    void SetVisible(bool visible);   // 0x00812d80
    bool IsVisible();                // 0x00812d90
};

struct GameNounManager {
    void* GetPlayerCivilization();   // 0x00b25fb0
};

struct Civilization {
    void SetRadius(float radius, int mode);   // 0x00befd80
};

struct Player {
    void Spend(int amount);          // 0x00c31a00
};

struct EconomyTuning {
    int GetCheatMoneyAmount();       // 0x0102fe20
};

struct SpaceGame {
    void* f5180(int index);          // 0x01005180
};

struct PObj {
    void setF4(uint32_t* values);    // 0x00f33b50
};

struct CreatureCamera {
    void ToggleFreeCamera();         // 0x00d272e0
};

struct TribeStrategy {
    void apply();                    // 0x00cd0950
};

struct CivStrategy {
    void* getTarget();               // 0x00cf74f0
    void  apply();                   // 0x00cf2330
};

// ---------------------------------------------------------------------------
// App command classes.
namespace App {

struct cPauseUIVisibleCommand : EA::ArgScript::cCommandBase {
    EA::ArgScript::cArgumentSpec mSpec;   // +0x10

    cPauseUIVisibleCommand();                                            // 0x00b60350
    void FUN_00b603b0(EA::ArgScript::cArguments* args);                  // 0x00b603b0
};

struct cStyleFilter : EA::ArgScript::cCommandBase {
    EA::ArgScript::cArgumentSpec mSpec;   // +0x10
    AutoEffect mEffect;                   // +0xd8

    cStyleFilter();                                                      // 0x00b604a0
    void FUN_00b60550(EA::ArgScript::cArguments* args);                  // 0x00b60550
    void* FUN_00b60830(int flags);                                       // 0x00b60830
};

struct cAdventureLook : EA::ArgScript::cCommandBase {
    EA::ArgScript::cArgumentSpec mSpec;   // +0x10

    cAdventureLook();                                                    // 0x00b60870
    void FUN_00b60920(EA::ArgScript::cArguments* args);                  // 0x00b60920
};

}  // namespace App

// unnamed command bodies
struct UnnamedCommandA70 : EA::ArgScript::cCommandBase {
    EA::ArgScript::cArgumentSpec mSpec;   // +0x10
    void FUN_00b60a70(EA::ArgScript::cArguments* args);   // 0x00b60a70
};

struct SimulatorCommand {
    void FUN_00b60110(EA::ArgScript::cArguments* args);   // 0x00b60110
};

// ---------------------------------------------------------------------------
// constructor bodies
// @ 0x00b60350
App::cPauseUIVisibleCommand::cPauseUIVisibleCommand()
    : EA::ArgScript::cCommandBase()
{
    vtbl = (void**)0x01462e24;
    mSpec.ctor(true);
    mSpec.ConstructSpec(
        "sets or toggles whether the pause frame is drawn",
        "-show^ ", 0,
        "show the pause frame",
        "-hide^ ", 1,
        "hide the pause frame",
        "-toggle^ ", 2,
        "toggle visibility of the pause frame",
        0);
}

// @ 0x00b604a0
App::cStyleFilter::cStyleFilter()
    : EA::ArgScript::cCommandBase()
{
    vtbl = (void**)0x01462f2c;
    mSpec.ctor(true);
    mEffect.mPtr = 0;
    mSpec.ConstructSpec(
        "Applies a stylized look to Spore",
        "-filmnoir^ ", 0,
        "film noir style",
        "-oilpaint^ ", 1,
        "oil paint style",
        "-norainbows^ ", 2,
        "dark and gloomy style",
        "-nextgen^ ", 3,
        "next-gen style",
        "-microscope^ ", 4,
        "microscope style",
        "-none^ ", 5,
        "no styles",
        0);
}

// @ 0x00b60870
App::cAdventureLook::cAdventureLook()
    : EA::ArgScript::cCommandBase()
{
    vtbl = (void**)0x01463220;
    mSpec.ctor(true);
    mSpec.ConstructSpec(
        "Applies a stylized look to your Adventure! If used while editing an adventure, it gets saved with the adventure. Set Graphics Effects to Medium or High",
        "-filmnoir^ ", 0,
        "film noir style",
        "-eightbit^ ", 2,
        "old 8 bit game",
        "-sixteenbit^ ", 3,
        "old 16 bit game",
        "-watercolor^ ", 4,
        "render the adventure in watercolor",
        "-norainbows^ ", 1,
        "dark and gloomy style",
        "-sepia^ ", 5,
        "old sepia tone film",
        "-none^ ", 6,
        "no styles",
        0);
}

// ---------------------------------------------------------------------------
// pause UI visibility command
// @ 0x00b603b0
void App::cPauseUIVisibleCommand::FUN_00b603b0(EA::ArgScript::cArguments* args)
{
    mSpec.Parse(args, mParser);

    void* wm = FUN_0067caa0();
    void* raw = ((void*(__thiscall*)(void*))(((void***)wm)[0][4 / 4]))(wm);
    PauseFrame* frame = raw ? (PauseFrame*)((char*)raw - 4) : 0;

    if (mSpec.mFlags & 1) {
        frame->SetVisible(false);
    } else {
        uint32_t flags = *(volatile uint32_t*)&mSpec.mFlags;
        if ((flags >> 1) & 1)
            frame->SetVisible(true);
        else if ((flags >> 2) & 1)
            frame->SetVisible(!frame->IsVisible());
    }

    bool visible = frame->IsVisible();
    EA::ArgScript::Output(mParser, "pause ui visible: %s\n",
                          visible ? g_143d498 : g_143d49c);
}

// ---------------------------------------------------------------------------
// style filter command
// @ 0x00b60550
void App::cStyleFilter::FUN_00b60550(EA::ArgScript::cArguments* args)
{
    mSpec.Parse(args, mParser);

    uint32_t flags = mSpec.mFlags;

    if ((flags >> 4) & 1) {
        if (mEffect.mPtr && mEffect.mPtr->v10()) {
            mEffect.mPtr->v0c(1);
            IEffect* e = mEffect.mPtr;
            if (e) {
                mEffect.mPtr = 0;
                e->v04();
            }
        }
        IEffectsManager* mgr = (IEffectsManager*)FUN_0067ddd0();
        if (mEffect.mPtr) {
            IEffect* e = mEffect.mPtr;
            mEffect.mPtr = 0;
            e->v04();
        }
        mgr->v2c(0x6ef24821u, 0, &mEffect);
        mEffect.mPtr->v08(0);
        return;
    }

    if (FUN_00b5b800() == 0x01654c00u)
        return;

    if ((flags >> 5) & 1) {
        if (mEffect.mPtr) {
            mEffect.mPtr->v0c(1);
            IEffect* e = mEffect.mPtr;
            if (e) {
                mEffect.mPtr = 0;
                e->v04();
            }
        }
        return;
    }

    if (flags & 1) {
        if (mEffect.mPtr && mEffect.mPtr->v10()) {
            mEffect.mPtr->v0c(1);
            IEffect* e = mEffect.mPtr;
            if (e) {
                mEffect.mPtr = 0;
                e->v04();
            }
        }
        IEffectsManager* mgr = (IEffectsManager*)FUN_0067ddd0();
        if (mEffect.mPtr) {
            IEffect* e = mEffect.mPtr;
            mEffect.mPtr = 0;
            e->v04();
        }
        mgr->v2c(0x91e41ff3u, 0, &mEffect);
        mEffect.mPtr->v08(0);
        return;
    }

    if ((flags >> 1) & 1) {
        if (mEffect.mPtr && mEffect.mPtr->v10()) {
            mEffect.mPtr->v0c(1);
            IEffect* e = mEffect.mPtr;
            if (e) {
                mEffect.mPtr = 0;
                e->v04();
            }
        }
        IEffectsManager* mgr = (IEffectsManager*)FUN_0067ddd0();
        void* p = ((void*(__thiscall*)(AutoEffect*))0x00a16f40)(&mEffect);
        mgr->v2c(0x74a75629u, 0, p);
        mEffect.mPtr->v08(0);
        return;
    }

    if ((flags >> 2) & 1) {
        if (mEffect.mPtr && mEffect.mPtr->v10()) {
            mEffect.mPtr->v0c(1);
            IEffect* e = mEffect.mPtr;
            if (e) {
                mEffect.mPtr = 0;
                e->v04();
            }
        }
        IEffectsManager* mgr = (IEffectsManager*)FUN_0067ddd0();
        void* p = ((void*(__thiscall*)(AutoEffect*))0x00a16f40)(&mEffect);
        mgr->v2c(0x3e57e88du, 0, p);
        mEffect.mPtr->v08(0);
        return;
    }

    if ((flags >> 3) & 1) {
        if (mEffect.mPtr && mEffect.mPtr->v10()) {
            mEffect.mPtr->v0c(1);
            IEffect* e = mEffect.mPtr;
            if (e) {
                mEffect.mPtr = 0;
                e->v04();
            }
        }
        IEffectsManager* mgr = (IEffectsManager*)FUN_0067ddd0();
        void* p = ((void*(__thiscall*)(AutoEffect*))0x00a16f40)(&mEffect);
        mgr->v2c(0x92caed00u, 0, p);
        mEffect.mPtr->v08(0);
        return;
    }
}

// @ 0x00b60830
void* App::cStyleFilter::FUN_00b60830(int flags)
{
    // volatile store keeps the original store-then-load order in the dtor.
    *(void* volatile*)&vtbl = (void*)0x01462f2c;
    _ReadWriteBarrier();
    if (mEffect.mPtr)
        mEffect.mPtr->v04();
    mSpec.dtor();
    this->EA::ArgScript::cCommandBase::~cCommandBase();
    if (flags & 1)
        operator_delete__(this);
    return this;
}

// ---------------------------------------------------------------------------
// adventure look command
// @ 0x00b60920
void App::cAdventureLook::FUN_00b60920(EA::ArgScript::cArguments* args)
{
    mSpec.Parse(args, mParser);

    uint32_t values[3] = {0, 0, 0};
    PObj* target = (PObj*)g_p016c7aa4->m18;

    if (FUN_00b5b800() == 0x01654c10u) {
        uint32_t flags = mSpec.mFlags;
        if ((flags >> 6) & 1)
            values[0] = 0;
        else if (flags & 1)
            values[0] = 0x297afb05u;
        else if ((flags >> 1) & 1)
            values[0] = 0x3799e2d2u;
        else if ((flags >> 2) & 1)
            values[0] = 0xeada7b12u;
        else if ((flags >> 3) & 1)
            values[0] = 0xd5ceb45fu;
        else if ((flags >> 4) & 1)
            values[0] = 0xb826c751u;
        else if ((flags >> 5) & 1)
            values[0] = 0x1fcf4c87u;

        if (target)
            target->setF4(values);
    }
}

// ---------------------------------------------------------------------------
// unnamed command body: toggle free camera / related mode actions
// @ 0x00b60a70
void UnnamedCommandA70::FUN_00b60a70(EA::ArgScript::cArguments* args)
{
    mSpec.Parse(args, mParser);

    switch (FUN_00b5b800()) {
    case 0x01654c01u:
    case 0x01654c10u: {
        void* app = FUN_0067dd10();
        void* a = ((void*(__thiscall*)(void*))(((void***)app)[0][0x50 / 4]))(app);
        void* b = ((void*(__thiscall*)(void*))(((void***)a)[0][0x38 / 4]))(a);
        if (b) {
            void* cam = ((void*(__thiscall*)(void*, int))(((void***)b)[0][0x0c / 4]))(b, 0x2a7ecd2);
            if (cam)
                ((CreatureCamera*)cam)->ToggleFreeCamera();
        }
        break;
    }
    case 0x01654c02u: {
        if (FUN_00cd40b0()) {
            void* inst = FUN_00cd40b0();
            void* o = ((void*(__thiscall*)(void*))(((void***)inst)[0][0x70 / 4]))(inst);
            if (o) {
                inst = FUN_00cd40b0();
                o = ((void*(__thiscall*)(void*))(((void***)inst)[0][0x70 / 4]))(inst);
                ((TribeStrategy*)o)->apply();
            }
        }
        break;
    }
    case 0x01654c04u: {
        if (FUN_00cf74c0()) {
            CivStrategy* s = (CivStrategy*)FUN_00cf74c0();
            void* o = s->getTarget();
            if (o) {
                s = (CivStrategy*)FUN_00cf74c0();
                o = s->getTarget();
                ((CivStrategy*)o)->apply();
            }
        }
        break;
    }
    default:
        break;
    }
}

// ---------------------------------------------------------------------------
// simulator setup command
struct HkObject {
    void** vtbl;   // +0x00
};

struct RefCountedObject {
    void** vtbl;         // +0x00
    uint32_t m04;        // +0x04
    uint32_t mRefCount;  // +0x08
};

struct SimulatorRecord {
    int m00;   // +0x00
    int m04;   // +0x04
    int m08;   // +0x08
};

struct GonzagoSimulator {
    void**            vtbl;   // +0x00
    uint32_t          m04;    // +0x04
    float             m08;    // +0x08
    uint32_t          m0c;    // +0x0c
    HkObject*         m10;    // +0x10
    RefCountedObject* m14;    // +0x14
    EString8          m18;    // +0x18
    uint32_t          m24;    // +0x24
    uint32_t          m28;    // +0x28
};

// @ 0x00b60110
void SimulatorCommand::FUN_00b60110(EA::ArgScript::cArguments*)
{
    if (FUN_01021080() != 0)
        return;
    if (FUN_00b5b800() == 0x01654c00u)
        return;

    GonzagoSimulator* sim = (GonzagoSimulator*)operator_new(0x2c, "Simulator", 0, 0, 0, 0);
    if (sim) {
        sim->m04 = 0;
        sim->vtbl = (void**)0x01462d70;
        sim->m10 = 0;
        sim->m14 = 0;
        sim->m18.begin = g_emptyString;
        sim->m18.end = g_emptyString;
        sim->m18.cap = g_emptyString + 1;
        ((void(__thiscall*)(void*))sim->vtbl[1])(sim);
    } else {
        sim = 0;
    }

    void* mem = operator_new(0x20, "Simulator", 0, 0, 0, 0);
    HkObject* thing = mem ? ((HkObject*(__thiscall*)(void*))0x00760c00)(mem) : 0;
    if (thing)
        ((void(__thiscall*)(void*))thing->vtbl[0])(thing);

    void* sing = FUN_0067dd50();
    int count = ((int(__thiscall*)(void*))(((void***)sing)[0][0x68 / 4]))(sing);
    for (int i = 0; i < count; i++) {
        sing = FUN_0067dd50();
        SimulatorRecord* rec =
            (SimulatorRecord*)((void*(__thiscall*)(void*, int))(((void***)sing)[0][0x70 / 4]))(sing, i);
        int kind = rec->m04;
        if (kind == 7 || kind == 8 || kind == 10)
            ((void(__thiscall*)(void*, int, int, int))0x00760fd0)(thing, rec->m00, rec->m04, rec->m08);
    }

    void* planet = FUN_01021260();
    WString16* planetName = ((WString16*(__thiscall*)(void*))0x00c707e0)(planet);

    EString8 tmp;
    EA::ConvertToString8(&tmp, planetName);
    if (&tmp != &sim->m18)
        ((void(__thiscall*)(EString8*, char*, char*))0x00454cb0)(&sim->m18, tmp.begin, tmp.end);
    if ((int)(tmp.cap - tmp.begin) > 1 && tmp.begin)
        operator_delete__(tmp.begin);

    void* model = FUN_00b3d350();
    float value = ((float(__thiscall*)(void*))0x00b7e4d0)(model);
    sim->m08 = value;
    sim->m0c = 1;
    sim->m28 = 0;

    RefCountedObject* ref = sim->m14;
    if (ref) {
        int prev = _InterlockedExchangeAdd((volatile long*)&ref->mRefCount, -1);
        sim->m14 = 0;
        if (prev - 1 < 1)
            _InterlockedExchangeAdd((volatile long*)&ref->mRefCount, 1);
    }

    HkObject* old = sim->m10;
    if (thing != old) {
        if (thing)
            ((void(__thiscall*)(void*))thing->vtbl[0])(thing);
        sim->m10 = thing;
        if (old)
            ((void(__thiscall*)(void*))old->vtbl[1])(old);
    }

    void* mgr = FUN_0067ddb0();
    ((void(__thiscall*)(void*, void*, int))(((void***)mgr)[0][0x34 / 4]))(mgr, sim, 0x80);

    if (thing)
        ((void(__thiscall*)(void*))thing->vtbl[1])(thing);
    ((void(__thiscall*)(void*))sim->vtbl[2])(sim);
}

// ---------------------------------------------------------------------------
// App mode space key handler

// SP::IntVector: element storage pointer at +0xc; the cheat writes into the
// second dword of the element at +0x1c of that storage record.
struct IntVectorNode {
    char pad00[0x1c];
    int  m1c;                    // +0x1c
};
struct IntVector {
    char          pad00[0xc];
    IntVectorNode* m0c;          // +0x0c
    void resize(unsigned count);  // 0x007eb820
};

struct cAppModeSpace {
    void OnKeyDown(int key);   // 0x00b60bb0
};

// @ 0x00b60bb0
void cAppModeSpace::OnKeyDown(int)
{
    if (FUN_00b5b800() == 0x01654c04u) {
        GameNounManager* manager = (GameNounManager*)FUN_00b3d300();
        Civilization* civ = (Civilization*)manager->GetPlayerCivilization();
        if (civ)
            civ->SetRadius(g_0145c12c, 0);
        return;
    }

    if (FUN_00b5b800() == 0x01654c05u) {
        Player* player = (Player*)FUN_01021300();
        if (!player)
            return;
        EconomyTuning* tuning = (EconomyTuning*)FUN_0102f810();
        int money = tuning->GetCheatMoneyAmount();
        player->Spend(money);
        IntVector* vec = (IntVector*)((SpaceGame*)FUN_01002bd0())->f5180(11);
        vec->resize(8);
        vec->m0c->m1c = money;
    }
}

// ---------------------------------------------------------------------------
// texture cheat command
namespace {

struct cTextureCheat : EA::ArgScript::cCommandBase {
    EA::ArgScript::cArgumentSpec mSpec;   // +0x10
    bool mUseEnglish;                     // +0xd8
    char mPadD9[3];
    int  mIndex;                          // +0xdc

    void Execute(EA::ArgScript::cArguments* args);
};

}  // namespace

// @ 0x00b60c70
void cTextureCheat::Execute(EA::ArgScript::cArguments* args)
{
    mSpec.Parse(args, mParser);

    if (mUseEnglish) {
        WString16 text;
        EA::ConvertToString16(&text, g_sEnglishTable[mIndex * 2], -1);
        void* sys = FUN_0067de40();
        ((void(__thiscall*)(void*, WString16*))(((void***)sys)[0][0x18 / 4]))(sys, &text);
        if ((((int)(text.cap - text.begin)) & ~1) > 2 && text.begin)
            operator_delete__(text.begin);
    } else {
        WString16 text;
        EA::ConvertToString16(&text, g_sEnUsTable[mIndex * 2], -1);
        FixedWString16 fixed(text.begin);
        void* sys = FUN_0067de40();
        ((void(__thiscall*)(void*, FixedWString16*))(((void***)sys)[0][0x10 / 4]))(sys, &fixed);
        if ((((int)(fixed.cap - fixed.begin)) & ~1) > 2 && fixed.begin &&
            fixed.begin != fixed.poolBegin)
            operator_delete__(fixed.begin);
        if ((((int)(text.cap - text.begin)) & ~1) > 2 && text.begin)
            operator_delete__(text.begin);
    }
}
