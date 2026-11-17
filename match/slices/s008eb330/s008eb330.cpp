// Scalar deleting destructor (0x008eb330): run the destructor (0x8eb2e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_8eb330(void* p);   // 0x00f47380

struct Object_8eb330 {
    ~Object_8eb330();        // 0x008eb2e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x008eb330
void* Object_8eb330::DeletingDtor(unsigned int flags)
{
    this->~Object_8eb330();
    if (flags & 1)
        Free_8eb330(this);
    return this;
}
