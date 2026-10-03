// Slice s00424010: EASTL-style vector internals instantiated for several element types
// (unoptimized module: /Od /Ob1 /MD /Gy /EHsc /TP /arch:SSE).
//   0x00424010  Vec24::DoInsertValue       (vector of 24-byte records = two Vector3, realloc-insert)
//   0x00424340  UninitCopy24               (uninitialized_copy of those records)
//   0x004243e0  RefVec::DestroyRange       (release a range of intrusive refs)
//   0x00424430  RefVec::DoInsertValue      (vector of intrusive refs to ThreadedObject)
//   0x004246e0  Vec4Vec::DoAllocateAndCopy (vector of 16-byte records)
//   0x00424770  CopyVec4                   (copy a range of 16-byte records)
//   0x004247f0  RcVec::erase               (vector of DefaultRefCounted pointers)
//
// Local variable *names* in this file are not meaningful. At /Od the stack-slot order of locals
// (and of inlined-helper locals) depends on the identifiers, so the names were chosen by search
// to reproduce the original frame layouts; unused locals reproduce dead slots of inlined helpers.
#include "types.h"

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);

void __cdecl EASTL_allocator_deallocate(void* p);                                  // 0x00f47380
inline void* operator new(unsigned int, void* p) { return p; }

struct Alloc { int unused; };
void* __cdecl AllocatorAllocate(Alloc* a, unsigned size, unsigned align, unsigned off);   // 0x0042dee0

// ============================================================================= 24-byte records
struct Vector3 { float x, y, z; Vector3(const Vector3& o); };                     // 0x004098a0
struct Elem24 {
    Vector3 a, b;
    Elem24(const Elem24& o);                                                       // 0x00511140
};
// View of the same record whose copy is done member by member (assignment copies b, then a).
struct Elem24Inl {
    Vector3 a, b;
    Elem24Inl& operator=(const Elem24Inl& o) { b = o.b; a = o.a; return *this; }
};
Elem24* __cdecl UninitCopy24(Elem24* first, Elem24* last, Elem24* dest);          // 0x00424340
Elem24* __cdecl UninitMove24(Elem24* first, Elem24* last, Elem24* dest);          // 0x00512000

struct Vec24 {
    Elem24* mpBegin; Elem24* mpEnd; Elem24* mpCap; Alloc alloc;
    void DoInsertValue(Elem24* pos, const Elem24& v);
};
inline void dealloc24(Elem24* p, unsigned n) { if (((int*)p)[-1]) { void* q = p; EASTL_allocator_deallocate(q); } }
inline void free24(Elem24* p, unsigned n) { if (p) dealloc24(p, n); }

inline Elem24* Vec24_CopyBack(Elem24* first, Elem24* last, Elem24* dest)
{
    bool h = false; bool m3 = false; bool it = false;
    Elem24* z1 = dest; Elem24* l = last;
    while (l != first) { --l; --z1; *(Elem24Inl*)z1 = *(Elem24Inl*)l; }
    return z1;
}
inline void Vec24_DestroyTail(Elem24* first, Elem24* last, Elem24* dest)
{
    bool res = false; int inIt, dd, d2; Elem24* t1 = dest; Elem24* o = first;
    for (; o != last; ++o, ++t1) { }
}
inline Elem24* Vec24_Move(Elem24* first, Elem24* last, Elem24* dest)
{
    bool w = false;
    Elem24* e = UninitMove24(first, last, dest);
    Vec24_DestroyTail(first, last, dest);
    return e;
}

// @ 0x00424010  (not byte-exact: the inline copy of the two Vector3 members at the end of the
//               vector stores the sub-object address in a temp in the original)
void Vec24::DoInsertValue(Elem24* pos, const Elem24& v)
{
    if (mpEnd != mpCap) {
        const Elem24* iter = &v;
        if (iter >= pos && iter < mpEnd) ++iter;
        ::new((void*)mpEnd) Elem24Inl(*(Elem24Inl*)(mpEnd - 1));
        Vec24_CopyBack(pos, mpEnd - 1, mpEnd);
        *(Elem24Inl*)pos = *(const Elem24Inl*)iter;
        ++mpEnd;
    } else {
        unsigned tag1 = (unsigned)(mpEnd - mpBegin);
        unsigned ret = (tag1 > 0) ? tag1 * 2 : 1;
        Elem24* pD = ret ? (Elem24*)AllocatorAllocate(&alloc, ret * 0x18, 4, 0) : 0;
        Elem24* pv = UninitCopy24(mpBegin, pos, pD);
        ::new((void*)pv) Elem24(v);
        ++pv;
        pv = Vec24_Move(pos, mpEnd, pv);
        free24(mpBegin, mpCap - mpBegin);
        mpBegin = pD; mpEnd = pv; mpCap = pD + ret;
    }
}

