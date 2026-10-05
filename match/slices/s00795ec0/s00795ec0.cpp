// Slice s00795ec0 -- Spherical-harmonics ambient lighting module.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE

#include <math.h>

// ---- external module state / helpers (real addresses; relocations masked) ----
int DAT_01634370;
int DAT_01634374;
int DAT_01634378;
int DAT_0163437c;
int DAT_01634380;

extern float DAT_016342f0[16];
extern float DAT_01634330[16];
extern unsigned char DAT_01634384;

extern const float DAT_016340e0;
extern const float DAT_016341d8;
extern const float DAT_01634068;
extern const float DAT_01634108;
extern const float DAT_0153ae10;
extern const float DAT_0140ebdc;
extern const float DAT_0140ebd8;
extern const float DAT_0140ebd4;
extern const float DAT_0140ebd0;
extern const float DAT_0140ebcc;
extern const float DAT_0140ebc8;
extern const float DAT_0140ebc4;

extern int DAT_0140eae8[];
extern unsigned char DAT_0140eac4;
extern unsigned char DAT_0140eac5;
extern unsigned char DAT_0140eac6;

extern void *operator_new__(void *, int, unsigned int);
extern float __cdecl AddColourSample(float *, int, float *, int);
extern void __cdecl RotateZHToSHAddT(float *, int, float *, int);
extern void __cdecl CalcHGPhaseZH(float, void *, int, void *);
extern void __cdecl CalcHGPhaseZHAdd(float, void *, int, void *);
extern void __cdecl MultiplyZH(int, void *, void *, int, void *);
extern char _kBasisTriples3[];
extern char _kBasisTriples4[];
extern char _kBasisTriples5[];

struct StubHandle {
    int __thiscall Method(int *);
};

// @ 0x00795ec0  SP::FindSHCoeffsFromHDRCubeMap
void FUN_00795ec0(int param_1, int param_2, int param_3)
{
    int iVar6;
    unsigned int uVar8;
    int iVar7;
    int iVar1;
    int local_80;
    int local_70;
    unsigned int local_68;
    int *local_84;
    unsigned short *local_7c;
    float local_4c[4];
    float fStack_3c;
    float fStack_38;
    int uStack_34;
    float local_30;
    float fStack_2c;
    float fStack_28;
    int uStack_24;
    float local_20;
    float fStack_1c;
    float fStack_18;
    float fStack_14;

    iVar6 = *(int *)(param_1 + 0x1c);
    uVar8 = (int)(iVar6 + (iVar6 >> 0x1f & 3U)) >> 2;
    if ((((uVar8 & uVar8 - 1) == 0) && (uVar8 * 4 - iVar6 == 0)) &&
        (uVar8 * 3 == *(int *)(param_1 + 0x20))) {
        iVar7 = *(int *)(param_1 + 0x28);
        uStack_34 = 0;
        local_68 = 0;
        local_84 = DAT_0140eae8;
        do {
            local_7c = (unsigned short *)(iVar7 + (local_84[1] * iVar6 * 3 + *local_84 * 3) * uVar8 * 2);
            local_80 = 0;
            if (0 < (int)uVar8) {
                iVar1 = ((int)local_68 >> 1) * 4;
                do {
                    local_70 = 0;
                    float fVar14 = (float)(1.0 - (((double)local_80 + 0.5) * 2.0) / (double)(int)uVar8);
                    float fVar2 = fVar14;
                    unsigned short *puVar9 = local_7c;
                    do {
                        double fVar13 = (((double)local_70 + 0.5) * 2.0) / (double)(int)uVar8 - 1.0;
                        double fVar15 = (double)(float)local_84[2] * fVar13 + (double)(float)local_84[3] * (double)fVar14;
                        fStack_38 = (float)((6.103609e-05 / ((float)(int)uVar8 * (float)(int)uVar8)) /
                                            (((float)fVar13 * (float)fVar13 + fVar2 * fVar2) + 1.0f));
                        local_4c[3] = (float)*puVar9 * fStack_38;
                        fVar14 = (float)((double)(float)local_84[5] * (double)fVar14 + (double)(float)local_84[4] * fVar13);
                        fStack_3c = (float)puVar9[1] * fStack_38;
                        fStack_38 = (float)puVar9[2] * fStack_38;
                        uStack_24 = uStack_34;
                        float fVar3 = (float)(1.0 / sqrt(((double)fVar14 * (double)fVar14 + fVar15 * fVar15) + 1.0));
                        float fVar16 = fVar3;
                        if ((local_68 & 1) != 0) {
                            fVar16 = -fVar3;
                        }
                        unsigned char bVar4 = (&DAT_0140eac5)[iVar1];
                        unsigned char bVar5 = (&DAT_0140eac6)[iVar1];
                        local_30 = local_4c[3];
                        fStack_2c = fStack_3c;
                        fStack_28 = fStack_38;
                        local_20 = fStack_38;
                        fStack_1c = fStack_38;
                        fStack_18 = fStack_38;
                        fStack_14 = fStack_38;
                        local_4c[(unsigned char)(&DAT_0140eac4)[iVar1]] = fVar16 * (float)fVar15;
                        local_4c[bVar4] = fVar3 * (float)fVar14;
                        local_4c[bVar5] = fVar16;
                        AddColourSample(local_4c + 3, param_2, local_4c, param_3);
                        local_70 = local_70 + 1;
                        puVar9 = puVar9 + 3;
                    } while (local_70 < (int)uVar8);
                    local_7c = local_7c + iVar6 * 3;
                    local_80 = local_80 + 1;
                } while (local_80 < (int)uVar8);
            }
            local_84 = local_84 + 6;
            local_68 = local_68 + 1;
        } while ((int)local_84 < (int)0x140eb78);
    }
    return;
}

