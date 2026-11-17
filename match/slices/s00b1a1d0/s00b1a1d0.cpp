// uninitialized_copy over iterators (0x00b1a1d0): copy-construct each 0x38-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xb1a0f0); the end iterator is returned.
#include "game/types.h"

struct Elem_b1a1d0 {
    char mData[0x38];
    Elem_b1a1d0(const Elem_b1a1d0& o);   // 0x00b1a0f0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_b1a1d0 {
    Elem_b1a1d0* mpNode;
    Iterator_b1a1d0(Elem_b1a1d0* p) : mpNode(p) {}
    Iterator_b1a1d0(const Iterator_b1a1d0& x) : mpNode(x.mpNode) {}
    Elem_b1a1d0& operator*() const { return *mpNode; }
    Iterator_b1a1d0& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_b1a1d0& x) const { return mpNode != x.mpNode; }
};

// @ 0x00b1a1d0
Iterator_b1a1d0 UninitializedCopy_b1a1d0(Iterator_b1a1d0 first, Iterator_b1a1d0 last, Iterator_b1a1d0 dest)
{
    Iterator_b1a1d0 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_b1a1d0(*first);
    return currentDest;
}
