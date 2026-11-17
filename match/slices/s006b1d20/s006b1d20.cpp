// Scalar deleting destructor (0x006b1d20): run the destructor (0x6b1ab0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6b1d20(void* p);   // 0x00f47380

struct Object_6b1d20 {
    ~Object_6b1d20();        // 0x006b1ab0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006b1d20
void* Object_6b1d20::DeletingDtor(unsigned int flags)
{
    this->~Object_6b1d20();
    if (flags & 1)
        Free_6b1d20(this);
    return this;
}
