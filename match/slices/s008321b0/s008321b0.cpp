// Scalar deleting destructor (0x008321b0): run the destructor (0x832160), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_8321b0(void* p);   // 0x00f47380

struct Object_8321b0 {
    ~Object_8321b0();        // 0x00832160
    void* DeletingDtor(unsigned int flags);
};

// @ 0x008321b0
void* Object_8321b0::DeletingDtor(unsigned int flags)
{
    this->~Object_8321b0();
    if (flags & 1)
        Free_8321b0(this);
    return this;
}
