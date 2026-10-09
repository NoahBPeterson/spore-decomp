// Slice s00cacf40: per-tick "nearby objects" update of a creature-like agent (VA 00cacf40, thiscall on the
// secondary-base subobject at object+0x34; the full object is this-0x34).
// Flags guess: /O2 /MD /Gy /TP /arch:SSE /fp:fast (inline fsqrt; without /fp:fast sqrtf becomes a _CIsqrt call).
//
// What it does:
//   1. BaseUpdate(); in game mode A refreshes a float from the owner info and ticks the tracker (+0x61c).
//   2. Works out the sensing range: game mode A -> field at +0x26c, else gauge.GetBase() + 60.
//   3. Collects into the AutoRefCount list at +0x278 (unique entries) every object closer than the range:
//        - all tribes (game data vector 0x18c6de8) except the owner itself,
//        - all objects of the SimSingleton list,
//        - if the civ-mode strategy exists: the nearest tribe of data vector 0x18c43e8, and (when it is
//          within range + its radius) all of its members and interaction agents.
//   4. Re-targets the nearest tribe (+0xb28) with attach/detach notifications on the gauge.
//   5. Clears the creature list at +0xb58 and refills it from the +0x278 list with the objects that pass the
//      species/owner/relationship checks, then runs the finishing step on the full object.
#include "types.h"
#include <math.h>
#include <new>

struct Vec3 { float x, y, z; };

#define VSLOT(o, off) ((*(void***)(o))[(off) / 4])

// -- interface helpers (retail vtable slots) ----------------------------------------------------------
static __forceinline Vec3* PosOf(void* o) { return ((Vec3*(__thiscall*)(void*))VSLOT(o, 0x2c))(o); }
static __forceinline void SpAddRef(void* o) { ((void(__thiscall*)(void*))VSLOT(o, 0xbc))(o); }
static __forceinline void SpRelease(void* o) { ((void(__thiscall*)(void*))VSLOT(o, 0xc0))(o); }
static __forceinline void* SpCast(void* o, uint32_t id) { return ((void*(__thiscall*)(void*, uint32_t))VSLOT(o, 0xb8))(o, id); }
static __forceinline void CrAddRef(void* o) { ((void(__thiscall*)(void*))VSLOT(o, 0x60))(o); }
static __forceinline void CrRelease(void* o) { ((void(__thiscall*)(void*))VSLOT(o, 0x64))(o); }
static __forceinline void TrAddRef(void* o) { ((void(__thiscall*)(void*))VSLOT(o, 0x0))(o); }
static __forceinline void TrRelease(void* o) { ((void(__thiscall*)(void*))VSLOT(o, 0x4))(o); }

static __forceinline float DistXYZ(const Vec3* a, const Vec3* b)
{
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float dz = b->z - a->z;
    return sqrtf((dx * dx + dy * dy) + dz * dz);
}
static __forceinline float DistZYX(const Vec3* a, const Vec3* b)
{
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float dz = b->z - a->z;
    return sqrtf((dz * dz + dy * dy) + dx * dx);
}

// -- containers -------------------------------------------------------------------------------------
struct SpList {                     // eastl::vector<AutoRefCount<spatial>> (4-byte elements)
    void** mBegin; void** mEnd; void** mCap;
    void DoInsertValue(void** pos, void** const& v);        // 0x00bab900
};
struct CrList {                     // eastl::vector<AutoRefCount<creature>>
    void** mBegin; void** mEnd; void** mCap;
    void DoInsertValue(void** pos, void** const& v);        // 0x00ae6ed0
};
void** __cdecl CopyPtrRange(void** first, void** last, void** dest);       // 0x00ae6880

static __forceinline void AddUnique(SpList* v, void* p)
{
    void** it = v->mBegin;
    void** end = v->mEnd;
    if (it != end) {
        do {
            if (*it == p) break;
            ++it;
        } while (it != end);
        if (it != end) return;
    }
    void* tmp = p;
    if (tmp) SpAddRef(tmp);
    if (v->mEnd < v->mCap) {
        void** slot = v->mEnd++;
        if (slot) {
            *slot = p;
            if (p) SpAddRef(p);
        }
    } else {
        v->DoInsertValue(v->mEnd, &tmp);
    }
    if (tmp) SpRelease(tmp);
}

