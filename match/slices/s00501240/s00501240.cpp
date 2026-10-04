// EASTL vector / fixed_vector instantiations (unoptimized module: /Od /Ob1 /MD /Gy /TP, no /EHsc).
// Element types are unnamed in the retail binary; they are named here by size (E30, E48, Ed8).
#include "types.h"
#include <string.h>

inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}


template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}

namespace eastl {

typedef unsigned int size_t;
typedef int ptrdiff_t;

void* __cdecl allocate_memory(void* allocator, size_t n, size_t alignment, size_t alignmentOffset); // 0x0042dee0

struct allocator {};

// fixed_vector_allocator: overflow allocator + pool begin (8 bytes)
struct fixed_vector_allocator {
    allocator mOverflowAllocator;
    void* mpPoolBegin;
    fixed_vector_allocator(void* pNodeBuffer) : mpPoolBegin(pNodeBuffer) {}
    fixed_vector_allocator(const fixed_vector_allocator& x) { mpPoolBegin = x.mpPoolBegin; }
};

// uninitialized/copy helpers -----------------------------------------------------------------
template <typename T>
inline T* copy_trivial(const T* first, const T* last, T* result)
{
    const bool bInputIsGenericIterator = false;
    const bool bOutputIsGenericIterator = false;
    const bool bHasTrivialCopy = true;
    return (T*)memcpy(result, first, (size_t)((uint32_t)last - (uint32_t)first)) + (last - first);
}

template <typename T>
inline T* copy_memcpy(const T* first, const T* last, T* result)
{
    return (T*)memcpy(result, first, (size_t)((uint32_t)last - (uint32_t)first)) + (last - first);
}

template <typename T>
inline T* uninitialized_copy_trivial(T* first, T* last, T* result)
{
    const bool bHasTrivialRelocate = true;
    T* const pEnd = copy_memcpy(first, last, result);
    const bool bHasTrivialCopy = true;
    return pEnd;
}

template <typename T>
inline T* copy_backward_trivial(T* first, T* last, T* resultEnd)
{
    const bool bInputIsGenericIterator = false;
    const bool bOutputIsGenericIterator = false;
    const bool bHasTrivialCopy = true;
    return (T*)memmove(resultEnd - (last - first), first, (size_t)((uint32_t)last - (uint32_t)first));
}

template <typename T>
inline T* do_copy_generic(T* first, T* last, T* result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}

// Same loop for element types whose operator= is an out-of-line call: one extra (unused) dword slot.
template <int kSlots, typename T>
inline T* do_copy_assign(T* first, T* last, T* result)
{
    ScratchSlots<kSlots>();
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}

template <int kSlots, typename T>
inline T* copy_assign(T* first, T* last, T* result)
{
    const bool bInputIsGenericIterator = false;
    const bool bOutputIsGenericIterator = false;
    const bool bHasTrivialCopy = false;
    return do_copy_assign<kSlots>(first, last, result);
}

template <typename T>
inline T* copy_generic(T* first, T* last, T* result)
{
    const bool bInputIsGenericIterator = false;
    const bool bOutputIsGenericIterator = false;
    const bool bHasTrivialCopy = false;
    return do_copy_generic(first, last, result);
}

template <typename T>
__forceinline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}

template <typename T>
__forceinline void destruct_elems(T* first, T* last)
{
    for (; first < last; ++first)
        first->ScalarDtor(0);
}

template <typename T>
inline void destruct_trivial(T* first, T* last)
{
    for (; first < last; ++first)
        ;
}

} // namespace eastl


// ---- 4-byte pointer-like element ----
struct PtrElem {
    void* p;
};

// fixed_vector<PtrElem, 8>: 0x14-byte vector header, 0x20-byte buffer at +0x18
struct FixedVec8 {
    PtrElem* mpBegin;
    PtrElem* mpEnd;
    PtrElem* mpCapacity;
    eastl::fixed_vector_allocator mAllocator;
    uint32_t mPad;
    PtrElem mBuffer[8];

