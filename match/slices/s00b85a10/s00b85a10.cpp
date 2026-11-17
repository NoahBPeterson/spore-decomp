// Scalar deleting destructor (0x00b85a10): run the destructor (0xb85110), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b85a10(void* p);   // 0x00f47380

struct Object_b85a10 {
    ~Object_b85a10();        // 0x00b85110
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b85a10
void* Object_b85a10::DeletingDtor(unsigned int flags)
{
    this->~Object_b85a10();
    if (flags & 1)
        Free_b85a10(this);
    return this;
}
