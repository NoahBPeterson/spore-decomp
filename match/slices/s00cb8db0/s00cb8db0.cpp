// Scalar deleting destructor (0x00cb8db0): run the destructor (0xcb5bd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_cb8db0(void* p);   // 0x00f47380

struct Object_cb8db0 {
    ~Object_cb8db0();        // 0x00cb5bd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cb8db0
void* Object_cb8db0::DeletingDtor(unsigned int flags)
{
    this->~Object_cb8db0();
    if (flags & 1)
        Free_cb8db0(this);
    return this;
}
