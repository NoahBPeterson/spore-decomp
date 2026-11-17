// Scalar deleting destructor (0x0093b610): run the destructor (0x93b5a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_93b610(void* p);   // 0x00f47380

struct Object_93b610 {
    ~Object_93b610();        // 0x0093b5a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0093b610
void* Object_93b610::DeletingDtor(unsigned int flags)
{
    this->~Object_93b610();
    if (flags & 1)
        Free_93b610(this);
    return this;
}
