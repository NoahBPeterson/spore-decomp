// uninitialized_copy (0x00b1a210): copy-construct each 0x38-byte element of [first, last) into raw storage at dest
// (copy constructor 0xb1a0f0); returns the end of the copied range.
#include "game/types.h"

struct Elem_b1a210 {
    char mData[0x38];
    Elem_b1a210(const Elem_b1a210& o);   // 0x00b1a0f0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00b1a210
Elem_b1a210* UninitializedCopy_b1a210(const Elem_b1a210* first, const Elem_b1a210* last, Elem_b1a210* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_b1a210(*first);
    return dest;
}
