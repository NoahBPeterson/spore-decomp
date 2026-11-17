// Scalar deleting destructor (0x005e6a40): run the destructor (0x5e6980), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5e6a40(void* p);   // 0x00f47380

struct Object_5e6a40 {
    ~Object_5e6a40();        // 0x005e6980
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005e6a40
void* Object_5e6a40::DeletingDtor(unsigned int flags)
{
    this->~Object_5e6a40();
    if (flags & 1)
        Free_5e6a40(this);
    return this;
}
