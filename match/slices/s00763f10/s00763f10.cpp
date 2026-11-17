// uninitialized_copy (0x00763f10): copy-construct each 0xa0-byte element of [first, last) into raw storage at dest
// (copy constructor 0x763e50); returns the end of the copied range.
#include "game/types.h"

struct Elem_763f10 {
    char mData[0xa0];
    Elem_763f10(const Elem_763f10& o);   // 0x00763e50
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00763f10
Elem_763f10* UninitializedCopy_763f10(const Elem_763f10* first, const Elem_763f10* last, Elem_763f10* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_763f10(*first);
    return dest;
}
