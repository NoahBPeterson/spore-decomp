// Slice s00d512f0 - 0x00d51c30: finds (or creates) the herd a creature-stage task works with and
// activates it.  Class and field names are inferred from behaviour (the function has no PDB name).
//
// `this` is a task object with an owner (+0x40), a vector_map<uint,uint> of counters (+0x44) and a
// vector_map<uint, ref-counted herd> of named slots (+0x5c).
//   * target "species" object: slot 0x5f11333 of the +0x5c map (queried for interface
//     0x4f396a66), else the game-data object whose index is counter 0x5f10ce1;
//   * property id from the owner (0x64aaf64e, default 0xd00f20e4), position of the species;
//   1. nearest herd (type 0x1be418e) of another empire with creatures of that id,
//   2. else nearest scenario object (type 0x36be27e) of that id: load it and use its herd (+0x1a4),
//   3. else create a herd and place it at the first world point farther than 75 units from the
//      species (point list from the species);
// then store the herd in slot 0x5f115ab, populate an empty herd (random positions around the
// species), set its brain level, send message 0x609b763 and attach every creature to the species.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <intrin.h>

namespace RT
{
    struct Vec3
    {
        float x, y, z;
        Vec3() {}
        Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
    };

    // Sub-object with a vtable: slot 3 = GetValue (+0xc), slot 11 = GetPosition (+0x2c).
    struct Holder
    {
        virtual void s0(); virtual void s1(); virtual void s2();
        virtual unsigned GetValue();                        // +0xc
        virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
        virtual void s8(); virtual void s9(); virtual void s10();
        virtual const Vec3* GetPosition();                  // +0x2c
    };

    struct PtrList { char** mpBegin; char** mpEnd; };

    struct Creature
    {
        char   pad[0xb4c];
        char*  mpSub;                                       // +0xb4c (its +8 sub-object takes Apply)
        char   pad2[0xe84 - 0xb50];
        void*  mpSpeciesRecord;                             // +0xe84

        char*  GetSpeciesRecord();                          // 0x00c0c1a0
    };

    struct Sub8 { void Apply(int zero, int flags, float f, unsigned v); };      // 0x00bc97f0 (ret 0x10)
    struct CreatureHost                                                         // global at 0x00b3d480
    {
        char  pad[0x2c];
        float mScale;                                                           // +0x2c
        void Attach(Creature* c);                                               // 0x00acd2d0 (ret 4)
        int  Place(const Vec3* p, float a, float b);                            // 0x00acc700 (ret 0xc)
        void FUN_00aca360(Creature* c);                                         // 0x00aca360 (ret 4)
    };
    struct PlanetModel
    {
        void MakeRandomWorldPosition(Vec3* out, const Vec3* center, float a, float b); // 0x00b81780 (ret 0x10)
        void SnapB(void* out, const void* in, void* tag);                       // 0x00b82970 (ret 0xc)
        void BuildSurfaceOrientation2(void* out, const void* in, const void* dir); // 0x00b7f250 (ret 0xc)
    };

    struct MessageU
    {
        union { unsigned id; unsigned short sub; };
        unsigned short pad4;
        unsigned short flags;
    };

    struct Router                                           // 0x00401010 returns the global router
    {
        virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
        virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
        virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
        virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
        virtual void Send(void* target, MessageU* msg);     // +0x4c
    };

    // Species object (interface 0x4f396a66): vtable slots 43 (+0xac) and 47 (+0xbc), holder at +0x120.
    struct Vec3List;

    struct Species
    {
        virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
        virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
        virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
        virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
        virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
        virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
        virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
        virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
        virtual void s40(); virtual void s41(); virtual void s42();
        virtual Species* GetLinked();                       // +0xac
        virtual void s44(); virtual void s45(); virtual void s46();
        virtual PtrList* GetList();                         // +0xbc

        Vec3List* GetPoints();                              // 0x00c97020
    };

    struct Vec3List { Vec3* mpBegin; Vec3* mpEnd; };

    inline Holder* HolderOf(Species* s) { return (Holder*)((char*)s + 0x120); }

