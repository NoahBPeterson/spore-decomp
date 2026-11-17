// Scalar deleting destructor (0x00dd4240): run the destructor (0xdd3b60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_dd4240(void* p);   // 0x00f47380

struct Object_dd4240 {
    ~Object_dd4240();        // 0x00dd3b60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00dd4240
void* Object_dd4240::DeletingDtor(unsigned int flags)
{
    this->~Object_dd4240();
    if (flags & 1)
        Free_dd4240(this);
    return this;
}
