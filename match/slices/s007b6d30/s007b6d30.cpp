// Scalar deleting destructor (0x007b6d30): run the destructor (0x7b5090), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b6d30(void* p);   // 0x00f47380

struct Object_7b6d30 {
    ~Object_7b6d30();        // 0x007b5090
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b6d30
void* Object_7b6d30::DeletingDtor(unsigned int flags)
{
    this->~Object_7b6d30();
    if (flags & 1)
        Free_7b6d30(this);
    return this;
}
