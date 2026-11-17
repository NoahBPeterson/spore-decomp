// Scalar deleting destructor (0x00b5e000): run the destructor (0xb5d7c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b5e000(void* p);   // 0x00f47380

struct Object_b5e000 {
    ~Object_b5e000();        // 0x00b5d7c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b5e000
void* Object_b5e000::DeletingDtor(unsigned int flags)
{
    this->~Object_b5e000();
    if (flags & 1)
        Free_b5e000(this);
    return this;
}
