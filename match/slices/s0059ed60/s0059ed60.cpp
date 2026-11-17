// uninitialized_copy (0x0059ed60): copy-construct each 0x18-byte element of [first, last) into raw storage at dest
// (copy constructor 0x810020); returns the end of the copied range.
#include "game/types.h"

struct Elem_59ed60 {
    char mData[0x18];
    Elem_59ed60(const Elem_59ed60& o);   // 0x00810020
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x0059ed60
Elem_59ed60* UninitializedCopy_59ed60(const Elem_59ed60* first, const Elem_59ed60* last, Elem_59ed60* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_59ed60(*first);
    return dest;
}
