// Slice s00cb2480 -- 0x00cb2770 (2047 bytes, cdecl, 7 args): creature path-ahead update.
//
// Traces a few steps ahead of the creature along the planet surface toward the first waypoint of
// its path (TracePlanetPath with the sweep test SweepTick as the cast callback), then reconciles
// the creature's waypoint path with what the trace found:
//   * path (arg 3, eastl::vector<Waypoint> with the "current" waypoint copy at +0x14 and mode
//     flags at +0x70) first drops every flagged waypoint (remove_if + erase) and remembers its
//     first waypoint as `cur`.
//   * the trace direction is the normalized velocity (or `fallbackDir` when still).
//   * trace result state < 3 only updates creature flags (+0x2a4) and returns the state;
//     otherwise *pScale is reset to 1.0, possibly lowered to 0.5 when the first hit is a nearby
//     blocker, and lowered further by the cached per-creature trace record.
//   * hits that lie on the surface become new waypoints (flag |= 1, weight 0.2) in a local
//     fixed vector; when the path ended up different, the new waypoints are inserted into `path`,
//     the distance to the path's current waypoint is stored in *pDist, and a one-waypoint path
//     that is very close is consumed.
// Returns the trace state (0..5).
//
// Flags: /O2 /Ob2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (no /EHsc: the local Hit[8] is built with
// plain loops).
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
    Waypoint(const Vec3& p) : pos(p), weight(1.0f), kind(0) { flags = 0; }
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
    void      InsertRange(Waypoint* where, Waypoint* first, Waypoint* last, float f);   // 0x00b96360
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

struct TraceCtx {                    // context handed to SweepTick
    void* self;
    Vec3  pos;
    Vec3  goal;
    float radius;
};

float __cdecl SweepTick(TraceCtx* ctx, const Vec3* origin, const Vec3* dir, float t, Hit* out);   // 0x00cb1270
typedef float (__cdecl* CastFn)(TraceCtx*, const Vec3*, const Vec3*, float, Hit*);

int __cdecl TracePlanetPath(TraceCtx* ctx, const Vec3* initDir, float p3, CastFn cast, const Vec3* start,
                            const Vec3* end, Hit* out, int maxHits, unsigned* state, float* outLen,
                            const Hit* prev, int extra);                 // 0x00af6bf0

Hit* __cdecl GetTraceCache(void* creature);                              // 0x00cb1210
void __cdecl SaveHits(const Hit* src, Hit* dst);                         // 0x00cb01e0
void __cdecl FUN_00cadb50(Hit* cache);                                   // 0x00cadb50
Vec3* __cdecl SnapToSurface(Vec3* out, const Vec3* p, void* creature);   // 0x00cadb90
float __cdecl Dot3(const Vec3* a, const Vec3* b);                        // 0x00455cc0
void* __cdecl PlanetModel();                                             // 0x00b3d350

extern const Vec3 kZeroVector;                                           // 0x0169a37c

// ---- the creature -----------------------------------------------------------------------------
#define PAD(n) virtual void pad##n();

struct SpatialPart {                 // sub-object at creature + 0x34
    PAD(0) PAD(1) PAD(2) PAD(3) PAD(4) PAD(5) PAD(6) PAD(7) PAD(8) PAD(9) PAD(10)
    virtual const Vec3* GetPosition();            // +0x2c
    PAD(12) PAD(13) PAD(14) PAD(15) PAD(16) PAD(17) PAD(18) PAD(19) PAD(20) PAD(21) PAD(22) PAD(23)
    PAD(24) PAD(25) PAD(26) PAD(27) PAD(28)
    virtual float GetRadius();                    // +0x74
    const Vec3* GetVelocity();                    // 0x00d20610
};

struct Creature {
    char pad0[0x34];
    // SpatialPart lives at +0x34 (accessed through a cast below)
    char pad34[0x2a4 - 0x34];
    unsigned flags;                               // +0x2a4
    bool  IsOnSurface(const Vec3* p);             // 0x00c9e940
    float SurfaceHeight(const Vec3* p);           // 0x00c9ffd0
};

