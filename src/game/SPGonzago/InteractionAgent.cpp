// src/game/SPGonzago/InteractionAgent.cpp -- migrated from slice(s) s0047c400, s0047b480, s0047a5a0, s00479830, s00478930, s00477930, s00475d00, s00474bd0, s00473e40, s00472b80, s004553b0, s00454330, s00401200 by tools/migrate/rewrite.py
// Object file: SPGonzago/InteractionAgent.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <stdarg.h>
#include <new>

// Preamble items the tool's verbatim emission drops for 0x00401930 (see
// work/migrate/report_s00401200_InteractionAgent.md): rewrite.py's needed_items() keeps `struct ArrayElement`
// but not this pointer-to-member typedef, because RS.item_names("typedef", ...) returns [] for
// `typedef ret (Class::*Name)();`.  Both are the slice's own text (s00401200 lines 190-199).
struct ArrayElement { };
typedef void (ArrayElement::*ElementCtorDtor)();

// ---- items of slice s00454330 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_11e0744_memcpy(void*, const void*, unsigned int);        // 0x011e0744
struct BasicString { char* mpBegin; char* mpEnd; char* mpCapacity;
    BasicString* assign(const char* first, const char* last);
    BasicString* append(const char* first, const char* last);   // 0x00455d60
    char*        erase(char* first, char* last);                // 0x0045f080
};
// ---- items of slice s00454330 end

// ---- items of slice s004553b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* EASTL_allocator_deallocate(void* p, int n); // 0x00f47380
extern void* FUN_11e0744_alloc(unsigned int n);
extern void  FUN_11e0744_copy(void* dst, void* src, int n);
// ---- items of slice s004553b0 end

// ---- items of slice s00472b80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned int __cdecl strlen(const char* p);                          // inlined (intrinsic)
#pragma intrinsic(strlen)
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
struct Elem16 { float x, y, z, w; Elem16() {} Elem16(const Elem16& o) : x(o.x), y(o.y), z(o.z), w(o.w) {} };
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
typedef unsigned short ushort;
template <int N> inline void ScratchSlots_s0047_4bd0() { uint s[N]; }
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
struct Vec16 {
    StreamDesc* mpBegin; StreamDesc* mpEnd; StreamDesc* mpCapacity;
    void resize(uint n);
    void Fill(StreamDesc* pos, uint count, const StreamDesc* v);   // 0x47aa40
    void Erase(StreamDesc* first, StreamDesc* last);               // 0x4772a0
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
struct StreamIndex { short mStream; short mSub; };     // 4 bytes
struct IndexVec {                                      // 4-byte-element vector
    StreamIndex* mpBegin; StreamIndex* mpEnd; StreamIndex* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    StreamIndex* begin() const { return mpBegin; }
};
extern ushort gEmptyString;                            // 0x01667bac (shared empty buffer)
int Vsnprintf8(char* dst, uint cap, const char* fmt, void* args);
void* operator_new_eastl(uint size, const char* name, int flags, int dbg, const char* file, int line);
namespace eastl {
struct basic_string_s0047_4bd0 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    basic_string_s0047_4bd0& append_sprintf_va_list(const char* fmt, void* args);
    void RangeInitialize(uint n);
    void set_capacity(uint n);                         // 0x478930
};
}
// ---- items of slice s00474bd0 end

// ---- items of slice s00475d00 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct E12 { uint a, b, c; };
// ---- items of slice s00475d00 end

// ---- items of slice s00477930 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(memmove)
// ---- items of slice s00477930 end

// ---- items of slice s00478930 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* EASTL_Allocate(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0
struct Counted_s0047_8930 {
    char pad[0x40];
    int mRefCount;
    void Release();  // 0x0040f360 (Counted::Release)
};
struct Str8 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void Shrink(char* first, char* last);           // @ 0x0045f080
    void ResizeFill(uint n, char c);                // @ 0x00478930 (recursive)
    void resize(uint n);
};
int* CopyIntRange(int* first, int* last, int* dest);           // @ 0x0047c700
void DestroyInts(int* first, int* last);                       // @ 0x0047c660
int* MoveIntsBack(int* first, int* last, int* dst);            // @ 0x0047c010
void FillInts(int* dst, uint n, const int& v);                 // @ 0x0047c0d0
struct IntVec {
    int* mpBegin; int* mpEnd; int* mpCapacity;
    void IntVectorInsert(int* position, uint n, const int& value);
};
struct RefPtr {
    Counted_s0047_8930* mpObject;
    RefPtr& operator=(Counted_s0047_8930* p);
};
struct Elem29c {
    char pad[0x294];
    Counted_s0047_8930* m298;
    Elem29c() : m298(0) {}
};
void MoveElem29(Elem29c* dst, Elem29c* src);                   // @ 0x0047cf00
Elem29c* Copy29Range(Elem29c* first, Elem29c* last, Elem29c* dest); // @ 0x0047c140
void Construct29Range(Elem29c* dst, uint n, const Elem29c& v);      // @ 0x0047c920
void Shift29(Elem29c* first, Elem29c* last);                        // @ 0x0047c8a0
void Fill29(Elem29c* dst, uint n, const Elem29c& v);                // @ 0x0047bbf0
struct Vec29c {
    Elem29c* mpBegin; Elem29c* mpEnd; Elem29c* mpCapacity;
    void Elem29Insert(Elem29c* position, uint n, const Elem29c& value);
};
struct E12_s0047_8930 { float x, y, z; };
void* Copy12Range(const void* first, const void* last, void* dest);   // @ 0x004b66b0
void  Construct12Range(void* dst, uint n, const void* v);             // @ 0x0047ca00
void* Move12Range(const void* first, const void* last, void* dest);   // @ 0x004b6bf0
struct AllocHolder { void* mpData; };
struct Vec12 {
    E12_s0047_8930* mpBegin; E12_s0047_8930* mpEnd; E12_s0047_8930* mpCapacity;
    AllocHolder alloc;                    // +0xc
    void Elem12Insert(E12_s0047_8930* position, uint n, const E12_s0047_8930& value);
};
// ---- items of slice s00478930 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
void Shift12Out(E12_s0047_8930** out, E12_s0047_8930* first, E12_s0047_8930* last, E12_s0047_8930* dest);   // defined at 0x004797a0, called earlier in the TU

