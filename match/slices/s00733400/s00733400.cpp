// Slice s00733400 — EASTL container helpers (vector reserve/fill/insert) and four EH/unwind
// constructors for a resource object; the two large functions are left as skeletons.
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

// external callees (masked relocations)
void  FUN_006fa770(int, int);
void  FUN_00733070(int, void*);
void  FUN_006a46a0(int, void*);
void  FUN_006a4600(int, void*);
void  FUN_007c7a40(int, void*);
void  FUN_0047cae0(int, int, void*, int);
int   FUN_00a11310(int, int, int);
void* EAAlloc(int, const char*, int, int, const char*, int);
void  EAFree(void*);
void  FUN_00733a50(void*);
void  FUN_00733f20(void*);

// @ 0x00733400
int* FUN_00733400(int* p1, int param_2, int param_3)
{
    FUN_006fa770(param_2, param_3);
    int zeros[7] = { 0, 0, 0, 0, 0, 0, 0 };
    int* dst = (int*)*p1;
    for (int n = param_2; n != 0; --n)
    {
        if (dst)
        {
            for (int k = 0; k < 7; ++k)
                dst[k] = zeros[k];
        }
        dst += 7;
    }
    p1[1] = *p1 + param_2 * 0x1c;
    return p1;
}

// @ 0x00733510
void* FUN_00733510(int* param_1, int* param_2, int* param_3, int* param_4, int* param_5, int param_6)
{
    while (param_1 != param_2 && param_3 != param_4)
    {
        uint32_t mask = g_masks[*(uint16_t*)(param_6 + 8)];
        uint32_t a = *(uint32_t*)(*param_3 * (uint32_t)*(uint16_t*)(param_6 + 10) + *(int*)(param_6 + 4));
        uint32_t b = *(uint32_t*)(*(int*)(param_6 + 4) + *param_1 * (uint32_t)*(uint16_t*)(param_6 + 10));
        if ((a & mask) < (b & mask))
        {
            int v = *param_3;
            param_3++;
            *param_5 = v;
        }
        else
        {
            *param_5 = *param_1;
            param_1++;
        }
        param_5++;
    }
    int n1 = (int)param_2 - (int)param_1;
    void* r = memcpy(param_5, param_1, n1);
    int n2 = (int)param_4 - (int)param_3;
    r = memcpy((char*)r + (n1 >> 2) * 4, param_3, n2);
    return (char*)r + (n2 >> 2) * 4;
}

