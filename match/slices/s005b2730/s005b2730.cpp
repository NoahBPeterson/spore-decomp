// Scalar deleting destructor (0x005b2730): run the destructor (0x5b24a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5b2730(void* p);   // 0x00f47380

struct Object_5b2730 {
    ~Object_5b2730();        // 0x005b24a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005b2730
void* Object_5b2730::DeletingDtor(unsigned int flags)
{
    this->~Object_5b2730();
    if (flags & 1)
        Free_5b2730(this);
    return this;
}
