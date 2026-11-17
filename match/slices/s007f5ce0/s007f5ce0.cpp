// Scalar deleting destructor (0x007f5ce0): run the destructor (0x7f58e0), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7f5ce0(void* p);   // 0x00951330

struct Object_7f5ce0 {
    ~Object_7f5ce0();        // 0x007f58e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007f5ce0
void* Object_7f5ce0::DeletingDtor(unsigned int flags)
{
    this->~Object_7f5ce0();
    if (flags & 1)
        Free_7f5ce0(this);
    return this;
}
