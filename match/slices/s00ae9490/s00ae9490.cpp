// Slice s00ae9490 -- Spore "space tool" (the object with the 0xc-byte refcounted entry
// vector at +0x24, selected entry at +0x20, hashtable at +0x40 and bool at +0x60), its
// entry type, the entry ctor/dtor, the vector element copy/move/serialize helpers, and the
// neighbouring comm-screen/mission/empire update routines.
//
// The same class and the same vector instantiations are reconstructed in the neighbouring
// slice s00aea5d0 (bfs2 #45); this file follows its idioms (raw-offset accessors + generic
// virtual-dispatch helpers) because the original is VS2008 /O2 code whose register
// allocation and EASTL inlining are reproduced only approximately.
//
// Flags: default VS2008 (/O2 /MD /Gy /EHsc /TP).
#include "types.h"

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef signed   int   i32;

extern "C" void  op_del(void* p);      // 0x00f47380

// ---- generic virtual dispatch helpers (direct calls, masked targets) ------
typedef void* (__thiscall *tc0_t)(void*);
typedef void* (__thiscall *tc1_t)(void*, int);
typedef void* (__thiscall *tc2_t)(void*, int, int);
typedef void* (__thiscall *tc3_t)(void*, int, int, int);
typedef void* (__thiscall *tc4_t)(void*, int, int, int, int);
static inline void* vt0(void* p, int slot) { return ((tc0_t*)(*(void***)p))[slot](p); }
static inline void* vt1(void* p, int slot, int a) { return ((tc1_t*)(*(void***)p))[slot](p, a); }
static inline void* vt2(void* p, int slot, int a, int b) { return ((tc2_t*)(*(void***)p))[slot](p, a, b); }
static inline void* vt3(void* p, int slot, int a, int b, int c) { return ((tc3_t*)(*(void***)p))[slot](p, a, b, c); }
static inline void* vt4(void* p, int slot, int a, int b, int c, int d) { return ((tc4_t*)(*(void***)p))[slot](p, a, b, c, d); }
static inline void  addref(void* p) { if (p) vt0(p, 0); }
static inline void  relref(void* p) { if (p) vt0(p, 1); }

#define E(e, off)  (*(void**)((char*)(e) + (off)))
#define EI(e, off) (*(int*)((char*)(e) + (off)))

// ---- external helpers -----------------------------------------------------
extern "C" bool EA_WriteUint32(void* s, const u32* p, int n, int flags);   // 0x0093aa70
extern "C" bool EA_ReadInt32(void* s, i32* p, int n, int flags);           // 0x0093a780

struct Vec3i { int x, y, z; };

