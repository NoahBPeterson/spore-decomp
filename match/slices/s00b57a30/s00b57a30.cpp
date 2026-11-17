// Scalar deleting destructor (0x00b57a30): run the destructor (0xb57720), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b57a30(void* p);   // 0x00f47380

struct Object_b57a30 {
    ~Object_b57a30();        // 0x00b57720
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b57a30
void* Object_b57a30::DeletingDtor(unsigned int flags)
{
    this->~Object_b57a30();
    if (flags & 1)
        Free_b57a30(this);
    return this;
}
