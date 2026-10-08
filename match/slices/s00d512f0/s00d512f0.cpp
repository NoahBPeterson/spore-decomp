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
    };
    struct PlanetModel { void MakeRandomWorldPosition(Vec3* out, const Vec3* center, float a, float b); }; // 0x00b81780 (ret 0x10)

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
