// Slice s00a798d0: Hermite keyframe-spline step. Finds the first key whose time is after the
// state's time (4x-unrolled search over keys[0 .. n-1)), transforms the key position and tangent
// by an optional Transform (rotation flag 2, scale, offset), optionally rewinds the state when the
// remaining distance is too large for the max speed, and advances position/velocity by dt along
// the cubic Hermite basis.  Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast (to be confirmed by chk).
#include <math.h>
#include "types.h"

struct V3 { float x, y, z; V3() {} V3(float a, float b, float c) { x = a; y = b; z = c; } };

struct HKey {              // 0x1c bytes
    V3 p;                  // +0x00 position
    V3 t;                  // +0x0c tangent
    float time;            // +0x18
};


struct HKeyVec { HKey* mpBegin; HKey* mpEnd; };

struct HXform {            // Transform: flags / offset / scale / rotation
    unsigned short flags;  // bit 1 = rotation present
    unsigned short pad;
    float off[3];          // +0x04
    float scale;           // +0x10
    float m[9];            // +0x14
};

struct HState {
    float time;            // +0x00
    float defaultEnd;      // +0x04
    V3 pos;                // +0x08
    V3 vel;                // +0x14
};

__forceinline HKey* FindAfter(HKey* cur, HKey* last, float t)
{
    if (cur < last)
    {
        int n = ((int)((char*)last - (char*)cur) + 0x1b) / 0x1c;
        if (n >= 4)
        {
            do
            {
                if (!(cur[0].time <= t)) return cur;
                if (!(cur[1].time <= t)) return cur + 1;
                if (!(cur[2].time <= t)) return cur + 2;
                if (!(cur[3].time <= t)) return cur + 3;
                cur += 4;
            } while ((int)cur < (int)(last - 3));
        }
        for (; cur < last; ++cur)
            if (!(cur->time <= t)) return cur;
    }
    return cur;
}

__forceinline V3 Rotate(const HXform* xf, const V3& v)
{
    V3 r;
    r.x = (xf->m[6] * v.z + xf->m[3] * v.y) + xf->m[0] * v.x;
    r.y = (xf->m[7] * v.z + xf->m[4] * v.y) + xf->m[1] * v.x;
    r.z = (xf->m[8] * v.z + xf->m[5] * v.y) + xf->m[2] * v.x;
    return r;
}

// @ 0x00A798D0
void HermiteStep(HState* s, float dt, HKeyVec* keys, float maxSpeed, HXform* xf)
{
    float t = s->time;
    HKey* first = keys->mpBegin;
    HKey* last = keys->mpEnd - 1;
    HKey* cur = FindAfter(first, last, t);
    float tk = cur->time;
    if (tk == 0.0f)
        tk = s->defaultEnd;
    else if (tk < t)
    {
        s->pos.x = s->vel.x * dt + s->pos.x;
        s->pos.y = s->vel.y * dt + s->pos.y;
        s->pos.z = s->vel.z * dt + s->pos.z;
        return;
    }
    float T = (tk - t) + dt;
    V3 rp = cur->p;
    if (xf->flags & 2)
        rp = Rotate(xf, cur->p);
    float sc = xf->scale;
    float px = sc * rp.x + xf->off[0];
    float py = xf->off[1] + sc * rp.y;
    float pz = xf->off[2] + sc * rp.z;
    V3 rt = cur->t;
    if (xf->flags & 2)
        rt = Rotate(xf, cur->t);
    sc = xf->scale;
    float qx = rt.x * sc, qy = rt.y * sc, qz = rt.z * sc;
    float dx = s->pos.x - px, dy = s->pos.y - py, dz = s->pos.z - pz;
    if (maxSpeed != 0.0f)
    {
        if (T * maxSpeed < sqrt(dx * dx + dz * dz + dy * dy))
        {
            float prev = 0.0f;
            if (first < cur)
                prev = cur[-1].time;
            float d = t - prev;
            T = d + T;
            s->time = t - d;
        }
    }
    float inv = 1.0f / T;
    float u = inv * dt;
    float u2 = u * u;
    float A = u2 * u - u2;
    float u2x = u * 2.0f;
    float h1 = u2 - A * 2.0f;
    float h0 = 1.0f - h1;
    float d1 = u2 * 3.0f - u2x;
    float d2 = (d1 - u2x) + 1.0f;
    float d3 = u2x - d1 * 2.0f;
    float m1 = ((A - u2) + u) * T;
    float m2 = A * T;
    float dn = -d3 * inv;
    float dp = d3 * inv;
    float vx = s->vel.x, vy = s->vel.y, vz = s->vel.z;
    float ox = s->pos.x, oy = s->pos.y, oz = s->pos.z;
    V3 np(((ox * h0 + h1 * px) + vx * m1) + m2 * qx,
          ((oy * h0 + h1 * py) + vy * m1) + m2 * qy,
          ((oz * h0 + h1 * pz) + vz * m1) + m2 * qz);
    V3 nv(((ox * dn + dp * px) + vx * d2) + d1 * qx,
          ((oy * dn + dp * py) + vy * d2) + d1 * qy,
          ((oz * dn + dp * pz) + vz * d2) + d1 * qz);
    s->pos = np;
    s->vel = nv;
}
