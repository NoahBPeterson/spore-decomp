// Scalar deleting destructor (0x009370b0): run the destructor (0x936ce0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_9370b0(void* p);   // 0x00f47380

struct Object_9370b0 {
    ~Object_9370b0();        // 0x00936ce0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x009370b0
void* Object_9370b0::DeletingDtor(unsigned int flags)
{
    this->~Object_9370b0();
    if (flags & 1)
        Free_9370b0(this);
    return this;
}
