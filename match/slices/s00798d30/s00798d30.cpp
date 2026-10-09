// Slice s00798d30 -- split-transform / lighting helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE

#include <intrin.h>
#include <math.h>
#define ABS(x) fabs(x)

// ---- neighbours from slices 10-14 / external module state ----
extern int DAT_01634370;
extern int DAT_01634374;
extern int DAT_0163437c;
extern int DAT_01634380;
extern unsigned char DAT_01634384;
extern float DAT_016342f0[16];
extern float DAT_01634330[16];
extern int (*DAT_01634378)(...);

extern void __cdecl FUN_00796910(int *, int *, int, int, float *, char *);
extern void __cdecl FUN_00796ed0();
extern void __cdecl FUN_00797a20(int *, int *, int, int, float *, char *, int, int);

extern float DAT_01634510;
extern float DAT_01634514;
extern float DAT_01634518;
extern int DAT_01634650;

extern int V_13ebc60;
extern int V_140f558;
extern int V_140f560;
extern int V_140f568;
extern int V_140f570;
extern int V_140f578;

extern void __cdecl FUN_00436ce0(...);
extern int __cdecl FUN_00f473a0(...);

struct VObj { virtual void f0(); virtual void f1(int); };
struct Mat3 { void Assign(void *); };
struct Elem { int *p; int *v; };
struct AllocThing { int *alloc(int n, int extra); };
struct Mgr { void Notify(int param); };
struct VCtor { void c0(int *); void c1(int *); void c2(int *); void c3(int *); void c4(int *); };
struct CSplitCtor { int *copy(int *src); };

// @ 0x00798d30
void FUN_00798d30(int param_1, int *param_2)
{
    int iVar1;
    char *puVar2;

    if (param_1 == 0) {
        param_1 = param_2[2];
    }
    puVar2 = (char *)0x0;
    if (DAT_01634384 != 0) {
        puVar2 = (char *)DAT_01634330;
    }
    iVar1 = *param_2;
    if (DAT_01634370 == 0) {
        if (*(int *)(iVar1 + 0x10) == 0x30) {
            FUN_00796ed0();
        } else {
            FUN_00796910((int *)param_2[4], (int *)param_2[3], iVar1, param_1,
                         DAT_016342f0, puVar2);
        }
    } else {
        FUN_00797a20((int *)param_2[4], (int *)param_2[3], iVar1, param_1,
                     DAT_016342f0, puVar2, DAT_01634370, DAT_01634374);
    }
    DAT_01634384 = 0;
    DAT_01634370 = 0;
    DAT_01634374 = 0;
    DAT_0163437c = 0;
    DAT_01634380 = 0;
    DAT_016342f0[0] = 1.0f;
    DAT_016342f0[1] = 0.0f;
    DAT_016342f0[2] = 0.0f;
    DAT_016342f0[3] = 0.0f;
    DAT_016342f0[4] = 0.0f;
    DAT_016342f0[5] = 1.0f;
    DAT_016342f0[6] = 0.0f;
    DAT_016342f0[7] = 0.0f;
    DAT_016342f0[8] = 0.0f;
    DAT_016342f0[9] = 0.0f;
    DAT_016342f0[10] = 1.0f;
    DAT_016342f0[11] = 0.0f;
    DAT_016342f0[12] = 0.0f;
    DAT_016342f0[13] = 0.0f;
    DAT_016342f0[14] = 0.0f;
    DAT_016342f0[15] = 0.0f;
    DAT_01634378 = (int (*)(...)) & V_13ebc60;
    return;
}

// @ 0x00798e40
void FUN_00798e40(int param_1, float param_2, float *param_3, float *param_4, float *param_5)
{
    switch (param_1) {
    case 1:
        *param_5 = (1.0f - param_2) * *param_3 + *param_4 * param_2;
        return;
    case 3:
        if (param_2 > 0.5f) { *param_5 = *param_4; return; }
        *param_5 = *param_3;
        return;
    case 4:
        *param_5 = *param_3;
        return;
    case 5:
        *param_5 = *param_4;
        return;
    }
}

