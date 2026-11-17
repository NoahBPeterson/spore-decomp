// Scalar deleting destructor (0x00946fc0): run the destructor (0x946f70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_946fc0(void* p);   // 0x00f47380

struct Object_946fc0 {
    ~Object_946fc0();        // 0x00946f70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00946fc0
void* Object_946fc0::DeletingDtor(unsigned int flags)
{
    this->~Object_946fc0();
    if (flags & 1)
        Free_946fc0(this);
    return this;
}
