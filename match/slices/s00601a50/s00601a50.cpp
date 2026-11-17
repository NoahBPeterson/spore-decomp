// Scalar deleting destructor (0x00601a50): run the destructor (0x601730), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_601a50(void* p);   // 0x00f47380

struct Object_601a50 {
    ~Object_601a50();        // 0x00601730
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00601a50
void* Object_601a50::DeletingDtor(unsigned int flags)
{
    this->~Object_601a50();
    if (flags & 1)
        Free_601a50(this);
    return this;
}
