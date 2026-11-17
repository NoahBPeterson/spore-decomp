// Scalar deleting destructor (0x00f53b40): run the destructor (0xf53420), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f53b40(void* p);   // 0x00f47380

struct Object_f53b40 {
    ~Object_f53b40();        // 0x00f53420
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f53b40
void* Object_f53b40::DeletingDtor(unsigned int flags)
{
    this->~Object_f53b40();
    if (flags & 1)
        Free_f53b40(this);
    return this;
}
