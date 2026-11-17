// vector::push_back (0x00a2aac0): with spare capacity the element is a ref copied and AddRef'd in place, otherwise DoInsertValue (0xa27760) grows
// the vector.
#include "game/types.h"

struct RefObj_a2aac0 {
    virtual void AddRef();
};
struct Elem_a2aac0 {
    RefObj_a2aac0* mpObject;
    Elem_a2aac0(const Elem_a2aac0& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_a2aac0 {
    Elem_a2aac0* mpBegin;
    Elem_a2aac0* mpEnd;
    Elem_a2aac0* mpCapacity;
    void DoInsertValue(Elem_a2aac0* position, const Elem_a2aac0& value);   // 0x00a27760
    void push_back(const Elem_a2aac0& value);
};

// @ 0x00a2aac0
void Vector_a2aac0::push_back(const Elem_a2aac0& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_a2aac0(value);
    else
        DoInsertValue(mpEnd, value);
}
