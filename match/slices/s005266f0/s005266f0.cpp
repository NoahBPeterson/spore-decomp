// nSPSkinner skin-mesh EASTL vector instantiations (unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE).
// Functor/allocator are the empty sp_vector_allocator; out-of-line helpers cl declined to inline are
// declared extern and called at their original shapes.
#include "types.h"

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}

extern "C" void* __cdecl memcpy(void*, const void*, uint32_t);
#pragma intrinsic(memcpy)

inline void* operator new(unsigned int, void* p) { return p; }

struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
};

void* EA_Allocate(void* allocator, uint32_t n, uint32_t align, uint32_t offset);  // 0x0042dee0
void  EA_Free(void* p);                                                            // 0x00f47380

// ---------------------------------------------------------------- refcounted element
struct IRefObj {
    virtual void AddRef();
    virtual void Release();
};
struct PooledObj {
    uint32_t pad00[0x13];
    int mRefCount;              // +0x4c
    void AddRef() { mRefCount++; }
};

struct Vec2f {
    float x, y;
    Vec2f() {}
    Vec2f(const Vec2f& o) { x = o.x; y = o.y; }
};
struct Vec3f {
    float x, y, z;
    Vec3f() {}
    Vec3f(const Vec3f& o) { x = o.x; y = o.y; z = o.z; }
};

struct ObjPtr {
    IRefObj* mp;
    ObjPtr() : mp(0) {}
    ObjPtr(const ObjPtr& o) : mp(o.mp) { if (mp) mp->AddRef(); }
};
struct PoolPtr2 {
    PooledObj* mp;
    PoolPtr2() : mp(0) {}
    PoolPtr2(const PoolPtr2& o) : mp(o.mp) { if (mp) mp->AddRef(); }
};

struct Elem38 {                 // 0x38 bytes
    uint32_t m00;               // +0x00
    Vec2f v04;                  // +0x04
    Vec3f v0c;                  // +0x0c
    float v18;                  // +0x18
    uint32_t m1c, m20, m24, m28;
    ObjPtr mpObj;               // +0x2c
    uint32_t m30;               // +0x30
    PoolPtr2 mpPooled;          // +0x34
    Elem38() {}
    Elem38(const Elem38& x);            // 0x00527440
    Elem38& operator=(const Elem38&);   // 0x005218e0
    ~Elem38();                          // 0x00526660
};

// @ 0x00527440
Elem38::Elem38(const Elem38& x)
    : m00(x.m00), v04(x.v04), v0c(x.v0c), v18(x.v18),
      m1c(x.m1c), m20(x.m20), m24(x.m24), m28(x.m28),
      mpObj(x.mpObj), m30(x.m30), mpPooled(x.mpPooled)
{
}

// helpers instantiated out of line by the original build
Elem38* UninitCopy38(Elem38* first, Elem38* last, Elem38* dest);      // 0x005279c0
Elem38* AllocAndCopy38(uint32_t n, Elem38* first, Elem38* last);      // 0x00527b10
void    UninitCopyTail38(Elem38* first, Elem38* last, Elem38* dest);  // 0x00527a70
void    FillN38(Elem38* dest, uint32_t n, const Elem38* value);       // 0x00528820

template <typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    uint32_t capacity() const { return (uint32_t)(mpCapacity - mpBegin); }
    T* DoAllocate(uint32_t n) { return n ? (T*)EA_Allocate(&mAllocator, n * sizeof(T), 4, 0) : 0; }
    void DoFree(T* p, uint32_t) { if (p && ((uint32_t*)p)[-1]) { void* q = p; EA_Free(q); } }
};

template <typename T> inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}

template <class In, class Out> __forceinline Out copy_impl(In first, In last, Out result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}
template <class In, class Out> __forceinline Out copy(In first, In last, Out result)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = false;
    return copy_impl(first, last, result);
}
template <class Bi1, class Bi2> __forceinline Bi2 copy_backward_impl(Bi1 first, Bi1 last, Bi2 result)
{
    while (last != first)
        *--result = *--last;
    return result;
}
template <class Bi1, class Bi2> __forceinline Bi2 copy_backward(Bi1 first, Bi1 last, Bi2 result)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = false;
    return copy_backward_impl(first, last, result);
}

