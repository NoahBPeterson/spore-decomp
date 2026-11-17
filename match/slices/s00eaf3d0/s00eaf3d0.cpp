// uninitialized_copy (0x00eaf3d0): copy-construct each 0x6c-byte element of [first, last) into raw storage at dest
// (copy constructor 0xeaf190); returns the end of the copied range.
#include "game/types.h"

struct Elem_eaf3d0 {
    char mData[0x6c];
    Elem_eaf3d0(const Elem_eaf3d0& o);   // 0x00eaf190
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00eaf3d0
Elem_eaf3d0* UninitializedCopy_eaf3d0(const Elem_eaf3d0* first, const Elem_eaf3d0* last, Elem_eaf3d0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_eaf3d0(*first);
    return dest;
}
