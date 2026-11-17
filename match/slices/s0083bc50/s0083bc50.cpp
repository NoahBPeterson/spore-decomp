// vector::push_back (0x0083bc50): with spare capacity the element is copy-constructed in place (0x839e00), otherwise DoInsertValue (0x83baa0) grows
// the vector.
#include "game/types.h"

struct Elem_83bc50 {
    char mData[0x38];
    Elem_83bc50(const Elem_83bc50& o);   // 0x00839e00
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_83bc50 {
    Elem_83bc50* mpBegin;
    Elem_83bc50* mpEnd;
    Elem_83bc50* mpCapacity;
    void DoInsertValue(Elem_83bc50* position, const Elem_83bc50& value);   // 0x0083baa0
    void push_back(const Elem_83bc50& value);
};

// @ 0x0083bc50
void Vector_83bc50::push_back(const Elem_83bc50& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_83bc50(value);
    else
        DoInsertValue(mpEnd, value);
}
