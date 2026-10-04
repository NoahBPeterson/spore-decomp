// Slice s0047c400: EASTL algorithm/memory template instantiations, built /Od /Ob1:
// sort helpers over (float key, value) pairs, uninitialized_copy / uninitialized_fill_n /
// uninitialized_relocate_commit for AutoRefCount, Vector, Matrix44 and cEltArrayRef elements,
// a compiler-style operator= for a 0x29c-byte record, and basic_string<char> capacity helpers.
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }

void* EASTL_allocator_allocate(uint32_t n, const char* pName, int flags, int align, const char* pFile, int line);  // @ 0x00f473a0
void  EASTL_allocator_deallocate(void* p);                                                                         // @ 0x00f47380
void* EASTL_memmove(void* pDest, const void* pSource, uint32_t n);                                                 // @ 0x011e0744

// Unused locals of inline helpers that /Od still reserves frame slots for (shape helper).
template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct false_type {};

// ---------------------------------------------------------------------------
// Sort element: 8 bytes, ordered by the float key.
struct FloatKeyPair {
    float x, y;
    FloatKeyPair(const FloatKeyPair& v) { x = v.x; y = v.y; }
    const float& operator[](int i) const { return (&x)[i]; }
};

struct FloatKeyLess {
    bool operator()(const FloatKeyPair& a, const FloatKeyPair& b) const { return a[0] < b[0]; }
};

void make_heap(FloatKeyPair* first, FloatKeyPair* last, FloatKeyLess compare);
void adjust_heap(FloatKeyPair* first, int topPosition, int heapSize, int position, FloatKeyPair value, FloatKeyLess compare);
void promote_heap(FloatKeyPair* first, int topPosition, int position, FloatKeyPair value, FloatKeyLess compare);  // @ 0x0047d450
void pop_heap(FloatKeyPair* first, FloatKeyPair* last, FloatKeyLess compare);                                     // @ 0x0047d4f0

inline void sort_heap(FloatKeyPair* first, FloatKeyPair* last, FloatKeyLess compare)
{
    for (; (last - first) > 1; --last)
        pop_heap(first, last, compare);
}

// @ 0x0047c400
FloatKeyPair* get_partition(FloatKeyPair* first, FloatKeyPair* last, FloatKeyPair pivotValue, FloatKeyLess compare)
{
    for (; ; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        FloatKeyPair temp(*first);
        *first = *last;
        *last = temp;
    }
}

// @ 0x0047c4e0
void partial_sort(FloatKeyPair* first, FloatKeyPair* middle, FloatKeyPair* last, FloatKeyLess compare)
{
    make_heap(first, middle, compare);
    for (FloatKeyPair* i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            const FloatKeyPair temp(*i);
            *i = *first;
            adjust_heap(first, 0, (int)(middle - first), 0, temp, compare);
        }
    }
    ScratchSlots<5>();
    sort_heap(first, middle, compare);
}

// @ 0x0047cd80
void make_heap(FloatKeyPair* first, FloatKeyPair* last, FloatKeyLess compare)
{
    const int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            adjust_heap(first, parentPosition, heapSize, parentPosition, *(first + parentPosition), compare);
        } while (parentPosition != 0);
    }
}

// @ 0x0047ce00
void adjust_heap(FloatKeyPair* first, int topPosition, int heapSize, int position, FloatKeyPair value, FloatKeyLess compare)
{
    int childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(*(first + childPosition), *(first + (childPosition - 1))))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    promote_heap(first, topPosition, position, value, compare);
    ScratchSlots<1>();
}

// ---------------------------------------------------------------------------
// Ref-counted element types.
struct Counted { void Release(); };              // @ 0x0040f360 (thiscall)
struct cMWModel : Counted {
    uint32_t pad[0x10];
    int mnRefCount;                               // +0x40, non-atomic
    void AddRef() { ++mnRefCount; }
};

