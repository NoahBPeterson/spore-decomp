// vector::push_back (0x00a36ce0): with spare capacity the element is a ref copied and AddRef'd in place, otherwise DoInsertValue (0xa36ad0) grows
// the vector.
#include "game/types.h"

struct RefObj_a36ce0 {
    virtual void AddRef();
};
struct Elem_a36ce0 {
    RefObj_a36ce0* mpObject;
    Elem_a36ce0(const Elem_a36ce0& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_a36ce0 {
    Elem_a36ce0* mpBegin;
    Elem_a36ce0* mpEnd;
    Elem_a36ce0* mpCapacity;
    void DoInsertValue(Elem_a36ce0* position, const Elem_a36ce0& value);   // 0x00a36ad0
    void push_back(const Elem_a36ce0& value);
};

// @ 0x00a36ce0
void Vector_a36ce0::push_back(const Elem_a36ce0& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_a36ce0(value);
    else
        DoInsertValue(mpEnd, value);
}
