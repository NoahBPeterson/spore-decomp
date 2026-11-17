// Scalar deleting destructor (0x009a95e0): run the destructor (0x9e1710), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_9a95e0(void* p);   // 0x00f47380

struct Object_9a95e0 {
    ~Object_9a95e0();        // 0x009e1710
    void* DeletingDtor(unsigned int flags);
};

// @ 0x009a95e0
void* Object_9a95e0::DeletingDtor(unsigned int flags)
{
    this->~Object_9a95e0();
    if (flags & 1)
        Free_9a95e0(this);
    return this;
}
