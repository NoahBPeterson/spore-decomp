// Scalar deleting destructor (0x00ba2ad0): run the destructor (0x5725a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ba2ad0(void* p);   // 0x00f47380

struct Object_ba2ad0 {
    ~Object_ba2ad0();        // 0x005725a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ba2ad0
void* Object_ba2ad0::DeletingDtor(unsigned int flags)
{
    this->~Object_ba2ad0();
    if (flags & 1)
        Free_ba2ad0(this);
    return this;
}
