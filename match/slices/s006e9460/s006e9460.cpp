// uninitialized_copy (0x006e9460): copy-construct each 0x70-byte element of [first, last) into raw storage at dest
// (copy constructor 0x6e9330); returns the end of the copied range.
#include "game/types.h"

struct Elem_6e9460 {
    char mData[0x70];
    Elem_6e9460(const Elem_6e9460& o);   // 0x006e9330
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x006e9460
Elem_6e9460* UninitializedCopy_6e9460(const Elem_6e9460* first, const Elem_6e9460* last, Elem_6e9460* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_6e9460(*first);
    return dest;
}
