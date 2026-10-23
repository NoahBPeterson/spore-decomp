// s010aed40.cpp -- Havok 3.1.0 powered-chain solver internals.
//
//   0x010aed40  _hkPoweredChain_RestoreVelocityValue        (straight-line x87)
//   0x010aef10  _hkPoweredChain_AccumulateConstraintVelocities (unnamed in the
//               dev-build PDB; sits between RestoreVelocityValue and
//               ScanAndDisableMotors, one loop over the chain's constraints)
//   0x010af330  _hkPoweredChain_ScanAndDisableMotors
//
// All three are "identical-code" Havok routines built by the dev toolset
// (cl 13.10.x, /O2, whole-program optimisation): every helper is inlined, there
// are no calls at all, and the math is pure x87.  The reconstructions below
// follow the disassembly's data flow (same input loads, same stores, same loop
// bounds) but the compiler's x87 register schedule and exact expression nesting
// could not be recovered, so they are not byte-exact.
//
#include "types.h"

typedef float hkReal;

struct hkVector4 { hkReal x, y, z, w; };

// ---------------------------------------------------------------------------
// 0x010aed40 -- _hkPoweredChain_RestoreVelocityValue
//
// Recomputes one constraint row's velocity value from the pivot offsets of the
// two bodies it connects, the row's rotation, and the stored per-row offset,
// and writes it back into the runtime velocity array at out[i*8 + k + 4].
// @ 0x10aed40
void _hkPoweredChain_RestoreVelocityValue(int i, int k, const unsigned char* d, hkReal* out)
{
    const int*           idx = *(const int* const*)(d + 0x18);
    const unsigned char* ref = *(const unsigned char* const*)(d + 0x1c);
    const unsigned char* P   = ref + idx[i];
    const unsigned char* Q   = ref + idx[i + 1];

    const unsigned char* row = *(const unsigned char* const*)(d + 0x24) + i * 0x4c;
    const hkReal*        T   = (const hkReal*)(row + k * 24);
    const hkReal*        m   = (const hkReal*)(*(const unsigned char* const*)(d + 0x14) + (k + 3 * i) * 32);

    hkVector4 a;                                    // body-A pivot displacement
    a.x = *(const hkReal*)(P + 0x20) - *(const hkReal*)(P + 0x50);
    a.y = *(const hkReal*)(P + 0x24) - *(const hkReal*)(P + 0x54);
    a.z = *(const hkReal*)(P + 0x28) - *(const hkReal*)(P + 0x58);

    hkVector4 b;                                    // body-B pivot displacement
    b.x = *(const hkReal*)(Q + 0x20) - *(const hkReal*)(Q + 0x50);
    b.y = *(const hkReal*)(Q + 0x24) - *(const hkReal*)(Q + 0x54);
    b.z = *(const hkReal*)(Q + 0x28) - *(const hkReal*)(Q + 0x58);

    hkVector4 p;                                    // A reference (P + 0x50)
    p.x = *(const hkReal*)(P + 0x50);
    p.y = *(const hkReal*)(P + 0x54);
    p.z = *(const hkReal*)(P + 0x58);
    p.w = *(const hkReal*)(P + 0x5c);

    hkVector4 q;                                    // B reference (Q + 0x50)
    q.x = *(const hkReal*)(Q + 0x50);
    q.y = *(const hkReal*)(Q + 0x54);
    q.z = *(const hkReal*)(Q + 0x58);
    q.w = *(const hkReal*)(Q + 0x5c);

    // (a, b) projected through the row rotation, plus the (p, q) terms and the
    // stored row offset T[4] / T[5].
    hkReal v = (a.x * m[0] + b.x * m[4])
             + (a.y * m[1] + b.y * m[5])
             + (a.z * m[2] + b.z * m[6])
             + (p.z * m[4] + q.x * m[6])
             + (p.z * m[2])
             + (p.w * m[5] + p.y * m[1])
             + T[4] - T[5];

    out[i * 8 + k + 4] = v;
}

// ---------------------------------------------------------------------------
// 0x010aef10 -- _hkPoweredChain_AccumulateConstraintVelocities
//
// Zeroes the two 4-vector accumulators at *out and then, walking the chain's
// constraints from the last to the first, adds each constraint's transformed
// pivot velocity into them.
// @ 0x10aef10
void _hkPoweredChain_AccumulateConstraintVelocities(const unsigned char* chain, hkVector4* out)
{
    const int    n     = *(const int*)(chain + 4);
    const hkReal* basis = (const hkReal*)*(const unsigned char* const*)(chain + 0x20);
    const hkReal* pos   = (const hkReal*)(*(const unsigned char* const*)(chain + 0x28) + 0x20);

    out[0].x = out[0].y = out[0].z = out[0].w = 0.0f;
    out[1].x = out[1].y = out[1].z = out[1].w = 0.0f;

    for (int i = n - 1; i >= 0; --i)
    {
        const hkReal* m  = basis + i * 8;           // 0x20 bytes per row
        const hkReal* v  = pos + i * 8;             // constraint pivot/velocity

        // Rotate the constraint's pivot velocity into chain space.
        hkVector4 r;
        r.x = v[0] * m[0x10] + v[1] * m[4] + v[2] * m[0];
        r.y = v[0] * m[0x14] + v[1] * m[5] + v[2] * m[1];
        r.z = v[0] * m[0x18] + v[1] * m[6] + v[2] * m[2];
        r.w = 0.0f;

        hkVector4 s;
        s.x = v[0] * m[0x40] + v[1] * m[0x50] + v[2] * m[0x30];
        s.y = v[0] * m[0x44] + v[1] * m[0x54] + v[2] * m[0x34];
        s.z = v[0] * m[0x48] + v[1] * m[0x58] + v[2] * m[0x38];
        s.w = 0.0f;

        out[0].x += r.x; out[0].y += r.y; out[0].z += r.z;
        out[1].x += s.x; out[1].y += s.y; out[1].z += s.z;
        out[1].w += m[0x154] * m[0x178] + m[0x168] * m[0x158];
    }
}

