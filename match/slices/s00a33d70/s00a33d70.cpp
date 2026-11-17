// Scalar deleting destructor (0x00a33d70): run the destructor (0xa32550), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a33d70(void* p);   // 0x00f47380

struct Object_a33d70 {
    ~Object_a33d70();        // 0x00a32550
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a33d70
void* Object_a33d70::DeletingDtor(unsigned int flags)
{
    this->~Object_a33d70();
    if (flags & 1)
        Free_a33d70(this);
    return this;
}
