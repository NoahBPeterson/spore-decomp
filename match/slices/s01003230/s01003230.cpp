// Slice s01003230: SP::cSPSimulatorSpaceGame galaxy/solar/planet context transitions
// (0x01003230..0x01003c60) plus the free function SP::UpdateSound.
// Retail build. Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
//
// cSPSimulatorSpaceGame member offsets observed in this slice:
//   mpSpaceUI       +0x14  EA::AutoRefCount<cSPUISpace>
//   mfCamOffset_3c  +0x3c  float (ChangeCameraByOffset tilt/pan scale)
//   mpInv_40        +0x40  cSPPlayerInventory*
//   mFlag4c..4f     +0x4c..+0x4f  four bools
//   mpEditorResult  +0x54  pointer (passed to FUN_00ff9390)
//   mpObj6c         +0x6c  interface pointer (vtable +0x10 test / +0x08 action)
//   mpSub70/AC      +0x70 / +0xac  SimTicker subsystem pointers
//   mpSubB4..C0     +0xb4/+0xb8/+0xbc/+0xc0  SimTicker subsystem pointers
#include "types.h"
#include <stddef.h>
#include <math.h>

// ----------------------------------------------------------------- allocator ---
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
inline void* operator new(size_t, void* p) { return p; }

// -------------------------------------------------------- vtable-call types ---
typedef void  (__thiscall *PFNv)(void*);
typedef void  (__thiscall *PFNvi)(void*, int);
typedef void  (__thiscall *PFNvu)(void*, unsigned);
typedef void  (__thiscall *PFNvp)(void*, void*);
typedef void  (__thiscall *PFNvii)(void*, int, int);
typedef void  (__thiscall *PFNvpi)(void*, void*, int);
typedef void  (__thiscall *PFNv_di)(void*, unsigned, void*, int);
typedef void  (__thiscall *PFNvf)(void*, float);
typedef void* (__thiscall *PFNpv)(void*);
typedef void* (__thiscall *PFNpvu)(void*, unsigned);
typedef char  (__thiscall *PFNcv)(void*);

// -------------------------------------------------------------- declarations ---
struct cSPSimulatorSpaceGame;

struct cSPUISpace {
    cSPUISpace();                              // 0x01070ba0
    void Init();                               // 0x01073700
    void OnContextDeactivate();                // 0x0106e270
    void FUN_0106f380();                       // 0x0106f380
    void FUN_01070890();                       // 0x01070890
    char mPad[0x6ac];
};

struct cCitySimulator {
    cCitySimulator();                          // 0x00ae6a70
    void AttachSubsystems();                   // 0x00ae7350
    char mPad[0x40];
};

struct SimSingleton {
    SimSingleton();                            // 0x00ae5c30
    void SetSerializer();                      // 0x00c2e4e0
    char mPad[0xc8];
};

struct cUIMissionCardPanel {
    void RefreshFromMissionList();             // 0x00e184d0
    void SetCardsVisibility(bool show);        // 0x00e14c10
};

// SpVectorF: three-float vector. The retail build passes it by value to
// FUN_01036940; its user-declared copy constructor copies the members through
// the x87 stack, which is what produces the `fld`/`fstp` argument fill at the
// FUN_01036940 call sites.
class SpVectorF {
public:
    float x, y, z;
    SpVectorF() {}
    SpVectorF(const SpVectorF& o) { x = o.x; y = o.y; z = o.z; }
    SpVectorF(float a, float b, float c) { x = a; y = b; z = c; }
};

struct cCivData {
    SpVectorF* GetCities();                    // 0x005c65e0
};

struct cSPPlayerInventory {
    void  FUN_00ff3e80();                      // 0x00ff3e80
    char  FUN_00c37170();                      // 0x00c37170
};

struct cSPGameDataUFO {
    void SetDestinationFromCities(void* cities); // 0x00c3c360
    void PopToDestination();                     // 0x00c37e60
};

struct cTerrainSphere {
    void FUN_00c77bf0();                       // 0x00c77bf0
};

struct cStarMap {
    void FilterHelperRebuildAll();             // 0x01048ce0
};

struct cSolarSystem {
    void ActivateGraphics(int on);             // 0x00c86c70
};

