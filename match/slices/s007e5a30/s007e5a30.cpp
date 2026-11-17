// vector::push_back (0x007e5a30): with spare capacity the element is copy-constructed in place (0x7e2ae0), otherwise DoInsertValue (0x7e5890) grows
// the vector.
#include "game/types.h"

struct Elem_7e5a30 {
    char mData[0x50];
    Elem_7e5a30(const Elem_7e5a30& o);   // 0x007e2ae0
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_7e5a30 {
    Elem_7e5a30* mpBegin;
    Elem_7e5a30* mpEnd;
    Elem_7e5a30* mpCapacity;
    void DoInsertValue(Elem_7e5a30* position, const Elem_7e5a30& value);   // 0x007e5890
    void push_back(const Elem_7e5a30& value);
};

// @ 0x007e5a30
void Vector_7e5a30::push_back(const Elem_7e5a30& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_7e5a30(value);
    else
        DoInsertValue(mpEnd, value);
}
