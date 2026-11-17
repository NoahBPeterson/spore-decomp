// Scalar deleting destructor (0x007b6c50): run the destructor (0x7b6bd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b6c50(void* p);   // 0x00f47380

struct Object_7b6c50 {
    ~Object_7b6c50();        // 0x007b6bd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b6c50
void* Object_7b6c50::DeletingDtor(unsigned int flags)
{
    this->~Object_7b6c50();
    if (flags & 1)
        Free_7b6c50(this);
    return this;
}
