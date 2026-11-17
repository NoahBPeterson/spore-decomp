// uninitialized_copy over iterators (0x007f6e60): copy-construct each 0x8c-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x7f6df0); the end iterator is returned.
#include "game/types.h"

struct Elem_7f6e60 {
    char mData[0x8c];
    Elem_7f6e60(const Elem_7f6e60& o);   // 0x007f6df0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_7f6e60 {
    Elem_7f6e60* mpNode;
    Iterator_7f6e60(Elem_7f6e60* p) : mpNode(p) {}
    Iterator_7f6e60(const Iterator_7f6e60& x) : mpNode(x.mpNode) {}
    Elem_7f6e60& operator*() const { return *mpNode; }
    Iterator_7f6e60& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_7f6e60& x) const { return mpNode != x.mpNode; }
};

// @ 0x007f6e60
Iterator_7f6e60 UninitializedCopy_7f6e60(Iterator_7f6e60 first, Iterator_7f6e60 last, Iterator_7f6e60 dest)
{
    Iterator_7f6e60 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_7f6e60(*first);
    return currentDest;
}
