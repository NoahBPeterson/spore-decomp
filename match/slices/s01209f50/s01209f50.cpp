// Spore / Havok math + swept-transform slice s01209f50.
// Reconstructed from the PE disassembly; x87 code is kept in the same
// expression shape as the original so /O2 reproduces the FP stack order.
#include "types.h"
#include <math.h>

// ------------------------------------------------------------------ layout
struct hkQuaternion;
struct hkRotation;

struct __declspec(align(16)) hkVector4 { float f[4]; };
struct __declspec(align(16)) hkQuaternion { float f[4]; void set(const hkRotation& r); };      // 0x1082490
struct hkRotation  { float f[12]; void set(const hkQuaternion& q); };    // 0x10824a0
struct hkTransform {
    hkRotation m_rotation;      // +0x00
    hkVector4  m_translation;   // +0x30
    void assign(const hkTransform& t);                                   // 0x1088410
};
struct hkSweptTransform {
    hkVector4    m_centerOfMass0;   // +0x00
    hkVector4    m_centerOfMass1;   // +0x10
    hkQuaternion m_rotation0;       // +0x20
    hkQuaternion m_rotation1;       // +0x30
    hkVector4    m_translation;     // +0x40
    void initSweptTransform(const hkVector4& p, const hkQuaternion& q);
};
struct hkMotionState {
    hkTransform      m_transform;       // +0x00
    hkSweptTransform m_swept;           // +0x40
    hkVector4        m_linearVelocity;  // +0x90
    float            m_fa0;             // +0xa0
    void initMotionState(const hkVector4& p, const hkQuaternion& q);
};

struct hkSweptTransformUtil {
    static void lerp2Ha(const hkSweptTransform& s, float t0, float t1, hkTransform& out);
    static void backStepMotionState(float time, hkMotionState& ms);
    static void freezeMotionState(float time, hkMotionState& ms);
    static void warpTo(const hkVector4& p, const hkQuaternion& q, hkMotionState& ms);
    static void warpTo(const hkTransform& t, hkMotionState& ms);
    static void warpToPosition(const hkVector4& p, hkMotionState& ms);
    static void warpToRotation(const hkQuaternion& q, hkMotionState& ms);
};

struct hkMath {
    static float hkFloor(float x);
    static int   hkFloatToInt(float x);
    static float atan2fApproximation(float a, float b);
};

// ================================================================== 0x01209f50
// void hkSweptTransformUtil::lerp2Ha(const hkSweptTransform&, float, float, hkTransform&)
// @ 0x01209f50
void hkSweptTransformUtil::lerp2Ha(const hkSweptTransform& s, float t0, float t1,
                                   hkTransform& out)
{
    float x0 = s.m_rotation0.f[0];
    float y0 = s.m_rotation0.f[1];
    float z0 = s.m_rotation0.f[2];
    float w0 = s.m_rotation0.f[3];
    float phase = ((t0 - s.m_centerOfMass0.f[3]) + t1) * s.m_centerOfMass1.f[3];
    float x1 = s.m_rotation1.f[0];
    float y1 = s.m_rotation1.f[1];
    float z1 = s.m_rotation1.f[2];
    float w1 = s.m_rotation1.f[3];

    float sx = x1 + x0;
    float sy = y1 + y0;
    float sz = z1 + z0;
    float sw = w1 + w0;
    float mag = sy * sy + (sx * sx + (sz * sz + sw * sw));
    float corr = 0.75f - mag * 0.125f;
    corr = (1.5f - ((corr * corr) * mag) * 0.5f) * corr;

    float a = phase + phase;
    float qx, qy, qz, qw, v;
    if (0.5f <= phase) {
        a = a - 1.0f;
        v = 1.0f - a;
        qx = a * x1 + v * (sx * corr);
        qy = v * (sy * corr) + y1 * a;
        qz = z1 * a + (sz * corr) * v;
        qw = w1 * a + v * (sw * corr);
    } else {
        v = 1.0f - a;
        qx = v * x0 + a * (sx * corr);
        qy = a * (sy * corr) + y0 * v;
        qz = z0 * v + (sz * corr) * a;
        qw = w0 * v + a * (sw * corr);
    }

    float len = qy * qy + (qx * qx + (qz * qz + qw * qw));
    float inv = (len == 0.0f) ? 0.0f : 1.0f / sqrtf(len);
    hkQuaternion q;
    q.f[0] = inv * qx;
    q.f[1] = qy * inv;
    q.f[2] = qz * inv;
    q.f[3] = inv * qw;
    out.m_rotation.set(q);

    float invp = 1.0f - phase;
    out.m_translation.f[0] = phase * s.m_centerOfMass1.f[0] + invp * s.m_centerOfMass0.f[0];
    out.m_translation.f[1] = phase * s.m_centerOfMass1.f[1] + invp * s.m_centerOfMass0.f[1];
    out.m_translation.f[2] = phase * s.m_centerOfMass1.f[2] + invp * s.m_centerOfMass0.f[2];
    out.m_translation.f[3] = invp * s.m_centerOfMass0.f[3] + phase * s.m_centerOfMass1.f[3];

    float rx = s.m_translation.f[0];
    float ry = s.m_translation.f[1];
    float rz = s.m_translation.f[2];
    out.m_translation.f[0] = out.m_translation.f[0] -
        (rx * out.m_rotation.f[0] + (ry * out.m_rotation.f[4] + rz * out.m_rotation.f[8]));
    out.m_translation.f[1] = out.m_translation.f[1] -
        (rx * out.m_rotation.f[1] + (ry * out.m_rotation.f[5] + rz * out.m_rotation.f[9]));
    out.m_translation.f[2] = out.m_translation.f[2] -
        (rx * out.m_rotation.f[2] + (ry * out.m_rotation.f[6] + rz * out.m_rotation.f[10]));
}

