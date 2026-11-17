// Scalar deleting destructor (0x00affbd0): run the destructor (0x7ced20), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_affbd0(void* p);   // 0x00f47380

struct Object_affbd0 {
    ~Object_affbd0();        // 0x007ced20
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00affbd0
void* Object_affbd0::DeletingDtor(unsigned int flags)
{
    this->~Object_affbd0();
    if (flags & 1)
        Free_affbd0(this);
    return this;
}
