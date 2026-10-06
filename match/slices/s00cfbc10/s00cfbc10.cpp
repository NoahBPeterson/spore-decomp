// @ 0x00cfbc10   SP::cCivModeStrategy::ContinueLoading  (5644 bytes)
//
// __thiscall.  One step of the Civilization-mode loading state machine.  `this+0xb4` is the
// state; the function switches on it (states 0..9) and advances the mode, driving the app
// (PlanetModel/city/UI/minimap) through loading.  `this+0xb8`/`this+0xbc` are the two pending
// mode/state words captured at entry (the cached `cIAppMode` and universe hand-off).
//
// The body is a huge /O2 switch over the state word; every arm issues a sequence of engine
// calls (loaded through the IAT / relative calls, invisible to byte-exact matching).
//
// Filed PARTIAL: the switch skeleton, the state transitions and the recovered call sequence
// are here; the many inlined EASTL/Havok sequences and the second `this`-subobject accesses
// Ghidra renders against this[1] are represented at the call level, not reproduced byte-exact.

#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

struct IRefCounted { virtual void _vf0(); virtual void Release(); };

// Minimal controller prefix; only the fields the states touch are named.
struct cCivModeStrategy {
    IRefCounted* vftable;             // +0x00
    char pad04[0xb4 - 4];
    int  mState;                      // +0xb4
    int* mpAppMode;                   // +0xb8   (cached cIAppMode)
    char padbc[0xc0 - 0xbc];
    int* mpUniverse;                  // +0xbc/0xc0 area (second mode word)

    void ContinueLoading(int param_2);
};