struct cSimulatorUniverse {
    void AdjustAwareness(void* a, int b);      // 0x01014a80
};

struct cDirectPropertyList {
    char GetDescription(unsigned key);         // 0x006a25a0
};

// planet (0x01021260 result) ------------------------------------------------
struct cPlanet {
    char  _pad00[0x13c];
    void* mpCiv13c;                            // +0x13c
    int   FUN_00c70e00();                      // 0x00c70e00
    void  FUN_00c70bc0(int a);                 // 0x00c70bc0
    int   FUN_00c70880();                      // 0x00c70880
    char  FUN_00c70c00();                      // 0x00c70c00
    void  PlanetSimActivate();                 // 0x00c71e70
    void* FUN_00c71e30();                      // 0x00c71e30
    void  FUN_008414c0();                      // 0x008414c0
};

struct cStar {
    char            _pad00[0x48];
    void*           mpTime48;                  // +0x48
    float* FUN_00c8b360();                     // 0x00c8b360
    cSolarSystem* GetSolarSystem();            // 0x00c8b770
};

struct cSPCameraControllerSolarSystem {
    char  _pad00[0x68];
    float mf68;                                // +0x68
    float mf6c;                                // +0x6c
    float mf70;                                // +0x70
    char  _pad74[0x80 - 0x74];
    float mf80;                                // +0x80
    void  FUN_01017170(float v);               // 0x01017170
    void  FUN_010171b0(float v);               // 0x010171b0
    float FUN_010175b0(float v);               // 0x010175b0
};

// direct-call receiver models -----------------------------------------------
struct H00b3d360 { void FUN_00b7dec0(); };                // 0x00b7dec0
struct H00b3d2a0 { void FUN_00bb5990(); };                // 0x00bb5990
struct H00b3d3b0 { void FUN_00b2ec80(); };                // 0x00b2ec80
struct H00b3d440 { void FUN_00b0b150(); };                // 0x00b0b150
struct H00b3d3c0 { void FUN_00b79aa0(); };                // 0x00b79aa0
struct H00b3d480 { void FUN_00acd790(); };                // 0x00acd790
struct H00b3d430 { void FUN_00bc2070(); void FUN_00bc0180(); }; // 0x00bc2070 / 0x00bc0180
struct H00b3d230 { void FUN_00b5cde0(); };                // 0x00b5cde0
struct H00b3d380 { uint64_t FUN_00b316c0(); };            // 0x00b316c0
struct H00b3d240 { float FUN_00b35fa0(); };               // 0x00b35fa0
struct H00b3d300 { void* GetCurrentTerrainSphere(); };    // 0x00f67d90 (cTerrainEditor)
struct H00b8de30  { cCivData* SortBanners(); };           // 0x00b8de30
void  FUN_00cfea20();                                     // 0x00cfea20

// external functions --------------------------------------------------------
void* App();                                              // 0x0067dd10
void* MessageServer();                                    // 0x0067dcc0
void* EffectsManagerPtr();                                // 0x0067ddd0
void* FUN_0067dd40();                                     // 0x0067dd40
void* FUN_0067de00();                                     // 0x0067de00
void* __stdcall FUN_0067de00u(unsigned kind);             // 0x0067de00
void* FUN_0067ddc0();                                     // 0x0067ddc0
void* ModelManager();                                     // 0x0067dd80
void* FUN_0067dd50();                                     // 0x0067dd50

void* SimTicker();                                        // 0x00b3d330
cUIMissionCardPanel* FUN_00b3d400();                      // 0x00b3d400
cSPSimulatorSpaceGame* FUN_00b3d470();                    // 0x00b3d470
H00b3d360* FUN_00b3d360();                                // 0x00b3d360
H00b3d2a0* __stdcall FUN_00b3d2a0(void* planet, int flag);         // 0x00b3d2a0
H00b3d3b0* __stdcall FUN_00b3d3b0(int a);                 // 0x00b3d3b0
H00b3d440* FUN_00b3d440();                                // 0x00b3d440
H00b3d3c0* FUN_00b3d3c0();                                // 0x00b3d3c0
H00b3d480* FUN_00b3d480();                                // 0x00b3d480
H00b3d430* __stdcall TerraformingManager(void* planet, int flag);    // 0x00b3d430
H00b3d430* __stdcall TerraformingManager1(int flag);                 // 0x00b3d430
H00b3d230* __stdcall FUN_00b3d230(unsigned id);                    // 0x00b3d230
H00b3d300* __stdcall NounManager(unsigned id);                     // 0x00b3d300
H00b3d380* GameTimeManager();                             // 0x00b3d380
H00b3d240* FUN_00b3d240();                                // 0x00b3d240
void* GonzagoModelWorld();                                // 0x00b3d520
void* PlanetModel();                                      // 0x00b3d350

