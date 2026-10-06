// @ 0x009ae7e0  FUN_009ae7e0   (no PDB name; /O2 /MD /TP)
//
// Large spatial/terrain update routine.  The retail code is compiled with a
// static-helper register convention: the context object arrives in EDI and is
// modelled here as an explicit first parameter `ectx`.
//
// Every branch and callee of the original is reproduced; x87 inline math is
// expressed with libm calls.

#include "types.h"
extern "C" float sqrtf(float);

extern int DAT_015509f0, DAT_01550aa4;

extern "C" {
    void   FUN_009ae450(float*, float*);
    float* FUN_0099c1a0(void*, const void*, const void*);
    float  FUN_009b6220(float*, int);
    float* FUN_009ac7a0(void*, ...);
    float* FUN_009a49d0(void*, const void*, int);
    float* FUN_0099c0b0(const void*, void*);
    float* FUN_0099c310(void*, const void*, const void*);
    void   FUN_009adfd0(void*);
    void   FUN_009ae590(unsigned, int, const void*, const void*);
}

void __cdecl FUN_009ae7e0(int* ectx, int* param_1, float* param_2, void* param_3)
{
    float local_d0, local_cc, local_c8;
    float local_c0, local_bc, local_b8, local_b4, local_b0;
    float local_ac, local_a8, local_a4, local_a0;
    float local_9c, local_98, local_94, local_90;
    float local_8c, local_88, local_84, local_80;
    float local_7c, local_78, local_74, local_70;
    float local_6c, local_68, local_64, local_60;
    float local_5c, local_58, local_54, local_50;
    float local_4c, local_48, local_44, local_40, local_3c, local_38, local_34, local_30;
    int   local_2c;
    int   local_28[2];
    float local_20, local_18, local_14, local_10, local_c, local_8;
    float fVar12, fVar13, fVar14, fVar15, fVar16, fVar17, fVar18;
    float* pfVar4;
    int *piVar6, *piVar8;
    int iVar2, iVar3;
    unsigned uVar7, uVar10;
    unsigned local_18u;

    local_18u = *(unsigned*)(*param_1 + 0x440);
    piVar8 = (int*)(local_18u * 700 + *(int*)(*ectx + 0x2e4));
    unsigned char bVar1 = *(unsigned char*)(ectx[2] + ectx[0xc] * 8 + 0x5b);
    if (((bVar1 & 2) == 0) ||
        (((bVar1 & 1) == 0) && (*(char*)(*ectx + 0x261) != '\0'))) {
        local_94 = 1.0f / ((float)piVar8[0x22] + 1e-8f);
        local_90 = (float)piVar8[0x23];
        local_8c = (float)piVar8[0x24];
        local_88 = (float)piVar8[0x25];
        local_9c = local_94 * (float)piVar8[0x1f];
        local_98 = (float)piVar8[0x20] * local_94;
        local_84 = (float)piVar8[0x26];
        local_94 = (float)piVar8[0x21] * local_94;
        local_b0 = sqrtf(local_8c * local_8c +
                         (local_88 * local_88 + (local_84 * local_84 + local_90 * local_90)));
        local_50 = local_84; local_54 = local_88; local_58 = local_8c; local_5c = local_90;
        if (local_b0 != 0.0f) {
            fVar12 = 1.0f / local_b0;
            local_50 = fVar12 * local_84;
            local_54 = fVar12 * local_88;
            local_58 = fVar12 * local_8c;
            local_5c = fVar12 * local_90;
        }
        if ((local_18u < 0xff) &&
            ((*(unsigned*)(*(int*)ectx[1] + 0x18 + (local_18u >> 5) * 4) &
              (1u << ((unsigned char)local_18u & 0x1f))) != 0)) {
            ectx[0xc] = ectx[0xc] + 1;
        }
    } else {
        FUN_009ae450(&local_9c, &local_5c);
        if (DAT_015509f0 != 0) {
            iVar2 = *ectx;
            pfVar4 = FUN_0099c1a0(local_28, (void*)(iVar2 + 0x3c), &local_9c);
            local_d0 = *(float*)(iVar2 + 0x18) + pfVar4[0];
            local_cc = pfVar4[1] + *(float*)(iVar2 + 0x1c);
            local_c8 = pfVar4[2] + *(float*)(iVar2 + 0x20);
            float f11 = FUN_009b6220(&local_d0, 0);
            local_b0 = f11;
            fVar12 = local_b0 - (float)ectx[0xb];
            local_9c = (float)ectx[8] * fVar12 + local_9c;
            local_98 = (float)ectx[9] * fVar12 + local_98;
            local_94 = (float)ectx[10] * fVar12 + local_94;
        }
    }

    iVar2 = *param_1;
    local_2c = *(int*)(iVar2 + 0x444);
    iVar3 = *ectx;
    piVar6 = (int*)(local_2c * 700 + *(int*)(iVar3 + 0x2e4));

    if (DAT_01550aa4 == 0) {
        local_90 = *(float*)(iVar2 + 0x118);
        local_8c = *(float*)(iVar2 + 0x11c);
        local_88 = *(float*)(iVar2 + 0x120);
        local_84 = *(float*)(iVar2 + 0x124);
        local_c8 = *(float*)(iVar3 + 0x70);
        local_bc = local_c8 * *(float*)(iVar2 + 0x344);
        local_b8 = *(float*)(iVar2 + 0x348) * local_c8;
        local_b4 = *(float*)(iVar2 + 0x34c) * local_c8;
        local_d0 = local_c8 * *(float*)(iVar2 + 0x350);
        local_cc = *(float*)(iVar2 + 0x354) * local_c8;
        local_c8 = *(float*)(iVar2 + 0x358) * local_c8;
        pfVar4 = FUN_0099c1a0(local_28, param_3, &local_d0);
        local_38 = pfVar4[0] + param_2[0];
        local_34 = pfVar4[1] + param_2[1];
        local_30 = pfVar4[2] + param_2[2];
        pfVar4 = FUN_0099c1a0(&local_d0, &local_90, &local_bc);
        local_6c = local_38 - pfVar4[0];
        local_68 = local_34 - pfVar4[1];
        local_64 = local_30 - pfVar4[2];
        iVar2 = *piVar8;
        iVar3 = *piVar6;
        fVar12 = *(float*)(iVar3 + 0x118);
        fVar14 = *(float*)(iVar2 + 0x118);
        fVar13 = *(float*)(iVar2 + 0x124);
        fVar16 = *(float*)(iVar3 + 0x124);
        fVar17 = *(float*)(iVar3 + 0x120);
        local_c0 = *(float*)(iVar2 + 0x11c);
        fVar18 = ((fVar12 * fVar13 - fVar14 * fVar16) +
                  *(float*)(iVar2 + 0x120) * *(float*)(iVar3 + 0x11c)) - local_c0 * fVar17;
        fVar15 = ((*(float*)(iVar3 + 0x11c) * fVar13 - local_c0 * fVar16) -
                  *(float*)(iVar2 + 0x120) * fVar12) + fVar17 * fVar14;
        fVar12 = ((local_c0 * fVar12 - *(float*)(iVar2 + 0x120) * fVar16) -
                  *(float*)(iVar3 + 0x11c) * fVar14) + fVar17 * fVar13;
        fVar14 = ((fVar17 * *(float*)(iVar2 + 0x120) + local_c0 * *(float*)(iVar3 + 0x11c)) +
                  fVar14 * *(float*)(iVar3 + 0x118)) + fVar16 * *(float*)(iVar2 + 0x124);
        local_48 = ((fVar18 * local_50 + local_5c * fVar14) - fVar15 * local_54) + fVar12 * local_58;
        local_44 = ((fVar18 * local_54 + fVar15 * local_50) + fVar14 * local_58) - local_5c * fVar12;
        local_80 = (fVar14 * local_54 - fVar18 * local_58) + local_5c * fVar15;
        local_40 = local_80 + fVar12 * local_50;
        local_3c = ((fVar14 * local_50 - fVar18 * local_5c) - fVar15 * local_58) - fVar12 * local_54;
        fVar12 = *(float*)(*ectx + 0x70);
        local_d0 = fVar12 * *(float*)(iVar3 + 0x10c) - fVar12 * *(float*)(iVar2 + 0x10c);
        local_cc = *(float*)(iVar3 + 0x110) * fVar12 - *(float*)(iVar2 + 0x110) * fVar12;
        local_c8 = *(float*)(iVar3 + 0x114) * fVar12 - *(float*)(iVar2 + 0x114) * fVar12;
        pfVar4 = FUN_0099c1a0(local_28, &local_5c, &local_d0);
        local_ac = pfVar4[0] + local_9c;
        local_a8 = pfVar4[1] + local_98;
        local_a4 = pfVar4[2] + local_94;
    } else {
        local_c8 = *(float*)(iVar3 + 0x70);
        local_d0 = *(float*)(iVar2 + 0x350) * local_c8;
        local_cc = *(float*)(iVar2 + 0x354) * local_c8;
        local_c8 = *(float*)(iVar2 + 0x358) * local_c8;
        pfVar4 = FUN_0099c1a0(local_28, param_3, &local_d0);
        local_ac = pfVar4[0] + param_2[0];
        local_a8 = pfVar4[1] + param_2[1];
        local_a4 = pfVar4[2] + param_2[2];
        local_c8 = *(float*)(*ectx + 0x70);
        iVar3 = *piVar8;
        local_d0 = local_c8 * *(float*)(iVar3 + 0x344);
        local_cc = *(float*)(iVar3 + 0x348) * local_c8;
        local_c8 = *(float*)(iVar3 + 0x34c) * local_c8;
        pfVar4 = FUN_0099c1a0(local_28, &local_5c, &local_d0);
        local_c8 = *(float*)(*ectx + 0x70);
        local_20 = pfVar4[2] + local_94;
        local_d0 = *(float*)(iVar2 + 0x448) * local_c8;
        local_cc = *(float*)(iVar2 + 0x44c) * local_c8;
        local_64 = local_20 - local_a4;
        local_6c = (pfVar4[0] + local_9c) - local_ac;
        local_68 = (pfVar4[1] + local_98) - local_a8;
        local_c8 = *(float*)(iVar2 + 0x450) * local_c8;
        if (*(int*)(iVar2 + 0x1f8) == local_2c) {
            pfVar4 = FUN_009ac7a0(&local_90, &local_d0, &local_6c, 0);
            fVar12 = pfVar4[3];
            fVar14 = *(float*)(iVar2 + 0x118);
            fVar13 = pfVar4[1];
            fVar16 = *(float*)(iVar2 + 0x120);
            local_90 = ((fVar14 * fVar12 + pfVar4[0] * *(float*)(iVar2 + 0x124)) -
                        *(float*)(iVar2 + 0x11c) * pfVar4[2]) + fVar16 * fVar13;
            local_8c = ((pfVar4[2] * fVar14 + *(float*)(iVar2 + 0x11c) * fVar12) +
                        fVar13 * *(float*)(iVar2 + 0x124)) - fVar16 * pfVar4[0];
            local_b0 = (pfVar4[2] * *(float*)(iVar2 + 0x124) - fVar13 * fVar14) + fVar16 * fVar12;
            local_88 = local_b0 + *(float*)(iVar2 + 0x11c) * pfVar4[0];
            local_84 = ((fVar12 * *(float*)(iVar2 + 0x124) - fVar14 * pfVar4[0]) -
                        fVar13 * *(float*)(iVar2 + 0x11c)) - fVar16 * pfVar4[2];
            local_c8 = *(float*)(*ectx + 0x70);
            iVar2 = *param_1;
            local_d0 = local_c8 * *(float*)(iVar2 + 0x344);
            local_cc = *(float*)(iVar2 + 0x348) * local_c8;
            local_c8 = *(float*)(iVar2 + 0x34c) * local_c8;
            pfVar4 = FUN_0099c1a0(local_28, &local_90, &local_d0);
            local_6c = local_ac - pfVar4[0];
            local_68 = local_a8 - pfVar4[1];
            local_64 = local_a4 - pfVar4[2];
        } else {
            local_b0 = *(float*)(*ectx + 0x70);
            iVar3 = *piVar6;
            local_70 = *(float*)(iVar2 + 0x454) * local_b0;
            local_70 = local_70 * local_70;
            local_38 = local_b0 * *(float*)(iVar3 + 0x448);
            local_34 = *(float*)(iVar3 + 0x44c) * local_b0;
            local_30 = *(float*)(iVar3 + 0x450) * local_b0;
            local_b0 = *(float*)(iVar3 + 0x454) * local_b0;
            local_b0 = local_b0 * local_b0;
            fVar13 = (local_68 * local_68 + local_64 * local_64) + local_6c * local_6c;
            local_60 = 1.0f / (fVar13 + 1e-6f);
            fVar17 = *(float*)(iVar3 + 0x45c) * local_64 - *(float*)(iVar3 + 0x460) * local_68;
            fVar18 = local_6c * *(float*)(iVar3 + 0x460) - *(float*)(iVar3 + 0x458) * local_64;
            fVar16 = *(float*)(iVar3 + 0x458) * local_68 - local_6c * *(float*)(iVar3 + 0x45c);
            fVar14 = (((fVar13 + local_70) - local_b0) * local_60) * 0.5f;
            local_80 = fVar14 * fVar14;
            fVar12 = 0.0f;
            local_60 = local_60 * local_70;
            if (local_60 < local_80) {
                if (fVar14 == 0.0f) local_c0 = 0.0f;
                else if (0.0f <= fVar14) local_c0 = 1.0f;
                else local_c0 = -1.0f;
                fVar14 = sqrtf(local_60) * local_c0;
                local_a0 = fVar14;
            } else {
                fVar12 = sqrtf((local_70 - local_80 * fVar13) /
                               (fVar17 * fVar17 + (fVar18 * fVar18 + fVar16 * fVar16)));
                local_a0 = fVar12;
            }
            local_c = fVar14 * local_68 + fVar12 * fVar18;
            local_78 = local_c + local_a8;
            local_8 = fVar14 * local_64 + fVar12 * fVar16;
            local_10 = local_6c * fVar14 + fVar17 * fVar12;
            local_b8 = (pfVar4[1] + local_98) - local_78;
            local_74 = local_8 + local_a4;
            local_7c = local_10 + local_ac;
            local_bc = (pfVar4[0] + local_9c) - local_7c;
            local_b4 = local_20 - local_74;
            pfVar4 = FUN_009ac7a0(&local_90, &local_d0, &local_10, 0);
            local_14 = *(float*)(iVar2 + 0x124);
            fVar12 = *(float*)(iVar2 + 0x118);
            local_70 = pfVar4[0];
            fVar14 = pfVar4[3];
            local_c0 = *(float*)(iVar2 + 0x11c);
            local_a0 = pfVar4[2];
            fVar13 = *(float*)(iVar2 + 0x120);
            fVar16 = pfVar4[1];
            local_90 = ((fVar12 * fVar14 + local_70 * local_14) - local_c0 * local_a0) + fVar13 * fVar16;
            local_8c = ((local_a0 * fVar12 + local_c0 * fVar14) + fVar16 * local_14) - fVar13 * local_70;
            local_4c = (local_a0 * local_14 - fVar16 * fVar12) + fVar13 * fVar14;
            local_88 = local_4c + local_c0 * local_70;
            iVar2 = *param_1;
            local_84 = ((fVar14 * local_14 - fVar12 * local_70) - fVar16 * local_c0) - fVar13 * local_a0;
            local_c8 = *(float*)(*ectx + 0x70);
            local_d0 = local_c8 * *(float*)(iVar2 + 0x344);
            local_cc = *(float*)(iVar2 + 0x348) * local_c8;
            local_c8 = *(float*)(iVar2 + 0x34c) * local_c8;
            pfVar4 = FUN_0099c1a0(local_28, &local_90, &local_d0);
            local_6c = local_ac - pfVar4[0];
            local_68 = local_a8 - pfVar4[1];
            local_64 = local_a4 - pfVar4[2];
            if (local_80 <= local_60) {
                iVar2 = *piVar6;
                pfVar4 = FUN_009ac7a0(&local_48, &local_38, &local_bc, 0);
                fVar12 = pfVar4[0];
                fVar14 = pfVar4[2];
                fVar13 = *(float*)(iVar2 + 0x124);
                fVar16 = pfVar4[1];
                fVar17 = *(float*)(iVar2 + 0x120);
                local_48 = ((fVar12 * fVar13 + *(float*)(iVar2 + 0x118) * pfVar4[3]) -
                            fVar14 * *(float*)(iVar2 + 0x11c)) + fVar16 * fVar17;
                local_44 = ((pfVar4[3] * *(float*)(iVar2 + 0x11c) + fVar13 * fVar16) +
                            *(float*)(iVar2 + 0x118) * fVar14) - fVar12 * fVar17;
                local_4c = (fVar13 * fVar14 - *(float*)(iVar2 + 0x118) * fVar16) + pfVar4[3] * fVar17;
                local_40 = local_4c + fVar12 * *(float*)(iVar2 + 0x11c);
                local_3c = ((fVar13 * pfVar4[3] - fVar12 * *(float*)(iVar2 + 0x118)) -
                            fVar16 * *(float*)(iVar2 + 0x11c)) - fVar17 * pfVar4[2];
                local_c8 = *(float*)(*ectx + 0x70);
                iVar2 = *piVar6;
                local_d0 = local_c8 * *(float*)(iVar2 + 0x344);
                local_cc = *(float*)(iVar2 + 0x348) * local_c8;
                local_c8 = *(float*)(iVar2 + 0x34c) * local_c8;
                pfVar4 = FUN_0099c1a0(local_28, &local_48, &local_d0);
                local_ac = local_7c;
                local_a8 = local_78;
                local_a4 = local_74;
            } else {
                if (0.0f < (local_bc * local_10 + local_b4 * local_8) + local_b8 * local_c) {
                    local_4c = sqrtf(local_b0);
                    pfVar4 = FUN_009a49d0(local_28, &local_10, 0);
                    local_bc = pfVar4[0] * local_4c + local_7c;
                    local_d0 = local_bc - local_7c;
                    local_b8 = pfVar4[1] * local_4c + local_78;
                    local_b4 = pfVar4[2] * local_4c + local_74;
                    local_cc = local_b8 - local_78;
                    local_c8 = local_b4 - local_74;
                    void* uVar5 = FUN_009ac7a0(local_28, &local_38, &local_d0, 0, *piVar6 + 0x118);
                    pfVar4 = FUN_0099c0b0(&local_10, uVar5);
                    local_48 = pfVar4[0];
                    iVar2 = *ectx;
                    local_44 = pfVar4[1];
                    local_40 = pfVar4[2];
                    local_3c = pfVar4[3];
                    iVar3 = *piVar6;
                    local_c8 = *(float*)(iVar2 + 0x70);
                    local_d0 = *(float*)(iVar3 + 0x344) * local_c8;
                    local_cc = *(float*)(iVar3 + 0x348) * local_c8;
                    local_c8 = *(float*)(iVar3 + 0x34c) * local_c8;
                    pfVar4 = FUN_0099c1a0(local_28, &local_48, &local_d0);
                    local_ac = local_7c - pfVar4[0];
                    local_a8 = local_78 - pfVar4[1];
                    local_a4 = local_74 - pfVar4[2];
                    iVar3 = *piVar8;
                    local_c8 = *(float*)(iVar2 + 0x70);
                    local_d0 = local_c8 * *(float*)(iVar3 + 0x344);
                    local_cc = *(float*)(iVar3 + 0x348) * local_c8;
                    local_c8 = *(float*)(iVar3 + 0x34c) * local_c8;
                    pfVar4 = FUN_0099c1a0(local_28, &local_5c, &local_d0);
                    local_9c = local_bc - pfVar4[0];
                    local_98 = local_b8 - pfVar4[1];
                    local_94 = local_b4 - pfVar4[2];
                    goto LAB_009afc60;
                }
                void* uVar5 = FUN_009ac7a0(local_28, &local_38, &local_bc, 0, *piVar6 + 0x118);
                pfVar4 = FUN_0099c0b0(&local_d0, uVar5);
                local_48 = pfVar4[0];
                iVar2 = *ectx;
                local_44 = pfVar4[1];
                local_40 = pfVar4[2];
                local_3c = pfVar4[3];
                iVar3 = *piVar6;
                local_c8 = *(float*)(iVar2 + 0x70);
                local_bc = local_c8 * *(float*)(iVar3 + 0x344);
                local_b8 = *(float*)(iVar3 + 0x348) * local_c8;
                local_b4 = *(float*)(iVar3 + 0x34c) * local_c8;
                local_d0 = *(float*)(iVar3 + 0x448) * local_c8;
                local_cc = *(float*)(iVar3 + 0x44c) * local_c8;
                local_c8 = *(float*)(iVar3 + 0x450) * local_c8;
                pfVar4 = FUN_0099c310(local_28, (void*)(iVar3 + 0x118), &local_d0);
                local_38 = local_bc + pfVar4[0];
                local_34 = pfVar4[1] + local_b8;
                local_30 = pfVar4[2] + local_b4;
                iVar3 = *piVar8;
                local_c8 = *(float*)(iVar2 + 0x70);
                local_d0 = *(float*)(iVar3 + 0x344) * local_c8;
                local_cc = *(float*)(iVar3 + 0x348) * local_c8;
                local_c8 = *(float*)(iVar3 + 0x34c) * local_c8;
                pfVar4 = FUN_0099c1a0(&local_10, &local_5c, &local_d0);
                local_bc = pfVar4[0] + local_9c;
                local_b8 = pfVar4[1] + local_98;
                local_b4 = pfVar4[2] + local_94;
                pfVar4 = FUN_0099c1a0(&local_7c, &local_48, &local_38);
                local_ac = local_bc;
                local_a8 = local_b8;
                local_a4 = local_b4;
            }
            local_a8 = local_a8 - pfVar4[1];
            local_ac = local_ac - pfVar4[0];
            local_a4 = local_a4 - pfVar4[2];
        }
    }

LAB_009afc60:
    if (*(int*)(*param_1 + 0x1f8) == local_2c) {
        FUN_009adfd0(ectx);
        FUN_009adfd0(ectx);
        uVar10 = *(unsigned*)(*param_1 + 0x204);
        uVar7 = *(int*)(*param_1 + 0x208) + uVar10;
        if (uVar10 < uVar7) {
            do {
                FUN_009ae590(uVar10, (int)local_18u, &local_6c, &local_90);
                uVar10 = uVar10 + 1;
            } while (uVar10 < uVar7);
            return;
        }
    } else {
        FUN_009adfd0(ectx);
        FUN_009adfd0(ectx);
        FUN_009adfd0(ectx);
        uVar10 = *(unsigned*)(*param_1 + 0x204);
        uVar7 = *(int*)(*param_1 + 0x208) + uVar10;
        for (; uVar10 < uVar7; uVar10 = uVar10 + 1) {
            FUN_009ae590(uVar10, local_2c, &local_6c, &local_90);
        }
        uVar10 = *(unsigned*)(*piVar6 + 0x204);
        uVar7 = *(int*)(*piVar6 + 0x208) + uVar10;
        for (; uVar10 < uVar7; uVar10 = uVar10 + 1) {
            FUN_009ae590(uVar10, (int)local_18u, &local_ac, &local_48);
        }
    }
    return;
}
