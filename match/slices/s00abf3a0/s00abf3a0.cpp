// Scalar deleting destructor (0x00abf3a0): run the destructor (0xabf190), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_abf3a0(void* p);   // 0x00f47380

struct Object_abf3a0 {
    ~Object_abf3a0();        // 0x00abf190
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00abf3a0
void* Object_abf3a0::DeletingDtor(unsigned int flags)
{
    this->~Object_abf3a0();
    if (flags & 1)
        Free_abf3a0(this);
    return this;
}
