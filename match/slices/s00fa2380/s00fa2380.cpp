// Scalar deleting destructor (0x00fa2380): run the destructor (0xfa0780), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_fa2380(void* p);   // 0x00f47380

struct Object_fa2380 {
    ~Object_fa2380();        // 0x00fa0780
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fa2380
void* Object_fa2380::DeletingDtor(unsigned int flags)
{
    this->~Object_fa2380();
    if (flags & 1)
        Free_fa2380(this);
    return this;
}
