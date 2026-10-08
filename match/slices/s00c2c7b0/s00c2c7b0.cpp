// Slice s00c2c7b0 -- 0x00c2cac0 (1887 bytes, cdecl, 7 args): creature path-ahead update.
//
// Traces a few steps ahead of a locomotive creature along the planet surface toward the first
// waypoint of its path (TracePlanetPath with CreatureObstacleSweep, slice s00c2b170, as the cast
// callback), then reconciles the creature's waypoint path with what the trace found. This is the
// creature-class twin of UpdatePathAhead (slice s00cb2480): creature flags live at +0x330 and the
// locomotion sub-object at +0xc0.
//   * path (arg 3: eastl::vector<Waypoint> with the "current" waypoint copy at +0x14 and mode
//     flags at +0x70) first drops every flagged waypoint (remove_if + erase) and copies its first
//     waypoint into the local `cur`.
//   * trace direction is the normalized velocity (or `fallbackDir` when still).
//   * trace state 4 sets flag 0x20 and, like every state >= 3, lowers *pScale to 1.0 / possibly
//     0.5 on a nearby blocker and turns the hits into new waypoints; states < 3 only update the
//     creature flags.
// Returns the trace state (0..5).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (neighbouring slices s00c2a190/s00c2b170); no EH.
#include "types.h"
#include <new>

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline float sqrtf(float x) { return (float)sqrt((double)x); }

struct Vec3 { float x, y, z; };

// ---- waypoint (0x3c bytes) and vectors ------------------------------------------------------
struct Waypoint {
    Vec3  pos;        // 0x00
    float weight;     // 0x0c
    int   kind;       // 0x10
    Vec3  v14, v20, v2c;
    unsigned char flags;   // 0x38 (bit 0 = "tracked" waypoint)
    char  pad39[3];
    Waypoint(const Vec3& p) : weight(1.0f), kind(0) { pos.x = p.x; pos.y = p.y; pos.z = p.z; flags = 0; }
    Waypoint(const Waypoint& o);                        // 0x00ac1ff0
};

typedef char WaypointSizeCheck[sizeof(Waypoint) == 0x3c ? 1 : -1];

bool __cdecl IsFlaggedWaypoint(const Waypoint& w);      // 0x00c27ff0
Waypoint* __cdecl RemoveCopyIf(Waypoint* first, Waypoint* last, Waypoint* out,
                               bool (__cdecl* pred)(const Waypoint&));   // 0x00c28000

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
    void      InsertRange(Waypoint* where, Waypoint* first, Waypoint* last, uint32_t continent);   // 0x00b96360
    void      EraseOne(Waypoint* where);                                  // 0x00b47520
};

