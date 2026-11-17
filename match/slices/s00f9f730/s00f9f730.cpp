// uninitialized_copy (0x00f9f730): copy-construct each 0xac-byte element of [first, last) into raw storage at dest
// (copy constructor 0xf9b1e0); returns the end of the copied range.
#include "game/types.h"

struct Elem_f9f730 {
    char mData[0xac];
    Elem_f9f730(const Elem_f9f730& o);   // 0x00f9b1e0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00f9f730
Elem_f9f730* UninitializedCopy_f9f730(const Elem_f9f730* first, const Elem_f9f730* last, Elem_f9f730* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_f9f730(*first);
    return dest;
}
