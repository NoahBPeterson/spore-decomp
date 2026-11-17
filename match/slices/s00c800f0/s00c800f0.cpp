// Scalar deleting destructor (0x00c800f0): run the destructor (0xc7fdd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c800f0(void* p);   // 0x00f47380

struct Object_c800f0 {
    ~Object_c800f0();        // 0x00c7fdd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c800f0
void* Object_c800f0::DeletingDtor(unsigned int flags)
{
    this->~Object_c800f0();
    if (flags & 1)
        Free_c800f0(this);
    return this;
}
