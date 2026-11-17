// vector::push_back (0x007a6ac0): with spare capacity the element is a ref copied and AddRef'd in place, otherwise DoInsertValue (0x7a6910) grows
// the vector.
#include "game/types.h"

struct RefObj_7a6ac0 {
    virtual void AddRef();
};
struct Elem_7a6ac0 {
    RefObj_7a6ac0* mpObject;
    Elem_7a6ac0(const Elem_7a6ac0& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_7a6ac0 {
    Elem_7a6ac0* mpBegin;
    Elem_7a6ac0* mpEnd;
    Elem_7a6ac0* mpCapacity;
    void DoInsertValue(Elem_7a6ac0* position, const Elem_7a6ac0& value);   // 0x007a6910
    void push_back(const Elem_7a6ac0& value);
};

// @ 0x007a6ac0
void Vector_7a6ac0::push_back(const Elem_7a6ac0& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_7a6ac0(value);
    else
        DoInsertValue(mpEnd, value);
}
