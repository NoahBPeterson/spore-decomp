// Scalar deleting destructor (0x00601a30): run the destructor (0x600df0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_601a30(void* p);   // 0x00f47380

struct Object_601a30 {
    ~Object_601a30();        // 0x00600df0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00601a30
void* Object_601a30::DeletingDtor(unsigned int flags)
{
    this->~Object_601a30();
    if (flags & 1)
        Free_601a30(this);
    return this;
}
