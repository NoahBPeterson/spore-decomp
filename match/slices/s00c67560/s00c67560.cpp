// Slice s00c67560 -- camera ring controller update (0x00c678f0, 2010 bytes).
//
// Reconstructs the controller's target orientation from the current camera ray and the tracked
// target position: it picks the point on a plane through the target (normal = direction from the
// camera to the target, or the controller axis when they are nearly parallel), converts the in-plane
// offset to an angle, rotates the stored direction vector by it, then composes the resulting
// rotation with the stored base quaternion, normalizes, and writes it to the output quaternion (and
// notifies the controller) only if it changed.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (x87 sqrt/sin/cos/fabs, SSE float math).
#include "types.h"

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, sin, cos, fabs)

#define P4(n) virtual void p##n##a(); virtual void p##n##b(); virtual void p##n##c(); virtual void p##n##d();

struct V3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct V3c {
    float x, y, z;
    V3c(const V3& o) : x(o.x), y(o.y), z(o.z) {}
};

static inline float fabsf_(float v) { return (float)fabs((double)v); }

struct Viewer {
    void GetCameraRay(V3* origin, V3* dir);               // 0x007c4900 (ret 8)
};
struct AppObj {
    P4(0) P4(1) P4(2) P4(3) P4(4)
    virtual void p5a(); virtual void p5b();
    virtual Viewer* GetViewer();                          // +0x58
};
AppObj* AppGet();                                         // 0x0067dd10 (SP::App)

V3* __cdecl RotateByQuat(V3* out, const V3* v, const Quat* q);   // 0x0059aed0
float __cdecl AngleAroundAxis(const V3* a, const V3* b, const V3* axis);   // 0x006994a0 (result in st0)

// Embedded object at +0x34 with a vtable; slot 11 (+0x2c) returns its position.
struct TargetObj {
    P4(0) P4(1) virtual void p2a(); virtual void p2b(); virtual void p2c();
    virtual const V3* GetPosition();                      // +0x2c
};
struct ConstrainObj {
    V3* Apply(V3* out, const V3* in);                     // 0x00c650d0 (ret 8)
};

struct Ctrl {
    uint8_t pad00[0x34];
    TargetObj mTarget;               // +0x34
    uint8_t pad38[0x108 - 0x38];
    V3 mFocus;                       // +0x108
    uint8_t pad114[0x118 - 0x114];
    ConstrainObj mConstrain;         // +0x118
    uint8_t pad11c[0x170 - 0x11c];
    V3 mAxis;                        // +0x170
    V3 mDirRef;                      // +0x17c
    Quat mBase;                      // +0x188
    uint8_t pad198[0x1a4 - 0x198];
    Quat mOut;                       // +0x1a4
    float mScaleA;                   // +0x1b4
    uint8_t pad1b8[0x1c0 - 0x1b8];
    float mScaleB;                   // +0x1c0

    void MarkChanged();              // 0x00c66c10

    void Update();
};

