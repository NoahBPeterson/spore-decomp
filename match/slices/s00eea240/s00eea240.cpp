// Scalar deleting destructor (0x00eea240): run the destructor (0xee9c70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_eea240(void* p);   // 0x00f47380

struct Object_eea240 {
    ~Object_eea240();        // 0x00ee9c70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00eea240
void* Object_eea240::DeletingDtor(unsigned int flags)
{
    this->~Object_eea240();
    if (flags & 1)
        Free_eea240(this);
    return this;
}
