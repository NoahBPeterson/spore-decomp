// Scalar deleting destructor (0x0082aa00): run the destructor (0x82a0d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_82aa00(void* p);   // 0x00f47380

struct Object_82aa00 {
    ~Object_82aa00();        // 0x0082a0d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0082aa00
void* Object_82aa00::DeletingDtor(unsigned int flags)
{
    this->~Object_82aa00();
    if (flags & 1)
        Free_82aa00(this);
    return this;
}
