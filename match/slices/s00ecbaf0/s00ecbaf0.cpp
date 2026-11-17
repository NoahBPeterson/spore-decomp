// Scalar deleting destructor (0x00ecbaf0): run the destructor (0xecb8c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ecbaf0(void* p);   // 0x00f47380

struct Object_ecbaf0 {
    ~Object_ecbaf0();        // 0x00ecb8c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ecbaf0
void* Object_ecbaf0::DeletingDtor(unsigned int flags)
{
    this->~Object_ecbaf0();
    if (flags & 1)
        Free_ecbaf0(this);
    return this;
}
