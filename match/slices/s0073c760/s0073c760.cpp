// Scalar deleting destructor (0x0073c760): run the destructor (0x73a9e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_73c760(void* p);   // 0x00f47380

struct Object_73c760 {
    ~Object_73c760();        // 0x0073a9e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0073c760
void* Object_73c760::DeletingDtor(unsigned int flags)
{
    this->~Object_73c760();
    if (flags & 1)
        Free_73c760(this);
    return this;
}
