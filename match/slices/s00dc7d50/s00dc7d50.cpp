// Scalar deleting destructor (0x00dc7d50): run the destructor (0xdc7cc0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_dc7d50(void* p);   // 0x00f47380

struct Object_dc7d50 {
    ~Object_dc7d50();        // 0x00dc7cc0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00dc7d50
void* Object_dc7d50::DeletingDtor(unsigned int flags)
{
    this->~Object_dc7d50();
    if (flags & 1)
        Free_dc7d50(this);
    return this;
}
