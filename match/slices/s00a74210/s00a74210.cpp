// Scalar deleting destructor (0x00a74210): run the destructor (0xa74150), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a74210(void* p);   // 0x00f47380

struct Object_a74210 {
    ~Object_a74210();        // 0x00a74150
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a74210
void* Object_a74210::DeletingDtor(unsigned int flags)
{
    this->~Object_a74210();
    if (flags & 1)
        Free_a74210(this);
    return this;
}
