// Scalar deleting destructor (0x010763a0): run the destructor (0x1075db0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_10763a0(void* p);   // 0x00f47380

struct Object_10763a0 {
    ~Object_10763a0();        // 0x01075db0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x010763a0
void* Object_10763a0::DeletingDtor(unsigned int flags)
{
    this->~Object_10763a0();
    if (flags & 1)
        Free_10763a0(this);
    return this;
}
