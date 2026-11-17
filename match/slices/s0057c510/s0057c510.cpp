// Scalar deleting destructor (0x0057c510): run the destructor (0x57c4b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_57c510(void* p);   // 0x00f47380

struct Object_57c510 {
    ~Object_57c510();        // 0x0057c4b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0057c510
void* Object_57c510::DeletingDtor(unsigned int flags)
{
    this->~Object_57c510();
    if (flags & 1)
        Free_57c510(this);
    return this;
}
