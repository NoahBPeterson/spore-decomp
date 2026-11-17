// Scalar deleting destructor (0x007610d0): run the destructor (0x760f50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7610d0(void* p);   // 0x00f47380

struct Object_7610d0 {
    ~Object_7610d0();        // 0x00760f50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007610d0
void* Object_7610d0::DeletingDtor(unsigned int flags)
{
    this->~Object_7610d0();
    if (flags & 1)
        Free_7610d0(this);
    return this;
}
