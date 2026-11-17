// Scalar deleting destructor (0x0103bed0): run the destructor (0x103b7c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_103bed0(void* p);   // 0x00f47380

struct Object_103bed0 {
    ~Object_103bed0();        // 0x0103b7c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0103bed0
void* Object_103bed0::DeletingDtor(unsigned int flags)
{
    this->~Object_103bed0();
    if (flags & 1)
        Free_103bed0(this);
    return this;
}
