// Scalar deleting destructor (0x00e0a5a0): run the destructor (0xe0a400), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e0a5a0(void* p);   // 0x00f47380

struct Object_e0a5a0 {
    ~Object_e0a5a0();        // 0x00e0a400
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e0a5a0
void* Object_e0a5a0::DeletingDtor(unsigned int flags)
{
    this->~Object_e0a5a0();
    if (flags & 1)
        Free_e0a5a0(this);
    return this;
}
