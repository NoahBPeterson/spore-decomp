// Scalar deleting destructor (0x007b2950): run the destructor (0x7b2900), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b2950(void* p);   // 0x00f47380

struct Object_7b2950 {
    ~Object_7b2950();        // 0x007b2900
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b2950
void* Object_7b2950::DeletingDtor(unsigned int flags)
{
    this->~Object_7b2950();
    if (flags & 1)
        Free_7b2950(this);
    return this;
}
