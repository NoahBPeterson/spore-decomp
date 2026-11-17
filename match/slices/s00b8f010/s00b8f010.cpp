// Scalar deleting destructor (0x00b8f010): run the destructor (0xb8e860), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b8f010(void* p);   // 0x00f47380

struct Object_b8f010 {
    ~Object_b8f010();        // 0x00b8e860
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b8f010
void* Object_b8f010::DeletingDtor(unsigned int flags)
{
    this->~Object_b8f010();
    if (flags & 1)
        Free_b8f010(this);
    return this;
}
