// Slice s004b0490 — vector (re)allocation helpers.
#include "types.h"
#include <string.h>

struct V3 { float x, y, z; };
struct B24 { V3 a; V3 b; };

extern void FUN_004b2030(void* a, void** b);
extern void FUN_004b00a0(void* p);
extern void FUN_004b0180(void* p);

struct Vec24 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;

    void Wrapper(void* a, void* b);       // 0x4b0560
    B24* Erase24(B24* dst, B24* end);     // 0x4b0490
    void Other(void* a, void** b);        // 0x4b2030
};

// @ 0x004b0560
void Vec24::Wrapper(void* a, void* b)
{
    void* local[2];
    local[0] = b;
    Other(a, local);
}

// @ 0x004b0490
B24* Vec24::Erase24(B24* param_2, B24* param_3)
{
    B24* out = (B24*)mpEnd;
    B24* local_14 = param_2;
    for (B24* local_10 = param_3; local_10 != out;
         local_10 = (B24*)((char*)local_10 + 0x18)) {
        local_14->b = local_10->b;
        local_14->a = local_10->a;
        local_14 = (B24*)((char*)local_14 + 0x18);
    }
    for (B24* local_1c = local_14; local_1c < (B24*)mpEnd;
         local_1c = (B24*)((char*)local_1c + 0x18)) {
    }
    mpEnd = mpEnd + ((char*)param_3 - (char*)param_2) / 0x18 * -0x18;
    return param_2;
}

// ---------------------------------------------------------------------------
// Shared allocator plumbing.
// ---------------------------------------------------------------------------
struct sp_vector_allocator { };

void* AllocatorAllocate(const void* allocator, unsigned size, unsigned align, unsigned flags); // 0x42dee0
void AllocatorDeallocate(void* p);                                                             // 0xf47380

// ---------------------------------------------------------------------------
// AutoRef: intrusive reference-counted handle (4-byte element).
// ---------------------------------------------------------------------------
struct AutoRef {
    void* mpObject;   // +0x0
    AutoRef* Set(void* v);
    void AddRef() { (*(void(__thiscall*)(void*))(*(void**)((char*)mpObject + 4)))(mpObject); }
    void Release() { (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)mpObject + 8)))(mpObject); }
    AutoRef() : mpObject(0) { }
    AutoRef(const AutoRef& other) : mpObject(other.mpObject) { if (mpObject != 0) AddRef(); }
    ~AutoRef() { if (mpObject != 0) Release(); }
};

// @ 0x004b09b0
AutoRef* AutoRef::Set(void* v)
{
    if (v != mpObject) {
        void* old = mpObject;
        if (v != 0) {
            (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)v + 4)))(v);
        }
        mpObject = v;
        if (old != 0) {
            (*(void(__thiscall*)(void*))(*(void**)((char*)*(void**)old + 8)))(old);
        }
    }
    return this;
}

void ConstructArray(AutoRef* dst, unsigned n, const AutoRef* value, bool tag);        // 0x4b2320
void UninitializedCopyRef(AutoRef** result, AutoRef* first, AutoRef* last, AutoRef* dst); // 0x4b2220
void FillRef(AutoRef* first, AutoRef* last, const AutoRef* value);                    // 0x4b22b0
void CopyRef(AutoRef* first, AutoRef* last, AutoRef* dst);                            // 0x4551e0

struct AutoRefVector {
    AutoRef* mpBegin;
    AutoRef* mpEnd;
    AutoRef* mpCapacity;
    sp_vector_allocator mAllocator;

    void DoInsertValues(AutoRef* position, unsigned n, const AutoRef* value);         // 0x4b0590
};

// @ 0x004b0590
void AutoRefVector::DoInsertValues(AutoRef* position, unsigned n, const AutoRef* value)
{
    if ((unsigned)(mpCapacity - mpEnd) < n) {
        unsigned nOldSize = (unsigned)(mpEnd - mpBegin);
        unsigned nGrow = nOldSize ? nOldSize * 2 : 1;
        unsigned nNewSize = nGrow > nOldSize + n ? nGrow : nOldSize + n;
        AutoRef* pNewData = nNewSize
            ? (AutoRef*)AllocatorAllocate(&mAllocator, nNewSize * sizeof(AutoRef), 4, 0) : 0;
        AutoRef* pNewPos = (AutoRef*)memcpy(pNewData, mpBegin,
            (unsigned)((char*)position - (char*)mpBegin)) + (position - mpBegin);
        ConstructArray(pNewPos, n, value, false);
        AutoRef* pNewEnd = (AutoRef*)memcpy(pNewPos + n, position,
            (unsigned)((char*)mpEnd - (char*)position)) + (mpEnd - position);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            AllocatorDeallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    } else if (n > 0) {
        AutoRef temp(*value);
        unsigned nExtra = (unsigned)(mpEnd - position);
        AutoRef* pOldEnd = mpEnd;
        if (n < nExtra) {
            AutoRef* result;
            UninitializedCopyRef(&result, mpEnd - n, mpEnd, mpEnd);
            mpEnd = pOldEnd + n;
            AutoRef* src = pOldEnd - n;
            AutoRef* dst = pOldEnd;
            while (src != position) {
                --src;
                --dst;
                dst->Set(src->mpObject);
            }
            FillRef(position, position + n, &temp);
        } else {
            ConstructArray(mpEnd, n - nExtra, &temp, false);
            mpEnd = pOldEnd + (n - nExtra);
            CopyRef(position, pOldEnd, mpEnd);
            mpEnd = mpEnd + nExtra;
            FillRef(position, pOldEnd, &temp);
        }
    }
}

