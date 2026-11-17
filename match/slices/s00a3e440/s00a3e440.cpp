// vector::push_back (0x00a3e440): with spare capacity the element is copy-constructed in place (0xa3dfa0), otherwise DoInsertValue (0xa3e280) grows
// the vector.
#include "game/types.h"

struct Elem_a3e440 {
    char mData[0x28];
    Elem_a3e440(const Elem_a3e440& o);   // 0x00a3dfa0
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_a3e440 {
    Elem_a3e440* mpBegin;
    Elem_a3e440* mpEnd;
    Elem_a3e440* mpCapacity;
    void DoInsertValue(Elem_a3e440* position, const Elem_a3e440& value);   // 0x00a3e280
    void push_back(const Elem_a3e440& value);
};

// @ 0x00a3e440
void Vector_a3e440::push_back(const Elem_a3e440& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_a3e440(value);
    else
        DoInsertValue(mpEnd, value);
}
