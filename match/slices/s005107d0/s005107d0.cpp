// w1g1 slice s005107d0 -- /Od sort internals (median / partition) and range-insert
// helpers for vector<pair<int,int>> (stride 8) and vector<T24> (stride 0x18), plus
// the T24 copy constructor.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }
void* EASTL_Allocate(void* alloc, unsigned int n, unsigned int align, unsigned int offset);  // 0x0042dee0
void EASTL_allocator_deallocate(void* p);                                                    // 0x00f47380

struct Vector3 { float x, y, z; Vector3() {} Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; } };
struct T24 { Vector3 a, b; T24() {} T24(const T24& o); };

// @ 0x00511140
T24::T24(const T24& o) : a(o.a), b(o.b)
{
}

// ---------------------------------------------------------------------------
// sort records (array elements are pointers to a record with k60/k64)
// ---------------------------------------------------------------------------
struct Keyed { char pad[0x60]; float k60; float k64; };
inline float KeyOf(Keyed* p) { return p->k64 - p->k60; }
inline bool Le(Keyed* a, Keyed* b, uint8_t desc)
{
    const float x = KeyOf(a);
    const float y = KeyOf(b);
    return desc ? (y <= x) : (x <= y);
}

// @ 0x005111b0  median(a, b, c) with the keyed compare
Keyed** MedianCmp(Keyed** a, Keyed** b, Keyed** c, uint8_t desc)
{
    if (Le(*a, *b, desc)) {
        if (Le(*b, *c, desc))
            return b;
        if (Le(*a, *c, desc))
            return c;
        return a;
    }
    if (Le(*a, *c, desc))
        return a;
    if (Le(*b, *c, desc))
        return c;
    return b;
}

// @ 0x005114f0  get_partition
Keyed** GetPartitionCmp(Keyed** first, Keyed** last, Keyed* pivot, uint8_t desc)
{
    for (;;) {
        while (!Le(pivot, *first, desc))
            ++first;
        --last;
        while (!Le(*last, pivot, desc))
            --last;
        if (first >= last)
            return first;
        Keyed* const t = *first;
        *first = *last;
        *last = t;
        ++first;
    }
}

// ---------------------------------------------------------------------------
// vector<pair<int,int>> range insert
// ---------------------------------------------------------------------------
struct P2 { int first; int second; };

void* UninitCopyP2A(void* first, void* last, void* dest);   // 0x0040cce0
void* UninitCopyP2B(void* first, void* last, void* dest);   // 0x00476290
void* UninitCopyP2C(void* first, void* last, void* dest);   // 0x0040cc??

struct Vec8I {
    P2* mpBegin;
    P2* mpEnd;
    P2* mpCapacity;
    uint32_t mAlloc;

    void insert(P2* position, P2* first, P2* last);
};

// @ 0x005107d0
void Vec8I::insert(P2* position, P2* first, P2* last)
{
    if (first != last) {
        const uint32_t n = (uint32_t)(last - first);
        if ((uint32_t)(mpCapacity - mpEnd) < n) {
            const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
            const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
            const uint32_t nNewSize = (nPrevSize + n < nGrowSize) ? nGrowSize : (nPrevSize + n);
            P2* const pNewData = nNewSize ? (P2*)EASTL_Allocate(&mAlloc, nNewSize * sizeof(P2), 4, 0) : 0;
            P2* pNewEnd = (P2*)UninitCopyP2A(mpBegin, position, pNewData);
            pNewEnd = (P2*)UninitCopyP2B(first, last, pNewEnd);
            pNewEnd = (P2*)UninitCopyP2A(position, mpEnd, pNewEnd);
            for (P2* p = position; p != mpEnd; ++p) {}
            if (mpBegin && ((uint32_t*)mpBegin)[-1]) {
                void* q = mpBegin;
                EASTL_allocator_deallocate(q);
            }
            mpBegin = pNewData;
            mpEnd = pNewEnd;
            mpCapacity = pNewData + nNewSize;
        } else {
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            P2* const pOldEnd = mpEnd;
            if (n < nExtra) {
                for (uint32_t i = 0; i < n; ++i)
                    pOldEnd[i] = pOldEnd[i - n];
                for (P2* d = pOldEnd, *s = pOldEnd - n; d != position; ) {
                    --d;
                    --s;
                    *d = *s;
                }
                mpEnd = pOldEnd + n;
                for (uint32_t i = 0; i < n; ++i)
                    position[i] = first[i];
            } else {
                for (uint32_t i = 0; i < n - nExtra; ++i)
                    pOldEnd[i] = first[i];
                mpEnd = pOldEnd + (n - nExtra);
                for (uint32_t i = 0; i < nExtra; ++i)
                    mpEnd[i] = position[i];
                mpEnd += nExtra;
                for (uint32_t i = 0; i < nExtra; ++i)
                    position[i] = first[i + (n - nExtra)];
            }
        }
    }
}

// ---------------------------------------------------------------------------
// vector<T24>::insert(position, first, last)
// ---------------------------------------------------------------------------
void* UninitCopy24A(void* first, void* last, void* dest);   // 0x004b?? (24-byte)
void* UninitCopy24B(void* first, void* last, void* dest);
void* UninitCopy24C(void* first, void* last, void* dest);

struct Vec24I {
    T24* mpBegin;
    T24* mpEnd;
    T24* mpCapacity;
    uint32_t mAlloc;

    void insert(T24* position, T24* first, T24* last);
};

// @ 0x00510bc0
void Vec24I::insert(T24* position, T24* first, T24* last)
{
    if (first != last) {
        const uint32_t n = (uint32_t)(last - first);
        if ((uint32_t)(mpCapacity - mpEnd) < n) {
            const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
            const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
            const uint32_t nNewSize = (nPrevSize + n < nGrowSize) ? nGrowSize : (nPrevSize + n);
            T24* const pNewData = nNewSize ? (T24*)EASTL_Allocate(&mAlloc, nNewSize * sizeof(T24), 4, 0) : 0;
            T24* pNewEnd = (T24*)UninitCopy24A(mpBegin, position, pNewData);
            pNewEnd = (T24*)UninitCopy24B(first, last, pNewEnd);
            pNewEnd = (T24*)UninitCopy24C(position, mpEnd, pNewEnd);
            for (T24* p = position; p != mpEnd; ++p) {}
            if (mpBegin && ((uint32_t*)mpBegin)[-1]) {
                void* q = mpBegin;
                EASTL_allocator_deallocate(q);
            }
            mpBegin = pNewData;
            mpEnd = pNewEnd;
            mpCapacity = pNewData + nNewSize;
        } else {
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            T24* const pOldEnd = mpEnd;
            if (n < nExtra) {
                for (uint32_t i = 0; i < n; ++i)
                    pOldEnd[i] = pOldEnd[i - n];
                for (T24* d = pOldEnd, *s = pOldEnd - n; d != position; ) {
                    --d;
                    --s;
                    *d = *s;
                }
                mpEnd = pOldEnd + n;
                for (uint32_t i = 0; i < n; ++i)
                    position[i] = first[i];
            } else {
                for (uint32_t i = 0; i < n - nExtra; ++i)
                    pOldEnd[i] = first[i];
                mpEnd = pOldEnd + (n - nExtra);
                for (uint32_t i = 0; i < nExtra; ++i)
                    mpEnd[i] = position[i];
                mpEnd += nExtra;
                for (uint32_t i = 0; i < nExtra; ++i)
                    position[i] = first[i + (n - nExtra)];
            }
        }
    }
}
