// Scalar deleting destructor (0x00e8d4d0): run the destructor (0xe8d160), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e8d4d0(void* p);   // 0x00f47380

struct Object_e8d4d0 {
    ~Object_e8d4d0();        // 0x00e8d160
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e8d4d0
void* Object_e8d4d0::DeletingDtor(unsigned int flags)
{
    this->~Object_e8d4d0();
    if (flags & 1)
        Free_e8d4d0(this);
    return this;
}
