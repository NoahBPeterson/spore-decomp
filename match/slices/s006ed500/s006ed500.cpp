// vector::push_back (0x006ed500): with spare capacity the element is a ref copied and AddRef'd in place, otherwise DoInsertValue (0x6ec8a0) grows
// the vector.
#include "game/types.h"

struct RefObj_6ed500 {
    virtual void AddRef();
};
struct Elem_6ed500 {
    RefObj_6ed500* mpObject;
    Elem_6ed500(const Elem_6ed500& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct Vector_6ed500 {
    Elem_6ed500* mpBegin;
    Elem_6ed500* mpEnd;
    Elem_6ed500* mpCapacity;
    void DoInsertValue(Elem_6ed500* position, const Elem_6ed500& value);   // 0x006ec8a0
    void push_back(const Elem_6ed500& value);
};

// @ 0x006ed500
void Vector_6ed500::push_back(const Elem_6ed500& value)
{
    if (mpEnd < mpCapacity)
        new (mpEnd++) Elem_6ed500(value);
    else
        DoInsertValue(mpEnd, value);
}