// @ 0x00798ed0
void FUN_00798ed0(int param_1, float param_2, int *param_3, int *param_4, int *param_5)
{
    float fVar1;
    float fVar2;
    int local_8;

    switch (param_1) {
    case 1:
        fVar1 = (float)*param_3;
        if (*param_3 < 0) {
            fVar1 = fVar1 + 4.2949673e+09f;
        }
        fVar2 = (float)*param_4;
        if (*param_4 < 0) {
            fVar2 = fVar2 + 4.2949673e+09f;
        }
        local_8 = (int)(long long)(fVar2 * param_2 + fVar1 * (1.0f - param_2));
        *param_5 = local_8;
        return;
    case 3:
        if (param_2 <= 0.5f) { *param_5 = *param_3; return; }
        *param_5 = *param_4;
        return;
    case 4:
        *param_5 = *param_3;
        return;
    case 5:
        *param_5 = *param_4;
        return;
    }
}

// @ 0x00798fb0
void FUN_00798fb0(int param_1, float param_2, int *param_3, int *param_4, int *param_5)
{
    switch (param_1) {
    case 1:
        *param_5 = (int)((1.0f - param_2) * (float)*param_3 + (float)*param_4 * param_2);
        return;
    case 3:
        if (param_2 > 0.5f) { *param_5 = *param_4; return; }
        *param_5 = *param_3;
        return;
    case 4:
        *param_5 = *param_3;
        return;
    case 5:
        *param_5 = *param_4;
        return;
    }
}

// @ 0x00799050
void FUN_00799050(int param_1, float param_2, int *param_3, int *param_4, int *param_5)
{
    switch (param_1) {
    case 3:
        if (param_2 > 0.5f) { *param_5 = *param_4; return; }
        *param_5 = *param_3;
        return;
    case 4:
        *param_5 = *param_3;
        return;
    case 5:
        *param_5 = *param_4;
        return;
    }
}

// @ 0x00799090
void FUN_00799090(int param_1, float param_2, int *param_3, int *param_4, int *param_5)
{
    switch (param_1) {
    case 3:
        if (param_2 > 0.5f) { *param_5 = *param_4; param_5[1] = param_4[1]; return; }
        *param_5 = *param_3;
        param_5[1] = param_3[1];
        return;
    case 4:
        *param_5 = *param_3;
        param_5[1] = param_3[1];
        return;
    case 5:
        *param_5 = *param_4;
        param_5[1] = param_4[1];
        return;
    }
}

// @ 0x007990e0
void Mgr::Notify(int param)
{
    VObj **puVar1;

    puVar1 = *(VObj ***)((char *)this + 0xc);
    if (puVar1 != *(VObj ***)((char *)this + 0x10)) {
        do {
            (*puVar1)->f1(param);
            puVar1 = puVar1 + 1;
        } while (puVar1 != *(VObj ***)((char *)this + 0x10));
    }
    return;
}

// @ 0x00799110
void FUN_00799110(int param_1, float param_2, float *param_3, float *param_4, float *param_5)
{
    switch (param_1) {
    case 1: {
        float fVar4 = 1.0f - param_2;
        float fVar5 = param_3[1];
        float fVar1 = param_3[2];
        float fVar2 = param_4[1];
        float fVar3 = param_4[2];
        *param_5 = *param_4 * param_2 + *param_3 * fVar4;
        param_5[1] = fVar2 * param_2 + fVar5 * fVar4;
        param_5[2] = fVar3 * param_2 + fVar1 * fVar4;
        return;
    }
    case 2: {
        float fVar5 = 1.0f - param_2;
        float local_18 = *param_4 * param_2 + *param_3 * fVar5;
        float local_14 = param_4[1] * param_2 + param_3[1] * fVar5;
        float local_10 = param_4[2] * param_2 + param_3[2] * fVar5;
        float local_c[3];
        FUN_00436ce0(local_c, &local_18);
        param_4 = local_c;
        break;
    }
    case 3:
        if (param_2 <= 0.5f) {
            *param_5 = *param_3;
            param_5[1] = param_3[1];
            param_5[2] = param_3[2];
            return;
        }
        *param_5 = *param_4;
        param_5[1] = param_4[1];
        param_5[2] = param_4[2];
        return;
    case 4:
        param_4 = param_3;
        break;
    case 5:
        break;
    default:
        return;
    }
    *param_5 = *param_4;
    param_5[1] = param_4[1];
    param_5[2] = param_4[2];
    return;
}