// @ 0x00cb2770
unsigned __cdecl UpdatePathAhead(Creature* self, const Vec3* fallbackDir, WaypointPath* path, char* pBlocked,
                                 float* pDist, float* pScale, int* pKind)
{
    unsigned state = 0;
    float outLen = 0.0f;
    Hit hits[8];

    Hit* cache = GetTraceCache(self);
    Waypoint cur(path->cur);
    SpatialPart* loco = (SpatialPart*)((char*)self + 0x34);
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
    const Vec3* dirp;
    if (vel->x != kZeroVector.x || vel->y != kZeroVector.y || vel->z != kZeroVector.z) {
        const Vec3* v = loco->GetVelocity();
        float k = 1.0f / sqrtf((v->x * v->x + v->y * v->y) + v->z * v->z + 1e-08f);
        velDir.x = v->x * k;
        velDir.y = k * v->y;
        velDir.z = k * v->z;
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
    ctx.self = self;
    ctx.pos.x = pos->x; ctx.pos.y = pos->y; ctx.pos.z = pos->z;
    ctx.goal.x = cur.pos.x; ctx.goal.y = cur.pos.y; ctx.goal.z = cur.pos.z;

    int n = TracePlanetPath(&ctx, &initDir, 0.25f, SweepTick, pos, &cur.pos, hits, 8, &state, &outLen,
                            cache, 1);

    if (state < 3) {
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
    } else {
        *pScale = 1.0f;
        self->flags &= 0xffffffe4;
        if (state != 5 && hits[0].id != 0 &&
            (hits[0].normal.x != kZeroVector.x || hits[0].normal.y != kZeroVector.y ||
             hits[0].normal.z != kZeroVector.z)) {
            bool lower = true;
            if ((unsigned)self <= hits[0].id) {
                if (Dot3(&hits[0].normal, loco->GetVelocity()) <= 0.0f)
                    lower = false;
            }
            if (lower && *pScale > 0.5f) {
                *pScale = 0.5f;
                *pKind = 2;
            }
        }

        SaveHits(hits, cache);
        LocalWaypoints vec;
        vec.mpBegin = (Waypoint*)vec.storage;
        vec.mpEnd = vec.mpBegin;
        vec.mpCapacity = (Waypoint*)(vec.storage + 8 * 15);
        vec.mAlloc = 0;
        vec.reserve(n);
        if (cache->f04 != 0 && cache->f08 < *pScale) {
            *pScale = cache->f08;
            *pKind = cache->f0c;
        }

        PlanetModel();
        for (int i = 0; i < n; i++) {
            const Vec3* hp = &hits[i].pos;
            float dz = hp->z - cur.pos.z;
            float dy = hp->y - cur.pos.y;
            float dx = hp->x - cur.pos.x;
            if ((dz * dz + dy * dy) + dx * dx < 1.5258789e-05f)
                break;
            if (!self->IsOnSurface(hp))
                break;
            Vec3 tmp;
            Vec3* sp = SnapToSurface(&tmp, hp, self);
            Waypoint w(*sp);
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
            if (!(path->mpBegin != path->mpEnd && vec.mpBegin != vec.mpEnd)) {
                if (self->IsOnSurface(&cur.pos)) {
                    float h = self->SurfaceHeight(&cur.pos);
                    float k = 1.0f / sqrtf((cur.pos.z * cur.pos.z + cur.pos.y * cur.pos.y) +
                                           cur.pos.x * cur.pos.x + 1e-08f);
                    Vec3 s;
                    s.x = (k * cur.pos.x) * h;
                    s.y = (cur.pos.y * k) * h;
                    s.z = (cur.pos.z * k) * h;
                    Waypoint w(s);
                    vec.push_back(w);
                }
            }
            if (vec.mpBegin != vec.mpEnd) {
                path->InsertRange(path->mpBegin, vec.mpBegin, vec.mpEnd, outLen);
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
            }
            float ex = pos->x - path->cur.pos.x;
            float ey = pos->y - path->cur.pos.y;
            float ez = pos->z - path->cur.pos.z;
            *pDist = sqrtf(ey * ey + (ex * ex + ez * ez));
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
    return state;
}
