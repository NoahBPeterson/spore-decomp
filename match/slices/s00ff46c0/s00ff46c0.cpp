// Scalar deleting destructor (0x00ff46c0): run the destructor (0xff3ff0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ff46c0(void* p);   // 0x00f47380

struct Object_ff46c0 {
    ~Object_ff46c0();        // 0x00ff3ff0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ff46c0
void* Object_ff46c0::DeletingDtor(unsigned int flags)
{
    this->~Object_ff46c0();
    if (flags & 1)
        Free_ff46c0(this);
    return this;
}
