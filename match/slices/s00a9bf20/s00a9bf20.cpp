// Slice s00a9bf20: FUN_00a9bf20, Swarm particle effect: constrain / deflect one particle
// against the effect's collision sampler (0x00a9bf20). Class and field names are
// Claude-coined from usage (retail layout differs from the 2008 PDB); same family as
// 0x00a9ddd0 (InitParticle) and 0x00a9f170.
//
// Particle position is first moved to world space (inlined Xform::Transform), then tested
// against the sampler. Behaviours selected by description flag bits:
//   bit 15 : set velocity from the sampler's direction field
//   bit 16 : add sampler direction field * dt to velocity
//   bit 14 : push out of the surface (penetration force), optionally spinning the particle
//   none   : stick to / bounce off the surface (restitution f1c4, kill chance f1dc)
// Returns false when the particle should die.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
};
static inline bool Bit(uint32_t v, int n) { return (v >> n) & 1; }

struct RandomLinearCongruential { double RandomDoubleUniform(); };   // 0x009360d0
extern RandomLinearCongruential g_Random;                            // 0x016778dc (sRandom_Swarm)

// 3x3 + translation transform (flags bit 1 = has rotation), at emitter+0x68.
struct Xform {
    uint32_t flags;      // +0x00
    Vec3 t;              // +0x04
    float scale;         // +0x10
    float m[9];          // +0x14
    void Transform(Vec3* v);       // 0x007cdee0
    void InvTransform(Vec3* v);    // 0x007cda70
    void InvDir(Vec3* v);          // 0x00a78e90
    void Dir(Vec3* v);             // 0x00a7ca50
};

void FastSinCos(float a, float& s, float& c);     // 0x00a78ce0 (cdecl)

struct Sampler {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual bool Contains(Vec3* p);               // 0x18
    virtual void s7();
    virtual float Height(Vec3* p);                // 0x20
    virtual void Normal(Vec3* out, Vec3* p);      // 0x24
    virtual void Field(Vec3* out, Vec3* p);       // 0x28
};

struct Desc {
    uint32_t pad0[2];
    uint32_t flags;          // +0x08
    uint32_t pad0c[(0x1c4 - 0x0c) / 4];
    float restitution;       // +0x1c4
    float depthMax;          // +0x1c8
    float strength;          // +0x1cc
    float spring;            // +0x1d0
    float zScale;            // +0x1d4
    float depthKill;         // +0x1d8
    float killChance;        // +0x1dc
};

struct Particle {
    uint32_t node[2];
    float age;               // +0x08
    float life;              // +0x0c
    Vec3 pos;                // +0x10
    Vec3 vel;                // +0x1c
    uint32_t pad28[(0x50 - 0x28) / 4];
    float spinA;             // +0x50
    float spinB;             // +0x54
    float angle1;            // +0x58
    float angle2;            // +0x5c
};

class Emitter {
public:
    uint32_t pad00[3];
    Desc* desc;              // +0x0c
    uint32_t pad10[(0x68 - 0x10) / 4];
    Xform xf;                // +0x68
    uint32_t pada0[(0x194 - 0xa0) / 4];
    Sampler* sampler;        // +0x194
    uint32_t pad198;
    uint32_t pad19c;
    bool local;              // +0x1a0

    bool Constrain(Particle* p, float dt);        // 0x00a9bf20
};

