// Scalar deleting destructor (0x005c9db0): run the destructor (0x5c9d10), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5c9db0(void* p);   // 0x00f47380

struct Object_5c9db0 {
    ~Object_5c9db0();        // 0x005c9d10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005c9db0
void* Object_5c9db0::DeletingDtor(unsigned int flags)
{
    this->~Object_5c9db0();
    if (flags & 1)
        Free_5c9db0(this);
    return this;
}