    // Ref-counted game object: slot 0 AddRef, 1 Release, 3 Cast(interface id).
    struct Obj
    {
        virtual void AddRef();
        virtual void Release();
        virtual void s2();
        virtual Species* Cast(unsigned interfaceId);        // +0xc
    };

    struct Herd : Obj
    {
        virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
        virtual unsigned GetTypeId();                       // +0x20
        virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
        virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
        virtual int GetOwnerEmpire();                       // +0x4c

        char          pad04[0x40 - 4];
        Creature**    mpCreaturesBegin;                     // +0x40
        Creature**    mpCreaturesEnd;                       // +0x44
        char          pad48[0xa4 - 0x48];
        char*         mpInfo;                               // +0xa4
        char          padA8[0xf4 - 0xa8];
        unsigned      mGeneration;                          // +0xf4
        char          padF8[0x124 - 0xf8];
        int           mActivateBrainLevel;                  // +0x124

        char IsFlagged();                                   // 0x00c6a020
        const Vec3* GetPosition();                          // 0x00c6acc0
        int SetPosition(const Vec3* p);                    // 0x00c6ba20
    };

    // Scenario object (type 0x36be27e): vtable slot 11 (+0x2c) = bool; holder at +0x34.
    struct Scenario
    {
        virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
        virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
        virtual void s10();
        virtual char IsFlagged();                           // +0x2c

        char     pad04[0x34 - 4];
        char     holder[4];                                 // +0x34 (sub-object with vtable)
        char     pad38[0x10c - 0x38];
        unsigned mTypeId;                                   // +0x10c
        unsigned mId;                                       // +0x110
        char     pad114[0x1a4 - 0x114];
        Herd*    mpHerd;                                    // +0x1a4
    };

    inline Holder* HolderOf(Scenario* s) { return (Holder*)((char*)s + 0x34); }

    struct GameDataVec { int pad0; char** mpBegin; char** mpEnd; };

    typedef void (*Fn)();

    struct NounManager
    {
        int          GetPlayerEmpireOrMinus1();             // 0x00b1f9d0
        GameDataVec* GetGameDataVector(Fn a, Fn b, Fn c, Fn d, unsigned type);   // 0x00b21340 (ret 0x14)
        Herd*        CreateGameData(unsigned type, int id, int zero0, const Vec3* pos, int zero1);   // 0x00b23650 (ret 0x14)
        void*        GetAvatar();                           // 0x00b1fdb0
        void         RemoveNoun(void* noun);                // 0x00b225d0 (ret 4)
    };

    struct ValueMap { unsigned& operator[](const unsigned& key); };            // 0x00564a10 (ret 4)

    struct PairUR { unsigned key; Obj* value; };
    struct RefMap                                                              // vector_map<uint, ref-counted object>
    {
        PairUR* mpBegin;                                                       // +0x00
        PairUR* mpEnd;                                                         // +0x04
        char    pad[0x14 - 8];
        bool    mbFlag;                                                        // +0x14
        Obj*& operator[](const unsigned& key);                                 // 0x00d4eb30 (ret 4)
        inline PairUR* find(unsigned key);
        void Remove(const unsigned& key);                                      // 0x00d4e8e0 (ret 4)
    };

    // eastl::lower_bound over 8-byte pairs (0x00d01260).  The body is given here (noinline) so the
    // compiler knows the call writes no memory, as it did when it compiled the original.
    extern "C" __declspec(noinline) PairUR* __cdecl LowerBound(PairUR* first, PairUR* last, const unsigned* key, bool)
    {
        int n = (int)(last - first);
        while (n > 0)
        {
            int half = n >> 1;
            if (first[half].key < *key)
            {
                first += half + 1;
                n -= half + 1;
            }
            else
                n = half;
        }
        return first;
    }

    inline PairUR* RefMap::find(unsigned keyIn)
    {
        const unsigned key = keyIn;
        PairUR* const e = mpEnd;
        PairUR* it = LowerBound(mpBegin, e, &key, mbFlag);
        if (it == e || keyIn < it->key)
            it = e;
        else if (it == it + 1)
            it = e;
        return it;
    }

