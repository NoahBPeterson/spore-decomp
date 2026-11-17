// uninitialized_copy over iterators (0x009bedf0): copy-construct each 0x2bc-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x9bea50); the end iterator is returned.
#include "game/types.h"

struct Elem_9bedf0 {
    char mData[0x2bc];
    Elem_9bedf0(const Elem_9bedf0& o);   // 0x009bea50
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_9bedf0 {
    Elem_9bedf0* mpNode;
    Iterator_9bedf0(Elem_9bedf0* p) : mpNode(p) {}
    Iterator_9bedf0(const Iterator_9bedf0& x) : mpNode(x.mpNode) {}
    Elem_9bedf0& operator*() const { return *mpNode; }
    Iterator_9bedf0& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_9bedf0& x) const { return mpNode != x.mpNode; }
};

// @ 0x009bedf0
Iterator_9bedf0 UninitializedCopy_9bedf0(Iterator_9bedf0 first, Iterator_9bedf0 last, Iterator_9bedf0 dest)
{
    Iterator_9bedf0 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_9bedf0(*first);
    return currentDest;
}
