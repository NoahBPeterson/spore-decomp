// Scalar deleting destructor (0x00b37b50): run the destructor (0xb37440), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b37b50(void* p);   // 0x00f47380

struct Object_b37b50 {
    ~Object_b37b50();        // 0x00b37440
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b37b50
void* Object_b37b50::DeletingDtor(unsigned int flags)
{
    this->~Object_b37b50();
    if (flags & 1)
        Free_b37b50(this);
    return this;
}
