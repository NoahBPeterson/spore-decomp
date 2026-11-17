// Scalar deleting destructor (0x0104fa70): run the destructor (0x104f740), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_104fa70(void* p);   // 0x00f47380

struct Object_104fa70 {
    ~Object_104fa70();        // 0x0104f740
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0104fa70
void* Object_104fa70::DeletingDtor(unsigned int flags)
{
    this->~Object_104fa70();
    if (flags & 1)
        Free_104fa70(this);
    return this;
}
