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

// ---------------------------------------------------------------------------------------------
// Simulator UI panel: 8 layout sub-objects (0x100 bytes each) followed by 8 ref-counted slots.
struct IRef2 {
    virtual void AddRef();
    virtual void Release();                                         // +4
};
struct SimSlot {
    void ResetSerializer();                                         // 0x00c2e4e0
    uint8_t pad00[0x100];                                           // sizeof == 0x100
};
struct SimPanel {
    SimSlot mSlotArray[8];                                          // +0x000
    IRef2*  mRefArray[8];                                           // +0x800
    void Shutdown();
};
extern "C" void* __cdecl memset(void*, int, size_t);

// @ 0x00cadb00
void SimPanel::Shutdown()
{
    int i = 7;
    do
    {
        IRef2* r = mRefArray[i];
        if (r)
            r->Release();
    } while (--i >= 0);
    int j = 7;
    do
    {
        mSlotArray[j].ResetSerializer();
    } while (--j >= 0);
}

// @ 0x00cadb50
void SimPanelReset(SimPanel* panel)
{
    memset(panel, 0, 0x800);
    for (int i = 0; i < 8; ++i)
    {
        IRef2* r = panel->mRefArray[i];
        if (r)
        {
            panel->mRefArray[i] = 0;
            r->Release();
        }
    }
}

// Normalized-direction helper: out = normalize(v) * ctx->GetScale(v).
struct NormCtx {
    float GetScale(const Vec3& v);                                  // 0x00c9ffd0
};
extern const float kNormalizeEps;                                   // 0x013ec4b8

// @ 0x00cadb90
void ScaleNormalizedVec(Vec3* out, const Vec3* v, NormCtx* ctx)
{
    float scale = ctx->GetScale(*v);
    float inv = 1.0f / sqrtf(v->x * v->x + v->y * v->y + v->z * v->z + kNormalizeEps);
    Vec3 dir;
    dir.x = v->x * inv;
    dir.y = v->y * inv;
    dir.z = v->z * inv;
    out->x = dir.x * scale;
    out->y = dir.y * scale;
    out->z = dir.z * scale;
}

// Ref-counted simulator object added to a per-object target list.
struct SimTarget {
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void AddRef();                                          // +0x60
    virtual void Release();                                         // +0x64
};

struct SimTargetVec {                   // eastl::vector<AutoRefCount<SimTarget>>
    SimTarget** mpBegin;                                            // +0x684
    SimTarget** mpEnd;                                              // +0x688
    SimTarget** mpEndOfStorage;                                     // +0x68c
    void PushBack(SimTarget* const& value);
    void Grow(SimTarget** pEnd, SimTarget* const& value);           // 0x00ae6ed0
};

void SimTargetVec::PushBack(SimTarget* const& value)
{
    SimTarget** pEnd = mpEnd;
    if (pEnd >= mpEndOfStorage) {
        Grow(pEnd, value);
        return;
    }
    mpEnd = pEnd + 1;
    if (!pEnd)
        return;
    *pEnd = value;
    if (value)
        value->AddRef();
}

struct SimObject {
    uint8_t pad00[0x684];
    SimTargetVec mTargets;                                          // +0x684
    void AddTarget(SimTarget* target);
};

// @ 0x00cad7e0
void SimObject::AddTarget(SimTarget* target)
{
    SimTargetVec* vec = &mTargets;
    SimTarget** it = vec->mpBegin;
    SimTarget** end = vec->mpEnd;
    if (it != end) {
        do {
            if (*it == target)
                break;
            ++it;
        } while (it != end);
    }
    if (it != end)
        return;

    SimTarget* ref = target;
    if (ref)
        ref->AddRef();
    vec->PushBack(ref);
    if (ref)
        ref->Release();
}

// Sub-object reached through SimObjA::mSub; its vtable feeds the pathing update.
struct SimSub {
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10();
    virtual Vec3* GetPos();                                         // +0x2c
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28();
    virtual float GetPathScale();                                   // +0x74
    virtual void V30(); virtual void V31(); virtual void V32(); virtual void V33();
    virtual void V34(); virtual void V35(); virtual void V36(); virtual void V37();
    virtual void V38(); virtual void V39(); virtual void V40(); virtual void V41();
    virtual void V42(); virtual void V43(); virtual void V44(); virtual void V45();
    virtual void V46(); virtual void V47(); virtual void V48(); virtual void V49();
    virtual void V50(); virtual void V51(); virtual void V52(); virtual void V53();
    virtual void V54(); virtual void V55(); virtual void V56();
    virtual void SetDestination(const Vec3& v, float radius);       // +0xe4
    void* CreateSpawn();                                            // 0x00c41ec0
};

