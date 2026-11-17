// Scalar deleting destructor (0x00835380): run the destructor (0x835320), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_835380(void* p);   // 0x00f47380

struct Object_835380 {
    ~Object_835380();        // 0x00835320
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00835380
void* Object_835380::DeletingDtor(unsigned int flags)
{
    this->~Object_835380();
    if (flags & 1)
        Free_835380(this);
    return this;
}
