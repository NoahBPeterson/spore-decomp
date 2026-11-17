// Scalar deleting destructor (0x01064ee0): run the destructor (0x1064ac0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_1064ee0(void* p);   // 0x00f47380

struct Object_1064ee0 {
    ~Object_1064ee0();        // 0x01064ac0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x01064ee0
void* Object_1064ee0::DeletingDtor(unsigned int flags)
{
    this->~Object_1064ee0();
    if (flags & 1)
        Free_1064ee0(this);
    return this;
}