// @ 0x00799290
void FUN_00799290(int **param_1, int *param_2, int *param_3, int *param_4)
{
    int *piVar1;
    int iVar2;

    *param_1 = param_4;
    for (; param_2 != param_3; param_2 = param_2 + 2) {
        piVar1 = *param_1;
        if (piVar1 != (int *)0x0) {
            iVar2 = *param_2;
            *piVar1 = iVar2;
            if (iVar2 != 0) {
                _InterlockedIncrement((volatile long *)(iVar2 + 4));
            }
            piVar1[1] = param_2[1];
        }
        *param_1 = (int *)((char *)*param_1 + 8);
    }
    return;
}

// @ 0x007992e0
void FUN_007992e0(int *param_1, int *param_2, int *param_3)
{
    int iVar1;

    for (; param_1 != param_2; param_1 = param_1 + 2) {
        if (param_3 != (int *)0x0) {
            iVar1 = *param_1;
            *param_3 = iVar1;
            if (iVar1 != 0) {
                _InterlockedIncrement((volatile long *)(iVar1 + 4));
            }
            param_3[1] = param_1[1];
        }
        param_3 = param_3 + 2;
    }
    return;
}

// @ 0x00799320
void FUN_00799320(float *param_1, float *param_2)
{
    float fVar1 = *param_2;
    float fVar2 = param_2[1];
    float fVar5 = 1.0f / sqrtf(((fVar1 * fVar1 + param_2[1] * param_2[1]) + param_2[2] * param_2[2]) +
                               param_2[3] * param_2[3]);
    float fVar3 = param_2[2];
    float fVar4 = param_2[3];
    *param_1 = fVar1 * fVar5;
    param_1[1] = fVar2 * fVar5;
    param_1[2] = fVar5 * fVar3;
    param_1[3] = fVar5 * fVar4;
    return;
}

// @ 0x007993a0  SP::cSplitManager::cSplitInstance::cSplitInstance
int *__fastcall SP_cSplitInstance_ctor(int *this_)
{
    *(char *)this_ = 0;
    *(short *)((char *)this_ + 6) = 0;
    *(short *)((char *)this_ + 4) = 0;
    *(float *)((char *)this_ + 8) = DAT_01634510;
    *(float *)((char *)this_ + 0xc) = DAT_01634514;
    *(float *)((char *)this_ + 0x10) = DAT_01634518;
    *(float *)((char *)this_ + 0x14) = 1.0f;
    ((Mat3 *)((char *)this_ + 0x18))->Assign(&DAT_01634650);
    *(short *)((char *)this_ + 0x3c) = 0;
    *(short *)((char *)this_ + 0x3e) = 0;
    *(float *)((char *)this_ + 0x40) = DAT_01634510;
    *(float *)((char *)this_ + 0x44) = DAT_01634514;
    *(float *)((char *)this_ + 0x48) = DAT_01634518;
    *(float *)((char *)this_ + 0x4c) = 1.0f;
    ((Mat3 *)((char *)this_ + 0x50))->Assign(&DAT_01634650);
    return this_;
}

