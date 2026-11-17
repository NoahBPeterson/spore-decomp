// Scalar deleting destructor (0x00c73b40): run the destructor (0xc73680), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c73b40(void* p);   // 0x00f47380

struct Object_c73b40 {
    ~Object_c73b40();        // 0x00c73680
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c73b40
void* Object_c73b40::DeletingDtor(unsigned int flags)
{
    this->~Object_c73b40();
    if (flags & 1)
        Free_c73b40(this);
    return this;
}
