// Scalar deleting destructor (0x00ca95a0): run the destructor (0xca7ef0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ca95a0(void* p);   // 0x00f47380

struct Object_ca95a0 {
    ~Object_ca95a0();        // 0x00ca7ef0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ca95a0
void* Object_ca95a0::DeletingDtor(unsigned int flags)
{
    this->~Object_ca95a0();
    if (flags & 1)
        Free_ca95a0(this);
    return this;
}
