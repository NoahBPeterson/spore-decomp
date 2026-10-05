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
struct VecStub {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    int* mpAlloc;
    int* mFixed;
    // @ 0x007743b0
    void insert_n30(int position, unsigned n, int* value) {
        (void)position; (void)n; (void)value;
    }
    // @ 0x007745d0
    void insert_nB0(int position, unsigned n, int* value) {
        (void)position; (void)n; (void)value;
    }
    // @ 0x007747c0
    void insert_nM34(int position, unsigned n, int* value) {
        (void)position; (void)n; (void)value;
    }
    // @ 0x00774a60
    void insert_range(int first, int last) {
        (void)first; (void)last;
    }
    // @ 0x00774b50
    void resize8(unsigned n) {
        (void)n;
    }
    // @ 0x00774bb0
    void resize30(unsigned n) {
        (void)n;
    }
    // @ 0x00774c30
    void resizeB0(unsigned n) {
        (void)n;
    }
    // @ 0x00774cc0
    void resizeM34(unsigned n) {
        (void)n;
    }
    // @ 0x00774f10
    VecStub* init_range(int first, int last) {
        (void)first; (void)last;
        return this;
    }
};

// @ 0x00774110  UI / resource glue with an EH frame -- skeleton
void FUN_00774110(int* param_1, unsigned param_2, int* param_3) {
    (void)param_1;
    (void)param_2;
    (void)param_3;
}
