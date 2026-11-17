// Scalar deleting destructor (0x00b7c270): run the destructor (0xb7b780), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b7c270(void* p);   // 0x00f47380

struct Object_b7c270 {
    ~Object_b7c270();        // 0x00b7b780
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b7c270
void* Object_b7c270::DeletingDtor(unsigned int flags)
{
    this->~Object_b7c270();
    if (flags & 1)
        Free_b7c270(this);
    return this;
}
