/* hk3AxisSweep broadphase sweep-and-prune axis updates and the
 * updateAabbs virtual that drives them (x/y/z via FUN_010f6ea0 /
 * FUN_010f7100 / FUN_010f7480). */

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

typedef unsigned short undefined2;
typedef unsigned int   undefined4;

extern void FUN_0107f530(int *arr, int size);   /* hkArrayUtil::_reserveMore */

extern void FUN_010f6ea0(int a, int b, int c, int d, uint e, uint f,
                         int *g, int *h);
extern void FUN_010f7100(int param_1, int param_2, ushort *param_3, ushort param_4,
                         uint param_5, uint param_6, int *param_7, int *param_8);
extern void FUN_010f7480(int param_1, int param_2, short *param_3, ushort param_4,
                         uint param_5, uint param_6, int *param_7, int *param_8);

extern float DAT_015ba360;
extern float DAT_015ba364;
extern float DAT_015ba368;
extern float DAT_015ba36c;

/* ------------------------------------------------------------------ */
// @ 0x010f7100
void FUN_010f7100(int param_1, int param_2, ushort *param_3, ushort param_4,
                  uint param_5, uint param_6, int *param_7, int *param_8)
{
    undefined4 *puVar1;
    undefined4 *puVar2;
    ushort *puVar3;
    ushort uVar4;
    ushort uVar5;
    ushort uVar6;
    ushort *puVar7;
    ushort uVar8;
    uint uVar9;
    short sVar10;
    undefined2 *puVar11;
    short *psVar12;

    uVar8 = *param_3;
    uVar9 = (uint)uVar8;
    uVar4 = *(ushort *)(*(int *)(param_1 + 0x58) + -4 + uVar9 * 4);
    puVar3 = (ushort *)(*(int *)(param_1 + 0x58) + uVar9 * 4);
    while (param_5 < uVar4) {
        puVar11 = (undefined2 *)((uint)puVar3[-1] * 0x10 + param_2);
        *puVar3 = uVar4;
        puVar3[1] = puVar3[-1];
        if ((uVar4 & 1) == 0) {
            *puVar11 = (short)uVar9;
        }
        else {
            uVar8 = param_3[3];
            uVar4 = param_3[5];
            uVar5 = param_3[4];
            uVar6 = param_3[1];
            puVar11[2] = (short)uVar9;
            if (-1 < (short)(uVar4 - puVar11[4] | uVar8 - puVar11[1] | puVar11[5] - uVar5 |
                             puVar11[3] - uVar6)) {
                if (param_7[1] == (param_7[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_7, 8);
                }
                puVar1 = (undefined4 *)(*param_7 + param_7[1] * 8);
                param_7[1] = param_7[1] + 1;
                *puVar1 = *(undefined4 *)(param_3 + 6);
                puVar1[1] = *(undefined4 *)(puVar11 + 6);
            }
        }
        puVar3[-1] = param_4;
        uVar9 = uVar9 - 1;
        uVar8 = (ushort)uVar9;
        uVar4 = puVar3[-4];
        puVar3 = puVar3 + -2;
    }
    *param_3 = uVar8;
    *puVar3 = (ushort)param_5;
    puVar1 = (undefined4 *)(*(int *)(param_1 + 0x58) + (uint)param_3[2] * 4);
    sVar10 = 0;
    uVar8 = *(ushort *)(puVar1 + 1);
    while (uVar8 < param_6) {
        sVar10 = sVar10 + 1;
        *puVar1 = puVar1[1];
        psVar12 = (short *)((uint)*(ushort *)((int)puVar1 + 6) * 0x10 + param_2);
        *(ushort *)((int)puVar1 + 6) = param_4;
        if ((uVar8 & 1) == 0) {
            uVar8 = param_3[3];
            uVar4 = param_3[5];
            uVar5 = param_3[4];
            uVar6 = param_3[1];
            *psVar12 = *psVar12 + -1;
            if (-1 < (short)(uVar4 - psVar12[4] | uVar8 - psVar12[1] | psVar12[5] - uVar5 |
                             psVar12[3] - uVar6)) {
                if (param_7[1] == (param_7[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_7, 8);
                }
                puVar2 = (undefined4 *)(*param_7 + param_7[1] * 8);
                param_7[1] = param_7[1] + 1;
                *puVar2 = *(undefined4 *)(param_3 + 6);
                puVar2[1] = *(undefined4 *)(psVar12 + 6);
            }
        }
        else {
            psVar12[2] = psVar12[2] + -1;
        }
        uVar8 = *(ushort *)(puVar1 + 2);
        puVar1 = puVar1 + 1;
    }
    param_3[2] = param_3[2] + sVar10;
    puVar1 = (undefined4 *)(*(int *)(param_1 + 0x58) + (uint)param_3[2] * 4);
    sVar10 = 0;
    uVar8 = *(ushort *)(puVar1 + -1);
    while (param_6 < uVar8) {
        sVar10 = sVar10 + -1;
        psVar12 = (short *)((uint)*(ushort *)((int)puVar1 + -2) * 0x10 + param_2);
        *puVar1 = puVar1[-1];
        *(ushort *)((int)puVar1 + -2) = param_4;
        if ((uVar8 & 1) == 0) {
            uVar8 = param_3[3];
            uVar4 = param_3[5];
            uVar5 = param_3[4];
            uVar6 = param_3[1];
            *psVar12 = *psVar12 + 1;
            if (-1 < (short)(uVar4 - psVar12[4] | uVar8 - psVar12[1] | psVar12[5] - uVar5 |
                             psVar12[3] - uVar6)) {
                if (param_8[1] == (param_8[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_8, 8);
                }
                puVar2 = (undefined4 *)(*param_8 + param_8[1] * 8);
                param_8[1] = param_8[1] + 1;
                *puVar2 = *(undefined4 *)(param_3 + 6);
                puVar2[1] = *(undefined4 *)(psVar12 + 6);
            }
        }
        else {
            psVar12[2] = psVar12[2] + 1;
        }
        uVar8 = *(ushort *)(puVar1 + -2);
        puVar1 = puVar1 + -1;
    }
    param_3[2] = param_3[2] + sVar10;
    *(short *)puVar1 = (short)param_6;
    puVar3 = (ushort *)(*(int *)(param_1 + 0x58) + (uint)*param_3 * 4);
    uVar9 = (uint)puVar3[2];
    sVar10 = 0;
    if (param_5 <= uVar9) {
        *param_3 = *param_3;
        *puVar3 = (ushort)param_5;
        return;
    }
    do {
        puVar7 = puVar3 + 2;
        psVar12 = (short *)((uint)puVar3[3] * 0x10 + param_2);
        sVar10 = sVar10 + 1;
        *(undefined4 *)puVar3 = *(undefined4 *)puVar7;
        puVar3[3] = param_4;
        if ((uVar9 & 1) == 0) {
            *psVar12 = *psVar12 + -1;
        }
        else {
            uVar8 = param_3[3];
            uVar4 = param_3[5];
            uVar5 = param_3[4];
            uVar6 = param_3[1];
            psVar12[2] = psVar12[2] + -1;
            if (-1 < (short)(uVar4 - psVar12[4] | uVar8 - psVar12[1] | psVar12[5] - uVar5 |
                             psVar12[3] - uVar6)) {
                if (param_8[1] == (param_8[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_8, 8);
                }
                puVar1 = (undefined4 *)(*param_8 + param_8[1] * 8);
                param_8[1] = param_8[1] + 1;
                *puVar1 = *(undefined4 *)(param_3 + 6);
                puVar1[1] = *(undefined4 *)(psVar12 + 6);
            }
        }
        uVar9 = (uint)puVar3[4];
        puVar3 = puVar7;
    } while (uVar9 < param_5);
    *param_3 = *param_3 + sVar10;
    *puVar7 = (ushort)param_5;
}

/* ------------------------------------------------------------------ */
// @ 0x010f7480
void FUN_010f7480(int param_1, int param_2, short *param_3, ushort param_4,
                  uint param_5, uint param_6, int *param_7, int *param_8)
{
    undefined4 *puVar1;
    undefined4 *puVar2;
    ushort *puVar3;
    ushort uVar4;
    short sVar5;
    short sVar6;
    short sVar7;
    short sVar8;
    ushort *puVar9;
    ushort uVar10;
    uint uVar11;
    short sVar12;
    short *psVar13;

    uVar10 = param_3[1];
    uVar11 = (uint)uVar10;
    uVar4 = *(ushort *)(*(int *)(param_1 + 100) + -4 + uVar11 * 4);
    puVar3 = (ushort *)(*(int *)(param_1 + 100) + uVar11 * 4);
    while (param_5 < uVar4) {
        psVar13 = (short *)((uint)puVar3[-1] * 0x10 + param_2);
        *puVar3 = uVar4;
        puVar3[1] = puVar3[-1];
        if ((uVar4 & 1) == 0) {
            psVar13[1] = (short)uVar11;
        }
        else {
            sVar12 = param_3[4];
            sVar5 = param_3[5];
            sVar6 = *param_3;
            sVar7 = param_3[2];
            psVar13[3] = (short)uVar11;
            if (-1 < (short)(sVar5 - psVar13[4] | psVar13[5] - sVar12 | psVar13[2] - sVar6 |
                             sVar7 - *psVar13)) {
                if (param_7[1] == (param_7[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_7, 8);
                }
                puVar1 = (undefined4 *)(*param_7 + param_7[1] * 8);
                param_7[1] = param_7[1] + 1;
                *puVar1 = *(undefined4 *)(param_3 + 6);
                puVar1[1] = *(undefined4 *)(psVar13 + 6);
            }
        }
        puVar3[-1] = param_4;
        uVar11 = uVar11 - 1;
        uVar10 = (ushort)uVar11;
        uVar4 = puVar3[-4];
        puVar3 = puVar3 + -2;
    }
    param_3[1] = uVar10;
    *puVar3 = (ushort)param_5;
    puVar1 = (undefined4 *)(*(int *)(param_1 + 100) + (uint)(ushort)param_3[3] * 4);
    sVar12 = 0;
    uVar10 = *(ushort *)(puVar1 + 1);
    while (uVar10 < param_6) {
        sVar12 = sVar12 + 1;
        *puVar1 = puVar1[1];
        psVar13 = (short *)((uint)*(ushort *)((int)puVar1 + 6) * 0x10 + param_2);
        *(ushort *)((int)puVar1 + 6) = param_4;
        if ((uVar10 & 1) == 0) {
            sVar5 = param_3[4];
            sVar6 = param_3[5];
            sVar7 = *param_3;
            sVar8 = param_3[2];
            psVar13[1] = psVar13[1] + -1;
            if (-1 < (short)(sVar6 - psVar13[4] | psVar13[5] - sVar5 | psVar13[2] - sVar7 |
                             sVar8 - *psVar13)) {
                if (param_7[1] == (param_7[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_7, 8);
                }
                puVar2 = (undefined4 *)(*param_7 + param_7[1] * 8);
                param_7[1] = param_7[1] + 1;
                *puVar2 = *(undefined4 *)(param_3 + 6);
                puVar2[1] = *(undefined4 *)(psVar13 + 6);
            }
        }
        else {
            psVar13[3] = psVar13[3] + -1;
        }
        uVar10 = *(ushort *)(puVar1 + 2);
        puVar1 = puVar1 + 1;
    }
    param_3[3] = param_3[3] + sVar12;
    puVar1 = (undefined4 *)(*(int *)(param_1 + 100) + (uint)(ushort)param_3[3] * 4);
    sVar12 = 0;
    uVar10 = *(ushort *)(puVar1 + -1);
    while (param_6 < uVar10) {
        sVar12 = sVar12 + -1;
        psVar13 = (short *)((uint)*(ushort *)((int)puVar1 + -2) * 0x10 + param_2);
        *puVar1 = puVar1[-1];
        *(ushort *)((int)puVar1 + -2) = param_4;
        if ((uVar10 & 1) == 0) {
            sVar5 = param_3[4];
            sVar6 = param_3[5];
            sVar7 = *param_3;
            sVar8 = param_3[2];
            psVar13[1] = psVar13[1] + 1;
            if (-1 < (short)(sVar6 - psVar13[4] | psVar13[5] - sVar5 | psVar13[2] - sVar7 |
                             sVar8 - *psVar13)) {
                if (param_8[1] == (param_8[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_8, 8);
                }
                puVar2 = (undefined4 *)(*param_8 + param_8[1] * 8);
                param_8[1] = param_8[1] + 1;
                *puVar2 = *(undefined4 *)(param_3 + 6);
                puVar2[1] = *(undefined4 *)(psVar13 + 6);
            }
        }
        else {
            psVar13[3] = psVar13[3] + 1;
        }
        uVar10 = *(ushort *)(puVar1 + -2);
        puVar1 = puVar1 + -1;
    }
    param_3[3] = param_3[3] + sVar12;
    *(short *)puVar1 = (short)param_6;
    puVar3 = (ushort *)(*(int *)(param_1 + 100) + (uint)(ushort)param_3[1] * 4);
    uVar11 = (uint)puVar3[2];
    sVar12 = 0;
    if (param_5 <= uVar11) {
        param_3[1] = param_3[1];
        *puVar3 = (ushort)param_5;
        return;
    }
    do {
        puVar9 = puVar3 + 2;
        psVar13 = (short *)((uint)puVar3[3] * 0x10 + param_2);
        sVar12 = sVar12 + 1;
        *(undefined4 *)puVar3 = *(undefined4 *)puVar9;
        puVar3[3] = param_4;
        if ((uVar11 & 1) == 0) {
            psVar13[1] = psVar13[1] + -1;
        }
        else {
            sVar5 = param_3[4];
            sVar6 = param_3[5];
            sVar7 = param_3[2];
            sVar8 = *param_3;
            psVar13[3] = psVar13[3] + -1;
            if (-1 < (short)(sVar6 - psVar13[4] | psVar13[5] - sVar5 | sVar7 - *psVar13 |
                             psVar13[2] - sVar8)) {
                if (param_8[1] == (param_8[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_8, 8);
                }
                puVar1 = (undefined4 *)(*param_8 + param_8[1] * 8);
                param_8[1] = param_8[1] + 1;
                *puVar1 = *(undefined4 *)(param_3 + 6);
                puVar1[1] = *(undefined4 *)(psVar13 + 6);
            }
        }
        uVar11 = (uint)puVar3[4];
        puVar3 = puVar9;
    } while (uVar11 < param_5);
    param_3[1] = param_3[1] + sVar12;
    *puVar9 = (ushort)param_5;
}

/* ------------------------------------------------------------------ */
struct hk3AxisSweep {
    void updateAabbs(undefined4 *param_2, float *param_3, int param_4,
                     int *param_5, int *param_6);
};

// @ 0x010f7800
void hk3AxisSweep::updateAabbs(undefined4 *param_2, float *param_3, int param_4,
                               int *param_5, int *param_6)
{
    int param_1 = (int)this;
    undefined4 *local_78;
    float local_70;
    float local_6c;
    float local_68;
    float local_64;
    float local_60;
    float local_5c;
    float local_58;
    float local_54;
    ushort kMinX;
    ushort kMinY;
    ushort kMinZ;
    ushort kMaxX;
    ushort kMaxY;
    ushort kMaxZ;
    int iVar1;
    int iVar2;
    int iVar4;

    local_78 = param_2;
    if (param_2 < param_2 + param_4) {
        do {
            local_70 = (param_3[0] + *(float *)(param_1 + 0x10)) * *(float *)(param_1 + 0x30);
            local_6c = (param_3[1] + *(float *)(param_1 + 0x14)) * *(float *)(param_1 + 0x34);
            local_68 = (param_3[2] + *(float *)(param_1 + 0x18)) * *(float *)(param_1 + 0x38);
            local_64 = (param_3[3] + *(float *)(param_1 + 0x1c)) * *(float *)(param_1 + 0x3c);
            if (DAT_015ba360 <= local_70) {
                local_70 = DAT_015ba360;
            }
            if (DAT_015ba364 <= local_6c) {
                local_6c = DAT_015ba364;
            }
            if (DAT_015ba368 <= local_68) {
                local_68 = DAT_015ba368;
            }
            if (DAT_015ba36c <= local_64) {
                local_64 = DAT_015ba36c;
            }
            if (local_70 <= 0.0f) {
                local_70 = 0.0f;
            }
            if (local_6c <= 0.0f) {
                local_6c = 0.0f;
            }
            if (local_68 <= 0.0f) {
                local_68 = 0.0f;
            }
            if (local_64 <= 0.0f) {
                local_64 = 0.0f;
            }
            local_70 = local_70 + 65536.0f;
            kMinX = (ushort)(*(uint *)&local_70 >> 7);
            local_6c = local_6c + 65536.0f;
            kMinY = (ushort)(*(uint *)&local_6c >> 7);
            local_68 = local_68 + 65536.0f;
            kMinZ = (ushort)(*(uint *)&local_68 >> 7);
            local_64 = local_64 + 65536.0f;
            local_60 = (param_3[4] + *(float *)(param_1 + 0x20)) * *(float *)(param_1 + 0x30);
            local_5c = (param_3[5] + *(float *)(param_1 + 0x24)) * *(float *)(param_1 + 0x34);
            local_58 = (param_3[6] + *(float *)(param_1 + 0x28)) * *(float *)(param_1 + 0x38);
            local_54 = (param_3[7] + *(float *)(param_1 + 0x2c)) * *(float *)(param_1 + 0x3c);
            if (DAT_015ba360 <= local_60) {
                local_60 = DAT_015ba360;
            }
            if (DAT_015ba364 <= local_5c) {
                local_5c = DAT_015ba364;
            }
            if (DAT_015ba368 <= local_58) {
                local_58 = DAT_015ba368;
            }
            if (DAT_015ba36c <= local_54) {
                local_54 = DAT_015ba36c;
            }
            if (local_60 <= 0.0f) {
                local_60 = 0.0f;
            }
            if (local_5c <= 0.0f) {
                local_5c = 0.0f;
            }
            if (local_58 <= 0.0f) {
                local_58 = 0.0f;
            }
            if (local_54 <= 0.0f) {
                local_54 = 0.0f;
            }
            local_60 = local_60 + 65536.0f;
            kMaxX = (ushort)(*(uint *)&local_60 >> 7);
            local_5c = local_5c + 65536.0f;
            kMaxY = (ushort)(*(uint *)&local_5c >> 7);
            local_58 = local_58 + 65536.0f;
            kMaxZ = (ushort)(*(uint *)&local_58 >> 7);
            local_54 = local_54 + 65536.0f;
            iVar1 = *(int *)(param_1 + 0x40);
            iVar2 = *(int *)*local_78;
            iVar4 = iVar2 * 0x10 + iVar1;
            FUN_010f6ea0(param_1, iVar1, iVar4, iVar2,
                         (uint)kMinX & 0xfffe, (uint)kMaxX & 0xffff | 1,
                         param_5, param_6);
            FUN_010f7100(param_1, iVar1, (ushort *)iVar4, (ushort)iVar2,
                         (uint)kMinY & 0xfffe, (uint)kMaxY & 0xffff | 1,
                         param_5, param_6);
            FUN_010f7480(param_1, iVar1, (short *)iVar4, (ushort)iVar2,
                         (uint)kMinZ & 0xfffe, (uint)kMaxZ & 0xffff | 1,
                         param_5, param_6);
            param_3 = param_3 + 8;
            local_78 = local_78 + 1;
        } while (local_78 < param_2 + param_4);
    }
}
