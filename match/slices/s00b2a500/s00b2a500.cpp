// Scalar deleting destructor (0x00b2a500): run the destructor (0xff38a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b2a500(void* p);   // 0x00f47380

struct Object_b2a500 {
    ~Object_b2a500();        // 0x00ff38a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b2a500
void* Object_b2a500::DeletingDtor(unsigned int flags)
{
    this->~Object_b2a500();
    if (flags & 1)
        Free_b2a500(this);
    return this;
}