// @ 0x007961d0  SP::AddSphereLighting
void AddSphereLighting(float param_1, float param_2, float param_3, float param_4,
                       int param_5, int param_6, int param_7)
{
    float *pfVar1;
    float fVar2, fVar3, fVar4, fVar5, fVar6, fVar7, fVar8;
    float local_8c, local_88, local_84, local_80, fStack_7c, fStack_78, fStack_74;
    float local_70, fStack_6c, fStack_68, fStack_64;
    float local_60, fStack_5c, fStack_58, fStack_54;
    float local_50, fStack_4c, fStack_48, fStack_44;
    float local_40, fStack_3c, fStack_38, fStack_34;
    float local_30, fStack_2c, fStack_28, fStack_24;
    float local_20, fStack_1c, fStack_18, fStack_14;

    if (0 < param_5) {
        fVar4 = DAT_016340e0 * DAT_0153ae10;
        fVar5 = DAT_016341d8 * DAT_0153ae10;
        fVar8 = DAT_01634068 * DAT_0153ae10;
        fVar6 = DAT_01634108 * DAT_0153ae10;
        local_70 = param_4;
        fStack_6c = param_4;
        fStack_68 = param_4;
        fStack_64 = param_4;
        pfVar1 = (float *)(param_6 + 0x18);
        do {
            local_88 = pfVar1[-1] - param_2;
            local_84 = *pfVar1 - param_3;
            fVar7 = pfVar1[-2] - param_1;
            fVar2 = (local_84 * local_84 + local_88 * local_88) + fVar7 * fVar7;
            fStack_74 = pfVar1[-3];
            local_80 = fStack_74 * local_70;
            fStack_7c = fStack_74 * fStack_6c;
            fStack_78 = fStack_74 * fStack_68;
            fStack_74 = fStack_74 * fStack_64;
            local_60 = pfVar1[-2];
            fStack_5c = pfVar1[-1];
            fStack_58 = *pfVar1;
            fStack_54 = pfVar1[1];
            fVar3 = fVar2 / (fStack_54 * fStack_54 + fVar2);
            local_8c = 1.0f / (sqrtf(fVar2) + 1e-06f);
            local_84 = local_84 * local_8c;
            local_88 = local_88 * local_8c;
            local_8c = local_8c * fVar7;
            fStack_44 = ((1.0f - sqrtf(fVar3)) * (fVar4 * 2.0f)) * local_80;
            local_20 = pfVar1[-6];
            fStack_1c = pfVar1[-5];
            fStack_18 = pfVar1[-4];
            fVar2 = pfVar1[-3];
            local_50 = fStack_44 * local_20;
            fStack_4c = fStack_44 * fStack_1c;
            fStack_48 = fStack_44 * fStack_18;
            fStack_44 = fStack_44 * fVar2;
            fStack_34 = (((1.0f - fVar3) * (fVar8 * 2.0f)) * local_80) * 0.5f;
            local_40 = fStack_34 * local_20;
            fStack_3c = fStack_34 * fStack_1c;
            fStack_38 = fStack_34 * fStack_18;
            fStack_34 = fStack_34 * fVar2;
            fStack_24 = (((fVar5 * 2.0f) * (1.0f - fVar3)) * local_80) * sqrtf(fVar3);
            local_30 = fStack_24 * local_20;
            fStack_2c = fStack_24 * fStack_1c;
            fStack_28 = fStack_24 * fStack_18;
            fStack_24 = fStack_24 * fVar2;
            fStack_14 = ((((6.0f - fVar3 * 5.0f) * fVar3 - 1.0f) * (fVar6 * 2.0f)) * local_80) * 0.25f;
            local_20 = fStack_14 * local_20;
            fStack_1c = fStack_14 * fStack_1c;
            fStack_18 = fStack_14 * fStack_18;
            fStack_14 = fStack_14 * fVar2;
            RotateZHToSHAddT(&local_8c, 4, &local_50, param_7);
            pfVar1 = pfVar1 + 8;
            param_5 = param_5 + -1;
        } while (param_5 != 0);
    }
    return;
}

