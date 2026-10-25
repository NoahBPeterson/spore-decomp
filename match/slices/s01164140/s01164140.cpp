// Slice s01164140: terrain weight-plane rotation.
//
//   0x01164140  in-place 45-degree butterfly between two 576-float weight planes
//
// The retail body reads its buffer pointer out of EAX (custom register
// convention: `lea ecx,[eax+0x900]` with no stack argument), so it cannot be
// expressed as a normal parameter.  It is modelled here as the plain cdecl
// `void FUN_01164140(float*)` used by the caller slice (0x01164200 FillWeightMap
// calls it with the buffer); that costs the 4-byte `mov eax,[esp+4]` prologue
// load but everything after it is the retail instruction sequence.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

// Both planes of the weight map, in floats.  0x900 bytes / 4 = 576 per plane.
static const int kPlaneFloats = 576;

// cos(45 deg) == sin(45 deg); retail loads it from 0x013ef584.
static const float kSqrtHalf = 0.70710677f;

// Each step rotates one xyz triple of the low plane against the matching triple
// of the high plane:
//
//   lo = (lo + hi) * kSqrtHalf
//   hi = (lo - hi) * kSqrtHalf
//
// (the rotated pair is written with the sum in the low plane and the difference
// in the high plane, which is a 45-degree rotation of each component pair).
//
// @ 0x01164140
void FUN_01164140(float* dst)
{
    const float s = kSqrtHalf;

    for (float* p = dst; p != dst + kPlaneFloats; p += 3) {
        // The x component sums as (lo + hi), y and z as (hi + lo); adding
        // floats is commutative but /fp:fast keeps the retail operand order.
        const float lo0 = p[0];
        const float hi0 = p[kPlaneFloats + 0];
        const float lo1 = p[1];
        const float hi1 = p[kPlaneFloats + 1];
        const float lo2 = p[2];
        const float hi2 = p[kPlaneFloats + 2];

        p[0] = (lo0 + hi0) * s;
        p[kPlaneFloats + 0] = (lo0 - hi0) * s;
        p[1] = (hi1 + lo1) * s;
        p[kPlaneFloats + 1] = (lo1 - hi1) * s;
        p[2] = (hi2 + lo2) * s;
        p[kPlaneFloats + 2] = (lo2 - hi2) * s;
    }
}
