// Scalar deleting destructor (0x00a41980): run the destructor (0xa41710), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a41980(void* p);   // 0x00f47380

struct Object_a41980 {
    ~Object_a41980();        // 0x00a41710
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a41980
void* Object_a41980::DeletingDtor(unsigned int flags)
{
    this->~Object_a41980();
    if (flags & 1)
        Free_a41980(this);
    return this;
}
