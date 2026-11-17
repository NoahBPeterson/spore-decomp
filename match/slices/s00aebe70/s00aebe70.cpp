// Scalar deleting destructor (0x00aebe70): run the destructor (0xaebb30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_aebe70(void* p);   // 0x00f47380

struct Object_aebe70 {
    ~Object_aebe70();        // 0x00aebb30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00aebe70
void* Object_aebe70::DeletingDtor(unsigned int flags)
{
    this->~Object_aebe70();
    if (flags & 1)
        Free_aebe70(this);
    return this;
}
