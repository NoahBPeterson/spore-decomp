// vector::push_back (0x0083a830): with spare capacity the element is copy-constructed in place (0xe84850), otherwise DoInsertValue (0x83a580) grows
// the vector.
#include "game/types.h"

struct Elem_83a830 {
    char mData[0x18];
    Elem_83a830(const Elem_83a830& o);   // 0x00e84850
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_83a830 {
    Elem_83a830* mpBegin;
    Elem_83a830* mpEnd;
    Elem_83a830* mpCapacity;
    void DoInsertValue(Elem_83a830* position, const Elem_83a830& value);   // 0x0083a580
    void push_back(const Elem_83a830& value);
};

// @ 0x0083a830
void Vector_83a830::push_back(const Elem_83a830& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_83a830(value);
    else
        DoInsertValue(mpEnd, value);
}
