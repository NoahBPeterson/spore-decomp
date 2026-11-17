// Scalar deleting destructor (0x005a6fa0): run the destructor (0x5a6ee0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5a6fa0(void* p);   // 0x00f47380

struct Object_5a6fa0 {
    ~Object_5a6fa0();        // 0x005a6ee0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005a6fa0
void* Object_5a6fa0::DeletingDtor(unsigned int flags)
{
    this->~Object_5a6fa0();
    if (flags & 1)
        Free_5a6fa0(this);
    return this;
}
