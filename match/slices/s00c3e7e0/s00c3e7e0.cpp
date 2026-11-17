// Scalar deleting destructor (0x00c3e7e0): run the destructor (0xc3e700), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c3e7e0(void* p);   // 0x00f47380

struct Object_c3e7e0 {
    ~Object_c3e7e0();        // 0x00c3e700
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c3e7e0
void* Object_c3e7e0::DeletingDtor(unsigned int flags)
{
    this->~Object_c3e7e0();
    if (flags & 1)
        Free_c3e7e0(this);
    return this;
}
