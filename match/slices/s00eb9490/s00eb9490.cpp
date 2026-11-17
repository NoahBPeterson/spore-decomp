// Scalar deleting destructor (0x00eb9490): run the destructor (0xeb92d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_eb9490(void* p);   // 0x00f47380

struct Object_eb9490 {
    ~Object_eb9490();        // 0x00eb92d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00eb9490
void* Object_eb9490::DeletingDtor(unsigned int flags)
{
    this->~Object_eb9490();
    if (flags & 1)
        Free_eb9490(this);
    return this;
}
