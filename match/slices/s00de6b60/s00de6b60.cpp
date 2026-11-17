// uninitialized_copy over iterators (0x00de6b60): copy-construct each 0xbc-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xde60f0); the end iterator is returned.
#include "game/types.h"

struct Elem_de6b60 {
    char mData[0xbc];
    Elem_de6b60(const Elem_de6b60& o);   // 0x00de60f0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_de6b60 {
    Elem_de6b60* mpNode;
    Iterator_de6b60(Elem_de6b60* p) : mpNode(p) {}
    Iterator_de6b60(const Iterator_de6b60& x) : mpNode(x.mpNode) {}
    Elem_de6b60& operator*() const { return *mpNode; }
    Iterator_de6b60& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_de6b60& x) const { return mpNode != x.mpNode; }
};

// @ 0x00de6b60
Iterator_de6b60 UninitializedCopy_de6b60(Iterator_de6b60 first, Iterator_de6b60 last, Iterator_de6b60 dest)
{
    Iterator_de6b60 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_de6b60(*first);
    return currentDest;
}
