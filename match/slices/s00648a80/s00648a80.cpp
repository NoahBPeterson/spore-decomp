// Scalar deleting destructor (0x00648a80): run the destructor (0x647f40), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_648a80(void* p);   // 0x00f47380

struct Object_648a80 {
    ~Object_648a80();        // 0x00647f40
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00648a80
void* Object_648a80::DeletingDtor(unsigned int flags)
{
    this->~Object_648a80();
    if (flags & 1)
        Free_648a80(this);
    return this;
}
