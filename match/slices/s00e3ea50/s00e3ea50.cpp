// Scalar deleting destructor (0x00e3ea50): run the destructor (0xe3dca0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e3ea50(void* p);   // 0x00f47380

struct Object_e3ea50 {
    ~Object_e3ea50();        // 0x00e3dca0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e3ea50
void* Object_e3ea50::DeletingDtor(unsigned int flags)
{
    this->~Object_e3ea50();
    if (flags & 1)
        Free_e3ea50(this);
    return this;
}
