// Scalar deleting destructor (0x00f11f70): run the destructor (0xf11c30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f11f70(void* p);   // 0x00f47380

struct Object_f11f70 {
    ~Object_f11f70();        // 0x00f11c30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f11f70
void* Object_f11f70::DeletingDtor(unsigned int flags)
{
    this->~Object_f11f70();
    if (flags & 1)
        Free_f11f70(this);
    return this;
}
