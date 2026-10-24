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
struct E64 {                                      // 64-byte element with an out-of-line initialiser
    uint q[16];
    void Ctor(const void* src);                   // 0x0045dca0: copies 64 bytes from src
};

// range helpers (out of line, relocations masked)
void* MoveRefs(void* first, void* last, void* dest);         // @ 0x0047c780
void  MoveElem29(Elem29c* dst, Elem29c* src);                // @ 0x0047cf00

// Out-of-line range copies, one address per instantiation.  Hex names keep the relocation exact:
// the four Copy specialisations shared a name and the two E8 instantiations shared a parameter
// list, which left the annotation resolver with two candidates (and the E8,4 link unresolved).
E8*  FUN_004763a0(E8*, E8*, E8*);        // 0x4763a0, same code as UninitCopy8Destruct below
E8*  FUN_004554f0(E8*, E8*, E8*);        // 0x4554f0
E16* FUN_00476950(E16*, E16*, E16*);     // 0x476950, same VA as CopyAndDestruct16 below
E16* FUN_0047c1c0(E16*, E16*, E16*);     // 0x47c1c0, the second-range copy for E16
E64* FUN_0047a9a0(E64*, E64*, E64*);     // 0x47a9a0

// "construct an element from a source element": a plain copy for the trivial types, the element's
// own initialiser for E64 (whose original calls 0x45dca0 here).
#define VEC_COPY_ELEM(d, s) (*(d) = *(s))
#define VEC_CTOR_ELEM(d, s) ((d)->Ctor(s))

// The eastl::vector instantiations are told apart by name (the checker's symbol lookup ignores
// template arguments), so the template is stamped out once per instantiated element/alignment.
#define DEFINE_VEC(NAME, COPY_FIRST, COPY_SECOND, CONSTRUCT) \
template<class T, int A> \
struct NAME { \
    T* mpBegin; T* mpEnd; T* mpCapacity; void* mAllocator; \
    T* DoAllocate(uint n) { return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), A, 0) : 0; } \
    void DoFree(T* p) { if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p); } \
    void DoInsertValue(T* position, const T& value); \
    T* erase(T* first, T* last); \
}; \
 \
template<class T, int A> \
void NAME<T,A>::DoInsertValue(T* position, const T& value) \
{ \
    if (mpEnd != mpCapacity) { \
        const T* pv = &value; \
        if (pv >= position && pv < mpEnd) ++pv; \
        const T& v = *pv; \
        T* pEnd = mpEnd; \
        if (pEnd) CONSTRUCT(pEnd, pEnd - 1); \
        T* p = pEnd; \
        T* q = pEnd - 1; \
        while (q != position) { p[-1] = q[-1]; --p; --q; } \
        *position = v; \
        ++mpEnd; \
    } else { \
        const uint oldSize = (uint)(mpEnd - mpBegin); \
        uint newSize = oldSize ? oldSize * 2 : 1; \
        T* pNewData = DoAllocate(newSize); \
        T* p = COPY_FIRST(mpBegin, position, pNewData); \
        if (p) CONSTRUCT(p, &value); \
        T* pNewEnd = COPY_SECOND(position, mpEnd, p + 1); \
        DoFree(mpBegin); \
        mpBegin = pNewData; \
        mpEnd = pNewEnd; \
        mpCapacity = pNewData + newSize; \
    } \
} \
 \
template<class T, int A> \
T* NAME<T,A>::erase(T* first, T* last) \
{ \
    T* newEnd = first; \
    for (T* q = last; q != mpEnd; ++q, ++newEnd) \
        *newEnd = *q; \
    for (T* r = newEnd; r < mpEnd; ++r) \
        r->~T(); \
    mpEnd -= (uint)(last - first); \
    return first; \
}

DEFINE_VEC(vec, FUN_0047a9a0, FUN_0047a9a0, VEC_CTOR_ELEM)          // E64,4
DEFINE_VEC(vecE8a4, FUN_004763a0, FUN_004763a0, VEC_COPY_ELEM)      // E8,4
DEFINE_VEC(vecE8a2, FUN_004554f0, FUN_004554f0, VEC_COPY_ELEM)      // E8,2
DEFINE_VEC(vecE16, FUN_00476950, FUN_0047c1c0, VEC_COPY_ELEM)       // E16,4

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
    // the copy half of the original (its relocation-masked call to 0x47c1c0); the second half is a
    // destructor pass over [first,last) that writes nothing observable.
    void* result = FUN_0047c1c0((E16*)first, (E16*)last, (E16*)dest);
    E16* q = (E16*)first;
    while (q != (E16*)last) ++q;
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
template void vecE8a4<E8, 4>::DoInsertValue(E8*, const E8&);
// @ 0x00476440
template void vecE8a2<E8, 2>::DoInsertValue(E8*, const E8&);
// @ 0x00476680
template void vecE16<E16, 4>::DoInsertValue(E16*, const E16&);
// @ 0x00476ae0
template void vec<E64, 4>::DoInsertValue(E64*, const E64&);
// @ 0x00476a40
template E64* vec<E64, 4>::erase(E64*, E64*);
