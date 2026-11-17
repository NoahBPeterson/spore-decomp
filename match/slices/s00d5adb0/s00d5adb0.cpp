// uninitialized_copy (0x00d5adb0): copy-construct each 0x64-byte element of [first, last) into raw storage at dest
// (copy constructor 0xc278e0); returns the end of the copied range.
#include "game/types.h"

struct Elem_d5adb0 {
    char mData[0x64];
    Elem_d5adb0(const Elem_d5adb0& o);   // 0x00c278e0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00d5adb0
Elem_d5adb0* UninitializedCopy_d5adb0(const Elem_d5adb0* first, const Elem_d5adb0* last, Elem_d5adb0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_d5adb0(*first);
    return dest;
}
