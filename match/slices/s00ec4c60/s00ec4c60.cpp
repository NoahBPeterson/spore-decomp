// Scalar deleting destructor (0x00ec4c60): run the destructor (0xec4980), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ec4c60(void* p);   // 0x00f47380

struct Object_ec4c60 {
    ~Object_ec4c60();        // 0x00ec4980
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ec4c60
void* Object_ec4c60::DeletingDtor(unsigned int flags)
{
    this->~Object_ec4c60();
    if (flags & 1)
        Free_ec4c60(this);
    return this;
}
