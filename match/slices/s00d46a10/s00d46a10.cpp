// uninitialized_copy over iterators (0x00d46a10): copy-construct each 0x2c-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xd46900); the end iterator is returned.
#include "game/types.h"

struct Elem_d46a10 {
    char mData[0x2c];
    Elem_d46a10(const Elem_d46a10& o);   // 0x00d46900
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_d46a10 {
    Elem_d46a10* mpNode;
    Iterator_d46a10(Elem_d46a10* p) : mpNode(p) {}
    Iterator_d46a10(const Iterator_d46a10& x) : mpNode(x.mpNode) {}
    Elem_d46a10& operator*() const { return *mpNode; }
    Iterator_d46a10& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_d46a10& x) const { return mpNode != x.mpNode; }
};

// @ 0x00d46a10
Iterator_d46a10 UninitializedCopy_d46a10(Iterator_d46a10 first, Iterator_d46a10 last, Iterator_d46a10 dest)
{
    Iterator_d46a10 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_d46a10(*first);
    return currentDest;
}
