// Scalar deleting destructor (0x00f14100): run the destructor (0xf139f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f14100(void* p);   // 0x00f47380

struct Object_f14100 {
    ~Object_f14100();        // 0x00f139f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f14100
void* Object_f14100::DeletingDtor(unsigned int flags)
{
    this->~Object_f14100();
    if (flags & 1)
        Free_f14100(this);
    return this;
}
