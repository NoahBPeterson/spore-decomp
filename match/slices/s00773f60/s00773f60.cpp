// slice s00773f60: EASTL sort machinery over the 0x14-byte element with a
// function-pointer comparator (get_partition / partial_sort / introsort_loop /
// sort), plus vector helpers and UI glue functions for the same module.
#include "types.h"

struct SortElem {
    int f0, f1, f2, f3, f4;
};
typedef bool (__cdecl *SortCompare)(const SortElem&, const SortElem&);

// Defined in earlier slices (masked relocations).
void insertion_sort(SortElem* first, SortElem* last, SortCompare compare);
void unguarded_insertion_sort(SortElem* first, SortElem* last, SortCompare compare);
void make_heap(SortElem* first, SortElem* last, SortCompare compare);
void adjust_heap(SortElem* first, int topPosition, int heapSize, int position, SortElem value,
                 SortCompare compare);
void sort_heap(SortElem* first, SortElem* last, SortCompare compare);
void partial_sort(SortElem* first, SortElem* middle, SortElem* last, SortCompare compare);
void introsort_loop(SortElem* first, SortElem* last, int depthLimit, SortCompare compare);

// @ 0x00773f60
SortElem* get_partition(SortElem* first, SortElem* last, SortElem pivotValue, SortCompare compare) {
    for (;; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        const SortElem temp(*first);
        *first = *last;
        *last = temp;
    }
}

// @ 0x00774010
void partial_sort(SortElem* first, SortElem* middle, SortElem* last, SortCompare compare) {
    make_heap(first, middle, compare);
    for (SortElem* i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            const SortElem temp(*i);
            *i = *first;
            adjust_heap(first, 0, (int)(middle - first), 0, temp, compare);
        }
    }
    sort_heap(first, middle, compare);
}

// @ 0x00774290
void introsort_loop(SortElem* first, SortElem* last, int depthLimit, SortCompare compare) {
    do {
        if (((last - first) <= 0x1c) || (depthLimit <= 0)) {
            if (depthLimit == 0)
                partial_sort(first, last, last, compare);
            return;
        }
        SortElem* middle = first + (last - first) / 2;
        SortElem* pivot = first;
        if (compare(*first, *middle)) {
            if (compare(*middle, *(last - 1))) {
                pivot = middle;
            } else {
                middle = last - 1;
                if (compare(*first, *(last - 1)))
                    pivot = last - 1;
                else
                    pivot = first;
            }
        } else {
            if (compare(*first, *(last - 1))) {
                pivot = first;
            } else {
                if (compare(*middle, *(last - 1)))
                    pivot = last - 1;
                else
                    pivot = middle;
            }
        }
        SortElem* cut = get_partition(first, last, *pivot, compare);
        --depthLimit;
        introsort_loop(cut, last, depthLimit, compare);
        last = cut;
    } while (true);
}

