// Slice s00cf6df0 -- Spore Simulator cCivModeStrategy cluster.
//
// Modelled types (retail member offsets are read from the disassembly; the PDB
// layout differs, so objects are modelled locally with role-named members and
// explicit padding for the untouched gaps):
//   cCivModeStrategy   civilization mode strategy (tutorial counters/dialogue)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef int            i32;

#define FORCEINLINE __forceinline

// --------------------------------------------------------------- extern decls
extern "C" void  *SP_NounManager();                         // 0x00b3d300
extern "C" void  *GetTriggerMgr();                          // 0x00b3d4d0
extern "C" void  *CheatManager();                           // 0x0067de20
extern "C" void  *SP_GetTerrainSphere();                    // 0x00f67d90 cTerrainEditor::GetCurrentTerrainSphere
extern "C" i32    FUN_00c75420(void *o);                    // 0x00c75420
extern "C" void  *GetPlayerCivilization(void *mgr);         // 0x00b25fb0
extern "C" bool   FUN_007cd9c0(void *o);                    // 0x007cd9c0
extern "C" bool   FUN_007cfac0(void *o);                    // 0x007cfac0

extern const float kOne;             // 0x1485720 = 1.0f

// ============================================================ cCivModeStrategy
struct cCivModeStrategy {
    void **m_vtbl;              // +0x00
    u8     m_pad04[0xb0];
    u32    m_fieldB4;           // +0xb4
    u8     m_padB8[0x58];
    void  *m_dialogue110;       // +0x110
    void  *m_dialogue114;       // +0x114
    u32    m_dialogue118;       // +0x118
    u32    m_dialogue11c;       // +0x11c

    void  ClearDialogue();      // 0x00cf7a30
    bool  IsNotCivEventA();     // 0x00cf7a40
    void  SetDialogueTimed(u32); // 0x00cf7a10
    bool  CanBuildSeaVehicles(); // 0x00cf75d0
    bool  CanBuildAirVehicles(); // 0x00cf7600
    void *AsInterface(u32 iid);  // 0x00cf7490
    bool  IsEitherDialogueIdle(); // 0x00cf7880
    void *FindBuildableVehicle(u32 arg); // 0x00cf7d40
    int   HasCivTutorialOccurred(u32 id); // 0x00cf7830
    void  OnMouseDown(u32 a, float x, float y, u32 b); // 0x00cf7380
    void  OnMouseMove(float x, float y, u32 a);        // 0x00cf73d0
    void  OnMouseUp(u32 a, float x, float y, u32 b);   // 0x00cf7420
    void  DoCVGCompletionAchievements();               // 0x00cf7630
};

// @ 0x00cf7a30
void cCivModeStrategy::ClearDialogue()
{
    m_dialogue11c = 0;
    m_dialogue118 = 0;
}

// @ 0x00cf7a40
bool cCivModeStrategy::IsNotCivEventA()
{
    return m_fieldB4 != 10;
}

// @ 0x00cf7a10
void cCivModeStrategy::SetDialogueTimed(u32 id)
{
    m_dialogue11c = 0xfa;
    m_dialogue118 = id;
}

// @ 0x00cf7360
void ShutdownGonzagoSubsystem()
{
    void *cm = CheatManager();
    void **vtbl = *(void ***)cm;
    typedef void (__thiscall *ExecFn)(void *self, const char *cmd);
    ((ExecFn)vtbl[0x1c / 4])(cm, "globalthermonuclearwar");
}

// @ 0x00cf75d0
bool cCivModeStrategy::CanBuildSeaVehicles()
{
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    if (civ != 0) {
        return *(i32 *)((u8 *)civ + 0x298) >= 4;
    }
    return false;
}

// @ 0x00cf7600
bool cCivModeStrategy::CanBuildAirVehicles()
{
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    if (civ != 0) {
        return *(i32 *)((u8 *)civ + 0x298) >= 3;
    }
    return false;
}

// @ 0x00cf7490
void *cCivModeStrategy::AsInterface(u32 iid)
{
    if (iid == 0x0116d389) {
        return this;
    }
    if (iid == 0x2f009dd0 && this != 0) {
        return (u8 *)this + 0x20;
    }
    return 0;
}

