// Scalar deleting destructor (0x00e34520): run the destructor (0xe34290), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e34520(void* p);   // 0x00f47380

struct Object_e34520 {
    ~Object_e34520();        // 0x00e34290
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e34520
void* Object_e34520::DeletingDtor(unsigned int flags)
{
    this->~Object_e34520();
    if (flags & 1)
        Free_e34520(this);
    return this;
}
