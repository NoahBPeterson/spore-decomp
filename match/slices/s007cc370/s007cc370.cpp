// Scalar deleting destructor (0x007cc370): run the destructor (0x7cc260), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7cc370(void* p);   // 0x00f47380

struct Object_7cc370 {
    ~Object_7cc370();        // 0x007cc260
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007cc370
void* Object_7cc370::DeletingDtor(unsigned int flags)
{
    this->~Object_7cc370();
    if (flags & 1)
        Free_7cc370(this);
    return this;
}
