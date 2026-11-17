// Scalar deleting destructor (0x00944830): run the destructor (0x944570), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_944830(void* p);   // 0x00f47380

struct Object_944830 {
    ~Object_944830();        // 0x00944570
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00944830
void* Object_944830::DeletingDtor(unsigned int flags)
{
    this->~Object_944830();
    if (flags & 1)
        Free_944830(this);
    return this;
}
