// vector::push_back (0x006810e0): with spare capacity the element is copy-constructed in place (0x6800c0), otherwise DoInsertValue (0x680cc0) grows
// the vector.
#include "game/types.h"

struct Elem_6810e0 {
    char mData[0x48];
    Elem_6810e0(const Elem_6810e0& o);   // 0x006800c0
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_6810e0 {
    Elem_6810e0* mpBegin;
    Elem_6810e0* mpEnd;
    Elem_6810e0* mpCapacity;
    void DoInsertValue(Elem_6810e0* position, const Elem_6810e0& value);   // 0x00680cc0
    void push_back(const Elem_6810e0& value);
};

// @ 0x006810e0
void Vector_6810e0::push_back(const Elem_6810e0& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_6810e0(value);
    else
        DoInsertValue(mpEnd, value);
}
