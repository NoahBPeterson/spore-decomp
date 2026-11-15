// Slice s00799cc0 -- UTFKernel graphics/split-transform helpers (final batch).
// Flags: /O2 /MD /Gy /EHsc /TP /fp:fast (scalar math is x87 here).

#include <intrin.h>
#include <math.h>
#include <xmmintrin.h>

const char *const ALLOC_PATH =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

extern int DAT_0153b208[];
extern float DAT_01634510;
extern float DAT_01634514;
extern float DAT_01634518;
extern float DAT_01634650[9];

// ----------------------------------------------------------------------------------------------
// Split-transform combine (0079a0d0): `combine` folds a source transform into a destination one.
// ----------------------------------------------------------------------------------------------
struct SplitSource {
    unsigned int flags;         // +0x00  bit1: orientation, bit2: offset
    float    offset[3];         // +0x04
    float    scale;             // +0x10
    float    matrix[9];         // +0x14  row-major 3x3
};

struct SplitState {
    unsigned int flags;         // +0x00  bit0: fold the source scale, bit1: fold the orientation
    unsigned char orientFlags;  // +0x04  bit1: orientation, bit2: position
    unsigned char pad05[3];
    float    position[3];       // +0x08
    float    scaleFactor;       // +0x14
    float    matrix[9];         // +0x18  row-major 3x3
    unsigned short mask;        // +0x3c  fields folded so far
    unsigned short count;       // +0x3e
    float    outPosition[3];    // +0x40
    float    outScale;          // +0x4c
    float    outMatrix[9];      // +0x50
    SplitState * __thiscall combine(const SplitSource *src);
};

// ----------------------------------------------------------------------------------------------
// EASTL vector storage (begin / end / capacity) of the split-transform lists. `reserve` grows the
// buffer; retail leaves the element count in eax when it returns early and the new capacity-end
// pointer after a reallocation, so the return value reproduces that.
// ----------------------------------------------------------------------------------------------
struct SplitElem20Vector {      // 20-byte elements (0079a4f0)
    void *mBegin;               // +0x00
    void *mEnd;                 // +0x04
    void *mCapacityEnd;         // +0x08
    void * __thiscall reserve(unsigned int count);
};

struct SplitElem8Vector {       // 8-byte elements (0079af80)
    void *mBegin;               // +0x00
    void *mEnd;                 // +0x04
    void *mCapacityEnd;         // +0x08
    void * __thiscall reserve(unsigned int count);
};

// ----------------------------------------------------------------------------------------------
// Refcounted objects and the records that own them (0079ac70 / 0079aeb0).
// ----------------------------------------------------------------------------------------------
struct SharedObject {           // vtable pointer, then the shared count
    void **mVtable;             // +0x00
    int mRefCount;              // +0x04
};

struct SplitInner {             // destroyed by 0079ac70
    SharedObject *mOwner;       // +0x00
    SharedObject *mList;        // +0x04
    unsigned int pad08[4];      // +0x08
    void *mBufferBegin;         // +0x18
    void *mBufferEnd;           // +0x1c
    void *mBufferCapacityEnd;   // +0x20
    unsigned int pad24[7];      // +0x24
    void __thiscall destroy();
};

struct SplitRecord {            // torn down by 0079aeb0
    SharedObject *mOwner;       // +0x00
    SharedObject *mResource;    // +0x04
    SplitInner mInner;          // +0x08
    void *mBufferBegin;         // +0x48
    void *mBufferEnd;           // +0x4c
    unsigned int pad50;         // +0x50
    void __thiscall destroy();
};

// Drop a shared reference; the last owner calls the object's first vtable slot with `delete`.
static __forceinline void ReleaseShared(SharedObject *object)
{
    if (object == 0) {
        return;
    }
    int refs = object->mRefCount;
    object->mRefCount = refs - 1;
    if (refs == 1) {
        object->mRefCount = 1;
        ((void (__thiscall *)(SharedObject *, int))object->mVtable[0])(object, 1);
    }
}

extern int V_13ebc60;
extern int V_140f580;
extern int V_140f588;
extern int V_140f58c;
extern int V_13ef094;

extern int FUN_00f473a0(...);
extern void FUN_00f47380(void *block);
extern int FUN_011e0744(...);
extern void __stdcall FUN_01023030(void *begin, void *end);   // SP::nSpaceCheats::vector_dtor_IntVector
extern int FUN_00537dc0(...);
extern int FUN_008def80(...);

// EASTL's debug heap keeps a 4-byte marker in front of every block; 0 means "never allocated".
static __forceinline void FreeDebugBlock(void *block)
{
    if ((block != 0) && (((const int *)block)[-1] != 0)) {
        FUN_00f47380(block);
    }
}

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
struct VCtor16 { VCtor16 *c0(int *); };

