// uninitialized_copy (0x00e61880): copy-construct each 0x74-byte element of [first, last) into raw storage at dest
// (copy constructor 0xe61750); returns the end of the copied range.
#include "game/types.h"

struct Elem_e61880 {
    char mData[0x74];
    Elem_e61880(const Elem_e61880& o);   // 0x00e61750
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00e61880
Elem_e61880* UninitializedCopy_e61880(const Elem_e61880* first, const Elem_e61880* last, Elem_e61880* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_e61880(*first);
    return dest;
}
