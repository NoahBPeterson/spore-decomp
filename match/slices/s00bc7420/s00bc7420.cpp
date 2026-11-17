// Scalar deleting destructor (0x00bc7420): run the destructor (0xbc7080), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bc7420(void* p);   // 0x00f47380

struct Object_bc7420 {
    ~Object_bc7420();        // 0x00bc7080
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bc7420
void* Object_bc7420::DeletingDtor(unsigned int flags)
{
    this->~Object_bc7420();
    if (flags & 1)
        Free_bc7420(this);
    return this;
}
