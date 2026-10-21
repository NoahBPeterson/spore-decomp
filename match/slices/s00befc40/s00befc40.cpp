// match/slices/s00befc40/s00befc40.cpp
// Slice s00befc40 -- Simulator "city / civilization helper" cluster.  The module
// also holds SP::cCity (see s00be9d60 UpdateLanes) and Simulator::cCommunity
// (s00bfd9f0); this slice is the set of small helpers that operate on a
// civilization's city vector plus the SimSingleton / city-music plumbing and the
// "civic timer" state machine driven by the comm-event hooks.
//
// Every function takes `this` in ecx (retail `mov esi,ecx` / `[ecx+N]`), so the
// whole set is modelled as __thiscall members of one stub struct carrying the
// retail field offsets and the vtable slots the disassembly addresses.  Callees
// without a name are declared (never defined) so a real `call rel32` is emitted
// and MSVC cannot fold them away; each callee's calling convention is taken from
// its own `ret N`.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- /Isrc/game/include
#include "s00befc40.h"
#include <math.h>

typedef unsigned int  u32;
typedef signed   int  i32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------
// Callees / singletons (free, __cdecl)
// ---------------------------------------------------------------------------
void* __cdecl SP_NounManager();                        // 0x00b3d300
void* __cdecl SP_RelationshipManager();                // 0x00b3d2c0
void* __stdcall SP_PlanetModel(void* pos);             // 0x00b3d350 ret 4
void* __cdecl SP_CommManager();                        // 0x00b3d4a0
void* __cdecl SP_MessageServer();                      // 0x0067dcc0
void* __cdecl SP_ActivePlanet();                       // 0x01021260
void* __cdecl EA_Allocate(unsigned n, const char* tag, int a, int b, int c, int d); // 0x00f473a0

struct PhaseRatioStub { float FUN_00bfdea0(); };        // 0x00bfdea0 (ret 0)
int   __cdecl FUN_00b6f0c0(int id);                    // 0x00b6f0c0 ret 4
void  __cdecl FUN_00be9850(int a, int b);              // 0x00be9850 ret 8
struct NoopStub { void FUN_00bef850(); };               // 0x00bef850 ret 0
void* __cdecl FUN_00b3d300();                          // 0x00b3d300 NounManager (ECX-safe alias)

// ---------------------------------------------------------------------------
// Callee stubs -- calling convention from each callee's own `ret N`.
// ---------------------------------------------------------------------------
struct NounMgrStub {
    void* FUN_00b21410(void* a);                       // 0x00b21410 ret 4
    int   FUN_00b20790(int id);                        // 0x00b20790 ClassifyById ret 4
    void  FUN_00b23560(void* a);                       // 0x00b23560 ret 4
    void* FUN_00b25f40(int id);                        // 0x00b25f40 ret 4
    void* FUN_00b25ca0();                              // 0x00b25ca0 GetCivilizationList ret 0
    void* FUN_00b25fb0();                              // 0x00b25fb0 GetPlayerCivilization ret 0
};

struct TerrainSphereStub {
    int FUN_00c75420();                                // 0x00c75420 terrain mode, ret 0
};

struct PlanetMgrStub {
    TerrainSphereStub* FUN_00f67d90();                 // 0x00f67d90 GetCurrentTerrainSphere ret 0
};

static inline TerrainSphereStub* GetTerrainSphere()
{
    return ((PlanetMgrStub*)SP_NounManager())->FUN_00f67d90();
}

struct CityStub {
    int FUN_00bd8210();                                // 0x00bd8210 GetContinent ret 0
    int FUN_00bd81d0();                                // 0x00bd81d0 GetVehicleSpecialty ret 0
    int FUN_00bd9bf0();                                // 0x00bd9bf0 GetCivilization ret 0
    void* FUN_00bd92d0();                              // 0x00bd92d0 ret 0
    u8  FUN_00bdb880(int a);                           // 0x00bdb880 ret 4
};

struct PlanetObj {
    int FUN_00b88590();                                // 0x00b88590 GetContinent ret 0
    int FUN_00fa0e00();                                // 0x00fa0e00 GetPositionPtr ret 0
};

struct TimerStub {
    void      FUN_00bc3130();                          // 0x00bc3130 cSPTimer::Restart
    void      FUN_00bc3170();                          // 0x00bc3170 reset
    long long FUN_00bc3190();                          // 0x00bc3190 GetElapsedTime
};

