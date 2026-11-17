// Scalar deleting destructor (0x00f38d70): run the destructor (0xf38ce0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f38d70(void* p);   // 0x00f47380

struct Object_f38d70 {
    ~Object_f38d70();        // 0x00f38ce0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f38d70
void* Object_f38d70::DeletingDtor(unsigned int flags)
{
    this->~Object_f38d70();
    if (flags & 1)
        Free_f38d70(this);
    return this;
}
