// Scalar deleting destructor (0x00a6b950): run the destructor (0xa6b650), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a6b950(void* p);   // 0x00f47380

struct Object_a6b950 {
    ~Object_a6b950();        // 0x00a6b650
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a6b950
void* Object_a6b950::DeletingDtor(unsigned int flags)
{
    this->~Object_a6b950();
    if (flags & 1)
        Free_a6b950(this);
    return this;
}
