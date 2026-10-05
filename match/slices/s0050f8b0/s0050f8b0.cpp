// w1g1 slice s0050f8b0 -- /Od sort internals and vector<100>/<0xc> insert helpers
// from the same TU as s0050e850. Elements sorted are pointers to a record whose
// sort key is (f64 - f60).
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

template <int N> inline void ScratchSlots() { unsigned int s[N]; }
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

void* EASTL_Allocate(void* alloc, unsigned int n, unsigned int align, unsigned int offset);  // 0x0042dee0
void EASTL_allocator_deallocate(void* p);                                                    // 0x00f47380

void FixedVec_Destroy();   // 0x004c0b80 (called on an element address)

// ---------------------------------------------------------------------------
// sort record (array elements are pointers to this)
// ---------------------------------------------------------------------------
struct Keyed { char pad[0x60]; float k60; float k64; };

inline float KeyOf(Keyed* p) { return p->k64 - p->k60; }
inline bool StopCmp(Keyed* value, Keyed* cur, uint8_t desc)
{
    const float a = KeyOf(value);
    const float b = KeyOf(cur);
    return desc ? (b <= a) : (a <= b);
}

// ---------------------------------------------------------------------------
// sort helpers over pointer arrays with the Keyed compare
// ---------------------------------------------------------------------------
void QuickSortCmp(Keyed** first, Keyed** last, int n, uint8_t desc);   // 0x0050f950
Keyed** MedianCmp(Keyed** a, Keyed** b, Keyed** c, uint8_t d1, uint8_t d2);  // 0x005111b0
Keyed** GetPartitionCmp(Keyed** first, Keyed** last, Keyed* pivot);     // 0x005114f0
void PartialSortCmp(Keyed** first, Keyed** middle, Keyed** last, uint8_t desc);  // 0x00511670

// @ 0x0050f950
void QuickSortCmp(Keyed** first, Keyed** last, int n, uint8_t desc)
{
    while (((int)(last - first) > 0x1c) && (n > 0)) {
        Keyed** p = MedianCmp(first, first + ((last - first) - ((int)(last - first) >> 31)) / 2, last - 1, desc, desc);
        Keyed** mid = GetPartitionCmp(first, last, *p);
        --n;
        QuickSortCmp(mid, last, n, desc);
        last = mid;
    }
    if (n == 0)
        PartialSortCmp(first, last, last, desc);
}

