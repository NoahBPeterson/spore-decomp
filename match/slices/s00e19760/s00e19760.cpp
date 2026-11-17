// Scalar deleting destructor (0x00e19760): run the destructor (0xe193f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e19760(void* p);   // 0x00f47380

struct Object_e19760 {
    ~Object_e19760();        // 0x00e193f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e19760
void* Object_e19760::DeletingDtor(unsigned int flags)
{
    this->~Object_e19760();
    if (flags & 1)
        Free_e19760(this);
    return this;
}