    struct Task
    {
        char     pad00[0x40];
        void*    mpOwner;                                   // +0x40
        ValueMap mCounters;                                 // +0x44 (vector_map<uint,uint>, 0x18 bytes)
        char     pad48[0x5c - 0x48];
        RefMap   mSlots;                                    // +0x5c

        int Activate();                                     // 0x00d51c30
        void Method1540();                                  // 0x00d51540
    };
}

extern "C"
{
    RT::NounManager* __cdecl GetNounManager();              // 0x00b3d300
    RT::CreatureHost* __cdecl GetCreatureHost();            // 0x00b3d480
    RT::PlanetModel* __cdecl GetPlanetModel();              // 0x00b3d350
    RT::Router* __cdecl GetRouter();                        // 0x00401010
    int __cdecl GetOwnerProperty(void* owner, unsigned id, unsigned defaultValue);     // 0x00ac8fa0
    char __cdecl LoadScenarioFn(RT::Scenario* s, int a, int b);                        // 0x00b931c0
    void __cdecl PlaceNewCreature(RT::Vec3* pos, int infoId, int one, RT::Herd* h, int zero, int one2);  // 0x00c099e0
    void F_cd7d10(); // 0x00cd7d10
    void F_d3d420(); // 0x00d3d420
    void F_accbb0(); // 0x00accbb0
    void F_accc30(); // 0x00accc30
    void F_ace070(); // 0x00ace070
    void F_b1e500(); // 0x00b1e500
}

