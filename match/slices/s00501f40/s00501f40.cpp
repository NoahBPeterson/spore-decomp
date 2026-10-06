// Slice s00501f40: eastl::vector<T>::DoInsertValues(position, n, value) for three element types,
// plus a deque push_back slow path and two small helpers.  /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

inline void* operator new(size_t, void* p) { return p; }
void EASTL_allocator_deallocate(void* p);   // 0x00f47380 (operator delete[])
void* EASTL_Allocate(void* alloc, unsigned size, int align, int flags);   // 0x0042dee0 (cdecl)
struct Tag {};

struct DequeBase2 { void Deallocate(void* p); };   // 0x00569260
struct DequeIter  { void SetSubarray(int p); };    // 0x00569340

struct Alloc2 {
    void deallocate(void* p, int n);        // 0x00502eb0
};

// ---------------------------------------------------------------------------
// Deque (4-byte element): 0x00502dd0 push_back slow path, 0x00502e70 helper
// ---------------------------------------------------------------------------
struct DequeIt4 {
    unsigned* mpCurrent; unsigned* mpBegin; unsigned* mpEnd; unsigned** mpCurrentArrayPtr;
    void SetSubarray(unsigned** p);         // 0x00569340
};
struct Deque {
    unsigned** mpPtrArray;                  // +0x00
    int mnPtrArraySize;                     // +0x04
    DequeIt4 mItBegin;                      // +0x08
    DequeIt4 mItEnd;                        // +0x18
    void F();                               // 0x00502e70
    void DoReallocPtrArray(int a, int b);   // 0x00503470
    unsigned* DoAllocateSubarray();         // 0x004ab320
    void DoPushBackSlow(const unsigned& value);   // 0x00502dd0
};

// @ 0x00502dd0
void Deque::DoPushBackSlow(const unsigned& value)
{
    unsigned valueSaved = value;
    if ((mItEnd.mpCurrentArrayPtr - mpPtrArray) + 1 >= mnPtrArraySize)
        DoReallocPtrArray(1, 1);
    mItEnd.mpCurrentArrayPtr[1] = DoAllocateSubarray();
    ::new (mItEnd.mpCurrent) unsigned(valueSaved);
    mItEnd.SetSubarray(mItEnd.mpCurrentArrayPtr + 1);
    mItEnd.mpCurrent = mItEnd.mpBegin;
}

// @ 0x00502e70
void Deque::F()
{
    ((DequeBase2*)this)->Deallocate(*(void**)((char*)this + 0xc));
    ((DequeIter*)((char*)this + 8))->SetSubarray(*(int*)((char*)this + 0x14) + 4);
    *(void**)((char*)this + 8) = *(void**)((char*)this + 0xc);
}

// @ 0x00502eb0
void Alloc2::deallocate(void* p, int n)
{
    if (p) {
        void* q = p;
        EASTL_allocator_deallocate(q);
    }
}

// ---------------------------------------------------------------------------
// element type E48 (0x48 bytes): Vector3 + small vector + int
// ---------------------------------------------------------------------------
struct V3 { float x, y, z; V3(const V3& o); };            // copy ctor 0x004098a0
struct FV {                                               // 0x38-byte small vector
    unsigned* mpBegin; unsigned* mpEnd; unsigned p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13;
    FV(const FV& o);                                      // 0x005030e0
    FV& operator=(const FV& o);                           // 0x0041d140
    void FreeStorage();                                   // 0x004c0b80
    ~FV() { for (unsigned* p = mpBegin; p < mpEnd; ++p) {} FreeStorage(); }
};
struct E48 {
    V3 v; FV w; int x;
    E48(const E48& o) : v(o.v), w(o.w), x(o.x) {}
    E48& operator=(const E48& o) { v = o.v; w = o.w; x = o.x; return *this; }
};
E48* __cdecl E48_uninit_copy_a(Tag* t, E48* a, E48* b, E48* c, Tag flag);   // 0x00503670
E48* __cdecl E48_copy_backward(E48* first, E48* last, E48* result);        // 0x00503180
E48* __cdecl E48_fill_n(E48* dst, unsigned n, const E48* value, Tag flag);  // 0x005036f0
E48* __cdecl E48_uninit_move(E48* first, E48* last, E48* dest);            // 0x005031d0
E48* __cdecl E48_move_b(E48* first, E48* last, E48* dest);                 // 0x00503b90
void __cdecl E48_destroy(E48* first, E48* last, E48* dest);                // 0x00503be0

