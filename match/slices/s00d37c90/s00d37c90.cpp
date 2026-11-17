// Scalar deleting destructor (0x00d37c90): run the destructor (0xd37b60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d37c90(void* p);   // 0x00f47380

struct Object_d37c90 {
    ~Object_d37c90();        // 0x00d37b60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d37c90
void* Object_d37c90::DeletingDtor(unsigned int flags)
{
    this->~Object_d37c90();
    if (flags & 1)
        Free_d37c90(this);
    return this;
}
