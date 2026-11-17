// Scalar deleting destructor (0x00ae8fe0): run the destructor (0xae7f90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ae8fe0(void* p);   // 0x00f47380

struct Object_ae8fe0 {
    ~Object_ae8fe0();        // 0x00ae7f90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ae8fe0
void* Object_ae8fe0::DeletingDtor(unsigned int flags)
{
    this->~Object_ae8fe0();
    if (flags & 1)
        Free_ae8fe0(this);
    return this;
}
