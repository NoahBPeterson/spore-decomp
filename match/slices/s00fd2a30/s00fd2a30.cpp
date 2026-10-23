// Slice s00fd2a30 -- nine functions from the SporeApp image (VAs 0x00fd2a30 .. 0x00fd3550).
//
// This is the baseline-JPEG decode unit: 0x00fd2a30 mirrors the DCT block edges into a padded
// sample buffer, 0x00fd2d00 is the fast Huffman bit receiver (state in ECX), 0x00fd2d60 builds the
// AC/DC Huffman lookup tables, 0x00fd2e30 / 0x00fd2f80 are fixed-point ARGB colour expanders,
// 0x00fd30a0 runs the IDCT + chroma upsample driver and 0x00fd3210 parses the DHT/DQT tables.
// 0x00fd34c0 / 0x00fd3550 are the per-component reset / predictor-table initialisers.
//
// flags: /O2 /MD /Gy /EHsc /TP  (per-row overrides in manifest.txt)
#include "types.h"
#include <string.h>

// ---------------------------------------------------------------- data (absolute image addresses)
extern unsigned char DAT_01493640[];
extern unsigned char DAT_01493658[];
extern unsigned char DAT_01493698[];
extern unsigned char DAT_014936b4[];
extern unsigned char DAT_014936d0[];

// ---------------------------------------------------------------- JPEG bit-stream helpers
extern int  FUN_00fcf130(int, int);                     // 0x00fcf130  look-ahead one bit
extern int  FUN_00fcef80(int);                          // 0x00fcef80  consume one bit
extern void FUN_00fd4cb0(int, int, int);                // 0x00fd4cb0
extern void FUN_00fd4e50(int, int);                     // 0x00fd4e50
extern void FUN_00fd6880(int);                          // 0x00fd6880

