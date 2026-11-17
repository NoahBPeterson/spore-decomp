// uninitialized_copy over iterators (0x009be710): copy-construct each 0x468-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x9b3e40); the end iterator is returned.
#include "game/types.h"

struct Elem_9be710 {
    char mData[0x468];
    Elem_9be710(const Elem_9be710& o);   // 0x009b3e40
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_9be710 {
    Elem_9be710* mpNode;
    Iterator_9be710(Elem_9be710* p) : mpNode(p) {}
    Iterator_9be710(const Iterator_9be710& x) : mpNode(x.mpNode) {}
    Elem_9be710& operator*() const { return *mpNode; }
    Iterator_9be710& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_9be710& x) const { return mpNode != x.mpNode; }
};

// @ 0x009be710
Iterator_9be710 UninitializedCopy_9be710(Iterator_9be710 first, Iterator_9be710 last, Iterator_9be710 dest)
{
    Iterator_9be710 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_9be710(*first);
    return currentDest;
}
