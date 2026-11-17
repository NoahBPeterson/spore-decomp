// uninitialized_copy (0x00f148c0): copy-construct each 0x70-byte element of [first, last) into raw storage at dest
// (copy constructor 0xf14690); returns the end of the copied range.
#include "game/types.h"

struct Elem_f148c0 {
    char mData[0x70];
    Elem_f148c0(const Elem_f148c0& o);   // 0x00f14690
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00f148c0
Elem_f148c0* UninitializedCopy_f148c0(const Elem_f148c0* first, const Elem_f148c0* last, Elem_f148c0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_f148c0(*first);
    return dest;
}
