// uninitialized_copy over iterators (0x00bc56b0): copy-construct each 0x7b4-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xbc54f0); the end iterator is returned.
#include "game/types.h"

struct Elem_bc56b0 {
    char mData[0x7b4];
    Elem_bc56b0(const Elem_bc56b0& o);   // 0x00bc54f0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_bc56b0 {
    Elem_bc56b0* mpNode;
    Iterator_bc56b0(Elem_bc56b0* p) : mpNode(p) {}
    Iterator_bc56b0(const Iterator_bc56b0& x) : mpNode(x.mpNode) {}
    Elem_bc56b0& operator*() const { return *mpNode; }
    Iterator_bc56b0& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_bc56b0& x) const { return mpNode != x.mpNode; }
};

// @ 0x00bc56b0
Iterator_bc56b0 UninitializedCopy_bc56b0(Iterator_bc56b0 first, Iterator_bc56b0 last, Iterator_bc56b0 dest)
{
    Iterator_bc56b0 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_bc56b0(*first);
    return currentDest;
}
