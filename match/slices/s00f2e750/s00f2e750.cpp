// uninitialized_copy (0x00f2e750): copy-construct each 0x534-byte element of [first, last) into raw storage at dest
// (copy constructor 0xdff130); returns the end of the copied range.
#include "game/types.h"

struct Elem_f2e750 {
    char mData[0x534];
    Elem_f2e750(const Elem_f2e750& o);   // 0x00dff130
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00f2e750
Elem_f2e750* UninitializedCopy_f2e750(const Elem_f2e750* first, const Elem_f2e750* last, Elem_f2e750* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_f2e750(*first);
    return dest;
}
