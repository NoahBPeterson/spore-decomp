// Scalar deleting destructor (0x00fc1b80): run the destructor (0xfc1ae0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_fc1b80(void* p);   // 0x00f47380

struct Object_fc1b80 {
    ~Object_fc1b80();        // 0x00fc1ae0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fc1b80
void* Object_fc1b80::DeletingDtor(unsigned int flags)
{
    this->~Object_fc1b80();
    if (flags & 1)
        Free_fc1b80(this);
    return this;
}