// @ 0x00796420  SP::CalcAtmosphereZH
void CalcAtmosphereZH(int param_1, int *param_2, int param_3, int param_4)
{
    float local_a0[8];
    unsigned char local_80[124];

    if (0 < param_1) {
        local_a0[0] = *(float *)param_2;
        local_a0[1] = *(float *)(param_2 + 1);
        local_a0[2] = *(float *)(param_2 + 2);
        local_a0[3] = *(float *)(param_2 + 3);
        CalcHGPhaseZH(*(float *)(param_2 + 3), local_a0, 7, local_80);
    }
    if (1 < param_1) {
        param_2 = param_2 + 7;
        param_1 = param_1 + -1;
        do {
            local_a0[3] = *(float *)param_2;
            local_a0[0] = *(float *)(param_2 - 3);
            local_a0[1] = *(float *)(param_2 - 2);
            local_a0[2] = *(float *)(param_2 - 1);
            CalcHGPhaseZHAdd(*(float *)param_2, local_a0, 7, local_80);
            param_2 = param_2 + 4;
            param_1 = param_1 + -1;
        } while (param_1 != 0);
    }
    local_a0[0] = DAT_0140ebdc;
    local_a0[1] = DAT_0140ebd8;
    local_a0[2] = DAT_0140ebd4;
    local_a0[3] = DAT_0140ebd0;
    local_a0[4] = DAT_0140ebcc;
    local_a0[5] = DAT_0140ebc8;
    local_a0[6] = DAT_0140ebc4;
    if (param_3 == 3) {
        MultiplyZH(3, local_a0, local_80, param_4, _kBasisTriples3);
    } else if (param_3 == 4) {
        MultiplyZH(4, local_a0, local_80, param_4, _kBasisTriples4);
    } else if (param_3 == 5) {
        MultiplyZH(5, local_a0, local_80, param_4, _kBasisTriples5);
    }
    return;
}

