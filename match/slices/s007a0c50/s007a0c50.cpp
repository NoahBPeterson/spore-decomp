// vector::push_back (0x007a0c50): with spare capacity the element is copy-constructed in place (0x79a4a0), otherwise DoInsertValue (0x7a0600) grows
// the vector.
#include "game/types.h"

struct Elem_7a0c50 {
    char mData[0x14];
    Elem_7a0c50(const Elem_7a0c50& o);   // 0x0079a4a0
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_7a0c50 {
    Elem_7a0c50* mpBegin;
    Elem_7a0c50* mpEnd;
    Elem_7a0c50* mpCapacity;
    void DoInsertValue(Elem_7a0c50* position, const Elem_7a0c50& value);   // 0x007a0600
    void push_back(const Elem_7a0c50& value);
};

// @ 0x007a0c50
void Vector_7a0c50::push_back(const Elem_7a0c50& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_7a0c50(value);
    else
        DoInsertValue(mpEnd, value);
}