struct CommMgrStub {
    u8    FUN_00ae9f10(void* a);                       // 0x00ae9f10 SpaceTool::MatchesCiv ret 4
    u8    FUN_00ae9390();                              // 0x00ae9390 ret 0
    void  FUN_00aeb760(int a, void* b, void* c, int d, int e, int f); // 0xaeb760 ret 0x18
};

struct StarRefStub {
    void* FUN_00ce6950(int a, int b, int c);           // 0x00ce6950 GetCommContext ret 0xc
};

struct RelMgrStub {
    float FUN_00d00a10(int a, int b, int c);           // 0x00d00a10 ret 0xc
};

struct TuningStub {
    void FUN_00cfe7a0(int a, int v);                   // 0x00cfe7a0 ret 8
};

struct CommEventMgrStub {
    void FUN_00cf9040(int a, int b, int c, void* d);   // 0x00cf9040 ret 0x10
};

void* __cdecl FUN_00cf74c0(int a, int b, int c, void* d); // 0x00cf74c0 ret 0x10

// A ref-counted object (AddRef at vtable +0, Release at vtable +4).
struct CtorStub {
    CtorStub* SimSingleton_ctor();                     // 0x00ae5c30
    void CityMusic_ctor();                             // 0x00eb0ea0
};

struct RefObj {
    virtual void AddRef();           // +0x00
    virtual void Release();          // +0x04
};

// The object handed in as a stack argument (a civ / city noun).
struct CivObject {
    void** vt;                                         // +0x00 (+0x48 get-id, +0x4c get-specialty)
    char pad04[0x8d - 0x04];
    u8   m8d;                                          // +0x8d
    char pad8e[0x1ec - 0x8e];
    int  m1ec;                                         // +0x1ec
    char pad1f0[0x234 - 0x1f0];
    int  m234;                                         // +0x234
};

// A city object: a +0x120 sub-object with a transform vtable.
struct CityObj {
    void** vt;
    char pad04[0x120 - 0x04];
    void* m120;                                        // +0x120
};

// ---------------------------------------------------------------------------
// The stub class shared by all 23 members.
// ---------------------------------------------------------------------------
struct CStub {
    void** vt;                                         // +0x00
    char pad04[0x38 - 0x04];
    void* m38;                                         // +0x38
    char pad3c[0x40 - 0x3c];
    int  m40;                                          // +0x40
    char pad44[0x89 - 0x44];
    u8   m89;                                          // +0x89
    u8   m8a;                                          // +0x8a
    char pad8b[0x98 - 0x8b];
    float m98;                                         // +0x98
    int  m9c;                                          // +0x9c city-vector begin
    int  ma0;                                          // +0xa0 city-vector end
    char pada4[0xc4 - 0xa4];
    float mc4;                                         // +0xc4
    float mc8;                                         // +0xc8
    float mcc;                                         // +0xcc
    char pad_d0[0x274 - 0xd0];
    void* m274;                                        // +0x274
    char pad278[0x2a0 - 0x278];
    int     m2a0;                                      // +0x2a0
    RefObj* m2a4;                                      // +0x2a4
    RefObj* m2a8;                                      // +0x2a8
    RefObj* m2ac;                                      // +0x2ac
    char    m2b0[0x20];                                // +0x2b0 cSPTimer
    RefObj* m2d0;                                      // +0x2d0
    char    pad2d4[0x2d8 - 0x2d4];
    char    m2d8[0x20];                                // +0x2d8 cSPTimer
    RefObj* m2f8;                                      // +0x2f8
    char    pad2fc[0x300 - 0x2fc];
    char    m300[0x20];                                // +0x300 cSPTimer
    char    m320;                                      // +0x320
    char    pad321[0x328 - 0x321];
    char    m328[0x20];                                // +0x328 cSPTimer
    char    m348;                                      // +0x348
    char    pad349[0x350 - 0x349];
    char    m350[0x20];                                // +0x350 cSPTimer
    char    m370;                                      // +0x370
    char    pad371[0x378 - 0x371];
    char    m378[0x20];                                // +0x378 cSPTimer
    char    m398;                                      // +0x398
    char    pad399[0x3a0 - 0x399];
    char    m3a0[0x20];                                // +0x3a0 cSPTimer
    char    m3c0;                                      // +0x3c0
    char    pad3c1[0x3c8 - 0x3c1];
    char    m3c8[0x20];                                // +0x3c8 cSPTimer
    char    m3e8;                                      // +0x3e8
    char    pad3e9[0x3f0 - 0x3e9];
    char    m3f0[0x20];                                // +0x3f0 cSPTimer
    char    pad410[0x434 - 0x410];
    unsigned m434;                                     // +0x434
    void*    m438;                                     // +0x438
    int      m43c;                                     // +0x43c
    void*    m440;                                     // +0x440
    int      m444;                                     // +0x444
    float    m448;                                     // +0x448

