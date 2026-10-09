// Slice s00799cc0 -- UTFKernel graphics/split-transform helpers (final batch).
// Flags: /O2 /MD /Gy /EHsc /TP /fp:fast (scalar math is x87 here).

#include <intrin.h>
#include <math.h>

const char *const ALLOC_PATH =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

extern int DAT_0153b208[];
extern float DAT_01634510;
extern float DAT_01634514;
extern float DAT_01634518;
extern int DAT_01634650;

extern int V_13ebc60;
extern int V_140f580;
extern int V_140f588;
extern int V_140f58c;
extern int V_13ef094;

extern int FUN_00f473a0(...);
extern int FUN_00f47380(...);
extern int FUN_011e0744(...);
extern int FUN_01023030(...);
extern int FUN_00537dc0(...);
extern int FUN_008def80(...);

extern void FUN_00798e40(int, float, void *, void *, void *);
extern void FUN_007994d0(int, float, void *, void *, void *);
extern void FUN_00799110(int, float, void *, void *, void *);
extern void FUN_00799640(int, float, void *, void *, void *);
extern void FUN_00798ed0(int, float, void *, void *, void *);
extern void FUN_00798fb0(int, float, void *, void *, void *);
extern void FUN_00799050(int, float, void *, void *, void *);
extern void FUN_00799090(int, float, void *, void *, void *);

extern void FUN_00799290(int **, int *, int *, int *);
extern void FUN_007992e0(int *, int *, int *);
extern int FUN_0079a5a0(int, int);
extern int FUN_0079a630(int, int);
extern void __fastcall FUN_0079ac70(int *);

struct StubCtor { void *c(void *); };
struct VCtor16 { void c0(int *); };

// @ 0x00799cc0
void VCtor16::c0(int *param_2)
{
    int *param_1 = (int *)this;
    param_1[0] = (int)&V_13ebc60;
    param_1[1] = 0;
    param_1[2] = 4;
    *(float *)(param_1 + 3) = *(float *)param_2;
    *(float *)(param_1 + 4) = *(float *)(param_2 + 1);
    *(float *)(param_1 + 5) = *(float *)(param_2 + 2);
    *(float *)(param_1 + 6) = *(float *)(param_2 + 3);
    param_1[0] = (int)&V_140f580;
    return;
}

// @ 0x00799e00
int *FUN_00799e00(int param_1, int param_2, int *param_3)
{
    int iVar6;
    int *piVar5;
    int iVar2;

    if (param_2 == param_1) {
        return param_3;
    }
    do {
        int *puVar3 = *(int **)(param_2 - 8);
        int *puVar4 = (int *)param_3[-2];
        iVar6 = param_2 - 8;
        piVar5 = param_3 - 2;
        if (puVar3 != puVar4) {
            if (puVar3 != 0) {
                _InterlockedIncrement((volatile long *)((char *)puVar3 + 4));
            }
            *piVar5 = (int)puVar3;
            if (puVar4 != 0) {
                long *piVar1 = (long *)(puVar4 + 1);
                iVar2 = (int)*piVar1;
                *piVar1 = *piVar1 + -1;
                if (iVar2 == 1) {
                    *piVar1 = 1;
                    (*(void (__thiscall **)(int *, int)) * puVar4)(puVar4, 1);
                }
            }
        }
        param_3[-1] = *(int *)(param_2 - 4);
        param_3 = piVar5;
        param_2 = iVar6;
    } while (iVar6 != param_1);
    return piVar5;
}