// ================================================================== 0x0120a260
// void hkSweptTransformUtil::backStepMotionState(float, hkMotionState&)
// @ 0x0120a260
void hkSweptTransformUtil::backStepMotionState(float time, hkMotionState& ms)
{
    hkSweptTransform& s = ms.m_swept;
    float t = (time - s.m_centerOfMass0.f[3]) * s.m_centerOfMass1.f[3];
    if (t <= 1.1920929e-07f)
        t = 1.1920929e-07f;

    float x0 = s.m_rotation0.f[0];
    float y0 = s.m_rotation0.f[1];
    float z0 = s.m_rotation0.f[2];
    float w0 = s.m_rotation0.f[3];
    float x1 = s.m_rotation1.f[0];
    float y1 = s.m_rotation1.f[1];
    float z1 = s.m_rotation1.f[2];
    float w1 = s.m_rotation1.f[3];
    float invdt = s.m_centerOfMass1.f[3];

    float sx = x1 + x0;
    float sy = y1 + y0;
    float sz = z1 + z0;
    float sw = w1 + w0;
    float mag = sy * sy + (sx * sx + (sz * sz + sw * sw));
    float corr = 0.75f - mag * 0.125f;
    corr = (1.5f - ((corr * corr) * mag) * 0.5f) * corr;

    s.m_rotation1.f[0] = sx * corr;
    s.m_rotation1.f[1] = sy * corr;
    s.m_rotation1.f[2] = sz * corr;
    s.m_rotation1.f[3] = sw * corr;

    float a = t + t;
    float v, wsrc;
    if (0.5f <= t) {
        float u = a - 1.0f;
        v = 1.0f - u;
        s.m_rotation1.f[0] = u * x1 + v * s.m_rotation1.f[0];
        s.m_rotation1.f[1] = v * s.m_rotation1.f[1] + y1 * u;
        s.m_rotation1.f[2] = z1 * u + v * s.m_rotation1.f[2];
        wsrc = w1;
        v = v * s.m_rotation1.f[3];
        s.m_rotation1.f[3] = wsrc * u + v;
    } else {
        v = 1.0f - a;
        s.m_rotation1.f[0] = v * x0 + a * s.m_rotation1.f[0];
        s.m_rotation1.f[1] = a * s.m_rotation1.f[1] + y0 * v;
        s.m_rotation1.f[2] = z0 * v + a * s.m_rotation1.f[2];
        wsrc = w0;
        s.m_rotation1.f[3] = wsrc * (1.0f - a) + a * s.m_rotation1.f[3];
    }

    float len = s.m_rotation1.f[1] * s.m_rotation1.f[1] +
        (s.m_rotation1.f[0] * s.m_rotation1.f[0] +
         (s.m_rotation1.f[2] * s.m_rotation1.f[2] + s.m_rotation1.f[3] * s.m_rotation1.f[3]));
    if (len == 0.0f)
        len = 0.0f;
    else
        len = 1.0f / sqrtf(len);
    s.m_rotation1.f[0] = len * s.m_rotation1.f[0];
    s.m_rotation1.f[1] = len * s.m_rotation1.f[1];
    s.m_rotation1.f[2] = len * s.m_rotation1.f[2];
    s.m_rotation1.f[3] = len * s.m_rotation1.f[3];

    float inv = 1.0f - t;
    s.m_centerOfMass1.f[0] = t * s.m_centerOfMass1.f[0] + inv * s.m_centerOfMass0.f[0];
    s.m_centerOfMass1.f[1] = t * s.m_centerOfMass1.f[1] + inv * s.m_centerOfMass0.f[1];
    s.m_centerOfMass1.f[2] = t * s.m_centerOfMass1.f[2] + inv * s.m_centerOfMass0.f[2];
    s.m_centerOfMass1.f[3] = inv * s.m_centerOfMass0.f[3] + t * s.m_centerOfMass1.f[3];
    s.m_centerOfMass1.f[3] = invdt / t;

    ms.m_linearVelocity.f[0] = t * ms.m_linearVelocity.f[0];
    ms.m_linearVelocity.f[1] = t * ms.m_linearVelocity.f[1];
    ms.m_linearVelocity.f[2] = t * ms.m_linearVelocity.f[2];
    ms.m_linearVelocity.f[3] = t * ms.m_linearVelocity.f[3];

    ms.m_transform.m_rotation.set(s.m_rotation1);

    float tx = s.m_translation.f[0];
    float ty = s.m_translation.f[1];
    float tz = s.m_translation.f[2];
    ms.m_transform.m_translation.f[0] = s.m_centerOfMass1.f[0] -
        (tx * ms.m_transform.m_rotation.f[0] +
         (ty * ms.m_transform.m_rotation.f[4] + tz * ms.m_transform.m_rotation.f[8]));
    ms.m_transform.m_translation.f[1] = s.m_centerOfMass1.f[1] -
        (tx * ms.m_transform.m_rotation.f[1] +
         (ty * ms.m_transform.m_rotation.f[5] + tz * ms.m_transform.m_rotation.f[9]));
    ms.m_transform.m_translation.f[2] = s.m_centerOfMass1.f[2] -
        (tx * ms.m_transform.m_rotation.f[2] +
         (ty * ms.m_transform.m_rotation.f[6] + tz * ms.m_transform.m_rotation.f[10]));
    ms.m_transform.m_translation.f[3] = s.m_centerOfMass1.f[3];
}