    void  FUN_00befc40(CivObject* src);                // 0x00befc40
    void  FUN_00befd80(float f, u8 flag);              // 0x00befd80
    void* FUN_00befee0(float* pos, int skip);          // 0x00befee0
    u8    FUN_00beff90(float* pos, int specialty);     // 0x00beff90
    u8    FUN_00bf00a0(int continent, int specialty);  // 0x00bf00a0
    u8    FUN_00bf0110(void* a, int city);            // 0x00bf0110
    u8    FUN_00bf0130(CStub* other);                  // 0x00bf0130
    int   FUN_00bf01f0(int specialty, u8 flag);        // 0x00bf01f0
    int   FUN_00bf0260(int arg);                       // 0x00bf0260
    void  FUN_00bf02b0(void* arg, int b, int c, int d); // 0x00bf02b0
    void  FUN_00bf0330(void* city);                    // 0x00bf0330
    void  FUN_00bf03e0(CivObject* city, float f);      // 0x00bf03e0
    void  FUN_00bf04c0(u8 enable);                     // 0x00bf04c0
    float FUN_00bf0640(CivObject* object);             // 0x00bf0640
    float FUN_00bf06d0(int arg);                       // 0x00bf06d0
    void  FUN_00bf0710(int index, RefObj* a, RefObj* b);// 0x00bf0710
    void  FUN_00bf07c0();                              // 0x00bf07c0
    void  FUN_00bf0810(void* a, ...);                  // 0x00bf0810 caller cleans
    void  FUN_00bf08b0();                              // 0x00bf08b0
    void  FUN_00bf0a60(RefObj* p);                     // 0x00bf0a60
    void  FUN_00bf0b00(RefObj* p);                     // 0x00bf0b00
    void  FUN_00bf0b70(RefObj* p);                     // 0x00bf0b70

    int cityCount() { return (ma0 - m9c) >> 2; }
};

// cSPTimer helpers usable from within the members above.
static inline void timerReset(void* p) { ((TimerStub*)p)->FUN_00bc3170(); }

// globals
extern void* g_167a60c;                                // 0x167a60c SimSingleton
extern float g_1485378;                                // 0x1485378
extern float g_1486374;                                // 0x1486374
extern float g_13ec480;                                // 0x13ec480
extern float g_13eb1c0;                                // 0x13eb1c0
extern float g_13ec434;                                // 0x13ec434
extern float g_1488874;                                // 0x1488874
extern float g_146933c;                                // 0x146933c 3.4e38
extern float g_1469358;                                // 0x1469358
extern float g_168c514;                                // 0x168c514
extern float g_168c518;                                // 0x168c518
extern float g_168c51c;                                // 0x168c51c
extern float g_1485720;                                // 0x1485720 1.0f
extern float g_13ec4d0;                                // 0x13ec4d0
extern float g_146935c;                                // 0x146935c 1200.0f
extern float g_1471064;                                // 0x1471064
extern void* g_169d3c8;                                // 0x169d3c8 CommEventMgr
extern int   g_1570840[256];                           // 0x1570840 tuning weights
extern const char g_13f09b4[];                         // 0x13f09b4 "Simulator"
extern const char g_145f924[];                         // 0x145f924 "Simulator/SimSingleton"

