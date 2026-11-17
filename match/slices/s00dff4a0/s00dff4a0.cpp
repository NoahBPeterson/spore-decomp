// uninitialized_copy over iterators (0x00dff4a0): copy-construct each 0x27e0-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xdff1a0); the end iterator is returned.
#include "game/types.h"

struct Elem_dff4a0 {
    char mData[0x27e0];
    Elem_dff4a0(const Elem_dff4a0& o);   // 0x00dff1a0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_dff4a0 {
    Elem_dff4a0* mpNode;
    Iterator_dff4a0(Elem_dff4a0* p) : mpNode(p) {}
    Iterator_dff4a0(const Iterator_dff4a0& x) : mpNode(x.mpNode) {}
    Elem_dff4a0& operator*() const { return *mpNode; }
    Iterator_dff4a0& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_dff4a0& x) const { return mpNode != x.mpNode; }
};

// @ 0x00dff4a0
Iterator_dff4a0 UninitializedCopy_dff4a0(Iterator_dff4a0 first, Iterator_dff4a0 last, Iterator_dff4a0 dest)
{
    Iterator_dff4a0 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_dff4a0(*first);
    return currentDest;
}
