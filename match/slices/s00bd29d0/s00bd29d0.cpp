// uninitialized_copy (0x00bd29d0): copy-construct each 0xc64-byte element of [first, last) into raw storage at dest
// (copy constructor 0xb778b0); returns the end of the copied range.
#include "game/types.h"

struct Elem_bd29d0 {
    char mData[0xc64];
    Elem_bd29d0(const Elem_bd29d0& o);   // 0x00b778b0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00bd29d0
Elem_bd29d0* UninitializedCopy_bd29d0(const Elem_bd29d0* first, const Elem_bd29d0* last, Elem_bd29d0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_bd29d0(*first);
    return dest;
}
