// Scalar deleting destructor (0x005c0a40): run the destructor (0x5c07d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5c0a40(void* p);   // 0x00f47380

struct Object_5c0a40 {
    ~Object_5c0a40();        // 0x005c07d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005c0a40
void* Object_5c0a40::DeletingDtor(unsigned int flags)
{
    this->~Object_5c0a40();
    if (flags & 1)
        Free_5c0a40(this);
    return this;
}