// @ 0x00cf7a50
extern const float kDefaultTerrainA;   // 0x169ca8c
extern const float kDefaultTerrainB;   // 0x169ca88
extern const float kDefaultTerrainC;   // 0x169ca84

float GetTerrainEditModeHeight()
{
    void *sphere = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    i32 mode = ((i32 (__thiscall *)(void *))FUN_00c75420)(sphere);
    switch (mode) {
    case 0: return kDefaultTerrainC;
    case 2: return kDefaultTerrainA;
    }
    return kDefaultTerrainB;
}

// @ 0x00cf7a90
bool IsCivTriggerActive()
{
    i32 kind = *(i32 *)((u8 *)GetTriggerMgr() + 0x2c);
    if (kind != 1 && kind != 2) {
        return false;
    }
    if (*(u32 *)((u8 *)GetTriggerMgr() + 0x148) != 0x5fdca7a2) {
        if (*(u32 *)((u8 *)GetTriggerMgr() + 0x148) != 0xb1ea776a) {
            return false;
        }
    }
    return true;
}

// @ 0x00cf7880
bool cCivModeStrategy::IsEitherDialogueIdle()
{
    if (!((bool (__thiscall *)(void *))FUN_007cd9c0)(m_dialogue110)
        && !((bool (__thiscall *)(void *))FUN_007cfac0)(m_dialogue110)) {
        return false;
    }
    if (((bool (__thiscall *)(void *))FUN_007cd9c0)(m_dialogue114)
        || ((bool (__thiscall *)(void *))FUN_007cfac0)(m_dialogue114)) {
        return true;
    }
    return false;
}

// @ 0x00cf78d0
extern "C" i32 FUN_00bd81d0(void *city);      // 0x00bd81d0 cCity::GetVehicleSpecialty
extern "C" void FUN_00bd91e0(void *city);      // 0x00bd91e0

bool IsCityVehicleSpecialtyMismatch()
{
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    void *city = *(void **)((u8 *)civ + 0x44c);
    i32 spec = ((i32 (__thiscall *)(void *))FUN_00bd81d0)(city);
    i32 cur = *(i32 *)((u8 *)city + 0x29c);
    if ((cur == 0 && spec != 0)
        || (cur == 1 && spec != cur)
        || (cur == 2 && spec != cur)) {
        FUN_00bd91e0(city);
        return true;
    }
    return false;
}

// @ 0x00cf7d40
struct Vec4Arr {
    void **m_begin;     // +0x00
    void **m_end;       // +0x04
};

struct SubObj {
    void **m_vtbl;      // +0x00
};

void *cCivModeStrategy::FindBuildableVehicle(u32 arg)
{
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    Vec4Arr *vec = (Vec4Arr *)((u8 *)civ + 0xb0);
    u32 count = (u32)(vec->m_end - vec->m_begin);
    u32 i = 0;
    if (count != 0) {
        u8 bl = (u8)arg;
        for (; i < count; i++) {
            void *elem = vec->m_begin[i];
            if (*(u32 *)((u8 *)elem + 0xb1c) != 0) continue;
            if (bl == 0) break;
            SubObj *sub = (SubObj *)((u8 *)elem + 0x34);
            if (((u8 (__thiscall *)(SubObj *))sub->m_vtbl[0x50 / 4])(sub) == 1) break;
        }
    }
    u32 n = (u32)(vec->m_end - vec->m_begin);
    if (i >= n) {
        return 0;
    }
    return vec->m_begin[i];
}

// --------------------------------------------------------------- civ-event data
// A 12-byte request record used by the terrain-sphere event store.
struct CivEventReq {
    u32 m_id;       // +0x00
    u32 m_pad04;    // +0x04
    u32 m_hash;     // +0x08 (0xaa9a8ed7)
};

extern "C" bool FUN_00c78420();                                 // 0x00c78420 (thiscall)
extern "C" bool FUN_00c77c50();                                 // 0x00c77c50 (thiscall)