// ===========================================================================
// @ 0x00befc40
// Fold `src`'s state into this simulator object and lazily create the city
// music player.
// ===========================================================================
void CStub::FUN_00befc40(CivObject* src)
{
    NounMgrStub* nm = (NounMgrStub*)SP_NounManager();
    int specialty = (**(int(__thiscall**)(CivObject*))(*(void***)src + 0x4c / 4))(src);
    (**(void(__thiscall**)(CStub*, int))(*(void***)this + 0x48 / 4))(this, specialty);
    nm->FUN_00b21410(src);
    if (nm->FUN_00b20790(specialty) < 5)
        nm->FUN_00b23560(this);

    m40 = src->m234;
    int* cr = (int*)FUN_00b6f0c0(src->m234);
    mc4 = *(float*)(cr + 0);
    mc8 = *(float*)(cr + 1);
    mcc = *(float*)(cr + 2);

    if (m274 == 0) {
        void* ms = SP_MessageServer();
        (**(void(__thiscall**)(void*, void*, int))(*(void***)ms + 0x20 / 4))(ms, (char*)this + 0x38, 0x20c089c);
        void* p = EA_Allocate(0x220, g_13f09b4, 0, 0, 0, 0);
        if (p) ((CtorStub*)p)->CityMusic_ctor();
        if (p != m274) {
            if (p) ((RefObj*)p)->AddRef();
            void* old = m274;
            m274 = p;
            if (old) ((RefObj*)old)->Release();
        }
    }
}

// ===========================================================================
// @ 0x00befd30
// SimSingleton accessor: lazily construct, return the +0xac member.
// ===========================================================================
void* SimSingletonAccessor_00befd30()
{
    if (g_167a60c == 0) {
        CtorStub* p = (CtorStub*)EA_Allocate(0xc8, g_145f924, 0, 0, 0, 0);
        if (p) {
            g_167a60c = p->SimSingleton_ctor();
            return *(void**)((char*)g_167a60c + 0xac);
        }
        g_167a60c = 0;
    }
    return *(void**)((char*)g_167a60c + 0xac);
}

// ===========================================================================
// @ 0x00befd80
// Accumulate the building radius over time, scaled by the terrain mode and the
// two flags.
// ===========================================================================
void CStub::FUN_00befd80(float f, u8 flag)
{
    NounMgrStub* nm;
    int civ;
    int mode;

    // early-out: no update requested, or already tracking
    if (flag == 0 || f <= g_1485378 || m89 != 0)
        goto add;

    nm = (NounMgrStub*)SP_NounManager();
    civ = (int)nm->FUN_00b25fb0();
    if (civ == 0) goto add;

    if (*(u8*)(civ + 0x8d) != 0) {
        if (m8a == 0) goto arm_28;
        goto arm_d8;
    } else {
        if (m8a != 0) goto arm_67;
        goto arm_d8;
    }

arm_d8:
    nm = (NounMgrStub*)SP_NounManager();
    mode = GetTerrainSphere()->FUN_00c75420();
    switch (mode) {
    case 0:  f = f * g_13ec480; goto add;   // 0.2
    case 1:  f = f * g_13ec434; goto add;   // 0.4
    case 2:  f = f * g_1486374; goto add;   // 0.8
    default: goto add;
    }

arm_28:
    nm = (NounMgrStub*)SP_NounManager();
    mode = GetTerrainSphere()->FUN_00c75420();
    switch (mode) {
    case 0:  f = f * g_13ec434; goto add;   // 0.4
    case 1:  f = f * g_1486374; goto add;   // 0.8
    case 2:  f = f * g_13eb1c0; goto add;   // 1.2
    default: goto add;
    }

arm_67:
    nm = (NounMgrStub*)SP_NounManager();
    mode = GetTerrainSphere()->FUN_00c75420();
    switch (mode) {
    case 0:  f = f * g_1488874; goto add;
    case 1:  f = f * g_13ec480; goto add;   // 0.2
    case 2:  f = f * g_13ec434; goto add;   // 0.4
    default: goto add;
    }

add:
    f = f + m98;
    m98 = f;
    if (f > g_1469358) m98 = g_1469358;
}

// ===========================================================================
// @ 0x00befee0
// Nearest non-skipped city to `pos`, by Euclidean distance.
// ===========================================================================
void* CStub::FUN_00befee0(float* pos, int skip)
{
    float best = g_146933c;
    void* found = 0;
    int* it = (int*)m9c;
    int* end = (int*)ma0;
    for (; it != end; ++it) {
        int c = *it;
        if (c == skip) continue;
        float* p = (float*)(**(int(__thiscall**)(int))(*(int*)(c + 0x120) + 0x2c))(c + 0x120);
        float dx = p[0] - pos[0];
        float dy = p[1] - pos[1];
        float dz = p[2] - pos[2];
        float d = sqrtf(dx * dx + dy * dy + dz * dz);
        if (d < best) { best = d; found = (void*)c; }
    }
    return found;
}

