// Scalar deleting destructor (0x00a14660): run the destructor (0xa14380), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a14660(void* p);   // 0x00f47380

struct Object_a14660 {
    ~Object_a14660();        // 0x00a14380
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a14660
void* Object_a14660::DeletingDtor(unsigned int flags)
{
    this->~Object_a14660();
    if (flags & 1)
        Free_a14660(this);
    return this;
}
