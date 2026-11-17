// Scalar deleting destructor (0x00ba3f70): run the destructor (0xba37a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ba3f70(void* p);   // 0x00f47380

struct Object_ba3f70 {
    ~Object_ba3f70();        // 0x00ba37a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ba3f70
void* Object_ba3f70::DeletingDtor(unsigned int flags)
{
    this->~Object_ba3f70();
    if (flags & 1)
        Free_ba3f70(this);
    return this;
}
