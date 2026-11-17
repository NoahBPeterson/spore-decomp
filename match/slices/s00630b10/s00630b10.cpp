// Scalar deleting destructor (0x00630b10): run the destructor (0x630930), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_630b10(void* p);   // 0x00f47380

struct Object_630b10 {
    ~Object_630b10();        // 0x00630930
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00630b10
void* Object_630b10::DeletingDtor(unsigned int flags)
{
    this->~Object_630b10();
    if (flags & 1)
        Free_630b10(this);
    return this;
}