// @ 0x0050fa10  insertion_sort (bounded)
void InsertionSortCmp(Keyed** first, Keyed** last, uint8_t desc)
{
    if (first != last) {
        Keyed** iCurrent;
        Keyed** iNext;
        Keyed** iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            Keyed* const temp(*iSorted);
            iNext = iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && !StopCmp(temp, *iCurrent, desc); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}

// @ 0x0050fb30  insertion_sort_simple
void InsertionSortSimpleCmp(Keyed** first, Keyed** last, uint8_t desc)
{
    for (Keyed** current = first; current != last; ++current) {
        Keyed** end = current;
        Keyed** prev = current;
        Keyed* value = *current;
        for (--prev; !StopCmp(value, *prev, desc); --end, --prev)
            *end = *prev;
        *end = value;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00510080  relocate-commit wrapper
// ---------------------------------------------------------------------------
void* CopyCommit(Keyed** first, Keyed** last, Keyed** dest);  // 0x00511d50
void UninitRelocateCommit(void* first, void* last, void* dest);           // 0x00511880

void* RelocateCommit(void* first, void* last, void* dest)
{
    uint8_t tag = 0;
    (void)tag;
    ScratchSlots<12>();
    void* p = CopyCommit((Keyed**)first, (Keyed**)last, (Keyed**)dest);
    UninitRelocateCommit(first, last, dest);
    return p;
}

// ---------------------------------------------------------------------------
// default (uint32) compare sort helpers
// ---------------------------------------------------------------------------
void QuickSortU32(uint32_t* first, uint32_t* last, int n);   // 0x005100c0
void PartialSortU32(uint32_t* first, uint32_t* middle, uint32_t* last);  // 0x00511900

// @ 0x005100c0
void QuickSortU32(uint32_t* first, uint32_t* last, int n)
{
    while (((int)(last - first) > 0x1c) && (n > 0)) {
        uint32_t* pEnd = last - 1;
        uint32_t* mid = first + (((int)(last - first)) / 2);
        uint32_t* pivot;
        if (*first < *mid) {
            if (*pEnd <= *mid) {
                pivot = pEnd;
                if (*pEnd <= *first)
                    pivot = first;
            } else {
                pivot = mid;
            }
        } else if (*first < *pEnd) {
            pivot = first;
        } else if (*mid < *pEnd) {
            pivot = pEnd;
        } else {
            pivot = mid;
        }
        const uint32_t value = *pivot;
        uint32_t* p = last;
        uint32_t* q = first;
        for (;;) {
            while (*q < value)
                ++q;
            do {
                --p;
            } while (value < *p);
            if (p <= q)
                break;
            const uint32_t t = *q;
            *q = *p;
            *p = t;
            ++q;
        }
        --n;
        QuickSortU32(q, last, n);
        last = q;
    }
    if (n == 0)
        PartialSortU32(first, last, last);
}

// @ 0x00510240  insertion_sort (default)
void InsertionSortU32(uint32_t* first, uint32_t* last)
{
    if (first != last) {
        uint32_t* iCurrent;
        uint32_t* iNext;
        uint32_t* iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            const uint32_t temp(*iSorted);
            iNext = iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && (temp < *iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}

// @ 0x005102d0  insertion_sort_simple (default)
void InsertionSortSimpleU32(uint32_t* first, uint32_t* last)
{
    for (uint32_t* current = first; current != last; ++current) {
        uint32_t* end(current);
        uint32_t* prev(current);
        const uint32_t value(*current);
        for (--prev; value < *prev; --end, --prev)
            *end = *prev;
        *end = value;
    }
}

// ---------------------------------------------------------------------------
// Elem100 / FixedVec (shared with s0050d750)
// ---------------------------------------------------------------------------
void DwordVector_assign(uint32_t* first, uint32_t* last, uint8_t tag);  // 0x0042c750

struct FixedVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAlloc[3];
    uint32_t mBuf[16];
    void Destroy();
};

struct Base100 {
    FixedVec vec;
    Base100();
    Base100(const Base100&);
};

struct Elem100 : Base100 {
    float f58, f5c, f60;
    Elem100() : f58(0), f5c(0), f60(0) {}
};

struct T12 { uint32_t a, b, c; };

// @ 0x0050f8b0
T12* UninitRelocate12(T12* first, T12* last, T12* dest)
{
    uint8_t tag = 0;
    (void)tag;
    ScratchSlots<6>();
    T12* d = dest;
    for (T12* p = first; p != last; ++p, ++d) {
        if (d) {
            d->a = p->a;
            d->b = p->b;
            d->c = p->c;
        }
    }
    for (T12* q = first; q != last; ++q) {}
    return d;
}

// ---------------------------------------------------------------------------
// @ 0x0050fc30  vector<Elem100>::DoInsertValues
// ---------------------------------------------------------------------------
Elem100* Relocate100(Elem100* first, Elem100* last, Elem100* dest);  // 0x00511d50
void RelocateCommit100(Elem100* first, Elem100* last, Elem100* dest); // 0x00511880
void UninitCopy100(Elem100* first, Elem100* last, Elem100* dest);   // 0x00511be0
Elem100* UninitCopy100b(Elem100* first, Elem100* last, Elem100* dest); // 0x00510080
void CopyBackward100(Elem100* first, Elem100* last, Elem100* resultEnd); // 0x00511d00
void UninitFillN100(Elem100* first, uint32_t n, const Elem100& value);  // 0x00511c80
void Fill100(Elem100* first, Elem100* last, const Elem100& value);      // 0x005117d0
void Copy100(Elem100* first, Elem100* last, Elem100* dest);             // 0x00511790

struct Vec100 {
    Elem100* mpBegin;
    Elem100* mpEnd;
    Elem100* mpCapacity;
    uint32_t mAlloc;
    Elem100* mFixed;

    void DoInsertValues(Elem100* position, uint32_t n, const Elem100& value);
};

// @ 0x0050fc30
void Vec100::DoInsertValues(Elem100* position, uint32_t n, const Elem100& value)
{
    if ((uint32_t)(mpCapacity - mpEnd) < n) {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const uint32_t nNewSize = (nPrevSize + n < nGrowSize) ? nGrowSize : (nPrevSize + n);
        Elem100* const pNewData = nNewSize ? (Elem100*)EASTL_Allocate(&mAlloc, nNewSize * sizeof(Elem100), 4, 0) : 0;
        Elem100* pNewEnd = UninitCopy100b(mpBegin, position, pNewData);
        UninitFillN100(pNewEnd, n, value);
        pNewEnd = Relocate100(position, mpEnd, pNewEnd + n);
        RelocateCommit100(position, mpEnd, pNewEnd);
        if (mpBegin && mpBegin != mFixed) {
            void* q = mpBegin;
            EASTL_allocator_deallocate(q);
        }
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    } else if (n != 0) {
        Elem100 valueSaved(value);
        const uint32_t nExtra = (uint32_t)(mpEnd - position);
        if (n < nExtra) {
            UninitCopy100(mpEnd - n, mpEnd, mpEnd);
            Elem100* const pEnd = mpEnd;
            mpEnd += n;
            CopyBackward100(position, pEnd - n, pEnd);
            Fill100(position, position + n, valueSaved);
        } else {
            UninitFillN100(mpEnd, n - nExtra, valueSaved);
            Elem100* const pEnd = mpEnd;
            mpEnd += n - nExtra;
            Copy100(position, pEnd, mpEnd);
            mpEnd += nExtra;
            Fill100(position, pEnd, valueSaved);
        }
        for (Elem100* p = mpBegin; p < mpEnd; ++p) {}
        FixedVec_Destroy();
    }
}

// ---------------------------------------------------------------------------
// @ 0x00510350  vector<T12>::insert(position, first, last)
// ---------------------------------------------------------------------------
void* UninitCopy12a(void* first, void* last, void* dest);   // 0x004b66b0
void* UninitCopy12b(void* first, void* last, void* dest);   // 0x00475ef0
void* UninitCopy12c(void* first, void* last, void* dest);   // 0x004b6bf0
void Relocate12a(T12* first, T12* last, T12* dest);         // 0x004797a0
void Relocate12b(T12* first, T12* last, T12* dest);         // 0x0042c750-ish
void Copy12(T12* first, T12* last, T12* dest);

struct Vec12I {
    T12* mpBegin;
    T12* mpEnd;
    T12* mpCapacity;
    uint32_t mAlloc;

    void insert(T12* position, T12* first, T12* last);
};

// @ 0x00510350
void Vec12I::insert(T12* position, T12* first, T12* last)
{
    if (first != last) {
        const uint32_t n = (uint32_t)(last - first);
        if ((uint32_t)(mpCapacity - mpEnd) < n) {
            const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
            const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
            const uint32_t nNewSize = (nPrevSize + n < nGrowSize) ? nGrowSize : (nPrevSize + n);
            T12* const pNewData = nNewSize ? (T12*)EASTL_Allocate(&mAlloc, nNewSize * sizeof(T12), 4, 0) : 0;
            T12* pNewEnd = (T12*)UninitCopy12a(mpBegin, position, pNewData);
            pNewEnd = (T12*)UninitCopy12b(first, last, pNewEnd);
            pNewEnd = (T12*)UninitCopy12c(position, mpEnd, pNewEnd);
            for (T12* p = position; p != mpEnd; ++p) {}
            if (mpBegin && ((uint32_t*)mpBegin)[-1]) {
                void* q = mpBegin;
                EASTL_allocator_deallocate(q);
            }
            mpBegin = pNewData;
            mpEnd = pNewEnd;
            mpCapacity = pNewData + nNewSize;
        } else {
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            T12* const pOldEnd = mpEnd;
            if (n < nExtra) {
                for (uint32_t i = 0; i < n; ++i)
                    pOldEnd[i] = pOldEnd[i - n];
                for (T12* d = pOldEnd, *s = pOldEnd - n; d != position; ) {
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