// ==================================================================== 0x00fd2a30
// @ 0x00fd2a30
void FUN_00fd2a30(unsigned char *param_1, void *param_2)
{
    int *piVar1;
    size_t sVar2;
    int iVar3;
    int *piVar4;
    void *pvVar5;
    unsigned char *pbVar6;
    void *pvVar7;
    unsigned char *pbVar8;
    void *_Src;
    unsigned int uVar9;
    unsigned char *local_14;
    unsigned char *local_10;
    unsigned int local_c;
    unsigned int local_8;

    piVar4 = (int *)param_1;
    piVar1 = (int *)((int)param_1 + 0x10);
    pbVar6 = (unsigned char *)(*(int *)param_1 + (int)param_2);
    local_14 = pbVar6 + *(int *)((int)param_1 + 0xc) * 8 + -1;
    sVar2 = *(size_t *)((int)param_1 + 0x14);
    uVar9 = *(unsigned int *)((int)param_1 + 0x1c);
    param_1 = pbVar6 - uVar9;
    local_c = *piVar1 * 8;
    local_10 = local_14 + 1;
    if (0 < (int)local_c) {
        do {
            memset(param_1, (unsigned int)*pbVar6, uVar9);
            memset(local_10, (unsigned int)*local_14, uVar9);
            local_14 = local_14 + sVar2;
            param_1 = param_1 + sVar2;
            local_10 = local_10 + sVar2;
            pbVar6 = pbVar6 + sVar2;
            local_c = local_c + -1;
        } while (local_c != 0);
    }
    pvVar7 = (void *)(sVar2 * uVar9 + (int)param_2);
    pvVar5 = (void *)((piVar4[4] * 8 + -1) * sVar2 + (int)pvVar7);
    param_1 = (unsigned char *)param_2;
    if (0 < (int)uVar9) {
        local_c = uVar9;
        do {
            memcpy(param_1, pvVar7, sVar2);
            memcpy((void *)((int)pvVar5 + (sVar2 - (int)param_2) + (int)param_1), pvVar5, sVar2);
            param_1 = param_1 + sVar2;
            local_c = local_c - 1;
        } while (local_c != 0);
    }
    sVar2 = piVar4[6];
    iVar3 = piVar4[4] * 4;
    pbVar8 = (unsigned char *)(piVar4[1] + (int)param_2);
    local_14 = pbVar8 + piVar4[3] * 4 + -1;
    local_10 = local_14 + 1;
    uVar9 = uVar9 >> 1;
    pbVar6 = pbVar8 - uVar9;
    local_8 = iVar3;
    if (0 < iVar3) {
        do {
            memset(pbVar6, (unsigned int)*pbVar8, uVar9);
            memset(local_10, (unsigned int)*local_14, uVar9);
            local_14 = local_14 + sVar2;
            pbVar6 = pbVar6 + sVar2;
            local_10 = local_10 + sVar2;
            pbVar8 = pbVar8 + sVar2;
            local_8 = local_8 + -1;
        } while (local_8 != 0);
    }
    pvVar7 = (void *)((piVar4[1] - uVar9) + (int)param_2);
    pvVar5 = (void *)((piVar4[4] * 4 + -1) * sVar2 + (int)pvVar7);
    param_1 = (unsigned char *)((int)pvVar7 - uVar9 * sVar2);
    if (uVar9 != 0) {
        local_8 = uVar9;
        do {
            memcpy(param_1, pvVar7, sVar2);
            memcpy((void *)((int)pvVar5 + (uVar9 * sVar2 - (int)pvVar7) + sVar2 + (int)param_1), pvVar5, sVar2);
            param_1 = param_1 + sVar2;
            local_8 = local_8 + -1;
        } while (local_8 != 0);
    }
    pbVar6 = (unsigned char *)(piVar4[2] + (int)param_2);
    local_14 = pbVar6 + piVar4[3] * 4 + -1;
    param_1 = pbVar6 - uVar9;
    local_10 = local_14 + 1;
    local_8 = iVar3;
    if (0 < iVar3) {
        do {
            memset(param_1, (unsigned int)*pbVar6, uVar9);
            memset(local_10, (unsigned int)*local_14, uVar9);
            local_14 = local_14 + sVar2;
            param_1 = param_1 + sVar2;
            local_10 = local_10 + sVar2;
            pbVar6 = pbVar6 + sVar2;
            local_8 = local_8 + -1;
        } while (local_8 != 0);
    }
    _Src = (void *)((piVar4[2] - uVar9) + (int)param_2);
    pvVar5 = (void *)((int)_Src - uVar9 * sVar2);
    pvVar7 = (void *)((piVar4[4] * 4 + -1) * sVar2 + (int)_Src);
    if (uVar9 != 0) {
        param_2 = (void *)uVar9;
        do {
            memcpy(pvVar5, _Src, sVar2);
            memcpy((void *)((int)pvVar7 + (uVar9 * sVar2 - (int)_Src) + sVar2 + (int)pvVar5), pvVar7, sVar2);
            pvVar5 = (void *)((int)pvVar5 + sVar2);
            param_2 = (void *)((int)param_2 - 1);
        } while (param_2 != (void *)0x0);
    }
    return;
}

// ==================================================================== 0x00fd2d00
// @ 0x00fd2d00
void __fastcall FUN_00fd2d00(int param_1)
{
    unsigned int uVar2;
    unsigned int uVar1;
    int iVar3;

    uVar2 = *(unsigned int *)(param_1 + 8);
    uVar1 = (*(int *)(param_1 + 4) + 1U) >> 1;
    if (uVar1 * 0x1000000 <= uVar2) {
        uVar2 = uVar2 + uVar1 * -0x1000000;
        uVar1 = *(int *)(param_1 + 4) - uVar1;
    }
    iVar3 = *(int *)(param_1 + 0xc) + -1;
    uVar2 = uVar2 * 2;
    if (iVar3 == 0) {
        uVar2 = uVar2 | *(unsigned char *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x10));
        iVar3 = 8;
        *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
    }
    *(unsigned int *)(param_1 + 4) = uVar1 * 2;
    *(int *)(param_1 + 0xc) = iVar3;
    *(unsigned int *)(param_1 + 8) = uVar2;
    return;
}

