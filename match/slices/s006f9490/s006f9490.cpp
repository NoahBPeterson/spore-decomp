// Scalar deleting destructor (0x006f9490): run the destructor (0x6f8f60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6f9490(void* p);   // 0x00f47380

struct Object_6f9490 {
    ~Object_6f9490();        // 0x006f8f60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006f9490
void* Object_6f9490::DeletingDtor(unsigned int flags)
{
    this->~Object_6f9490();
    if (flags & 1)
        Free_6f9490(this);
    return this;
}
