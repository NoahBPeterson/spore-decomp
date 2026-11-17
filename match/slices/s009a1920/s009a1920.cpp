// uninitialized_copy (0x009a1920): copy-construct each 0x1f0-byte element of [first, last) into raw storage at dest
// (copy constructor 0x9a17d0); returns the end of the copied range.
#include "game/types.h"

struct Elem_9a1920 {
    char mData[0x1f0];
    Elem_9a1920(const Elem_9a1920& o);   // 0x009a17d0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x009a1920
Elem_9a1920* UninitializedCopy_9a1920(const Elem_9a1920* first, const Elem_9a1920* last, Elem_9a1920* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_9a1920(*first);
    return dest;
}
