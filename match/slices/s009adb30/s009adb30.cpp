// @ 0x009adb30 .. slice s009adb30  (batch gold1, slices 64-67)
// Target module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// Context: nSPCreatureAnim skeletal-animation blending / bone-frame packing helpers.
//   Several functions take extra arguments in ecx/eax/esi/edi (Ghidra's unaff_ESI/EDI,
//   in_EAX). Only __fastcall is usable for ecx; the esi/edi/eax inputs are reproduced
//   as explicit parameters, so byte-exact codegen is not expected for those.
#include "types.h"

extern "C" void  FUN_009ac300(int a, ...);          // 0x009ac300 sample/accumulate
extern "C" void  FUN_009ac460(int a, void* b);      // 0x009ac460
extern "C" void* FUN_0099cae0(void* a, void* b, int c);       // 0x0099cae0
extern "C" void* FUN_0099c1a0(void* a, void* b, void* c);     // 0x0099c1a0 checkerlib::QuaternionVectorTransform
extern "C" void  FUN_009ac640(void* a, void* b);    // 0x009ac640 nSPCreatureAnim::PackBoneFrame
extern "C" void  operator_delete__(void* p);        // 0x00f47380
extern int DAT_0166c0c8;                            // 0x0166c0c8

void FUN_009adb30(int param_1, float* param_2, float* out, int* st);
void FUN_009adfd0(float* a, int b, float* q, int st);
int  __fastcall FUN_009ae450(int* this_, int* eaxv, float* param_2, float* param_3);
void __fastcall FUN_009ae4b0(int* this_, int edx_dummy, int param_2, int param_3);

// ===========================================================================
// 0x009adb30  (esi = 3-vector output, edi = state)
// ===========================================================================
// @ 0x009adb30
void FUN_009adb30(int param_1, float* param_2, float* out, int* st)
{
    int iVar2 = st[3];
    int iVar3 = st[2];
    param_1 = param_1 * 8;
    if (iVar3 == iVar2) {
        FUN_009ac300(*(int*)(param_1 + 0x54 + iVar3));
        float fVar6 = *(float*)(*st + 0x70);
        out[0] = out[0] * fVar6;
        out[1] = out[1] * fVar6;
        out[2] = fVar6 * out[2];
        FUN_009ac460(param_1 + 0x58 + iVar3, param_2);
        return;
    }
    float local_30, local_2c, local_28, local_24, local_20, local_1c;
    float local_18, local_14, local_10, local_c, local_8, local_4;
    FUN_009ac300(*(int*)(param_1 + 0x54 + iVar3), &local_20);
    FUN_009ac300(*(int*)(iVar2 + 0x54 + param_1), &local_30);
    float fVar6 = (float)st[4];
    float fVar5 = 1.0f - (float)st[4];
    float fVar1 = *(float*)(*st + 0x70);
    out[0] = fVar1 * (local_20 * fVar5 + fVar6 * local_30);
    out[1] = fVar1 * (local_1c * fVar5 + fVar6 * local_2c);
    out[2] = fVar1 * (local_18 * fVar5 + fVar6 * local_28);
    FUN_009ac460(param_1 + 0x58 + iVar3, &local_10);
    FUN_009ac460(iVar2 + 0x58 + param_1, &local_20);
    local_28 = (float)st[4];
    float g = 1.0f - (float)st[4];
    local_2c = local_28 * local_1c;
    local_20 = local_28 * local_20;
    local_24 = local_28 * local_14;
    local_28 = local_28 * local_18;
    local_c = local_c * g;
    local_8 = local_8 * g;
    local_10 = local_10 * g;
    local_4 = local_4 * g;
    if (0.0f <= ((local_4 * local_24 + local_8 * local_28) + local_c * local_2c) + local_10 * local_20) {
        local_18 = local_8 + local_28;
        local_14 = local_4 + local_24;
        local_20 = local_10 + local_20;
        local_1c = local_c + local_2c;
    } else {
        local_18 = local_8 - local_28;
        local_14 = local_4 - local_24;
        local_20 = local_10 - local_20;
        local_1c = local_c - local_2c;
    }
    float* puVar4 = (float*)FUN_0099cae0(&local_10, &local_20, 0);
    param_2[0] = puVar4[0];
    param_2[1] = puVar4[1];
    param_2[2] = puVar4[2];
    param_2[3] = puVar4[3];
}

