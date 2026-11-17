// uninitialized_copy over iterators (0x009a1bb0): copy-construct each 0x1f0-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x9a17d0); the end iterator is returned.
#include "game/types.h"

struct Elem_9a1bb0 {
    char mData[0x1f0];
    Elem_9a1bb0(const Elem_9a1bb0& o);   // 0x009a17d0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_9a1bb0 {
    Elem_9a1bb0* mpNode;
    Iterator_9a1bb0(Elem_9a1bb0* p) : mpNode(p) {}
    Iterator_9a1bb0(const Iterator_9a1bb0& x) : mpNode(x.mpNode) {}
    Elem_9a1bb0& operator*() const { return *mpNode; }
    Iterator_9a1bb0& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_9a1bb0& x) const { return mpNode != x.mpNode; }
};

// @ 0x009a1bb0
Iterator_9a1bb0 UninitializedCopy_9a1bb0(Iterator_9a1bb0 first, Iterator_9a1bb0 last, Iterator_9a1bb0 dest)
{
    Iterator_9a1bb0 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_9a1bb0(*first);
    return currentDest;
}