// ---- engine entry points (all masked relocations) ----
extern "C" void* PlanetModel();
extern "C" void  sInitMinimap(u32, u32, u32);
extern "C" void  FUN_00cf71d0(void*);
extern "C" void  FUN_00cf8560();
extern "C" int   FUN_00b26930();
extern "C" void  FUN_00ae3300();
extern "C" void  FUN_00cfea20();
extern "C" void* cSPLivingUniverse__GetActivePlanet();
extern "C" void* PropertyManager();
extern "C" int   FUN_00c708f0();
extern "C" void* FUN_00c70930();
extern "C" void* QuaternionFromDirections(void* out, void* a, void* b);
extern "C" void* FUN_007dcb00(void* out, void* in);
extern "C" void  FUN_00bf55d0();
extern "C" void* NounManager();
extern "C" void  FUN_00b93960();
extern "C" void* FUN_00b1f9d0();
extern "C" void  FUN_00bf8170(void*,u32,u32,u32);
extern "C" void* cTerrainEditor__GetCurrentTerrainSphere(void*);
extern "C" char  cPlanet__IsSpeciesScanned(void*);
extern "C" void  FUN_00c73cb0(void*);
extern "C" void* FUN_00ba4520(void*);
extern "C" void  FUN_00ba57f0(void*, int);
extern "C" void* FUN_00b25f40(void*);
extern "C" void  FUN_00ba5a60(void*, int);
extern "C" void  FUN_00c73cd0(void*);
extern "C" void* FUN_00c735e0(void*);
extern "C" void  InitCityCivModeFromLaunchScreen();
extern "C" void  FUN_00675250(u32,u32,u32);
extern "C" void  FUN_00676ed0(u32,u32,u32);
extern "C" void  FUN_00b22650(u32);
extern "C" void* cGameNounManager__GetPlayerTribe(void*);
extern "C" void* cGameNounManager__GetPlayerCivilization(void*);
extern "C" int   FUN_00b2fa60();
extern "C" void  FUN_00572660(void*);
extern "C" void* FUN_00acd9d0();
extern "C" void  FUN_00ba95a0(void*);
extern "C" void  cGameNounManager__RemoveNoun(void*, void*);
extern "C" void  FUN_00b969e0();
extern "C" void  FUN_00ae3d70();
extern "C" void* EA__RefCountTemplate_int__Release(const char*, u32, int);
extern "C" void* FUN_0067ddc0();
extern "C" void* GonzagoModelWorld();
extern "C" void* ModelManager();
extern "C" void* FUN_0067de00(int);
extern "C" void  TerraformingManager(int);
extern "C" void  FUN_00bc08d0(u32);
extern "C" void  FUN_00b87dc0();
extern "C" void* FUN_00b993c0(int);
extern "C" int   FUN_00b3d280();
extern "C" void* FUN_00b25c30();
extern "C" void  FUN_00b146a0(void*,u32,u32);
extern "C" void  FUN_00b3d280_v(int*);
extern "C" void* cCity__GetCityHall(void*);
extern "C" void* FUN_004a9b40(void*, void*);
extern "C" void* rw__math__fpu__QuaternionFromMatrix33(void*, void*, int);
extern "C" void  FUN_00b12dd0(void*, void*, u32);
extern "C" void  FUN_00b13b50();
extern "C" void* GameInputManager();
extern "C" void* FUN_0067de40();
extern "C" char  eastl__DoFindNode_wchar(void*);
extern "C" void  operator_delete__(void*);
extern "C" void  FUN_00b316d0(u32,u32,u32,u32);
extern "C" void* BehaviorManager();
extern "C" void* cGameNounManager__GetGameDataVector(void*,void*,void*,void*,void*,void*);
extern "C" void  FUN_00cf94e0(void*,u32,u32,void*,int);
extern "C" void  cTribe__UpdateRoboTribeness();
extern "C" void  FUN_00cf0f80(int,int);
extern "C" void* operator_new(u32, const char*, int, int, int, int);
extern "C" void  cTexturePreload__cTexturePreload(void*);
extern "C" void  cTexturePreload__PreloadTextureList(float*);
extern "C" void* Simulator__SimSingleton__SimSingleton();
extern "C" void  FUN_00ae3750(int*,int*,int*);
extern "C" void  FUN_00b3d4a0(int,int);
extern "C" void  FUN_00ae9150(u32,u32);
extern "C" void  FUN_00ce96a0();
extern "C" void  FUN_00e042d0(int);
extern "C" void* App();
extern "C" void  FUN_00b0f210(int*,int*,int*);
extern "C" void  FUN_00b11870(u32);
extern "C" void  FUN_00b10340(int,int,int);
extern "C" void  FUN_00b10760(u32,u32,u32);
extern "C" int   FUN_00bc30b0();
extern "C" void* FUN_00b137d0(void*);
extern "C" void  FUN_00bc2f00(int*, void*);
extern "C" void  FUN_00cf8fd0();
extern "C" void  cCityInputStrategy__RestoreCommunityEditorOrShopping(void*, void*);
extern "C" void* FUN_00401090(void*);
extern "C" void  FUN_00401090_v();
extern "C" int   FUN_00bef950();
extern "C" void  FUN_00e3c7c0(u32, int);
extern "C" void  FUN_00ae0930(const char*, u32, u32, u32, u32, u32);
extern "C" void  cSPEditorSpeciesManager__SetAvatarSpecies(void*, void*);
extern "C" void* FUN_00b25ca0();
extern "C" void  FUN_00bebdd0(void*);
extern "C" void* FUN_00bef6c0();
extern "C" void  FUN_00b3d480(u32,u32);
extern "C" void  FUN_00ac8cd0(u32,u32);
extern "C" void* FUN_004df550(void*);
extern "C" void  FUN_00c8e830(void*, int);
extern "C" void  GameTimeManager();
extern "C" void  StateManager(u32);
extern "C" void  FUN_00cf1500(int);
extern "C" void  FUN_007b19c0();
extern "C" char  FUN_007b19c0_c();
extern "C" void* FUN_00572620_dummy();
extern "C" void  FUN_00cf44c0(void*);
extern "C" void  cCityDisplayStrategy__AddResourceNodes(void*);
extern "C" void  FUN_00cec6d0();
extern "C" void  FUN_00cfb890();
extern "C" void  FUN_00cfb0b0();
extern "C" void  FUN_00bed460();
extern "C" void  FUN_00cf9190();
extern "C" void  FUN_00acd790();
extern "C" void* FUN_0067cb20();
extern "C" void* FUN_00b3d230();
extern "C" void  FUN_00b3d230_v(int);
extern "C" void* FUN_0067dd50();
extern "C" void* FUN_00401010();
extern "C" void  FUN_004df420();
extern "C" void  FUN_00cf7880();
extern "C" void* AppSystem();
extern "C" void  FUN_00cfb040();
extern "C" void* EA__Stopwatch__GetElapsedTime();
extern "C" void* EventLog(int);
extern "C" void  cSPUIEventLog__SetVisibility(void*, u32);
extern "C" void  FUN_00cf7150();
extern "C" void* FUN_00cf7d40(int);
extern "C" void* FUN_00b18e00(void*);
extern "C" void  FUN_00ad7a30(void*);
extern "C" void  FUN_00b3d4d0(u32,void*,int);
extern "C" void  FUN_00ae09b0(u32,void*,u32);
extern "C" void  FUN_00ae46f0(u32,u32,u32);
extern "C" void* FUN_00ad7b50();
extern "C" void  Start3dSoundByName(u32, void*);
extern "C" void  FUN_00adf390(u32);
extern "C" void  FUN_0067cac0(int,int);
extern "C" void  FUN_0067c420(u32,u32);
extern "C" void* ConfigManager();
extern "C" void  FUN_00cf7ad0();
extern "C" void  FUN_00bd7f70(void*,void*);
extern "C" void  FUN_00ad7b70();
extern "C" void  FUN_00ad79d0(void*,void*);
extern "C" void  FUN_00b3d340();
extern "C" void  FUN_00b2a100();
extern "C" void  FUN_00ad7ad0();
extern "C" void  FUN_00b3d410();
extern "C" char  FUN_00e36fa0();
extern "C" void  FUN_00e36de0();
extern "C" void  FUN_00e3e350(u32,void*,u32);
extern "C" char  FUN_00e36dd0();
extern "C" void  FUN_00e3b1f0();
extern "C" char  FUN_00e36e10();
extern "C" void  FUN_00b5e9a0(int);

