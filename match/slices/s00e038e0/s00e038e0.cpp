// uninitialized_copy (0x00e038e0): copy-construct each 0x24-byte element of [first, last) into raw storage at dest
// (copy constructor 0xe03830); returns the end of the copied range.
#include "game/types.h"

struct Elem_e038e0 {
    char mData[0x24];
    Elem_e038e0(const Elem_e038e0& o);   // 0x00e03830
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00e038e0
Elem_e038e0* UninitializedCopy_e038e0(const Elem_e038e0* first, const Elem_e038e0* last, Elem_e038e0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_e038e0(*first);
    return dest;
}
