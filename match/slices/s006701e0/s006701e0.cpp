// Scalar deleting destructor (0x006701e0): run the destructor (0x66fee0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6701e0(void* p);   // 0x00f47380

struct Object_6701e0 {
    ~Object_6701e0();        // 0x0066fee0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006701e0
void* Object_6701e0::DeletingDtor(unsigned int flags)
{
    this->~Object_6701e0();
    if (flags & 1)
        Free_6701e0(this);
    return this;
}
