// Scalar deleting destructor (0x0082f5a0): run the destructor (0x82f500), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_82f5a0(void* p);   // 0x00f47380

struct Object_82f5a0 {
    ~Object_82f5a0();        // 0x0082f500
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0082f5a0
void* Object_82f5a0::DeletingDtor(unsigned int flags)
{
    this->~Object_82f5a0();
    if (flags & 1)
        Free_82f5a0(this);
    return this;
}
