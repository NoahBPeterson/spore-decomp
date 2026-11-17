// Scalar deleting destructor (0x005b8670): run the destructor (0x5b84f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5b8670(void* p);   // 0x00f47380

struct Object_5b8670 {
    ~Object_5b8670();        // 0x005b84f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005b8670
void* Object_5b8670::DeletingDtor(unsigned int flags)
{
    this->~Object_5b8670();
    if (flags & 1)
        Free_5b8670(this);
    return this;
}