// ---- items of slice s00479830 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct P8  { uint a, b; };
struct P16 { uint a, b, c, d; };
struct AllocBlock { uint mPad0; uint mHeapFlag; };
struct V8 { P8* mpBegin; P8* mpEnd; P8* mpCapacity; uint mAlloc; void Insert8(P8* position, uint n, const P8& value); };
void  Construct8 (void* dst, uint n, const void* v);          // @ 0x0047ca70
void* UninitCopy8Destruct(void* first, void* last, void* dest);  // @ 0x004763a0
void* Copy8Range (const void* first, const void* last, void* dest);  // @ 0x00476290
void  Shift8Range(void* out, void* first, void* last, void* dest);   // @ 0x00479c00
void  operator_delete__(void* p);                              // @ 0x00f47380
void  Construct16(void* dst, uint n, const void* v);          // @ 0x0052c8f0
void* Copy16Range(const void* first, const void* last, void* dest);
void  Shift16Range(void* out, void* first, void* last, void* dest);  // @ 0x00541450
struct Elem16Iter_s0047_9830 { P16* mIterator; Elem16Iter_s0047_9830(P16* p) : mIterator(p) {} };
// ---- items of slice s00479830 end

// ---- items of slice s0047a5a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  FUN_00f47380(void* p);                                           // @ 0x00f47380
struct Matrix44 {
    float m[16];
    Matrix44() {}
    Matrix44(const Matrix44& o) { for (int i = 0; i < 16; ++i) m[i] = o.m[i]; }
};
struct VM44 { Matrix44* mpBegin; Matrix44* mpEnd; Matrix44* mpCapacity; void Insert(Matrix44* position, uint n, const Matrix44& value); };
struct V16 { P16* mpBegin; P16* mpEnd; P16* mpCapacity; void Insert(P16* position, uint n, const P16& value); };
void  ConstructM44(void* dst, uint n, const void* v);          // @ 0x0047cbe0
void  ShiftM44(void* out, void* first, void* last, void* dest); // @ 0x0047cb60
void* UninitCopyM44(const void* first, const void* last, void* dest); // @ 0x0045dc00
void  Shift16(void* out, void* first, void* last, void* dest);  // @ 0x0047cc40
void* Copy16(const void* first, const void* last, void* dest);  // @ 0x0047c240
struct Elem20
{
    uint32_t w0, w1, w2, w3, w4;
    Elem20& operator=(const Elem20& o)
    {
        w0 = o.w0; w1 = o.w1; w2 = o.w2; w3 = o.w3; w4 = o.w4;
        return *this;
    }
};
struct Elem32
{
    uint32_t w0, w1, w2, w3;
    uint32_t h0, h1, h2, h3;                 // 0x10-byte Handle
    Elem32(const Elem32& src);               // 0x00423080
    Elem32& operator=(const Elem32& src);    // 0x00424f10
};
struct Vec32Alloc { uint32_t mPad; };        // empty EASTL allocator, occupies 4 bytes
void    Construct32(Elem32* dst, uint n, const Elem32& value);            // 0x0047cd20
void    ShiftUp32(void** out, Elem32* first, Elem32* last, Elem32* dest); // 0x0047b290
Elem32* UninitMove32(Elem32* first, Elem32* last, Elem32* dest);          // 0x0042a730
struct Vec32_s0047_a5a0
{
    Elem32*    mpBegin;
    Elem32*    mpEnd;
    Elem32*    mpCapacity;
    Vec32Alloc mAllocator;

    void DoInsertValues(Elem32* position, uint n, const Elem32& value);
};
// ---- items of slice s0047a5a0 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
Matrix44* CopyM44Range(Matrix44* first, Matrix44* last, Matrix44* dest);   // defined at 0x0047a9a0, called earlier in the TU

// ---- items of slice s0047b480 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl FUN_0041cb40(void* dst, const void* src); // cSPMatrix3::Assign
template <int N> inline void ScratchSlots_s0047_b480() { unsigned int slots[N]; }
struct Counted_s0047_b480 {
    char pad[0x40];
    int mRefCount;
    void Release();  // 0x0040f360 (Counted::Release)
};
struct E16 { float a, b, c, d; };
struct M33 { float m[12]; };
struct Big { uint a, b, c, d, e; M33 mat; Big* CopyBig(const Big* src); };
void  MoveBig(void* dst, void* src);                     // copy-construct a 0x29c element (0x0047bbf0)
void  CopyElems29(void* first, void* last, void* dest);  // @ 0x0047c980
void  Move16(void* p);                                   // @ 0x00401b80
void  CopyElems16(void* first, void* last, void* dest);  // @ 0x0047d3f0
extern "C" void __cdecl FUN_0047c600(void* self, uint n);          // basic_string reserve
extern "C" void* __cdecl FUN_011e073e(void* p, int c, uint n);     // memset
struct Str8_s0047_b480 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    Str8_s0047_b480* resize(uint n, char c);  // 0x00478930 (Str8::resize)
};
struct cSPMatrix3_s0047_b480 {                                     // 0x24 bytes
    float m[9];
    cSPMatrix3_s0047_b480() {}
    // Inline copy ctor: reserves the frame slots the original leaves behind, then
    // delegates the actual copy to the out-of-line assignment helper.
    cSPMatrix3_s0047_b480(const cSPMatrix3_s0047_b480& o) { ScratchSlots_s0047_b480<11>(); Assign(o); }
    void Assign(const cSPMatrix3_s0047_b480& o);                   // 0x0041cb40
};
struct cSPTransform_s0047_b480 {                                   // 0x38 bytes
    unsigned short mFlags;                              // +0x00
    unsigned short mModCount;                           // +0x02
    float mTranslation[3];                              // +0x04
    float mScale;                                       // +0x10
    float mRotation[9];                                 // +0x14
    cSPTransform_s0047_b480& operator=(const cSPTransform_s0047_b480& o);     // 0x00537dc0
};
void EAFreeArray(void* p);                                                              // 0x00f47380
cSPTransform_s0047_b480* UninitializedCopy56(const cSPTransform_s0047_b480* first, const cSPTransform_s0047_b480* last,
                                  cSPTransform_s0047_b480* dest);                                  // 0x0042e510
