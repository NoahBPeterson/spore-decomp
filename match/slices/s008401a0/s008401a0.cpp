// vector::push_back (0x008401a0): with spare capacity the element is copy-constructed in place (0x83fae0), otherwise DoInsertValue (0x83fff0) grows
// the vector.
#include "game/types.h"

struct Elem_8401a0 {
    char mData[0x14];
    Elem_8401a0(const Elem_8401a0& o);   // 0x0083fae0
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_8401a0 {
    Elem_8401a0* mpBegin;
    Elem_8401a0* mpEnd;
    Elem_8401a0* mpCapacity;
    void DoInsertValue(Elem_8401a0* position, const Elem_8401a0& value);   // 0x0083fff0
    void push_back(const Elem_8401a0& value);
};

// @ 0x008401a0
void Vector_8401a0::push_back(const Elem_8401a0& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_8401a0(value);
    else
        DoInsertValue(mpEnd, value);
}
