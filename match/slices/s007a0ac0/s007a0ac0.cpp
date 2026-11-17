// Scalar deleting destructor (0x007a0ac0): run the destructor (0x7a09f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7a0ac0(void* p);   // 0x00f47380

struct Object_7a0ac0 {
    ~Object_7a0ac0();        // 0x007a09f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007a0ac0
void* Object_7a0ac0::DeletingDtor(unsigned int flags)
{
    this->~Object_7a0ac0();
    if (flags & 1)
        Free_7a0ac0(this);
    return this;
}
