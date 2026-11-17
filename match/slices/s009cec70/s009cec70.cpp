// uninitialized_copy (0x009cec70): copy-construct each 0x108-byte element of [first, last) into raw storage at dest
// (copy constructor 0x9ce790); returns the end of the copied range.
#include "game/types.h"

struct Elem_9cec70 {
    char mData[0x108];
    Elem_9cec70(const Elem_9cec70& o);   // 0x009ce790
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x009cec70
Elem_9cec70* UninitializedCopy_9cec70(const Elem_9cec70* first, const Elem_9cec70* last, Elem_9cec70* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_9cec70(*first);
    return dest;
}
