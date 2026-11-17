// uninitialized_copy over iterators (0x00619610): copy-construct each 0x70-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x549500); the end iterator is returned.
#include "game/types.h"

struct Elem_619610 {
    char mData[0x70];
    Elem_619610(const Elem_619610& o);   // 0x00549500
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_619610 {
    Elem_619610* mpNode;
    Iterator_619610(Elem_619610* p) : mpNode(p) {}
    Iterator_619610(const Iterator_619610& x) : mpNode(x.mpNode) {}
    Elem_619610& operator*() const { return *mpNode; }
    Iterator_619610& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_619610& x) const { return mpNode != x.mpNode; }
};

// @ 0x00619610
Iterator_619610 UninitializedCopy_619610(Iterator_619610 first, Iterator_619610 last, Iterator_619610 dest)
{
    Iterator_619610 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_619610(*first);
    return currentDest;
}
