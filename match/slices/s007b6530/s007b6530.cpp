// Scalar deleting destructor (0x007b6530): run the destructor (0x7b3530), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b6530(void* p);   // 0x00f47380

struct Object_7b6530 {
    ~Object_7b6530();        // 0x007b3530
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b6530
void* Object_7b6530::DeletingDtor(unsigned int flags)
{
    this->~Object_7b6530();
    if (flags & 1)
        Free_7b6530(this);
    return this;
}
