// Scalar deleting destructor (0x00e91b80): run the destructor (0xe915f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e91b80(void* p);   // 0x00f47380

struct Object_e91b80 {
    ~Object_e91b80();        // 0x00e915f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e91b80
void* Object_e91b80::DeletingDtor(unsigned int flags)
{
    this->~Object_e91b80();
    if (flags & 1)
        Free_e91b80(this);
    return this;
}
