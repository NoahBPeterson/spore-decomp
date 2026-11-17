// Scalar deleting destructor (0x006efc50): run the destructor (0x6ee4f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6efc50(void* p);   // 0x00f47380

struct Object_6efc50 {
    ~Object_6efc50();        // 0x006ee4f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006efc50
void* Object_6efc50::DeletingDtor(unsigned int flags)
{
    this->~Object_6efc50();
    if (flags & 1)
        Free_6efc50(this);
    return this;
}
