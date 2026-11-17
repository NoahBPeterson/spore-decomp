// Scalar deleting destructor (0x00b221f0): run the destructor (0xb22180), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b221f0(void* p);   // 0x00f47380

struct Object_b221f0 {
    ~Object_b221f0();        // 0x00b22180
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b221f0
void* Object_b221f0::DeletingDtor(unsigned int flags)
{
    this->~Object_b221f0();
    if (flags & 1)
        Free_b221f0(this);
    return this;
}
