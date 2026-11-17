// uninitialized_copy (0x010066a0): copy-construct each 0x1c-byte element of [first, last) into raw storage at dest
// (copy constructor 0x1006630); returns the end of the copied range.
#include "game/types.h"

struct Elem_10066a0 {
    char mData[0x1c];
    Elem_10066a0(const Elem_10066a0& o);   // 0x01006630
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x010066a0
Elem_10066a0* UninitializedCopy_10066a0(const Elem_10066a0* first, const Elem_10066a0* last, Elem_10066a0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_10066a0(*first);
    return dest;
}
