// uninitialized_copy (0x00a69d20): copy-construct each 0x24-byte element of [first, last) into raw storage at dest
// (copy constructor 0xa69b20); returns the end of the copied range.
#include "game/types.h"

struct Elem_a69d20 {
    char mData[0x24];
    Elem_a69d20(const Elem_a69d20& o);   // 0x00a69b20
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00a69d20
Elem_a69d20* UninitializedCopy_a69d20(const Elem_a69d20* first, const Elem_a69d20* last, Elem_a69d20* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_a69d20(*first);
    return dest;
}
