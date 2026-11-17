// vector::push_back (0x006956f0): with spare capacity the element is copy-constructed in place (0x6940d0), otherwise DoInsertValue (0x695550) grows
// the vector.
#include "game/types.h"

struct Elem_6956f0 {
    char mData[0x60];
    Elem_6956f0(const Elem_6956f0& o);   // 0x006940d0
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_6956f0 {
    Elem_6956f0* mpBegin;
    Elem_6956f0* mpEnd;
    Elem_6956f0* mpCapacity;
    void DoInsertValue(Elem_6956f0* position, const Elem_6956f0& value);   // 0x00695550
    void push_back(const Elem_6956f0& value);
};

// @ 0x006956f0
void Vector_6956f0::push_back(const Elem_6956f0& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_6956f0(value);
    else
        DoInsertValue(mpEnd, value);
}
