// Scalar deleting destructor (0x005d4950): run the destructor (0x5d35c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5d4950(void* p);   // 0x00f47380

struct Object_5d4950 {
    ~Object_5d4950();        // 0x005d35c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005d4950
void* Object_5d4950::DeletingDtor(unsigned int flags)
{
    this->~Object_5d4950();
    if (flags & 1)
        Free_5d4950(this);
    return this;
}
