// Scalar deleting destructor (0x005c70b0): run the destructor (0x5c7050), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5c70b0(void* p);   // 0x00f47380

struct Object_5c70b0 {
    ~Object_5c70b0();        // 0x005c7050
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005c70b0
void* Object_5c70b0::DeletingDtor(unsigned int flags)
{
    this->~Object_5c70b0();
    if (flags & 1)
        Free_5c70b0(this);
    return this;
}