// ---- uninitialized_copy of 24-byte records ---------------------------------------------------
inline Elem24* UninitCopy24_Impl(Elem24* first, Elem24* last, Elem24* dest)
{
    bool pBegin = false; int m1, pC; Elem24* r = dest; Elem24* u1 = first;
    for (; u1 != last; ++u1, ++r) { ::new((void*)r) Elem24(*u1); }
    return r;
}
inline void UninitCopy24_Tail(Elem24* first, Elem24* last, Elem24* dest)
{
    bool l3 = false; Elem24* n2 = dest; Elem24* z = first;
    for (; z != last; ++z, ++n2) { }
}

// @ 0x00424340  (not byte-exact: the placement-new null-check temp sits below the loop locals)
Elem24* __cdecl UninitCopy24(Elem24* first, Elem24* last, Elem24* dest)
{
    Elem24* s1 = UninitCopy24_Impl(first, last, dest);
    UninitCopy24_Tail(first, last, dest);
    return s1;
}

// ============================================================================= intrusive refs
struct ThreadedObject {
    void* vtable; volatile long mnRefCount;
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();                                                                // 0x00404f90
};
struct Ref {
    ThreadedObject* p;
    Ref(const Ref& o) : p(o.p) { if (p) p->AddRef(); }
    Ref& operator=(const Ref& o)
    {
        ThreadedObject* old; ThreadedObject* n = o.p;
        if (n != p) { old = p; if (n) n->AddRef(); p = n; if (old) old->Release(); }
        return *this;
    }
    ~Ref() { if (p) p->Release(); }
};
Ref* __cdecl CopyBackRefs(Ref* first, Ref* last, Ref* dest);                       // 0x0042e760

struct RefVec {
    Ref* mpBegin; Ref* mpEnd; Ref* mpCap; Alloc alloc;
    void DestroyRange(Ref* first, Ref* last);
    void DoInsertValue(Ref* pos, const Ref& v);
};
inline void DestroyRef(Ref* r, int flags) { if (r->p) r->p->Release(); if (flags & 1) EASTL_allocator_deallocate(r); }

// @ 0x004243e0
void RefVec::DestroyRange(Ref* first, Ref* last)
{
    int u0, u1, u2;
    for (; first < last; ++first) DestroyRef(first, 0);
}

inline void dealloc(Ref* p, unsigned n) { if (((int*)p)[-1]) { void* q = p; EASTL_allocator_deallocate(q); } }
inline void freeRefs(Ref* p, unsigned n) { if (p) dealloc(p, n); }

inline Ref* RefVec_CopyBack(Ref* first, Ref* last, Ref* dest)
{
    bool d3 = false; bool aa = false; int z1, x1, b3, r;
    return CopyBackRefs(first, last, dest);
}
inline Ref* RefVec_MoveRaw(Ref* first, Ref* last, Ref* dest)
{
    return (Ref*)memcpy(dest, first, (char*)last - (char*)first) + (last - first);
}
inline Ref* RefVec_Move(Ref* first, Ref* last, Ref* dest)
{
    bool t1 = true; Ref* r0 = RefVec_MoveRaw(first, last, dest);
    bool j = true;
    return r0;
}

