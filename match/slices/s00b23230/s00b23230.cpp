// Scalar deleting destructor (0x00b23230): run the destructor (0xdcd530), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b23230(void* p);   // 0x00f47380

struct Object_b23230 {
    ~Object_b23230();        // 0x00dcd530
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b23230
void* Object_b23230::DeletingDtor(unsigned int flags)
{
    this->~Object_b23230();
    if (flags & 1)
        Free_b23230(this);
    return this;
}
