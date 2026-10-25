// Slice s00b5b540 (batch bfs1) — 39 functions.
// Module "Spore"; SP::cGonzagoSubsystem and related Gonzago helpers.  Each block
// starts with its original address.

#include "s00b5b540.h"

extern "C" void* FUN_00b3d320();
extern "C" void* FUN_00b3d3a0();
extern "C" void* SP_App_67dd10();
extern "C" void* SP_MessageServer_67dcc0();
extern "C" void* SP_GameTimeManager_00b3d380();
struct SPVector_00b96600 { void FUN_00b96600(void* pos, const void* key); };  // 0x00B96600
extern "C" void  FUN_004cd3c0(void*);
extern "C" void  FUN_00586800(void*, int);
extern "C" void  FUN_005724e0(void*, int);
extern "C" void  FUN_00d3bd70(void*);
extern "C" void  RegisterAppMode_cGameEditModeStrategy(void*);
extern "C" void  RegisterAppMode_SPcTribeModeStrategy(void*);
extern "C" void  FUN_00cfa320(void*);
extern "C" void  FUN_00fddb40(void*);
extern "C" void  RegisterAppMode_cCellMode(void*);
extern "C" void  FUN_00b5d3f0(void*);
extern "C" void  FUN_00b32190(int, int, const char*);
extern "C" void  FUN_00b323f0(void*);
extern "C" void  FUN_00b6a530();
extern "C" void  FUN_00c103f0();
extern "C" void  FUN_00d1f2a0();
extern "C" void  FUN_00ec40b0();
extern "C" void  FUN_00b13b20();
extern "C" void  FUN_00bbb802();
extern "C" void  free_00f47380(void*);
extern "C" void  operator_delete_proxy(void*);
extern "C" void  FUN_00692f90(void*, void*, const char*, unsigned);
extern "C" void  FUN_00692900(void*, void*);
extern "C" char  FUN_00693e10(void*, void*);
extern "C" int   FUN_00574570();
extern "C" char  FUN_00dd18d0(int);
extern "C" void* FUN_00b3d220();

extern int* g_1686a18;   // vector begin
extern int* g_1686a1c;   // vector end
extern int* g_1686a20;   // vector capacity
extern char g_vt0dummy, g_vt1dummy;

static inline void* g_vt(void* p) { return *(void**)p; }
static inline void* g_vfn(void* p, int off) { return *(void**)((char*)g_vt(p) + off); }

// ---- wrappers / free helpers ------------------------------------------------

// @ 0x00b5b800
__declspec(noinline) int FUN_00b5b800()
{
    GameModeObj* p = (GameModeObj*)FUN_00b3d320();
    if (p) return p->GetLocation();
    return -1;
}

// @ 0x00b5b820
int FUN_00b5b820()
{
    GameModeObj* p = (GameModeObj*)FUN_00b3d320();
    if (p) return p->FUN_00ff35d0();
    return -1;
}

// @ 0x00b5b690
void FUN_00b5b690(int v)
{
    int* p = g_1686a18;
    if (p == g_1686a1c) return;
    while (*p != v)
    {
        ++p;
        if (p == g_1686a1c) return;
    }
    if (p != g_1686a1c)
    {
        *p = g_1686a1c[-1];
        --g_1686a1c;
    }
}

// @ 0x00b5b6f0
void FUN_00b5b6f0(int v)
{
    int* p = g_1686a1c;
    if (p < g_1686a20)
    {
        g_1686a1c = p + 1;
        if (p) *p = v;
    }
    else
    {
        ((SPVector_00b96600*)0x1686a18)->FUN_00b96600(g_1686a1c, &v);
    }
}

// @ 0x00b5ca60
bool __fastcall FUN_00b5ca60(int* p)
{
    return *(int*)((char*)p + 0x30) > 0;
}

// @ 0x00b5cb60
bool FUN_00b5cb60(int a, int* p)
{
    void* obj = (void*)*p;
    ((void(__thiscall*)(void*, int))g_vfn(obj, 0x2c))(obj, a);
    return true;
}

// @ 0x00b5cb80
bool FUN_00b5cb80(int a, int* p)
{
    void* obj = (void*)*p;
    ((void(__thiscall*)(void*, int))g_vfn(obj, 0x28))(obj, a);
    return true;
}

// @ 0x00b5cba0
bool FUN_00b5cba0(int a, int* p)
{
    void* sub = (char*)(void*)*p + 8;
    ((void(__thiscall*)(void*, int))g_vfn(sub, 0x14))(sub, a);
    return true;
}

// @ 0x00b5cbc0
bool FUN_00b5cbc0(int a, int* p)
{
    void* sub = (char*)(void*)*p + 8;
    ((void(__thiscall*)(void*, int))g_vfn(sub, 0x10))(sub, a);
    return true;
}

// @ 0x00b5cbe0
bool FUN_00b5cbe0(int a, int* p)
{
    void* obj = (void*)*p;
    ((void(__thiscall*)(void*, int))FUN_00586800)(obj, a);
    return true;
}

