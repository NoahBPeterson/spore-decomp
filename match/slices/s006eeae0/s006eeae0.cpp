// vector::push_back (0x006eeae0): with spare capacity the element is copy-constructed in place (0x6eb8c0), otherwise DoInsertValue (0x6ed6f0) grows
// the vector.
#include "game/types.h"

struct Elem_6eeae0 {
    char mData[0x68];
    Elem_6eeae0(const Elem_6eeae0& o);   // 0x006eb8c0
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_6eeae0 {
    Elem_6eeae0* mpBegin;
    Elem_6eeae0* mpEnd;
    Elem_6eeae0* mpCapacity;
    void DoInsertValue(Elem_6eeae0* position, const Elem_6eeae0& value);   // 0x006ed6f0
    void push_back(const Elem_6eeae0& value);
};

// @ 0x006eeae0
void Vector_6eeae0::push_back(const Elem_6eeae0& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_6eeae0(value);
    else
        DoInsertValue(mpEnd, value);
}
