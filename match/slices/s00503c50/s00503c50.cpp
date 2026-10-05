// w1g1 slice s00503c50 -- single large function at 0x503c50.
//
// 0x503c50 is a 5402-byte /Od SSE segment-vs-AABB (slab) classifier:
//   unsigned __cdecl f(float x0, float y0, float z0,
//                      float dx, float dy, float dz, const float* box)
// box points at 6 floats (three min / three max planes).  The original is a huge
// hand-unrolled boolean tree of comiss/mulss/subss early-outs (Ghidra renders it
// as ~200 lines of nested if/else); every comparison reloads one of the six
// scalar parameters through the frame because they are also indexed as a vector.
//
// This 5.4 KB function is far past the per-function budget (see the batch lessons
// on oversized functions), so only a behavior skeleton is provided here: the
// signature and the directional slab test are reproduced, but the original's
// exact early-out tree and instruction schedule are not.  Recorded as PARTIAL.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE (movss/comiss, x87 not used for these).

typedef unsigned int uint32_t;

// @ 0x00503c50  (PARTIAL skeleton)
uint32_t __cdecl SegmentAABBTouches(float x0, float y0, float z0,
                                    float dx, float dy, float dz,
                                    const float* box)
{
    // box[0..2] = max corner, box[3..5] = min corner (as compared in the original).
    const float bxLo = box[3], byLo = box[4], bzLo = box[5];
    const float bxHi = box[0], byHi = box[1], bzHi = box[2];

    // Directional inside test (the first three branches of the original):
    // each component must point toward the box when the start is outside it.
    float t0 = 0.0f, t1 = 1.0f;

    // X slab
    if (dx == 0.0f) {
        if (x0 < bxLo || bxHi < x0) return 0;
    } else {
        float a = (bxLo - x0) / dx, b = (bxHi - x0) / dx;
        if (a > b) { float s = a; a = b; b = s; }
        if (a > t0) t0 = a;
        if (b < t1) t1 = b;
    }
    // Y slab
    if (dy == 0.0f) {
        if (y0 < byLo || byHi < y0) return 0;
    } else {
        float a = (byLo - y0) / dy, b = (byHi - y0) / dy;
        if (a > b) { float s = a; a = b; b = s; }
        if (a > t0) t0 = a;
        if (b < t1) t1 = b;
    }
    // Z slab
    if (dz == 0.0f) {
        if (z0 < bzLo || bzHi < z0) return 0;
    } else {
        float a = (bzLo - z0) / dz, b = (bzHi - z0) / dz;
        if (a > b) { float s = a; a = b; b = s; }
        if (a > t0) t0 = a;
        if (b < t1) t1 = b;
    }

    return (t0 <= t1) ? 1u : 0u;
}