// @ 0x00b5cc00
bool FUN_00b5cc00(int a, int* p)
{
    void* obj = (void*)*p;
    ((void(__thiscall*)(void*, int))FUN_005724e0)(obj, a);
    return true;
}

// @ 0x00b5ca50
void FUN_00b5ca50()
{
    void* p = FUN_00b3d3a0();
    ((void(__thiscall*)(void*))g_vfn(p, 0x28))(p);
}

// @ 0x00b5c990
void FUN_00b5c990()
{
    void* a = SP_App_67dd10();
    RegisterAppMode_cGameEditModeStrategy(a);
    FUN_00d3bd70(a);
    RegisterAppMode_SPcTribeModeStrategy(a);
    FUN_00cfa320(a);
    FUN_00fddb40(a);
    RegisterAppMode_cCellMode(a);
    FUN_00b5d3f0(a);
}

// ===========================================================================
// SP::cGonzagoSubsystem
// ===========================================================================

#define V0_CALL(ret, slot, ...) ((ret(__thiscall*)(cGonzagoSubsystem*, ...))vt0[(slot)/4])(this, __VA_ARGS__)

// @ 0x00b5b840
bool cGonzagoSubsystem::CheckGonzagoSubsystemInitState(int param)
{
    if (param != ((int(__thiscall*)(void*))vt0[0x1c / 4])(this)) return false;
    if (param != ((int(__thiscall*)(void*))vt0[0x20 / 4])(this)) return false;
    if (mCurrent != -1) return false;
    return true;
}

// @ 0x00b5b880
void cGonzagoSubsystem::SetTransitionState1(int p)
{
    mPhase = 1;
    if (mCurrent == -1) mCurrent = p;
}

// @ 0x00b5b8a0
void cGonzagoSubsystem::SetTransitionState2(int p)
{
    mPhase = 2;
    if (mCurrent == -1) mCurrent = p;
}

// @ 0x00b5b8c0
void cGonzagoSubsystem::EndTransitionPre()
{
    mPreMode = mCurrent;
    mCurrent = -1;
    mPhase = 0;
}

// @ 0x00b5b8e0
void cGonzagoSubsystem::EndTransitionPost()
{
    mPostMode = mCurrent;
    mCurrent = -1;
    mPhase = 0;
}

// @ 0x00b5b900
void cGonzagoSubsystem::PostGameModeTransition(int, int mode)
{
    if (((int(__thiscall*)(void*))vt0[0x20 / 4])(this) != mode)
    {
        ((void(__thiscall*)(void*, int))vt0[0x44 / 4])(this, mode);
        ((void(__thiscall*)(void*))vt0[0x4c / 4])(this);
    }
}

// @ 0x00b5b930
void cGonzagoSubsystem::PreGameModeTransition(int, int mode)
{
    if (((int(__thiscall*)(void*))vt0[0x1c / 4])(this) != mode)
    {
        ((void(__thiscall*)(void*, int))vt0[0x40 / 4])(this, mode);
        ((void(__thiscall*)(void*))vt0[0x48 / 4])(this);
    }
}

// @ 0x00b5b960
cGonzagoSubsystem::cGonzagoSubsystem()
{
    vt4 = (void**)&g_vt1dummy;
    m08 = 0;
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
    mPreMode = -1;
    mPostMode = -1;
    mCurrent = -1;
    mPhase = 0;
}

// @ 0x00b5b9a0
cGonzagoSubsystem::~cGonzagoSubsystem()
{
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
}

// @ 0x00b5b9b0
void* cGonzagoSubsystem::ScalarDeletingDtor(char flags)
{
    void* self = this;
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
    if (flags & 1) free_00f47380(this);
    return self;
}

// ===========================================================================
// Remaining (complete behaviour / approximations)
// ===========================================================================

// @ 0x00b5b540
bool FUN_00b5b540(int* a, int* b, int, int p4)
{
    int* s = (int*)((int(__thiscall*)(void*))g_vfn(a, 0x10))(a);
    b[2] = s[0];
    b[3] = p4;
    b[4] = s[2];
    int r = ((int(__thiscall*)(void*, unsigned))g_vfn(b, 0xc))(b, 0x532dc8b);
    if (!r) return false;
    int* t = (int*)((int(__thiscall*)(void*))g_vfn(a, 0x18))(a);
    unsigned u = ((unsigned(__thiscall*)(void*))g_vfn(t, 0x1c))(t);
    FUN_004cd3c0((void*)u);
    int q = ((int(__thiscall*)(void*, int, unsigned))g_vfn(t, 0x30))(t, *(int*)(r + 0x18), u);
    return q != -1;
}

struct AdjustThunk_00b5b5d0 {
    void* FUN_00b5b5d0_adjust(unsigned id);
};

