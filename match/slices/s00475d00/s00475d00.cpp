// Slice s00475d00: eastl::vector<T,sp_vector_allocator> helper members for several element
// types (erase, uninitialized_copy/relocate, DoInsertValue). Built /Od /Ob1 /MD /Gy /TP.
#include "types.h"

typedef unsigned int uint;
void* EASTL_Allocate(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0
void  EASTL_allocator_deallocate(void* p);                               // @ 0x00f47380

struct Counted { void Release(); };                                       // @ 0x40f360
struct AutoRefCount {
    Counted* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};
struct Elem29c {
    char pad[0x158];
    uint32_t a[64];
    uint32_t b[16];
    Counted* m298;
    Elem29c();
    ~Elem29c() { if (m298) m298->Release(); }
};

struct E8  { uint a, b; };
struct E16 { uint a, b, c, d; };
struct E64 { uint q[16]; };                       // 64-byte trivially-copyable element

// range helpers (out of line, relocations masked)
void* MoveRefs(void* first, void* last, void* dest);         // @ 0x0047c780
void  MoveElem29(Elem29c* dst, Elem29c* src);                // @ 0x0047cf00
template<class T> T* UninitCopyRange(T* first, T* last, T* dest);   // out of line

template<class T, int A>
struct vec {
    T* mpBegin; T* mpEnd; T* mpCapacity; void* mAllocator;
    T* DoAllocate(uint n) { return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), A, 0) : 0; }
    void DoFree(T* p) { if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p); }
    void DoInsertValue(T* position, const T& value);
    T* erase(T* first, T* last);
};

template<class T, int A>
void vec<T,A>::DoInsertValue(T* position, const T& value)
{
    if (mpEnd != mpCapacity) {
        const T& v = value;                       // handle self-insert (see disasm)
        T* pEnd = mpEnd;
        if (pEnd) *pEnd = *(pEnd - 1);
        T* p = pEnd;
        T* q = pEnd - 1;
        while (q != position) { p[-1] = q[-1]; --p; --q; }
        *position = v;
        ++mpEnd;
    } else {
        const uint oldSize = (uint)(mpEnd - mpBegin);
        uint newSize = oldSize ? oldSize * 2 : 1;
        T* pNewData = DoAllocate(newSize);
        T* p = UninitCopyRange(mpBegin, position, pNewData);
        if (p) *p = value;
        T* pNewEnd = UninitCopyRange(position, mpEnd, p + 1);
        DoFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + newSize;
    }
}

template<class T, int A>
T* vec<T,A>::erase(T* first, T* last)
{
    T* newEnd = first;
    for (T* q = last; q != mpEnd; ++q, ++newEnd)
        *newEnd = *q;
    for (T* r = newEnd; r < mpEnd; ++r)
        r->~T();
    mpEnd -= (uint)(last - first);
    return first;
}

// ---- 4-byte refcounted vector erase ----------------------------------------------------
struct RefVec4 {
    AutoRefCount* mpBegin; AutoRefCount* mpEnd; AutoRefCount* mpCapacity; void* mAllocator;
    AutoRefCount* erase(AutoRefCount* first, AutoRefCount* last);
};
// @ 0x00475d00
AutoRefCount* RefVec4::erase(AutoRefCount* first, AutoRefCount* last)
{
    AutoRefCount* newEnd = (AutoRefCount*)MoveRefs(last, mpEnd, first);
    for (AutoRefCount* p = newEnd; p < mpEnd; ++p)
        p->~AutoRefCount();
    mpEnd -= (last - first);
    return first;
}

// ---- 0x29c vector erase ----------------------------------------------------------------
struct Vec29 {
    Elem29c* mpBegin; Elem29c* mpEnd; Elem29c* mpCapacity; void* mAllocator;
    Elem29c* erase(Elem29c* first, Elem29c* last);
};
// @ 0x00475da0
Elem29c* Vec29::erase(Elem29c* first, Elem29c* last)
{
    Elem29c* newEnd = first;
    for (Elem29c* q = last; q != mpEnd; ++q, ++newEnd)
        MoveElem29(newEnd, q);
    for (Elem29c* r = newEnd; r < mpEnd; ++r)
        r->~Elem29c();
    mpEnd -= (last - first);
    return first;
}

// ---- uninitialized_copy helpers --------------------------------------------------------
struct E12 { uint a, b, c; };

// @ 0x00476290
E8* UninitCopy8(E8* first, E8* last, E8* dest)
{
    while (first != last) {
        if (dest) { *dest = *first; }
        ++first;
        ++dest;
    }
    return dest;
}

// @ 0x004763a0
E8* UninitCopy8Destruct(E8* first, E8* last, E8* dest)
{
    E8* result = dest;
    for (E8* p = first; p != last; ++p, ++result) {
        if (result) *result = *p;
    }
    for (E8* q = first; q != last; ++q) {}
    return result;
}

// @ 0x00476950
void* CopyAndDestruct16(void* first, void* last, void* dest)
{
    void* result = dest;
    for (void* p = first; p != last; p = (char*)p + 0x10, result = (char*)result + 0x10) {}
    return result;
}

// @ 0x00475ef0
E12* UninitCopy12(E12* first, E12* last, E12* dest)
{
    E12* result = dest;
    for (E12* p = first; p != last; ++p, ++result) {
        if (result) { *result = *p; }
    }
    return result;
}

// @ 0x004769b0
void* MoveRange4(void* first, void* last, void* dest);      // out of line range move
struct Vec4 {
    uint* mpBegin; uint* mpEnd; uint* mpCapacity; void* mAllocator;
    uint* erase(uint* first, uint* last);
};
uint* Vec4::erase(uint* first, uint* last)
{
    uint* newEnd = (uint*)MoveRange4(last, mpEnd, first);
    for (uint* p = newEnd; p < mpEnd; ++p) {}
    mpEnd -= (last - first);
    return first;
}

// ------------------------------ explicit instantiations ---------------------------------
// @ 0x00476000
template void vec<E8, 4>::DoInsertValue(E8*, const E8&);
// @ 0x00476440
template void vec<E8, 2>::DoInsertValue(E8*, const E8&);
// @ 0x00476680
template void vec<E16, 4>::DoInsertValue(E16*, const E16&);
// @ 0x00476ae0
template void vec<E64, 4>::DoInsertValue(E64*, const E64&);
// @ 0x00476a40
template E64* vec<E64, 4>::erase(E64*, E64*);
