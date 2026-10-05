// Slice s004c10e0: EASTL sort/heap/vector instantiations used by the creature-editor
// skin subsystem, plus a fixed_string<wchar_t,256> append helper.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

#pragma pack(push, 4)

// ===========================================================================
// 0x18-byte value type used by the sort/heap helpers.
// ===========================================================================
struct Elem18 {
    uint32_t v[6];
    bool operator<(const Elem18& x) const { return v[0] < x.v[0]; }
};

namespace eastl {

struct Compare18 {
    bool operator()(const Elem18& a, const Elem18& b) const { return a.v[0] < b.v[0]; }
};

// Out-of-line heap primitives (0x004c2460 / 0x004c2520).
void make_heap(Elem18* first, Elem18* middle, Compare18 compare);
void adjust_heap(Elem18* first, int topIndex, int size, int valueIndex, Elem18 value, Compare18 compare);
void partial_sort(Elem18* first, Elem18* middle, Elem18* last, Compare18 compare);

// ---------------------------------------------------------------------------
// @ 0x004c1920  eastl::Internal::quick_sort_impl<It,Size,Compare>
// ---------------------------------------------------------------------------
inline const Elem18& median(const Elem18& a, const Elem18& b, const Elem18& c, Compare18 compare)
{
    if (compare(a, b)) {
        if (compare(b, c))
            return b;
        else if (compare(a, c))
            return c;
        else
            return a;
    } else if (compare(a, c))
        return a;
    else if (compare(b, c))
        return c;
    return b;
}

inline void iter_swap(Elem18* a, Elem18* b) { Elem18 tmp(*a); *a = *b; *b = tmp; }

inline Elem18* get_partition(Elem18* first, Elem18* last, const Elem18& pivotValue, Compare18 compare)
{
    const Elem18 pivotCopy(pivotValue);
    for (;; ++first) {
        while (compare(*first, pivotCopy))
            ++first;
        --last;
        while (compare(pivotCopy, *last))
            --last;
        if (first >= last)
            return first;
        eastl::iter_swap(first, last);
    }
}

void quick_sort_impl(Elem18* first, Elem18* last, int kRecursionCount, Compare18 compare)
{
    while (((last - first) > 28) && (kRecursionCount > 0)) {
        Elem18* const position = eastl::get_partition(first, last,
            eastl::median(*first, *(first + (last - first) / 2), *(last - 1), compare), compare);
        eastl::quick_sort_impl(position, last, --kRecursionCount, compare);
        last = position;
    }
    if (kRecursionCount == 0)
        eastl::partial_sort(first, last, last, compare);
}

// ---------------------------------------------------------------------------
// @ 0x004c1e20  eastl::partial_sort<It,Compare>
// ---------------------------------------------------------------------------
inline void sort_heap(Elem18* first, Elem18* last, Compare18 compare)
{
    for (; (last - first) > 1; --last) {
        const Elem18 temp(*(last - 1));
        *(last - 1) = *first;
        eastl::adjust_heap(first, 0, (int)(last - first) - 1, 0, temp, compare);
    }
}

void partial_sort(Elem18* first, Elem18* middle, Elem18* last, Compare18 compare)
{
    eastl::make_heap(first, middle, compare);
    for (Elem18* i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            const Elem18 temp(*i);
            *i = *first;
            eastl::adjust_heap(first, 0, (int)(middle - first), 0, temp, compare);
        }
    }
    eastl::sort_heap(first, middle, compare);
}

// ---------------------------------------------------------------------------
// @ 0x004c1b80  eastl::insertion_sort<Elem18*>
// ---------------------------------------------------------------------------
template <class It> void insertion_sort(It first, It last);

template <> void insertion_sort<Elem18*>(Elem18* first, Elem18* last)
{
    if (first != last) {
        Elem18* iCurrent;
        Elem18* iNext;
        Elem18* iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            const Elem18 temp(*iSorted);
            iNext = iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && (temp < *iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}

} // namespace eastl

// ===========================================================================
// eastl::vector<T, sp_vector_allocator> insert helper.
// ===========================================================================
namespace eastl {

struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
};

void* eastl_alloc(void* allocator, uint32_t size, uint32_t align, uint32_t offset);
void eastl_free(void* p);

template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    uint32_t GetNewCapacity(uint32_t nPrevSize) const { return nPrevSize ? nPrevSize * 2 : 1; }
    void DoInsertValues(T* position, uint32_t n, const T& value);
    T* DoAllocate(uint32_t n);
    void DoFree(T* p, uint32_t n);
};

// 0x38-byte non-trivial element (has an out-of-line copy ctor at 0x0047bb70).
struct Rec38 {
    uint32_t v[14];
    Rec38() {}
    Rec38(const Rec38&);
};

Rec38* uninitialized_copy_ptr(Rec38* first, Rec38* last, Rec38* result);
void uninitialized_fill_n_ptr(Rec38* first, uint32_t n, const Rec38& value);
Rec38* copy_backward(Rec38* first, Rec38* last, Rec38* result);
void fill(Rec38* first, Rec38* last, const Rec38& value);
void destruct(Rec38* first, Rec38* last);