// ===========================================================================
// 0x009add80  (ecx = a, eax = **int, esi = 4-float out, edi = 3-float out)
// ===========================================================================
// @ 0x009add80
void FUN_009add80(float* a, int* b, float* c, int** eaxv, float* esi, float* edi)
{
    int iVar17 = (int)(size_t)*eaxv;
    float c0 = a[0], c1 = a[1], c2 = a[2], c3 = a[3];
    float f2 = *(float*)(iVar17 + 0x128);
    float f3 = *(float*)(iVar17 + 0x134);
    float f5 = *(float*)(iVar17 + 0x130);
    float f7 = *(float*)(iVar17 + 0x12c);
    esi[0] = ((c0 * f3 + f2 * c3) - c2 * f7) + c1 * f5;
    esi[1] = ((c1 * f3 + c2 * f2) + f7 * c3) - f5 * c0;
    esi[2] = ((c2 * f3 - c1 * f2) + f7 * c0) + f5 * c3;
    esi[3] = ((f3 * c3 - c0 * f2) - c1 * f7) - f5 * c2;

    int iVar18 = *b;
    float local_28 = *(float*)(iVar18 + 0x70);
    float local_24 = *(float*)(iVar17 + 0x344) * local_28;
    float local_20 = *(float*)(iVar17 + 0x348) * local_28;
    float local_1c = *(float*)(iVar17 + 0x34c) * local_28;
    float local_30 = *(float*)(iVar17 + 0x350) * local_28;
    float local_2c = *(float*)(iVar17 + 0x354) * local_28;
    local_28 = *(float*)(iVar17 + 0x358) * local_28;
    float local_18[3], local_c[3];
    float* pfVar19 = (float*)FUN_0099c1a0(local_18, a, &local_30);
    local_30 = c[0] + pfVar19[0];
    local_2c = pfVar19[1] + c[1];
    local_28 = pfVar19[2] + c[2];
    pfVar19 = (float*)FUN_0099c1a0(local_c, esi, &local_30);
    float g1 = pfVar19[1];
    float g2 = pfVar19[2];
    edi[0] = local_30 - pfVar19[0];
    edi[1] = local_2c - g1;
    edi[2] = local_28 - g2;
}