// @ 0x00799e70
void FUN_00799e70(int param_1, int param_2, float param_3, void *param_4, void *param_5,
                  void *param_6)
{
    switch (param_2) {
    case 1:  FUN_00798e40(DAT_0153b208[param_1], param_3, param_4, param_5, param_6); return;
    case 2:  FUN_007994d0(DAT_0153b208[param_1], param_3, param_4, param_5, param_6); return;
    case 3:  FUN_00799110(DAT_0153b208[param_1], param_3, param_4, param_5, param_6); return;
    case 4:  FUN_00799640(DAT_0153b208[param_1], param_3, param_4, param_5, param_6); return;
    case 5:  FUN_00798ed0(DAT_0153b208[param_1], param_3, param_4, param_5, param_6); return;
    case 6:  FUN_00798fb0(DAT_0153b208[param_1], param_3, param_4, param_5, param_6); return;
    case 7:  FUN_00799050(DAT_0153b208[param_1], param_3, param_4, param_5, param_6); return;
    case 8:  FUN_00799050(DAT_0153b208[param_1], param_3, param_4, param_5, param_6); return;
    case 9:  FUN_00799090(DAT_0153b208[param_1], param_3, param_4, param_5, param_6); return;
    case 10: FUN_00799050(DAT_0153b208[param_1], param_3, param_4, param_5, param_6); return;
    case 11: FUN_00799050(DAT_0153b208[param_1], param_3, param_4, param_5, param_6); return;
    case 12: FUN_00799090(DAT_0153b208[param_1], param_3, param_4, param_5, param_6); return;
    }
    return;
}

