// Scalar deleting destructor (0x00b20180): run the destructor (0xb20120), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b20180(void* p);   // 0x00f47380

struct Object_b20180 {
    ~Object_b20180();        // 0x00b20120
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b20180
void* Object_b20180::DeletingDtor(unsigned int flags)
{
    this->~Object_b20180();
    if (flags & 1)
        Free_b20180(this);
    return this;
}
