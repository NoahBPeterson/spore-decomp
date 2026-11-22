// src/game/UTFSpore_Win32/Types.cpp -- migrated from slice(s) s0095df60, s0095eeb0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Types.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) double __cdecl sin(double);
extern "C" __declspec(dllimport) double __cdecl cos(double);
extern "C" char __cdecl MatInvertFull(void*, void*);                    // 0x0095E0B0
extern "C" void __cdecl FUN_0045EAC0(void* out, const void* a, const void* b); // 0x0045EAC0
extern "C" double __cdecl Det33(const float* m);                          // 0x0095E040
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)

// ---- items of slice s0095eeb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) double __cdecl sin(double);
extern "C" __declspec(dllimport) double __cdecl cos(double);
extern "C" char __cdecl MatInvertFull(void*, void*);                    // 0x0095E0B0
extern "C" void __cdecl FUN_0045EAC0(void* out, const void* a, const void* b); // 0x0045EAC0
struct CM;
struct CMV { void BuildMat33V(const float* src); };  // 0x0095F0F0 (callee result unused by Inv3)
extern "C" double __cdecl Det33(const float* m);                          // 0x0095E040
extern "C" CM* __cdecl Inv3(CM* out, const float* in, float* det);       // 0x0095F490
struct CM {
    float m[16];

    void  TransformPoint3(float* out, const float* v);
    void  TransformPoint3B(float* out, const float* v);
    float* TransformPoint4(float* out, const float* v);
    __declspec(noinline) void* BuildMat33(const float* src);
    void  SetRotationAtLeast2(float* axis, float angle);
    void  Invert();
    void  Multiply(const float* o);
    CM*   SetAxes(float* a, float* b, float* c);
};
// ---- items of slice s0095eeb0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" CM* __cdecl Inv3(CM* out, const float* in, float* det);       // 0x0095F490

// ---- items of slice s0095df60 begin
#pragma intrinsic(sin, cos)
// ---- items of slice s0095df60 end

// @ 0x0095e040
float FUN_0095e040(const float* m)
{
    return (((((m[2] * m[4]) * m[9] +
              ((m[1] * m[6]) * m[8] + (m[0] * m[5]) * m[10])) -
             (m[0] * m[6]) * m[9]) -
            (m[1] * m[10]) * m[4]) -
           m[2] * (m[5] * m[8]));
}

// @ 0x0095e0b0
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

// @ 0x0095f090
CM* CM::SetAxes(float* a, float* b, float* c)
{
    void* self = this;
    ((float*)self)[0] = a[0]; ((float*)self)[1] = a[1]; ((float*)self)[2] = a[2]; ((float*)self)[3] = a[3];
    ((float*)self)[4] = b[0]; ((float*)self)[5] = b[1]; ((float*)self)[6] = b[2]; ((float*)self)[7] = b[3];
    ((float*)self)[8] = c[0]; ((float*)self)[9] = c[1]; ((float*)self)[10] = c[2]; ((float*)self)[11] = c[3];
    return this;
}

// @ 0x0095f0f0
void* CM::BuildMat33(const float* src)
{
    int pad = (int)0xcccccccc;
    int* mi = (int*)m;
    const int* si = (const int*)src;
    mi[0] = si[0]; mi[1] = si[1]; mi[2] = si[2]; mi[3] = pad;
    mi[4] = si[4]; mi[5] = si[5]; mi[6] = si[6]; mi[7] = pad;
    mi[8] = si[8]; mi[9] = si[9]; mi[10] = si[10]; mi[11] = pad;
    return this;
}

// @ 0x0095f1c0
float* CM::TransformPoint4(float* out, const float* v)
{
    float x = v[0], y = v[1], z = v[2];
    float r0 = m[12] + (m[8] * z + (m[4] * y + x * m[0]));
    float r1 = m[13] + (m[9] * z + (m[5] * y + m[1] * x));
    float r2 = m[14] + (m[10] * z + (m[6] * y + m[2] * x));
    float w = m[15] + (m[11] * z + (m[7] * y + m[3] * x));
    out[0] = r0;
    out[1] = r1;
    out[2] = r2;
    if (w != 1.0f) {
        w = 1.0f / w;
        out[0] = w * r0;
        out[1] = w * r1;
        out[2] = w * r2;
    }
    return out;
}

