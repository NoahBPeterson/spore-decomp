// Slice s009f1990 -- 0x009f1990 (4056 bytes): IK particle constraint step (nSPCreatureAnim ik_solver.cpp).
//
// Per-particle post-pass of the IK solver (name guessed: IKUpdateParticle).  For a particle
// (700 bytes, body pointer at +0, parent particle at +8):
//   1. clamp its position to a leash around the parent (max = (1+k)*radius, min = (1-k2)*radius),
//      then, if the solver's collision flag is set, push it out of the body's ground plane
//      (blend between the two corrected positions via smoothstep FUN_009b01e0);
//   2. recurse into the child particles (body->childStart / body->childCount, 700-byte stride);
//   3. rebuild the particle's orientation (nearest-neighbour twist correction when the
//      particle has no fixed link) and derive the pivot (+0x190) = position - R * (body offset * scale).
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Vec3 {
    float x, y, z;
    Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

struct Quat;
extern "C" {
    Vec3* __cdecl FUN_0099c1a0(Vec3* out, const Quat* q, const Vec3* v);       // 0x0099c1a0 q.Rotate(v)
    float __cdecl FUN_009b01e0(float lo, float hi, float x);                   // 0x009b01e0 smoothstep(lo,hi,x)
    // 0x009ed8c0: register-arg helper (ecx=offset, edx=plane normal, esi=anchor, stack: out, plane d);
    // slides the offset onto the plane; modelled as a cdecl function with the same arguments.
    Vec3* __cdecl FUN_009ed8c0(const Vec3* off, const Vec3* n, const Vec3* anchor, Vec3* out, float d);
    Quat* __cdecl QuaternionFromTwoVectors(Quat* out, const Vec3* a, const Vec3* b, int flag); // 0x009ac7a0
}
struct Quat {
    float x, y, z, w;
    // 0x009edcf0: out(ecx) = quaternion from (axis*s ... c); ret 0x10
    Quat* __thiscall FromAxisSC(const Vec3* axis, float s, float c, int flag);   // 0x009edcf0
};
extern float g_leashBase;     // DAT_01550a10
extern float g_leashExtra;    // DAT_01550a14
extern float g_leashAlt;      // DAT_0166bff4
extern int   g_collideFlag;   // DAT_01550a68

struct IKBody {
    uint32_t pad000[0x114 / 4];
    float    radiusScale;         // +0x114
    float    q[4];                // +0x118 orientation (4 floats; order x?,y,z,w by offset)
    uint32_t pad128[10];
    uint32_t flags;               // +0x150
    uint32_t pad154[44];
    uint32_t childStart;          // +0x204
    uint32_t childCount;          // +0x208
    uint32_t pad20c[78];
    float    offset[3];           // +0x344
};

struct IKParticle;

struct IKWorld {
    uint32_t pad000[0x70 / 4];
    float    scale;               // +0x70
    uint32_t pad074[(0x2e4 - 0x74) / 4];
    char*    particles;           // +0x2e4 (700-byte IKParticle array)
    uint32_t pad2e8[(0x168c - 0x2e8) / 4];
    char     enabled;             // +0x168c
};

struct IKParticle {
    IKBody*     body;             // +0x000
    uint32_t    pad004;
    IKParticle* parent;           // +0x008
    uint32_t    pad00c[11];
    uint8_t     dirty;            // +0x038
    uint8_t     pad039[0x78 - 0x39];
    float       f078;             // +0x078
    uint32_t    pad07c[(0x190 - 0x7c) / 4];
    Vec3        pivot;            // +0x190
    Quat        q;                // +0x19c
    uint8_t     state;            // +0x1ac (low 3 bits = mode)
    uint8_t     pad1ad[3];
    Vec3        pos;              // +0x1b0
    Vec3        rot;              // +0x1bc
    uint32_t    pad1c8[3];
    Vec3        prev;             // +0x1d4
    uint32_t    pad1e0[(0x214 - 0x1e0) / 4];
    float       radius;           // +0x214
    uint32_t    pad218[(0x234 - 0x218) / 4];
    uint8_t     active;           // +0x234
    uint8_t     pad235[0x2a0 - 0x235];
    uint8_t     hasPlane;         // +0x2a0
    uint8_t     pad2a1[3];
    Vec3        planeN;           // +0x2a4
    Vec3        planeP;           // +0x2b0
};

struct IKContext {
    IKWorld* world;               // +0x00
    Quat*    rootQuat;            // +0x04
    Vec3     axis;                // +0x08
    uint32_t pad14[3];
    float    d;                   // +0x20

    void __thiscall Update(IKParticle* p);   // 0x009f1990
};

static inline float rsqrt_fast(float x)
{
    union { float f; int i; } u;
    u.i = 0x5f375a86 - (((int)x) >> 1);   // original uses the integer value of x (int)
    float y = u.f;
    return (1.5f - ((x * 0.5f) * y) * y) * y;
}

// @ 0x009f1990
void __thiscall IKContext::Update(IKParticle* p)
{
    float t4c, t30, t34, t38;
    Vec3 v1;

    if ((p->state & 7) == 4)
        return;

    uint32_t flagsBit = (p->body->flags >> 3) & 1;
    IKParticle* parent = p->parent;

    if (flagsBit == 0 && p->active != 0) {
        p->prev = p->pos;

        bool near_ = ((p->state & 7) == 0) && ((p->body->flags & 4) != 0);
        float lo = g_leashBase;
        if (((p->state & 7) == 0) && ((p->body->flags & 2) == 0) && ((parent->body->flags & 2) != 0))
            lo = 0.0f;
        float hi = near_ ? g_leashExtra : g_leashAlt;
        if (((p->body->flags & 0x80) != 0) || ((parent->body->flags & 0x80) != 0)) {
            lo = 0.0f;
            hi = 0.0f;
        }

        // The original squares the x difference unrounded (x87) and the y/z differences
        // after rounding them to float (SSE); dx is double and vy/vz volatile to keep that rounding.
        double dx = (double)p->pos.x - (double)parent->pos.x;
        Vec3 c;
        c.x = (float)dx;
        volatile float vy = p->pos.y - parent->pos.y;
        volatile float vz = p->pos.z - parent->pos.z;
        c.y = vy;
        c.z = vz;
        float maxLen = (lo + 1.0f) * p->radius;
        float len = (float)(sqrt(dx * dx + (double)(c.y * c.y) + (double)(c.z * c.z)) + 1e-08f);
        t4c = len;
        if (len > maxLen) {
            float s = maxLen / len;
            p->pos.x = c.x * s + parent->pos.x;
            p->pos.y = parent->pos.y + c.y * s;
            p->pos.z = parent->pos.z + c.z * s;
            t4c = maxLen;
        } else {
            float minLen = (1.0f - hi) * p->radius;
            if (len < minLen) {
                float s = minLen / len;
                p->pos.x = parent->pos.x + c.x * s;
                p->pos.y = parent->pos.y + c.y * s;
                p->pos.z = parent->pos.z + c.z * s;
                t4c = minLen;
            }
        }

        if (g_collideFlag != 0 && near_ && world->enabled != 0) {
            Vec3 n;
            float d;
            if (p->hasPlane == 0) {
                n = axis;
                d = world->scale * p->body->radiusScale + this->d;
            } else {
                n = p->planeP;
                d = (p->planeN.z * n.z + p->planeN.y * n.y) + p->planeN.x * n.x;
            }
            float sc = world->scale;
            Vec3 loc;
            loc.x = p->body->offset[0] * sc;
            loc.y = p->body->offset[1] * sc;
            loc.z = p->body->offset[2] * sc;
            Vec3* r = FUN_0099c1a0(&v1, &p->q, &loc);
            d = ((r->z * n.z + r->y * n.y) + n.x * r->x) + d;
            if (((p->pos.z * n.z + p->pos.y * n.y) + n.x * p->pos.x) < d) {
                Vec3 a = parent->pos;
                c.x = p->pos.x - a.x;
                c.y = p->pos.y - a.y;
                c.z = p->pos.z - a.z;
                float proj = (c.z * n.z + c.y * n.y) + c.x * n.x;
                float blend = FUN_009b01e0(t4c * -0.9396926f, t4c * -0.70710677f, proj);
                Vec3 sl;
                if (blend > 0.0f) {
                    Vec3 tmp;
                    Vec3* s = FUN_009ed8c0(&v1, &n, &a, &tmp, d);
                    t38 = s->x;
                    t34 = s->y;
                    t30 = s->z;
                }
                float rx = v1.x, ry = v1.y, rz = v1.z;
                if (blend < 1.0f) {
                    float k;
                    if (fabsf(proj) <= 1e-06f)
                        k = 1.0f;
                    else
                        k = (((d - a.z * n.z) - a.y * n.y) - a.x * n.x) / proj;
                    rx = c.x * k + a.x;
                    rz = c.z * k + a.z;
                    ry = c.y * k + a.y;
                    if (k < 0.7f) {
                        v1.x = c.x * 0.7f;
                        v1.y = c.y * 0.7f;
                        v1.z = c.z * 0.7f;
                        Vec3* s = FUN_009ed8c0(&c, &n, &a, &sl, d);
                        rx = s->x;
                        ry = s->y;
                        rz = s->z;
                    }
                }
                if (blend != 0.0f) {
                    if (blend == 1.0f) {
                        p->pos.x = t38;
                        p->pos.y = t34;
                        p->pos.z = t30;
                        goto children;
                    }
                    float ib = 1.0f - blend;
                    rx = rx * ib + t38 * blend;
                    ry = ry * ib + t34 * blend;
                    rz = rz * ib + t30 * blend;
                }
                p->pos.z = rz;
                p->pos.y = ry;
                p->pos.x = rx;
            }
        }
    }

children:
    {
        uint32_t n = p->body->childCount;
        if (n != 0) {
            uint32_t i = 0;
            do {
                Update((IKParticle*)(world->particles + (p->body->childStart + i) * 700));
                i++;
            } while (i < n);
        }
    }

    if (flagsBit != 0)
        return;

    if (p->active != 0) {
        if (p->f078 <= 0.0f && (p->state & 7) != 0) {
            IKParticle* top1 = 0;
            IKParticle* top2 = 0;
            if (p->body->childCount != 0) {
                IKParticle* c = (IKParticle*)(world->particles + p->body->childStart * 700);
                int cnt = p->body->childCount;
                do {
                    if ((c->state & 7) != 4) {
                        IKParticle* a = top1;
                        IKParticle* b = top2;
                        top1 = c;
                        if (a != 0) {
                            float r = c->radius;
                            top2 = a;
                            if (r < a->radius &&
                                (b == 0 || (b->radius <= r && r != b->radius))) {
                                top1 = a;
                                top2 = c;
                            } else if (r < a->radius) {
                                top1 = a;
                                top2 = b;
                            }
                        }
                    }
                    c = (IKParticle*)((char*)c + 700);
                } while (--cnt != 0);
            }

            Vec3 d1, e1, ax;
            Quat qq;
            d1.x = top1->pos.x - p->pos.x;
            d1.y = top1->pos.y - p->pos.y;
            d1.z = top1->pos.z - p->pos.z;
            e1.x = top1->rot.x - p->rot.x;
            e1.y = top1->rot.y - p->rot.y;
            e1.z = top1->rot.z - p->rot.z;
            QuaternionFromTwoVectors(&qq, &e1, &d1, 0);

            if (top2 != 0) {
                float len = sqrtf(d1.x * d1.x + (d1.y * d1.y + d1.z * d1.z));
                if (len != 0.0f) {
                    len = 1.0f / len;
                    d1.x = d1.x * len;
                    d1.y = d1.y * len;
                    d1.z = d1.z * len;
                }
                Vec3 g;
                g.x = top2->pos.x - p->pos.x;
                g.y = top2->pos.y - p->pos.y;
                g.z = top2->pos.z - p->pos.z;
                e1.x = top2->rot.x - p->rot.x;
                e1.y = top2->rot.y - p->rot.y;
                e1.z = top2->rot.z - p->rot.z;
                Vec3 h;
                FUN_0099c1a0(&h, &qq, &e1);
                float s1 = ((h.x * g.x + h.z * g.z) + h.y * g.y) -
                           ((h.x * d1.x + h.z * d1.z) + h.y * d1.y) *
                           ((g.x * d1.x + g.z * d1.z) + g.y * d1.y);
                float s2 = ((h.z * d1.y - h.y * d1.z) * g.x +
                            (h.y * d1.x - d1.y * h.x) * g.z) +
                           (d1.z * h.x - h.z * d1.x) * g.y;
                float m = s2 * s2 + s1 * s1;
                if (1e-05f < m) {
                    float y = rsqrt_fast(m);
                    Quat q2;
                    Quat* r = q2.FromAxisSC(&d1, y * s1, y * s2, 0);
                    float a = qq.w * r->x;
                    float b = qq.y * r->z;
                    float c = qq.z * r->y;
                    float dd = qq.w * r->y;
                    float e = qq.z * r->x;
                    float f = qq.z * r->z;
                    qq.z = ((qq.w * r->z - qq.x * r->y) + qq.y * r->x) + qq.z * r->w;
                    qq.w = ((qq.w * r->w - qq.x * r->x) - qq.y * r->y) - f;
                    qq.y = ((dd + qq.y * r->w) + qq.x * r->z) - e;
                    qq.x = ((a + qq.x * r->w) - b) + c;
                }
            }

            Quat* R = rootQuat;
            float rw = R->w;
            float f20 = ((qq.w * R->x + qq.x * rw) - qq.z * R->y) + qq.y * R->z;
            float f22 = ((qq.w * R->y + qq.z * R->x) + qq.y * rw) - qq.x * R->z;
            float f24 = ((qq.z * rw - qq.y * R->x) + qq.w * R->z) + qq.x * R->y;
            IKBody* b = p->body;
            float b0 = b->q[0], b1 = b->q[1], b2 = b->q[2], b3 = b->q[3];
            float f27 = ((qq.w * R->w - qq.x * R->x) - qq.y * R->y) - qq.z * R->z;
            p->q.x = ((f27 * b0 + f20 * b3) - f24 * b1) + f22 * b2;
            p->q.y = ((f27 * b1 + f24 * b0) + f22 * b3) - f20 * b2;
            p->q.z = ((f24 * b3 - f22 * b0) + f27 * b2) + f20 * b1;
            p->q.w = ((f27 * b3 - f20 * b0) - f22 * b1) - f24 * b2;
        }

        float sc = world->scale;
        IKBody* b = p->body;
        float qw = p->q.w;
        float qy = p->q.y;
        float o0 = b->offset[0] * sc;
        float o1 = b->offset[1] * sc;
        float o2 = b->offset[2] * sc;
        float qx = p->q.x;
        float qz = p->q.z;
        p->pivot.x = p->pos.x -
                     ((((qz * qx + qy * qw) * o2 + (qy * qx - qz * qw) * o1) +
                       (-(qz * qz) + -(qy * qy)) * o0) * 2.0f + o0);
        p->pivot.y = p->pos.y -
                     ((((-(qz * qz) + -(qx * qx)) * o1 + (qz * qy - qx * qw) * o2) +
                       (qy * qx + qz * qw) * o0) * 2.0f + o1);
        p->pivot.z = p->pos.z -
                     ((((-(qy * qy) + -(qx * qx)) * o2 + (qz * qy + qx * qw) * o1) +
                       (qz * qx - qy * qw) * o0) * 2.0f + o2);
        p->dirty = 1;
    } else {
        IKBody* b = p->body;
        float sc = world->scale;
        Vec3 loc;
        loc.x = b->offset[0] * sc;
        loc.y = b->offset[1] * sc;
        loc.z = b->offset[2] * sc;
        Vec3* r = FUN_0099c1a0(&v1, &p->q, &loc);
        float ry = r->y, rz = r->z;
        p->pivot.x = p->pos.x - r->x;
        p->pivot.y = p->pos.y - ry;
        p->pivot.z = p->pos.z - rz;
        p->dirty = 1;
    }
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct Quat {
    void FromAxisSC(void*, float, float, int); // 0x009edcf0
};
}
