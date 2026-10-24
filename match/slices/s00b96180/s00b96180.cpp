// s00b96180: 19 functions, 0x00b96180..0x00b97240, EASTL rbtree/vector + mission-setup helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-   (no /EHsc)
#include "types.h"
#include <string.h>
#include <math.h>

#pragma warning(disable: 4100)

typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned int undefined4;

#define ROUND(x) ((int)((x) + 0.5f))

// ---- external helpers -------------------------------------------------------
int  operator_new(int size, const char* n, int a, int b, const char* path, int line);
void operator_delete__(void*);
void RBTreeInsert(void* node, void* parent, void* header, unsigned isLeft);
int FUN_00b95340(int a, int b, void* c, undefined4 d);
int FUN_00b952e0(int a, int b, void* c, undefined4 d);
void FUN_00b3f260(int* out, int a, int b, int c, int d);
void FUN_00ac4470(int a, int b, int c);
void FUN_00ac4360(int a, int b, int c);
int  FUN_00ac2130(int a, int b, int c);
void* VectorInsert(void* dst, void* src, unsigned n);
void FUN_00edba80(void* a, int b, int c);
void* FUN_00c7ea30(int a, void* b, int c);
void DoNukeSubtree(void* node);
void cArithmeticaProgram_ctor(void* p);
void LoadArithmeticaFile(unsigned a, unsigned b, void* p);
float FUN_00b7ec50();
void FUN_007f25c0(const char* name, float v);
void FUN_007f2500();
float FUN_007f2590(const char* name);
void FUN_007f1d90();
void* FUN_00401090();
int  cTribeData_ctor(void* p, int a, int b);
void FUN_00b8ef00(int a);
unsigned RandomUint32Uniform(void* rng, unsigned n);
int  FUN_00ff34c0(float f);
int  FUN_00ff1cb0();
int  FUN_00bef920(unsigned a);
void FUN_00bfc460(int a);
int  FUN_00bebc90(int a, unsigned b);
void FUN_00ff0380(int a);
void FUN_00ff2c70(void* p);
void FUN_00b8eec0(void* p);
void FUN_00b8d920(int a);
char FUN_00c6fe50(int a);
int  FUN_00b8d8f0(int a);
void FUN_00b3d2a0(int a);
void FUN_00ba6d80(int a);
char FUN_00bb9af0(int a);
int  FUN_00ff3440();
void* BioProtectorSort_op();
int  cGameNounManager_GetAvatar(void* mgr);
void rw_SList_SetElementSize(void* list, int a);
int  FUN_00ba9370(int a);
void FUN_00c352f0(void* p);
void FUN_00ff3190(void* p);
void VideoEncoder_Jpeg_SetWidth(void* p, int w);
int  FUN_00885c90();
int* FUN_00c71000();
int  FUN_00c71030(int i);
int  FUN_00ff0df0(void* g, int a, int b);
void FUN_00ff2d20(int a);
void FUN_00b96560(void* p);

struct VideoEncoder_Jpeg { char pad0[0x18]; float mFramesPerSecond; };

extern int   DAT_01688888;
extern int   DAT_01688884;
extern float DAT_01688880;
extern float DAT_0168887c;
extern char  DAT_01688890;
extern char  _sMathRandom_SP__3VRandomLinearCongruential_Random_EA__A;

extern const char kAllocFile[];

