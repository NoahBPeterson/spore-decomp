// Scalar deleting destructor (0x00623bc0): run the destructor (0x623af0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_623bc0(void* p);   // 0x00f47380

struct Object_623bc0 {
    ~Object_623bc0();        // 0x00623af0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00623bc0
void* Object_623bc0::DeletingDtor(unsigned int flags)
{
    this->~Object_623bc0();
    if (flags & 1)
        Free_623bc0(this);
    return this;
}
