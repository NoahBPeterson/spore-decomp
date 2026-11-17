// vector::push_back (0x007e9350): with spare capacity the element is a ref copied and AddRef'd in place, otherwise DoInsertValue (0x7e89c0) grows
// the vector.
#include "game/types.h"

struct RefObj_7e9350 {
    virtual void AddRef();
};
struct Elem_7e9350 {
    RefObj_7e9350* mpObject;
    Elem_7e9350(const Elem_7e9350& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_7e9350 {
    Elem_7e9350* mpBegin;
    Elem_7e9350* mpEnd;
    Elem_7e9350* mpCapacity;
    void DoInsertValue(Elem_7e9350* position, const Elem_7e9350& value);   // 0x007e89c0
    void push_back(const Elem_7e9350& value);
};

// @ 0x007e9350
void Vector_7e9350::push_back(const Elem_7e9350& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_7e9350(value);
    else
        DoInsertValue(mpEnd, value);
}
