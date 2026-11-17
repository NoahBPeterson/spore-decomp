// Scalar deleting destructor (0x00656b60): run the destructor (0x656410), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_656b60(void* p);   // 0x00f47380

struct Object_656b60 {
    ~Object_656b60();        // 0x00656410
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00656b60
void* Object_656b60::DeletingDtor(unsigned int flags)
{
    this->~Object_656b60();
    if (flags & 1)
        Free_656b60(this);
    return this;
}
