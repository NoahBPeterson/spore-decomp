// Scalar deleting destructor (0x0077f4f0): run the destructor (0x77f210), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_77f4f0(void* p);   // 0x00f47380

struct Object_77f4f0 {
    ~Object_77f4f0();        // 0x0077f210
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0077f4f0
void* Object_77f4f0::DeletingDtor(unsigned int flags)
{
    this->~Object_77f4f0();
    if (flags & 1)
        Free_77f4f0(this);
    return this;
}
