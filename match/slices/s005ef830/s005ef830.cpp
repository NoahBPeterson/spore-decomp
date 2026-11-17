// Scalar deleting destructor (0x005ef830): run the destructor (0x5ef760), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5ef830(void* p);   // 0x00f47380

struct Object_5ef830 {
    ~Object_5ef830();        // 0x005ef760
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005ef830
void* Object_5ef830::DeletingDtor(unsigned int flags)
{
    this->~Object_5ef830();
    if (flags & 1)
        Free_5ef830(this);
    return this;
}
