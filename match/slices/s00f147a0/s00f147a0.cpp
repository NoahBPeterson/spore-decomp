// uninitialized_copy over iterators (0x00f147a0): copy-construct each 0x70-byte element of [first, last) into raw
// storage starting at dest (copy constructor 0xf14690); the end iterator is returned.
#include "game/types.h"

struct Elem_f147a0 {
    char mData[0x70];
    Elem_f147a0(const Elem_f147a0& o);   // 0x00f14690
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Iterator_f147a0 {
    Elem_f147a0* mpNode;
    Iterator_f147a0(Elem_f147a0* p) : mpNode(p) {}
    Iterator_f147a0(const Iterator_f147a0& x) : mpNode(x.mpNode) {}
    Elem_f147a0& operator*() const { return *mpNode; }
    Iterator_f147a0& operator++() { ++mpNode; return *this; }
    bool operator!=(const Iterator_f147a0& x) const { return mpNode != x.mpNode; }
};

// @ 0x00f147a0
Iterator_f147a0 UninitializedCopy_f147a0(Iterator_f147a0 first, Iterator_f147a0 last, Iterator_f147a0 dest)
{
    Iterator_f147a0 currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        new (&*currentDest) Elem_f147a0(*first);
    return currentDest;
}
