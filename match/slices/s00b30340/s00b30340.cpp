// Scalar deleting destructor (0x00b30340): run the destructor (0xb2fc60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b30340(void* p);   // 0x00f47380

struct Object_b30340 {
    ~Object_b30340();        // 0x00b2fc60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b30340
void* Object_b30340::DeletingDtor(unsigned int flags)
{
    this->~Object_b30340();
    if (flags & 1)
        Free_b30340(this);
    return this;
}