// ---------------------------------------------------------------------------
// 0x010af330 -- _hkPoweredChain_ScanAndDisableMotors
//
// Walks every constraint row from last to first, accumulates the row's
// angular/linear velocity error, and for each of the three angular motors
// (whose enable status occupies two bits of the row's status byte at
// flags[i*0x4c], masks 0x03 / 0x0c / 0x30) keeps the largest error that is
// still below the row's stored threshold.  Finally the winning motor's status
// is updated: 1 if its error is below the threshold, 3 if at/above it.
// @ 0x10af330
void _hkPoweredChain_ScanAndDisableMotors(const unsigned char* chain,
                                          int* outConstraint, int* outMotor, hkReal* outValue)
{
    const int            n      = *(const int*)(chain + 4);
    const unsigned char* flags  = *(const unsigned char* const*)(chain + 0x24);
    const unsigned char* basis  = *(const unsigned char* const*)(chain + 0x20);
    const unsigned char* pivots = *(const unsigned char* const*)(chain + 0x28) + 0x20;

    hkReal best      = -1.0f;                        // [esp + 0x0c]
    int    bestCon   = -1;                           // [esp + 0x14]
    int    bestMotor = -1;                           // [esp + 0x18]

    hkVector4 ang = { 0.0f, 0.0f, 0.0f, 0.0f };      // [esp + 0x20]
    hkVector4 lin = { 0.0f, 0.0f, 0.0f, 0.0f };      // [esp + 0x30]

    for (int i = n - 1; i >= 0; --i)
    {
        const unsigned char* b = basis + i * 0x3c0;
        const hkReal*        v = (const hkReal*)(pivots + i * 0x20);

        // Row's angular velocity error (columns at +0x180 .. +0x1b8).
        ang.x = v[0] * (*(const hkReal*)(b + 0x1b0)) + v[1] * (*(const hkReal*)(b + 0x1a0)) + v[2] * (*(const hkReal*)(b + 0x180));
        ang.y = v[0] * (*(const hkReal*)(b + 0x1b4)) + v[1] * (*(const hkReal*)(b + 0x1a4)) + v[2] * (*(const hkReal*)(b + 0x184));
        ang.z = v[0] * (*(const hkReal*)(b + 0x1b8)) + v[1] * (*(const hkReal*)(b + 0x1a8)) + v[2] * (*(const hkReal*)(b + 0x188));

        lin.x = v[0] * (*(const hkReal*)(b + 0x190)) + v[1] * (*(const hkReal*)(b + 0x1a0)) + v[2] * (*(const hkReal*)(b + 0x1b0));
        lin.y = v[0] * (*(const hkReal*)(b + 0x194)) + v[1] * (*(const hkReal*)(b + 0x1a4)) + v[2] * (*(const hkReal*)(b + 0x1b4));
        lin.z = v[0] * (*(const hkReal*)(b + 0x198)) + v[1] * (*(const hkReal*)(b + 0x1a8)) + v[2] * (*(const hkReal*)(b + 0x1b8));

        // The stored velocity is subtracted (vectors at v - 0x18 / v - 8).
        const hkReal* prev = v - 8;
        hkReal ex = ang.x - prev[0], ey = ang.y - prev[1], ez = ang.z - prev[2];
        hkReal fx = lin.x - prev[3], fy = lin.y - prev[4], fz = lin.z - prev[5];

        const unsigned char status = flags[i * 0x4c];

        if ((status & 0x03) == 0)
        {
            hkReal d = (*(const hkReal*)(b + 0x188) * 2.0f - ex) - (*(const hkReal*)(b + 0x184) * 2.0f - fy);
            if (!(d < best)) { }
            if (d >= best) { best = d; bestCon = i; bestMotor = 0; }
        }
        if ((status & 0x0c) == 0)
        {
            hkReal d = (*(const hkReal*)(b + 0x1a0) * 2.0f - ey) - (*(const hkReal*)(b + 0x19c) * 2.0f - fx);
            if (d >= best) { best = d; bestCon = i; bestMotor = 1; }
        }
        if ((status & 0x30) == 0)
        {
            hkReal d = (*(const hkReal*)(b + 0x1b8) * 2.0f - ez) - (*(const hkReal*)(b + 0x1b4) * 2.0f - fz);
            if (d >= best) { best = d; bestCon = i; bestMotor = 2; }
        }
    }

    if (bestCon < 0)
        return;

    unsigned char*       row = (unsigned char*)flags + bestCon * 0x4c;
    const hkReal*        lim = (const hkReal*)(row + bestMotor * 0x18);
    unsigned int         bits = (best > lim[1]) ? 3u : 1u;
    unsigned int         shift = (unsigned int)bestMotor * 2u;
    unsigned char        mask = (unsigned char)(3u << shift);

    *row = (unsigned char)((*row & ~mask) | ((unsigned char)bits << shift));
    *outConstraint = bestCon;
    *outMotor = bestMotor;
    (void)outValue;
}