// EA::AutoRefCount<SP::cMWModel>
struct ModelRef {
    cMWModel* mpObject;
    ModelRef(const ModelRef& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~ModelRef() { if (mpObject) mpObject->Release(); }
    ModelRef& operator=(cMWModel* pObject)
    {
        if (pObject != mpObject) {
            cMWModel* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        ScratchSlots<2>();
        return *this;
    }
    ModelRef& operator=(const ModelRef& x) { return operator=(x.mpObject); }
};

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)
struct AtomicRefCounted {
    void* vftable;
    volatile long mnRefCount;                     // +4
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
};
// AutoRefCount over an atomically counted object
struct AtomicRef {
    AtomicRefCounted* mpObject;
    AtomicRef(const AtomicRef& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
};

// EA::COM::IRefCount / EA::AutoRefCount<EA::COM::IRefCount>
struct IRefCount { virtual void AddRef(); virtual void Release(); };
struct IRefCountRef {
    IRefCount* mpObject;
    IRefCountRef(const IRefCountRef& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~IRefCountRef() { if (mpObject) mpObject->Release(); }
};
// SP::cEltArrayRef (implicit copy ctor @ 0x00401b80)
struct cEltArrayRefBase {
    int mNumElts;
    unsigned char* mData;
    unsigned short mEltSize;
    unsigned short mEltStride;
    IRefCountRef mDataRC;
};
// SP::cEltArrayRef element wrapper (its implicit copy ctor inlines and calls the base's)
struct cEltArrayRef : cEltArrayRefBase {
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};

// Vector types (user copy ctors, x87 copies)
struct Vector2 { float x, y; Vector2(const Vector2& v) : x(v.x), y(v.y) {} };
struct Vector3 { float x, y, z; Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {} };
struct Vector4 { float x, y, z, w; Vector4() {} Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {} };

struct Matrix44Template {
    Vector4 mRow0, mRow1, mRow2, mRow3;
    Matrix44Template() {}
    // rw::math::fpu::Matrix44Template<float,0> copy ctor @ 0x0045dca0 (inline, but cl emits it out of line)
    Matrix44Template(const Matrix44Template& m) {
        mRow0 = Vector4(m.mRow0);
        mRow1 = Vector4(m.Row1());
        mRow2 = Vector4(m.Row2());
        mRow3 = Vector4(m.Row3());
    }
    const Vector4& Row1() const { return mRow1; }
    const Vector4& Row2() const { return mRow2; }
    const Vector4& Row3() const { return mRow3; }
};
struct Matrix44 : Matrix44Template { Matrix44() {} };

// ---------------------------------------------------------------------------
// eastl::generic_iterator<T*> (returned through a hidden pointer)
template<class T>
struct generic_iterator {
    T* mIterator;
    generic_iterator(T* p) : mIterator(p) {}
    T& operator*() const { return *mIterator; }
    generic_iterator& operator++() { ++mIterator; return *this; }
};
template<class T>
inline bool operator!=(const generic_iterator<T>& a, const generic_iterator<T>& b) { return a.mIterator != b.mIterator; }

template<class T>
generic_iterator<T> uninitialized_copy_impl(generic_iterator<T> first, generic_iterator<T> last, generic_iterator<T> dest, false_type)
{
    generic_iterator<T> currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        ::new(&*currentDest) T(*first);
    return currentDest;
}

template<class T>
void uninitialized_fill_n_impl(generic_iterator<T> first, uint32_t n, const T& value, false_type)
{
    generic_iterator<T> currentDest(first);
    for (; n > 0; --n, ++currentDest)
        ::new(&*currentDest) T(value);
}

// @ 0x0047c660
template generic_iterator<ModelRef> uninitialized_copy_impl(generic_iterator<ModelRef>, generic_iterator<ModelRef>, generic_iterator<ModelRef>, false_type);
// @ 0x0047c700
template void uninitialized_fill_n_impl(generic_iterator<ModelRef>, uint32_t, const ModelRef&, false_type);
// @ 0x0047c800
template generic_iterator<AtomicRef> uninitialized_copy_impl(generic_iterator<AtomicRef>, generic_iterator<AtomicRef>, generic_iterator<AtomicRef>, false_type);
// @ 0x0047ca00
template void uninitialized_fill_n_impl(generic_iterator<Vector3>, uint32_t, const Vector3&, false_type);
// @ 0x0047ca70
template void uninitialized_fill_n_impl(generic_iterator<Vector2>, uint32_t, const Vector2&, false_type);
// @ 0x0047cae0
template void uninitialized_fill_n_impl(generic_iterator<Vector4>, uint32_t, const Vector4&, false_type);
// @ 0x0047cb60
template generic_iterator<Matrix44> uninitialized_copy_impl(generic_iterator<Matrix44>, generic_iterator<Matrix44>, generic_iterator<Matrix44>, false_type);
// @ 0x0047cbe0
template void uninitialized_fill_n_impl(generic_iterator<Matrix44>, uint32_t, const Matrix44&, false_type);
// @ 0x0047cc40
template generic_iterator<cEltArrayRef> uninitialized_copy_impl(generic_iterator<cEltArrayRef>, generic_iterator<cEltArrayRef>, generic_iterator<cEltArrayRef>, false_type);
// @ 0x0047ccc0
template void uninitialized_fill_n_impl(generic_iterator<cEltArrayRef>, uint32_t, const cEltArrayRef&, false_type);

// copy for AutoRefCount<cMWModel>
inline ModelRef* copy_impl(ModelRef* first, ModelRef* last, ModelRef* result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}

// @ 0x0047c780
ModelRef* copy(ModelRef* first, ModelRef* last, ModelRef* result)
{
    const bool bTrivial = false;
    return copy_impl(first, last, result);
}

// ---------------------------------------------------------------------------
// 0x29c-byte record holding an AutoRefCount<cMWModel> at +0x298.
struct Vec3Block { float x, y, z; };
struct Vec4Block { float x, y, z, w; };
struct Pair8 { uint32_t a, b; };
struct ModelRecord {
    uint32_t       mId;               // +0x000
    unsigned short mShorts[0x50];     // +0x004
    unsigned char  mBytes[0x28];      // +0x0a4
    uint32_t       mValues[5];        // +0x0cc
    Vec3Block      mVec0;             // +0x0e0
    uint32_t       mValue1;           // +0x0ec
    Vec3Block      mVec1;             // +0x0f0
    Vec3Block      mVec2;             // +0x0fc
    Vec3Block      mVec3;             // +0x108
    Vec4Block      mVec4;             // +0x114
    Vec3Block      mVec5;             // +0x124
    Vec3Block      mVec6;             // +0x130
    float          mFloat0;           // +0x13c
    float          mFloat1;           // +0x140
    uint32_t       mValue2;           // +0x144
    uint32_t       mValue3;           // +0x148
    uint32_t       mValue4;           // +0x14c
    uint32_t       mValue5;           // +0x150
    uint32_t       mValue6;           // +0x154
    Pair8          mPairs0[0x20];     // +0x158
    Pair8          mPairs1[8];        // +0x258
    ModelRef       mModel;            // +0x298

