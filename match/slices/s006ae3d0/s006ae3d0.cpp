// Scalar deleting destructor (0x006ae3d0): run the destructor (0x6ae190), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6ae3d0(void* p);   // 0x00926060

struct Object_6ae3d0 {
    ~Object_6ae3d0();        // 0x006ae190
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006ae3d0
void* Object_6ae3d0::DeletingDtor(unsigned int flags)
{
    this->~Object_6ae3d0();
    if (flags & 1)
        Free_6ae3d0(this);
    return this;
}
