// uninitialized_copy over iterators (0x00aa1d30): copy-construct each 0x28-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xaa1cc0); the end iterator is returned.
#include "game/types.h"

struct Elem_aa1d30 {
    char mData[0x28];
    Elem_aa1d30(const Elem_aa1d30& o);   // 0x00aa1cc0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_aa1d30 {
    Elem_aa1d30* mpNode;
    Iterator_aa1d30(Elem_aa1d30* p) : mpNode(p) {}
    Iterator_aa1d30(const Iterator_aa1d30& x) : mpNode(x.mpNode) {}
    Elem_aa1d30& operator*() const { return *mpNode; }
    Iterator_aa1d30& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_aa1d30& x) const { return mpNode != x.mpNode; }
};

// @ 0x00aa1d30
Iterator_aa1d30 UninitializedCopy_aa1d30(Iterator_aa1d30 first, Iterator_aa1d30 last, Iterator_aa1d30 dest)
{
    Iterator_aa1d30 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_aa1d30(*first);
    return currentDest;
}
