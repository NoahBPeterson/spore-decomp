// Slice s007361e0 — refcounted EltArray/descriptor construction and reconstruction loops.
// 0x00736660 is a small in-place emplace; the three larger EH/refcount routines are skeletons.
#include "types.h"

void FUN_00423080(int);
void FUN_00424cf0(int, int);
void FUN_004751a0(int);
void FUN_00424f70(int*);
void FUN_00720070(int*);
int* FUN_00732ff0(void*);
void* FUN_00723680(int);
void* EAAlloc(int, const char*, int, int, const char*, int);
void  EAFree(void*);

struct Vec41
{
    int* mBegin;
    int* mEnd;
    int* mCap;
    int  emit(int pos, int src);   // 0x736660
};

// @ 0x00736660
int Vec41::emit(int param_2, int param_3)
{
    int iVar1 = (int)mEnd;
    int iVar2 = (int)mBegin;
    if (param_2 == iVar1 && iVar1 != (int)mCap)
    {
        mEnd = (int*)(iVar1 + 0x20);
        if (iVar1 != 0)
            FUN_00423080(param_3);
    }
    else
    {
        FUN_00424cf0(param_2, param_3);
    }
    return ((param_2 - iVar2) >> 5) * 0x20 + (int)mBegin;
}

// @ 0x007361e0
void FUN_007361e0(void)
{
    // PARTIAL: ~1.1 KB EltArray/descriptor construction with EH; skeleton only.
}

// @ 0x007366e0
void FUN_007366e0(int param_1)
{
    // PARTIAL: rebuild per-cluster index arrays (0x8c-byte records, refcounted); skeleton only.
    (void)param_1;
}

// @ 0x007368a0
void FUN_007368a0(int* param_1)
{
    // PARTIAL: rebuild reverse index streams with refcounted EltArrays; skeleton only.
    (void)param_1;
}