// @ 0x00b96180
struct S96180 { void fn(int* param_2, int* param_3); };
void S96180::fn(int* param_2, int* param_3)
{
    int param_1 = (int)this;
    undefined4* puVar3 = (undefined4*)(param_1 + 4);
    if (*(undefined4**)(param_1 + 0xc) != 0) {
        undefined4* puVar1 = *(undefined4**)(param_1 + 0xc);
        do {
            puVar3 = puVar1;
            if (*param_3 < (int)puVar3[4])
                puVar1 = (undefined4*)puVar3[1];
            else
                puVar1 = (undefined4*)*puVar3;
        } while (puVar1 != 0);
    }
    undefined4 uVar4;
    if ((puVar3 == (undefined4*)(param_1 + 4)) || (*param_3 < (int)puVar3[4]))
        uVar4 = 0;
    else
        uVar4 = 1;
    int iVar2 = operator_new(0x18, "Simulator", 0, 0, kAllocFile, 0xd1);
    if ((int*)(iVar2 + 0x10) != 0) {
        *(int*)(iVar2 + 0x10) = *param_3;
        *(int*)(iVar2 + 0x14) = param_3[1];
    }
    RBTreeInsert((void*)iVar2, puVar3, (void*)(param_1 + 4), uVar4);
    *(int*)(param_1 + 0x14) = *(int*)(param_1 + 0x14) + 1;
    *param_2 = iVar2;
}

// @ 0x00b96220
int* FUN_00b96220(int* param_1, int param_2, int param_3, uint* param_4, undefined4 param_5)
{
    int iVar3 = param_3 - param_2 >> 4;
    int iVar5;
    int iVar2;
    if (0 < iVar3) {
        uint uVar4 = *param_4;
        do {
            iVar2 = iVar3 >> 1;
            uint uVar1 = *(uint*)(iVar2 * 0x10 + param_2);
            iVar5 = iVar2 * 0x10 + param_2;
            if ((uVar1 < uVar4) ||
                ((uVar1 <= uVar4 && (uVar4 = *param_4, *(uint*)(iVar5 + 4) < param_4[1])))) {
                param_2 = iVar5 + 0x10;
                iVar2 = iVar3 + (-1 - iVar2);
                iVar5 = param_3;
            } else if ((uVar1 <= uVar4) && (*(uint*)(iVar5 + 4) <= param_4[1])) {
                int p = FUN_00b95340(iVar5 + 0x10, param_3, param_4, param_5);
                iVar5 = FUN_00b952e0(param_2, iVar5, param_4, param_5);
                *param_1 = iVar5;
                param_1[1] = p;
                return param_1;
            }
            param_3 = iVar5;
            iVar3 = iVar2;
        } while (0 < iVar2);
    }
    *param_1 = param_2;
    param_1[1] = param_2;
    return param_1;
}

// @ 0x00b96360
struct S96360 { void fn(int param_2, int param_3, int param_4, int allocator); };
void S96360::fn(int param_2, int param_3, int param_4, int allocator)
{
    int* param_1 = (int*)this;
    int local_4;
    if (param_3 != param_4) {
        int iVar3 = param_1[1];
        uint uVar2 = (param_4 - param_3) / 0x3c;
        if (uVar2 <= (uint)((param_1[2] - iVar3) / 0x3c)) {
            int iVar1 = param_1[1];
            uint uVar5 = (iVar3 - param_2) / 0x3c;
            if (uVar2 < uVar5) {
                int iVar6 = iVar1 + uVar2 * -0x3c;
                FUN_00b3f260(&local_4, iVar6, iVar1, iVar1, param_3);
                iVar3 = param_2;
                param_1[1] = param_1[1] + uVar2 * 0x3c;
                FUN_00ac4470(param_2, iVar6, iVar1);
                FUN_00ac4360(param_3, param_4, iVar3);
                return;
            }
            iVar3 = uVar5 * 0x3c;
            local_4 = iVar3 + param_3;
            FUN_00b3f260(&param_4, local_4, param_4, iVar1, param_3);
            int iVar6 = param_2;
            param_1[1] = param_1[1] + (uVar2 - uVar5) * 0x3c;
            FUN_00b3f260(&param_2, param_2, iVar1, param_1[1], param_3);
            param_1[1] = param_1[1] + iVar3;
            FUN_00ac4470(param_3, local_4, iVar3 + iVar6);
            return;
        }
        iVar3 = (iVar3 - *param_1) / 0x3c;
        uint uVar5 = iVar3 * 2;
        if (iVar3 == 0)
            uVar5 = 1;
        if (uVar5 <= uVar2 + iVar3)
            uVar5 = uVar2 + iVar3;
        if (uVar5 == 0)
            iVar3 = 0;
        else
            iVar3 = operator_new(uVar5 * 0x3c, "Simulator", 0, 0, kAllocFile, 0xd1);
        int iVar1 = param_2;
        undefined4 uVar4 = FUN_00ac2130(*param_1, param_2, iVar3);
        FUN_00b3f260(&param_3, param_3, param_4, uVar4, param_3);
        int iVar6 = FUN_00ac2130(iVar1, param_1[1], param_3);
        iVar1 = *param_1;
        if ((iVar1 != 0) && (*(int*)(iVar1 + -4) != 0))
            operator_delete__((void*)iVar1);
        *param_1 = iVar3;
        param_1[1] = iVar6;
        param_1[2] = iVar3 + uVar5 * 0x3c;
    }
}

