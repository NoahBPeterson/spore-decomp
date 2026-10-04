// eastl::vector<T, sp_vector_allocator> instantiations: reserve / resize / push_back / size / copy-ctor / operator=.
// Built /Od /Ob1 (no /EHsc): frame pointer, every local in memory, inline helpers expanded in place.
// Layout: mpBegin +0, mpEnd +4, mpCapacity +8, mAllocator +0xC.
#include "types.h"
#include <new>

void* EASTL_Allocate(void* alloc, uint32_t n, uint32_t align, uint32_t flags);   // @ 0x0042dee0
void  EASTL_allocator_deallocate(void* p);                                         // @ 0x00f47380

// Unused locals of inline helpers that /Od still reserves frame slots for (shape helpers, not original code).
template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct sp_vector_allocator {
    uint32_t mDummy;
    void deallocate(void* p, uint32_t) { void* q = p; EASTL_allocator_deallocate(q); }
};

// Element types
struct PairIF { int first; float second; };
struct PairFF { float a, b; PairFF(const PairFF& o) : a(o.a), b(o.b) {} };
struct Elem8  { uint32_t a, b; };
struct Elem16 { float x, y, z, w; Elem16() {} Elem16(const Elem16& o) : x(o.x), y(o.y), z(o.z), w(o.w) {} };
struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
};
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
struct IRefCounted { virtual void v0(); virtual void Release(); };

// Unused-slot count left by resize()'s inline helpers, per element type.
template<class T> struct ResizeHoles { enum { N = 6 }; };
template<> struct ResizeHoles<uint32_t> { enum { N = 4 }; };
template<class T> T* uninitialized_copy_ptr(T* first, T* last, T* dest);    // out of line (e.g. 0x004763a0)
template<class T> inline void destruct(T* first, T* last) { ScratchSlots<8>(); }

// Elem16 (non-trivial copy) paths
struct false_type2 { false_type2() {} };
struct Elem16Iter { Elem16* mIterator; Elem16Iter(Elem16* p) : mIterator(p) {} };
Elem16* CopyRange_Elem16(Elem16* first, Elem16* last, Elem16* dest);                       // @ 0x0047c1c0
Elem16Iter UninitializedCopy_Elem16(Elem16Iter first, Elem16Iter last, Elem16Iter dest, false_type2); // @ 0x0047a500
inline Elem16* uninitialized_copy_ptr(Elem16* first, Elem16* last, Elem16* dest)
{
    { bool bTrivial = false; }
    Elem16* const pResult = CopyRange_Elem16(first, last, dest);
    { uint32_t unused; }
    { bool bTrivial2 = false; }
    {
        Elem16* d = dest;
        Elem16* s = first;
        for (; s != last; ++s, ++d) {}
    }
    return pResult;
}
inline void destruct(Elem16* first, Elem16* last) {}
inline Elem16Iter uninitialized_copy(Elem16* first, Elem16* last, Elem16* dest)
{
    ScratchSlots<4>();
    char unusedFlag;
    return UninitializedCopy_Elem16(Elem16Iter(first), Elem16Iter(last), Elem16Iter(dest), false_type2());
}

// AutoRefCount<T>-style element (eastl::vector<EA::AutoRefCount<...>>)
struct AutoRefCount {
    IRefCounted* mpObject;
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
template<> struct ResizeHoles<AutoRefCount> { enum { N = 15 }; };
AutoRefCount* CopyRange_Ref(AutoRefCount* first, AutoRefCount* last, AutoRefCount* dest);              // @ 0x0042f530
AutoRefCount* uninitialized_copy_ptr(AutoRefCount* first, AutoRefCount* last, AutoRefCount* dest);     // @ 0x004e8c80
inline void destruct(AutoRefCount* first, AutoRefCount* last)
{
    for (; first < last; ++first)
        first->~AutoRefCount();
}
inline AutoRefCount* CopyRef(AutoRefCount* first, AutoRefCount* last, AutoRefCount* dest)
{
    // eastl::copy's type-trait flags; the names only fix their /Od slot order.
    const bool from = false, left = false, pos = false;
    { uint32_t unused[2]; }
    return CopyRange_Ref(first, last, dest);
}

template<class T, int A>
struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; sp_vector_allocator mAllocator;