// ---- game singletons / services -------------------------------------------
// Every external callee is named FUN_<va> so that the differential tester can resolve the
// relocation by its hexadecimal name; the calling convention of each is taken from the
// callee's own ret operand (thiscall, arg count).
struct NounMgr {
    void* FUN_00b20750(int id);                          // GetFeedback, ret 4
    void* FUN_00f67d90();                                // GetCurrentTerrainSphere
};
struct StarMgr {
    void* FUN_00ba9370(int id);                          // GetEmpireByID, ret 4
    int   FUN_00ba6440(int id);                          // ret 4
    int   FUN_00ba6dc0(int id);                          // ret 4
    void* FUN_00ba6d80(int id);                          // ret 4
    void* FUN_00bb59b0(int id, void** out);              // ret 8
    int   FUN_00885c90();
};
struct EmpireObj {
    char pad84[0x84];
    int  m84;                                            // +0x84
    u8   FUN_00c30910();
    u8   FUN_00c30990();
};
struct Sphere {
    u8   FUN_00c772c0(int id);                           // ret 4
    u8   FUN_00c7a6c0(int id);                           // ret 4
    void FUN_00c7bb60(int id);                           // ret 4
    void FUN_00c77bf0(int id);                           // ret 4
};
struct PlanetObj {
    u8 FUN_00c71400(int id);                             // ret 4
};
struct City {
    int FUN_00bd9bf0();                                  // GetCivilization
};
struct MissionObj {
    u8    FUN_00c44c80();                                // IsActive
};
struct MissionMgr {
    void* FUN_00fee480(int id);                          // GetMissionByID, ret 4
};
struct TuningObj {
    char pad90[0x90];
    int  m90;                                            // +0x90
    int  FUN_010407d0(int empire);                       // ret 4
};
struct UniverseObj {
    u8 FUN_0100da10(u32* out);                           // ret 4
};
struct CivDataObj {
    void* FUN_005c65e0();                                // GetCities -> this+0x3c
};
struct SimGameObj {
    void FUN_01004c80(void* cities);                     // ret 4
};
struct PlayerEmpireObj {
    Vec3i* FUN_00c30f90();                               // -> this+0xc4
};
struct RelMgr {
    int FUN_00d00a70(int a, int b, int c);               // ret 0xc
};
struct EventLogObj {
    void FUN_00dd69f0(int a, int b, int c, int d, void** out);  // GetEventData, ret 0x14
};
struct LayoutObj {
    void FUN_00dd30d0();                                 // Hide
};
struct MsgDestruct {
    void FUN_00421cf0();                                 // Destruct
};
struct B3D490Obj {
    void FUN_00ae8ea0();
};
struct B3D400Obj {
    void FUN_00e14c10(int a);                            // ret 4
};
struct StringImpl {
    void FUN_00454cb0(char* first, char* last);          // basic_string::assign, ret 8
};
struct HashImpl {
    void* FUN_00aea1b0(u32 key);                         // hashtable::find, ret 8
};
struct TriggerObj {
    void FUN_00ae0930(int a, int b, int c, int d, int e, int f);  // ret 0x18
};
struct GameTimeObj {
    void FUN_00b32250(int id);                           // DecPauseGate, ret 4
};

struct StarMgr*             SP_StarManager();             // 0x00b3d2a0
struct NounMgr*             SP_NounManager();             // 0x00b3d300
struct RelMgr*              SP_RelationshipManager();     // 0x00b3d2c0
struct TriggerObj*          SP_GetTriggerMgr();           // 0x00b3d4d0
struct GameTimeObj*         SP_GameTimeManager();         // 0x00b3d380
void*                       SP_MessageServer();           // 0x0067dcc0
void*                       SP_EventLog();                // 0x00b3d3e0
void*                       SP_GetPlayerEmpire();         // 0x01021300
void*                       SP_GetPlayerHomePlanet();     // 0x01021370
int                         SP_GetPlayerEmpireID();       // 0x01021090
int                         SP_GetUniverseContext();       // 0x01021080
struct MissionMgr*          SP_GetMissionManager();       // 0x00feb9f0
struct TuningObj*           GetSpaceRelationshipTuning(); // 0x010407c0
bool                        world(int mode);              // 0x00685520
void*                       Audio_GetSystemAT();          // 0x00a206f0
void                        KillSetiEffects(void* system, int id); // 0x00435ed0
void*                       FUN_00b3d400();               // 0x00b3d400
void*                       FUN_00b3d490();               // 0x00b3d490
void                        FUN_00c35240(void* p, int a); // 0x00c35240
void*                       ctor_UILayout();              // 0x00dd1ca0
void*                       SP_SpaceGameGet();            // 0x01002bd0

extern void*  g_translator;      // 0x016e0d08
extern void*  g_simUniverse;     // 0x016dc798
extern void*  g_16c7aa4;         // 0x016c7aa4 (pointer value at that address)

// ===========================================================================
// 0xc-byte refcounted element (E12): {u32 a; u32 b; AutoRefCount<T> p;}
// ===========================================================================
struct E12 {
    u32   a;      // +0x00
    u32   b;      // +0x04
    void* p;      // +0x08

    E12* Init(u32 a_, u32 b_, void* p_);   // 0x00ae9640
    bool Write(void* stream);              // 0x00ae9680
    bool Read(void* stream);               // 0x00ae9700
};

struct Vec12 {
    E12* mpBegin;
    E12* mpEnd;
    E12* mpCapacity;
};