struct VectorElem38 : VectorBase<Elem38> {
    typedef Elem38 value_type;
    typedef uint32_t size_type;
    Elem38* erase(Elem38* first, Elem38* last);                                  // 0x005266f0
    void DoInsertValue(Elem38* position, const Elem38& value);                   // 0x005267c0
    void DoInsertValues(Elem38* position, size_type n, const Elem38& value);     // 0x00527570
    void insert(Elem38* position, size_type n, const Elem38& value) { DoInsertValues(position, n, value); }
    VectorElem38& operator=(const VectorElem38& x);
};

// @ 0x005266f0
Elem38* VectorElem38::erase(Elem38* first, Elem38* last)
{
    ScratchSlots<8>();
    Elem38* const position = copy(last, mpEnd, first);
    destruct(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// @ 0x005267c0
void VectorElem38::DoInsertValue(Elem38* position, const Elem38& value)
{
    if (mpEnd != mpCapacity) {
        const Elem38* pValue = &value;
        if (pValue >= position && pValue < mpEnd)
            ++pValue;
        ::new (mpEnd) Elem38(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        Elem38* const pNewData = DoAllocate(nNewSize);
        Elem38* pNewEnd = UninitCopy38(mpBegin, position, pNewData);
        if (pNewEnd)
            ::new (pNewEnd) Elem38(value);
        ++pNewEnd;
        pNewEnd = UninitCopy38(position, mpEnd, pNewEnd);
        if (mpBegin && ((uint32_t*)mpBegin)[-1]) {
            void* q = mpBegin;
            EA_Free(q);
        }
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00527570
void VectorElem38::DoInsertValues(Elem38* position, size_type n, const Elem38& value)
{
    if (n == 0)
        return;
    Elem38 valueSaved(value);
    size_type nAfter = (size_type)(mpEnd - position);
    if ((size_type)(mpCapacity - mpEnd) >= n) {
        if (nAfter > n) {
            for (size_type i = 0; i < n; ++i)
                ::new (mpEnd + i) Elem38(mpEnd[nAfter - n + i]);
            for (Elem38* p = mpEnd - n - 1; p >= position; --p)
                p[n] = *p;
            for (size_type i = 0; i < n; ++i)
                position[i] = valueSaved;
            mpEnd += n;
        } else {
            for (size_type i = 0; i < n - nAfter; ++i)
                ::new (mpEnd + i) Elem38(valueSaved);
            for (Elem38* p = mpEnd - 1; p >= position; --p)
                p[n] = *p;
            for (size_type i = 0; i < nAfter; ++i)
                position[i] = valueSaved;
            mpEnd += n;
        }
    } else {
        size_type nOldSize = (size_type)(mpEnd - mpBegin);
        size_type nNewSize = nOldSize + n;
        if (nOldSize > 0 && nNewSize < 2 * nOldSize)
            nNewSize = 2 * nOldSize;
        Elem38* pNewData = DoAllocate(nNewSize);
        Elem38* pNewEnd = UninitCopy38(mpBegin, position, pNewData);
        for (size_type i = 0; i < n; ++i)
            ::new (pNewEnd + i) Elem38(valueSaved);
        pNewEnd += n;
        pNewEnd = UninitCopy38(position, mpEnd, pNewEnd);
        destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------- 0x18-byte element vector
struct Elem18 {
    uint32_t data[6];
};
Elem18* UninitCopy18(Elem18* first, Elem18* last, Elem18* dest);      // 0x00527b70
Elem18* AllocAndCopy18(uint32_t n, Elem18* first, Elem18* last);      // 0x00527c10

struct VectorElem18 : VectorBase<Elem18> {
    typedef Elem18 value_type;
    typedef uint32_t size_type;
    VectorElem18& operator=(const VectorElem18& x);
};

// @ 0x00526e70
VectorElem18& VectorElem18::operator=(const VectorElem18& x)
{
    if (this != &x) {
        uint32_t n = x.size();
        if (n > capacity()) {
            Elem18* pNewData = AllocAndCopy18(n, x.mpBegin, x.mpEnd);
            destruct(mpBegin, mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpCapacity = pNewData + n;
        } else if (n > size()) {
            memcpy(mpBegin, x.mpBegin, size() * sizeof(Elem18));
            UninitCopy18(x.mpBegin + size(), x.mpEnd, mpEnd);
        } else {
            Elem18* pNewEnd = (Elem18*)memcpy(mpBegin, x.mpBegin, (x.mpEnd - x.mpBegin) * sizeof(Elem18));
            destruct(pNewEnd, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x00526b30  vector<Elem38-ish 0x1c>::operator=
struct Elem1c {
    uint32_t data[7];
};
Elem1c* UninitCopy1c(Elem1c* first, Elem1c* last, Elem1c* dest);      // 0x00527a70
Elem1c* AllocAndCopy1c(uint32_t n, Elem1c* first, Elem1c* last);      // 0x00527b10

struct VectorElem1c : VectorBase<Elem1c> {
    typedef Elem1c value_type;
    typedef uint32_t size_type;
    VectorElem1c& operator=(const VectorElem1c& x);
};

// @ 0x00526b30
VectorElem1c& VectorElem1c::operator=(const VectorElem1c& x)
{
    if (this != &x) {
        uint32_t n = x.size();
        if (n > capacity()) {
            Elem1c* pNewData = AllocAndCopy1c(n, x.mpBegin, x.mpEnd);
            destruct(mpBegin, mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpCapacity = pNewData + n;
        } else if (n > size()) {
            memcpy(mpBegin, x.mpBegin, size() * sizeof(Elem1c));
            UninitCopy1c(x.mpBegin + size(), x.mpEnd, mpEnd);
        } else {
            Elem1c* pNewEnd = (Elem1c*)memcpy(mpBegin, x.mpBegin, (x.mpEnd - x.mpBegin) * sizeof(Elem1c));
            destruct(pNewEnd, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// ---------------------------------------------------------------- 0x40-byte element vector
struct Elem40 {
    uint32_t data[0x10];
    Elem40() {}
};
Elem40* UninitCopy40(Elem40* first, Elem40* last, Elem40* dest);      // 0x00528330

struct VectorElem40 : VectorBase<Elem40> {
    typedef Elem40 value_type;
    typedef uint32_t size_type;
    VectorElem40(const VectorElem40& x);                              // 0x00527150
};

// @ 0x00527150
VectorElem40::VectorElem40(const VectorElem40& x)
{
    ScratchSlots<15>();
    uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
    mpBegin = n ? (Elem40*)EA_Allocate(&mAllocator, n << 6, 4, 0) : 0;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
    mpEnd = UninitCopy40(x.mpBegin, x.mpEnd, mpBegin);
}

// ---------------------------------------------------------------- deque node reclaim
struct DequeElem48 {
    Elem40** mpPtrArray;
    uint32_t mnPtrArraySize;
    struct Iterator {
        void* mpCurrent;
        void* mpBegin;
        void* mpEnd;
        void** mpCurrentArrayPtr;
        void DoFreeMap(void* p);   // 0x00515170 (this = &mItBegin)
    };
    Iterator mItBegin;       // +0x08
    Iterator mItEnd;         // +0x18
    void FreeNode(void* p);  // 0x00569260
    void DoPopFront();       // 0x00527110
};

// @ 0x00527110 
void DequeElem48::DoPopFront()
{
    FreeNode(mItBegin.mpBegin);
    mItBegin.DoFreeMap((char*)mItBegin.mpCurrentArrayPtr + 4);
    mItBegin.mpCurrent = mItBegin.mpBegin;
}

// ---------------------------------------------------------------- fixed_vector free (8-byte element)
struct Alloc4 {
    uint32_t mFlags;
};
struct FixedVec8 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    Alloc4 mAllocator;
    void* mpInlineBuffer;    // +0x10
    void Free();             // 0x00526a40
};

// @ 0x00526a40
void FixedVec8::Free()
{
    void* q;
    if (mpBegin) {
        int nBytes = (int)(((char*)mpCapacity - (char*)mpBegin) >> 3) << 3;
        void* p = mpBegin;
        (void)nBytes;
        if (p != mpInlineBuffer) {
            q = p;
            EA_Free(q);
        }
    }
}
