// uninitialized_copy over iterators (0x00a87340): copy-construct each 0x58-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xa87280); the end iterator is returned.
#include "game/types.h"

struct Elem_a87340 {
    char mData[0x58];
    Elem_a87340(const Elem_a87340& o);   // 0x00a87280
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_a87340 {
    Elem_a87340* mpNode;
    Iterator_a87340(Elem_a87340* p) : mpNode(p) {}
    Iterator_a87340(const Iterator_a87340& x) : mpNode(x.mpNode) {}
    Elem_a87340& operator*() const { return *mpNode; }
    Iterator_a87340& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_a87340& x) const { return mpNode != x.mpNode; }
};

// @ 0x00a87340
Iterator_a87340 UninitializedCopy_a87340(Iterator_a87340 first, Iterator_a87340 last, Iterator_a87340 dest)
{
    Iterator_a87340 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_a87340(*first);
    return currentDest;
}
