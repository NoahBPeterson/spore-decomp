// Slice s009ec360 -- 0x009ec360 (1886 bytes, ret 8): nSPCreatureAnim IK solver, "apply constraint
// rotation" helper (retail-only; called from IkSolver::UpdateBone 0x009ecac0 as FUN_009ec360).
//
// Register convention in the original: EAX = bone, ESI = target quaternion, stack = (tangent, up)
// vectors, callee pops 8.  Modeled here as four ordinary leading arguments (cdecl), exactly as the
// caller slice s009ecac0 declares it.
//
// What it does: the bone's current orientation (quat at +0x19c) is turned towards the target
// quaternion, limited by the bone's turn limit (+0x23c).
//   * limit <= 0, or the limited step <= 1e-5: the quaternion simply becomes the target.
//   * otherwise the shortest rotation r taking the current tangent direction to the target's is built
//     as a normalized (axis*|axis|, 1 + dot) quaternion (axis length through the 0x5f375a86 fast
//     reciprocal-square-root with two Newton steps), and T' = r * target is formed.  A smoothstep
//     of cos-window [-0.766, -0.1736] on the dot of (current * up) and (T' * up) scales the limit;
//     when the scaled limit is positive, the rotation r is scaled towards identity by it, composed
//     with the target again, and the result is blended in around the tangent axis by
//     sin/cos(atan2(triple product, dot) * limit * 0.5).  When the scale is not positive the
//     quaternion is set to the target.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (x87 fsin/fcos/fpatan/fsqrt inline, SSE for the rest).
#include <math.h>
#pragma intrinsic(sin, cos, atan2, sqrt)

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

struct Bone {
    char pad000[0x19c];
    Quat quat;                  // +0x19c
    char pad1ac[0x23c - 0x1ac];
    float turnLimit;            // +0x23c
};

extern "C" {
    Vec3* __cdecl FUN_0099c1a0(Vec3* out, const Quat* q, const Vec3* v);   // QuaternionVectorTransform
    float __cdecl FUN_009b01e0(float a, float b, float t);                  // smoothstep(a, b, t)
}

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
