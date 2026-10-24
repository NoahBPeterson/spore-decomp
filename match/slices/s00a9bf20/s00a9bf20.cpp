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

namespace EA { namespace Random {
struct RandomLinearCongruential { double RandomDoubleUniform(); };   // 0x009360d0
}}
extern EA::Random::RandomLinearCongruential g_Random;                // 0x016778dc (sRandom_Swarm)

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

// ---------------------------------------------------------------------------------------------
// Swarm emitter subclass used by 0x00a9c710 / 0x00a9ca50.  Same object family as Emitter but
// with the sampler at +0x198 and the "local space" flag at +0x1a1 (see 0x00a9b480, which
// manipulates the same +0x30/+0x68 transforms and +0xc description).
// ---------------------------------------------------------------------------------------------

float FUN_0053c480(const float* a, const float* b);        // 0x0053c480 (dot product)
float FUN_007cdb90(float* range);                          // 0x007cdb90 (random in [range[0],range[1]])
void* FUN_007d5590(void* out, void* a, const void* b);     // 0x007d5590 (copy matrix + update)
void FUN_00a7ab40(int count, const float* data, float scale, void* params, void* extra);  // 0x00a7ab40

struct SwarmDesc {
    uint32_t pad0[2];
    uint32_t flags;                          // +0x08
    uint32_t pad0c[(0x44 - 0x0c) / 4];
    float m_44;                              // +0x44
};

struct SwarmChild {
    SwarmChild* m_next;                      // +0x00
    uint32_t m_pad04[0x1f - 1];              // +0x04 .. +0x7b
    void* m_processor;                       // +0x7c
};

struct SwarmProcessor {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void p4(); virtual void p5(); virtual void p6();
    virtual bool Command(int command, float* data, int count);   // +0x1c
};

struct SwarmParamArray {
    uint32_t m_begin;                        // +0x00
    uint32_t m_end;                          // +0x04
    uint32_t m_capacityAndFlags;             // +0x08
};

static inline void TransformPoint(const Xform& xf, Vec3& v)
{
    if (xf.flags & 2) {
        Vec3 r;
        r.x = (xf.m[3] * v.y + xf.m[6] * v.z) + xf.m[0] * v.x;
        r.y = (xf.m[4] * v.y + xf.m[7] * v.z) + xf.m[1] * v.x;
        r.z = (xf.m[5] * v.y + xf.m[8] * v.z) + xf.m[2] * v.x;
        v = r;
    }
    v.x = xf.scale * v.x + xf.t.x;
    v.y = xf.t.y + xf.scale * v.y;
    v.z = xf.t.z + xf.scale * v.z;
}

class SwarmEmitter {
public:
    uint32_t m_pad00[3];                     // +0x00
    SwarmDesc* m_desc;                       // +0x0c
    uint32_t m_pad10[5];                     // +0x10 .. +0x23
    SwarmChild* m_children;                  // +0x24 (head sentinel's next pointer)
    uint32_t m_pad28[2];                     // +0x28 .. +0x2f
    Xform m_xfA;                             // +0x30
    Xform m_xfB;                             // +0x68
    uint32_t m_padA0[(0x114 - 0xa0) / 4];    // +0xa0 .. +0x113
    Vec3 m_surfacePoint;                     // +0x114
    float m_surfaceSign;                     // +0x120
    uint32_t m_pad124[(0x130 - 0x124) / 4];  // +0x124 .. +0x12f
    Vec3 m_planePoint;                       // +0x130
    float m_param13c;                        // +0x13c
    float m_param140;                        // +0x140
    float m_param144;                        // +0x144
    float m_param148;                        // +0x148
    float m_param14c;                        // +0x14c
    Vec3 m_param150;                         // +0x150
    float m_minHeight;                       // +0x15c
    float m_maxHeight;                       // +0x160
    float m_basis0;                          // +0x164
    float m_basis1;                          // +0x168
    float m_basis2;                          // +0x16c
    float m_basis3;                          // +0x170
    float m_basis4;                          // +0x174
    float m_basis5;                          // +0x178
    uint32_t m_pad17c[(0x198 - 0x17c) / 4];  // +0x17c .. +0x197
    Sampler* m_sampler;                      // +0x198
    uint32_t m_pad19c;                       // +0x19c
    bool m_localA;                           // +0x1a0
    bool m_local;                            // +0x1a1
    uint8_t m_pad1a2[2];                     // +0x1a2 .. +0x1a3
    Vec3 m_bboxMin;                          // +0x1a4
    Vec3 m_bboxMax;                          // +0x1b0
    uint32_t m_pad1bc[(0x218 - 0x1bc) / 4];  // +0x1bc .. +0x217
    SwarmParamArray m_params;                // +0x218