// ===========================================================================
// the space tool
// ===========================================================================
struct String64 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void FUN_00454cb0(char* first, char* last);   // 0x00454cb0
};
struct HashTable {
    u32    mBucketCount;   // +0x00
    void** mpBuckets;      // +0x04
    u32    mEndIndex;      // +0x08
    void*  FUN_00aea1b0(u32 key);                   // 0x00aea1b0 find
};
struct SpaceTool {
    char   pad00[0x20];
    void*  mp20;           // +0x20 selected entry
    void** mpVecBegin;     // +0x24 (vector of entry pointers, stride 4)
    void** mpVecEnd;       // +0x28
    void** mpVecCap;       // +0x2c
    char   pad30[0x10];
    HashTable mHash;       // +0x40
    char   pad50[0x18];
    String64 mStr;         // +0x64
    int    m74;            // +0x74

    u8& flag60() { return *(u8*)((char*)this + 0x60); }

    void* FindBest(int a, int b, int c);          // 0x00ae9490
    void* FindBestByPlanet(int a, int b, int c);  // 0x00ae9500
    bool  Select(int a, int b);                   // 0x00ae9b90
    bool  Has(int a, int b);                      // 0x00ae9c10
    bool  MatchesCiv(int civ);                    // 0x00ae9f10
    __declspec(noinline) void OnShutdown0();      // 0x00ae9f50
    bool  CheckEntry(void* e);                    // 0x00aea3d0
    void  AssignString(String64* src);            // 0x00aea230
    u8    FUN_00ae9390();                         // 0x00ae9390
    u8    FUN_00ae9040(int a, int b, void** x, void** y);      // 0x00ae9040
    int   FUN_00ae93f0(int a, int b, int c, int d, int e);     // 0x00ae93f0
};
struct Entry {
    char m[0x98];

    Entry* ctor();                                // 0x00aea250
    void   dtor();                                // 0x00aea310
    int    GetCiv();                              // 0x00ae9da0
    bool   Differs(void* other);                  // 0x00ae9d40
};

struct AutoRef {
    void* mP;
    AutoRef* Reset();                             // 0x00ae9790
};

void FUN_00aea170(void* p);                      // 0x00aea170

// ===========================================================================
// 0x00ae9490 -- best visible entry matching (empire id, object id, priority)
// ===========================================================================
// @ 0x00ae9490
void* SpaceTool::FindBest(int a, int b, int c)
{
    int n = *(int*)((char*)this + 0x28) - *(int*)((char*)this + 0x24) >> 2;
    int bestPriority = -1;
    void* best = 0;
    for (int i = 0; i < n; ++i)
    {
        void* e = mpVecBegin[i];
        if (*(u8*)((char*)e + 0x30) == 0)
            continue;
        int id = EI(e, 0x18);
        if (id != a && a != -1 && id != -1)
            continue;
        int prio = EI(e, 0x44);
        if (prio < c)
            continue;
        int obj = EI(e, 0x34);
        if (obj != b && obj != -1)
            continue;
        if (prio <= bestPriority)
            continue;
        best = e;
        bestPriority = prio;
    }
    return best;
}

// @ 0x00ae9500
void* SpaceTool::FindBestByPlanet(int a, int b, int c)
{
    int n = (int)(mpVecEnd - mpVecBegin);
    int bestPriority = -1;
    void* best = 0;
    for (int i = 0; i < n; ++i)
    {
        void* e = mpVecBegin[i];
        if (*(u8*)((char*)e + 0x30) == 0)
            continue;
        int id = EI(e, 0x18);
        if (id != a && a != -1 && id != -1)
            continue;
        if (EI(e, 0x44) < c)
            continue;
        int key = SP_StarManager()->FUN_00ba6440(EI(e, 0x34));
        if (key != b && key != -1)
            continue;
        if (EI(e, 0x44) <= bestPriority)
            continue;
        best = e;
        bestPriority = EI(e, 0x44);
    }
    return best;
}

