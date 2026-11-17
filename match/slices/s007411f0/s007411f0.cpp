// Scalar deleting destructor (0x007411f0): run the destructor (0x741040), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7411f0(void* p);   // 0x00f47380

struct Object_7411f0 {
    ~Object_7411f0();        // 0x00741040
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007411f0
void* Object_7411f0::DeletingDtor(unsigned int flags)
{
    this->~Object_7411f0();
    if (flags & 1)
        Free_7411f0(this);
    return this;
}