// ---------------------------------------------------------------------------
// Float vector (4-byte elements, memcpy/memmove paths).
// ---------------------------------------------------------------------------
void UninitializedFillFloat(float** result, float* dst, unsigned n, const float* value);   // 0x42efc0
void UninitializedCopyFloat(float** result, const float* first, const float* last, float* dst); // 0x4d1240

struct FloatVector {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    sp_vector_allocator mAllocator;

    void DoInsertValues(float* position, unsigned n, const float* value);             // 0x4b0a10
};

// @ 0x004b0a10
void FloatVector::DoInsertValues(float* position, unsigned n, const float* value)
{
    if ((unsigned)(mpCapacity - mpEnd) < n) {
        unsigned nOldSize = (unsigned)(mpEnd - mpBegin);
        unsigned nGrow = nOldSize ? nOldSize * 2 : 1;
        unsigned nNewSize = nGrow > nOldSize + n ? nGrow : nOldSize + n;
        float* pNewData = nNewSize
            ? (float*)AllocatorAllocate(&mAllocator, nNewSize * sizeof(float), 4, 0) : 0;
        float* pNewPos = (float*)memcpy(pNewData, mpBegin,
            (unsigned)((char*)position - (char*)mpBegin)) + (position - mpBegin);
        {
            float* result;
            UninitializedFillFloat(&result, pNewPos, n, value);
        }
        float* pNewEnd = (float*)memcpy(pNewPos + n, position,
            (unsigned)((char*)mpEnd - (char*)position)) + (mpEnd - position);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            AllocatorDeallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    } else if (n > 0) {
        float temp = *value;
        unsigned nExtra = (unsigned)(mpEnd - position);
        float* pOldEnd = mpEnd;
        if (n < nExtra) {
            float* result;
            UninitializedCopyFloat(&result, mpEnd - n, mpEnd, mpEnd);
            mpEnd = pOldEnd + n;
            memmove(position + n, position, (unsigned)((char*)(pOldEnd - n) - (char*)position));
            for (float* p = position; p != position + n; ++p)
                *p = temp;
        } else {
            float* result;
            UninitializedFillFloat(&result, mpEnd, n - nExtra, &temp);
            mpEnd = pOldEnd + (n - nExtra);
            float* result2;
            UninitializedCopyFloat(&result2, position, pOldEnd, mpEnd);
            mpEnd = mpEnd + nExtra;
            for (float* p = position; p != pOldEnd; ++p)
                *p = temp;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x1d8-byte record vector (assignment operator).
// ---------------------------------------------------------------------------
struct Elem1d8 { unsigned int mData[0x76]; };

void UninitializedCopy24(const Elem1d8* first, const Elem1d8* last, Elem1d8* dst);       // 0x4b1760

struct Record1d8Vector {
    Elem1d8* mpBegin;
    Elem1d8* mpEnd;
    Elem1d8* mpCapacity;

    Elem1d8* DoAllocateAndCopy(int n, const Elem1d8* first, const Elem1d8* last);        // 0x4b1f50
    Record1d8Vector& Assign(const Record1d8Vector& other);                               // 0x4b0ef0
};

// @ 0x004b0ef0
Record1d8Vector& Record1d8Vector::Assign(const Record1d8Vector& other)
{
    if (this != &other) {
        int n = (int)((other.mpEnd - other.mpBegin) / (int)sizeof(Elem1d8));
        if ((unsigned)((mpCapacity - mpBegin) / (int)sizeof(Elem1d8)) < (unsigned)n) {
            Elem1d8* pNewData = DoAllocateAndCopy(n, other.mpBegin, other.mpEnd);
            for (Elem1d8* p = mpBegin; p < mpEnd; ++p) {
            }
            if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
                AllocatorDeallocate(mpBegin);
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if ((unsigned)((mpEnd - mpBegin) / (int)sizeof(Elem1d8)) < (unsigned)n) {
            Elem1d8* dst = mpBegin;
            const Elem1d8* src = other.mpBegin;
            const Elem1d8* srcEnd = other.mpBegin + (mpEnd - mpBegin) / (int)sizeof(Elem1d8);
            while (src != srcEnd) {
                *dst = *src;
                ++dst;
                ++src;
            }
            UninitializedCopy24(srcEnd, other.mpEnd, mpEnd);
        } else {
            Elem1d8* dst = mpBegin;
            for (const Elem1d8* src = other.mpBegin; src != other.mpEnd; ++src) {
                *dst = *src;
                ++dst;
            }
            for (Elem1d8* p = dst; p < mpEnd; ++p) {
            }
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}
