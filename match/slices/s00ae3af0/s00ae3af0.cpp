// uninitialized_copy (0x00ae3af0): copy-construct each 0x64-byte element of [first, last) into raw storage at dest
// (copy constructor 0xae3a10); returns the end of the copied range.
#include "game/types.h"

struct Elem_ae3af0 {
    char mData[0x64];
    Elem_ae3af0(const Elem_ae3af0& o);   // 0x00ae3a10
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00ae3af0
Elem_ae3af0* UninitializedCopy_ae3af0(const Elem_ae3af0* first, const Elem_ae3af0* last, Elem_ae3af0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_ae3af0(*first);
    return dest;
}
