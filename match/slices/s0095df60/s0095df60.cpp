// Slice s0095df60 -- 4x4 matrix helpers (row-major float[16] + int flags at 0x40).
#include "types.h"
#include <math.h>
#pragma intrinsic(sin, cos)

struct Mat4 {
    float m[16];
    int flags;     // 0x40: 0 identity, 1 translate/scale, 2 rotated, 3 projective

    void SetIdentity();
    void SetScaleTranslate(const float* t, const float* s);
    void Translate(const float* v);
    void Scale(const float* s);
    void RotateX(float a);
    void RotateY(float a);
    void RotateZ(float a);
    void AddPerspectiveCol(float d);
};

// @ 0x95df60
void FUN_0095df60(float* out, const float* v, const float* m)
{
    float x = v[0], y = v[1], z = v[2];
    out[0] = z * m[8] + (y * m[4] + x * m[0]);
    out[1] = m[9] * z + (m[1] * x + m[5] * y);
    out[2] = m[10] * z + (m[2] * x + m[6] * y);
}

// @ 0x95e040
float FUN_0095e040(const float* m)
{
    return (((((m[2] * m[4]) * m[9] +
              ((m[1] * m[6]) * m[8] + (m[0] * m[5]) * m[10])) -
             (m[0] * m[6]) * m[9]) -
            (m[1] * m[10]) * m[4]) -
           m[2] * (m[5] * m[8]));
}

// @ 0x95e0b0
bool FUN_0095e0b0(const float* p, float* o)
{
    float fVar1 = p[10];
    float fVar2 = p[0xb];
    float fVar3 = p[0xe];
    float fVar4 = p[9];
    float fVar5 = p[5];
    float fVar6 = p[4];
    float fVar7 = p[6];
    float fVar8 = p[7];
    float fVar9 = p[8];
    float fVar10 = p[0xc];
    float fVar29 = p[0xd];
    float fVar11 = p[0xf];
    float fVar21 = fVar11 * fVar1 - fVar3 * fVar2;
    float fVar17 = fVar29 * fVar2 - fVar11 * fVar4;
    float fVar12 = fVar11 * fVar4 - fVar29 * fVar2;
    float fVar27 = fVar3 * fVar4 - fVar29 * fVar1;
    float fVar28 = (fVar27 * fVar8 + fVar17 * fVar7) + fVar21 * fVar5;
    float fVar24 = fVar10 * fVar2 - fVar11 * fVar9;
    float fVar18 = fVar3 * fVar9 - fVar10 * fVar1;
    float fVar19 = -((fVar18 * fVar8 + fVar24 * fVar7) + fVar21 * fVar6);
    float fVar13 = fVar10 * fVar1 - fVar3 * fVar9;
    float fVar22 = fVar29 * fVar9 - fVar10 * fVar4;
    float fVar25 = (fVar22 * fVar8 + fVar12 * fVar6) + fVar24 * fVar5;
    float fVar14 = -((fVar13 * fVar5 + fVar22 * fVar7) + fVar27 * fVar6);
    float fVar15 = ((fVar14 * p[3] + fVar25 * p[2]) + fVar19 * p[1]) + fVar28 * p[0];
    if (fabsf(fVar15) < 1e-06f) {
        return false;
    }
    fVar15 = 1.0f / fVar15;
    float fVar16 = fVar15 * p[0];
    float fVar20 = fVar15 * p[1];
    float fVar23 = fVar15 * p[2];
    float fVar26 = fVar15 * p[3];
    o[0] = fVar15 * fVar28;
    o[1] = -((fVar27 * fVar26 + fVar17 * fVar23) + fVar21 * fVar20);
    fVar28 = fVar11 * fVar7 - fVar3 * fVar8;
    float fVar30 = fVar3 * fVar5 - fVar29 * fVar7;
    o[2] = ((fVar29 * fVar8 - fVar11 * fVar5) * fVar23 + fVar30 * fVar26) + fVar28 * fVar20;
    float fVar31 = fVar2 * fVar7 - fVar1 * fVar8;
    fVar17 = fVar1 * fVar5 - fVar4 * fVar7;
    o[3] = -(((fVar4 * fVar8 - fVar2 * fVar5) * fVar23 + fVar17 * fVar26) + fVar31 * fVar20);
    o[4] = fVar15 * fVar19;
    o[5] = (fVar18 * fVar26 + fVar24 * fVar23) + fVar21 * fVar16;
    fVar18 = fVar10 * fVar8 - fVar11 * fVar6;
    o[6] = -(((fVar3 * fVar6 - fVar10 * fVar7) * fVar26 + fVar18 * fVar23) + fVar28 * fVar16);
    fVar19 = fVar9 * fVar8 - fVar2 * fVar6;
    o[7] = ((fVar1 * fVar6 - fVar9 * fVar7) * fVar26 + fVar19 * fVar23) + fVar31 * fVar16;
    o[8] = fVar15 * fVar25;
    o[9] = -((fVar22 * fVar26 + fVar12 * fVar16) + fVar24 * fVar20);
    fVar12 = fVar29 * fVar6 - fVar10 * fVar5;
    o[10] = ((fVar11 * fVar5 - fVar29 * fVar8) * fVar16 + fVar12 * fVar26) + fVar18 * fVar20;
    fVar29 = fVar4 * fVar6 - fVar9 * fVar5;
    o[0xb] = -(((fVar2 * fVar5 - fVar4 * fVar8) * fVar16 + fVar29 * fVar26) + fVar19 * fVar20);
    o[0xc] = fVar15 * fVar14;
    o[0xd] = (fVar13 * fVar20 + fVar22 * fVar23) + fVar27 * fVar16;
    o[0xe] = -(((fVar10 * fVar7 - fVar3 * fVar6) * fVar20 + fVar12 * fVar23) + fVar30 * fVar16);
    o[0xf] = ((fVar9 * fVar7 - fVar1 * fVar6) * fVar20 + fVar29 * fVar23) + fVar17 * fVar16;
    return true;
}

