// Scalar deleting destructor (0x00cb8ff0): run the destructor (0xcb8f50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_cb8ff0(void* p);   // 0x00f47380

struct Object_cb8ff0 {
    ~Object_cb8ff0();        // 0x00cb8f50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cb8ff0
void* Object_cb8ff0::DeletingDtor(unsigned int flags)
{
    this->~Object_cb8ff0();
    if (flags & 1)
        Free_cb8ff0(this);
    return this;
}
