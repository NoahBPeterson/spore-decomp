// Slice s004fa6c0: builds a picking OBB for the force-field grid cell containing a point.
// Unoptimized module (/Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast).  The ~0x2b0-byte /Od frame is
// not reproduced, so this complete reconstruction is listed in nonmatching.txt.
#include "types.h"
#include <math.h>

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
    void BuildOBB(const Vector3* a, const Vector3* b, float* pMatrix, uint32_t* pFlags, float* pCorner);
};

SphereFields* GetField(const Vector3* p);                                   // 0x004f8f70
void FUN_004fb880(SphereFields* self, const Vector3* a, float* b, float* c, Matrix33* d); // 0x004fb880
Vector3* SubV(Vector3* out, const Vector3* a, const Vector3* b);            // 0x0041db10
void Cross(Vector3* out, const Vector3* a, const Vector3* b);              // 0x0044e460
void Matrix33_ctor(Matrix33* out, const void* src);                        // 0x0041cb40
extern "C" void* DAT_015db080;

// @ 0x004fa6c0
void ForceGrid::BuildOBB(const Vector3* a, const Vector3* b, float* pMatrix, uint32_t* pFlags, float* pCorner)
{
    uint32_t local_3c = *(uint32_t*)((char*)this + 0x0c) ^ 0x80000000u;
    float local_48 = 0.0f, local_44 = 0.0f, local_40 = 0.0f;
    float local_38, local_34, local_30;
    Matrix33 local_78;
    Matrix33_ctor(&local_78, &DAT_015db080);

    SphereFields* local_8 = GetField(a);
    if (local_8) {
        uint32_t local_7c = *(uint32_t*)((char*)local_8 - 8);
        for (uint32_t local_80 = 0; local_80 < local_7c; ++local_80) {
            FUN_004fb880((SphereFields*)((char*)local_8 + local_80 * 0x80), a, &local_38, &local_48, &local_78);
        }
    }
    if (pCorner) {
        pCorner[0] = local_48;
        pCorner[1] = local_44;
        pCorner[2] = local_40;
    }

    Vector3 tmp;
    Vector3* pfVar1 = SubV(&tmp, b, a);
    local_38 = pfVar1->x;
    local_34 = pfVar1->y;
    local_30 = pfVar1->z;

    Vector3 local_54;
    Cross(&local_54, (const Vector3*)&local_38, (const Vector3*)&local_48);
    float fStack_50 = local_54.y;
    float fStack_4c = local_54.z;

    float fVar2 = local_34 * local_78.xAxis.PaddingForAlignment[0] - local_30 * local_78.xAxis.y;
    float fVar3 = (local_34 * local_78.yAxis.PaddingForAlignment[0] - local_30 * local_78.yAxis.y) - local_40;
    float fVar4 = (local_34 * local_78.zAxis.PaddingForAlignment[0] - local_30 * local_78.yAxis.PaddingForAlignment[0]) + local_44;
    float fVar5 = (local_30 * local_78.xAxis.x - local_38 * local_78.xAxis.PaddingForAlignment[0]) + local_40;
    float fVar6 = local_30 * local_78.xAxis.y - local_38 * local_78.yAxis.PaddingForAlignment[0];
    float fVar7 = (local_30 * local_78.xAxis.PaddingForAlignment[0] - local_38 * local_78.zAxis.PaddingForAlignment[0]) - local_48;
    float fVar8 = (local_38 * local_78.xAxis.y - local_34 * local_78.xAxis.x) - local_44;
    float fVar9 = (local_38 * local_78.yAxis.y - local_34 * local_78.xAxis.y) + local_48;
    float fVar10 = local_38 * local_78.yAxis.PaddingForAlignment[0] - local_34 * local_78.xAxis.PaddingForAlignment[0];

    pMatrix[0] = local_48;
    pMatrix[1] = local_44;
    pMatrix[2] = local_40;
    pFlags[0] = local_3c;

    if (fabsf(local_54.x) <= fabsf(fStack_50)) {
        if (fabsf(fStack_50) <= fabsf(fStack_4c)) {
            if (fabsf((fVar8 * fVar5 + fVar9 * fVar6) + fVar10 * fVar7) <=
                fabsf((fVar8 * fVar2 + fVar9 * fVar3) + fVar10 * fVar4)) {
                pMatrix[3] = fVar8; pMatrix[4] = fVar9; pMatrix[5] = fVar10;
                pMatrix[6] = fVar5; pMatrix[7] = fVar6; pMatrix[8] = fVar7;
                pFlags[1] = (uint32_t)fStack_4c;
                pFlags[2] = (uint32_t)fStack_50;
            } else {
                pMatrix[3] = fVar8; pMatrix[4] = fVar9; pMatrix[5] = fVar10;
                pMatrix[6] = fVar2; pMatrix[7] = fVar3; pMatrix[8] = fVar4;
                pFlags[1] = (uint32_t)fStack_4c;
                pFlags[2] = (uint32_t)local_54.x;
            }
        } else if (fabsf((fVar5 * fVar8 + fVar6 * fVar9) + fVar7 * fVar10) <=
                   fabsf((fVar5 * fVar2 + fVar6 * fVar3) + fVar7 * fVar4)) {
            pMatrix[3] = fVar5; pMatrix[4] = fVar6; pMatrix[5] = fVar7;
            pMatrix[6] = fVar8; pMatrix[7] = fVar9; pMatrix[8] = fVar10;
            pFlags[1] = (uint32_t)fStack_50;
            pFlags[2] = (uint32_t)fStack_4c;
        } else {
            pMatrix[3] = fVar5; pMatrix[4] = fVar6; pMatrix[5] = fVar7;
            pMatrix[6] = fVar2; pMatrix[7] = fVar3; pMatrix[8] = fVar4;
            pFlags[1] = (uint32_t)fStack_50;
            pFlags[2] = (uint32_t)local_54.x;
        }
    } else if (fabsf(local_54.x) <= fabsf(fStack_4c)) {
        if (fabsf((fVar8 * fVar5 + fVar9 * fVar6) + fVar10 * fVar7) <=
            fabsf((fVar8 * fVar2 + fVar9 * fVar3) + fVar10 * fVar4)) {
            pMatrix[3] = fVar8; pMatrix[4] = fVar9; pMatrix[5] = fVar10;
            pMatrix[6] = fVar5; pMatrix[7] = fVar6; pMatrix[8] = fVar7;
            pFlags[1] = (uint32_t)fStack_4c;
            pFlags[2] = (uint32_t)fStack_50;
        } else {
            pMatrix[3] = fVar8; pMatrix[4] = fVar9; pMatrix[5] = fVar10;
            pMatrix[6] = fVar2; pMatrix[7] = fVar3; pMatrix[8] = fVar4;
            pFlags[1] = (uint32_t)fStack_4c;
            pFlags[2] = (uint32_t)local_54.x;
        }
    } else if (fabsf((fVar2 * fVar8 + fVar3 * fVar9) + fVar4 * fVar10) <=
               fabsf((fVar2 * fVar5 + fVar3 * fVar6) + fVar4 * fVar7)) {
        pMatrix[3] = fVar2; pMatrix[4] = fVar3; pMatrix[5] = fVar4;
        pMatrix[6] = fVar8; pMatrix[7] = fVar9; pMatrix[8] = fVar10;
        pFlags[1] = (uint32_t)local_54.x;
        pFlags[2] = (uint32_t)fStack_4c;
    } else {
        pMatrix[3] = fVar2; pMatrix[4] = fVar3; pMatrix[5] = fVar4;
        pMatrix[6] = fVar5; pMatrix[7] = fVar6; pMatrix[8] = fVar7;
        pFlags[1] = (uint32_t)local_54.x;
        pFlags[2] = (uint32_t)fStack_50;
    }
}
