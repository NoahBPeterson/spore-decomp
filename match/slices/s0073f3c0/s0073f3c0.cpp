// uninitialized_copy (0x0073f3c0): copy-construct each 0xc4-byte element of [first, last) into raw storage at dest
// (copy constructor 0x73f1c0); returns the end of the copied range.
#include "game/types.h"

struct Elem_73f3c0 {
    char mData[0xc4];
    Elem_73f3c0(const Elem_73f3c0& o);   // 0x0073f1c0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x0073f3c0
Elem_73f3c0* UninitializedCopy_73f3c0(const Elem_73f3c0* first, const Elem_73f3c0* last, Elem_73f3c0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_73f3c0(*first);
    return dest;
}
