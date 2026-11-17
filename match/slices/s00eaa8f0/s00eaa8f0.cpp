// Scalar deleting destructor (0x00eaa8f0): run the destructor (0xeaa850), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_eaa8f0(void* p);   // 0x00f47380

struct Object_eaa8f0 {
    ~Object_eaa8f0();        // 0x00eaa850
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00eaa8f0
void* Object_eaa8f0::DeletingDtor(unsigned int flags)
{
    this->~Object_eaa8f0();
    if (flags & 1)
        Free_eaa8f0(this);
    return this;
}