// @ 0x00cf77f0
void __stdcall MarkCivEventAsOccurred(u32 id)
{
    CivEventReq req;
    req.m_id = id;
    req.m_pad04 = 0;
    req.m_hash = 0xaa9a8ed7;
    void *sphere = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (sphere != 0) {
        ((bool (__thiscall *)(void *, CivEventReq *))FUN_00c78420)(sphere, &req);
    }
}

// @ 0x00cf7830
int cCivModeStrategy::HasCivTutorialOccurred(u32 id)
{
    CivEventReq req;
    req.m_id = id;
    req.m_pad04 = 0;
    req.m_hash = 0xaa9a8ed7;
    void *sphere = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (sphere != 0) {
        if (((bool (__thiscall *)(void *, CivEventReq *))FUN_00c77c50)(sphere, &req)) {
            return 1;
        }
    }
    return 0;
}

// ------------------------------------------------------------------ property list
extern "C" u32 FNVHash(const char *s, u32 seed, int flag);      // 0x00932e80
extern "C" bool FUN_006a25a0();                                // 0x006a25a0 cDirectPropertyList::GetDescription (thiscall)
extern u32 g_propList15fd918;                                   // 0x015fd918

// @ 0x00cf6e30
u32 FUN_00cf6e30()
{
    void *list = (void *)g_propList15fd918;
    typedef bool (__thiscall *GetDescFn)(void *self, u32 hash);
    bool present = ((GetDescFn)FUN_006a25a0)(list, 0x61b67b6);
    if (present) {
        return FNVHash("CVG-CamRotate-MAC", 0x811c9dc5, 1);
    }
    return FNVHash("CVG-CamRotate", 0x811c9dc5, 1);
}

// --------------------------------------------------------------- pause gate
extern "C" void  *GameTimeManager();                            // 0x00b3d380
extern "C" void  *FUN_00b3d4f0();                               // 0x00b3d4f0
extern "C" void   FUN_00b32250();                               // 0x00b32250
extern "C" void   FUN_00e2f270();                               // 0x00e2f270

// @ 0x00cf6df0
void FUN_00cf6df0()
{
    void *gtm = GameTimeManager();
    typedef void (__thiscall *DecPauseFn)(void *self, u32 hash);
    ((DecPauseFn)FUN_00b32250)(gtm, 0x4bf38a7);
    while (*(u32 *)((u8 *)FUN_00b3d4f0() + 0x54) != 0) {
        typedef void (__thiscall *StepFn)(void *self, int v);
        ((StepFn)FUN_00e2f270)(FUN_00b3d4f0(), 0);
    }
}

// --------------------------------------------------------------- city purchase
extern "C" void  *FUN_00b25c30();                               // 0x00b25c30
extern "C" void   FUN_00bddda0();                               // 0x00bddda0 cCity method (thiscall)
extern "C" float  FUN_00bf2170();                               // 0x00bf2170 cCivilization method (thiscall)
extern "C" void   FUN_00bef710();                               // 0x00bef710 cCivilization::SpendMoney (thiscall)

struct Sphere115c {
    u32 m_x;    // +0x115c
    u32 m_y;    // +0x1160
    u32 m_z;    // +0x1164
};

// @ 0x00cf7150
struct Vec3f { u32 x, y, z; };

void FUN_00cf7150()
{
    void *city = ((void *(__thiscall *)(void *))FUN_00b25c30)(SP_NounManager());
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    void *sphere = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    ((void (__thiscall *)(void *, i32, int, Vec3f, int))FUN_00bddda0)(
        city, ((i32 (__thiscall *)(void *))FUN_00bd81d0)(city), 0,
        *(Vec3f *)((u8 *)sphere + 0x115c), 0);
    float cost = ((float (__thiscall *)(void *, i32, int))FUN_00bf2170)(civ, ((i32 (__thiscall *)(void *))FUN_00bd81d0)(city), 0);
    ((void (__thiscall *)(void *, float))FUN_00bef710)(civ, cost);
}

// --------------------------------------------------------------- mouse forwarding
extern "C" void *GameInputManager();    // 0x00b3d250
extern "C" void  FUN_00697ab0();        // 0x00697ab0 cLocalInputState::OnMouseDown (thiscall)
extern "C" void  FUN_00697af0();        // 0x00697af0 cLocalInputState::OnMouseUp   (thiscall)
extern "C" void  FUN_00697b20();        // 0x00697b20 cLocalInputState::OnMouseWheel (thiscall)

