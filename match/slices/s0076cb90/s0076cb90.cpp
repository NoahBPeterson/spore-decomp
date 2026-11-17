// Scalar deleting destructor (0x0076cb90): run the destructor (0x76c710), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_76cb90(void* p);   // 0x00f47380

struct Object_76cb90 {
    ~Object_76cb90();        // 0x0076c710
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0076cb90
void* Object_76cb90::DeletingDtor(unsigned int flags)
{
    this->~Object_76cb90();
    if (flags & 1)
        Free_76cb90(this);
    return this;
}
