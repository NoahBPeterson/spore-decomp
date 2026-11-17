// uninitialized_copy (0x00fa9b10): copy-construct each 0x110-byte element of [first, last) into raw storage at dest
// (copy constructor 0xfa9840); returns the end of the copied range.
#include "game/types.h"

struct Elem_fa9b10 {
    char mData[0x110];
    Elem_fa9b10(const Elem_fa9b10& o);   // 0x00fa9840
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00fa9b10
Elem_fa9b10* UninitializedCopy_fa9b10(const Elem_fa9b10* first, const Elem_fa9b10* last, Elem_fa9b10* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_fa9b10(*first);
    return dest;
}