    bool ConstrainLocal(Particle* p);                       // 0x00a9c710
    bool SetParameter(int command, float* data, int count); // 0x00a9ca50
    void UpdateBasis(float* data);                          // 0x00a9b480
};

// @ 0x00a9c710  SwarmEmitter::ConstrainLocal
bool SwarmEmitter::ConstrainLocal(Particle* p)
{
    Vec3 pos = p->pos;
    if (m_local) {
        TransformPoint(m_xfA, pos);
        TransformPoint(m_xfB, pos);
    }

    if (m_sampler == 0 || !m_sampler->Contains(&pos))
        return false;

    float h = m_sampler->Height(&pos);
    uint32_t flags = m_desc->flags;
    if (Bit(flags, 6)) {
        if (m_minHeight > h) return false;
        if (h > m_maxHeight) return false;
    } else if (Bit(flags, 7)) {
        if (!(h > g_Random.RandomDoubleUniform()))
            return false;
    }

    if (Bit(flags, 5)) {
        float range[2];
        range[0] = m_bboxMin.z;
        range[1] = m_bboxMax.z;
        pos.z = h + FUN_007cdb90(range);
    }

    if (m_local) {
        m_xfB.InvTransform(&pos);
        m_xfA.InvTransform(&pos);
    }

    p->pos = pos;
    return true;
}

// @ 0x00a9ca50  SwarmEmitter::SetParameter
bool SwarmEmitter::SetParameter(int command, float* data, int count)
{
    switch (command) {
    case 0:
        m_param13c = data[0];
        return true;
    case 1:
        m_param148 = data[0];
        return true;
    case 2:
        m_param144 = data[0];
        return true;
    case 3:
        m_param140 = data[0];
        return true;
    case 4:
        m_param14c = data[0];
        return true;
    case 5:
        m_param150.x = data[0];
        m_param150.y = data[1];
        m_param150.z = data[2];
        return true;
    case 7:
        UpdateBasis(data);
        return true;
    case 9:
        m_surfacePoint.x = data[0];
        m_surfacePoint.y = data[1];
        m_surfacePoint.z = data[2];
        m_xfB.InvTransform(&m_surfacePoint);
        return true;
    case 0xa:
        m_surfaceSign = data[0];
        return true;
    case 0xb: {
        float numer = (m_planePoint.x - data[0]) * data[3];
        numer = numer + (m_planePoint.y - data[1]) * data[4];
        numer = numer + (m_planePoint.z - data[2]) * data[5];
        float len2 = FUN_0053c480(data + 3, data + 3);
        float t = numer / len2;
        m_surfacePoint.x = data[0] + data[3] * t;
        m_surfacePoint.y = data[1] + data[4] * t;
        m_surfacePoint.z = data[2] + data[5] * t;
        m_surfaceSign = (t >= 0.0f) ? 1.0f : 0.0f;
        m_xfB.InvTransform(&m_surfacePoint);
        return true;
    }
    case 0xd: {
        uint32_t buf[14];
        void* out = FUN_007d5590(buf, &m_xfA, &m_xfB);
        FUN_00a7ab40(count / 3, data, m_desc->m_44, out, &m_params);
        return true;
    }
    case 0x10:
        m_minHeight = data[0];
        m_maxHeight = data[1];
        return true;
    case 0x101:
        m_basis0 = data[0];
        m_basis2 = data[1];
        m_basis4 = data[2];
        m_basis1 = data[3];
        m_basis3 = data[4];
        m_basis5 = data[5];
        return true;
    default:
        break;
    }

    SwarmChild* head = (SwarmChild*)&m_children;
    bool result = false;
    for (SwarmChild* n = head->m_next; n != head; n = n->m_next) {
        SwarmProcessor* proc = (SwarmProcessor*)n->m_processor;
        if (proc != 0) {
            bool r = proc->Command(command, data, count);
            if (r || result)
                result = true;
        }
    }
    return result;
}
