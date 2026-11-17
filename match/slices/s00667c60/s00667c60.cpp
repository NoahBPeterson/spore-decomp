// Scalar deleting destructor (0x00667c60): run the destructor (0x6678f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_667c60(void* p);   // 0x00f47380

struct Object_667c60 {
    ~Object_667c60();        // 0x006678f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00667c60
void* Object_667c60::DeletingDtor(unsigned int flags)
{
    this->~Object_667c60();
    if (flags & 1)
        Free_667c60(this);
    return this;
}