// ===========================================================================
// 0x00ae9590 -- refresh the space-token translator value and the player's
// current-context position, keyed by the passed object's 0x3c token.
// ===========================================================================
// @ 0x00ae9590
void FUN_00ae9590(int* p)
{
    int token = p[0xf];
    if (token == 0x4fc08a9e)
    {
        TuningObj* t = GetSpaceRelationshipTuning();
        *(float*)((char*)g_translator + 0x40) = (float)t->m90;
    }
    else if (token == 0x7fc02fbc)
    {
        void* empire = SP_StarManager()->FUN_00ba9370(p[6]);
        TuningObj* t = GetSpaceRelationshipTuning();
        *(float*)((char*)g_translator + 0x40) = (float)t->FUN_010407d0((int)empire);
    }
    if (world(2))
    {
        void* o = *(void**)((char*)g_16c7aa4 + 0x7c);
        Vec3i* v = ((PlayerEmpireObj*)SP_GetPlayerEmpire())->FUN_00c30f90();
        *(int*)((char*)o + 0x14) = v->x;
        *(int*)((char*)o + 0x18) = v->y;
        *(int*)((char*)o + 0x1c) = v->z;
        *(int*)((char*)o + 0x20) = -1;
    }
}

// ===========================================================================
// 0xc-byte element helpers
// ===========================================================================
// @ 0x00ae9640
E12* E12::Init(u32 a_, u32 b_, void* p_)
{
    a = a_;
    b = b_;
    p = p_;
    if (p_)
        addref(p_);
    return this;
}

// @ 0x00ae9680
bool E12::Write(void* stream)
{
    void* inner = vt0(stream, 0x20 / 4);
    void* io = vt0(inner, 0x18 / 4);
    u32 v = a;
    EA_WriteUint32(io, &v, 1, 0);
    inner = vt0(stream, 0x20 / 4);
    io = vt0(inner, 0x18 / 4);
    v = b;
    EA_WriteUint32(io, &v, 1, 0);
    vt1(stream, 0x2c / 4, (int)p);
    return true;
}

// @ 0x00ae9700
bool E12::Read(void* stream)
{
    void* inner = vt0(stream, 0x20 / 4);
    void* io = vt0(inner, 0x18 / 4);
    i32 v = 0;
    EA_ReadInt32(io, &v, 1, 0);
    a = (u32)v;
    inner = vt0(stream, 0x20 / 4);
    io = vt0(inner, 0x18 / 4);
    EA_ReadInt32(io, &v, 1, 0);
    b = (u32)v;
    if (p)
    {
        void* old = p;
        p = 0;
        vt0(old, 0x4 / 4);
    }
    vt3(stream, 0x28 / 4, 0x2aa5ada, (int)&p, 0);
    return true;
}

// @ 0x00ae9790
AutoRef* AutoRef::Reset()
{
    void* p = mP;
    if (p)
    {
        mP = 0;
        vt0(p, 0xc0 / 4);
    }
    return this;
}

// @ 0x00ae97e0
E12* copy_addref(E12* first, E12* last, E12* dest)
{
    if (first == last)
        return dest;
    do
    {
        if (dest)
        {
            dest->a = first->a;
            dest->b = first->b;
            dest->p = first->p;
            if (dest->p)
                addref(dest->p);
        }
        first += 1;
        dest += 1;
    } while (first != last);
    return dest;
}

// @ 0x00ae9870
E12* move_assign(E12* first, E12* last, E12* dest)
{
    if (first == last)
        return dest;
    do
    {
        dest->a = first->a;
        dest->b = first->b;
        void* np = first->p;
        void* op = dest->p;
        if (np != op)
        {
            if (np)
                addref(np);
            dest->p = np;
            if (op)
                relref(op);
        }
        first += 1;
        dest += 1;
    } while (first != last);
    return dest;
}

// @ 0x00ae98d0
E12* move_backward(E12* first, E12* last, E12* dest)
{
    if (last == first)
        return dest;
    do
    {
        last -= 1;
        dest -= 1;
        dest->a = last->a;
        dest->b = last->b;
        void* np = last->p;
        void* op = dest->p;
        if (np != op)
        {
            if (np)
                addref(np);
            dest->p = np;
            if (op)
                relref(op);
        }
    } while (last != first);
    return dest;
}