// ===========================================================================
// 0x009adfd0  (ecx = a, eax = q, esi = state)
// ===========================================================================
// @ 0x009adfd0
void FUN_009adfd0(float* a, int b, float* q, int st)
{
    if (*(char*)(b + 0x1c) != '\0') {
        float fVar5 = *(float*)(b + 0x18);
        float fVar1 = *(float*)(b + 0x14);
        float fVar2 = a[1];
        float fVar3 = a[2];
        *(float*)(st + 0x280) = *(float*)(st + 0x280) * fVar1 + a[0] * fVar5;
        *(float*)(st + 0x284) = *(float*)(st + 0x284) * fVar1 + fVar2 * fVar5;
        *(float*)(st + 0x288) = *(float*)(st + 0x288) * fVar1 + fVar3 * fVar5;
        fVar5 = *(float*)(b + 0x18);
        float local_14 = *(float*)(b + 0x14);
        float local_8 = q[2] * fVar5;
        float local_4 = q[3] * fVar5;
        float local_c = q[1] * fVar5;
        float local_1c = *(float*)(st + 0x290) * local_14;
        float local_18 = *(float*)(st + 0x294) * local_14;
        fVar5 = fVar5 * q[0];
        float local_20 = local_14 * *(float*)(st + 0x28c);
        local_14 = *(float*)(st + 0x298) * local_14;
        if (0.0f <= ((local_14 * local_4 + local_18 * local_8) + local_1c * local_c) + local_20 * fVar5) {
            local_18 = local_18 + local_8;
            local_14 = local_14 + local_4;
            local_20 = local_20 + fVar5;
            local_1c = local_1c + local_c;
        } else {
            local_18 = local_18 - local_8;
            local_14 = local_14 - local_4;
            local_20 = local_20 - fVar5;
            local_1c = local_1c - local_c;
        }
        float local_10[1];
        uint32_t* puVar4 = (uint32_t*)FUN_0099cae0(local_10, &local_20, 0);
        *(uint32_t*)(st + 0x28c) = puVar4[0];
        *(uint32_t*)(st + 0x290) = puVar4[1];
        *(uint32_t*)(st + 0x294) = puVar4[2];
        *(uint32_t*)(st + 0x298) = puVar4[3];
        *(uint8_t*)(st + 0x38) = 1;
        return;
    }
    *(float*)(st + 0x10) = a[0];
    *(float*)(st + 0x14) = a[1];
    *(float*)(st + 0x18) = a[2];
    *(float*)(st + 0x1c) = q[0];
    *(float*)(st + 0x20) = q[1];
    *(float*)(st + 0x24) = q[2];
    *(float*)(st + 0x28) = q[3];
    *(uint8_t*)(st + 0x38) = 1;
}

// ===========================================================================
// 0x009ae1c0  ref-count release (ecx = this)
// ===========================================================================
// @ 0x009ae1c0
int __fastcall FUN_009ae1c0(int* p)
{
    int local_8[2];
    int* piVar1 = local_8;
    local_8[0] = p[0x44] + -1;
    local_8[1] = 0;
    if (p[0x44] - 1 < 1) piVar1 = local_8 + 1;
    int iVar2 = *piVar1;
    p[0x44] = iVar2;
    if (iVar2 < 1) {
        p[0x44] = 1;
        operator_delete__((void*)*p);
        *p = 0;
        p[1] = 0;
        p[2] = DAT_0166c0c8;
        DAT_0166c0c8 = DAT_0166c0c8 + 1;
        *(uint8_t*)(p + 3) = 0;
        operator_delete__(p);
        iVar2 = 0;
    }
    return iVar2;
}

// ===========================================================================
// 0x009ae240  recursive bone packing (ecx = this, edx unused, 4 stack args)
// ===========================================================================
void __fastcall FUN_009ae240(int* param_1, int edx_dummy, int param_2, int param_3, uint32_t param_4, uint32_t* param_5)
{
    (void)edx_dummy;
    int* piVar2 = (int*)(param_4 * 700 + *(int*)(param_3 + 0x2e4));
    if (*(uint32_t*)(*param_1 + 0xc) <= *param_5) return;
    int iVar5;
    int* piVar4;
    if (*(uint32_t*)(*piVar2 + 0x440) <
        (uint32_t)((*(int*)(param_3 + 0x2e8) - *(int*)(param_3 + 0x2e4)) / 700)) {
        if ((uint32_t)((*(int*)(param_3 + 0x2e8) - *(int*)(param_3 + 0x2e4)) / 700) <=
            *(uint32_t*)(*piVar2 + 0x444)) goto LAB_009ae317;
        iVar5 = param_2 + 0x54 + *param_5 * 8;
        piVar4 = (int*)(*(uint32_t*)(*piVar2 + 0x440) * 700 + *(int*)(param_3 + 0x2e4));
    } else {
        if ((0xfe < param_4) ||
            ((*(uint32_t*)(*param_1 + 0x18 + (param_4 >> 5) * 4) & (1u << ((uint8_t)param_4 & 0x1f))) == 0))
            goto LAB_009ae317;
        iVar5 = param_2 + 0x54 + *param_5 * 8;
        piVar4 = piVar2;
    }
    FUN_009ac640(piVar4, (void*)iVar5);
    *param_5 = *param_5 + 1;
LAB_009ae317:
    uint32_t uVar3 = *(uint32_t*)(*piVar2 + 0x204);
    uint32_t uVar1 = *(int*)(*piVar2 + 0x208) + uVar3;
    for (; uVar3 < uVar1; uVar3 = uVar3 + 1) {
        FUN_009ae240(param_1, 0, param_2, param_3, uVar3, param_5);
    }
}

