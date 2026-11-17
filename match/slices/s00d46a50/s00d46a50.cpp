// uninitialized_copy (0x00d46a50): copy-construct each 0x2c-byte element of [first, last) into raw storage at dest
// (copy constructor 0xd46900); returns the end of the copied range.
#include "game/types.h"

struct Elem_d46a50 {
    char mData[0x2c];
    Elem_d46a50(const Elem_d46a50& o);   // 0x00d46900
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00d46a50
Elem_d46a50* UninitializedCopy_d46a50(const Elem_d46a50* first, const Elem_d46a50* last, Elem_d46a50* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_d46a50(*first);
    return dest;
}
