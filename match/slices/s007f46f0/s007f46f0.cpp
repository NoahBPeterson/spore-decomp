// Scalar deleting destructor (0x007f46f0): run the destructor (0x7f3cc0), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7f46f0(void* p);   // 0x00951330

struct Object_7f46f0 {
    ~Object_7f46f0();        // 0x007f3cc0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007f46f0
void* Object_7f46f0::DeletingDtor(unsigned int flags)
{
    this->~Object_7f46f0();
    if (flags & 1)
        Free_7f46f0(this);
    return this;
}
