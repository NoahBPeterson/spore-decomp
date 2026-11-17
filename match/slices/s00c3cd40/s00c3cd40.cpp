// Scalar deleting destructor (0x00c3cd40): run the destructor (0xc3b9a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c3cd40(void* p);   // 0x00f47380

struct Object_c3cd40 {
    ~Object_c3cd40();        // 0x00c3b9a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c3cd40
void* Object_c3cd40::DeletingDtor(unsigned int flags)
{
    this->~Object_c3cd40();
    if (flags & 1)
        Free_c3cd40(this);
    return this;
}
