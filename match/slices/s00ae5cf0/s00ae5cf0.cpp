// Scalar deleting destructor (0x00ae5cf0): run the destructor (0xae5740), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ae5cf0(void* p);   // 0x00f47380

struct Object_ae5cf0 {
    ~Object_ae5cf0();        // 0x00ae5740
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ae5cf0
void* Object_ae5cf0::DeletingDtor(unsigned int flags)
{
    this->~Object_ae5cf0();
    if (flags & 1)
        Free_ae5cf0(this);
    return this;
}
