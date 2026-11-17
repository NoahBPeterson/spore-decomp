// Scalar deleting destructor (0x0060b530): run the destructor (0x60b470), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_60b530(void* p);   // 0x00f47380

struct Object_60b530 {
    ~Object_60b530();        // 0x0060b470
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0060b530
void* Object_60b530::DeletingDtor(unsigned int flags)
{
    this->~Object_60b530();
    if (flags & 1)
        Free_60b530(this);
    return this;
}
