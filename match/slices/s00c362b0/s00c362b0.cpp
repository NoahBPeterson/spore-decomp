// Scalar deleting destructor (0x00c362b0): run the destructor (0xc35f70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c362b0(void* p);   // 0x00f47380

struct Object_c362b0 {
    ~Object_c362b0();        // 0x00c35f70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c362b0
void* Object_c362b0::DeletingDtor(unsigned int flags)
{
    this->~Object_c362b0();
    if (flags & 1)
        Free_c362b0(this);
    return this;
}
