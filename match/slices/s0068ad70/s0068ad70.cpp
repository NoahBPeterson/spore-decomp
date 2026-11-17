// Scalar deleting destructor (0x0068ad70): run the destructor (0x68a720), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_68ad70(void* p);   // 0x00f47380

struct Object_68ad70 {
    ~Object_68ad70();        // 0x0068a720
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0068ad70
void* Object_68ad70::DeletingDtor(unsigned int flags)
{
    this->~Object_68ad70();
    if (flags & 1)
        Free_68ad70(this);
    return this;
}