// ===========================================================================
// 0x00ae9930 -- mission/planet status update for an empire pair
// ===========================================================================
// @ 0x00ae9930
void FUN_00ae9930(int idA, int idB, u32* outA, u32* outB, void** outMission)
{
    Sphere* sphere = (Sphere*)SP_NounManager()->FUN_00f67d90();
    EmpireObj* empireA = (EmpireObj*)SP_StarManager()->FUN_00ba9370(idA);
    *outA = 0xc8fbf7d7;
    u8 b = empireA->FUN_00c30910();
    *outB = (-(u32)b & 0xae864cb) + 0xa99d2018;

    int planetId = SP_StarManager()->FUN_00ba6dc0(idB);
    if (!planetId)
        return;

    if (empireA == SP_GetPlayerEmpire())
    {
        if ((void*)planetId != SP_GetPlayerHomePlanet())
        {
            void* planet = 0;
            SP_StarManager()->FUN_00bb59b0(planetId, &planet);
            if (!((PlanetObj*)planet)->FUN_00c71400(4))
                *outB = 0xaa220a3;
            if (planet)
                vt0(planet, 0xc0 / 4);
        }
        u32 v = 0;
        if (((UniverseObj*)g_simUniverse)->FUN_0100da10(&v))
        {
            int x = SP_StarManager()->FUN_00885c90();
            *outB = (-(u32)(v != (u32)x) & 0xcb133b3) + 0x5eee891c;
        }
        if (sphere->FUN_00c772c0(0x4ac8010))
        {
            if (!sphere->FUN_00c772c0(0x61f1455))
                *outB = 0xe2f7711c;
        }
    }
    else
    {
        if (empireA->FUN_00c30990())
            *outB = 0x4cf22e16;
        sphere = (Sphere*)SP_NounManager()->FUN_00f67d90();
        if (sphere->FUN_00c772c0(0x4ac8010))
        {
            if (!sphere->FUN_00c772c0(0x61f1456))
                *outB = 0xe2f7711c;
        }
    }

    if (empireA && !sphere->FUN_00c7a6c0(empireA->m84) &&
        sphere->FUN_00c772c0(0x4ed001a))
    {
        *outA = 0xc8fbf7d7;
        *outB = 0xc0efaa6e;
        sphere->FUN_00c7bb60(empireA->m84);
        return;
    }

    if ((void*)planetId == SP_GetPlayerHomePlanet())
    {
        MissionObj* m = (MissionObj*)SP_GetMissionManager()->FUN_00fee480(0xfe773af7);
        if (m && m->FUN_00c44c80() && !(u8)vt0(m, 0xf8 / 4))
        {
            *outA = 0x47808f9e;
            *outB = 0x1a2b6f64;
            if (outMission)
                *outMission = m;
        }
        m = (MissionObj*)SP_GetMissionManager()->FUN_00fee480(0x7bdbb97d);
        if (m && m->FUN_00c44c80() && !(u8)vt0(m, 0xf8 / 4))
        {
            *outA = 0xffb44c0a;
            *outB = (u32)vt0(m, 0x10c / 4);
            if (outMission)
                *outMission = m;
        }
    }
}

// ===========================================================================
// 0x00ae9b90 -- select an entry by (empire, object) or by the terrain criteria
// ===========================================================================
// @ 0x00ae9b90
bool SpaceTool::Select(int a, int b)
{
    if (b == -1)
        return false;
    if (*(int*)((char*)this + 0x28) - *(int*)((char*)this + 0x24) >> 2 == 0)
        return false;
    if (FindBest(a, b, 2))
        return true;
    void* x;
    void* y;
    if (FUN_00ae9040(a, b, &x, &y))
        return false;
    return FUN_00ae93f0(a, b, 0, -1, -1) ? true : false;
}

// @ 0x00ae9c10
bool SpaceTool::Has(int a, int b)
{
    if (b == -1)
        return false;
    if (*(int*)((char*)this + 0x28) - *(int*)((char*)this + 0x24) >> 2 == 0)
        return false;
    return FindBestByPlanet(a, b, 0) != 0;
}

