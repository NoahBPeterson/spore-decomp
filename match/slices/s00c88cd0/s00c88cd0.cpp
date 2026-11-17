// uninitialized_copy (0x00c88cd0): copy-construct each 0x3c-byte element of [first, last) into raw storage at dest
// (copy constructor 0xc88ba0); returns the end of the copied range.
#include "game/types.h"

struct Elem_c88cd0 {
    char mData[0x3c];
    Elem_c88cd0(const Elem_c88cd0& o);   // 0x00c88ba0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00c88cd0
Elem_c88cd0* UninitializedCopy_c88cd0(const Elem_c88cd0* first, const Elem_c88cd0* last, Elem_c88cd0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_c88cd0(*first);
    return dest;
}
