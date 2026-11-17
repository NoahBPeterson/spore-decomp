// uninitialized_copy over iterators (0x00a09560): copy-construct each 0x1c-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xa093b0); the end iterator is returned.
#include "game/types.h"

struct Elem_a09560 {
    char mData[0x1c];
    Elem_a09560(const Elem_a09560& o);   // 0x00a093b0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_a09560 {
    Elem_a09560* mpNode;
    Iterator_a09560(Elem_a09560* p) : mpNode(p) {}
    Iterator_a09560(const Iterator_a09560& x) : mpNode(x.mpNode) {}
    Elem_a09560& operator*() const { return *mpNode; }
    Iterator_a09560& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_a09560& x) const { return mpNode != x.mpNode; }
};

// @ 0x00a09560
Iterator_a09560 UninitializedCopy_a09560(Iterator_a09560 first, Iterator_a09560 last, Iterator_a09560 dest)
{
    Iterator_a09560 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_a09560(*first);
    return currentDest;
}