// ===========================================================================
// 0x00ae9c50 -- GmeEditorResBase-style scalar deleting destructor
// ===========================================================================
// @ 0x00ae9c50
struct GmeEditorRes {
    void* Destroy(u8 flags);
};

void* GmeEditorRes::Destroy(u8 flags)
{
    *(u32*)((char*)this + 0x0c) = 0xffffffff;
    *(u32*)((char*)this + 0x10) = 0;
    *(u32*)((char*)this + 0x04) = 0x13ef094;
    *(u32*)((char*)this + 0x00) = 0x13eb938;
    if (flags & 1)
        op_del(this);
    return this;
}

// ===========================================================================
// 0x00ae9c90 -- event-log handler: zoom to the event's city
// ===========================================================================
// @ 0x00ae9c90
u8 FUN_00ae9c90(int eventId)
{
    void* data = 0;
    ((EventLogObj*)SP_EventLog())->FUN_00dd69f0(eventId, 0, 0, 0, &data);
    u8 result = 0;
    if (data)
    {
        void* obj = vt1(data, 0x0c / 4, 0x5760e04);
        if (obj)
        {
            vt0(obj, 0);
            result = 1;
            Sphere* ts = (Sphere*)SP_NounManager()->FUN_00f67d90();
            ts->FUN_00c77bf0(0x57f6a86);
            if (SP_GetUniverseContext() == 2)
            {
                void* cities = (*(CivDataObj**)((char*)obj + 0x10))->FUN_005c65e0();
                ((SimGameObj*)SP_SpaceGameGet())->FUN_01004c80(cities);
            }
            vt0(obj, 1);
        }
        relref(data);
    }
    return result;
}

// ===========================================================================
// 0x00ae9d40 -- entry comparison
// ===========================================================================
// @ 0x00ae9d40
bool Entry::Differs(void* other)
{
    if (!other)
        return false;
    int t = *(int*)(m + 0x0c);
    bool different = t != *(int*)((char*)other + 0x0c);
    if (!different)
    {
        if (t == 0)
            return *(int*)(m + 0x18) != *(int*)((char*)other + 0x18);
        if (t == 1)
        {
            if (*(int*)(m + 0x18) == *(int*)((char*)other + 0x18) &&
                *(int*)(m + 0x20) == *(int*)((char*)other + 0x20) &&
                *(int*)(m + 0x24) == *(int*)((char*)other + 0x24))
                return false;
            different = true;
        }
    }
    return different;
}

// ===========================================================================
// 0x00ae9da0 -- the entry's civilization (or its city's)
// ===========================================================================
// @ 0x00ae9da0
int Entry::GetCiv()
{
    SP_NounManager()->FUN_00b20750(EI(this, 0x18));
    int civ = EI(this, 0x28);
    if (civ != 0)
        return civ;
    return ((City*)E(this, 0x20))->FUN_00bd9bf0();
}

// ===========================================================================
// vector <-> stream
// ===========================================================================
// @ 0x00ae9e60
void write_vec(void* stream, Vec12* v)
{
    u32 count = (u32)(v->mpEnd - v->mpBegin);
    void* inner = vt0(stream, 0x20 / 4);
    void* io = vt0(inner, 0x18 / 4);
    EA_WriteUint32(io, &count, 1, 0);
    for (E12* p = v->mpBegin; p != v->mpEnd; ++p)
        p->Write(stream);
    vt0(stream, 0x1c / 4);
}

// @ 0x00ae9ed0
bool visit_vec(void* visitor, Vec12* v)
{
    E12* p = v->mpBegin;
    E12* end = v->mpEnd;
    if (p == end)
        return true;
    do
    {
        if (p)
        {
            void* q = p->p;
            if (q)
                vt1(q, 0x1c / 4, (int)visitor);
        }
        p = (E12*)((char*)p + 0xc);
    } while (p != end);
    return true;
}

// @ 0x00ae9f10
bool SpaceTool::MatchesCiv(int civ)
{
    if (!FUN_00ae9390())
        return false;
    void* e = mp20;
    SP_NounManager()->FUN_00b20750(EI(e, 0x18));
    int c = EI(e, 0x28);
    if (c == 0)
        c = ((City*)E(e, 0x20))->FUN_00bd9bf0();
    return c == civ;
}