struct LocalWaypoints {              // fixed_vector<Waypoint, 8>
    Waypoint* mpBegin;
    Waypoint* mpEnd;
    Waypoint* mpCapacity;
    int       pad0c;
    int       pad10;
    int       mAlloc;
    uint32_t  storage[8 * 15];
    void reserve(unsigned n);                                            // 0x00c199e0
    void DoInsertValue(Waypoint* where, const Waypoint& v);              // 0x00ac45e0
    void push_back(const Waypoint& v)
    {
        if (mpEnd < mpCapacity) {
            Waypoint* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                new (p) Waypoint(v);
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};

extern void __cdecl operator_delete__(void* p);                          // 0x00f47380

// ---- the trace --------------------------------------------------------------------------------
// 0x100-byte trace result record (see slice s00af6bf0)
struct Hit {
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

    Hit();                           // 0x00af4da0
    ~Hit();                          // 0x00c2e4e0 (just `ret`)
};

struct CreatureSweepCtx {            // context handed to CreatureObstacleSweep (s00c2b170)
    void* self;
    Vec3  pos;
    Vec3  goal;
    float radius;
    bool  ignoreObjects;             // +0x20
};

float __cdecl CreatureObstacleSweep(CreatureSweepCtx* ctx, const Vec3* origin, const Vec3* dir, float t,
                                    Hit* out);   // 0x00c2b170
typedef float (__cdecl* CastFn)(CreatureSweepCtx*, const Vec3*, const Vec3*, float, Hit*);

int __cdecl TracePlanetPath(CreatureSweepCtx* ctx, const Vec3* initDir, float p3, CastFn cast,
                            const Vec3* start, const Vec3* end, Hit* out, int maxHits, unsigned* state,
                            float* outLen, const Hit* prev, int extra);                 // 0x00af6bf0

struct Creature;
Hit* __cdecl GetTraceCache(Creature* creature);                          // 0x00c2b110
void __cdecl SaveHits(const Hit* src, Hit* dst);                         // 0x00cb01e0
void __cdecl FUN_00cadb50(Hit* cache);                                   // 0x00cadb50
void __cdecl SnapToGround(Creature* creature, Vec3* pos, uint32_t* continent);   // 0x00c28290
float __cdecl Dot3(const Vec3* a, const Vec3* b);                        // 0x00455cc0
struct PlanetModelT { Vec3* Project(Vec3* out, const Vec3* in); };       // 0x00b816f0 (ret 8)
PlanetModelT* __cdecl PlanetModel();                                     // 0x00b3d350

extern const Vec3 kZeroVector;                                           // 0x0168dd78

// ---- the creature -----------------------------------------------------------------------------
#define PAD(n) virtual void pad##n();

struct LocoPart {                    // SP::cLocomotiveObject, sub-object at creature + 0xc0
    PAD(0) PAD(1) PAD(2) PAD(3) PAD(4) PAD(5) PAD(6) PAD(7) PAD(8) PAD(9) PAD(10)
    virtual const Vec3* GetPosition();            // +0x2c
    PAD(12) PAD(13) PAD(14) PAD(15) PAD(16) PAD(17) PAD(18) PAD(19) PAD(20) PAD(21)
    virtual bool IsFlagSet();                     // +0x58
    PAD(23) PAD(24) PAD(25) PAD(26) PAD(27) PAD(28)
    virtual float GetRadius();                    // +0x74
    const Vec3* GetVelocity();                    // 0x00d20610
};

struct Creature {
    char pad0[0x330];
    unsigned flags;                               // +0x330
};

// @ 0x00c2cac0
unsigned __cdecl UpdatePathAhead(Creature* self, const Vec3* fallbackDir, WaypointPath* path, char* pBlocked,
                                 float* pDist, float* pScale, int* pKind)
{
    unsigned state = 0;
    float outLen = 0.0f;
    Hit hits[8];

    Hit* cache = GetTraceCache(self);
    Waypoint cur(path->cur);
    LocoPart* loco = (LocoPart*)((char*)self + 0xc0);
    const Vec3* pos = loco->GetPosition();

    // drop flagged waypoints
    Waypoint* first = path->mpBegin;
    Waypoint* last = path->mpEnd;
    if (first != last) {
        Waypoint* it = first;
        while (it != last) {
            if (it->flags & 1) {
                if (it != last)
                    it = RemoveCopyIf(it + 1, last, it, IsFlaggedWaypoint);
                break;
            }
            it = it + 1;
        }
        if (it == path->mpEnd) {
            if (cur.flags & 1)
                cur = *path->mpBegin;
        } else {
            path->erase(it, path->mpEnd);
            cur = *path->mpBegin;
        }
    }

    // trace direction
    const Vec3* vel = loco->GetVelocity();
    Vec3 velDir;
    if (vel->x != kZeroVector.x || vel->y != kZeroVector.y || vel->z != kZeroVector.z) {
        const Vec3* v = loco->GetVelocity();
        float k = 1.0f / sqrtf((v->x * v->x + v->y * v->y) + v->z * v->z + 1e-08f);
        velDir.x = v->x * k;
        velDir.y = k * v->y;
        velDir.z = k * v->z;
        fallbackDir = &velDir;
    }

    Vec3 initDir;
    initDir.x = fallbackDir->x;
    initDir.y = fallbackDir->y;
    initDir.z = fallbackDir->z;

    CreatureSweepCtx ctx;
    float radius = loco->GetRadius();
    bool ign = loco->IsFlagSet();
    ctx.self = self;
    ctx.pos.x = pos->x; ctx.pos.y = pos->y; ctx.pos.z = pos->z;
    ctx.radius = radius;
    ctx.ignoreObjects = ign;
    ctx.goal.x = cur.pos.x; ctx.goal.y = cur.pos.y; ctx.goal.z = cur.pos.z;

    int n = TracePlanetPath(&ctx, &initDir, 0.25f, CreatureObstacleSweep, pos, &cur.pos, hits, 8, &state,
                            &outLen, cache, 1);

    if (state == 4) {
        self->flags |= 0x20;
    } else {
        self->flags &= 0xffffffdf;
        if (state < 3)
            goto small;
    }

    {
    *pScale = 1.0f;
    self->flags &= 0xffffffe4;
    if (state != 5 && hits[0].id != 0 &&
        (hits[0].normal.x != kZeroVector.x || hits[0].normal.y != kZeroVector.y ||
         hits[0].normal.z != kZeroVector.z)) {
        bool lower = true;
        if (hits[0].id >= (unsigned)self)
            lower = Dot3(&hits[0].normal, loco->GetVelocity()) > 0.0f;
        if (lower && *pScale > 0.5f) {
            *pScale = 0.5f;
            *pKind = 2;
        }
    }

    SaveHits(hits, cache);
    LocalWaypoints vec;
    vec.mpBegin = (Waypoint*)vec.storage;
    vec.mAlloc = 0;
    vec.mpEnd = vec.mpBegin;
    vec.mpCapacity = (Waypoint*)(vec.storage + 8 * 15);
    vec.reserve(n);
    float limit = cache->f08;
    int kind = cache->f0c;
    if (cache->f04 != 0 && limit < *pScale) {
        *pScale = limit;
        *pKind = kind;
    }

    PlanetModelT* planet = PlanetModel();
    uint32_t continent;
    for (int i = 0; i < n; i++) {
        Vec3 p;
        p.x = hits[i].pos.x;
        p.y = hits[i].pos.y;
        p.z = hits[i].pos.z;
        SnapToGround(self, &p, &continent);
        float dz = p.z - cur.pos.z;
        float dy = p.y - cur.pos.y;
        float dx = p.x - cur.pos.x;
        if ((dz * dz + dy * dy) + dx * dx < 0.1f)
            break;
        Vec3 scratch;
        const Vec3* proj = planet->Project(&scratch, &p);
        Waypoint w(*proj);
        vec.push_back(w);
        vec.mpEnd[-1].flags |= 1;
        vec.mpEnd[-1].weight = 0.2f;
    }

    bool skipAll = false;
    if (path->mpBegin == path->mpEnd) {
        if (vec.mpBegin == vec.mpEnd && path->cur.pos.x == cur.pos.x && path->cur.pos.y == cur.pos.y &&
            path->cur.pos.z == cur.pos.z)
            skipAll = true;
    }
    if (!skipAll) {
        if (!(path->mpBegin != path->mpEnd && vec.mpBegin != vec.mpEnd))
            vec.push_back(cur);
        path->InsertRange(path->mpBegin, vec.mpBegin, vec.mpEnd, continent);
        Waypoint* dst = path->mpBegin;
        Waypoint* end = path->mpEnd;
        Waypoint* src = dst + 1;
        path->cur = *dst;
        if (src < end) {
            do {
                *dst = *src;
                src = src + 1;
                dst = dst + 1;
            } while (src != end);
        }
        path->mpEnd = path->mpEnd - 1;
        float ex = pos->x - path->cur.pos.x;
        float ey = pos->y - path->cur.pos.y;
        float ez = pos->z - path->cur.pos.z;
        *pDist = sqrtf((ez * ez + ey * ey) + ex * ex);
        *pBlocked = 0;
        if (state == 5 && *pDist <= 0.45f) {
            Waypoint* b = path->mpBegin;
            if ((int)(path->mpEnd - b) == 1) {
                path->cur = *b;
                path->EraseOne(b);
                if (!(path->mode & 2))
                    self->flags |= 1;
            }
        }
    }
    if (vec.mpBegin && ((int*)vec.mpBegin)[-1] != 0)
        operator_delete__(vec.mpBegin);
    }
    goto done;
small:
    if (path->mode & 2) {
        self->flags &= 0xffffffe4;
    } else {
        FUN_00cadb50(GetTraceCache(self));
        switch (state) {
        case 0:
            self->flags |= 8;
            break;
        case 1:
            self->flags = 0;
            break;
        case 2:
            if (hits[0].flag)
                self->flags |= 2;
            break;
        }
    }
done:
    return state;
}
