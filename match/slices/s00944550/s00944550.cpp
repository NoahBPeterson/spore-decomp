// Scalar deleting destructor (0x00944550): run the destructor (0x943ea0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_944550(void* p);   // 0x00f47380

struct Object_944550 {
    ~Object_944550();        // 0x00943ea0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00944550
void* Object_944550::DeletingDtor(unsigned int flags)
{
    this->~Object_944550();
    if (flags & 1)
        Free_944550(this);
    return this;
}
