// w1g1 slice s00514910 -- continuation of the deque<Elem48> TU (see s00513930):
// DequeBase subarray allocation, DequeIterator set/--, a 7-dword fill and a range
// helper, plus two large deque insert routines (partial).
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }
extern "C" void* __cdecl memcpy(void*, const void*, uint32_t);
void* EASTL_Allocate(void* alloc, unsigned int n, unsigned int align, unsigned int offset);  // 0x0042dee0

enum { kSubarraySize = 4 };

// ---------------------------------------------------------------------------
// element / deque types (same as s00513930)
// ---------------------------------------------------------------------------
struct Vector3 { float x, y, z; Vector3() {} Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; } };
struct Vector2f { float x, y; Vector2f() {} Vector2f(const Vector2f& v) { x = v.x; y = v.y; } };
struct Tri3 { uint32_t a, b, c; };
struct Bytes3 { uint8_t a, b, c; };
struct Elem48 {
    uint32_t mId;
    Vector3 mA, mB, mC;
    Vector2f mUV;
    Tri3 mTri;
    uint32_t m3c, m40;
    Bytes3 m44;
    uint8_t m47;
    Elem48() {}
};

template <typename T>
struct DequeIterator {
    T* mpCurrent;
    T* mpBegin;
    T* mpEnd;
    T** mpCurrentArrayPtr;
    struct Decrement {};
    DequeIterator& operator--();
    void SetSubarray(T** pCurrentArrayPtr);
};

// @ 0x00515170
template <typename T>
void DequeIterator<T>::SetSubarray(T** pCurrentArrayPtr)
{
    mpCurrentArrayPtr = pCurrentArrayPtr;
    mpBegin = *pCurrentArrayPtr;
    mpEnd = mpBegin + kSubarraySize;
}

// @ 0x00515100
template <typename T>
DequeIterator<T>& DequeIterator<T>::operator--()
{
    if (mpCurrent == mpBegin) {
        --mpCurrentArrayPtr;
        mpBegin = *mpCurrentArrayPtr;
        mpEnd = mpBegin + kSubarraySize;
        mpCurrent = mpEnd;
    }
    --mpCurrent;
    return *this;
}

template DequeIterator<Elem48>& DequeIterator<Elem48>::operator--();
template void DequeIterator<Elem48>::SetSubarray(Elem48**);

namespace eastl {
template <typename T>
inline const T& max(const T& a, const T& b) { return (a < b) ? b : a; }
}

template <typename T>
struct DequeBase {
    T** mpPtrArray;
    uint32_t mnPtrArraySize;     // +0x04
    DequeIterator<T> mItBegin;   // +0x08
    DequeIterator<T> mItEnd;     // +0x18
    uint32_t mAlloc;             // +0x28
    T* DoAllocateSubarray();
    T** DoAllocatePtrArray(uint32_t n);   // @ 0x0056a240
    void Construct(uint32_t n);      // @ 0x00515000
};

// @ 0x00514e10
template <typename T>
T* DequeBase<T>::DoAllocateSubarray()
{
    return (T*)EASTL_Allocate(&mAlloc, kSubarraySize * sizeof(T), 4, 0);
}
template Elem48* DequeBase<Elem48>::DoAllocateSubarray();

