// Scalar deleting destructor (0x007b6140): run the destructor (0x7b2c30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b6140(void* p);   // 0x00f47380

struct Object_7b6140 {
    ~Object_7b6140();        // 0x007b2c30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b6140
void* Object_7b6140::DeletingDtor(unsigned int flags)
{
    this->~Object_7b6140();
    if (flags & 1)
        Free_7b6140(this);
    return this;
}
