// src/game/SPCreatureAnim/ik_solver.cpp -- migrated from slice(s) s009f1990, s009f09a0, s009eddc0, s009ec360 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/ik_solver.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" float __cdecl FUN_009b01e0(float a, float b, float t);                  // smoothstep(a, b, t)
#include <math.h>
#include <stddef.h>
#pragma intrinsic(sin, cos, atan2, sqrt)

// ---- items of slice s009ec360 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct Bone {
    char pad000[0x19c];
    Quat quat;                  // +0x19c
    char pad1ac[0x23c - 0x1ac];
    float turnLimit;            // +0x23c
};
extern "C" Vec3* __cdecl FUN_0099c1a0(Vec3* out, const Quat* q, const Vec3* v);   // QuaternionVectorTransform
extern "C" float __cdecl FUN_009b01e0(float a, float b, float t);                  // smoothstep(a, b, t)
// ---- items of slice s009ec360 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" Vec3* __cdecl FUN_0099c1a0(Vec3* out, const Quat* q, const Vec3* v);   // QuaternionVectorTransform

// ---- items of slice s009eddc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sqrt, atan2, pow)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;
struct Vec3_s009e_ddc0 { f32 x, y, z; };
struct Quat_s009e_ddc0 { f32 x, y, z, w; };
struct Mat3 {
    f32 m[9];
    void __thiscall RotateY(f32 angle);                 // 0x009e5f50
};
extern "C" Vec3_s009e_ddc0* __cdecl FUN_0099c1a0_s009e_ddc0(Vec3_s009e_ddc0* out, const Quat_s009e_ddc0* q, const Vec3_s009e_ddc0* v);     // q.Rotate(v)
extern "C" Quat_s009e_ddc0* __cdecl FUN_009a4f10(Quat_s009e_ddc0* out, const Mat3* m);                    // Quat from Mat3
extern "C" void  __cdecl FUN_009a4a70(const Vec3_s009e_ddc0* v, Vec3_s009e_ddc0* perpA, Vec3_s009e_ddc0* perpB);     // orthonormal basis
extern "C" void  __cdecl FUN_009e5c30(Mat3* out, const Mat3* a, const Mat3* b);     // a^T-conjugation of b
extern i32 g_splineMinCount;    // DAT_01550a3c
struct BoneOwner {              // *bone
    u8  pad0[0x144];
    Vec3_s009e_ddc0 pivot;                 // +0x144
};
struct Bone_s009e_ddc0 {
    BoneOwner* owner;           // +0x000
    u8  pad4[4];
    Bone_s009e_ddc0* next;                 // +0x008
    u8  padc[0x38 - 0xc];
    u8  dirty;                  // +0x038
    u8  pad39[0x190 - 0x39];
    Vec3_s009e_ddc0 pivotPos;              // +0x190  pos - quat.Rotate(owner->pivot * scale)
    Quat_s009e_ddc0 quat;                  // +0x19c  world orientation
    u8  pad1ac[4];
    Vec3_s009e_ddc0 pos;                   // +0x1b0  world position
    u8  pad1bc[0x244 - 0x1bc];
    i32 noEase;                 // +0x244  (read on ctx->start)
    u8  pad248[0x254 - 0x248];
    f32 t;                      // +0x254  curve parameter
    Vec3_s009e_ddc0 offset;                // +0x258  local offset from the curve point
    Vec3_s009e_ddc0 splinePos;             // +0x264  point on the curve
    Quat_s009e_ddc0 localRot;              // +0x270  local rotation relative to the curve frame
};
struct SplineCtx {
    Bone_s009e_ddc0* end;                  // +0x00
    Bone_s009e_ddc0* start;                // +0x04
    u8  pad8[0x1c - 0x8];
    Vec3_s009e_ddc0 endVel;                // +0x1c  (end-bone space)
    Vec3_s009e_ddc0 endAcc;                // +0x28
    Vec3_s009e_ddc0 endTan;                // +0x34
    Vec3_s009e_ddc0 endUp;                 // +0x40
    Vec3_s009e_ddc0 startVel;              // +0x4c  (start-bone space)
    Vec3_s009e_ddc0 startAcc;              // +0x58
    Vec3_s009e_ddc0 startTan;              // +0x64
    Vec3_s009e_ddc0 startUp;               // +0x70
    u8  pad7c[0x94 - 0x7c];
    u32 flags;                  // +0x94  0x800: do not scale end derivatives by distance
    u8  pad98[0xc8 - 0x98];
    f32 length;                 // +0xc8
    i32 count;                  // +0xcc
};
struct ScaleSrc { u8 pad[0x70]; f32 scale; };
struct ScaleOwner { ScaleSrc* src; };
static __forceinline f32 Sqrt(f32 v) { return (f32)sqrt((double)v); }
static __forceinline void SetColumns(Mat3& m, const f32* a, const f32* b, const f32* c)
{
    for (int i = 0; i < 3; i++) {
        m.m[i * 3 + 0] = a[i];
        m.m[i * 3 + 1] = b[i];
        m.m[i * 3 + 2] = c[i];
    }
}
static __forceinline void QuatMul(Quat_s009e_ddc0& o, const Quat_s009e_ddc0& q, const Quat_s009e_ddc0& r)
{
    o.x = ((q.w * r.x + q.x * r.w) - q.z * r.y) + q.y * r.z;
    o.y = ((q.w * r.y + q.z * r.x) + q.y * r.w) - q.x * r.z;
    o.z = ((q.z * r.w - q.y * r.x) + q.w * r.z) + q.x * r.y;
    o.w = ((q.w * r.w - q.x * r.x) - q.y * r.y) - q.z * r.z;
}
static __forceinline void QuatToMat3(Mat3& o, f32 x, f32 y, f32 z, f32 w)
{
    o.m[0] = 1.0f - (z * z + y * y) * 2.0f;
    o.m[1] = (y * x - w * z) * 2.0f;
    o.m[2] = (w * y + z * x) * 2.0f;
    o.m[3] = (w * z + y * x) * 2.0f;
    o.m[4] = 1.0f - (z * z + x * x) * 2.0f;
    o.m[5] = (z * y - w * x) * 2.0f;
    o.m[6] = (z * x - w * y) * 2.0f;
    o.m[7] = (w * x + z * y) * 2.0f;
    o.m[8] = 1.0f - (y * y + x * x) * 2.0f;
}
static __forceinline void UpdatePivotPos(Bone_s009e_ddc0* b, ScaleOwner* so)
{
    f32 s = so->src->scale;
    f32 vx = b->owner->pivot.x * s;
    f32 vy = b->owner->pivot.y * s;
    f32 vz = b->owner->pivot.z * s;
    f32 x = b->quat.x, y = b->quat.y, z = b->quat.z, w = b->quat.w;
    b->pivotPos.x = b->pos.x - ((((z * x + y * w) * vz + (y * x - z * w) * vy)
                                 + (-(z * z) + -(y * y)) * vx) * 2.0f + vx);
    b->pivotPos.y = b->pos.y - ((((z * y - x * w) * vz + (y * x + z * w) * vx)
                                 + (-(z * z) + -(x * x)) * vy) * 2.0f + vy);
    b->pivotPos.z = b->pos.z - ((((z * y + x * w) * vy + (z * x - y * w) * vx)
                                 + (-(y * y) + -(x * x)) * vz) * 2.0f + vz);
}
// ---- items of slice s009eddc0 end

