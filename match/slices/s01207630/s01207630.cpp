// Slice s01207630 -- 0x01207630, 2291 bytes (cdecl).
//
// BoxVolume contact-feature builder: given an oriented box (center, three axes, half extents), a
// direction n and a winding flag, find the box feature that lies furthest along n and describe
// it in `out`:
//   * n (nearly) parallel to one box axis (the other two |n.axis| < 0.2): the box FACE on that
//     axis: four corners (out+0x10 + 0x40*c: position, side tangent, edge tangent, edge length),
//     the face normal (out+0x110), type 4;
//   * n perpendicular to one axis (exactly one |n.axis| < 0.2): the box EDGE along that axis: the
//     segment end points of the extreme edge, built with the segment constructor at 0x012016f0
//     (position, normalised direction, length), copied to out+0x10, type 1;
//   * otherwise the extreme VERTEX (out+0x120), type 0.
// out->result (+0x00) is always 0.  The tables at 0x015d0b28 (corner signs), 0x015d0b48 (corner
// axis picks) and 0x015d0b68 (the two other axes of an axis) are part of the box-volume type data.
//
// All vector math is 4-wide SSE as in Havok 3.1's hkVector4 (dot3 via two shuffles, cross via
// yzx/zxy shuffles, 2-step Newton-Raphson rsqrt).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast (as the neighbouring volume-cast slices).
//
//

#include <xmmintrin.h>

typedef unsigned int uint32_t;

struct ObbFrame {               // 16-byte aligned
    __m128 center;              // +0x00
    __m128 axis[3];             // +0x10
    uint32_t pad[12];           // +0x40
    float half[3];              // +0x70
};

struct FeatureCorner {          // 0x40 bytes, out + 0x10 + 0x40 * i
    __m128 pos;
    __m128 sideDir;
    __m128 edgeDir;
    float length;
    float pad[3];
};

struct FeatureOut {
    int result;                 // +0x00
    uint32_t pad0[3];
    FeatureCorner corner[4];    // +0x10
    __m128 faceNormal;          // +0x110
    __m128 vertex;              // +0x120
    int type;                   // +0x130
};

// segment from a to b: pos = a, dir = (b-a)/|b-a|, length |b-a|   (thiscall ctor, 0x012016f0)
struct Segment {
    __m128 pos;
    __m128 dir;
    __m128 unused;
    float length;
    Segment(const __m128& a, const __m128& b);
};

struct CornerSign { float a; float b; };
struct CornerPick { int a; int b; };
struct AxisPair { int a; int b; };
extern const CornerSign gCornerSign[4];     // 0x015d0b28
extern const CornerPick gCornerPick[4];     // 0x015d0b48
extern const AxisPair gOtherAxes[3];        // 0x015d0b68

static __forceinline __m128 Splat(float f) { return _mm_set_ps1(f); }
static __forceinline __m128 SplatX(__m128 v) { return _mm_shuffle_ps(v, v, 0x00); }

union Vec4Access {
    __m128 v;
    float f[4];
    uint32_t u[4];
};
static __forceinline float Get0(__m128 v)
{
    Vec4Access a;
    a.v = v;
    return a.f[0];
}

static __forceinline __m128 Dot3(__m128 a, __m128 b)
{
    __m128 m = _mm_mul_ps(a, b);
    return SplatX(_mm_add_ps(m, _mm_add_ps(_mm_shuffle_ps(m, m, 1), _mm_shuffle_ps(m, m, 2))));
}

// two Newton-Raphson steps of rsqrt, then d * (1/|d|); unchanged for a tiny vector
static __forceinline __m128 NormalizeSafe(__m128 d)
{
    __m128 len2 = Dot3(d, d);
    if (!(Get0(len2) > 1.1920929e-07f))
        return d;
    const __m128 half = Splat(0.5f);
    const __m128 one = Splat(1.0f);
    __m128 r = _mm_rsqrt_ps(len2);
    r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(len2, _mm_mul_ps(r, r))), _mm_mul_ps(r, half)));
    r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(len2, _mm_mul_ps(r, r))), _mm_mul_ps(r, half)));
    return _mm_mul_ps(d, r);
}

// cross(a, b)
static __forceinline __m128 Cross(__m128 a, __m128 b)
{
    return _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(a, a, 9), _mm_shuffle_ps(b, b, 0x12)),
                      _mm_mul_ps(_mm_shuffle_ps(a, a, 0x12), _mm_shuffle_ps(b, b, 9)));
}

