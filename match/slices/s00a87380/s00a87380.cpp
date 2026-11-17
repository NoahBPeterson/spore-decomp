// uninitialized_copy (0x00a87380): copy-construct each 0x58-byte element of [first, last) into raw storage at dest
// (copy constructor 0xa87280); returns the end of the copied range.
#include "game/types.h"

struct Elem_a87380 {
    char mData[0x58];
    Elem_a87380(const Elem_a87380& o);   // 0x00a87280
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00a87380
Elem_a87380* UninitializedCopy_a87380(const Elem_a87380* first, const Elem_a87380* last, Elem_a87380* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_a87380(*first);
    return dest;
}
