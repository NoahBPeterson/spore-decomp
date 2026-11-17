// Scalar deleting destructor (0x00ebc180): run the destructor (0xebbf00), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ebc180(void* p);   // 0x00f47380

struct Object_ebc180 {
    ~Object_ebc180();        // 0x00ebbf00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ebc180
void* Object_ebc180::DeletingDtor(unsigned int flags)
{
    this->~Object_ebc180();
    if (flags & 1)
        Free_ebc180(this);
    return this;
}
