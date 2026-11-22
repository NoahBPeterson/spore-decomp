// src/game/SPGonzago/_at_00cb0000.cpp -- migrated from slice(s) s00cb2480, s00cb1270, s00cb1110 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00cb0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cSpatialObject.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)
// no <math.h>: slice s00cb2480 supplies its own inline `sqrtf`, which <math.h> also declares (C2084);
// both slices declare `sqrt` themselves.
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

// ---- items of slice s00cb1110 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(size_t, void* p) { return p; }
#define EASTL_ALLOCATOR_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
struct TraceCache
{
    char mBytes[0x820];          // 8 * 0x100 hit records followed by 8 cached object pointers
};
struct Value                       // the hashtable value (0x824 bytes)
{
    unsigned   mKey;               // +0x000
    TraceCache mTrace;             // +0x004 .. +0x823

    Value(const Value& src);       // 0x00cb02a0
};
struct Node
{
    Value mValue;                  // +0x000 .. +0x823
    Node* mpNext;                  // +0x824
};
struct Iter                        // eastl hash iterator (8 bytes)
{
    Node*  mpNode;                 // +0x00
    Node** mpBucket;               // +0x04
};
struct InsertResult                // eastl insert() result (12 bytes)
{
    Node*  mpNode;                 // +0x00
    Node** mpBucket;               // +0x04
    bool   mInserted;              // +0x08
};
struct RehashResult                // prime_rehash_policy::RehashResult (8 bytes)
{
    bool     first;                // +0x00
    unsigned second;               // +0x04
};
struct RehashPolicy
{
    float    mfMaxLoadFactor;      // +0x00
    float    mfGrowthFactor;       // +0x04
    unsigned mnNextResize;         // +0x08

    // 0x00921440
    RehashResult GetRehashRequired(unsigned nBucketCount, unsigned nElementCount, unsigned nElementAdd);
};
struct Ht                          // global instance at 0x0157d30c
{
    void*        mField00;         // +0x00 (hash functor)
    Node**       mpBuckets;        // +0x04
    unsigned     mBucketCount;     // +0x08
    unsigned     mSize;            // +0x0c
    RehashPolicy mRehashPolicy;    // +0x10

    void Find(Iter* out, const unsigned* key);                            // 0x00cb00d0
    TraceCache* FindOrInsert(const unsigned* key);                        // 0x00c2b080
    void DoRehash(unsigned newBucketCount);                               // 0x00c29710

    Node* DoFindNode(Node* pNode, unsigned key)
    {
        for (; pNode; pNode = pNode->mpNext) {
            if (key == pNode->mValue.mKey)
                return pNode;
        }
        return 0;
    }

