// Scalar deleting destructor (0x00ecea90): run the destructor (0xecdd70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ecea90(void* p);   // 0x00f47380

struct Object_ecea90 {
    ~Object_ecea90();        // 0x00ecdd70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ecea90
void* Object_ecea90::DeletingDtor(unsigned int flags)
{
    this->~Object_ecea90();
    if (flags & 1)
        Free_ecea90(this);
    return this;
}