int   GetUniverseContext();                               // 0x01021080
void* FUN_01021230();                                     // 0x01021230
void* FUN_01021260();                                     // 0x01021260
void* FUN_01021240();                                     // 0x01021240
void  FUN_01021740(void* planet);                         // 0x01021740
void  FUN_01021960(int a);                                // 0x01021960
void  FUN_01034810();                                     // 0x01034810
void  FUN_01034950(int a, int b);                         // 0x01034950
void  FUN_01036940(SpVectorF v);                          // 0x01036940
void  FUN_01036590(void* planet);                         // 0x01036590
void  FUN_010347e0();                                     // 0x010347e0
void  FUN_01034b90(void* star);                           // 0x01034b90
void  FUN_010367e0(int a);                                // 0x010367e0
void  FUN_01036830(int a);                                // 0x01036830
void  FUN_0106e270(void* ui);                             // 0x0106e270
void  FUN_0106f380(void* ui);                             // 0x0106f380
void  FUN_01070890(void* ui);                             // 0x01070890
void* FUN_01046fc0();                                     // 0x01046fc0
float FUN_01017030(int ctx);                              // 0x01017030
float FUN_01017070(int ctx);                              // 0x01017070
float FUN_01017010(int ctx, float f);                     // 0x01017010
void  __fastcall FUN_00ff9390(void* p);                   // 0x00ff9390
cSPSimulatorSpaceGame* GetUFOSimulator();                 // 0x00ffbe50
unsigned FNVHash(const char* s, unsigned basis, int a);   // 0x00932e80

// globals -------------------------------------------------------------------
cCitySimulator*        g_167a690;        // 0x0167a690
SimSingleton*          g_167a60c;        // 0x0167a60c
void*                  g_167ea54;        // 0x0167ea54
cDirectPropertyList*   g_15fd918;        // 0x015fd918
unsigned char          g_15b743e;        // 0x015b743e
cSimulatorUniverse*    g_16dc798;        // 0x016dc798

// --------------------------------------------------------- the simulator class
struct cSPSimulatorSpaceGame {
    char              _pad00[0x14];
    cSPUISpace*       mpSpaceUI;      // +0x14
    char              _pad18[0x3c - 0x18];
    float             mfCamOffset_3c; // +0x3c
    cSPPlayerInventory* mpInv_40;     // +0x40
    char              _pad44[0x4c - 0x44];
    bool              mFlag4c;        // +0x4c
    bool              mFlag4d;        // +0x4d
    bool              mFlag4e;        // +0x4e
    bool              mFlag4f;        // +0x4f
    char              _pad50[0x54 - 0x50];
    void*             mpEditorResult; // +0x54
    char              _pad58[0x6c - 0x58];
    void*             mpObj6c;        // +0x6c
    void*             mpSub70;        // +0x70
    char              _pad74[0xac - 0x74];
    void*             mpObjAC;        // +0xac
    char              _padB0[0xb4 - 0xb0];
    void*             mpSubB4;        // +0xb4
    void*             mpSubB8;        // +0xb8
    void*             mpSubBC;        // +0xbc
    void*             mpSubC0;        // +0xc0

    void  FUN_01003230();                                    // 0x01003230
    void  FUN_01003620();                                    // 0x01003620
    void  FUN_01003690();                                    // 0x01003690
    void  GalaxyContextActivate();                           // 0x01003490
    void  FUN_010039c0(cStar* star);                         // 0x010039c0
    void  ChangeCameraByOffset(float a, float b);            // 0x01003c60
    void  FUN_01034950(int a, int b);                        // 0x01034950
    void  FUN_010367e0(int a);                               // 0x010367e0
    void  FUN_01036830(int a);                               // 0x01036830
    void  FUN_01034810();                                    // 0x01034810
    void  FUN_01036940(SpVectorF v);                         // 0x01036940
    void  FUN_01036590(void* planet);                        // 0x01036590
    void  FUN_010347e0();                                    // 0x010347e0
    void  FUN_01034b90(void* star);                          // 0x01034b90
    void  SolarContextFinishActivate(float len, bool flag);  // 0x01036c20
    cSPPlayerInventory* GetPlayerInventory();                // 0x00a1ad60
};

