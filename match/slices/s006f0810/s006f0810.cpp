// vector::push_back (0x006f0810): with spare capacity the element is copy-constructed in place (0x6e9230), otherwise DoInsertValue (0x6eeb60) grows
// the vector.
#include "game/types.h"

struct Elem_6f0810 {
    char mData[0x70];
    Elem_6f0810(const Elem_6f0810& o);   // 0x006e9230
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_6f0810 {
    Elem_6f0810* mpBegin;
    Elem_6f0810* mpEnd;
    Elem_6f0810* mpCapacity;
    void DoInsertValue(Elem_6f0810* position, const Elem_6f0810& value);   // 0x006eeb60
    void push_back(const Elem_6f0810& value);
};

// @ 0x006f0810
void Vector_6f0810::push_back(const Elem_6f0810& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_6f0810(value);
    else
        DoInsertValue(mpEnd, value);
}