// ===========================================================================
// 0x009ae350  build a bone frame and pack (ecx = this, edx unused, 4 stack args)
// ===========================================================================
// @ 0x009ae350
void __fastcall FUN_009ae350(int* param_1, int edx_dummy, int param_2, uint32_t param_3, int param_4, int param_5)
{
    (void)edx_dummy;
    int iVar2 = *param_1;
    int off = (*(int*)(iVar2 + 0xc) * 8 + 0x54) * param_2;
    uint32_t* puVar1 = (uint32_t*)(off + 0x38 + iVar2);
    if ((*(uint8_t*)(off + 0x38 + iVar2) & 1) == 0) {
        param_1[1] = param_1[1] + 1;
    }
    *puVar1 = *puVar1 | 1;
    puVar1[1] = param_3;
    puVar1[2] = *(uint32_t*)(param_4 + 0x70);
    uint32_t uVar3 = (uint32_t)(-(int32_t)(*(char*)(param_4 + 0x1a8) != '\0') & 2) | *puVar1;
    *puVar1 = uVar3;
    *puVar1 = (uint32_t)(-(int32_t)(*(char*)(param_4 + 0x1a9) != '\0') & 4) | uVar3;
    for (int k = 0; k < 18; k++) {
        puVar1[3 + k] = *(uint32_t*)(param_5 + 0x2c + k * 4);
    }
    int zero = 0;
    FUN_009ae240(param_1, 0, (int)puVar1, param_4, 0, (uint32_t*)&zero);
    param_1[2] = DAT_0166c0c8;
    DAT_0166c0c8 = DAT_0166c0c8 + 1;
}

// ===========================================================================
// 0x009ae450  (ecx = this, eax = piVar, 2 stack args)
// ===========================================================================
// @ 0x009ae450
int __fastcall FUN_009ae450(int* this_, int* eaxv, float* param_2, float* param_3)
{
    uint32_t uVar1 = *(uint32_t*)(*eaxv + 0x1f8);
    if ((uVar1 < 0xff) &&
        ((*(uint32_t*)(**(int**)((int)this_ + 4) + 0x18 + (uVar1 >> 5) * 4) & (1u << ((uint8_t)uVar1 & 0x1f))) != 0)) {
        FUN_009adb30(*(int*)((int)this_ + 0x30), param_3, param_2, this_);
        *(int*)((int)this_ + 0x30) = *(int*)((int)this_ + 0x30) + 1;
        return 1;
    }
    return 0;
}

// ===========================================================================
// 0x009ae4b0  recursive pack (ecx = this, edx unused, 2 stack args)
// ===========================================================================
// @ 0x009ae4b0
void __fastcall FUN_009ae4b0(int* param_1, int edx_dummy, int param_2, int param_3)
{
    (void)edx_dummy;
    int* piVar2 = (int*)(param_2 * 700 + *(int*)(*param_1 + 0x2e4));
    uint32_t uVar4 = *(uint32_t*)(*piVar2 + 0x1f8);
    if ((uVar4 < 0xff) &&
        ((*(uint32_t*)(*(int*)param_1[1] + 0x18 + (uVar4 >> 5) * 4) & (1u << ((uint8_t)uVar4 & 0x1f))) != 0)) {
        float local_10[4];
        float local_20[4];
        FUN_009adb30(param_1[0xc], local_20, local_10, param_1);
        param_1[0xc] = param_1[0xc] + 1;
        float sum[3];
        sum[0] = ((float*)param_3)[0] + local_10[0];
        sum[1] = ((float*)param_3)[1] + local_10[1];
        sum[2] = ((float*)param_3)[2] + local_10[2];
        FUN_009adfd0(sum, (int)param_3, (float*)&local_20[0], (int)piVar2);
    }
    int iVar1 = *piVar2;
    uint32_t uVar4b = *(uint32_t*)(iVar1 + 0x204);
    uint32_t uVar3 = *(int*)(iVar1 + 0x208) + uVar4b;
    for (; uVar4b < uVar3; uVar4b = uVar4b + 1) {
        FUN_009ae4b0(param_1, 0, uVar4b, param_3);
    }
}

