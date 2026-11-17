// uninitialized_copy over iterators (0x00764720): copy-construct each 0xa0-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x763e50); the end iterator is returned.
#include "game/types.h"

struct Elem_764720 {
    char mData[0xa0];
    Elem_764720(const Elem_764720& o);   // 0x00763e50
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_764720 {
    Elem_764720* mpNode;
    Iterator_764720(Elem_764720* p) : mpNode(p) {}
    Iterator_764720(const Iterator_764720& x) : mpNode(x.mpNode) {}
    Elem_764720& operator*() const { return *mpNode; }
    Iterator_764720& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_764720& x) const { return mpNode != x.mpNode; }
};

// @ 0x00764720
Iterator_764720 UninitializedCopy_764720(Iterator_764720 first, Iterator_764720 last, Iterator_764720 dest)
{
    Iterator_764720 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_764720(*first);
    return currentDest;
}