struct RandomAccessTag { };
struct TransformVec {                                   // begin, end, capacity, allocator
    cSPTransform_s0047_b480* mpBegin;                              // +0x00
    cSPTransform_s0047_b480* mpEnd;                                // +0x04
    cSPTransform_s0047_b480* mpCapacity;                           // +0x08
    uint32_t mAllocator;                                // +0x0c

    cSPTransform_s0047_b480* DoRealloc(uint n, const cSPTransform_s0047_b480* first,
                            const cSPTransform_s0047_b480* last);                              // 0x0042e4b0
    static cSPTransform_s0047_b480* CopyImpl(const cSPTransform_s0047_b480* first, const cSPTransform_s0047_b480* last,
                                  cSPTransform_s0047_b480* dest, bool b0, bool b1, bool b2)
    {
        for (; first != last; ++dest, ++first)
            *dest = *first;
        return dest;
    }
    static cSPTransform_s0047_b480* Copy(const cSPTransform_s0047_b480* first, const cSPTransform_s0047_b480* last,
                              cSPTransform_s0047_b480* dest)
    {
        bool b2 = false, b0 = false, b1 = false;
        return CopyImpl(first, last, dest, b0, b1, b2);
    }
    static void DoDestroyValues(cSPTransform_s0047_b480* first, cSPTransform_s0047_b480* last)
    {
        for (; first < last; ++first) {}
    }
    void DoFree(cSPTransform_s0047_b480* p, uint)
    {
        if (p && ((int*)p)[-1] != 0) {
            void* q = p;
            EAFreeArray(q);
        }
    }
    void DoAssignFromIterator(const cSPTransform_s0047_b480* first, const cSPTransform_s0047_b480* last,
                              RandomAccessTag tag);
};
struct SortKey {
    float mKey[2];
    SortKey(const SortKey& o) { mKey[0] = o.mKey[0]; mKey[1] = o.mKey[1]; }
    float& operator[](int i) { return mKey[i]; }
    const float& operator[](int i) const { return mKey[i]; }
};
struct KeyLess {
    bool operator()(const SortKey& a, const SortKey& b) const { return a[0] < b[0]; }
};
SortKey* GetPartition(SortKey* first, SortKey* last, SortKey pivot, KeyLess pred);  // 0x0047c400
void     PartialSort(SortKey* first, SortKey* middle, SortKey* last, KeyLess pred); // 0x0047c4e0
struct Vec3f {                                         // user copy ctor/assign: inline pointer temps
    float v[3];
    Vec3f() {}
    Vec3f(const Vec3f& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; }
    void operator=(const Vec3f& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; }
};
struct Vec4f {
    float v[4];
    Vec4f() {}
    Vec4f(const Vec4f& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; v[3] = o.v[3]; }
};
struct Obj8C {                                          // 0x8c bytes
    uint16_t mFlags0;                                   // +0x00
    uint16_t mCount2;                                   // +0x02
    uint16_t m4;                                        // +0x04
    uint16_t m6;                                        // +0x06
    uint16_t m8;                                        // +0x08
    uint8_t mA;                                         // +0x0a
    uint8_t mB;                                         // +0x0b
    uint16_t mC;                                        // +0x0c
    uint16_t mE;                                        // +0x0e
    uint8_t m10;                                        // +0x10
    uint8_t m11;                                        // +0x11
    uint16_t m12;                                       // +0x12
    Vec3f mV14;                                         // +0x14
    Vec3f mV20;                                         // +0x20
    float m2C;                                          // +0x2c
    cSPMatrix3_s0047_b480 mRot30;                                  // +0x30
    Vec3f mV54;                                         // +0x54
    Vec3f mV60;                                         // +0x60
    float m6C, m70, m74, m78;                           // +0x6c
    float m7C;                                          // +0x7c
    uint32_t m80;                                       // +0x80
    uint32_t m84;                                       // +0x84
    uint32_t m88;                                       // +0x88
    Obj8C(const Obj8C& o);
};
struct Blk40D { uint32_t m[0x28]; };                    // 160 bytes
struct Blk10D { uint32_t m[0x0a]; };                    //  40 bytes
struct Blk64D { uint32_t m[0x40]; };                    // 256 bytes
struct Blk16D { uint32_t m[0x10]; };                    //  64 bytes
struct RefObj40 {                                       // refcount at +0x40
    uint32_t mPad[0x10];
    int mRefCount;                                      // +0x40
    void AddRef() { ++mRefCount; }
};
struct ObjPtr298 {                                      // AutoRefCount-style member
    RefObj40* mpObj;
    ObjPtr298(const ObjPtr298& o) : mpObj(o.mpObj) { if (mpObj) mpObj->AddRef(); }
};
struct Obj29C {                                         // 0x29c bytes
    uint32_t m0;                                        // +0x000
    Blk40D m4;                                          // +0x004
    Blk10D mA4;                                         // +0x0a4
    uint32_t mCC;                                       // +0x0cc
    uint32_t mD0;                                       // +0x0d0
    uint32_t mD4;                                       // +0x0d4
    uint32_t mD8;                                       // +0x0d8
    uint32_t mDC;                                       // +0x0dc
    Vec3f mE0;                                          // +0x0e0
    uint32_t mEC;                                       // +0x0ec
    Vec3f mF0;                                          // +0x0f0
    Vec3f mFC;                                          // +0x0fc
    Vec3f m108;                                         // +0x108
    Vec4f m114;                                         // +0x114
    Vec3f m124;                                         // +0x124
    Vec3f m130;                                         // +0x130
    float m13C;                                         // +0x13c
    float m140;                                         // +0x140
    uint32_t m144;                                      // +0x144
    uint32_t m148;                                      // +0x148
    uint32_t m14C;                                      // +0x14c
    uint32_t m150;                                      // +0x150
    uint32_t m154;                                      // +0x154
    Blk64D m158;                                        // +0x158
    Blk16D m258;                                        // +0x258
    ObjPtr298 mObj298;                                  // +0x298
    Obj29C(const Obj29C& o);
};
void MoveBig(void* dst, void* src)
{
    new (dst) Obj29C(*(const Obj29C*)src);
}
// ---- items of slice s0047b480 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
const SortKey& Median(const SortKey& a, const SortKey& b, const SortKey& c, KeyLess pred);   // defined at 0x0047c2c0, called earlier in the TU

