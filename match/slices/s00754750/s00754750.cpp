// Scalar deleting destructor (0x00754750): run the destructor (0x754140), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_754750(void* p);   // 0x00f47380

struct Object_754750 {
    ~Object_754750();        // 0x00754140
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00754750
void* Object_754750::DeletingDtor(unsigned int flags)
{
    this->~Object_754750();
    if (flags & 1)
        Free_754750(this);
    return this;
}
