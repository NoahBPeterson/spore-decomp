// Scalar deleting destructor (0x00e8a4f0): run the destructor (0xe89f20), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e8a4f0(void* p);   // 0x00f47380

struct Object_e8a4f0 {
    ~Object_e8a4f0();        // 0x00e89f20
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e8a4f0
void* Object_e8a4f0::DeletingDtor(unsigned int flags)
{
    this->~Object_e8a4f0();
    if (flags & 1)
        Free_e8a4f0(this);
    return this;
}