// @ 0x00cf7380
void cCivModeStrategy::OnMouseDown(u32 a, float x, float y, u32 b)
{
    typedef void (__thiscall *LISFn)(void *self, u32 a, float x, float y, u32 b);
    ((LISFn)FUN_00697ab0)((u8 *)this + 0x68, a, x, y, b);
    void *gim = GameInputManager();
    typedef void (__thiscall *GimFn)(void *self, u32 a, float x, float y, u32 b);
    ((GimFn)(*(void ***)gim)[0x54 / 4])(gim, a, x, y, b);
}

// @ 0x00cf73d0
void cCivModeStrategy::OnMouseMove(float x, float y, u32 a)
{
    typedef void (__thiscall *LISFn)(void *self, float x, float y, u32 a);
    ((LISFn)FUN_00697b20)((u8 *)this + 0x68, x, y, a);
    void *gim = GameInputManager();
    typedef void (__thiscall *GimFn)(void *self, float x, float y, u32 a);
    ((GimFn)(*(void ***)gim)[0x5c / 4])(gim, x, y, a);
}

// @ 0x00cf7420
void cCivModeStrategy::OnMouseUp(u32 a, float x, float y, u32 b)
{
    typedef void (__thiscall *LISFn)(void *self, u32 a, float x, float y, u32 b);
    ((LISFn)FUN_00697af0)((u8 *)this + 0x68, a, x, y, b);
    void *gim = GameInputManager();
    typedef void (__thiscall *GimFn)(void *self, u32 a, float x, float y, u32 b);
    ((GimFn)(*(void ***)gim)[0x58 / 4])(gim, a, x, y, b);
}

// --------------------------------------------------------------- civ ratios
extern const float kCivRatioConst;      // 0x1471064
extern const float kZero;               // 0x1485378
extern "C" float FUN_00bf1880();        // 0x00bf1880 cCivilization method (thiscall)

// @ 0x00cf7090
float FUN_00cf7090()
{
    float result = kCivRatioConst;
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    if (civ == 0) {
        return result;
    }
    float a = ((float (__thiscall *)(void *, u32))FUN_00bf1880)(civ, 0xa35d0f5);
    float b = ((float (__thiscall *)(void *, u32))FUN_00bf1880)(civ, 0x6aeb96a1);
    float c = ((float (__thiscall *)(void *, u32))FUN_00bf1880)(civ, 0x3360727f);
    float lo1 = (b > a) ? a : b;
    float m = (c > lo1) ? lo1 : c;
    result = m;
    if (m > kZero) {
        result = m / (c + b + a);
    }
    return result;
}

// --------------------------------------------------------------- serializer table
extern u8   g_serTable[];               // 0x168caf0 .. 0x168cb44 (stride 0x1c)
extern u32  g_serVersion;               // 0x145f8dc
extern "C" bool WriteUint32();          // 0x0093aa70 EA::IO::WriteUint32 (cdecl)
extern "C" bool ReadInt32();            // 0x0093a780 EA::IO::ReadInt32 (cdecl)
extern "C" void FUN_00befc00(void *stream, void *elem);   // 0x00befc00 write one record
extern "C" void FUN_00befbc0(void *stream, void *elem);   // 0x00befbc0 read one record

// @ 0x00cf7710
bool FUN_00cf7710(void *stream)
{
    u32 version = 3;
    void *o1 = ((void *(__thiscall *)(void *))(*(void ***)stream)[0x20 / 4])(stream);
    void *o2 = ((void *(__thiscall *)(void *))(*(void ***)o1)[0x18 / 4])(o1);
    ((bool (__cdecl *)(void *, u32 *, int, int))WriteUint32)(o2, &version, 1, 0);
    u8 *p = g_serTable;
    while (p < (u8 *)0x168cb44) {
        FUN_00befc00(stream, p);
        p += 0x1c;
    }
    return true;
}