// ---- items of slice s009f09a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   g_ikUseRatioScale;   // 0x0166bffc
extern float g_ikRatioScale;      // 0x01550a58
extern float g_ikPushRange;       // 0x01550a08
extern float g_ikHeavyWeight;     // 0x01550a04
#pragma intrinsic(sqrt)
struct Vec3_s009f_09a0 {
    float x, y, z;
    Vec3_s009f_09a0& operator=(const Vec3_s009f_09a0& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Mat3_s009f_09a0 {
    float m[9];
    // rotation about a unit axis from (cos, sin); thiscall, ret 0xc
    void SetAxisCosSin(const Vec3_s009f_09a0& axis, float c, float s);   // 0x009e6cf0
};
extern "C" void  __cdecl PerpPair(const Vec3_s009f_09a0* dir, Vec3_s009f_09a0* o1, Vec3_s009f_09a0* o2);          // 0x009a4a70
struct BodyStatic {
    uint32_t pad000[0x150 / 4];
    uint32_t flags;               // +0x150
    uint32_t pad154[(0x204 - 0x154) / 4];
    uint32_t first_child_bidx;    // +0x204
    uint32_t num_children;        // +0x208
    uint32_t num_all_children;    // +0x20c
};
struct Body {                     // 700 bytes
    BodyStatic* static_data;      // +0x000
    uint8_t  pad004[0x1ac - 4];
    uint8_t  goal_mode;           // +0x1ac (low 3 bits)
    uint8_t  pad1ad[2];
    uint8_t  goal_count;          // +0x1af (bidx for mode 2, count for modes 1/3)
    Vec3_s009f_09a0     particle;            // +0x1b0
    Vec3_s009f_09a0     particle_rest;       // +0x1bc
    Vec3_s009f_09a0     particle_goal;       // +0x1c8
    uint8_t  pad1d4[0x1fc - 0x1d4];
    uint8_t  particle_valid;      // +0x1fc
    uint8_t  push_out;            // +0x1fd
    uint8_t  pad1fe[0x214 - 0x1fe];
    float    radius;              // +0x214
    uint8_t  pad218[700 - 0x218];
};
struct Creature {
    uint8_t  pad000[0x2e4];
    Body*    bodies;              // +0x2e4
};
struct IKCtx {
    Creature* creature;           // +0x00
};
static __declspec(noinline) void AccumulateReference(Body* other, Body* self, float* ratio,
                                                     Vec3_s009f_09a0* sumGoal, Vec3_s009f_09a0* sumCur, float* weight)
{
    Vec3_s009f_09a0 g;
    g.x = other->particle_goal.x - self->particle_goal.x;
    g.y = other->particle_goal.y - self->particle_goal.y;
    g.z = other->particle_goal.z - self->particle_goal.z;
    Vec3_s009f_09a0 c;
    if (other->particle_valid == 0) {
        c.x = other->particle_rest.x - self->particle_rest.x;
        c.y = other->particle_rest.y - self->particle_rest.y;
        c.z = other->particle_rest.z - self->particle_rest.z;
    } else {
        c.x = other->particle.x - self->particle.x;
        c.y = other->particle.y - self->particle.y;
        c.z = other->particle.z - self->particle.z;
    }
    float invC = 1.0f / (float)(sqrt(c.x * c.x + (c.y * c.y + c.z * c.z)) + 1e-08);
    float lenG = sqrtf(g.x * g.x + (g.z * g.z + g.y * g.y));
    float invG = 1.0f / (float)(lenG + 1e-08);
    float w = (other->static_data->flags & 4) ? g_ikHeavyWeight : 1.0f;
    float k = w * invG;
    sumGoal->x += g.x * k;
    sumGoal->y += g.y * k;
    sumGoal->z += g.z * k;
    k = w * invC;
    sumCur->z = c.z * k + sumCur->z;
    sumCur->x += c.x * k;
    sumCur->y += c.y * k;
    *ratio = (w * lenG) * invC + *ratio;
    *weight += w;
}
// ---- items of slice s009f09a0 end

// ---- items of slice s009f1990 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_leashBase;     // DAT_01550a10
extern float g_leashExtra;    // DAT_01550a14
extern float g_leashAlt;      // DAT_0166bff4
extern int   g_collideFlag;   // DAT_01550a68
struct Vec3_s009f_1990 {
    float x, y, z;
    Vec3_s009f_1990& operator=(const Vec3_s009f_1990& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Quat_s009f_1990;
extern "C" Vec3_s009f_1990* __cdecl FUN_0099c1a0_s009f_1990(Vec3_s009f_1990* out, const Quat_s009f_1990* q, const Vec3_s009f_1990* v);       // 0x0099c1a0 q.Rotate(v)
extern "C" Vec3_s009f_1990* __cdecl FUN_009ed8c0(const Vec3_s009f_1990* off, const Vec3_s009f_1990* n, const Vec3_s009f_1990* anchor, Vec3_s009f_1990* out, float d);
extern "C" Quat_s009f_1990* __cdecl QuaternionFromTwoVectors(Quat_s009f_1990* out, const Vec3_s009f_1990* a, const Vec3_s009f_1990* b, int flag); // 0x009ac7a0
struct Quat_s009f_1990 {
    float x, y, z, w;
    // 0x009edcf0: out(ecx) = quaternion from (axis*s ... c); ret 0x10
    Quat_s009f_1990* __thiscall FromAxisSC(const Vec3_s009f_1990* axis, float s, float c, int flag);   // 0x009edcf0
};
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
    Vec3_s009f_1990        pivot;            // +0x190
    Quat_s009f_1990        q;                // +0x19c
    uint8_t     state;            // +0x1ac (low 3 bits = mode)
    uint8_t     pad1ad[3];
    Vec3_s009f_1990        pos;              // +0x1b0
    Vec3_s009f_1990        rot;              // +0x1bc
    uint32_t    pad1c8[3];
    Vec3_s009f_1990        prev;             // +0x1d4
    uint32_t    pad1e0[(0x214 - 0x1e0) / 4];
    float       radius;           // +0x214
    uint32_t    pad218[(0x234 - 0x218) / 4];
    uint8_t     active;           // +0x234
    uint8_t     pad235[0x2a0 - 0x235];
    uint8_t     hasPlane;         // +0x2a0
    uint8_t     pad2a1[3];
    Vec3_s009f_1990        planeN;           // +0x2a4
    Vec3_s009f_1990        planeP;           // +0x2b0
};
struct IKContext {
    IKWorld* world;               // +0x00
    Quat_s009f_1990*    rootQuat;            // +0x04
    Vec3_s009f_1990     axis;                // +0x08
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
// ---- items of slice s009f1990 end

// @ 0x009ec360
void __cdecl ApplyConstraintRotation(Bone* bone, const Quat* target, const Vec3* tangent, const Vec3* up)
{
    float limit = bone->turnLimit;
    Quat* cur = &bone->quat;
    if (!(limit > 0.0f)) {
        cur->x = target->x;
        cur->y = target->y;
        cur->z = target->z;
        cur->w = target->w;
        return;
    }

    // where the tangent points now (a) and where it should point (b)
    Vec3 a, b, c;
    FUN_0099c1a0(&a, cur, tangent);
    FUN_0099c1a0(&b, target, tangent);

    // axis between them (b x a), its squared length, and the step limit shrunk for tiny angles
    float cy = b.z * a.x - a.z * b.x;
    float cx = a.z * b.y - a.y * b.z;
    float cz = a.y * b.x - b.y * a.x;
    float len2 = (cy * cy + cz * cz) + cx * cx;
    float step = limit;
    if (len2 < 0.001f)
        step = (len2 * limit) * 999.99994f;

    if (step <= 1e-05f) {
        cur->x = target->x;
        cur->y = target->y;
        cur->z = target->z;
        cur->w = target->w;
        return;
    }

    // r = normalized (axis * |axis|, 1 + a.b)
    float w = (b.z * a.z + (a.y * b.y + b.x * a.x)) + 1.0f;
    union { float f; int i; } rs;
    rs.f = len2;
    rs.i = 0x5f375a86 - (rs.i >> 1);
    float inv = rs.f;
    inv = (1.5f - ((len2 * 0.5f) * inv) * inv) * inv;
    inv = (1.5f - ((len2 * 0.5f) * inv) * inv) * inv;
    float len = ((cx * inv) * cx + (cz * inv) * cz) + (cy * inv) * cy;
    float ux = len * (cx * inv);
    float uz = (cz * inv) * len;
    float uy = (cy * inv) * len;
    float n = (float)sqrt((uy * uy + (uz * uz + ux * ux)) + w * w);
    Quat r;
    r.x = ux;
    r.y = uy;
    r.z = uz;
    r.w = w;
    if (n != 0.0f) {
        float k = 1.0f / n;
        r.w = k * w;
        r.z = uz * k;
        r.x = ux * k;
        r.y = uy * k;
    }

    // T' = r * target
    float tx = target->x, ty = target->y, tz = target->z, tw = target->w;
    Quat t2;
    t2.x = ((tx * r.w + tw * r.x) - ty * r.z) + tz * r.y;
    t2.y = ((ty * r.w + tx * r.z) + tw * r.y) - tz * r.x;
    t2.z = ((tw * r.z - tx * r.y) + tz * r.w) + ty * r.x;
    t2.w = ((tw * r.w - tx * r.x) - ty * r.y) - tz * r.z;

    FUN_0099c1a0(&b, cur, up);
    FUN_0099c1a0(&c, (const Quat*)&t2, up);
    float d = c.y * b.y + (c.z * b.z + c.x * b.x);
    float s = FUN_009b01e0(-0.7660444f, -0.17364818f, d);
    if (s > 0.0f) {
        step = s * step;
        float qx = r.x * step;
        float qw = r.w * step + (1.0f - step);
        float qz = r.z * step;
        float qy = r.y * step;
        double angle = atan2(((double)b.y * c.x - (double)c.y * b.x) * a.z +
                                 (((double)c.z * b.x - (double)b.z * c.x) * a.y +
                                  ((double)b.z * c.y - (double)c.z * b.y) * a.x),
                             (double)d);
        double nn = sqrt((double)qy * qy + ((double)qz * qz + ((double)qw * qw + (double)qx * qx)));
        if (nn != 0.0) {
            float k = 1.0f / (float)nn;
            qx = qx * k;
            qy = qy * k;
            qz = qz * k;
            qw = k * qw;
        }
        Quat q2;
        q2.x = ((qx * tw + tx * qw) - qz * ty) + qy * tz;
        q2.y = ((tx * qz + qy * tw) + qw * ty) - qx * tz;
        q2.z = ((qz * tw - tx * qy) + qx * ty) + qw * tz;
        q2.w = ((qw * tw - tx * qx) - qy * ty) - qz * tz;
        Quat q3 = q2;
        FUN_0099c1a0(&c, &q2, tangent);
        float half = ((float)angle * step) * 0.5f;
        float sn = (float)sin((double)half);
        float cs = (float)cos((double)half);
        c.x = c.x * sn;
        c.y = c.y * sn;
        c.z = c.z * sn;
        cur->x = ((q3.w * c.x + cs * q3.x) - c.z * q3.y) + c.y * q3.z;
        cur->y = ((c.y * q3.w + cs * q3.y) + c.z * q3.x) - q3.z * c.x;
        cur->z = ((c.z * q3.w - c.y * q3.x) + cs * q3.z) + q3.y * c.x;
        cur->w = ((cs * q3.w - c.x * q3.x) - c.y * q3.y) - c.z * q3.z;
        return;
    }
    cur->x = tx;
    cur->y = target->y;
    cur->z = target->z;
    cur->w = target->w;
}

// @ 0x009eddc0
void __stdcall FUN_009eddc0(ScaleOwner* so, SplineCtx* ctx)
{
    Vec3_s009e_ddc0 tmp;
    Vec3_s009e_ddc0 p0 = ctx->start->pos;
    Bone_s009e_ddc0* end = ctx->end;
    Vec3_s009e_ddc0 p1 = end->pos;

    // Start/end frames in world space.
    Vec3_s009e_ddc0 tan0 = *FUN_0099c1a0_s009e_ddc0(&tmp, &ctx->start->quat, &ctx->startTan);
    Vec3_s009e_ddc0 up0  = *FUN_0099c1a0_s009e_ddc0(&tmp, &ctx->start->quat, &ctx->startUp);
    Vec3_s009e_ddc0 vel0, acc0, vel1, acc1;
    if (ctx->count >= g_splineMinCount) {
        vel0 = *FUN_0099c1a0_s009e_ddc0(&tmp, &ctx->start->quat, &ctx->startVel);
        acc0 = *FUN_0099c1a0_s009e_ddc0(&tmp, &ctx->start->quat, &ctx->startAcc);
    }
    Vec3_s009e_ddc0 tan1 = *FUN_0099c1a0_s009e_ddc0(&tmp, &end->quat, &ctx->endTan);
    Vec3_s009e_ddc0 up1  = *FUN_0099c1a0_s009e_ddc0(&tmp, &end->quat, &ctx->endUp);
    if (ctx->count >= g_splineMinCount) {
        vel1 = *FUN_0099c1a0_s009e_ddc0(&tmp, &end->quat, &ctx->endVel);
        acc1 = *FUN_0099c1a0_s009e_ddc0(&tmp, &end->quat, &ctx->endAcc);
    }

    f32 blend = 1.0f;
    if ((ctx->flags & 0x800) == 0) {
        f32 dx = p1.x - p0.x, dy = p1.y - p0.y, dz = p1.z - p0.z;
        blend = Sqrt(dx * dx + dy * dy + dz * dz) / ctx->length;
        if (blend > 0.0f) {
            if (blend > 1.0f)
                blend = 1.0f;
        } else {
            blend = 0.0f;
        }
        vel0.x *= blend; vel0.y *= blend; vel0.z *= blend;
        vel1.x *= blend; vel1.y *= blend; vel1.z *= blend;
        acc0.x *= blend; acc0.y *= blend; acc0.z *= blend;
        acc1.x *= blend; acc1.y *= blend; acc1.z *= blend;
    }

    Mat3 basis;
    Vec3_s009e_ddc0 side;
    Quat_s009e_ddc0 q0, q1;

    if (ctx->count < g_splineMinCount) {
        // ---------------- linear blend of the two end frames ----------------
        side.x = up0.y * tan0.z - up0.z * tan0.y;
        side.y = up0.z * tan0.x - tan0.z * up0.x;
        side.z = tan0.y * up0.x - up0.y * tan0.x;
        SetColumns(basis, &up0.x, &tan0.x, &side.x);
        FUN_009a4f10(&q0, &basis);

        side.x = up1.y * tan1.z - up1.z * tan1.y;
        side.y = up1.z * tan1.x - tan1.z * up1.x;
        side.z = tan1.y * up1.x - up1.y * tan1.x;
        SetColumns(basis, &up1.x, &tan1.x, &side.x);
        FUN_009a4f10(&q1, &basis);

        if (((q1.x * q0.x + q1.w * q0.w) + q1.z * q0.z) + q1.y * q0.y < 0.0f) {
            q1.x = -q1.x; q1.y = -q1.y; q1.z = -q1.z; q1.w = -q1.w;
        }

        Bone_s009e_ddc0* b = ctx->start->next;
        if (b == end->next)
            return;
        do {
            f32 t = b->t;
            f32 s = 1.0f - t;
            f32 px = p0.x * s + p1.x * t;
            f32 pz = p0.z * s + p1.z * t;
            f32 py = p0.y * s + p1.y * t;
            f32 x = q0.x * s + q1.x * t;
            f32 w = q0.w * s + q1.w * t;
            f32 z = q0.z * s + q1.z * t;
            f32 y = q0.y * s + q1.y * t;
            f32 len = Sqrt(y * y + (z * z + (w * w + x * x)));
            if (len != 0.0f) {
                f32 inv = 1.0f / len;
                y *= inv; z *= inv; w *= inv; x = inv * x;
            }
            b->splinePos.x = px;
            b->splinePos.y = py;
            b->splinePos.z = pz;
            b->pos.x = ((((y * x - w * z) * 2.0f) * b->offset.y
                         + ((w * y + z * x) * 2.0f) * b->offset.z)
                        + (1.0f - (y * y + z * z) * 2.0f) * b->offset.x) + px;
            b->pos.y = ((((w * z + y * x) * 2.0f) * b->offset.x
                         + (1.0f - (z * z + x * x) * 2.0f) * b->offset.y)
                        + ((z * y - w * x) * 2.0f) * b->offset.z) + py;
            b->pos.z = ((((z * x - w * y) * 2.0f) * b->offset.x
                         + ((w * x + z * y) * 2.0f) * b->offset.y)
                        + (1.0f - (y * y + x * x) * 2.0f) * b->offset.z) + pz;
            Quat_s009e_ddc0 q = { x, y, z, w };
            QuatMul(b->quat, q, b->localRot);
            UpdatePivotPos(b, so);
            b->dirty = 1;
            b = b->next;
        } while (b != ctx->end->next);
        return;
    }

    // ---------------- quintic Hermite spline with transported frame ----------------
    Bone_s009e_ddc0* b = ctx->start->next;
    if (b != end->next) {
        do {
            f32 t = b->t;
            if (ctx->start->noEase == 0 && blend < 1.0f)
                t = (f32)pow((double)t, (double)blend);

            f32 t2 = t * t;
            f32 t3 = t2 * t;
            f32 t4 = t3 * t;
            f32 t5 = t4 * t;
            f32 t4x15 = t4 * 15.0f;

            // position basis
            f32 h1 = (t3 * 10.0f - t4x15) + t5 * 6.0f;
            f32 h0 = ((1.0f - t3 * 10.0f) + t4x15) - t5 * 6.0f;
            f32 h2 = ((t - t3 * 6.0f) + t4 * 8.0f) - t5 * 3.0f;
            f32 h3 = (t4 * 7.0f - t3 * 4.0f) - t5 * 3.0f;
            f32 h4 = (((t2 - t3 * 3.0f) + t4 * 3.0f) - t5) * 0.5f;
            f32 h5 = ((t3 - t4 * 2.0f) + t5) * 0.5f;
            Vec3_s009e_ddc0 sp;
            sp.x = ((((p0.x * h0 + p1.x * h1) + vel0.x * h2) + vel1.x * h3) + acc0.x * h4) + acc1.x * h5;
            sp.y = ((((p0.y * h0 + p1.y * h1) + vel0.y * h2) + vel1.y * h3) + acc0.y * h4) + acc1.y * h5;
            sp.z = ((((p0.z * h0 + p1.z * h1) + vel0.z * h2) + vel1.z * h3) + acc0.z * h4) + acc1.z * h5;

            // derivative basis
            f32 d1 = (t2 * 30.0f - t3 * 60.0f) + t4 * 30.0f;
            f32 d0 = (t3 * 60.0f - t2 * 30.0f) - t4 * 30.0f;
            f32 d2 = ((1.0f - t2 * 18.0f) + t3 * 32.0f) - t4x15;
            f32 d3 = (t3 * 28.0f - t2 * 12.0f) - t4x15;
            f32 d5 = ((t2 * 3.0f - t3 * 8.0f) + t4 * 5.0f) * 0.5f;
            f32 d4 = (((t * 2.0f - t2 * 9.0f) + t3 * 12.0f) - t4 * 5.0f) * 0.5f;
            Vec3_s009e_ddc0 dv;
            dv.x = ((((p0.x * d0 + p1.x * d1) + vel0.x * d2) + vel1.x * d3) + acc0.x * d4) + acc1.x * d5;
            dv.z = ((((p0.z * d0 + p1.z * d1) + vel0.z * d2) + vel1.z * d3) + acc0.z * d4) + acc1.z * d5;
            dv.y = ((((p0.y * d0 + p1.y * d1) + vel0.y * d2) + vel1.y * d3) + acc0.y * d4) + acc1.y * d5;

            f32 inv = 1.0f / (Sqrt(dv.z * dv.z + (dv.y * dv.y + dv.x * dv.x)) + 1e-08f);
            Vec3_s009e_ddc0 tan;
            tan.x = dv.x * inv;
            tan.z = inv * dv.z;
            tan.y = inv * dv.y;

            // rotation taking the previous tangent onto the new one
            f32 c = (tan.z * tan0.z + tan.y * tan0.y) + tan0.x * tan.x;
            f32 ax = tan.z * tan0.y - tan.y * tan0.z;
            f32 ay = tan0.z * tan.x - tan.z * tan0.x;
            f32 az = tan.y * tan0.x - tan0.y * tan.x;
            f32 s = Sqrt(ax * ax + (az * az + ay * ay));
            if (s != 0.0f) {
                f32 r = 1.0f / s;
                ax = r * ax;
                ay = ay * r;
                az = az * r;
            }
            Mat3 rot;
            if (s > 0.0f) {
                f32 omc = 1.0f - c;
                f32 azomc = az * omc;
                f32 ayomcax = (ay * omc) * ax;
                f32 ays = ay * s;
                f32 ayazomc = ay * azomc;
                f32 sax = s * ax;
                rot.m[0] = (1.0f - ax * ax) * c + ax * ax;
                rot.m[1] = ayomcax - az * s;
                rot.m[2] = ays + azomc * ax;
                rot.m[3] = az * s + ayomcax;
                rot.m[4] = (1.0f - ay * ay) * c + ay * ay;
                rot.m[5] = ayazomc - sax;
                rot.m[6] = azomc * ax - ays;
                rot.m[7] = sax + ayazomc;
                rot.m[8] = (1.0f - az * az) * c + az * az;
            } else if (c > 0.0f) {
                rot.m[0] = 1.0f; rot.m[1] = 0.0f; rot.m[2] = 0.0f;
                rot.m[3] = 0.0f; rot.m[4] = 1.0f; rot.m[5] = 0.0f;
                rot.m[6] = 0.0f; rot.m[7] = 0.0f; rot.m[8] = 1.0f;
            } else {
                // antiparallel: half turn about any axis perpendicular to tan0
                Vec3_s009e_ddc0 axis, other;
                axis.x = 0.0f; axis.y = 0.0f; axis.z = 0.0f;
                FUN_009a4a70(&tan0, &axis, &other);
                f32 x = axis.x, y = axis.y, z = axis.z;
                f32 xy2 = (y * x) * 2.0f;
                f32 y0 = y * 0.0f;
                f32 zx2 = (z * x) * 2.0f;
                f32 yz2 = (y * z) * 2.0f;
                rot.m[0] = x * x - (1.0f - x * x);
                rot.m[1] = xy2 - z * 0.0f;
                rot.m[3] = z * 0.0f + xy2;
                rot.m[4] = y * y - (1.0f - y * y);
                rot.m[5] = yz2 - x * 0.0f;
                rot.m[2] = y0 + zx2;
                rot.m[7] = x * 0.0f + yz2;
                rot.m[6] = zx2 - y0;
                rot.m[8] = z * z - (1.0f - z * z);
            }

            tan0 = tan;
            Vec3_s009e_ddc0 up;
            up.x = (up0.x * rot.m[0] + rot.m[2] * up0.z) + rot.m[1] * up0.y;
            up.y = (rot.m[3] * up0.x + rot.m[5] * up0.z) + rot.m[4] * up0.y;
            up.z = (rot.m[6] * up0.x + rot.m[8] * up0.z) + rot.m[7] * up0.y;
            up0 = up;

            b->splinePos = sp;
            side.x = up.y * tan.z - up.z * tan.y;
            side.y = up.z * tan.x - tan.z * up.x;
            side.z = tan.y * up.x - up.y * tan.x;
            SetColumns(basis, &up.x, &tan.x, &side.x);
            FUN_009a4f10(&q1, &basis);

            f32 ox = b->offset.x, oy = b->offset.y, oz = b->offset.z;
            b->pos.x = sp.x + ((oy * basis.m[1] + oz * basis.m[2]) + ox * basis.m[0]);
            b->pos.y = ((ox * basis.m[3] + oy * basis.m[4]) + oz * basis.m[5]) + sp.y;
            b->pos.z = ((ox * basis.m[6] + oy * basis.m[7]) + oz * basis.m[8]) + sp.z;
            QuatMul(b->quat, q1, b->localRot);
            UpdatePivotPos(b, so);
            b->dirty = 1;
            b = b->next;
        } while (b != ctx->end->next);
    }

    // ---------------- spread the remaining twist over the chain ----------------
    Vec3_s009e_ddc0 axis;
    axis.y = up0.z * up1.x - up1.z * up0.x;
    axis.x = up1.z * up0.y - up1.y * up0.z;
    axis.z = up1.y * up0.x - up0.y * up1.x;
    if (axis.x * axis.x + (axis.z * axis.z + axis.y * axis.y) > 1e-06) {
        Mat3 step;
        step.m[1] = 0.0f; step.m[2] = 0.0f; step.m[3] = 0.0f;
        step.m[5] = 0.0f; step.m[6] = 0.0f; step.m[7] = 0.0f;
        step.m[8] = 1.0f; step.m[4] = 1.0f; step.m[0] = 1.0f;
        double y = (axis.y * tan1.y + axis.z * tan1.z) + tan1.x * axis.x;
        double x = up1.x * up0.x + (up1.y * up0.y + up1.z * up0.z);
        step.RotateY((f32)(atan2(y, x) / ctx->count));
        Mat3 accum = step;

        Bone_s009e_ddc0* n = ctx->start->next;
        if (n == ctx->end->next)
            return;
        do {
            Mat3 local, conj, rq, rt, rm;
            QuatToMat3(local, n->localRot.x, n->localRot.y, n->localRot.z, n->localRot.w);
            FUN_009e5c30(&conj, &local, &accum);

            QuatToMat3(rq, n->quat.x, n->quat.y, n->quat.z, n->quat.w);
            // rt = rq * conj
            rt.m[0] = (conj.m[6] * rq.m[2] + conj.m[3] * rq.m[1]) + conj.m[0] * rq.m[0];
            rt.m[1] = (conj.m[7] * rq.m[2] + conj.m[4] * rq.m[1]) + conj.m[1] * rq.m[0];
            rt.m[2] = (conj.m[8] * rq.m[2] + conj.m[5] * rq.m[1]) + conj.m[2] * rq.m[0];
            rt.m[3] = (conj.m[6] * rq.m[5] + conj.m[3] * rq.m[4]) + conj.m[0] * rq.m[3];
            rt.m[4] = (conj.m[7] * rq.m[5] + conj.m[4] * rq.m[4]) + conj.m[1] * rq.m[3];
            rt.m[5] = (conj.m[8] * rq.m[5] + conj.m[5] * rq.m[4]) + conj.m[2] * rq.m[3];
            rt.m[6] = (conj.m[6] * rq.m[8] + conj.m[3] * rq.m[7]) + conj.m[0] * rq.m[6];
            rt.m[7] = (conj.m[7] * rq.m[8] + conj.m[4] * rq.m[7]) + conj.m[1] * rq.m[6];
            rt.m[8] = (conj.m[8] * rq.m[8] + conj.m[5] * rq.m[7]) + conj.m[2] * rq.m[6];
            // rm = rt * rq^T
            rm.m[0] = (rt.m[2] * rq.m[2] + rt.m[1] * rq.m[1]) + rq.m[0] * rt.m[0];
            rm.m[1] = (rt.m[2] * rq.m[5] + rt.m[1] * rq.m[4]) + rq.m[3] * rt.m[0];
            rm.m[2] = (rt.m[2] * rq.m[8] + rt.m[1] * rq.m[7]) + rq.m[6] * rt.m[0];
            rm.m[3] = (rt.m[5] * rq.m[2] + rt.m[4] * rq.m[1]) + rq.m[0] * rt.m[3];
            rm.m[4] = (rt.m[5] * rq.m[5] + rt.m[4] * rq.m[4]) + rq.m[3] * rt.m[3];
            rm.m[5] = (rt.m[5] * rq.m[8] + rt.m[4] * rq.m[7]) + rq.m[6] * rt.m[3];
            rm.m[6] = (rt.m[8] * rq.m[2] + rt.m[7] * rq.m[1]) + rq.m[0] * rt.m[6];
            rm.m[7] = (rt.m[8] * rq.m[5] + rt.m[7] * rq.m[4]) + rq.m[3] * rt.m[6];
            rm.m[8] = (rt.m[8] * rq.m[8] + rt.m[7] * rq.m[7]) + rq.m[6] * rt.m[6];

            f32 dx = n->pos.x - n->splinePos.x;
            f32 dz = n->pos.z - n->splinePos.z;
            f32 dy = n->pos.y - n->splinePos.y;
            f32 yz = dz * rm.m[5] + dy * rm.m[4];
            n->pos.y = n->splinePos.y + (yz + rm.m[3] * dx);
            n->pos.x = ((dx * rm.m[0] + dz * rm.m[2]) + dy * rm.m[1]) + n->splinePos.x;
            n->pos.z = n->splinePos.z + ((dz * rm.m[8] + dy * rm.m[7]) + rm.m[6] * dx);

            dx = n->pivotPos.x - n->splinePos.x;
            dy = n->pivotPos.y - n->splinePos.y;
            dz = n->pivotPos.z - n->splinePos.z;
            n->pivotPos.x = ((dz * rm.m[2] + dy * rm.m[1]) + dx * rm.m[0]) + n->splinePos.x;
            n->pivotPos.y = n->splinePos.y + ((dz * rm.m[5] + dy * rm.m[4]) + rm.m[3] * dx);
            n->pivotPos.z = n->splinePos.z + ((dz * rm.m[8] + dy * rm.m[7]) + rm.m[6] * dx);

            n->quat = *FUN_009a4f10(&q1, &rt);

            // accum = accum * step
            Mat3 next;
            next.m[0] = (accum.m[2] * step.m[6] + accum.m[1] * step.m[3]) + accum.m[0] * step.m[0];
            next.m[1] = (accum.m[2] * step.m[7] + accum.m[1] * step.m[4]) + accum.m[0] * step.m[1];
            next.m[2] = (accum.m[2] * step.m[8] + accum.m[1] * step.m[5]) + accum.m[0] * step.m[2];
            next.m[3] = (accum.m[5] * step.m[6] + accum.m[4] * step.m[3]) + accum.m[3] * step.m[0];
            next.m[4] = (accum.m[5] * step.m[7] + accum.m[4] * step.m[4]) + accum.m[3] * step.m[1];
            next.m[5] = (accum.m[5] * step.m[8] + accum.m[4] * step.m[5]) + accum.m[3] * step.m[2];
            next.m[6] = (accum.m[8] * step.m[6] + accum.m[7] * step.m[3]) + accum.m[6] * step.m[0];
            next.m[7] = (accum.m[8] * step.m[7] + accum.m[7] * step.m[4]) + accum.m[6] * step.m[1];
            next.m[8] = (accum.m[8] * step.m[8] + accum.m[7] * step.m[5]) + accum.m[6] * step.m[2];
            n = n->next;
            accum = next;
        } while (n != ctx->end->next);
    }
}

// @ 0x009f09a0
void __stdcall IKRigidFollow(IKCtx* ctx, Body* self)
{
    Vec3_s009f_09a0  sumGoal;                // a
    float weight;
    float ratio;
    Vec3_s009f_09a0  sumCur;                 // b
    sumGoal.x = 0.0f; sumGoal.y = 0.0f; sumGoal.z = 0.0f;
    sumCur.x = 0.0f;  sumCur.y = 0.0f;  sumCur.z = 0.0f;
    ratio = 0.0f;
    weight = 0.0f;

    switch (self->goal_mode & 7) {
    case 0:
        return;
    case 1:
    case 3: {
        uint32_t n = self->static_data->num_all_children;
        uint32_t start = self->static_data->first_child_bidx;
        uint32_t found = 0;
        for (uint32_t i = 0; i < n; ++i) {
            if (found >= self->goal_count)
                break;
            Body* other = &ctx->creature->bodies[start + i];
            if ((other->goal_mode & 7) == 0) {
                ++found;
                AccumulateReference(other, self, &ratio, &sumGoal, &sumCur, &weight);
            }
        }
        break;
    }
    case 2:
        AccumulateReference(&ctx->creature->bodies[self->goal_count], self, &ratio,
                            &sumGoal, &sumCur, &weight);
        break;
    }

    if (weight != 1.0f) {
        ratio = ratio / weight;
        float inv = 1.0f / (sqrtf(sumGoal.x * sumGoal.x + sumGoal.y * sumGoal.y +
                                  sumGoal.z * sumGoal.z) + 1e-08f);
        sumGoal.x = inv * sumGoal.x;
        sumGoal.y = sumGoal.y * inv;
        sumGoal.z = sumGoal.z * inv;
        inv = 1.0f / (sqrtf(sumCur.x * sumCur.x + sumCur.y * sumCur.y +
                            sumCur.z * sumCur.z) + 1e-08f);
        sumCur.x = inv * sumCur.x;
        sumCur.y = sumCur.y * inv;
        sumCur.z = sumCur.z * inv;
    }

    // R: rotation taking sumCur onto sumGoal
    float c = (sumCur.x * sumGoal.x + sumCur.z * sumGoal.z) + sumCur.y * sumGoal.y;
    Vec3_s009f_09a0 axis;
    axis.x = sumCur.y * sumGoal.z - sumCur.z * sumGoal.y;
    axis.y = sumCur.z * sumGoal.x - sumGoal.z * sumCur.x;
    axis.z = sumGoal.y * sumCur.x - sumCur.y * sumGoal.x;
    float s = sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    if (s != 0.0f) {
        float inv = 1.0f / s;
        axis.x = inv * axis.x;
        axis.y = inv * axis.y;
        axis.z = inv * axis.z;
    }
    Mat3_s009f_09a0 R;
    if (s > 0.0f) {
        float x = axis.x, y = axis.y, z = axis.z;
        float yy = y * y;
        float zz = z * z;
        float xx = x * x;
        R.m[0] = (1.0f - xx) * c + xx;
        float t = 1.0f - c;
        float txy = (t * y) * x;
        float zs = z * s;
        float tz = t * z;
        R.m[1] = txy - zs;
        R.m[3] = zs + txy;
        float tyz = y * tz;
        float ys = y * s;
        float tzx = tz * x;
        R.m[2] = ys + tzx;
        R.m[6] = tzx - ys;
        R.m[4] = (1.0f - yy) * c + yy;
        float xs = s * x;
        R.m[5] = tyz - xs;
        R.m[7] = xs + tyz;
        R.m[8] = (1.0f - zz) * c + zz;
    } else if (c > 0.0f) {
        R.m[0] = 1.0f; R.m[1] = 0.0f; R.m[2] = 0.0f;
        R.m[3] = 0.0f; R.m[4] = 1.0f; R.m[5] = 0.0f;
        R.m[6] = 0.0f; R.m[7] = 0.0f; R.m[8] = 1.0f;
    } else {
        Vec3_s009f_09a0 perp, other;
        perp.x = 0.0f; perp.y = 0.0f; perp.z = 0.0f;
        PerpPair(&sumCur, &perp, &other);
        R.SetAxisCosSin(perp, -1.0f, 0.0f);
    }

    // stretch: C = t*I + (ratio - t) * a (x) a ;  M = C * R
    float t = g_ikUseRatioScale ? g_ikRatioScale / ratio : 1.0f;
    float k = ratio - t;
    float v[3];
    v[0] = sumGoal.x * k;
    v[1] = sumGoal.y * k;
    v[2] = sumGoal.z * k;
    Mat3_s009f_09a0 O;
    for (uint32_t i = 0; i < 3; ++i) {
        float vi = v[i];
        O.m[i * 3 + 0] = vi * sumGoal.x;
        O.m[i * 3 + 1] = vi * sumGoal.y;
        O.m[i * 3 + 2] = vi * sumGoal.z;
    }
    Mat3_s009f_09a0 S;
    {
        float* r = S.m;
        int n = 3;
        do {
            r[0] = 0.0f; r[1] = 0.0f; r[2] = 0.0f;
            r += 3;
        } while (--n != 0);
    }
    S.m[0] = t; S.m[4] = t; S.m[8] = t;
    Mat3_s009f_09a0 C;
    for (int i = 0; i < 3; ++i) {
        C.m[i]     = S.m[i] + O.m[i];
        C.m[3 + i] = O.m[3 + i] + S.m[3 + i];
        C.m[6 + i] = O.m[6 + i] + S.m[6 + i];
    }
    Mat3_s009f_09a0 M;
    M.m[0] = (C.m[2] * R.m[6] + C.m[1] * R.m[3]) + C.m[0] * R.m[0];
    M.m[1] = (R.m[1] * C.m[0] + C.m[2] * R.m[7]) + C.m[1] * R.m[4];
    M.m[2] = (R.m[2] * C.m[0] + C.m[2] * R.m[8]) + C.m[1] * R.m[5];
    M.m[3] = (C.m[3] * R.m[0] + C.m[5] * R.m[6]) + C.m[4] * R.m[3];
    M.m[4] = (C.m[5] * R.m[7] + C.m[4] * R.m[4]) + C.m[3] * R.m[1];
    M.m[5] = (C.m[5] * R.m[8] + C.m[4] * R.m[5]) + C.m[3] * R.m[2];
    M.m[6] = (C.m[6] * R.m[0] + C.m[7] * R.m[3]) + C.m[8] * R.m[6];
    M.m[7] = (C.m[7] * R.m[4] + C.m[8] * R.m[7]) + C.m[6] * R.m[1];
    M.m[8] = (C.m[7] * R.m[5] + C.m[8] * R.m[8]) + C.m[6] * R.m[2];

    uint32_t n = self->static_data->num_all_children;
    uint32_t start = self->static_data->first_child_bidx;
    for (uint32_t i = 0; i < n; ++i) {
        Body* o = &ctx->creature->bodies[start + i];
        uint32_t mode = o->goal_mode & 7;
        if (mode == 0) {
            if ((uint8_t)(self->goal_mode & 7) == 2) {
                o->particle = o->particle_goal;
                o->particle_valid = 1;
                continue;
            }
        } else if (!(mode > 0 && mode <= 3)) {
            continue;
        }

        Vec3_s009f_09a0 d;
        if (o->particle_valid == 0) {
            d.x = o->particle_rest.x - self->particle_rest.x;
            d.y = o->particle_rest.y - self->particle_rest.y;
            d.z = o->particle_rest.z - self->particle_rest.z;
        } else {
            d.x = o->particle.x - self->particle.x;
            d.y = o->particle.y - self->particle.y;
            d.z = o->particle.z - self->particle.z;
        }

        float px, py, pz;
        if ((d.x * sumCur.x + d.z * sumCur.z) + d.y * sumCur.y < 0.0f) {
            float rx = (d.z * R.m[2] + d.y * R.m[1]) + d.x * R.m[0];
            float ry = (R.m[3] * d.x + d.z * R.m[5]) + d.y * R.m[4];
            float rz = (R.m[6] * d.x + d.z * R.m[8]) + d.y * R.m[7];
            if (ratio <= 1.0f) {
                o->particle.x = rx + self->particle_goal.x;
                o->particle.y = self->particle_goal.y + ry;
                o->particle.z = self->particle_goal.z + rz;
                o->particle_valid = 1;
                continue;
            }
            float f = (ratio > 2.0f) ? 1.0f : ratio - 1.0f;
            float proj = ((rx * sumGoal.x + rz * sumGoal.z) + ry * sumGoal.y) * f;
            px = (self->particle_goal.x + rx) - sumGoal.x * proj;
            py = (self->particle_goal.y + ry) - sumGoal.y * proj;
            pz = (self->particle_goal.z + rz) - sumGoal.z * proj;
        } else {
            float rx = (d.x * M.m[0] + d.z * M.m[2]) + d.y * M.m[1];
            float ry = (M.m[3] * d.x + d.z * M.m[5]) + d.y * M.m[4];
            float rz = (M.m[6] * d.x + d.z * M.m[8]) + d.y * M.m[7];
            o->particle.x = rx + self->particle_goal.x;
            o->particle.y = self->particle_goal.y + ry;
            o->particle.z = self->particle_goal.z + rz;
            if (o->push_out == 0 || !(ratio < 1.0f)) {
                o->particle_valid = 1;
                continue;
            }
            float proj = (rx * sumGoal.x + rz * sumGoal.z) + ry * sumGoal.y;
            rx = rx - sumGoal.x * proj;
            ry = ry - sumGoal.y * proj;
            rz = rz - sumGoal.z * proj;
            float inv = 1.0f / (sqrtf(rx * rx + ry * ry + rz * rz) + 1e-08f);
            float rad = o->radius;
            Vec3_s009f_09a0 push;
            push.x = (rx * inv) * rad;
            push.y = (ry * inv) * rad;
            push.z = (rz * inv) * rad;
            float w = FUN_009b01e0(0.0f, g_ikPushRange, 1.0f - ratio);
            px = push.x * w + o->particle.x;
            py = push.y * w + o->particle.y;
            pz = push.z * w + o->particle.z;
        }
        o->particle.z = pz;
        o->particle.y = py;
        o->particle.x = px;
        o->particle_valid = 1;
    }
}

// @ 0x009f1990
void __thiscall IKContext::Update(IKParticle* p)
{
    float t4c, t30, t34, t38;
    Vec3_s009f_1990 v1;

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
        Vec3_s009f_1990 c;
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
            Vec3_s009f_1990 n;
            float d;
            if (p->hasPlane == 0) {
                n = axis;
                d = world->scale * p->body->radiusScale + this->d;
            } else {
                n = p->planeP;
                d = (p->planeN.z * n.z + p->planeN.y * n.y) + p->planeN.x * n.x;
            }
            float sc = world->scale;
            Vec3_s009f_1990 loc;
            loc.x = p->body->offset[0] * sc;
            loc.y = p->body->offset[1] * sc;
            loc.z = p->body->offset[2] * sc;
            Vec3_s009f_1990* r = FUN_0099c1a0_s009f_1990(&v1, &p->q, &loc);
            d = ((r->z * n.z + r->y * n.y) + n.x * r->x) + d;
            if (((p->pos.z * n.z + p->pos.y * n.y) + n.x * p->pos.x) < d) {
                Vec3_s009f_1990 a = parent->pos;
                c.x = p->pos.x - a.x;
                c.y = p->pos.y - a.y;
                c.z = p->pos.z - a.z;
                float proj = (c.z * n.z + c.y * n.y) + c.x * n.x;
                float blend = FUN_009b01e0(t4c * -0.9396926f, t4c * -0.70710677f, proj);
                Vec3_s009f_1990 sl;
                if (blend > 0.0f) {
                    Vec3_s009f_1990 tmp;
                    Vec3_s009f_1990* s = FUN_009ed8c0(&v1, &n, &a, &tmp, d);
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
                        Vec3_s009f_1990* s = FUN_009ed8c0(&c, &n, &a, &sl, d);
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

            Vec3_s009f_1990 d1, e1, ax;
            Quat_s009f_1990 qq;
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
                Vec3_s009f_1990 g;
                g.x = top2->pos.x - p->pos.x;
                g.y = top2->pos.y - p->pos.y;
                g.z = top2->pos.z - p->pos.z;
                e1.x = top2->rot.x - p->rot.x;
                e1.y = top2->rot.y - p->rot.y;
                e1.z = top2->rot.z - p->rot.z;
                Vec3_s009f_1990 h;
                FUN_0099c1a0_s009f_1990(&h, &qq, &e1);
                float s1 = ((h.x * g.x + h.z * g.z) + h.y * g.y) -
                           ((h.x * d1.x + h.z * d1.z) + h.y * d1.y) *
                           ((g.x * d1.x + g.z * d1.z) + g.y * d1.y);
                float s2 = ((h.z * d1.y - h.y * d1.z) * g.x +
                            (h.y * d1.x - d1.y * h.x) * g.z) +
                           (d1.z * h.x - h.z * d1.x) * g.y;
                float m = s2 * s2 + s1 * s1;
                if (1e-05f < m) {
                    float y = rsqrt_fast(m);
                    Quat_s009f_1990 q2;
                    Quat_s009f_1990* r = q2.FromAxisSC(&d1, y * s1, y * s2, 0);
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

            Quat_s009f_1990* R = rootQuat;
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
        Vec3_s009f_1990 loc;
        loc.x = b->offset[0] * sc;
        loc.y = b->offset[1] * sc;
        loc.z = b->offset[2] * sc;
        Vec3_s009f_1990* r = FUN_0099c1a0_s009f_1990(&v1, &p->q, &loc);
        float ry = r->y, rz = r->z;
        p->pivot.x = p->pos.x - r->x;
        p->pivot.y = p->pos.y - ry;
        p->pivot.z = p->pos.z - rz;
        p->dirty = 1;
    }
}
