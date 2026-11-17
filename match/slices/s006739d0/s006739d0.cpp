// uninitialized_copy (0x006739d0): copy-construct each 0x63c-byte element of [first, last) into raw storage at dest
// (copy constructor 0x673870); returns the end of the copied range.
#include "game/types.h"

struct Elem_6739d0 {
    char mData[0x63c];
    Elem_6739d0(const Elem_6739d0& o);   // 0x00673870
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x006739d0
Elem_6739d0* UninitializedCopy_6739d0(const Elem_6739d0* first, const Elem_6739d0* last, Elem_6739d0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_6739d0(*first);
    return dest;
}
