// vector::push_back (0x0070dd50): with spare capacity the element is copy-constructed in place (0x708100), otherwise DoInsertValue (0x70ced0) grows
// the vector.
#include "game/types.h"

struct Elem_70dd50 {
    char mData[0x144];
    Elem_70dd50(const Elem_70dd50& o);   // 0x00708100
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_70dd50 {
    Elem_70dd50* mpBegin;
    Elem_70dd50* mpEnd;
    Elem_70dd50* mpCapacity;
    void DoInsertValue(Elem_70dd50* position, const Elem_70dd50& value);   // 0x0070ced0
    void push_back(const Elem_70dd50& value);
};

// @ 0x0070dd50
void Vector_70dd50::push_back(const Elem_70dd50& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_70dd50(value);
    else
        DoInsertValue(mpEnd, value);
}