// @ 0x00cf7770
bool FUN_00cf7770(void *stream)
{
    if (g_serVersion < 0x1c0007) {
        return true;
    }
    u32 version = 0;
    void *o1 = ((void *(__thiscall *)(void *))(*(void ***)stream)[0x20 / 4])(stream);
    void *o2 = ((void *(__thiscall *)(void *))(*(void ***)o1)[0x18 / 4])(o1);
    ((bool (__cdecl *)(void *, u32 *, int, int))ReadInt32)(o2, &version, 1, 0);
    if (version != 3) {
        return false;
    }
    u8 *p = g_serTable;
    while (p < (u8 *)0x168cb44) {
        FUN_00befbc0(stream, p);
        p += 0x1c;
    }
    return true;
}

// --------------------------------------------------------------- achievements
extern "C" void *AchievementsController();      // 0x00675250
extern "C" i32   FUN_00bf01f0();                // 0x00bf01f0 count_specialty_cities (thiscall)
extern "C" void  FUN_00676e90();                // 0x00676e90 Achievements::Controller::AutoTest (thiscall)
extern "C" void  FUN_00676710();                // 0x00676710 Achievements::Controller::AwardAchievement (thiscall)
extern "C" bool  FUN_00c772c0();                // 0x00c772c0 (thiscall)

// @ 0x00cf7630
void cCivModeStrategy::DoCVGCompletionAchievements()
{
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    void *ctrl = AchievementsController();
    typedef i32  (__thiscall *CountFn)(void *self, int idx, int flag);
    typedef void (__thiscall *AutoTestFn)(void *self, u32 hash, i32 count);
    typedef void (__thiscall *AwardFn)(void *self, u32 hash);
    ((AutoTestFn)FUN_00676e90)(ctrl, 0x256ed7f6, ((CountFn)FUN_00bf01f0)(civ, 0, 0));
    ((AutoTestFn)FUN_00676e90)(ctrl, 0x78d05a36, ((CountFn)FUN_00bf01f0)(civ, 1, 0));
    ((AutoTestFn)FUN_00676e90)(ctrl, 0xc15fda9b, ((CountFn)FUN_00bf01f0)(civ, 2, 0));
    ((AutoTestFn)FUN_00676e90)(ctrl, 0xb2352dc5, 1);
    void *sphere = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (*(u32 *)((u8 *)sphere + 0x128c) < 0x36ee80) {
        ((AwardFn)FUN_00676710)(ctrl, 0x6a5c80e9);
    }
    u32 kHash = 0x5dd433e;
    if (!((bool (__thiscall *)(void *, u32))FUN_00c772c0)(
            ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager()), kHash)) {
        ((AwardFn)FUN_00676710)(ctrl, 0x9d649052);
    }
    void *sphere3 = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (((i32 (__thiscall *)(void *))FUN_00c75420)(sphere3) == 2) {
        ((AwardFn)FUN_00676710)(ctrl, 0xa7b1c920);
    }
}

// --------------------------------------------------------------- spice tutorial
extern "C" void  FUN_0067caf0();            // 0x0067caf0 (cdecl)
extern "C" void  FUN_0067aaf0();            // 0x0067aaf0 (thiscall)
extern "C" void  FUN_00b32220();            // 0x00b32220 IncPauseGate (thiscall)
extern "C" void *SP_ConfigManager();        // 0x0067dd30
extern const float kNegOne;                 // 0x13eb1bc
struct V3 { float x, y, z; };
extern u32 g_1581b48, g_1581b4c, g_1581b50;
extern u8  g_1581bd0;

