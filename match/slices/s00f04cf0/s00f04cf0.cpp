// Scalar deleting destructor (0x00f04cf0): run the destructor (0xf04910), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f04cf0(void* p);   // 0x00f47380

struct Object_f04cf0 {
    ~Object_f04cf0();        // 0x00f04910
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f04cf0
void* Object_f04cf0::DeletingDtor(unsigned int flags)
{
    this->~Object_f04cf0();
    if (flags & 1)
        Free_f04cf0(this);
    return this;
}
