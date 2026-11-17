// Scalar deleting destructor (0x00ea4ee0): run the destructor (0xea4bd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ea4ee0(void* p);   // 0x00f47380

struct Object_ea4ee0 {
    ~Object_ea4ee0();        // 0x00ea4bd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ea4ee0
void* Object_ea4ee0::DeletingDtor(unsigned int flags)
{
    this->~Object_ea4ee0();
    if (flags & 1)
        Free_ea4ee0(this);
    return this;
}
