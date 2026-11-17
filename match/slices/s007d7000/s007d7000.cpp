// vector::push_back (0x007d7000): with spare capacity the element is copy-constructed in place (0x7d5300), otherwise DoInsertValue (0x7d6620) grows
// the vector.
#include "game/types.h"

struct Elem_7d7000 {
    char mData[0x40];
    Elem_7d7000(const Elem_7d7000& o);   // 0x007d5300
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_7d7000 {
    Elem_7d7000* mpBegin;
    Elem_7d7000* mpEnd;
    Elem_7d7000* mpCapacity;
    void DoInsertValue(Elem_7d7000* position, const Elem_7d7000& value);   // 0x007d6620
    void push_back(const Elem_7d7000& value);
};

// @ 0x007d7000
void Vector_7d7000::push_back(const Elem_7d7000& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_7d7000(value);
    else
        DoInsertValue(mpEnd, value);
}
