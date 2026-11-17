// Scalar deleting destructor (0x00b27140): run the destructor (0xb26ec0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b27140(void* p);   // 0x00f47380

struct Object_b27140 {
    ~Object_b27140();        // 0x00b26ec0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b27140
void* Object_b27140::DeletingDtor(unsigned int flags)
{
    this->~Object_b27140();
    if (flags & 1)
        Free_b27140(this);
    return this;
}