// @ 0x00b5b5d0
void* AdjustThunk_00b5b5d0::FUN_00b5b5d0_adjust(unsigned id)
{
    char* self = (char*)this;
    if (id == 0x11416b8) return self - 8;
    if (id == 0x179c807) return (self - 8) ? self : 0;
    return 0;
}

// @ 0x00b5b6c0
void* cGonzagoSimulator_ctor(void* p)
{
    *(int*)((char*)p + 4) = (int)&g_vt0dummy;
    *(int*)((char*)p + 8) = 0x1444434;
    *(int*)((char*)p) = 0x146155c;
    *(int*)((char*)p + 8) = (int)&g_vt1dummy;
    *(char*)((char*)p + 0xc) = 0;
    *(char*)((char*)p + 0xd) = 0;
    *(char*)((char*)p + 0xe) = 0;
    return p;
}

// ---------------------------------------------------------------------------
// Global eastl vector<int> at 0x01686a18 (begin/end/capacity at a18/a1c/a20;
// its allocator object lives at 0x01686a24).
// ---------------------------------------------------------------------------
struct EastlIntVector
{
    int* mpBegin;      // +0x00
    int* mpEnd;        // +0x04
    int* mpCapacity;   // +0x08

    EastlIntVector(int count, void* allocator);   // 0x00b93c60
    void resize(int size);                        // 0x00b98ea0
    void swap(EastlIntVector* other);             // 0x00ebf480
};

// EASTL's heap blocks carry a four-byte owner/size header just before them.
struct EastlBlockHeader { int mOwner; };

static inline int eastl_block_owner(void* p)
{
    return ((EastlBlockHeader*)p)[-1].mOwner;
}

extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);  // 0x011e0744 memmove
extern "C" void  FUN_00f47380(void* p);                                // 0x00f47380 operator delete
extern int g_1686a24;                                                  // vector allocator

// @ 0x00b5b730
void FUN_00b5b730(void)
{
    int* begin = g_1686a18;
    int* end   = g_1686a1c;

    // erase(begin, end): nothing to move, then reset the end pointer
    FUN_011e0744(begin, end, 0);
    g_1686a1c += begin - end;
    if (g_1686a1c - g_1686a18 > 0)
        ((EastlIntVector*)&g_1686a18)->resize(0);

    // rebuild the (now empty) vector through a copy, then swap the stale
    // buffer into the temporary so releasing it frees the old allocation
    EastlIntVector tmp((int)(g_1686a1c - g_1686a18), &g_1686a24);
    tmp.mpEnd = (int*)FUN_011e0744(tmp.mpBegin, g_1686a18,
                                   (unsigned)((char*)g_1686a1c - (char*)g_1686a18))
              + (g_1686a1c - g_1686a18);
    ((EastlIntVector*)&g_1686a18)->swap(&tmp);
    if (tmp.mpBegin && eastl_block_owner(tmp.mpBegin))
        FUN_00f47380(tmp.mpBegin);
}

// ---------------------------------------------------------------------------
// 0x00b5ba30 — refresh the simulator container slots.  With a non-zero
// argument the two global resource keys are rebuilt first (planet key from
// the universe context, avatar species key from the species manager); the
// rest republishes every subsystem's ISimulatorStrategy sub-object.
// ---------------------------------------------------------------------------
struct Key3
{
    int x, y, z;
    Key3() {}
    Key3(int a, int b, int c) : x(a), y(b), z(c) {}
};

struct cSpeciesProfile
{
    char mPad000[0x504];
    int  mAvatarKeyX;    // +0x504
    int  mAvatarKeyY;    // +0x508
    int  mAvatarKeyZ;    // +0x50c
};

struct cSPEditorSpeciesManager
{
    const cSpeciesProfile* GetProfile(const Key3* key);              // 0x004df550
    char GetDefaultReplacementKey(const Key3* key, Key3* out);       // 0x004df790
    void SetAvatarSpecies(const Key3* key);                          // 0x004df310
    const cSpeciesProfile* GetAvatarProfile();                       // 0x004df420
};

struct cPlanetModel
{
    Key3* GetPlanetKey();                                            // 0x00b7e380
    void  SetPlanetKey(const Key3* key, int a, int b);               // 0x00b8d8a0
    void  FUN_010829f0(int value);                                   // 0x010829f0
};