// ===========================================================================
// @ 0x00beff90
// Does the civ own a city on `pos`'s continent whose vehicle specialty matches?
// ===========================================================================
u8 CStub::FUN_00beff90(float* pos, int specialty)
{
    if (pos[0] == g_168c514 && pos[1] == g_168c518 && pos[2] == g_168c51c)
        return 0;

    int n = cityCount();
    for (int i = 0; i < n; ++i) {
        CityObj* city = (CityObj*)*(int*)(m9c + i * 4);
        float* p = (float*)((PlanetObj*)city)->FUN_00fa0e00();
        if (p[0] == g_168c514 && p[1] == g_168c518 && p[2] == g_168c51c)
            continue;
        int contA = ((PlanetObj*)SP_PlanetModel((void*)((PlanetObj*)city)->FUN_00fa0e00()))->FUN_00b88590();
        int contB = ((PlanetObj*)SP_PlanetModel(pos))->FUN_00b88590();
        if (contA == contB) {
            if (specialty == -1) return 1;
            if (((CityStub*)city)->FUN_00bd81d0() == specialty) return 1;
        }
    }
    return 0;
}

// ===========================================================================
// @ 0x00bf00a0
// Is there a city on `continent` with the given vehicle specialty?
// ===========================================================================
u8 CStub::FUN_00bf00a0(int continent, int specialty)
{
    int n = cityCount();
    for (int i = 0; i < n; ++i) {
        CityObj* city = (CityObj*)*(int*)(m9c + i * 4);
        if (((CityStub*)city)->FUN_00bd8210() == continent) {
            if (specialty == -1) return 1;
            if (((CityStub*)city)->FUN_00bd81d0() == specialty) return 1;
        }
    }
    return 0;
}

// ===========================================================================
// @ 0x00bf0110
// Convenience: look up `city`'s continent, then search.
// ===========================================================================
u8 CStub::FUN_00bf0110(void* a, int city)
{
    return FUN_00bf00a0(((CityStub*)a)->FUN_00bd8210(), city);
}

// ===========================================================================
// @ 0x00bf0130
// Do this and `other` share a continent?
// ===========================================================================
u8 CStub::FUN_00bf0130(CStub* other)
{
    int nA = cityCount();
    for (int i = 0; i < nA; ++i) {
        int contA = ((CityStub*)*(int*)(m9c + i * 4))->FUN_00bd8210();
        int nB = other->cityCount();
        for (int j = 0; j < nB; ++j) {
            if (((CityStub*)*(int*)(other->m9c + j * 4))->FUN_00bd8210() == contA)
                return 1;
        }
    }
    return 0;
}

// ===========================================================================
// @ 0x00bf01f0
// Count cities with the given vehicle specialty (optionally only "not yet
// converted").
// ===========================================================================
int CStub::FUN_00bf01f0(int specialty, u8 flag)
{
    int count = 0;
    int n = cityCount();
    for (int i = 0; i < n; ++i) {
        CityObj* city = (CityObj*)*(int*)(m9c + i * 4);
        if (city == 0) continue;
        if (((CityStub*)city)->FUN_00bd81d0() != specialty) continue;
        if (flag != 0 && *(u8*)((char*)city + 0x519) != 0) continue;
        ++count;
    }
    return count;
}

// ===========================================================================
// @ 0x00bf0260
// Count non-null cities accepted by the predicate.
// ===========================================================================
int CStub::FUN_00bf0260(int arg)
{
    int count = 0;
    int n = cityCount();
    for (int i = 0; i < n; ++i) {
        CityObj* city = (CityObj*)*(int*)(m9c + i * 4);
        if (city == 0) continue;
        if (((CityStub*)city)->FUN_00bdb880(arg)) ++count;
    }
    return count;
}

// ===========================================================================
// @ 0x00bf02b0
// Civic-padding hand-off: if neither this object nor `arg` is already doing it,
// start the padding timer on whichever of the two is the player's own civ.
// ===========================================================================
void CStub::FUN_00bf02b0(void* arg, int b, int c, int d)
{
    (void)b; (void)c; (void)d;
    NounMgrStub* nm = (NounMgrStub*)SP_NounManager();
    void* src = nm->FUN_00b25f40((int)arg);
    nm = (NounMgrStub*)SP_NounManager();
    void* player = nm->FUN_00b25fb0();

    if ((**(u8(__thiscall**)(CStub*))(*(void***)this + 0x2c / 4))(this)) return;
    if (src == 0) return;
    if ((**(u8(__thiscall**)(void*))(*(void***)src + 0x2c / 4))(src)) return;

    if (this == player) {
        *(u8*)((char*)src + 0x398) = 1;
        ((TimerStub*)((char*)src + 0x3a0))->FUN_00bc3130();
        return;
    }
    if (src == player)
        ((NoopStub*)this)->FUN_00bef850();
}

