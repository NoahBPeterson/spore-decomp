// Scalar deleting destructor (0x00605ec0): run the destructor (0x605cb0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_605ec0(void* p);   // 0x00f47380

struct Object_605ec0 {
    ~Object_605ec0();        // 0x00605cb0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00605ec0
void* Object_605ec0::DeletingDtor(unsigned int flags)
{
    this->~Object_605ec0();
    if (flags & 1)
        Free_605ec0(this);
    return this;
}
