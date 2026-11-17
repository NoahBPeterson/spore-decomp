// Scalar deleting destructor (0x0067b350): run the destructor (0x67b2f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_67b350(void* p);   // 0x00f47380

struct Object_67b350 {
    ~Object_67b350();        // 0x0067b2f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0067b350
void* Object_67b350::DeletingDtor(unsigned int flags)
{
    this->~Object_67b350();
    if (flags & 1)
        Free_67b350(this);
    return this;
}