struct cSimulatorSubSystems
{
    void* mp00;                          // +0x00
    void* mpGameViewManager;             // +0x04
    void* mp08;                          // +0x08
    void* mp0c;                          // +0x0c
    void* mpGameInputManager;            // +0x10
    void* mpAStar;                       // +0x14
    void* mpGameBehaviorManager;         // +0x18
    void* mpBundleManager;               // +0x1c
    void* mpGameNounManager;             // +0x20
    void* mpStarManager;                 // +0x24
    void* mpGonzagoPhysics;              // +0x28
    void* mpGameModeManager;             // +0x2c
    void* mpSimTicker;                   // +0x30
    void* mpGamePersistenceManager;      // +0x34
    void* mpPlanetModel;                 // +0x38
    void* mpPlanetImpostorManager;       // +0x3c
    void* mpBlobShadowManager;           // +0x40
    void* mpGameTimeManager;             // +0x44
    void* mpToolManager;                 // +0x48
    void* mpCheatObjectManager;          // +0x4c
    void* mpGamePlantManager;            // +0x50
    void* mpObstacleManager;             // +0x54
    void* mpSpaceGfx;                    // +0x58
    void* mpLivingUniverse;              // +0x5c
    void* mpSpaceTrading;                // +0x60
    void* mpUIEventLog;                  // +0x64
    void* mpUITimeline;                  // +0x68
    void* mpPlantSpeciesManager;         // +0x6c
    void* mpTerraformingManager;         // +0x70
    void* mpFruitManager;                // +0x74
    void* mpAnimalSpeciesManager;        // +0x78
    void* mpCastingManager;              // +0x7c
    void* mpCommGraphicsManager;         // +0x80
    void* mpCommManager;                 // +0x84
    void* mpEventLogCommManager;         // +0x88
    void* mpSpeciesRelationshipManager;  // +0x8c
    void* mpCinematicManager;            // +0x90
    void* mpVignetteManager;             // +0x94
    void* mpNPCCityMusicManager;         // +0x98
    void* mpUIMissionLogManager;         // +0x9c
    void* mpUIMissionCardPanel;          // +0xa0
    void* mpUIAssetDiscoveryManager;     // +0xa4
    void* mpNanoDroneManager;            // +0xa8
    void* mpScenarioVehicleTicker;       // +0xac
};

extern "C" cPlanetModel*         FUN_00b3d350();                      // 0x00b3d350 SP::PlanetModel
extern "C" int                   FUN_01021080();                      // 0x01021080 GetUniverseContext
extern "C" void*                 FUN_00401090();                      // 0x00401090 species manager
extern "C" void*                 FUN_00d1bf00();                      // 0x00d1bf00 GetEditSelection
extern "C" void*                 FUN_00d38840();                      // 0x00d38840 creature strategy
extern "C" void*                 FUN_00cd40b0();                      // 0x00cd40b0 tribe strategy
extern "C" void*                 FUN_00cf74c0();                      // 0x00cf74c0 civ strategy
extern "C" void*                 FUN_00fd9c60();                      // 0x00fd9c60 space strategy
extern "C" void*                 FUN_0067de90();                      // 0x0067de90 telemetry
extern "C" int                   DAT_015e4ef0;                        // 0x015e4ef0 editor base strategy

static Key3* const        g_planetKey        = (Key3*)0x016870e4;      // sPlanetKey
static Key3* const        g_avatarKey        = (Key3*)0x016870f0;      // sAvatarSpecies

// Container slots (data pointers published by the "s*Container" records in
// 0x0131ea90); every value is (subsystem + strategy offset).
static int* const g_cGameTimeManager        = (int*)0x01686aec;
static int* const g_cGameViewManager        = (int*)0x01686ae8;
static int* const g_cPlanetModel            = (int*)0x01686ae4;
static int* const g_cAnimalSpeciesManager   = (int*)0x01686ae0;
static int* const g_cFruitManager           = (int*)0x01686adc;
static int* const g_cObstacleManager        = (int*)0x01686ad8;
static int* const g_cPlantSpeciesManager    = (int*)0x01686ad4;
static int* const g_cGameInputManager       = (int*)0x01686ad0;
static int* const g_cAStar                  = (int*)0x01686acc;
static int* const g_cGameBehaviorManager    = (int*)0x01686ac8;
static int* const g_cGameNounManager        = (int*)0x01686ac4;
static int* const g_cBundleManager          = (int*)0x01686ac0;
static int* const g_cStarManager            = (int*)0x01686abc;
static int* const g_cGonzagoPhysics         = (int*)0x01686ab8;
static int* const g_cGameModeManager        = (int*)0x01686ab4;
static int* const g_cSimTicker              = (int*)0x01686ab0;
static int* const g_cGamePersistenceManager = (int*)0x01686aac;
static int* const g_cToolManager            = (int*)0x01686aa8;
static int* const g_cCheatObjectManager     = (int*)0x01686aa4;
static int* const g_cTerraformingManager    = (int*)0x01686aa0;
static int* const g_cGamePlantManager       = (int*)0x01686a9c;
static int* const g_cSpaceGfx               = (int*)0x01686a98;
static int* const g_cCommGraphicsManager    = (int*)0x01686a94;
static int* const g_cCommManager            = (int*)0x01686a90;
static int* const g_cLivingUniverse         = (int*)0x01686a8c;
static int* const g_cSpaceTrading           = (int*)0x01686a88;
static int* const g_cUIEventLog             = (int*)0x01686a84;
static int* const g_cUITimeline             = (int*)0x01686a80;
static int* const g_cCastingManager         = (int*)0x01686a7c;
static int* const g_cSpeciesRelationshipManager = (int*)0x01686a78;
static int* const g_cPlanetImpostorManager  = (int*)0x01686a74;
static int* const g_cBlobShadowManager      = (int*)0x01686a70;
static int* const g_cCinematicManager       = (int*)0x01686a6c;
static int* const g_cEventLogCommManager    = (int*)0x01686a68;
static int* const g_cVignetteManager        = (int*)0x01686a64;
static int* const g_cNPCCityMusicManager    = (int*)0x01686a60;
static int* const g_cUIMissionLogManager    = (int*)0x01686a5c;
static int* const g_cUIAssetDiscoveryManager = (int*)0x01686a58;
static int* const g_cUIMissionCardPanel     = (int*)0x01686a54;
static int* const g_cNanoDroneManager       = (int*)0x01686a50;
static int* const g_cScenarioVehicleTicker  = (int*)0x01686a4c;
static int* const g_cGameEditModeStrategy   = (int*)0x01686a48;
static int* const g_cCreatureModeStrategy   = (int*)0x01686a44;
static int* const g_cTribeModeStrategy      = (int*)0x01686a40;
static int* const g_cCivModeStrategy        = (int*)0x01686a3c;
static int* const g_cSpaceModeStrategy      = (int*)0x01686a38;
static int* const g_cTelemetry              = (int*)0x01686a34;
static int* const g_cEditorBaseStrategy     = (int*)0x01686a30;

