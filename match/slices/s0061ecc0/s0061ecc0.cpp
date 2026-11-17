// Scalar deleting destructor (0x0061ecc0): run the destructor (0x61e540), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_61ecc0(void* p);   // 0x00f47380

struct Object_61ecc0 {
    ~Object_61ecc0();        // 0x0061e540
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0061ecc0
void* Object_61ecc0::DeletingDtor(unsigned int flags)
{
    this->~Object_61ecc0();
    if (flags & 1)
        Free_61ecc0(this);
    return this;
}
