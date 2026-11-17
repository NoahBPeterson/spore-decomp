// Scalar deleting destructor (0x0107fbc0): run the destructor (0x107f6c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_107fbc0(void* p);   // 0x00f47380

struct Object_107fbc0 {
    ~Object_107fbc0();        // 0x0107f6c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0107fbc0
void* Object_107fbc0::DeletingDtor(unsigned int flags)
{
    this->~Object_107fbc0();
    if (flags & 1)
        Free_107fbc0(this);
    return this;
}