// @ 0x95e7a0
void Mat4::SetIdentity()
{
    flags = 0;
    m[0] = 1.0f; m[1] = 0; m[2] = 0; m[3] = 0;
    m[4] = 0; m[5] = 1.0f; m[6] = 0; m[7] = 0;
    m[8] = 0; m[9] = 0; m[10] = 1.0f; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1.0f;
}

// @ 0x95e810
void Mat4::SetScaleTranslate(const float* t, const float* s)
{
    flags = 1;
    m[0] = s[0]; m[1] = 0; m[2] = 0; m[3] = 0;
    m[4] = 0; m[6] = 0; m[7] = 0; m[5] = s[1];
    m[8] = 0; m[9] = 0; m[11] = 0; m[10] = s[2];
    m[12] = t[0]; m[13] = t[1]; m[14] = t[2]; m[15] = 1.0f;
}

// @ 0x95e890
void Mat4::Translate(const float* v)
{
    if (flags == 0) flags = 1;
    float w = m[15];
    float x = v[0], y = v[1], z = v[2];
    m[12] = m[12] + w * x;
    m[13] = m[13] + w * y;
    m[14] = m[14] + w * z;
    m[15] = m[15] + w * 0.0f;
    if (flags == 3) {
        w = m[11];
        m[8] = m[8] + w * x;
        m[9] = m[9] + w * y;
        m[10] = m[10] + w * z;
        m[11] = m[11] + w * 0.0f;
        w = m[7];
        m[4] = m[4] + w * x;
        m[5] = m[5] + w * y;
        m[6] = m[6] + w * z;
        m[7] = m[7] + w * 0.0f;
        w = m[3];
        m[1] = w * y + m[1];
        m[0] = m[0] + w * x;
        m[2] = w * z + m[2];
        m[3] = m[3] + w * 0.0f;
    }
}

// @ 0x95ea30
void Mat4::Scale(const float* s)
{
    if (flags == 0) flags = 1;
    m[0] = s[0] * m[0];
    m[1] = m[1] * s[1];
    m[2] = m[2] * s[2];
    m[4] = m[4] * s[0];
    m[5] = m[5] * s[1];
    m[6] = m[6] * s[2];
    m[8] = m[8] * s[0];
    m[9] = m[9] * s[1];
    m[10] = m[10] * s[2];
    m[12] = m[12] * s[0];
    m[13] = m[13] * s[1];
    m[14] = m[14] * s[2];
}

// @ 0x95eb00
void Mat4::RotateX(float a)
{
    if (flags < 2) flags = 2;
    float f6 = m[6];
    float sn = (float)sin((double)a);
    float f1 = m[1];
    float f9 = m[9];
    float f13 = m[13];
    float cs = (float)cos((double)a);
    m[1] = f1 * cs - m[2] * sn;
    m[2] = m[2] * cs + f1 * sn;
    m[6] = f6 * cs + m[5] * sn;
    m[5] = m[5] * cs - f6 * sn;
    m[9] = f9 * cs - m[10] * sn;
    m[10] = m[10] * cs + f9 * sn;
    m[13] = f13 * cs - m[14] * sn;
    m[14] = m[14] * cs + f13 * sn;
}

// @ 0x95ec30
void Mat4::RotateY(float a)
{
    if (flags < 2) flags = 2;
    float f6 = m[6];
    float sn = (float)sin((double)a);
    float f0 = m[0];
    float f8 = m[8];
    float f12 = m[12];
    float cs = (float)cos((double)a);
    m[0] = m[2] * sn + f0 * cs;
    m[2] = m[2] * cs - f0 * sn;
    m[6] = f6 * cs - m[4] * sn;
    m[4] = f6 * sn + m[4] * cs;
    m[8] = m[10] * sn + f8 * cs;
    m[10] = m[10] * cs - f8 * sn;
    m[12] = m[14] * sn + f12 * cs;
    m[14] = m[14] * cs - f12 * sn;
}

// @ 0x95ed60
void Mat4::RotateZ(float a)
{
    if (flags < 2) flags = 2;
    float f4 = m[4];
    float sn = (float)sin((double)a);
    float f1 = m[1];
    float f9 = m[9];
    float cs = (float)cos((double)a);
    m[1] = f1 * cs + m[0] * sn;
    m[0] = m[0] * cs - f1 * sn;
    m[9] = f9 * cs + m[8] * sn;
    m[8] = m[8] * cs - f9 * sn;
    m[4] = f4 * cs - m[5] * sn;
    m[5] = m[5] * cs + f4 * sn;
}

// @ 0x95ee40
void Mat4::AddPerspectiveCol(float d)
{
    if (flags < 3) flags = 3;
    d = 1.0f / d;
    m[3] = m[2] * d + m[3];
    m[7] = m[6] * d + m[7];
    m[11] = m[10] * d + m[11];
    m[15] = m[14] * d + m[15];
}
