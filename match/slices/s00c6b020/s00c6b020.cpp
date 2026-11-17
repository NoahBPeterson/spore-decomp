// Scalar deleting destructor (0x00c6b020): run the destructor (0xc6a430), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c6b020(void* p);   // 0x00f47380

struct Object_c6b020 {
    ~Object_c6b020();        // 0x00c6a430
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c6b020
void* Object_c6b020::DeletingDtor(unsigned int flags)
{
    this->~Object_c6b020();
    if (flags & 1)
        Free_c6b020(this);
    return this;
}
