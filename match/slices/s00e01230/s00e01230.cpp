// Scalar deleting destructor (0x00e01230): run the destructor (0xe011a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e01230(void* p);   // 0x00f47380

struct Object_e01230 {
    ~Object_e01230();        // 0x00e011a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e01230
void* Object_e01230::DeletingDtor(unsigned int flags)
{
    this->~Object_e01230();
    if (flags & 1)
        Free_e01230(this);
    return this;
}
