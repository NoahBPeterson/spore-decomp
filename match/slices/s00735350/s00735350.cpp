// Slice s00735350 — sorted-vector (eastl::set-like) operations over 0xc/0x24/0x20-byte keys plus
// a refcounted element fill.  Small operations are reconstructed; the two large ones are
// skeletons.
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
extern uint32_t g_masks[];

int   FUN_007330d0(int, int, int*, int);
int   FUN_00734660(int*, int*);
void  FUN_007346d0(int*, int, int, int);
void  FUN_00b85500(int, int);
int*  FUN_00732ff0(void*);
int   FUN_0072ac10(int*);
void  FUN_007348a0(int*);
void* FUN_00723680(int);
int*  FUN_007334b0(uint32_t, int, int);
void  FUN_00714b10(int, int);
int   FUN_0071e7d0(int, int, int);
void  FUN_0047b290(void**, int, int, int, void*);
void  FUN_0072a1a0(uint32_t, int*);
void* EAAlloc(int, const char*, int, int, const char*, int);
void  EAFree(void*);

struct Vec
{
    int*   mBegin;   // +0x00
    int*   mEnd;     // +0x04
    int*   mCap;     // +0x08
    int    pad0;     // +0x0c
    int    pad1;     // +0x10
    int8_t mFlag;    // +0x14

    int*   insertL(int* a, int* b);     // 0x735350
    int*   operator=(int* other);       // 0x735dd0
    int*   findLower(int* key);         // 0x735ec0
    void   resize24(uint32_t n, int v); // 0x735f30
    void   fill(uint32_t n, void* v);   // 0x736090
};

// @ 0x00735350
int* Vec::insertL(int* param_2, int* param_3)
{
    int* piVar2 = mEnd;
    int uVar1;
    int* piVar3;
    if (param_2 != piVar2)
    {
        if ((*param_3 < *param_2) || ((*param_3 <= *param_2 && (param_3[1] < param_2[1]))))
        {
            uVar1 = mFlag;
            piVar3 = mBegin;
            goto call;
        }
    }
    uVar1 = mFlag;
    piVar3 = param_2;
    param_2 = piVar2;
call:
    piVar3 = (int*)FUN_007330d0((int)piVar3, (int)param_2, param_3, uVar1);
    if (piVar3 != piVar2)
    {
        if (*piVar3 <= *param_3)
        {
            if (*piVar3 < *param_3)
                return piVar3;
            if (piVar3[1] <= param_3[1])
                return piVar3;
        }
    }
    return (int*)FUN_00734660(piVar3, param_3);
}

// @ 0x00735ec0
int* Vec::findLower(int* param_2)
{
    int* piVar1 = mEnd;
    int* piVar2 = (int*)FUN_007330d0((int)mBegin, (int)piVar1, param_2, mFlag);
    if (piVar2 != piVar1)
    {
        if ((*piVar2 <= *param_2) && ((*piVar2 < *param_2) || (piVar2[1] <= param_2[1])))
            goto ret;
    }
    {
        int local_c = *param_2;
        int local_8 = param_2[1];
        int local_4 = 0;
        piVar2 = insertL(piVar2, &local_c);
    }
ret:
    return piVar2 + 2;
}

// @ 0x00735f30
void Vec::resize24(uint32_t param_2, int param_3)
{
    int iVar1 = mEnd ? (int)mEnd : 0;
    int iVar2 = (int)mBegin;
    if ((uint32_t)((iVar1 - iVar2) / 0x24) < param_2)
    {
        FUN_007346d0((int*)iVar1, param_2 - (iVar1 - iVar2) / 0x24, param_3, 0);
        return;
    }
    FUN_00b85500(iVar2 + param_2 * 0x24, iVar1);
}

// @ 0x00735dd0
int* Vec::operator=(int* param_2)
{
    if (param_2 != (int*)this)
    {
        int iVar1 = *param_2;
        int iVar4 = *mBegin;
        int iVar2 = param_2[1];
        uint32_t uVar7 = (uint32_t)(iVar2 - iVar1) >> 5;
        if ((uint32_t)((int)mCap - iVar4) >> 5 < uVar7)
        {
            iVar4 = (int)FUN_007334b0(uVar7, iVar1, iVar2);
            FUN_00714b10((int)mBegin, (int)mEnd);
            if (mBegin != 0 && *(int*)((int)mBegin - 4) != 0)
                EAFree(mBegin);
            mEnd = (int*)(uVar7 * 0x20 + iVar4);
            mCap = (int*)(uVar7 * 0x20 + iVar4);
            mBegin = (int*)iVar4;
            return (int*)this;
        }
        uint32_t uVar5 = (uint32_t)((int)mEnd - iVar4) >> 5;
        if (uVar5 < uVar7)
        {
            FUN_0071e7d0(iVar1, uVar5 * 0x20 + iVar1, iVar4);
            FUN_0047b290((void**)&param_2, ((int)((int)mEnd - (int)mBegin) >> 5) * 0x20 + *param_2,
                         param_2[1], (int)mEnd, param_2);
            mEnd = (int*)(uVar7 * 0x20 + (int)mBegin);
            return (int*)this;
        }
        int uVar6 = FUN_0071e7d0(iVar1, iVar2, iVar4);
        FUN_00714b10(uVar6, (int)mEnd);
        mEnd = (int*)(uVar7 * 0x20 + (int)mBegin);
    }
    return (int*)this;
}

// @ 0x00735fa0
void FUN_00735fa0(int param_1, int param_2, int* param_3)
{
    if (param_2 != 0)
    {
        int* piVar2 = (int*)(param_1 + 0x14);
        do
        {
            if (piVar2 != (int*)0x14)
            {
                piVar2[-5] = param_3[0];
                piVar2[-4] = param_3[1];
                piVar2[-3] = param_3[2];
                piVar2[-2] = param_3[3];
                int iVar3 = (param_3[5] - param_3[4]) >> 2;
                void* pvVar1 = 0;
                if (iVar3 != 0)
                    pvVar1 = EAAlloc(iVar3 * 4, "Graphics", 0, 0,
                                     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
                piVar2[-1] = (int)pvVar1;
                *piVar2 = (int)pvVar1;
                piVar2[1] = (int)pvVar1 + iVar3 * 4;
                size_t sz = param_3[5] - param_3[4];
                pvVar1 = memcpy(pvVar1, (void*)param_3[4], sz);
                *piVar2 = (int)pvVar1 + ((int)sz >> 2) * 4;
            }
            param_2 = param_2 - 1;
            piVar2 = piVar2 + 9;
        } while (param_2 != 0);
    }
}

// @ 0x007353c0
void FUN_007353c0(int* param_1, int* param_2)
{
    // PARTIAL: swap-or-assign of a 0x24-byte-element vector with EH cleanup; skeleton.
    (void)param_1; (void)param_2;
}

// @ 0x00735470
void FUN_00735470(void)
{
    // PARTIAL: ~1.2 KB container routine; skeleton only.
}

// @ 0x00735960
void FUN_00735960(int* param_1, int* param_2)
{
    // PARTIAL: refcounted element list builder with EH; skeleton only.
    (void)param_1; (void)param_2;
}

// @ 0x00735a90
void FUN_00735a90(void)
{
    // PARTIAL: ~0.8 KB container routine; skeleton only.
}

// @ 0x00736090
void FUN_00736090(int* param_1, uint32_t param_2, int* param_3)
{
    // PARTIAL: vector fill/insert with EH; skeleton only.
    (void)param_1; (void)param_2; (void)param_3;
}
