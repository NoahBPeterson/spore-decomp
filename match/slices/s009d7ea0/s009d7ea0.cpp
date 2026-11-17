// uninitialized_copy over iterators (0x009d7ea0): copy-construct each 0x38-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x9d7dd0); the end iterator is returned.
#include "game/types.h"

struct Elem_9d7ea0 {
    char mData[0x38];
    Elem_9d7ea0(const Elem_9d7ea0& o);   // 0x009d7dd0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_9d7ea0 {
    Elem_9d7ea0* mpNode;
    Iterator_9d7ea0(Elem_9d7ea0* p) : mpNode(p) {}
    Iterator_9d7ea0(const Iterator_9d7ea0& x) : mpNode(x.mpNode) {}
    Elem_9d7ea0& operator*() const { return *mpNode; }
    Iterator_9d7ea0& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_9d7ea0& x) const { return mpNode != x.mpNode; }
};

// @ 0x009d7ea0
Iterator_9d7ea0 UninitializedCopy_9d7ea0(Iterator_9d7ea0 first, Iterator_9d7ea0 last, Iterator_9d7ea0 dest)
{
    Iterator_9d7ea0 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_9d7ea0(*first);
    return currentDest;
}