// @ 0x007965c0
void __fastcall FUN_007965c0(int *param_1)
{
    float *p = (float *)param_1;
    int i;
    for (i = 0; i < 32; ++i) {
        p[i] = 0.0f;
    }
    p[0] = 1.0f;
    p[5] = 1.0f;
    p[10] = 1.0f;
    p[16] = 1.0f;
    p[21] = 1.0f;
    p[26] = 1.0f;
    param_1[0x20] = 0;
    param_1[0x21] = 0;
    param_1[0x22] = 0xc2e4e0;
    param_1[0x23] = 0;
    param_1[0x24] = 0;
    *(char *)(param_1 + 0x25) = 0;
}

// @ 0x00796650
void FUN_00796650(StubHandle *param_1)
{
    if (param_1 != 0) {
        DAT_01634370 = param_1->Method(&DAT_01634374);
        return;
    }
    DAT_01634370 = 0;
    return;
}

// @ 0x00796680
void FUN_00796680(int param_1, int param_2, int param_3)
{
    DAT_01634378 = param_1;
    DAT_0163437c = param_2;
    DAT_01634380 = param_3;
    return;
}

// @ 0x007966a0
void __fastcall FUN_007966a0(int param_1)
{
    float *pDst;
    int iVar1;

    iVar1 = *(int *)(*(int *)(param_1 + 0xc) + 0xc);
    pDst = *(float **)(*(int *)(param_1 + 8));
    operator_new__(pDst, 0, iVar1 * 0x30);
    if (0 < iVar1) {
        do {
            pDst[0] = 1.0f;
            pDst[5] = 1.0f;
            pDst[10] = 1.0f;
            pDst = pDst + 12;
            iVar1 = iVar1 - 1;
        } while (iVar1 != 0);
    }
    return;
}

// @ 0x007966f0
void FUN_007966f0(int param_1)
{
    float s = *(float *)(param_1 + 0x10);
    float *m = (float *)param_1;
    DAT_016342f0[0] = m[5] * s;
    DAT_016342f0[4] = m[8] * s;
    DAT_016342f0[8] = m[11] * s;
    DAT_016342f0[1] = m[6] * s;
    DAT_016342f0[2] = m[7] * s;
    DAT_016342f0[3] = DAT_016342f0[0];
    DAT_016342f0[5] = m[9] * s;
    DAT_016342f0[6] = m[10] * s;
    DAT_016342f0[7] = DAT_016342f0[4];
    DAT_016342f0[9] = m[12] * s;
    DAT_016342f0[10] = m[13] * s;
    DAT_016342f0[11] = DAT_016342f0[8];
    DAT_016342f0[12] = m[1];
    DAT_016342f0[13] = m[2];
    DAT_016342f0[14] = m[3];
    DAT_016342f0[15] = m[1];
    return;
}

// @ 0x00796800
void FUN_00796800(int param_1)
{
    float s = *(float *)(param_1 + 0x10);
    float *m = (float *)param_1;
    DAT_01634330[0] = m[5] * s;
    DAT_01634330[4] = m[8] * s;
    DAT_01634330[8] = m[11] * s;
    DAT_01634330[1] = m[6] * s;
    DAT_01634330[2] = m[7] * s;
    DAT_01634330[3] = DAT_01634330[0];
    DAT_01634384 = 1;
    DAT_01634330[5] = m[9] * s;
    DAT_01634330[6] = m[10] * s;
    DAT_01634330[7] = DAT_01634330[4];
    DAT_01634330[9] = m[12] * s;
    DAT_01634330[10] = m[13] * s;
    DAT_01634330[11] = DAT_01634330[8];
    DAT_01634330[12] = m[1];
    DAT_01634330[13] = m[2];
    DAT_01634330[14] = m[3];
    DAT_01634330[15] = m[1];
    return;
}

// @ 0x00796910 -- SP::RotateZHToSHAdd<Vector4,Vector4> is at 0x785500 (not this slice);
// placeholder extern kept here for the AddSphereLighting call above.
