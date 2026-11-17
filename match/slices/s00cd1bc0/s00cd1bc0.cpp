// Scalar deleting destructor (0x00cd1bc0): run the destructor (0xcd18a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_cd1bc0(void* p);   // 0x00f47380

struct Object_cd1bc0 {
    ~Object_cd1bc0();        // 0x00cd18a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cd1bc0
void* Object_cd1bc0::DeletingDtor(unsigned int flags)
{
    this->~Object_cd1bc0();
    if (flags & 1)
        Free_cd1bc0(this);
    return this;
}
