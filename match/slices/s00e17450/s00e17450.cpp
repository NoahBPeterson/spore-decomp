// Scalar deleting destructor (0x00e17450): run the destructor (0xe15910), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e17450(void* p);   // 0x00f47380

struct Object_e17450 {
    ~Object_e17450();        // 0x00e15910
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e17450
void* Object_e17450::DeletingDtor(unsigned int flags)
{
    this->~Object_e17450();
    if (flags & 1)
        Free_e17450(this);
    return this;
}
