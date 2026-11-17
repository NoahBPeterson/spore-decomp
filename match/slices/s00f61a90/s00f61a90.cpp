// Scalar deleting destructor (0x00f61a90): run the destructor (0xf60d80), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f61a90(void* p);   // 0x00f47380

struct Object_f61a90 {
    ~Object_f61a90();        // 0x00f60d80
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f61a90
void* Object_f61a90::DeletingDtor(unsigned int flags)
{
    this->~Object_f61a90();
    if (flags & 1)
        Free_f61a90(this);
    return this;
}