// @ 0x0079a0d0
void __fastcall FUN_0079a0d0(unsigned char *param_1, unsigned char *param_2)
{
    int iVar14;
    float local_24, local_20, local_1c, local_18, local_14, local_10, local_c, local_8, local_4;
    float *pfVar16;
    int *puVar15 = &DAT_01634650;
    unsigned char *pbVar17 = param_1 + 0x50;
    for (iVar14 = 9; iVar14 != 0; iVar14 = iVar14 + -1) {
        *(int *)pbVar17 = *puVar15;
        puVar15 = puVar15 + 1;
        pbVar17 = pbVar17 + 4;
    }
    param_1[0x4c] = 0;
    param_1[0x4d] = 0;
    param_1[0x4e] = 0x80;
    param_1[0x4f] = 0x3f;
    *(int *)(param_1 + 0x40) = *(int *)&DAT_01634510;
    *(int *)(param_1 + 0x44) = *(int *)&DAT_01634514;
    *(int *)(param_1 + 0x48) = *(int *)&DAT_01634518;
    *(short *)(param_1 + 0x3e) = 0;
    *(short *)(param_1 + 0x3c) = 0;
    int uVar13 = *(int *)(param_2 + 0x10);
    *(short *)(param_1 + 0x3e) = *(short *)(param_1 + 0x3e) + 1;
    *(int *)(param_1 + 0x4c) = uVar13;
    if ((*param_1 & 1) != 0) {
        *(unsigned short *)(param_1 + 0x3c) = *(unsigned short *)(param_1 + 0x3c) | 1;
        *(short *)(param_1 + 0x3e) = *(short *)(param_1 + 0x3e) + 1;
        *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x14) * *(float *)(param_1 + 0x4c);
    }
    if (((param_1[4] >> 2) & 1) != 0) {
        *(int *)(param_1 + 0x40) = *(int *)(param_1 + 8);
        *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0xc);
        *(unsigned short *)(param_1 + 0x3c) = *(unsigned short *)(param_1 + 0x3c) | 4;
        *(short *)(param_1 + 0x3e) = *(short *)(param_1 + 0x3e) + 1;
        *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x10);
    }
    if (((*param_1 & 2) != 0) && (((*param_2 >> 2) & 1) != 0)) {
        float fVar1 = *(float *)(param_2 + 8);
        float fVar2 = *(float *)(param_2 + 0xc);
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) + *(float *)(param_2 + 4);
        *(float *)(param_1 + 0x44) = fVar1 + *(float *)(param_1 + 0x44);
        *(float *)(param_1 + 0x48) = fVar2 + *(float *)(param_1 + 0x48);
        *(unsigned short *)(param_1 + 0x3c) = *(unsigned short *)(param_1 + 0x3c) | 4;
        *(short *)(param_1 + 0x3e) = *(short *)(param_1 + 0x3e) + 1;
    }
    if (((*param_1 >> 1) & 1) == 0) {
        if (((*param_2 >> 1) & 1) == 0) return;
        pfVar16 = (float *)(param_2 + 0x14);
    } else if (((*param_2 >> 1) & 1) == 0) {
        pfVar16 = (float *)(param_1 + 0x18);
    } else {
        float fVar1 = *(float *)(param_1 + 0x1c);
        float fVar2 = *(float *)(param_2 + 0x20);
        float fVar3 = *(float *)(param_2 + 0x14);
        float fVar4 = *(float *)(param_2 + 0x2c);
        local_24 = (fVar3 * *(float *)(param_1 + 0x18) + fVar2 * fVar1) +
                   fVar4 * *(float *)(param_1 + 0x20);
        float fVar5 = *(float *)(param_2 + 0x30);
        float fVar6 = *(float *)(param_2 + 0x24);
        float fVar7 = *(float *)(param_2 + 0x18);
        float fVar8 = *(float *)(param_2 + 0x34);
        local_20 = (fVar7 * *(float *)(param_1 + 0x18) + fVar6 * fVar1) +
                   fVar5 * *(float *)(param_1 + 0x20);
        float fVar9 = *(float *)(param_2 + 0x28);
        float fVar10 = *(float *)(param_2 + 0x1c);
        local_1c = (fVar10 * *(float *)(param_1 + 0x18) + fVar9 * fVar1) +
                   fVar8 * *(float *)(param_1 + 0x20);
        local_18 = (fVar3 * *(float *)(param_1 + 0x24) + fVar2 * *(float *)(param_1 + 0x28)) +
                   fVar4 * *(float *)(param_1 + 0x2c);
        local_14 = (fVar7 * *(float *)(param_1 + 0x24) + fVar6 * *(float *)(param_1 + 0x28)) +
                   fVar5 * *(float *)(param_1 + 0x2c);
        local_10 = (fVar10 * *(float *)(param_1 + 0x24) + fVar9 * *(float *)(param_1 + 0x28)) +
                   fVar8 * *(float *)(param_1 + 0x2c);
        fVar1 = *(float *)(param_1 + 0x34);
        float fVar11 = *(float *)(param_1 + 0x30);
        float fVar12 = *(float *)(param_1 + 0x38);
        local_c = (fVar3 * fVar11 + fVar2 * fVar1) + fVar4 * fVar12;
        local_8 = (fVar7 * fVar11 + fVar6 * fVar1) + fVar5 * fVar12;
        local_4 = (fVar10 * fVar11 + fVar9 * fVar1) + fVar8 * fVar12;
        pfVar16 = &local_24;
    }
    float *pfVar18 = (float *)(param_1 + 0x50);
    for (iVar14 = 9; iVar14 != 0; iVar14 = iVar14 + -1) {
        *pfVar18 = *pfVar16;
        pfVar16 = pfVar16 + 1;
        pfVar18 = pfVar18 + 1;
    }
    *(unsigned short *)(param_1 + 0x3c) = *(unsigned short *)(param_1 + 0x3c) | 2;
    *(short *)(param_1 + 0x3e) = *(short *)(param_1 + 0x3e) + 1;
    return;
}

// @ 0x0079a4f0
void __fastcall FUN_0079a4f0(int *param_1, unsigned int param_2)
{
    int iVar1;
    int _Dst;
    if ((unsigned int)((param_1[2] - *param_1) / 0x14) < param_2) {
        if (param_2 == 0) {
            _Dst = 0;
        } else {
            _Dst = FUN_00f473a0(param_2 * 0x14, "Graphics", 0, 0, ALLOC_PATH, 0xd1);
        }
        FUN_011e0744(_Dst, *param_1, param_1[1] - *param_1, 0);
        iVar1 = *param_1;
        if ((iVar1 != 0) && (*(int *)(iVar1 - 4) != 0)) {
            FUN_00f47380(iVar1);
        }
        iVar1 = *param_1;
        *param_1 = _Dst;
        param_1[1] = _Dst + ((param_1[1] - iVar1) / 0x14) * 0x14;
        param_1[2] = _Dst + param_2 * 0x14;
    }
    return;
}