// ============================================================================
// @ 0x01003230
void cSPSimulatorSpaceGame::FUN_01003230()
{
    void* ticker = SimTicker();                              // 0x00b3d330
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, this);
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, mpSub70);
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, mpSubB8);

    cCitySimulator* sim = g_167a690;
    if (sim == 0)
        g_167a690 = new ("Simulator/SimSingleton", 0, 0, 0, 0) cCitySimulator();
    g_167a690->AttachSubsystems();                           // 0x00ae7350

    cCitySimulator* sim2 = g_167a690;
    if (sim2 == 0)
        g_167a690 = new ("Simulator/SimSingleton", 0, 0, 0, 0) cCitySimulator();
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, g_167a690);

    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, mpSubC0);
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, mpSubB4);
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, mpSubBC);

    if (mpSpaceUI == 0) {
        cSPUISpace* ui = new ("Simulator", 0, 0, 0, 0) cSPUISpace();
        cSPUISpace* old = mpSpaceUI;
        if (ui != old) {
            if (ui != 0)
                (*(PFNv*)((char*)*(void**)ui + 0x00))(ui);
            mpSpaceUI = ui;
            if (old != 0)
                (*(PFNv*)((char*)*(void**)old + 0x04))(old);
        }
        mpSpaceUI->Init();                                   // 0x01073700
        if (mpEditorResult != 0)
            FUN_00ff9390(mpEditorResult);                    // 0x00ff9390
    }

    cUIMissionCardPanel* panel = FUN_00b3d400();             // 0x00b3d400
    if (panel != 0) {
        panel->RefreshFromMissionList();                     // 0x00e184d0
        panel->SetCardsVisibility(true);                     // 0x00e14c10
    }
    void* sys = g_167ea54;
    (*(PFNvu*)((char*)*(void**)sys + 0x30))(sys, 0x74d2735b);
}

// ============================================================================
// @ 0x010033a0
void UpdateSound()
{
    void* app = App();                                       // 0x0067dd10
    void* frame = (*(PFNpv*)((char*)*(void**)app + 0x50))(app);
    void* mode  = (*(PFNpv*)((char*)*(void**)frame + 0x38))(frame);
    if (mode == 0)
        return;
    cSPCameraControllerSolarSystem* cam =
        (cSPCameraControllerSolarSystem*)(*(PFNpvu*)((char*)*(void**)mode + 0x0c))(mode, 0x303154cc);
    if (cam == 0)
        return;

    int ctx = GetUniverseContext();                          // 0x01021080
    float lo = FUN_01017030(ctx);                            // 0x01017030
    float hi = FUN_01017070(ctx);                            // 0x01017070
    float v = cam->mf68;                                     // +0x68
    if (v < lo) v = lo;
    if (v > hi) v = hi;
    float t = (v - lo) / (hi - lo) * 0.5f + (float)(ctx - 1) * 0.5f;
    void* msg = MessageServer();                             // 0x0067dcc0
    (*(PFNv_di*)((char*)*(void**)msg + 0x14))(msg, 0x1959007, &t, 0);
}

