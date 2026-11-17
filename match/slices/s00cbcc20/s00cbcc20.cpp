// Scalar deleting destructor (0x00cbcc20): run the destructor (0xcbb6f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_cbcc20(void* p);   // 0x00f47380

struct Object_cbcc20 {
    ~Object_cbcc20();        // 0x00cbb6f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cbcc20
void* Object_cbcc20::DeletingDtor(unsigned int flags)
{
    this->~Object_cbcc20();
    if (flags & 1)
        Free_cbcc20(this);
    return this;
}
