// Scalar deleting destructor (0x009838e0): run the destructor (0x982710), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_9838e0(void* p);   // 0x00951330

struct Object_9838e0 {
    ~Object_9838e0();        // 0x00982710
    void* DeletingDtor(unsigned int flags);
};

// @ 0x009838e0
void* Object_9838e0::DeletingDtor(unsigned int flags)
{
    this->~Object_9838e0();
    if (flags & 1)
        Free_9838e0(this);
    return this;
}
