// Slice s0069b910: one large function at 0x69b910.
// Shape = translation (base[3]) + uniform scale + optional 3x3 orientation (flags bit 1).
// boxA/boxB are two opposite corners of an axis-aligned box (x0,y0,z0,x1,y1,z1).
// The function transforms the 8 corners of each box by its shape and runs a 6-axis
// separating-axis test (3 edge axes per box); returns false as soon as the projections
// are disjoint on any axis, true otherwise.
//
// Behaviour-only reconstruction (see nonmatching.txt). The original is a fully unrolled
// /O2 /arch:SSE /fp:fast routine; this source is behaviourally complete but its scalar
// floating-point schedule does not reproduce the original bytes.
#include "types.h"

struct Shape {
    unsigned short flags;   // +0  bit1 => apply orientation
    unsigned short pad;     // +2
    float base[3];          // +4
    float scale;            // +16
    float m[9];             // +20 orientation, rows m[0..2], m[3..5], m[6..8]
};

// Transform a local point by the shape: orientation (if flags&2) then base + scale*t.
static inline void XForm(const Shape* s, float x, float y, float z, float* o)
{
    float tx = x;
    float ty = y;
    float tz = z;
    if (s->flags & 2) {
        tx = (s->m[3] * y + s->m[6] * z) + s->m[0] * x;
        ty = (s->m[1] * x + s->m[4] * y) + s->m[7] * z;
        tz = (s->m[2] * x + s->m[5] * y) + s->m[8] * z;
    }
    o[0] = s->base[0] + s->scale * tx;
    o[1] = s->base[1] + ty * s->scale;
    o[2] = s->base[2] + tz * s->scale;
}

static inline void Proj4A(const float* p, float v0, float v1, float v2, float len2,
                          float& mn, float& mx)
{
    for (int q = 0; q < 4; ++q, p += 3) {
        float r = ((p[0] * v0 + p[2] * v2) + v1 * p[1]) / len2;
        r = ((r * v0) * v0 + (r * v2) * v2) + (r * v1) * v1;
        if (mx < r) mx = r;
        if (r < mn) mn = r;
    }
}

static inline void Proj4B(const float* p, float v0, float v1, float v2, float len2,
                          float& mn, float& mx)
{
    for (int q = 0; q < 4; ++q, p += 3) {
        float r = ((p[0] * v0 + p[2] * v2) + p[1] * v1) / len2;
        r = ((r * v2) * v2 + (r * v1) * v1) + (r * v0) * v0;
        if (mx < r) mx = r;
        if (r < mn) mn = r;
    }
}

// @ 0x0069b910
extern "C" bool FUN_0069b910(const float* boxA, const Shape* shA,
                             const float* boxB, const Shape* shB)
{
    float A[24];
    float B[24];
    XForm(shA, boxA[0], boxA[1], boxA[2], A + 0);
    XForm(shA, boxA[3], boxA[1], boxA[2], A + 3);
    XForm(shA, boxA[0], boxA[4], boxA[2], A + 6);
    XForm(shA, boxA[3], boxA[4], boxA[2], A + 9);
    XForm(shA, boxA[0], boxA[1], boxA[5], A + 12);
    XForm(shA, boxA[3], boxA[1], boxA[5], A + 15);
    XForm(shA, boxA[0], boxA[4], boxA[5], A + 18);
    XForm(shA, boxA[3], boxA[4], boxA[5], A + 21);
    XForm(shB, boxB[0], boxB[1], boxB[2], B + 0);
    XForm(shB, boxB[3], boxB[1], boxB[2], B + 3);
    XForm(shB, boxB[0], boxB[4], boxB[2], B + 6);
    XForm(shB, boxB[3], boxB[4], boxB[2], B + 9);
    XForm(shB, boxB[0], boxB[1], boxB[5], B + 12);
    XForm(shB, boxB[3], boxB[1], boxB[5], B + 15);
    XForm(shB, boxB[0], boxB[4], boxB[5], B + 18);
    XForm(shB, boxB[3], boxB[4], boxB[5], B + 21);

    float ax[18];
    for (int j = 0; j < 3; ++j) {
        ax[0 + j] = A[0 + j] - A[3 + j];
        ax[3 + j] = A[3 + j] - A[9 + j];
        ax[6 + j] = A[0 + j] - A[12 + j];
        ax[9 + j] = B[0 + j] - B[3 + j];
        ax[12 + j] = B[3 + j] - B[9 + j];
        ax[15 + j] = B[0 + j] - B[12 + j];
    }

    for (int k = 0; k < 6; ++k) {
        float v0 = ax[k * 3 + 0];
        float v1 = ax[k * 3 + 1];
        float v2 = ax[k * 3 + 2];
        float len2 = v0 * v0 + v1 * v1 + v2 * v2;
        float minA = 100000.0f, maxA = -100000.0f;
        float minB = 100000.0f, maxB = -100000.0f;
        Proj4A(A + 0, v0, v1, v2, len2, minA, maxA);
        Proj4A(A + 12, v0, v1, v2, len2, minA, maxA);
        Proj4B(B + 0, v0, v1, v2, len2, minB, maxB);
        Proj4B(B + 12, v0, v1, v2, len2, minB, maxB);
        if (maxA < minB || maxB < minA)
            return false;
    }
    return true;
}
