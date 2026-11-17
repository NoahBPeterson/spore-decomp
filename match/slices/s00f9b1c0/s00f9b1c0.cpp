// Scalar deleting destructor (0x00f9b1c0): run the destructor (0xf9b170), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f9b1c0(void* p);   // 0x00f47380

struct Object_f9b1c0 {
    ~Object_f9b1c0();        // 0x00f9b170
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f9b1c0
void* Object_f9b1c0::DeletingDtor(unsigned int flags)
{
    this->~Object_f9b1c0();
    if (flags & 1)
        Free_f9b1c0(this);
    return this;
}