// ================================================================== 0x0120a570
// void hkSweptTransformUtil::freezeMotionState(float, hkMotionState&)
// @ 0x0120a570
void hkSweptTransformUtil::freezeMotionState(float time, hkMotionState& ms)
{
    hkSweptTransform& s = ms.m_swept;
    float t0 = s.m_centerOfMass0.f[3];
    if (time <= t0)
        time = t0;

    float x0 = s.m_rotation0.f[0];
    float y0 = s.m_rotation0.f[1];
    float z0 = s.m_rotation0.f[2];
    float w0 = s.m_rotation0.f[3];
    float x1 = s.m_rotation1.f[0];
    float y1 = s.m_rotation1.f[1];
    float z1 = s.m_rotation1.f[2];
    float w1 = s.m_rotation1.f[3];

    float t = (time - s.m_centerOfMass0.f[3]) * s.m_centerOfMass1.f[3];

    float sx = x1 + x0;
    float sy = y1 + y0;
    float sz = z1 + z0;
    float sw = w1 + w0;
    float mag = sy * sy + (sx * sx + (sz * sz + sw * sw));
    float corr = 0.75f - mag * 0.125f;
    corr = (1.5f - ((corr * corr) * mag) * 0.5f) * corr;

    s.m_rotation1.f[0] = sx * corr;
    s.m_rotation1.f[1] = sy * corr;
    s.m_rotation1.f[2] = sz * corr;
    s.m_rotation1.f[3] = sw * corr;

    float a = t + t;
    float v, wsrc;
    if (0.5f <= t) {
        float u = a - 1.0f;
        v = 1.0f - u;
        s.m_rotation1.f[0] = u * x1 + v * s.m_rotation1.f[0];
        s.m_rotation1.f[1] = v * s.m_rotation1.f[1] + y1 * u;
        s.m_rotation1.f[2] = z1 * u + v * s.m_rotation1.f[2];
        wsrc = w1;
        v = v * s.m_rotation1.f[3];
        s.m_rotation1.f[3] = wsrc * u + v;
    } else {
        v = 1.0f - a;
        s.m_rotation1.f[0] = v * x0 + a * s.m_rotation1.f[0];
        s.m_rotation1.f[1] = a * s.m_rotation1.f[1] + y0 * v;
        s.m_rotation1.f[2] = z0 * v + a * s.m_rotation1.f[2];
        wsrc = w0;
        v = a * s.m_rotation1.f[3];
        s.m_rotation1.f[3] = wsrc * (1.0f - a) + a * 0.0f;
    }

    float len = s.m_rotation1.f[1] * s.m_rotation1.f[1] +
        (s.m_rotation1.f[0] * s.m_rotation1.f[0] +
         (s.m_rotation1.f[2] * s.m_rotation1.f[2] + s.m_rotation1.f[3] * s.m_rotation1.f[3]));
    if (len == 0.0f)
        len = 0.0f;
    else
        len = 1.0f / sqrtf(len);
    s.m_rotation1.f[0] = len * s.m_rotation1.f[0];
    s.m_rotation1.f[1] = len * s.m_rotation1.f[1];
    s.m_rotation1.f[2] = len * s.m_rotation1.f[2];
    s.m_rotation1.f[3] = len * s.m_rotation1.f[3];

    s.m_rotation0.f[0] = s.m_rotation1.f[0];
    s.m_rotation0.f[1] = s.m_rotation1.f[1];
    s.m_rotation0.f[2] = s.m_rotation1.f[2];
    s.m_rotation0.f[3] = s.m_rotation1.f[3];

    float inv = 1.0f - t;
    s.m_centerOfMass1.f[0] = inv * s.m_centerOfMass0.f[0] + t * s.m_centerOfMass1.f[0];
    s.m_centerOfMass1.f[1] = inv * s.m_centerOfMass0.f[1] + t * s.m_centerOfMass1.f[1];
    s.m_centerOfMass1.f[2] = inv * s.m_centerOfMass0.f[2] + t * s.m_centerOfMass1.f[2];
    s.m_centerOfMass1.f[3] = inv * s.m_centerOfMass0.f[3] + t * s.m_centerOfMass1.f[3];

    s.m_centerOfMass0.f[0] = s.m_centerOfMass1.f[0];
    s.m_centerOfMass0.f[1] = s.m_centerOfMass1.f[1];
    s.m_centerOfMass0.f[2] = s.m_centerOfMass1.f[2];
    s.m_centerOfMass0.f[3] = time;
    s.m_centerOfMass1.f[3] = 0.0f;

    ms.m_transform.m_rotation.set(s.m_rotation1);

    float tx = s.m_translation.f[0];
    float ty = s.m_translation.f[1];
    float tz = s.m_translation.f[2];
    ms.m_transform.m_translation.f[0] = s.m_centerOfMass0.f[0] -
        (tx * ms.m_transform.m_rotation.f[0] +
         (ty * ms.m_transform.m_rotation.f[4] + tz * ms.m_transform.m_rotation.f[8]));
    ms.m_transform.m_translation.f[1] = s.m_centerOfMass0.f[1] -
        (tx * ms.m_transform.m_rotation.f[1] +
         (ty * ms.m_transform.m_rotation.f[5] + tz * ms.m_transform.m_rotation.f[9]));
    ms.m_transform.m_translation.f[2] = s.m_centerOfMass0.f[2] -
        (tx * ms.m_transform.m_rotation.f[2] +
         (ty * ms.m_transform.m_rotation.f[6] + tz * ms.m_transform.m_rotation.f[10]));
    ms.m_transform.m_translation.f[3] = s.m_centerOfMass0.f[3];
}

