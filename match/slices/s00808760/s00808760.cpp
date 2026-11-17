// Scalar deleting destructor (0x00808760): run the destructor (0x8077f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_808760(void* p);   // 0x00f47380

struct Object_808760 {
    ~Object_808760();        // 0x008077f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00808760
void* Object_808760::DeletingDtor(unsigned int flags)
{
    this->~Object_808760();
    if (flags & 1)
        Free_808760(this);
    return this;
}
