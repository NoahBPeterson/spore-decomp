// Scalar deleting destructor (0x00ea3cf0): run the destructor (0xea3ab0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ea3cf0(void* p);   // 0x00f47380

struct Object_ea3cf0 {
    ~Object_ea3cf0();        // 0x00ea3ab0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ea3cf0
void* Object_ea3cf0::DeletingDtor(unsigned int flags)
{
    this->~Object_ea3cf0();
    if (flags & 1)
        Free_ea3cf0(this);
    return this;
}