// @ 0x00799cc0
VCtor16 *VCtor16::c0(int *param_2)
{
    int *param_1 = (int *)this;
    param_1[0] = (int)&V_13ebc60;
    param_1[1] = 0;
    param_1[2] = 4;
    *(float *)(param_1 + 3) = *(float *)param_2;
    *(float *)(param_1 + 4) = *(float *)(param_2 + 1);
    *(float *)(param_1 + 5) = *(float *)(param_2 + 2);
    *(float *)(param_1 + 6) = *(float *)(param_2 + 3);
    _ReadWriteBarrier();
    param_1[0] = (int)&V_140f580;
    return this;
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
SplitState *SplitState::combine(const SplitSource *src)
{
    const float *mat = matrix;
    const float *srcMat = src->matrix;
    float product[9];
    int i;
    for (i = 0; i != 9; i = i + 1) {
        outMatrix[i] = DAT_01634650[i];
    }
    outScale = 1.0f;
    outPosition[0] = DAT_01634510;
    outPosition[1] = DAT_01634514;
    outPosition[2] = DAT_01634518;
    count = 0;
    mask = 0;
    outScale = src->scale;
    count = count + 1;
    if ((flags & 1) != 0) {
        outScale = scaleFactor * outScale;
        mask = mask | 1;
        count = count + 1;
    }
    if ((orientFlags & 4) != 0) {
        outPosition[0] = position[0];
        outPosition[1] = position[1];
        outPosition[2] = position[2];
        mask = mask | 4;
        count = count + 1;
    }
    if (((flags & 2) != 0) && ((src->flags & 4) != 0)) {
        outPosition[0] = outPosition[0] + src->offset[0];
        outPosition[1] = src->offset[1] + outPosition[1];
        outPosition[2] = src->offset[2] + outPosition[2];
        mask = mask | 4;
        count = count + 1;
    }
    if ((orientFlags & 2) == 0) {
        if ((src->flags & 2) == 0) {
            return this;
        }
        mat = srcMat;
    } else if ((src->flags & 2) == 0) {
        mat = matrix;
    } else {
        // retail multiplies with scalar SSE: (a0*b0 + a1*b1) + a2*b2, so the rounding of the
        // source's per-column products is reproduced only with the _mm_*_ss intrinsics.
        for (i = 0; i != 3; i = i + 1) {
            __m128 c0 = _mm_set_ss(srcMat[i]);
            __m128 c1 = _mm_set_ss(srcMat[3 + i]);
            __m128 c2 = _mm_set_ss(srcMat[6 + i]);
            for (int row = 0; row != 3; row = row + 1) {
                __m128 p = _mm_mul_ss(c0, _mm_set_ss(matrix[row * 3]));
                p = _mm_add_ss(p, _mm_mul_ss(c1, _mm_set_ss(matrix[row * 3 + 1])));
                p = _mm_add_ss(p, _mm_mul_ss(c2, _mm_set_ss(matrix[row * 3 + 2])));
                product[row * 3 + i] = _mm_cvtss_f32(p);
            }
        }
        mat = product;
    }
    for (i = 0; i != 9; i = i + 1) {
        outMatrix[i] = mat[i];
    }
    mask = mask | 2;
    count = count + 1;
    return this;
}

// @ 0x0079a4f0
void *SplitElem20Vector::reserve(unsigned int count)
{
    unsigned int capacity = (unsigned int)(((char *)mCapacityEnd - (char *)mBegin) / 20);
    if (capacity >= count) {
        return (void *)capacity;
    }
    char *fresh = 0;
    if (count != 0) {
        fresh = (char *)FUN_00f473a0(count * 20, "Graphics", 0, 0, ALLOC_PATH, 0xd1);
    }
    FUN_011e0744(fresh, mBegin, (int)((char *)mEnd - (char *)mBegin));
    // retail re-reads the storage after the copy: a source pointer that aliases the vector
    // itself makes the copy move the object, not just its elements
    FreeDebugBlock(mBegin);
    unsigned int used = (unsigned int)(((char *)mEnd - (char *)mBegin) / 20);
    mBegin = fresh;
    mEnd = fresh + used * 20;
    mCapacityEnd = fresh + count * 20;
    return mCapacityEnd;
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
void SplitInner::destroy()
{
    SplitInner *const self = this;
    FUN_01023030(mBufferBegin, mBufferEnd);
    FreeDebugBlock(mBufferBegin);
    FreeDebugBlock(mList);
    ReleaseShared(mOwner);
    // retail brackets the body with push ecx / pop ecx (stack scratch), so the caller's ecx holds
    // the incoming `this` again when the function returns
    __asm { mov ecx, self }
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
void SplitRecord::destroy()
{
    FUN_01023030(mBufferBegin, mBufferEnd);
    FreeDebugBlock(mBufferBegin);
    mInner.destroy();
    ReleaseShared(mResource);
    ReleaseShared(mOwner);
}

// @ 0x0079af80
void *SplitElem8Vector::reserve(unsigned int count)
{
    // retail shifts the byte difference (8-byte elements) instead of dividing, so a garbage
    // storage range (capacity end below begin) rounds towards -inf
    unsigned int capacity = (unsigned int)((int)((char *)mCapacityEnd - (char *)mBegin) >> 3);
    if (capacity >= count) {
        return (void *)count;
    }
    char *fresh = 0;
    if (count != 0) {
        fresh = (char *)FUN_00f473a0(count * 8, "Graphics", 0, 0, ALLOC_PATH, 0xd1);
    }
    FUN_007992e0((int *)mBegin, (int *)mEnd, (int *)fresh);
    FUN_008def80(mBegin, mEnd, fresh);
    // retail re-reads the storage after the copy: a source pointer that aliases the vector
    // itself makes the copy move the object, not just its elements
    FreeDebugBlock(mBegin);
    unsigned int used = (unsigned int)(((char *)mEnd - (char *)mBegin) / 8);
    mBegin = fresh;
    mEnd = fresh + used * 8;
    mCapacityEnd = fresh + count * 8;
    return mEnd;                // retail leaves the new end pointer in eax on this path
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
