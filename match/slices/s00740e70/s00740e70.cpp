// Scalar deleting destructor (0x00740e70): run the destructor (0x740160), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_740e70(void* p);   // 0x00f47380

struct Object_740e70 {
    ~Object_740e70();        // 0x00740160
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00740e70
void* Object_740e70::DeletingDtor(unsigned int flags)
{
    this->~Object_740e70();
    if (flags & 1)
        Free_740e70(this);
    return this;
}
