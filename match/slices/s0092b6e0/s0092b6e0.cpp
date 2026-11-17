// Scalar deleting destructor (0x0092b6e0): run the destructor (0x5d7450), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_92b6e0(void* p);   // 0x00f47380

struct Object_92b6e0 {
    ~Object_92b6e0();        // 0x005d7450
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0092b6e0
void* Object_92b6e0::DeletingDtor(unsigned int flags)
{
    this->~Object_92b6e0();
    if (flags & 1)
        Free_92b6e0(this);
    return this;
}
