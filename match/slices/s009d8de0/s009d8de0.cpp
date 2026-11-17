// uninitialized_copy (0x009d8de0): copy-construct each 0x104-byte element of [first, last) into raw storage at dest
// (copy constructor 0x9d8720); returns the end of the copied range.
#include "game/types.h"

struct Elem_9d8de0 {
    char mData[0x104];
    Elem_9d8de0(const Elem_9d8de0& o);   // 0x009d8720
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x009d8de0
Elem_9d8de0* UninitializedCopy_9d8de0(const Elem_9d8de0* first, const Elem_9d8de0* last, Elem_9d8de0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_9d8de0(*first);
    return dest;
}
