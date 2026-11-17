// Scalar deleting destructor (0x005cb480): run the destructor (0x5cb420), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5cb480(void* p);   // 0x00f47380

struct Object_5cb480 {
    ~Object_5cb480();        // 0x005cb420
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005cb480
void* Object_5cb480::DeletingDtor(unsigned int flags)
{
    this->~Object_5cb480();
    if (flags & 1)
        Free_5cb480(this);
    return this;
}