    FixedVec8();                     // 0x00533360
    void DoFreeBase();               // 0x004c0b80 (~VectorBase)
    __forceinline void Destroy()
    {
        ScratchSlots<3>();
        for (PtrElem* p = mpBegin; p < mpEnd; ++p)
            ;
        DoFreeBase();
    }
    __forceinline ~FixedVec8() { Destroy(); }
};

// 0x48-byte element: 12 bytes of data + fixed_vector
struct E48 {
    uint32_t a, b, c;
    FixedVec8 mList;
    uint32_t d;
    E48& operator=(const E48& x);    // 0x00503930
    __forceinline ~E48() {}
    // body of the compiler's inline scalar deleting destructor (what `p->~E48()` expands to)
    __forceinline void ScalarDtor(unsigned int flags)
    {
        mList.Destroy();
        if (flags & 1)
            operator delete(this);
    }
};

// 0x54-byte element (Transform)
struct TransformData {
    uint32_t data[21];
    TransformData();                 // 0x00409930
};
struct Transform {
    TransformData mData;
    Transform& operator=(const Transform& x);   // 0x005039c0
};

// 0xd8-byte element: 0x10 bytes of data + fixed_vector + more
struct Ed8 {
    uint32_t a, b, c, d;
    FixedVec8 mList;
    uint32_t rest[(0xd8 - 0x10 - 0x38) / 4];
    Ed8();                           // 0x00501760
    Ed8(const Ed8& x);               // 0x00502f60
    Ed8& operator=(const Ed8& x);    // 0x00503a50
    __forceinline ~Ed8() {}
    __forceinline void ScalarDtor(unsigned int flags)
    {
        mList.Destroy();
        if (flags & 1)
            operator delete(this);
    }
};

// 0x30-byte POD element
struct E30 { uint32_t v[12]; };

struct Vec4f {
    float x, y, z, w;
    Vec4f& operator=(const Vec4f& o);
};

template <typename T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;

    void DoInsertValues(T* position, unsigned int n, const T& value);
    void DoInsertValue(T* position, const T& value);
    void insert(T* position, unsigned int n, const T& value) { DoInsertValues(position, n, value); }
    T* erase(T* first, T* last);
    void resize(unsigned int n);
    void reserve(unsigned int n);
    void push_back(const T& value);
    template <int kSlots> void clear() { ScratchSlots<kSlots>(); erase(mpBegin, mpEnd); }

    unsigned int GetNewCapacity(unsigned int currentCapacity)
    {
        return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
    }
    T* DoAllocate(unsigned int n)
    {
        return n ? (T*)eastl::allocate_memory(&mAllocator, n * sizeof(T), __alignof(T), 0) : 0;
    }
    void DoFree(T* p, unsigned int n)
    {
        if (p) {
            if (((int*)p)[-1]) {
                void* q = p;
                operator delete(q);
            }
        }
    }
};


// @ 0x00501240
struct Owner501240 {
    uint8_t pad[0x7c];
    vector<double> mDoubles;    // +0x7c
    uint8_t pad2[0x90 - 0x8c];
    vector<E30> mItems;         // +0x90
    void Clear();
};
void Owner501240::Clear()
{
    ScratchSlots<1>();
    mItems.clear<5>();
    mDoubles.clear<4>();
}

// @ 0x00501290
Vec4f& Vec4f::operator=(const Vec4f& o)
{
    x = o.x;
    y = o.y;
    z = o.z;
    w = o.w;
    return *this;
}

template <typename T, typename Allocator>
struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    VectorBase(const Allocator& allocator) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator) {}
};

// fixed_vector<uint32_t, 256>
struct FixedVec256 : VectorBase<uint32_t, eastl::fixed_vector_allocator> {
    uint32_t mPad;
    uint32_t mBuffer[256];
    void resize(unsigned int n);     // 0x00454b80
    FixedVec256(unsigned int n);
};

