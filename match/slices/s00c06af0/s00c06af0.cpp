// Scalar deleting destructor (0x00c06af0): run the destructor (0xc061b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c06af0(void* p);   // 0x00f47380

struct Object_c06af0 {
    ~Object_c06af0();        // 0x00c061b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c06af0
void* Object_c06af0::DeletingDtor(unsigned int flags)
{
    this->~Object_c06af0();
    if (flags & 1)
        Free_c06af0(this);
    return this;
}
