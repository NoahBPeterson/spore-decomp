// Scalar deleting destructor (0x00c2fe80): run the destructor (0xc2f520), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c2fe80(void* p);   // 0x00f47380

struct Object_c2fe80 {
    ~Object_c2fe80();        // 0x00c2f520
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c2fe80
void* Object_c2fe80::DeletingDtor(unsigned int flags)
{
    this->~Object_c2fe80();
    if (flags & 1)
        Free_c2fe80(this);
    return this;
}
