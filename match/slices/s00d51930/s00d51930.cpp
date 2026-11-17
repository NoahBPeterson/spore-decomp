// Scalar deleting destructor (0x00d51930): run the destructor (0xd517d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d51930(void* p);   // 0x00f47380

struct Object_d51930 {
    ~Object_d51930();        // 0x00d517d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d51930
void* Object_d51930::DeletingDtor(unsigned int flags)
{
    this->~Object_d51930();
    if (flags & 1)
        Free_d51930(this);
    return this;
}
