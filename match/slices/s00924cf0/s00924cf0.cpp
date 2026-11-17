// Scalar deleting destructor (0x00924cf0): run the destructor (0x924bd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_924cf0(void* p);   // 0x00f47380

struct Object_924cf0 {
    ~Object_924cf0();        // 0x00924bd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00924cf0
void* Object_924cf0::DeletingDtor(unsigned int flags)
{
    this->~Object_924cf0();
    if (flags & 1)
        Free_924cf0(this);
    return this;
}