// @ 0x00799450  SP::cSplitManager::cSplitInstance::cSplitInstance (copy)
int *CSplitCtor::copy(int *param_2)
{
    int *this_ = (int *)this;
    *(char *)this_ = *(char *)param_2;
    *(short *)((char *)this_ + 4) = *(unsigned short *)((char *)param_2 + 4);
    *(short *)((char *)this_ + 6) = *(unsigned short *)((char *)param_2 + 6);
    *(float *)((char *)this_ + 8) = *(float *)((char *)param_2 + 8);
    *(float *)((char *)this_ + 0xc) = *(float *)((char *)param_2 + 0xc);
    *(float *)((char *)this_ + 0x10) = *(float *)((char *)param_2 + 0x10);
    *(float *)((char *)this_ + 0x14) = *(float *)((char *)param_2 + 0x14);
    ((Mat3 *)((char *)this_ + 0x18))->Assign((char *)param_2 + 0x18);
    *(short *)((char *)this_ + 0x3c) = *(unsigned short *)((char *)param_2 + 0x3c);
    *(short *)((char *)this_ + 0x3e) = *(unsigned short *)((char *)param_2 + 0x3e);
    *(float *)((char *)this_ + 0x40) = *(float *)((char *)param_2 + 0x40);
    *(float *)((char *)this_ + 0x44) = *(float *)((char *)param_2 + 0x44);
    *(float *)((char *)this_ + 0x48) = *(float *)((char *)param_2 + 0x48);
    *(float *)((char *)this_ + 0x4c) = *(float *)((char *)param_2 + 0x4c);
    ((Mat3 *)((char *)this_ + 0x50))->Assign((char *)param_2 + 0x50);
    return this_;
}

// @ 0x007994d0
void FUN_007994d0(int param_1, float param_2, float *param_3, float *param_4, float *param_5)
{
    switch (param_1) {
    case 1:
        *param_5 = *param_4 * param_2 + *param_3 * (1.0f - param_2);
        param_5[1] = param_4[1] * param_2 + param_3[1] * (1.0f - param_2);
        return;
    case 2: {
        float fVar1 = *param_4 * param_2 + *param_3 * (1.0f - param_2);
        float fVar2 = param_4[1] * param_2 + param_3[1] * (1.0f - param_2);
        float fVar3 = 1.0f / sqrtf(fVar1 * fVar1 + fVar2 * fVar2);
        *param_5 = fVar3 * fVar1;
        param_5[1] = fVar3 * fVar2;
        return;
    }
    case 3:
        if (param_2 <= 0.5f) { *param_5 = *param_3; param_5[1] = param_3[1]; return; }
        break;
    case 4:
        *param_5 = *param_3;
        param_5[1] = param_3[1];
        return;
    case 5:
        break;
    default:
        return;
    }
    *param_5 = *param_4;
    param_5[1] = param_4[1];
    return;
}

// @ 0x00799640
void FUN_00799640(int param_1, float param_2, float *param_3, float *param_4, float *param_5)
{
    switch (param_1) {
    case 1: {
        float fVar7 = param_3[1];
        float fVar1 = param_3[2];
        float fVar2 = param_3[3];
        float fVar3 = param_4[2];
        float fVar4 = param_4[3];
        float fVar6 = 1.0f - param_2;
        float fVar5 = param_4[1];
        *param_5 = *param_4 * param_2 + *param_3 * fVar6;
        param_5[1] = fVar5 * param_2 + fVar7 * fVar6;
        param_5[2] = fVar3 * param_2 + fVar1 * fVar6;
        param_5[3] = fVar4 * param_2 + fVar2 * fVar6;
        return;
    }
    case 2: {
        float fVar7 = 1.0f - param_2;
        float local_14 = param_4[3] * param_2 + param_3[3] * fVar7;
        float local_20 = *param_4 * param_2 + *param_3 * fVar7;
        float local_1c = param_4[1] * param_2 + param_3[1] * fVar7;
        float local_18 = param_4[2] * param_2 + param_3[2] * fVar7;
        float local_10[4];
        FUN_00799320(local_10, &local_20);
        param_3 = local_10;
        break;
    }
    case 3:
        if (0.5f < param_2) { param_3 = param_4; }
        break;
    case 4:
        break;
    case 5:
        param_3 = param_4;
        break;
    default:
        return;
    }
    *param_5 = *param_3;
    param_5[1] = param_3[1];
    param_5[2] = param_3[2];
    param_5[3] = param_3[3];
    return;
}