// ==================================================================== 0x00fd2d60
// @ 0x00fd2d60
void FUN_00fd2d60(int param_1, int param_2)
{
    unsigned int bVar1;
    unsigned int uVar2;
    int iVar3;
    unsigned char *pbVar4;
    unsigned int uVar5;

    iVar3 = 1;
    *(unsigned char *)(param_1 + 0x228) = 0;
    uVar5 = 0;
    do {
        uVar2 = 1;
        do {
            if (*(unsigned char *)(uVar2 + param_2) == uVar5) {
                *(char *)(param_1 + 0x228 + iVar3) = (char)uVar2;
                iVar3 = iVar3 + 1;
            }
            uVar2 = uVar2 + 1;
        } while (uVar2 < 0x40);
        uVar5 = uVar5 + 1;
    } while (uVar5 < 0x10);
    bVar1 = 0;
    pbVar4 = (unsigned char *)(param_1 + 0x268);
    iVar3 = bVar1 + 0x10;
    do {
        if (pbVar4[-0x40] > bVar1) {
            bVar1 = pbVar4[-0x40];
        }
        *pbVar4 = bVar1;
        if (6 < *(unsigned char *)(param_1 + 0x14c)) {
            *pbVar4 = bVar1 + 1;
        }
        if (pbVar4[-0x3f] > bVar1) {
            bVar1 = pbVar4[-0x3f];
        }
        pbVar4[1] = bVar1;
        if (6 < *(unsigned char *)(param_1 + 0x14c)) {
            pbVar4[1] = bVar1 + 1;
        }
        if (pbVar4[-0x3e] > bVar1) {
            bVar1 = pbVar4[-0x3e];
        }
        pbVar4[2] = bVar1;
        if (6 < *(unsigned char *)(param_1 + 0x14c)) {
            pbVar4[2] = bVar1 + 1;
        }
        if (pbVar4[-0x3d] > bVar1) {
            bVar1 = pbVar4[-0x3d];
        }
        pbVar4[3] = bVar1;
        if (6 < *(unsigned char *)(param_1 + 0x14c)) {
            pbVar4[3] = bVar1 + 1;
        }
        pbVar4 = pbVar4 + 4;
        iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    return;
}

// ==================================================================== 0x00fd2e30
// @ 0x00fd2e30
void FUN_00fd2e30(unsigned char *param_1, unsigned int *param_2)
{
    unsigned char bVar1;
    unsigned int uVar2;
    unsigned int uVar3;

    param_2[0xb] = (unsigned int)*param_1 * (unsigned int)param_1[1] >> 8;
    *param_2 = (0xff - (unsigned int)param_1[1]) * (unsigned int)*param_1 >> 8;
    bVar1 = *param_1;
    param_2[1] = (unsigned int)param_1[2] * (0xff - (unsigned int)bVar1) >> 8;
    uVar2 = (0xff - (unsigned int)param_1[2]) * (0xff - (unsigned int)bVar1) >> 8;
    uVar3 = param_1[3] * uVar2 >> 8;
    param_2[2] = param_1[4] * uVar3 >> 8;
    uVar3 = (0xff - (unsigned int)param_1[4]) * uVar3 >> 8;
    param_2[3] = param_1[5] * uVar3 >> 8;
    param_2[4] = (0xff - (unsigned int)param_1[5]) * uVar3 >> 8;
    uVar3 = (0xff - (unsigned int)param_1[3]) * uVar2 >> 8;
    uVar2 = param_1[6] * uVar3 >> 8;
    param_2[5] = param_1[7] * uVar2 >> 8;
    param_2[6] = (0xff - (unsigned int)param_1[7]) * uVar2 >> 8;
    uVar2 = (0xff - (unsigned int)param_1[6]) * uVar3 >> 8;
    uVar3 = param_1[8] * uVar2 >> 8;
    param_2[7] = param_1[9] * uVar3 >> 8;
    param_2[8] = (0xff - (unsigned int)param_1[9]) * uVar3 >> 8;
    uVar2 = (0xff - (unsigned int)param_1[8]) * uVar2 >> 8;
    param_2[9] = param_1[10] * uVar2 >> 8;
    param_2[10] = (0xff - (unsigned int)param_1[10]) * uVar2 >> 8;
    return;
}

// ==================================================================== 0x00fd2f80
// @ 0x00fd2f80
void FUN_00fd2f80(unsigned char *param_1, unsigned int *param_2)
{
    unsigned int uVar1;

    uVar1 = (unsigned int)*param_1 * (unsigned int)param_1[1] >> 8;
    *param_2 = param_1[2] * uVar1 >> 8;
    param_2[1] = (0xff - (unsigned int)param_1[2]) * uVar1 >> 8;
    uVar1 = (0xff - (unsigned int)param_1[1]) * (unsigned int)*param_1 >> 8;
    param_2[2] = param_1[3] * uVar1 >> 8;
    param_2[3] = (0xff - (unsigned int)param_1[3]) * uVar1 >> 8;
    uVar1 = ((0xff - (unsigned int)*param_1) * (unsigned int)param_1[4] >> 8) * (unsigned int)param_1[5] >> 8;
    param_2[4] = param_1[6] * uVar1 >> 8;
    param_2[5] = (0xff - (unsigned int)param_1[6]) * uVar1 >> 8;
    uVar1 = ((0xff - (unsigned int)*param_1) * (unsigned int)param_1[4] >> 8) * (0xff - (unsigned int)param_1[5]) >> 8;
    param_2[6] = param_1[7] * uVar1 >> 8;
    param_2[7] = (0xff - (unsigned int)param_1[7]) * uVar1 >> 8;
    param_2[8] = (0xff - (unsigned int)*param_1) * (0xff - (unsigned int)param_1[4]) >> 8;
    return;
}

// ==================================================================== 0x00fd30a0
// @ 0x00fd30a0
void FUN_00fd30a0(int param_1)
{
    int iVar1;
    int iVar2;
    int iVar3;
    int local_14;
    int local_10;
    int local_c;
    int local_8;
    int local_4;

    local_14 = param_1 + 0x2390;
    iVar3 = param_1 + 0x368;
    iVar2 = param_1 + 0x488;
    iVar1 = param_1 + 0x39a2;
    local_10 = 2;
    do {
        FUN_00fd2e30((unsigned char *)iVar1, (unsigned int *)iVar2);
        FUN_00fd4cb0(iVar3, iVar2, 0xc);
        FUN_00fd4e50(iVar3, local_14);
        local_14 = local_14 + 0x80;
        iVar1 = iVar1 + 0xb;
        iVar2 = iVar2 + 0x30;
        iVar3 = iVar3 + 0x90;
        local_10 = local_10 + -1;
    } while (local_10 != 0);
    local_14 = param_1 + 0x3690;
    iVar3 = param_1 + 0x21b0;
    iVar2 = param_1 + 0x2300;
    iVar1 = param_1 + 0x334;
    local_10 = 2;
    do {
        FUN_00fd2f80((unsigned char *)iVar1, (unsigned int *)iVar2);
        FUN_00fd4cb0(iVar3, iVar2, 9);
        FUN_00fd4e50(iVar3, local_14);
        local_14 = local_14 + 0x80;
        iVar2 = iVar2 + 0x38;
        iVar1 = iVar1 + 0xe;
        iVar3 = iVar3 + 0xa8;
        local_10 = local_10 + -1;
    } while (local_10 != 0);
    local_10 = param_1 + 0x39b8;
    iVar3 = param_1 + 0x500;
    iVar2 = param_1 + 0x2490;
    param_1 = param_1 + 0x1940;
    local_4 = 3;
    do {
        local_14 = local_10;
        local_8 = 2;
        do {
            local_c = 6;
            iVar1 = local_14;
            do {
                FUN_00fd2e30((unsigned char *)iVar1, (unsigned int *)param_1);
                FUN_00fd4cb0(iVar3, param_1, 0xc);
                FUN_00fd4e50(iVar3, iVar2);
                iVar1 = iVar1 + 0xb;
                param_1 = param_1 + 0x30;
                iVar2 = iVar2 + 0x80;
                iVar3 = iVar3 + 0x90;
                local_c = local_c + -1;
            } while (local_c != 0);
            local_14 = local_14 + 0xc6;
            local_8 = local_8 + -1;
        } while (local_8 != 0);
        local_10 = local_10 + 0x42;
        local_4 = local_4 + -1;
    } while (local_4 != 0);
    return;
}

// ==================================================================== 0x00fd3210
// @ 0x00fd3210
void FUN_00fd3210(int param_1, char param_2)
{
    char cVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    unsigned int uVar5;
    unsigned int uVar6;
    unsigned int uVar7;
    unsigned char *puVar10;
    int local_1c;
    int local_18;
    int local_10;
    char local_c[12];

    local_c[0] = -0x80;
    local_c[1] = -0x80;
    local_c[2] = -0x80;
    local_c[3] = -0x80;
    local_c[4] = -0x80;
    local_c[5] = -0x80;
    local_c[6] = -0x80;
    local_c[7] = -0x80;
    local_c[8] = -0x80;
    local_c[9] = -0x80;
    local_c[10] = -0x80;

    iVar4 = param_1 + 0x10c;
    local_1c = 0;
    do {
        uVar7 = 0;
        do {
            iVar2 = FUN_00fcf130(iVar4, DAT_01493640[uVar7 + local_1c]);
            if (iVar2 == 0) {
                if (param_2 == 0) {
                    *(char *)(local_1c + uVar7 + 0x39a2 + param_1) = local_c[uVar7];
                }
            } else {
                uVar5 = 0;
                iVar2 = 6;
                do {
                    iVar3 = FUN_00fcef80(iVar4);
                    uVar5 = uVar5 | iVar3 << iVar2;
                    iVar2 = iVar2 + -1;
                } while (-1 < iVar2);
                cVar1 = (char)uVar5 * 2;
                cVar1 = (cVar1 == 0) + cVar1;
                local_c[uVar7] = cVar1;
                *(char *)(local_1c + uVar7 + 0x39a2 + param_1) = cVar1;
            }
            uVar7 = uVar7 + 1;
        } while (uVar7 < 0xb);
        local_1c = local_1c + 0xb;
    } while (local_1c < 0x16);
    if (param_2 == 0) {
        unsigned int *puVar8 = (unsigned int *)DAT_014936b4;
        unsigned int *puVar9 = (unsigned int *)(param_1 + 0x334);
        for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar9 = *puVar8;
            puVar8 = puVar8 + 1;
            puVar9 = puVar9 + 1;
        }
    }
    iVar2 = FUN_00fcf130(iVar4, 0x80);
    if (iVar2 != 0) {
        uVar7 = 1;
        do {
            iVar2 = FUN_00fcf130(iVar4, DAT_01493658[uVar7]);
            if (iVar2 != 0) {
                uVar5 = 0;
                iVar2 = 3;
                do {
                    iVar3 = FUN_00fcef80(iVar4);
                    uVar5 = uVar5 | iVar3 << iVar2;
                    iVar2 = iVar2 + -1;
                } while (-1 < iVar2);
                *(char *)(uVar7 + 0x2a8 + param_1) = (char)uVar5;
            }
            uVar7 = uVar7 + 1;
        } while (uVar7 < 0x40);
        FUN_00fd2d60(param_1, param_1 + 0x2a8);
    }
    local_1c = 0;
    do {
        uVar7 = 0;
        do {
            iVar2 = FUN_00fcf130(iVar4, DAT_01493698[uVar7 + local_1c]);
            if (iVar2 != 0) {
                uVar5 = 0;
                iVar2 = 6;
                do {
                    iVar3 = FUN_00fcef80(iVar4);
                    uVar5 = uVar5 | iVar3 << iVar2;
                    iVar2 = iVar2 + -1;
                } while (-1 < iVar2);
                cVar1 = (char)uVar5 * 2;
                *(char *)(local_1c + uVar7 + 0x334 + param_1) = (cVar1 == 0) + cVar1;
            }
            uVar7 = uVar7 + 1;
        } while (uVar7 < 0xe);
        local_1c = local_1c + 0xe;
    } while (local_1c < 0x1c);
    local_18 = 0;
    puVar10 = DAT_014936d0;
    do {
        local_1c = local_18;
        local_10 = 2;
        do {
            unsigned int jj = 0;
            do {
                unsigned int kk = 0;
                do {
                    iVar4 = FUN_00fcf130(param_1 + 0x10c, puVar10[kk]);
                    if (iVar4 == 0) {
                        if (param_2 == 0) {
                            *(char *)((local_1c + jj) * 0xb + kk + 0x39b8 + param_1) = local_c[kk];
                        }
                    } else {
                        uVar6 = 0;
                        iVar4 = 6;
                        do {
                            iVar2 = FUN_00fcef80(param_1 + 0x10c);
                            uVar6 = uVar6 | iVar2 << iVar4;
                            iVar4 = iVar4 + -1;
                        } while (-1 < iVar4);
                        cVar1 = (char)uVar6 * 2;
                        cVar1 = (cVar1 == 0) + cVar1;
                        local_c[kk] = cVar1;
                        *(char *)((local_1c + jj) * 0xb + kk + 0x39b8 + param_1) = cVar1;
                    }
                    kk = kk + 1;
                } while (kk < 0xb);
                jj = jj + 1;
                puVar10 = puVar10 + 0xb;
            } while (jj < 6);
            local_1c = local_1c + 0x12;
            local_10 = local_10 + -1;
        } while (local_10 != 0);
        local_18 = local_18 + 6;
    } while ((int)puVar10 < 0x149385c);
    FUN_00fd6880(param_1);
    return;
}

