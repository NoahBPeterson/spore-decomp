// Scalar deleting destructor (0x00b02db0): run the destructor (0xb01a40), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b02db0(void* p);   // 0x00f47380

struct Object_b02db0 {
    ~Object_b02db0();        // 0x00b01a40
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b02db0
void* Object_b02db0::DeletingDtor(unsigned int flags)
{
    this->~Object_b02db0();
    if (flags & 1)
        Free_b02db0(this);
    return this;
}
