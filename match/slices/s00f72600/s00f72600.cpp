// Slice s00f72600 -- 0x0f726xx region: three terrain-contact helpers that share
// a "block" object (flag word, scale, bias vector, 3x3 basis, radius) and the
// terrain-map owner reached through ecx.  Each transforms a point into the
// block's space, clamps it against a radius and writes a contact point, an
// optional normal and (for one of them) a quaternion back out.
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (default /GS on).

#include "types.h"

// ---------------------------------------------------------------------------
// The "block" (5th stack argument of every function below): flag word at +0x00,
// scale at +0x10, bias vector at +0x04..+0x0c, 3x3 basis at +0x14..+0x34 and a
// radius offset at +0x38.  FUN_007cda70 (defined in the binary, called with the
// block in ecx) subtracts the bias, scales by 1/scale and applies the basis to
// the first three floats of its argument, in place.
// ---------------------------------------------------------------------------
struct Blk {
    uint16_t f00;                 // +0x00  flags
    uint16_t f02;                 // +0x02
    float    f04;                 // +0x04  bias.x
    float    f08;                 // +0x08  bias.y
    float    f0c;                 // +0x0c  bias.z
    float    f10;                 // +0x10  scale
    float    f14;                 // +0x14  basis row 0
    float    f18;                 // +0x18
    float    f1c;                 // +0x1c
    float    f20;                 // +0x20  basis row 1
    float    f24;                 // +0x24
    float    f28;                 // +0x28
    float    f2c;                 // +0x2c  basis row 2
    float    f30;                 // +0x30
    float    f34;                 // +0x34
    float    f38;                 // +0x38  radius offset
    void FUN_007cda70(float* p);  // 0x007cda70
};

// The terrain map (only GetFloat is reached here).  It returns an x87 value in
// st(0), so it is modelled as returning double (the x86 x87 return convention).
struct TerrainMap {
    double FUN_00f8d620(float* p); // 0x00f8d620 (returns in st(0))
};

// The owner object handed to us in ecx; only its tail is touched.
struct Sim {
    char         m00[0xc];        // +0x00
    float        m0c;             // +0x0c
    float        m10;             // +0x10
    float        m14;             // +0x14
    TerrainMap*  m18;             // +0x18
    char FUN_00f72600(float param_2, float* param_3, float* param_4, float* param_5, void* param_6, int arg6);
    char FUN_00f72a80(float* param_2, float* param_3, float* param_4, uint32_t* param_5, void* param_6, int arg6);
    char FUN_00f72e00(float param_2, uint32_t param_3, float* param_4, float* param_5, void* param_6, int arg6);
};

// The orthonormal-basis builder (0x00a81b80) and the matrix->quaternion
// converter (rw::math::fpu::QuaternionFromMatrix33<float,0>, 0x00472b80); both
// are plain __cdecl and both are defined in the binary.
extern "C" void   FUN_00a81b80(float* dir, float* out);            // 0x00a81b80
extern "C" float* FUN_00472b80(float* m, float* out, float eps);   // 0x00472b80

// x87 helpers: the original evaluates these in the x87 unit.
static float fs_sqrt(float x) { __asm { fld dword ptr x }; __asm { fsqrt }; }
static float fs_abs(float x)  { __asm { fld dword ptr x }; __asm { fabs }; }

// A UV + face-index triple handed to the terrain map.
struct UVF { float u; float v; uint32_t face; };

