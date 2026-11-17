// Scalar deleting destructor (0x00b34fd0): run the destructor (0xe92660), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b34fd0(void* p);   // 0x00f47380

struct Object_b34fd0 {
    ~Object_b34fd0();        // 0x00e92660
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b34fd0
void* Object_b34fd0::DeletingDtor(unsigned int flags)
{
    this->~Object_b34fd0();
    if (flags & 1)
        Free_b34fd0(this);
    return this;
}