// -- external pieces ---------------------------------------------------------------------------------
struct PtrRange { void** mBegin; void** mEnd; };
struct GameDataVec { int pad0; PtrRange vec; };
typedef void (__cdecl *GameDataFn)();
struct NounMgr {
    GameDataVec* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d, void* type);  // 0x00b21340
};
NounMgr* NounManager();                                         // 0x00b3d300
const void* GetCurrentGameMode();                               // 0x00b5b800
extern char kGameModeA;                                         // 0x01654c10
extern char kTypeTribes;                                        // 0x018c6de8
extern char kTypeTribes2;                                       // 0x018c43e8
extern char kCreatureType;                                      // 0x013f94d4
void __cdecl fnA();     // 0x00cd7d10
void __cdecl fnB();     // 0x00d3d420
void __cdecl fnC();     // 0x00ae72d0
void __cdecl fnD();     // 0x00b1e500
void __cdecl fnE();     // 0x00acdff0

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
struct SimList { void** mBegin; void** mEnd; };
struct SimSingleton {
    char data[0x58];
    SimSingleton();                                             // 0x00dc7d70
    SimList* GetObjects();                                      // 0x00ad2800
};
extern SimSingleton* gSimSingleton;                             // 0x01699ab8

struct CivStrategy;
CivStrategy* GetCivStrategy();                                  // 0x00cf74c0

struct MemberVec { void** mBegin; void** mEnd; };

struct OwnerInfo { char pad[0x14]; float v14; };
struct Gauge {
    virtual void g0(); virtual void g1(); virtual void g2(); virtual void g3();
    virtual int GetOwnerId();                                   // +0x10
    float GetBaseRange();                                       // 0x00bfc400
};
struct TribeInfo { char pad[0x25c]; float radius; };
struct Tribe {
    char pad[0x120];
    char spatial[1];                                            // +0x120 (position provider subobject)
    char pad2[0x354 - 0x121];
    void** mAgentsBegin;                                        // +0x354
    void** mAgentsEnd;                                          // +0x358
    MemberVec* GetMembers();                                    // 0x00c8e810
    void Attach(Gauge* g);                                      // 0x00be2390
    void Detach(Gauge* g);                                      // 0x00be2420
};
struct Tracker {
    void Update();                                              // 0x00c7dcb0
};
struct RelMgr {
    int Relation(int a, int b, int c);                          // 0x00d00a70
};
RelMgr* RelationshipManager();                                  // 0x00b3d2c0
struct CrHelper {
    bool Test();                                                // 0x00c0c0e0
};

struct Real {
    virtual void r0();
    char pad04[0x4c - 4];
    void FinalStep();                                           // 0x00cabe70
};

static __forceinline void PushCreature(CrList* v, void* c)
{
    void* tmp = c;
    CrAddRef(c);
    if (v->mEnd < v->mCap) {
        void** slot = v->mEnd++;
        if (slot) {
            *slot = c;
            CrAddRef(c);
        }
    } else {
        v->DoInsertValue(v->mEnd, &tmp);
    }
    if (tmp) CrRelease(tmp);
}

static __forceinline void* CastOrNull(void** slot, uint32_t id)
{
    void* o = *slot;
    return o ? SpCast(o, id) : 0;
}

struct Agent34 {
    virtual void a0();
    char pad04[0x26c - 4];
    float mSenseRange;                                          // +0x26c
    char pad270[8];
    SpList mNear;                                               // +0x278
    char pad284[0x4d4 - 0x284];
    Gauge mGauge;                                               // +0x4d4
    char pad4d8[0x61c - 0x4d8];
    Tracker mTracker;                                           // +0x61c
    char pad61d[0xab4 - 0x61d];
    float mOwnerValue;                                          // +0xab4
    char pad_ab8[0xb28 - 0xab8];
    Tribe* mNearest;                                            // +0xb28
    char padb2c[0xb58 - 0xb2c];
    CrList mCreatures;                                          // +0xb58

    void BaseUpdate();                                          // 0x00c42350
    Real* R() { return (Real*)((char*)this - 0x34); }
    void Update();
};

