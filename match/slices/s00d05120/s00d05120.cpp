// Scalar deleting destructor (0x00d05120): run the destructor (0xd04d10), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d05120(void* p);   // 0x00f47380

struct Object_d05120 {
    ~Object_d05120();        // 0x00d04d10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d05120
void* Object_d05120::DeletingDtor(unsigned int flags)
{
    this->~Object_d05120();
    if (flags & 1)
        Free_d05120(this);
    return this;
}
