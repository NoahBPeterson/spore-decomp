// Scalar deleting destructor (0x00bcffc0): run the destructor (0xbce0a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bcffc0(void* p);   // 0x00f47380

struct Object_bcffc0 {
    ~Object_bcffc0();        // 0x00bce0a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bcffc0
void* Object_bcffc0::DeletingDtor(unsigned int flags)
{
    this->~Object_bcffc0();
    if (flags & 1)
        Free_bcffc0(this);
    return this;
}
