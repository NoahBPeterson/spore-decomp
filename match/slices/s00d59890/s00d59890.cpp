// uninitialized_copy (0x00d59890): copy-construct each 0x1c-byte element of [first, last) into raw storage at dest
// (copy constructor 0xd59630); returns the end of the copied range.
#include "game/types.h"

struct Elem_d59890 {
    char mData[0x1c];
    Elem_d59890(const Elem_d59890& o);   // 0x00d59630
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00d59890
Elem_d59890* UninitializedCopy_d59890(const Elem_d59890* first, const Elem_d59890* last, Elem_d59890* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_d59890(*first);
    return dest;
}
