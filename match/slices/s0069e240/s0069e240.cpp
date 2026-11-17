// Scalar deleting destructor (0x0069e240): run the destructor (0x69d860), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_69e240(void* p);   // 0x00f47380

struct Object_69e240 {
    ~Object_69e240();        // 0x0069d860
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0069e240
void* Object_69e240::DeletingDtor(unsigned int flags)
{
    this->~Object_69e240();
    if (flags & 1)
        Free_69e240(this);
    return this;
}
