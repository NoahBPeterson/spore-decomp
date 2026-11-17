// Scalar deleting destructor (0x007d7eb0): run the destructor (0x7d7d00), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7d7eb0(void* p);   // 0x00f47380

struct Object_7d7eb0 {
    ~Object_7d7eb0();        // 0x007d7d00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007d7eb0
void* Object_7d7eb0::DeletingDtor(unsigned int flags)
{
    this->~Object_7d7eb0();
    if (flags & 1)
        Free_7d7eb0(this);
    return this;
}
