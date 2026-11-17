// uninitialized_copy (0x00cd70c0): copy-construct each 0x1c-byte element of [first, last) into raw storage at dest
// (copy constructor 0xcd7010); returns the end of the copied range.
#include "game/types.h"

struct Elem_cd70c0 {
    char mData[0x1c];
    Elem_cd70c0(const Elem_cd70c0& o);   // 0x00cd7010
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00cd70c0
Elem_cd70c0* UninitializedCopy_cd70c0(const Elem_cd70c0* first, const Elem_cd70c0* last, Elem_cd70c0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_cd70c0(*first);
    return dest;
}
