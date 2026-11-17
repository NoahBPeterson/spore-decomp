// Scalar deleting destructor (0x00dfbd50): run the destructor (0xdfbac0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_dfbd50(void* p);   // 0x00f47380

struct Object_dfbd50 {
    ~Object_dfbd50();        // 0x00dfbac0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00dfbd50
void* Object_dfbd50::DeletingDtor(unsigned int flags)
{
    this->~Object_dfbd50();
    if (flags & 1)
        Free_dfbd50(this);
    return this;
}