// @ 0x00b965d0
struct S965d0 { unsigned fn(unsigned param_2, unsigned param_3); };
unsigned S965d0::fn(unsigned param_2, unsigned param_3)
{
    undefined4* param_1 = (undefined4*)this;
    FUN_00b96220((int*)param_2, *param_1, param_1[1], (uint*)param_3, *(undefined1*)(param_1 + 5));
    return param_2;
}

// @ 0x00b96600
struct S96600 { void fn(undefined4* param_2, undefined4* param_3); };
void S96600::fn(undefined4* param_2, undefined4* param_3)
{
    int* param_1 = (int*)this;
    undefined4* puVar1 = (undefined4*)param_1[1];
    int local_4;
    if (puVar1 != (undefined4*)param_1[2]) {
        if ((param_2 <= param_3) && (param_3 < puVar1))
            param_3 = param_3 + 1;
        if (puVar1 != 0)
            *puVar1 = puVar1[-1];
        size_t sVar4 = (size_t)((param_1[1] + -4) - (int)param_2);
        memmove((void*)(param_1[1] + ((int)sVar4 >> 2) * -4), param_2, sVar4);
        *param_2 = *param_3;
        param_1[1] = param_1[1] + 4;
        return;
    }
    local_4 = (int)puVar1 - *param_1 >> 2;
    void* _Dst;
    if (local_4 == 0) {
        local_4 = 1;
    } else {
        local_4 = local_4 * 2;
        if (local_4 == 0) {
            _Dst = 0;
            goto LAB_00b966a0;
        }
    }
    _Dst = (void*)operator_new(local_4 * 4, "Simulator", 0, 0, kAllocFile, 0xd1);
LAB_00b966a0:
    size_t sVar4 = (size_t)((int)param_2 - *param_1);
    void* pvVar5 = VectorInsert(_Dst, (void*)*param_1, (unsigned)sVar4);
    puVar1 = (undefined4*)((int)pvVar5 + ((int)sVar4 >> 2) * 4);
    if (puVar1 != 0)
        *puVar1 = *param_3;
    int iVar2 = param_1[1];
    pvVar5 = VectorInsert(puVar1 + 1, param_2, (unsigned)(iVar2 - (int)param_2));
    int iVar3 = *param_1;
    if ((iVar3 != 0) && (*(int*)(iVar3 + -4) != 0))
        operator_delete__((void*)iVar3);
    *param_1 = (int)_Dst;
    param_1[1] = (int)((int)pvVar5 + (iVar2 - (int)param_2 >> 2) * 4);
    param_1[2] = (int)((int)_Dst + local_4 * 4);
}

