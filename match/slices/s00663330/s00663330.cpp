// Scalar deleting destructor (0x00663330): run the destructor (0x6630e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_663330(void* p);   // 0x00f47380

struct Object_663330 {
    ~Object_663330();        // 0x006630e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00663330
void* Object_663330::DeletingDtor(unsigned int flags)
{
    this->~Object_663330();
    if (flags & 1)
        Free_663330(this);
    return this;
}
