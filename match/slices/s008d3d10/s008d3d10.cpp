// Scalar deleting destructor (0x008d3d10): run the destructor (0x8d3ca0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_8d3d10(void* p);   // 0x00f47380

struct Object_8d3d10 {
    ~Object_8d3d10();        // 0x008d3ca0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x008d3d10
void* Object_8d3d10::DeletingDtor(unsigned int flags)
{
    this->~Object_8d3d10();
    if (flags & 1)
        Free_8d3d10(this);
    return this;
}
