// Scalar deleting destructor (0x005fd080): run the destructor (0x5fb900), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5fd080(void* p);   // 0x00f47380

struct Object_5fd080 {
    ~Object_5fd080();        // 0x005fb900
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005fd080
void* Object_5fd080::DeletingDtor(unsigned int flags)
{
    this->~Object_5fd080();
    if (flags & 1)
        Free_5fd080(this);
    return this;
}
