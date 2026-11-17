// uninitialized_copy over iterators (0x00b02710): copy-construct each 0x20-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xb01cb0); the end iterator is returned.
#include "game/types.h"

struct Elem_b02710 {
    char mData[0x20];
    Elem_b02710(const Elem_b02710& o);   // 0x00b01cb0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_b02710 {
    Elem_b02710* mpNode;
    Iterator_b02710(Elem_b02710* p) : mpNode(p) {}
    Iterator_b02710(const Iterator_b02710& x) : mpNode(x.mpNode) {}
    Elem_b02710& operator*() const { return *mpNode; }
    Iterator_b02710& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_b02710& x) const { return mpNode != x.mpNode; }
};

// @ 0x00b02710
Iterator_b02710 UninitializedCopy_b02710(Iterator_b02710 first, Iterator_b02710 last, Iterator_b02710 dest)
{
    Iterator_b02710 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_b02710(*first);
    return currentDest;
}
