// vector::push_back (0x007cca90): with spare capacity the element is copy-constructed in place (0x7cc6f0), otherwise DoInsertValue (0x7cc7f0) grows
// the vector.
#include "game/types.h"

struct Elem_7cca90 {
    char mData[0xac];
    Elem_7cca90(const Elem_7cca90& o);   // 0x007cc6f0
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_7cca90 {
    Elem_7cca90* mpBegin;
    Elem_7cca90* mpEnd;
    Elem_7cca90* mpCapacity;
    void DoInsertValue(Elem_7cca90* position, const Elem_7cca90& value);   // 0x007cc7f0
    void push_back(const Elem_7cca90& value);
};

// @ 0x007cca90
void Vector_7cca90::push_back(const Elem_7cca90& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_7cca90(value);
    else
        DoInsertValue(mpEnd, value);
}
