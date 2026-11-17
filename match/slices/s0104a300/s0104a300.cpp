// Scalar deleting destructor (0x0104a300): run the destructor (0x104a210), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_104a300(void* p);   // 0x00f47380

struct Object_104a300 {
    ~Object_104a300();        // 0x0104a210
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0104a300
void* Object_104a300::DeletingDtor(unsigned int flags)
{
    this->~Object_104a300();
    if (flags & 1)
        Free_104a300(this);
    return this;
}
