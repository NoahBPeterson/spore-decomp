// uninitialized_copy over iterators (0x00fb6690): copy-construct each 0x110-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xfa9840); the end iterator is returned.
#include "game/types.h"

struct Elem_fb6690 {
    char mData[0x110];
    Elem_fb6690(const Elem_fb6690& o);   // 0x00fa9840
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_fb6690 {
    Elem_fb6690* mpNode;
    Iterator_fb6690(Elem_fb6690* p) : mpNode(p) {}
    Iterator_fb6690(const Iterator_fb6690& x) : mpNode(x.mpNode) {}
    Elem_fb6690& operator*() const { return *mpNode; }
    Iterator_fb6690& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_fb6690& x) const { return mpNode != x.mpNode; }
};

// @ 0x00fb6690
Iterator_fb6690 UninitializedCopy_fb6690(Iterator_fb6690 first, Iterator_fb6690 last, Iterator_fb6690 dest)
{
    Iterator_fb6690 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_fb6690(*first);
    return currentDest;
}