// @ 0x00d51c30
int RT::Task::Activate()
{
    using namespace RT;
    Vec3 tmpVec;
    unsigned tmpKey;
    PairUR* it = mSlots.find(0x5f11333);
    PairUR* const end = mSlots.mpEnd;

    Species* species;
    Obj* slotObj;
    if (it == end || !(slotObj = it->value) || !(species = slotObj->Cast(0x4f396a66)))
    {
        tmpKey = 0x5f10ce1;
        int idx = mCounters[tmpKey];
        GameDataVec* vec = GetNounManager()->GetGameDataVector(F_cd7d10, F_d3d420, F_accbb0, F_b1e500, 0x18c6d19);
        if ((int)(vec->mpEnd - vec->mpBegin) <= idx)
            return (int)&vec->mpBegin;
        species = (Species*)vec->mpBegin[idx];
        if (!species)
            return (int)&vec->mpBegin;
    }

    int id = GetOwnerProperty(mpOwner, 0x64aaf64e, 0xd00f20e4);
    const Vec3* pos = HolderOf(species)->GetPosition();

    Herd* best = 0;
    float bestDist = 90000.0f;
    int player = GetNounManager()->GetPlayerEmpireOrMinus1();
    {
        GameDataVec* vec = GetNounManager()->GetGameDataVector(F_cd7d10, F_d3d420, F_accc30, F_b1e500, 0x1be418e);
        Herd** p = (Herd**)vec->mpBegin;
        Herd** pEnd = (Herd**)vec->mpEnd;
        for (; p != pEnd; ++p)
        {
            Herd* h = *p;
            if (h->IsFlagged() && h->mpCreaturesBegin != h->mpCreaturesEnd && h->GetOwnerEmpire() != player)
            {
                char* rec = (*h->mpCreaturesBegin)->GetSpeciesRecord();
                if (rec && *(int*)(rec + 0x10) == id)
                {
                    const Vec3* hp = h->GetPosition();
                    float dx = pos->x - hp->x;
                    float dy = pos->y - hp->y;
                    float dz = pos->z - hp->z;
                    float d = (dz * dz + dx * dx) + dy * dy;
                    if (d <= bestDist)
                    {
                        best = h;
                        bestDist = d;
                    }
                }
            }
        }
    }

    Scenario* scenario = 0;
    if (!best)
    {
        bestDist = 90000.0f;
        GameDataVec* vec = GetNounManager()->GetGameDataVector(F_cd7d10, F_d3d420, F_ace070, F_b1e500, 0x36be27e);
        Scenario** p = (Scenario**)vec->mpBegin;
        Scenario** pEnd = (Scenario**)vec->mpEnd;
        for (; p != pEnd; ++p)
        {
            Scenario* s = *p;
            if (!s->IsFlagged() && s->mTypeId == 0x1be418e && (int)s->mId == id)
            {
                const Vec3* sp = HolderOf(s)->GetPosition();
                float dx = pos->x - sp->x;
                float dy = pos->y - sp->y;
                float dz = pos->z - sp->z;
                float d = (dx * dx + dz * dz) + dy * dy;
                if (d < bestDist)
                {
                    bestDist = d;
                    scenario = s;
                }
            }
        }
    }

    if (scenario)
    {
        int ok = LoadScenarioFn(scenario, -1, -1);
        if ((char)ok == 0)
            return ok;
        best = scenario->mpHerd;
        if (!best)
            return ok;
        int type = best->GetTypeId();
        if (type != 0x1be418e)
            return type;
    }
    else if (!best)
    {
        Herd* created = GetNounManager()->CreateGameData(0x1be418e, id, 0, pos, 0);
        if (!created)
            return 0;
        best = (created->GetTypeId() == 0x1be418e) ? created : 0;

        tmpKey = 0x613614c;
        mCounters[tmpKey] = 1;

        Vec3& spot = tmpVec;
        spot = *pos;
        Vec3List* pts = species->GetPoints();
        if (pts->mpBegin != pts->mpEnd)
            spot = pts->mpBegin[0];
        int n = (int)(pts->mpEnd - pts->mpBegin);
        for (int i = 0; i < n; i++)
        {
            const Vec3& q = pts->mpBegin[i];
            float dx = pos->x - q.x;
            float dy = pos->y - q.y;
            float dz = pos->z - q.z;
            if (5625.0f < (dz * dz + dy * dy) + dx * dx)
            {
                spot = pts->mpBegin[i];
                break;
            }
        }
        int r = best->SetPosition(&spot);
        if (!best)
            return r;
    }

    tmpKey = 0x5f115ab;
    if (best)
    {
        Obj*& slot = mSlots[tmpKey];
        Obj* old = slot;
        if (best != old)
        {
            best->AddRef();
            slot = best;
            if (old)
                old->Release();
        }
    }
    else
        mSlots.Remove(tmpKey);

    if (best->mpCreaturesBegin == best->mpCreaturesEnd)
    {
        GetCreatureHost();
        int info = (int)best->mpInfo;
        for (unsigned i = 0; i < best->mGeneration; i++)
        {
            Vec3& out = tmpVec;
            GetPlanetModel()->MakeRandomWorldPosition(&out, best->GetPosition(), 3.0f, 6.0f);
            PlaceNewCreature(&out, info, 1, best, 0, 1);
        }
    }

    best->mActivateBrainLevel = -1;
    MessageU msg;
    msg.sub = 0;
    msg.flags = 4;
    msg.id = 0x609b763;
    GetRouter()->Send(best->mpInfo + 0x504, &msg);

    Species* linked = species->GetLinked();
    Species* second = 0;
    PtrList* list = species->GetList();
    if ((unsigned)(list->mpEnd - list->mpBegin) > 1)
        second = ((Species**)species->GetList()->mpBegin)[1];
    CreatureHost* host = GetCreatureHost();
    for (unsigned i = 0; i < (unsigned)(best->mpCreaturesEnd - best->mpCreaturesBegin); i++)
    {
        Creature* c = best->mpCreaturesBegin[i];
        host->Attach(c);
        Holder* hold = second ? HolderOf(second) : HolderOf(linked);
        unsigned v = hold->GetValue();
        ((Sub8*)(c->mpSub + 8))->Apply(0, 0x4000, host->mScale, v);
    }

    tmpKey = 0x5f11011;
    float zero = 0.0f;
    mCounters[tmpKey] = *(unsigned*)&zero;
    tmpKey = 0x5f0f28d;
    mCounters[tmpKey] = 0;
    return GetCreatureHost()->Place(best->GetPosition(), 25.0f, 37.5f);
}

// ===========================================================================
// gold7 additions to slice s00d512f0 (batch gold7): 9 functions.
// Retail member offsets are read from the disassembly; objects are modelled
// locally with role-named members at those offsets.
// ===========================================================================

