// Scalar deleting destructor (0x0063f120): run the destructor (0x63f0e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_63f120(void* p);   // 0x00f47380

struct Object_63f120 {
    ~Object_63f120();        // 0x0063f0e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0063f120
void* Object_63f120::DeletingDtor(unsigned int flags)
{
    this->~Object_63f120();
    if (flags & 1)
        Free_63f120(this);
    return this;
}
