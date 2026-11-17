// Scalar deleting destructor (0x00a17c50): run the destructor (0xa17910), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a17c50(void* p);   // 0x00f47380

struct Object_a17c50 {
    ~Object_a17c50();        // 0x00a17910
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a17c50
void* Object_a17c50::DeletingDtor(unsigned int flags)
{
    this->~Object_a17c50();
    if (flags & 1)
        Free_a17c50(this);
    return this;
}
