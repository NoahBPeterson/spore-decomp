// Scalar deleting destructor (0x005a51a0): run the destructor (0x5a5100), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5a51a0(void* p);   // 0x00f47380

struct Object_5a51a0 {
    ~Object_5a51a0();        // 0x005a5100
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005a51a0
void* Object_5a51a0::DeletingDtor(unsigned int flags)
{
    this->~Object_5a51a0();
    if (flags & 1)
        Free_5a51a0(this);
    return this;
}
