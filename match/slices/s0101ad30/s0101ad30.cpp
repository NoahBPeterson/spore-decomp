// Scalar deleting destructor (0x0101ad30): run the destructor (0x1018060), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_101ad30(void* p);   // 0x00f47380

struct Object_101ad30 {
    ~Object_101ad30();        // 0x01018060
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0101ad30
void* Object_101ad30::DeletingDtor(unsigned int flags)
{
    this->~Object_101ad30();
    if (flags & 1)
        Free_101ad30(this);
    return this;
}
