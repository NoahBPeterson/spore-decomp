// uninitialized_copy (0x009bf500): copy-construct each 0x10c-byte element of [first, last) into raw storage at dest
// (copy constructor 0x9be850); returns the end of the copied range.
#include "game/types.h"

struct Elem_9bf500 {
    char mData[0x10c];
    Elem_9bf500(const Elem_9bf500& o);   // 0x009be850
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x009bf500
Elem_9bf500* UninitializedCopy_9bf500(const Elem_9bf500* first, const Elem_9bf500* last, Elem_9bf500* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_9bf500(*first);
    return dest;
}