template <> Rec38* vector<Rec38>::DoAllocate(uint32_t n)
{
    return n ? (Rec38*)eastl_alloc(&mAllocator, n * 0x38, 4, 0) : 0;
}

template <> void vector<Rec38>::DoFree(Rec38* p, uint32_t)
{
    if (p)
        eastl_free(p);
}

// @ 0x004c1520  eastl::vector<Rec38,sp_vector_allocator>::DoInsertValues
template <> void vector<Rec38>::DoInsertValues(Rec38* position, uint32_t n, const Rec38& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const Rec38 temp = value;
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            if (n < nExtra) {
                eastl::uninitialized_copy_ptr(mpEnd - n, mpEnd, mpEnd);
                eastl::copy_backward(position, mpEnd - n, mpEnd);
                eastl::fill(position, position + n, temp);
            } else {
                eastl::uninitialized_fill_n_ptr(mpEnd, n - nExtra, temp);
                eastl::uninitialized_copy_ptr(position, mpEnd, mpEnd + n - nExtra);
                eastl::fill(position, mpEnd, temp);
            }
            mpEnd += n;
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = GetNewCapacity(nPrevSize);
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        Rec38* const pNewData = DoAllocate(nNewSize);
        Rec38* pNewEnd = eastl::uninitialized_copy_ptr(mpBegin, position, pNewData);
        eastl::uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = eastl::uninitialized_copy_ptr(position, mpEnd, pNewEnd + n);
        eastl::destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// 1-byte trivial element (bool).
bool* uninitialized_copy_ptr(bool* first, bool* last, bool* result);
void uninitialized_fill_n_ptr(bool* first, uint32_t n, const bool& value);
bool* copy_backward(bool* first, bool* last, bool* result);
void fill(bool* first, bool* last, const bool& value);
void destruct(bool* first, bool* last);

template <> bool* vector<bool>::DoAllocate(uint32_t n)
{
    return n ? (bool*)eastl_alloc(&mAllocator, n, 1, 0) : 0;
}

template <> void vector<bool>::DoFree(bool* p, uint32_t)
{
    if (p)
        eastl_free(p);
}

// @ 0x004c10e0  eastl::vector<bool,fixed_vector_allocator<1,16,1,0,1>>::DoInsertValues
template <> void vector<bool>::DoInsertValues(bool* position, uint32_t n, const bool& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const bool temp = value;
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            if (n < nExtra) {
                eastl::uninitialized_copy_ptr(mpEnd - n, mpEnd, mpEnd);
                eastl::copy_backward(position, mpEnd - n, mpEnd);
                eastl::fill(position, position + n, temp);
            } else {
                eastl::uninitialized_fill_n_ptr(mpEnd, n - nExtra, temp);
                eastl::uninitialized_copy_ptr(position, mpEnd, mpEnd + n - nExtra);
                eastl::fill(position, mpEnd, temp);
            }
            mpEnd += n;
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = GetNewCapacity(nPrevSize);
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        bool* const pNewData = DoAllocate(nNewSize);
        bool* pNewEnd = eastl::uninitialized_copy_ptr(mpBegin, position, pNewData);
        eastl::uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = eastl::uninitialized_copy_ptr(position, mpEnd, pNewEnd + n);
        eastl::destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

} // namespace eastl

// ===========================================================================
// fixed_string<wchar_t,256> append helper (0x004c1ff0). Layout: begin/end/cap
// then an 8-byte fixed-vector allocator.
// ===========================================================================
namespace eastl {

struct WideFixedAlloc {
    uint32_t mOverflow;
    void* mpPoolBegin;
};

struct WideFixedStr {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    WideFixedAlloc mAllocator;

    void SetCapacity(uint32_t n);        // 0x004c26d0
    WideFixedStr* AppendN(uint32_t n, uint16_t c);
};

// @ 0x004c1ff0  eastl::basic_string<wchar_t,...>::append / resize(n,c)
WideFixedStr* WideFixedStr::AppendN(uint32_t n, uint16_t c)
{
    const uint32_t nSize = (uint32_t)(mpEnd - mpBegin);
    const uint32_t nCapacity = (uint32_t)(mpCapacity - mpBegin) - 1;
    if (nCapacity < nSize + n) {
        const uint32_t nRequired = nSize + n;
        const uint32_t nGrowSize = (nCapacity < 9) ? 8 : nCapacity * 2;
        SetCapacity(nGrowSize < nRequired ? nRequired : nGrowSize);
    }
    if (n != 0) {
        uint16_t* p = mpEnd + 1;
        uint16_t* const pEnd = p + n - 1;
        for (; p < pEnd; ++p)
            *p = c;
        *mpEnd = c;
        mpEnd += n;
        *mpEnd = 0;
    }
    return this;
}

} // namespace eastl

#pragma pack(pop)
