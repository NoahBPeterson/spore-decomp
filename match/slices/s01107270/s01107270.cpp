// Havok 3.1 capsule vs triangle contact manifold (hkCollideCapsuleUtil family).
#include "../../include/types.h"
#include <math.h>

struct hkVector4 { float v[4]; };

struct hkContactPointF {
    float pos[4];
    float nrm[4];   // nrm[3] is the separating distance
    void assign(const hkContactPointF& o);   // 0x01101fd0: 32-byte copy
};

struct hkCollideTriangleUtil {
    struct ClosestLineSegLineSegResult {
        hkVector4 closestPointA;
        hkVector4 closestAminusClosestB;
        float distanceSquared;
    };
    static int closestLineSegLineSeg(const hkVector4& A, const hkVector4& dA, const hkVector4& B,
                                     const hkVector4& dB, ClosestLineSegLineSegResult& r);
};

extern "C" void hkCollideCapsuleUtilManifoldCapsVsCaps(const float* a, float ra, const float* b, float rb,
                                                       hkContactPointF* out);

extern const signed char g_edgeEnd[];    // 0x014a5e70, pairs (end, start) per edge
#define EDGE_END(i)   (*(const signed char*)(0x014a5e70 + (i)))
#define EDGE_START(i) (*(const signed char*)(0x014a5e72 + (i)))

