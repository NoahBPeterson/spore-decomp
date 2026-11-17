// vector::push_back (0x006da2e0): with spare capacity the element is copy-constructed in place (0x6c2ad0), otherwise DoInsertValue (0x6d9660) grows
// the vector.
#include "game/types.h"

struct Elem_6da2e0 {
    char mData[0x10];
    Elem_6da2e0(const Elem_6da2e0& o);   // 0x006c2ad0
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_6da2e0 {
    Elem_6da2e0* mpBegin;
    Elem_6da2e0* mpEnd;
    Elem_6da2e0* mpCapacity;
    void DoInsertValue(Elem_6da2e0* position, const Elem_6da2e0& value);   // 0x006d9660
    void push_back(const Elem_6da2e0& value);
};

// @ 0x006da2e0
void Vector_6da2e0::push_back(const Elem_6da2e0& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_6da2e0(value);
    else
        DoInsertValue(mpEnd, value);
}
