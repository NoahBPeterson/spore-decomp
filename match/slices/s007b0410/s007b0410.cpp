// Scalar deleting destructor (0x007b0410): run the destructor (0x7b0160), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b0410(void* p);   // 0x00f47380

struct Object_7b0410 {
    ~Object_7b0410();        // 0x007b0160
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b0410
void* Object_7b0410::DeletingDtor(unsigned int flags)
{
    this->~Object_7b0410();
    if (flags & 1)
        Free_7b0410(this);
    return this;
}
