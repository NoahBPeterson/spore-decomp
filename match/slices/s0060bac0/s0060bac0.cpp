// Scalar deleting destructor (0x0060bac0): run the destructor (0x60b9e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_60bac0(void* p);   // 0x00f47380

struct Object_60bac0 {
    ~Object_60bac0();        // 0x0060b9e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0060bac0
void* Object_60bac0::DeletingDtor(unsigned int flags)
{
    this->~Object_60bac0();
    if (flags & 1)
        Free_60bac0(this);
    return this;
}