// ---------------------------------------------------------------------------
// @ 0x00f72600
// Given a point (param_3) and a direction (param_4) plus a radius (param_2),
// transform the direction into the block's space, build the contact offset
// along it, clamp the two candidate distances against the radius and write the
// contact point into param_4 and the contact normal into param_5.
// ---------------------------------------------------------------------------
char Sim::FUN_00f72600(float param_2, float* param_3, float* param_4, float* param_5, void* param_6raw, int arg6)
{
    Blk* b = (Blk*)param_6raw;
    float m[9];                       // the 3x3 block handed to FUN_007cda70
    float fVar2, fVar3, fVar4, fVar5, fVar6, fVar7, fVar8, fVar9;
    float fStack_4;
    uint16_t uVar1;

    fVar8 = param_3[0];
    fVar7 = param_3[1];
    fVar6 = param_3[2];
    uVar1 = b->f00;
    fVar9 = param_4[0];
    fVar5 = param_4[1];
    fVar4 = param_4[2];
    fVar3 = fVar5;
    fVar2 = fVar9;
    if ((uVar1 & 2) != 0) {
        fVar2 = (b->f20 * fVar5 + b->f2c * fVar4) + b->f14 * fVar9;
        fVar3 = (b->f24 * fVar5 + b->f30 * fVar4) + b->f18 * fVar9;
        fVar4 = (b->f28 * fVar5 + b->f34 * fVar4) + b->f1c * fVar9;
    }
    fVar9 = b->f10;
    fVar2 = b->f04 + fVar9 * fVar2;
    m[7] = b->f08 + fVar9 * fVar3;
    fVar5 = fVar7;
    fVar3 = fVar8;
    if ((uVar1 & 2) != 0) {
        fVar3 = (b->f2c * fVar6 + b->f20 * fVar7) + b->f14 * fVar8;
        fVar5 = (b->f30 * fVar6 + b->f24 * fVar7) + b->f18 * fVar8;
        fVar6 = (b->f34 * fVar6 + b->f28 * fVar7) + b->f1c * fVar8;
    }
    fVar8 = b->f10;
    fStack_4 = (b->f0c + fVar9 * fVar4) + 1e-06f;
    fVar9 = b->f04 + fVar8 * fVar3;
    fVar7 = b->f08 + fVar8 * fVar5;
    param_2 = (b->f38 + this->m0c) + param_2;
    fVar6 = (b->f0c + fVar8 * fVar6) + 1e-06f;
    fVar8 = fs_sqrt(fVar2 * fVar2 + (m[7] * m[7] + fStack_4 * fStack_4));
    if (fVar8 <= param_2) {
        if (fs_sqrt(fVar9 * fVar9 + (fVar7 * fVar7 + fVar6 * fVar6)) <= param_2)
            return 0;
        if (fVar8 <= param_2) {
            m[5] = 1.0f / fVar8;
            fVar8 = m[5] * fVar2;
            m[7] = m[5] * m[7];
            m[5] = fStack_4 * m[5];
            goto LAB_00f72925;
        }
    }
    fVar8 = 1.0f / fVar8;
    m[5] = -fStack_4 * fVar8;
    m[7] = -m[7] * fVar8;
    fVar8 = fVar8 * -fVar2;
LAB_00f72925:
    fVar7 = m[7];
    m[0] = fVar8 * param_2;
    m[4] = m[7];
    m[1] = m[7] * param_2;
    m[2] = m[5] * param_2;
    if ((b->f10 != 1.0f) || ((uVar1 & 6) != 0)) {
        m[3] = fVar8;
        m[6] = m[0];
        m[7] = m[1];
        m[8] = m[2];
        b->FUN_007cda70(m);
        if ((b->f00 & 2) != 0) {
            fVar8 = (b->f1c * m[5] + b->f18 * m[4]) + b->f14 * m[3];
            fVar7 = (b->f28 * m[5] + b->f24 * m[4]) + b->f20 * m[3];
            m[5] = (b->f34 * m[5] + b->f30 * m[4]) + b->f2c * m[3];
        }
    }
    param_4[0] = m[0];
    param_4[1] = m[1];
    param_4[2] = m[2];
    param_5[0] = fVar8;
    param_5[1] = fVar7;
    param_5[2] = m[5];
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00f72a80
// Same idea as 00f72600 but takes a single point (param_2), normalises it in
// block space, offsets it by the block radius, builds an orthonormal basis from
// the direction and writes the contact point (param_3), an optional normal
// (param_4) and an optional quaternion (param_5).
// ---------------------------------------------------------------------------
char Sim::FUN_00f72a80(float* param_2, float* param_3, float* param_4, uint32_t* param_5, void* param_6raw, int arg6)
{
    Blk* b = (Blk*)param_6raw;
    float P[9];                       // P[0..2] point for FUN_007cda70, P[6..8] direction
    float basis[9];                   // orthonormal basis built from the direction
    uint32_t q24[9];                  // working copy of the basis
    float fVar7, fVar8, fVar9, fVar10, fVar11;
    float fStack_4c;

    fVar11 = param_2[0];
    fVar10 = param_2[1];
    fVar9  = param_2[2];
    fVar7 = fVar11;
    fVar8 = fVar10;
    if ((b->f00 & 2) != 0) {
        fVar7 = (b->f2c * fVar9 + b->f20 * fVar10) + fVar11 * b->f14;
        fVar8 = (b->f30 * fVar9 + b->f18 * fVar11) + b->f24 * fVar10;
        fVar9 = (b->f34 * fVar9 + b->f1c * fVar11) + b->f28 * fVar10;
    }
    fVar11 = b->f10;
    fVar10 = b->f04 + fVar11 * fVar7;
    fVar7  = b->f08 + fVar11 * fVar8;
    fVar11 = (b->f0c + fVar11 * fVar9) + 1e-06f;
    fStack_4c = fs_sqrt(fVar7 * fVar7 + (fVar10 * fVar10 + fVar11 * fVar11));
    if (1e-06f <= fStack_4c) {
        fVar8 = 1.0f / fStack_4c;
        fVar9 = -fVar7 * fVar8;
        fVar11 = -fVar11 * fVar8;
        fVar7 = b->f38 + this->m0c;
        fVar8 = fVar8 * -fVar10;
        P[0] = fVar8 * fVar7;
        P[1] = fVar9 * fVar7;
        P[2] = fVar11 * fVar7;
        P[3] = P[0];
        P[4] = P[1];
        P[5] = P[2];
        P[6] = fVar8;
        P[7] = fVar9;
        P[8] = fVar11;
        b->FUN_007cda70(P);
        param_3[0] = P[0];
        param_3[1] = P[1];
        param_3[2] = P[2];
        if (param_4 != 0) {
            if ((b->f00 & 2) != 0) {
                fVar8 = (b->f1c * P[8] + b->f18 * P[7]) + b->f14 * P[6];
                fVar9 = (b->f28 * P[8] + b->f24 * P[7]) + b->f20 * P[6];
                fVar11 = (b->f34 * P[8] + b->f30 * P[7]) + P[6] * b->f2c;
                P[3] = fVar8;
                P[4] = fVar9;
                P[5] = fVar11;
                P[6] = fVar8;
                P[7] = fVar9;
                P[8] = fVar11;
            }
            param_4[0] = fVar8;
            param_4[1] = fVar9;
            param_4[2] = fVar11;
        }
        if (param_5 != 0) {
            FUN_00a81b80(&P[6], basis);
            for (int i = 0; i < 9; ++i)
                q24[i] = ((uint32_t*)basis)[i];
            float* r = FUN_00472b80(basis, (float*)q24, 0.0f);
            param_5[0] = ((uint32_t*)r)[0];
            param_5[1] = ((uint32_t*)r)[1];
            param_5[2] = ((uint32_t*)r)[2];
            param_5[3] = ((uint32_t*)r)[3];
        }
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f72e00
// Transform the point param_4 into block space, clamp its distance against the
// radius (which is enlarged by the terrain height sampled through the map at
// this+0x18), then if the point is inside the radius renormalise it and write
// the contact point back to param_4 and the normal to param_5.
// ---------------------------------------------------------------------------
char Sim::FUN_00f72e00(float param_2, uint32_t param_3, float* param_4, float* param_5, void* param_6raw, int arg6)
{
    Blk* b = (Blk*)param_6raw;
    float blk[3];                     // contact offset, transformed in place
    UVF   local_34;                   // UV + face handed to the terrain map
    float local_28, local_24, local_20, local_1c, local_18, local_14, local_10, local_8;
    float fVar2, fVar3, fVar4, fVar5, fVar6;

    fVar5 = param_4[0];
    fVar6 = param_4[1];
    fVar4 = param_4[2];
    fVar3 = fVar6;
    fVar2 = fVar5;
    if ((b->f00 & 2) != 0) {
        fVar2 = (b->f20 * fVar6 + b->f2c * fVar4) + b->f14 * fVar5;
        fVar3 = (b->f24 * fVar6 + b->f30 * fVar4) + b->f18 * fVar5;
        fVar4 = (b->f28 * fVar6 + b->f34 * fVar4) + b->f1c * fVar5;
        blk[2] = fVar4;
        local_28 = fVar2;
        local_24 = fVar3;
        local_20 = fVar4;
    }
    fVar5 = b->f10;
    blk[0] = b->f04 + fVar5 * fVar2;
    local_14 = (b->f0c + fVar5 * fVar4) + 1e-06f;
    blk[1] = b->f08 + fVar5 * fVar3;
    fVar4 = fs_sqrt(blk[0] * blk[0] + (blk[1] * blk[1] + local_14 * local_14));
    fVar6 = fs_abs(blk[0]);
    fVar3 = fs_abs(blk[1]);
    fVar5 = fs_abs(local_14);
    if ((fVar5 < fVar6) || (fVar5 < fVar3)) {
        if (fVar3 < fVar6) {
            local_34.u = (blk[1] / blk[0] + 1.0f) * 0.5f;
            local_34.v = (local_14 / fVar6 + 1.0f) * 0.5f;
            local_34.face = 2;
            if (blk[0] < 0.0f)
                local_34.face = 3;
        } else {
            local_34.u = (local_14 / blk[1] + 1.0f) * 0.5f;
            local_34.v = (blk[0] / fVar3 + 1.0f) * 0.5f;
            if (blk[1] < 0.0f)
                local_34.face = 5;
            else
                local_34.face = 4;
        }
    } else {
        local_34.u = (blk[0] / local_14 + 1.0f) * 0.5f;
        local_34.v = (blk[1] / fVar5 + 1.0f) * 0.5f;
        if (local_14 < 0.0f)
            local_34.face = 1;
        else
            local_34.face = 0;
    }
    local_10 = this->m10 * (float)this->m18->FUN_00f8d620((float*)&local_34);
    if (local_10 <= this->m14)
        local_10 = this->m14;
    param_2 = ((b->f38 + this->m0c) + local_10) + param_2;
    if (fVar4 < param_2) {
        fVar4 = 1.0f / fVar4;
        fVar5 = fVar4 * blk[0];
        fVar6 = fVar4 * blk[1];
        local_20 = local_14 * fVar4;
        blk[0] = fVar5 * param_2;
        blk[1] = fVar6 * param_2;
        blk[2] = local_20 * param_2;
        local_8 = local_20;
        if ((b->f10 != 1.0f) || ((b->f00 & 6) != 0)) {
            local_28 = fVar5;
            local_24 = fVar6;
            local_1c = blk[0];
            local_18 = blk[1];
            local_14 = blk[2];
            b->FUN_007cda70(blk);
            if ((b->f00 & 2) != 0) {
                fVar5 = (b->f1c * local_20 + b->f18 * local_24) + b->f14 * local_28;
                fVar6 = (b->f28 * local_20 + b->f24 * local_24) + b->f20 * local_28;
                local_8 = (b->f34 * local_20 + b->f30 * local_24) + b->f2c * local_28;
            }
        }
        param_4[0] = blk[0];
        param_4[1] = blk[1];
        param_4[2] = blk[2];
        param_5[0] = fVar5;
        param_5[1] = fVar6;
        param_5[2] = local_8;
        return 1;
    }
    return 0;
}