// ============================================================================
// @ 0x01003490
void cSPSimulatorSpaceGame::GalaxyContextActivate()
{
    if (mpInv_40 != 0)
        mpInv_40->FUN_00ff3e80();                            // 0x00ff3e80
    void* msg = MessageServer();                             // 0x0067dcc0
    (*(PFNv_di*)((char*)*(void**)msg + 0x14))(msg, 0x279a680, 0, 0);

    FUN_00b3d470()->FUN_010367e0(1);                         // 0x010367e0
    FUN_00b3d470()->FUN_01036830(1);                         // 0x01036830
    FUN_00b3d470()->FUN_01034950(3, -1);                     // 0x01034950

    cSPSimulatorSpaceGame* sim = FUN_00b3d470();
    char* slotAC = (char*)sim + offsetof(cSPSimulatorSpaceGame, mpObjAC); // +0xac
    void* ac = *(void**)slotAC;
    (*(PFNvi*)((char*)*(void**)ac + 0x0c))(ac, 0);

    FUN_01021960(2);                                         // 0x01021960
    void* o = FUN_0067de00();                                // 0x0067de00
    char* slotE0 = (char*)*(void**)o + 0xe0;
    (*(PFNvi*)slotE0)(o, GetUniverseContext());

    void* fx = EffectsManagerPtr();                          // 0x0067ddd0
    (*(PFNvii*)((char*)*(void**)fx + 0x98))(fx, 0x12, 1);
    void* d1 = FUN_0067dd40();                               // 0x0067dd40
    (*(PFNvi*)((char*)*(void**)d1 + 0x100))(d1, 1);
    void* d2 = FUN_0067dd40();
    (*(PFNvi*)((char*)*(void**)d2 + 0x108))(d2, 1);

    cCivData* civ = (cCivData*)FUN_01021240();               // 0x01021240
    SpVectorF* p = civ->GetCities();                         // 0x005c65e0
    FUN_00b3d470()->FUN_01036940(*p);                        // 0x01036940

    cSPSimulatorSpaceGame* ufo = GetUFOSimulator();          // 0x00ffbe50
    cSPGameDataUFO* inv = (cSPGameDataUFO*)ufo->GetPlayerInventory(); // 0x00a1ad60
    inv->SetDestinationFromCities(civ);                      // 0x00c3c360
    inv->PopToDestination();                                 // 0x00c37e60

    H00b3d300* te = NounManager(0x574ac68);                  // 0x00b3d300
    cTerrainSphere* ts = (cTerrainSphere*)te->GetCurrentTerrainSphere(); // 0x00f67d90
    ts->FUN_00c77bf0();                                      // 0x00c77bf0

    msg = MessageServer();
    (*(PFNv_di*)((char*)*(void**)msg + 0x14))(msg, 0x248976a, 0, 0);
    mpSpaceUI->FUN_01070890();                               // 0x01070890

    void* sys = g_167ea54;
    (*(PFNvu*)((char*)*(void**)sys + 0x30))(sys, 0x74d2735b);

    cStarMap* map = (cStarMap*)FUN_01046fc0();               // 0x01046fc0
    map->FilterHelperRebuildAll();                           // 0x01048ce0

    void* gm = GonzagoModelWorld();                          // 0x00b3d520
    if (gm != 0)
        (*(PFNvf*)((char*)*(void**)gm + 0x154))(gm, 0.0f);
}

// ============================================================================
// @ 0x01003620
void cSPSimulatorSpaceGame::FUN_01003620()
{
    void* fx = EffectsManagerPtr();                          // 0x0067ddd0
    (*(PFNvii*)((char*)*(void**)fx + 0x98))(fx, 0x12, 0);

    FUN_00b3d470()->FUN_01036830(0);                         // 0x01036830
    cSPSimulatorSpaceGame* sim = FUN_00b3d470();
    char* slotAC = (char*)sim + offsetof(cSPSimulatorSpaceGame, mpObjAC); // +0xac
    void* ac = *(void**)slotAC;
    (*(PFNvi*)((char*)*(void**)ac + 0x0c))(ac, 2);

    void* fx2 = EffectsManagerPtr();
    void* o = (*(PFNpv*)((char*)*(void**)fx2 + 0x5c))(fx2);
    (*(PFNv*)((char*)*(void**)o + 0x38))(o);

    if (mpSpaceUI != 0) {
        mpSpaceUI->OnContextDeactivate();                    // 0x0106e270
        mpSpaceUI->FUN_0106f380();                           // 0x0106f380
    }
}

