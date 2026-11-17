// Scalar deleting destructor (0x00900050): run the destructor (0x8fff80), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_900050(void* p);   // 0x00f47380

struct Object_900050 {
    ~Object_900050();        // 0x008fff80
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00900050
void* Object_900050::DeletingDtor(unsigned int flags)
{
    this->~Object_900050();
    if (flags & 1)
        Free_900050(this);
    return this;
}
