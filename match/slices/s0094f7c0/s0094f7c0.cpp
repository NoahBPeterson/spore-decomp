// Scalar deleting destructor (0x0094f7c0): run the destructor (0x931e70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_94f7c0(void* p);   // 0x00f47380

struct Object_94f7c0 {
    ~Object_94f7c0();        // 0x00931e70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0094f7c0
void* Object_94f7c0::DeletingDtor(unsigned int flags)
{
    this->~Object_94f7c0();
    if (flags & 1)
        Free_94f7c0(this);
    return this;
}