extern "C" void* DAT_0167ea54;
extern "C" int   DAT_0167a60c;
extern "C" int   DAT_0169d3cc;
extern "C" void* g_TestSystem;
extern "C" void* g_CivStrategy;

// @ 0x00cfbc10
void cCivModeStrategy::ContinueLoading(int param_2)
{
    int* appMode  = *(int**)((char*)this + 0xb8);   // cached cIAppMode
    int* universe = *(int**)((char*)this + 0xbc);

    if (PlanetModel() != 0) {
        // re-init the minimap with the just-activated planet
        sInitMinimap((u32)param_2, 0, 0);
    }

    switch (*(int*)((char*)this + 0xb4)) {
    case 0:
        *(int*)((char*)this + 0xb4) = 1;
        FUN_00cf71d0(appMode);
        if (appMode != (int*)0x01654c06 && appMode != (int*)0x01654c04 &&
            appMode != (int*)0x00dbdba1) {
            if (appMode == (int*)0x01654c08) {
                // transition-flow UFO editor
                *(u8*)((char*)this + 0x1d0) = 1;
            }
            else {
                FUN_00cf8560();
            }
        }
        if (appMode != (int*)0x00dbdba1) {
            FUN_00b26930();
            FUN_00ae3300();
            FUN_00cfea20();
        }
        {
            int* planet = (int*)cSPLivingUniverse__GetActivePlanet();
            void* props = PropertyManager();
            (void)props;
            // set planet orientation from the species profile
            char c = FUN_00c708f0();
            float* dir = (c == 0) ? (float*)FUN_00c70930() : (float*)&DAT_0167ea54;
            QuaternionFromDirections(0, 0, dir);
            (void)planet;
        }
        // city / terraineditor bring-up (sequence of engine calls)
        if (appMode == (int*)0x01654c02 || appMode == (int*)0x02ccd1d2) {
            FUN_00bf55d0();
            NounManager();
            FUN_00b93960();
            FUN_00bf8170(FUN_00b1f9d0(), 1, 0x053dbcf2, 0);
        }
        {
            void* sphere = cTerrainEditor__GetCurrentTerrainSphere(NounManager());
            (void)sphere;
            if (cPlanet__IsSpeciesScanned(0) == 0) {
                FUN_00c73cb0(0);
                void* p = FUN_00ba4520(0);
                *(u8*)p = 1;
                FUN_00ba57f0(0, 1);
            }
        }
        {
            void* p = FUN_00b1f9d0();
            if (appMode == (int*)0x01654c02 || appMode == (int*)0x02ccd1d2) {
                FUN_00ba5a60(FUN_00b25f40(p), 7);
                FUN_00c73cd0(0);
                void* q = FUN_00c735e0(0);
                *(u8*)q = 1;
            }
        }
        if (appMode == (int*)0x01654c02 || appMode == (int*)0xffffffff) {
            if (appMode != (int*)0x01654c02)
                InitCityCivModeFromLaunchScreen();
            FUN_00675250(0xd082675a, 8, 1);
            FUN_00676ed0(0, 0, 0);
            void* sphere = cTerrainEditor__GetCurrentTerrainSphere(NounManager());
            *(int*)((char*)sphere + 0x128c) = 0;
        }
        else {
            if (appMode == (int*)0x01654c02) {
                FUN_00b22650(0x1be418e);
                FUN_00b22650(0x3a2511e);
                void* tribe = cGameNounManager__GetPlayerTribe(NounManager());
                FUN_00572660(tribe);
                FUN_00ba95a0(FUN_00acd9d0());
            }
            else if (appMode == (int*)0x01654c08) {
                FUN_00b969e0();
                FUN_00b26930();
                FUN_00ae3d70();
            }
        }
        {
            int* mgr = (int*)DAT_0167ea54;
            (void)mgr;
            u32 r = (u32)EA__RefCountTemplate_int__Release("Planet_Civ", 0x811c9dc5u, 1);
            (void)r;
        }
        {
            int* world = (int*)FUN_0067ddc0();
            if (world != 0) {
                // configure the model world for Civ mode
                (void)GonzagoModelWorld();
                (void)ModelManager();
                (void)FUN_0067de00(0x20007);
                (void)FUN_00b3d280();
            }
        }
        TerraformingManager(0);
        FUN_00bc08d0(0);
        PlanetModel();
        FUN_00b87dc0();
        if (appMode != (int*)0x00dbdba1) {
            if (appMode == (int*)0x01654c02) {
                void* tribe = cGameNounManager__GetPlayerTribe(NounManager());
                if (tribe != 0)
                    (void)tribe;
            }
            else {
                if (FUN_00b3d280() != 0) {
                    void* city = FUN_00b25c30();
                    if (city == 0) {
                        FUN_00b146a0(0, 1, 1);
                    }
                    else {
                        void* hall = cCity__GetCityHall(city);
                        if (hall != 0)
                            FUN_00b13b50();
                    }                }
            }
        }
        (**(void(__thiscall**)(void*, const char*, int, int))GameInputManager())(
            GameInputManager(), "TriggerConfigTribeGame", 0, 1);
        {
            void* locale = FUN_0067de40();
            const char* cfg = "TriggerConfigWASD";
            if (eastl__DoFindNode_wchar(locale) != 0)
                cfg = "TriggerConfigWASD_fr-fr";
            (**(void(__thiscall**)(void*, const char*, int, int))GameInputManager())(
                GameInputManager(), cfg, 0, 0);
        }
        break;

    case 1:
        *(int*)((char*)this + 0xb4) = 2;
        {
            void* civ = cGameNounManager__GetPlayerCivilization(NounManager());
            if (civ != 0) {
                // point the terrain cursor at the civ
                (**(void(__thiscall**)(void*, u32))(*(int*)civ))(
                    civ, (u32)FUN_00b2fa60());
            }
            (void)universe;
        }
        if (appMode == (int*)0x01654c02 || appMode == (int*)0x02ccd1d2 ||
            appMode == (int*)0xffffffff) {
            (void)cGameNounManager__GetPlayerCivilization(NounManager());
            FUN_00e3c7c0(0x3b38f92a, FUN_00bef950() + 0x504);
        }
        if (appMode == (int*)0x01654c08) {
            // species / town-name setup for a new city game
            FUN_00bef950();
        }
        FUN_00b316d0(0, 0, 0, 0);
        if (appMode != (int*)0x00dbdba1 && appMode != (int*)0x01654c08) {
            (**(void(__thiscall**)(void*))BehaviorManager())(BehaviorManager());
        }
        {
            void* v = cGameNounManager__GetGameDataVector(NounManager(), 0, 0, 0, 0, 0);
            FUN_00cf94e0(v, *(u32*)((char*)v + 4), *(u32*)((char*)v + 8),
                         (void*)cTribe__UpdateRoboTribeness, 0);
        }
        if (appMode != (int*)0x00dbdba1) {
            FUN_00cf0f80(0, 0);
            if (g_TestSystem == 0 || appMode != (int*)0x01654c08) {
                void* tp = operator_new(0x34, "Simulator", 0, 0, 0, 0);
                if (tp) cTexturePreload__cTexturePreload(tp);
                for (u32 i = 0; i < 0x30; i += 4)
                    cTexturePreload__PreloadTextureList((float*)i);
            }
            if (DAT_0167a60c == 0)
                DAT_0167a60c = (int)Simulator__SimSingleton__SimSingleton();
            {
                int a = 0, b = 0, c2 = 0;
                FUN_00ae3750(&a, &b, &c2);
                if (a > 0) FUN_00ae9150(0, a);
                if (b > 0) FUN_00ae9150(1, b);
                if (c2 > 0) FUN_00ae9150(2, c2);
            }
        }
        if (appMode == (int*)0x01654c08) {
            FUN_00ce96a0();
            void* civ = cGameNounManager__GetPlayerCivilization(NounManager());
            if (civ != 0 && *(int*)((char*)civ + 0x298) > 3)
                FUN_00e042d0(1);
        }
        {
            void* mgr = App();
            void* p = (**(void*(__thiscall**)(void*, u32))mgr)(mgr, 0xe3057616u);
            (void)p;
        }
        if (appMode != (int*)0x00dbdba1) {
            if (appMode == (int*)0x02ccd1d2 || appMode == (int*)0xffffffff ||
                appMode == (int*)0x01654c02) {
                int r = FUN_00bc30b0();
                if (r != 0)
                    FUN_00bc2f00(0, 0);
                FUN_00cf8fd0();
            }
            break;
        }
        if (*(u8*)((char*)this + 0x1c0) == 0) {
            cCityInputStrategy__RestoreCommunityEditorOrShopping(0, 0);
            break;
        }
        break;

    case 2:
        if (*(int*)0x0169d3cc != -1 && FUN_007b19c0_c() == 0)
            break;
        *(int*)((char*)this + 0xb4) = 3;
        if (appMode != (int*)0x00dbdba1) {
            if (appMode == (int*)0x01654c08)
                FUN_00572620_dummy();
            break;
        }
        if (*(u8*)((char*)this + 0x1c0) != 1)
            break;
        *(u8*)((char*)this + 0x1c0) = 0;
        break;

    case 3:
        if (FUN_00b3d280() != 0) {
            int pm = (int)PlanetModel();
            if ((**(char(__thiscall**)(int))(**(int**)(pm + 0x24) + 0x50))(pm) != 0) {
                cCityDisplayStrategy__AddResourceNodes((void*)PlanetModel());
                *(int*)((char*)this + 0xb4) = 4;
            }
        }
        break;

    case 4:
        if (FUN_00b3d280() > 4) {
            *(int*)((char*)this + 0xb4) = 5;
            FUN_00cfb0b0();
            if (appMode != (int*)0x00dbdba1) {
                FUN_00bed460();
                FUN_00cf9190();
                FUN_00b3d480(0, 0);
                FUN_00acd790();
                (**(void(__thiscall**)(void*, u32, int))FUN_0067cb20())(
                    FUN_0067cb20(), 0x8bff672au, 0);
            }
        }
        (**(void(__thiscall**)(void*, int))FUN_00b3d230())(FUN_00b3d230(), param_2);
        (**(void(__thiscall**)(void*, int))FUN_00b3d230())(FUN_00b3d230(), param_2);
        break;
    case 5:
        (**(void(__thiscall**)(void*, int, int))FUN_0067dd50())(
            FUN_0067dd50(), 0x16, 2);
        (**(void(__thiscall**)(void*))FUN_00401010())(FUN_00401010());
        (**(void(__thiscall**)(void*))GonzagoModelWorld())(GonzagoModelWorld());
        FUN_00401090_v();
        FUN_004df420();
        {
            bool bAny = false;
            FUN_00cf7880();
            if (FUN_00cf7880(), bAny) {
                // leave the loading screen
                (**(void(__thiscall**)(void*, int))AppSystem())(AppSystem(), 0);
            }
        }
        break;

    case 6:
        if (((u32)((u32)(size_t)EA__Stopwatch__GetElapsedTime() >> 32) == 0) &&
            ((u32)(size_t)EA__Stopwatch__GetElapsedTime() < 0x3e9))
            break;
        if (appMode != (int*)0x00dbdba1 && appMode != (int*)0x01654c08) {
            cSPUIEventLog__SetVisibility((void*)EventLog(1), 1);
            // city reveal sequence
            FUN_00cf7150();
            FUN_00ad7a30(FUN_00b18e00(FUN_00cf7d40(0)));
            FUN_00b3d4d0(0x9e430ff6, 0, 0);
            FUN_00ae09b0(0x9e430ff6, 0, 0);
            {
                void* city = FUN_00b25c30();
                void* hall = city ? cCity__GetCityHall(city) : 0;
                FUN_00ad7a30(hall ? (void*)((char*)hall + 0x34) : 0);
                (void)city;
            }
            FUN_00b26930();
            FUN_00b3d340();
            FUN_00b2a100();
            FUN_00ad7ad0();
            FUN_00ad7ad0();
            FUN_00ad7ad0();
        }
        if (*(u8*)((char*)this + 0x1c1) != 0 && appMode != (int*)0x00dbdba1) {
            FUN_00b3d410();
            if (FUN_00e36fa0() != 0) {
                FUN_00b3d410();
                FUN_00e36de0();
                *(int*)((char*)this + 0xb4) = 8;
                break;
            }
        }
        *(int*)((char*)this + 0xb4) = 7;
        break;

    case 7:
        if (appMode == (int*)0x00dbdba1)
            break;
        FUN_00b3d410();
        if (FUN_00e36fa0() == 0) {
            GameTimeManager();
            StateManager(0x4bf38a7);
        }
        *(int*)((char*)this + 0xb4) = 10;
        break;

    case 8:
        FUN_00b3d410();
        if (FUN_00e36dd0() != 0) {
            FUN_00b3d410();
            FUN_00e3b1f0();
            *(int*)((char*)this + 0xb4) = 9;
        }
        break;

    case 9:
        FUN_00b3d410();
        if (FUN_00e36e10() == 0)
            break;
        *(int*)((char*)this + 0xb4) = 7;
        break;

    default:
        *(int*)((char*)this + 0xb4) = 10;
        break;
    }

    FUN_00b3d230_v(param_2);
    FUN_00b5e9a0(param_2);
    (void)universe;
}
