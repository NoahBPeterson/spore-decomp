// Scalar deleting destructor (0x00ee90c0): run the destructor (0xee8570), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ee90c0(void* p);   // 0x00f47380

struct Object_ee90c0 {
    ~Object_ee90c0();        // 0x00ee8570
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ee90c0
void* Object_ee90c0::DeletingDtor(unsigned int flags)
{
    this->~Object_ee90c0();
    if (flags & 1)
        Free_ee90c0(this);
    return this;
}
