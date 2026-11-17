// uninitialized_copy (0x00de6ba0): copy-construct each 0xbc-byte element of [first, last) into raw storage at dest
// (copy constructor 0xde60f0); returns the end of the copied range.
#include "game/types.h"

struct Elem_de6ba0 {
    char mData[0xbc];
    Elem_de6ba0(const Elem_de6ba0& o);   // 0x00de60f0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00de6ba0
Elem_de6ba0* UninitializedCopy_de6ba0(const Elem_de6ba0* first, const Elem_de6ba0* last, Elem_de6ba0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_de6ba0(*first);
    return dest;
}