// @ 0x0079a5a0
int FUN_0079a5a0(int param_1, int param_2)
{
    int iVar1;
    if (param_1 == 0) {
        iVar1 = FUN_00f473a0(0x1c, "Graphics", 0, 0, 0, 0);
        if (iVar1 != 0) return (int)((StubCtor *)iVar1)->c((void *)param_2);
    } else if (param_1 == 1) {
        iVar1 = FUN_00f473a0(0x1c, "Graphics", 0, 0, 0, 0);
        if (iVar1 != 0) return (int)((StubCtor *)iVar1)->c((void *)param_2);
    } else if (param_1 == 2) {
        iVar1 = FUN_00f473a0(0x28, "Graphics", 0, 0, 0, 0);
        if (iVar1 != 0) return (int)((StubCtor *)iVar1)->c((void *)param_2);
    }
    return 0;
}

// @ 0x0079a630
int FUN_0079a630(int param_1, int param_2)
{
    int iVar1;
    if (param_1 == 0) {
        iVar1 = FUN_00f473a0(0x20, "Graphics", 0, 0, 0, 0);
        if (iVar1 != 0) return (int)((StubCtor *)iVar1)->c((void *)param_2);
    } else if (param_1 == 1) {
        iVar1 = FUN_00f473a0(0x20, "Graphics", 0, 0, 0, 0);
        if (iVar1 != 0) return (int)((StubCtor *)iVar1)->c((void *)param_2);
    } else if (param_1 == 2) {
        iVar1 = FUN_00f473a0(0x2c, "Graphics", 0, 0, 0, 0);
        if (iVar1 != 0) return (int)((StubCtor *)iVar1)->c((void *)param_2);
    }
    return 0;
}

// @ 0x0079a710
int *FUN_0079a710(int *param_1, int *param_2, int *param_3, int param_4)
{
    int *piVar1;
    *param_1 = param_4;
    for (; param_2 != param_3; param_2 = param_2 + 5) {
        piVar1 = (int *)*param_1;
        if (piVar1 != 0) {
            int iVar3 = (param_2[1] - *param_2) >> 3;
            int iVar2;
            if (iVar3 == 0) iVar2 = 0;
            else iVar2 = FUN_00f473a0(iVar3 * 8, "Graphics", 0, 0, ALLOC_PATH, 0xd1);
            *piVar1 = iVar2;
            piVar1[1] = iVar2;
            piVar1[2] = iVar2 + iVar3 * 8;
            int local_18 = 0;
            FUN_00799290((int **)&local_18, (int *)*param_2, (int *)param_2[1], (int *)iVar2);
            piVar1[1] = local_18;
        }
        *param_1 = *param_1 + 0x14;
    }
    return param_1;
}

// @ 0x0079a800
int *FUN_0079a800(int *param_1, int *param_2, int *param_3, int param_4)
{
    *param_1 = param_4;
    for (; param_2 != param_3; param_2 = param_2 + 5) {
        int *piVar1 = (int *)*param_1;
        if (piVar1 != 0) {
            int iVar4 = (param_2[1] - *param_2) >> 3;
            int *puVar2;
            if (iVar4 == 0) puVar2 = 0;
            else puVar2 = (int *)FUN_00f473a0(iVar4 * 8, "Graphics", 0, 0, ALLOC_PATH, 0xd1);
            *piVar1 = (int)puVar2;
            piVar1[1] = (int)puVar2;
            piVar1[2] = (int)puVar2 + iVar4 * 8;
            int iVar3 = *param_2;
            while (iVar3 != param_2[1]) {
                if (puVar2 != 0) {
                    *puVar2 = *(int *)iVar3;
                    puVar2[1] = *(int *)(iVar3 + 4);
                }
                puVar2 = puVar2 + 2;
                iVar3 += 8;
            }
            piVar1[1] = (int)puVar2;
        }
        *param_1 = *param_1 + 0x14;
    }
    return param_1;
}

