// Scalar deleting destructor (0x007b91d0): run the destructor (0x7b8be0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b91d0(void* p);   // 0x00f47380

struct Object_7b91d0 {
    ~Object_7b91d0();        // 0x007b8be0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b91d0
void* Object_7b91d0::DeletingDtor(unsigned int flags)
{
    this->~Object_7b91d0();
    if (flags & 1)
        Free_7b91d0(this);
    return this;
}
