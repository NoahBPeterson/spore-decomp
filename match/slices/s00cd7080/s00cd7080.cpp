// uninitialized_copy over iterators (0x00cd7080): copy-construct each 0x14-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x473460); the end iterator is returned.
#include "game/types.h"

struct Elem_cd7080 {
    char mData[0x14];
    Elem_cd7080(const Elem_cd7080& o);   // 0x00473460
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_cd7080 {
    Elem_cd7080* mpNode;
    Iterator_cd7080(Elem_cd7080* p) : mpNode(p) {}
    Iterator_cd7080(const Iterator_cd7080& x) : mpNode(x.mpNode) {}
    Elem_cd7080& operator*() const { return *mpNode; }
    Iterator_cd7080& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_cd7080& x) const { return mpNode != x.mpNode; }
};

// @ 0x00cd7080
Iterator_cd7080 UninitializedCopy_cd7080(Iterator_cd7080 first, Iterator_cd7080 last, Iterator_cd7080 dest)
{
    Iterator_cd7080 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_cd7080(*first);
    return currentDest;
}
