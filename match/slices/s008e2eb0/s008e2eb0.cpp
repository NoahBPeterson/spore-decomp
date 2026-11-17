// Scalar deleting destructor (0x008e2eb0): run the destructor (0x8e2b90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_8e2eb0(void* p);   // 0x00f47380

struct Object_8e2eb0 {
    ~Object_8e2eb0();        // 0x008e2b90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x008e2eb0
void* Object_8e2eb0::DeletingDtor(unsigned int flags)
{
    this->~Object_8e2eb0();
    if (flags & 1)
        Free_8e2eb0(this);
    return this;
}