// ============================================================================
// @ 0x01003690
void cSPSimulatorSpaceGame::FUN_01003690()
{
    cPlanet* planet = (cPlanet*)FUN_01021260();              // 0x01021260
    H00b8de30* civOwner = (H00b8de30*)planet->mpCiv13c;      // +0x13c

    FUN_00b3d360()->FUN_00b7dec0();                          // 0x00b7dec0
    FUN_00b3d2a0(planet, 0)->FUN_00bb5990();                 // 0x00b3d2a0 / 0x00bb5990

    if (planet->FUN_00c70e00() < 4)                          // 0x00c70e00
        planet->FUN_00c70bc0(0);                             // 0x00c70bc0

    mFlag4d = 0;
    mFlag4c = 0;
    mFlag4f = 0;
    mFlag4e = 0;

    void* o = FUN_0067de00();                                // 0x0067de00
    (*(PFNvi*)((char*)*(void**)o + 0xe0))(o, 0);
    void* fx = EffectsManagerPtr();                          // 0x0067ddd0
    (*(PFNvii*)((char*)*(void**)fx + 0x98))(fx, 0x14, 1);
    void* d1 = FUN_0067dd40();                               // 0x0067dd40
    (*(PFNvi*)((char*)*(void**)d1 + 0x100))(d1, 1);
    void* d2 = FUN_0067dd40();
    (*(PFNvi*)((char*)*(void**)d2 + 0x108))(d2, 0);

    cSPSimulatorSpaceGame* sim = FUN_00b3d470();             // 0x00b3d470
    if (sim->mpObj6c != 0) {                                 // +0x6c
        if ((*(PFNcv*)((char*)*(void**)sim->mpObj6c + 0x10))(sim->mpObj6c) == 0)
            (*(PFNvi*)((char*)*(void**)sim->mpObj6c + 0x08))(sim->mpObj6c, 0);
    }

    FUN_01021960(0);                                         // 0x01021960
    FUN_00b3d470()->FUN_01034810();                          // 0x01034810
    FUN_00b3d470()->FUN_01034950(1, planet->FUN_00c70880()); // 0x00c70880 / 0x01034950

    cStar* star = (cStar*)FUN_01021230();                    // 0x01021230
    cSolarSystem* solar = star->GetSolarSystem();            // 0x00c8b770
    if (solar != 0)
        solar->ActivateGraphics(1);                          // 0x00c86c70

    TerraformingManager(planet, 1)->FUN_00bc2070();          // 0x00b3d430 / 0x00bc2070

    FUN_00b3d3b0(0)->FUN_00b2ec80();                         // 0x00b3d3b0 / 0x00b2ec80
    FUN_00b3d440()->FUN_00b0b150();                          // 0x00b3d440 / 0x00b0b150
    FUN_00b3d3c0()->FUN_00b79aa0();                          // 0x00b3d3c0 / 0x00b79aa0
    FUN_00b3d480()->FUN_00acd790();                          // 0x00b3d480 / 0x00acd790

    if (planet->FUN_00c70c00() == 0)                         // 0x00c70c00
        planet->PlanetSimActivate();                         // 0x00c71e70
    planet->FUN_008414c0();                                  // 0x008414c0
    sim->FUN_01036590(planet);                               // 0x01036590

    cCivData* civ = civOwner->SortBanners();                 // 0x00b8de30
    SpVectorF* p = civ->GetCities();                         // 0x005c65e0
    FUN_00b3d470()->FUN_01036940(*p);                        // 0x01036940

    FUN_01021740(planet);                                    // 0x01021740

    void* ticker = SimTicker();                              // 0x00b3d330
    if (g_167a60c == 0)
        g_167a60c = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
    (*(PFNvp*)((char*)*(void**)ticker + 0x50))(ticker, g_167a60c);

    if (g_167a60c == 0)
        g_167a60c = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
    g_167a60c->SetSerializer();                              // 0x00c2e4e0

    TerraformingManager1(1)->FUN_00bc0180();                 // 0x00b3d430 / 0x00bc0180

    void* sys = g_167ea54;
    (*(PFNvu*)((char*)*(void**)sys + 0x30))(sys, FNVHash("Planet_Space", 0x811c9dc5, 1)); // 0x00932e80

    void* gm = GonzagoModelWorld();                          // 0x00b3d520
    if (gm != 0)
        (*(PFNvf*)((char*)*(void**)gm + 0x154))(gm, FUN_00b3d240()->FUN_00b35fa0()); // 0x00b3d240 / 0x00b35fa0

    void* layout = FUN_0067ddc0();                           // 0x0067ddc0
    if (layout != 0) {
        (*(PFNvp*)((char*)*(void**)layout + 0x10))(layout, g_167ea54);
        (*(PFNvpi*)((char*)*(void**)layout + 0x18))(layout, gm, 3);
        void* mdl = ModelManager();                          // 0x0067dd80
        void* m = (*(PFNpvu*)((char*)*(void**)mdl + 0x1c))(mdl, 0x3fbae24);
        if (m != 0)
            (*(PFNvpi*)((char*)*(void**)layout + 0x18))(layout, m, 0);
        (*(PFNvp*)((char*)*(void**)layout + 0x1c))(layout, FUN_0067de00u(0x20007));
        (*(PFNvu*)((char*)*(void**)layout + 0x48))(layout, 0x5e51c01);
        (*(PFNvi*)((char*)*(void**)layout + 0x28))(layout, 1);
    }

    void* aware = planet->FUN_00c71e30();                    // 0x00c71e30
    if (aware != 0) {
        void* a = *(void**)((char*)aware + 0x84);
        g_16dc798->AdjustAwareness(a, 1);                    // 0x01014a80
    }

    void* pm = *(void**)((char*)PlanetModel() + 0x24);       // 0x00b3d350
    char* slot8c = (char*)*(void**)pm + 0x8c;
    (*(PFNvp*)slot8c)(pm, FUN_0067dd50());                   // 0x0067dd50
    FUN_00cfea20();                                          // 0x00cfea20
}

