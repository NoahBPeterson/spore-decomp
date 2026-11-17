// Scalar deleting destructor (0x008e29c0): run the destructor (0x8e4bd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_8e29c0(void* p);   // 0x00f47380

struct Object_8e29c0 {
    ~Object_8e29c0();        // 0x008e4bd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x008e29c0
void* Object_8e29c0::DeletingDtor(unsigned int flags)
{
    this->~Object_8e29c0();
    if (flags & 1)
        Free_8e29c0(this);
    return this;
}
