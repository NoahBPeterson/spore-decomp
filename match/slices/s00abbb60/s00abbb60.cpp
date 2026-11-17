// Scalar deleting destructor (0x00abbb60): run the destructor (0xabb9e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_abbb60(void* p);   // 0x00f47380

struct Object_abbb60 {
    ~Object_abbb60();        // 0x00abb9e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00abbb60
void* Object_abbb60::DeletingDtor(unsigned int flags)
{
    this->~Object_abbb60();
    if (flags & 1)
        Free_abbb60(this);
    return this;
}
