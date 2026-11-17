// Scalar deleting destructor (0x00de6e60): run the destructor (0xde6170), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_de6e60(void* p);   // 0x00f47380

struct Object_de6e60 {
    ~Object_de6e60();        // 0x00de6170
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00de6e60
void* Object_de6e60::DeletingDtor(unsigned int flags)
{
    this->~Object_de6e60();
    if (flags & 1)
        Free_de6e60(this);
    return this;
}
