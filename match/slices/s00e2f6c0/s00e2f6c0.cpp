// Scalar deleting destructor (0x00e2f6c0): run the destructor (0xe2f160), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e2f6c0(void* p);   // 0x00f47380

struct Object_e2f6c0 {
    ~Object_e2f6c0();        // 0x00e2f160
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e2f6c0
void* Object_e2f6c0::DeletingDtor(unsigned int flags)
{
    this->~Object_e2f6c0();
    if (flags & 1)
        Free_e2f6c0(this);
    return this;
}
