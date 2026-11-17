// uninitialized_copy over iterators (0x0104f100): copy-construct each 0x14-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x6606a0); the end iterator is returned.
#include "game/types.h"

struct Elem_104f100 {
    char mData[0x14];
    Elem_104f100(const Elem_104f100& o);   // 0x006606a0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_104f100 {
    Elem_104f100* mpNode;
    Iterator_104f100(Elem_104f100* p) : mpNode(p) {}
    Iterator_104f100(const Iterator_104f100& x) : mpNode(x.mpNode) {}
    Elem_104f100& operator*() const { return *mpNode; }
    Iterator_104f100& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_104f100& x) const { return mpNode != x.mpNode; }
};

// @ 0x0104f100
Iterator_104f100 UninitializedCopy_104f100(Iterator_104f100 first, Iterator_104f100 last, Iterator_104f100 dest)
{
    Iterator_104f100 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_104f100(*first);
    return currentDest;
}