// ================================================================== 0x0120a880
// void hkSweptTransformUtil::warpTo(const hkVector4&, const hkQuaternion&, hkMotionState&)
// @ 0x0120a880
void hkSweptTransformUtil::warpTo(const hkVector4& p, const hkQuaternion& q,
                                  hkMotionState& ms)
{
    hkSweptTransform& s = ms.m_swept;

    ms.m_linearVelocity.f[3] = 0.0f;
    ms.m_linearVelocity.f[2] = 0.0f;
    ms.m_linearVelocity.f[1] = 0.0f;
    ms.m_linearVelocity.f[0] = 0.0f;

    s.m_rotation0.f[0] = q.f[0];
    s.m_rotation0.f[1] = q.f[1];
    s.m_rotation0.f[2] = q.f[2];
    s.m_rotation0.f[3] = q.f[3];
    s.m_rotation1.f[0] = q.f[0];
    s.m_rotation1.f[1] = q.f[1];
    s.m_rotation1.f[2] = q.f[2];
    s.m_rotation1.f[3] = q.f[3];
    ms.m_transform.m_rotation.set(q);
    ms.m_transform.m_translation.f[0] = p.f[0];
    ms.m_transform.m_translation.f[1] = p.f[1];
    ms.m_transform.m_translation.f[2] = p.f[2];
    ms.m_transform.m_translation.f[3] = p.f[3];

    float px = s.m_translation.f[0];
    float py = s.m_translation.f[1];
    float pz = s.m_translation.f[2];
    float time0 = s.m_centerOfMass0.f[3];

    hkVector4 c;
    c.f[0] = (px * ms.m_transform.m_rotation.f[0] +
              (pz * ms.m_transform.m_rotation.f[8] + py * ms.m_transform.m_rotation.f[4])) + p.f[0];
    c.f[1] = (px * ms.m_transform.m_rotation.f[1] +
              (pz * ms.m_transform.m_rotation.f[9] + py * ms.m_transform.m_rotation.f[5])) + p.f[1];
    c.f[2] = (px * ms.m_transform.m_rotation.f[2] +
              (pz * ms.m_transform.m_rotation.f[10] + py * ms.m_transform.m_rotation.f[6])) + p.f[2];
    c.f[3] = p.f[3];

    s.m_centerOfMass0.f[0] = c.f[0];
    s.m_centerOfMass0.f[1] = c.f[1];
    s.m_centerOfMass0.f[2] = c.f[2];
    s.m_centerOfMass0.f[3] = c.f[3];
    s.m_centerOfMass1.f[0] = s.m_centerOfMass0.f[0];
    s.m_centerOfMass1.f[1] = s.m_centerOfMass0.f[1];
    s.m_centerOfMass1.f[2] = s.m_centerOfMass0.f[2];
    s.m_centerOfMass1.f[3] = s.m_centerOfMass0.f[3];
    s.m_centerOfMass0.f[3] = time0;
    s.m_centerOfMass1.f[3] = 0.0f;
}

