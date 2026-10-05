// w1g1 slice s00514910 -- continuation of the deque<Elem48> TU (see s00513930):
// DequeBase subarray allocation, DequeIterator set/--, a 7-dword fill and a range
// helper, plus two large deque insert routines (partial).
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }
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

template <typename T>
struct DequeBase {
    T** mpPtrArray;
    int mnPtrArraySize;
    DequeIterator<T> mItBegin;   // +0x08
    DequeIterator<T> mItEnd;     // +0x18
    uint32_t mAlloc;             // +0x28
    T* DoAllocateSubarray();
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
void* RangeInsertHelper(void* self, void* first, void* last, void* dst);

void** RangeInsertOut(void** out, void* first, int last, void* dst)
{
    void* p = RangeInsertHelper(dst, first, (void*)last, dst);
    *out = (char*)p + ((last - (int)first) / 0x1c) * 0x1c;
    return out;
}

// ---------------------------------------------------------------------------
// large deque routines -- partial
// ---------------------------------------------------------------------------
struct BigDequeBase {
    void* pad[0x28 / 4];
    void DoInsertValues(void* position, uint32_t n, void* value);   // 0x00514910
    void Construct(uint32_t n);                                     // 0x00515000
    void Insert(void* position, uint32_t n, char* value);           // 0x005151b0
};

// @ 0x00515000
void BigDequeBase::Construct(uint32_t n)
{
    // PARTIAL (246-byte body not fully reproduced).
    (void)n;
}

// @ 0x00514910
void BigDequeBase::DoInsertValues(void* position, uint32_t n, void* value)
{
    // PARTIAL (1279-byte body not reproduced).
    (void)position; (void)n; (void)value;
}

// @ 0x005151b0
void BigDequeBase::Insert(void* position, uint32_t n, char* value)
{
    // PARTIAL (1088-byte body not reproduced).
    (void)position; (void)n; (void)value;
}
