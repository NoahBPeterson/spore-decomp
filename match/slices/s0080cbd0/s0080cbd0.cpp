// uninitialized_copy (0x0080cbd0): copy-construct each 0x42c-byte element of [first, last) into raw storage at dest
// (copy constructor 0x80cb30); returns the end of the copied range.
#include "game/types.h"

struct Elem_80cbd0 {
    char mData[0x42c];
    Elem_80cbd0(const Elem_80cbd0& o);   // 0x0080cb30
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x0080cbd0
Elem_80cbd0* UninitializedCopy_80cbd0(const Elem_80cbd0* first, const Elem_80cbd0* last, Elem_80cbd0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_80cbd0(*first);
    return dest;
}