// @ 0x007749e0
void sort_range(SortElem* first, SortElem* last, SortCompare compare) {
    if (first != last) {
        const int nSize = (int)(last - first);
        int nDepth = 0;
        for (int i = nSize; i > 0; i >>= 1)
            ++nDepth;
        introsort_loop(first, last, (nDepth * 2) - 2, compare);
        if (nSize > 0x1c) {
            insertion_sort(first, first + 0x1c, compare);
            unguarded_insertion_sort(first + 0x1c, last, compare);
        } else {
            insertion_sort(first, last, compare);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x007740f0  thunk into the big 0x00770320 method on the global at 0x01630b68
// ---------------------------------------------------------------------------
struct Unk770320 {
    unsigned int Method(unsigned int param_2, int* param_3);
};
extern Unk770320 g_770320;

void FUN_007740f0(unsigned int param_1, int* param_2) {
    g_770320.Method(param_1, param_2);
}

// ---------------------------------------------------------------------------
// Remaining functions in this slice are EASTL vector / UI glue for element
// types of 0x08, 0x30 and 0xb0 bytes (plus one EH-framed UI function).  They
// are recorded as partial: the algorithms are known but not reproduced
// byte-for-byte, so these are signature-only skeletons.  See partial.txt.
// ---------------------------------------------------------------------------
// 8-byte element: a pair of ints, grown with the (-1, -1) sentinel.
struct Idx2 {
    int m0;
    int m1;
    Idx2(int v) { m0 = v; m1 = v; }
};

struct VecIdx2 {
    Idx2* mpBegin;              // +0
    Idx2* mpEnd;                // +4
    Idx2* mpCapacity;           // +8
    void InsertN(Idx2* position, unsigned n, const Idx2& value);   // 0x00707D10
    void Erase(Idx2* first, Idx2* last);                           // 0x00D018D0
    void resize(unsigned n);
};

// @ 0x00774B50
void VecIdx2::resize(unsigned n) {
    if (n > (unsigned)(mpEnd - mpBegin)) {
        Idx2 value(-1);
        InsertN(mpEnd, n - (unsigned)(mpEnd - mpBegin), value);
    } else {
        Erase(mpBegin + n, mpEnd);
    }
}

// 0x30-byte element (12 floats).
struct __declspec(align(16)) Blob30 {
    float m[12];
};

void Move30(Blob30* first, Blob30* last, Blob30* dst);             // 0x0076F990
void MoveB0(void* first, void* last, void* dst);                   // 0x0076FA30

struct Vec30 {
    Blob30* mpBegin;            // +0
    Blob30* mpEnd;              // +4
    Blob30* mpCapacity;         // +8
    void InsertN(Blob30* position, unsigned n, const Blob30& value);   // 0x007743B0
    void resize(unsigned n);
};

// @ 0x00774BB0
void Vec30::resize(unsigned n) {
    if (n > (unsigned)(mpEnd - mpBegin)) {
        Blob30 value;
        InsertN(mpEnd, n - (unsigned)(mpEnd - mpBegin), value);
    } else {
        Blob30* position = mpBegin + n;
        Blob30* last = mpEnd;
        Move30(last, last, position);
        mpEnd -= (last - position);
    }
}

// 0xb0-byte element.
struct __declspec(align(16)) BlobB0 {
    char m[0xb0];
};

struct VecB0 {
    BlobB0* mpBegin;            // +0
    BlobB0* mpEnd;              // +4
    BlobB0* mpCapacity;         // +8
    void InsertN(BlobB0* position, unsigned n, const BlobB0& value);   // 0x007745D0
    void resize(unsigned n);
};

// @ 0x00774C30
void VecB0::resize(unsigned n) {
    if (n > (unsigned)(mpEnd - mpBegin)) {
        BlobB0 value;
        InsertN(mpEnd, n - (unsigned)(mpEnd - mpBegin), value);
    } else {
        BlobB0* position = mpBegin + n;
        BlobB0* last = mpEnd;
        MoveB0(last, last, position);
        mpEnd -= (last - position);
    }
}

// 0x30-byte matrix element (its own vector instantiation: copy ctor + out-of-line erase).
struct Mat34 {
    float m[12];
};

struct VecM34 {
    Mat34* mpBegin;             // +0
    Mat34* mpEnd;               // +4
    Mat34* mpCapacity;          // +8
    void InsertN(Mat34* position, unsigned n, const Mat34& value);     // 0x007747C0
    void Erase(Mat34* first, Mat34* last);                             // 0x009C69F0
    void resize(unsigned n);
};

// @ 0x00774CC0
void VecM34::resize(unsigned n) {
    if (n > (unsigned)(mpEnd - mpBegin)) {
        Mat34 value;
        InsertN(mpEnd, n - (unsigned)(mpEnd - mpBegin), value);
    } else {
        Erase(mpBegin + n, mpEnd);
    }
}

// ---------------------------------------------------------------------------
// insert_n for the three vector instantiations above.
// ---------------------------------------------------------------------------
extern "C" void* malloc(unsigned bytes);
extern "C" void free(void* p);
extern "C" void* memcpy(void* dst, const void* src, unsigned n);
extern "C" void* memmove(void* dst, const void* src, unsigned n);

#define INSERT_N_BODY(T)                                                   \
    T* begin = mpBegin;                                                        \
    T* end = mpEnd;                                                            \
    unsigned size = (unsigned)(end - begin);                                   \
    unsigned index = (unsigned)(position - begin);                             \
    unsigned after;                                                            \
    unsigned i;                                                                \
    if (n > (unsigned)(mpCapacity - end)) {                                    \
        /* EASTL grows to max(2 * size, size + n). */                          \
        unsigned newCapacity = size + n;                                       \
        unsigned grown = size * 2;                                             \
        if (grown == 0)                                                        \
            grown = 1;                                                         \
        if (newCapacity < grown)                                               \
            newCapacity = grown;                                               \
        T* newBuf = (T*)malloc(newCapacity * sizeof(T));                       \
        if (index)                                                             \
            memcpy(newBuf, begin, index * sizeof(T));                          \
        for (i = 0; i < n; ++i)                                                \
            memcpy(newBuf + index + i, &value, sizeof(T));                     \
        after = size - index;                                                  \
        if (after)                                                             \
            memcpy(newBuf + index + n, begin + index, after * sizeof(T));      \
        if (begin)                                                             \
            free(begin);                                                       \
        mpBegin = newBuf;                                                      \
        mpEnd = newBuf + size + n;                                             \
        mpCapacity = newBuf + newCapacity;                                     \
    } else {                                                                   \
        after = size - index;                                                  \
        if (after)                                                             \
            memmove(position + n, position, after * sizeof(T));                \
        for (unsigned i = 0; i < n; ++i)                                       \
            memcpy(position + i, &value, sizeof(T));                           \
        mpEnd = end + n;                                                       \
    }

// @ 0x007743B0
void Vec30::InsertN(Blob30* position, unsigned n, const Blob30& value) {
    INSERT_N_BODY(Blob30)
}

// @ 0x007745D0
void VecB0::InsertN(BlobB0* position, unsigned n, const BlobB0& value) {
    INSERT_N_BODY(BlobB0)
}

// @ 0x007747C0
void VecM34::InsertN(Mat34* position, unsigned n, const Mat34& value) {
    INSERT_N_BODY(Mat34)
}

// ---------------------------------------------------------------------------
// 0x14-byte element in a vector with an inline 16-element buffer at +0x18.
// ---------------------------------------------------------------------------
struct Elt14 {
    int m[5];
};

Elt14* Copy14(const Elt14* first, const Elt14* last, Elt14* dst);         // 0x00951BF0
Elt14* Alloc14Range(unsigned n, const Elt14* first, const Elt14* last, const void* owner);  // 0x00774980
void Free14(Elt14* p);                                                    // 0x00F47380

struct Vec14Fixed {
    Elt14* mpBegin;             // +0x00
    Elt14* mpEnd;               // +0x04
    Elt14* mpCapacity;          // +0x08
    void* mUnkC;                // +0x0c
    Elt14* mpFixed;             // +0x10
    int mUnk14;                 // +0x14
    Elt14 mBuffer[16];          // +0x18
    Vec14Fixed* assign(const Elt14* first, const Elt14* last, const Elt14* endHint);
    Vec14Fixed(const Elt14* first, const Elt14* last);
};

// @ 0x00774A60  assign(first, last, endHint) for the 0x14-byte element (ret 0xc)
Vec14Fixed* Vec14Fixed::assign(const Elt14* first, const Elt14* last, const Elt14* endHint) {
    (void)endHint;
    unsigned n = (unsigned)(last - first);
    if (n > (unsigned)(mpCapacity - mpBegin)) {
        Elt14* p = Alloc14Range(n, first, last, endHint);
        if (mpBegin && mpBegin != mpFixed)
            Free14(mpBegin);
        mpBegin = p;
        mpEnd = p + n;
        mpCapacity = p + n;
    } else {
        unsigned size = (unsigned)(mpEnd - mpBegin);
        if (n > size) {
            // Copy the existing tail, then construct the remaining elements
            // in the spare capacity.
            Elt14* mid = const_cast<Elt14*>(first) + size;
            Copy14(first, mid, mpBegin);
            for (unsigned i = size; i < n; ++i)
                mpBegin[i] = first[i];
            mpEnd = mpBegin + n;
        } else {
            mpEnd = Copy14(first, last, mpBegin);
        }
    }
    return this;
}

// @ 0x00774F10  fixed_vector range constructor (ret 8)
Vec14Fixed::Vec14Fixed(const Elt14* first, const Elt14* last) {
    // mpFixed = mBuffer; begin = end = mBuffer; capacity = mBuffer + 16;

    mpFixed = mBuffer;
    mpBegin = mBuffer;
    mpEnd = mBuffer;
    mpCapacity = mBuffer + 16;
    assign(first, last, last);
}

// @ 0x00774110  UI / resource glue with an EH frame -- skeleton
void FUN_00774110(int* param_1, unsigned param_2, int* param_3) {
    (void)param_1;
    (void)param_2;
    (void)param_3;
}
