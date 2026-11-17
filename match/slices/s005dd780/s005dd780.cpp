// Scalar deleting destructor (0x005dd780): run the destructor (0x5dc6c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5dd780(void* p);   // 0x00f47380

struct Object_5dd780 {
    ~Object_5dd780();        // 0x005dc6c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005dd780
void* Object_5dd780::DeletingDtor(unsigned int flags)
{
    this->~Object_5dd780();
    if (flags & 1)
        Free_5dd780(this);
    return this;
}