    ModelRecord& operator=(const ModelRecord& x);
    ~ModelRecord() { ScratchSlots<2>(); }
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};

// @ 0x0047cf00
ModelRecord& ModelRecord::operator=(const ModelRecord& x)
{
    mId = x.mId;
    for (unsigned i = 0; i < 0x50; ++i) mShorts[i] = x.mShorts[i];
    for (unsigned j = 0; j < 0x28; ++j) mBytes[j] = x.mBytes[j];
    mValues[0] = x.mValues[0];
    mValues[1] = x.mValues[1];
    mValues[2] = x.mValues[2];
    mValues[3] = x.mValues[3];
    mValues[4] = x.mValues[4];
    mVec0 = x.mVec0;
    mValue1 = x.mValue1;
    mVec1 = x.mVec1;
    mVec2 = x.mVec2;
    mVec3 = x.mVec3;
    mVec4 = x.mVec4;
    mVec5 = x.mVec5;
    mVec6 = x.mVec6;
    mFloat0 = x.mFloat0;
    mFloat1 = x.mFloat1;
    mValue2 = x.mValue2;
    mValue3 = x.mValue3;
    mValue4 = x.mValue4;
    mValue5 = x.mValue5;
    mValue6 = x.mValue6;
    for (unsigned k = 0; k < 0x20; ++k) mPairs0[k] = x.mPairs0[k];
    for (unsigned m = 0; m < 8; ++m) mPairs1[m] = x.mPairs1[m];
    mModel = x.mModel;
    return *this;
}

inline ModelRecord* uninitialized_relocate_commit_impl(ModelRecord* first, ModelRecord* last, ModelRecord* dest)
{
    for (; first != last; ++first, ++dest)
        first->~ModelRecord();
    return dest;
}

// @ 0x0047c980
ModelRecord* uninitialized_relocate_commit(ModelRecord* first, ModelRecord* last, ModelRecord* dest)
{
    const bool bTrivial = false;
    return uninitialized_relocate_commit_impl(first, last, dest);
}

// @ 0x0047d3f0
cEltArrayRef* uninitialized_relocate_commit(cEltArrayRef* first, cEltArrayRef* last, cEltArrayRef* dest)
{
    for (; first != last; ++first, ++dest)
        first->~cEltArrayRef();
    return dest;
}

// ---------------------------------------------------------------------------
// eastl::basic_string<char, eastl::allocator>
struct allocator {
    void* allocate(uint32_t n) { void* const p = EASTL_allocator_allocate(n, "Editor", 0, 0, __FILE__, 0xd1); return p; }
};

template<class T> inline const T& max_alt(const T& a, const T& b) { return a < b ? b : a; }

struct string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator mAllocator;

