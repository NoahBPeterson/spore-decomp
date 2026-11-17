// Scalar deleting destructor (0x00b1ca80): run the destructor (0xb1c480), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b1ca80(void* p);   // 0x00f47380

struct Object_b1ca80 {
    ~Object_b1ca80();        // 0x00b1c480
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b1ca80
void* Object_b1ca80::DeletingDtor(unsigned int flags)
{
    this->~Object_b1ca80();
    if (flags & 1)
        Free_b1ca80(this);
    return this;
}
