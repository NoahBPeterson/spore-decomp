// Scalar deleting destructor (0x005c1110): run the destructor (0x5c1050), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5c1110(void* p);   // 0x00f47380

struct Object_5c1110 {
    ~Object_5c1110();        // 0x005c1050
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005c1110
void* Object_5c1110::DeletingDtor(unsigned int flags)
{
    this->~Object_5c1110();
    if (flags & 1)
        Free_5c1110(this);
    return this;
}