// @ 0x00b5ba30
void FUN_00b5ba30(char rebuildKeys)
{
    if (rebuildKeys)
    {
        Key3 zero1 = Key3(0, 0, 0);
        g_planetKey->x = zero1.x;
        g_planetKey->y = zero1.y;
        g_planetKey->z = zero1.z;
        if (FUN_01021080() == 0)
        {
            Key3* pk = FUN_00b3d350()->GetPlanetKey();
            g_planetKey->x = pk->x;
            g_planetKey->y = pk->y;
            g_planetKey->z = pk->z;
        }

        g_avatarKey->x = 0;
        g_avatarKey->y = 0;
        g_avatarKey->z = 0;
        const cSpeciesProfile* prof =
            ((cSPEditorSpeciesManager*)FUN_00401090())->GetAvatarProfile();
        if (prof)
        {
            g_avatarKey->x = prof->mAvatarKeyX;
            g_avatarKey->y = prof->mAvatarKeyY;
            g_avatarKey->z = prof->mAvatarKeyZ;
        }
    }

    cSimulatorSubSystems* s = (cSimulatorSubSystems*)FUN_00b3d220();
    *g_cGameTimeManager        = (int)s->mpGameTimeManager;
    if (s->mpGameViewManager) *g_cGameViewManager = (int)s->mpGameViewManager + 8; else *g_cGameViewManager = 0;
    if (s->mpPlanetModel) *g_cPlanetModel = (int)s->mpPlanetModel + 4; else *g_cPlanetModel = 0;
    *g_cAnimalSpeciesManager   = (int)s->mpAnimalSpeciesManager;
    if (s->mpFruitManager) *g_cFruitManager = (int)s->mpFruitManager + 4; else *g_cFruitManager = 0;
    if (s->mpObstacleManager) *g_cObstacleManager = (int)s->mpObstacleManager + 4; else *g_cObstacleManager = 0;
    *g_cPlantSpeciesManager    = (int)s->mpPlantSpeciesManager;
    if (s->mpGameInputManager) *g_cGameInputManager = (int)s->mpGameInputManager + 0xc; else *g_cGameInputManager = 0;
    if (s->mpAStar) *g_cAStar = (int)s->mpAStar + 4; else *g_cAStar = 0;
    if (s->mpGameBehaviorManager) *g_cGameBehaviorManager = (int)s->mpGameBehaviorManager + 4; else *g_cGameBehaviorManager = 0;
    if (s->mpGameNounManager) *g_cGameNounManager = (int)s->mpGameNounManager + 4; else *g_cGameNounManager = 0;
    *g_cBundleManager          = (int)s->mpBundleManager;
    *g_cStarManager            = (int)s->mpStarManager;
    if (s->mpGonzagoPhysics) *g_cGonzagoPhysics = (int)s->mpGonzagoPhysics + 4; else *g_cGonzagoPhysics = 0;
    *g_cGameModeManager        = (int)s->mpGameModeManager;
    *g_cSimTicker              = (int)s->mpSimTicker;
    if (s->mpGamePersistenceManager) *g_cGamePersistenceManager = (int)s->mpGamePersistenceManager + 4; else *g_cGamePersistenceManager = 0;
    *g_cToolManager            = (int)s->mpToolManager;
    if (s->mpCheatObjectManager) *g_cCheatObjectManager = (int)s->mpCheatObjectManager + 4; else *g_cCheatObjectManager = 0;
    *g_cTerraformingManager    = (int)s->mpTerraformingManager;
    if (s->mpGamePlantManager) *g_cGamePlantManager = (int)s->mpGamePlantManager + 4; else *g_cGamePlantManager = 0;
    *g_cSpaceGfx               = (int)s->mpSpaceGfx;
    *g_cCommGraphicsManager    = (int)s->mpCommGraphicsManager;
    *g_cCommManager            = (int)s->mpCommManager;
    *g_cLivingUniverse         = (int)s->mpLivingUniverse;
    *g_cSpaceTrading           = (int)s->mpSpaceTrading;
    if (s->mpUIEventLog) *g_cUIEventLog = (int)s->mpUIEventLog + 4; else *g_cUIEventLog = 0;
    if (s->mpUIMissionLogManager) *g_cUITimeline = (int)s->mpUIMissionLogManager + 4; else *g_cUITimeline = 0;
    if (s->mpUITimeline) *g_cCastingManager = (int)s->mpUITimeline + 8; else *g_cCastingManager = 0;
    *g_cSpeciesRelationshipManager = (int)s->mpCastingManager;
    if (s->mpSpeciesRelationshipManager) *g_cPlanetImpostorManager = (int)s->mpSpeciesRelationshipManager + 4; else *g_cPlanetImpostorManager = 0;
    if (s->mpPlanetImpostorManager) *g_cBlobShadowManager = (int)s->mpPlanetImpostorManager + 4; else *g_cBlobShadowManager = 0;
    *g_cCinematicManager       = (int)s->mpBlobShadowManager;
    if (s->mpCinematicManager) *g_cEventLogCommManager = (int)s->mpCinematicManager + 4; else *g_cEventLogCommManager = 0;
    *g_cVignetteManager        = (int)s->mpEventLogCommManager;
    *g_cNPCCityMusicManager    = (int)s->mpVignetteManager;
    *g_cUIMissionLogManager    = (int)s->mpNPCCityMusicManager;
    *g_cUIAssetDiscoveryManager = (int)s->mpUIAssetDiscoveryManager;
    *g_cUIMissionCardPanel     = (int)s->mpUIMissionCardPanel;
    *g_cNanoDroneManager       = (int)s->mpNanoDroneManager;
    *g_cScenarioVehicleTicker  = (int)s->mpScenarioVehicleTicker;

    void* p;
    p = FUN_00d1bf00();
    if (p) *g_cGameEditModeStrategy = (int)p + 8; else *g_cGameEditModeStrategy = 0;
    p = FUN_00d38840();
    if (p) *g_cCreatureModeStrategy = (int)p + 8; else *g_cCreatureModeStrategy = 0;
    p = FUN_00cd40b0();
    if (p) *g_cTribeModeStrategy = (int)p + 0xc; else *g_cTribeModeStrategy = 0;
    p = FUN_00cf74c0();
    if (p) *g_cCivModeStrategy = (int)p + 4; else *g_cCivModeStrategy = 0;
    p = FUN_00fd9c60();
    if (p) *g_cSpaceModeStrategy = (int)p + 8; else *g_cSpaceModeStrategy = 0;
    *g_cTelemetry            = (int)FUN_0067de90();
    *g_cEditorBaseStrategy   = DAT_015e4ef0;
}

