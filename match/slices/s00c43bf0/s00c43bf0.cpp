// Scalar deleting destructor (0x00c43bf0): run the destructor (0xc432e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c43bf0(void* p);   // 0x00f47380

struct Object_c43bf0 {
    ~Object_c43bf0();        // 0x00c432e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c43bf0
void* Object_c43bf0::DeletingDtor(unsigned int flags)
{
    this->~Object_c43bf0();
    if (flags & 1)
        Free_c43bf0(this);
    return this;
}