// @ 0x01107270
void hkCollideCapsuleUtilManifoldCapsVsTriangle(const float* cap, float capRadius, const float* tri,
                                                           float triRadius, const float* sc, float extraRadius,
                                                           int singleCheck, hkContactPointF* out)
{
    float* o = (float*)out;

    // triangle edges
    float e12x = tri[8] - tri[4], e12y = tri[9] - tri[5], e12z = tri[10] - tri[6];
    float w = sc[3];
    float e20x = tri[0] - tri[8], e20y = tri[1] - tri[9], e20z = tri[2] - tri[10];
    float nx = (e20z * e12y - e12z * e20y) * w;
    float ny = w * (e12z * e20x - e12x * e20z);
    float nz = w * (e12x * e20y - e12y * e20x);
    float nw = w * 0.0f;
    float p0 = sc[0];
    float q0 = p0 * e12x;
    float q1 = e12y * p0;
    float q2 = e12z * p0;
    float p1 = sc[1];
    float r1 = e20y * p1;
    float r0 = e20x * p1;
    float b8 = p1 * e20z;
    float p2 = sc[2];
    float s0 = (tri[4] - tri[0]) * p2;
    float s1 = (tri[5] - tri[1]) * p2;
    float s2 = p2 * (tri[6] - tri[2]);

    __declspec(align(16)) float m80[4];
    __declspec(align(16)) float m70[4];
    __declspec(align(16)) float m60[4];
    m80[0] = q1 * nz - q2 * ny;
    m70[0] = q2 * nx - q0 * nz;
    m60[0] = q0 * ny - q1 * nx;
    m80[1] = nz * r1 - ny * b8;
    m70[1] = nx * b8 - r0 * nz;
    m60[1] = r0 * ny - nx * r1;
    m80[2] = nz * s1 - ny * s2;
    m70[2] = nx * s2 - s0 * nz;
    m60[2] = s0 * ny - nx * s1;
    m80[3] = nx;
    m70[3] = ny;
    m60[3] = nz;
    float off = -(sc[4] * sc[0]);

    float d0x = cap[0] - tri[0], d0y = cap[1] - tri[1], d0z = cap[2] - tri[2];
    float d1x = cap[4] - tri[0], d1y = cap[5] - tri[1], d1z = cap[6] - tri[2];

    __declspec(align(16)) float f[8];
    f[0] = (m70[0] * d0y + (d0x * m80[0] + m60[0] * d0z)) + off;
    f[1] = m70[1] * d0y + (d0x * m80[1] + m60[1] * d0z);
    f[2] = d0x * m80[2] + (d0y * m70[2] + m60[2] * d0z);
    f[3] = d0x * nx + (d0y * ny + d0z * nz);
    o[7] = 3.40282e+38f;
    o[15] = 3.40282e+38f;
    o[23] = 3.40282e+38f;
    f[4] = (m70[0] * d1y + (d1x * m80[0] + m60[0] * d1z)) + off;
    f[5] = m70[1] * d1y + (d1x * m80[1] + m60[1] * d1z);
    f[6] = d1x * m80[2] + (d1y * m70[2] + m60[2] * d1z);
    f[7] = d1x * nx + (d1y * ny + d1z * nz);

    float c4 = capRadius + triRadius;
    float rr = c4 + extraRadius;
    if ((((rr < f[2]) << 1 | (rr < f[1]) << 2 | (rr < f[0]) << 3 | (rr < f[3])) &
         ((rr < f[6]) << 1 | (rr < f[5]) << 2 | (rr < f[4]) << 3 | (rr < f[7]))) != 0)
        return;
    if (f[3] < -rr && f[7] < -rr)
        return;

    unsigned c0[2];
    unsigned uA = (f[2] < 0.0f) << 1 | (f[1] < 0.0f) << 2 | (f[0] < 0.0f) << 3 | (f[3] < 0.0f);
    c0[0] = uA;
    unsigned uB = (f[6] < 0.0f) << 1 | (f[5] < 0.0f) << 2 | (f[4] < 0.0f) << 3 | (f[7] < 0.0f);
    c0[1] = uB;

    if (((uB ^ uA) & 1) != 0) {
        float t = f[3] / (f[3] - f[7]);
        float u = 1.0f - t;
        float l1 = u * f[1] + t * f[5];
        float l2 = u * f[2] + t * f[6];
        if ((((l2 < 0.0f) << 1 | (l1 < 0.0f) << 2 | (u * f[0] + t * f[4] < 0.0f) * -8) & 0xe) == 0xe) {
            o[15] = -3.40282e+38f;
            for (int i = 0; i < 2; ++i) {
                float sd = f[3 + 4 * i];
                if ((c0[i] & 0xe) == 0xe) {
                    float v = -fabsf(sd) - c4;
                    if (o[15] < v) {
                        float s;
                        if ((c0[i] & 1) == 0) {
                            o[12] = -nx; o[13] = -ny; o[14] = -nz; o[15] = -nw;
                            s = -triRadius;
                        } else {
                            o[12] = nx; o[13] = ny; o[14] = nz; o[15] = nw;
                            s = triRadius;
                        }
                        s = s - sd;
                        o[8] = cap[4 * i];
                        o[9] = cap[4 * i + 1];
                        o[10] = cap[4 * i + 2];
                        o[11] = cap[4 * i + 3];
                        o[8] = nx * s + o[8];
                        o[9] = ny * s + o[9];
                        o[10] = nz * s + o[10];
                        o[11] = s * nw + o[11];
                        o[15] = v;
                    }
                }
            }
            float dd[4];
            dd[0] = f[4] - f[0];
            dd[1] = f[5] - f[1];
            dd[2] = f[6] - f[2];
            f[7] = f[7] - f[3];
            for (int k = 0; k < 3; ++k) {
                float a = dd[k];
                float inv = 1.0f / (a * a + f[7] * f[7]);
                float cr = a * f[3] - f[7] * f[k];
                cr = (cr * cr) * inv;
                if (cr < (c4 + o[15]) * (c4 + o[15])) {
                    float tt = -((f[7] * f[3] + a * f[k]) * inv);
                    if (-0.0001f < tt && tt < 1.0001f) {
                        float c9 = m70[k];
                        float c10 = f[7];
                        if (f[7] < 0.0f) {
                            c10 = -f[7];
                            a = -a;
                        }
                        float c98 = c10 * m60[k];
                        a = -a;
                        o[12] = a * nx + m80[k] * c10;
                        o[13] = a * ny + c10 * c9;
                        o[14] = a * nz + c98;
                        o[15] = a * nw + c10 * 0.0f;
                        float len2 = o[14] * o[14] + (o[13] * o[13] + o[12] * o[12]);
                        float il;
                        if (len2 == 0.0f) il = 0.0f; else il = 1.0f / (float)sqrt(len2);
                        o[12] = il * o[12];
                        o[13] = il * o[13];
                        o[14] = il * o[14];
                        o[15] = il * o[15];
                        float uu = 1.0f - tt;
                        float px = tt * cap[4] + uu * cap[0];
                        float py = uu * cap[1] + tt * cap[5];
                        float pz = uu * cap[2] + tt * cap[6];
                        float pw = uu * cap[3] + tt * cap[7];
                        o[11] = pw;
                        float dist = -(float)sqrt(cr);
                        o[8] = px;
                        o[9] = py;
                        o[10] = pz;
                        float g = triRadius - dist;
                        o[8] = g * o[12] + px;
                        o[9] = g * o[13] + py;
                        o[10] = g * o[14] + pz;
                        o[11] = g * o[15] + pw;
                        o[15] = dist - c4;
                    }
                }
            }
            return;
        }
    }

    __declspec(align(16)) float seg[4];
    seg[0] = cap[4] - cap[0];
    seg[1] = cap[5] - cap[1];
    seg[2] = cap[6] - cap[2];
    seg[3] = cap[7] - cap[3];
    int idx = 0;
    bool oneShot = false;
    unsigned both = uB | uA;

    if ((both & 0xe) != 0xe) {
        if (singleCheck != 0) {
            o[7] = extraRadius;
            o[15] = extraRadius;
            o[23] = extraRadius;
            hkContactPointF best;
            ((float*)&best)[7] = 3.40282e+38f;
            unsigned m = 8;
            for (int e = 0; e < 3; ++e) {
                if ((m & both) == 0) {
                    float seg2[8];
                    const float* p = tri + EDGE_START(e) * 4;
                    seg2[0] = p[0]; seg2[1] = p[1]; seg2[2] = p[2]; seg2[3] = p[3];
                    const float* q = tri + EDGE_END(e) * 4;
                    seg2[4] = q[0]; seg2[5] = q[1]; seg2[6] = q[2]; seg2[7] = q[3];
                    hkCollideCapsuleUtilManifoldCapsVsCaps(cap, capRadius, seg2, triRadius, out);
                    if (o[7] <= ((float*)&best)[7])
                        best.assign(*out);
                    else
                        out->assign(best);
                }
                m = (int)m >> 1;
            }
            return;
        }
        oneShot = true;
    }

    for (;;) {
        if (!oneShot) {
            for (;;) {
                if (idx > 1)
                    return;
                if ((c0[idx] & 0xe) != 0xe)
                    break;
                float fd = f[idx * 4 + 3];
                float g;
                if ((c0[idx] & 1) == 0)
                    g = triRadius - fd;
                else
                    g = -triRadius - fd;
                o[0] = cap[idx * 4];
                o[1] = cap[idx * 4 + 1];
                o[2] = cap[idx * 4 + 2];
                o[3] = cap[idx * 4 + 3];
                o[0] = nx * g + o[0];
                o[1] = ny * g + o[1];
                o[2] = nz * g + o[2];
                o[3] = g * nw + o[3];
                if ((c0[idx] & 1) == 0) {
                    o[4] = nx; o[5] = ny; o[6] = nz; o[7] = nw;
                    o[7] = fd - c4;
                } else {
                    o[4] = -nx; o[5] = -ny; o[6] = -nz; o[7] = -nw;
                    o[7] = -fd - c4;
                }
                ++idx;
                o += 8;
            }
        }
        // edge phase
        unsigned m = 8;
        for (int e = 0; e < 3; ++e) {
            unsigned hi, lo;
            if (oneShot) {
                hi = m & c0[1];
                lo = c0[0];
            } else {
                hi = c0[idx];
                lo = m;
            }
            if ((lo & hi) == 0) {
                const float* pB = tri + EDGE_END(e) * 4;
                const float* pA = tri + EDGE_START(e) * 4;
                float ed[4];
                ed[0] = pB[0] - pA[0];
                ed[1] = pB[1] - pA[1];
                ed[2] = pB[2] - pA[2];
                ed[3] = pB[3] - pA[3];
                hkCollideTriangleUtil::ClosestLineSegLineSegResult r;
                int fl = hkCollideTriangleUtil::closestLineSegLineSeg(*(const hkVector4*)cap, *(const hkVector4*)seg,
                                                                      *(const hkVector4*)pA, *(const hkVector4*)ed, r);
                float rad = c4 + o[7];
                if (r.distanceSquared < rad * rad) {
                    bool skip = false;
                    if ((fl & (1 << idx)) != 0) {
                        if (!oneShot) skip = true;
                        else idx = 1;
                    }
                    if (!skip) {
                        float n0, n1, n2, n3;
                        float* diff = r.closestAminusClosestB.v;
                        bool useCross = true;
                        if (fl == 0) {
                            n1 = ed[0] * seg[2] - seg[0] * ed[2];
                            n2 = seg[0] * ed[1] - ed[0] * seg[1];
                            n3 = 0.0f;
                            n0 = ed[2] * seg[1] - ed[1] * seg[2];
                        } else {
                            useCross = false;
                            bool tiny = r.distanceSquared <= 1.4210855e-14f;
                            if (tiny) {
                                diff[0] = m80[e];
                                diff[1] = m70[e];
                                diff[2] = m60[e];
                                diff[3] = 0.0f;
                                n3 = 0.0f;
                                n0 = ed[2] * seg[1] - ed[1] * seg[2];
                                n1 = ed[0] * seg[2] - seg[0] * ed[2];
                                n2 = seg[0] * ed[1] - ed[0] * seg[1];
                                float l2 = n1 * n1 + (n2 * n2 + n0 * n0);
                                if (l2 > 1.4210855e-14f)
                                    useCross = true;
                            }
                            if (!useCross) {
                                n0 = diff[0];
                                n1 = diff[1];
                                n2 = diff[2];
                                n3 = diff[3];
                            }
                        }
                        float l2 = n1 * n1 + (n2 * n2 + n0 * n0);
                        float il;
                        if (l2 == 0.0f) il = 0.0f; else il = 1.0f / (float)sqrt(l2);
                        n0 = n0 * il;
                        n1 = il * n1;
                        n2 = il * n2;
                        n3 = il * n3;
                        float dist = diff[1] * n1 + (diff[2] * n2 + diff[0] * n0);
                        if (dist < 0.0f) {
                            dist = -dist;
                            n0 = -n0; n1 = -n1; n2 = -n2; n3 = -n3;
                        }
                        float g = triRadius - dist;
                        o[0] = n0 * g + r.closestPointA.v[0];
                        o[1] = n1 * g + r.closestPointA.v[1];
                        o[2] = n2 * g + r.closestPointA.v[2];
                        o[3] = n3 * g + r.closestPointA.v[3];
                        o[6] = n2;
                        o[7] = n3;
                        o[4] = n0;
                        o[5] = n1;
                        o[7] = dist - c4;
                    }
                }
            }
            m = (int)m >> 1;
        }
        if (oneShot)
            return;
        ++idx;
        o += 8;
    }
}
