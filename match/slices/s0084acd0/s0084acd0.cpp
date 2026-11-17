// Scalar deleting destructor (0x0084acd0): run the destructor (0x84abd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_84acd0(void* p);   // 0x00f47380

struct Object_84acd0 {
    ~Object_84acd0();        // 0x0084abd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0084acd0
void* Object_84acd0::DeletingDtor(unsigned int flags)
{
    this->~Object_84acd0();
    if (flags & 1)
        Free_84acd0(this);
    return this;
}
