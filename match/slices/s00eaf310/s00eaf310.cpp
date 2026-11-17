// uninitialized_copy over iterators (0x00eaf310): copy-construct each 0x6c-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xeaf190); the end iterator is returned.
#include "game/types.h"

struct Elem_eaf310 {
    char mData[0x6c];
    Elem_eaf310(const Elem_eaf310& o);   // 0x00eaf190
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_eaf310 {
    Elem_eaf310* mpNode;
    Iterator_eaf310(Elem_eaf310* p) : mpNode(p) {}
    Iterator_eaf310(const Iterator_eaf310& x) : mpNode(x.mpNode) {}
    Elem_eaf310& operator*() const { return *mpNode; }
    Iterator_eaf310& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_eaf310& x) const { return mpNode != x.mpNode; }
};

// @ 0x00eaf310
Iterator_eaf310 UninitializedCopy_eaf310(Iterator_eaf310 first, Iterator_eaf310 last, Iterator_eaf310 dest)
{
    Iterator_eaf310 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_eaf310(*first);
    return currentDest;
}
