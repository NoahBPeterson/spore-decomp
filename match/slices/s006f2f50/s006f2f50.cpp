// Scalar deleting destructor (0x006f2f50): run the destructor (0x6f2e80), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6f2f50(void* p);   // 0x00f47380

struct Object_6f2f50 {
    ~Object_6f2f50();        // 0x006f2e80
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006f2f50
void* Object_6f2f50::DeletingDtor(unsigned int flags)
{
    this->~Object_6f2f50();
    if (flags & 1)
        Free_6f2f50(this);
    return this;
}
