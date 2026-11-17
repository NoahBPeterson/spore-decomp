// Scalar deleting destructor (0x00776900): run the destructor (0x776590), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_776900(void* p);   // 0x00f47380

struct Object_776900 {
    ~Object_776900();        // 0x00776590
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00776900
void* Object_776900::DeletingDtor(unsigned int flags)
{
    this->~Object_776900();
    if (flags & 1)
        Free_776900(this);
    return this;
}
