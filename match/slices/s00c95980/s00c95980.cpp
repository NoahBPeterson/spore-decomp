// Slice s00c95980: eastl::quick_sort<cSPVector3_*, SP::(anon)::ComparePositions> (0x00c95980, 226 bytes).
// __cdecl, three stack args: first, last, and the 12-byte comparator copied by value (ret 0, caller pops).
// Callees: quick_sort_impl<cSPVector3*,int,ComparePositions> 0x00c94ec0, insertion_sort 0x00c90920,
// insertion_sort_simple 0x00c90a40. Each callee receives the comparator by value again.
#include "types.h"

namespace SP {
struct cSPVector3 {
    float x, y, z;      // 12 bytes, passed by value on the stack
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }   // user copy ctor: per-field copies
};

namespace {
struct ComparePositions {
    cSPVector3 mRef;    // 12-byte functor; the operator() body is not part of this function
};
}
}

namespace eastl {

template <typename RandomAccessIterator, typename Compare>
void quick_sort_impl(RandomAccessIterator first, RandomAccessIterator last, int kRecursionCount, Compare compare);   // 0x00c94ec0

template <typename RandomAccessIterator, typename Compare>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare);   // 0x00c90920

template <typename RandomAccessIterator, typename Compare>
void insertion_sort_simple(RandomAccessIterator first, RandomAccessIterator last, Compare compare);   // 0x00c90a40

template <typename Size>
inline Size Log2(Size n) {
    int i;
    for (i = 0; n; ++i)
        n >>= 1;
    return i - 1;
}

static const int kQuickSortLimit = 28;

// @ 0x00c95980  eastl::quick_sort<cSPVector3_*, ComparePositions>
template <typename RandomAccessIterator, typename Compare>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare) {
    if (first != last) {
        quick_sort_impl<RandomAccessIterator, Compare>(first, last, 2 * Log2((int)(last - first)), compare);
        if ((int)(last - first) > kQuickSortLimit) {
            insertion_sort<RandomAccessIterator, Compare>(first, first + kQuickSortLimit, compare);
            insertion_sort_simple<RandomAccessIterator, Compare>(first + kQuickSortLimit, last, compare);
        } else
            insertion_sort<RandomAccessIterator, Compare>(first, last, compare);
    }
}

}  // namespace eastl

template void eastl::quick_sort<SP::cSPVector3*, SP::ComparePositions>(SP::cSPVector3*, SP::cSPVector3*, SP::ComparePositions);
