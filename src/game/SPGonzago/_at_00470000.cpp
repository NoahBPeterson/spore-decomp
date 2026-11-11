// src/game/SPGonzago/_at_00470000.cpp -- migrated from slice(s) s00474bd0, s00473e40, s00472b80 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00470000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" unsigned int __cdecl strlen(const char* p);                          // inlined (intrinsic)
#include <stdarg.h>
#include <math.h>
#include <new>
#pragma intrinsic(strlen)

// ---- items of slice s00472b80 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* EASTL_Allocate(void* alloc, uint32_t n, uint32_t align, uint32_t flags); // @ 0x0042dee0
void  EASTL_allocator_deallocate(void* p);                                      // @ 0x00f47380
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct sp_vector_allocator {
    uint32_t mDummy;
    void deallocate(void* p, uint32_t) { void* q = p; EASTL_allocator_deallocate(q); }
};
struct Counted { void Release(); };                                  // 0x40f360
struct AutoRefCount {
    Counted* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
struct Pod12 { float x, y, z; };                                     // 12-byte POD
struct Pair8 { int first; float second; Pair8() {} };                 // 8-byte, empty default ctor
template<class T> struct ResizeHoles { enum { N = 6 }; };
template<> struct ResizeHoles<AutoRefCount> { enum { N = 15 }; };
template<class T> T* uninitialized_copy_ptr(T* first, T* last, T* dest);   // out of line
template<class T> inline void destruct(T* first, T* last)
{ for (; first < last; ++first) first->~T(); }
template<class T> inline T* CopyRef(T* first, T* last, T* dest)
{
    const bool from = false, left = false, pos = false;
    { uint32_t unused[2]; }
    T* pSource = first;
    T* pDest = dest;
    for (; pSource != last; ++pSource, ++pDest) *pDest = *pSource;
    return pDest;
}
template<class T, int A>
struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; sp_vector_allocator mAllocator;

    T* DoAllocate(uint32_t n) { return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), A, 0) : 0; }
    void DoFree(T* p, uint32_t n) { if (p && ((int*)p)[-1]) mAllocator.deallocate(p, n); }

    void DoInsertValues(T* pos, uint32_t n, const T& v);   // out of line
    void erase(T* first, T* last);                         // out of line
    void insert(T* pos, uint32_t n, const T& v) { DoInsertValues(pos, n, v); }

    vector& operator=(const vector& x);
    T* DoRealloc(uint32_t n, T* first, T* last);           // out of line
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void reserve(uint32_t n);
    void resize(uint32_t n);
};
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
            ScratchSlots<8>();
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
// ---- items of slice s00472b80 end

// ---- items of slice s00473e40 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
template<class T> struct ResizeHoles_s0047_3e40 { enum { N = 6 }; };
template<> struct ResizeHoles_s0047_3e40<uint32_t> { enum { N = 4 }; };
template<class T> T* uninitialized_copy_ptr_s0047_3e40(T* first, T* last, T* dest);    // out of line (e.g. 0x004763a0)
template<class T> inline void destruct_s0047_3e40(T* first, T* last) { ScratchSlots<8>(); }
struct false_type2 { false_type2() {} };
struct Elem16Iter { Elem16* mIterator; Elem16Iter(Elem16* p) : mIterator(p) {} };
Elem16* CopyRange_Elem16(Elem16* first, Elem16* last, Elem16* dest);                       // @ 0x0047c1c0
Elem16Iter UninitializedCopy_Elem16(Elem16Iter first, Elem16Iter last, Elem16Iter dest, false_type2); // @ 0x0047a500
inline Elem16* uninitialized_copy_ptr_s0047_3e40(Elem16* first, Elem16* last, Elem16* dest)
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
inline void destruct_s0047_3e40(Elem16* first, Elem16* last) {}
inline Elem16Iter uninitialized_copy(Elem16* first, Elem16* last, Elem16* dest)
{
    ScratchSlots<4>();
    char unusedFlag;
    return UninitializedCopy_Elem16(Elem16Iter(first), Elem16Iter(last), Elem16Iter(dest), false_type2());
}
struct AutoRefCount_s0047_3e40 {
    IRefCounted* mpObject;
    ~AutoRefCount_s0047_3e40() { if (mpObject) mpObject->Release(); }
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
template<> struct ResizeHoles_s0047_3e40<AutoRefCount_s0047_3e40> { enum { N = 15 }; };
AutoRefCount_s0047_3e40* CopyRange_Ref(AutoRefCount_s0047_3e40* first, AutoRefCount_s0047_3e40* last, AutoRefCount_s0047_3e40* dest);              // @ 0x0042f530
AutoRefCount_s0047_3e40* uninitialized_copy_ptr_s0047_3e40(AutoRefCount_s0047_3e40* first, AutoRefCount_s0047_3e40* last, AutoRefCount_s0047_3e40* dest);     // @ 0x004e8c80
inline void destruct_s0047_3e40(AutoRefCount_s0047_3e40* first, AutoRefCount_s0047_3e40* last)
{
    for (; first < last; ++first)
        first->~AutoRefCount_s0047_3e40();
}
inline AutoRefCount_s0047_3e40* CopyRef_s0047_3e40(AutoRefCount_s0047_3e40* first, AutoRefCount_s0047_3e40* last, AutoRefCount_s0047_3e40* dest)
{
    // eastl::copy's type-trait flags; the names only fix their /Od slot order.
    const bool from = false, left = false, pos = false;
    { uint32_t unused[2]; }
    return CopyRange_Ref(first, last, dest);
}
template<class T, int A>
struct vector_s0047_3e40 {
    T* mpBegin; T* mpEnd; T* mpCapacity; sp_vector_allocator mAllocator;

