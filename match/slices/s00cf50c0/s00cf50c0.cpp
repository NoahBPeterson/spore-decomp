// Scalar deleting destructor (0x00cf50c0): run the destructor (0xcf4ea0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_cf50c0(void* p);   // 0x00f47380

struct Object_cf50c0 {
    ~Object_cf50c0();        // 0x00cf4ea0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cf50c0
void* Object_cf50c0::DeletingDtor(unsigned int flags)
{
    this->~Object_cf50c0();
    if (flags & 1)
        Free_cf50c0(this);
    return this;
}