// @ 0x00b96710
struct S96710 { void fn(undefined4* param_2, undefined4* param_3); };
void S96710::fn(undefined4* param_2, undefined4* param_3)
{
    int* param_1 = (int*)this;
    undefined4* puVar3 = (undefined4*)param_1[1];
    if (puVar3 != (undefined4*)param_1[2]) {
        if ((param_2 <= param_3) && (param_3 < puVar3))
            param_3 = param_3 + 4;
        if (puVar3 != 0) {
            *puVar3 = puVar3[-4];
            puVar3[1] = puVar3[-3];
            puVar3[2] = puVar3[-2];
            puVar3[3] = puVar3[-1];
        }
        FUN_00edba80(param_2, param_1[1] + -0x10, param_1[1]);
        *param_2 = *param_3;
        param_2[1] = param_3[1];
        param_2[2] = param_3[2];
        param_2[3] = param_3[3];
        param_1[1] = param_1[1] + 0x10;
        return;
    }
    int iVar1 = (int)puVar3 - *param_1 >> 4;
    int iVar2;
    if (iVar1 == 0) {
        iVar1 = 1;
    } else {
        iVar1 = iVar1 * 2;
        if (iVar1 == 0) {
            iVar2 = 0;
            goto LAB_00b967ba;
        }
    }
    iVar2 = operator_new(iVar1 << 4, "Simulator", 0, 0, kAllocFile, 0xd1);
LAB_00b967ba:
    puVar3 = (undefined4*)FUN_00c7ea30(*param_1, param_2, iVar2);
    if (puVar3 != 0) {
        *puVar3 = *param_3;
        puVar3[1] = param_3[1];
        puVar3[2] = param_3[2];
        puVar3[3] = param_3[3];
    }
    int iVar4 = (int)FUN_00c7ea30((int)param_2, (void*)param_1[1], (int)(puVar3 + 4));
    if (*param_1 != 0)
        operator_delete__((void*)*param_1);
    param_1[1] = iVar4;
    param_1[2] = iVar1 * 0x10 + iVar2;
    *param_1 = iVar2;
}

// @ 0x00b96820
struct S96820 { void fn(undefined4* param_2, int param_3, uint* param_4, char param_5); };
void S96820::fn(undefined4* param_2, int param_3, uint* param_4, char param_5)
{
    int param_1 = (int)this;
    undefined4 uVar2;
    if (((param_5 == '\0') && (param_3 != param_1 + 4)) && (*(uint*)(param_3 + 0x10) <= *param_4))
        uVar2 = 1;
    else
        uVar2 = 0;
    undefined4* puVar1 = *(undefined4**)(param_1 + 0x18);
    if (puVar1 == 0)
        puVar1 = (undefined4*)operator_new(*(undefined4*)(param_1 + 0x28), "Simulator", 0, 0, kAllocFile, 0xd1);
    else
        *(undefined4*)(param_1 + 0x18) = *puVar1;
    if (puVar1 + 4 != 0)
        puVar1[4] = *param_4;
    RBTreeInsert(puVar1, (void*)param_3, (void*)(param_1 + 4), uVar2);
    *(int*)(param_1 + 0x14) = *(int*)(param_1 + 0x14) + 1;
    *param_2 = (int)puVar1;
}

// @ 0x00b96900
struct S96560 { void ctorFrom(const void* src); };
undefined4* FUN_00b96900(undefined4* param_1, undefined4* param_2, undefined4* param_3)
{
    if (param_1 != param_2) {
        do {
            if (param_3 != 0) {
                *(float*)param_3 = *(float*)param_1;
                ((S96560*)(param_3 + 1))->ctorFrom(param_1 + 1);
            }
            param_1 = param_1 + 6;
            param_3 = param_3 + 6;
        } while (param_1 != param_2);
    }
    return param_3;
}

// @ 0x00b96940
struct SRBTree { void DoNuke(void* child); };
int FUN_00b96940(int param_1, int param_2, int param_3)
{
    for (; param_1 != param_2; param_1 = param_1 + 0x34) {
        undefined4* puVar2 = *(undefined4**)(param_1 + 0x24);
        SRBTree* tree = (SRBTree*)(param_1 + 0x18);
        while (puVar2 != 0) {
            tree->DoNuke((void*)puVar2[0]);
            undefined4* puVar1 = (undefined4*)puVar2[1];
            operator_delete__(puVar2);
            puVar2 = puVar1;
        }
        param_3 = param_3 + 0x34;
    }
    return param_3;
}

