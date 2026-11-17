// uninitialized_copy over iterators (0x00dff460): copy-construct each 0x534-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xdff130); the end iterator is returned.
#include "game/types.h"

struct Elem_dff460 {
    char mData[0x534];
    Elem_dff460(const Elem_dff460& o);   // 0x00dff130
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_dff460 {
    Elem_dff460* mpNode;
    Iterator_dff460(Elem_dff460* p) : mpNode(p) {}
    Iterator_dff460(const Iterator_dff460& x) : mpNode(x.mpNode) {}
    Elem_dff460& operator*() const { return *mpNode; }
    Iterator_dff460& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_dff460& x) const { return mpNode != x.mpNode; }
};

// @ 0x00dff460
Iterator_dff460 UninitializedCopy_dff460(Iterator_dff460 first, Iterator_dff460 last, Iterator_dff460 dest)
{
    Iterator_dff460 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_dff460(*first);
    return currentDest;
}
