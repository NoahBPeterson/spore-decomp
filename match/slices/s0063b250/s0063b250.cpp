// Scalar deleting destructor (0x0063b250): run the destructor (0x639b70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_63b250(void* p);   // 0x00f47380

struct Object_63b250 {
    ~Object_63b250();        // 0x00639b70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0063b250
void* Object_63b250::DeletingDtor(unsigned int flags)
{
    this->~Object_63b250();
    if (flags & 1)
        Free_63b250(this);
    return this;
}
