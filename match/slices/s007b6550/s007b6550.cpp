// Scalar deleting destructor (0x007b6550): run the destructor (0x7b36f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b6550(void* p);   // 0x00f47380

struct Object_7b6550 {
    ~Object_7b6550();        // 0x007b36f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b6550
void* Object_7b6550::DeletingDtor(unsigned int flags)
{
    this->~Object_7b6550();
    if (flags & 1)
        Free_7b6550(this);
    return this;
}
