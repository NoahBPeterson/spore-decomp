// Slice s004fa6c0: builds a picking OBB for the force-field grid cell containing a point.
// Unoptimized module (/Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast).  The ~0x2b0-byte /Od frame is
// not reproduced, so this complete reconstruction is listed in nonmatching.txt.
#include "types.h"

// Retail evaluates these scalar abs/compare expressions on the x87 stack, not in SSE.
inline double Abs(double v)
{
    volatile float rounded = (float)v;  // retail rounds each fabs result to float
    return rounded < 0.0f ? -(double)rounded : (double)rounded;
}

// pFlags is a float array whose first word is a raw sign-bit pattern, not an integer conversion.
inline float FloatBits(uint32_t bits)
{
    union { uint32_t u; float f; } v;
    v.u = bits;
    return v.f;
}

struct Vector3 { float x, y, z; };

struct Axis { float x; float y; float PaddingForAlignment[1]; };
struct Matrix33 { Axis xAxis; Axis yAxis; Axis zAxis; };

// argument of FUN_004fb880: one 128-byte field element
struct SphereFields { char pad[0x80]; };

struct ForceGrid {
    char pad00[0x0c];
    float mField0c;              // +0x0c
    char pad10[0x08];
    Vector3 mV20;                // +0x20
    Vector3 mV2c;                // +0x2c
    char pad38[0x1c];
    void BuildOBB(const Vector3* a, const Vector3* b, float* pMatrix, float* pFlags, float* pCorner);
};

SphereFields* __fastcall GetField(ForceGrid* self, int dummy, const Vector3* p); // 0x004f8f70
void __fastcall FUN_004fb880(SphereFields* self, int dummy, const Vector3* a,
                             float* b, float* c, Matrix33* d);             // 0x004fb880
Vector3* SubV(Vector3* out, const Vector3* a, const Vector3* b);            // 0x0041db10
void Cross(Vector3* out, const Vector3* a, const Vector3* b);              // 0x0044e460
void __fastcall Matrix33_ctor(Matrix33* self, int dummy, const void* src); // 0x0041cb40
extern "C" void* DAT_015db080;