// @ 0x005012d0
FixedVec256::FixedVec256(unsigned int n)
    : VectorBase<uint32_t, eastl::fixed_vector_allocator>(eastl::fixed_vector_allocator(mBuffer))
{
    ScratchSlots<7>();
    mpBegin = mpEnd = &mBuffer[0];
    mpCapacity = mpBegin + 256;
    resize(n);
}

// @ 0x00501350 resize@?$vector@UE48
template <> void vector<E48>::resize(unsigned int n)
{
    if (n > (unsigned int)(mpEnd - mpBegin)) {
        ScratchSlots<3>();
        insert(mpEnd, n - (unsigned int)(mpEnd - mpBegin), E48());
        ScratchSlots<17>();
    } else
        erase(mpBegin + n, mpEnd);
}

// @ 0x00501430 resize@?$vector@UTransform
template <> void vector<Transform>::resize(unsigned int n)
{
    if (n > (unsigned int)(mpEnd - mpBegin)) {
        ScratchSlots<2>();
        insert(mpEnd, n - (unsigned int)(mpEnd - mpBegin), Transform());
        ScratchSlots<7>();
    } else
        erase(mpBegin + n, mpEnd);
}

// @ 0x005014e0 resize@?$vector@UEd8
template <> void vector<Ed8>::resize(unsigned int n)
{
    ScratchSlots<1>();
    if (n > (unsigned int)(mpEnd - mpBegin)) {
        ScratchSlots<3>();
        insert(mpEnd, n - (unsigned int)(mpEnd - mpBegin), Ed8());
        ScratchSlots<17>();
    } else
        erase(mpBegin + n, mpEnd);
}

Ed8* uninitialized_move_ptr(Ed8* first, Ed8* last, Ed8* dest);   // 0x00501a10

// @ 0x005015f0
template <> void vector<Ed8>::reserve(unsigned int n)
{
    ScratchSlots<1>();
    if (n > (unsigned int)(mpCapacity - mpBegin)) {
        ScratchSlots<5>();
        Ed8* const pNewData = DoAllocate(n);
        uninitialized_move_ptr(mpBegin, mpEnd, pNewData);
        ScratchSlots<5>();
        DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
        const eastl::ptrdiff_t nPrevSize = mpEnd - mpBegin;
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = mpBegin + n;
    }
}

// @ 0x005016f0
template <> void vector<double>::push_back(const double& value)
{
    if (mpEnd < mpCapacity)
        ::new(mpEnd++) double(value);
    else
        DoInsertValue(mpEnd, value);
}

// @ 0x00501760 ??0Ed8
Ed8::Ed8()
{
    ScratchSlots<3>();
}

