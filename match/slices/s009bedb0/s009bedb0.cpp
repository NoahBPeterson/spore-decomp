// uninitialized_copy over iterators (0x009bedb0): copy-construct each 0x10c-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x9be850); the end iterator is returned.
#include "game/types.h"

struct Elem_9bedb0 {
    char mData[0x10c];
    Elem_9bedb0(const Elem_9bedb0& o);   // 0x009be850
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_9bedb0 {
    Elem_9bedb0* mpNode;
    Iterator_9bedb0(Elem_9bedb0* p) : mpNode(p) {}
    Iterator_9bedb0(const Iterator_9bedb0& x) : mpNode(x.mpNode) {}
    Elem_9bedb0& operator*() const { return *mpNode; }
    Iterator_9bedb0& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_9bedb0& x) const { return mpNode != x.mpNode; }
};

// @ 0x009bedb0
Iterator_9bedb0 UninitializedCopy_9bedb0(Iterator_9bedb0 first, Iterator_9bedb0 last, Iterator_9bedb0 dest)
{
    Iterator_9bedb0 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_9bedb0(*first);
    return currentDest;
}
