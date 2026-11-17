// Scalar deleting destructor (0x00e15470): run the destructor (0xe13210), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e15470(void* p);   // 0x00f47380

struct Object_e15470 {
    ~Object_e15470();        // 0x00e13210
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e15470
void* Object_e15470::DeletingDtor(unsigned int flags)
{
    this->~Object_e15470();
    if (flags & 1)
        Free_e15470(this);
    return this;
}