struct SimObjA : NormCtx {
    uint8_t pad00[0x34];
    SimSub  mSub;                                                   // +0x34
    uint8_t pad38[0x2a4 - 0x38];
    uint32_t mFlags;                                                // +0x2a4
};

struct SimObjB {
    uint8_t pad00[0x14];
    Vec3    mDir;                                                   // +0x14
    uint8_t pad20[0x50 - 0x20];
    Vec3    mVel;                                                   // +0x50
    int32_t mMode;                                                  // +0x5c
    uint8_t pad60[0x68 - 0x60];
    float   mTimer;                                                 // +0x68
    float   mTimer2;                                                // +0x6c
};

struct SimStepProvider {
    uint8_t pad00[0x10];
    float mStep;                                                    // +0x10
};

Vec3 normalized_safe(const Vec3& v);                                // 0x00449c20
extern const float kPathOne;                                        // 0x013eb8a0
extern const float kPathTwo;                                        // 0x013eeda0

// @ 0x00cadd50
void SimPathUpdate(SimStepProvider* step, SimObjA* a, SimObjB* b, bool armed, float dt)
{
    if (dt < b->mTimer && !(a->mFlags & 0xb))
    {
        b->mTimer2 = 0.0f;
        return;
    }
    b->mTimer2 += step->mStep;
    if (b->mTimer2 <= kPathOne)
        return;

    Vec3 dir;
    ScaleNormalizedVec(&dir, &b->mDir, a);
    b->mDir = dir;
    if (b->mTimer2 <= kPathTwo)
        return;

    if (!armed || b->mMode != 3)
    {
        a->mFlags |= 1;
        return;
    }

    float k = a->mSub.GetPathScale();
    Vec3 tmp;
    tmp.x = b->mVel.x * k + b->mDir.x;
    tmp.y = b->mVel.y * k + b->mDir.y;
    tmp.z = b->mVel.z * k + b->mDir.z;
    const Vec3* pos = a->mSub.GetPos();
    tmp.x -= pos->x;
    tmp.y -= pos->y;
    tmp.z -= pos->z;
    b->mVel = normalized_safe(tmp);
    a->mFlags &= ~0xbu;
}

struct SimSpawnOut {
    Vec3    mPos;                                                   // +0x00
    uint8_t pad0c[0x50 - 0x0c];
    Vec3    mVel;                                                   // +0x50
    int32_t mKind;                                                  // +0x5c
    float   mScale;                                                 // +0x60
};

struct SimSpawnSrc {
    void**  mpBegin;                                                // +0x00
    void**  mpEnd;                                                  // +0x04
    uint8_t pad08[0x14 - 0x08];
    Vec3    mVec;                                                   // +0x14
    float   mRadiusIn;                                              // +0x20
    uint8_t pad24[0x50 - 0x24];
    Vec3    mVel;                                                   // +0x50
    int32_t mKind;                                                  // +0x5c
    float   mScale;                                                 // +0x60
};

extern const float kSpawnRadiusBias;                                // 0x013ec4d0

// @ 0x00cadc20
bool SimTrySpawn(SimSpawnOut* out, SimObjA* self, const Vec3* target, SimSpawnSrc* src)
{
    if (src->mpBegin != src->mpEnd)
        return true;

    float radiusIn = src->mRadiusIn;
    float radius = src->mRadiusIn + src->mScale + kSpawnRadiusBias;
    if (self->mFlags & 4)
        return true;

    float dx = src->mVec.x - target->x;
    float dy = src->mVec.y - target->y;
    float dz = src->mVec.z - target->z;
    if (dx * dx + dy * dy + dz * dz <= radius * radius)
        return true;

    out->mPos.x = 0.0f;
    out->mPos.y = 0.0f;
    out->mPos.z = 0.0f;

    self->mSub.SetDestination(src->mVec, radiusIn);
    SimSpawnOut* spawn = (SimSpawnOut*)self->mSub.CreateSpawn();
    spawn->mVel = src->mVel;
    spawn->mKind = src->mKind;
    spawn->mScale = src->mScale;
    return false;
}
