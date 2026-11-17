// uninitialized_copy over iterators (0x0080b970): copy-construct each 0x34-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x80af90); the end iterator is returned.
#include "game/types.h"

struct Elem_80b970 {
    char mData[0x34];
    Elem_80b970(const Elem_80b970& o);   // 0x0080af90
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_80b970 {
    Elem_80b970* mpNode;
    Iterator_80b970(Elem_80b970* p) : mpNode(p) {}
    Iterator_80b970(const Iterator_80b970& x) : mpNode(x.mpNode) {}
    Elem_80b970& operator*() const { return *mpNode; }
    Iterator_80b970& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_80b970& x) const { return mpNode != x.mpNode; }
};

// @ 0x0080b970
Iterator_80b970 UninitializedCopy_80b970(Iterator_80b970 first, Iterator_80b970 last, Iterator_80b970 dest)
{
    Iterator_80b970 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_80b970(*first);
    return currentDest;
}
