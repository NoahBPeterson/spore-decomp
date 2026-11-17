// Scalar deleting destructor (0x00b34fb0): run the destructor (0xe8c030), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b34fb0(void* p);   // 0x00f47380

struct Object_b34fb0 {
    ~Object_b34fb0();        // 0x00e8c030
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b34fb0
void* Object_b34fb0::DeletingDtor(unsigned int flags)
{
    this->~Object_b34fb0();
    if (flags & 1)
        Free_b34fb0(this);
    return this;
}
