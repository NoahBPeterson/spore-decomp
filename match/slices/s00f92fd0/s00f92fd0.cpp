// Scalar deleting destructor (0x00f92fd0): run the destructor (0xf92b10), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f92fd0(void* p);   // 0x00f47380

struct Object_f92fd0 {
    ~Object_f92fd0();        // 0x00f92b10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f92fd0
void* Object_f92fd0::DeletingDtor(unsigned int flags)
{
    this->~Object_f92fd0();
    if (flags & 1)
        Free_f92fd0(this);
    return this;
}
