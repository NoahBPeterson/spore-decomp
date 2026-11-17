// Scalar deleting destructor (0x00fe6ab0): run the destructor (0xfe6a00), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_fe6ab0(void* p);   // 0x00f47380

struct Object_fe6ab0 {
    ~Object_fe6ab0();        // 0x00fe6a00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fe6ab0
void* Object_fe6ab0::DeletingDtor(unsigned int flags)
{
    this->~Object_fe6ab0();
    if (flags & 1)
        Free_fe6ab0(this);
    return this;
}
