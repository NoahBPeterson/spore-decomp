#include "game/types.h"
#include "SP/cOrnamentData.h"
#include "eastl/vector.h"

namespace eastl {

// eastl::copy for trivially assignable elements: forward copy, returning the
// end of the destination range.  The destination precedes the source, so a
// forward copy is safe.
template <class T>
inline T* CopyRemainingOrnaments(T* first, T* last, T* destination) {
    for (; first != last; ++destination, ++first)
        *destination = *first;
    return destination;
}

// @ 0x00ff1840
template <>
vector<SP::cOrnamentData, sp_vector_allocator>::iterator
vector<SP::cOrnamentData, sp_vector_allocator>::erase(iterator first, iterator last) {
    // Reference implementation of vector::erase: move the tail down over the
    // erased range, destroy the moved-from values, then shrink the vector.
    iterator const position = CopyRemainingOrnaments(last, mpEnd, first);
    for (iterator p = position; p < mpEnd; ++p)
        p->~cOrnamentData();
    mpEnd -= last - first;
    return first;
}

}
