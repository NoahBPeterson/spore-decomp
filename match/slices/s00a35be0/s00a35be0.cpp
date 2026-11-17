// Scalar deleting destructor (0x00a35be0): run the destructor (0xa35720), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a35be0(void* p);   // 0x00f47380

struct Object_a35be0 {
    ~Object_a35be0();        // 0x00a35720
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a35be0
void* Object_a35be0::DeletingDtor(unsigned int flags)
{
    this->~Object_a35be0();
    if (flags & 1)
        Free_a35be0(this);
    return this;
}
