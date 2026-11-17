// Scalar deleting destructor (0x00e8ff80): run the destructor (0xe8f000), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e8ff80(void* p);   // 0x00f47380

struct Object_e8ff80 {
    ~Object_e8ff80();        // 0x00e8f000
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e8ff80
void* Object_e8ff80::DeletingDtor(unsigned int flags)
{
    this->~Object_e8ff80();
    if (flags & 1)
        Free_e8ff80(this);
    return this;
}