// ============================================================================
// @ 0x010039c0
void cSPSimulatorSpaceGame::FUN_010039c0(cStar* star)
{
    void* fx = EffectsManagerPtr();                          // 0x0067ddd0
    (*(PFNvii*)((char*)*(void**)fx + 0x98))(fx, 0x13, 0);
    void* fx2 = EffectsManagerPtr();
    void* o = (*(PFNpv*)((char*)*(void**)fx2 + 0x5c))(fx2);
    (*(PFNv*)((char*)*(void**)o + 0x38))(o);

    if (mpSpaceUI != 0)
        mpSpaceUI->OnContextDeactivate();                    // 0x0106e270

    cSolarSystem* solar = star->GetSolarSystem();            // 0x00c8b770
    if (solar != 0) {
        solar->ActivateGraphics(0);                          // 0x00c86c70
        void* time = star->mpTime48;
        uint64_t t = GameTimeManager()->FUN_00b316c0();      // 0x00b3d380 / 0x00b316c0
        *(unsigned*)((char*)time + 0xc) = (unsigned)(t / 60000);
    }
    FUN_00b3d470()->FUN_01034950(0, -1);                     // 0x01034950
}

// ============================================================================
// @ 0x01003a50
void FUN_01003a50()
{
    cStar* star = (cStar*)FUN_01021230();                    // 0x01021230

    void* msg = MessageServer();                             // 0x0067dcc0
    (*(PFNv_di*)((char*)*(void**)msg + 0x14))(msg, 0x279a67c, 0, 0);
    void* fx = EffectsManagerPtr();                          // 0x0067ddd0
    (*(PFNvii*)((char*)*(void**)fx + 0x98))(fx, 0x13, 1);
    void* d1 = FUN_0067dd40();                               // 0x0067dd40
    (*(PFNvi*)((char*)*(void**)d1 + 0x100))(d1, 1);
    void* d2 = FUN_0067dd40();
    (*(PFNvi*)((char*)*(void**)d2 + 0x108))(d2, 1);

    FUN_01021960(1);                                         // 0x01021960
    void* o = FUN_0067de00();                                // 0x0067de00
    (*(PFNvi*)((char*)*(void**)o + 0xe0))(o, 1);

    FUN_00b3d230(0x1103192)->FUN_00b5cde0();                 // 0x00b3d230 / 0x00b5cde0

    void* app = App();                                       // 0x0067dd10
    void* frame = (*(PFNpv*)((char*)*(void**)app + 0x50))(app);
    void* g = (*(PFNpv*)((char*)*(void**)frame + 0x38))(frame);
    void* camRoot = (g != 0)
        ? (*(PFNpvu*)((char*)*(void**)g + 0x0c))(g, 0x303154cc)
        : 0;
    (*(PFNv*)((char*)*(void**)camRoot + 0x58))(camRoot);

    float* p = star->FUN_00c8b360();                         // 0x00c8b360
    float x = p[0];
    float y = p[1];
    float z = p[2];
    float len = sqrtf(x * x + (y * y + z * z));

    FUN_00b3d470()->SolarContextFinishActivate(len, true);    // 0x01036c20
    FUN_00b3d470()->FUN_010347e0();                          // 0x010347e0
    FUN_00b3d470()->FUN_01034950(2, -1);                     // 0x01034950
    FUN_00b3d470()->FUN_01036940(SpVectorF(x, y, z));         // 0x01036940
    star->GetSolarSystem()->ActivateGraphics(1);             // 0x00c8b770 / 0x00c86c70

    void* sys = g_167ea54;
    (*(PFNvu*)((char*)*(void**)sys + 0x30))(sys, 0x74d2735b);

    void* fx3 = EffectsManagerPtr();
    (*(PFNv*)((char*)*(void**)fx3 + 0x48))(fx3);

    msg = MessageServer();
    (*(PFNv_di*)((char*)*(void**)msg + 0x14))(msg, 0x2489766, 0, 0);
    FUN_00b3d470()->FUN_01034b90(star);                      // 0x01034b90

    if (g_15b743e != 0 || g_15fd918->GetDescription(0xffbdc58d) != 0) { // 0x006a25a0
        msg = MessageServer();
        (*(PFNv_di*)((char*)*(void**)msg + 0x14))(msg, 0x1cd20f0, (void*)1, 0);
    }

    void* gm = GonzagoModelWorld();                          // 0x00b3d520
    if (gm != 0)
        (*(PFNvf*)((char*)*(void**)gm + 0x154))(gm, 0.0f);
}

