// uninitialized_copy over iterators (0x00e2aad0): copy-construct each 0x14-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x6b56f0); the end iterator is returned.
#include "game/types.h"

struct Elem_e2aad0 {
    char mData[0x14];
    Elem_e2aad0(const Elem_e2aad0& o);   // 0x006b56f0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_e2aad0 {
    Elem_e2aad0* mpNode;
    Iterator_e2aad0(Elem_e2aad0* p) : mpNode(p) {}
    Iterator_e2aad0(const Iterator_e2aad0& x) : mpNode(x.mpNode) {}
    Elem_e2aad0& operator*() const { return *mpNode; }
    Iterator_e2aad0& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_e2aad0& x) const { return mpNode != x.mpNode; }
};

// @ 0x00e2aad0
Iterator_e2aad0 UninitializedCopy_e2aad0(Iterator_e2aad0 first, Iterator_e2aad0 last, Iterator_e2aad0 dest)
{
    Iterator_e2aad0 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_e2aad0(*first);
    return currentDest;
}
