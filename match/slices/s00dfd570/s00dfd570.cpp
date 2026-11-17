// uninitialized_copy over iterators (0x00dfd570): copy-construct each 0x4e0-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xdfd080); the end iterator is returned.
#include "game/types.h"

struct Elem_dfd570 {
    char mData[0x4e0];
    Elem_dfd570(const Elem_dfd570& o);   // 0x00dfd080
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_dfd570 {
    Elem_dfd570* mpNode;
    Iterator_dfd570(Elem_dfd570* p) : mpNode(p) {}
    Iterator_dfd570(const Iterator_dfd570& x) : mpNode(x.mpNode) {}
    Elem_dfd570& operator*() const { return *mpNode; }
    Iterator_dfd570& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_dfd570& x) const { return mpNode != x.mpNode; }
};

// @ 0x00dfd570
Iterator_dfd570 UninitializedCopy_dfd570(Iterator_dfd570 first, Iterator_dfd570 last, Iterator_dfd570 dest)
{
    Iterator_dfd570 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_dfd570(*first);
    return currentDest;
}
