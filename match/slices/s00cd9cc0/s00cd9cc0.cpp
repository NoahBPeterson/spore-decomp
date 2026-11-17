// Scalar deleting destructor (0x00cd9cc0): run the destructor (0xcd7d90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_cd9cc0(void* p);   // 0x00f47380

struct Object_cd9cc0 {
    ~Object_cd9cc0();        // 0x00cd7d90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cd9cc0
void* Object_cd9cc0::DeletingDtor(unsigned int flags)
{
    this->~Object_cd9cc0();
    if (flags & 1)
        Free_cd9cc0(this);
    return this;
}
