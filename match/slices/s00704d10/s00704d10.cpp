// Scalar deleting destructor (0x00704d10): run the destructor (0x7043d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_704d10(void* p);   // 0x00f47380

struct Object_704d10 {
    ~Object_704d10();        // 0x007043d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00704d10
void* Object_704d10::DeletingDtor(unsigned int flags)
{
    this->~Object_704d10();
    if (flags & 1)
        Free_704d10(this);
    return this;
}
