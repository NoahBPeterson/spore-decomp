// Slice s009eddc0 (batch big0, op1_big slice 12) - 0x009eddc0, 11221 bytes.
//
// Bone-chain spline solver.  ctx->start and ctx->end are two bones of an intrusive
// bone list (next at +8); every bone strictly after `start` up to and including
// `end` is re-posed along a curve between the two:
//
//  * ctx->count <  g_splineMinCount: linear blend.  Each bone's parameter t (+0x254)
//    lerps position and the (sign-aligned) frame quaternions of the two ends.
//  * otherwise: quintic Hermite spline (positions, end tangents +0x4c/+0x1c and
//    end accelerations +0x58/+0x28, all rotated into world by the end bones' quats)
//    with a rotation-minimising frame carried bone to bone (Rodrigues rotation from
//    the previous tangent to the new one).  Afterwards the remaining twist between
//    the propagated up vector and the end bone's up vector is spread evenly over the
//    chain (RotateY by angle/count, accumulated per bone, conjugated into each
//    bone's local frame and applied about the bone's spline point).
//
// Module is /arch:SSE /fp:fast (inline fsqrt/fpatan, fsin/fcos in Matrix3::RotateY).
//
// @ 0x009eddc0

#include <math.h>
#pragma intrinsic(sqrt, atan2, pow)

typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;

struct Vec3 { f32 x, y, z; };
struct Quat { f32 x, y, z, w; };

// Row-major 3x3 (m[row*3+col]).
struct Mat3 {
    f32 m[9];
    void __thiscall RotateY(f32 angle);                 // 0x009e5f50
};

extern "C" {
    Vec3* __cdecl FUN_0099c1a0(Vec3* out, const Quat* q, const Vec3* v);     // q.Rotate(v)
    Quat* __cdecl FUN_009a4f10(Quat* out, const Mat3* m);                    // Quat from Mat3
    void  __cdecl FUN_009a4a70(const Vec3* v, Vec3* perpA, Vec3* perpB);     // orthonormal basis
    void  __cdecl FUN_009e5c30(Mat3* out, const Mat3* a, const Mat3* b);     // a^T-conjugation of b
}
extern i32 g_splineMinCount;    // DAT_01550a3c

struct BoneOwner {              // *bone
    u8  pad0[0x144];
    Vec3 pivot;                 // +0x144
};

struct Bone {
    BoneOwner* owner;           // +0x000
    u8  pad4[4];
    Bone* next;                 // +0x008
    u8  padc[0x38 - 0xc];
    u8  dirty;                  // +0x038
    u8  pad39[0x190 - 0x39];
    Vec3 pivotPos;              // +0x190  pos - quat.Rotate(owner->pivot * scale)
    Quat quat;                  // +0x19c  world orientation
    Vec3 pos;                   // +0x1b0  world position
    u8  pad1bc[0x244 - 0x1bc];
    i32 noEase;                 // +0x244  (read on ctx->start)
    u8  pad248[0x254 - 0x248];
    f32 t;                      // +0x254  curve parameter
    Vec3 offset;                // +0x258  local offset from the curve point
    Vec3 splinePos;             // +0x264  point on the curve
    Quat localRot;              // +0x270  local rotation relative to the curve frame
};

struct SplineCtx {
    Bone* end;                  // +0x00
    Bone* start;                // +0x04
    u8  pad8[0x1c - 0x8];
    Vec3 endVel;                // +0x1c  (end-bone space)
    Vec3 endAcc;                // +0x28
    Vec3 endTan;                // +0x34
    Vec3 endUp;                 // +0x40
    Vec3 startVel;              // +0x4c  (start-bone space)
    Vec3 startAcc;              // +0x58
    Vec3 startTan;              // +0x64
    Vec3 startUp;               // +0x70
    u8  pad7c[0x94 - 0x7c];
    u32 flags;                  // +0x94  0x800: do not scale end derivatives by distance
    u8  pad98[0xc8 - 0x98];
    f32 length;                 // +0xc8
    i32 count;                  // +0xcc
};

struct ScaleSrc { u8 pad[0x70]; f32 scale; };
struct ScaleOwner { ScaleSrc* src; };

static __forceinline f32 Sqrt(f32 v) { return (f32)sqrt((double)v); }

// Matrix whose columns are a, b, c (element-wise loop, as in the original).
static __forceinline void SetColumns(Mat3& m, const f32* a, const f32* b, const f32* c)
{
    for (int i = 0; i < 3; i++) {
        m.m[i * 3 + 0] = a[i];
        m.m[i * 3 + 1] = b[i];
        m.m[i * 3 + 2] = c[i];
    }
}

static __forceinline void QuatMul(Quat& o, const Quat& q, const Quat& r)
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

// bone->pivotPos = bone->pos - bone->quat.Rotate(owner->pivot * scale)
static __forceinline void UpdatePivotPos(Bone* b, ScaleOwner* so)
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

// @ 0x009eddc0
void __stdcall FUN_009eddc0(ScaleOwner* so, SplineCtx* ctx)
{
    Vec3 tmp;
    Vec3 p0 = ctx->start->pos;
    Bone* end = ctx->end;
    Vec3 p1 = end->pos;

    // Start/end frames in world space.
    Vec3 tan0 = *FUN_0099c1a0(&tmp, &ctx->start->quat, &ctx->startTan);
    Vec3 up0  = *FUN_0099c1a0(&tmp, &ctx->start->quat, &ctx->startUp);
    Vec3 vel0, acc0, vel1, acc1;
    if (ctx->count >= g_splineMinCount) {
        vel0 = *FUN_0099c1a0(&tmp, &ctx->start->quat, &ctx->startVel);
        acc0 = *FUN_0099c1a0(&tmp, &ctx->start->quat, &ctx->startAcc);
    }
    Vec3 tan1 = *FUN_0099c1a0(&tmp, &end->quat, &ctx->endTan);
    Vec3 up1  = *FUN_0099c1a0(&tmp, &end->quat, &ctx->endUp);
    if (ctx->count >= g_splineMinCount) {
        vel1 = *FUN_0099c1a0(&tmp, &end->quat, &ctx->endVel);
        acc1 = *FUN_0099c1a0(&tmp, &end->quat, &ctx->endAcc);
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
    Vec3 side;
    Quat q0, q1;

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

        Bone* b = ctx->start->next;
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
            Quat q = { x, y, z, w };
            QuatMul(b->quat, q, b->localRot);
            UpdatePivotPos(b, so);
            b->dirty = 1;
            b = b->next;
        } while (b != ctx->end->next);
        return;
    }

    // ---------------- quintic Hermite spline with transported frame ----------------
    Bone* b = ctx->start->next;
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
            Vec3 sp;
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
            Vec3 dv;
            dv.x = ((((p0.x * d0 + p1.x * d1) + vel0.x * d2) + vel1.x * d3) + acc0.x * d4) + acc1.x * d5;
            dv.z = ((((p0.z * d0 + p1.z * d1) + vel0.z * d2) + vel1.z * d3) + acc0.z * d4) + acc1.z * d5;
            dv.y = ((((p0.y * d0 + p1.y * d1) + vel0.y * d2) + vel1.y * d3) + acc0.y * d4) + acc1.y * d5;

            f32 inv = 1.0f / (Sqrt(dv.z * dv.z + (dv.y * dv.y + dv.x * dv.x)) + 1e-08f);
            Vec3 tan;
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
                Vec3 axis, other;
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
            Vec3 up;
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
    Vec3 axis;
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

        Bone* n = ctx->start->next;
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