// ================================================================== 0x0120a9a0
// void hkSweptTransformUtil::warpTo(const hkTransform&, hkMotionState&)
// @ 0x0120a9a0
void hkSweptTransformUtil::warpTo(const hkTransform& t, hkMotionState& ms)
{
    hkSweptTransform& s = ms.m_swept;

    ms.m_linearVelocity.f[3] = 0.0f;
    ms.m_linearVelocity.f[2] = 0.0f;
    ms.m_linearVelocity.f[1] = 0.0f;
    ms.m_linearVelocity.f[0] = 0.0f;

    hkQuaternion q;
    q.set(t.m_rotation);
    ms.m_transform.assign(t);

    s.m_rotation0.f[0] = q.f[0];
    s.m_rotation0.f[1] = q.f[1];
    s.m_rotation0.f[2] = q.f[2];
    s.m_rotation0.f[3] = q.f[3];
    s.m_rotation1.f[0] = q.f[0];
    s.m_rotation1.f[1] = q.f[1];
    s.m_rotation1.f[2] = q.f[2];
    s.m_rotation1.f[3] = q.f[3];

    float px = s.m_translation.f[0];
    float py = s.m_translation.f[1];
    float pz = s.m_translation.f[2];
    float time0 = s.m_centerOfMass0.f[3];

    hkVector4 c;
    c.f[0] = (px * t.m_rotation.f[0] +
              (py * t.m_rotation.f[4] + pz * t.m_rotation.f[8])) + t.m_translation.f[0];
    c.f[1] = (px * t.m_rotation.f[1] +
              (py * t.m_rotation.f[5] + pz * t.m_rotation.f[9])) + t.m_translation.f[1];
    c.f[2] = (px * t.m_rotation.f[2] +
              (py * t.m_rotation.f[6] + pz * t.m_rotation.f[10])) + t.m_translation.f[2];
    c.f[3] = t.m_translation.f[3];

    s.m_centerOfMass0.f[0] = c.f[0];
    s.m_centerOfMass0.f[1] = c.f[1];
    s.m_centerOfMass0.f[2] = c.f[2];
    s.m_centerOfMass0.f[3] = c.f[3];
    s.m_centerOfMass1.f[0] = s.m_centerOfMass0.f[0];
    s.m_centerOfMass1.f[1] = s.m_centerOfMass0.f[1];
    s.m_centerOfMass1.f[2] = s.m_centerOfMass0.f[2];
    s.m_centerOfMass1.f[3] = s.m_centerOfMass0.f[3];
    s.m_centerOfMass0.f[3] = time0;
    s.m_centerOfMass1.f[3] = 0.0f;
}

