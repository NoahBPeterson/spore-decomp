// Scalar deleting destructor (0x00b864e0): run the destructor (0xb85a30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b864e0(void* p);   // 0x00f47380

struct Object_b864e0 {
    ~Object_b864e0();        // 0x00b85a30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b864e0
void* Object_b864e0::DeletingDtor(unsigned int flags)
{
    this->~Object_b864e0();
    if (flags & 1)
        Free_b864e0(this);
    return this;
}
