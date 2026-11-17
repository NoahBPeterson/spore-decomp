// Scalar deleting destructor (0x007b8c70): run the destructor (0x7b8700), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b8c70(void* p);   // 0x00f47380

struct Object_7b8c70 {
    ~Object_7b8c70();        // 0x007b8700
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b8c70
void* Object_7b8c70::DeletingDtor(unsigned int flags)
{
    this->~Object_7b8c70();
    if (flags & 1)
        Free_7b8c70(this);
    return this;
}
