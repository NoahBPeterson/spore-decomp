// uninitialized_copy over iterators (0x00a6b330): copy-construct each 0x58-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xa6b290); the end iterator is returned.
#include "game/types.h"

struct Elem_a6b330 {
    char mData[0x58];
    Elem_a6b330(const Elem_a6b330& o);   // 0x00a6b290
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_a6b330 {
    Elem_a6b330* mpNode;
    Iterator_a6b330(Elem_a6b330* p) : mpNode(p) {}
    Iterator_a6b330(const Iterator_a6b330& x) : mpNode(x.mpNode) {}
    Elem_a6b330& operator*() const { return *mpNode; }
    Iterator_a6b330& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_a6b330& x) const { return mpNode != x.mpNode; }
};

// @ 0x00a6b330
Iterator_a6b330 UninitializedCopy_a6b330(Iterator_a6b330 first, Iterator_a6b330 last, Iterator_a6b330 dest)
{
    Iterator_a6b330 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_a6b330(*first);
    return currentDest;
}