// @ 0x00cf7920
void FUN_00cf7920()
{
    CivEventReq req;
    req.m_id = 0x6307841;
    req.m_pad04 = 0;
    req.m_hash = 0xaa9a8ed7;
    void *sphere = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (sphere != 0) {
        if (((bool (__thiscall *)(void *, CivEventReq *))FUN_00c77c50)(sphere, &req)) {
            return;
        }
    }
    req.m_id = 0x6307841;
    req.m_pad04 = 0;
    req.m_hash = 0xaa9a8ed7;
    void *sphere2 = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (sphere2 != 0) {
        ((bool (__thiscall *)(void *, CivEventReq *))FUN_00c78420)(sphere2, &req);
    }
    void *cfg = SP_ConfigManager();
    u32 v = ((u32 (__thiscall *)(void *, u32))(*(void ***)cfg)[0x30 / 4])(cfg, 0x4ea96cb);
    if (v == 0) {
        return;
    }
    {
        typedef void (__thiscall *IncFn)(void *self, u32 hash);
        ((IncFn)FUN_00b32220)(GameTimeManager(), 0x4bf38a7);
    }
    typedef void (__thiscall *StepFn)(void *self);
    ((StepFn)FUN_0067aaf0)(((void *(__cdecl *)(u32, u32, u32, void *, int, int, int, int))FUN_0067caf0)(
        g_1581b48, g_1581b4c, g_1581b50, &g_1581bd0, 0xbf800000, 0xbf800000, 0, 0));
}

// --------------------------------------------------------------- city strategies
extern "C" void  *g_opNew();                 // 0x00f473a0 operator new
extern "C" void  *FUN_00cf4ca0();            // 0x00cf4ca0 cCityInputStrategy ctor (thiscall)
extern "C" void  *FUN_00ceb090();            // 0x00ceb090 cCityDisplayStrategy ctor (thiscall)
extern "C" void   FUN_00cea090();            // 0x00cea090 cCityDisplayStrategy::Init (thiscall)
extern "C" void   FUN_00cf14d0();            // 0x00cf14d0 (thiscall)
extern "C" void   FUN_00cf4c00();            // 0x00cf4c00 (thiscall)
extern "C" void   FUN_00cf1500();            // 0x00cf1500 (thiscall)
extern "C" void   FUN_00b22960();            // 0x00b22960 cGNM2::ProcessPending (thiscall)
extern "C" void  *FUN_0067cab0();            // 0x0067cab0
extern "C" void   FUN_00801bb0();            // 0x00801bb0 CurMgr::FindLocal (thiscall)
extern "C" void  *FUN_00b3d230();            // 0x00b3d230
extern "C" void   FUN_00b5cde0();            // 0x00b5cde0 (thiscall)
extern "C" void  *SP_GetCameraCtl();         // 0x00b3d280
extern "C" void   FUN_00cf28f0();            // 0x00cf28f0 cCityInputStrategy::SetDefaultPickPriorities
extern "C" void   FUN_00b316d0();            // 0x00b316d0 (thiscall)
extern const float k42c80000;                // 0x13ec4d0 == 100.0f
extern const float kCamPitch789;             // 0x169cb78
extern const float kCamPitch77c;             // 0x169cb7c
extern const float kCamPitch780;             // 0x169cb80
extern const float kCamPitch784;             // 0x169cb84