struct CVarListSerializer
{
    char mData[0xa14];
    void ctor(const void* owner, void* desc, unsigned id);   // 0x00692f90
    char read(void* stream);                                 // 0x00693e10
};

struct S5be10 { void f(void* stream); };
// @ 0x00b5be10
void S5be10::f(void* stream)
{
    void* self = this;
    FUN_00b5ba30(1);
    char buf[0xa14];
    FUN_00692f90(buf, self, "cmp", 0x1a80d26);
    FUN_00692900(buf, stream);
}

// 0x00b5be60 — read the planet/avatar keys out of a variable list and push
// them into the species manager + planet model.  __thiscall, one stack arg.
struct S5be60
{
    char f(void* stream);
};

// @ 0x00b5be60
char S5be60::f(void* stream)
{
    FUN_00b5ba30(0);

    CVarListSerializer ser;
    ser.ctor(this, (void*)0x0156a118, 0x1a80d26);
    char ok = ser.read(stream);

    if (ok)
    {
        cSPEditorSpeciesManager* mgr = (cSPEditorSpeciesManager*)FUN_00401090();

        if (!mgr->GetProfile(g_avatarKey))
        {
            Key3 key = Key3(0, 0, 0);
            if (mgr->GetDefaultReplacementKey(g_avatarKey, &key))
            {
                int kx = key.x, ky = key.y, kz = key.z;
                g_avatarKey->x = kx;
                g_avatarKey->y = ky;
                g_avatarKey->z = kz;
            }
        }

        mgr->SetAvatarSpecies(g_avatarKey);

        if (g_planetKey->y)
            FUN_00b3d350()->SetPlanetKey(g_planetKey, 0, 1);
    }
    return ok;
}