// ===========================================================================
// @ 0x00bf0330
// Comm hook: fire the "embassy" event when the object becomes interesting.
// ===========================================================================
void CStub::FUN_00bf0330(void* city)
{
    if (!(**(u8(__thiscall**)(int))(*(int*)((char*)city + 0x120) + 0x58))((int)city + 0x120)) return;
    if (m434 <= 4) return;
    if (m438 != 0) return;

    void* cm = SP_CommManager();
    m434 = 0;
    m438 = city;

    void* edi = ((CityStub*)city)->FUN_00bd92d0();
    if (edi == 0) edi = (void*)(**(int(__thiscall**)(CStub*, int))(*(void***)this + 0xc / 4))(this, 0x17f243b);
    else {
        void* r = (**(void*(__thiscall**)(void*, int))(*(void***)edi + 0xc / 4))(edi, 0x17f243b);
        edi = r;
        if (r == 0) edi = (void*)(**(int(__thiscall**)(CStub*, int))(*(void***)this + 0xc / 4))(this, 0x17f243b);
    }

    void* planet = SP_ActivePlanet();
    void* ctx = ((StarRefStub*)((char*)planet + 0x13c))->FUN_00ce6950(0xdbf385bf, 0x832b3aa4, 0);
    ((CommMgrStub*)cm)->FUN_00aeb760((int)edi, city, ctx, 0xdbf385bf, 0x832b3aa4, 0);
}

// ===========================================================================
// @ 0x00bf03e0
// Second comm hook: arm the "native gift" event.
// ===========================================================================
void CStub::FUN_00bf03e0(CivObject* city, float f)
{
    if (m440 != 0) return;
    if ((**(u8(__thiscall**)(void*))(*(int*)((char*)city + 0x120) + 0x58))(city)) {
        m440 = city;
        return;
    }

    void* cm = SP_CommManager();
    void* mgr = g_169d3c8;
    ((TuningStub*)mgr)->FUN_00cfe7a0(0, 0x7d00);
    ((TuningStub*)mgr)->FUN_00cfe7a0(1, 0x5dc0);
    ((TuningStub*)mgr)->FUN_00cfe7a0(2, 0x3e80);
    ((TuningStub*)mgr)->FUN_00cfe7a0(3, 0x1f40);
    ((TuningStub*)mgr)->FUN_00cfe7a0(4, 0x0fa0);
    m444 = 0;
    m448 = f;

    void* planet = SP_ActivePlanet();
    void* ctx = ((StarRefStub*)((char*)planet + 0x13c))->FUN_00ce6950(0xdbf385bf, 0xe05d0481, 0);
    int civ = ((CityStub*)city)->FUN_00bd9bf0();
    ((CommMgrStub*)cm)->FUN_00aeb760(civ, city, ctx, 0xdbf385bf, 0xe05d0481, 0);
    m440 = city;
}

// ===========================================================================
// @ 0x00bf04c0
// Tear down the arming done by 0x00bf03e0, optionally firing the event first.
// ===========================================================================
void CStub::FUN_00bf04c0(u8 enable)
{
    void* target = m440;
    if (target == 0) return;

    if (enable != 0) {
        float v = (float)m444;
        int id = (**(int(__thiscall**)(CStub*, float))(*(void***)this + 0x4c / 4))(this, v);
        FUN_00be9850((int)target, id);
        if (m89 != 0) {
            float pos[4];
            pos[0] = mc4; pos[1] = mc8; pos[2] = mcc; pos[3] = g_1485720;
            void* p = (**(void*(__thiscall**)(int, float*, int, int))(*(int*)((char*)m440 + 0x120) + 0x2c))((int)m440 + 0x120, pos, 0, 0);
            void* strat = FUN_00cf74c0((int)m440, 0x664d26ce, 0xaa9a8ed7, p);
            ((CommEventMgrStub*)strat)->FUN_00cf9040((int)m440, 0x664d26ce, 0xaa9a8ed7, p);
        }
    } else {
        *(int*)((char*)target + 0x75c) = -1;
        *(float*)((char*)target + 0x758) = 0.0f;
        if (m89 != 0) {
            float pos[4];
            pos[0] = mc4; pos[1] = mc8; pos[2] = mcc; pos[3] = g_1485720;
            void* p = (**(void*(__thiscall**)(int, float*, int, int))(*(int*)((char*)m440 + 0x120) + 0x2c))((int)m440 + 0x120, pos, 0, 0);
            void* strat = FUN_00cf74c0((int)m440, 0x1e920e12, 0xaa9a8ed7, p);
            ((CommEventMgrStub*)strat)->FUN_00cf9040((int)m440, 0x1e920e12, 0xaa9a8ed7, p);
        }
    }

    m43c = -1;
    m440 = 0;
    m444 = 0;
    m448 = 0.0f;
}

