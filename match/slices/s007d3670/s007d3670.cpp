// vector::push_back (0x007d3670): with spare capacity the element is copy-constructed in place (0x7d1140), otherwise DoInsertValue (0x7d3210) grows
// the vector.
#include "game/types.h"

struct Elem_7d3670 {
    char mData[0x2c];
    Elem_7d3670(const Elem_7d3670& o);   // 0x007d1140
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_7d3670 {
    Elem_7d3670* mpBegin;
    Elem_7d3670* mpEnd;
    Elem_7d3670* mpCapacity;
    void DoInsertValue(Elem_7d3670* position, const Elem_7d3670& value);   // 0x007d3210
    void push_back(const Elem_7d3670& value);
};

// @ 0x007d3670
void Vector_7d3670::push_back(const Elem_7d3670& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_7d3670(value);
    else
        DoInsertValue(mpEnd, value);
}