namespace G7
{
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#pragma warning(disable: 4100)

#define VTC(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

extern "C" void* operator_new(u32 n, const char* pFile, int a, int b,
                              const char* pAlloc, int line);            // 0x00f473a0
extern "C" void  operator_delete_array(void* p);                        // 0x00f47380

#define G7_NEW(n) operator_new((n), "Simulator/cDramaManager", 0, 0, (const char*)0, 0)

static inline bool BlockIsOurs(const void* p)
{
    return p != 0 && ((const u32*)p)[-1] != 0;
}

extern "C" void* GetSystemAT();                 // 0x00a206f0
extern "C" int   GetCurrentGameMode();          // 0x00b5b800
extern "C" void* GetPosseSimulatorRaw();        // 0x00d539d0

// ------------------------------------------------------- drama event instance
struct EventInstance
{
    char          pad00[0x44];
    RT::ValueMap  mCounters;                        // +0x44
};

// ------------------------------------------------------------- drama manager
struct Range { void* first; void* second; };

struct MultiMap
{
    void equal_range(Range* out, const u32* key);   // 0x00f21cd0
};

struct AgentOrderManager
{
    void Activate(int a, int b, void* c, float d, void* e, void* f);   // 0x00bca810
};

struct Mate
{
    char               pad00[0xb48];
    AgentOrderManager* mpOrder;                     // +0xb48
    void Activate(float f) { mpOrder->Activate(3, 1, 0, f, 0, 0); }
};

struct AbductTarget;
struct EventObj
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    AbductTarget* Cast(u32 interfaceId);            // +0x0c
};

struct AbductTarget
{
    char          pad00[0x44];
    RT::ValueMap  mCounters;                        // +0x44
    void FUN_00d4edd0(u32 a, u32 b);                // 0x00d4edd0
};

struct MapNode { char pad00[0x14]; EventObj* value; };   // +0x14

struct DramaManager
{
    char      pad00[0x14];
    void*     mp14;                                 // +0x14
    char      pad18[0x38 - 0x18];
    void*     mpMate;                               // +0x38
    char      pad3c[0x50 - 0x3c];
    MultiMap  mEvents;                              // +0x50

    DramaManager*  Ctor();                          // 0x00d4ea90
    EventInstance* GetActiveEvent(int a, char b);   // 0x00d4cad0
    void           ClearMate(void* mate);           // 0x00d4b1d0
    void           CheckBabyTeacher();              // 0x00d4b220
    u32            GetVal();                        // 0x00d516a0
    void           SetVal(u32 v);                   // 0x00d516d0
    void           Method1700(u32 arg);             // 0x00d51700
};

extern DramaManager* g_sDramaInstance;              // 0x0169e43c

static inline DramaManager* GetDramaInstance()
{
    DramaManager* p = g_sDramaInstance;
    if (p == 0)
    {
        p = (DramaManager*)G7_NEW(0x70);
        p = p ? p->Ctor() : 0;
        g_sDramaInstance = p;
    }
    return p;
}

// @ 0x00d516a0
u32 DramaManager::GetVal()
{
    EventInstance* e = GetActiveEvent(2, 1);
    if (e != 0)
        return e->mCounters[0];
    return 0;
}

// @ 0x00d516d0
void DramaManager::SetVal(u32 v)
{
    EventInstance* e = GetActiveEvent(2, 1);
    if (e != 0)
        e->mCounters[0] = v;
}

// @ 0x00d51700
void DramaManager::Method1700(u32 arg)
{
    if (arg == 0)
        return;
    if (GetCurrentGameMode() != 0x1654c02)
        return;

    Range range;
    u32 key = 7;
    mEvents.equal_range(&range, &key);
    if (range.first == range.second)
        return;

    EventObj* e = ((MapNode*)range.first)->value;
    if (e == 0)
        return;
    AbductTarget* o = ((AbductTarget*(__thiscall*)(void*, u32))VTC(e, 0xc))(e, 0x5ed29d3);
    if (o == 0)
        return;

    u32 v = o->mCounters[0x5f10cdd];
    o->mCounters[0x5f10cdd] = v + 1;
    if (v + 1 == o->mCounters[0x5f10ce1])
        o->FUN_00d4edd0(0x5f11333, *(volatile u32*)&arg);
}

