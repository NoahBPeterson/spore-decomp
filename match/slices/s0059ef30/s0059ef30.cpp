// uninitialized_copy over iterators (0x0059ef30): copy-construct each 0x18-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0x810020); the end iterator is returned.
#include "game/types.h"

struct Elem_59ef30 {
    char mData[0x18];
    Elem_59ef30(const Elem_59ef30& o);   // 0x00810020
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_59ef30 {
    Elem_59ef30* mpNode;
    Iterator_59ef30(Elem_59ef30* p) : mpNode(p) {}
    Iterator_59ef30(const Iterator_59ef30& x) : mpNode(x.mpNode) {}
    Elem_59ef30& operator*() const { return *mpNode; }
    Iterator_59ef30& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_59ef30& x) const { return mpNode != x.mpNode; }
};

// @ 0x0059ef30
Iterator_59ef30 UninitializedCopy_59ef30(Iterator_59ef30 first, Iterator_59ef30 last, Iterator_59ef30 dest)
{
    Iterator_59ef30 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_59ef30(*first);
    return currentDest;
}