// ============================================================================
// @ 0x01003c60
void cSPSimulatorSpaceGame::ChangeCameraByOffset(float a, float b)
{
    cSPSimulatorSpaceGame* ufo = GetUFOSimulator();          // 0x00ffbe50
    cSPPlayerInventory* inv = (cSPPlayerInventory*)ufo->GetPlayerInventory(); // 0x00a1ad60
    bool blocked = false;
    if (inv == 0)
        blocked = true;
    else if (inv->FUN_00c37170() != 0)                       // 0x00c37170
        blocked = true;

    if (blocked) {
        int ctx = GetUniverseContext();                      // 0x01021080
        if (ctx == 0) {
            void* app = App();                               // 0x0067dd10
            void* frame = (*(PFNpv*)((char*)*(void**)app + 0x50))(app);
            void* g = (*(PFNpv*)((char*)*(void**)frame + 0x38))(frame);
            if (g != 0) {
                cSPCameraControllerSolarSystem* cam =
                    (cSPCameraControllerSolarSystem*)(*(PFNpvu*)((char*)*(void**)g + 0x0c))(g, 0x303154cd);
                if (cam != 0) {
                    cam->FUN_01017170(mfCamOffset_3c * a);   // 0x01017170
                    cam->FUN_010171b0(mfCamOffset_3c * b);   // 0x010171b0
                }
            }
        } else if (ctx > 0 && ctx < 3) {
            void* app = App();
            void* frame = (*(PFNpv*)((char*)*(void**)app + 0x50))(app);
            void* g = (*(PFNpv*)((char*)*(void**)frame + 0x38))(frame);
            if (g != 0) {
                cSPCameraControllerSolarSystem* cam =
                    (cSPCameraControllerSolarSystem*)(*(PFNpvu*)((char*)*(void**)g + 0x0c))(g, 0x303154cc);
                if (cam != 0) {
                    cam->mf6c = a * 0.005f + cam->mf6c;
                    cam->mf70 = b * 0.005f + cam->mf70;
                    float lim = FUN_01017010(ctx, cam->mf68); // 0x01017010
                    float v = cam->mf70;
                    if (v < 0.1f) v = 0.1f;
                    if (v > lim) v = lim;
                    cam->mf70 = v;
                    float r = cam->FUN_010175b0(cam->mf68);  // 0x010175b0
                    cam->mf80 = cam->mf70 - r;
                    return;
                }
            }
        }
    }
    return;
}