// ---- items of slice s0047c400 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)
void* EASTL_allocator_allocate(uint32_t n, const char* pName, int flags, int align, const char* pFile, int line);  // @ 0x00f473a0
void* EASTL_memmove(void* pDest, const void* pSource, uint32_t n);                                                 // @ 0x011e0744
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
void pop_heap(FloatKeyPair* first, FloatKeyPair* last, FloatKeyLess compare);                                     // @ 0x0047d4f0
inline void sort_heap(FloatKeyPair* first, FloatKeyPair* last, FloatKeyLess compare)
{
    for (; (last - first) > 1; --last)
        pop_heap(first, last, compare);
}
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
// ---- items of slice s0047c400 end

// @ 0x00401930
void __stdcall VectorConstructorIterator(void* p, unsigned int size, int count, ElementCtorDtor ctor)
{
    while (--count >= 0) {
        (((ArrayElement*)p)->*ctor)();
        p = (char*)p + size;
    }
}

// @ 0x00454cb0
BasicString* BasicString::assign(const char* first, const char* last)
{
    unsigned n = (unsigned)(last - first);
    if (n > (unsigned)(mpEnd - mpBegin)) {
        // too long for the current buffer: keep the bytes that fit and append the rest
        FUN_11e0744_memcpy(mpBegin, first, (unsigned)(mpEnd - mpBegin));
        append(first + (mpEnd - mpBegin), last);
    } else {
        FUN_11e0744_memcpy(mpBegin, first, n);
        erase(mpBegin + n, mpEnd);
    }
    return this;
}

// @ 0x00455d60
int* StringAppend(int* self, const char* first, const char* last)
{
    if (first != last) {
        int oldSize = self[1] - self[0];
        int n = (int)last - (int)first;
        unsigned int capacity = (unsigned int)((self[2] - self[0]) - 1);
        if (capacity < (unsigned int)(oldSize + n)) {
            unsigned int newCap = (unsigned int)(oldSize + n);
            unsigned int cap2 = capacity <= 8 ? 8 : capacity * 2;
            unsigned int alloc = (cap2 < newCap ? newCap : cap2) + 1;
            char* p = (char*)FUN_11e0744_alloc(alloc);
            FUN_11e0744_copy(p, (void*)self[0], oldSize);
            FUN_11e0744_copy(p + oldSize, (void*)first, n);
            p[oldSize + n] = 0;
            if (self[2] - self[0] > 1) {
                if (self[0] != 0)
                    EASTL_allocator_deallocate((void*)self[0], 0);
            }
            self[0] = (int)p;
            self[1] = (int)(p + oldSize + n);
            self[2] = (int)(p + alloc);
        } else {
            FUN_11e0744_copy((void*)(self[1] + 1), (void*)(first + 1), n - 1);
            *(char*)(self[1] + n) = 0;
            *(char*)self[1] = *first;
            self[1] += n;
        }
    }
    return self;
}

// @ 0x00473dc0
template void vector<Pair8, 4>::resize(uint32_t)
;

// @ 0x004742e0
template vector_s0047_3e40<Elem16, 4>::vector_s0047_3e40(const vector_s0047_3e40<Elem16, 4>&)
;

// @ 0x004744d0
template void vector_s0047_3e40<Elem16, 4>::reserve(uint32_t)
;

