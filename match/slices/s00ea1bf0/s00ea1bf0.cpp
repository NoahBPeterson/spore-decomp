// Scalar deleting destructor (0x00ea1bf0): run the destructor (0xea1a30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ea1bf0(void* p);   // 0x00f47380

struct Object_ea1bf0 {
    ~Object_ea1bf0();        // 0x00ea1a30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ea1bf0
void* Object_ea1bf0::DeletingDtor(unsigned int flags)
{
    this->~Object_ea1bf0();
    if (flags & 1)
        Free_ea1bf0(this);
    return this;
}