struct S5bf30 { bool f(); };
// @ 0x00b5bf30
bool S5bf30::f()
{
    void* self = this;
    void* ms = SP_MessageServer_67dcc0();
    *(void**)((char*)self + 0x48) = ms;
    *(void**)((char*)self + 0x4c) = self;
    *(int*)((char*)self + 0x50) = (int)&g_vt0dummy;
    *(int*)((char*)self + 0x54) = 1;
    *(int*)((char*)self + 0x58) = 0;
    if (ms && self)
        ((void(__thiscall*)(void*, void*, unsigned))g_vfn(ms, 0x24))(ms, self, 0xf52feda1);
    FUN_00ec40b0();
    return true;
}

// @ 0x00b5bf80
bool FUN_00b5bf80(void* self, void*)
{
    void* ms = SP_MessageServer_67dcc0();
    *(void**)((char*)self + 0x34) = ms;
    *(void**)((char*)self + 0x38) = self;
    *(int*)((char*)self + 0x3c) = (int)&g_vt0dummy;
    *(int*)((char*)self + 0x40) = 0xc;
    *(int*)((char*)self + 0x44) = 0;
    if (ms && self)
        for (unsigned i = 0; i < 0x30; i += 4)
            ((void(__thiscall*)(void*, void*, int))g_vfn(ms, 0x24))(ms, self, 0);
    void* app = SP_App_67dd10();
    void* q = (void*)((int(__thiscall*)(void*))g_vfn(app, 0x50))(app);
    ((void(__thiscall*)(void*, int, void*))g_vfn(q, 0x20))(q, 0xebb802, (void*)&FUN_00b13b20);
    FUN_00b6a530();
    FUN_00c103f0();
    FUN_00d1f2a0();
    return true;
}

// @ 0x00b5c9d0
int FUN_00b5c9d0(void* p)
{
    unsigned v = (unsigned)p;
    if (v > 0x1654c10)
    {
        if (v == 0x2ccd1d2) return (int)p;
        if (v == 0x8916f92d) return 0x1654c11;
        if (v != 0xfffffffe) return -1;
    }
    else
    {
        if (v == 0x1654c10) return (int)p;
        if (v <= 0x1654c06)
        {
            if (v >= 0x1654c04) return (int)p;
            if (v == 0xdbdba1) return 0xdbdba1;
            if (v <= 0x1654bff) return -1;
            if (v <= 0x1654c02) return (int)p;
            return -1;
        }
        if (v != 0x1654c08) return -1;
    }
    return (int)p;
}

// @ 0x00b5ca70
bool FUN_00b5ca70()
{
    int m = FUN_00b5b800();
    if (m == -1) return false;
    for (;;)
    {
        if (m == 0x1654c00 || m == 0x1654c01 || m == 0x1654c02 ||
            m == 0x1654c04 || m == 0x1654c05) return true;
        if (m == 0x1654c10 && *(int*)(0x16c7aa4 + 0xd0) == 2) return true;
        if (m == 0xdbdba1)
        {
            m = FUN_00574570();
            if (m == -1) return false;
            continue;
        }
        return false;
    }
}

// @ 0x00b5cb20
bool FUN_00b5cb20(int p)
{
    if (!FUN_00dd18d0(p)) return false;
    if (FUN_00b5b800() == 0xdbdba1 && FUN_00b5ca70()) return false;
    return true;
}

// @ 0x00b5cc80
void FUN_00b5cc80()
{
    void* gt = SP_GameTimeManager_00b3d380();
    ((void(__thiscall*)(void*))g_vfn(gt, 0))(gt);
    FUN_00b32190(0x600c4ae, 3, "cinematicAll");
    FUN_00b32190(0x4bf38a5, 1, "cinematic");
    FUN_00b32190(0x64beb65, 1, "tutorial");
    FUN_00b32190(0x4bf38a6, 1, "editor");
    FUN_00b32190(0x4d02e35, 3, "comm screen");
    FUN_00b32190(0x7e9e4b7, 1, "adventure dialog");
    FUN_00b323f0(gt);
}

struct S5cd90 { void f(int); };
// @ 0x00b5cd90
void S5cd90::f(int param)
{
    char* self = (char*)this;
    unsigned n = (unsigned)((*(char**)(self + 0x60) - *(char**)(self + 0x5c)) >> 2);
    for (unsigned i = 0; i < n; ++i)
    {
        void* e = ((void**)*(void**)(self + 0x5c))[i];
        ((void(__thiscall*)(void*, int))g_vfn(e, 0x30))(e, param);
    }
}

