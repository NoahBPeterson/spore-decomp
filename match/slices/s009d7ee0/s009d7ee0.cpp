// uninitialized_copy (0x009d7ee0): copy-construct each 0x38-byte element of [first, last) into raw storage at dest
// (copy constructor 0x9d7dd0); returns the end of the copied range.
#include "game/types.h"

struct Elem_9d7ee0 {
    char mData[0x38];
    Elem_9d7ee0(const Elem_9d7ee0& o);   // 0x009d7dd0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x009d7ee0
Elem_9d7ee0* UninitializedCopy_9d7ee0(const Elem_9d7ee0* first, const Elem_9d7ee0* last, Elem_9d7ee0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_9d7ee0(*first);
    return dest;
}