// @ 0x0079a8f0
void FUN_0079a8f0(int *param_1, int param_2, int *param_3)
{
    for (; param_2 != 0; param_2 = param_2 + -1) {
        if (param_1 != 0) {
            int iVar3 = (param_3[1] - *param_3) >> 3;
            int *puVar1;
            if (iVar3 == 0) puVar1 = 0;
            else puVar1 = (int *)FUN_00f473a0(iVar3 * 8, "Graphics", 0, 0, ALLOC_PATH, 0xd1);
            *param_1 = (int)puVar1;
            param_1[1] = (int)puVar1;
            param_1[2] = (int)puVar1 + iVar3 * 8;
            int iVar2 = *param_3;
            while (iVar2 != param_3[1]) {
                if (puVar1 != 0) {
                    *puVar1 = *(int *)iVar2;
                    puVar1[1] = *(int *)(iVar2 + 4);
                }
                puVar1 = puVar1 + 2;
                iVar2 += 8;
            }
            param_1[1] = (int)puVar1;
        }
        param_1 = param_1 + 5;
    }
    return;
}

// @ 0x0079a9d0
void FUN_0079a9d0(int *param_1, int param_2, int *param_3)
{
    int *piVar4 = param_1;
    for (int iVar3 = param_2; iVar3 != 0; iVar3 = iVar3 + -1) {
        if (piVar4 != 0) {
            int iVar5 = (param_3[1] - *param_3) >> 3;
            int iVar2;
            if (iVar5 == 0) iVar2 = 0;
            else iVar2 = FUN_00f473a0(iVar5 * 8, "Graphics", 0, 0, ALLOC_PATH, 0xd1);
            *piVar4 = iVar2;
            piVar4[1] = iVar2;
            piVar4[2] = iVar2 + iVar5 * 8;
            int local = 0;
            FUN_00799290((int **)&local, (int *)*param_3, (int *)param_3[1], (int *)iVar2);
            piVar4[1] = local;
        }
        piVar4 = piVar4 + 5;
    }
    return;
}

// @ 0x0079aaa0
int *FUN_0079aaa0(int param_1, int param_2, int *param_3)
{
    if (param_2 != param_1) {
        do {
            int *puVar1 = (int *)(param_2 - 0x78);
            param_2 = param_2 - 0x78;
            param_3 = param_3 - 0x1e;
            *param_3 = *puVar1;
            FUN_00537dc0((void *)(param_3 + 2), (void *)(param_2 + 8));
            FUN_00537dc0(param_3 + 0x10, (void *)(param_2 + 0x40));
        } while (param_2 != param_1);
    }
    return param_3;
}

// @ 0x0079ab90
void FUN_0079ab90(int param_1, int param_2, int param_3, int param_4)
{
    int iVar1 = 0;
    if (param_1 == 0) {
        iVar1 = FUN_0079a630(param_2, param_3);
    } else if (param_1 == 1) {
        iVar1 = FUN_0079a630(param_2, param_3);
        if ((param_2 == 0) || (param_2 == 1)) {
            *(int *)(iVar1 + 0x1c) = 0;
        } else if (param_2 == 2) {
            *(int *)(iVar1 + 0x28) = 0;
        }
    } else if (param_1 == 2) {
        iVar1 = FUN_0079a5a0(param_2, param_3);
    } else {
        return;
    }
    if (iVar1 != 0) {
        *(int *)(iVar1 + 8) = param_4;
    }
    return;
}

// @ 0x0079ac10
int *FUN_0079ac10(int param_1, int param_2)
{
    int *puVar1 = (int *)FUN_00f473a0(0x28, "Graphics", 0, 0, 0, 0);
    if (puVar1 == 0) {
        return 0;
    }
    puVar1[1] = (int)&V_13ef094;
    puVar1[2] = 0;
    puVar1[0] = (int)&V_140f58c;
    puVar1[1] = (int)&V_140f588;
    puVar1[3] = param_1;
    if (param_1 != 0) {
        *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
    }
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[9] = param_2;
    if (param_2 != 0) {
        *(int *)(param_2 + 4) = *(int *)(param_2 + 4) + 1;
        return puVar1;
    }
    return puVar1;
}