// @ 0x00b5cde0
bool FUN_00b5cde0(int p)
{
    void* app = SP_App_67dd10();
    void* q = (void*)((int(__thiscall*)(void*))g_vfn(app, 0x50))(app);
    ((void(__thiscall*)(void*, int))g_vfn(q, 0x34))(q, p);
    void* r = FUN_00b3d220();
    if (!r) return false;
    app = SP_App_67dd10();
    q = (void*)((int(__thiscall*)(void*))g_vfn(app, 0x50))(app);
    void* s = (void*)((int(__thiscall*)(void*))g_vfn(q, 0x38))(q);
    if (s)
    {
        int v = ((int(__thiscall*)(void*, unsigned))g_vfn(s, 0xc))(s, 0x11966ed);
        *(int*)((char*)r + 0xc) = v;
        return v != 0;
    }
    *(int*)((char*)r + 0xc) = 0;
    return false;
}

// ---------------------------------------------------------------------------
// 0x00b5ce70 — per-frame update of the Gonzago simulator.
// ---------------------------------------------------------------------------
struct EAStopwatch
{
    long long mnStartTime;         // +0x00
    long long mnTotalElapsedTime;  // +0x08
    int       mnUnits;             // +0x10
    float     mfCyclesToUnits;     // +0x14

    EAStopwatch(int units, bool useRdtsc);   // 0x0093a560
    void Start();                            // 0x00435480
    long long GetElapsed();                  // 0x0093a3a0
};

struct cTimeScaler     { void FUN_00ea53b0(float scale); };   // 0x00ea53b0
struct cEventLogObj    { void FUN_00dd8d80(int value); };     // 0x00dd8d80
struct cUniverseObj    { int  FUN_00ac68e0(int value); };     // 0x00ac68e0
struct cSpaceGfxObj    { void FUN_00c2e4e0(); };              // 0x00c2e4e0

struct CAchievementsController
{
    void AutoTest(unsigned id, int value);                    // 0x00676e90
};

extern "C" void* FUN_00b3d290();                              // 0x00b3d290
extern "C" void* FUN_00b3d3e0();                              // 0x00b3d3e0 EventLog
extern "C" void* FUN_00675250();                              // 0x00675250 Achievements::Controller
extern "C" int   FUN_01021080();                              // 0x01021080 GetUniverseContext

static unsigned char* const g_p1686af2 = (unsigned char*)0x01686af2;
static unsigned char* const g_p1686af3 = (unsigned char*)0x01686af3;
static unsigned char* const g_p1686af4 = (unsigned char*)0x01686af4;
static unsigned char* const g_p156b5d0 = (unsigned char*)0x0156b5d0;
static unsigned char* const g_p1569d48 = (unsigned char*)0x01569d48;

struct cGonzagoSimulatorFrame
{
    void* mpVt0;             // +0x00
    void* mpVt4;             // +0x04
    void* mp08;              // +0x08
    char   mb0c;             // +0x0c
    char   mbActive;         // +0x0d
    char   mb0e;             // +0x0e
    char   mPad0f;           // +0x0f
    float  mfFrameTime;      // +0x10
    float  mfBlendedTime;    // +0x14
    int    mPad18;           // +0x18
    void*  mpTimeScaler;     // +0x1c

    void Update(unsigned dt);
};

// @ 0x00b5ce70
void cGonzagoSimulatorFrame::Update(unsigned dt)
{
    if (!mbActive)
        return;

    if (mpTimeScaler)
        ((cTimeScaler*)mpTimeScaler)->FUN_00ea53b0((float)dt * 0.001f);

    switch (FUN_00b5b800())
    {
    case 0x1654c00:
    case 0x1654c01:
    case 0x1654c02:
    case 0x1654c04:
    case 0x1654c05:
        ((CAchievementsController*)FUN_00675250())->AutoTest(0x54cf0c2c, (int)dt);
        ((CAchievementsController*)FUN_00675250())->AutoTest(0x257c7f6, (int)dt);
        break;
    case 0xdbdba1:
        ((CAchievementsController*)FUN_00675250())->AutoTest(0xbaebb1d6, (int)dt);
        break;
    }

    if (FUN_00b5b800() == 0x1654c00)
        return;

    EAStopwatch sw(0, false);
    sw.Start();

    ((cEventLogObj*)FUN_00b3d3e0())->FUN_00dd8d80(0);

    if (FUN_01021080() == 0)
        ((cUniverseObj*)FUN_00b3d290())->FUN_00ac68e0(2);

    unsigned char flag = *g_p1686af3;
    if (*g_p1686af2 || flag)
        FUN_00b3d350()->FUN_010829f0(flag);

    char tick = *g_p1569d48;
    if (*g_p156b5d0 || (*g_p156b5d0 = 1, !tick))
        *g_p156b5d0 = tick;

    if (*g_p1686af4)
        ((cSpaceGfxObj*)FUN_00b3d290())->FUN_00c2e4e0();

    long long elapsed = sw.GetElapsed();
    float frame = ((float)elapsed * sw.mfCyclesToUnits) * 0.001f;
    mfFrameTime = frame;
    float blended = mfBlendedTime * 0.9f;
    mfBlendedTime = blended + frame * 0.1f;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