bool Emitter::Constrain(Particle* p, float dt)
{
    Vec3 pos = p->pos;
    if (local) {
        if (xf.flags & 2) {
            Vec3 r;
            r.x = (xf.m[3] * pos.y + xf.m[6] * pos.z) + xf.m[0] * pos.x;
            r.y = (xf.m[4] * pos.y + xf.m[7] * pos.z) + xf.m[1] * pos.x;
            r.z = (xf.m[5] * pos.y + xf.m[8] * pos.z) + xf.m[2] * pos.x;
            pos = r;
        }
        pos.x = xf.scale * pos.x + xf.t.x;
        pos.y = xf.t.y + xf.scale * pos.y;
        pos.z = xf.t.z + xf.scale * pos.z;
    }

    if (!sampler->Contains(&pos))
        return !Bit(desc->flags, 17);

    Desc* d = desc;
    if (Bit(d->flags, 15)) {
        Vec3 out;
        sampler->Field(&out, &pos);
        if (local) xf.InvDir(&out);
        float k = desc->strength;
        Vec3 nv;
        nv.x = out.x * k;
        nv.y = out.y * k;
        nv.z = out.z * k;
        p->vel = nv;
        return true;
    }
    if (Bit(d->flags, 16)) {
        Vec3 out;
        sampler->Field(&out, &pos);
        if (local) xf.InvDir(&out);
        float k = desc->strength;
        p->vel.x = p->vel.x + (out.x * k) * dt;
        p->vel.y = p->vel.y + (out.y * k) * dt;
        p->vel.z = p->vel.z + (out.z * k) * dt;
        return true;
    }
    if (Bit(d->flags, 14)) {
        float k2 = d->spring;
        float len = (float)sqrt(((double)p->vel.x * p->vel.x + (double)p->vel.y * p->vel.y) + (double)p->vel.z * p->vel.z);
        float sx = p->vel.x * k2, sy = p->vel.y * k2, sz = p->vel.z * k2;
        Vec3 dir;
        if (len > 10.0f) {
            float inv = 1.0f / len;
            dir.x = inv * sx;
            dir.y = inv * sy;
            dir.z = inv * sz;
        } else {
            dir.x = sx * 0.1f;
            dir.y = sy * 0.1f;
            dir.z = sz * 0.1f;
        }
        if (local) xf.Transform(&dir);
        Vec3& cand = dir;
        cand.x = dir.x + pos.x;
        cand.y = dir.y + pos.y;
        cand.z = dir.z + pos.z;
        if (!sampler->Contains(&cand)) return true;
        float h = sampler->Height(&cand);
        float depth = cand.z - h;
        if (desc->depthKill > depth) return false;
        if (!(desc->depthMax > depth)) return true;
        Vec3 n;
        sampler->Normal(&n, &cand);
        if (local) xf.Dir(&n);
        d = desc;
        float t = d->depthMax - depth;
        float t2 = t * t;
        float nz = n.z * t2, nx = n.x * t2, ny = n.y * t2;
        float fz = d->zScale * nz;
        float kd = d->strength * dt;
        Vec3 force;
        force.x = nx * kd;
        force.y = ny * kd;
        force.z = fz * kd;
        if (Bit(d->flags, 20)) {
            float r54 = p->spinB;
            if (r54 > 0.001f) {
                float s, c;
                FastSinCos(p->angle1, s, c);
                float inv = 1.0f / r54;
                p->angle1 = (float)atan2(force.y * inv + s, force.x * inv + c);
            }
            float r50 = p->spinA;
            if (r50 > 0.001f) {
                p->angle2 = (float)acos(cos(p->angle2) + force.z / r50);
                return true;
            }
        } else {
            p->vel.x = p->vel.x + force.x;
            p->vel.y = p->vel.y + force.y;
            p->vel.z = p->vel.z + force.z;
        }
        return true;
    }

    // No flag: stick to / bounce off the surface.
    if (desc->restitution == 0.0f) {
        float h = sampler->Height(&pos);
        if (!Bit(desc->flags, 18)) {
            if (!(h > pos.z)) return true;
        }
        p->pos.x = pos.x;
        p->pos.y = pos.y;
        p->pos.z = h;
        Vec3 n;
        sampler->Normal(&n, &pos);
        if (local) {
            xf.InvTransform(&p->pos);
            xf.Dir(&n);
        }
        float dot = (p->vel.z * n.z + p->vel.y * n.y) + p->vel.x * n.x;
        float neg = -dot;
        if (!(neg > 0.0f)) return true;
        p->vel.x = p->vel.x + n.x * neg;
        p->vel.y = p->vel.y + n.y * neg;
        p->vel.z = p->vel.z + n.z * neg;
        return true;
    }

    float h = sampler->Height(&pos);
    if (!(h > pos.z)) return true;
    if (desc->killChance != 0.0f) {
        if (desc->killChance == 1.0f) return false;
        double r = g_Random.RandomDoubleUniform();
        if (!(desc->killChance < r)) return false;
    }
    p->pos.x = pos.x;
    p->pos.y = pos.y;
    p->pos.z = h;
    Vec3 n;
    sampler->Normal(&n, &pos);
    if (local) {
        xf.InvTransform(&p->pos);
        xf.Dir(&n);
    }
    float dot = (p->vel.z * n.z + p->vel.y * n.y) + p->vel.x * n.x;
    dot = dot * (desc->restitution + 1.0f);
    p->vel.x = p->vel.x - n.x * dot;
    p->vel.y = p->vel.y - n.y * dot;
    p->vel.z = p->vel.z - n.z * dot;
    return true;
}
