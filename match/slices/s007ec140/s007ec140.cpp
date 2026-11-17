// Scalar deleting destructor (0x007ec140): run the destructor (0x7ebe70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7ec140(void* p);   // 0x00f47380

struct Object_7ec140 {
    ~Object_7ec140();        // 0x007ebe70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007ec140
void* Object_7ec140::DeletingDtor(unsigned int flags)
{
    this->~Object_7ec140();
    if (flags & 1)
        Free_7ec140(this);
    return this;
}