// @ 0x00cf71d0
void __fastcall FUN_00cf71d0(void *self, void * /*edx*/, u32 arg)
{
    u8 *s = (u8 *)self;
    if (*(void **)(s + 0xe8) == 0) {
        void *p = ((void *(__cdecl *)(u32, const char *, int, int, int, int))g_opNew)(
            0x148, "Simulator/cCityInputStrategy", 0, 0, 0, 0);
        if (p != 0) {
            typedef void *(__thiscall *CtorFn)(void *, void *);
            p = ((CtorFn)FUN_00cf4ca0)(p, self);
        }
        *(void **)(s + 0xe8) = p;
    }
    void *in = *(void **)(s + 0xe8);
    if (in != 0) {
        ((void (__thiscall *)(void *))(*(void ***)in)[1])(in);
        if (arg == 0xdbdba1) {
            ((void (__thiscall *)(void *))FUN_00cf14d0)(*(void **)(s + 0xe8));
        }
        void *cfg = SP_ConfigManager();
        u32 q = ((u32 (__thiscall *)(void *, u32))(*(void ***)cfg)[0x30 / 4])(cfg, 0x679b873);
        ((void (__thiscall *)(void *, u32))FUN_00cf4c00)(*(void **)(s + 0xe8), q);
    }
    void *gim = GameInputManager();
    ((void (__thiscall *)(void *, void *, int, int))(*(void ***)gim)[0x20 / 4])(
        gim, (u8 *)*(void **)(s + 0xe8) + 4, 0, 0);
    ((void (__thiscall *)(void *))FUN_00b22960)(SP_NounManager());
    if (*(void **)(s + 0xec) == 0) {
        void *p = ((void *(__cdecl *)(u32, const char *, int, int, int, int))g_opNew)(
            0x120, "Simulator/cCityDisplayStrategy", 0, 0, 0, 0);
        if (p != 0) {
            typedef void *(__thiscall *CtorFn)(void *, void *);
            p = ((CtorFn)FUN_00ceb090)(p, self);
        }
        *(void **)(s + 0xec) = p;
        ((void (__thiscall *)(void *))FUN_00cea090)(p);
    }
    if (arg != 0xdbdba1) {
        ((void (__thiscall *)(void *, int))FUN_00cf1500)(*(void **)(s + 0xe8), 1);
    }
    void *cm = FUN_0067cab0();
    ((void (__thiscall *)(void *, u32))FUN_00801bb0)(cm, 0x1002);
    void *v = FUN_00b3d230();
    ((void (__thiscall *)(void *, u32))FUN_00b5cde0)(v, 0xe3057616);
    void *cam = SP_GetCameraCtl();
    *(float *)((u8 *)cam + 0x380) = k42c80000;
    cam = SP_GetCameraCtl();
    *(u32 *)((u8 *)cam + 0x384) = 0x3e9;
    ((void (__thiscall *)(void *))FUN_00cf28f0)(*(void **)(s + 0xe8));
    ((void (__thiscall *)(void *, float, float, float, float))FUN_00b316d0)(
        GameTimeManager(), kCamPitch789, kCamPitch77c, kCamPitch780, kCamPitch784);
}

// --------------------------------------------------------------- gameplay events
extern u32 g_1581bb4, g_1581bb8, g_1581bbc;
extern u32 g_1581bc0, g_1581bc4, g_1581bc8;
extern u8  g_1581bcc;

// @ 0x00cf7520
struct U3 { u32 x, y, z; };

void FUN_00cf7520()
{
    ((void (__thiscall *)(void *, u32))FUN_00b32220)(GameTimeManager(), 0x4bf38a7);
    typedef void (__thiscall *StepFn)(void *self);
    V3 f = { -1.0f, -1.0f, 0.0f };
    U3 g1 = { g_1581bb4, g_1581bb8, g_1581bbc };
    ((StepFn)FUN_0067aaf0)(((void *(__cdecl *)(U3, void *, int, V3, int, int))FUN_0067caf0)(
        g1, &g_1581bcc, 0, f, 0, 0));
    U3 g2 = { g_1581bc0, g_1581bc4, g_1581bc8 };
    ((StepFn)FUN_0067aaf0)(((void *(__cdecl *)(U3, void *, int, V3, int, int))FUN_0067caf0)(
        g2, &g_1581bd0, 0, f, 0, 0));
}

// --------------------------------------------------------------- pause drain
extern "C" i32  FUN_00b320d0();          // 0x00b320d0 GetPauseGateCount (thiscall)
extern "C" void FUN_00b32250();          // 0x00b32250 DecPauseGate (thiscall)
extern "C" void *FUN_0067cac0();         // 0x0067cac0
extern "C" void  FUN_0067c8c0();         // 0x0067c8c0 (thiscall)

static void MarkCivEventId(u32 id)
{
    CivEventReq req;
    req.m_id = id;
    req.m_pad04 = 0;
    req.m_hash = 0xaa9a8ed7;
    void *sphere = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (sphere != 0) {
        ((bool (__thiscall *)(void *, CivEventReq *))FUN_00c78420)(sphere, &req);
    }
}