// @ 0x00501780
template <> E48* vector<E48>::erase(E48* first, E48* last)
{
    E48* const position = eastl::copy_assign<5>(last, mpEnd, first);
    eastl::destruct_elems(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// @ 0x00501870
template <> Transform* vector<Transform>::erase(Transform* first, Transform* last)
{
    Transform* const position = eastl::copy_assign<1>(last, mpEnd, first);
    eastl::destruct_trivial(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// @ 0x00501910
template <> Ed8* vector<Ed8>::erase(Ed8* first, Ed8* last)
{
    Ed8* const position = eastl::copy_assign<5>(last, mpEnd, first);
    eastl::destruct_elems(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

void destruct_range(Ed8* first, Ed8* last, Ed8* dest);   // 0x005033f0

template <typename T>
inline void uninitialized_copy_loop(T* first, T* last, T*& currentDest)
{
    for (; first != last; ++first, ++currentDest)
        ::new(&*currentDest) T(*first);
}

template <int kSlots, typename T>
inline T* uninitialized_copy_impl(T* first, T* last, T* dest)
{
    ScratchSlots<kSlots>();
    T* currentDest(dest);
    uninitialized_copy_loop(first, last, currentDest);
    return currentDest;
}

// @ 0x00501a10
template <int kSlots>
inline void destruct_wrap(Ed8* first, Ed8* last, Ed8* dest)
{
    ScratchSlots<kSlots>();
    const bool bHasTrivialDestructor = false;
    destruct_range(first, last, dest);
}

Ed8* uninitialized_move_ptr(Ed8* first, Ed8* last, Ed8* dest)
{
    ScratchSlots<1>();
    const bool bHasTrivialCopy = false;
    Ed8* const result = uninitialized_copy_impl<4>(first, last, dest);
    ScratchSlots<2>();
    destruct_wrap<4>(first, last, dest);
    return result;
}

// @ 0x00501aa0
template <> double* vector<double>::erase(double* first, double* last)
{
    double* const position = eastl::copy_trivial(last, mpEnd, first);
    eastl::destruct_trivial(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// @ 0x00501b30 DoInsertValue@?$vector@N
template <> void vector<double>::DoInsertValue(double* position, const double& value)
{
    if (mpEnd != mpCapacity) {
        const double* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) double(*(mpEnd - 1));
        eastl::copy_backward_trivial(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const unsigned int nPrevSize = (unsigned int)(mpEnd - mpBegin);
        const unsigned int nNewSize = GetNewCapacity(nPrevSize);
        double* const pNewData = DoAllocate(nNewSize);
        double* pNewEnd = eastl::uninitialized_copy_trivial(mpBegin, position, pNewData);
        ::new(pNewEnd) double(value);
        pNewEnd = eastl::uninitialized_copy_trivial(position, mpEnd, ++pNewEnd);
        DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00501d70
template <> E30* vector<E30>::erase(E30* first, E30* last)
{
    E30* const position = eastl::copy_generic(last, mpEnd, first);
    eastl::destruct_trivial(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// @ 0x00501e20
struct Holder501e20 {
    uint32_t a, b;
    struct Inner { void Destroy(); } mInner;   // +8, 0x005658b0
    void Destroy();
};
void Holder501e20::Destroy()
{
    mInner.Destroy();
}

// deque-like push_back (4-byte elements, end-of-subarray check)
struct Deque4 {
    uint32_t pad[6];
    uint32_t* mItEndCur;      // +0x18
    uint32_t* mItEndFirst;    // +0x1c
    uint32_t* mItEndLast;     // +0x20
    void DoPushBack(const uint32_t& value);   // 0x00502dd0
    void push_back(const uint32_t& value);
};

// @ 0x00501e40
void Deque4::push_back(const uint32_t& value)
{
    if ((mItEndCur + 1) != mItEndLast)
        ::new(mItEndCur++) uint32_t(value);
    else
        DoPushBack(value);
}

struct Deque4b {
    uint32_t pad[2];
    uint32_t* mItEndCur;      // +0x08
    uint32_t* mItEndFirst;    // +0x0c
    uint32_t* mItEndLast;     // +0x10
    void DoPushBack();        // 0x00502e70
    void push_back();
};

// @ 0x00501eb0
void Deque4b::push_back()
{
    if ((mItEndCur + 1) != mItEndLast)
        ++mItEndCur;
    else
        DoPushBack();
}

struct DequeBase {
    uint32_t** mpPtrArray;     // +0
    uint32_t mnPtrArraySize;   // +4
    uint32_t pad[3];
    uint32_t** mItBeginNode;   // +0x14
    uint32_t pad2[3];
    uint32_t** mItEndNode;     // +0x24
    void DoFreeSubarrays(uint32_t** pBegin, uint32_t** pEnd);   // 0x00569290
    void DoFreePtrArray(uint32_t** pp, uint32_t n);              // 0x00502eb0
    void Destroy();
};

// @ 0x00501ef0
void DequeBase::Destroy()
{
    if (mpPtrArray) {
        DoFreeSubarrays(mItBeginNode, mItEndNode + 1);
        DoFreePtrArray(mpPtrArray, mnPtrArraySize);
    }
}