// @ 0x00c678f0
void Ctrl::Update()
{
    V3 origin, dir;
    AppGet()->GetViewer()->GetCameraRay(&origin, &dir);

    const V3* tp = mTarget.GetPosition();
    V3 d;
    d.y = tp->y - origin.y;
    d.z = tp->z - origin.z;
    d.x = tp->x - origin.x;
    float inv = 1.0f / (float)sqrt((double)(d.x * d.x + d.z * d.z + d.y * d.y));
    d.x = inv * d.x;
    d.z = d.z * inv;
    d.y = d.y * inv;
    float dot = (mAxis.z * d.z + mAxis.y * d.y) + mAxis.x * d.x;

    static float cosLimit = (float)cos(1.2566370517015457);

    V3 res;
    V3 scratch;
    if (fabsf_(dot) < cosLimit) {
        V3 c;
        c.x = mAxis.z * d.y - mAxis.y * d.z;
        c.z = mAxis.y * d.x - mAxis.x * d.y;
        c.y = mAxis.x * d.z - mAxis.z * d.x;
        float inv2 = 1.0f / (float)sqrt((double)(c.x * c.x + c.z * c.z + c.y * c.y));
        c.x = inv2 * c.x;
        c.y = c.y * inv2;
        c.z = c.z * inv2;
        const V3* p = mTarget.GetPosition();
        V3 r;
        r.x = p->x - mFocus.x;
        r.z = p->z - mFocus.z;
        r.y = p->y - mFocus.y;
        float num = -((r.x * d.x + r.z * d.z) + r.y * d.y);
        float den = (dir.x * d.x + dir.z * d.z) + dir.y * d.y;
        float t = dot;
        if (den != 0.0f)
            t = -((((d.x * origin.x + d.z * origin.z) + d.y * origin.y) + num) / den);
        V3 h;
        h.x = dir.x * t + origin.x;
        h.y = dir.y * t + origin.y;
        h.z = dir.z * t + origin.z;
        V3 rel;
        rel.x = h.x - r.x;
        rel.y = h.y - r.y;
        rel.z = h.z - r.z;
        float ang = ((rel.z * c.z + rel.y * c.y) + rel.x * c.x) * 1.5707964f / (mScaleB + mScaleA) * 0.5f;
        float s = (float)sin((double)ang);
        float cw = (float)cos((double)ang);
        V3c ax(mAxis);
        Quat q;
        q.x = ax.x * s;
        q.y = ax.y * s;
        q.z = ax.z * s;
        q.w = cw;
        const V3* rot = RotateByQuat(&scratch, &mDirRef, &q);
        res.x = rot->x;
        res.y = rot->y;
        res.z = rot->z;
    } else {
        const V3* p = mTarget.GetPosition();
        float nn = -((p->z * mAxis.z + p->y * mAxis.y) + p->x * mAxis.x);
        float den = (mAxis.z * dir.z + mAxis.y * dir.y) + mAxis.x * dir.x;
        float t = dot;
        if (den != 0.0f)
            t = -((((mAxis.x * origin.x + mAxis.z * origin.z) + mAxis.y * origin.y) + nn) / den);
        V3 h;
        h.x = dir.x * t + origin.x;
        h.y = dir.y * t + origin.y;
        h.z = dir.z * t + origin.z;
        const V3* p2 = mTarget.GetPosition();
        V3 e;
        e.x = h.x - p2->x;
        e.z = h.z - p2->z;
        e.y = h.y - p2->y;
        float inv3 = 1.0f / (float)sqrt((double)(e.x * e.x + e.z * e.z + e.y * e.y + 1e-8f));
        scratch.x = inv3 * e.x;
        scratch.y = e.y * inv3;
        scratch.z = e.z * inv3;
        res = scratch;
    }

    res = *mConstrain.Apply(&scratch, &res);

    float half = AngleAroundAxis(&mDirRef, &res, &mAxis) * 0.5f;
    float s2 = (float)sin((double)half);
    float w = (float)cos((double)half);
    float vx = s2 * mAxis.x;
    float vy = mAxis.y * s2;
    float vz = mAxis.z * s2;
    float qx = mBase.x, qy = mBase.y, qz = mBase.z, qw = mBase.w;
    Quat R;
    R.x = (w * qx + vx * qw) + (qz * vy - qy * vz);
    R.y = (w * qy + vy * qw) + (vz * qx - qz * vx);
    R.z = (w * qz + vz * qw) + (qy * vx - vy * qx);
    R.w = w * qw - ((qz * vz + qy * vy) + qx * vx);
    float inv4 = 1.0f / (float)sqrt((double)(R.w * R.w + R.x * R.x + R.y * R.y + R.z * R.z + 1e-8f));
    Quat N;
    N.x = inv4 * R.x;
    N.y = inv4 * R.y;
    N.z = inv4 * R.z;
    N.w = R.w * inv4;
    if (mOut.x != N.x || mOut.y != N.y || mOut.z != N.z || mOut.w != N.w) {
        mOut = N;
        MarkChanged();
    }
}