// @ 0x004751a0
void Vec16::resize(uint n)
{
    if (n > (uint)(mpEnd - mpBegin)) {
        StreamDesc tmp;
        ScratchSlots_s0047_4bd0<15>();
        Fill(mpEnd, n - (uint)(mpEnd - mpBegin), &tmp);
        if (tmp.mpOwner) tmp.mpOwner->Release();
    } else {
        Erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00475260
void Vec32::resize(uint n)
{
    if (n > (uint)((mpEnd - mpBegin) >> 5)) {
        StreamElem tmp;
        ScratchSlots_s0047_4bd0<14>();
        Fill32(mpEnd, n - (uint)((mpEnd - mpBegin) >> 5), &tmp);
        if (tmp.mDesc.mpOwner) tmp.mDesc.mpOwner->Release();
    } else {
        Erase32(mpBegin + n * 0x20, mpEnd);
    }
}

// @ 0x00475930
namespace eastl {
basic_string_s0047_4bd0& basic_string_s0047_4bd0::append_sprintf_va_list(const char* fmt, void* args)
{
    const int nPrevLength = (int)(mpEnd - mpBegin);
    int n;
    if ((ushort*)mpBegin == &gEmptyString)
        n = Vsnprintf8(mpEnd, 0, fmt, args);
    else
        n = Vsnprintf8(mpEnd, (uint)(mpCapacity - mpEnd), fmt, args);

    if (n < (int)(mpCapacity - mpEnd)) {
        if (n < 0) {
            uint a = (uint)(mpEnd - mpBegin) * 2;
            uint b = 7;
            uint nCap = (a < 8) ? b : a;     // max(2*size, 8)-1 style growth
            for (; n < 0 && nCap < 1000000; nCap <<= 1) {
                set_capacity(nCap);
                n = Vsnprintf8(mpBegin + nPrevLength, (nCap + 1) - nPrevLength, fmt, args);
            }
        }
    } else {
        set_capacity(nPrevLength + n);
        n = Vsnprintf8(mpBegin + nPrevLength, n + 1, fmt, args);
    }
    if (-1 < n)
        mpEnd = mpBegin + nPrevLength + n;
    return *this;
}
}  // namespace eastl

// @ 0x00475ab0
namespace eastl {
void basic_string_s0047_4bd0::RangeInitialize(uint n)
{
    if (n < 2) {
        mpBegin = (char*)&gEmptyString;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    } else {
        mpBegin = (char*)operator_new_eastl(n, "Editor", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        mpEnd = mpBegin;
        mpCapacity = mpBegin + n;
    }
}
}  // namespace eastl

// @ 0x00475ef0
E12* UninitCopy12(E12* first, E12* last, E12* dest)
{
    E12* result = dest;
    for (E12* p = first; p != last; ++p, ++result) {
        if (result) { *result = *p; }
    }
    return result;
}

// @ 0x00478620
void IntrosortRange(char* first, char* last, char pred)
{
    if (first != last) {
        uint n = (uint)(last - first) >> 3;
        uint depth = 0;
        for (uint t = n; t != 0; t >>= 1) ++depth;
        (void)pred;
        // introsort: depth-limited quicksort then insertion sort
        (void)depth;
    }
}

// @ 0x00478930
void Str8::resize(uint n)
{
    const uint cur = (uint)(mpEnd - mpBegin);
    if (n < cur) {
        Shrink(mpBegin + n, mpEnd);
    } else if (n > cur) {
        ResizeFill(n - cur, 0);
    }
}

// @ 0x00478990
void IntVec::IntVectorInsert(int* position, uint n, const int& value)
{
    if ((uint)(mpCapacity - mpEnd) < n) {
        uint oldSize = (uint)(mpEnd - mpBegin);
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        int* pNew = newSize ? (int*)EASTL_Allocate(mpCapacity, newSize * 4, 4, 0) : 0;
        int* p = CopyIntRange(mpBegin, position, pNew);
        FillInts(p, n, value);
        int* pNewEnd = CopyIntRange(position, mpEnd, p + n);
        if (mpBegin) EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        int v = value;
        uint tail = (uint)(mpEnd - position);
        if (n < tail) {
            int* newEnd = MoveIntsBack(position, mpEnd, mpEnd + n);
            DestroyInts(position, position + n);
            FillInts(position, n, v);
            (void)newEnd;
        } else {
            FillInts(mpEnd, n - tail, v);
            mpEnd += n - tail;
            CopyIntRange(position, mpEnd - n, mpEnd);
            mpEnd += tail;
            FillInts(position, tail, v);
        }
    }
}

// @ 0x00478db0
RefPtr& RefPtr::operator=(Counted_s0047_8930* p)
{
    ScratchSlots<2>();
    if (p != mpObject) {
        Counted_s0047_8930* old = mpObject;
        if (p) p->mRefCount += 1;
        mpObject = p;
        if (old) old->Release();
    }
    return *this;
}

// @ 0x00478e00
void Vec29c::Elem29Insert(Elem29c* position, uint n, const Elem29c& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 0x29c < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 0x29c;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        Elem29c* pNew = newSize ? (Elem29c*)EASTL_Allocate(mpCapacity, newSize * 0x29c, 4, 0) : 0;
        Elem29c* p = Copy29Range(mpBegin, position, pNew);
        Construct29Range(p, n, value);
        Elem29c* pNewEnd = Copy29Range(position, mpEnd, p + n);
        if (mpBegin) EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        Elem29c v = value;
        uint tail = (uint)((char*)mpEnd - (char*)position) / 0x29c;
        if (n < tail) {
            Shift29(position, mpEnd);
            mpEnd += n;
            Elem29c* q = mpEnd - n;
            while (q != position) { --q; MoveElem29(q, q + n); }
            Fill29(position, n, v);
        } else {
            Construct29Range(mpEnd, n - tail, v);
            mpEnd += n - tail;
            Shift29(position, mpEnd - n + tail);
            Fill29(position, n, v);
        }
    }
}

// @ 0x00479330
void Vec12::Elem12Insert(E12_s0047_8930* position, uint n, const E12_s0047_8930& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 0xc < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 0xc;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        E12_s0047_8930* pNew = newSize ? (E12_s0047_8930*)EASTL_Allocate(&alloc, newSize * 0xc, 4, 0) : 0;
        E12_s0047_8930* p = (E12_s0047_8930*)Copy12Range(mpBegin, position, pNew);
        Construct12Range(p, n, &value);
        E12_s0047_8930* pNewEnd = (E12_s0047_8930*)Move12Range(position, mpEnd, p + n);
        // eastl's debug header in front of the block gates the release.
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        E12_s0047_8930 v = value;
        uint tail = (uint)((char*)mpEnd - (char*)position) / 0xc;
        if (n < tail) {
            E12_s0047_8930* tmp;
            Shift12Out(&tmp, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            E12_s0047_8930* q = mpEnd - n;
            while (q != position) { --q; q[n] = *q; }
            for (E12_s0047_8930* w = position; w != position + n; ++w) *w = v;
        } else {
            Construct12Range(mpEnd, n - tail, &v);
            mpEnd += n - tail;
            Move12Range(position, mpEnd - n + tail, position + n);
            mpEnd += tail;
            for (E12_s0047_8930* w = position; w != position + n; ++w) *w = v;
        }
    }
}

// @ 0x004797a0
void Shift12Out(E12_s0047_8930** out, E12_s0047_8930* first, E12_s0047_8930* last, E12_s0047_8930* dest)
{
    E12_s0047_8930* d = dest;
    while (first != last) {
        if (d) { d->x = first->x; d->y = first->y; d->z = first->z; }
        ++first;
        ++d;
    }
    *out = d;
}

// @ 0x00479830
void V8::Insert8(P8* position, uint n, const P8& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 8 < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 8;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        P8* pNew = newSize ? (P8*)EASTL_Allocate(&mAlloc, newSize * 8, 4, 0) : 0;
        P8* p = (P8*)UninitCopy8Destruct(mpBegin, position, pNew);
        Construct8(p, n, &value);
        P8* pNewEnd = (P8*)UninitCopy8Destruct(position, mpEnd, p + n);
        if (mpBegin && ((AllocBlock*)mpBegin)[-1].mHeapFlag != 0)
            operator_delete__(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        P8 v = value;
        P8* oldEnd = mpEnd;
        uint tail = (uint)((char*)oldEnd - (char*)position) / 8;
        if (n < tail) {
            P8* outv;
            Shift8Range(&outv, oldEnd - n, oldEnd, oldEnd);
            mpEnd = oldEnd + n;
            P8* src = oldEnd - n;
            P8* dst = oldEnd;
            while (src != position) { --src; --dst; *dst = *src; }
            for (P8* w = position; w != position + n; ++w) *w = v;
        } else {
            Construct8(oldEnd, n - tail, &v);
            mpEnd = oldEnd + (n - tail);
            Copy8Range(position, oldEnd, mpEnd);
            mpEnd += tail;
            for (P8* w = position; w != oldEnd; ++w) *w = v;
        }
    }
}

// @ 0x00479c00
P8** Shift8Out(P8** out, P8* first, P8* last, P8* dest)
{
    P8* d = dest;
    for (; first != last; ++first) {
        if (d) {
            ((float*)d)[0] = ((float*)first)[0];
            ((float*)d)[1] = ((float*)first)[1];
        }
        ++d;
    }
    *out = d;
    return out;
}

// @ 0x00479c80
void Insert8b(P8*& mpBegin, P8*& mpEnd, P8*& mpCapacity, P8* position, uint n, const P8& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 8 < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 8;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        P8* pNew = newSize ? (P8*)EASTL_Allocate(mpCapacity, newSize * 8, 2, 0) : 0;
        P8* p = (P8*)Copy8Range(mpBegin, position, pNew);
        Construct16(p, n, &value);
        P8* pNewEnd = (P8*)Copy8Range(position, mpEnd, p + n);
        if (mpBegin) EASTL_Allocate(mpBegin, 0, 0, 0);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        P8 v = value;
        uint tail = (uint)((char*)mpEnd - (char*)position) / 8;
        if (n < tail) {
            Shift16Range(position, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            P8* p = mpEnd - n;
            while (p != position) { --p; p[n] = *p; }
            for (P8* w = position; w != position + n; ++w) *w = v;
        } else {
            Construct16(mpEnd, n - tail, &v);
            mpEnd += n - tail;
            Copy16Range(position, mpEnd - n + tail, position + n);
            mpEnd += tail;
            for (P8* w = position; w != position + n; ++w) *w = v;
        }
    }
}

// @ 0x0047a040
void Insert16(P16*& mpBegin, P16*& mpEnd, P16*& mpCapacity, P16* position, uint n, const P16& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 0x10 < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 0x10;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        P16* pNew = newSize ? (P16*)EASTL_Allocate(mpCapacity, newSize * 0x10, 4, 0) : 0;
        P16* p = pNew;
        P16* pNewEnd = pNew + oldSize + n;
        (void)p;
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        P16 v = value;
        uint tail = (uint)((char*)mpEnd - (char*)position) / 0x10;
        if (n < tail) {
            Shift16Range(position, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            P16* p = mpEnd - n;
            while (p != position) { --p; p[n] = *p; }
            for (P16* w = position; w != position + n; ++w) *w = v;
        } else {
            Construct16(mpEnd, n - tail, &v);
            mpEnd += n - tail;
            Copy16Range(position, mpEnd - n + tail, position + n);
            mpEnd += tail;
            for (P16* w = position; w != position + n; ++w) *w = v;
        }
    }
}

// @ 0x0047a500
Elem16Iter_s0047_9830 UninitializedCopy_Elem16(Elem16Iter_s0047_9830 first, Elem16Iter_s0047_9830 last, Elem16Iter_s0047_9830 dest, false_type2)
{
    P16* p = dest.mIterator;
    for (P16* s = first.mIterator; s != last.mIterator; ++s, ++p) {
        if (p) *p = *s;
    }
    for (P16* q = first.mIterator; q != last.mIterator; ++q) {}
    return Elem16Iter_s0047_9830(p);
}

// @ 0x0047a5a0
void VM44::Insert(Matrix44* position, uint n, const Matrix44& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 0x40 < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 0x40;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        // the empty allocator subobject is at this+0xc (0x0047a870: `lea eax,[edx+0xc]; push eax`)
        Matrix44* pNew = newSize ? (Matrix44*)EASTL_Allocate((char*)this + 0xc, newSize * 0x40, 4, 0) : 0;
        Matrix44* p = CopyM44Range(mpBegin, position, pNew);
        ConstructM44(p, n, &value);
        Matrix44* pNewEnd = CopyM44Range(position, mpEnd, p + n);
        // deallocate through the shared allocator, only when the block header dword is set
        // (0x0047a941: `cmp dword [eax-4],0 / je skip`, then call 0x00f47380)
        if (mpBegin && ((uint*)mpBegin)[-1] != 0) FUN_00f47380(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        Matrix44 v = value;
        Matrix44* oldEnd = mpEnd;
        uint tail = (uint)((char*)oldEnd - (char*)position) / 0x40;
        if (n < tail) {
            // 0x0047cb60 writes its result pointer through its first argument (and returns it):
            // the original passes a stack local (`lea edx,[ebp-0x64]`, the discarded return slot),
            // never `position` - writing the helper's out value into the element array corrupted
            // the vector contents the caller passed in (memory pool mismatch at position + n*0x40).
            Matrix44* shifted;
            ShiftM44(&shifted, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            Matrix44* p = mpEnd - n;
            while (p != position) { --p; p[n] = *p; }
            for (Matrix44* w = position; w != position + n; ++w) *w = v;
        } else {
            ConstructM44(mpEnd, n - tail, &v);
            mpEnd += n - tail;
            // the n >= tail path uses the generic uninitialized_copy (0x0045dc00), not vec::Copy
            UninitCopyM44(position, mpEnd - n + tail, position + n);
            mpEnd += tail;
            // bound is the old end (`cmp ecx,[ebp-0x4]` at 0x0047a7db), not position + n:
            // only the elements that were already present get overwritten with the value
            for (Matrix44* w = position; w != oldEnd; ++w) *w = v;
        }
    }
}

// @ 0x0047a9a0
Matrix44* CopyM44Range(Matrix44* first, Matrix44* last, Matrix44* dest)
{
    Matrix44* d = dest;
    for (Matrix44* s = first; s != last; s += 1) {
        if (d) *d = *s;
        d += 1;
    }
    for (Matrix44* q = first; q != last; q += 1) {}
    return d;
}

// @ 0x0047aa40
void V16::Insert(P16* position, uint n, const P16& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 0x10 < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 0x10;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        P16* pNew = newSize ? (P16*)EASTL_Allocate(mpCapacity, newSize * 0x10, 4, 0) : 0;
        P16* p = pNew;
        P16* pNewEnd = pNew + oldSize + n;
        (void)p;
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        P16 v = value;
        uint tail = (uint)((char*)mpEnd - (char*)position) / 0x10;
        if (n < tail) {
            Shift16(position, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            P16* p = mpEnd - n;
            while (p != position) { --p; p[n] = *p; }
            for (P16* w = position; w != position + n; ++w) *w = v;
        } else {
            Construct16(mpEnd, n - tail, &v);
            mpEnd += n - tail;
            Copy16(position, mpEnd - n + tail, position + n);
            mpEnd += tail;
            for (P16* w = position; w != position + n; ++w) *w = v;
        }
    }
}

// @ 0x0047ae60
void Vec32_s0047_a5a0::DoInsertValues(Elem32* position, uint n, const Elem32& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 0x20 < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 0x20;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        Elem32* pNew = newSize ? (Elem32*)EASTL_Allocate(&mAllocator, newSize * 0x20, 4, 0) : 0;
        Elem32* p = UninitMove32(mpBegin, position, pNew);
        Construct32(p, n, value);
        p = UninitMove32(position, mpEnd, p + n);
        if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0) FUN_00f47380(mpBegin);
        mpBegin = pNew;
        mpEnd = p;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        Elem32 v = value;
        uint tail = (uint)((char*)mpEnd - (char*)position) / 0x20;
        Elem32* oldEnd = mpEnd;
        if (n < tail) {
            Elem32* out;
            ShiftUp32((void**)&out, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            Elem32* s = oldEnd;
            Elem32* d = oldEnd - n;
            while (d != position) { d -= 1; s -= 1; *s = *d; }
            for (Elem32* w = position; w != position + n; ++w) *w = v;
        } else {
            Elem32* out;
            Construct32(mpEnd, n - tail, v);
            mpEnd += n - tail;
            ShiftUp32((void**)&out, position, oldEnd, mpEnd);
            mpEnd += tail;
            for (Elem32* w = position; w != oldEnd; ++w) *w = v;
        }
    }
}

// @ 0x0047b3d0
Elem20* Copy20Range(Elem20* first, Elem20* last, Elem20* dest)
{
    Elem20* d = dest;
    Elem20* s = first;
    while (s != last) {
        if (d) *d = *s;
        ++s;
        ++d;
    }
    for (Elem20* q = first, * r = dest; q != last; ++q, ++r) {}
    return d;
}

// @ 0x0047b480
void TransformVec::DoAssignFromIterator(const cSPTransform_s0047_b480* first, const cSPTransform_s0047_b480* last, RandomAccessTag)
{
    const uint n = (uint)(last - first);

    if (n > (uint)(mpCapacity - mpBegin)) {
        cSPTransform_s0047_b480* const pNewData = DoRealloc(n, first, last);
        ScratchSlots_s0047_b480<10>();
        DoDestroyValues(mpBegin, mpEnd);
        DoFree(mpBegin, (uint)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
    }
    else if (n <= (uint)(mpEnd - mpBegin)) {
        cSPTransform_s0047_b480* const pNewEnd = Copy(first, last, mpBegin);
        DoDestroyValues(pNewEnd, mpEnd);
        mpEnd = pNewEnd;
    }
    else {
        const cSPTransform_s0047_b480* position = first + (mpEnd - mpBegin);
        Copy(first, position, mpBegin);
        mpEnd = UninitializedCopy56(position, last, mpEnd);
    }
    ScratchSlots_s0047_b480<14>();
}

// @ 0x0047b6d0
void QuickSortImpl(SortKey* first, SortKey* last, int depth, KeyLess pred)
{
    while ((last - first) > 28 && depth > 0) {
        SortKey* position = GetPartition(first, last,
            Median(*first, *(first + (last - first) / 2), *(last - 1), pred), pred);
        --depth;
        QuickSortImpl(position, last, depth, pred);
        last = position;
    }
    if (depth == 0) {
        ScratchSlots_s0047_b480<14>();
        PartialSort(first, last, last, pred);
    }
}

// @ 0x0047b7b0
float* InsertionSort8F(float* first, float* last)
{
    if (first == last || first + 2 == last) return first;
    float* cur = first;
    while (cur + 2 != last) {
        float* p = cur + 2;
        float k0 = p[0], k1 = p[1];
        float* w = p;
        while (w != first && k0 < cur[0]) {
            float t = cur[1];
            w[0] = cur[0]; w[1] = t;
            w -= 2;
            cur -= 2;
        }
        w[0] = k0; w[1] = k1;
        cur = p;
    }
    return last;
}

// @ 0x0047b890
void InsertionSort8F2(float* first, float* last)
{
    for (float* i = first; i != last; i += 2) {
        float* w = i;
        float k0 = i[0], k1 = i[1];
        float* p = i;
        while (p - 2 >= first && k0 < p[-2]) {
            float t = p[-1];
            w[0] = p[-2]; w[1] = t;
            w -= 2; p -= 2;
        }
        w[0] = k0; w[1] = k1;
    }
}

// @ 0x0047b950
Obj8C::Obj8C(const Obj8C& o)
: mFlags0(o.mFlags0), mCount2(o.mCount2), m4(o.m4), m6(o.m6), m8(o.m8),
      mA(o.mA), mB(o.mB), mC(o.mC), mE(o.mE), m10(o.m10), m11(o.m11), m12(o.m12),
      mV14(o.mV14), mV20(o.mV20), m2C(o.m2C), mRot30(o.mRot30),
      mV54(o.mV54), mV60(o.mV60), m6C(o.m6C), m70(o.m70), m74(o.m74), m78(o.m78),
      m7C(o.m7C), m80(o.m80), m84(o.m84), m88(o.m88)
{
}

// @ 0x0047bb70
Big* Big::CopyBig(const Big* src)
{
    Big* dst = this;
    dst->a = src->a; dst->b = src->b; dst->c = src->c; dst->d = src->d; dst->e = src->e;
    ((void(__thiscall*)(void*, const void*))FUN_0041cb40)(&dst->mat, &src->mat);
    return dst;
}

// @ 0x0047bbf0
Obj29C::Obj29C(const Obj29C& o)
: m0(o.m0), m4(o.m4), mA4(o.mA4), mCC(o.mCC), mD0(o.mD0), mD4(o.mD4), mD8(o.mD8), mDC(o.mDC),
      mE0(o.mE0), mEC(o.mEC), mF0(o.mF0), mFC(o.mFC), m108(o.m108), m114(o.m114), m124(o.m124),
      m130(o.m130), m13C(o.m13C), m140(o.m140), m144(o.m144), m148(o.m148), m14C(o.m14C),
      m150(o.m150), m154(o.m154), m158(o.m158), m258(o.m258), mObj298(o.mObj298)
{
}

// @ 0x0047bf30
Str8_s0047_b480* Str8_s0047_b480::resize(uint n, char c)
{
    const uint cur = (uint)(mpEnd - mpBegin);
    const uint cap = (uint)(mpCapacity - mpBegin) - 1;
    if (cur + n > cap) {
        const uint target = cur + n;
        const uint cap2 = cap > 8 ? cap * 2 : 8;
        const uint chosen = cap2 >= target ? cap2 : target;
        ((void(__thiscall*)(void*, uint))FUN_0047c600)(this, chosen);
    }
    if (n) {
        FUN_011e073e(mpEnd + 1, (unsigned char)c, n - 1);
        *mpEnd = c;
        mpEnd += n;
        *mpEnd = 0;
    }
    return this;
}

// @ 0x0047c010
Counted_s0047_b480** CopyRefs(Counted_s0047_b480** first, Counted_s0047_b480** last, Counted_s0047_b480** dest)
{
    for (; first != last; ++first) {
        if (dest) {
            *dest = *first;
            if (*dest) (*dest)->mRefCount += 1;
        }
        ++dest;
    }
    return dest;
}

// @ 0x0047c0d0
void AssignRefs(Counted_s0047_b480** first, Counted_s0047_b480** last, Counted_s0047_b480** value)
{
    for (; first != last; ++first) {
        Counted_s0047_b480* v = *value;
        if (v != *first) {
            Counted_s0047_b480* old = *first;
            if (v) v->mRefCount += 1;
            *first = v;
            if (old) old->Release();
        }
    }
}

// @ 0x0047c140
void* Copy29Range(void* first, void* last, void* dest)
{
    char* d = (char*)dest;
    for (char* s = (char*)first; s != (char*)last; s += 0x29c) {
        if (d) MoveBig(d, s);
        d += 0x29c;
    }
    CopyElems29(first, last, dest);
    return d;
}

// @ 0x0047c1c0
E16* Copy16Range(E16* first, E16* last, E16* dest)
{
    for (; first != last; ++first, ++dest) {
        if (dest) { dest->a = first->a; dest->b = first->b; dest->c = first->c; dest->d = first->d; }
    }
    return dest;
}

// @ 0x0047c240
void* Copy16Ctor(void* first, void* last, void* dest)
{
    char* d = (char*)dest;
    for (char* s = (char*)first; s != (char*)last; s += 0x10) {
        if (d) Move16(s);
        d += 0x10;
    }
    CopyElems16(first, last, dest);
    return d;
}

// @ 0x0047c2c0
const SortKey& Median(const SortKey& a, const SortKey& b, const SortKey& c, KeyLess pred)
{
    if (pred(a, b)) {
        if (pred(b, c)) return b;
        else if (pred(a, c)) return c;
        else return a;
    }
    else if (pred(a, c)) return a;
    else if (pred(b, c)) return c;
    return b;
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
