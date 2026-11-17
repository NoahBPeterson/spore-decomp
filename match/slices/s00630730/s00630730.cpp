// Scalar deleting destructor (0x00630730): run the destructor (0x6306f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_630730(void* p);   // 0x00f47380

struct Object_630730 {
    ~Object_630730();        // 0x006306f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00630730
void* Object_630730::DeletingDtor(unsigned int flags)
{
    this->~Object_630730();
    if (flags & 1)
        Free_630730(this);
    return this;
}
