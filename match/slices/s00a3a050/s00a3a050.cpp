// Scalar deleting destructor (0x00a3a050): run the destructor (0xa39ff0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a3a050(void* p);   // 0x00f47380

struct Object_a3a050 {
    ~Object_a3a050();        // 0x00a39ff0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a3a050
void* Object_a3a050::DeletingDtor(unsigned int flags)
{
    this->~Object_a3a050();
    if (flags & 1)
        Free_a3a050(this);
    return this;
}
