// Scalar deleting destructor (0x006a3d30): run the destructor (0x6a3bd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6a3d30(void* p);   // 0x00f47380

struct Object_6a3d30 {
    ~Object_6a3d30();        // 0x006a3bd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006a3d30
void* Object_6a3d30::DeletingDtor(unsigned int flags)
{
    this->~Object_6a3d30();
    if (flags & 1)
        Free_6a3d30(this);
    return this;
}
