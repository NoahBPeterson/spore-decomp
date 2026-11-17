// uninitialized_copy over iterators (0x00a6a9c0): copy-construct each 0x84-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xa6a2f0); the end iterator is returned.
#include "game/types.h"

struct Elem_a6a9c0 {
    char mData[0x84];
    Elem_a6a9c0(const Elem_a6a9c0& o);   // 0x00a6a2f0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_a6a9c0 {
    Elem_a6a9c0* mpNode;
    Iterator_a6a9c0(Elem_a6a9c0* p) : mpNode(p) {}
    Iterator_a6a9c0(const Iterator_a6a9c0& x) : mpNode(x.mpNode) {}
    Elem_a6a9c0& operator*() const { return *mpNode; }
    Iterator_a6a9c0& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_a6a9c0& x) const { return mpNode != x.mpNode; }
};

// @ 0x00a6a9c0
Iterator_a6a9c0 UninitializedCopy_a6a9c0(Iterator_a6a9c0 first, Iterator_a6a9c0 last, Iterator_a6a9c0 dest)
{
    Iterator_a6a9c0 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_a6a9c0(*first);
    return currentDest;
}