// @ 0x00cacf40
void Agent34::Update()
{
    BaseUpdate();
    if (GetCurrentGameMode() == &kGameModeA) {
        OwnerInfo* info = ((OwnerInfo*(__thiscall*)(void*))VSLOT(this, 0x68))(this);
        mOwnerValue = info->v14;
        mTracker.Update();
    }
    float range;
    if (GetCurrentGameMode() != &kGameModeA)
        range = mGauge.GetBaseRange() + 60.0f;
    else
        range = mSenseRange;

    // 1. all other tribes
    PtrRange* gv = &NounManager()->GetGameDataVector(fnA, fnB, fnC, fnD, &kTypeTribes)->vec;
    void** it = gv->mBegin;
    void** end = gv->mEnd;
    if (it != end) {
        do {
            void* t = *it;
            if (t != (void*)R()) {
                Vec3* a = PosOf(this);
                char* sp = (char*)t + 0x34;
                Vec3* b = PosOf(sp);
                if (DistXYZ(a, b) < range)
                    AddUnique(&mNear, sp);
            }
            ++it;
        } while (it != end);
    }

    // 2. the SimSingleton object list
    if (!gSimSingleton)
        gSimSingleton = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
    SimList* sl = gSimSingleton->GetObjects();
    it = sl->mBegin;
    end = sl->mEnd;
    if (it != end) {
        do {
            Vec3* a = PosOf(this);
            void* sp = *it;
            Vec3* b = PosOf(sp);
            if (DistZYX(a, b) < range)
                AddUnique(&mNear, sp);
            ++it;
        } while (it != end);
    }

    // 3. nearest tribe and its members / agents
    if (GetCivStrategy()) {
        float bestDist = 3.40282346e+38f;
        Tribe* best = 0;
        PtrRange* gv2 = &NounManager()->GetGameDataVector(fnA, fnB, fnE, fnD, &kTypeTribes2)->vec;
        int n = (int)(gv2->mEnd - gv2->mBegin);
        for (int i = 0; i < n; ++i) {
            Tribe* t = (Tribe*)gv2->mBegin[i];
            Vec3* a = PosOf(this);
            Vec3* b = PosOf(&t->spatial);
            float d = DistZYX(a, b);
            if (d < bestDist) {
                bestDist = d;
                if (t != best) {
                    TrAddRef(t);
                    Tribe* old = best;
                    best = t;
                    if (old) TrRelease(old);
                }
            }
            TribeInfo* ti = ((TribeInfo*(__thiscall*)(void*))VSLOT(t, 0x6c))(t);
            if (d - ti->radius < range) {
                MemberVec* mv = t->GetMembers();
                void** mp = mv->mBegin;
                void** me = mv->mEnd;
                if (mp != me) {
                    do {
                        Vec3* a2 = PosOf(this);
                        char* sp = (char*)*mp + 0x34;
                        Vec3* b2 = PosOf(sp);
                        if (DistZYX(a2, b2) < range)
                            AddUnique(&mNear, sp);
                        ++mp;
                    } while (mp != me);
                }
                void** ap = t->mAgentsBegin;
                void** ae = t->mAgentsEnd;
                if (ap != ae) {
                    do {
                        Vec3* a2 = PosOf(this);
                        char* sp = (char*)*ap + 0x34;
                        Vec3* b2 = PosOf(sp);
                        if (DistZYX(a2, b2) < range)
                            AddUnique(&mNear, sp);
                        ++ap;
                    } while (ap != ae);
                }
            }
        }
        if (best != mNearest) {
            if (mNearest)
                mNearest->Detach(R() ? &mGauge : 0);
            if (best)
                best->Attach(R() ? &mGauge : 0);
            Tribe* old = mNearest;
            if (best != old) {
                if (best) TrAddRef(best);
                mNearest = best;
                if (old) TrRelease(old);
            }
        }
        if (best) TrRelease(best);
    }

    // 4. rebuild the creature list from the near list
    {
        void** first = mCreatures.mBegin;
        void** last = mCreatures.mEnd;
        void** newEnd = CopyPtrRange(last, mCreatures.mEnd, first);
        void** cEnd = mCreatures.mEnd;
        for (void** p = newEnd; p < cEnd; ++p)
            if (*p) CrRelease(*p);
        mCreatures.mEnd -= (last - first);
    }
    int myId = mGauge.GetOwnerId();
    void** np = mNear.mBegin;
    void** ne = mNear.mEnd;
    if (np != ne) {
        do {
            void* item = *np;
            void* c;
            if (item && (c = SpCast(item, (uint32_t)&kCreatureType)) != 0) {
                void* q1 = CastOrNull(np, 0x4f176642);
                void* q2 = CastOrNull(np, 0x403df5f);
                void* q3 = CastOrNull(np, 0x116d858);
                void* q4 = CastOrNull(np, 0xb033b403);
                if (!q1 && !q2 && !q3 && !q4) {
                    bool add = false;
                    const void* mode = GetCurrentGameMode();
                    int (__thiscall *getOwner)(void*) = (int (__thiscall*)(void*))VSLOT(c, 0x10);
                    if (mode == &kGameModeA) {
                        add = getOwner(c) != myId;
                    } else {
                        int v = getOwner(c);
                        if (v == myId || v == -1) {
                            void* r = ((void*(__thiscall*)(void*, uint32_t))VSLOT(c, 0x5c))(c, 0xce9f6639);
                            if (r)
                                add = ((CrHelper*)r)->Test();
                        } else {
                            void* rel = ((void*(__thiscall*)(void*))VSLOT(c, 0xc))(c);
                            int a = ((int(__thiscall*)(void*))VSLOT(R(), 0x4c))(R());
                            int b = ((int(__thiscall*)(void*))VSLOT(rel, 0x4c))(rel);
                            add = RelationshipManager()->Relation(b, a, 1) <= 1;
                        }
                    }
                    if (add)
                        PushCreature(&mCreatures, c);
                }
            }
            ++np;
        } while (np != ne);
    }
    R()->FinalStep();
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
