// Scalar deleting destructor (0x007662b0): run the destructor (0x766250), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7662b0(void* p);   // 0x00f47380

struct Object_7662b0 {
    ~Object_7662b0();        // 0x00766250
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007662b0
void* Object_7662b0::DeletingDtor(unsigned int flags)
{
    this->~Object_7662b0();
    if (flags & 1)
        Free_7662b0(this);
    return this;
}