// @ 0x007997f0
void VCtor::c0(int *param_2)
{
    int *param_1 = (int *)this;
    param_1[0] = (int)&V_13ebc60;
    param_1[1] = 0;
    param_1[2] = 4;
    *(float *)(param_1 + 3) = *(float *)param_2;
    *(float *)(param_1 + 4) = *(float *)(param_2 + 1);
    *(float *)(param_1 + 5) = *(float *)(param_2 + 2);
    *(float *)(param_1 + 6) = *(float *)(param_2 + 3);
    param_1[0] = (int)&V_140f558;
    param_1[7] = 1;
    return;
}

// @ 0x00799840
int *AllocThing::alloc(int param_2, int param_3)
{
    int *param_1 = (int *)this;
    int iVar1;
    (void)param_3;
    if (param_2 != 0) {
        iVar1 = FUN_00f473a0(param_2 * 2, "Graphics", 0, 0,
                             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                             0xd1);
        param_1[0] = iVar1;
        param_1[1] = iVar1;
        param_1[2] = iVar1 + param_2 * 2;
        return param_1;
    }
    param_1[0] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    return param_1;
}

// @ 0x007998a0
long double __fastcall FUN_007998a0(float *param_1, float *param_2, float *param_3)
{
    return ((long double)param_1[3] -
            ((long double)*param_1 * (long double)*param_2 +
            ((long double)param_1[1] * (long double)param_2[1] + (long double)param_1[2] * (long double)param_2[2]))) /
            ((long double)param_1[2] * (long double)(param_3[2] - param_2[2]) +
            ((long double)param_1[1] * (long double)(param_3[1] - param_2[1]) +
            (long double)*param_1 * (long double)(*param_3 - *param_2)));
}

// @ 0x00799940
void VCtor::c1(int *param_2)
{
    int *param_1 = (int *)this;
    param_1[0] = (int)&V_13ebc60;
    param_1[1] = 0;
    param_1[2] = 4;
    *(float *)(param_1 + 3) = *(float *)param_2;
    *(float *)(param_1 + 4) = *(float *)(param_2 + 1);
    *(float *)(param_1 + 5) = *(float *)(param_2 + 2);
    *(float *)(param_1 + 6) = *(float *)(param_2 + 3);
    *(float *)(param_1 + 7) = *(float *)(param_2 + 4);
    *(float *)(param_1 + 8) = *(float *)(param_2 + 5);
    *(float *)(param_1 + 9) = *(float *)(param_2 + 6);
    param_1[0] = (int)&V_140f560;
    param_1[10] = 1;
    return;
}

// @ 0x007999a0
long double __fastcall FUN_007999a0(float *param_1, float *param_2, float *param_3)
{
    float fVar7 = *param_2 - *param_1;
    float fVar9 = param_2[2] - param_1[2];
    float fVar10 = *param_3 - *param_1;
    float fVar8 = param_2[1] - param_1[1];
    float fVar11 = param_3[1] - param_1[1];
    float fVar12 = param_3[2] - param_1[2];
    float fVar5 = (param_1[5] * fVar9 + param_1[4] * fVar8) + param_1[3] * fVar7;
    float fVar6 = (param_1[5] * fVar12 + param_1[4] * fVar11) + param_1[3] * fVar10;
    float fVar1 = (fVar9 - param_1[5] * fVar5);
    float fVar2 = (fVar8 - param_1[4] * fVar5);
    float fVar3 = (fVar7 - param_1[3] * fVar5);
    double dVar1 = ABS(sqrt((double)(fVar3 * fVar3 + (fVar2 * fVar2 + fVar1 * fVar1))) -
                       sqrt((double)param_1[6]));
    float fVar4 = (fVar12 - param_1[5] * fVar6);
    float fVar13 = (fVar11 - param_1[4] * fVar6);
    float fVar14 = (fVar10 - fVar6 * param_1[3]);
    return (long double)dVar1 /
           (ABS(sqrt((double)(fVar4 * fVar4 + (fVar13 * fVar13 + fVar14 * fVar14))) -
                sqrt((double)param_1[6])) + (double)dVar1);
}