// ------------------------------------------------------ meteor strike event
struct Sub8 { void Apply(int a, int b, float f, void* d); };   // 0x00bc97f0

struct Chunk
{
    void** mpBegin;                                 // +0x00
    void** mpEnd;                                   // +0x04
    char   pad08[0x218 - 0x08];
};

struct Embed5c { void DestroyMembers(); };          // 0x00d4b4b0

struct MeteorStrikeEvent
{
    void*    mpVtbl;                                // +0x00
    void*    mpVtbl2;                               // +0x04
    char     pad08[0x40 - 0x08];
    void*    mp40;                                  // +0x40
    void*    mp44;                                  // +0x44
    char     pad48[0x5c - 0x48];
    Embed5c  mEmbed;                                // +0x5c
    char     pad5d[0xc8 - 0x5d];
    Chunk    mChunk0;                               // +0xc8
    Chunk    mChunk1;                               // +0x2e0

    void  Clear();                                  // 0x00d4e950
    void  LoadAndInitMeteorStrikeData(u32 a);       // 0x00d50380
    void  Dtor();                                   // 0x00d517d0
    void  Method1890();                             // 0x00d51890
};

// @ 0x00d517d0
void MeteorStrikeEvent::Dtor()
{
    mpVtbl  = (void*)0x147b640;
    mpVtbl2 = (void*)0x147b62c;
    Clear();

    int i = 1;
    Chunk* q = (Chunk*)((char*)this + 0x4f8);
    do
    {
        void** end = q[-1].mpEnd;
        void** p = q[-1].mpBegin;
        q = (Chunk*)((char*)q - 0x218);
        for (; p < end; ++p)
        {
            void* o = *p;
            if (o != 0)
                ((void(__thiscall*)(void*))VTC(o, 4))(o);
        }
        if (BlockIsOurs(q->mpBegin))
            operator_delete_array(q->mpBegin);
    } while (--i >= 0);

    mpVtbl  = (void*)0x147b090;
    mpVtbl2 = (void*)0x147b278;
    mEmbed.DestroyMembers();
    if (mp44 != 0)
        operator_delete_array(mp44);
    if (mp40 != 0)
        ((void(__thiscall*)(void*))VTC(mp40, 4))(mp40);
    mpVtbl  = (void*)0x13eb938;
    mpVtbl2 = (void*)0x13ec458;
}

// @ 0x00d51890
void MeteorStrikeEvent::Method1890()
{
    void* audio = GetSystemAT();
    if (audio != 0)
    {
        ((void(__thiscall*)(void*, u32))VTC(audio, 0x38))(audio, 0x3cdd1a9);
        ((void(__thiscall*)(void*, u32, u32))VTC(audio, 0x40))(audio, 0x34753a7, 0x413df353);
        ((void(__thiscall*)(void*, u32, float))VTC(audio, 0x3c))(audio, 0x34753aa, 1.0f);
        ((void(__thiscall*)(void*))VTC(audio, 0x58))(audio);
    }
    LoadAndInitMeteorStrikeData(*(u32*)((char*)this + 0x40));

    DramaManager* dm = GetDramaInstance();
    if (dm == 0)
        return;
    if (dm->mpMate != 0)
        dm->ClearMate(dm->mpMate);
}

// -------------------------------------------------------- sea monster event
struct SeaObj
{
    char pad00[0x135];
    u8   mb135;                                     // +0x135
    char pad136[0xb4c - 0x136];
    void* mpSub;                                    // +0xb4c
    char padB50[0xf90 - 0xb50];
    u8   mbF90;                                     // +0xf90

    void* LookupTextStyle(u32 a);                   // 0x00c14e70
    void  FUN_00c1d460(u32 a, u32 b);               // 0x00c1d460
    void  FUN_00c17350(u32 a, u32 b);               // 0x00c17350
};

struct SeaEvent
{
    char      pad00[0x40];
    SeaObj**  mpBegin;                              // +0x40
    SeaObj**  mpEnd;                                // +0x44
};

