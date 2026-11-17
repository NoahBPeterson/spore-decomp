// uninitialized_copy (0x009bf580): copy-construct each 0x2bc-byte element of [first, last) into raw storage at dest
// (copy constructor 0x9bea50); returns the end of the copied range.
#include "game/types.h"

struct Elem_9bf580 {
    char mData[0x2bc];
    Elem_9bf580(const Elem_9bf580& o);   // 0x009bea50
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x009bf580
Elem_9bf580* UninitializedCopy_9bf580(const Elem_9bf580* first, const Elem_9bf580* last, Elem_9bf580* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_9bf580(*first);
    return dest;
}
