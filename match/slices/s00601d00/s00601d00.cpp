// uninitialized_copy (0x00601d00): copy-construct each 0x58-byte element of [first, last) into raw storage at dest
// (copy constructor 0x601a70); returns the end of the copied range.
#include "game/types.h"

struct Elem_601d00 {
    char mData[0x58];
    Elem_601d00(const Elem_601d00& o);   // 0x00601a70
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00601d00
Elem_601d00* UninitializedCopy_601d00(const Elem_601d00* first, const Elem_601d00* last, Elem_601d00* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_601d00(*first);
    return dest;
}
