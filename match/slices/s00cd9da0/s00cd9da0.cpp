// Slice s00cd9da0: the tribe-mode global game setup and SP::cTribeModeStrategy::UpgradePlayerTribe.
// Targets: 00CD9DA0 FUN_00cd9da0                                  (global tribe setup, 1473 bytes)
//          00CDA370 SP::cTribeModeStrategy::UpgradePlayerTribe    (1948 bytes)
// The originals reach every subsystem through accessor + virtual pairs; the virtual receivers are
// modelled here as explicit vtable-slot calls so every call site of the original is represented.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "s00cd9da0.h"

// Dispatch helpers for the untyped vtable receivers (this in ecx; extra args on the stack).
static void  VC0(void* p, int slot)                       { ((void (__thiscall*)(void*))(((void**)*(void**)p)[slot/4]))(p); }
static void  VC1(void* p, int slot, int a)                { ((void (__thiscall*)(void*, int))(((void**)*(void**)p)[slot/4]))(p, a); }
static void  VC2(void* p, int slot, int a, int b)         { ((void (__thiscall*)(void*, int, int))(((void**)*(void**)p)[slot/4]))(p, a, b); }
static void  VC3(void* p, int slot, int a, int b, int c)  { ((void (__thiscall*)(void*, int, int, int))(((void**)*(void**)p)[slot/4]))(p, a, b, c); }
static void* VC0R(void* p, int slot)                      { return ((void* (__thiscall*)(void*))(((void**)*(void**)p)[slot/4]))(p); }
static void* VC1R(void* p, int slot, int a)               { return ((void* (__thiscall*)(void*, int))(((void**)*(void**)p)[slot/4]))(p, a); }

// ===========================================================================
// 0x00cd9da0  FUN_00cd9da0: one-time global tribe/planet/game-mode setup
// ===========================================================================
// @ 0x00cd9da0
void FUN_00cd9da0()
{
    cMotiveTuning_Init((cMotiveTuning*)0x01687A00, (int)0xF71FA311u);
    for (int i = 0; i < 4; ++i) {
        float v = FUN_00ce68f0(i);
        (void)v;
    }
    void* gtm = GameTimeManager();
    FUN_00b316d0();
    (void)gtm;

    // install the tribe trigger configs
    void* in = GameInputManager();
    VC3(in, 0x10, (int)"TriggerConfigTribeGame", 0, 1);
    const char* wasd = "TriggerConfigWASD";
    void* ml = FUN_0067de40();
    if (FUN_006ab760(ml, L"fr-fr") != 0)
        wasd = "TriggerConfigWASD_fr-fr";
    in = GameInputManager();
    VC3(in, 0x10, (int)wasd, 0, 0);

    unsigned name = FNVHash("Planet_Tribe", 0x811C9DC5u);
    VC1((void*)gTribeConfigName, 0x30, (int)(size_t)name);

    // create + configure the tribe planet model
    void* model = FUN_0067ddc0();
    if (model != 0) {
        VC1(model, 0x10, (int)gTribeConfigName);
        VC2(model, 0x18, (int)GonzagoModelWorld(), 3);
        void* mm = ModelManager();
        void* state = VC1R(mm, 0x1C, (int)0x3FBAE24);
        if (state != 0)
            VC2(model, 0x18, (int)state, 0);
        VC1(model, 0x1C, (int)FUN_0067de00(0x20007));
        VC1(model, 0x28, 1);
    }

    void* cam = GetCameraCtl();
    *(float*)((char*)cam + 0x380) = gTribeF0;
    *(int*)((char*)cam + 0x384) = 0x3E9;
    void* planet = PlanetModel();
    FUN_00b81720();
    (void)planet;

    void* gd = SetGameDataOwner2();
    if (gd != 0) {
        void* v = VC0R((char*)gd + 0x120, 0x2C);
        FUN_00b146a0(cam, 1, 1, v);
    }
    FUN_00b10760(cam, 0.0f, 0.0f, 0.0f);
    FUN_00b11870(cam, (int)0xCF0A771B);
    FUN_00b84a60(0, 0xd);
}

// ===========================================================================
// 0x00cda370  SP::cTribeModeStrategy::UpgradePlayerTribe
// ===========================================================================
// @ 0x00cda370
void cTribeModeStrategy::UpgradePlayerTribe()
{
    void* sphere = GetCurrentTerrainSphere();
    void* gd = SetGameDataOwner2();
    int tier = 0;
    if (gd != 0) {
        FUN_00a1ad10(gd);
        uint32_t arr = 0, n = 0;
        if (GetPropertyAsUint32Array(gd, gTribePropId, &arr, &n, 0) != 0) {
            int target = (int)*(float*)((char*)sphere + 0x10F0);
            int count = (int)n;
            tier = 0;
            for (int i = 0; i < count; ++i) {
                if ((unsigned)target >= ((unsigned*)arr)[i]) {
                    tier = i;
                    break;
                }
            }
        }
        FUN_00ff03b0(gd, tier);
    }

    if (sphere != 0) {
        if (gd == 0)
            return;
        FUN_00c79f00(sphere, (int)0x575E6E1, 1);
        FUN_00c79f00(sphere, (int)0x575E6E2, 1);
        FUN_00c79f00(sphere, (int)0x575E6E3, 1);
    }
}