// @ 0x00cf7ad0
void __fastcall FUN_00cf7ad0(void *self, void * /*edx*/)
{
    *(u8 *)((u8 *)self + 0x148) = 0;
    if (((i32 (__thiscall *)(void *, u32))FUN_00b320d0)(GameTimeManager(), 0x64beb65) > 0) {
        do {
            ((void (__thiscall *)(void *, u32))FUN_00b32250)(GameTimeManager(), 0x64beb65);
        } while (((i32 (__thiscall *)(void *, u32))FUN_00b320d0)(GameTimeManager(), 0x64beb65) > 0);
    }
    while (*(u32 *)((u8 *)FUN_00b3d4f0() + 0x54) != 0) {
        typedef void (__thiscall *StepFn)(void *self, int v);
        ((StepFn)FUN_00e2f270)(FUN_00b3d4f0(), 0);
    }
    MarkCivEventId(0x64e6666);
    MarkCivEventId(0x64e666f);
    MarkCivEventId(0x64e6671);
    MarkCivEventId(0x64e6673);
    MarkCivEventId(0x64e6674);
    MarkCivEventId(0x64e6676);
    MarkCivEventId(0x64e6678);
    MarkCivEventId(0x64e6679);
    void *list = (void *)g_propList15fd918;
    typedef bool (__thiscall *GetDescFn)(void *self, u32 hash);
    u32 h;
    if (((GetDescFn)FUN_006a25a0)(list, 0x61b67b6)) {
        h = FNVHash("CVG-CamRotate-MAC", 0x811c9dc5, 1);
    } else {
        h = FNVHash("CVG-CamRotate", 0x811c9dc5, 1);
    }
    ((void (__thiscall *)(void *, u32))FUN_0067c8c0)(((void *(__cdecl *)(u32, int))FUN_0067cac0)(h, 1), 0);
    ((void (__thiscall *)(void *, u32))FUN_0067c8c0)(((void *(__cdecl *)(u32, int))FUN_0067cac0)(0x5f011813, 1), 0);
    ((void (__thiscall *)(void *, u32))FUN_0067c8c0)(((void *(__cdecl *)(u32, int))FUN_0067cac0)(0xdb5f195a, 1), 0);
    ((void (__thiscall *)(void *, u32))FUN_0067c8c0)(((void *(__cdecl *)(u32, int))FUN_0067cac0)(0x90382acc, 1), 0);
}

// --------------------------------------------------------------- civ hue
extern const float kTwoj;       // 0x1470f1c == 2.0f
extern const float kThird;      // 0x13f26dc == 0.33333334f
extern const float kTwoThird;   // 0x140e87c == 0.6666667f
extern const float kOne;        // 0x1485720 == 1.0f
extern const float kNegThird;   // 0x140d0cc == -0.33333334f

// @ 0x00cf6e70
float FUN_00cf6e70()
{
    float local = 0.0f;
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    if (civ != 0) {
        float fVar6 = ((float (__thiscall *)(void *, u32))FUN_00bf1880)(civ, 0xa35d0f5);
        float fVar1 = ((float (__thiscall *)(void *, u32))FUN_00bf1880)(civ, 0x6aeb96a1);
        float fVar2 = ((float (__thiscall *)(void *, u32))FUN_00bf1880)(civ, 0x3360727f);
        if (fVar6 > fVar2 && fVar2 < fVar1) {
            float fVar7 = ((fVar1 / (fVar1 + fVar6)) * kTwoj) * kThird + kTwoThird;
            if (kOne < fVar7) {
                return (fVar2 / ((fVar2 + fVar1) + fVar6)) * kThird + (fVar7 - kTwoj);
            }
            return fVar7 - (fVar2 / ((fVar2 + fVar1) + fVar6)) * kThird;
        }
        if (fVar1 < fVar6 && fVar1 < fVar2) {
            float fVar7 = ((fVar6 / (fVar2 + fVar6)) * kTwoj) * kThird;
            float fVar6b = (fVar1 / ((fVar2 + fVar1) + fVar6)) * kThird;
            if (kThird < fVar7) {
                return fVar6b + fVar7;
            }
            return fVar7 - fVar6b;
        }
        if (fVar6 < fVar1 && fVar6 < fVar2) {
            float fVar7 = -(((fVar1 / (fVar2 + fVar1)) * kTwoj) * kThird);
            float fVar6b = (fVar6 / ((fVar2 + fVar1) + fVar6)) * kThird;
            if (fVar7 < kNegThird) {
                return fVar7 - fVar6b;
            }
            return fVar6b + fVar7;
        }
        if (0.0f < fVar6) {
            return kTwoThird;
        }
        if (0.0f < fVar1) {
            local = -kTwoThird;
        }
    }
    return local;
}
