// vector::push_back (0x007d36f0): with spare capacity the element is copy-constructed in place (0x7d0d60), otherwise DoInsertValue (0x7d33e0) grows
// the vector.
#include "game/types.h"

struct Elem_7d36f0 {
    char mData[0x68];
    Elem_7d36f0(const Elem_7d36f0& o);   // 0x007d0d60
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_7d36f0 {
    Elem_7d36f0* mpBegin;
    Elem_7d36f0* mpEnd;
    Elem_7d36f0* mpCapacity;
    void DoInsertValue(Elem_7d36f0* position, const Elem_7d36f0& value);   // 0x007d33e0
    void push_back(const Elem_7d36f0& value);
};

// @ 0x007d36f0
void Vector_7d36f0::push_back(const Elem_7d36f0& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_7d36f0(value);
    else
        DoInsertValue(mpEnd, value);
}
