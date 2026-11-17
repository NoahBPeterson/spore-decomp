// uninitialized_copy over iterators (0x010233e0): copy-construct each 0x1c-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x7d0ac0); the end iterator is returned.
#include "game/types.h"

struct Elem_10233e0 {
    char mData[0x1c];
    Elem_10233e0(const Elem_10233e0& o);   // 0x007d0ac0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_10233e0 {
    Elem_10233e0* mpNode;
    Iterator_10233e0(Elem_10233e0* p) : mpNode(p) {}
    Iterator_10233e0(const Iterator_10233e0& x) : mpNode(x.mpNode) {}
    Elem_10233e0& operator*() const { return *mpNode; }
    Iterator_10233e0& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_10233e0& x) const { return mpNode != x.mpNode; }
};

// @ 0x010233e0
Iterator_10233e0 UninitializedCopy_10233e0(Iterator_10233e0 first, Iterator_10233e0 last, Iterator_10233e0 dest)
{
    Iterator_10233e0 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_10233e0(*first);
    return currentDest;
}
