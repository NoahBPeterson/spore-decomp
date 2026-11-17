// Scalar deleting destructor (0x00a7a560): run the destructor (0x83c750), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a7a560(void* p);   // 0x00f47380

struct Object_a7a560 {
    ~Object_a7a560();        // 0x0083c750
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a7a560
void* Object_a7a560::DeletingDtor(unsigned int flags)
{
    this->~Object_a7a560();
    if (flags & 1)
        Free_a7a560(this);
    return this;
}
