// Scalar deleting destructor (0x006960d0): run the destructor (0x695e80), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6960d0(void* p);   // 0x00f47380

struct Object_6960d0 {
    ~Object_6960d0();        // 0x00695e80
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006960d0
void* Object_6960d0::DeletingDtor(unsigned int flags)
{
    this->~Object_6960d0();
    if (flags & 1)
        Free_6960d0(this);
    return this;
}
