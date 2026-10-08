// Slice s00da3b90 -- SOCIAL_RESPOND activation step (0x00da3b90, 2157 bytes).
//
// One step of a "respond to a social partner" behavior: the owner (mOwner) and a partner
// (mPartner) both stand on the planet. If the "keep away" flag (0x20) is set, the partner is
// nudged toward a point on the line from the owner to the creature, and the activation is
// aborted (-1). Otherwise, unless creature `c` already is the registered target in slot
// `slot`, three candidate stand points are built around the owner (the direction toward the
// partner rotated about the owner's up axis by two fixed angles, and its opposite), projected
// onto the planet, sorted by squared distance to the creature, and handed to
// MoveToTarget; if nothing was chosen the creature is walked toward the owner when close.
// Module flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
    Vec3& operator=(const Vec3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

struct Quat {
    float x, y, z, w;
    Quat() {}
    Quat(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    Quat(const Quat& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
};

Vec3 QuatRotate(const Vec3& v, const Quat& q);   // 0x0059aed0

extern const float kAngleA;   // 0x01593470 (pi/4)
extern const float kAngleB;   // 0x01593474 (pi/2)
extern const float kAngleC;   // 0x01593478 (pi)

// Rotation of `angle` radians about the unit vector `axis`.
inline Quat AxisAngle(const Vec3& axis, float angle)
{
    float h = angle * 0.5f;
    float s = sinf(h);
    float c = cosf(h);
    return Quat(axis.x * s, axis.y * s, axis.z * s, c);
}

// Locomotion sub-object at creature + 0xc0 (has its own vtable).
struct Loco {
    PV8 PV2 PV                       // slots 0..10
    virtual const Vec3* GetPosition();   // slot 11 (+0x2c)
    PV8 PV8 PV                       // slots 12..28
    virtual float GetRadius();           // slot 29 (+0x74)
    PV8 PV8 PV8 PV4 PV               // slots 30..58
    virtual void Stop();                 // slot 59 (+0xec)
};

struct Vec3F { Vec3 v; };

struct Obj {
    virtual int pv_0();
    virtual int Release();
};

struct Creature;
struct Planet {
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* p);   // 0x00b815a0
};
Planet* __cdecl PlanetModel();                                    // 0x00b3d350

struct Creature {
    char pad00[0xc0];
    Loco loco;                                                     // +0xc0
    void MoveToPointAtSpeed(int mode, const Vec3* p, float speed, float f);   // 0x00c1c1d0
};

// A candidate stand point (32 bytes).
struct Cand {
    int kind;
    Vec3 dir;
    Vec3 pos;
    float dist2;
};

// fixed_vector<Cand, 3> with an overflow allocator.
struct CandVec {
    Cand* mpBegin;
    Cand* mpEnd;
    Cand* mpCapacity;
    int mAlloc;
    Cand* mpPool;
    void Resize(unsigned n);                                       // 0x00da1db0
};
void __cdecl SortCands(Cand* first, Cand* last, bool (__cdecl* less)(const Cand*, const Cand*));   // 0x00da1e00
// Comparator passed to the sort (the original is the 11-byte function at 0x00d9b2b0).
bool __cdecl CandLess(const Cand* a, const Cand* b) { return a->dist2 < b->dist2; }
void __cdecl operator_delete_array(void* p);                        // 0x00f47380

struct SocialRespond;
int __cdecl MoveToTarget(Creature* c, unsigned pick, CandVec* cands, Obj*** targets);   // 0x00d9bee0

inline Vec3 Target(const Vec3& origin, const Vec3& dir, float scale)
{
    return Vec3(dir.x * scale + origin.x, origin.y + dir.y * scale, origin.z + dir.z * scale);
}

struct SocialRespond {
    Creature* mOwner;       // +0x00
    Creature* mPartner;     // +0x04
    uint32_t pad08[18];
    uint32_t mCount;        // +0x50
    uint32_t pad54;
    uint32_t mFlags;        // +0x58
    Obj** mTargets;         // +0x5c

    int Activate(Creature* c, int slot);
};

// @ 0x00da3b90
int SocialRespond::Activate(Creature* c, int slot)
{
    Vec3 p0 = *mOwner->loco.GetPosition();
    float rr = c->loco.GetRadius() + 1.0f;
    float t = rr + rr;
    float r5 = t + 5.0f;
    float sq = r5 * r5;
    Vec3 b = *c->loco.GetPosition();
    Planet* planet = PlanetModel();

    if (mFlags & 0x20) {
        float dx = b.x - p0.x, dy = b.y - p0.y, dz = b.z - p0.z;
        float d2 = (dz * dz + dy * dy) + dx * dx;
        if (sq > d2) {
            float inv = 1.0f / sqrtf(d2 + 1e-8f);
            Vec3 tgt(dx * inv * sq + p0.x, p0.y + dy * inv * sq, p0.z + dz * inv * sq);
            Vec3 out;
            planet->DirectionToSurfacePosition(&out, &tgt);
            c->MoveToPointAtSpeed(2, &out, 1.0f, 2.0f);
            if (slot != -1) {
                Obj** pp = &mTargets[slot];
                Obj* o = *pp;
                if (o) {
                    *pp = 0;
                    o->Release();
                    return -1;
                }
            }
        } else {
            c->loco.Stop();
        }
        return -1;
    }

    if (slot != -1 && mTargets[slot] == (Obj*)c)
        return slot;

    Cand stackBuf[3];
    CandVec cands;
    cands.mpBegin = stackBuf;
    cands.mpEnd = stackBuf;
    cands.mpCapacity = stackBuf + 3;
    cands.mpPool = stackBuf;
    cands.Resize(3);

    Creature* partner = mPartner;
    const Vec3* po = mOwner->loco.GetPosition();
    const Vec3* pp = partner->loco.GetPosition();
    float fx = pp->x - po->x;
    float fz = pp->z - po->z;
    float fy = pp->y - po->y;
    float inv1 = 1.0f / sqrtf((fy * fy + (fz * fz + fx * fx)) + 1e-8f);
    Vec3 fwd(inv1 * fx, inv1 * fy, inv1 * fz);

    const Vec3* up = mOwner->loco.GetPosition();
    float inv2 = 1.0f / sqrtf(((up->x * up->x + up->y * up->y) + up->z * up->z) + 1e-8f);
    Vec3 axis(inv2 * up->x, inv2 * up->y, inv2 * up->z);
    Quat q1 = AxisAngle(axis, kAngleB + kAngleA);
    Quat q2 = AxisAngle(axis, kAngleC + kAngleA);

    Cand* cd = cands.mpBegin;
    cd[0].kind = 0;
    cd[0].dir = QuatRotate(fwd, q1);
    Vec3 tg0 = Target(p0, cd[0].dir, t);
    Vec3 s0;
    cd[0].pos = *planet->DirectionToSurfacePosition(&s0, &tg0);
    {
        float ex = b.x - cd[0].pos.x, ez = b.z - cd[0].pos.z, ey = b.y - cd[0].pos.y;
        cd[0].dist2 = (ex * ex + ez * ez) + ey * ey;
    }

    cd[1].kind = 1;
    cd[1].dir = QuatRotate(fwd, q2);
    Vec3 tg1 = Target(p0, cd[1].dir, t);
    Vec3 s1;
    cd[1].pos = *planet->DirectionToSurfacePosition(&s1, &tg1);
    {
        float ex = b.x - cd[1].pos.x, ez = b.z - cd[1].pos.z, ey = b.y - cd[1].pos.y;
        cd[1].dist2 = (ex * ex + ez * ez) + ey * ey;
    }

    cd[2].kind = 2;
    {
        float inv3 = 1.0f / sqrtf(((fwd.x * fwd.x + fwd.z * fwd.z) + fwd.y * fwd.y) + 1e-8f);
        cd[2].dir.y = -(inv3 * fwd.y);
        cd[2].dir.x = -(inv3 * fwd.x);
        cd[2].dir.z = -(inv3 * fwd.z);
    }
    Vec3 tg2 = Target(p0, cd[2].dir, t);
    Vec3 s2;
    cd[2].pos = *planet->DirectionToSurfacePosition(&s2, &tg2);
    {
        float ex = b.x - cd[2].pos.x, ez = b.z - cd[2].pos.z, ey = b.y - cd[2].pos.y;
        cd[2].dist2 = (ex * ex + ez * ez) + ey * ey;
    }

    SortCands(cands.mpBegin, cands.mpEnd, CandLess);

    unsigned pick = 0;
    for (unsigned i = 0; i < 3; ++i) {
        if (mCount > 2 || cands.mpBegin[i].kind != 2) {
            pick = i;
            break;
        }
    }
    int result = MoveToTarget(c, pick, &cands, &mTargets);
    if (result == -1) {
        float dx = b.x - p0.x, dz = b.z - p0.z, dy = b.y - p0.y;
        float d2 = (dx * dx + dz * dz) + dy * dy;
        if (d2 < sq) {
            float inv = 1.0f / sqrtf(d2 + 1e-8f);
            Vec3 tgt(inv * dx * sq + p0.x, p0.y + inv * dy * sq, p0.z + inv * dz * sq);
            Vec3 out;
            planet->DirectionToSurfacePosition(&out, &tgt);
            c->MoveToPointAtSpeed(2, &out, 1.0f, 2.0f);
        }
    }
    if (cands.mpBegin && cands.mpBegin != cands.mpPool)
        operator_delete_array(cands.mpBegin);
    return result;
}
