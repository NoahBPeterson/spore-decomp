// uninitialized_copy (0x0059f700): copy-construct each 0xc4-byte element of [first, last) into raw storage at dest
// (copy constructor 0x59f2a0); returns the end of the copied range.
#include "game/types.h"

struct Elem_59f700 {
    char mData[0xc4];
    Elem_59f700(const Elem_59f700& o);   // 0x0059f2a0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x0059f700
Elem_59f700* UninitializedCopy_59f700(const Elem_59f700* first, const Elem_59f700* last, Elem_59f700* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_59f700(*first);
    return dest;
}