    Node* DoAllocateNode(const Value& value)
    {
        Node* const pNode = (Node*)operator new[](sizeof(Node), "Simulator", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
        if (pNode)
            ::new (&pNode->mValue) Value(value);
        pNode->mpNext = 0;
        return pNode;
    }

    InsertResult DoInsertValue(const Value& value, bool trueType);        // 0x00cb1110
};
// ---- items of slice s00cb1110 end

// ---- items of slice s00cb1270 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
#define AT(T, p, off) (*(T*)((char*)(p) + (off)))
#define VT(p) (*(void***)(p))
struct Goal {
    float* mpPoints;          // +0x00: array of 0x3c-byte records, xyz first
    char pad04[0x10];
    Vec3 target;              // +0x14
    char pad20[0x3c];
    int mActive;              // +0x5c
    unsigned Count();         // FUN_00ac15f0
};
struct Loco {                 // SP::cLocomotiveObject sub-object (at owner + 0x34)
    Vec3* GetVelocity();      // 0xd20610
    Goal* GetGoal();          // 0xc41ec0
    bool IsNearGoal();        // 0xc42e20
};
struct Transform {
    char d[0x3c];
    Transform();   // 0x409930
};
struct Mesh {
    char pad00[0x40];
    char data40[0xc];
    Vec3* mpBegin;            // +0x4c
    Vec3* mpEnd;              // +0x50
};
struct MeshRef {
    Mesh* GetMesh();   // 0xb7c360
};
struct Obj {                  // spatial object seen through the entity's component
    void LocalToWorldTransform(Transform* xf);     // 0xc897e0
};
struct Creature {
    bool Check();   // 0xc0c0e0
};
struct Flag10c {
    int Check();   // 0xc90460
};
struct Hit { void* first; void* second; };
struct HitVec {               // fixed-capacity vector of 16 hits
    Hit* mpBegin;
    Hit* mpEnd;
    Hit* mpCapacity;
    int pad0c;
    Hit* mpFixed;
    int pad14;
    Hit buf[16];
    HitVec() { mpBegin = buf; mpEnd = buf; mpCapacity = buf + 16; mpFixed = buf; }
    void erase(Hit* first, Hit* last);             // 0xd018d0
};
struct Filter { int a, b, c, d, e; char f, g; };
struct Ctx {
    void* self;
    char sub[0x18];
    float radius;
};
struct SweepOut {
    int type;
    void* hitObj;
    float hitFrac;
    int hitFlag;
    char pad10[0x10];
    int count20;
    char pad24[0x10];
    Vec3 hitVec;
};
void* __cdecl GonzagoModelWorld();
Vec3* __cdecl normalized_safe(Vec3* out, const Vec3* in);
float __cdecl Dot3(const Vec3* a, const Vec3* b);
float __cdecl FUN_00c297d0(const Vec3* origin, const Vec3* vel, const Vec3* pos, const Vec3* velV);
float __cdecl FUN_00c29880(const Vec3* origin, const Vec3* vel, const Vec3* pos, const Vec3* velV, float r);
bool __cdecl FUN_0041dd30(void* sub, const Vec3* origin);
void* __cdecl FUN_00ae6760(void* o);
void* __cdecl FUN_00cb1210(void* o);
void* __cdecl FUN_00ac80d0(void* o, unsigned id);
void* __cdecl FUN_00f19200(void* o);
void* __stdcall FUN_00b3d3c0(void* o);
bool __cdecl FUN_00af5400(SweepOut* out, void* other, const Vec3* origin, const Vec3* pos, const Vec3* seg,
                          const Vec3* dir, float* t, float one, Transform* xf, void* meshData, float rad,
                          Vec3* tris, unsigned nTris, float radius, int zero, SweepOut* out2);
bool __cdecl FUN_00af17f0(SweepOut* out, void* other, const Vec3* origin, const Vec3* pos, const Vec3* dir,
                          float* t, float one, float rr, int flag, SweepOut* out2);
void __cdecl FUN_00af7c60(const Vec3* origin, const Vec3* dir, float radius, float one, int a, int b,
                          SweepOut* out, float* t);
void __cdecl FUN_00af3e50(const Vec3* origin, const Vec3* dir, float radius, float a, float b, float c,
                          SweepOut* out, float* t, int zero);
void __cdecl FUN_00af4870(const Vec3* origin, const Vec3* dir, float radius, float a, SweepOut* out, float* t);
typedef void* (__thiscall* FnPtr1)(void*, unsigned);
typedef Vec3* (__thiscall* FnVec0)(void*);
typedef float (__thiscall* FnF0)(void*);
typedef void* (__thiscall* FnP1)(void*, void*);
typedef void* (__thiscall* FnP0)(void*);
typedef unsigned (__thiscall* FnU0)(void*);
typedef int (__thiscall* FnI0)(void*);
typedef void (__thiscall* FnWorld)(void*, const Vec3*, Vec3*, HitVec*, Filter*, float);
// ---- items of slice s00cb1270 end

// ---- items of slice s00cb2480 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline float sqrtf(float x) { return (float)sqrt((double)x); }
struct Waypoint {
    Vec3  pos;        // 0x00
    float weight;     // 0x0c
    int   kind;       // 0x10
    Vec3  v14, v20, v2c;
    unsigned char flags;   // 0x38 (bit 0 = "tracked" waypoint)
    char  pad39[3];
    Waypoint(const Vec3& p) : pos(p), weight(1.0f), kind(0) { flags = 0; }
    Waypoint(const Waypoint& o);                        // 0x00ac1ff0
};
struct WaypointPath {                // creature path (eastl::vector<Waypoint> + extras)
    Waypoint* mpBegin;               // +0x00
    Waypoint* mpEnd;                 // +0x04
    Waypoint* mpCapacity;            // +0x08
    int       mAlloc;                // +0x0c
    int       pad10;
    Waypoint  cur;                   // +0x14 current waypoint
    char      pad50[0x20];
    unsigned  mode;                  // +0x70 (bit 1 = hold)
    Waypoint* erase(Waypoint* first, Waypoint* last);                    // 0x00ac4570
    void      InsertRange(Waypoint* where, Waypoint* first, Waypoint* last, float f);   // 0x00b96360
    void      EraseOne(Waypoint* where);                                  // 0x00b47520
};
struct Hit_s00cb_2480 {
    char  p00[4];
    int   f04;                       // +0x04 (cache entry: "has limit")
    float f08;                       // +0x08 (cache entry: limit)
    int   f0c;                       // +0x0c (cache entry: kind)
    char  p10[0x20 - 0x10];
    unsigned id;                     // +0x20
    char  p24[0x34 - 0x24];
    Vec3  normal;                    // +0x34
    bool  flag;                      // +0x40
    char  p41[3];
    float dist;                      // +0x44
    char  p48[0xf0 - 0x48];
    float w;                         // +0xf0
    Vec3  pos;                       // +0xf4