// ================================================================== 0x0120aab0
// void hkSweptTransformUtil::warpToPosition(const hkVector4&, hkMotionState&)
// @ 0x0120aab0
void hkSweptTransformUtil::warpToPosition(const hkVector4& p, hkMotionState& ms)
{
    hkSweptTransform& s = ms.m_swept;

    ms.m_linearVelocity.f[0] = 0.0f;
    ms.m_linearVelocity.f[1] = 0.0f;
    ms.m_linearVelocity.f[2] = 0.0f;
    ms.m_linearVelocity.f[3] = 0.0f;

    ms.m_transform.m_translation.f[0] = p.f[0];
    ms.m_transform.m_translation.f[1] = p.f[1];
    ms.m_transform.m_translation.f[2] = p.f[2];
    ms.m_transform.m_translation.f[3] = p.f[3];

    float px = s.m_translation.f[0];
    float py = s.m_translation.f[1];
    float pz = s.m_translation.f[2];
    float time0 = s.m_centerOfMass0.f[3];

    hkVector4 c;
    c.f[0] = (px * ms.m_transform.m_rotation.f[0] +
              (pz * ms.m_transform.m_rotation.f[8] + py * ms.m_transform.m_rotation.f[4])) + p.f[0];
    c.f[1] = (px * ms.m_transform.m_rotation.f[1] +
              (pz * ms.m_transform.m_rotation.f[9] + py * ms.m_transform.m_rotation.f[5])) + p.f[1];
    c.f[2] = (px * ms.m_transform.m_rotation.f[2] +
              (pz * ms.m_transform.m_rotation.f[10] + py * ms.m_transform.m_rotation.f[6])) + p.f[2];
    c.f[3] = p.f[3];

    s.m_centerOfMass0.f[0] = c.f[0];
    s.m_centerOfMass0.f[1] = c.f[1];
    s.m_centerOfMass0.f[2] = c.f[2];
    s.m_centerOfMass0.f[3] = c.f[3];
    s.m_centerOfMass1.f[0] = s.m_centerOfMass0.f[0];
    s.m_centerOfMass1.f[1] = s.m_centerOfMass0.f[1];
    s.m_centerOfMass1.f[2] = s.m_centerOfMass0.f[2];
    s.m_centerOfMass1.f[3] = s.m_centerOfMass0.f[3];
    s.m_rotation0.f[0] = s.m_rotation1.f[0];
    s.m_rotation0.f[1] = s.m_rotation1.f[1];
    s.m_rotation0.f[2] = s.m_rotation1.f[2];
    s.m_rotation0.f[3] = s.m_rotation1.f[3];
    s.m_centerOfMass0.f[3] = time0;
    s.m_centerOfMass1.f[3] = 0.0f;
}

// ================================================================== 0x0120aba0
// void hkSweptTransformUtil::warpToRotation(const hkQuaternion&, hkMotionState&)
// @ 0x0120aba0
void hkSweptTransformUtil::warpToRotation(const hkQuaternion& q, hkMotionState& ms)
{
    warpTo(*(const hkVector4*)((const char*)&ms + 0x30), q, ms);
}

