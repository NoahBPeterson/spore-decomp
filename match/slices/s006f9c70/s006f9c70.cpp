// vector::push_back (0x006f9c70): with spare capacity the element is copy-constructed in place (0x6f95e0), otherwise DoInsertValue (0x6f9ac0) grows
// the vector.
#include "game/types.h"

struct Elem_6f9c70 {
    char mData[0x78];
    Elem_6f9c70(const Elem_6f9c70& o);   // 0x006f95e0
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_6f9c70 {
    Elem_6f9c70* mpBegin;
    Elem_6f9c70* mpEnd;
    Elem_6f9c70* mpCapacity;
    void DoInsertValue(Elem_6f9c70* position, const Elem_6f9c70& value);   // 0x006f9ac0
    void push_back(const Elem_6f9c70& value);
};

// @ 0x006f9c70
void Vector_6f9c70::push_back(const Elem_6f9c70& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_6f9c70(value);
    else
        DoInsertValue(mpEnd, value);
}
