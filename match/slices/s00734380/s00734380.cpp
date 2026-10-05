// Slice s00734380 — mesh/refcount container helpers: a refcounted element builder, two vector
// insert/assign operations and their wrappers.  The two large functions are left as skeletons.
#include "types.h"
#include <string.h>

struct EltArray
{
    int32_t  mNumElts;
    uint8_t* mData;
    uint16_t mEltSize;
    uint16_t mEltStride;
    void*    mRC;
};

// external callees (masked relocations / other slices)
void  FUN_00734380(int, int, float);
int   FUN_0071ddc0(int, int, int, int, int);
void* EAAlloc(int, const char*, int, int, const char*, int);
void  EAFree(void*);
int*  FUN_00733760(int);
EltArray* FUN_00732ff0(void*);
void  FUN_00424f70(void*);
void* FUN_00733310(int, int, int);
void  FUN_00733230(int, int, int, int);
void  FUN_00733140(int*, int, int, int);
void* FUN_00758630(uint32_t, int, int);
void* FUN_007b0920(uint32_t, int, int);
void  FUN_00b007f0(int, int);
void* FUN_007b0040(void*, int, int, int, int);
void  FUN_00b85090(int, int, int);
void  FUN_00b7f6a0(int, int, void*);
void* FUN_006782c0(void*, void*, void*);
void  FUN_00733920(void*, void*);
void  FUN_00733a50(void*);
void  FUN_00733f20(void*);

// @ 0x00734380
__declspec(noinline) void FUN_00734380(int param_1, int param_2, float fac)
{
    // PARTIAL: 0x00734380 allocates a refcounted 0x24-byte element, packs a float3 list into it
    // and installs it into a descriptor slot.  Skeleton only.
    (void)param_1; (void)param_2; (void)fac;
    *(volatile int*)param_1 = *(volatile int*)param_1;
}

// @ 0x007345c0
void FUN_007345c0(int param_1)
{
    FUN_00734380(param_1, 3, 0.5f);
    FUN_00734380(param_1, 2, 0.5f);
}

// @ 0x00734660
int FUN_00734660(int* param_1, int param_2, int* param_3)
{
    int* puVar1 = (int*)param_1[1];
    int iVar2 = (param_2 - *param_1) / 0xc;
    if ((param_2 == (int)puVar1) && (puVar1 != (int*)param_1[2]))
    {
        param_1[1] = (int)(puVar1 + 3);
        if (puVar1 != 0)
        {
            puVar1[0] = param_3[0];
            puVar1[1] = param_3[1];
            puVar1[2] = param_3[2];
            return *param_1 + iVar2 * 0xc;
        }
    }
    else
    {
        FUN_00733920((void*)param_2, param_3);
    }
    return *param_1 + iVar2 * 0xc;
}

// @ 0x007346d0
void FUN_007346d0(int* param_1, int param_2, uint32_t param_3, int param_4)
{
    // PARTIAL: reserve/insert over 0x24-byte Matrix33 elements.  Skeleton only.
    (void)param_1; (void)param_2; (void)param_3; (void)param_4;
}

// @ 0x007348a0
int* FUN_007348a0(int* param_1, int* param_2)
{
    if (param_2 != param_1)
    {
        int pvVar1 = *param_2;
        int _Dst = *param_1;
        int iVar2 = param_2[1];
        uint32_t uVar5 = (uint32_t)(iVar2 - pvVar1) >> 2;
        if ((uint32_t)(param_1[2] - _Dst) >> 2 < uVar5)
        {
            int iVar3 = (int)FUN_00758630(uVar5, pvVar1, iVar2);
            int t = *param_1;
            if (t != 0 && t != param_1[4])
                EAFree((void*)t);
            *param_1 = iVar3;
            param_1[2] = iVar3 + uVar5 * 4;
            param_1[1] = iVar3 + uVar5 * 4;
            return param_1;
        }
        uint32_t uVar4 = (uint32_t)(param_1[1] - _Dst) >> 2;
        if (uVar4 < uVar5)
        {
            memcpy((void*)_Dst, (void*)pvVar1, uVar4 * 4);
            int src = *param_2 + ((param_1[1] - *param_1) >> 2) * 4;
            memcpy((void*)param_1[1], (void*)src, param_2[1] - src);
            param_1[1] = *param_1 + uVar5 * 4;
            return param_1;
        }
        memcpy((void*)_Dst, (void*)pvVar1, iVar2 - pvVar1);
        param_1[1] = *param_1 + uVar5 * 4;
    }
    return param_1;
}

// @ 0x00734970
void FUN_00734970(void)
{
    // PARTIAL: ~0.9 KB table/container routine; skeleton only.
}

// @ 0x00734d00
void FUN_00734d00(void)
{
    // PARTIAL: ~1.3 KB container routine; skeleton only.
}

// @ 0x00735260
int* FUN_00735260(int* param_1, int* param_2)
{
    if (param_2 != param_1)
    {
        int iVar1 = *param_2;
        int iVar4 = *param_1;
        int iVar2 = param_2[1];
        uint32_t uVar7 = (uint32_t)(iVar2 - iVar1) >> 2;
        if ((uint32_t)(param_1[2] - iVar4) >> 2 < uVar7)
        {
            int nv = (int)FUN_007b0920(uVar7, iVar1, iVar2);
            FUN_00b007f0(*param_1, param_1[1]);
            int t = *param_1;
            if (t != 0 && *(int*)(t - 4) != 0)
                EAFree((void*)t);
            param_1[2] = nv + uVar7 * 4;
            param_1[1] = nv + uVar7 * 4;
            *param_1 = nv;
            return param_1;
        }
        uint32_t uVar6 = (uint32_t)(param_1[1] - iVar4) >> 2;
        if (uVar6 < uVar7)
        {
            FUN_006782c0((void*)iVar1, (void*)(iVar1 + uVar6 * 4), (void*)iVar4);
            FUN_007b0040(&param_2, *param_2 + ((param_1[1] - *param_1) >> 2) * 4, param_2[1],
                         param_1[1], (int)param_2);
            param_1[1] = *param_1 + uVar7 * 4;
            return param_1;
        }
        int p = (int)FUN_006782c0((void*)iVar1, (void*)iVar2, (void*)iVar4);
        FUN_00b007f0(p, param_1[1]);
        param_1[1] = *param_1 + uVar7 * 4;
    }
    return param_1;
}
