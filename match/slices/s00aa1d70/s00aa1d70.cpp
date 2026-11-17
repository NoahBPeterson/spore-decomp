// uninitialized_copy (0x00aa1d70): copy-construct each 0x28-byte element of [first, last) into raw storage at dest
// (copy constructor 0xaa1cc0); returns the end of the copied range.
#include "game/types.h"

struct Elem_aa1d70 {
    char mData[0x28];
    Elem_aa1d70(const Elem_aa1d70& o);   // 0x00aa1cc0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00aa1d70
Elem_aa1d70* UninitializedCopy_aa1d70(const Elem_aa1d70* first, const Elem_aa1d70* last, Elem_aa1d70* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_aa1d70(*first);
    return dest;
}