    string(const string& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
    ~string();                                            // @ 0x00530670
    void AllocateSelf(uint32_t n);                        // @ 0x00475ab0 (RangeInitialize helper)
    void resize(uint32_t n);                              // @ 0x00478930
    void swap(string& x);                                 // @ 0x0047d570
    void RangeInitialize(const char* pBegin, const char* pEnd);
    void reserve(uint32_t n);
    void set_capacity(uint32_t n);

    char* DoAllocate(uint32_t n) { ScratchSlots<3>(); return (char*)mAllocator.allocate(n); }
    void DoFree(char* p, uint32_t n) { if (p) Deallocate(p, n); }
    void Deallocate(char* p, uint32_t) { char* q = p; EASTL_allocator_deallocate(q); }
    void DeallocateSelf() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin)); }
    static char* CharStringUninitializedCopy(const char* pSource, const char* pSourceEnd, char* pDestination)
    {
        EASTL_memmove(pDestination, pSource, (uint32_t)(pSourceEnd - pSource));
        return pDestination + (pSourceEnd - pSource);
    }
};

// @ 0x0047c600
void string::reserve(uint32_t n)
{
    n = max_alt(n, (uint32_t)(mpEnd - mpBegin)) + 1;
    ScratchSlots<15>();
    if (n > (uint32_t)(mpCapacity - mpBegin))
        set_capacity(n);
}

// @ 0x0047d240
void string::set_capacity(uint32_t n)
{
    if ((n == (uint32_t)-1) || (n <= (uint32_t)(mpEnd - mpBegin))) {
        if (n < (uint32_t)(mpEnd - mpBegin))
            resize(n);
        string temp(*this);
        swap(temp);
    } else {
        char* pNewBegin = DoAllocate(n);
        char* pNewEnd = pNewBegin;
        pNewEnd = CharStringUninitializedCopy(mpBegin, mpEnd, pNewBegin);
        *pNewEnd = 0;
        DeallocateSelf();
        mpBegin = pNewBegin;
        mpEnd = pNewEnd;
        mpCapacity = pNewBegin + n;
    }
}

// @ 0x0047d390
void string::RangeInitialize(const char* pBegin, const char* pEnd)
{
    // (local names chosen for their /Od slot order: n, p)
    const uint32_t last = (uint32_t)(pEnd - pBegin);
    AllocateSelf(last + 1);
    char* const ptr = mpBegin;
    EASTL_memmove(ptr, pBegin, (uint32_t)(pEnd - pBegin));
    mpEnd = ptr + (pEnd - pBegin);
    *mpEnd = 0;
}
