// Scalar deleting destructor (0x006b6e30): run the destructor (0x6b6920), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6b6e30(void* p);   // 0x00f47380

struct Object_6b6e30 {
    ~Object_6b6e30();        // 0x006b6920
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006b6e30
void* Object_6b6e30::DeletingDtor(unsigned int flags)
{
    this->~Object_6b6e30();
    if (flags & 1)
        Free_6b6e30(this);
    return this;
}