struct SeaMonsterEvent
{
    char          pad00[0x2c];
    float         mf2c;                             // +0x2c
    char          pad30[0x44 - 0x30];
    RT::ValueMap  mCounters;                        // +0x44

    SeaEvent* FUN_00d4cf10(u32 a, u32 b);           // 0x00d4cf10
    void  TriggerEvent(u32 arg);                    // 0x00d512f0
};

// @ 0x00d512f0
void SeaMonsterEvent::TriggerEvent(u32 arg)
{
    if (mCounters[0x614a7ea] == 0 && !(0.0f > mf2c))
    {
        SeaEvent* e = FUN_00d4cf10(0x609f2f8, 0x52aa6117);
        if (e != 0)
        {
            SeaObj** p = e->mpBegin;
            SeaObj** pEnd = e->mpEnd;
            if (p != pEnd)
            {
                do
                {
                    SeaObj* o = *p;
                    if (o != 0)
                    {
                        ((void(__thiscall*)(void*))VTC(o, 0))(o);
                        if (o->LookupTextStyle(0x6a17b05a) == 0)
                            o->FUN_00c1d460(0x6a17b05a, 0x6a17b05a);
                        ((void(__thiscall*)(void*))VTC(o, 4))(o);
                    }
                    ++p;
                } while (p != pEnd);
            }
        }
        return;
    }

    bool firstTime = (mCounters[0x614a7ea] == 0);
    void* avatar = GetNounManager()->GetAvatar();
    SeaEvent* e = FUN_00d4cf10(0x609f2f8, 0x52aa6117);
    if (e == 0 || avatar == 0)
        return;
    SeaObj** p = e->mpBegin;
    SeaObj** pEnd = e->mpEnd;
    if (p == pEnd)
        return;
    do
    {
        SeaObj* o = *p;
        if (o != 0)
            ((void(__thiscall*)(void*))VTC(o, 0))(o);
        ((Sub8*)((char*)o->mpSub + 8))->Apply(0, 4, *(float*)0x147af20, avatar);
        if (firstTime)
        {
            mCounters[0x614a7ea] = 1;
            o->FUN_00c17350(0x6a17b05a, 0);
        }
        else
        {
            void* asub = (char*)avatar + 0xc0;
            void* osub = (char*)o + 0xc0;
            const RT::Vec3* ap = ((const RT::Vec3*(__thiscall*)(void*))VTC(asub, 0x2c))(asub);
            const RT::Vec3* op = ((const RT::Vec3*(__thiscall*)(void*))VTC(osub, 0x2c))(osub);
            float dx = op->x - ap->x;
            float dy = op->y - ap->y;
            float dz = op->z - ap->z;
            float dist = (dz * dz + dy * dy) + dx * dx;
            if (dist > 10000.0f ||
                (dist > 2500.0f && ((char(__thiscall*)(void*))VTC(osub, 0x48))(osub) == 0))
            {
                if (o->mb135 != 0)
                {
                    o->mb135 = 0;
                    o->mbF90 = 0;
                    void* s = ((void*(__thiscall*)(void*))VTC(osub, 0xac))(osub);
                    if (s != 0)
                    {
                        *(u32*)((char*)s + 4) &= ~1u;
                        _ReadWriteBarrier();
                        void* inner = *(void**)s;
                        ((void(__thiscall*)(void*, void*, int))VTC(inner, 0x16c))(inner, s, 0);
                    }
                }
            }
        }
        ((void(__thiscall*)(void*))VTC(o, 4))(o);
        ++p;
    } while (p != pEnd);
}

