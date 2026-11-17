// Scalar deleting destructor (0x007a6850): run the destructor (0x7a62c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7a6850(void* p);   // 0x00f47380

struct Object_7a6850 {
    ~Object_7a6850();        // 0x007a62c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007a6850
void* Object_7a6850::DeletingDtor(unsigned int flags)
{
    this->~Object_7a6850();
    if (flags & 1)
        Free_7a6850(this);
    return this;
}