// @ 0x0079ac70
void __fastcall FUN_0079ac70(int *param_1)
{
    FUN_01023030(param_1[6], param_1[7]);
    int iVar2 = param_1[6];
    if ((iVar2 != 0) && (*(int *)(iVar2 - 4) != 0)) {
        FUN_00f47380(iVar2);
    }
    iVar2 = param_1[1];
    if ((iVar2 != 0) && (*(int *)(iVar2 - 4) != 0)) {
        FUN_00f47380(iVar2);
    }
    int *puVar3 = (int *)*param_1;
    if (puVar3 != 0) {
        long *piVar1 = (long *)(puVar3 + 1);
        int iVar4 = (int)*piVar1;
        *piVar1 = *piVar1 + -1;
        if (iVar4 == 1) {
            *piVar1 = 1;
            if (puVar3 != 0) {
                (*(void (__thiscall **)(int *, int)) * puVar3)(puVar3, 1);
            }
        }
    }
    return;
}

// @ 0x0079ae60
int __stdcall FUN_0079ae60(int param_1, void *param_2, int param_3)
{
    int _Dst;
    if (param_1 != 0) {
        _Dst = FUN_00f473a0(param_1 * 2, "Graphics", 0, 0, ALLOC_PATH, 0xd1);
    } else {
        _Dst = 0;
    }
    FUN_011e0744(_Dst, param_2, param_3 - (int)param_2);
    return _Dst;
}

// @ 0x0079aeb0
void __fastcall FUN_0079aeb0(int *param_1)
{
    FUN_01023030(param_1[0x12], param_1[0x13]);
    int iVar2 = param_1[0x12];
    if ((iVar2 != 0) && (*(int *)(iVar2 - 4) != 0)) {
        FUN_00f47380(iVar2);
    }
    FUN_0079ac70(param_1 + 2);
    int *puVar3 = (int *)param_1[1];
    if (puVar3 != 0) {
        long *piVar1 = (long *)(puVar3 + 1);
        int iVar4 = (int)*piVar1;
        *piVar1 = *piVar1 + -1;
        if (iVar4 == 1) {
            *piVar1 = 1;
            if (puVar3 != 0) {
                (*(void (__thiscall **)(int *, int)) * puVar3)(puVar3, 1);
            }
        }
    }
    puVar3 = (int *)*param_1;
    if (puVar3 != 0) {
        long *piVar1 = (long *)(puVar3 + 1);
        int iVar4 = (int)*piVar1;
        *piVar1 = *piVar1 + -1;
        if (iVar4 == 1) {
            *piVar1 = 1;
            if (puVar3 != 0) {
                (*(void (__thiscall **)(int *, int)) * puVar3)(puVar3, 1);
            }
        }
    }
    return;
}

// @ 0x0079af80
void __fastcall FUN_0079af80(int *param_1, unsigned int param_2)
{
    if ((unsigned int)(param_1[2] - *param_1) >> 3 < param_2) {
        int iVar3;
        if (param_2 == 0) iVar3 = 0;
        else iVar3 = FUN_00f473a0(param_2 * 8, "Graphics", 0, 0, ALLOC_PATH, 0xd1);
        int iVar1 = param_1[1];
        int iVar2 = *param_1;
        FUN_007992e0((int *)iVar2, (int *)iVar1, (int *)iVar3);
        FUN_008def80((void *)iVar2, (void *)iVar1, (void *)iVar3);
        iVar1 = *param_1;
        if ((iVar1 != 0) && (*(int *)(iVar1 - 4) != 0)) {
            FUN_00f47380(iVar1);
        }
        iVar1 = *param_1;
        *param_1 = iVar3;
        param_1[1] = iVar3 + ((param_1[1] - iVar1) >> 3) * 8;
        param_1[2] = iVar3 + param_2 * 8;
    }
    return;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
