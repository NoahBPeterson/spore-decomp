// Scalar deleting destructor (0x00cb8740): run the destructor (0xcb86a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_cb8740(void* p);   // 0x00f47380

struct Object_cb8740 {
    ~Object_cb8740();        // 0x00cb86a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cb8740
void* Object_cb8740::DeletingDtor(unsigned int flags)
{
    this->~Object_cb8740();
    if (flags & 1)
        Free_cb8740(this);
    return this;
}
