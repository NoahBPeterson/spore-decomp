// Scalar deleting destructor (0x01139f00): run the destructor (0x1139eb0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_1139f00(void* p);   // 0x00f47380

struct Object_1139f00 {
    ~Object_1139f00();        // 0x01139eb0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x01139f00
void* Object_1139f00::DeletingDtor(unsigned int flags)
{
    this->~Object_1139f00();
    if (flags & 1)
        Free_1139f00(this);
    return this;
}
