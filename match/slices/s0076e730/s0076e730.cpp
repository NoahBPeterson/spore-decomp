// Scalar deleting destructor (0x0076e730): run the destructor (0x76e5c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_76e730(void* p);   // 0x00f47380

struct Object_76e730 {
    ~Object_76e730();        // 0x0076e5c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0076e730
void* Object_76e730::DeletingDtor(unsigned int flags)
{
    this->~Object_76e730();
    if (flags & 1)
        Free_76e730(this);
    return this;
}
