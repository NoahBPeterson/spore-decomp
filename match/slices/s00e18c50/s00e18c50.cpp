// Scalar deleting destructor (0x00e18c50): run the destructor (0xe18980), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e18c50(void* p);   // 0x00f47380

struct Object_e18c50 {
    ~Object_e18c50();        // 0x00e18980
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e18c50
void* Object_e18c50::DeletingDtor(unsigned int flags)
{
    this->~Object_e18c50();
    if (flags & 1)
        Free_e18c50(this);
    return this;
}
