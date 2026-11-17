// uninitialized_copy (0x00933a50): copy-construct each 0x20-byte element of [first, last) into raw storage at dest
// (copy constructor 0x614990); returns the end of the copied range.
#include "game/types.h"

struct Elem_933a50 {
    char mData[0x20];
    Elem_933a50(const Elem_933a50& o);   // 0x00614990
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00933a50
Elem_933a50* UninitializedCopy_933a50(const Elem_933a50* first, const Elem_933a50* last, Elem_933a50* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_933a50(*first);
    return dest;
}
