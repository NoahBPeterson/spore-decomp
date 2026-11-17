// Scalar deleting destructor (0x00dd18f0): run the destructor (0xdd1670), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_dd18f0(void* p);   // 0x00f47380

struct Object_dd18f0 {
    ~Object_dd18f0();        // 0x00dd1670
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00dd18f0
void* Object_dd18f0::DeletingDtor(unsigned int flags)
{
    this->~Object_dd18f0();
    if (flags & 1)
        Free_dd18f0(this);
    return this;
}
