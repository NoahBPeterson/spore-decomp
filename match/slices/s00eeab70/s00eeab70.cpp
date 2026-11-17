// Scalar deleting destructor (0x00eeab70): run the destructor (0xeea960), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_eeab70(void* p);   // 0x00f47380

struct Object_eeab70 {
    ~Object_eeab70();        // 0x00eea960
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00eeab70
void* Object_eeab70::DeletingDtor(unsigned int flags)
{
    this->~Object_eeab70();
    if (flags & 1)
        Free_eeab70(this);
    return this;
}
