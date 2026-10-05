// Slice s004fa470 companion: 0x004fa5a0 overlap query, compiled from a separate /O2 TU
// (SSE vectorized).  Complete behavioural reconstruction; the original's auto-vectorized
// compress-store schedule is not reproduced, so it is listed in nonmatching.txt.
#include "types.h"
#include <math.h>

struct Vector3 { float x, y, z; };
struct SphereFields {
    float mX[4]; float mY[4]; float mZ[4];
    float mRadiusSq[4]; float mInvRadiusSq[4]; float mStrength[4]; float mScaledStrength[4];
    uint32_t mId[4];
};
struct FieldQuery {
    float mTolX[4];
    float mTolY[4];
    float mTolZ[4];
    Vector3 mPoint;
    const void* mpFields;   // +0x3c
    int mCount;             // +0x40
};

// @ 0x004fa5a0
uint32_t Query(const FieldQuery* q, int* pOut, float threshold)
{
    const Vector3& pos = q->mPoint;
    int count = q->mCount;
    const SphereFields* p = (const SphereFields*)((const char*)q->mpFields + count * 32 - 128);
    int idx = count - 1;
    int* pFirst = pOut;
    float total = 0.0f;
    int last;
    do {
        for (int k = 0; k < 4; ++k) {
            float ax = p->mX[k] - pos.x;
            float ay = p->mY[k] - pos.y;
            float az = p->mZ[k] - pos.z;
            if (ax < 0.0f) ax = -ax;
            if (ay < 0.0f) ay = -ay;
            if (az < 0.0f) az = -az;
            float dx = ax - q->mTolX[k];
            float dy = ay - q->mTolY[k];
            float dz = az - q->mTolZ[k];
            if (dx < 0.0f) dx = 0.0f;
            if (dy < 0.0f) dy = 0.0f;
            if (dz < 0.0f) dz = 0.0f;
            float d2 = dx * dx + dy * dy + dz * dz;
            float c = 0.0f;
            if (d2 < p->mRadiusSq[k]) {
                float t = d2 * p->mInvRadiusSq[k] - 1.0f;
                t = t * t;
                c = t * t * p->mStrength[k];
            }
            total += c;
            if (c > 0.0f)
                *pOut++ = idx - k;
        }
        p--;
        last = idx - 3;
        idx -= 4;
    } while (last > 0);
    if (total < threshold)
        return 0;
    return (uint32_t)(pOut - pFirst);
}
