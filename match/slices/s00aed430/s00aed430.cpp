// uninitialized_copy (0x00aed430): copy-construct each 0x14-byte element of [first, last) into raw storage at dest
// (copy constructor 0x6b56f0); returns the end of the copied range.
#include "game/types.h"

struct Elem_aed430 {
    char mData[0x14];
    Elem_aed430(const Elem_aed430& o);   // 0x006b56f0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00aed430
Elem_aed430* UninitializedCopy_aed430(const Elem_aed430* first, const Elem_aed430* last, Elem_aed430* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_aed430(*first);
    return dest;
}