// @ 0x004fa6c0
void ForceGrid::BuildOBB(const Vector3* a, const Vector3* b, float* pMatrix, float* pFlags, float* pCorner)
{
    uint32_t local_3c = *(uint32_t*)((char*)this + 0x0c) ^ 0x80000000u;
    float local_48 = 0.0f, local_44 = 0.0f, local_40 = 0.0f;
    Vector3 fieldNormal;
    fieldNormal.x = FloatBits(local_3c);
    Matrix33 local_78;
    Matrix33_ctor(&local_78, 0, &DAT_015db080);

    SphereFields* local_8 = GetField(this, 0, a);
    if (local_8) {
        uint32_t local_7c = *(uint32_t*)((char*)local_8 - 8);
        for (uint32_t local_80 = 0; local_80 < local_7c; ++local_80) {
            FUN_004fb880((SphereFields*)((char*)local_8 + local_80 * 0x80), 0,
                         a, &fieldNormal.x, &local_48, &local_78);
        }
    }
    if (pCorner) {
        pCorner[0] = local_48;
        pCorner[1] = local_44;
        pCorner[2] = local_40;
    }

    Vector3 tmp;
    Vector3 delta;
    Vector3* pfVar1 = SubV(&tmp, b, a);
    delta.x = pfVar1->x;
    delta.y = pfVar1->y;
    delta.z = pfVar1->z;

    Vector3 local_54;
    Cross(&local_54, &delta, (const Vector3*)&local_48);
    float fStack_50 = local_54.y;
    float fStack_4c = local_54.z;

    float fVar2 = delta.y * local_78.xAxis.PaddingForAlignment[0] - delta.z * local_78.xAxis.y;
    float fVar3 = (delta.y * local_78.yAxis.PaddingForAlignment[0] - delta.z * local_78.yAxis.y) - local_40;
    float fVar4 = (delta.y * local_78.zAxis.PaddingForAlignment[0] - delta.z * local_78.yAxis.PaddingForAlignment[0]) + local_44;
    float fVar5 = (delta.z * local_78.xAxis.x - delta.x * local_78.xAxis.PaddingForAlignment[0]) + local_40;
    float fVar6 = delta.z * local_78.xAxis.y - delta.x * local_78.yAxis.PaddingForAlignment[0];
    float fVar7 = (delta.z * local_78.xAxis.PaddingForAlignment[0] - delta.x * local_78.zAxis.PaddingForAlignment[0]) - local_48;
    float fVar8 = (delta.x * local_78.xAxis.y - delta.y * local_78.xAxis.x) - local_44;
    float fVar9 = (delta.x * local_78.yAxis.y - delta.y * local_78.xAxis.y) + local_48;
    float fVar10 = delta.x * local_78.yAxis.PaddingForAlignment[0] - delta.y * local_78.xAxis.PaddingForAlignment[0];

    pMatrix[0] = local_48;
    pMatrix[1] = local_44;
    pMatrix[2] = local_40;
    pFlags[0] = fieldNormal.x;

    if (!(Abs(local_54.x) > Abs(fStack_50))) {
        if (!(Abs(fStack_50) > Abs(fStack_4c))) {
            if (!(Abs(((double)fVar8 * fVar5 + (double)fVar9 * fVar6) + (double)fVar10 * fVar7) >
                  Abs(((double)fVar8 * fVar2 + (double)fVar9 * fVar3) + (double)fVar10 * fVar4))) {
                pMatrix[3] = fVar8; pMatrix[4] = fVar9; pMatrix[5] = fVar10;
                pMatrix[6] = fVar5; pMatrix[7] = fVar6; pMatrix[8] = fVar7;
                pFlags[1] = fStack_4c;
                pFlags[2] = fStack_50;
            } else {
                pMatrix[3] = fVar8; pMatrix[4] = fVar9; pMatrix[5] = fVar10;
                pMatrix[6] = fVar2; pMatrix[7] = fVar3; pMatrix[8] = fVar4;
                pFlags[1] = fStack_4c;
                pFlags[2] = local_54.x;
            }
        } else if (!(Abs(((double)fVar5 * fVar8 + (double)fVar6 * fVar9) + (double)fVar7 * fVar10) >
                      Abs(((double)fVar5 * fVar2 + (double)fVar6 * fVar3) + (double)fVar7 * fVar4))) {
            pMatrix[3] = fVar5; pMatrix[4] = fVar6; pMatrix[5] = fVar7;
            pMatrix[6] = fVar8; pMatrix[7] = fVar9; pMatrix[8] = fVar10;
            pFlags[1] = fStack_50;
            pFlags[2] = fStack_4c;
        } else {
            pMatrix[3] = fVar5; pMatrix[4] = fVar6; pMatrix[5] = fVar7;
            pMatrix[6] = fVar2; pMatrix[7] = fVar3; pMatrix[8] = fVar4;
            pFlags[1] = fStack_50;
            pFlags[2] = local_54.x;
        }
    } else if (!(Abs(local_54.x) > Abs(fStack_4c))) {
        if (!(Abs(((double)fVar8 * fVar5 + (double)fVar9 * fVar6) + (double)fVar10 * fVar7) >
              Abs(((double)fVar8 * fVar2 + (double)fVar9 * fVar3) + (double)fVar10 * fVar4))) {
            pMatrix[3] = fVar8; pMatrix[4] = fVar9; pMatrix[5] = fVar10;
            pMatrix[6] = fVar5; pMatrix[7] = fVar6; pMatrix[8] = fVar7;
            pFlags[1] = fStack_4c;
            pFlags[2] = fStack_50;
        } else {
            pMatrix[3] = fVar8; pMatrix[4] = fVar9; pMatrix[5] = fVar10;
            pMatrix[6] = fVar2; pMatrix[7] = fVar3; pMatrix[8] = fVar4;
            pFlags[1] = fStack_4c;
            pFlags[2] = local_54.x;
        }
    } else if (!(Abs(((double)fVar2 * fVar8 + (double)fVar3 * fVar9) + (double)fVar4 * fVar10) >
                  Abs(((double)fVar2 * fVar5 + (double)fVar3 * fVar6) + (double)fVar4 * fVar7))) {
        pMatrix[3] = fVar2; pMatrix[4] = fVar3; pMatrix[5] = fVar4;
        pMatrix[6] = fVar8; pMatrix[7] = fVar9; pMatrix[8] = fVar10;
        pFlags[1] = local_54.x;
        pFlags[2] = fStack_4c;
    } else {
        pMatrix[3] = fVar2; pMatrix[4] = fVar3; pMatrix[5] = fVar4;
        pMatrix[6] = fVar5; pMatrix[7] = fVar6; pMatrix[8] = fVar7;
        pFlags[1] = local_54.x;
        pFlags[2] = fStack_50;
    }
}
