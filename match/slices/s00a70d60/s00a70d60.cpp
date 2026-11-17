// uninitialized_copy (0x00a70d60): copy-construct each 0x5c-byte element of [first, last) into raw storage at dest
// (copy constructor 0xa70cc0); returns the end of the copied range.
#include "game/types.h"

struct Elem_a70d60 {
    char mData[0x5c];
    Elem_a70d60(const Elem_a70d60& o);   // 0x00a70cc0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00a70d60
Elem_a70d60* UninitializedCopy_a70d60(const Elem_a70d60* first, const Elem_a70d60* last, Elem_a70d60* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_a70d60(*first);
    return dest;
}
