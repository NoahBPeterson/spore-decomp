// Scalar deleting destructor (0x00a9a1a0): run the destructor (0xa99870), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a9a1a0(void* p);   // 0x00f47380

struct Object_a9a1a0 {
    ~Object_a9a1a0();        // 0x00a99870
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a9a1a0
void* Object_a9a1a0::DeletingDtor(unsigned int flags)
{
    this->~Object_a9a1a0();
    if (flags & 1)
        Free_a9a1a0(this);
    return this;
}