// ===========================================================================
// @ 0x00bf0640
// Weighted relation score for `object`.
// ===========================================================================
float CStub::FUN_00bf0640(CivObject* object)
{
    int id = (**(int(__thiscall**)(CivObject*))(*(void***)object + 0x4c / 4))(object);
    if (id == -1) return 0.0f;

    int mine = (**(int(__thiscall**)(CStub*, int))(*(void***)this + 0x4c / 4))(this, 1);
    int theirs = (**(int(__thiscall**)(CivObject*, int))(*(void***)object + 0x4c / 4))(object, mine);
    void* rel = SP_RelationshipManager();
    float v = ((RelMgrStub*)rel)->FUN_00d00a10(theirs, mine, 1);
    float w = v * 100.0f + g_146935c;
    float base;
    if (w > 0.0f) {
        base = w;
    } else {
        base = 0.0f;
    }
    float t = ((PhaseRatioStub*)(size_t)object)->FUN_00bfdea0();
    return (t + g_1485720) * g_1471064 * base;
}

// ===========================================================================
// @ 0x00bf06d0
// Weighted city-count score: phase * (cityCount * 600 + 1400).
// ===========================================================================
float CStub::FUN_00bf06d0(int arg)
{
    int n = (ma0 - m9c) >> 2;
    float weight = (float)(n * 600 + 0x578);
    float t = ((PhaseRatioStub*)(size_t)arg)->FUN_00bfdea0();
    return (t + g_1485720) * g_1471064 * weight;
}

// ===========================================================================
// @ 0x00bf0710
// Replace the current "best" index and the two ref-counted payloads, but only
// when the new index outranks the old one.
// ===========================================================================
void CStub::FUN_00bf0710(int index, RefObj* a, RefObj* b)
{
    void* cm = SP_CommManager();
    if (((CommMgrStub*)cm)->FUN_00ae9f10(this)) return;
    if (m2a0 != -1 && g_1570840[m2a0] > g_1570840[index]) return;

    m2a0 = index;
    if (a != m2a4) {
        if (a) a->AddRef();
        RefObj* old = m2a4;
        m2a4 = a;
        if (old) old->Release();
    }
    if (b != m2a8) {
        if (b) b->AddRef();
        RefObj* old = m2a8;
        m2a8 = b;
        if (old) old->Release();
    }
}

// ===========================================================================
// @ 0x00bf07c0
// Clear the "best" selection and release the two payloads.
// ===========================================================================
void CStub::FUN_00bf07c0()
{
    int none = -1;
    m2a0 = none;
    RefObj* a = m2a4;
    m2a4 = 0;
    if (a) a->Release();
    RefObj* b = m2a8;
    m2a8 = 0;
    if (b) b->Release();
}
// ===========================================================================
// @ 0x00bf0810
// Fire the comm event for the currently selected entry and clear it.
// ===========================================================================
void CStub::FUN_00bf0810(void* a, ...)
{
    void* cm = SP_CommManager();
    if (((CommMgrStub*)cm)->FUN_00ae9390()) return;

    int index = m2a0;
    RefObj* pa = m2a4;
    RefObj* pb = m2a8;
    int what = -1;

    if (index == 0) {
        what = 0x822e8de4;
    } else if (index == 1) {
        what = 0xa1566b04;
    } else if (index == 2) {
        what = 0x2ab3e3ad;
        m3e8 = 0;
        timerReset(m3f0);
    } else {
        pa = (RefObj*)this;
        pb = 0;
    }

    void* planet = SP_ActivePlanet();
    void* ctx = ((StarRefStub*)((char*)planet + 0x13c))->FUN_00ce6950(0xdbf385bf, what, 0);
    ((CommMgrStub*)cm)->FUN_00aeb760((int)pa, pb, ctx, 0xdbf385bf, what, 0);
}

