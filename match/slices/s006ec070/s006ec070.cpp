// Scalar deleting destructor (0x006ec070): run the destructor (0x6ec000), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6ec070(void* p);   // 0x00f47380

struct Object_6ec070 {
    ~Object_6ec070();        // 0x006ec000
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006ec070
void* Object_6ec070::DeletingDtor(unsigned int flags)
{
    this->~Object_6ec070();
    if (flags & 1)
        Free_6ec070(this);
    return this;
}
