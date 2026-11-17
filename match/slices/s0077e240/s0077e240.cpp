// Scalar deleting destructor (0x0077e240): run the destructor (0x77d8c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_77e240(void* p);   // 0x00f47380

struct Object_77e240 {
    ~Object_77e240();        // 0x0077d8c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0077e240
void* Object_77e240::DeletingDtor(unsigned int flags)
{
    this->~Object_77e240();
    if (flags & 1)
        Free_77e240(this);
    return this;
}
