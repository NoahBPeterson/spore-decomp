// Scalar deleting destructor (0x00d295f0): run the destructor (0xd29570), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d295f0(void* p);   // 0x00f47380

struct Object_d295f0 {
    ~Object_d295f0();        // 0x00d29570
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d295f0
void* Object_d295f0::DeletingDtor(unsigned int flags)
{
    this->~Object_d295f0();
    if (flags & 1)
        Free_d295f0(this);
    return this;
}
