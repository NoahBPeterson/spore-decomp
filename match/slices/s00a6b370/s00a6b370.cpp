// uninitialized_copy (0x00a6b370): copy-construct each 0x58-byte element of [first, last) into raw storage at dest
// (copy constructor 0xa6b290); returns the end of the copied range.
#include "game/types.h"

struct Elem_a6b370 {
    char mData[0x58];
    Elem_a6b370(const Elem_a6b370& o);   // 0x00a6b290
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00a6b370
Elem_a6b370* UninitializedCopy_a6b370(const Elem_a6b370* first, const Elem_a6b370* last, Elem_a6b370* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_a6b370(*first);
    return dest;
}