// @ 0x00d51950
void Method1950()
{
    DramaManager* dm = GetDramaInstance();
    void* avatar = GetNounManager()->GetAvatar();
    *(u8*)((char*)avatar + 0x131) = 1;
    dm->CheckBabyTeacher();

    float v[3];
    ((void(__thiscall*)(void*, float*))VTC((char*)avatar + 0xc0, 0x5c))((char*)avatar + 0xc0, v);

    if (dm->mp14 == 0)
    {
        void* a = ((void*(__thiscall*)(void*, int, int))0x00c04590)(avatar, 0, 1);
        void* b = ((void*(__thiscall*)(void*, u32, int))0x00c04590)(avatar, *(u32*)((char*)avatar + 0xb20), 1);
        void* pos = ((void*(__thiscall*)(void*))0x00c6acc0)(b);
        void* mate = ((void*(__cdecl*)(void*))0x00c099e0)(pos);
        void* old = dm->mp14;
        if (mate != old)
        {
            if (mate != 0)
                ((void(__thiscall*)(void*))VTC(mate, 0))(mate);
            dm->mp14 = mate;
            if (old != 0)
                ((void(__thiscall*)(void*))VTC(old, 4))(old);
        }
    }

    float scale = ((float(__thiscall*)(void*))VTC((char*)dm->mp14 + 0xc0, 0x74))((char*)dm->mp14 + 0xc0);
    scale = scale * 2.0f + *(float*)0x1471064;

    float off[3];
    off[0] = v[0] * scale;
    off[1] = v[1] * scale;
    off[2] = v[2] * scale;

    void* asub = (char*)avatar + 0xc0;
    const RT::Vec3* ap = ((const RT::Vec3*(__thiscall*)(void*))VTC(asub, 0x2c))(asub);
    float p2[3];
    p2[0] = ap->x + off[0];
    p2[1] = ap->y + off[1];
    p2[2] = ap->z + off[2];

    float snapped[3];
    ::GetPlanetModel()->SnapB(snapped, p2, 0);

    float neg[3];
    neg[0] = -v[0];
    neg[1] = -v[1];
    neg[2] = -v[2];

    float orient[3];
    ::GetPlanetModel()->BuildSurfaceOrientation2(orient, snapped, neg);

    void* msub = (char*)dm->mp14 + 0xc0;
    ((void(__thiscall*)(void*, const float*, const float*))VTC(msub, 0x44))(msub, snapped, orient);

    float f = *(float*)0x147af20;
    void* mpSub = ((SeaObj*)dm->mp14)->mpSub;
    ((Sub8*)((char*)mpSub + 8))->Apply(0, 0x4000000, f, 0);
}

// @ 0x00d51b60
void Method1b60()
{
    void* avatar = GetNounManager()->GetAvatar();
    if (avatar == 0)
        return;
    *(u8*)((char*)avatar + 0x131) = 0;

    DramaManager* dm = GetDramaInstance();
    if (dm->mp14 != 0)
    {
        float f = *(float*)0x1582f88 * *(float*)0x1470f1c;
        ((Mate*)dm->mp14)->Activate(f);
    }

    dm = GetDramaInstance();
    void* p = dm->mp14;
    if (p != 0)
    {
        dm->mp14 = 0;
        ((void(__thiscall*)(void*))VTC(p, 4))(p);
    }
}

}  // namespace G7

// ---------------------------------------------------------------------------
// 0x00d51540: Task::Method1540 (member of the cl2 RT::Task class above).
// ---------------------------------------------------------------------------
namespace RT
{
    struct PosseSimulator { void RemovePosseMember(Creature* c, int a, int b); };   // 0x00d53490
    extern "C" PosseSimulator* GetPosseSimulator();                                 // 0x00d539d0
}

// @ 0x00d51540
void RT::Task::Method1540()
{
    unsigned key = 0x609f2f8;
    PairUR* const end = mSlots.mpEnd;
    PairUR* it = LowerBound(mSlots.mpBegin, end, &key, mSlots.mbFlag);
    if (it == end || key < it->key)
        it = end;
    else if (it == it + 1)
        it = end;
    if (it == mSlots.mpEnd)
        return;

    Obj* o = it->value;
    if (o == 0)
        return;
    Herd* h = (Herd*)o->Cast(0x52aa6117);
    if (h == 0)
        return;

    CreatureHost* host = GetCreatureHost();
    PosseSimulator* ps = GetPosseSimulator();
    for (Creature** p = h->mpCreaturesBegin; p != h->mpCreaturesEnd; ++p)
    {
        Creature* c = *p;
        host->FUN_00aca360(c);
        if (ps != 0)
            ps->RemovePosseMember(c, 0, 0);
    }
    GetNounManager()->RemoveNoun(h);
    mSlots.Remove(key);
}