// @ 0x00b969e0
void FUN_00b969e0(void)
{
    char local_94[0x94];
    cArithmeticaProgram_ctor(local_94);
    LoadArithmeticaFile(0x18657795, 0x24a4f5a, local_94);
    FUN_00401090();
    float fVar1 = FUN_00b7ec50();
    FUN_007f25c0("water_fraction", fVar1);
    FUN_007f2500();
    DAT_01688888 = (int)FUN_007f2590("population_min");
    DAT_01688884 = (int)FUN_007f2590("population_max");
    DAT_01688880 = FUN_007f2590("wealth_min");
    DAT_0168887c = FUN_007f2590("wealth_max");
    FUN_007f1d90();
}

// @ 0x00b96aa0
void FUN_00b96aa0(int param_1)
{
    char local_94[0x94];
    cArithmeticaProgram_ctor(local_94);
    LoadArithmeticaFile(0xa1ed6e3c, 0x24a4f5a, local_94);
    FUN_007f2500();
    int iVar1 = (int)FUN_007f2590("num_tribes");
    float fVar4 = FUN_007f2590("tribe_pop");
    float fVar5 = FUN_007f2590("tribe_food");
    if (0 < iVar1) {
        do {
            void* pcVar2 = (void*)operator_new(0x18, "Simulator/cTribeData", 0, 0, 0, 0);
            int uVar3;
            if (pcVar2 == 0)
                uVar3 = 0;
            else
                uVar3 = cTribeData_ctor(pcVar2, (int)fVar4, (int)fVar5);
            FUN_00b8ef00(uVar3);
            iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
    }
    FUN_007f1d90();
}

// @ 0x00b96b80
void FUN_00b96b80(int param_1)
{
    char local_94[0x94];
    cArithmeticaProgram_ctor(local_94);
    LoadArithmeticaFile(0x18657795, 0x24a4f5a, local_94);
    FUN_007f2500();
    int local_a8 = (int)FUN_007f2590("num_cities");
    float fVar7 = FUN_007f2590("wealth_min");
    float fVar8 = FUN_007f2590("wealth_max");
    if (0 < local_a8) {
        int local_9c = (int)ROUND(fVar8 - fVar7);
        do {
            unsigned iVar1 = RandomUint32Uniform(&_sMathRandom_SP__3VRandomLinearCongruential_Random_EA__A, local_9c + 1);
            int iVar2 = operator_new(0x50, "Simulator/cCivData", 0, 0, 0, 0);
            undefined4 uVar3;
            if (iVar2 == 0)
                uVar3 = 0;
            else
                uVar3 = FUN_00ff34c0((float)iVar1 + fVar7);
            iVar1 = operator_new(0xc4, "Simulator/cCityData", 0, 0, 0, 0);
            void* pVVar4;
            if (iVar1 == 0)
                pVVar4 = 0;
            else
                pVVar4 = (void*)FUN_00ff1cb0();
            VideoEncoder_Jpeg_SetWidth(pVVar4, 4);
            unsigned uVar5 = RandomUint32Uniform(&_sMathRandom_SP__3VRandomLinearCongruential_Random_EA__A, 3);
            uVar5 = FUN_00bef920(uVar5);
            FUN_00bfc460(uVar5);
            unsigned uVar6 = RandomUint32Uniform(&_sMathRandom_SP__3VRandomLinearCongruential_Random_EA__A, 3);
            uVar5 = FUN_00bebc90(uVar5, uVar6);
            FUN_00ff0380(uVar5);
            FUN_00ff2c70(pVVar4);
            FUN_00b8eec0((void*)uVar3);
            local_a8 = local_a8 + -1;
        } while (local_a8 != 0);
        FUN_007f1d90();
        return;
    }
    FUN_007f1d90();
}

// @ 0x00b96d40
void FUN_00b96d40(undefined4 param_1)
{
    char local_94[0x94];
    char local_b0[12];
    undefined4 local_a4;
    cArithmeticaProgram_ctor(local_94);
    LoadArithmeticaFile(0x9dd95c4, 0x24a4f5a, local_94);
    FUN_007f2500();
    char cVar1 = FUN_00c6fe50(param_1);
    float fVar8;
    if (cVar1 == '\0')
        fVar8 = FUN_007f2590("num_cities_in_colony");
    else
        fVar8 = FUN_007f2590("num_cities_in_home_planet");
    int local_b4 = (int)fVar8;
    undefined4 uVar9 = 0x100;
    undefined4 uVar2 = (undefined4)FUN_00b8d8f0(0x100);
    FUN_00b3d2a0(uVar2);
    FUN_00ba6d80(uVar2);
    cVar1 = FUN_00bb9af0(uVar9);
    if (cVar1 != '\0')
        local_b4 = 1;
    int iVar3 = operator_new(0x50, "Simulator/cCivData", 0, 0, 0, 0);
    void* pSVar4;
    if (iVar3 == 0)
        pSVar4 = 0;
    else
        pSVar4 = (void*)FUN_00ff3440();
    void* pcVar5 = BioProtectorSort_op();
    uVar2 = (undefined4)cGameNounManager_GetAvatar(pcVar5);
    rw_SList_SetElementSize(pSVar4, uVar2);
    pcVar5 = BioProtectorSort_op();
    if (pcVar5 != 0) {
        uVar2 = (undefined4)cGameNounManager_GetAvatar(pcVar5);
        FUN_00b3d2a0(uVar2);
        iVar3 = FUN_00ba9370(uVar2);
        if (iVar3 != 0) {
            FUN_00c352f0(local_b0);
            FUN_00ff3190(local_b0);
            DoNukeSubtree((void*)local_a4);
        }
    }
    if (0 < local_b4) {
        do {
            iVar3 = operator_new(0xc4, "Simulator/cCityData", 0, 0, 0, 0);
            void* pVVar6;
            if (iVar3 == 0)
                pVVar6 = 0;
            else
                pVVar6 = (void*)FUN_00ff1cb0();
            uVar9 = 0x100;
            uVar2 = (undefined4)FUN_00b8d8f0(0x100);
            FUN_00b3d2a0(uVar2);
            FUN_00ba6d80(uVar2);
            cVar1 = FUN_00bb9af0(uVar9);
            if (cVar1 == '\0') {
                VideoEncoder_Jpeg_SetWidth(pVVar6, 4);
                ((VideoEncoder_Jpeg*)pVVar6)->mFramesPerSecond = 2.10195e-43f;
            } else {
                VideoEncoder_Jpeg_SetWidth(pVVar6, 2);
            }
            pcVar5 = BioProtectorSort_op();
            iVar3 = cGameNounManager_GetAvatar(pcVar5);
            FUN_00b3d2a0(iVar3);
            int iVar7 = FUN_00885c90();
            if (iVar3 == iVar7)
                uVar2 = 0x280852f1;
            else
                uVar2 = 0xfd701f6f;
            FUN_00ff0380(uVar2);
            FUN_00ff2c70(pVVar6);
            local_b4 = local_b4 + -1;
        } while (local_b4 != 0);
    }
    FUN_00b8eec0(pSVar4);
    FUN_007f1d90();
}

// @ 0x00b96f40
struct S96f40 { void Notify(int n); };
void FUN_00b96f40(int param_1, int param_2)
{
    if (param_1 != 0) {
        switch (param_2) {
        case 2:
            FUN_00b96aa0(param_1);
            break;
        case 4:
            FUN_00b96b80(param_1);
            break;
        case 5:
            FUN_00b96d40(param_1);
            break;
        }
        ((S96f40*)param_1)->Notify(1);
    }
}

// @ 0x00b96fa0
void FUN_00b96fa0(void)
{
    char local_94[0x94];
    cArithmeticaProgram_ctor(local_94);
    LoadArithmeticaFile(0x18657795, 0x24a4f5a, local_94);
    FUN_007f2500();
    FUN_007f2590("num_harvesters");
    float fVar7 = FUN_007f2590("num_offensive_vehicles");
    int local_9c = 0;
    int* piVar2 = FUN_00c71000();
    int iVar6 = piVar2[1] - *piVar2 >> 2;
    if (0 < iVar6) {
        do {
            int iVar3 = FUN_00c71030(local_9c);
            if ((*(int*)(iVar3 + 0x40) - *(int*)(iVar3 + 0x3c) & 0xfffffffcU) != 0) {
                undefined4 uVar1 = *(undefined4*)(**(int**)(iVar3 + 0x3c) + 0x34);
                iVar3 = (int)fVar7;
                if (0 < (int)fVar7) {
                    do {
                        int iVar4 = operator_new(0x14, "Simulator/cVehicleData", 0, 0, 0, 0);
                        undefined4 uVar5;
                        if (iVar4 == 0)
                            uVar5 = 0;
                        else
                            uVar5 = FUN_00ff0df0(&DAT_01688890, 2, uVar1);
                        FUN_00ff2d20(uVar5);
                        iVar3 = iVar3 + -1;
                    } while (iVar3 != 0);
                }
            }
            local_9c = local_9c + 1;
        } while (local_9c < iVar6);
    }
    FUN_007f1d90();
}

// @ 0x00b970c0
struct S970c0 { int fn(undefined4 param_2); };
int S970c0::fn(undefined4 param_2)
{
    undefined4* param_1 = (undefined4*)this;
    int local[2];
    FUN_00b96220(local, *param_1, param_1[1], (uint*)param_2, *(undefined1*)(param_1 + 5));
    return local[1] - local[0] >> 4;
}

// @ 0x00b970f0
void __stdcall FUN_00b970f0(uint param_1, uint param_2)
{
    for (; param_1 < param_2; param_1 = param_1 + 0x34) {
        undefined4* puVar2 = *(undefined4**)(param_1 + 0x24);
        SRBTree* tree = (SRBTree*)(param_1 + 0x18);
        while (puVar2 != 0) {
            tree->DoNuke((void*)puVar2[0]);
            undefined4* puVar1 = (undefined4*)puVar2[1];
            operator_delete__(puVar2);
            puVar2 = puVar1;
        }
    }
}

// @ 0x00b97140
struct S97140 { int fn(undefined4* param_2, undefined4* param_3); };
int S97140::fn(undefined4* param_2, undefined4* param_3)
{
    int* param_1 = (int*)this;
    undefined4* puVar1 = (undefined4*)param_1[1];
    int iVar2 = (int)param_2 - *param_1 >> 4;
    if ((param_2 == puVar1) && (puVar1 != (undefined4*)param_1[2])) {
        param_1[1] = (int)(puVar1 + 4);
        if (puVar1 != 0) {
            *puVar1 = *param_3;
            puVar1[1] = param_3[1];
            puVar1[2] = param_3[2];
            puVar1[3] = param_3[3];
            return iVar2 * 0x10 + *param_1;
        }
    } else {
        ((S96710*)param_1)->fn(param_2, param_3);
    }
    return iVar2 * 0x10 + *param_1;
}

// @ 0x00b97240
struct Vec4f { float a, b, c, d; };
struct Elem97240 { Vec4f v; char b; int i; };
struct S97240 { undefined4* fn(undefined4* param_2); };
undefined4* S97240::fn(undefined4* param_2)
{
    Elem97240* dst = (Elem97240*)this;
    Elem97240* src = (Elem97240*)param_2;
    dst->v.a = src->v.a;
    dst->v.b = src->v.b;
    dst->v.c = src->v.c;
    dst->v.d = src->v.d;
    dst->b = src->b;
    dst->i = src->i;
    ((S96560*)((char*)dst + 0x18))->ctorFrom((char*)src + 0x18);
    return (undefined4*)this;
}
