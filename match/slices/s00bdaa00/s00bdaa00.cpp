// uninitialized_copy (0x00bdaa00): copy-construct each 0x50-byte element of [first, last) into raw storage at dest
// (copy constructor 0xbda7d0); returns the end of the copied range.
#include "game/types.h"

struct Elem_bdaa00 {
    char mData[0x50];
    Elem_bdaa00(const Elem_bdaa00& o);   // 0x00bda7d0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00bdaa00
Elem_bdaa00* UninitializedCopy_bdaa00(const Elem_bdaa00* first, const Elem_bdaa00* last, Elem_bdaa00* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_bdaa00(*first);
    return dest;
}