// ===========================================================================
// 0x009ae590  recalc tree (ecx = this, edx unused, 4 stack args)
// ===========================================================================
// @ 0x009ae590
void __fastcall FUN_009ae590(int* param_1, int edx_dummy, uint32_t param_2, uint32_t param_3, float* param_4, int param_5)
{
    (void)edx_dummy;
    if (param_2 == param_3) return;
    float local_40[3], local_38[3];
    float local_28[3], local_1c[3], local_10[3];
    int* piVar11 = (int*)(param_2 * 700 + *(int*)(*param_1 + 0x2e4));
    if (*(int*)(*piVar11 + 0x440) == -3) {
        char cVar8 = (char)FUN_009ae450(param_1, piVar11, local_40, local_38);
        if (cVar8 != '\0') {
            int iVar7 = *piVar11;
            float local_50 = *(float*)(*param_1 + 0x70);
            float local_4c = *(float*)(iVar7 + 0x344) * local_50;
            float local_48 = *(float*)(iVar7 + 0x348) * local_50;
            float local_44 = *(float*)(iVar7 + 0x34c) * local_50;
            float local_58 = *(float*)(iVar7 + 0x350) * local_50;
            float local_54 = *(float*)(iVar7 + 0x354) * local_50;
            local_50 = *(float*)(iVar7 + 0x358) * local_50;
            float* pfVar9 = (float*)FUN_0099c1a0(local_28, (void*)param_5, &local_58);
            float fVar1 = pfVar9[0], fVar2 = param_4[0];
            float fVar3 = pfVar9[1], fVar4 = param_4[1];
            float fVar5 = pfVar9[2], fVar6 = param_4[2];
            pfVar9 = (float*)FUN_0099c1a0(local_1c, local_10, &local_4c);
            local_58 = (fVar1 + fVar2) - pfVar9[0];
            local_54 = (fVar3 + fVar4) - pfVar9[1];
            local_50 = (fVar5 + fVar6) - pfVar9[2];
            local_4c = local_58;
            local_48 = local_54;
            local_44 = local_50;
            FUN_009adfd0(&local_58, 0, &local_4c, (int)piVar11);
            local_38[0] = local_58 - local_40[0];
            local_38[1] = local_54 - local_40[1];
            local_38[2] = local_50 - local_40[2];
        }
        uint32_t uVar10 = *(uint32_t*)(*piVar11 + 0x204);
        uint32_t uVar12 = *(int*)(*piVar11 + 0x208) + uVar10;
        if (uVar10 < uVar12) {
            do {
                FUN_009ae4b0(param_1, 0, uVar10, (int)local_38);
                uVar10 = uVar10 + 1;
            } while (uVar10 < uVar12);
            return;
        }
    } else {
        if ((param_2 < 0xff) &&
            ((*(uint32_t*)(*(int*)param_1[1] + 0x18 + (param_2 >> 5) * 4) & (1u << ((uint8_t)param_2 & 0x1f))) != 0)) {
            param_1[0xc] = param_1[0xc] + 1;
        }
        uint32_t uVar10 = *(uint32_t*)(*piVar11 + 0x204);
        uint32_t uVar12 = *(int*)(*piVar11 + 0x208) + uVar10;
        for (; uVar10 < uVar12; uVar10 = uVar10 + 1) {
            FUN_009ae590(param_1, 0, uVar10, param_3, local_1c, (int)local_10);
        }
    }
}