// ===========================================================================
// 0x00ae9f50 -- close the comm screen and flush the pending event state
// ===========================================================================
struct MsgData { u32 lo; u32 hi; };
struct MsgBasic5 {
    void*   mVtbl;      // +0x00
    u32     mRef;       // +0x04
    MsgData mData[5];   // +0x08 .. +0x2f
    u32     mId;        // +0x30
    u32     mPad34;     // +0x34
    u32     mFlags;     // +0x38
};

// @ 0x00ae9f50
void SpaceTool::OnShutdown0()
{
    ((LayoutObj*)ctor_UILayout())->FUN_00dd30d0();
    if (!mp20)
        return;

    u8 isZeroType = EI(mp20, 0x0c) == 0;
    void* empire = 0;
    if (isZeroType)
        empire = SP_StarManager()->FUN_00ba9370(EI(mp20, 0x18));

    MsgBasic5 msg;
    msg.mVtbl = (void*)0x13eb844;
    msg.mRef = 0;
    msg.mData[0].lo = (u32)EI(mp20, 0x0c);
    if (isZeroType)
        msg.mData[1].lo = (u32)empire;
    else
    {
        SP_NounManager()->FUN_00b20750(EI(mp20, 0x18));
        int c = EI(mp20, 0x28);
        if (c == 0)
            c = ((City*)E(mp20, 0x20))->FUN_00bd9bf0();
        msg.mData[1].lo = (u32)c;
    }
    if (isZeroType)
        msg.mData[2].lo = (u32)mp20;
    else
        msg.mData[2].lo = (u32)E(mp20, 0x20);
    msg.mData[3].lo = isZeroType ? 0 : (u32)EI(mp20, 0x24);
    msg.mId = 0x3ac86b5;
    msg.mFlags = 0;
    vt3(SP_MessageServer(), 0x14 / 4, msg.mId, (int)&msg, 0);

    if (*(u8*)((char*)mp20 + 0x30) == 0 && empire != SP_GetPlayerEmpire())
    {
        MsgBasic5 msg2;
        msg2.mVtbl = (void*)0x13eb844;
        msg2.mRef = 0;
        msg2.mData[0].lo = (u32)empire;
        msg2.mId = 0x43f2590;
        msg2.mFlags = 0;
        vt3(SP_MessageServer(), 0x14 / 4, msg2.mId, (int)&msg2, 0);
        ((MsgDestruct*)&msg2)->FUN_00421cf0();
    }

    GameTimeObj* gt = SP_GameTimeManager();
    if (gt)
        gt->FUN_00b32250(0x4d02e35);

    void* audio = Audio_GetSystemAT();
    if (audio)
        audio = vt0(audio, 0x20 / 4);
    else
        audio = 0;
    KillSetiEffects(audio, 0x1e5e7302);

    if (FUN_00b3d490())
        ((B3D490Obj*)FUN_00b3d490())->FUN_00ae8ea0();
    ((B3D400Obj*)FUN_00b3d400())->FUN_00e14c10(1);

    if (m74 != -1)
    {
        void* p = SP_StarManager()->FUN_00ba6d80(m74);
        if (p)
            FUN_00c35240(p, SP_GetPlayerEmpireID());
        m74 = -1;
    }

    if (mStr.mpBegin != mStr.mpEnd)
    {
        SP_GetTriggerMgr()->FUN_00ae0930((int)mStr.mpBegin, 1, 0, 0, 0, 0);
        if (mStr.mpBegin != mStr.mpEnd)
        {
            *mStr.mpBegin = 0;
            mStr.mpEnd = mStr.mpBegin;
        }
    }
    ((MsgDestruct*)&msg)->FUN_00421cf0();
}

// ===========================================================================
// 0x00aea210 -- close the comm screen and post the close message
// ===========================================================================
// @ 0x00aea210
struct CommManager : SpaceTool {
    void CloseCommEvent();
};