// ==================================================================== 0x00fd34c0
// @ 0x00fd34c0
void FUN_00fd34c0(int param_1)
{
    int *piVar1;
    int i;

    piVar1 = (int *)(param_1 + 0x84);
    for (i = 0; i < 4; i = i + 1) {
        piVar1[i * 4] = 0;
        piVar1[i * 4 + 2] = 0;
        piVar1[i * 4 + 3] = 0;
    }
    for (i = 0; i < 4; i = i + 1) {
        piVar1[i * 4 + 1] = -1;
    }
    *(unsigned short *)(param_1 + 0x8c) = 4;
    *(unsigned short *)(param_1 + 0x9c) = 4;
    *(unsigned short *)(param_1 + 0xac) = 4;
    *(unsigned short *)(param_1 + 0xbc) = 4;
    return;
}

// ==================================================================== 0x00fd3550
// @ 0x00fd3550
void FUN_00fd3550(int param_1)
{
    unsigned short *puVar1;
    int iVar2;
    unsigned int uVar3;

    uVar3 = 0;
    if (*(int *)(param_1 + 0x17c) + 8 != 0) {
        iVar2 = 0;
        do {
            *(unsigned int *)(*(int *)(param_1 + 0xc4) + 4 + iVar2) = 0xffffffff;
            *(unsigned short *)(*(int *)(param_1 + 0xc4) + 8 + iVar2) = 4;
            *(unsigned short *)(*(int *)(param_1 + 0xc4) + 10 + iVar2) = 0;
            *(unsigned char *)(*(int *)(param_1 + 0xc4) + iVar2) = 0;
            uVar3 = uVar3 + 1;
            iVar2 = iVar2 + 0x10;
        } while (uVar3 < *(int *)(param_1 + 0x17c) + 8U);
    }
    uVar3 = 0;
    if ((*(unsigned int *)(param_1 + 0x17c) >> 1) + 8 != 0) {
        iVar2 = 0;
        do {
            *(unsigned int *)(*(int *)(param_1 + 200) + 4 + iVar2) = 0xffffffff;
            *(unsigned short *)(*(int *)(param_1 + 200) + 8 + iVar2) = 4;
            *(unsigned char *)(*(int *)(param_1 + 200) + iVar2) = 0;
            *(unsigned short *)(*(int *)(param_1 + 200) + 10 + iVar2) = 0;
            *(unsigned int *)(*(int *)(param_1 + 0xcc) + 4 + iVar2) = 0xffffffff;
            *(unsigned short *)(*(int *)(param_1 + 0xcc) + 8 + iVar2) = 4;
            *(unsigned char *)(*(int *)(param_1 + 0xcc) + iVar2) = 0;
            *(unsigned short *)(*(int *)(param_1 + 0xcc) + 10 + iVar2) = 0;
            uVar3 = uVar3 + 1;
            iVar2 = iVar2 + 0x10;
        } while (uVar3 < (*(unsigned int *)(param_1 + 0x17c) >> 1) + 8);
    }
    if (*(unsigned char *)(param_1 + 0x14c) < 6) {
        *(unsigned int *)(*(int *)(param_1 + 200) + 0x14) = 0;
        *(unsigned short *)(*(int *)(param_1 + 200) + 0x18) = 0;
        *(unsigned int *)(*(int *)(param_1 + 0xcc) + 0x14) = 0;
        *(unsigned short *)(*(int *)(param_1 + 0xcc) + 0x18) = 0;
    }
    *(unsigned short *)(param_1 + 0xdc) = 0;
    *(unsigned short *)(param_1 + 0xe4) = 0x80;
    *(unsigned short *)(param_1 + 0xec) = 0x80;
    puVar1 = (unsigned short *)(param_1 + 0xe6);
    iVar2 = 2;
    do {
        puVar1[-4] = 0;
        *puVar1 = 0;
        puVar1[4] = 0;
        puVar1 = puVar1 + 1;
        iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    return;
}