    T* DoAllocate(uint32_t n) { return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), A, 0) : 0; }
    void DoFree(T* p, uint32_t n) { if (p && ((int*)p)[-1]) mAllocator.deallocate(p, n); }

    void DoInsertValues(T* pos, uint32_t n, const T& v);   // out of line
    void DoInsertValueEnd(T* pos, const T& v);             // out of line
    void erase(T* first, T* last);                         // out of line 0x00621f50
    void insert(T* pos, uint32_t n, const T& v) { DoInsertValues(pos, n, v); }

    vector_s0047_3e40(const vector_s0047_3e40& x);
    vector_s0047_3e40& operator=(const vector_s0047_3e40& x);
    T* DoRealloc(uint32_t n, T* first, T* last);           // out of line
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void reserve(uint32_t n);
    void resize(uint32_t n);
    void resize(uint32_t n, const T& v);
    void push_back(const T& v);
};
template<class T, int A>
vector_s0047_3e40<T,A>::vector_s0047_3e40(const vector_s0047_3e40& x)
{
    const uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
    mpBegin = DoAllocate(n);
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
    mpEnd = uninitialized_copy(x.mpBegin, x.mpEnd, mpBegin).mIterator;
}
template<class T, int A>
vector_s0047_3e40<T,A>& vector_s0047_3e40<T,A>::operator=(const vector_s0047_3e40& x)
{
    if (&x != this) {
        const uint32_t n = x.size();
        if (n > (uint32_t)(mpCapacity - mpBegin)) {
            T* const pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            ScratchSlots<9>();
            destruct_s0047_3e40(mpBegin, mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if (n > size()) {
            CopyRef_s0047_3e40(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            uninitialized_copy_ptr_s0047_3e40(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
            ScratchSlots<12>();
        } else {
            T* const position = CopyRef_s0047_3e40(x.mpBegin, x.mpEnd, mpBegin);
            destruct_s0047_3e40(position, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}
template<class T, int A>
void vector_s0047_3e40<T,A>::reserve(uint32_t n)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        T* const pNewData = DoAllocate(n);
        uninitialized_copy_ptr_s0047_3e40(mpBegin, mpEnd, pNewData);
        destruct_s0047_3e40(mpBegin, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        const int nPrevSize = mpEnd - mpBegin;
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = mpBegin + n;
    }
}
template<class T, int A>
void vector_s0047_3e40<T,A>::resize(uint32_t n)
{
    if (n > size()) {
        insert(mpEnd, n - size(), T());
        ScratchSlots<ResizeHoles_s0047_3e40<T>::N>();
    } else
        erase(mpBegin + n, mpEnd);
}
template<class T, int A>
void vector_s0047_3e40<T,A>::resize(uint32_t n, const T& v)
{
    if (n > size()) {
        insert(mpEnd, n - size(), v);
        ScratchSlots<ResizeHoles_s0047_3e40<T>::N>();
    } else
        erase(mpBegin + n, mpEnd);
}
template<class T, int A>
void vector_s0047_3e40<T,A>::push_back(const T& v)
{
    if (mpEnd < mpCapacity)
        ::new(mpEnd++) T(v);
    else
        DoInsertValueEnd(mpEnd, v);
}
// ---- items of slice s00473e40 end

// ---- items of slice s00474bd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef unsigned char uchar;
struct DefaultRefCounted { void Release(); };
void operator_delete_array(void* p);                       // operator delete[] // 0x00f47380
void operator_delete_alloc(void* p, void* a, void* alloc, uint n);
void* Alloc(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0 (thiscall on allocator)
struct RefVec {
    DefaultRefCounted** mpBegin;
    DefaultRefCounted** mpEnd;
    DefaultRefCounted** mpCapacity;
    RefVec& assign(const RefVec& x);
    DefaultRefCounted** DoAllocateCopy(uint n, DefaultRefCounted** first, DefaultRefCounted** last); // 0x476dd0
};
void CopyNode(DefaultRefCounted** p);                     // 0x4e4350 (ref-counted pointer copy)
void UninitCopy(void* out, DefaultRefCounted** first, DefaultRefCounted** last, DefaultRefCounted** dst, uchar t); // 0x42e860
struct ElemRange {
    void Destroy();   // 0x4c0b80 (thiscall, range member in ecx)
};
struct Vec48 {
    char* mpBegin; char* mpEnd;
    ~Vec48();
    void Free();   // 0x476e60
};
struct VecD8 {
    char* mpBegin; char* mpEnd;
    ~VecD8();
    void Free();   // 0x476f20
};
struct FixedVecInt {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    char mAllocator[4];       // +0x0c
    int* mpFixedBuffer;       // +0x10
    void reserve(uint n);
    void push_back(const int& v);
    void DoInsertValue(int* pos, const int& v);        // 0x476fe0
};
void CopyInts(int* first, int* last, int* dst);        // 0x477200
struct IRefObj {                       // ref-counted object: slot 0 = AddRef, slot 1 = Release
    virtual int AddRef();
    virtual int Release();
};
struct IndexVec;                       // 4-byte-element vector (StreamIndex pairs), +0x98 in the caller
struct StreamDesc {                    // 0x10 bytes (the "Desc" of s0046e450)
    int mCount;                        // +0x0
    void* mpData;                      // +0x4
    unsigned short mStride;            // +0x8
    unsigned short mStride2;           // +0xa
    IRefObj* mpOwner;                  // +0xc
    StreamDesc() { init0(); }
    StreamDesc* init0();                                            // 0x46f1f0
    StreamDesc* init(int count, void* data, IRefObj* owner, int);   // 0x46f140
    StreamDesc* initFromVec(const IndexVec* v, IRefObj* owner, int); // 0x4755a0
};
struct StreamElem {                    // 0x20 bytes
    int mUsage;                        // +0x0
    int mIndex;                        // +0x4
    int mType;                         // +0x8
    int mSlot;                         // +0xc
    StreamDesc mDesc;                  // +0x10
    StreamElem() : mUsage(0), mIndex(0), mType(0), mSlot(14) {}
};
struct Vec32 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    char mAllocator[4];
    void resize(uint n);
    void reserve(uint n);
    int size() const;
    void Fill32(char* pos, uint count, const StreamElem* v);       // 0x47ae60
    void Erase32(char* first, char* last);                         // 0x477380
};
void Move32(char* first, char* last, char* dst);       // 0x42a730
struct Elem8c {
    char mData[0x8c];
    void* Construct();                 // 0x46f1b0
    void Fixup();                      // 0x41f940
    void* CopyFrom(void* src);         // 0x42cba0
};
struct Vec8c {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    int size();
    void push_back_default();
    void push_back(void* v);
    void DoInsert(char* pos, void* v);     // 0x477460 (thiscall on the vector)
};
void Uninit4(void* a, void* b, float c);               // 0x477820 (cdecl, 3 args; 3rd is a float)
struct StreamIndex { short mStream; short mSub; };     // 4 bytes
struct IndexVec {                                      // 4-byte-element vector
    StreamIndex* mpBegin; StreamIndex* mpEnd; StreamIndex* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    StreamIndex* begin() const { return mpBegin; }
};
struct Vec8 {
    uint* mpBegin; uint* mpEnd; uint* mpCapacity;
    void push_backA(uint* v);
    void push_backB(uint* v);
    void DoInsertA(uint* pos, uint* v);    // 0x478390 (thiscall on the vector)
    void DoInsertB(uint* pos, uint* v);    // 0x4786e0 (thiscall on the vector)
};
struct VecBits {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    char mAllocator[4];
    void reserve(uint n);
};
void* DoInsertValue(void* dst, void* src, int bytes);  // vector<bool,fixed_vector_allocator<1,16,1,0,1>>::DoInsertValue // 0x011e0744
struct Struct29c {
    char pad[0x158];
    uint a[64];          // 0x158 (32 pairs)
    uint b[16];          // 0x258 (8 pairs)
    uint c;              // 0x298
    Struct29c* Clear();
};
// ---- items of slice s00474bd0 end

// @ 0x004737f0
template uint32_t vector<Pod12, 4>::size() const
;

// @ 0x00473b00
template vector<Pair8, 4>& vector<Pair8, 4>::operator=(const vector<Pair8, 4>&)
;

// @ 0x00473e40
template void vector_s0047_3e40<PairIF, 4>::reserve(uint32_t)
;

// @ 0x00473f30
template void vector_s0047_3e40<PairFF, 4>::push_back(const PairFF&)
;

// @ 0x00474170
template void vector_s0047_3e40<Elem8, 2>::reserve(uint32_t)
;

// @ 0x00474260
template void vector_s0047_3e40<Elem8, 4>::push_back(const Elem8&)
;

// @ 0x00474600
template void vector_s0047_3e40<Elem16, 4>::push_back(const Elem16&)
;

// @ 0x004746c0
template void vector_s0047_3e40<uint32_t, 4>::resize(uint32_t, const uint32_t&)
;

// @ 0x004747c0
template void vector_s0047_3e40<Matrix44, 4>::push_back(const Matrix44&)
;

// @ 0x00474840
template void vector_s0047_3e40<AutoRefCount_s0047_3e40, 4>::resize(uint32_t, const AutoRefCount_s0047_3e40&)
;

// @ 0x00474bd0
RefVec& RefVec::assign(const RefVec& x)
{
    if (&x != this) {
        const uint n = (uint)(x.mpEnd - x.mpBegin);
        if ((uint)(mpCapacity - mpBegin) < n) {
            DefaultRefCounted** pNew = DoAllocateCopy(n, x.mpBegin, x.mpEnd);
            for (DefaultRefCounted** p = mpBegin; p < mpEnd; ++p)
                if (*p) (*p)->Release();
            if (mpBegin) operator_delete_array(mpBegin);
            mpBegin = pNew;
            mpCapacity = mpBegin + n;
        } else if ((uint)(mpEnd - mpBegin) < n) {
            DefaultRefCounted** dst = mpBegin;
            DefaultRefCounted** mid = x.mpBegin + (mpEnd - mpBegin);
            for (DefaultRefCounted** s = x.mpBegin; s != mid; ++s) { CopyNode(s); ++dst; }
            char tmp[4];
            UninitCopy(tmp, mid, x.mpEnd, mpEnd, 0);
        } else {
            DefaultRefCounted** dst = mpBegin;
            for (DefaultRefCounted** s = x.mpBegin; s != x.mpEnd; ++s) { CopyNode(s); ++dst; }
            for (DefaultRefCounted** p = dst; p < mpEnd; ++p)
                if (*p) (*p)->Release();
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x00474f30
Vec48::~Vec48()
{
    char* end = mpEnd;
    for (char* e = mpBegin; e < end; e += 0x48) {
        for (char* q = *(char**)(e + 0xc); q < *(char**)(e + 0x10); q += 4) {}
        ((ElemRange*)(e + 0xc))->Destroy();
    }
    Free();
}

// @ 0x00474fb0
VecD8::~VecD8()
{
    char* end = mpEnd;
    for (char* e = mpBegin; e < end; e += 0xd8) {
        for (char* q = *(char**)(e + 0x10); q < *(char**)(e + 0x14); q += 4) {}
        ((ElemRange*)(e + 0x10))->Destroy();
    }
    Free();
}

// @ 0x00475040
void FixedVecInt::reserve(uint n)
{
    if ((uint)(mpCapacity - mpBegin) < n) {
        int* pNew = n ? (int*)Alloc(mAllocator, n << 2, 2, 0) : 0;
        CopyInts(mpBegin, mpEnd, pNew);
        if (mpBegin && mpBegin != mpFixedBuffer)
            operator_delete_alloc(mpBegin, pNew, this, (uint)(mpCapacity - mpBegin));
        int* old = mpBegin;
        mpBegin = pNew;
        mpEnd = pNew + (mpEnd - old);
        mpCapacity = mpBegin + n;
    }
}

// @ 0x00475130
struct IntCopy { int x; };
void FixedVecInt::push_back(const int& v)
{
    int* p;
    int* snap;
    if (mpEnd < mpCapacity) {
        snap = mpEnd;
        mpEnd += 1;
        p = snap;
        // Struct assignment loads the source first. A scalar `*p = v` loads the destination first.
        p ? (*(IntCopy*)p = *(IntCopy*)&v, p) : 0;
    } else {
        DoInsertValue(mpEnd, v);
    }
}

// @ 0x00475240
int Vec32::size() const
{ return (mpEnd - mpBegin) >> 5; }

// @ 0x00475320
void Vec32::reserve(uint n)
{
    if ((uint)((mpCapacity - mpBegin) >> 5) < n) {
        char* pNew = n ? (char*)Alloc(mAllocator, n << 5, 4, 0) : 0;
        Move32(mpBegin, mpEnd, pNew);
        if (mpBegin && *(int*)(mpBegin - 4) != 0)
            operator_delete_alloc(mpBegin, pNew, this, (uint)((mpCapacity - mpBegin) >> 5));
        char* old = mpBegin;
        mpBegin = pNew;
        mpEnd = pNew + ((mpEnd - old) >> 5) * 0x20;
        mpCapacity = mpBegin + n * 0x20;
    }
}

// @ 0x00475410
int Vec8c::size()
{ return (mpEnd - mpBegin) / 0x8c; }

// @ 0x00475430
void Vec8c::push_back_default()
{
    Elem8c tmp;
    if (mpEnd < mpCapacity) {
        Elem8c* p = (Elem8c*)mpEnd;
        mpEnd += 0x8c;
        void* r = p ? p->Construct() : 0;
    } else {
        DoInsert(mpEnd, tmp.Construct());
        tmp.Fixup();
    }
}

// @ 0x004754e0
void Vec8c::push_back(void* v)
{
    if (mpEnd < mpCapacity) {
        Elem8c* p = (Elem8c*)mpEnd;
        mpEnd += 0x8c;
        void* r = p ? p->CopyFrom(v) : 0;
    } else {
        DoInsert(mpEnd, v);
    }
}

// @ 0x00475550
void* Wrap4(void* out, void* in, float* pv)
{
    Uninit4(out, in, *pv);
    return out;
}

// @ 0x004755a0
StreamDesc* StreamDesc::initFromVec(const IndexVec* v, IRefObj* owner, int)
{
    mCount = v->size();
    StreamIndex* p = v->begin();
    mpData = p;
    mStride = 4;
    mStride2 = 4;
    IRefObj*& r = mpOwner;
    r = owner;
    if (r) r->AddRef();
    return this;
}

// @ 0x00475670
void Vec8::push_backA(uint* v)
{
    uint* p;
    uint* snap;
    if (mpEnd < mpCapacity) {
        snap = mpEnd;
        mpEnd += 2;
        p = snap;
        p ? (*(float*)p = *(float*)v,
             *(float*)(p + 1) = *(float*)(v + 1), p) : 0;
    } else {
        DoInsertA(mpEnd, v);
    }
}

// @ 0x004756f0
void VecBits::reserve(uint n)
{
    if ((uint)((mpCapacity - mpBegin) >> 3) < n) {
        void* pNew = n ? Alloc(mAllocator, n << 3, 8, 0) : 0;
        DoInsertValue(pNew, mpBegin, (int)(mpEnd - mpBegin));
        if (mpBegin && *(int*)(mpBegin - 4) != 0)
            operator_delete_array(mpBegin); // 0x00f47380
        char* old = mpBegin;
        mpBegin = (char*)pNew;
        mpEnd = (char*)pNew + ((mpEnd - old) >> 3) * 8;
        mpCapacity = mpBegin + n * 8;
    }
}

// @ 0x00475800
void Vec8::push_backB(uint* v)
{
    uint* p;
    uint* snap;
    if (mpEnd < mpCapacity) {
        snap = mpEnd;
        mpEnd += 2;
        p = snap;
        p ? (*(unsigned long long*)p = *(unsigned long long*)v, p) : 0;
    } else {
        DoInsertB(mpEnd, v);
    }
}

// @ 0x00475880
Struct29c* Struct29c::Clear()
{
    int i = 0x20;
    uint* p = a;
    while (--i, -1 < i) { p[0] = 0; p[1] = 0; p += 2; }
    int j = 8;
    uint* q = b;
    while (--j, -1 < j) { q[0] = 0; q[1] = 0; q += 2; }
    c = 0;
    return this;
}
