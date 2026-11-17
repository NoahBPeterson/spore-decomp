// uninitialized_copy (0x009c84d0): copy-construct each 0x468-byte element of [first, last) into raw storage at dest
// (copy constructor 0x9b3e40); returns the end of the copied range.
#include "game/types.h"

struct Elem_9c84d0 {
    char mData[0x468];
    Elem_9c84d0(const Elem_9c84d0& o);   // 0x009b3e40
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x009c84d0
Elem_9c84d0* UninitializedCopy_9c84d0(const Elem_9c84d0* first, const Elem_9c84d0* last, Elem_9c84d0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_9c84d0(*first);
    return dest;
}
