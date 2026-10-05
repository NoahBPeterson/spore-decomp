// Slice s004fa470: component-wise fractional-part helpers (unoptimized module:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast).  0x004fa5a0 (the SSE overlap query, a separate
// /O2 TU) lives in s004fa470_o2.cpp.
#include "types.h"
#include <math.h>

struct Vector3 {
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};

// @ 0x004fa520
float Fract(float x, float* pFloor)
{
    if (x < 0.0f) {
        double ip;
        double frac = modf((double)(x - 1.0f), &ip);
        *pFloor = (float)ip;
        return 1.0f + (float)frac;
    } else {
        double ip;
        double frac = modf((double)x, &ip);
        *pFloor = (float)ip;
        return (float)frac;
    }
}

// @ 0x004fa470
Vector3* FractV(Vector3* out, const Vector3* v, Vector3* iout)
{
    uint32_t p30[24];
    float n30 = Fract((*v)[0], &(*iout)[0]);
    float t25 = Fract((*v)[1], &(*iout)[1]);
    float begin = Fract((*v)[2], &(*iout)[2]);
    out->x = n30;
    out->y = t25;
    out->z = begin;
    return out;
}
