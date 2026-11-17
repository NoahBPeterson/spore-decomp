// Scalar deleting destructor (0x00ab2e80): run the destructor (0xab2950), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ab2e80(void* p);   // 0x00f47380

struct Object_ab2e80 {
    ~Object_ab2e80();        // 0x00ab2950
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ab2e80
void* Object_ab2e80::DeletingDtor(unsigned int flags)
{
    this->~Object_ab2e80();
    if (flags & 1)
        Free_ab2e80(this);
    return this;
}