// ================================================================== 0x0120abc0
// void hkSweptTransform::initSweptTransform(const hkVector4&, const hkQuaternion&)
// @ 0x0120abc0
void hkSweptTransform::initSweptTransform(const hkVector4& p, const hkQuaternion& q)
{
    m_centerOfMass0.f[0] = p.f[0];
    m_centerOfMass0.f[1] = p.f[1];
    m_centerOfMass0.f[2] = p.f[2];
    m_centerOfMass0.f[3] = 0.0f;
    m_centerOfMass1.f[0] = p.f[0];
    m_centerOfMass1.f[1] = p.f[1];
    m_centerOfMass1.f[2] = p.f[2];
    m_centerOfMass1.f[3] = 0.0f;
    m_rotation0.f[0] = q.f[0];
    m_rotation0.f[1] = q.f[1];
    m_rotation0.f[2] = q.f[2];
    m_rotation0.f[3] = q.f[3];
    m_rotation1.f[0] = q.f[0];
    m_rotation1.f[1] = q.f[1];
    m_rotation1.f[2] = q.f[2];
    m_rotation1.f[3] = q.f[3];
    m_translation.f[3] = 0.0f;
    m_translation.f[2] = 0.0f;
    m_translation.f[1] = 0.0f;
    m_translation.f[0] = 0.0f;
}

// ================================================================== 0x0120ac30
// void hkMotionState::initMotionState(const hkVector4&, const hkQuaternion&)
// @ 0x0120ac30
void hkMotionState::initMotionState(const hkVector4& p, const hkQuaternion& q)
{
    m_swept.initSweptTransform(p, q);
    m_transform.m_rotation.set(q);
    m_transform.m_translation.f[0] = p.f[0];
    m_transform.m_translation.f[1] = p.f[1];
    m_transform.m_translation.f[2] = p.f[2];
    m_transform.m_translation.f[3] = p.f[3];
    m_linearVelocity.f[3] = 0.0f;
    m_linearVelocity.f[2] = 0.0f;
    m_linearVelocity.f[1] = 0.0f;
    m_linearVelocity.f[0] = 0.0f;
    m_fa0 = 1.0f;
}

// ================================================================== 0x0120ac90
// float hkMath::hkFloor(float)
// @ 0x0120ac90
float hkMath::hkFloor(float x)
{
    int u = *(int*)&x;
    int e = (int)(((unsigned)u >> 23) & 0xff) - 0x7f;
    int c = 0x17 - e;
    int a = c >> 31;
    int d = ~(((u & 0x7fffffff) - 1) >> 31);
    u &= d;
    int na = ~a;
    int mask = ((int)0xff800000 >> ((na & 0x17) - (na & c))) | a;
    int t = ~((~mask & u) - 1);
    t &= (int)0x800000 >> (e & 0x1f);
    t &= u >> 31;
    t += u;
    t &= ~(e >> 31);
    t &= mask;
    t |= ((e >> 31) & (u >> 31)) & (int)0xbf800000;
    return *(float*)&t;
}

// ================================================================== 0x0120ad30
// int hkMath::hkFloatToInt(float)
// @ 0x0120ad30
int hkMath::hkFloatToInt(float x)
{
    int u = *(int*)&x;
    int e = (int)(((unsigned)u >> 23) & 0xff) - 0x7f;
    int eb = e - 0x17;
    int c = eb - 1;
    int cc = c >> 31;
    int nb = ~cc;
    eb &= nb;
    int d = ~((((u & 0x7fffffff) - 1) >> 31));
    u &= d;
    int esi = (0x17 - e) & cc;
    int ecx = (cc & 0x17) - esi;
    int mask = (int)0xff800000 >> (ecx & 0x1f);
    mask |= nb;
    int top = u;
    int m = ((u & 0x7fffff) | 0x800000) & mask;
    int msign = top >> 31;
    int v = m + m - 1;
    v |= msign;
    v -= m;
    v += 1;
    int em = ~(e >> 31);
    v &= em;
    v >>= (esi & 0x1f);
    v <<= (eb & 0x1f);
    return v;
}

// ================================================================== 0x0120adb0
// float hkMath::atan2fApproximation(float, float)
// @ 0x0120adb0
float hkMath::atan2fApproximation(float a, float b)
{
    float fa = fabsf(a);
    float fb = fabsf(b);
    float r;
    if (fa <= fb) {
        float q = fa / (fb + 1.1920929e-07f);
        r = (q - 0.121079f * (q * q)) - ((q * q) * q) * 0.09352282f;
    } else {
        float q = fb / (fa + 1.1920929e-07f);
        r = 1.5707964f - ((q - 0.121079f * (q * q)) -
                          ((q * q) * q) * 0.09352282f);
    }
    if (b < 0.0f)
        r = 3.1415927f - r;
    if (a < 0.0f)
        r = -r;
    return r;
}