// ===========================================================================
// @ 0x00bf08b0
// Expire the eight civic timers (600000 ms each) and the "best entry" timer.
// ===========================================================================
void CStub::FUN_00bf08b0()
{
    long long t;

    t = ((TimerStub*)m2b0)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        RefObj* vm2ac = m2ac; if (vm2ac) { m2ac = 0; vm2ac->Release(); }
        ((TimerStub*)m2b0)->FUN_00bc3170();
    }

    t = ((TimerStub*)m2d8)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        RefObj* vm2d0 = m2d0; if (vm2d0) { m2d0 = 0; vm2d0->Release(); }
        ((TimerStub*)m2d8)->FUN_00bc3170();
    }

    t = ((TimerStub*)m300)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        RefObj* vm2f8 = m2f8; if (vm2f8) { m2f8 = 0; vm2f8->Release(); }
        ((TimerStub*)m300)->FUN_00bc3170();
    }

    t = ((TimerStub*)m328)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        m320 = 0;
        ((TimerStub*)m328)->FUN_00bc3170();
    }

    t = ((TimerStub*)m350)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        m348 = 0;
        ((TimerStub*)m350)->FUN_00bc3170();
    }

    t = ((TimerStub*)m378)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        m370 = 0;
        ((TimerStub*)m378)->FUN_00bc3170();
    }

    t = ((TimerStub*)m3a0)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        m398 = 0;
        ((TimerStub*)m3a0)->FUN_00bc3170();
    }

    t = ((TimerStub*)m3c8)->FUN_00bc3190();
    if ((unsigned)(t >> 32) != 0 || (unsigned)t > 0x927c0) {
        m3c0 = 0;
        ((TimerStub*)m3c8)->FUN_00bc3170();
    }

    if (m3e8 == 0 || m2a0 == 2) {
        t = ((TimerStub*)m3f0)->FUN_00bc3190();
        if ((unsigned)(t >> 32) == 0 && (unsigned)t <= 0x927c0)
            return;
    }
    m3e8 = 0;
    ((TimerStub*)m3f0)->FUN_00bc3170();
}

// ===========================================================================
// @ 0x00bf0a60
// Clear the entry matching `p` from each of the three tracked slots.
// ===========================================================================
void CStub::FUN_00bf0a60(RefObj* p)
{
    if (m2ac == p) {
        RefObj* v = m2ac;
        if (v) { m2ac = 0; v->Release(); }
        ((TimerStub*)m2b0)->FUN_00bc3170();
    }
    if (m2d0 == p) {
        RefObj* v = m2d0;
        if (v) { m2d0 = 0; v->Release(); }
        ((TimerStub*)m2d8)->FUN_00bc3170();
    }
    if (m2f8 == p) {
        RefObj* v = m2f8;
        if (v) { m2f8 = 0; v->Release(); }
        ((TimerStub*)m300)->FUN_00bc3170();
    }
}

// ===========================================================================
// @ 0x00bf0b00
// Track `p` in the first slot (clearing it everywhere else first).
// ===========================================================================
void CStub::FUN_00bf0b00(RefObj* p)
{
    NounMgrStub* nm = (NounMgrStub*)SP_NounManager();
    int* list = (int*)nm->FUN_00b25ca0();
    int* it = (int*)*list;
    int* end = (int*)list[1];
    for (; it != end; ++it)
        ((CStub*)*it)->FUN_00bf0a60(p);

    RefObj* old = m2ac;
    if (p != old) {
        if (p) p->AddRef();
        m2ac = p;
        if (old) old->Release();
    }
    ((TimerStub*)m2b0)->FUN_00bc3130();
}

// ===========================================================================
// @ 0x00bf0b70
// Track `p` in the second slot.
// ===========================================================================
void CStub::FUN_00bf0b70(RefObj* p)
{
    NounMgrStub* nm = (NounMgrStub*)SP_NounManager();
    int* list = (int*)nm->FUN_00b25ca0();
    int* it = (int*)*list;
    int* end = (int*)list[1];
    for (; it != end; ++it)
        ((CStub*)*it)->FUN_00bf0a60(p);

    RefObj* old = m2d0;
    if (p != old) {
        if (p) p->AddRef();
        m2d0 = p;
        if (old) old->Release();
    }
    ((TimerStub*)m2d8)->FUN_00bc3130();
}
