// uninitialized_copy (0x00dfb340): copy-construct each 0x24-byte element of [first, last) into raw storage at dest
// (copy constructor 0xdfb130); returns the end of the copied range.
#include "game/types.h"

struct Elem_dfb340 {
    char mData[0x24];
    Elem_dfb340(const Elem_dfb340& o);   // 0x00dfb130
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00dfb340
Elem_dfb340* UninitializedCopy_dfb340(const Elem_dfb340* first, const Elem_dfb340* last, Elem_dfb340* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_dfb340(*first);
    return dest;
}
