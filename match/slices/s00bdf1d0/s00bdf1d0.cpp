// Scalar deleting destructor (0x00bdf1d0): run the destructor (0xbdd780), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bdf1d0(void* p);   // 0x00f47380

struct Object_bdf1d0 {
    ~Object_bdf1d0();        // 0x00bdd780
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bdf1d0
void* Object_bdf1d0::DeletingDtor(unsigned int flags)
{
    this->~Object_bdf1d0();
    if (flags & 1)
        Free_bdf1d0(this);
    return this;
}
