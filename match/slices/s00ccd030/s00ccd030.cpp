// Scalar deleting destructor (0x00ccd030): run the destructor (0xccc190), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ccd030(void* p);   // 0x00f47380

struct Object_ccd030 {
    ~Object_ccd030();        // 0x00ccc190
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ccd030
void* Object_ccd030::DeletingDtor(unsigned int flags)
{
    this->~Object_ccd030();
    if (flags & 1)
        Free_ccd030(this);
    return this;
}
