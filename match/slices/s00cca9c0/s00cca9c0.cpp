// Scalar deleting destructor (0x00cca9c0): run the destructor (0xcc9430), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_cca9c0(void* p);   // 0x00f47380

struct Object_cca9c0 {
    ~Object_cca9c0();        // 0x00cc9430
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cca9c0
void* Object_cca9c0::DeletingDtor(unsigned int flags)
{
    this->~Object_cca9c0();
    if (flags & 1)
        Free_cca9c0(this);
    return this;
}
