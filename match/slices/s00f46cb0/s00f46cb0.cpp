// Scalar deleting destructor (0x00f46cb0): run the destructor (0xf46c00), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f46cb0(void* p);   // 0x00f47380

struct Object_f46cb0 {
    ~Object_f46cb0();        // 0x00f46c00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f46cb0
void* Object_f46cb0::DeletingDtor(unsigned int flags)
{
    this->~Object_f46cb0();
    if (flags & 1)
        Free_f46cb0(this);
    return this;
}
