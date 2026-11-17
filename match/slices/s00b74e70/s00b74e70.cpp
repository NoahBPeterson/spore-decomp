// Scalar deleting destructor (0x00b74e70): run the destructor (0xb73b30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b74e70(void* p);   // 0x00f47380

struct Object_b74e70 {
    ~Object_b74e70();        // 0x00b73b30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b74e70
void* Object_b74e70::DeletingDtor(unsigned int flags)
{
    this->~Object_b74e70();
    if (flags & 1)
        Free_b74e70(this);
    return this;
}
