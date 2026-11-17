// Scalar deleting destructor (0x00a15130): run the destructor (0xa14a10), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a15130(void* p);   // 0x00f47380

struct Object_a15130 {
    ~Object_a15130();        // 0x00a14a10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a15130
void* Object_a15130::DeletingDtor(unsigned int flags)
{
    this->~Object_a15130();
    if (flags & 1)
        Free_a15130(this);
    return this;
}
