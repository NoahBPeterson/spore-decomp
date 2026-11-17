// Scalar deleting destructor (0x00c4e180): run the destructor (0xc47680), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c4e180(void* p);   // 0x00f47380

struct Object_c4e180 {
    ~Object_c4e180();        // 0x00c47680
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c4e180
void* Object_c4e180::DeletingDtor(unsigned int flags)
{
    this->~Object_c4e180();
    if (flags & 1)
        Free_c4e180(this);
    return this;
}