inline E48* L2_move(E48* first, E48* last, E48* dest)
{
    Tag t; Tag f;
    return E48_uninit_copy_a(&t, first, last, dest, f);
}
inline E48* L1_move(E48* first, E48* last, E48* dest) { return L2_move(first, last, dest); }
inline E48* L1_fill(E48* first, unsigned n, const E48* v) { Tag f; return E48_fill_n(first, n, v, f); }

struct VecE48 {
    E48* mpBegin; E48* mpEnd; E48* mpCapacity; int alloc;
    void DoInsertValues(E48* position, unsigned n, const E48& value);   // 0x00501f40
};

// @ 0x00501f40
void VecE48::DoInsertValues(E48* position, unsigned n, const E48& value)
{
    if (!(n > (unsigned)(mpCapacity - mpEnd))) {
        if (n > 0) {
            E48 temp(value);
            unsigned nExtra = mpEnd - position;
            E48* pOldEnd = mpEnd;
            if (n < nExtra) {
                L1_move(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                E48_copy_backward(position, pOldEnd - n, pOldEnd);
                for (E48* p = position; p != position + n; ++p)
                    *p = temp;
            } else {
                Tag flag;
                E48_fill_n(mpEnd, n - nExtra, &temp, flag);
                mpEnd += n - nExtra;
                L1_move(position, pOldEnd, mpEnd);
                mpEnd += nExtra;
                for (E48* p = position; p != pOldEnd; ++p)
                    *p = temp;
            }
        }
    } else {
        unsigned nPrevSize = mpEnd - mpBegin;
        unsigned nGrowSize = nPrevSize ? nPrevSize * 2 : 1;
        unsigned nNewSize = nGrowSize > nPrevSize + n ? nGrowSize : nPrevSize + n;
        E48* pNewData = nNewSize ? (E48*)EASTL_Allocate(&alloc, nNewSize * 0x48, 4, 0) : 0;
        E48* pNewEnd = E48_uninit_move(mpBegin, position, pNewData);
        L1_fill(pNewEnd, n, &value);
        E48* dest = pNewEnd + n;
        pNewEnd = E48_move_b(position, mpEnd, dest);
        E48_destroy(position, mpEnd, dest);
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------
// element type A (0x54 bytes) with out-of-line copy ctor / operator=
// ---------------------------------------------------------------------------
struct B16 { unsigned a, b, c, d; };
struct EA54 {
    B16 p0, p1, p2, p3; unsigned p4;
    EA54(const EA54& o);                   // 0x00502ee0
    EA54& operator=(const EA54& o);        // 0x005039c0
};
EA54* __cdecl EA54_uninit_a(Tag* t, EA54* a, EA54* b, EA54* c, Tag flag);   // 0x00503750
EA54* __cdecl EA54_fill_n(EA54* dst, unsigned n, const EA54* value, Tag flag);   // 0x005037d0
EA54* __cdecl EA54_uninit_move(EA54* first, EA54* last, EA54* dest);        // 0x005032b0 / 0x00503350
EA54* __cdecl EA54_uninit_move2(EA54* first, EA54* last, EA54* dest);       // 0x00503350

struct VecEA54 {
    EA54* mpBegin; EA54* mpEnd; EA54* mpCapacity; int alloc;
    void DoInsertValues(EA54* position, unsigned n, const EA54& value);   // 0x00502450
};

// @ 0x00502450
void VecEA54::DoInsertValues(EA54* position, unsigned n, const EA54& value)
{
    if (!(n > (unsigned)(mpCapacity - mpEnd))) {
        if (n != 0) {
            EA54 temp(value);
            unsigned nExtra = mpEnd - position;
            EA54* pOldEnd = mpEnd;
            if (n < nExtra) {
                Tag t; Tag f;
                EA54_uninit_a(&t, mpEnd - n, mpEnd, mpEnd, f);
                mpEnd += n;
                EA54* last = pOldEnd - n;
                EA54* result = pOldEnd;
                while (last != position) {
                    --last; --result;
                    *result = *last;
                }
                for (EA54* p = position; p != position + n; ++p)
                    *p = temp;
            } else {
                Tag f;
                EA54_fill_n(mpEnd, n - nExtra, &temp, f);
                mpEnd += n - nExtra;
                EA54_uninit_move(position, pOldEnd, mpEnd);
                mpEnd += nExtra;
                for (EA54* p = position; p != pOldEnd; ++p)
                    *p = temp;
            }
        }
    } else {
        unsigned nPrevSize = mpEnd - mpBegin;
        unsigned nGrowSize = nPrevSize ? nPrevSize * 2 : 1;
        unsigned nNewSize = nGrowSize > nPrevSize + n ? nGrowSize : nPrevSize + n;
        EA54* pNewData = nNewSize ? (EA54*)EASTL_Allocate(&alloc, nNewSize * 0x54, 4, 0) : 0;
        EA54* pNewEnd = EA54_uninit_move2(mpBegin, position, pNewData);
        Tag f;
        EA54_fill_n(pNewEnd, n, &value, f);
        pNewEnd = EA54_uninit_move2(position, mpEnd, pNewEnd + n);
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------
// element type Ed8 (0xd8 bytes), temp copy owns a small vector at +0x14
// ---------------------------------------------------------------------------
struct EdVec {                              // vector<unsigned> header (begin, end, cap, alloc)
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCap; unsigned alloc;
    void FreeStorage();                     // 0x004c0b80
    ~EdVec() { for (unsigned* p = mpBegin; p < mpEnd; ++p) {} FreeStorage(); }
};
struct Ed216 {
    B16 p0; unsigned q0; EdVec vec;         // vec at +0x14
    B16 p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11; unsigned r0, r1, r2;
    Ed216(const Ed216& o);                  // 0x00502f60
    Ed216& operator=(const Ed216& o);       // 0x00503a50
};
Ed216* __cdecl Ed216_uninit_a(Tag* t, Ed216* a, Ed216* b, Ed216* c, Tag flag);   // 0x00503830
Ed216* __cdecl Ed216_fill_n(Ed216* dst, unsigned n, const Ed216* value, Tag flag);   // 0x005038c0
Ed216* __cdecl Ed216_move(Ed216* first, Ed216* last, Ed216* dest);          // 0x00501a10

struct VecEd216 {
    Ed216* mpBegin; Ed216* mpEnd; Ed216* mpCapacity; int alloc;
    void DoInsertValues(Ed216* position, unsigned n, const Ed216& value);   // 0x00502880
};

// @ 0x00502880
void VecEd216::DoInsertValues(Ed216* position, unsigned n, const Ed216& value)
{
    if (!(n > (unsigned)(mpCapacity - mpEnd))) {
        if (n != 0) {
            Ed216 temp(value);
            unsigned nExtra = mpEnd - position;
            Ed216* pOldEnd = mpEnd;
            if (n < nExtra) {
                Tag t; Tag f;
                Ed216_uninit_a(&t, mpEnd - n, mpEnd, mpEnd, f);
                mpEnd += n;
                Ed216* last = pOldEnd - n;
                Ed216* result = pOldEnd;
                while (last != position) {
                    --last; --result;
                    *result = *last;
                }
                for (Ed216* p = position; p != position + n; ++p)
                    *p = temp;
            } else {
                Tag t; Tag f;
                Ed216_fill_n(mpEnd, n - nExtra, &temp, f);
                mpEnd += n - nExtra;
                Ed216_uninit_a(&t, position, pOldEnd, mpEnd, f);
                mpEnd += nExtra;
                for (Ed216* p = position; p != pOldEnd; ++p)
                    *p = temp;
            }
        }
    } else {
        unsigned nPrevSize = mpEnd - mpBegin;
        unsigned nGrowSize = nPrevSize ? nPrevSize * 2 : 1;
        unsigned nNewSize = nGrowSize > nPrevSize + n ? nGrowSize : nPrevSize + n;
        Ed216* pNewData = nNewSize ? (Ed216*)EASTL_Allocate(&alloc, nNewSize * 0xd8, 4, 0) : 0;
        Ed216* pNewEnd = Ed216_move(mpBegin, position, pNewData);
        Tag f;
        Ed216_fill_n(pNewEnd, n, &value, f);
        pNewEnd = Ed216_move(position, mpEnd, pNewEnd + n);
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
