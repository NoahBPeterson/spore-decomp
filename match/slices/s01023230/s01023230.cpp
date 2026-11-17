// uninitialized_copy (0x01023230): copy-construct each 0x1c-byte element of [first, last) into raw storage at dest
// (copy constructor 0x7d0ac0); returns the end of the copied range.
#include "game/types.h"

struct Elem_1023230 {
    char mData[0x1c];
    Elem_1023230(const Elem_1023230& o);   // 0x007d0ac0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x01023230
Elem_1023230* UninitializedCopy_1023230(const Elem_1023230* first, const Elem_1023230* last, Elem_1023230* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_1023230(*first);
    return dest;
}
