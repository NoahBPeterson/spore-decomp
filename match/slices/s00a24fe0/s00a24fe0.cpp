// Scalar deleting destructor (0x00a24fe0): run the destructor (0xa227d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a24fe0(void* p);   // 0x00f47380

struct Object_a24fe0 {
    ~Object_a24fe0();        // 0x00a227d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a24fe0
void* Object_a24fe0::DeletingDtor(unsigned int flags)
{
    this->~Object_a24fe0();
    if (flags & 1)
        Free_a24fe0(this);
    return this;
}