// @ 0x00424430
void RefVec::DoInsertValue(Ref* pos, const Ref& v)
{
    if (mpEnd != mpCap) {
        const Ref* j = &v;
        if (j >= pos && j < mpEnd) ++j;
        ::new((void*)mpEnd) Ref(*(mpEnd - 1));
        RefVec_CopyBack(pos, mpEnd - 1, mpEnd);
        *pos = *j;
        ++mpEnd;
    } else {
        unsigned w0 = (unsigned)(mpEnd - mpBegin);
        unsigned e2 = (w0 > 0) ? w0 * 2 : 1;
        Ref* out = e2 ? (Ref*)AllocatorAllocate(&alloc, e2 * 4, 4, 0) : 0;
        Ref* g1 = RefVec_Move(mpBegin, pos, out);
        ::new((void*)g1) Ref(v);
        ++g1;
        g1 = RefVec_Move(pos, mpEnd, g1);
        freeRefs(mpBegin, mpCap - mpBegin);
        mpBegin = out; mpEnd = g1; mpCap = out + e2;
    }
}

// ============================================================================= 16-byte records
struct Vec4 { float x, y, z, w; };
struct PtrBox { Vec4* p; };
PtrBox* __cdecl UninitCopyV4(PtrBox* out, Vec4* first, Vec4* last, Vec4* dest, bool tag);   // 0x0047a500

struct Vec4Vec {
    Vec4* mpBegin; Vec4* mpEnd; Vec4* mpCap; Alloc alloc;
    Vec4* DoAllocateAndCopy(unsigned n, Vec4* first, Vec4* last);
};
inline Vec4* Vec4Vec_Copy3(Vec4* e3, Vec4* z2, Vec4* m1)
{
    PtrBox a; bool dst; bool y;
    UninitCopyV4(&a, e3, z2, m1, dst);
    return a.p;
}
inline Vec4* Vec4Vec_Copy2(Vec4*& first, Vec4*& last, Vec4*& dest)
{
    int idx, tag2, j2, p1;
    return Vec4Vec_Copy3(first, last, dest);
}
inline Vec4* Vec4Vec_Copy1(Vec4* f1, Vec4* flag, Vec4* r0)
{
    return Vec4Vec_Copy2(f1, flag, r0);
}

// @ 0x004246e0  (not byte-exact: frame slot layout of the nested inline wrappers)
Vec4* Vec4Vec::DoAllocateAndCopy(unsigned n, Vec4* first, Vec4* last)
{
    Vec4* sz = n ? (Vec4*)AllocatorAllocate(&alloc, n << 4, 4, 0) : 0;
    Vec4Vec_Copy1(first, last, sz);
    return sz;
}

// @ 0x00424770
Vec4* __cdecl CopyVec4(Vec4* first, Vec4* last, Vec4* dest)
{
    bool b2 = false; bool tag = false; bool tag1 = false; Vec4* src = dest; Vec4* c = first;
    for (; c != last; ++src, ++c) { src->x = c->x; src->y = c->y; src->z = c->z; src->w = c->w; }
    return src;
}

// ============================================================================= ref-counted pointers
struct DefaultRefCounted { void Release(); };                                      // 0x00453540
struct RcPtr {
    DefaultRefCounted* p;
    RcPtr& operator=(const RcPtr& o);                                              // 0x004e4350
};
struct RcVec {
    RcPtr* mpBegin; RcPtr* mpEnd; RcPtr* mpCap;
    RcPtr* erase(RcPtr* first, RcPtr* last);
};
inline RcPtr* RcVec_MoveDown(RcPtr* first, RcPtr* last, RcPtr* dest)
{
    bool y = false; bool a = false; bool u6 = false; int b3, b, j1, val, m1;
    RcPtr* done = dest; RcPtr* pE = first;
    for (; pE != last; ++done, ++pE) { *done = *pE; }
    return done;
}
inline void RcVec_DestroyOne(RcPtr* p, int fl) { if (p->p) p->p->Release(); if (fl & 1) EASTL_allocator_deallocate(p); }
inline void RcVec_DestroyRange(RcPtr* first, RcPtr* last)
{
    int val, idx, first2; RcPtr* i2 = first;
    for (; i2 < last; ++i2) { RcVec_DestroyOne(i2, 0); }
}

// @ 0x004247f0
RcPtr* RcVec::erase(RcPtr* first, RcPtr* last)
{
    RcPtr* last2 = RcVec_MoveDown(last, mpEnd, first);
    RcVec_DestroyRange(last2, mpEnd);
    mpEnd -= (last - first);
    return first;
}