void CommManager::CloseCommEvent()
{
    OnShutdown0();
    vt4(SP_MessageServer(), 0x18 / 4, 0x490d429, 0, 0, 0);
}

// @ 0x00aea230
void SpaceTool::AssignString(String64* src)
{
    if (src != &mStr)
        mStr.FUN_00454cb0(src->mpBegin, src->mpEnd);
}

// ===========================================================================
// Entry ctor / dtor
// ===========================================================================
// @ 0x00aea250
Entry* Entry::ctor()
{
    int* p = (int*)m;
    p[1] = 0x13ef094;
    p[2] = 0;
    p[0] = 0x145bed8;
    p[1] = 0x145bed4;
    p[4] = 0;
    p[5] = 0;
    p[3] = -1;
    p[6] = -1;
    p[7] = -1;
    p[8] = 0;
    p[9] = 0;
    p[10] = 0;
    p[11] = 0;
    *(u8*)(p + 12) = 0;
    p[13] = -1;
    p[14] = -1;
    p[15] = -1;
    p[16] = 0;
    p[17] = -1;
    p[18] = 0;
    p[19] = 0;
    p[20] = 0;
    p[21] = 0;
    p[22] = 0;
    p[25] = 0;
    p[26] = 0;
    p[27] = 0;
    p[30] = 0;
    p[31] = 0;
    p[32] = 0;
    p[35] = 0;
    p[36] = 0;
    p[37] = 0;
    return this;
}

// @ 0x00aea310
void Entry::dtor()
{
    int* p = (int*)m;
    p[0] = 0x145bed8;
    p[1] = 0x145bed4;
    void* a = *(void**)((char*)this + 0x8c);
    if (a && *(int*)((char*)a - 4) != 0)
        op_del(a);
    a = *(void**)((char*)this + 0x78);
    if (a && *(int*)((char*)a - 4) != 0)
        op_del(a);
    a = *(void**)((char*)this + 0x64);
    if (a && *(int*)((char*)a - 4) != 0)
        op_del(a);
    FUN_00aea170((char*)this + 0x50);
    void* r = *(void**)((char*)this + 0x40);
    if (r)
        vt0(r, 1);
    r = *(void**)((char*)this + 0x2c);
    if (r)
        vt0(r, 1);
    r = *(void**)((char*)this + 0x28);
    if (r)
        vt0(r, 1);
    r = *(void**)((char*)this + 0x24);
    if (r)
        vt0(r, 1);
    r = *(void**)((char*)this + 0x20);
    if (r)
        vt0(r, 1);
    p[0] = 0x13eb938;
    p[1] = 0x13ef094;
}

// ===========================================================================
// 0x00aea3d0 -- relationship check for one entry
// ===========================================================================
// @ 0x00aea3d0
bool SpaceTool::CheckEntry(void* e)
{
    u32 key = (u32)EI(e, 0x3c);
    void* it = mHash.FUN_00aea1b0(key);
    if (it == mHash.mpBuckets[mHash.mEndIndex])
        return false;
    RelMgr* rel = SP_RelationshipManager();
    int id = EI(e, 0x18);
    int player = SP_GetPlayerEmpireID();
    int n = (int)((*(int*)((char*)it + 8) - *(int*)((char*)it + 4)) >> 2);
    int* vals = *(int**)((char*)it + 4);
    for (int i = 0; i < n; ++i)
    {
        int t = vals[i];
        if (t == 0x0456d072) { if (rel->FUN_00d00a70(id, player, 1) == 0) return true; }
        else if (t == (int)0xcfe5a2a3) { if (rel->FUN_00d00a70(id, player, 1) == 1) return true; }
        else if (t == (int)0xf2bc5e44) { if (rel->FUN_00d00a70(id, player, 1) == 2) return true; }
        else if (t == 0x1a071e2b) { if (rel->FUN_00d00a70(id, player, 1) == 3) return true; }
        else if (t == (int)0xb371f27e) { if (rel->FUN_00d00a70(id, player, 1) == 4) return true; }
        else if (t == (int)0xe9484325) { if (*(u8*)((char*)this + 0x60) != 0) return true; }
        else return false;
    }
    return false;
}
