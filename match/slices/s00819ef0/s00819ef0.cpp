// Scalar deleting destructor (0x00819ef0): run the destructor (0x819880), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_819ef0(void* p);   // 0x00f47380

struct Object_819ef0 {
    ~Object_819ef0();        // 0x00819880
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00819ef0
void* Object_819ef0::DeletingDtor(unsigned int flags)
{
    this->~Object_819ef0();
    if (flags & 1)
        Free_819ef0(this);
    return this;
}
