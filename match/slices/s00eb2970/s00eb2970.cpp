// Scalar deleting destructor (0x00eb2970): run the destructor (0xeb2470), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_eb2970(void* p);   // 0x00f47380

struct Object_eb2970 {
    ~Object_eb2970();        // 0x00eb2470
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00eb2970
void* Object_eb2970::DeletingDtor(unsigned int flags)
{
    this->~Object_eb2970();
    if (flags & 1)
        Free_eb2970(this);
    return this;
}
