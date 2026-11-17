// vector::push_back (0x0076efd0): with spare capacity the element is copy-constructed in place (0x76e750), otherwise DoInsertValue (0x76edf0) grows
// the vector.
#include "game/types.h"

struct Elem_76efd0 {
    char mData[0x3c];
    Elem_76efd0(const Elem_76efd0& o);   // 0x0076e750
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_76efd0 {
    Elem_76efd0* mpBegin;
    Elem_76efd0* mpEnd;
    Elem_76efd0* mpCapacity;
    void DoInsertValue(Elem_76efd0* position, const Elem_76efd0& value);   // 0x0076edf0
    void push_back(const Elem_76efd0& value);
};

// @ 0x0076efd0
void Vector_76efd0::push_back(const Elem_76efd0& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_76efd0(value);
    else
        DoInsertValue(mpEnd, value);
}
