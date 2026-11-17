// Scalar deleting destructor (0x00c410c0): run the destructor (0xc41040), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c410c0(void* p);   // 0x00f47380

struct Object_c410c0 {
    ~Object_c410c0();        // 0x00c41040
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c410c0
void* Object_c410c0::DeletingDtor(unsigned int flags)
{
    this->~Object_c410c0();
    if (flags & 1)
        Free_c410c0(this);
    return this;
}
