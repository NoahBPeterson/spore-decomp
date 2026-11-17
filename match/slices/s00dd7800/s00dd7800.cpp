// Scalar deleting destructor (0x00dd7800): run the destructor (0xdd7770), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_dd7800(void* p);   // 0x00f47380

struct Object_dd7800 {
    ~Object_dd7800();        // 0x00dd7770
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00dd7800
void* Object_dd7800::DeletingDtor(unsigned int flags)
{
    this->~Object_dd7800();
    if (flags & 1)
        Free_dd7800(this);
    return this;
}
