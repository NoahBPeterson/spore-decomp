// vector::push_back (0x007ca860): with spare capacity the element is a ref copied and AddRef'd in place, otherwise DoInsertValue (0x7c99e0) grows
// the vector.
#include "game/types.h"

struct RefObj_7ca860 {
    virtual void AddRef();
};
struct Elem_7ca860 {
    RefObj_7ca860* mpObject;
    Elem_7ca860(const Elem_7ca860& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_7ca860 {
    Elem_7ca860* mpBegin;
    Elem_7ca860* mpEnd;
    Elem_7ca860* mpCapacity;
    void DoInsertValue(Elem_7ca860* position, const Elem_7ca860& value);   // 0x007c99e0
    void push_back(const Elem_7ca860& value);
};

// @ 0x007ca860
void Vector_7ca860::push_back(const Elem_7ca860& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_7ca860(value);
    else
        DoInsertValue(mpEnd, value);
}
