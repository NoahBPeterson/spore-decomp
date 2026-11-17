// Scalar deleting destructor (0x007691e0): run the destructor (0x768540), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7691e0(void* p);   // 0x00f47380

struct Object_7691e0 {
    ~Object_7691e0();        // 0x00768540
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007691e0
void* Object_7691e0::DeletingDtor(unsigned int flags)
{
    this->~Object_7691e0();
    if (flags & 1)
        Free_7691e0(this);
    return this;
}
