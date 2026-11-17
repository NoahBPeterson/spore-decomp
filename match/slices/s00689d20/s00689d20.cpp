// Scalar deleting destructor (0x00689d20): run the destructor (0x689810), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_689d20(void* p);   // 0x00f47380

struct Object_689d20 {
    ~Object_689d20();        // 0x00689810
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00689d20
void* Object_689d20::DeletingDtor(unsigned int flags)
{
    this->~Object_689d20();
    if (flags & 1)
        Free_689d20(this);
    return this;
}
