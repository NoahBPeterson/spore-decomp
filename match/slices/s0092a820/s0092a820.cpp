// Scalar deleting destructor (0x0092a820): run the destructor (0x92a4c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_92a820(void* p);   // 0x00f47380

struct Object_92a820 {
    ~Object_92a820();        // 0x0092a4c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0092a820
void* Object_92a820::DeletingDtor(unsigned int flags)
{
    this->~Object_92a820();
    if (flags & 1)
        Free_92a820(this);
    return this;
}
