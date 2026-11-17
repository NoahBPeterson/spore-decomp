// Scalar deleting destructor (0x00cd3bd0): run the destructor (0xcd3ab0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_cd3bd0(void* p);   // 0x00f47380

struct Object_cd3bd0 {
    ~Object_cd3bd0();        // 0x00cd3ab0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cd3bd0
void* Object_cd3bd0::DeletingDtor(unsigned int flags)
{
    this->~Object_cd3bd0();
    if (flags & 1)
        Free_cd3bd0(this);
    return this;
}
