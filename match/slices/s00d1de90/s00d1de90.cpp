// Scalar deleting destructor (0x00d1de90): run the destructor (0xd1de10), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d1de90(void* p);   // 0x00f47380

struct Object_d1de90 {
    ~Object_d1de90();        // 0x00d1de10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d1de90
void* Object_d1de90::DeletingDtor(unsigned int flags)
{
    this->~Object_d1de90();
    if (flags & 1)
        Free_d1de90(this);
    return this;
}
