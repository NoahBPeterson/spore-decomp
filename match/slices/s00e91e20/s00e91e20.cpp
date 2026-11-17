// Scalar deleting destructor (0x00e91e20): run the destructor (0xe91c30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e91e20(void* p);   // 0x00f47380

struct Object_e91e20 {
    ~Object_e91e20();        // 0x00e91c30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e91e20
void* Object_e91e20::DeletingDtor(unsigned int flags)
{
    this->~Object_e91e20();
    if (flags & 1)
        Free_e91e20(this);
    return this;
}
