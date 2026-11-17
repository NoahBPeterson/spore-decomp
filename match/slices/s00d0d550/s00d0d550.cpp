// Scalar deleting destructor (0x00d0d550): run the destructor (0xd0cca0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d0d550(void* p);   // 0x00f47380

struct Object_d0d550 {
    ~Object_d0d550();        // 0x00d0cca0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d0d550
void* Object_d0d550::DeletingDtor(unsigned int flags)
{
    this->~Object_d0d550();
    if (flags & 1)
        Free_d0d550(this);
    return this;
}
