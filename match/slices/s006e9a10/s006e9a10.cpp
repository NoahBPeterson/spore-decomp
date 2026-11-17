// Scalar deleting destructor (0x006e9a10): run the destructor (0x6e9990), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6e9a10(void* p);   // 0x00f47380

struct Object_6e9a10 {
    ~Object_6e9a10();        // 0x006e9990
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006e9a10
void* Object_6e9a10::DeletingDtor(unsigned int flags)
{
    this->~Object_6e9a10();
    if (flags & 1)
        Free_6e9a10(this);
    return this;
}