// @ 0x0095f320
void BuildRotation(float* out, float* axis, float angle)
{
    float s = (float)sin(angle);
    float c = (float)cos(angle);
    float t = 1.0f - c;
    float x = axis[0], y = axis[1], z = axis[2];
    float xs = x * s, ys = y * s, zs = z * s;
    out[0] = x * (x * t) + c;
    out[1] = y * (x * t) + zs;
    out[2] = z * (x * t) - ys;
    out[3] = 0.0f;
    out[5] = y * (y * t) + c;
    out[7] = 0.0f;
    out[4] = x * (y * t) - zs;
    out[6] = z * (y * t) + xs;
    out[11] = 0.0f;
    out[8] = x * (z * t) + ys;
    out[9] = y * (z * t) - xs;
    out[10] = z * (z * t) + c;
    out[12] = 0.0f;
    out[13] = 0.0f;
    out[14] = 0.0f;
    out[15] = 1.0f;
}

// @ 0x0095f490
extern "C" CM* __cdecl Inv3(CM* out, const float* in, float* det)
{
    double d = *det = (float)Det33(in);
    if (d == 0.0)
        return out;
    float inv = 1.0f / *det;
    __declspec(align(16)) float tmp[12];
    float* p = tmp;
    volatile int i = 2;
    volatile int n = 3;
    do {
        int a = (i - 1) % 3;
        int b = i % 3;
        p[0] = (in[a * 4 + 1] * in[b * 4 + 2] - in[a * 4 + 2] * in[b * 4 + 1]) * inv;
        p[4] = (in[a * 4 + 2] * in[b * 4] - in[b * 4 + 2] * in[a * 4]) * inv;
        p[8] = (in[b * 4 + 1] * in[a * 4] - in[a * 4 + 1] * in[b * 4]) * inv;
        i++;
        n--;
        p++;
    } while (n != 0);
    ((CMV*)out)->BuildMat33V(tmp);
    return out;
}

// @ 0x0095f5c0
void CM::SetRotationAtLeast2(float* axis, float angle)
{
    if (((int*)m)[16] < 2)
        ((int*)m)[16] = 2;
    float rot[16];
    BuildRotation(rot, axis, angle);
    float tmp[16];
    FUN_0045EAC0(tmp, this, rot);
    for (int i = 0; i < 16; i++)
        m[i] = tmp[i];
}

// @ 0x0095f620
void CM::Invert()
{
    int type = *(int*)&m[16];
    if (type == 1) {
        float f1 = m[9];
        float f6 = 1.0f / m[10];
        m[10] = f6;
        float f2 = m[11];
        float f7 = 1.0f / m[15];
        m[15] = f7;
        float f5 = 1.0f / m[0];
        m[0] = f5;
        m[12] = -(m[12] * f5);
        m[13] = -(f1 * f6);
        m[14] = -(f2 * f7);
        m[15] = 1.0f;
    } else if (type == 2) {
        float axes[12];
        ((CM*)axes)->SetAxes(m + 8, m + 4, m);
        float inv[12];
        float det;
        Inv3((CM*)inv, axes, &det);
        for (int i = 0; i < 12; i++)
            m[i] = inv[i];
        m[3] = 0.0f; m[7] = 0.0f; m[11] = 0.0f;
        m[12] = -m[12]; m[13] = -m[13]; m[14] = -m[14];
        m[15] = 1.0f;
    } else if (type == 3) {
        if (MatInvertFull(this, this))
            *(int*)&m[16] = *(int*)&m[16];
        else
            *(int*)&m[16] = 4;
    }
}
