// Scalar deleting destructor (0x0075a600): run the destructor (0x75a550), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_75a600(void* p);   // 0x00f47380

struct Object_75a600 {
    ~Object_75a600();        // 0x0075a550
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0075a600
void* Object_75a600::DeletingDtor(unsigned int flags)
{
    this->~Object_75a600();
    if (flags & 1)
        Free_75a600(this);
    return this;
}