// ---------------------------------------------------------------------------
// @ 0x005155f0  uninitialized_fill_n over 7-dword elements (result via out-param)
// ---------------------------------------------------------------------------
void** Fill7(void** out, void* dst, int n, void* value)
{
    void* d = dst;
    while (n != 0) {
        const uint32_t* s = (const uint32_t*)value;
        uint32_t* p = (uint32_t*)d;
        for (int i = 0; i < 7; ++i)
            p[i] = s[i];
        d = (char*)d + 0x1c;
        --n;
    }
    *out = d;
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00515650  range insert helper (result via out-param)
// ---------------------------------------------------------------------------
void** RangeInsertOut(void** out, void* first, int last, void* dst)
{
    void* d = dst;
    int l = last;
    void* f = first;
    bool b = true;
    *out = (char*)memcpy(d, f, (uint32_t)(l - (int)f)) + ((l - (int)f) / 0x1c) * 0x1c;
    return out;
}

// ---------------------------------------------------------------------------
// vector insert routines: 0x00514910 is the copy-insert of 0x1c-byte elements,
// 0x005151b0 the byte-strided Insert(position, n, value).
// ---------------------------------------------------------------------------
extern "C" void* __cdecl memmove(void*, const void*, uint32_t);
extern "C" void* __cdecl memset(void*, int, uint32_t);
void FreeRawBlock(void* p);                                     // 0x00f47380

// 7-dword element (0x1c bytes, same shape as the Fill7 target).
struct Elem28 {
    uint32_t m[7];
};

// memcpy of [first, last) to dst; returns dst advanced by the element count.
template <typename T>
inline T* CopyRange(T* dst, const T* first, const T* last)
{
    const uint32_t len = (uint32_t)((const char*)last - (const char*)first);
    memcpy(dst, first, len);
    return (T*)((char*)dst + (len / sizeof(T)) * sizeof(T));
}

struct Vec28 {
    Elem28* mpBegin;
    Elem28* mpEnd;
    Elem28* mpCap;
    void*   mAlloc;             // +0x0c
    void DoInsertValues(Elem28* position, uint32_t n, const Elem28& value);   // 0x00514910
};

struct ByteVec {
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCap;
    void*    mAlloc;            // +0x0c
    void Insert(uint8_t* position, uint32_t n, const uint8_t& value);        // 0x005151b0
};

// @ 0x00515000
template <typename T>
void DequeBase<T>::Construct(uint32_t n)
{
    const uint32_t subarrayCount = (n / kSubarraySize) + 1;
    mnPtrArraySize = eastl::max<uint32_t>(8, subarrayCount + 2);
    mpPtrArray = DoAllocatePtrArray(mnPtrArraySize);
    T** pPtrArrayBegin = mpPtrArray + ((mnPtrArraySize - subarrayCount) >> 1);
    T** pPtrArrayEnd = pPtrArrayBegin + subarrayCount;
    for (T** pPtrArray = pPtrArrayBegin; pPtrArray < pPtrArrayEnd; ++pPtrArray)
        *pPtrArray = DoAllocateSubarray();
    mItBegin.SetSubarray(pPtrArrayBegin);
    mItBegin.mpCurrent = mItBegin.mpBegin;
    mItEnd.SetSubarray(pPtrArrayEnd - 1);
    mItEnd.mpCurrent = mItEnd.mpBegin + (n % kSubarraySize);
}
template void DequeBase<Elem48>::Construct(uint32_t);

// @ 0x00514910
void Vec28::DoInsertValues(Elem28* position, uint32_t n, const Elem28& value)
{
    const uint32_t count = (uint32_t)((const char*)mpEnd - (const char*)mpBegin) / sizeof(Elem28);
    if (n > count) {
        const uint32_t newCap = count ? count * 2 : 1;
        const uint32_t newCount = (count + n < newCap) ? newCap : (count + n);
        Elem28* newBegin = newCount ? (Elem28*)EASTL_Allocate(&mAlloc, newCount * sizeof(Elem28), 4, 0) : 0;
        Elem28* newPos = CopyRange(newBegin, mpBegin, position);
        void* out;
        Fill7(&out, newPos, (int)n, (void*)&value);
        Elem28* newEnd = CopyRange(newPos + n, position, mpEnd);
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            FreeRawBlock(mpBegin);
        mpBegin = newBegin;
        mpEnd = newEnd;
        mpCap = (Elem28*)((char*)newBegin + newCount * sizeof(Elem28));
        return;
    }
    if (n == 0)
        return;

    Elem28 valueSaved = value;
    const uint32_t nAfter = (uint32_t)((const char*)mpEnd - (const char*)position) / sizeof(Elem28);
    Elem28* pOldEnd = mpEnd;
    if (n < nAfter) {
        Elem28* p = pOldEnd - n;
        CopyRange(pOldEnd, p, pOldEnd);
        mpEnd = pOldEnd + n;
        memmove(position + n, position, (uint32_t)((const char*)p - (const char*)position));
        for (Elem28* q = position; q != position + n; ++q)
            *q = valueSaved;
    } else {
        const uint32_t nExtra = n - nAfter;
        void* out;
        Fill7(&out, mpEnd, (int)nExtra, (void*)&valueSaved);
        mpEnd += nExtra;
        CopyRange(mpEnd, position, pOldEnd);
        mpEnd = pOldEnd + n;
        for (Elem28* q = position; q != pOldEnd; ++q)
            *q = valueSaved;
    }
}

// @ 0x005151b0
void ByteVec::Insert(uint8_t* position, uint32_t n, const uint8_t& value)
{
    const uint32_t count = (uint32_t)(mpEnd - mpBegin);
    if (n > count) {
        const uint32_t newCap = count ? count * 2 : 1;
        const uint32_t newCount = (count + n < newCap) ? newCap : (count + n);
        uint8_t* newBegin = newCount ? (uint8_t*)EASTL_Allocate(&mAlloc, newCount, 1, 0) : 0;
        uint8_t* newPos = CopyRange(newBegin, mpBegin, position);
        memset(newPos, value, n);
        uint8_t* newEnd = CopyRange(newPos + n, position, mpEnd);
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            FreeRawBlock(mpBegin);
        mpBegin = newBegin;
        mpEnd = newEnd;
        mpCap = newBegin + newCount;
        return;
    }
    if (n == 0)
        return;

    const uint8_t valueSaved = value;
    const uint32_t nAfter = (uint32_t)(mpEnd - position);
    uint8_t* pOldEnd = mpEnd;
    if (n < nAfter) {
        uint8_t* p = pOldEnd - n;
        CopyRange(pOldEnd, p, pOldEnd);
        mpEnd = pOldEnd + n;
        memmove(position + n, position, (uint32_t)(p - position));
        memset(position, valueSaved, n);
    } else {
        const uint32_t nExtra = n - nAfter;
        memset(mpEnd, valueSaved, nExtra);
        mpEnd += nExtra;
        CopyRange(mpEnd, position, pOldEnd);
        mpEnd = pOldEnd + n;
        memset(position, valueSaved, (uint32_t)(pOldEnd - position));
    }
}
