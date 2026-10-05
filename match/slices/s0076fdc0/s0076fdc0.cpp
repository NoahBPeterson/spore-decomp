// slice s0076fdc0: EASTL heap/sort primitives over a 0x14-byte element (function-pointer
// comparator), plus copy/fill helpers for 0x30/0x08-byte element types and the index-building
// helper at 0x0076fdc0.  Module is /O2 with SSE (aligned frames in the copy helpers).
#include "types.h"
#include <xmmintrin.h>

// ---------------------------------------------------------------------------
// 0x14-byte sort element.  The comparator (FUN_0076f540) compares the ints at
// +4, +8 and +0xc lexicographically.
// ---------------------------------------------------------------------------
struct SortElem {
    int f0, f1, f2, f3, f4;
};
typedef bool (__cdecl *SortCompare)(const SortElem&, const SortElem&);

// @ 0x0076f880  eastl::promote_heap(first, topPosition, position, value, compare)
__declspec(noinline)
void promote_heap(SortElem* first, int topPosition, int position, SortElem value,
                  SortCompare compare) {
    for (int parentPosition = (position - 1) >> 1;
         (position > topPosition) && compare(first[parentPosition], value);
         parentPosition = (position - 1) >> 1) {
        first[position] = first[parentPosition];
        position = parentPosition;
    }
    first[position] = value;
}

// @ 0x0076fef0  eastl::adjust_heap(first, topPosition, heapSize, position, value, compare)
__declspec(noinline)
void adjust_heap(SortElem* first, int topPosition, int heapSize, int position, SortElem value,
                 SortCompare compare) {
    int childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(first[childPosition], first[childPosition - 1]))
            --childPosition;
        first[position] = first[childPosition];
        position = childPosition;
    }
    if (childPosition == heapSize) {
        first[position] = first[childPosition - 1];
        position = childPosition - 1;
    }
    promote_heap(first, topPosition, position, value, compare);
}

// @ 0x00770180  eastl::pop_heap(first, last, compare)
__declspec(noinline)
void pop_heap(SortElem* first, SortElem* last, SortCompare compare) {
    const SortElem tempBottom(*(last - 1));
    *(last - 1) = *first;
    adjust_heap(first, 0, (int)(last - first) - 1, 0, tempBottom, compare);
}

// @ 0x00770240  eastl::make_heap(first, last, compare)
__declspec(noinline)
void make_heap(SortElem* first, SortElem* last, SortCompare compare) {
    const int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            adjust_heap(first, parentPosition, heapSize, parentPosition, first[parentPosition],
                        compare);
        } while (parentPosition != 0);
    }
}

// @ 0x007702c0  eastl::sort_heap(first, last, compare)
__declspec(noinline)
void sort_heap(SortElem* first, SortElem* last, SortCompare compare) {
    for (; (last - first) > 1; --last)
        pop_heap(first, last, compare);
}

// ---------------------------------------------------------------------------
// Small copy/fill helpers.
// ---------------------------------------------------------------------------

struct Pair8 {
    int a, b;
};

// @ 0x0076ffd0  copy of 8-byte elements; dest is null-checked
void copy8(Pair8** result, Pair8* first, Pair8* last, Pair8* dest) {
    *result = dest;
    if (first != last) {
        for (; first != last; ++first, ++dest) {
            if (dest) {
                dest->a = first->a;
                dest->b = first->b;
            }
        }
        *result = dest;
    }
}

// 0x30-byte element; the copy constructor copies a 16-byte aligned block plus
// six floats (the trailing 8 bytes are not part of the copied value).
struct Elem30 {
    __m128 v;
    float f4, f5, f6, f7, f8, f9;
    unsigned int tail0, tail1;
};

// @ 0x00770010  uninitialized_copy(first, last, dest) for Elem30
Elem30** uninit_copy30(Elem30** result, Elem30* first, Elem30* last, Elem30* dest) {
    *result = dest;
    if (first != last) {
        do {
            if (dest) {
                dest->v = first->v;
                dest->f4 = first->f4;
                dest->f5 = first->f5;
                dest->f6 = first->f6;
                dest->f7 = first->f7;
                dest->f8 = first->f8;
                dest->f9 = first->f9;
            }
            ++first;
            ++dest;
        } while (first != last);
        *result = dest;
    }
    return result;
}

struct Big30 {
    __m128 v;
    unsigned int b[8];
};

// @ 0x00770080  fill(first, last, value) for Big30
void fill30(Big30* first, Big30* last, const Big30& value) {
    while (first != last) {
        first->v = value.v;
        first->b[0] = value.b[0];
        first->b[1] = value.b[1];
        first->b[2] = value.b[2];
        first->b[3] = value.b[3];
        first->b[4] = value.b[4];
        first->b[5] = value.b[5];
        first->b[6] = value.b[6];
        first->b[7] = value.b[7];
        ++first;
    }
}

// @ 0x007700e0  uninitialized_fill_n(dest, n, value) for Big30
void uninit_fill_n30(Big30* dest, unsigned int n, const Big30& value) {
    while (n != 0) {
        if (dest) {
            dest->v = value.v;
            dest->b[0] = value.b[0];
            dest->b[1] = value.b[1];
            dest->b[2] = value.b[2];
            dest->b[3] = value.b[3];
            dest->b[4] = value.b[4];
            dest->b[5] = value.b[5];
            dest->b[6] = value.b[6];
            dest->b[7] = value.b[7];
        }
        dest = (Big30*)((char*)dest + 0x30);
        --n;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0076fdc0  build an 8-byte index table from a manager's 0x8c-byte records.
// ---------------------------------------------------------------------------
struct Item8 {
    int a, b;
};

struct Vec8 {
    Item8* begin;  // +0x00
    Item8* end;    // +0x04
};

struct Rec8c {
    int count;             // +0x00
    int* data;             // +0x04  (null => use count2 path)
    unsigned short field8; // +0x08
    unsigned short stride; // +0x0a
    int field0c;           // +0x0c
    int count2;            // +0x10
    // ... total 0x8c bytes
    char pad[0x8c - 0x14];
};

struct Mgr8c {
    char pad[0x1c];
    Rec8c* begin;  // +0x1c
    Rec8c* end;    // +0x20
};

extern unsigned int g_maskTable[];  // 0x0140e5b4

void __cdecl buildIndex(Mgr8c* mgr, Vec8* vec) {
    const int n = (int)(mgr->end - mgr->begin);
    const int numItems = (int)(vec->end - vec->begin);
    int local_c = 0;
    int off = 0;
    if (n <= 0)
        return;
    Item8* items = vec->begin;
    do {
        Rec8c* r = (Rec8c*)((char*)mgr->begin + off);
        if (r->data == 0) {
            const int cnt = r->count2;
            if (cnt > 0) {
                int i = 0;
                do {
                    if (i < numItems && items[i].a == -1) {
                        items[i].a = local_c;
                        items[i].b = i;
                    }
                    ++i;
                } while (i < cnt);
            }
        } else {
            const int cnt = r->count;
            int j = 0;
            if (cnt > 0) {
                do {
                    int val = *(int*)((char*)r->data + r->stride * j);
                    val &= (int)g_maskTable[r->field8];
                    if (val < numItems && items[val].a == -1) {
                        items[val].a = local_c;
                        items[val].b = j;
                    }
                    ++j;
                } while (j < cnt);
            }
        }
        off += 0x8c;
        ++local_c;
    } while (local_c < n);
}
