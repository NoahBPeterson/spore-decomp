// Scalar deleting destructor (0x00c7ace0): run the destructor (0xc79b60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c7ace0(void* p);   // 0x00f47380

struct Object_c7ace0 {
    ~Object_c7ace0();        // 0x00c79b60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c7ace0
void* Object_c7ace0::DeletingDtor(unsigned int flags)
{
    this->~Object_c7ace0();
    if (flags & 1)
        Free_c7ace0(this);
    return this;
}
