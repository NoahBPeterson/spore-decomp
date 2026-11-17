// Scalar deleting destructor (0x00ae0910): run the destructor (0xae08b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ae0910(void* p);   // 0x00f47380

struct Object_ae0910 {
    ~Object_ae0910();        // 0x00ae08b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ae0910
void* Object_ae0910::DeletingDtor(unsigned int flags)
{
    this->~Object_ae0910();
    if (flags & 1)
        Free_ae0910(this);
    return this;
}
