// Scalar deleting destructor (0x007ff7a0): run the destructor (0x7fb000), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7ff7a0(void* p);   // 0x00951330

struct Object_7ff7a0 {
    ~Object_7ff7a0();        // 0x007fb000
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007ff7a0
void* Object_7ff7a0::DeletingDtor(unsigned int flags)
{
    this->~Object_7ff7a0();
    if (flags & 1)
        Free_7ff7a0(this);
    return this;
}
