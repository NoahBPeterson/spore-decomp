// uninitialized_copy (0x00ebbdf0): copy-construct each 0x50-byte element of [first, last) into raw storage at dest
// (copy constructor 0xebbcd0); returns the end of the copied range.
#include "game/types.h"

struct Elem_ebbdf0 {
    char mData[0x50];
    Elem_ebbdf0(const Elem_ebbdf0& o);   // 0x00ebbcd0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00ebbdf0
Elem_ebbdf0* UninitializedCopy_ebbdf0(const Elem_ebbdf0* first, const Elem_ebbdf0* last, Elem_ebbdf0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_ebbdf0(*first);
    return dest;
}