    T* DoAllocate(uint32_t n) { return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), A, 0) : 0; }
    void DoFree(T* p, uint32_t n) { if (p && ((int*)p)[-1]) mAllocator.deallocate(p, n); }

    void DoInsertValues(T* pos, uint32_t n, const T& v);   // out of line
    void DoInsertValueEnd(T* pos, const T& v);             // out of line
    void erase(T* first, T* last);                         // out of line
    void insert(T* pos, uint32_t n, const T& v) { DoInsertValues(pos, n, v); }

    vector(const vector& x);
    vector& operator=(const vector& x);
    T* DoRealloc(uint32_t n, T* first, T* last);           // out of line
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void reserve(uint32_t n);
    void resize(uint32_t n);
    void resize(uint32_t n, const T& v);
    void push_back(const T& v);
};


template<class T, int A>
vector<T,A>::vector(const vector& x)
{
    const uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
    mpBegin = DoAllocate(n);
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
    mpEnd = uninitialized_copy(x.mpBegin, x.mpEnd, mpBegin).mIterator;
}

template<class T, int A>
vector<T,A>& vector<T,A>::operator=(const vector& x)
{
    if (&x != this) {
        const uint32_t n = x.size();
        if (n > (uint32_t)(mpCapacity - mpBegin)) {
            T* const pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            ScratchSlots<9>();
            destruct(mpBegin, mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if (n > size()) {
            CopyRef(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            uninitialized_copy_ptr(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
            ScratchSlots<12>();
        } else {
            T* const position = CopyRef(x.mpBegin, x.mpEnd, mpBegin);
            destruct(position, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

template<class T, int A>
void vector<T,A>::reserve(uint32_t n)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        T* const pNewData = DoAllocate(n);
        uninitialized_copy_ptr(mpBegin, mpEnd, pNewData);
        destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        const int nPrevSize = mpEnd - mpBegin;
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = mpBegin + n;
    }
}

template<class T, int A>
void vector<T,A>::resize(uint32_t n)
{
    if (n > size()) {
        insert(mpEnd, n - size(), T());
        ScratchSlots<ResizeHoles<T>::N>();
    } else
        erase(mpBegin + n, mpEnd);
}

template<class T, int A>
void vector<T,A>::resize(uint32_t n, const T& v)
{
    if (n > size()) {
        insert(mpEnd, n - size(), v);
        ScratchSlots<ResizeHoles<T>::N>();
    } else
        erase(mpBegin + n, mpEnd);
}

template<class T, int A>
void vector<T,A>::push_back(const T& v)
{
    if (mpEnd < mpCapacity)
        ::new(mpEnd++) T(v);
    else
        DoInsertValueEnd(mpEnd, v);
}

// @ 0x00473e40
template void vector<PairIF, 4>::reserve(uint32_t);
// @ 0x00473f30
template void vector<PairFF, 4>::push_back(const PairFF&);
// @ 0x00474050
template uint32_t vector<PairIF, 4>::size() const;
// @ 0x00474070
template void vector<PairIF, 4>::resize(uint32_t);
// @ 0x004740f0
template void vector<PairIF, 4>::resize(uint32_t, const PairIF&);
// @ 0x00474170
template void vector<Elem8, 2>::reserve(uint32_t);
// @ 0x00474260
template void vector<Elem8, 4>::push_back(const Elem8&);
// @ 0x004743b0
template uint32_t vector<Elem16, 4>::size() const;
// @ 0x004743d0
template void vector<Elem16, 4>::resize(uint32_t);
// @ 0x00474450
template void vector<Elem16, 4>::resize(uint32_t, const Elem16&);
// @ 0x00474600
template void vector<Elem16, 4>::push_back(const Elem16&);
// @ 0x004746a0
template uint32_t vector<uint32_t, 4>::size() const;
// @ 0x004746c0
template void vector<uint32_t, 4>::resize(uint32_t, const uint32_t&);
// @ 0x00474740
template void vector<Matrix44, 4>::resize(uint32_t);
// @ 0x004747c0
template void vector<Matrix44, 4>::push_back(const Matrix44&);
// @ 0x004742e0
template vector<Elem16, 4>::vector(const vector<Elem16, 4>&);
// @ 0x004744d0
template void vector<Elem16, 4>::reserve(uint32_t);
// @ 0x00474840
template void vector<AutoRefCount, 4>::resize(uint32_t, const AutoRefCount&);
// @ 0x00474900
template vector<AutoRefCount, 4>& vector<AutoRefCount, 4>::operator=(const vector<AutoRefCount, 4>&);