// @ 0x00799b00
void VCtor::c2(int *param_2)
{
    int *param_1 = (int *)this;
    param_1[0] = (int)&V_13ebc60;
    param_1[1] = 0;
    param_1[2] = 4;
    *(float *)(param_1 + 3) = *(float *)param_2;
    *(float *)(param_1 + 4) = *(float *)(param_2 + 1);
    *(float *)(param_1 + 5) = *(float *)(param_2 + 2);
    *(float *)(param_1 + 6) = *(float *)(param_2 + 3);
    param_1[0] = (int)&V_140f568;
    param_1[7] = 1;
    return;
}

// @ 0x00799b50
long double __fastcall FUN_00799b50(float *param_1, float *param_2, float *param_3)
{
    float fVar11 = param_3[2] - param_2[2];
    float fVar9 = *param_3 - *param_2;
    float fVar10 = param_3[1] - param_2[1];
    float fVar6 = param_2[2] - param_1[2];
    float fVar7 = *param_2 - *param_1;
    float fVar8 = param_2[1] - param_1[1];
    long double fVar5 = (long double)1 / sqrt((long double)((long double)fVar10 * fVar10 +
                          ((long double)fVar9 * fVar9 + (long double)fVar11 * fVar11)));
    long double fVar1 = (long double)(((fVar6 * fVar11 + fVar7 * fVar9) + fVar8 * fVar10) * (float)fVar5);
    return (-fVar1 - sqrt(fVar1 * fVar1 -
                         (((long double)fVar7 * fVar7 + ((long double)fVar8 * fVar8 +
                         (long double)fVar6 * fVar6)) - (long double)param_1[3]))) * fVar5;
}

// @ 0x00799c30
void VCtor::c3(int *param_2)
{
    int *param_1 = (int *)this;
    param_1[0] = (int)&V_13ebc60;
    param_1[1] = 0;
    param_1[2] = 4;
    *(float *)(param_1 + 3) = *(float *)param_2;
    *(float *)(param_1 + 4) = *(float *)(param_2 + 1);
    *(float *)(param_1 + 5) = *(float *)(param_2 + 2);
    *(float *)(param_1 + 6) = *(float *)(param_2 + 3);
    param_1[0] = (int)&V_140f570;
    return;
}

// @ 0x00799c70
void VCtor::c4(int *param_2)
{
    int *param_1 = (int *)this;
    param_1[0] = (int)&V_13ebc60;
    param_1[1] = 0;
    param_1[2] = 4;
    *(float *)(param_1 + 3) = *(float *)param_2;
    *(float *)(param_1 + 4) = *(float *)(param_2 + 1);
    *(float *)(param_1 + 5) = *(float *)(param_2 + 2);
    *(float *)(param_1 + 6) = *(float *)(param_2 + 3);
    *(float *)(param_1 + 7) = *(float *)(param_2 + 4);
    *(float *)(param_1 + 8) = *(float *)(param_2 + 5);
    *(float *)(param_1 + 9) = *(float *)(param_2 + 6);
    param_1[0] = (int)&V_140f578;
    return;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct Mat3 {
    void Assign(void*); // 0x0041cb40
};
}
