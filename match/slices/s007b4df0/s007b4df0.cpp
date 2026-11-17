// Scalar deleting destructor (0x007b4df0): run the destructor (0x7b4d70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b4df0(void* p);   // 0x00f47380

struct Object_7b4df0 {
    ~Object_7b4df0();        // 0x007b4d70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b4df0
void* Object_7b4df0::DeletingDtor(unsigned int flags)
{
    this->~Object_7b4df0();
    if (flags & 1)
        Free_7b4df0(this);
    return this;
}
