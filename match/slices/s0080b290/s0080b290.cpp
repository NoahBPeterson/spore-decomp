// uninitialized_copy (0x0080b290): copy-construct each 0x34-byte element of [first, last) into raw storage at dest
// (copy constructor 0x80af90); returns the end of the copied range.
#include "game/types.h"

struct Elem_80b290 {
    char mData[0x34];
    Elem_80b290(const Elem_80b290& o);   // 0x0080af90
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x0080b290
Elem_80b290* UninitializedCopy_80b290(const Elem_80b290* first, const Elem_80b290* last, Elem_80b290* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_80b290(*first);
    return dest;
}
