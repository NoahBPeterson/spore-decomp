// Scalar deleting destructor (0x00c27880): run the destructor (0xc27120), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c27880(void* p);   // 0x00f47380

struct Object_c27880 {
    ~Object_c27880();        // 0x00c27120
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c27880
void* Object_c27880::DeletingDtor(unsigned int flags)
{
    this->~Object_c27880();
    if (flags & 1)
        Free_c27880(this);
    return this;
}
