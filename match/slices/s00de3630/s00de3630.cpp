// Scalar deleting destructor (0x00de3630): run the destructor (0xde35d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_de3630(void* p);   // 0x00f47380

struct Object_de3630 {
    ~Object_de3630();        // 0x00de35d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00de3630
void* Object_de3630::DeletingDtor(unsigned int flags)
{
    this->~Object_de3630();
    if (flags & 1)
        Free_de3630(this);
    return this;
}