// @ 0x00733920
void FUN_00733920(int* param_1, void* param_2, void* param_3)
{
    int* puVar3 = (int*)param_1[1];
    if (puVar3 != (int*)param_1[2])
    {
        if ((param_2 <= param_3) && (param_3 < puVar3))
            param_3 = (char*)param_3 + 0xc;
        if (puVar3 != 0)
        {
            puVar3[0] = puVar3[-3];
            puVar3[1] = puVar3[-2];
            puVar3[2] = puVar3[-1];
        }
        puVar3 = (int*)param_1[1];
        int* puVar1 = (int*)param_1[1];
        while (puVar1 - 3 != param_2)
        {
            puVar3[-3] = puVar1[-6];
            puVar3[-2] = puVar1[-5];
            puVar3[-1] = puVar1[-4];
            puVar3 -= 3;
            puVar1 -= 3;
        }
        *(int*)param_2 = *(int*)param_3;
        ((int*)param_2)[1] = ((int*)param_3)[1];
        ((int*)param_2)[2] = ((int*)param_3)[2];
        param_1[1] = param_1[1] + 0xc;
        return;
    }
    int iVar5 = ((int)puVar3 - *param_1) / 0xc;
    int iVar2;
    if (iVar5 == 0)
    {
        iVar5 = 1;
        iVar2 = (int)EAAlloc(iVar5 * 0xc, "Graphics", 0, 0,
                             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    else
    {
        iVar5 = iVar5 * 2;
        if (iVar5 == 0)
            iVar2 = 0;
        else
            iVar2 = (int)EAAlloc(iVar5 * 0xc, "Graphics", 0, 0,
                                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    puVar3 = (int*)FUN_00a11310(*param_1, (int)param_2, iVar2);
    if (puVar3 != 0)
    {
        puVar3[0] = *(int*)param_3;
        puVar3[1] = ((int*)param_3)[1];
        puVar3[2] = ((int*)param_3)[2];
    }
    int iVar4 = FUN_00a11310((int)param_2, param_1[1], (int)(puVar3 + 3));
    if (*param_1 != 0)
        EAFree((void*)*param_1);
    *param_1 = iVar2;
    param_1[1] = iVar4;
    param_1[2] = iVar2 + iVar5 * 0xc;
}

// @ 0x00733e90
void FUN_00733e90(int param_1, int param_2, int param_3)
{
    for (int i = 0; i < param_2; i++)
        FUN_00733a50((void*)(*(int*)(param_3 + i * 4) * 0x20 + *(int*)(param_1 + 8)));
}

// @ 0x00733ed0
void FUN_00733ed0(int param_1)
{
    for (int i = 0; i < (*(int*)(param_1 + 0xc) - *(int*)(param_1 + 8) >> 5); i += 0x20)
    {
        int v = *(int*)(*(int*)(param_1 + 8) + i);
        if (((v == 8) || (v == 2)) || (v == 3) || (v == 10))
            FUN_00733a50((void*)(*(int*)(param_1 + 8) + i));
    }
}

// --- EH/unwind constructors (vtable + cookie).  Vtable addresses are relocations; the EH
//     prolog is approximated with a plain prolog, so these are not byte-exact. --------------
extern void* g_vtblEditor;
extern void* g_vtblCreatureAbility; // 0x013ef094
extern void* g_vtblA; // 0x013ebcc8
extern void* g_vtblB; // 0x013ef8d4

struct CtorObj
{
    void* mVT0;
    void* mVT1;
    int   mRef;      // +0x08
    int   mArr;      // +0x0c
    int   mArrEnd;   // +0x10
    int   mPad[3];
    int   mLast;     // +0x20

    void ctor_c0(int arg);
    void ctor_640(int arg);
    void ctor_6e0(int arg);
    void ctor_760(int arg);
};

// @ 0x007335c0
void CtorObj::ctor_c0(int arg)
{
    mVT0 = g_vtblEditor;
    mVT1 = g_vtblCreatureAbility;
    mRef = 0;
    mVT0 = g_vtblA;
    mVT1 = g_vtblB;
    FUN_006a46a0(arg, &arg);
    mLast = 0;
}

// @ 0x00733640
void CtorObj::ctor_640(int arg)
{
    mVT0 = g_vtblEditor;
    mVT1 = g_vtblCreatureAbility;
    mRef = 0;
    mVT0 = g_vtblA;
    mVT1 = g_vtblB;
    char buf[16];
    FUN_007c7a40(arg, &arg);
    FUN_0047cae0(mArr, arg, buf, arg);
    mArrEnd = arg * 0x10 + mArr;
    mLast = 0;
}

// @ 0x007336e0
void CtorObj::ctor_6e0(int arg)
{
    mVT0 = g_vtblEditor;
    mVT1 = g_vtblCreatureAbility;
    mRef = 0;
    mVT0 = g_vtblA;
    mVT1 = g_vtblB;
    FUN_006a4600(arg, &arg);
    mLast = 0;
}

// @ 0x00733760
void CtorObj::ctor_760(int arg)
{
    mVT0 = g_vtblEditor;
    mVT1 = g_vtblCreatureAbility;
    mRef = 0;
    mVT0 = g_vtblA;
    mVT1 = g_vtblB;
    FUN_00733070(arg, &arg);
    int* p = (int*)mArr;
    for (int n = arg; n != 0; --n)
    {
        if (p)
            *p = 0;
        p++;
    }
    mArrEnd = mArr + arg * 4;
    mLast = 0;
}

// @ 0x00733a50
__declspec(noinline) void FUN_00733a50(void* p)
{
    // PARTIAL: 0x00733a50 is a ~1 KB element/sub-tree destructor; skeleton only.
    *(volatile int*)p = *(volatile int*)p;
}

// @ 0x00733f20
__declspec(noinline) void FUN_00733f20(void* p)
{
    // PARTIAL: 0x00733f20 is a ~1.1 KB destructor walk; skeleton only.
    *(volatile int*)p = *(volatile int*)p;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