    Hit_s00cb_2480();                           // 0x00af4da0
    ~Hit_s00cb_2480();                          // 0x00c2e4e0 (just `ret`)
};
struct TraceCtx {                    // context handed to SweepTick
    void* self;
    Vec3  pos;
    Vec3  goal;
    float radius;
};
float __cdecl SweepTick(TraceCtx* ctx, const Vec3* origin, const Vec3* dir, float t, Hit_s00cb_2480* out);   // 0x00cb1270
typedef float (__cdecl* CastFn)(TraceCtx*, const Vec3*, const Vec3*, float, Hit_s00cb_2480*);
int __cdecl TracePlanetPath(TraceCtx* ctx, const Vec3* initDir, float p3, CastFn cast, const Vec3* start,
                            const Vec3* end, Hit_s00cb_2480* out, int maxHits, unsigned* state, float* outLen,
                            const Hit_s00cb_2480* prev, int extra);                 // 0x00af6bf0
Hit_s00cb_2480* __cdecl GetTraceCache(void* creature);                              // 0x00cb1210
extern const Vec3 kZeroVector;                                           // 0x0169a37c
#define PAD(n) virtual void pad##n();
struct SpatialPart {                 // sub-object at creature + 0x34
    PAD(0) PAD(1) PAD(2) PAD(3) PAD(4) PAD(5) PAD(6) PAD(7) PAD(8) PAD(9) PAD(10)
    virtual const Vec3* GetPosition();            // +0x2c
    PAD(12) PAD(13) PAD(14) PAD(15) PAD(16) PAD(17) PAD(18) PAD(19) PAD(20) PAD(21) PAD(22) PAD(23)
    PAD(24) PAD(25) PAD(26) PAD(27) PAD(28)
    virtual float GetRadius();                    // +0x74
    const Vec3* GetVelocity();                    // 0x00d20610
};
struct Creature_s00cb_2480 {
    char pad0[0x34];
    // SpatialPart lives at +0x34 (accessed through a cast below)
    char pad34[0x2a4 - 0x34];
    unsigned flags;                               // +0x2a4
    bool  IsOnSurface(const Vec3* p);             // 0x00c9e940
    float SurfaceHeight(const Vec3* p);           // 0x00c9ffd0
};
class cCacheObjectResult {
public:
virtual void p00();
virtual void p04();
virtual void p08();
virtual void p0c();
virtual void p10();
virtual void p14();
virtual void p18();
virtual void p1c();
virtual void p20();
virtual void p24();
virtual void p28();
    virtual const Vec3* GetPosition();                 // +0x2c
};
class cCacheObject {
public:
virtual void p00();
virtual void p04();
virtual void p08();
    virtual cCacheObjectResult* Resolve(unsigned int type);   // +0x0c
};
struct CacheHit {                      // 0x100-byte cached trace hit
    char     pad00[4];
    int      f04;                      // +0x04
    float    f08;                      // +0x08
    int      f0c;                      // +0x0c
    char     pad10[0x20 - 0x10];
    unsigned id;                       // +0x20
    char     pad24[4];
    Vec3     pos28;                    // +0x28
    char     pad34[0x40 - 0x34];
    bool     flag;                     // +0x40
    char     pad41[0x100 - 0x41];
};
struct TraceCache_s00cb_2480 {
    CacheHit      hits[8];             // +0x000
    cCacheObject* objects[8];          // +0x800
};
// ---- items of slice s00cb2480 end

// @ 0x00cb1110
InsertResult Ht::DoInsertValue(const Value& value, bool trueType)
{
    const unsigned c = value.mKey;
    unsigned n = c % mBucketCount;
    Node* const pNode = DoFindNode(mpBuckets[n], value.mKey);
    InsertResult result;
    if (pNode == 0) {
        const RehashResult bRehash = mRehashPolicy.GetRehashRequired(mBucketCount, mSize, 1);
        Node* const pNodeNew = DoAllocateNode(value);
        if (bRehash.first) {
            n = c % bRehash.second;
            DoRehash(bRehash.second);
        }
        pNodeNew->mpNext = mpBuckets[n];
        mpBuckets[n] = pNodeNew;
        ++mSize;
        result.mpNode = pNodeNew;
        result.mInserted = true;
        result.mpBucket = mpBuckets + n;
        return result;
    }
    result.mpNode = pNode;
    result.mInserted = false;
    result.mpBucket = mpBuckets + n;
    return result;
}

// @ 0x00cb1270
float __cdecl SweepTick(Ctx* ctx, const Vec3* origin, const Vec3* dir, float t, SweepOut* out)
{
    out->count20 = 0;
    void* self = ctx->self;
    if (t < 1.5258789e-05f)
        return t;

    Loco* loco = (Loco*)((char*)self + 0x34);
    loco->GetVelocity();
    float R = ctx->radius;
    Vec3 end0;
    end0.x = dir->x * t + origin->x;
    end0.y = t * dir->y + origin->y;
    end0.z = t * dir->z + origin->z;
    float t2 = t * t;
    float speed = ((FnF0)VT(loco)[50])(loco);
    unsigned flags = AT(unsigned, AT(void*, self, 0xaf0), 0x5fc);
    Vec3 vel;
    vel.x = dir->x * speed;
    vel.y = speed * dir->y;
    vel.z = speed * dir->z;

    static HitVec sHits;
    static int sCount;
    static Vec3 sZero;

    sHits.erase(sHits.mpBegin, sHits.mpEnd);
    Filter filter;
    filter.a = 0; filter.b = 0; filter.c = 0; filter.d = 0; filter.e = 0;
    filter.f = 0; filter.g = 2;
    void* world = GonzagoModelWorld();
    Vec3 seg;
    if (t > 100.0f) {
        seg.x = dir->x * 100.0f + origin->x;
        seg.y = dir->y * 100.0f + origin->y;
        seg.z = dir->z * 100.0f + origin->z;
    } else {
        seg = end0;
    }
    Vec3 seg2 = seg;
    ((FnWorld)VT(world)[12])(world, origin, &seg2, &sHits, &filter, R);

    sCount = (int)(sHits.mpEnd - sHits.mpBegin);

    unsigned i = 0;
    if (sCount != 0) {
        do {
            void* ent = sHits.mpBegin[i].first;
            void* comp;
            Obj* obj;
            float scale, rad;
            bool noB71, flag13, moving, flagB;
            Vec3 hitVec, velV, hp, tmp1, tmp2, tmp3, acc;
            const Vec3* pos;
            unsigned type;
            void* other;
            float r1d, rr;

            if (!((AT(unsigned, ent, 4) >> 14) & 1)) goto next;
            if (AT(void*, ent, 0x64) == 0) goto next;
            comp = AT(void*, ent, 0x64);
            if (comp == 0) goto next;
            obj = (Obj*)((FnPtr1)VT(comp)[3])(comp, 0x1186577);
            if (obj == 0 || AT(char, obj, 0x70) == 0) goto next;
            if (AT(char, obj, 0x75) == 0) goto next;
            if (AT(unsigned, obj, 0x50) & 0x190) goto next;

            scale = 1.0f;
            noB71 = AT(char, obj, 0x71) == 0;
            flag13 = false;
            rad = 0.0f;
            pos = ((FnVec0)VT(obj)[11])(obj);
            hitVec = sZero;
            other = ((FnPtr1)VT(obj)[46])(obj, 0x17f243b);
            type = ((FnU0)VT(other)[8])(other);
            r1d = 0.0f;
            rr = 0.0f;
            moving = false;
            flagB = false;

            switch (type) {
            case 0x18c431c:
            case 0x18c84a9:
            case 0x18c7c97:
            case 0x2a034cd:
            case 0x2c9cc91:
            case 0x2e72cae:
            case 0x74e0069:
            case 0x7b38ba7:
            case 0x52aa6122:
                goto next;

            case 0x18c6de8: {
                void* other2 = FUN_00ae6760(other);
                if (self == other2) goto next;
                if (FUN_0041dd30(ctx->sub, origin)) {
                    if (((Loco*)((char*)other2 + 0x34))->GetGoal()->mActive != 0) goto next;
                }
                if (!(0.0f < (pos->z - origin->z) * dir->z + (pos->y - origin->y) * dir->y +
                                 (pos->x - origin->x) * dir->x))
                    goto next;
                rad = ((FnF0)VT(obj)[29])(obj);
                rr = rad * 0.9f + R;
                scale = 0.9f;
                {
                    float ax = dir->x * t, ay = t * dir->y, az = t * dir->z;
                    float dx = origin->x - pos->x, dz = origin->z - pos->z, dy = origin->y - pos->y;
                    float b = dx * ax + dz * az + dy * ay;
                    float c = dz * dz + dy * dy + dx * dx - rr * rr;
                    float disc = b * b - c * t2;
                    if (!(c < 0.0f)) {
                        if (disc < 0.0f) goto next;
                        float s = (float)sqrt(disc);
                        if (0.0f > s - b) goto next;
                        if (-b - s > t2) goto next;
                    }
                }
                {
                    Loco* loco2 = (Loco*)((char*)other2 + 0x34);
                    Vec3* v = loco2->GetVelocity();
                    velV = *v;
                    r1d = FUN_00c297d0(origin, &vel, pos, &velV);
                    if (1.5258789e-05f >= r1d || r1d > 10.0f) goto next;
                    if (FUN_00c29880(origin, &vel, pos, &velV, r1d) > rr) goto next;
                    if (AT(void*, FUN_00cb1210(other2), 4) == self) goto next;
                    moving = (velV.z * velV.z + velV.y * velV.y) + velV.x * velV.x > 1.5258789e-05f;
                    flagB = false;
                    if (moving) {
                        if (Dot3(normalized_safe(&tmp1, &velV), dir) > 0.7f) {
                            flagB = true;
                            goto sweepA;
                        }
                        flagB = false;
                    }
                    {
                        Goal* g = loco2->GetGoal();
                        if (g->mActive != 0 && !loco2->IsNearGoal()) {
                            float sx = pos->x, sy = pos->y, sz = pos->z;
                            acc.x = g->target.x - sx;
                            acc.y = g->target.y - sy;
                            acc.z = g->target.z - sz;
                            unsigned n = g->Count();
                            unsigned m = n > 3 ? 3 : n;
                            for (unsigned k = 0; k < m; ++k) {
                                float* e = (float*)((char*)g->mpPoints + k * 0x3c);
                                acc.x = (e[0] - sx) + acc.x;
                                acc.y = (e[1] - sy) + acc.y;
                                acc.z = (e[2] - sz) + acc.z;
                            }
                            Vec3* nv = normalized_safe(&tmp2, &acc);
                            acc = *nv;
                            if (0.7f < (acc.z * dir->z + acc.y * dir->y) + acc.x * dir->x) {
                                if (!moving) {
                                    float sp = ((FnF0)VT(loco2)[50])(loco2);
                                    velV.x = acc.x * sp;
                                    velV.y = acc.y * sp;
                                    velV.z = acc.z * sp;
                                }
                                flagB = false;
                                goto sweepA;
                            }
                        }
                    }
                    goto postSweep;
                sweepA:
                    {
                        float fracs[2];
                        fracs[0] = 0.5f;
                        fracs[1] = 0.1f;
                        for (int k = 0; k < 2; ++k) {
                            float f = fracs[k];
                            Vec3 sc;
                            sc.x = vel.x * f;
                            sc.y = vel.y * f;
                            sc.z = vel.z * f;
                            float rl = FUN_00c297d0(origin, &sc, pos, &velV);
                            if (1.5258789e-05f >= rl || rl > 10.0f) {
                                out->hitObj = other;
                                out->hitFrac = f;
                                out->hitFlag = !flagB;
                                goto next;
                            }
                            if (FUN_00c29880(origin, &sc, pos, &velV, rl) > rr) {
                                out->hitObj = other;
                                out->hitFrac = f;
                                out->hitFlag = !flagB;
                                goto next;
                            }
                        }
                    }
                postSweep:
                    {
                        Vec3* nv = normalized_safe(&tmp3, &velV);
                        hp.x = nv->x * r1d + pos->x;
                        hp.y = nv->y * r1d + pos->y;
                        hp.z = nv->z * r1d + pos->z;
                        pos = &hp;
                        hitVec = velV;
                    }
                }
                break;
            }

            case 0x18c88e4: {
                void* o = FUN_00ac80d0(other, 0x18c88e4);
                unsigned k = AT(unsigned, o, 0x228);
                if (k != 0x2ae5ba7 && k != 0x5d97f762) goto next;
                flag13 = true;
                break;
            }
            case 0x18c8f0c:
            case 0x18ea1eb:
            case 0x18ea2cc:
            case 0x18eb106:
            case 0x1a56aba:
            case 0x55cf865:
            case 0x70703b3:
                flag13 = true;
                break;
            case 0x18eb45e:
            case 0x18eb4b7: {
                Creature* c = (Creature*)FUN_00f19200(other);
                if (AT(char, c, 0xb5e) != 0 && !c->Check()) goto next;
                if (flags & 0x1000) goto next;
                if (flags & 0x4400) {
                    int a = ((FnI0)VT(c)[19])(c);
                    int b = ((FnI0)VT(self)[19])(self);
                    if (b != a) goto next;
                }
                flag13 = true;
                break;
            }
            case 0x1e4daae: {
                float dz = end0.z - pos->z, dy = end0.y - pos->y, dx = end0.x - pos->x;
                if (1.5258789e-05f > dz * dz + dy * dy + dx * dx) goto next;
                flag13 = true;
                break;
            }
            case 0x2a8fb3f:
                if (noB71) {
                    if (0.3f >= ((FnF0)VT(obj)[29])(obj)) goto next;
                    scale = 0.5f;
                }
                break;
            case 0x3a2511e:
                if (noB71) goto next;
                flag13 = true;
                break;
            case 0x629bafe: {
                void* o = FUN_00ac80d0(other, 0x629bafe);
                if (((Flag10c*)AT(void*, o, 0x10c))->Check() == 0) {
                    void* sub = (char*)o + 0x34;
                    float r = ((FnF0)VT(sub)[29])(sub);
                    const Vec3* sp = ((FnVec0)VT(sub)[11])(sub);
                    float dz = end0.z - sp->z, dy = end0.y - sp->y, dx = end0.x - sp->x;
                    if (r * r > dz * dz + dy * dy + dx * dx) goto next;
                }
                break;
            }
            default:
                break;
            }

            // common tail
            out->type = type;
            if (rad == 0.0f)
                rad = ((FnF0)VT(obj)[29])(obj);
            rad = rad * scale;
            {
                float rr2 = rad + R;
                bool ok;
                if (flag13 && !noB71) {
                    Transform xf;
                    obj->LocalToWorldTransform(&xf);
                    void* a = ((FnP0)VT(obj)[44])(obj);
                    void* b = ((FnP1)VT(obj)[43])(obj, a);
                    Mesh* mesh = ((MeshRef*)FUN_00b3d3c0(b))->GetMesh();
                    if (mesh == 0) goto next;
                    if ((unsigned)(mesh->mpEnd - mesh->mpBegin) < 3) goto next;
                    ok = FUN_00af5400(out, other, origin, pos, &end0, dir, &t, 1.0f, &xf, mesh->data40,
                                      rad, mesh->mpBegin, (unsigned)(mesh->mpEnd - mesh->mpBegin), R, 0, out);
                } else {
                    ok = FUN_00af17f0(out, other, origin, pos, dir, &t, 1.0f, rr2, noB71, out);
                }
                if (!ok) goto next;
            }
            out->hitVec = hitVec;
            if (1.5258789e-05f > t) {
                t = 0.0f;
                break;
            }
            t2 = t * t;
            end0.x = dir->x * t + origin->x;
            end0.y = t * dir->y + origin->y;
            end0.z = t * dir->z + origin->z;
        next:
            ++i;
        } while (i < (unsigned)sCount);
    }

    int mode = AT(int, self, 0xb1c);
    if (mode == 0) {
        if (t > 0.25f)
            FUN_00af7c60(origin, dir, R, 1.0f, 1, 1, out, &t);
        if (AT(char, self, 0xab) != 0) {
            float* v = (float*)((FnP0)VT(loco)[26])(loco);
            if (t > 0.25f) {
                FUN_00af3e50(origin, dir, R, 2.0f, 45.0f, (v[5] - v[2]) + 10.0f, out, &t, 0);
                return t;
            }
        }
    } else if (mode == 1) {
        FUN_00af4870(origin, dir, R, 2.0f, out, &t);
    }
    return t;
}

// @ 0x00cb2480
bool __cdecl IsPathAheadClear(Creature_s00cb_2480* self, WaypointPath* path, const Vec3* fallbackDir, float* pScale,
                              int* pKind)
{
    TraceCache_s00cb_2480* cache = (TraceCache_s00cb_2480*)GetTraceCache((void*)self);
    if (cache->hits[0].f04 != 0)
        return true;

    for (int i = 0; i < 8; i++) {
        CacheHit& hit = cache->hits[i];
        if (hit.id == 0)
            continue;
        cCacheObject* object = cache->objects[i];
        if (object == 0)
            continue;
        if (!hit.flag)
            continue;
        cCacheObjectResult* result = object->Resolve(0x1186577);
        const Vec3* p = result->GetPosition();
        float dx = p->x - hit.pos28.x;
        float dy = p->y - hit.pos28.y;
        float dz = p->z - hit.pos28.z;
        if ((dz * dz + dy * dy) + dx * dx > 0.1f)
            return true;
    }

    unsigned state = 0;
    float outLen = 0.0f;
    Hit_s00cb_2480 hits[8];

    SpatialPart* loco = (SpatialPart*)((char*)self + 0x34);
    const Vec3* pos = loco->GetPosition();
    const Vec3* vel = loco->GetVelocity();
    Vec3 velDir;
    const Vec3* dirp;
    if (vel->x != kZeroVector.x || vel->y != kZeroVector.y || vel->z != kZeroVector.z) {
        const Vec3* v = loco->GetVelocity();
        float k = 1.0f / sqrtf((v->x * v->x + v->y * v->y) + v->z * v->z + 1e-08f);
        velDir.x = v->x * k;
        velDir.y = v->y * k;
        velDir.z = v->z * k;
        dirp = &velDir;
    } else {
        dirp = fallbackDir;
    }

    Vec3 initDir;
    initDir.x = dirp->x;
    initDir.y = dirp->y;
    initDir.z = dirp->z;
    TraceCtx ctx;
    ctx.radius = loco->GetRadius();
    ctx.self = (void*)self;
    ctx.pos.x = pos->x; ctx.pos.y = pos->y; ctx.pos.z = pos->z;
    ctx.goal.x = path->cur.pos.x; ctx.goal.y = path->cur.pos.y; ctx.goal.z = path->cur.pos.z;

    int n = TracePlanetPath(&ctx, &initDir, 0.25f, (CastFn)SweepTick, pos, &path->cur.pos, hits, 1,
                            &state, &outLen, (const Hit_s00cb_2480*)cache, 1);

    bool clear = true;
    if (n == 1 && state == 3) {
        if (hits[0].f04 != 0 && *pScale > hits[0].f08) {
            *pScale = hits[0].f08;
            *pKind = hits[0].f0c;
        }
        self->flags &= 0xfffffff4;
        clear = false;
    }
    return clear;
}