// @ 0x01207630
void BuildBoxContactFeature(const ObbFrame* box, int flip, const __m128* pn, FeatureOut* out)
{
    const __m128 n = *pn;
    int numSmall = 0;
    int smallAxis = 0;
    int bigAxis = 0;
    float best = 0.0f;
    __m128 bestPoint;

    for (int i = 0; i < 3; i++) {
        Vec4Access d;
        d.v = Dot3(n, box->axis[i]);
        d.u[0] &= 0x7fffffff;
        if (d.f[0] < 0.2f) {
            numSmall++;
            smallAxis = i;
        } else {
            bigAxis = i;
        }
    }

    if (numSmall == 2) {
        // ---- face on axis k ----
        int k = bigAxis;
        float s = Get0(Dot3(box->axis[k], n)) > 0.0f ? 1.0f : -1.0f;
        __m128 center = _mm_add_ps(box->center, _mm_mul_ps(box->axis[k], Splat(box->half[k] * s)));
        float sn = s;
        if (k == 1)
            sn = 0.0f - s;
        int ia = gOtherAxes[k].a;
        int ib = gOtherAxes[k].b;
        float ha = box->half[ia];
        float hb = box->half[ib];
        __m128 u = box->axis[ia];
        __m128 v = box->axis[ib];

        __m128 qu[2], qv[2], dirE[4], dirD[4];
        qu[0] = _mm_mul_ps(u, Splat(ha));
        qu[1] = _mm_mul_ps(u, Splat(0.0f - ha));
        qv[0] = _mm_mul_ps(v, Splat(hb));
        qv[1] = _mm_mul_ps(v, Splat(0.0f - hb));
        dirE[2] = v;
        dirE[3] = u;
        __m128 zero = _mm_setzero_ps();
        dirE[0] = _mm_sub_ps(zero, v);
        dirE[1] = _mm_sub_ps(zero, u);
        __m128 t1, t2;
        if (flip != 0) {
            t1 = NormalizeSafe(Cross(v, n));
            t2 = NormalizeSafe(Cross(u, n));
        } else {
            t1 = NormalizeSafe(Cross(n, v));
            t2 = NormalizeSafe(Cross(n, u));
        }
        dirD[0] = _mm_sub_ps(zero, t1);
        dirD[1] = _mm_sub_ps(zero, t2);
        dirD[2] = t1;
        dirD[3] = t2;
        float len[2];
        len[0] = hb * 2.0f;
        len[1] = ha * 2.0f;

        int neg = 0.0f > sn ? 1 : 0;
        if (neg == flip) {
            for (int c = 0; c < 4; c++) {
                __m128 p = _mm_add_ps(_mm_add_ps(center, qu[gCornerPick[c].a]), qv[gCornerPick[c].b]);
                out->corner[c].pos = p;
                out->corner[c].sideDir = dirE[c];
                out->corner[c].edgeDir = dirD[c];
                out->corner[c].length = len[c & 1];
            }
        } else {
            for (int c = -2; c + 2 < 4; c++) {
                int pc = (c - 1) & 3;
                int dc = c & 3;
                __m128 p = _mm_add_ps(_mm_add_ps(center, qu[gCornerPick[pc].a]), qv[gCornerPick[pc].b]);
                FeatureCorner& o = out->corner[3 - (c + 2)];
                o.pos = p;
                o.sideDir = dirE[dc];
                o.edgeDir = dirD[dc];
                o.length = len[c & 1];
            }
        }
        out->faceNormal = _mm_mul_ps(box->axis[k], Splat(0.0f - sn));
        out->type = 4;
        out->result = 0;
        return;
    }

    if (numSmall == 1) {
        // ---- edge along smallAxis ----
        int ia = gOtherAxes[smallAxis].a;
        int ib = gOtherAxes[smallAxis].b;
        __m128 u = box->axis[ia];
        __m128 v = box->axis[ib];
        int bestIdx = -1;
        for (int c = 0; c < 4; c++) {
            __m128 tv = _mm_mul_ps(v, Splat(gCornerSign[c].b * box->half[ib]));
            __m128 tu = _mm_mul_ps(u, Splat(gCornerSign[c].a * box->half[ia]));
            __m128 p = _mm_add_ps(_mm_add_ps(box->center, tu), tv);
            float dd = Get0(Dot3(p, n));
            if (bestIdx < 0 || dd > best) {
                bestPoint = p;
                best = dd;
                bestIdx = c;
            }
        }
        __m128 e = _mm_mul_ps(box->axis[smallAxis], Splat(box->half[smallAxis]));
        __m128 hi = _mm_add_ps(bestPoint, e);
        __m128 lo = _mm_sub_ps(bestPoint, e);
        Segment seg(lo, hi);
        out->corner[0].pos = seg.pos;
        out->corner[0].sideDir = seg.dir;
        out->corner[0].edgeDir = seg.unused;
        out->corner[0].length = seg.length;
        out->type = 1;
        out->result = 0;
        return;
    }

    // ---- vertex ----
    int bestIdx = -1;
    for (int c = 0; c < 8; c++) {
        float sx = c > 3 ? 1.0f : -1.0f;
        sx *= box->half[0];
        __m128 t2 = _mm_mul_ps(box->axis[2], Splat(gCornerSign[c & 3].b * box->half[2]));
        __m128 t1 = _mm_mul_ps(box->axis[1], Splat(gCornerSign[c & 3].a * box->half[1]));
        __m128 t0 = _mm_mul_ps(box->axis[0], Splat(sx));
        __m128 p = _mm_add_ps(_mm_add_ps(_mm_add_ps(box->center, t0), t1), t2);
        float dd = Get0(Dot3(p, n));
        if (bestIdx < 0 || dd > best) {
            bestPoint = p;
            best = dd;
            bestIdx = c;
        }
    }
    out->vertex = bestPoint;
    out->type = 0;
    out->result = 0;
}
