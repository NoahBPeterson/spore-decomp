// Scalar deleting destructor (0x005c0f20): run the destructor (0x5c0e40), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5c0f20(void* p);   // 0x00f47380

struct Object_5c0f20 {
    ~Object_5c0f20();        // 0x005c0e40
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005c0f20
void* Object_5c0f20::DeletingDtor(unsigned int flags)
{
    this->~Object_5c0f20();
    if (flags & 1)
        Free_5c0f20(this);
    return this;
}
