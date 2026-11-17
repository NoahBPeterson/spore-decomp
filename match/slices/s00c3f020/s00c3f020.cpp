// Scalar deleting destructor (0x00c3f020): run the destructor (0xc3ec40), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c3f020(void* p);   // 0x00f47380

struct Object_c3f020 {
    ~Object_c3f020();        // 0x00c3ec40
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c3f020
void* Object_c3f020::DeletingDtor(unsigned int flags)
{
    this->~Object_c3f020();
    if (flags & 1)
        Free_c3f020(this);
    return this;
}
