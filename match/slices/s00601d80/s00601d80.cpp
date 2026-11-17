// Scalar deleting destructor (0x00601d80): run the destructor (0x601930), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_601d80(void* p);   // 0x00f47380

struct Object_601d80 {
    ~Object_601d80();        // 0x00601930
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00601d80
void* Object_601d80::DeletingDtor(unsigned int flags)
{
    this->~Object_601d80();
    if (flags & 1)
        Free_601d80(this);
    return this;
}
