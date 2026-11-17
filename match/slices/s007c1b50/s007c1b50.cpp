// Scalar deleting destructor (0x007c1b50): run the destructor (0x7c1330), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7c1b50(void* p);   // 0x00f47380

struct Object_7c1b50 {
    ~Object_7c1b50();        // 0x007c1330
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007c1b50
void* Object_7c1b50::DeletingDtor(unsigned int flags)
{
    this->~Object_7c1b50();
    if (flags & 1)
        Free_7c1b50(this);
    return this;
}
